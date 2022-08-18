#include "Game/camera.h"

extern GM_Camera GM_Camera_800B77E8;

void GCL_Command_camera_helper2_800308E0(SVECTOR *vec1, SVECTOR *vec2, int param_3_bool)
{
    GM_Camera_800B77E8.field_34[3][param_3_bool] = *vec1;
    GM_Camera_800B77E8.field_34[2][param_3_bool] = *vec2;
}
