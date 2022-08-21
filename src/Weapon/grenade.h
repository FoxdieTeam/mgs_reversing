#ifndef _GRENADE_H_
#define _GRENADE_H_

#include "Game/game.h"
#include "Game/object.h"
#include "libgv/libgv.h"

// grenade/stun/chaff (in hands)

typedef struct _Actor_Grenade
{
    Actor                  field_0_actor;
    SVECTOR               *f20_parent_pos;
    OBJECT                *f24_parent_obj;
    OBJECT                 f28_obj;
    int                    f4c;
    int                   *f50;
    SVECTOR                f54_pos;
    int                    f5c;
    int                    f60;
    int                    f64;
} Actor_Grenade;

STATIC_ASSERT_SIZE(Actor_Grenade, 0x68);

int grenade_act_8006641C(int a1);
Actor_Grenade *NewTimerBomb_80066ACC(GM_Control *a1, OBJECT *a2, int num_parent, int *a4, int a5);

#endif // _GRENADE_H_
