#pragma once

#include <vector>
#include <string>

typedef unsigned char byte;
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

struct vtnTRI {
    vtnVEC3 p[3], color;
    vtnVEC2 uv[3];
    bool lighted;

    vtnTRI(vtnVEC3 p1, vtnVEC3 p2, vtnVEC3 p3, vtnVEC3 color, vtnVEC2 uv1 = vtnVEC2(), vtnVEC2 uv2 = vtnVEC2(), vtnVEC2 uv3 = vtnVEC2()) {
        p[0] = p1;
        p[1] = p2;
        p[2] = p3;
        this->color = color;
        uv[0] = uv1;
        uv[1] = uv2;
        uv[2] = uv3;
    }
    vtnTRI(vtnVEC3 *p, vtnVEC3 color, vtnVEC2 *uv) {
        for (int i = 0; i < 3; i++)
            this->p[i] = p[i], this->uv[i] = uv[i];
        this->color = color;
    }
};

struct vtnMESH {
    std::vector<vtnTRI> t;

    bool LoadFromObjectFile(std::string sFilename, bool Textured);
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

    vtnMAT3X3 operator+(vtnMAT3X3 m) {
        vtnMAT3X3 ret{0};

        for (int y = 0; y < 3; y++)
            for (int x = 0; x < 3; x++)
                    ret.v[y][x] += v[y][x] + m.v[y][x];

        return ret;
    }

    vtnMAT3X3 operator-(vtnMAT3X3 m) {
        vtnMAT3X3 ret{0};

        for (int y = 0; y < 3; y++)
            for (int x = 0; x < 3; x++)
                    ret.v[y][x] += v[y][x] - m.v[y][x];

        return ret;
    }
    
    vtnMAT3X3 operator*(float a) {
        vtnMAT3X3 ret{0};

        for (int y = 0; y < 3; y++)
            for (int x = 0; x < 3; x++)
                ret.v[y][x] += v[y][x] * a;

        return ret;
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
