#ifndef _AMISSILE_H_
#define _AMISSILE_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>

#include "Game/control.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"

// stinger missile?

typedef struct AMissileWork
{
    GV_ACT         field_0_actor;
    CONTROL        field_20_ctrl;
    OBJECT_NO_ROTS field_9C_kmd;
    MATRIX         field_C0_light_matrix[2];
    MATRIX         field_100_rotation_matrix;
    int            field_120;
    int            field_124;
    int            field_128;
    SVECTOR        field_12C_svector;
    DG_PRIM       *field_134_prim;
    RECT           field_138_rect;
    SVECTOR        field_140_svector_4Array[4];
} AMissileWork;

STATIC_ASSERT_SIZE(AMissileWork, 0x160);

void amissile_act_8006D608(AMissileWork *work);
void amissile_act_helper_8006D2A0(AMissileWork *work, SVECTOR input);
void amissile_act_helper_8006D37C(AMissileWork *work);
int  amissile_act_helper_8006D600(void);

void amissile_kill_8006D99C(AMissileWork *work);

int  amissile_loader_8006DA0C(AMissileWork *work, MATRIX *pMtx, int);
void amissile_loader_helper_8006D1F4(POLY_FT4 *pPoly, DG_TEX *pTex);

AMissileWork * NewAMissile_8006DC50(MATRIX *pMtx, int);

#endif // _AMISSILE_H_
