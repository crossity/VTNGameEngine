#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "vtn_types.hpp"

extern SDL_Window *vtn_window;
extern SDL_Renderer *vtn_renderer;
extern uint16 VTN_WIDTH, VTN_HEIGHT;

void vtnInitWindow(std::string Name, uint16 Width, uint16 Height);
void vtnQuit();