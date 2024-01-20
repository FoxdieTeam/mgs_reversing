#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "unknown.h"
#include "linker.h"
#include "Game/game.h"
#include "Game/game.h"
#include "libgv/libgv.h"

// probably belongs in camera.h or something
// camera references this is a lot
typedef struct UnkCameraStruct // @ 800B77B8
{
    SVECTOR field_0;
    SVECTOR field_8;
    SVECTOR field_10;
    int     field_18;
    SVECTOR field_1C;
    int     field_24;
    SVECTOR field_28;
} UnkCameraStruct;

typedef void (*TGMCameraFunc)(void);

// see comment above
// extern demothrd_2Vec stru_800B77E8[9];
typedef struct GM_Camera // @ 800B77E8
{
    SVECTOR       field_0;
    SVECTOR       field_8;
    SVECTOR       field_10;
    int           field_18_flags;
    int           field_1C;
    short         field_20_zoomLevel; // Min 320, max 3200. Up to 320 levels?
    short         field_22;
    short         field_24_gcl_param_a;
    short         field_26;
    short         field_28;
    short         field_2A;
    SVECTOR       field_2C;
    SVECTOR       field_34[4][2];
    TGMCameraFunc field_74_funcs[2];
} GM_Camera;
STATIC_ASSERT_SIZE(GM_Camera, 0x7C);

typedef struct UnkCameraStruct2 // @ 800B7868
{
    SVECTOR eye;
    SVECTOR center;
    SVECTOR field_10;
    int field_18; // VECTOR?
    int clip_distance;
    int field_20;
    // int field_24; // padding?
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

#endif // _CAMERA_H_
