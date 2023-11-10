#pragma once

#include <vector>

#include "vtn_types.hpp"

float vtnVecLen(vtnVEC2 a);
float vtnVecLen(vtnVEC3 a);
float vtnVecLen2(vtnVEC2 a);
float vtnVecLen2(vtnVEC3 a);
float vtnDist(vtnVEC2 a, vtnVEC2 b);
float vtnDist(vtnVEC3 a, vtnVEC3 b);
float vtnDist2(vtnVEC2 a, vtnVEC2 b);
float vtnDist2(vtnVEC3 a, vtnVEC3 b);
vtnVEC2 vtnVecNorm(vtnVEC2 a);
vtnVEC3 vtnVecNorm(vtnVEC3 a);

float vtnDotProduct(vtnVEC2 a, vtnVEC2 b);
float vtnDotProduct(vtnVEC3 a, vtnVEC3 b);
float vtnVecAngle(vtnVEC2 a, vtnVEC2 b);
float vtnVecAngle(vtnVEC3 a, vtnVEC3 b);
vtnVEC3 vtnCrossProduct(vtnVEC3 a, vtnVEC3 b);
vtnMAT3X3 vtnTranspose(vtnMAT3X3 a);

vtnVEC3 vtnLineIntersectPlane(vtnVEC3 plane_p, vtnVEC3 plane_n, vtnVEC3 line_start, vtnVEC3 line_end);
void vtnTriangleClip(vtnVEC3 plane_p, vtnVEC3 plane_n, std::vector<vtnVEC3> &tri_queue);