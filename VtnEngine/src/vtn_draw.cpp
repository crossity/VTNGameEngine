#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>

#include "vtn_draw.hpp"
#include "vtn_window.hpp"
#include "vtn_types.hpp"

void vtnInitDraw() {
    if (IMG_Init(IMG_INIT_PNG) == 0)
        std::cout << "Couldn't initialize Image" << std::endl;
}

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

void vtnDrawTexturedTriangle(vtnVEC2 p1, vtnVEC2 p2, vtnVEC2 p3, vtnVEC2 uv1, vtnVEC2 uv2, vtnVEC2 uv3, SDL_Texture *texture, vtnVEC3 color) {
    SDL_Vertex verts[3];
    SDL_Color c{int_to_uint8(color.x), int_to_uint8(color.y), int_to_uint8(color.z), 255};

    verts[0].position.x = p1.x;
    verts[0].position.y = p1.y;
    verts[0].tex_coord.x = uv1.x;
    verts[0].tex_coord.y = uv1.y;
    verts[0].color = c;

    verts[1].position.x = p2.x;
    verts[1].position.y = p2.y;
    verts[1].tex_coord.x = uv2.x;
    verts[1].tex_coord.y = uv2.y;
    verts[1].color = c;

    verts[2].position.x = p3.x;
    verts[2].position.y = p3.y;
    verts[2].tex_coord.x = uv3.x;
    verts[2].tex_coord.y = uv3.y;
    verts[2].color = c;
    SDL_RenderGeometry(vtn_renderer, texture, verts, 3, NULL, 0);
}

void vtnLoadFromPNG(vtnTEXTURE **texture, std::string file) {
    *texture = IMG_LoadTexture(vtn_renderer, file.c_str());
}