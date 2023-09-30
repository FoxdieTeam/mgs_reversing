#ifndef _KOGAKU2_H_
#define _KOGAKU2_H_

#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/control.h"

typedef struct Actor_kogaku2
{
    GV_ACT   field_0_actor;
    OBJECT *field_20_pObj;
    int     field_24_unit;
    int     field_28_obj_old_flag;
    int     field_2C_ypos2;
    int     field_30_ypos1;
    int     field_34_ypos3_ninja;
    int     field_38_ninja_var;
    int     field_3C_msg_is_8650;
    int     field_40_rgb;
} Actor_kogaku2;

POLY_GT4 *kogaku2_tpage_uv_update_80060F98(POLY_GT4 *pPrims, int pack_count);
POLY_GT4 *kogaku2_tpage_uv_rgb_update_800610A4(POLY_GT4 *pPack, int pack_count, int ypos);
void      kogaku2_act_nullsub_800615F4(Actor_kogaku2 *pActor);
void      kogaku2_act_helper_80061528(Actor_kogaku2 *pActor);

GV_ACT * NewKogaku2_800615FC(CONTROL *pCtrl, OBJECT *pObj, int unit);
GV_ACT * NewKogaku3_80061708(CONTROL *pCtrl, OBJECT *pObject, int unit);

#endif // _KOGAKU2_H_
