// vrsave: VR revision copy of koba/vr/vrmenu.c
// (VrMenu_InitFrame, VrMenu_LoadFrameTexture, DrawFrame, MoveRect),
// adapted to work on the VR_SAVEMNGR_WORK.
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "menu/menuman.h"
#include "overlays/vrsave/vrsave.h"

#define FRAME_SIZE      9   // size of the frame corners/edges

extern RECT             vrsave_dword_800C1B30;

void vrsave_800CA66C(VR_SAVEMNGR_WORK *work, int clut)
{
    int i, j;

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < VR_SAVEMNGR_FRAME_POLYS; j++)
        {
            LSTORE(0x80ffffff, &work->polys[i][j].r0);
            setPolyFT4(&work->polys[i][j]);
            setSemiTrans(&work->polys[i][j], 1);
            work->polys[i][j].tpage = getTPage(0, 1, 960, 256);
            work->polys[i][j].clut = clut;
        }

        setRGB0(&work->tiles[i], 82, 164, 114);
        setTile(&work->tiles[i]);
    }
}

int vrsave_800CA738(void)
{
    PANEL_TEXTURE tex;
    RECT          rect;

    menu_init_rpk_item_8003DDCC(&tex, 43, 42);
    LoadImage(&vrsave_dword_800C1B30, tex.field_0_pixels);

    rect = vrsave_dword_800C1B30;
    rect.w = 16;
    rect.h = 1;
    rect.y += vrsave_dword_800C1B30.h;

    LoadImage(&rect, tex.field_4_word_ptr_pixels);
    return (rect.y << 6) | (rect.x >> 4 & 0x3f);
}

void vrsave_800CA7E8(VR_SAVEMNGR_WORK *work, int x, int y, int w, int h)
{
    POLY_FT4 *polys;
    TILE     *tile;
    int       xn, yn;
    int       xend, yend;
    int       size;
    int       i;
    POLY_FT4 *pPoly;
    int       px, py;
    POLY_FT4 *pPoly2;
    int       x2, y2;

    tile = &work->tiles[GV_Clock];
    setXY0(tile, x, y);
    setWH(tile, w, h);
    addPrim(DG_ChanlOTag(1), tile);

    x += 3;
    y += 3;
    w -= 7;
    h -= 7;

    polys = work->polys[GV_Clock];
    if (w < 0)
    {
        return;
    }

    xn = x;
    yn = y;

    xend = xn + w;
    yend = yn + h;

    size = FRAME_SIZE;

    for (i = 0; i < 8; i++)
    {
        pPoly = &polys[i];

        if (i < 4)
        {
            px = (i % 2) * 10 - 64;
            py = (i / 2) * 10 - 80;
            setUVWH(pPoly, px, py, 9, 9);
        }

        addPrim(DG_ChanlOTag(1), pPoly);
    }

    polys[0].x0 = polys[2].x0 = xn - size;
    polys[1].x0 = polys[3].x0 = xend;
    polys[0].y0 = polys[1].y0 = yn - size;
    polys[2].y0 = polys[3].y0 = yend;

    for (i = 0; i < 4; i++)
    {
        pPoly2 = &polys[i];

        x2 = pPoly2->x0;
        y2 = pPoly2->y0;

        pPoly2->x1 = x2 + size;
        pPoly2->y1 = y2;
        pPoly2->x2 = x2;
        pPoly2->y2 = y2 + size;
        pPoly2->x3 = x2 + size;
        pPoly2->y3 = y2 + size;
    }

    setUVWH(&polys[4], 201, 176, 1, 9);
    setXYWH(&polys[4], xn, yn - size, w, 9);

    setUVWH(&polys[5], 201, 186, 1, 9);
    setXYWH(&polys[5], xn, yend, w, 9);

    setUVWH(&polys[6], 192, 185, 9, 1);
    setXYWH(&polys[6], xn - size, yn, 9, h);

    setUVWH(&polys[7], 202, 185, 9, 1);
    setXYWH(&polys[7], xend, yn, 9, h);
}

// Moves each side of the rectangle half way to the target
void vrsave_800CAB38(RECT *out, RECT *rect, RECT *target)
{
    out->x = (rect->x + target->x) / 2 + ((target->x - rect->x) == 1);
    out->y = (rect->y + target->y) / 2 + ((target->y - rect->y) == 1);
    out->w = (rect->w + target->w) / 2 + ((target->w - rect->w) == 1);
    out->h = (rect->h + target->h) / 2 + ((target->h - rect->h) == 1);
}
