#ifndef _BOMB_H_
#define _BOMB_H_

#include "Game/game.h"
#include "Game/target.h"
#include "libgv/libgv.h"

// c4 (in hands)

typedef struct _Actor_Bomb
{
    GV_ACT       field_0_actor;
    GM_Control *field_20_pCtrl;
    OBJECT     *parent_obj;
    OBJECT      f28_obj;
    int         num_parent;
    int        *f50;
    int         f54;
    int         f58;
} Actor_Bomb;

STATIC_ASSERT_SIZE(Actor_Bomb, 0x5c);

void bomb_act_8006788C(Actor_Bomb *actor);
int  bomb_loader_80067A94(Actor_Bomb *actor_bomb, OBJECT *parent_obj, int num_parent);

#endif // _BOMB_H_
