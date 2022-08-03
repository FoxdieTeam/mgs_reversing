#include "linker.h"

extern int GM_CameraTrackSave_800AB42C;
int SECTION(".sdata") GM_CameraTrackSave_800AB42C;

extern int GM_CameraTrackOrg_800AB438;
int SECTION(".sdata") GM_CameraTrackOrg_800AB438;

void sub_8002FCF0(void);

void GCL_Command_camera_helper4_80030980(int param_1)
{
    GM_CameraTrackOrg_800AB438 = param_1;
    GM_CameraTrackSave_800AB42C = param_1;

    sub_8002FCF0();
}
