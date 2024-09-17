#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "common.h"
#include "Game/game.h"
#include "Game/game.h"
#include "libgv/libgv.h"

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
typedef struct GM_Camera // @ 800B77E8
{
    SVECTOR       eye;
    SVECTOR       center;
    SVECTOR       rotate;
    int           flags;
    int           track;
    short         zoom; // Min 320, max 3200. Up to 320 levels?
    short         first_person;
    short         field_24_gcl_param_a;
    short         interp;
    short         field_28;
    short         field_2A;
    SVECTOR       pan;
    SVECTOR       bounds[2][2];
    SVECTOR       limits[2][2];
    TGMCameraFunc callbacks[2];
} GM_Camera;

STATIC_ASSERT(sizeof(GM_Camera) == 0x7C, "sizeof(GM_Camera) is wrong!");

typedef struct UnkCameraStruct2 // @ 800B7868
{
    SVECTOR eye;
    SVECTOR center;
    SVECTOR rotate;
    int     track;
    int     zoom;
    int     type;
} UnkCameraStruct2;

void camera_act_helper5_80030118(GV_ACT *pActor);
int  camera_act_helper6_80030250(GV_ACT *pActor);
void camera_act_helper3_8002F64C();
void camera_act_helper_8002F1C8();
void camera_act_helper7_8002FB54();
int  camera_act_helper2_8002F5C4();
void camera_act_helper4_8002F78C();
void sub_8002ED68(int param_1);
void sub_800303E0(SVECTOR *);
void sub_8002EE80(void);
void GM_SetCameraCallbackFunc_8002FD84(int index, TGMCameraFunc func) ;
void sub_8002FC58(SVECTOR *param_1, SVECTOR *param_2, SVECTOR *param_3, int *param_4);
void sub_8002FCA4(SVECTOR *param_1, SVECTOR *param_2, SVECTOR *param_3, int *param_4);
void camera_get_euler_angles_8002FBC0(SVECTOR *pVec1, SVECTOR *pVec2, SVECTOR *pVec3, int *pLen);
void sub_8002FAAC(SVECTOR *a1, SVECTOR *a2, SVECTOR *a3, int *a4);
void sub_8002FCF0(void);
void camera_act_helper6_helper_8002FD9C(int, int);
GV_ACT *camera_init_800306A0(void);
void sub_8003049C(SVECTOR *a1);
void sub_8003081C();
void GM_CameraSetAlertMask_80030850(unsigned int id, unsigned int mask);

#endif // _CAMERA_H_
