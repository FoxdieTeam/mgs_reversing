#ifndef _HIND_BUL_H_
#define _HIND_BUL_H_

#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "game/game.h"

typedef struct _HindBulWork
{
    GV_ACT   actor;      // 0x00
    CONTROL  control;    // 0x20
    TARGET   target;     // 0x84
    int      f0E4;       // 0xE4
    int      enable;     // 0xE8
    int      map;        // 0xEC
    SVECTOR  pos;        // 0xF0
    DG_PRIM *prim;       // 0xF8
    SVECTOR  vertices[16]; // 0xFC - adds 128 bytes for total 0x17C
} HindBulWork;

GV_ACT *NewHindBul_800CB794(CONTROL *control, OBJECT *parent, int num_bullets);

#endif // _HIND_BUL_H_
