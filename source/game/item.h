#ifndef __MGS_GAME_ITEM_H__
#define __MGS_GAME_ITEM_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "common.h"

typedef struct Item_Info
{
    const char *message;
    short       type;
    short       id;
    short       num;
    short       time;
} Item_Info;

void *NewItem(int name, int where, int argc, char **argv);
void *NewItemPut(SVECTOR *pos, SVECTOR *step, Item_Info *info);

void disable_equipment(void);
void enable_equipment(void);

#endif // __MGS_GAME_ITEM_H__
