// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C6054), transplanted from the main-tree twin; offsets/constants adapted to the VR.
// Note that there are two "camera.c" actors,
// this is probably not the enemy/camera.c actor.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libpress.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libfs/libfs.h"
#include "menu/menuman.h"
#include "menu/radio.h"
#include "memcard/memcard.h"
#include "game/game.h"
#include "mts/mts.h"
#include "mts/taskid.h"
#include "overlays/camera/unknown/camera.h"

void vrtitle_800CDB88(SPRT *sprt);

extern char                       *MGS_MemoryCardName; /* in main.c */

void vrtitle_800CDEB8(MenuWork *work, u_long *ot, SELECT_INFO *info)
{
    unsigned int xoff;
    SPRT        *pPrim;
    KCB         *kcb;

    kcb = work->field_214_font;

    NEW_PRIM(pPrim, work);

    vrtitle_800CDB88(pPrim);

    xoff = kcb->max_width;

    pPrim->y0 = 200;
    pPrim->v0 = 4;
    pPrim->w = 252;
    pPrim->h = 14;
    pPrim->u0 = 0;
    pPrim->x0 = 160 - xoff / 2;

    addPrim(ot, pPrim);
}
