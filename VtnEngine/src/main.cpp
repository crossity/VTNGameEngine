#include <iostream>
#include "vtn.hpp"

#include <SDL2/SDL.h>

#define Height 600
#define Width  800

using namespace std;

vtnMESH m;

void Keyboard(uint8 key) {
    cout << key << endl;
}

void Display() {
    SDL_SetRenderDrawColor(vtn_renderer, VTN_COLOR_UWU, 0);
    SDL_RenderClear(vtn_renderer);

    SDL_SetRenderDrawColor(vtn_renderer, VTN_COLOR_RED, 0);
    for (int i = 0; i < m.t.size(); i++)
    {
        vtnVEC2 p1 = vtnRender((*m.t[i].vert_buff).v[m.t[i].p[0]]);
        vtnVEC2 p2 = vtnRender((*m.t[i].vert_buff).v[m.t[i].p[1]]);
        vtnVEC2 p3 = vtnRender((*m.t[i].vert_buff).v[m.t[i].p[2]]);
        vtnDrawTriangle(p1, p2, p3, m.t[i].color);
    }
}

int main() {
    vtnCAMERA main_camera{vtnVEC3(0, 0, -5), vtnVEC3(), 3.1415 / 2, 1000, 0.1};

    vtnInitWindow("hello", Width, Height);
    vtnInitRenderer(main_camera, vtnVEC2(Width, Height));
    vtnInitKeyboardFunc(Keyboard);
    vtnInitDisplayFunc(Display);

    if (!m.LoadFromObjectFile("models/sphere.obj"))
        cout << "failed to open file" << endl;
    for (int i = 0; i < m.vert_buffer.len; i++) {
        m.vert_buffer.v[i].z += 5;
    }

    bool run = true;

    while (run) {
        vtnUpdate(run);
    }
    vtnQuit();
    return 0;
}
