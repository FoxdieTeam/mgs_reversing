#ifndef _AAM_H_
#define _AAM_H_

#include "Game/game.h"
#include "libgv/libgv.h"
#include "stnsight.h"

// stinger

typedef struct _AamWork
{
    GV_ACT          actor;
    OBJECT_NO_ROTS  object;
    CONTROL        *control;
    OBJECT         *parent;
    int             num_parent;
    unsigned int   *trigger;
    int             side;
    int             cooldown;
    Actor_Stnsight *sight;
} AamWork;

STATIC_ASSERT_SIZE(AamWork, 0x60);

void aam_act_800670CC(AamWork *actor);

AamWork * NewAAM_80067480(CONTROL *ctrl, OBJECT *parent, int num_parent, unsigned int *trigger, int side);

#endif // _AAM
