#ifndef _FAMAS_H_
#define _FAMAS_H_

#include "game.h"
#include "actor.h"

typedef struct _Actor_Famas
{
    Actor field_0_actor;
    OBJECT f20_obj;
    int f44;
    int f48;
    int f4c;
    int f50;
    int f54;
    int f58;
    int f5c;
} Actor_Famas;

STATIC_ASSERT_SIZE(Actor_Famas, 0x60);

#endif // _FAMAS_H_