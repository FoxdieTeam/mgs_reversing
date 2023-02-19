#ifndef _TENAGE_H_
#define _TENAGE_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "libgv/libgv.h"
#include "Game/GM_Control.h"
#include "Game/object.h"

// the projectile for all types of grenades

typedef struct Actor_tenage
{
    GV_ACT     field_0_actor;
    GM_Control field_20_ctrl;
    OBJECT     field_9C_obj;
    MATRIX     field_C0_light_matrices[2];
    int        field_100_homing_arg2;
    int        field_104_count;
    SVECTOR    field_108;
    int        field_110;
    int        field_114_homing_arg3;
    int        field_118_do_sound;
    int        field_11C;
    int        field_120_ctrl_idx;
} Actor_tenage;

STATIC_ASSERT_SIZE(Actor_tenage, 0x124);

void tenage_act_800699A4(Actor_tenage *pActor);
void tenage_kill_80069DBC(Actor_tenage *pActor);

int  tenage_loader_80069E64(Actor_tenage *pActor, SVECTOR *vec, SVECTOR *vec2, int, int, int, int);

Actor_tenage * NewTenage_8006A010(SVECTOR *vec, SVECTOR *vec2, int param_3, int param_4, int param_5);

#endif // _TENAGE_H_
