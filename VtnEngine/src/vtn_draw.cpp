#include <SDL2/SDL.h>
#include <vector>

#include "vtn_draw.hpp"
#include "vtn_window.hpp"
#include "vtn_types.hpp"

unsigned char int_to_uint8(int value) {
    unsigned char ret = value;
    return ret;
}

void vtnDrawTriangle(vtnVEC2 a, vtnVEC2 b, vtnVEC2 c, vtnVEC3 color) {
    const std::vector< SDL_Vertex > verts =
    {
        { SDL_FPoint{ (float)a.x, (float)a.y }, SDL_Color{ int_to_uint8(color.x), int_to_uint8(color.y), int_to_uint8(color.z), 255 }, },
        { SDL_FPoint{ (float)b.x, (float)b.y }, SDL_Color{ int_to_uint8(color.x), int_to_uint8(color.y), int_to_uint8(color.z), 255 }, },
        { SDL_FPoint{ (float)c.x, (float)c.y }, SDL_Color{ int_to_uint8(color.x), int_to_uint8(color.y), int_to_uint8(color.z), 255 }, },
    };
    SDL_RenderGeometry( vtn_renderer, nullptr, verts.data(), verts.size(), nullptr, 0 );
}