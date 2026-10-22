// vrtitle: VR revision copy of onoda/open/open.c
// (title_open_800D4174, title_open_800D41E4), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libcd.h>

#include "mts/mts.h"
#include "sound/sd_cli.h"

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"
#include "font/font.h"
#include "game/game.h"
#include "menu/menuman.h"

#include "onoda/open/open.h"

typedef struct _Desc
{
    int     f0;
    DVECTOR f4;
    int     color;
} Desc;

extern char *MGS_MemoryCardName; /* in main.c */

static inline void title_open_helper_800D41E4(POLY_FT4 *poly, DG_TEX *tex, int uo, int vo)
{
    int u0, u1;
    int v0, v1;

    u0 = tex->off_x;
    u1 = u0 + tex->w + uo;
    v0 = tex->off_y;
    v1 = v0 + tex->h + vo;
    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}

void vrtitle_800D5F48(Work *work, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe)
{
    setPolyFT4(poly);
    setRGB0(poly, 128, 128, 128);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);
}

void vrtitle_800D5FB8(Work *work, int name, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe, int type)
{
    DG_TEX *tex;

    vrtitle_800D5F48(work, poly, x0, y0, x1, y1, abe);

    tex = DG_GetTexture(name);
    if (type == 0)
    {
        title_open_helper_800D41E4(poly, tex, 1, 1);
    }
    else if (type == 1)
    {
        title_open_helper_800D41E4(poly, tex, 1, 0);
    }
    else if (type == 2)
    {
        title_open_helper_800D41E4(poly, tex, 0, 1);
    }
    else if (type == 3)
    {
        title_open_helper_800D41E4(poly, tex, 0, 0);
    }
}
