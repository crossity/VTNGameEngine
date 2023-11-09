#pragma once

#include "vtn_types.hpp"

vtnVEC2 vtnRender(vtnVEC3 p);
void vtnUpadateCameraRot(vtnCAMERA &camera, vtnVEC3 rot);

void vtnInitRenderer(vtnCAMERA &camera, vtnVEC2 view_port);