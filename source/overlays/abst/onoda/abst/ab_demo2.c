#include "game/game.h"
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
    /* +0x000 */ char  sprites[0x180];
    /* +0x180 */ char *string;
    /* +0x184 */ short num;
    /* +0x186 */ short num2;
    /* +0x188 */ RECT  rect;
    /* +0x190 */ short unk1;
    /* +0x192 */ short unk2;
    /* +0x194 */ short x0;
    /* +0x196 */ short y0;
    /* +0x198 */ short cx;
    /* +0x19A */ short cy;
    /* +0x19C */ short unk3;
    /* +0x19E */ short unk4;
    /* +0x1A0 */ short x1;
    /* +0x1A2 */ short y1;
    /* +0x1A4 */ char  pad[0x204 - 0x1A4];
} Unknown;

typedef struct _Work
{
    /* +0x0000 */ GV_ACT   actor;
    /* +0x0020 */ int      end_proc;
    /* +0x0024 */ GV_PAD  *pad;
    /* +0x0028 */ int      field_28;
    /* +0x002C */ DG_PRIM *prim1;
    /* +0x0030 */ DG_PRIM *prim2;
    /* +0x0034 */ POLY_FT4 polys1[8];
    /* +0x0174 */ POLY_FT4 polys2[9];
    /* +0x02DC */ int      attrs1[8];
    /* +0x02FC */ int      attrs2[9];
    /* +0x0320 */ int      field_320;
    /* +0x0324 */ KCB      kcb[24];
    /* +0x0744 */ char     pad_744[0x818 - 0x744];
    /* +0x0818 */ Unknown  field_818[12];
    /* +0x2048 */ char     pad_2048[0x3818 - 0x2048];
    /* +0x3818 */ int      font_x;
    /* +0x381C */ int      font_y;
    /* +0x3820 */ int      clut_x;
    /* +0x3824 */ int      clut_y;
    /* +0x3828 */ int      field_3828;
    /* +0x382C */ char     pad_382C[0x3830 - 0x382C];
    /* +0x3830 */ int      field_3830;
    /* +0x3834 */ char     pad_3834[0x7878 - 0x3834];
    /* +0x7878 */ int      field_7878;
    /* +0x787C */ char     pad_787C[0x7884 - 0x787C];
} Work;

typedef struct _AbstRes
{
    int id;
    int file;
    int size;
} AbstRes;

extern int abst_dword_800C3CD0;
extern AbstRes abst_dword_800C3D50[];
extern const char abst_dword_800CE8B4[];
extern const char abst_dword_800CE8B8[];
extern const char abst_dword_800CE8F4[];
extern const char abst_dword_800CE910[];

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

    work->field_818[index].x0 = work->font_x;
    work->field_818[index].y0 = work->font_y;

    work->field_818[index].x1 = work->font_x + 64;
    work->field_818[index].y1 = work->font_y;
    work->font_y += 21;

    font_init_kcb(kcb, &rect, work->clut_x, work->clut_y);

    work->field_818[index].cx = work->clut_x;
    work->field_818[index].cy = work->clut_y;
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

    if (work->field_818[index].string)
    {
        kcb = &work->kcb[index];
        font_print_string(kcb, work->field_818[index].string);
        font_update(kcb);
        font_clut_update(kcb);

        work->field_818[index].unk1 = 256;
        work->field_818[index].unk2 = kcb->max_height - 1;

        work->field_818[index].rect.x = ((Unknown2 *)&abst_dword_800C3CD0)[index].x;
        work->field_818[index].rect.y = ((Unknown2 *)&abst_dword_800C3CD0)[index].y;
        work->field_818[index].unk3 = 128;

        work->field_818[index].unk4 = kcb->max_height - 1;

        work->field_818[index].rect.w = ((Unknown2 *)&abst_dword_800C3CD0)[index].x + 256;

        work->field_818[index].rect.h = ((Unknown2 *)&abst_dword_800C3CD0)[index].y;
        work->field_818[index].string = NULL;
        work->field_818[index].num = 1;
    }
}

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800CA7F0.s")

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

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800CB360.s")
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

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800CB8A4.s")
void abst_800CB8A4(Work *work);

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

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800CCF98.s")
int abst_800CCF98(Work *work, int where);

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
