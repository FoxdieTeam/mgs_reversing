#ifndef _JIRAI_H_
#define _JIRAI_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "libgv/libgv.h"
#include "libhzd/libhzd.h"
#include "game/control.h"
#include "game/object.h"
#include "game/target.h"

// Claymore (armed)

typedef struct JiraiWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT_NO_ROTS body;
    MATRIX         light[2];
    TARGET        *target;
    SVECTOR        field_104_vec;
    short          field_10C;
    short          field_10E;
    int            field_110;
    int            field_114;
    int            field_118;
    int            field_11C;
    int            field_120;
    int            field_124;
    int            field_128;
    int            field_12C;
    int            field_130;
    long           field_134_gcl_arg;
    int            field_138_gcl;
    int            field_13C_idx;
    int            field_140;
    SVECTOR        field_144_vec;
    int            map;
    int            field_150;
#ifdef VR_EXE
    int            field_154;
#endif
} JiraiWork;

void *NewJirai(MATRIX *world, HZD_FLR *floor);
void *NewScenarioJirai(MATRIX *world, int map);

#endif // _JIRAI_H_
