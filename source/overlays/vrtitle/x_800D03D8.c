// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C8564, camera_800C85B8, camera_800C85D8, camera_800C864C), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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

extern char                       *MGS_MemoryCardName; /* in main.c */
extern SPRT                        vrtitle_dword_800D9D84;

void vrtitle_800D03D8(MenuPrim *prim, SELECT_INFO *info, char *arg2)
{
    char sp10[64];

    sprintf(sp10, arg2);
    vrtitle_800D0200(prim, (CaptionInfo *)info, sp10);
    vrtitle_800D0188(prim, info);
}

void vrtitle_800D042C(int *arg0, int r, int g, int b)
{
    arg0[3] = (r | (g << 8) | (b << 16) | (GPU_CODE_SPRT << 24));
}

void vrtitle_800D044C(void)
{
    short sp0[4];
    SPRT *sprt;

    // Let's waste cycles by puting unused stuff on stack:
    sp0[0] = 976;
    sp0[1] = 511;
    sp0[2] = 16;
    sp0[3] = 1;

    sprt = &vrtitle_dword_800D9D84;
    LSTORE(0x80808080, &sprt->r0);
    setUV0(sprt, 0, 242);
    setWH(sprt, 8, 6);
    setSprt(sprt);
    setClut(sprt, 976, 511);
}

void vrtitle_800D04C0(Work *work)
{
    int i;

    for (i = 3; i >= 0; i--)
    {
        work->field_654[i] = 0;
    }

    for (i = 8; i >= 0; i--)
    {
        work->field_664[i] = NULL;
    }

    for (i = 0x19; i >= 0; i--)
    {
        work->field_688[i] = NULL;
    }
}
