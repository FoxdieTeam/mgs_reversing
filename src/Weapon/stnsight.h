#ifndef _STNSIGHT_H_
#define _STNSIGHT_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "Game/control.h"
#include "libgv/libgv.h"

// stinger first person HUD

typedef struct _StnSightWork
{
    GV_ACT      field_0_actor;
    CONTROL    *control;
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

GV_ACT *NewStnSight_800693E0(CONTROL *ctrl);

#endif // _STNSIGHT_H_
