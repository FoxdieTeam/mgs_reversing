#ifndef _GOGGLEIR_H
#define _GOGGLEIR_H

#include "actor.h"
#include "game.h"

typedef struct _Actor_GoggleIr
{
    Actor field_0_actor;
    OBJECT f20_obj;
    int f44;
    OBJECT *parent_object;
    int num_parent;
    int f50;
    short f54;
    short f56;
    int f58;
    int f5c;
    int f60;
    int f64;
    int f68;
} Actor_GoggleIr;

STATIC_ASSERT_SIZE(Actor_GoggleIr, 0x6C);

#endif // _GOGGLEIR_H