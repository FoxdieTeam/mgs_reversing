#ifndef _FAMAS_H_
#define _FAMAS_H_

#include "Game/game.h"
#include "libgv/libgv.h"
#include "Game/control.h"

typedef struct _Actor_Famas
{
    GV_ACT      field_0_actor;
    OBJECT      f20_obj;
    CONTROL *field_44_pCtrl;
    OBJECT     *parent_object;
    int         num_parent;
    int*        field_50_pFlags;
    int         field_54;
    int         field_58_counter;
    int         field_5C_mp5;
} Actor_Famas;

STATIC_ASSERT_SIZE(Actor_Famas, 0x60);

#endif // _FAMAS_H_
