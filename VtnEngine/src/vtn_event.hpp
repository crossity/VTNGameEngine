#pragma once

#include "vtn_types.hpp"

void vtnUpdate(bool &run);
void vtnInitKeyboardFunc(void (*func)(uint8));
void vtnInitDisplayFunc(void (*func)());