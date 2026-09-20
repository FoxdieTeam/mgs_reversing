#ifndef __MGS_GAME_ITEM_H__
#define __MGS_GAME_ITEM_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "mgstype.h"

typedef struct ITEM_INFO {
    const char *message;
    short       type;
    short       id;
    short       num;
    short       time;
} ITEM_INFO;

void *NewItem(int name, int where, int argc, char **argv);
void *NewItemPut(SVECTOR *pos, SVECTOR *step, ITEM_INFO *info);

void disable_equipment(void);
void enable_equipment(void);

#endif // __MGS_GAME_ITEM_H__
