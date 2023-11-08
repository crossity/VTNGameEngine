#include <cmath>

#include "vtn_types.hpp"

float vtnVecLen(vtnVEC2 &a);
float vtnVecLen(vtnVEC3 &a);
float vtnDotProduct(vtnVEC2 &a, vtnVEC2 &b);
float vtnDotProduct(vtnVEC3 &a, vtnVEC3 &b);
float vtnVecAngle(vtnVEC2 &a, vtnVEC2 &b);
float vtnVecAngle(vtnVEC3 &a, vtnVEC3 &b);
vtnVEC3 vtnCrossProduct(vtnVEC3 &a, vtnVEC3 &b);
vtnMAT3X3 vtnTranspose(vtnMAT3X3 &a);