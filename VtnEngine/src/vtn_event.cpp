#include <SDL2/SDL.h>

#include "vtn_event.hpp"
#include "vtn_types.hpp"
#include "vtn_window.hpp"
#include "vtn_defines.hpp"

void (*vtnKeyboard)(uint8);
bool vtnKeyboardDefined = false;
void (*vtnDisplay)();
bool vtnDisplayDefined = false;

void vtnInitKeyboardFunc(void (*func)(uint8)) {
    vtnKeyboardDefined = true;
    vtnKeyboard = func;
}

void vtnInitDisplayFunc(void (*func)()) {
    vtnDisplayDefined = true;
    vtnDisplay = func;
}

void vtnUpdate(bool &run) {
    static SDL_Event event;
    
    while(SDL_PollEvent(&event)){
        switch(event.type) {
            case SDL_QUIT:
                run = false;
                break;
            case SDL_KEYDOWN:
                if (vtnKeyboardDefined)
                    vtnKeyboard(event.key.keysym.sym);
                break;
            default:
                break;
        }
    }

    if (vtnDisplayDefined)
        vtnDisplay();
    SDL_RenderPresent(vtn_renderer);
}