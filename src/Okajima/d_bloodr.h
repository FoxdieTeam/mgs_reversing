#ifndef _D_BLOODR_H_
#define _D_BLOODR_H_

#include "libdg/libdg.h"
#include "libgv/libgv.h"

typedef struct _DBloodWorkr
{
    GV_ACT   actor;
    DG_PRIM *field_20_prims;
    SVECTOR  field_24[16];
    SVECTOR  field_A4_positions[4];
    SVECTOR  field_C4_rotation;
    int      field_CC_map;
    char     field_D0_pad[0x4];
    int      field_D4_sequence;
    int      field_D8;
} DBloodWorkr;

GV_ACT *NewKetchap_r_80073148(int map);

#endif // _D_BLOODR_H_
