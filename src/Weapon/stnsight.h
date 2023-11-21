#ifndef _STNSIGHT_H_
#define _STNSIGHT_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

#include "Game/control.h"
#include "libgv/libgv.h"

// stinger first person HUD

typedef struct _StnSightWork
{
    GV_ACT      field_0_actor;
    CONTROL    *field_20_ctrl;
    GV_PAD     *field_24_pad_data;
    LINE_F4    *field_28_lines_2Array[2];
    LINE_F4    *field_30_lines_2Array[2];
    LINE_F4    *field_38_lines_2Array[2];
    LINE_F4    *field_40_lines_2Array[2];
    TILE_1     *field_48_tiles_2Array[2];
    POLY_G4    *field_50_polys_2Array[2];
    int         field_58_ybase;
    int         field_5C_xbase;
    DVECTOR     field_60_coords_9Array[9];
    int         field_84_4Array[4];
    int         field_94;
} StnSightWork;

STATIC_ASSERT_SIZE(StnSightWork, 0x98);

void stnsight_act_helper_helper_80068320(unsigned int *ot, unsigned int *prim);

void stnsight_act_helper_80068420(StnSightWork *actor, unsigned int *ot);
void stnsight_act_helper_80068798(StnSightWork *actor, unsigned int *ot);
void stnsight_act_helper_80068A24(StnSightWork *actor, unsigned int *ot);
void stnsight_act_helper_80068BF4(StnSightWork *actor, unsigned int *ot);
void stnsight_act_helper_8006837C(StnSightWork *actor);

void stnsight_act_80068D0C(StnSightWork *actor);
void stnsight_kill_80068ED8(StnSightWork *actor);
int stnsight_init_helper_helper_80068F74(StnSightWork *actor);
int stnsight_init_helper_helper_80069100(StnSightWork *actor);
int stnsight_init_helper_helper_80069184(StnSightWork *actor);
int stnsight_init_helper_helper_80069234(StnSightWork *actor);
int stnsight_init_helper_800692D0(StnSightWork *actor, CONTROL *ctrl);
StnSightWork * NewStnSight_800693E0(CONTROL *ctrl);

#endif // _STNSIGHT_H_
