#ifndef _RCM_H_
#define _RCM_H_

#include "game.h"
#include "actor.h"

// nikita

typedef struct _Actor_Acm
{
    Actor field_0_actor;
    OBJECT* f20_obj;
    int f24;
    int f28;
    int f2c;
    int f30;
    int f34;
    int f38;
    int f3c;
    int f40;
    int f44;
    int f48;
    int f4c;
    int f50;
    int f54;
    int f58;
    DG_PRIM *f5c_prim;
    int f60;
} Actor_Rcm;

STATIC_ASSERT_SIZE(Actor_Rcm, 0x64);

#endif  // _RCM_H_
