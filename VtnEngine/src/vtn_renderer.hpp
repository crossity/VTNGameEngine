#pragma once

#include "vtn_types.hpp"

void vtnUpadateCameraRot(vtnCAMERA &camera, vtnVEC3 rot);
void vtnUpadateCameraPos(vtnCAMERA &camera, vtnVEC3 pos);
void vtnInitRenderer(vtnCAMERA &camera, vtnVEC2 view_port);

vtnVEC2 vtnRender(vtnVEC3 p);
void vtnRenderScene(vtnSCENE &scene);