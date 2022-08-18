#include "linker.h"
#include "libgcl/gcl.h"
#include "mts/mts_new.h"
#include "Game/GM_Control.h"
#include "game/game.h"
#include "game/Camera.h"

extern CAMERA GM_CameraList_800B7718[8];
extern GM_Camera GM_Camera_800B77E8;

extern const char aSetCameraD[];

extern int GM_GameStatus_800AB3CC;

/*
proc AGL_FIRST_VF {
#pos -3362 1759 4936
#trg -2475 770 6672
#rot 306 308 0
    camera  set 4  d:CAM_FIX d:CAM_INTERP_LINER d:CAM_CAM_TO_TRG \
            -3362,1759,4936 -2475,770,6672 1
*/

int GCL_Command_camera_8002B8F0(int argc, char **argv)
{
    int     isEnabled, param_p, camera_id;
    short   vec1[3], vec2[3];
    CAMERA *cam;

    isEnabled = GCL_GetParam_80020968('e') != 0; // enabled

    if (GCL_GetParam_80020968('b')) // bound
    {
        GCL_GetSV_80020A14(GCL_Get_Param_Result_80020AA4(), vec1);
        GCL_GetSV_80020A14(GCL_Get_Param_Result_80020AA4(), vec2);
        GCL_Command_camera_helper_80030888(vec1, vec2, isEnabled);
    }

    if (GCL_GetParam_80020968('t')) // track
    {
        GCL_Command_camera_helper4_80030980(GCL_GetNextParamValue_80020AD4());
    }

    if (GCL_GetParam_80020968('l')) // limit
    {
        GCL_GetSV_80020A14(GCL_Get_Param_Result_80020AA4(), vec1);
        GCL_GetSV_80020A14(GCL_Get_Param_Result_80020AA4(), vec2);
        GCL_Command_camera_helper2_800308E0(vec1, vec2, isEnabled);
    }

    if (GCL_GetParam_80020968('r')) // rotate
    {
        GCL_GetSV_80020A14(GCL_Get_Param_Result_80020AA4(), vec1);
        GCL_Command_camera_helper3_80030938(vec1);
    }

    param_p = GCL_GetParam_80020968('p') != 0;

    if (GCL_GetParam_80020968('s')) // set
    {
        camera_id = GCL_GetNextParamValue_80020AD4();
        if (camera_id < 8)
        {
            mts_printf_8008BBA0(aSetCameraD, camera_id); // "set camera %d\n"
            cam = &GM_CameraList_800B7718[camera_id];
            cam->field_10_param1 = GCL_GetNextParamValue_80020AD4();
            cam->field_11_param2 = GCL_GetNextParamValue_80020AD4();
            cam->field_12_param3 = GCL_GetNextParamValue_80020AD4();
            cam->field_13_param_p = param_p;
            GCL_GetSV_80020A14(GCL_Get_Param_Result_80020AA4(), cam->field_00_pos);
            GCL_GetSV_80020A14(GCL_Get_Param_Result_80020AA4(), cam->field_08_trg);
            if (GCL_Get_Param_Result_80020AA4())
            {
                cam->field_0e_alertMask = GCL_GetNextParamValue_80020AD4();
            }
            else
            {
                cam->field_0e_alertMask = 0;
            }
            GM_CameraSetAlertMask_80030850(camera_id, cam->field_0e_alertMask);
        }
    }

    if (GCL_GetParam_80020968('a'))
    {
        GM_Camera_800B77E8.field_24_gcl_param_a = GCL_GetNextParamValue_80020AD4();
    }

    if (GCL_GetParam_80020968('c'))
    {
        if (GCL_GetNextParamValue_80020AD4() == 0)
        {
            GM_GameStatus_800AB3CC &= ~0x40;
        }
        else
        {
            GM_GameStatus_800AB3CC |= 0x40;
        }
    }

    return 0;
}
