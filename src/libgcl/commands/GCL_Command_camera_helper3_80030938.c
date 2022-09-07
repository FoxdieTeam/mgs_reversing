#include "libgcl/gcl.h"

extern SVECTOR GM_CameraRotateSave_800AB430;

void GCL_Command_camera_helper3_80030938(SVECTOR *pVec)
{
    GM_CameraRotateSave_800AB430 = *pVec;
    sub_8002FCF0();
}
