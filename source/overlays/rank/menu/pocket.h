#ifndef _RANK_MENU_POCKET_H
#define _RANK_MENU_POCKET_H

#include "libgv/libgv.h"
#include "menu/menuman.h"
#include "menu/radio.h"

typedef struct _Work {
    GV_ACT    actor;
    KCB       kcb;
    int       proc_id;
    int       field_50;
    MenuPrim *prim_ptr;
    MenuPrim  prim;
    char      primbuf[ 2 ][ 0x2000 ];
} Work;

#endif
