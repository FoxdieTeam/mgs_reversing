#ifndef _STNSIGHT_H_
#define _STNSIGHT_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

#include "Game/GM_Control.h"
#include "libgv/libgv.h"

// stinger first person HUD

typedef struct _Actor_Stnsight
{
    Actor       field_0_actor;
    GM_Control *field_20_ctrl;
    GV_PAD     *field_24_pad_data;
    LINE_F4    *field_28_lines_2Array[2];
    LINE_F4    *field_30_lines_2Array[2];
    LINE_F4    *field_38_lines_2Array[2];
    LINE_F4    *field_40_lines_2Array[2];
    TILE_1     *field_48_tiles_2Array[2];
    POLY_G4    *field_50_polys_2Array[2];
    int         field_58_ybase;
    int         field_5C_xbase;
    DVECTOR     field_60_coords_9Array[9];
    int         field_84_4Array[4];
    int         field_94;
} Actor_Stnsight;

STATIC_ASSERT_SIZE(Actor_Stnsight, 0x98);

void stnsight_act_helper_helper_80068320(unsigned int *ot, unsigned int *prim);

void stnsight_act_helper_80068420(Actor_Stnsight *actor, unsigned int *ot);
void stnsight_act_helper_80068798(Actor_Stnsight *actor, unsigned int *ot);
void stnsight_act_helper_80068A24(Actor_Stnsight *actor, unsigned int *ot);
void stnsight_act_helper_80068BF4(Actor_Stnsight *actor, unsigned int *ot);
void stnsight_act_helper_8006837C(Actor_Stnsight *actor);

void stnsight_act_80068D0C(Actor_Stnsight *actor);
void stnsight_kill_80068ED8(Actor_Stnsight *actor);
int stnsight_init_helper_helper_80068F74(Actor_Stnsight *actor);
int stnsight_init_helper_helper_80069100(Actor_Stnsight *actor);
int stnsight_init_helper_helper_80069184(Actor_Stnsight *actor);
int stnsight_init_helper_helper_80069234(Actor_Stnsight *actor);
int stnsight_init_helper_800692D0(Actor_Stnsight *actor, GM_Control *ctrl);
Actor_Stnsight * NewStnSight_800693E0(GM_Control *ctrl);

#endif // _STNSIGHT_H_
