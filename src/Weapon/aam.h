#ifndef _AAM_H_
#define _AAM_H_

#include "Game/game.h"
#include "Game/control.h"
#include "libgv/libgv.h"

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
    GV_ACT         *sight;
} AamWork;

GV_ACT *NewAAM_80067480(CONTROL *ctrl, OBJECT *parent, int num_parent, unsigned int *trigger, int side);

#endif // _AAM
