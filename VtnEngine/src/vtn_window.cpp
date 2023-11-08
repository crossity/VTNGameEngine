#include <SDL2/SDL.h>
#include <stdexcept>
#include <string>

#include "vtn_types.hpp"
#include "vtn_window.hpp"

uint16 VTN_WIDTH, VTN_HEIGHT;
SDL_Window *vtn_window;
SDL_Renderer *vtn_renderer;

void vtnInitWindow(std::string Name, uint16 Width, uint16 Height) {
    VTN_WIDTH = Width;
    VTN_HEIGHT = Height;

    vtn_window = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error("SDL could not be initiaiized");

    vtn_window = SDL_CreateWindow(Name.c_str(), 20, 20, Width, Height, SDL_WINDOW_SHOWN);

    vtn_renderer = nullptr;
    vtn_renderer = SDL_CreateRenderer(vtn_window, -1, SDL_RENDERER_ACCELERATED);
}

void vtnQuit() {
    SDL_DestroyRenderer(vtn_renderer);
    SDL_DestroyWindow(vtn_window);
    SDL_Quit();
}