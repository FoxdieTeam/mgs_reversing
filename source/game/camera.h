#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "common.h"
#include "libhzd/libhzd.h"  // for HZD_HDL
#include "game/control.h"   // for CONTROL

typedef struct CAMERA
{
    SVECTOR     pos;
    short       trg[3]; // SVECTOR w/ padding as alertMask?
    short       field_0e_alertMask;
    signed char field_10_param1; // example: d:CAM_FIX
    u_char      field_11_param2; // example: d:CAM_INTERP_LINER
    char        field_12_param3; // example: d:CAM_CAM_TO_TRG
    char        field_13_param_p;
} CAMERA;

// probably belongs in camera.h or something
// camera references this is a lot
typedef struct UnkCameraStruct // @ 800B77B8
{
    SVECTOR eye;
    SVECTOR center;
    SVECTOR rotate;
    int     track;
    SVECTOR field_1C;
    int     interp;
    SVECTOR rotate2; // Not sure why there's two
} UnkCameraStruct;

typedef void (*TGMCameraFunc)(void);

// see comment above
// extern demothrd_2Vec stru_800B77E8[9];
typedef struct GM_CAMERA // @ 800B77E8
{
    SVECTOR       eye;
    SVECTOR       center;
    SVECTOR       rotate;
    int           flags;
    int           track;
    short         zoom; // Min 320, max 3200. Up to 320 levels?
    short         first_person;
    short         alert_mask;
    short         interp;
    short         field_28;
    short         field_2A;
    SVECTOR       pan;
    SVECTOR       bounds[2][2];
    SVECTOR       limits[2][2];
    TGMCameraFunc callbacks[2];
} GM_CAMERA;

STATIC_ASSERT(sizeof(GM_CAMERA) == 0x7C, "sizeof(GM_CAMERA) is wrong!");

typedef struct UnkCameraStruct2 // @ 800B7868
{
    SVECTOR eye;
    SVECTOR center;
    SVECTOR rotate;
    int     track;
    int     zoom;
    int     type;
} UnkCameraStruct2;

/* camera.c */
void GM_SetCameraCallbackFunc(int index, TGMCameraFunc func);
void sub_8003049C(SVECTOR *a1);
void *NewCameraSystem(void);
void GM_Reset_helper3_80030760();
void sub_8003081C();
void GM_CameraSetAlertMask(unsigned int id, unsigned int mask);
void GM_CameraSetBounds(SVECTOR *min, SVECTOR *max, int param_e);
void GM_CameraSetLimits(SVECTOR *min, SVECTOR *max, int param_e);
void GM_CameraSetRotation(SVECTOR *rot);
void GM_CameraSetTrack(int track);
void GM_CameraEventReset(void);
void sub_800309B4(int param_1, int param_2);
void sub_800309F8(int param_1, int param_2);
void sub_80030A30();
void GM_CameraBoundTrace(int param_1);
void GM_CameraLimitTrace(int param_1);
void GM_ExitBehindCamera(void);
void GM_CheckBehindCamera(HZD_HDL *pHzdMap, CONTROL *pControl);

#endif // _CAMERA_H_
