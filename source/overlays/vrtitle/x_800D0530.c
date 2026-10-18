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

typedef struct _Work
{
    GV_ACT   actor;
    int      f20;
    GV_PAD  *pad;
    int      f28;
    int      f2C;
    DG_PRIM *prim1, *prim2, *prim3;
    POLY_FT4 polys_lr[2];
    char     padding2[0x50];
    POLY_FT4 polys[9];
    POLY_FT4 polys2[26];
    int      field_654[4];
    GV_ACT  *field_664[9];
    GV_ACT  *field_688[26];
    char     padding3[0x10];
    MenuWork field_700;
    void    *field_920;
    u_long  *field_924_mOrderingTable;
    int      field_928;
    void    *field_92C[2];
    char     padding5[0x4000];
    int      field_4934;
    int      field_4938;
    char     padding6[0x2C];
    int      field_4968;
    int      field_496C;
    int      field_4970;
    char     padding6b[0x44];
    int      field_49B8;
    int      field_49BC;
    char     padding6c[0x8];
    int      field_49C8;
    MEMCARD  *field_49CC;
    int      field_49D0;
    char     padding6d[0xC];
    int      f49E0;
    char    *f49E4;
} Work;

extern char                       *MGS_MemoryCardName; /* in main.c */

// Copy of menu_radio_do_file_mode_helper2_helper_8004A4C4

// Copy of menu_radio_do_file_mode_helper4_helper_8004A54C

// duplicate of sub_8004A648

// duplicate of menu_radio_do_file_mode_helper3_helper_8004A790

// duplicate of init_file_mode_helper2_8004A800
// but with GV_AllocMemory(GV_NORMAL_MEMORY, ...)
// instead of GV_AllocMemory(0, ...)

// duplicate of init_radio_message_board_80040F74
// but with GV_AllocMemory(GV_NORMAL_MEMORY, ...)
// instead of GV_AllocMemory(0, ...)
// and with one font_set_color missing

// duplicate of drawCaption_8004AE3C

// duplicate of sub_8004AEA8

// duplicate of show_message_8004AFE4

// See also updateCurrentEntry_8004B9C4() in datasave.c

// duplicate of menu_radio_do_file_mode_helper12_8004BA80

// duplicate of menu_radio_do_file_mode_helper14_8004BE98

// duplicate of menu_radio_do_file_mode_helper15_8004C04C, but with one missing line

// duplicate of menu_radio_do_file_mode_helper16_8004C164

typedef struct CaptionInfo
{
    int     x;
    u_short y;
    short   field_6;
    int     field_8;
    int     color;
} CaptionInfo;

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
