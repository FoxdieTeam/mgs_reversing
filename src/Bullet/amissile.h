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
    MATRIX     field_C0_matrix;
    char       field_E0[32];
    MATRIX     field_100_matrix;
    int        field_120;
    int        field_124;
    int        field_128;
    SVECTOR    field_12C_svector;
    DG_PRIM   *field_134_prim;
    RECT       field_138_rect;
    SVECTOR    field_140_svector_4Array[4];
} Actor_amissile;

STATIC_ASSERT_SIZE(Actor_amissile, 0x160);

void amissile_act_8006D608(Actor_amissile *pActor);
void amissile_act_helper_8006D2A0(Actor_amissile *pActor, SVECTOR input);
void amissile_act_helper_8006D37C(Actor_amissile *pActor);
int  amissile_act_helper_8006D600(void);

void amissile_kill_8006D99C(Actor_amissile *pActor);

int  amissile_loader_8006DA0C(Actor_amissile *pActor, MATRIX *pMtx, int);
void amissile_loader_helper_8006D1F4(POLY_FT4 *pPoly, DG_TEX *pTex);

Actor_amissile * NewAMissile_8006DC50(MATRIX *pMtx, int);

#endif // _AMISSILE_H_
