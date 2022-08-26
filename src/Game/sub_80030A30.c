#include "camera.h"

extern GM_Camera GM_Camera_800B77E8;
extern UnkCameraStruct gUnkCameraStruct_800B77B8;

void sub_80030A30()
{
    if (GM_Camera_800B77E8.field_22 == 0)
    {
        gUnkCameraStruct_800B77B8.field_0 = gUnkCameraStruct_800B77B8.field_8 = GM_Camera_800B77E8.field_8;
    }

    GM_Camera_800B77E8.field_18_flags &= ~2;
}
