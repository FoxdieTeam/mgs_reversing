#ifndef _TENAGE_H_
#define _TENAGE_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/object.h"

// the projectile for all types of grenades

typedef struct TenageWork
{
    GV_ACT         field_0_actor;
    CONTROL        control;
    OBJECT_NO_ROTS field_9C_obj;
    MATRIX         field_C0_light_matrices[2];
    int            field_100_homing_arg2;
    int            field_104_count;
    SVECTOR        field_108;
    int            field_110;
    int            field_114_homing_arg3;
    int            field_118_do_sound;
    int            field_11C;
    int            field_120_ctrl_idx;
} TenageWork;

STATIC_ASSERT_SIZE(TenageWork, 0x124);

void tenage_act_800699A4(TenageWork *work);
void tenage_kill_80069DBC(TenageWork *work);

int  tenage_loader_80069E64(TenageWork *work, SVECTOR *vec, SVECTOR *vec2, int, int, int, int);

GV_ACT *NewTenage_8006A010(SVECTOR *vec, SVECTOR *vec2, int param_3, int param_4, int param_5);

#endif // _TENAGE_H_
