#pragma once

#include <vector>
#include <string>

#define VTN_VBUFFER_SIZE 100

typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;

struct vtnVEC2 {
    float x, y;

    vtnVEC2() {
        this->x = 0.f;
        this->y = 0.f;
    }
    vtnVEC2(float x, float y) {
        this->x = x;
        this->y = y;
    }

    vtnVEC2 operator+(vtnVEC2 a) {
        return vtnVEC2(this->x + a.x, this->y + a.y);
    }
    vtnVEC2 operator-(vtnVEC2 a) {
        return vtnVEC2(this->x - a.x, this->y - a.y);
    }
    vtnVEC2 operator*(float a) {
        return vtnVEC2(this->x * a, this->y * a);
    }
    vtnVEC2 operator/(float a);
};

struct vtnVEC3 {
    float x, y, z;

    vtnVEC3() {
        this->x = 0.f;
        this->y = 0.f;
        this->z = 0.f;
    }
    vtnVEC3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    vtnVEC3 operator+(vtnVEC3 a) {
        return vtnVEC3(this->x + a.x, this->y + a.y, this->z + a.z);
    }
    vtnVEC3 operator-(vtnVEC3 a) {
        return vtnVEC3(this->x - a.x, this->y - a.y, this->z - a.z);
    }
    vtnVEC3 operator*(float a) {
        return vtnVEC3(this->x * a, this->y * a, this->z * a);
   }
    vtnVEC3 operator/(float a);
};

struct vtnVBUFFER {
    vtnVEC3 v[VTN_VBUFFER_SIZE];
    int len;

    vtnVBUFFER() {
        this->len = 0;
    }

    bool add(vtnVEC3 v) {
        if (this->len >= VTN_VBUFFER_SIZE - 1)
            return false;
        
        (this->len)++;
        this->v[this->len - 1] = v;
        return true;
    }
};

struct vtnTRI {
    int p[3];
    vtnVEC3 color;
    vtnVEC2 uv[3];
    bool lighted;
    vtnVBUFFER *vert_buff;

    vtnTRI(vtnVBUFFER *vert_buff, int p1, int p2, int p3, vtnVEC3 color = vtnVEC3(255, 255, 255), vtnVEC2 uv1 = vtnVEC2(), vtnVEC2 uv2 = vtnVEC2(), vtnVEC2 uv3 = vtnVEC2()) {
        this->vert_buff = vert_buff;

        this->p[0] = p1;
        this->p[1] = p2;
        this->p[2] = p3;

        this->color = color;

        this->uv[0] = uv1;
        this->uv[1] = uv2;
        this->uv[2] = uv3;
    }
};

struct vtnMESH {
    std::vector<vtnTRI> t;
    vtnVBUFFER vert_buffer;

    bool LoadFromObjectFile(std::string sFilename, bool Textured = false);
};

struct vtnSCENE {
    std::vector<vtnMESH *> m;
};

struct vtnCAMERA {
    vtnVEC3 pos, rot;
    float fov;

    vtnCAMERA(vtnVEC3 pos, vtnVEC3 rot, float fov) {
        this->pos = pos;
        this->rot = rot;
        this->fov = fov;
    }
    vtnCAMERA() {
        this->pos = vtnVEC3();
        this->rot = vtnVEC3();
        this->fov = 3.1415;
    }
};

struct vtnMAT3X3 {
    float v[3][3];

    vtnMAT3X3(float a) {
        for (int y = 0; y < 3; y++)
            for (int x = 0; x < 3; x++)
                this->v[y][x] = a;
    }
    
    vtnMAT3X3() {
    	*this = vtnMAT3X3(0);
    }

    vtnMAT3X3 operator*(vtnMAT3X3 m) {
        vtnMAT3X3 ret{0};

        for (int y = 0; y < 3; y++)
            for (int x = 0; x < 3; x++)
                for (int i = 0; i < 3; i++)
                    ret.v[y][x] += v[y][i] * m.v[i][x];

        return ret;
    }       
};
