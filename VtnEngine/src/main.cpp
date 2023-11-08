#include <iostream>
#include "vtn.hpp"

#include <SDL2/SDL.h>

#define Height 600
#define Width  800

using namespace std;

void Keyboard(uint8 key) {
    cout << key << endl;
}

void Display() {
    SDL_SetRenderDrawColor(vtn_renderer, VTN_COLOR_UWU, 0);
    SDL_RenderClear(vtn_renderer);
}

int main() {
    vtnInitWindow("hello", Width, Height);
    vtnInitRenderer();
    vtnInitKeyboardFunc(Keyboard);
    vtnInitDisplayFunc(Display);

    bool run = true;

    while (run) {
        vtnUpdate(run);
    }
    vtnQuit();
    return 0;
}
