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

vtnVEC3 rotate_y(vtnVEC3 c, float angle, vtnVEC3 p) {
    float sn = sin(angle);
    float cs = cos(angle);

    p.z -= c.z;
    p.x -= c.x;

    float znew = p.z * cs - p.x * sn;
    float xnew = p.z * sn + p.x * cs;

    p.x = xnew + c.x;
    p.z = znew + c.z;
    return p;
}

void Display() {
    vtnTimer();
    SDL_SetRenderDrawColor(vtn_renderer, VTN_COLOR_UWU, 0);
    SDL_RenderClear(vtn_renderer);

    main_origin.child[0]->pos.x = sin(vtn_sync_time * 10) * 4;
    main_origin.update_mesh();
    main_origin.child[0]->update_collider();
    //main_origin.child[1]->update_colider();

    if (is_collide(main_origin.child[0], main_origin.child[1]))
        cout << "COLLISION" << endl;
    else
        cout << "DOT NOT COLLIDE" << endl;

    vtnRenderScene(main_scene);
}

int main(int argc, char** argv) {
    vtnInitWindow("hello", Width, Height);
    vtnInitRenderer(main_camera, vtnVEC2(Width, Height));
    vtnInitDraw();
    vtnInitKeyboardFunc(Keyboard);
    vtnInitDisplayFunc(Display);

    main_scene.lights.push_back(vtnVecNorm(vtnVEC3(1, -1, -1)));

    vtnLoadToScene(main_scene, main_origin, "scripts/main.script");

    main_origin.update_mesh();
    main_origin.child[0]->update_collider();
    main_origin.child[1]->update_collider();

    main_origin.print();

    bool run = true;

    while (run) {
        vtnUpdate(run);
    }

    return 0;
}
