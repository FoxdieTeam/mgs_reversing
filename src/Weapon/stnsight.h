#ifndef _STNSIGHT_H_
#define _STNSIGHT_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

#include "libgv/libgv.h"

// stinger first person HUD

// this structure is passed down from the parent of the parent of this actor, not sure what it is yet
typedef struct Actor_stnsight_unk {
    SVECTOR field_0;
    short field_8_x;
    short field_A_y;
    char pad2[32];
    int *field_2C;
    char pad3[28];
    short field_4C;
} Actor_stnsight_unk;

typedef struct Actor_stnsight {
    Actor field_0_actor;
    Actor_stnsight_unk *field_20;
    GV_PAD *field_24_pad_data;
    LINE_F4 *field_28_lines_2Array[2];
    LINE_F4 *field_30_lines_2Array[2];
    LINE_F4 *field_38_lines_2Array[2];
    LINE_F4 *field_40_lines_2Array[2];
    TILE_1 *field_48_tiles_2Array[2];
    POLY_G4 *field_50_polys_2Array[2];
    int field_58_ybase;
    int field_5C_xbase;
    DVECTOR field_60_coords_9Array[9];
    int field_84_4Array[4];
    int field_94;
} Actor_stnsight;

STATIC_ASSERT_SIZE(Actor_stnsight, 0x98);

void stnsight_act_helper_helper_80068320(unsigned int *ot, unsigned int *prim);

void stnsight_act_helper_80068420(Actor_stnsight *actor, unsigned int *ot);
void stnsight_act_helper_80068798(Actor_stnsight *actor, unsigned int *ot);
void stnsight_act_helper_80068A24(Actor_stnsight *actor, unsigned int *ot);
void stnsight_act_helper_80068BF4(Actor_stnsight *actor, unsigned int *ot);
void stnsight_act_helper_8006837C(Actor_stnsight *actor);

void stnsight_act_80068D0C(Actor_stnsight *actor);
void stnsight_kill_80068ED8(Actor_stnsight *actor);
int stnsight_init_helper_helper_80068F74(Actor_stnsight *actor);
int stnsight_init_helper_helper_80069100(Actor_stnsight *actor);
int stnsight_init_helper_helper_80069184(Actor_stnsight *actor);
int stnsight_init_helper_helper_80069234(Actor_stnsight *actor);
int stnsight_init_helper_800692D0(Actor_stnsight *actor, void *unknown);
Actor_stnsight * NewStnSight_800693E0(void *unknown);

#endif // _STNSIGHT_H_
