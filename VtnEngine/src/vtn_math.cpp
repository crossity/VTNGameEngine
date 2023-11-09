#include <cmath>

#include "vtn_types.hpp"

float vtnVecLen(vtnVEC2 &a) {
	return sqrt(a.x * a.x + a.y * a.y);
}
float vtnVecLen(vtnVEC3 &a) {
	return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

float vtnDotProduct(vtnVEC2 &a, vtnVEC2 &b) {
	return a.x * b.x + a.y * b.y;
}
float vtnDotProduct(vtnVEC3 &a, vtnVEC3 &b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float vtnVecAngle(vtnVEC2 &a, vtnVEC2 &b) {
	return vtnDotProduct(a, b) / (vtnVecLen(a) * vtnVecLen(b));
}
float vtnVecAngle(vtnVEC3 &a, vtnVEC3 &b) {
	return vtnDotProduct(a, b) / (vtnVecLen(a) * vtnVecLen(b));
}

vtnVEC3 vtnCrossProduct(vtnVEC3 &a, vtnVEC3 &b) {
    vtnVEC3 c;
    c.x = a.y * b.z - a.z * b.y;
    c.y = a.z * b.x - a.x * b.z;
    c.z = a.x * b.y - a.y * b.x;
    return c;
}

vtnMAT3X3 vtnTranspose(vtnMAT3X3 &a) {
    vtnMAT3X3 b;
    for (int y = 0; y < 3; y++)
        for (int x = 0; x < 3; x++)
            b.v[y][x] = a.v[x][y];
    return b;
}
