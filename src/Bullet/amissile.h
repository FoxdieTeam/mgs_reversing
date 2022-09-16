#ifndef _AMISSILE_H_
#define _AMISSILE_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>

#include "libgv/libgv.h"

// stinger missile?

typedef struct Actor_amissile
{
    Actor   field_0_actor;
    char    field_20[256];
    int     field_120;
    int     field_124;
    int     field_128;
    SVECTOR field_12C_svector;
    char    field_134[44];
} Actor_amissile;

void amissile_act_8006D608(Actor_amissile *pActor);
int  amissile_act_helper_8006D600(void);

void amissile_kill_8006D99C(Actor_amissile *pActor);

int amissile_loader_8006DA0C(Actor_amissile *pActor, int, void *);

Actor_amissile * NewAMissile_8006DC50(int arg0, void *arg1);

#endif // _AMISSILE_H_
