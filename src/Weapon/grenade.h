#ifndef _GRENADE_H_
#define _GRENADE_H_

#include "Game/control.h"
#include "Game/game.h"
#include "Game/object.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "psyq.h"

// grenade/stun/chaff (in hands)

typedef struct _GrenadeWork
{
    GV_ACT         actor;
    CONTROL       *f20_ctrl;
    OBJECT        *f24_parent_obj;
    OBJECT_NO_ROTS f28_obj;
    int            f4c_map_id;
    int           *f50_flags;
    SVECTOR        f54_pos;
    int            f5c_timer;
    int            f60_grenade_type;
    int            f64_has_exploded;
} GrenadeWork;

enum GRENADE_TYPE
{
    GRD_GRENADE = 0,
    GRD_STUN = 1,
    GRD_CHAFF = 2,
    GRD_TBOMB = 3
};

GV_ACT *NewTimerBomb_80066ACC( CONTROL *a1, OBJECT *a2, int num_parent, unsigned int *a4, int a5 );
GV_ACT *NewStanGrenade_80066A74( CONTROL *ctrl, OBJECT *parent_obj, int num_parent, unsigned int *flags, int unused );
GV_ACT *NewChaffGrenade_80066AA0( CONTROL *ctrl, OBJECT *parent_obj, int num_parent, unsigned int *flags, int unused );
GV_ACT *NewTimerBomb_80066ACC( CONTROL *ctrl, OBJECT *parent_obj, int num_parent, unsigned int *flags, int unused );
GV_ACT *grenade_create_80066A4C( CONTROL *ctrl, OBJECT *parent_obj, int num_parent, unsigned int *flags, int unused );

#endif // _GRENADE_H_
