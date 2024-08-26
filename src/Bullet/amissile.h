#ifndef _AMISSILE_H_
#define _AMISSILE_H_

#include <sys/types.h>
#include <libgte.h>

#include "Game/control.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"

// stinger missile?

typedef struct AMissileWork
{
    GV_ACT         field_0_actor;
    CONTROL        control;
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

GV_ACT *NewAMissile_8006DC50(MATRIX *pMtx, int);

#endif // _AMISSILE_H_
