#include <iostream>
#include "vtn.hpp"

#include <SDL2/SDL.h>

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

    // vtnUpadateCameraPos(main_camera, main_camera.pos + vtnVEC3(0, 0, 0.5 * vtn_delta_time));

    vtnRenderScene(main_scene);
}

int main(int argc, char** argv) {
    vtnInitWindow("hello", Width, Height);
    vtnInitRenderer(main_camera, vtnVEC2(Width, Height));
    vtnInitKeyboardFunc(Keyboard);
    vtnInitDisplayFunc(Display);

    /* vtnMESH m1{&main_scene, "models/sphere.obj"}, m2{&main_scene, "models/sphere.obj"}; */

    main_scene.lights.push_back(vtnVecNorm(vtnVEC3(1, -1, -1)));

    /* m1.colorize(vtnVEC3(VTN_COLOR_OWO));
    m2.colorize(vtnVEC3(VTN_COLOR_RED));
    */

    /* main_origin.add_child();
    (main_origin.child[0])->mesh = m1;
    (main_origin.child[0])->pos = vtnVEC3(0, 1, 0);
    main_origin.child[0]->add_child();
    main_origin.child[0]->child[0]->mesh = m2;
    main_origin.child[0]->child[0]->pos = vtnVEC3(1, 0, 0);
    */

   vtnLoadToScene(main_scene, main_origin, "scripts/main.script");

    main_origin.update_mesh();

    main_origin.print();

    bool run = true;

    while (run) {
        vtnUpdate(run);
    }
    vtnQuit();

    return 0;
}
