#ifndef _GRENADE_H_
#define _GRENADE_H_

#include "game.h"
#include "actor.h"

// @note(Voxel): Making this a generic unknown struct or now, not sure what it is yet.
typedef struct _Unknown_Grenade_Member
{
    unsigned short a[4];
} Unknown_Grenade_Member;

typedef struct _Actor_Grenade
{
    Actor field_0_actor;
    int f20;
    OBJECT *f24_parent_obj;
    OBJECT f28_obj;    
    int f4c;
    int f50;
    Unknown_Grenade_Member f54;
    int f5c;
    int f60;
    int f64;
} Actor_Grenade;

STATIC_ASSERT_SIZE(Actor_Grenade, 0x68);

#endif // _GRENADE_H_