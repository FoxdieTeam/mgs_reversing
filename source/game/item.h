#ifndef __MGS_GAME_ITEM_H__
#define __MGS_GAME_ITEM_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "common.h"

typedef struct Item_Info
{
    const char *field_0_pName;
    short       field_4_type;
    short       field_6_id;
    short       field_8_amount;
    short       field_A;
} Item_Info;

void *NewItem(int name, int where, int argc, char **argv);
void *item_init_80034758(SVECTOR *pPos, SVECTOR *a2, Item_Info *pItemInfo);

void item_all_items_and_weapons_unknown2_80033500(void);
void item_all_items_and_weapons_unknown_80033560(void);

#endif // __MGS_GAME_ITEM_H__
