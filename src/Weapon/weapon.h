#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Game/game.h"      // for OBJECT
#include "Game/control.h"   // for CONTROL
#include "libgv/libgv.h"    // for GV_ACT

#define WEAPON_TAKE     1
#define WEAPON_TRIG     2
#define WEAPON_TRIG2    4

enum GRENADE_TYPE
{
    GRD_GRENADE = 0,
    GRD_STUN    = 1,
    GRD_CHAFF   = 2,
    GRD_TBOMB   = 3
};

GV_ACT *NewSOCOM( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );
GV_ACT *NewFAMAS( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );

GV_ACT *NewGrenade( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );
GV_ACT *NewStanGrenade( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );
GV_ACT *NewChaffGrenade( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );
GV_ACT *NewTimerBomb( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );

GV_ACT *NewRCM( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );
GV_ACT *NewAAM( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );

GV_ACT *NewMine( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );
GV_ACT *NewBomb( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );

GV_ACT *NewRifle( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );

GV_ACT *NewStnSight( CONTROL *control );

GV_ACT *NewRifleSight();
GV_ACT *NewRifleSightFast();

#endif // _WEAPON_H_
