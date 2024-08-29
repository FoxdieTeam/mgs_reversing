#ifndef _GOGGLE_H
#define _GOGGLE_H

#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/control.h"

// night vision goggles (screen effect)

typedef struct GoggleWork
{
    GV_ACT         actor;
    OBJECT_NO_ROTS field_20_obj;
    CONTROL       *control;
    OBJECT        *field_48_pObj;
    int            field_4C_head_hidden;
    int            field_50;
    GV_ACT        *field_54_pScn_mask;
    GV_ACT        *field_58_pGglmng;
    short          field_5C_saved_n_packs;
    short          field_5E_saved_rise;
} GoggleWork;

GV_ACT *NewGoggle_8007781C(CONTROL *a1, OBJECT *parent_obj, int unused);

#endif // _GOGGLE_H
