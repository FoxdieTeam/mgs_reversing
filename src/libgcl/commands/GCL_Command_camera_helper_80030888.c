#include "Game/camera.h"

extern GM_Camera GM_Camera_800B77E8;

void GCL_Command_camera_helper_80030888(SVECTOR *vec1, SVECTOR *vec2, int param_3_bool)
{
    GM_Camera_800B77E8.field_34[1][param_3_bool] = *vec1;
    GM_Camera_800B77E8.field_34[0][param_3_bool] = *vec2;
}
