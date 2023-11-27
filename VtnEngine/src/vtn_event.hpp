#pragma once

#include "vtn_types.hpp"

void vtnUpdate(bool &run);
void vtnInitKeyboardDownFunc(void (*func)(uint8));
void vtnInitKeyboardUpFunc(void (*func)(uint8));
void vtnInitDisplayFunc(void (*func)());