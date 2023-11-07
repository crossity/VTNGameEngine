#include <iostream>
#include "vtn.hpp"

#include <SDL2/SDL.h>

#define Height 800
#define Width  1300

using namespace std;

int main() {
    vtnInit("hello", Width, Height);

    bool run = true;

    while (run) {
        SDL_Event event;
    
        while(SDL_PollEvent(&event)){
            switch(event.type) {
                case SDL_QUIT:
                    run = false;
                    break;
                default:
                    break;
            }
        }
    }
    vtnQuit();
    return 0;
}
