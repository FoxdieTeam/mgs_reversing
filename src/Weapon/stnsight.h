#ifndef _STNSIGHT_H_
#define _STNSIGHT_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

#include "libgv/libgv.h"

// stinger first person HUD

typedef struct Actor_stnsight {
    Actor field_0_actor;
    int field_20_type;
    GV_PAD *field_24_pad_data;
    LINE_F4 *field_28_lines;
    LINE_F4 *field_2C_lines;
    LINE_F4 *field_30_lines;
    LINE_F4 *field_34_lines;
    LINE_F4 *field_38_lines;
    LINE_F4 *field_3C_lines;
    LINE_F4 *field_40_lines;
    LINE_F4 *field_44_lines;
    TILE_1 *field_48_tiles;
    TILE_1 *field_4C_tiles;
    POLY_G4 *field_50_polys_2Array[2];
    int field_58;
    int field_5C;
    short field_60_18Array[18];
    int field_84_4Array[4];
    int field_94;
} Actor_stnsight;

STATIC_ASSERT_SIZE(Actor_stnsight, 0x98);

void stnsight_act_helper_helper_80068320(unsigned int *ot, unsigned int *prim);

void stnsight_act_helper_80068420(Actor_stnsight *actor, unsigned char *);
void stnsight_act_helper_80068798(Actor_stnsight *actor, unsigned char *);
void stnsight_act_helper_80068A24(Actor_stnsight *actor, unsigned char *);
void stnsight_act_helper_80068BF4(Actor_stnsight *actor, unsigned int *);
void stnsight_act_helper_8006837C(Actor_stnsight *actor);

void stnsight_act_80068D0C(Actor_stnsight *actor);
void stnsight_kill_80068ED8(Actor_stnsight *actor);
int stnsight_init_helper_helper_80068F74(Actor_stnsight *actor);
int stnsight_init_helper_helper_80069100(Actor_stnsight *actor);
int stnsight_init_helper_helper_80069184(Actor_stnsight *actor);
int stnsight_init_helper_helper_80069234(Actor_stnsight *actor);
int stnsight_init_helper_800692D0(Actor_stnsight *actor, int type);
Actor_stnsight * NewStnSight_800693E0(int type);

#endif // _STNSIGHT_H_
