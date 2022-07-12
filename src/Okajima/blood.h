#ifndef _BLOOD_H
#define _BLOOD_H

#include "game.h"
#include "actor.h"

typedef struct _Actor_Blood
{
    Actor field_0_actor;
	int f20;
	int f24;
	char f28_placeholder[16];
	int current_map;
} Actor_Blood;

STATIC_ASSERT_SIZE(Actor_Blood, 0x3c);

#endif // _BLOOD_H