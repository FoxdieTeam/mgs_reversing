// vrtitle: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C86BC, camera_800C86BC, camera_800C89DC), transplanted from the main-tree twin; offsets/constants adapted to the VR.
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

void vrtitle_800D0530(Work *work, int x, int y, int w, int h, int color, int unused)
{
    POLY_FT4 *p;
    int i;
    int xl0, xl1, xr0, xr1, yt0, yt1, yb0, yb1;
    int xw, yh;

    p = work->polys;
    for (i = 0; i < 9; i++)
    {
        work->field_664[i] = (GV_ACT *)0x400;
        setRGB0(&p[i], color, color, color);
    }

    xw = x + w;
    yh = y + h;
    xl0 = x - 6;   xl1 = x + 2;
    yt0 = y - 6;   yt1 = y + 2;
    xr0 = xw - 2;  xr1 = xw + 6;
    yb0 = yh - 2;  yb1 = yh + 6;

    /* corners */
    setXY4(&p[0], xl0, yt0, xl1, yt0, xl0, yt1, xl1, yt1);
    setXY4(&p[1], xr0, yt0, xr1, yt0, xr0, yt1, xr1, yt1);
    setXY4(&p[2], xl0, yb0, xl1, yb0, xl0, yb1, xl1, yb1);
    setXY4(&p[3], xr0, yb0, xr1, yb0, xr0, yb1, xr1, yb1);
    /* edges */
    setXY4(&p[4], xl1, yt0, xr0, yt0, xl1, yt1, xr0, yt1);
    setXY4(&p[5], xl1, yb0, xr0, yb0, xl1, yb1, xr0, yb1);
    setXY4(&p[6], xl0, yt1, xl1, yt1, xl0, yb0, xl1, yb0);
    setXY4(&p[7], xr0, yt1, xr1, yt1, xr0, yb0, xr1, yb0);
    /* center */
    setXY4(&p[8], xl1, yt1, xr0, yt1, xl1, yb0, xr0, yb0);
}

void vrtitle_800D06C0(Work *work, int x, int y, int w, int h, int color, int unused)
{
    POLY_FT4 *p;
    int i;
    int xl0, xl1, xr0, xr1, yt0, yt1, yb0, yb1;
    int xw, yh;

    p = work->polys;
    for (i = 0; i < 9; i++)
    {
        work->field_664[i] = (GV_ACT *)0x200;
        setRGB0(&p[i], color, color, color);
    }

    xw = x + w;
    yh = y + h;
    xl0 = x - 6;   xl1 = x + 2;
    yt0 = y - 6;   yt1 = y + 2;
    xr0 = xw - 2;  xr1 = xw + 6;
    yb0 = yh - 2;  yb1 = yh + 6;

    /* corners */
    setXY4(&p[0], xl0, yt0, xl1, yt0, xl0, yt1, xl1, yt1);
    setXY4(&p[1], xr0, yt0, xr1, yt0, xr0, yt1, xr1, yt1);
    setXY4(&p[2], xl0, yb0, xl1, yb0, xl0, yb1, xl1, yb1);
    setXY4(&p[3], xr0, yb0, xr1, yb0, xr0, yb1, xr1, yb1);
    /* edges */
    setXY4(&p[4], xl1, yt0, xr0, yt0, xl1, yt1, xr0, yt1);
    setXY4(&p[5], xl1, yb0, xr0, yb0, xl1, yb1, xr0, yb1);
    setXY4(&p[6], xl0, yt1, xl1, yt1, xl0, yb0, xl1, yb0);
    setXY4(&p[7], xr0, yt1, xr1, yt1, xr0, yb0, xr1, yb0);
    /* center */
    setXY4(&p[8], xl1, yt1, xr0, yt1, xl1, yb0, xr0, yb0);
}

void vrtitle_800D0850(Work *work)
{
    POLY_FT4 *p = work->polys_lr;
    int counter = work->field_4938;
    int rgb;

    if (counter < 31)
    {
        return;
    }

    if (counter < 47)
    {
        work->field_654[3] = 0x100;
        rgb = (counter - 30) * 255 / 16;
        p[3].r0 = rgb;
        p[3].g0 = rgb;
        p[3].b0 = rgb;
        return;
    }
    if (counter < 75)
    {
        work->field_654[2] = 0;
        work->field_4934 = 0;
        work->field_688[2] = (GV_ACT *)0x200;
        work->field_688[3] = (GV_ACT *)0x200;
        work->field_688[4] = (GV_ACT *)0x200;
        work->field_688[25] = NULL;
        work->field_688[22] = NULL;
        return;
    }
    if (counter < 91)
    {
        rgb = 0xFF - (counter - 74) * 255 / 16;
        p[3].r0 = rgb;
        p[3].g0 = rgb;
        p[3].b0 = rgb;
        return;
    }

    work->f28 = 3;
    work->f2C = 0;
    work->field_4938 = 0;
    vrtitle_800D0530(work, -0x90, 0x5A, 0x70, 0xC, 0xFF, 0);
}
