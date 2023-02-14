#ifndef _GOGGLE_H
#define _GOGGLE_H

#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/GM_Control.h"

// night vision goggles (screen effect)

typedef struct Actor_goggle
{
    GV_ACT       field_0_actor;
    OBJECT      field_20_obj;
    GM_Control *field_44_pCtrl;
    OBJECT     *field_48_pObj;
    int         field_4C_head_hidden;
    int         field_50;
    GV_ACT      *field_54_pScn_mask;
    GV_ACT      *field_58_actor_unknown;
    short       field_5C_saved_n_packs;
    short       field_5E_saved_rise;
} Actor_goggle;

void set_pal_effect_fns_80079194(void *fn1, void *fn2);
ushort goggle_pal_convert_8007743C(ushort);
void goggle_pal_cb_800774C0(void);
int  goggle_loader_8007773C(Actor_goggle *a1, OBJECT *a2);

#endif // _GOGGLE_H
