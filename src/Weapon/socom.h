#ifndef _SOCOM_H
#define _SOCOM_H

#include "Script_tbl_map_8002BB44.h"
#include "Game/game.h"
#include "libgv/actor.h"
#include "Game/GM_Control.h"

typedef struct _Actor_Socom
{
    Actor       field_0_actor;
    OBJECT      field_20;
    GM_Control *field_44_pCtrl;
    OBJECT     *field_48_parent_object;
    int         field_4C_obj_idx;
    int         field_50_ptr;
    short       field_54_bullet_type;
    short       field_56;
    DG_PRIM    *field_58_prim;
    void       *field_5C_pTexture;
    SVECTOR     field_60_array[20];
    int         field_100;
    int         field_104_rnd;
    int         field_108;
    DG_PRIM    *field_10C_pPrim;
    SVECTOR     field_110;
    SVECTOR     field_118;
} Actor_Socom;

STATIC_ASSERT_SIZE(Actor_Socom, 0x120);

#endif // _SOCOM_H
