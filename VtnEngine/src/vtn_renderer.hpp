#pragma once

#include "vtn_types.hpp"

extern float vtn_dir_sort_k;

void vtnUpadateCameraRot(vtnCAMERA &camera, vtnVEC3 rot);
void vtnUpadateCameraPos(vtnCAMERA &camera, vtnVEC3 pos);
void vtnInitRenderer(vtnCAMERA &camera, vtnVEC2 view_port, float dir_sort_k);

vtnVEC2 vtnRender(vtnVEC3 p);
void vtnRenderScene(vtnSCENE &scene);