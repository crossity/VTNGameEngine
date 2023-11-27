#include <SDL2/SDL.h>

#include "vtn_event.hpp"
#include "vtn_types.hpp"
#include "vtn_window.hpp"
#include "vtn_defines.hpp"

void (*vtnKeyboardDown)(uint8);
bool vtnKeyboardDownDefined = false;
void (*vtnKeyboardUp)(uint8);
bool vtnKeyboardUpDefined = false;
void (*vtnDisplay)();
bool vtnDisplayDefined = false;

void vtnInitKeyboardDownFunc(void (*func)(uint8)) {
    vtnKeyboardDownDefined = true;
    vtnKeyboardDown = func;
}

void vtnInitKeyboardUpFunc(void (*func)(uint8)) {
    vtnKeyboardUpDefined = true;
    vtnKeyboardUp = func;
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
                if (vtnKeyboardDownDefined)
                    vtnKeyboardDown(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                if (vtnKeyboardUpDefined)
                    vtnKeyboardUp(event.key.keysym.sym);
                break;
            default:
                break;
        }
    }

    if (vtnDisplayDefined)
        vtnDisplay();
    SDL_RenderPresent(vtn_renderer);
}