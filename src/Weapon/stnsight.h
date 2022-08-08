#ifndef _STNSIGHT_H_
#define _STNSIGHT_H_

#include "libgv/libgv.h"

// stinger first person HUD

typedef struct Actor_stnsight {
    Actor field_0_actor;
    int field_20_type;
    GV_PAD *field_24_pad_data;
    int field_28;
    char field_2c_padding[44];
    int field_58;
    int field_5c;
    short field_60_18Array[18];
    int field_84_4Array[4];
    int field_94;
} Actor_stnsight;

STATIC_ASSERT_SIZE(Actor_stnsight, 0x98);

void stnsight_act_80068D0C(Actor_stnsight *actor);
void stnsight_kill_80068ED8(Actor_stnsight *actor);
int stnsight_init_helper_helper_80068F74(Actor_stnsight *actor);
int stnsight_init_helper_helper_80069100(Actor_stnsight *actor);
int stnsight_init_helper_helper_80069184(Actor_stnsight *actor);
int stnsight_init_helper_helper_80069234(Actor_stnsight *actor);
int stnsight_init_helper_800692D0(Actor_stnsight *actor, int type);
Actor_stnsight * NewStnSight_800693E0(int type);

#endif // _STNSIGHT_H_
