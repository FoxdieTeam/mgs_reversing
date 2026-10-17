#include "vrmenu.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "menu/menuman.h"

/*---------------------------------------------------------------------------*/
// Menu frame and menu item helpers shared by the VR clear screen (vrclear.c)
// and the VR pause menu (pausmenu.c). The frame is drawn like the codec face
// frame of menu/radiofacedraw.c.

#define FRAME_SIZE      9   // size of the frame corners/edges

STATIC RECT vrmenu_frame_rect = {1008, 432, 5, 20};

/*---------------------------------------------------------------------------*/

void VrMenu_InitFrame(POLY_FT4 polys[2][VR_MENU_FRAME_POLYS], TILE tiles[2], int clut)
{
    int i, j;

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < VR_MENU_FRAME_POLYS; j++)
        {
            LSTORE(0x80ffffff, &polys[i][j].r0);
            setPolyFT4(&polys[i][j]);
            setSemiTrans(&polys[i][j], 1);
            polys[i][j].tpage = getTPage(0, 1, 960, 256);
            polys[i][j].clut = clut;
        }

        setRGB0(&tiles[i], 82, 164, 114);
        setTile(&tiles[i]);
    }
}

int VrMenu_LoadFrameTexture(void)
{
    PANEL_TEXTURE tex;
    RECT          rect;

    menu_init_rpk_item_8003DDCC(&tex, 43, 42);
    LoadImage(&vrmenu_frame_rect, tex.field_0_pixels);

    rect = vrmenu_frame_rect;
    rect.w = 16;
    rect.h = 1;
    rect.y += vrmenu_frame_rect.h;

    LoadImage(&rect, tex.field_4_word_ptr_pixels);
    return (rect.y << 6) | (rect.x >> 4 & 0x3f);
}

static void DrawFrame(POLY_FT4 *frame, TILE *tile, int x, int y, int w, int h)
{
    POLY_FT4 *polys;
    int       xn, yn;
    int       xend, yend;
    int       size;
    int       i;
    POLY_FT4 *pPoly;
    int       px, py;
    POLY_FT4 *pPoly2;
    int       x2, y2;

    setXY0(tile, x, y);
    setWH(tile, w, h);
    addPrim(DG_ChanlOTag(1), tile);

    x += 3;
    y += 3;
    w -= 7;
    h -= 7;

    // FIXME: copying the parameter here keeps it in a0 until the frame is drawn
    // (the temporaries of the tile get a2/a3 like in the original)
    polys = frame;
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
static void MoveRect(RECT *out, RECT *rect, RECT *target)
{
    out->x = (rect->x + target->x) / 2 + ((target->x - rect->x) == 1);
    out->y = (rect->y + target->y) / 2 + ((target->y - rect->y) == 1);
    out->w = (rect->w + target->w) / 2 + ((target->w - rect->w) == 1);
    out->h = (rect->h + target->h) / 2 + ((target->h - rect->h) == 1);
}

void VrMenu_UpdateFrame(RECT *rect, RECT *target, POLY_FT4 *polys, TILE *tile)
{
    MoveRect(rect, rect, target);
    DrawFrame(polys, tile, rect->x, rect->y, rect->w, rect->h);
}

/*---------------------------------------------------------------------------*/

static void SetItemRect(VR_MENU_ITEM *item, RECT *rect)
{
    setXY4(&item->polys[GV_Clock],
           rect->x, rect->y,
           rect->x + rect->w - 1, rect->y,
           rect->x, rect->y + rect->h - 1,
           rect->x + rect->w - 1, rect->y + rect->h - 1);
}

void VrMenu_ExecItem(VR_MENU_ITEM *item)
{
    if (item->proc != 0)
    {
        GCL_ExecProc(item->proc, NULL);
    }
}

void VrMenu_DrawItem(VR_MENU_ITEM *item)
{
    RECT rect;

    switch (item->state)
    {
    case VR_MENU_ITEM_STATE_OPEN:
        SetItemRect(item, &item->rect);
        break;

    case VR_MENU_ITEM_STATE_GROW_W:
        rect.w = (item->rect.w * item->step) / 5;
        rect.h = 1;
        rect.x = item->rect.x + (item->rect.w - rect.w) / 2;
        rect.y = item->rect.y + item->rect.h / 2;

        if (++item->step == 5)
        {
            item->state = VR_MENU_ITEM_STATE_GROW_H;
            item->step = 0;
        }

        SetItemRect(item, &rect);
        break;

    case VR_MENU_ITEM_STATE_GROW_H:
        rect.w = item->rect.w;
        rect.h = (item->rect.h * item->step) / 4;
        rect.x = item->rect.x;
        rect.y = item->rect.y + (item->rect.h - rect.h) / 2;

        if (++item->step == 5)
        {
            item->state = VR_MENU_ITEM_STATE_OPEN;
            item->step = 0;
        }

        SetItemRect(item, &rect);
        break;

    case VR_MENU_ITEM_STATE_SHRINK_H:
        rect.w = item->rect.w;
        rect.h = (item->rect.h * (4 - item->step)) / 4;
        rect.x = item->rect.x;
        rect.y = item->rect.y + (item->rect.h - rect.h) / 2;

        if (++item->step == 5)
        {
            item->state = VR_MENU_ITEM_STATE_SHRINK_W;
            item->step = 0;
        }

        SetItemRect(item, &rect);
        break;

    case VR_MENU_ITEM_STATE_SHRINK_W:
        rect.w = (item->rect.w * (4 - item->step)) / 4;
        rect.h = 1;
        rect.x = item->rect.x + (item->rect.w - rect.w) / 2;
        rect.y = item->rect.y + item->rect.h / 2;

        if (++item->step == 5)
        {
            item->state = VR_MENU_ITEM_STATE_CLOSED;
        }

        SetItemRect(item, &rect);
        break;

    case VR_MENU_ITEM_STATE_CLOSED:
        return;

    default:
        SetItemRect(item, &rect);
        break;
    }

    addPrim(DG_ChanlOTag(1), &item->polys[GV_Clock]);
}

// FIXME: the temporaries (separate x/w/y/h loads, v1/u1 only for the second poly) steer
// scheduling/regalloc to the original bytes; the original source form is unknown.
int VrMenu_InitItem(VR_MENU_ITEM *item, int proc, int state)
{
    unsigned int x, w, y, h;
    unsigned int x2, w2, y2, h2, u1, v1;

    item->state = state;
    item->step = 0;
    item->tex = DG_GetTexture(item->tex_id);

    setlen(&item->polys[0], 9);
    setcode(&item->polys[0], 0x2c);
    setlen(&item->polys[1], 9);
    setcode(&item->polys[1], 0x2c);
    setRGB0(&item->polys[0], 74, 118, 100);
    setRGB0(&item->polys[1], 74, 118, 100);

    x = item->tex->off_x;
    w = item->tex->w;
    y = item->tex->off_y;
    h = item->tex->h;
    setUV4(&item->polys[0], x, y, x + w, y, x, y + h, x + w, y + h);
    item->polys[0].tpage = item->tex->tpage;
    item->polys[0].clut = item->tex->clut;

    x2 = item->tex->off_x;
    w2 = item->tex->w;
    y2 = item->tex->off_y;
    h2 = item->tex->h;
    u1 = x2 + w2;
    v1 = y2 + h2;
    setUV4(&item->polys[1], x2, y2, u1, y2, x2, v1, u1, v1);
    item->polys[1].tpage = item->tex->tpage;
    item->polys[1].clut = item->tex->clut;
    setSemiTrans(&item->polys[0], 1);
    setSemiTrans(&item->polys[1], 1);

    if (item->proc > 0 && proc != 0)
    {
        item->proc = proc;
    }

    return item->proc > 0;
}
