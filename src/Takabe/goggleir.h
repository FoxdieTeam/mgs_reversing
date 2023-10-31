#ifndef _GOGGLEIR_H
#define _GOGGLEIR_H

#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/control.h"

// thermal goggles (screen effect)

typedef struct Actor_GoggleIr
{
    GV_ACT         field_0_actor;
    OBJECT_NO_ROTS field_20_obj;
    CONTROL       *field_44_pCtrl;
    OBJECT        *field_48_pParent;
    int            field_4C_head_hidden;
    int            field_50;
    GV_ACT        *field_54_pScn_mask;
    GV_ACT        *field_58_pGglmng;
    int            field_5C;
    int            field_60;
    GV_ACT        *field_64_pGglmng;
    short          field_68_savedNPacks;
    short          field_6A_saved_raise;
} Actor_GoggleIr;

STATIC_ASSERT_SIZE(Actor_GoggleIr, 0x6C);

GV_ACT *gglmng_init_800779B8(int type);
ushort goggleir_pal_convert_800789E0(ushort value);

GV_ACT * NewGoggleIr_80078E6C(CONTROL *pCtrl, OBJECT *parent_obj, int unused);

#endif // _GOGGLEIR_H
