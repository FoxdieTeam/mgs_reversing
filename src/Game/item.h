#ifndef _ITEM_H_
#define _ITEM_H_

#include "linker.h"
#include "libgv/libgv.h"
#include "libgcl/gcl.h"
#include <KERNEL.H>
#include "Game/game.h"
#include "libdg/libdg.h"
#include "Game/GM_Control.h"

typedef struct Item_Info
{
    const char *field_0_pName;
    short       field_4_type;
    short       field_6_id;
    short       field_8_amount;
    short       field_A;
} Item_Info;

typedef struct Actor_Item
{
    Actor          field_0;
    GM_Control     field_20_ctrl;
    OBJECT         field_9C_kmd;
    char           field_C0[8];
    MATRIX         field_C8_mtx;
    int            field_E8;
    int            field_EC;
    int            field_F0;
    int            field_F4;
    int            field_F8;
    int            field_FC;
    int            field_100;
    int            field_104;
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
    short          field_168;
    short          field_16A;
    short          field_16C;
    short          field_16E;
    short          field_170;
    short          field_172;
    short          field_174;
    short          field_176;
    short          field_178;
    short          field_17A;
    short          field_17C;
    short          field_17E;
} Actor_Item;

int  item_init_helper_800345C0(Actor_Item *pActor, SVECTOR *pPos, SVECTOR *a3, Item_Info *pItemInfo, int where);
void item_act_80033784(Actor_Item *pActor);
int  item_init_helper_800340D0(Actor_Item *pActor, int name, int where);
int  item_init_helper_helper_80034020(Actor_Item *pActor, int type);
void item_all_items_and_weapons_unknown2_80033500(void);
void item_all_items_and_weapons_unknown_80033560(void);

#endif // _ITEM_H_
