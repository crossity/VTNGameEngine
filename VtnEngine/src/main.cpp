#include <iostream>
#include "vtn.hpp"

#include <SDL2/SDL.h>

#define Height 600
#define Width  800

using namespace std;

vtnSCENE main_scene;
vtnMESH m;
vtnCAMERA main_camera{vtnVEC3(0, 0, -5), vtnVEC3(0.2, 0, 0), 3.1415 / 2, 1000, 0.1};
vtnVEC3 light_dir{0, 0, -1};

void Keyboard(uint8 key) {
    cout << key << endl;
}

void Display() {
    SDL_SetRenderDrawColor(vtn_renderer, VTN_COLOR_UWU, 0);
    SDL_RenderClear(vtn_renderer);

    vtnRenderScene(main_scene);
}

int main() {

    vtnInitWindow("hello", Width, Height);
    vtnInitRenderer(main_camera, vtnVEC2(Width, Height));
    vtnInitKeyboardFunc(Keyboard);
    vtnInitDisplayFunc(Display);

    m.scene = &main_scene;
    if (!m.LoadFromObjectFile("models/sphere.obj"))
        cout << "failed to open file" << endl;

    bool run = true;

    while (run) {
        vtnUpdate(run);
    }
    vtnQuit();
    return 0;
}
