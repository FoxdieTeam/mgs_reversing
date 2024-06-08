#ifndef _GASMASK_H_
#define _GASMASK_H_

#include "gmsight.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/control.h"

typedef struct GasMaskWork
{
    GV_ACT         field_0_actor;
    OBJECT_NO_ROTS field_20_obj;
    CONTROL       *control;
    OBJECT        *field_48_pParent;
    int            field_4C_unit;
    int            field_50_count;
    GasmaskSightWork *field_54_gmsight;
    short          field_58_maybe_pad; // not sure if padding
    short          field_5A_head_saved_packs;
    short          field_5C_head_saved_raise;
    short          field_5E_maybe_pad; // padding
} GasMaskWork;

GV_ACT * NewGasmask_80060C14(CONTROL *pCtrl, OBJECT *pParent, int unit);

// This has an issue with unused params
GasmaskSightWork * NewGasmaskSight_80063668(void);

#endif // _GASMASK_H_
