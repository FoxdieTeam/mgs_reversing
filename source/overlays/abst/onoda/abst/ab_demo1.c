#include "game/game.h"
#include "libgcl/libgcl.h"

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

extern Unknown2 abst_dword_800C37B8[];

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

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C7CF4.s")

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
#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C877C.s")
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

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C9954.s")

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

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C9C30.s")
int abst_800C9C30(Work *work, int where);

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
