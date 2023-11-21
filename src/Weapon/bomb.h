#ifndef _BOMB_H_
#define _BOMB_H_

#include "Game/game.h"
#include "Game/target.h"
#include "libgv/libgv.h"

// c4 (in hands)

typedef struct _BombWork
{
    GV_ACT         field_0_actor;
    CONTROL       *field_20_pCtrl;
    OBJECT        *parent_obj;
    OBJECT_NO_ROTS f28_obj;
    int            num_parent;
    int           *f50;
    int            f54;
    int            f58;
} BombWork;

STATIC_ASSERT_SIZE(BombWork, 0x5c);

void bomb_act_8006788C(BombWork *actor);
int  bomb_loader_80067A94(BombWork *actor_bomb, OBJECT *parent_obj, int num_parent);

#endif // _BOMB_H_
