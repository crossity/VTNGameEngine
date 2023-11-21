#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <SDL2/SDL.h>

#include "vtn_scripter.hpp"
#include "vtn_types.hpp"
#include "vtn_draw.hpp"
#include "vtn_math.hpp"

vtnMESH meshes[1000];
int meshes_size = 0;
vtnTEXTURE *textures[1000];
int textures_size = 0;

bool IsSpace( char c )
{
    return c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '[' || c == ']' || c == ',';
}

std::vector<std::string> vtnGetWords( std::string FilePath )
{
    static const char SingleChars[] = {
        '`', ';', ':',
        '*', '/',
        '&', '%', '#', '~',
        '<', '>', '=', '|',
        '{', '}', '(', ')'
    };
    static const int SingleCharsSize = 17;
    std::ifstream file{FilePath};
    if (!file.is_open())
        throw std::runtime_error("failed to open file \"" + FilePath + "\"");
    char c;
    std::vector<std::string> words;
    std::string word;

    while (file >> std::noskipws >> c)
    {
        bool is_single = false;
        for (int i = 0; i < SingleCharsSize; i++)
            if (c == SingleChars[i])
            {
                is_single = true;
                break;
            }

        if (IsSpace(c))
        {
            if (word.size() > 0)
                words.push_back(word), word = "";
        }
        else if (is_single)
        {
            if (word.size() > 0)
                words.push_back(word), word = "";
            words.push_back({c});
        }
        else if (c == '"') {
            if (word.size() > 0)
                words.push_back(word);
            word = "";
            while (file >> std::noskipws >> c) { 
                if (c == '"')
                    break;
                word += c;
            }
            words.push_back(word);
            word = "";
        }
        else
            word += c;
    }
    if (word.size() > 0)
        words.push_back(word);


    file.close();
    return words;
}

void vtnCompile(vtnSCENE &scene, vtnORIGIN &origin, vtnNODE *node, std::vector<std::string> &words, int start) {
    if (node == nullptr)
        origin.add_child();
    else
        node->add_child();
    
    while (start < words.size() && words[start] != "}") {
        if (start > 0 && words[start] == "(") {
            if (words[start - 1] == "mesh") {
                std::vector<std::string> args;
                start++;
                while (start < words.size() && words[start] != ")")
                    args.push_back(words[start++]);
                
                if (args.size() < 1)
                    throw(std::runtime_error("not enough arguments for mesh"));

                std::string path = "";
                for (int i = 1; i < start; i++) {
                    if (words[i] == "=" && words[i - 1] == args[0]) {
                        path = words[i + 1];
                        break;
                    }
                }

                bool textured = false;
                if (args.size() >= 2) {
                    if (args[1] == "TEXTURED")
                        textured = true;
                    else if (args[1] == "UNTEXTURED")
                        textured = false;
                    else
                        textured = args[1][0] - '0';
                }
                
                if (path == "")
                    throw(std::runtime_error("no such mesh '" + args[0] + "'"));
                meshes[meshes_size++] = vtnMESH(&scene, path, textured);

                if (args.size() >= 3 && textured) {
                    std::string texture_path = "";
                    for (int i = 1; i < start; i++) {
                        if (words[i] == "=" && words[i - 1] == args[2]) {
                            texture_path = words[i + 1];
                            break;
                        }
                    }
                    textures[textures_size++] = nullptr;
                    vtnLoadFromPNG(&textures[textures_size - 1], texture_path);

                    meshes[meshes_size - 1].texturize(&textures[textures_size - 1]);
                }

                vtnVEC3 pos = vtnVEC3();
                if (args.size() >= 5 + textured) {
                    pos = vtnVEC3(atof(args[2 + textured].c_str()), atof(args[3 + textured].c_str()), atof(args[4 + textured].c_str()));
                }

                vtnVEC3 rot = vtnVEC3();
                if (args.size() >= 8 + textured) {
                    rot = vtnVEC3(atof(args[5 + textured].c_str()), atof(args[6 + textured].c_str()), atof(args[7 + textured].c_str()));
                }

                if (args.size() >= 11 + textured) {
                    vtnVEC3 color = vtnVEC3(atof(args[8 + textured].c_str()), atof(args[9 + textured].c_str()), atof(args[10 + textured].c_str()));
                    meshes[meshes_size - 1].colorize(color);
                }

                for (int i = meshes[meshes_size - 1].vstart; i <= meshes[meshes_size - 1].vend; i++)
                    scene.vert_buffer.v[i] = scene.vert_buffer.v[i] + pos;
                vtnRotate(vtnROTATION(vtnVEC3(), rot), scene.vert_buffer.v + meshes[meshes_size - 1].vstart, meshes[meshes_size - 1].vend - meshes[meshes_size - 1].vstart + 1);

                if (node == nullptr) {
                    origin.child[origin.child.size() - 1]->mesh = meshes[meshes_size - 1];
                }
                else {
                    node->child[node->child.size() - 1]->mesh = meshes[meshes_size - 1];
                }
            }
            else if (words[start - 1] == "pos") {
                std::vector<std::string> args;
                start++;
                while (start < words.size() && words[start] != ")")
                    args.push_back(words[start++]);
                
                if (args.size() < 1)
                    throw(std::runtime_error("not enough arguments for mesh"));

                vtnVEC3 pos = vtnVEC3(atof(args[0].c_str()), atof(args[1].c_str()), atof(args[2].c_str()));
                if (node == nullptr)
                    origin.child[origin.child.size() - 1]->pos = pos;
                else
                    node->child[node->child.size() - 1]->pos = pos;
            }
            else if (words[start - 1] == "rot") {
                std::vector<std::string> args;
                start++;
                while (start < words.size() && words[start] != ")")
                    args.push_back(words[start++]);
                
                if (args.size() < 1)
                    throw(std::runtime_error("not enough arguments for mesh"));

                vtnVEC3 rot = vtnVEC3(atof(args[0].c_str()), atof(args[1].c_str()), atof(args[2].c_str()));
                if (node == nullptr)
                    origin.child[origin.child.size() - 1]->rot = rot;
                else
                    node->child[node->child.size() - 1]->rot = rot;
            }
            else if (words[start - 1] == "add") {
                std::vector<std::string> args;
                start++;
                while (start < words.size() && words[start] != ")")
                    args.push_back(words[start++]);
                
                if (args.size() < 1)
                    throw(std::runtime_error("not enough arguments for mesh"));

                int ind = start;

                while (ind > 0) {
                    if (words[ind] == "{" && words[ind - 1] == args[0]) {
                        if (node == nullptr)
                            vtnCompile(scene, origin, origin.child[origin.child.size() - 1], words, ind);
                        else
                            vtnCompile(scene, origin, node->child[node->child.size() - 1], words, ind);
                        break;
                    }
                    ind--;
                }

                vtnVEC3 pos = vtnVEC3();
                if (args.size() >= 4) {
                    pos = vtnVEC3(atof(args[1].c_str()), atof(args[2].c_str()), atof(args[3].c_str()));
                }
                if (node == nullptr)
                    origin.child[origin.child.size() - 1]->child[origin.child[origin.child.size() - 1]->child.size() - 1]->pos = 
                        origin.child[origin.child.size() - 1]->child[origin.child[origin.child.size() - 1]->child.size() - 1]->pos + pos;
                else
                    origin.child[origin.child.size() - 1]->child[origin.child[origin.child.size() - 1]->child.size() - 1]->pos = 
                        origin.child[origin.child.size() - 1]->child[origin.child[origin.child.size() - 1]->child.size() - 1]->pos + pos;
            }
        }
        start++;
    }
}

void vtnLoadToScene(vtnSCENE &scene, vtnORIGIN &origin, std::string file_path) {
    std::vector<std::string> words = vtnGetWords(file_path);

    for (int i = 0; i < words.size(); i++) {
        if (words[i] == "$define") {
            for (int j = i + 3; j < words.size(); j++) {
                if (words[i + 1] == words[j])
                    words[j] = words[i + 2];
            }
        }
    }

    for (int w = 0; w < words.size(); w++) {
        if (words[w] == "(" && w > 0) {
            if (words[w - 1] == "place") {
                int ww = w;
                std::vector<std::string> args;
                w++;
                while (w < words.size() && words[w] != ")")
                    args.push_back(words[w++]);
                for (; ww >= 0 && !(words[ww] == args[0] && words[ww + 1] == "{"); ww--);
                vtnCompile(scene, origin, nullptr, words, ww);
            }
        }
    }
}

void vtnQuitScripter() {
    for (int i = 0; i < textures_size; i++)
        SDL_DestroyTexture(textures[i]);
}