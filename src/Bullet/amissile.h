#ifndef _AMISSILE_H_
#define _AMISSILE_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>

#include "Game/GM_Control.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"

// stinger missile?

typedef struct Actor_amissile
{
    Actor      field_0_actor;
    GM_Control field_20_ctrl;
    OBJECT     field_9C_kmd;
    char       field_C0[96];
    int        field_120;
    int        field_124;
    int        field_128;
    SVECTOR    field_12C_svector;
    DG_PRIM   *field_134_prim;
    char       field_138[40];
} Actor_amissile;

STATIC_ASSERT_SIZE(Actor_amissile, 0x160);

void amissile_act_8006D608(Actor_amissile *pActor);
int  amissile_act_helper_8006D600(void);

void amissile_kill_8006D99C(Actor_amissile *pActor);

int amissile_loader_8006DA0C(Actor_amissile *pActor, int, void *);

Actor_amissile * NewAMissile_8006DC50(int arg0, void *arg1);

#endif // _AMISSILE_H_
