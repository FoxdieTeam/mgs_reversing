// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C8314, camera_800C838C), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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

extern int vrtitle_dword_800C1BCC;

void vrtitle_800D0188(MenuPrim *prim, SELECT_INFO *info)
{
    DR_TPAGE *pTpage;

    _NEW_PRIM(pTpage, prim);

    setlen(pTpage, 1);
    pTpage->code[0] = 0xE100061F | ((*(int *)((char *)info + 8) >> 3) & 0x60);
    addPrim(prim->ot, pTpage);
}

void vrtitle_800D0200(MenuPrim *prim, CaptionInfo *info, char *str)
{
    SPRT   *sprt;
    u_long *ot;
    int     x;
    int     color;
    int     c;
    int     u, v, w;
    char   *tbl;

    x = info->x;
    ot = prim->ot;
    color = info->color;

    for (; *str; str++)
    {
        c = *str | 0x20;

        if ((unsigned int)(c - '0') < 10)
        {
            u = (c - '0') * 8;
            v = 0xF8;
            w = 9;
        }
        else if ((unsigned int)(c - 'a') < 26)
        {
            if (c == 'i')
            {
                x += 3;
                u = 0x40;
                v = 0xF2;
                w = 6;
            }
            else
            {
                u = (c - 'a') * 8;
                v = 0xF2;
                w = 9;
            }
        }
        else if (c == ' ')
        {
            x += 9;
            continue;
        }
        else
        {
            u = 0;
            for (tbl = (char *)&vrtitle_dword_800C1BCC;; tbl += 2, u += 8)
            {
                if (*tbl == c)
                {
                    if (c == '!' || c == ':' || c == '[' || c == ']')
                    {
                        x += 3;
                        u += 0x50;
                        v = 0xF8;
                        w = 6;
                    }
                    else
                    {
                        u += 0x50;
                        v = 0xF8;
                        w = 9;
                    }
                    break;
                }
            }
        }

        _NEW_PRIM(sprt, prim);
        *sprt = vrtitle_dword_800D9D84;
        *(int *)&sprt->r0 = color;
        sprt->x0 = x;
        sprt->y0 = info->y;
        sprt->u0 = u;
        sprt->v0 = v;
        x += w;
        addPrim(ot, sprt);
    }
}
