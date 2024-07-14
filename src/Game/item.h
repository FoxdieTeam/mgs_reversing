#ifndef _ITEM_H_
#define _ITEM_H_

#include "linker.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include <KERNEL.H>
#include "Game/game.h"
#include "libdg/libdg.h"
#include "Game/control.h"

typedef struct Item_Info
{
    const char *field_0_pName;
    short       field_4_type;
    short       field_6_id;
    short       field_8_amount;
    short       field_A;
} Item_Info;

typedef struct ItemWork
{
    GV_ACT         field_0;
    CONTROL        control;
    OBJECT_NO_ROTS field_9C_kmd;
    char           field_C0[8];
    MATRIX         field_C8_mtx[2];
    int            field_108_where;
    short          field_10C_64;
    short          field_10E;
    short          field_110_counter;
    unsigned char  field_112_state;
    char           field_113;
    short          field_114_item_id;
    short          field_116_ammo_amount;
    const char    *field_118_str;
    const char    *field_11C_full_str;
    unsigned char *field_120_pScript;
    LINE_F4        field_124_lineF4_array[2];
    DG_PRIM       *field_15C_pPrim;
    SVECTOR        field_160;
    SVECTOR        field_168;
    SVECTOR        field_170;
    SVECTOR        field_178;
} ItemWork;

GV_ACT *item_init_800344F8(int name, int where, int argc, char **argv);
ItemWork * item_init_80034758(SVECTOR *pPos, SVECTOR *a2, Item_Info *pItemInfo);
int  item_init_helper_800345C0(ItemWork *work, SVECTOR *pPos, SVECTOR *a3, Item_Info *pItemInfo, int where);
void item_act_80033784(ItemWork *work);
int  item_init_helper_800340D0(ItemWork *work, int name, int where);
int  item_init_helper_helper_80034020(ItemWork *work, int type);
void item_all_items_and_weapons_unknown2_80033500(void);
void item_all_items_and_weapons_unknown_80033560(void);

#endif // _ITEM_H_
