#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Game/game.h"      // for OBJECT
#include "Game/control.h"   // for CONTROL

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

void *NewSOCOM( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );
void *NewFAMAS( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );

void *NewGrenade( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );
void *NewStanGrenade( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );
void *NewChaffGrenade( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );
void *NewTimerBomb( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );

void *NewRCM( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );
void *NewAAM( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );

void *NewMine( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );
void *NewBomb( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );

void *NewRifle( CONTROL *control, OBJECT *parent, int num_parent, unsigned int *flags, int which_side );

void *NewStnSight( CONTROL *control );

void *NewRifleSight();
void *NewRifleSightFast();

#endif // _WEAPON_H_
