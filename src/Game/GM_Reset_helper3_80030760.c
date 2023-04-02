#include "camera.h"

extern GM_Camera GM_Camera_800B77E8;
extern CAMERA    GM_CameraList_800B7718[];
extern SVECTOR   GM_CameraRotateSave_800AB430;
SVECTOR          GM_CameraRotateSave_800AB430;

extern int dword_800ABA94;
int        dword_800ABA94;

void GM_Reset_helper3_80030760()
{
    CAMERA    *cameraList, *cameraListIter;
    GM_Camera *gmCamera;
    int        i;
    int        field_10_param1;

    field_10_param1 = -1;
    i = 7;

    cameraList = GM_CameraList_800B7718;
    cameraListIter = cameraList + 7;

    gmCamera = &GM_Camera_800B77E8;
    gmCamera->field_24_gcl_param_a = 100;
    gmCamera->field_34[0][0].vx = 0x7fff;
    gmCamera->field_34[0][0].vy = 0x7fff;
    gmCamera->field_34[0][0].vz = 0x7fff;
    gmCamera->field_34[1][0].vx = -0x7fff;
    gmCamera->field_34[1][0].vy = -0x7fff;
    gmCamera->field_34[1][0].vz = -0x7fff;
    gmCamera->field_34[2][0].vx = 0x7fff;
    gmCamera->field_34[2][0].vy = 0x7fff;
    gmCamera->field_34[2][0].vz = 0x7fff;
    gmCamera->field_34[3][0].vx = -0x7fff;
    gmCamera->field_34[3][0].vy = -0x7fff;
    gmCamera->field_34[3][0].vz = -0x7fff;
    gmCamera->field_34[0][1].vx = 0x7fff;
    gmCamera->field_34[0][1].vy = 0x7fff;
    gmCamera->field_34[0][1].vz = 0x7fff;
    gmCamera->field_34[1][1].vx = -0x7fff;
    gmCamera->field_34[1][1].vy = -0x7fff;
    gmCamera->field_34[1][1].vz = -0x7fff;
    gmCamera->field_34[2][1].vx = 0x7fff;
    gmCamera->field_34[2][1].vy = 0x7fff;
    gmCamera->field_34[2][1].vz = 0x7fff;
    gmCamera->field_34[3][1].vx = -0x7fff;
    gmCamera->field_34[3][1].vy = -0x7fff;
    gmCamera->field_34[3][1].vz = -0x7fff;

    GM_CameraRotateSave_800AB430.vx = 0x280;
    GM_CameraRotateSave_800AB430.vy = 0x800;
    GM_CameraRotateSave_800AB430.vz = 0;

    while (i >= 0)
    {
        cameraListIter->field_10_param1 = field_10_param1;
        i--;
        cameraListIter--;
    }
    dword_800ABA94 = 0;
}
