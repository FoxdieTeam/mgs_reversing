#ifndef _SCN_MASK_H_
#define _SCN_MASK_H_

#include "linker.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include <sys/types.h>
#include "Equip/gglsight.h"

// Thermal goggles or Night vision goggles screen effect

typedef struct scn_mask_prims
{
    DR_TPAGE field_0_unknown1[2];
    TILE     field_10_tile_big[2];
    DR_TPAGE field_30_unknown2[2];
    TILE     field_40_tile_lines[2][112];
} scn_mask_prims;

typedef struct ScnMaskWork
{
    GV_ACT                  field_0_actor;
    struct scn_mask_prims *field_20_pPrims;
    int                    field_24;
    int                    field_28;
} ScnMaskWork;

GV_ACT *new_scn_mask_8007895C(int a1);

#endif // _SCN_MASK_H_
