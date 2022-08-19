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
    int     field_10;
    int     field_14;
    int     field_18;
    int     field_1C;
    int     field_20;
    int     field_24;
    SVECTOR field_28_aim_assist; // dont know what this really is
} UnkCameraStruct;
STATIC_ASSERT_SIZE(UnkCameraStruct, 0x30);

// see comment above
// extern demothrd_2Vec stru_800B77E8[9];
typedef struct GM_Camera // @ 800B77E8
{
    SVECTOR field_0;
    SVECTOR field_8;
    SVECTOR field_10;
    int field_18_flags;
    int field_1C;
    short field_20; // zoom leve, up to 320 levels?
    short field_22;
    short field_24_gcl_param_a;
    short field_26;
    short field_28;
    short field_2A;
    short field_2C;
    short field_2E;
    short field_30;
    short field_32;
    SVECTOR field_34[4][2];
    int field_74_2Array[2];
} GM_Camera;
STATIC_ASSERT_SIZE(GM_Camera, 0x7C);

typedef struct UnkCameraStruct2 // @ 800B7868
{
    SVECTOR field_0;
    SVECTOR field_8;
    SVECTOR field_10;
    int field_18; // VECTOR?
    int field_1C;
    int field_20;
    // int field_24; // padding?
} UnkCameraStruct2;

void camera_act_helper5_80030118(Actor *pActor);
int  camera_act_helper6_80030250(Actor *pActor);
void camera_act_helper3_8002F64C();
void camera_act_helper_8002F1C8();
void camera_act_helper7_8002FB54();
int  camera_act_helper2_8002F5C4();
void camera_act_helper4_8002F78C();

#endif // _CAMERA_H_
