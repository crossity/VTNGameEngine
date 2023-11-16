#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>

#include "vtn_scripter.hpp"
#include "vtn_types.hpp"

std::vector<vtnMESH> meshes;

bool IsSpace( char c )
{
    return c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '[' || c == ']' || c == ',';
}

std::vector<std::string> vtnGetWords( std::string FilePath )
{
    static const char SingleChars[] = {
        '`', '.', ';', ':',
        '+', '-', '*', '/',
        '&', '%', '#', '~',
        '<', '>', '=', '|',
        '{', '}', '(', ')'
    };
    static const int SingleCharsSize = 20;
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
                if (args.size() >= 2)
                    textured = args[7][0] - '0';
                
                if (path == "")
                    throw(std::runtime_error("no such mesh '" + args[0] + "'"));
                meshes.push_back(vtnMESH(&scene, path, textured));

                vtnVEC3 pos = vtnVEC3();
                if (args.size() >= 5) {
                    pos = vtnVEC3(atof(args[2].c_str()), atof(args[3].c_str()), atof(args[4].c_str()));
                }

                if (args.size() >= 8) {
                    vtnVEC3 color = vtnVEC3(atof(args[5].c_str()), atof(args[6].c_str()), atof(args[7].c_str()));
                    meshes[meshes.size() - 1].colorize(color);
                }

                for (int i = meshes[meshes.size() - 1].vstart; i <= meshes[meshes.size() - 1].vend; i++)
                    scene.vert_buffer.v[i] = scene.vert_buffer.v[i] + pos;

                if (node == nullptr) {
                    origin.child[origin.child.size() - 1]->mesh = meshes[meshes.size() - 1];
                }
                else {
                    node->child[node->child.size() - 1]->mesh = meshes[meshes.size() - 1];
                }
            }
            else if (words[start - 1] == "pos") {
                std::vector<std::string> args;
                start++;
                while (start < words.size() && words[start] != ")")
                    args.push_back(words[start++]);
                
                if (args.size() < 1)
                    throw(std::runtime_error("not enough arguments for mesh"));

                if (node == nullptr)
                    origin.child[origin.child.size() - 1]->pos = vtnVEC3(atof(args[0].c_str()), atof(args[1].c_str()), atof(args[2].c_str()));
                else
                    node->child[node->child.size() - 1]->pos = vtnVEC3(atof(args[0].c_str()), atof(args[1].c_str()), atof(args[2].c_str()));
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

    for (int w = 0; w < words.size(); w++) {
        if (words[w] == "(" && w > 0) {
            if (words[w - 1] == "place") {
                int ww = w;
                std::vector<std::string> args;
                w++;
                while (w < words.size() && words[w] != ")")
                    args.push_back(words[w++]);
                for (; ww >= 0 && words[ww] != args[0]; ww--);
                vtnCompile(scene, origin, nullptr, words, ww);
            }
        }
    }
}