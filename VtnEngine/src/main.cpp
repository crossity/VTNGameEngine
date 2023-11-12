#include <iostream>
#include "vtn.hpp"

#include <SDL2/SDL.h>

#define Height 600
#define Width  800

using namespace std;

vtnSCENE main_scene;
vtnCAMERA main_camera{vtnVEC3(0, 0, -5), vtnVEC3(0, 0, 0), 3.1415 / 2, 1000, 0.1};
vtnVEC3 light_dir{0, 0, -1};

void Keyboard(uint8 key) {
    cout << key << endl;
}

void Display() {
    vtnTimer();
    SDL_SetRenderDrawColor(vtn_renderer, VTN_COLOR_UWU, 0);
    SDL_RenderClear(vtn_renderer);

    vtnUpadateCameraPos(main_camera, main_camera.pos + vtnVEC3(0, 0, 0.5 * vtn_delta_time));

    vtnRenderScene(main_scene);
}

int main(int argc, char** argv) {
    vtnInitWindow("hello", Width, Height);
    vtnInitRenderer(main_camera, vtnVEC2(Width, Height));
    vtnInitKeyboardFunc(Keyboard);
    vtnInitDisplayFunc(Display);

    vtnMESH m1{&main_scene, "models/sphere.obj"}, m2{&main_scene, "models/sphere.obj"};

    main_scene.lights.push_back(vtnVecNorm(vtnVEC3(1, -1, -1)));

    m1.colorize(vtnVEC3(VTN_COLOR_OWO));

    main_scene.add_child();
    (*main_scene.child[0]).mesh = m1;
    (*main_scene.child[0]).add_child();
    (*(*main_scene.child[0]).child[0]).mesh = m2;

    bool run = true;

    while (run) {
        vtnUpdate(run);
    }
    vtnQuit();

    return 0;
}
