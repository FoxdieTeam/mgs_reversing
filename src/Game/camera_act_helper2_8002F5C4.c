#include "camera.h"

extern GM_Camera        GM_Camera_800B77E8;
extern UnkCameraStruct  gUnkCameraStruct_800B77B8;

unsigned int sub_8002F274();
unsigned int camera_act_helper2_helper_8002F384(int a1);

int camera_act_helper2_8002F5C4()
{
    int result; // $v0

    if ( (GM_Camera_800B77E8.field_18_flags & 1) == 0 )
    {
        return sub_8002F274();
    }
    if ( gUnkCameraStruct_800B77B8.field_24 >= 12 )
    {
        GM_Camera_800B77E8.field_18_flags &= ~0x101u;
        GM_Camera_800B77E8.field_26 = -1;
        GM_Camera_800B77E8.field_2A = 0;
    }
    result = camera_act_helper2_helper_8002F384(gUnkCameraStruct_800B77B8.field_24);
    ++gUnkCameraStruct_800B77B8.field_24;
    return result;
}