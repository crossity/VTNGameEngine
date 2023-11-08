#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "vtn_types.hpp"

extern SDL_Window *vtn_window;
extern SDL_Renderer *vtn_renderer;

void vtnInitWindow(std::string Name, uint16 Width, uint16 Height);
void vtnQuit();