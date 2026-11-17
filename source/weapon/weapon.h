#ifndef __MGS_WEAPON_H__
#define __MGS_WEAPON_H__

#include <sys/types.h>
#include "game/game.h"      // for OBJECT, CONTROL

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

/*---------------------------------------------------------------------------*/

/* socom.c */
void *NewSOCOM( CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *flags, int side );

/* famas.c */
void *NewFAMAS( CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *flags, int side );

/* grenade.c */
void *NewGrenade( CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *flags, int side );
void *NewStanGrenade( CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *flags, int side );
void *NewChaffGrenade( CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *flags, int side );
void *NewTimerBomb( CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *flags, int side );

/* rcm.c */
void *NewRCM( CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *flags, int side );

/* aam.c */
void *NewAAM( CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *flags, int side );

/* mine.c */
void *NewMine( CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *flags, int side );

/* bomb.c */
void *NewBomb( CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *flags, int side );

/* rifle.c */
void *NewRifle( CONTROL *root_ctrl, OBJECT *root_obj, int unit, u_long *flags, int side );

/*---------------------------------------------------------------------------*/

/* stnsight.c */
void *NewStnSight( CONTROL *root_ctrl );

/* rfsight.c */
void *NewRifleSight();
void *NewRifleSightFast();

#endif // __MGS_WEAPON_H__
