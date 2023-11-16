#include <cmath>
#include <vector>

#include "vtn_math.hpp"
#include "vtn_types.hpp"

float vtnVecLen(vtnVEC2 a)
{
    return sqrt(a.x * a.x + a.y * a.y);
}

float vtnVecLen(vtnVEC3 a)
{
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

float vtnVecLen2(vtnVEC2 a)
{
    return a.x * a.x + a.y * a.y;
}
float vtnVecLen2(vtnVEC3 a)
{
    return a.x * a.x + a.y * a.y + a.z * a.z;
}

float vtnDist(vtnVEC2 a, vtnVEC2 b)
{
    a = a - b;
    return vtnVecLen(a);
}

float vtnDist(vtnVEC3 a, vtnVEC3 b)
{
    a = a - b;
    return vtnVecLen(a);
}

float vtnDist2(vtnVEC2 a, vtnVEC2 b)
{
    a = a - b;
    return vtnVecLen2(a);
}

float vtnDist2(vtnVEC3 a, vtnVEC3 b)
{
    a = a - b;
    return vtnVecLen2(a);
}

vtnVEC2 vtnVecNorm(vtnVEC2 a)
{
    float l = vtnVecLen(a);
    if (l == 0)
        return a;
    return a / l;
}

vtnVEC3 vtnVecNorm(vtnVEC3 a)
{
    float l = vtnVecLen(a);
    if (l == 0)
        return a;
    return a / l;
}

float vtnDotProduct(vtnVEC2 a, vtnVEC2 b)
{
    return a.x * b.x + a.y * b.y;
}

float vtnDotProduct(vtnVEC3 a, vtnVEC3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float vtnVecAngle(vtnVEC2 a, vtnVEC2 b)
{
    return vtnDotProduct(a, b) / (vtnVecLen(a) * vtnVecLen(b));
}

float vtnVecAngle(vtnVEC3 a, vtnVEC3 b)
{
    return vtnDotProduct(a, b) / (vtnVecLen(a) * vtnVecLen(b));
}

vtnVEC3 vtnCrossProduct(vtnVEC3 a, vtnVEC3 b)
{
    vtnVEC3 c;
    c.x = a.y * b.z - a.z * b.y;
    c.y = a.z * b.x - a.x * b.z;
    c.z = a.x * b.y - a.y * b.x;
    return c;
}

vtnMAT3X3 vtnTranspose(vtnMAT3X3 a)
{
    vtnMAT3X3 b;
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 3; x++)
            b.v[y][x] = a.v[x][y];
    return b;
}

vtnVEC3 vtnLineIntersectPlane(vtnVEC3 plane_p, vtnVEC3 plane_n, vtnVEC3 line_start, vtnVEC3 line_end, float *t)
{
    float plane_d = -vtnDotProduct(plane_n, plane_p);
    float ad = vtnDotProduct(line_start, plane_n);
    float bd = vtnDotProduct(line_end, plane_n);
    *t = (-plane_d - ad) / (bd - ad);
    vtnVEC3 line_start_to_end = line_end - line_start;
    vtnVEC3 line_to_intersect = line_start_to_end * (*t);
    return line_start + line_to_intersect;
}

void vtnTriangleClip(vtnVEC3 plane_p, vtnVEC3 plane_n, std::vector<vtnVEC3> &tri_queue, std::vector<vtnVEC2> &uv_queue)
{
    auto dist = [&](vtnVEC3 &p)
    {
        //vtnVEC3 n = vtnVecNorm(p);
        return (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z - vtnDotProduct(plane_n, plane_p));
    };

    int inside_points[3];
    int nInsidePointCount = 0;
    int outside_points[3];
    int nOutsidePointCount = 0;
    int inside_uvs[3];
    int nInsideUVCount = 0;
    int outside_uvs[3];
    int nOutsideUVCount = 0;

    float d0 = dist(tri_queue[0]);
    float d1 = dist(tri_queue[1]);
    float d2 = dist(tri_queue[2]);

    if (d0 >= 0)
    {
        inside_points[nInsidePointCount++] = 0;
        inside_uvs[nInsideUVCount++] = 0;
    }
    else
    {
        outside_points[nOutsidePointCount++] = 0;
        outside_uvs[nOutsideUVCount++] = 0;
    }
    if (d1 >= 0)
    {
        inside_points[nInsidePointCount++] = 1;
        inside_uvs[nInsideUVCount++] = 1;
    }
    else
    {
        outside_points[nOutsidePointCount++] = 1;
        outside_uvs[nOutsideUVCount++] = 1;
    }
    if (d2 >= 0)
    {
        inside_points[nInsidePointCount++] = 2;
        inside_uvs[nInsideUVCount++] = 2;
    }
    else
    {
        outside_points[nOutsidePointCount++] = 2;
        outside_uvs[nOutsideUVCount++] = 2;
    }

    if (nInsidePointCount == 0)
    {
        tri_queue.clear();
        uv_queue.clear();
    }

    if (nInsidePointCount == 3)
    {
    }

    if (nInsidePointCount == 1 && nOutsidePointCount == 2)
    {
        tri_queue.push_back(tri_queue[inside_points[0]]);
        uv_queue.push_back(uv_queue[inside_uvs[0]]);

        float t;
        tri_queue.push_back(vtnLineIntersectPlane(plane_p, plane_n, tri_queue[inside_points[0]], tri_queue[outside_points[0]], &t));
        uv_queue.push_back((uv_queue[outside_uvs[0]] - uv_queue[inside_uvs[0]]) * t + uv_queue[inside_uvs[0]]);
        tri_queue.push_back(vtnLineIntersectPlane(plane_p, plane_n, tri_queue[inside_points[0]], tri_queue[outside_points[1]], &t));
        uv_queue.push_back((uv_queue[outside_uvs[1]] - uv_queue[inside_uvs[0]]) * t + uv_queue[inside_uvs[0]]);

        tri_queue.erase(tri_queue.begin(), tri_queue.begin() + 3);
        uv_queue.erase(uv_queue.begin(), uv_queue.begin() + 3);
    }

    if (nInsidePointCount == 2 && nOutsidePointCount == 1)
    {
        tri_queue.push_back(tri_queue[inside_points[0]]);
        tri_queue.push_back(tri_queue[inside_points[1]]);
        uv_queue.push_back(uv_queue[inside_uvs[0]]);
        uv_queue.push_back(uv_queue[inside_uvs[1]]);

        float t;
        tri_queue.push_back(vtnLineIntersectPlane(plane_p, plane_n, tri_queue[inside_points[0]], tri_queue[outside_points[0]], &t));
        uv_queue.push_back((uv_queue[outside_uvs[0]] - uv_queue[inside_uvs[0]]) * t + uv_queue[inside_uvs[0]]);

        tri_queue.push_back(tri_queue[inside_points[1]]);
        uv_queue.push_back(uv_queue[inside_uvs[1]]);
        tri_queue.push_back(tri_queue[5]);
        uv_queue.push_back(uv_queue[5]);
        tri_queue.push_back(vtnLineIntersectPlane(plane_p, plane_n, tri_queue[inside_points[1]], tri_queue[outside_points[0]], &t));
        uv_queue.push_back((uv_queue[outside_uvs[0]] - uv_queue[inside_uvs[1]]) * t + uv_queue[inside_uvs[1]]);

        tri_queue.erase(tri_queue.begin(), tri_queue.begin() + 3);
        uv_queue.erase(uv_queue.begin(), uv_queue.begin() + 3);
    }
}