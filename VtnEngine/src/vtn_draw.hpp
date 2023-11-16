#pragma once

#include <string>

#include "vtn_types.hpp"

void vtnInitDraw();

void vtnDrawTriangle(vtnVEC2 a, vtnVEC2 b, vtnVEC2 c, vtnVEC3 color);
void vtnDrawTexturedTriangle(vtnVEC2 p1, vtnVEC2 p2, vtnVEC2 p3, vtnVEC2 uv1, vtnVEC2 uv2, vtnVEC2 uv3, SDL_Texture *texture, vtnVEC3 color);

void vtnLoadFromPNG(vtnTEXTURE **texture, std::string file);