#include "game/game.h"
#include "libgcl/libgcl.h"
#include "font/font.h"
#include "libfs/libfs.h"
#include "mts/mts.h"

#include <stdio.h>

typedef struct _Unknown2
{
    short x, y;
    int   color;
} Unknown2;

typedef struct _Unknown
{
    SPRT  text_sprt[2];
    SPRT  text_sprt_outline[2][4];
    SPRT  text_sprt2[2];
    SPRT  text_sprt_outline2[2][4];
    SPRT  text_sprt3[2];
    SPRT  text_sprt4[2];
    /* +0x1E0 */ char *string;
    /* +0x1E4 */ short num;
    /* +0x1E6 */ short num2;
    /* +0x1E8 */ RECT  rect;
    /* +0x1F0 */ short unk1;
    /* +0x1F2 */ short unk2;
    /* +0x1F4 */ short x0;
    /* +0x1F6 */ short y0;
    /* +0x1F8 */ short cx;
    /* +0x1FA */ short cy;
    /* +0x1FC */ short unk3;
    /* +0x1FE */ short unk4;
    /* +0x200 */ short x1;
    /* +0x202 */ short y1;
} Unknown;

typedef struct _Work
{
    /* +0x0000 */ GV_ACT   actor;
    /* +0x0020 */ int      end_proc;
    /* +0x0024 */ int      field_24;
    /* +0x0028 */ GV_PAD  *pad;
    /* +0x002C */ DG_PRIM *prim1;
    /* +0x0030 */ DG_PRIM *prim2;
    /* +0x0034 */ POLY_FT4 polys1[8];
    /* +0x0174 */ POLY_FT4 polys2[9];
    /* +0x02DC */ int      attrs1[8];
    /* +0x02FC */ int      attrs2[9];
    /* +0x0320 */ int      field_320;
    /* +0x0324 */ KCB      kcb[24];
    /* +0x0744 */ char     pad_744[0x758 - 0x744];
    /* +0x0758 */ DR_TPAGE tpage[12];
    /* +0x07B8 */ Unknown  field_7B8[12];
    /* +0x1FE8 */ char     pad_1FE8[0x3818 - 0x1FE8];
    /* +0x3818 */ int      font_x;
    /* +0x381C */ int      font_y;
    /* +0x3820 */ int      clut_x;
    /* +0x3824 */ int      clut_y;
    /* +0x3828 */ int      field_3828;
    /* +0x382C */ char     pad_382C[0x3830 - 0x382C];
    /* +0x3830 */ int      field_3830;
    /* +0x3834 */ int      field_3834;
    /* +0x3838 */ char     pad_3838[0x3858 - 0x3838];
    /* +0x3858 */ MenuPrim primbuf;
    /* +0x386C */ char     field_386C[0x2000];
    /* +0x586C */ char     field_586C[0x2000];
    /* +0x786C */ int      field_786C;
    /* +0x7870 */ int      field_7870;
    /* +0x7874 */ int      field_7874;
    /* +0x7878 */ int      field_7878;
    /* +0x787C */ int      field_787C;
    /* +0x7880 */ char     pad_7880[0x7884 - 0x7880];
} Work;

typedef struct _AbstRes
{
    int id;
    int file;
    int size;
} AbstRes;

extern int abst_dword_800C3CD0;
extern signed char abst_dword_800C3D48[];
extern AbstRes abst_dword_800C3D50[];
extern const char abst_dword_800CE8B4[];
extern const char abst_dword_800CE8B8[];
extern const char abst_dword_800CE8F4[];
extern const char abst_dword_800CE910[];
extern const char abst_dword_800CE928[];
extern const char abst_dword_800CE940[];
extern const char abst_dword_800CE94C[];
extern const char abst_dword_800CE958[];
extern const char abst_dword_800CE964[];
extern const char abst_dword_800CE970[];
extern const char abst_dword_800CE97C[];
extern const char abst_dword_800CE988[];
extern const char abst_dword_800CE990[];
extern const char abst_dword_800CE998[];
extern const char abst_dword_800CE9A0[];
extern const char abst_dword_800CE9A8[];
extern const char abst_dword_800CE9B0[];
extern const char abst_dword_800CE9B8[];
extern const char abst_dword_800CE9C0[];
extern const char abst_dword_800CE9C8[];

void abst_800CA568(Work *work, int index)
{
    RECT  rect;
    KCB  *kcb;
    void *buf;

    kcb = &work->kcb[index];

    if (work->font_y + 21 >= 512)
    {
        work->font_y = 256;
        work->font_x = 704;
        work->clut_y = 276;
        work->clut_x = work->font_x;
    }

    rect.x = work->font_x;
    rect.y = work->font_y;
    rect.w = 128;
    rect.h = 21;

    work->field_7B8[index].x0 = work->font_x;
    work->field_7B8[index].y0 = work->font_y;

    work->field_7B8[index].x1 = work->font_x + 64;
    work->field_7B8[index].y1 = work->font_y;
    work->font_y += 21;

    font_init_kcb(kcb, &rect, work->clut_x, work->clut_y);

    work->field_7B8[index].cx = work->clut_x;
    work->field_7B8[index].cy = work->clut_y;
    work->clut_y += 21;

    font_set_kcb(kcb, -1, -1, 0, 6, 2, 0);

    buf = GV_AllocMemory(GV_NORMAL_MEMORY, font_get_buffer_size(kcb));
    font_set_buffer(kcb, buf);

    font_set_color(kcb, 0, ((Unknown2 *)&abst_dword_800C3CD0)[index].color, 0);
    font_clut_update(kcb);
}

void abst_800CA6FC(Work *work, int index)
{
    KCB *kcb;

    if (work->field_7B8[index].string)
    {
        kcb = &work->kcb[index];
        font_print_string(kcb, work->field_7B8[index].string);
        font_update(kcb);
        font_clut_update(kcb);

        work->field_7B8[index].unk1 = 256;
        work->field_7B8[index].unk2 = kcb->max_height - 1;

        work->field_7B8[index].rect.x = ((Unknown2 *)&abst_dword_800C3CD0)[index].x;
        work->field_7B8[index].rect.y = ((Unknown2 *)&abst_dword_800C3CD0)[index].y;
        work->field_7B8[index].unk3 = 128;

        work->field_7B8[index].unk4 = kcb->max_height - 1;

        work->field_7B8[index].rect.w = ((Unknown2 *)&abst_dword_800C3CD0)[index].x + 256;

        work->field_7B8[index].rect.h = ((Unknown2 *)&abst_dword_800C3CD0)[index].y;
        work->field_7B8[index].string = NULL;
        work->field_7B8[index].num = 1;
    }
}

void abst_800CA7F0(Work *work, u_long *ot, int arg2)
{
    int       i, j;
    SPRT     *sprt;
    DR_TPAGE *tpage;
    int       index;
    SPRT     *sprt1;
    SPRT     *sprt2;
    int       pass;

    index = 0;
    for (pass = 0; pass < 2; pass++)
    {
        for (i = 0; i < 12; i++)
        {
            if (work->field_7B8[index].num == 1)
            {
                sprt = &work->field_7B8[index].text_sprt[GV_Clock];
                setSprt(sprt);
                setRGB0(sprt, 128, 128, 128);
                setSemiTrans(sprt, 1);
                LCOPY(&work->field_7B8[index].rect.x, &sprt->x0);
                LCOPY(&work->field_7B8[index].unk1, &sprt->w);
                setUV0(sprt, 0, work->field_7B8[index].y0);
                setClut(sprt, work->field_7B8[index].cx, work->field_7B8[index].cy);
                sprt->x0 += work->field_787C;
                addPrim(ot, sprt);
                index++;
            }
        }

        tpage = &work->tpage[pass * 4];
        setDrawTPage(tpage, 1, 0, getTPage(0, 1, 0x240 + pass * 0x80, 256));
        addPrim(ot, tpage);
    }

    index = 0;
    for (pass = 0; pass < 2; pass++)
    {
        for (i = 0; i < 12; i++)
        {
            if (work->field_7B8[index].num == 1)
            {
                sprt = &work->field_7B8[index].text_sprt2[GV_Clock];
                setSprt(sprt);
                setRGB0(sprt, 128, 128, 128);
                setSemiTrans(sprt, 1);
                LCOPY(&work->field_7B8[index].rect.w, &sprt->x0);
                LCOPY(&work->field_7B8[index].unk3, &sprt->w);
                setUV0(sprt, 0, work->field_7B8[index].y1);
                setClut(sprt, work->field_7B8[index].cx, work->field_7B8[index].cy);
                sprt->x0 += work->field_787C;
                addPrim(ot, sprt);
                index++;
            }
        }

        tpage = &work->tpage[pass * 4 + 1];
        setDrawTPage(tpage, 1, 0, getTPage(0, 1, 0x280 + pass * 0x80, 256));
        addPrim(ot, tpage);
    }

    index = 0;
    for (pass = 0; pass < 2; pass++)
    {
        for (i = 0; i < 12; i++)
        {
            if (work->field_7B8[index].num == 1)
            {
                sprt = &work->field_7B8[index].text_sprt3[GV_Clock];
                setSprt(sprt);
                setRGB0(sprt, 128, 128, 128);
                setSemiTrans(sprt, 1);
                LCOPY(&work->field_7B8[index].rect.x, &sprt->x0);
                LCOPY(&work->field_7B8[index].unk1, &sprt->w);
                setUV0(sprt, 0, work->field_7B8[index].y0);
                setClut(sprt, work->field_7B8[index].cx, work->field_7B8[index].cy);
                sprt->x0 += work->field_787C;
                addPrim(ot, sprt);
                index++;
            }
        }

        tpage = &work->tpage[pass * 2 + 8];
        setDrawTPage(tpage, 1, 0, getTPage(0, 2, 0x240 + pass * 0x80, 256));
        addPrim(ot, tpage);
    }

    index = 0;
    for (pass = 0; pass < 2; pass++)
    {
        for (i = 0; i < 12; i++)
        {
            if (work->field_7B8[index].num == 1)
            {
                sprt = &work->field_7B8[index].text_sprt4[GV_Clock];
                setSprt(sprt);
                setRGB0(sprt, 128, 128, 128);
                setSemiTrans(sprt, 1);
                LCOPY(&work->field_7B8[index].rect.w, &sprt->x0);
                LCOPY(&work->field_7B8[index].unk3, &sprt->w);
                setUV0(sprt, 0, work->field_7B8[index].y1);
                setClut(sprt, work->field_7B8[index].cx, work->field_7B8[index].cy);
                sprt->x0 += work->field_787C;
                addPrim(ot, sprt);
                index++;
            }
        }

        tpage = &work->tpage[pass * 2 + 9];
        setDrawTPage(tpage, 1, 0, getTPage(0, 2, 0x280 + pass * 0x80, 256));
        addPrim(ot, tpage);
    }

    if (arg2 == 1)
    {
        index = 0;
        for (pass = 0; pass < 2; pass++)
        {
            for (i = 0; i < 12; i++)
            {
                if (work->field_7B8[index].num == 1)
                {
                    sprt2 = work->field_7B8[index].text_sprt_outline[GV_Clock];
                    sprt1 = &work->field_7B8[index].text_sprt[GV_Clock];

                    for (j = 0; j < 8; j += 2)
                    {
                        *sprt2 = *sprt1;
                        setSprt(sprt2);
                        setRGB0(sprt2, 128, 128, 128);
                        setSemiTrans(sprt2, 1);
                        sprt2->x0 += abst_dword_800C3D48[j];
                        sprt2->y0 += abst_dword_800C3D48[j + 1];
                        addPrim(ot, sprt2);
                        sprt2++;
                    }

                    index++;
                }
            }

            tpage = &work->tpage[pass * 4 + 2];
            setDrawTPage(tpage, 1, 0, getTPage(0, 2, 0x240 + pass * 0x80, 256));
            addPrim(ot, tpage);
        }

        index = 0;
        for (pass = 0; pass < 2; pass++)
        {
            for (i = 0; i < 12; i++)
            {
                if (work->field_7B8[index].num == 1)
                {
                    sprt2 = work->field_7B8[index].text_sprt_outline2[GV_Clock];
                    sprt1 = &work->field_7B8[index].text_sprt2[GV_Clock];

                    for (j = 0; j < 8; j += 2)
                    {
                        *sprt2 = *sprt1;
                        setSprt(sprt2);
                        setRGB0(sprt2, 128, 128, 128);
                        setSemiTrans(sprt2, 1);
                        sprt2->x0 += abst_dword_800C3D48[j];
                        sprt2->y0 += abst_dword_800C3D48[j + 1];
                        addPrim(ot, sprt2);
                        sprt2++;
                    }

                    index++;
                }
            }

            tpage = &work->tpage[pass * 4 + 3];
            setDrawTPage(tpage, 1, 0, getTPage(0, 2, 0x280 + pass * 0x80, 256));
            addPrim(ot, tpage);
        }
    }
}

void abst_800CB1E0(Work *work, int index, int col)
{
    font_set_color(&work->kcb[index], 0, col, 0);
    font_clut_update(&work->kcb[index]);
}

void *abst_800CB230(KCB *kcb)
{
    return kcb->cbuffer;
}

void abst_800CB23C(Work *work)
{
    POLY_FT4 *src;
    POLY_FT4 *dst;
    int       i;

    src = work->polys1;
    dst = (POLY_FT4 *)work->prim1->packs[GV_Clock];
    for (i = 0; i < 8; i++)
    {
        *dst = *src;
        *(u_short *)dst = work->attrs1[i];
        src++;
        dst++;
    }

    src = work->polys2;
    dst = (POLY_FT4 *)work->prim2->packs[GV_Clock];
    for (i = 0; i < 9; i++)
    {
        *dst = *src;
        *(u_short *)dst = work->attrs2[i];
        src++;
        dst++;
    }
}

void abst_800CB360(Work *work, int x, int y, int w, int h, int color, int sel)
{
    POLY_FT4 *poly;
    int       i;

    poly = work->polys2;
    for (i = 0; i < 9; i++)
    {
        work->attrs2[i] = 0x200;
        setRGB0(&poly[i], color, color, color);
    }

    if (sel == 0)
    {
        int xl = x - 8;
        int yl = y - 8;
        int xr = x + w;
        int xr8 = xr + 8;
        int yb = y + h;
        int yb8 = yb + 8;

        setXY4(&poly[0], xl, yl, x, yl, xl, y, x, y);
        setXY4(&poly[1], xr, yl, xr8, yl, xr, y, xr8, y);
        setXY4(&poly[2], xl, yb, x, yb, xl, yb8, x, yb8);
        setXY4(&poly[3], xr, yb, xr8, yb, xr, yb8, xr8, yb8);
        setXY4(&poly[4], x, yl, xr, yl, x, y, xr, y);
        setXY4(&poly[5], x, yb, xr, yb, x, yb8, xr, yb8);
        setXY4(&poly[6], xl, y, x, y, xl, yb, x, yb);
        setXY4(&poly[7], xr, y, xr8, y, xr, yb, xr8, yb);
        setXY4(&poly[8], x, y, xr, y, x, yb, xr, yb);
    }
    else if (sel == 1)
    {
        int xl = x - 6;
        int yl = y - 6;
        int xi = x + 2;
        int yi = y + 2;
        int xr = x + w;
        int xrl = xr - 2;
        int xrr = xr + 6;
        int yb = y + h;
        int ybl = yb - 2;
        int ybr = yb + 6;

        setXY4(&poly[0], xl, yl, xi, yl, xl, yi, xi, yi);
        setXY4(&poly[1], xrl, yl, xrr, yl, xrl, yi, xrr, yi);
        setXY4(&poly[2], xl, ybl, xi, ybl, xl, ybr, xi, ybr);
        setXY4(&poly[3], xrl, ybl, xrr, ybl, xrl, ybr, xrr, ybr);
        setXY4(&poly[4], xi, yl, xrl, yl, xi, yi, xrl, yi);
        setXY4(&poly[5], xi, ybl, xrl, ybl, xi, ybr, xrl, ybr);
        setXY4(&poly[6], xl, yi, xi, yi, xl, ybl, xi, ybl);
        setXY4(&poly[7], xrl, yi, xrr, yi, xrl, ybl, xrr, ybl);
        setXY4(&poly[8], xi, yi, xrl, yi, xi, ybl, xrl, ybl);
    }
}
void abst_800CB644(MenuPrim *prim, int x, int y, int w, int h)
{
    TILE *pTile;

    _NEW_PRIM(pTile, prim);

    LSTORE(0x72A452, &pTile->r0);
    setTile(pTile);
    pTile->x0 = x;
    pTile->y0 = y;
    pTile->w = w;
    pTile->h = h;
    setSemiTrans(pTile, 0);
    addPrim(prim->ot, pTile);

    radio_draw_face_frame(prim, x, y, w, h);
    radio_draw_face_frame(prim, x, y, w, h);
}

void abst_800CB73C(Work *work)
{
    int r, g, b;

    if (work->field_3830 == 3)
    {
        int n = work->field_3828;
        r = 86 - (n * 86) / 8;
        g = 137 - (n * 137) / 8;
        b = 116 - (n * 116) / 8;
    }
    else
    {
        r = 86;
        g = 137;
        b = 116;
    }

    MENU_Locate(145, 202, 16);
    MENU_Color(r, g, b);
    MENU_Printf(abst_dword_800CE8B4, work->field_7878);

    MENU_Locate(156, 202, 16);
    MENU_Color(r, g, b);
    MENU_Printf(abst_dword_800CE8B8);

    MENU_Locate(167, 202, 16);
    MENU_Color(r, g, b);
    MENU_Printf(abst_dword_800CE8B4, 2);
}

/* ---- group1 consts, placed BEFORE abst_800CB8A4 (0x800CE8B4..0x800CE8D8) ---- */
const char abst_dword_800CE8B4[] = "%d";
const char abst_dword_800CE8B8[] = "/";
const char abst_dword_800CE8BC[] = "READ MISSION LOG?";
const char abst_dword_800CE8D0[] = "YES";
const char abst_dword_800CE8D4[] = "NO";
const char abst_dword_800CE8D8[] = {0x0, 0x0, 0x0, 0x0}; /* pads the jump table to 0x800CE8DC */

void abst_800CB8A4(Work *work)
{
    int       press;
    int       i;
    int       r, g, b;
    POLY_FT4 *poly;
    int       shade;
    int       col;
    int       base;

    press = work->pad->press;

    work->primbuf.next = work->primbuf.buf[GV_Clock];
    work->primbuf.ot = DG_Chanl(1)->ot[GV_Clock];

    switch (work->field_3830)
    {
    case 0:
        if (work->field_3828 < 5)
        {
            MENU_Locate(90, 90, 0x10);
            MENU_Color(192, 192, 192);
            MENU_Printf(abst_dword_800CE8BC);
            abst_800CB644(&work->primbuf, 92, 85, 130, 15);
        }
        else if (work->field_3828 < 10)
        {
            MENU_Locate(90, 90 - (work->field_3828 - 4) * 8, 0x10);
            MENU_Color(192, 192, 192);
            MENU_Printf(abst_dword_800CE8BC);
            abst_800CB644(&work->primbuf, 92, 85, 130, 15);
        }
        else if (work->field_3828 == 10)
        {
            MENU_Locate(90, 50, 0x10);
            MENU_Color(86, 137, 116);
            MENU_Printf(abst_dword_800CE8BC);
            MENU_Locate(100, 105, 0x10);
            MENU_Color(192, 192, 192);
            MENU_Printf(abst_dword_800CE8D0);
            MENU_Locate(200, 105, 0x10);
            MENU_Color(46, 72, 61);
            MENU_Printf(abst_dword_800CE8D4);
            abst_800CB644(&work->primbuf, 92, 85, 130, 15);
        }
        else if (work->field_3828 < 14)
        {
            MENU_Locate(90, 50, 0x10);
            MENU_Color(86, 137, 116);
            MENU_Printf(abst_dword_800CE8BC);
            MENU_Locate(100, 105, 0x10);
            MENU_Color(192, 192, 192);
            MENU_Printf(abst_dword_800CE8D0);
            MENU_Locate(200, 105, 0x10);
            MENU_Color(46, 72, 61);
            MENU_Printf(abst_dword_800CE8D4);
            abst_800CB644(&work->primbuf, 92, (work->field_3828 - 10) * 5 + 85, 130 - (work->field_3828 - 10) * 30, 15);
        }
        else
        {
            MENU_Locate(90, 50, 0x10);
            MENU_Color(86, 137, 116);
            MENU_Printf(abst_dword_800CE8BC);
            MENU_Locate(100, 105, 0x10);
            if (work->field_3834 == 0)
            {
                MENU_Color(192, 192, 192);
            }
            else
            {
                MENU_Color(46, 72, 61);
            }
            MENU_Printf(abst_dword_800CE8D0);
            MENU_Locate(200, 105, 0x10);
            if (work->field_3834 == 1)
            {
                MENU_Color(192, 192, 192);
            }
            else
            {
                MENU_Color(46, 72, 61);
            }
            MENU_Printf(abst_dword_800CE8D4);
            if (work->field_3834 == 0)
            {
                abst_800CB644(&work->primbuf, 92, 100, 40, 15);
            }
            else
            {
                abst_800CB644(&work->primbuf, 188, 100, 40, 15);
            }

            if (press & (PAD_START | PAD_CIRCLE))
            {
                if (work->field_3834 == 0)
                {
                    GM_SeSet2(0, 63, SE_MENU_SELECT);
                    work->field_3830 = 1;
                    for (i = 0; i < 8; i++)
                    {
                        work->attrs1[i] = 0x100;
                    }
                    work->attrs1[4] = 0;
                    work->field_3828 = 0;
                    r = 86;
                    g = 137;
                    b = 116;
                    poly = work->polys1;
                    setRGB0(&poly[2], r, g, b);
                    setRGB0(&poly[3], r, g, b);
                    setRGB0(&poly[4], r, g, b);
                    setRGB0(&poly[5], r, g, b);
                    for (i = 0; i < 1; i++)
                    {
                        abst_800CB1E0(work, i, 0);
                    }
                    for (i = 0; i < 9; i++)
                    {
                        work->attrs2[i] = 0x200;
                    }
                    abst_800CB360(work, 30, 86, 16, 14, 255, 1);
                    poly = work->polys2;
                    for (i = 0; i < 9; i++)
                    {
                        setRGB0(poly, 0, 0, 0);
                        poly++;
                    }
                }
                else
                {
                    GM_SeSet2(0, 63, SE_MENU_EXIT);
                    GCL_ExecProc(work->end_proc, NULL);
                    GV_DestroyActor(work);
                }
            }
            else if (press & PAD_CROSS)
            {
                GM_SeSet2(0, 63, SE_MENU_EXIT);
                GCL_ExecProc(work->end_proc, NULL);
                GV_DestroyActor(work);
            }
            else if (press & PAD_UDLR)
            {
                GM_SeSet2(0, 63, SE_MENU_CURSOR);
                if (work->field_3834 == 0)
                {
                    work->field_3834 = 1;
                }
                else
                {
                    work->field_3834 = 0;
                }
            }

            work->field_786C = 1;
        }
        work->field_3828++;
        break;

    case 1:
        if (work->field_3828 < 9)
        {
            poly = work->polys1;
            r = (work->field_3828 * 86) / 64;
            g = (work->field_3828 * 137) / 64;
            b = (work->field_3828 * 116) / 64;
            for (i = 0; i < 2; i++)
            {
                setRGB0(poly, r, g, b);
                poly++;
            }
            col = 0;
            for (i = 1; i < 8; i++)
            {
                abst_800CB1E0(work, i, col);
            }
        }
        else if (work->field_3828 < 0x41)
        {
            poly = work->polys1;
            r = (work->field_3828 * 86) / 64;
            g = (work->field_3828 * 137) / 64;
            b = (work->field_3828 * 116) / 64;
            for (i = 0; i < 2; i++)
            {
                setRGB0(poly, r, g, b);
                poly++;
            }
            col = 0;
            for (i = 1; i < 8; i++)
            {
                abst_800CB1E0(work, i, col);
            }
        }
        else if (work->field_3828 < 0x51)
        {
            poly = work->polys1;
            r = 86;
            g = 137;
            b = 116;
            for (i = 0; i < 8; i++)
            {
                setRGB0(poly, r, g, b);
                poly++;
            }
            col = 0;
            for (i = 1; i < 8; i++)
            {
                abst_800CB1E0(work, i, col);
            }
        }
        else if (work->field_3828 < 0x89)
        {
            poly = work->polys1;
            r = 86;
            g = 137;
            b = 116;
            for (i = 0; i < 8; i++)
            {
                setRGB0(poly, r, g, b);
                poly++;
            }
            shade = ((work->field_3828 - 0x50) * 25) / 64;
            col = (shade << 10) | (shade << 5) | shade;
            for (i = 1; i < 8; i++)
            {
                abst_800CB1E0(work, i, col);
            }
            work->field_3828++;
            if (work->field_3828 < 0x59)
            {
                work->field_786C = 0;
            }
            else
            {
                work->field_786C = 1;
            }
            break;
        }
        else if (work->field_3828 < 0x91)
        {
            shade = ((work->field_3828 - 0x88) * 255) / 8;
            poly = work->polys2;
            for (i = 0; i < 9; i++)
            {
                setRGB0(poly, shade, shade, shade);
                poly++;
            }
            poly = work->polys1;
            r = 86;
            g = 137;
            b = 116;
            for (i = 0; i < 8; i++)
            {
                setRGB0(poly, r, g, b);
                poly++;
            }
            shade = ((work->field_3828 - 0x50) * 25) / 64;
            col = (shade << 10) | (shade << 5) | shade;
            for (i = 1; i < 8; i++)
            {
                abst_800CB1E0(work, i, col);
            }
            work->field_3828++;
            if (work->field_3828 < 0x59)
            {
                work->field_786C = 0;
            }
            else
            {
                work->field_786C = 1;
            }
            break;
        }
        else
        {
            work->field_3830 = 2;
            work->field_786C = 1;
            work->field_7874 = 2;
            abst_800CB73C(work);
            break;
        }
        work->field_3828++;
        break;

    case 2:
        switch (work->field_7874)
        {
        case 2:
            if (press & PAD_R)
            {
                work->field_7874 = 3;
                abst_800CB360(work, 66, 87, 78, 12, 255, 1);
                GM_SeSet2(0, 63, SE_MENU_CURSOR);
            }
            else if (press & PAD_L)
            {
                work->field_7874 = 0;
                abst_800CB360(work, -137, 87, 78, 12, 255, 1);
                GM_SeSet2(0, 63, SE_MENU_CURSOR);
            }
            else if (press & (PAD_CIRCLE | PAD_R1))
            {
                work->field_3830 = 4;
                work->field_7874 = 3;
                GM_SeSet2(0, 63, 0xb0);
                work->field_3828 = 0;
                abst_800CB360(work, 66, 87, 78, 12, 255, 1);
                work->attrs1[4] = 0x100;
                work->attrs1[5] = 0;
            }
            else if (press & PAD_SELECT)
            {
                base = (work->field_7878 - 1) * 7;
                if (work->field_7870 == 0)
                {
                    work->field_7870 = 1;
                    for (i = base + 1; i < base + 8; i++)
                    {
                        abst_800CB1E0(work, i, 0);
                    }
                }
                else
                {
                    work->field_7870 = 0;
                    for (i = base + 1; i < base + 8; i++)
                    {
                        abst_800CB1E0(work, i, 0x6739);
                    }
                }
            }
            else if (press & PAD_CROSS)
            {
                GM_SeSet2(0, 63, SE_MENU_EXIT);
                work->field_3830 = 3;
                work->field_7874 = 3;
                work->field_3828 = 0;
                abst_800CB360(work, 66, 87, 78, 12, 255, 1);
            }
            break;

        case 1:
            if (press & PAD_R)
            {
                work->field_7874 = 3;
                abst_800CB360(work, 66, 87, 78, 12, 255, 1);
                GM_SeSet2(0, 63, SE_MENU_CURSOR);
            }
            else if (press & PAD_L)
            {
                work->field_7874 = 0;
                abst_800CB360(work, -137, 87, 78, 12, 255, 1);
                GM_SeSet2(0, 63, SE_MENU_CURSOR);
            }
            else if (press & (PAD_CIRCLE | PAD_L1))
            {
                work->field_3830 = 5;
                work->field_7874 = 2;
                GM_SeSet2(0, 63, 0xb0);
                work->field_3828 = 0;
                abst_800CB360(work, 30, 86, 16, 14, 255, 1);
                work->attrs1[4] = 0;
                work->attrs1[5] = 0x100;
            }
            else if (press & PAD_SELECT)
            {
                base = (work->field_7878 - 1) * 7;
                if (work->field_7870 == 0)
                {
                    work->field_7870 = 1;
                    for (i = base + 1; i < base + 8; i++)
                    {
                        abst_800CB1E0(work, i, 0);
                    }
                }
                else
                {
                    work->field_7870 = 0;
                    for (i = base + 1; i < base + 8; i++)
                    {
                        abst_800CB1E0(work, i, 0x6739);
                    }
                }
            }
            else if (press & PAD_CROSS)
            {
                GM_SeSet2(0, 63, SE_MENU_EXIT);
                work->field_3830 = 3;
                work->field_7874 = 3;
                work->field_3828 = 0;
                abst_800CB360(work, 66, 87, 78, 12, 255, 1);
            }
            break;

        case 3:
            if (press & PAD_L)
            {
                if (work->field_7878 == 1)
                {
                    work->field_7874 = 2;
                    abst_800CB360(work, 30, 86, 16, 14, 255, 1);
                    GM_SeSet2(0, 63, SE_MENU_CURSOR);
                }
                else
                {
                    work->field_7874 = 1;
                    abst_800CB360(work, -46, 86, 16, 14, 255, 1);
                    GM_SeSet2(0, 63, SE_MENU_CURSOR);
                }
            }
            else if (press & PAD_L1)
            {
                if (work->field_7878 == 1)
                {
                    /* footer */
                }
                else
                {
                    work->field_3830 = 5;
                    work->field_7874 = 2;
                    GM_SeSet2(0, 63, 0xb0);
                    work->field_3828 = 0;
                    abst_800CB360(work, 30, 86, 16, 14, 255, 1);
                    work->attrs1[4] = 0;
                    work->attrs1[5] = 0x100;
                }
            }
            else if (press & PAD_R1)
            {
                if (work->field_7878 == 2)
                {
                    /* footer */
                }
                else
                {
                    work->field_3830 = 4;
                    work->field_7874 = 1;
                    GM_SeSet2(0, 63, 0xb0);
                    work->field_3828 = 0;
                    abst_800CB360(work, -46, 86, 16, 14, 255, 1);
                    work->attrs1[4] = 0x100;
                    work->attrs1[5] = 0;
                }
            }
            else if (press & PAD_SELECT)
            {
                base = (work->field_7878 - 1) * 7;
                if (work->field_7870 == 0)
                {
                    work->field_7870 = 1;
                    for (i = base + 1; i < base + 8; i++)
                    {
                        abst_800CB1E0(work, i, 0);
                    }
                }
                else
                {
                    work->field_7870 = 0;
                    for (i = base + 1; i < base + 8; i++)
                    {
                        abst_800CB1E0(work, i, 0x6739);
                    }
                }
            }
            else if (press & PAD_CIRCLE)
            {
                GM_SeSet2(0, 63, SE_MENU_SELECT);
                work->field_3830 = 3;
                work->field_3828 = 0;
            }
            else if (press & PAD_CROSS)
            {
                GM_SeSet2(0, 63, SE_MENU_EXIT);
                work->field_3830 = 3;
                work->field_3828 = 0;
            }
            break;

        case 0:
            if (press & PAD_R)
            {
                if (work->field_7878 == 1)
                {
                    work->field_7874 = 2;
                    abst_800CB360(work, 30, 86, 16, 14, 255, 1);
                    GM_SeSet2(0, 63, SE_MENU_CURSOR);
                }
                else
                {
                    work->field_7874 = 1;
                    abst_800CB360(work, -46, 86, 16, 14, 255, 1);
                    GM_SeSet2(0, 63, SE_MENU_CURSOR);
                }
            }
            else if (press & PAD_L1)
            {
                if (work->field_7878 == 1)
                {
                    /* footer */
                }
                else
                {
                    work->field_3830 = 5;
                    work->field_7874 = 2;
                    GM_SeSet2(0, 63, 0xb0);
                    work->field_3828 = 0;
                    abst_800CB360(work, 30, 86, 16, 14, 255, 1);
                    work->attrs1[4] = 0;
                    work->attrs1[5] = 0x100;
                }
            }
            else if (press & PAD_R1)
            {
                if (work->field_7878 == 2)
                {
                    /* footer */
                }
                else
                {
                    work->field_3830 = 4;
                    work->field_7874 = 1;
                    GM_SeSet2(0, 63, 0xb0);
                    work->field_3828 = 0;
                    abst_800CB360(work, -46, 86, 16, 14, 255, 1);
                    work->attrs1[4] = 0x100;
                    work->attrs1[5] = 0;
                }
            }
            else if (press & PAD_SELECT)
            {
                base = (work->field_7878 - 1) * 7;
                if (work->field_7870 == 0)
                {
                    work->field_7870 = 1;
                    for (i = base + 1; i < base + 8; i++)
                    {
                        abst_800CB1E0(work, i, 0);
                    }
                }
                else
                {
                    work->field_7870 = 0;
                    for (i = base + 1; i < base + 8; i++)
                    {
                        abst_800CB1E0(work, i, 0x6739);
                    }
                }
            }
            else if (press & PAD_CIRCLE)
            {
                GM_SeSet2(0, 63, SE_MENU_SELECT);
                work->field_3830 = 3;
                work->field_3828 = 0;
            }
            else if (press & PAD_CROSS)
            {
                GM_SeSet2(0, 63, SE_MENU_EXIT);
                work->field_3830 = 3;
                work->field_7874 = 3;
                work->field_3828 = 0;
                abst_800CB360(work, 66, 87, 78, 12, 255, 1);
            }
            break;
        }
        abst_800CB73C(work);
        break;

    case 4:
        if (work->field_3828 < 9)
        {
            work->field_787C = -(work->field_3828 * 0x28);
        }
        else if (work->field_3828 == 9)
        {
            base = (work->field_7878 - 1) * 7;
            for (i = base + 1; i < base + 8; i++)
            {
                abst_800CB1E0(work, i, 0);
            }
            for (i = base + 8; i < base + 15; i++)
            {
                abst_800CB1E0(work, i, 0x6739);
            }
        }
        else if (work->field_3828 < 0x12)
        {
            work->field_787C = (17 - work->field_3828) * 0x28;
        }
        else
        {
            work->field_3830 = 2;
            work->field_7870 = 0;
            work->field_7878++;
        }
        work->field_3828++;
        abst_800CB73C(work);
        break;

    case 5:
        if (work->field_3828 < 9)
        {
            work->field_787C = work->field_3828 * 0x28;
        }
        else if (work->field_3828 == 9)
        {
            base = (work->field_7878 - 1) * 7;
            for (i = base + 1; i < base + 8; i++)
            {
                abst_800CB1E0(work, i, 0);
            }
            for (i = base - 6; i < base + 1; i++)
            {
                abst_800CB1E0(work, i, 0x6739);
            }
        }
        else if (work->field_3828 < 0x12)
        {
            work->field_787C = -((17 - work->field_3828) * 0x28);
        }
        else
        {
            work->field_3830 = 2;
            work->field_7870 = 0;
            work->field_7878--;
        }
        work->field_3828++;
        abst_800CB73C(work);
        break;

    case 3:
        if (work->field_3828 < 0x61)
        {
            if (work->field_3828 < 9)
            {
                shade = 255 - (work->field_3828 * 255) / 8;
                poly = work->polys2;
                for (i = 0; i < 9; i++)
                {
                    setRGB0(poly, shade, shade, shade);
                    poly++;
                }
                abst_800CB73C(work);
            }

            r = 86 - (work->field_3828 * 86) / 96;
            g = 137 - (work->field_3828 * 137) / 96;
            b = 116 - (work->field_3828 * 116) / 96;
            poly = work->polys1;
            for (i = 0; i < 8; i++)
            {
                setRGB0(poly, r, g, b);
                poly++;
            }

            shade = 25 - (work->field_3828 * 25) / 96;
            col = (shade << 10) | (shade << 5) | shade;
            base = (work->field_7878 - 1) * 7;
            for (i = base + 1; i < base + 8; i++)
            {
                abst_800CB1E0(work, i, col);
            }

            if (work->field_7870 == 1)
            {
                for (i = base + 1; i < base + 8; i++)
                {
                    abst_800CB1E0(work, i, 0);
                }
            }

            work->field_3828++;
        }
        else
        {
            if (work->field_7874 == 3)
            {
                GCL_ExecProc(work->end_proc, NULL);
            }
            else
            {
                GCL_ExecProc(work->field_24, NULL);
            }
            GV_DestroyActor(work);
        }
        break;
    }

    abst_800CA7F0(work, DG_Chanl(1)->ot[GV_Clock], work->field_786C);
    abst_800CB23C(work);
}

/* ---- group2 consts, placed AFTER abst_800CB8A4 (0x800CE8F4..0x800CE9CC) ---- */
const char abst_dword_800CE8F4[] = "Texture LoadImage Finish!\n";
const char abst_dword_800CE910[] = "Cannot Find Texture\n";
const char abst_dword_800CE928[] = "Cannot Set Texture!!\n";
const char abst_dword_800CE940[] = "abst_ud_l";
const char abst_dword_800CE94C[] = "abst_ud_r";
const char abst_dword_800CE958[] = "abst_dd_l2";
const char abst_dword_800CE964[] = "abst_dd_r1";
const char abst_dword_800CE970[] = "abst_dd_r2";
const char abst_dword_800CE97C[] = "abst_dd_l1";
const char abst_dword_800CE988[] = "cur_lu";
const char abst_dword_800CE990[] = "cur_ru";
const char abst_dword_800CE998[] = "cur_ld";
const char abst_dword_800CE9A0[] = "cur_rd";
const char abst_dword_800CE9A8[] = "cur_u";
const char abst_dword_800CE9B0[] = "cur_d";
const char abst_dword_800CE9B8[] = "cur_l";
const char abst_dword_800CE9C0[] = "cur_r";
const char abst_dword_800CE9C8[] = "cur_c";

void abst_800CCC20(Work *work)
{
    int   i;
    void *buf;

    GM_FreePrim(work->prim1);
    GM_FreePrim(work->prim2);

    for (i = 0; i < 24; i++)
    {
        buf = abst_800CB230(&work->kcb[i]);
        GV_FreeMemory(GV_NORMAL_MEMORY, buf);
    }
}

void abst_800CCCBC(Work *work, int opt)
{
    AbstRes *res;
    int      i;
    int      found;
    int      file;
    int      size;
    void    *buf;

    found = -1;
    file = 0;
    size = 0;
    for (i = 0; i < 100; i++)
    {
        res = &abst_dword_800C3D50[i];
        if (opt == res->id)
        {
            found = i;
            file = res->file;
            size = res->size;
        }
    }

    if (found != -1)
    {
        buf = GV_Malloc(size);
        FS_LoadFileRequest(6, file, size, buf);
        while (FS_LoadFileSync() > 0)
        {
            mts_wait_vbl(1);
        }

        DG_LoadInitPcx(buf, opt);
        printf((char *)abst_dword_800CE8F4);
        GV_Free(buf);
    }
    else
    {
        printf((char *)abst_dword_800CE910);
    }
}

void abst_800CCDA8(void *work, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe)
{
    setPolyFT4(poly);
    setRGB0(poly, 0, 0, 0);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);
}

static inline void InitTex(POLY_FT4 *poly, DG_TEX *tex, int x, int y)
{
    int x0, x1, y0, y1;

    x0 = tex->off_x;
    x1 = x0 + tex->w + x;
    y0 = tex->off_y;
    y1 = y0 + tex->h + y;

    setUV4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}

void abst_800CCE14(void *work, int name, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe, int mode)
{
    DG_TEX *tex;

    abst_800CCDA8(work, poly, x0, y0, x1, y1, abe);
    tex = DG_GetTexture(name);

    if (mode == 0)
    {
        InitTex(poly, tex, 1, 1);
    }
    else if (mode == 1)
    {
        InitTex(poly, tex, 1, 0);
    }
    else if (mode == 2)
    {
        InitTex(poly, tex, 0, 1);
    }
    else if (mode == 3)
    {
        InitTex(poly, tex, 0, 0);
    }
}

int abst_800CCF98(Work *work, int where)
{
    char     *opt;
    POLY_FT4 *poly;
    DG_PRIM  *prim;
    int       i;

    GM_CurrentMap = where;

    work->font_x = 576;
    work->font_y = 256;
    work->clut_x = 576;
    work->clut_y = 276;

    prim = DG_MakePrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 8, 0, 0, 0);
    if (prim)
    {
        DG_QueuePrim(prim);
        DG_GroupPrim(prim, GM_CurrentMap);
    }
    work->prim1 = prim;

    prim = DG_MakePrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 9, 0, 0, 0);
    if (prim)
    {
        DG_QueuePrim(prim);
        DG_GroupPrim(prim, GM_CurrentMap);
    }
    work->prim2 = prim;

    poly = work->polys1;
    i = 0;

    opt = GCL_GetOption('l');
    if (opt)
    {
        abst_800CCCBC(work, GCL_StrToInt(opt));
        abst_800CCE14(work, GCL_StrToInt(opt), poly, -160, -82, 0, 82, 0, 0);
    }
    else
    {
        printf((char *)abst_dword_800CE928);
    }

    poly++;
    work->attrs1[i] = 0;
    i++;

    opt = GCL_GetOption('r');
    if (opt)
    {
        abst_800CCCBC(work, GCL_StrToInt(opt));
        abst_800CCE14(work, GCL_StrToInt(opt), poly, 0, -82, 160, 82, 0, 0);
    }
    else
    {
        printf((char *)abst_dword_800CE928);
    }

    poly++;
    work->attrs1[i] = 0;
    i++;

    abst_800CCE14(work, GV_StrCode((char *)abst_dword_800CE940), poly, -160, -112, 0, -82, 0, 0);

    poly++;
    work->attrs1[i] = 0;
    i++;

    abst_800CCE14(work, GV_StrCode((char *)abst_dword_800CE94C), poly, 0, -112, 160, -82, 0, 0);

    poly++;
    work->attrs1[i] = 0;
    i++;

    abst_800CCE14(work, GV_StrCode((char *)abst_dword_800CE958), poly, -160, 87, 0, 117, 1, 0);
    setRGB0(poly, 86, 137, 116);

    poly++;
    work->attrs1[i] = 0;
    i++;

    abst_800CCE14(work, GV_StrCode((char *)abst_dword_800CE964), poly, 0, 87, 60, 117, 1, 0);
    setRGB0(poly, 86, 137, 116);

    poly++;
    work->attrs1[i] = 0;
    i++;

    abst_800CCE14(work, GV_StrCode((char *)abst_dword_800CE970), poly, 60, 87, 160, 117, 1, 0);
    setRGB0(poly, 86, 137, 116);

    poly++;
    work->attrs1[i] = 0;
    i++;

    abst_800CCE14(work, GV_StrCode((char *)abst_dword_800CE97C), poly, -160, 87, 0, 117, 1, 0);
    setRGB0(poly, 86, 137, 116);

    work->attrs1[i] = 0;

    poly = work->polys2;
    i = 0;

    abst_800CCE14(work, GV_StrCode((char *)abst_dword_800CE988), poly, -33, 81, -25, 89, 0, 0);

    poly++;
    work->attrs2[i] = 0;
    i++;

    abst_800CCE14(work, GV_StrCode((char *)abst_dword_800CE990), poly, 25, 81, 33, 89, 0, 0);

    poly++;
    work->attrs2[i] = 0;
    i++;

    abst_800CCE14(work, GV_StrCode((char *)abst_dword_800CE998), poly, -33, 97, -25, 105, 0, 0);

    poly++;
    work->attrs2[i] = 0;
    i++;

    abst_800CCE14(work, GV_StrCode((char *)abst_dword_800CE9A0), poly, 25, 97, 33, 105, 0, 0);

    poly++;
    work->attrs2[i] = 0;
    i++;

    abst_800CCE14(work, GV_StrCode((char *)abst_dword_800CE9A8), poly, -25, 81, 25, 89, 0, 2);

    poly++;
    work->attrs2[i] = 0;
    i++;

    abst_800CCE14(work, GV_StrCode((char *)abst_dword_800CE9B0), poly, -25, 97, 25, 105, 0, 2);

    poly++;
    work->attrs2[i] = 0;
    i++;

    abst_800CCE14(work, GV_StrCode((char *)abst_dword_800CE9B8), poly, -33, 89, -25, 97, 0, 1);

    poly++;
    work->attrs2[i] = 0;
    i++;

    abst_800CCE14(work, GV_StrCode((char *)abst_dword_800CE9C0), poly, 25, 89, 33, 97, 0, 1);

    poly++;
    work->attrs2[i] = 0;
    i++;

    abst_800CCE14(work, GV_StrCode((char *)abst_dword_800CE9C8), poly, -25, 89, 25, 97, 0, 3);

    work->attrs2[i] = 0;

    if (GCL_GetOption('e'))
    {
        work->end_proc = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->end_proc = -1;
    }

    if (GCL_GetOption('d'))
    {
        work->field_24 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->field_24 = -1;
    }

    if (GCL_GetOption('i'))
    {
        work->field_320 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->field_320 = 24;
    }

    for (i = 0; i < work->field_320 + 1; i++)
    {
        work->field_7B8[i].string = GCL_GetString(GCL_NextStr());
        work->field_7B8[i].num = 0;
        abst_800CA568(work, i);
    }

    for (i = 0; i < work->field_320 + 1; i++)
    {
        abst_800CA6FC(work, i);
    }

    work->pad = &GV_PadData[2];
    work->field_3828 = 0;
    work->field_3830 = 0;
    work->field_3834 = 0;

    for (i = 0; i < 1; i++)
    {
        abst_800CB1E0(work, i, 0x6739);
    }

    for (i = 1; i < 24; i++)
    {
        abst_800CB1E0(work, i, 0);
    }

    work->primbuf.buf[0] = work->field_386C;
    work->primbuf.buf[1] = work->field_586C;
    sub_80048124();

    work->field_7870 = 0;
    work->field_7878 = 1;
    work->field_787C = 0;
    work->field_3830 = 1;

    for (i = 0; i < 8; i++)
    {
        work->attrs1[i] = 0x100;
    }

    work->attrs1[4] = 0;
    work->field_3828 = 0;

    {
        POLY_FT4 *p = work->polys1;
        setRGB0(&p[2], 86, 137, 116);
        setRGB0(&p[3], 86, 137, 116);
        setRGB0(&p[4], 86, 137, 116);
        setRGB0(&p[5], 86, 137, 116);
    }

    for (i = 0; i < 1; i++)
    {
        abst_800CB1E0(work, i, 0);
    }

    for (i = 0; i < 9; i++)
    {
        work->attrs2[i] = 0x200;
    }

    abst_800CB360(work, 30, 86, 16, 14, 255, 1);

    poly = work->polys2;
    for (i = 0; i < 9; i++)
    {
        setRGB0(poly, 0, 0, 0);
        poly++;
    }

    return 0;
}

void *NewAbstractDemo2(int name, int where)
{
    Work *work;

    GM_GameStatus |= STATE_ALL_OFF;
    
    work = GV_NewActor(GV_ACTOR_MANAGER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, abst_800CB8A4, abst_800CCC20, "ab_demo2.c");
        if (abst_800CCF98(work, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}
