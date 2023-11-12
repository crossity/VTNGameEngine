#pragma once

#include <vector>
#include <string>
#include <iostream>

#define VTN_VBUFFER_SIZE 1000

typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;

struct vtnMAT4X4 {
    float v[4][4];

    vtnMAT4X4(float a) {
        for (int y = 0; y < 4; y++)
            for (int x = 0; x < 4; x++)
                this->v[y][x] = a;
    }
    
    vtnMAT4X4() {
    	*this = vtnMAT4X4(0);
    }

    vtnMAT4X4 operator+(vtnMAT4X4 m) {
        vtnMAT4X4 ret{0};

        for (int y = 0; y < 4; y++)
            for (int x = 0; x < 4; x++)
                ret.v[y][x] += v[y][x] + m.v[y][x];

        return ret;
    }

    vtnMAT4X4 operator-(vtnMAT4X4 m) {
        vtnMAT4X4 ret{0};

        for (int y = 0; y < 4; y++)
            for (int x = 0; x < 4; x++)
                ret.v[y][x] += v[y][x] - m.v[y][x];

        return ret;
    }

    vtnMAT4X4 operator*(float a) {
        vtnMAT4X4 ret{0};

        for (int y = 0; y < 4; y++)
            for (int x = 0; x < 4; x++)
                ret.v[y][x] += v[y][x] * a;

        return ret;
    }

    vtnMAT4X4 operator*(vtnMAT4X4 m) {
        vtnMAT4X4 ret{0};

        for (int y = 0; y < 4; y++)
            for (int x = 0; x < 4; x++)
                for (int i = 0; i < 4; i++)
                    ret.v[y][x] += v[y][i] * m.v[i][x];

        return ret;
    }       
};

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

struct vtnVEC4 {
    float x, y, z, w;

    vtnVEC4() {
        this->x = 0.f;
        this->y = 0.f;
        this->z = 0.f;
        this->w = 0.f;
    }
    vtnVEC4(float x, float y, float z, float w) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    vtnVEC4 operator+(vtnVEC4 a) {
        return vtnVEC4(this->x + a.x, this->y + a.y, this->z + a.z, this->w + a.w);
    }
    vtnVEC4 operator-(vtnVEC4 a) {
        return vtnVEC4(this->x - a.x, this->y - a.y, this->z - a.z, this->w - a.w);
    }
    vtnVEC4 operator*(float a) {
        return vtnVEC4(this->x * a, this->y * a, this->z * a, this->w * a);
    }
    vtnVEC4 operator/(float a);

    vtnVEC4 operator*(vtnMAT4X4 m) {
        vtnVEC4 res;

        res.x = this->x * m.v[0][0] + this->y * m.v[1][0] + this->z * m.v[2][0] + this->w * m.v[3][0];
        res.y = this->x * m.v[0][1] + this->y * m.v[1][1] + this->z * m.v[2][1] + this->w * m.v[3][1];
        res.z = this->x * m.v[0][2] + this->y * m.v[1][2] + this->z * m.v[2][2] + this->w * m.v[3][2];
        res.w = this->x * m.v[0][3] + this->y * m.v[1][3] + this->z * m.v[2][3] + this->w * m.v[3][3];

        return res;
    }
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
    vtnSCENE *scene;
    int vstart, vend, tstart, tend;

    bool LoadFromObjectFile(std::string sFilename, bool Textured = false);

    vtnMESH(vtnSCENE *scene, std::string path, bool textured = false) {
        this->scene = scene;
        this->LoadFromObjectFile(path, textured);
    }

    vtnMESH() {
    }

    void colorize(vtnVEC3 color) {
        for (int i = this->tstart; i <= this->tend; i++)
            scene->tris[i].color = color;
    }
};

struct vtnNODE {
    vtnVEC3 pos = vtnVEC3(), glob_pos = vtnVEC3();

    std::vector<vtnNODE *> child;
    vtnMESH mesh;

    ~vtnNODE() {
        for (int i = 0; i < child.size(); i++) {
            child[i]->~vtnNODE();
        }
        delete this;
    }

    void add_child() {
        vtnNODE *ptr = new vtnNODE;

        child.push_back(ptr);
    }

    void update_mesh(vtnVEC3 new_global_pos) {

    }
};

struct vtnSCENE {
    vtnVBUFFER vert_buffer;
    std::vector<vtnTRI> tris;
    std::vector<vtnVEC3> lights;

    std::vector<vtnNODE *> child;

    ~vtnSCENE() {
        for (int i = 0; i < child.size(); i++)
            child[i]->~vtnNODE();
    }

    void add_child() {
        vtnNODE *ptr = new vtnNODE;

        child.push_back(ptr);
    }
};

struct vtnCAMERA {
    vtnVEC3 pos, rot;
    float fov, z_far, z_near;

    vtnCAMERA(vtnVEC3 pos, vtnVEC3 rot, float fov, float z_far, float z_near) {
        this->pos = pos;
        this->rot = rot;
        this->fov = fov;
        this->z_far = z_far;
        this->z_near = z_near;
    }
    vtnCAMERA() {
        this->pos = vtnVEC3();
        this->rot = vtnVEC3();
        this->fov = 3.1415;
        this->z_far = 10;
        this->z_near = 0.1;
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

    vtnVEC3 operator*(vtnVEC3 v) {
        vtnVEC3 res{};

        res.x = v.x * this->v[0][0] + v.y * this->v[0][1] + v.z * this->v[0][2];
        res.y = v.x * this->v[1][0] + v.y * this->v[1][1] + v.z * this->v[1][2];
        res.z = v.x * this->v[2][0] + v.y * this->v[2][1] + v.z * this->v[2][2];

        return res;
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