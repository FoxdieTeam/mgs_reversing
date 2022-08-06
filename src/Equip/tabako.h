#ifndef _TABAKO_H_
#define _TABAKO_H_

#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/GM_Control.h"
#include "Game/game.h"

// cigarettes

typedef struct Actor_tabako
{
    Actor          field_0;
    OBJECT_NO_ROTS field_20_pObj;
    GM_Control    *field_44_pCtrl;
    OBJECT        *field_48_pObj;
    int            field_4C_unknown;
    DG_PRIM       *field_50_prims;
    SVECTOR        field_54_vec;
    RECT           field_5C_unknown;
    // short field_5E;
    // short field_60_unknown;
    // short field_62;
} Actor_tabako;

#endif // _TABAKO_H_
