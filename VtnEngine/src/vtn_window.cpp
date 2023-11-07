#include <SDL2/SDL.h>
#include <stdexcept>
#include <string>

#include "vtn_types.hpp"
#include "vtn_window.hpp"

uint16 VTN_WIDTH, VTN_HEIGHT;
SDL_Window *VtnWindow;
SDL_Renderer *VtnRenderer;

void vtnInit(std::string Name, uint16 Width, uint16 Height) {
    VTN_WIDTH = Width;
    VTN_HEIGHT = Height;

    VtnWindow = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error("SDL could not be initiaiized");

    VtnWindow = SDL_CreateWindow(Name.c_str(), 20, 20, Width, Height, SDL_WINDOW_SHOWN);

    VtnRenderer = nullptr;
    VtnRenderer = SDL_CreateRenderer(VtnWindow, -1, SDL_RENDERER_ACCELERATED);
}

void vtnQuit() {
    SDL_DestroyRenderer(VtnRenderer);
    SDL_DestroyWindow(VtnWindow);
    SDL_Quit();
}