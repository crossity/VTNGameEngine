#include <iostream>
#include <cmath>
#include "vtn.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define Height 600
#define Width  800

using namespace std;

vtnSCENE main_scene;
vtnORIGIN main_origin;
vtnCAMERA main_camera{vtnVEC3(0, 0, -5), vtnVEC3(0, 0, 0), 3.1415 / 2, 1000, 0.1};
vtnVEC3 light_dir{0, 0, -1};

void Keyboard(uint8 key) {
    cout << key << endl;
}

void Display() {
    vtnTimer();
    SDL_SetRenderDrawColor(vtn_renderer, VTN_COLOR_UWU, 0);
    SDL_RenderClear(vtn_renderer);

    // vtnRotate(vtnROTATION(vtnVEC3(), vtnVEC3(0, 3.14 * 0.5 * vtn_delta_time, 0)), main_scene.vert_buffer.v + main_origin.child[0]->mesh.vstart, main_origin.child[0]->mesh.vend - main_origin.child[0]->mesh.vstart + 1);
    // main_origin.child[0]->rot = main_origin.child[0]->rot + vtnVEC3(0, 3.14 * 0.5 * vtn_delta_time, 0);
    main_origin.update_mesh();
    //vtnUpadateCameraRot(main_camera, main_camera.rot + vtnVEC3(0, 3.14 * 0.2 * vtn_delta_time, 0));

    vtnRenderScene(main_scene);
}

int main(int argc, char **argv) {
    vtnInitWindow("hello", Width, Height);
    vtnInitRenderer(main_camera, vtnVEC2(Width, Height));
    vtnInitDraw();
    vtnInitKeyboardFunc(Keyboard);
    vtnInitDisplayFunc(Display);

    main_scene.dir_lights.push_back(vtnVecNorm(vtnVEC3(1, -1, -1)));

    vtnLoadToScene(main_scene, main_origin, "scripts/main.script");

    main_origin.update_mesh();

    main_origin.print();

    bool run = true;

    while (run) {
        vtnUpdate(run);
    }

    return 0;
}
