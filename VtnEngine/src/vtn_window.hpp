#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "vtn_types.hpp"

extern SDL_Window *VtnWindow;
extern SDL_Renderer *VtnRenderer;

void vtnInit(std::string Name, uint16 Width, uint16 Height);
void vtnQuit();