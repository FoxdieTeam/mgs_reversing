#ifndef _BOMB_H_
#define _BOMB_H_

#include "Game/game.h"
#include "Game/target.h"
#include "libgv/libgv.h"

// c4 (in hands)

typedef struct _BombWork
{
    GV_ACT         field_0_actor;
    CONTROL       *control;
    OBJECT        *parent_obj;
    OBJECT_NO_ROTS f28_obj;
    int            num_parent;
    int           *f50;
    int            f54;
    int            f58;
} BombWork;

GV_ACT *NewBomb_80067B20(CONTROL *ctrl, OBJECT *parent_obj, int num_parent, int *a4, int a5);

#endif // _BOMB_H_
