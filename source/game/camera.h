#ifndef __MGS_GAME_CAMERA_H__
#define __MGS_GAME_CAMERA_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "common.h"
#include "libhzd/libhzd.h"  // for HZD_HDL
#include "game/control.h"   // for CONTROL

typedef struct CAMERA
{
    SVECTOR     pos;
    SVECTOR     trg;             // pad = alert mask
    signed char field_10_param1; // example: d:CAM_FIX
    u_char      interp;          // example: d:CAM_INTERP_LINER
    char        type;            // example: d:CAM_CAM_TO_TRG
    char        pad_type;
} CAMERA;

typedef void (*TGMCameraFunc)(void);

typedef struct
{
    SVECTOR       position;
    SVECTOR       target;
    SVECTOR       rotate;
    int           flag;
    int           track;
    short         zoom; // Min 320, max 3200. Up to 320 levels?
    short         first_person;
    short         alert_mask;
    short         interp;
    short         type;
    short         interp_mode;
    SVECTOR       pan;
    SVECTOR       bound[2][2];
    SVECTOR       limit[2][2];
    TGMCameraFunc callback[2];
} GM_CameraSystemWork;

typedef struct
{
    SVECTOR position;
    SVECTOR target;
    SVECTOR rotate;
    int     track;
    SVECTOR pan;
    int     interp;
    SVECTOR rotate2; // Not sure why there's two
} GM_SnakeCameraWork;

typedef struct
{
    SVECTOR position;
    SVECTOR target;
    SVECTOR rotate;
    int     track;
    int     zoom;
    int     type;
} UnkCameraStruct2;

/* camera.c */
void GM_SetCameraCallbackFunc(int index, TGMCameraFunc func);
void GM_PanCamera(SVECTOR *a1);
void *NewCameraSystem(void);
void GM_Reset_helper3_80030760();
void sub_8003081C();
void GM_CameraSetAlertMask(unsigned int id, unsigned int mask);
void GM_CameraSetBound(SVECTOR *min, SVECTOR *max, int param_e);
void GM_CameraSetLimit(SVECTOR *min, SVECTOR *max, int param_e);
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

#endif // __MGS_GAME_CAMERA_H__
