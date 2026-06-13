#include "game/game.h"
#include "libgcl/libgcl.h"
#include "libfs/libfs.h"
#include "mts/mts.h"

#include <stdio.h>

// Same struct as in abst.c (this is the "demo 1" UI variant).
typedef struct _Unknown
{
    SPRT  text_sprt[2];
    SPRT  text_sprt_outline[2][4];
    SPRT  text_sprt2[2];
    SPRT  text_sprt_outline2[2][4];
    SPRT  text_sprt3[2];
    SPRT  text_sprt4[2];
    char *string;
    short num;
    short num2;
    RECT  rect;
    short unk1;
    short unk2;
    short x0;
    short y0;
    short cx;
    short cy;
    short unk3;
    short unk4;
    short x1;
    short y1;
} Unknown;

typedef struct _Unknown2
{
    short x, y;
    int   color;
} Unknown2;

typedef struct _Work
{
    /* +0x0000 */ GV_ACT   actor;
    /* +0x0020 */ int      end_proc;
    /* +0x0024 */ int      field_24;
    /* +0x0028 */ GV_PAD  *pad;
    /* +0x002C */ DG_PRIM *prim1;
    /* +0x0030 */ DG_PRIM *prim2;
    /* +0x0034 */ POLY_FT4 polys1[6];
    /* +0x0124 */ POLY_FT4 polys2[9];
    /* +0x028C */ int      attrs1[6];
    /* +0x02A4 */ int      attrs2[9];
    /* +0x02C8 */ int      field_2C8;
    /* +0x02CC */ KCB      kcb[12];
    /* +0x04DC */ char     pad1[0x14];
    /* +0x04F0 */ DR_TPAGE tpage[6];
    /* +0x0520 */ Unknown  field_520[12];
    /* +0x1D50 */ int      font_x;
    /* +0x1D54 */ int      font_y;
    /* +0x1D58 */ int      clut_x;
    /* +0x1D5C */ int      clut_y;
    /* +0x1D60 */ int      field_1D60;
    /* +0x1D64 */ char     pad3[0x4];
    /* +0x1D68 */ int      field_1D68;
    /* +0x1D6C */ int      field_1D6C;
    /* +0x1D70 */ char     pad4[0x20];
    /* +0x1D90 */ MenuPrim primbuf;
    /* +0x1DA4 */ char     field_1DA4[0x2000];
    /* +0x3DA4 */ char     field_3DA4[0x2000];
    /* +0x5DA4 */ int      field_5DA4;
    /* +0x5DA8 */ int      field_5DA8;
    /* +0x5DAC */ int      field_5DAC;
} Work;

typedef struct _AbstRes
{
    int id;
    int file;
    int size;
} AbstRes;

extern Unknown2 abst_dword_800C37B8[];
extern signed char abst_dword_800C3818[];
extern AbstRes abst_dword_800C3820[];
extern const char abst_dword_800CE7E4[];
extern const char abst_dword_800CE800[];
extern const char abst_dword_800CE818[];
extern const char abst_dword_800CE830[];
extern const char abst_dword_800CE83C[];
extern const char abst_dword_800CE848[];
extern const char abst_dword_800CE854[];
extern const char abst_dword_800CE860[];
extern const char abst_dword_800CE868[];
extern const char abst_dword_800CE870[];
extern const char abst_dword_800CE878[];
extern const char abst_dword_800CE880[];
extern const char abst_dword_800CE888[];
extern const char abst_dword_800CE890[];
extern const char abst_dword_800CE898[];
extern const char abst_dword_800CE8A0[];

void abst_800C7AB0(Work *work, int index)
{
    RECT  rect;
    KCB  *kcb;
    void *buf;

    kcb = &work->kcb[index];

    rect.x = work->font_x;
    rect.y = work->font_y;
    rect.w = 128;
    rect.h = 21;

    work->field_520[index].x0 = work->font_x;
    work->field_520[index].y0 = work->font_y;

    work->field_520[index].x1 = work->font_x + 64;
    work->field_520[index].y1 = work->font_y;
    work->font_y += 21;

    font_init_kcb(kcb, &rect, work->clut_x, work->clut_y);

    work->field_520[index].cx = work->clut_x;
    work->field_520[index].cy = work->clut_y;
    work->clut_y += 21;

    font_set_kcb(kcb, -1, -1, 0, 6, 2, 0);

    buf = GV_AllocMemory(GV_NORMAL_MEMORY, font_get_buffer_size(kcb));
    font_set_buffer(kcb, buf);

    font_set_color(kcb, 0, abst_dword_800C37B8[index].color, 0);
    font_clut_update(kcb);
}

void abst_800C7C0C(Work *work, int index)
{
    KCB *kcb;

    if (work->field_520[index].string)
    {
        kcb = &work->kcb[index];
        font_print_string(kcb, work->field_520[index].string);
        font_update(kcb);
        font_clut_update(kcb);

        work->field_520[index].unk1 = 256;
        work->field_520[index].unk2 = kcb->max_height;

        work->field_520[index].rect.x = abst_dword_800C37B8[index].x;
        work->field_520[index].rect.y = abst_dword_800C37B8[index].y;

        work->field_520[index].unk3 = 256;
        work->field_520[index].unk4 = kcb->max_height;

        work->field_520[index].rect.w = abst_dword_800C37B8[index].x + 256;
        work->field_520[index].rect.h = abst_dword_800C37B8[index].y;

        work->field_520[index].string = NULL;
        work->field_520[index].num = 1;
    }
}

void abst_800C7CF4(Work *work, u_long *ot, int arg2)
{
    int       i, j;
    SPRT     *sprt;
    DR_TPAGE *tpage;
    int       index;
    SPRT     *sprt1;
    SPRT     *sprt2;

    index = 0;
    for (i = 0; i < work->field_2C8 + 3; i++)
    {
        if (work->field_520[index].num == 1)
        {
            sprt = &work->field_520[index].text_sprt[GV_Clock];
            setSprt(sprt);
            setRGB0(sprt, 128, 128, 128);
            setSemiTrans(sprt, 1);
            LCOPY(&work->field_520[index].rect.x, &sprt->x0);
            LCOPY(&work->field_520[index].unk1, &sprt->w);
            setUV0(sprt, 0, work->field_520[index].y0);
            setClut(sprt, work->field_520[index].cx, work->field_520[index].cy);
            addPrim(ot, sprt);
            index++;
        }
    }

    tpage = &work->tpage[0];
    setDrawTPage(tpage, 1, 0, getTPage(0, 1, 704, 256));
    addPrim(ot, tpage);

    index = 0;
    for (i = 0; i < work->field_2C8 + 3; i++)
    {
        if (work->field_520[index].num == 1)
        {
            sprt = &work->field_520[index].text_sprt2[GV_Clock];
            setSprt(sprt);
            setRGB0(sprt, 128, 128, 128);
            setSemiTrans(sprt, 1);
            LCOPY(&work->field_520[index].rect.w, &sprt->x0);
            LCOPY(&work->field_520[index].unk3, &sprt->w);
            setUV0(sprt, 0, work->field_520[index].y1);
            setClut(sprt, work->field_520[index].cx, work->field_520[index].cy);
            addPrim(ot, sprt);
            index++;
        }
    }

    tpage = &work->tpage[1];
    setDrawTPage(tpage, 1, 0, getTPage(0, 1, 768, 256));
    addPrim(ot, tpage);

    index = 0;
    for (i = 0; i < work->field_2C8 + 3; i++)
    {
        if (work->field_520[index].num == 1)
        {
            sprt = &work->field_520[index].text_sprt3[GV_Clock];
            setSprt(sprt);
            setRGB0(sprt, 128, 128, 128);
            setSemiTrans(sprt, 1);
            LCOPY(&work->field_520[index].rect.x, &sprt->x0);
            LCOPY(&work->field_520[index].unk1, &sprt->w);
            setUV0(sprt, 0, work->field_520[index].y0);
            setClut(sprt, work->field_520[index].cx, work->field_520[index].cy);
            addPrim(ot, sprt);
            index++;
        }
    }

    tpage = &work->tpage[4];
    setDrawTPage(tpage, 1, 0, getTPage(0, 2, 704, 256));
    addPrim(ot, tpage);

    index = 0;
    for (i = 0; i < work->field_2C8 + 3; i++)
    {
        if (work->field_520[index].num == 1)
        {
            sprt = &work->field_520[index].text_sprt4[GV_Clock];
            setSprt(sprt);
            setRGB0(sprt, 128, 128, 128);
            setSemiTrans(sprt, 1);
            LCOPY(&work->field_520[index].rect.w, &sprt->x0);
            LCOPY(&work->field_520[index].unk3, &sprt->w);
            setUV0(sprt, 0, work->field_520[index].y1);
            setClut(sprt, work->field_520[index].cx, work->field_520[index].cy);
            addPrim(ot, sprt);
            index++;
        }
    }

    tpage = &work->tpage[5];
    setDrawTPage(tpage, 1, 0, getTPage(0, 2, 768, 256));
    addPrim(ot, tpage);

    if (arg2 == 1)
    {
        index = 0;
        for (i = 0; i < work->field_2C8 + 3; i++)
        {
            if (work->field_520[index].num == 1)
            {
                sprt2 = work->field_520[index].text_sprt_outline[GV_Clock];
                sprt1 = &work->field_520[index].text_sprt[GV_Clock];

                for (j = 0; j < 8; j += 2)
                {
                    *sprt2 = *sprt1;
                    setSprt(sprt2);
                    setRGB0(sprt2, 128, 128, 128);
                    setSemiTrans(sprt2, 1);
                    sprt2->x0 += abst_dword_800C3818[j];
                    sprt2->y0 += abst_dword_800C3818[j + 1];
                    addPrim(ot, sprt2);
                    sprt2++;
                }

                index++;
            }
        }

        tpage = &work->tpage[2];
        setDrawTPage(tpage, 1, 0, getTPage(0, 2, 704, 256));
        addPrim(ot, tpage);

        index = 0;
        for (i = 0; i < work->field_2C8 + 3; i++)
        {
            if (work->field_520[index].num == 1)
            {
                sprt2 = work->field_520[index].text_sprt_outline2[GV_Clock];
                sprt1 = &work->field_520[index].text_sprt2[GV_Clock];

                for (j = 0; j < 8; j += 2, sprt++)
                {
                    *sprt2 = *sprt1;
                    setSprt(sprt2);
                    setRGB0(sprt2, 128, 128, 128);
                    setSemiTrans(sprt2, 1);
                    sprt2->x0 += abst_dword_800C3818[j];
                    sprt2->y0 += abst_dword_800C3818[j + 1];
                    addPrim(ot, sprt2);
                    sprt2++;
                }

                index++;
            }
        }

        tpage = &work->tpage[3];
        setDrawTPage(tpage, 1, 0, getTPage(0, 2, 768, 256));
        addPrim(ot, tpage);
    }
}

void abst_800C85FC(Work *work, int index, int col)
{
    font_set_color(&work->kcb[index], 0, col, 0);
    font_clut_update(&work->kcb[index]);
}

void *abst_800C864C(KCB *kcb)
{
    return kcb->cbuffer;
}

void abst_800C8658(Work *work)
{
    POLY_FT4 *src;
    POLY_FT4 *dst;
    int       i;

    dst = work->prim1->packs[GV_Clock];
    src = work->polys1;
    for (i = 0; i < 6; i++)
    {
        *dst = *src;
        *(short *)dst = work->attrs1[i];
        src++;
        dst++;
    }

    dst = work->prim2->packs[GV_Clock];
    src = work->polys2;
    for (i = 0; i < 9; i++)
    {
        *dst = *src;
        *(short *)dst = work->attrs2[i];
        src++;
        dst++;
    }
}
void abst_800C877C(Work *work, int x, int y, int w, int h, int color, int sel)
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
void abst_800C8A60(MenuPrim *prim, int x, int y, int w, int h)
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

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C8B58.s")
void abst_800C8B58(Work *work);

void abst_800C98B8(Work *work)
{
    int   i;
    void *buf;

    GM_FreePrim(work->prim1);
    GM_FreePrim(work->prim2);

    for (i = 0; i < 12; i++)
    {
        buf = abst_800C864C(&work->kcb[i]);
        GV_FreeMemory(GV_NORMAL_MEMORY, buf);
    }
}

void abst_800C9954(Work *work, int opt)
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
        res = &abst_dword_800C3820[i];
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
        printf((char *)abst_dword_800CE7E4);
        GV_Free(buf);
    }
    else
    {
        printf((char *)abst_dword_800CE800);
    }
}

void abst_800C9A40(void *work, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe)
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

void abst_800C9AAC(void *work, int name, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe, int mode)
{
    DG_TEX *tex;

    abst_800C9A40(work, poly, x0, y0, x1, y1, abe);
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

int abst_800C9C30(Work *work, int where)
{
    char     *opt;
    POLY_FT4 *poly;
    DG_PRIM  *prim;
    int       i;

    GM_CurrentMap = where;

    work->font_x = 704;
    work->font_y = 256;
    work->clut_x = 704;
    work->clut_y = 276;

    prim = DG_MakePrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 6, 0, 0, 0);
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
        abst_800C9954(work, GCL_StrToInt(opt));
        abst_800C9AAC(work, GCL_StrToInt(opt), poly, -160, -82, 0, 82, 0, 0);
    }
    else
    {
        printf((char *)abst_dword_800CE818);
    }

    poly++;
    work->attrs1[i] = 0;
    i++;

    opt = GCL_GetOption('r');
    if (opt)
    {
        abst_800C9954(work, GCL_StrToInt(opt));
        abst_800C9AAC(work, GCL_StrToInt(opt), poly, 0, -82, 160, 82, 0, 0);
    }
    else
    {
        printf((char *)abst_dword_800CE818);
    }

    poly++;
    work->attrs1[i] = 0;
    i++;

    abst_800C9AAC(work, GV_StrCode((char *)abst_dword_800CE830), poly, -160, -112, 0, -82, 0, 0);

    poly++;
    work->attrs1[i] = 0;
    i++;

    abst_800C9AAC(work, GV_StrCode((char *)abst_dword_800CE83C), poly, 0, -112, 160, -82, 0, 0);

    poly++;
    work->attrs1[i] = 0;
    i++;

    abst_800C9AAC(work, GV_StrCode((char *)abst_dword_800CE848), poly, -160, 82, 0, 112, 1, 0);

    poly++;
    work->attrs1[i] = 0;
    i++;

    abst_800C9AAC(work, GV_StrCode((char *)abst_dword_800CE854), poly, 0, 82, 160, 112, 1, 0);

    work->attrs1[i] = 0;

    poly = work->polys2;
    i = 0;

    abst_800C9AAC(work, GV_StrCode((char *)abst_dword_800CE860), poly, -33, 81, -25, 89, 0, 0);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    abst_800C9AAC(work, GV_StrCode((char *)abst_dword_800CE868), poly, 25, 81, 33, 89, 0, 0);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    abst_800C9AAC(work, GV_StrCode((char *)abst_dword_800CE870), poly, -33, 97, -25, 105, 0, 0);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    abst_800C9AAC(work, GV_StrCode((char *)abst_dword_800CE878), poly, 25, 97, 33, 105, 0, 0);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    abst_800C9AAC(work, GV_StrCode((char *)abst_dword_800CE880), poly, -25, 81, 25, 89, 0, 2);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    abst_800C9AAC(work, GV_StrCode((char *)abst_dword_800CE888), poly, -25, 97, 25, 105, 0, 2);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    abst_800C9AAC(work, GV_StrCode((char *)abst_dword_800CE890), poly, -33, 89, -25, 97, 0, 1);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    abst_800C9AAC(work, GV_StrCode((char *)abst_dword_800CE898), poly, 25, 89, 33, 97, 0, 1);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    abst_800C9AAC(work, GV_StrCode((char *)abst_dword_800CE8A0), poly, -25, 89, 25, 97, 0, 3);
    setRGB0(poly, 255, 255, 255);

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
        work->field_2C8 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->field_2C8 = 12;
    }

    for (i = 0; i < work->field_2C8 + 1; i++)
    {
        work->field_520[i].string = GCL_GetString(GCL_NextStr());
        work->field_520[i].num = 0;
        abst_800C7AB0(work, i);
    }

    for (i = 0; i < work->field_2C8 + 1; i++)
    {
        abst_800C7C0C(work, i);
    }

    work->pad = &GV_PadData[2];
    work->field_1D60 = 0;
    work->field_1D68 = 0;
    work->field_1D6C = 0;

    for (i = 0; i < 1; i++)
    {
        abst_800C85FC(work, i, 0x6739);
    }

    for (i = 1; i < work->field_2C8 + 1; i++)
    {
        abst_800C85FC(work, i, 0);
    }

    work->primbuf.buf[0] = work->field_1DA4;
    work->primbuf.buf[1] = work->field_3DA4;
    sub_80048124();

    work->field_5DA8 = 0;
    work->field_1D68 = 1;

    for (i = 0; i < 6; i++)
    {
        work->attrs1[i] = 0x100;
    }

    work->field_1D60 = 0;

    {
        POLY_FT4 *p = work->polys1;
        setRGB0(&p[2], 86, 137, 116);
        setRGB0(&p[3], 86, 137, 116);
        setRGB0(&p[4], 86, 137, 116);
        setRGB0(&p[5], 86, 137, 116);
    }

    for (i = 0; i < 1; i++)
    {
        abst_800C85FC(work, i, 0);
    }

    for (i = 0; i < 9; i++)
    {
        work->attrs2[i] = 0x200;
    }

    abst_800C877C(work, 41, 87, 78, 12, 255, 1);

    poly = work->polys2;
    for (i = 0; i < 9; i++)
    {
        setRGB0(poly, 0, 0, 0);
        poly++;
    }

    return 0;
}

void *NewAbstractDemo1(int name, int where)
{
    Work *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = GV_NewActor(GV_ACTOR_MANAGER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, abst_800C8B58, abst_800C98B8, "ab_demo1.c");
        if (abst_800C9C30(work, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}
