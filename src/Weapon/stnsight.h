#ifndef _STNSIGHT_H_
#define _STNSIGHT_H_

#include "libgv/libgv.h"

// stinger first person HUD

typedef struct Actor_stnsight
{
    Actor actor;
    int   field_20_pad[30];
} Actor_stnsight;

STATIC_ASSERT_SIZE(Actor_stnsight, 0x98);

void stnsight_act_80068D0C(Actor_stnsight *actor);
void stnsight_kill_80068ED8(Actor_stnsight *actor);
int stnsight_init_helper_800692D0(Actor_stnsight *actor, int type);
Actor_stnsight * NewStnSight_800693E0(int type);

#endif // _STNSIGHT_H_
