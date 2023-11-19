#include <stdexcept>
#include <string>
#include <fstream>
#include <strstream>
#include <vector>
#include <iostream>

#include "vtn_types.hpp"

vtnVEC2 vtnVEC2::operator/(float a) {
    if (a == 0)
        throw std::runtime_error("division by '0'");
    return vtnVEC2(this->x / a, this->y / a);
}

vtnVEC3 vtnVEC3::operator/(float a) {
    if (a == 0)
        throw std::runtime_error("division by '0'");
    return vtnVEC3(this->x / a, this->y / a, this->z / a);
}

vtnVEC4 vtnVEC4::operator/(float a) {
    if (a == 0)
        throw std::runtime_error("division by '0'");
    return vtnVEC4(this->x / a, this->y / a, this->z / a, this->w / a);
}

bool vtnMESH::LoadFromObjectFile(std::string sFilename, bool Textured) {
    std::ifstream f(sFilename);
    if (!f.is_open())
        return false;

    this->path = sFilename;

    // Local cache of verts
    std::vector<vtnVEC2> texts;

    std::string line;
    char junk;

    this->vstart = this->scene->vert_buffer.len;
    this->tstart = this->scene->tris.size();

    while (getline(f, line)) {
        std::strstream s;
        s << line;
        if (line[0] == 'v') {
            if (line[1] == 't') {
                s >> junk >> junk;
                float uv[2];
                for (int i = 0; i < 2; i++)
                    s >> uv[i];
                texts.push_back(vtnVEC2(uv[0], 1 - uv[1]));
            }
            else {
                float pos[3];
                s >> junk;
                for (int i = 0; i < 3; i++)
                    s >> pos[i];
                this->scene->vert_buffer.add(vtnVEC3(pos[0], pos[1], pos[2]));
            }
        }
        else if (line[0] == 'f') {
            if (Textured) {
                s >> junk;
                int face[3];
                int uvs[3];
                for (int i = 0; i < 3; i++)
                    s >> face[i] >> junk >> uvs[i];
                this->scene->tris.push_back(vtnTRI(
                    &(this->scene->vert_buffer),
                    face[0] - 1 + this->vstart,
                    face[1] - 1 + this->vstart,
                    face[2] - 1 + this->vstart,
                    vtnVEC3(255, 255, 255),
                    texts[uvs[0] - 1],
                    texts[uvs[1] - 1],
                    texts[uvs[2] - 1]
                    ));
            }
            else {
                s >> junk;
                int face[3];
                for (int i = 0; i < 3; i++)
                    s >> face[i];
                this->scene->tris.push_back(vtnTRI(&(this->scene->vert_buffer), face[0] - 1 + this->vstart, face[1] - 1 + this->vstart, face[2] - 1 + this->vstart));
            }
        }
    }

    this->vend = this->scene->vert_buffer.len - 1;
    this->tend = this->scene->tris.size() - 1;

    f.close();

    return true;
}