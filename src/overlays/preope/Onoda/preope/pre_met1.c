#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Font/font.h"
#include "Menu/menuman.h"
#include "Game/game.h"

typedef struct PreMet1SubWork_8000
{
    // offsets relative to PreMet1Work start
    char pad_8000[0x1584];
    int  field_9584;
    int  field_9588;
    int  field_958C;
    int  field_9590;
    int  field_9594;
    int  field_9598;
} PreMet1SubWork_8000;

typedef struct _PreMet1Work
{
    GV_ACT              actor;
    DG_PRIM            *field_20;
    DG_PRIM            *field_24;
    int                 field_28[6];
    int                 field_40[9];
    int                 field_64;
    POLY_FT4            field_68[6];
    POLY_FT4            field_158[9];
    short              *field_2C0;
    int                *field_2C4;
    int                 field_2C8;
    int                 field_2CC;
    KCB                 field_2D0[8];
    char                pad_430[0x7BD0];
    PreMet1SubWork_8000 field_8000;
} PreMet1Work;

#define EXEC_LEVEL 5

// TODO: move data to pre_met1.c and format preope_dword_800C3250
typedef struct PreMet1Unk
{
    int field_0;
    int field_4;
} PreMet1Unk;

extern PreMet1Unk preope_dword_800C3250[8];

extern int GV_Clock_800AB920;

void PreMet1_800C4E40(PreMet1Work *work, int index)
{
    RECT rect;
    KCB *kcb;

    kcb = &work->field_2D0[index];
    rect.x = work->field_8000.field_9584;
    rect.y = work->field_8000.field_9588;
    rect.w = 128;
    rect.h = 21;

    work->field_8000.field_9588 += 21;
    font_init_kcb_80044BE0(kcb, &rect, work->field_8000.field_958C, work->field_8000.field_9590);
    work->field_8000.field_9590 += 21;

    font_set_kcb_80044C90(kcb, -1, -1, 0, 6, 2, 0);
    font_set_buffer_80044FD8(kcb, GV_AllocMemory_80015EB8(2, font_get_buffer_size_80044F38(kcb)));
    font_set_color_80044DC4(kcb, 0, preope_dword_800C3250[index].field_4, 0);
    font_clut_update_80046980(kcb);
}

#pragma INCLUDE_ASM("asm/overlays/preope/pre_met1_800C4F58.s")
#pragma INCLUDE_ASM("asm/overlays/preope/pre_met1_800C4FD4.s")
void pre_met1_800C4FD4(PreMet1Work *work, int index);

#pragma INCLUDE_ASM("asm/overlays/preope/pre_met1_800C50D4.s")
void pre_met1_800C50D4(PreMet1Work *work, char *pOt);

void PreMet1SetColor_800C5738(PreMet1Work *work, int index, int fore)
{
    KCB *kcb;

    kcb = &work->field_2D0[index];
    font_set_color_80044DC4(kcb, 0, fore, 0);
    font_clut_update_80046980(kcb);
}

void *PreMet1GetClutBuffer_800C5788(KCB *kcb)
{
    return kcb->font_clut_buffer;
}

void PreMet1_800C5794(PreMet1Work *work)
{
    int i;
    for (i = 8; i >= 0; i--)
    {
        work->field_40[i] = 0;
    }
}

// Identical to title_open_800C4C38
void PreMet1_800C57B4(PreMet1Work *work, int x0, int y0, int xsize, int ysize, int color, int mode)
{
    POLY_FT4 *polys;
    int       i;

    polys = work->field_158;
    for (i = 0; i < 9; i++)
    {
        work->field_40[i] = 0x200;
        setRGB0(&polys[i], color, color, color);
    }

    if (mode == 0)
    {
        setXY4(&polys[0], x0 - 8, y0 - 8, x0, y0 - 8, x0 - 8, y0, x0, y0);
        setXY4(&polys[1], x0 + xsize, y0 - 8, x0 + xsize + 8, y0 - 8, x0 + xsize, y0, x0 + xsize + 8, y0);
        setXY4(&polys[2], x0 - 8, y0 + ysize, x0, y0 + ysize, x0 - 8, y0 + ysize + 8, x0, y0 + ysize + 8);
        setXY4(&polys[3], x0 + xsize, y0 + ysize, x0 + xsize + 8, y0 + ysize, x0 + xsize, y0 + ysize + 8,
               x0 + xsize + 8, y0 + ysize + 8);
        setXY4(&polys[4], x0, y0 - 8, x0 + xsize, y0 - 8, x0, y0, x0 + xsize, y0);
        setXY4(&polys[5], x0, y0 + ysize, x0 + xsize, y0 + ysize, x0, y0 + ysize + 8, x0 + xsize, y0 + ysize + 8);
        setXY4(&polys[6], x0 - 8, y0, x0, y0, x0 - 8, y0 + ysize, x0, y0 + ysize);
        setXY4(&polys[7], x0 + xsize, y0, x0 + xsize + 8, y0, x0 + xsize, y0 + ysize, x0 + xsize + 8, y0 + ysize);
        setXY4(&polys[8], x0, y0, x0 + xsize, y0, x0, y0 + ysize, x0 + xsize, y0 + ysize);
    }
    else if (mode == 1)
    {
        setXY4(&polys[0], x0 - 6, y0 - 6, x0 + 2, y0 - 6, x0 - 6, y0 + 2, x0 + 2, y0 + 2);
        setXY4(&polys[1], x0 + xsize - 2, y0 - 6, x0 + xsize + 6, y0 - 6, x0 + xsize - 2, y0 + 2, x0 + xsize + 6,
               y0 + 2);
        setXY4(&polys[2], x0 - 6, y0 + ysize - 2, x0 + 2, y0 + ysize - 2, x0 - 6, y0 + ysize + 6, x0 + 2,
               y0 + ysize + 6);
        setXY4(&polys[3], x0 + xsize - 2, y0 + ysize - 2, x0 + xsize + 6, y0 + ysize - 2, x0 + xsize - 2,
               y0 + ysize + 6, x0 + xsize + 6, y0 + ysize + 6);
        setXY4(&polys[4], x0 + 2, y0 - 6, x0 + xsize - 2, y0 - 6, x0 + 2, y0 + 2, x0 + xsize - 2, y0 + 2);
        setXY4(&polys[5], x0 + 2, y0 + ysize - 2, x0 + xsize - 2, y0 + ysize - 2, x0 + 2, y0 + ysize + 6,
               x0 + xsize - 2, y0 + ysize + 6);
        setXY4(&polys[6], x0 - 6, y0 + 2, x0 + 2, y0 + 2, x0 - 6, y0 + ysize - 2, x0 + 2, y0 + ysize - 2);
        setXY4(&polys[7], x0 + xsize - 2, y0 + 2, x0 + xsize + 6, y0 + 2, x0 + xsize - 2, y0 + ysize - 2,
               x0 + xsize + 6, y0 + ysize - 2);
        setXY4(&polys[8], x0 + 2, y0 + 2, x0 + xsize - 2, y0 + 2, x0 + 2, y0 + ysize - 2, x0 + xsize - 2,
               y0 + ysize - 2);
    }
}

void PreMet1ShadePacks_800C5A98(PreMet1Work *work)
{
    POLY_FT4 *poly_dst, *poly_src;
    int       r0, g0, b0;
    int       i;

    poly_src = work->field_68;
    poly_dst = &work->field_20->field_40_pBuffers[GV_Clock_800AB920]->poly_ft4;

    for (i = 0; i < 6; poly_dst++, poly_src++, i++)
    {
        *poly_dst = *poly_src;
        if (*work->field_2C4 == 1)
        {
            r0 = poly_dst->r0;
            g0 = poly_dst->g0;
            b0 = poly_dst->b0;
            setRGB0(poly_dst, r0 - r0 * work->field_64 / 16, g0 - g0 * work->field_64 / 16,
                    b0 - b0 * work->field_64 / 16);
        }
        else if (work->field_2C8 == 0)
        {
            r0 = poly_dst->r0;
            g0 = poly_dst->g0;
            b0 = poly_dst->b0;
            setRGB0(poly_dst, r0 * work->field_64 / 16, g0 * work->field_64 / 16, b0 * work->field_64 / 16);
        }

        SSTOREL(work->field_28[i], poly_dst); // some modification of POLY_FT4 tag?
    }

    poly_src = work->field_158;
    poly_dst = &work->field_24->field_40_pBuffers[GV_Clock_800AB920]->poly_ft4;

    for (i = 0; i < 9; poly_dst++, poly_src++, i++)
    {
        *poly_dst = *poly_src;
        SSTOREL(work->field_40[i], poly_dst); // some modification of POLY_FT4 tag?
    }
}

static inline int get_color(int shade)
{
    return (shade << 10) | (shade << 5) | shade;
}

static inline int get_shade(PreMet1Work *work)
{
    int shade = work->field_64 * 25;
    return shade / 16;
}

void PreMet1_800C5CE4(PreMet1Work *work)
{
    int                  i;
    unsigned short       flags;
    PreMet1SubWork_8000 *field_8000;

    flags = work->field_2C0[1];

    switch (work->field_2C8)
    {
    case 0:
        if (work->field_64 == 16)
        {
            work->field_64 = 0;
            work->field_2C8 = 1;
            PreMet1_800C57B4(work, 30, 86, 16, 14, 0xFF, 1);
        }
        break;
    case 1:
        if (flags & 0x8000)
        {
            work->field_2C8 = 2;
            PreMet1_800C57B4(work, -46, 86, 16, 14, 0xFF, 1);
            GM_SeSet2_80032968(0, 0x3F, 0x1F);
        }
        else if (flags & 0x2000)
        {
            work->field_2C8 = 3;
            PreMet1_800C57B4(work, 90, 87, 54, 12, 0xFF, 1);
            GM_SeSet2_80032968(0, 0x3F, 0x1F);
        }
        else if (flags & 0x28)
        {
            if (work->field_2CC != 9)
            {
                work->field_2C8 = 4;
                GM_SeSet2_80032968(0, 0x3F, 0xB0);
                work->field_64 = 0;
            }
        }
        else if (flags & 4)
        {
            if (work->field_2CC != 1)
            {
                work->field_2C8 = 5;
                PreMet1_800C57B4(work, -46, 86, 16, 14, 0xFF, 1);
                GM_SeSet2_80032968(0, 0x3F, 0xB0);
                work->field_64 = 0;
            }
        }
        else if (!(flags & 0x40))
        {
            if (flags & 0x100)
            {
                field_8000 = &work->field_8000;
                if (field_8000->field_9598 == 0)
                {
                    field_8000->field_9598 = 1;
                }
                else
                {
                    field_8000->field_9598 = 0;
                }
            }
        }
        else
        {
            *work->field_2C4 = 1;
            work->field_64 = 0;
            PreMet1_800C5794(work);
            GM_SeSet2_80032968(0, 0x3F, 0x21);
        }
        break;
    case 2:
        if (!(flags & 0x2000))
        {
            if (flags & 0x24)
            {
                if (work->field_2CC != 1)
                {
                    work->field_2C8 = 5;
                    GM_SeSet2_80032968(0, 0x3F, 0xB0);
                    work->field_64 = 0;
                }
            }
            else if (!(flags & 8))
            {
                if (!(flags & 0x40))
                {
                    if (flags & 0x100)
                    {
                        field_8000 = &work->field_8000;
                        if (field_8000->field_9598 == 0)
                        {
                            field_8000->field_9598 = 1;
                        }
                        else
                        {
                            field_8000->field_9598 = 0;
                        }
                    }
                }
                else
                {
                    *work->field_2C4 = 1;
                    work->field_64 = 0;
                    PreMet1_800C5794(work);
                    GM_SeSet2_80032968(0, 0x3F, 0x21);
                }
            }
            else if (work->field_2CC != 9)
            {
                work->field_2C8 = 4;
                GM_SeSet2_80032968(0, 0x3F, 0xB0);
                work->field_64 = 0;
                PreMet1_800C57B4(work, 30, 86, 16, 14, 0xFF, 1);
            }
        }
        else
        {
            work->field_2C8 = 1;
            PreMet1_800C57B4(work, 30, 86, 16, 14, 0xFF, 1);
            GM_SeSet2_80032968(0, 0x3F, 0x1F);
        }
        break;
    case 4:
        if (work->field_64 < 9)
        {
            work->field_8000.field_9594 = -(work->field_64 * 40);
        }
        else if (work->field_64 == 9)
        {
            for (i = 0; i < 8; i++)
            {
                PreMet1SetColor_800C5738(work, i, get_color(0));
            }
        }
        else if (work->field_64 == 10)
        {
            work->field_2CC++;
            for (i = 0; i < 8; i++)
            {

                pre_met1_800C4FD4(work, i);
            }
            work->field_8000.field_9598 = 0;
        }
        else if (work->field_64 == 11)
        {
            for (i = 0; i < 8; i++)
            {

                PreMet1SetColor_800C5738(work, i, get_color(25));
            }
        }
        else if (work->field_64 <= 19)
        {
            work->field_8000.field_9594 = (19 - work->field_64) * 40;
        }
        else
        {
            work->field_8000.field_9594 = 0;
            work->field_2C8 = 1;
        }
        break;
    case 5:
        if (work->field_64 < 9)
        {
            work->field_8000.field_9594 = work->field_64 * 40;
        }
        else if (work->field_64 == 9)
        {
            for (i = 0; i < 8; i++)
            {
                PreMet1SetColor_800C5738(work, i, get_color(0));
            }
        }
        else if (work->field_64 == 10)
        {
            work->field_2CC--;
            for (i = 0; i < 8; i++)
            {

                pre_met1_800C4FD4(work, i);
            }
            work->field_8000.field_9598 = 0;
        }
        else if (work->field_64 == 11)
        {
            for (i = 0; i < 8; i++)
            {
                PreMet1SetColor_800C5738(work, i, get_color(25));
            }
        }
        else if (work->field_64 <= 19)
        {
            work->field_8000.field_9594 = -((19 - work->field_64) * 40);
        }
        else
        {
            work->field_8000.field_9594 = 0;
            work->field_2C8 = 2;
        }
        break;
    case 3:
        if (flags & 0x8000)
        {
            work->field_2C8 = 1;
            PreMet1_800C57B4(work, 30, 86, 16, 14, 0xFF, 1);
            GM_SeSet2_80032968(0, 0x3F, 0x1F);
        }
        else if (flags & 0x20)
        {
            *work->field_2C4 = 1;
            work->field_64 = 0;
            PreMet1_800C5794(work);
            GM_SeSet2_80032968(0, 0x3F, 0x21);
        }
        else if (flags & 4)
        {
            if (work->field_2CC != 1)
            {
                work->field_2C8 = 5;
                GM_SeSet2_80032968(0, 0x3F, 0xB0);
                PreMet1_800C57B4(work, -46, 86, 16, 14, 0xFF, 1);
                work->field_64 = 0;
            }
        }
        else if (flags & 8)
        {
            if (work->field_2CC != 9)
            {
                work->field_2C8 = 4;
                GM_SeSet2_80032968(0, 0x3F, 0xB0);
                work->field_64 = 0;
                PreMet1_800C57B4(work, 30, 86, 16, 14, 0xFF, 1);
            }
        }
        else if (flags & 0x40)
        {
            *work->field_2C4 = 1;
            work->field_64 = 0;
            PreMet1_800C5794(work);
            GM_SeSet2_80032968(0, 0x3F, 0x21);
        }
        else if (flags & 0x100)
        {
            field_8000 = &work->field_8000;
            if (field_8000->field_9598 == 0)
            {
                field_8000->field_9598 = 1;
            }
            else
            {
                field_8000->field_9598 = 0;
            }
        }
        break;
    }
}

void PreMet1_800C62B0(PreMet1Work *work)
{
    int color;
    int shade, shade2;
    int i;

    if (work->field_2C8 == 0)
    {
        shade2 = get_shade(work);
        shade = get_shade(work); // silly dead code to get a match
        color = get_color(shade2);
    }
    else if (*work->field_2C4 == 1)
    {
        shade2 = 25 - get_shade(work);
        shade = 25 - get_shade(work); // silly dead code to get a match
        color = get_color(shade2);
    }
    else
    {
        shade = 25;
        color = get_color(shade);
    }

    if (work->field_8000.field_9598 == 1)
    {
        shade = 0;
        color = get_color(shade);
    }

    for (i = 0; i < 8; i++)
    {
        PreMet1SetColor_800C5738(work, i, color);
    }
}

void PreMet1_800C63B4(PreMet1Work *work)
{
    int r, g, b;

    if (work->field_2C8 == 0)
    {
        r = work->field_64 * 86 / 16;
        g = work->field_64 * 137 / 16;
        b = work->field_64 * 116 / 16;
    }
    else if (*work->field_2C4 == 1)
    {
        r = 86 - work->field_64 * 86 / 16;
        g = 137 - work->field_64 * 137 / 16;
        b = 116 - work->field_64 * 116 / 16;
    }
    else
    {
        r = 86;
        g = 137;
        b = 116;
    }

    MENU_Locate_80038B34(134, 202, 16);
    MENU_Color_80038B4C(r, g, b);
    MENU_Printf_80038C38("%2d", work->field_2CC);

    MENU_Locate_80038B34(156, 202, 16);
    MENU_Color_80038B4C(r, g, b);
    MENU_Printf_80038C38("/");

    MENU_Locate_80038B34(167, 202, 16);
    MENU_Color_80038B4C(r, g, b);
    MENU_Printf_80038C38("%d", 9);
}

void PreMet1Act_800C65A8(PreMet1Work *work)
{
    if (*work->field_2C4 == 0)
    {
        PreMet1_800C5CE4(work);
    }
    PreMet1_800C62B0(work);
    PreMet1_800C63B4(work);
    pre_met1_800C50D4(work, DG_ChanlOTag(1));
    PreMet1ShadePacks_800C5A98(work);
    work->field_64++;
}

void PreMet1Die_800C6634(PreMet1Work *work)
{
    DG_PRIM *prim;
    int      i;

    prim = work->field_20;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    prim = work->field_24;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    for (i = 0; i < 8; i++)
    {
        GV_FreeMemory_80015FD0(2, PreMet1GetClutBuffer_800C5788(&work->field_2D0[i]));
    }
}

// Duplicate of camera_800CE4F8
void PreMet1_800C66D0(PreMet1Work *work, POLY_FT4 *pPoly, int x0, int y0, int x1, int y1, int semiTrans)
{
    setPolyFT4(pPoly);
    pPoly->r0 = 0x80;
    pPoly->g0 = 0x80;
    pPoly->b0 = 0x80;
    pPoly->x0 = x0;
    pPoly->y0 = y0;
    pPoly->y1 = y0;
    pPoly->x2 = x0;
    pPoly->x1 = x1;
    pPoly->y2 = y1;
    pPoly->x3 = x1;
    pPoly->y3 = y1;
    SetSemiTrans(pPoly, semiTrans);
}

// Duplicate of camera_800CE568
void PreMet1_800C6740(PreMet1Work *work, int hashCode, POLY_FT4 *pPoly, int x0, int y0, int x1, int y1, int semiTrans,
                      int arg9)
{
    DG_TEX *tex;
    PreMet1_800C66D0(work, pPoly, x0, y0, x1, y1, semiTrans);
    tex = DG_GetTexture_8001D830(hashCode);

    if (arg9 == 0)
    {
        int offx, offx2, offx3;
        int offy, offy2;

        offx = tex->field_8_offx;
        offx2 = offx + tex->field_A_width;
        offy = tex->field_9_offy;
        offx3 = offx2 + 1;
        offy2 = offy + tex->field_B_height + 1;

        setUV4(pPoly, offx, offy, offx3, offy, offx, offy2, offx3, offy2);
        pPoly->tpage = tex->field_4_tPage;
        pPoly->clut = tex->field_6_clut;
    }

    else if (arg9 == 1)
    {
        int offx, offx2, offx3;
        int offy, offy2;

        offx = tex->field_8_offx;
        offx2 = offx + tex->field_A_width;
        offy = tex->field_9_offy;
        offx3 = offx2 + 1;
        offy2 = offy + tex->field_B_height;

        setUV4(pPoly, offx, offy, offx3, offy, offx, offy2, offx3, offy2);
        pPoly->tpage = tex->field_4_tPage;
        pPoly->clut = tex->field_6_clut;
    }

    else if (arg9 == 2)
    {
        int offx, offx2;
        int offy, offy2;

        offx = tex->field_8_offx;
        offx2 = offx + tex->field_A_width;
        offy = tex->field_9_offy;
        offy2 = offy + tex->field_B_height + 1;

        setUV4(pPoly, offx, offy, offx2, offy, offx, offy2, offx2, offy2);
        pPoly->tpage = tex->field_4_tPage;
        pPoly->clut = tex->field_6_clut;
    }

    else if (arg9 == 3)
    {
        int offx, offx2;
        int offy, offy2;

        offx = tex->field_8_offx;
        offx2 = offx + tex->field_A_width;
        offy = tex->field_9_offy;
        offy2 = offy + tex->field_B_height;

        setUV4(pPoly, offx, offy, offx2, offy, offx, offy2, offx2, offy2);
        pPoly->tpage = tex->field_4_tPage;
        pPoly->clut = tex->field_6_clut;
    }
}

const char preope_aPreupl_800C91FC[] = "pre_up1_l";
const char preope_aPreupr_800C9208[] = "pre_up_r";
const char preope_aPredownl_800C9214[] = "pre_down_l";
const char preope_aPredownr_800C9220[] = "pre_down_r";
const char preope_aPremetl_800C922C[] = "pre_met1_l";
const char preope_aPremetr_800C9238[] = "pre_met1_r";
const char preope_aCurlu_800C9244[] = "cur_lu";
const char preope_aCurru_800C924C[] = "cur_ru";
const char preope_aCurld_800C9254[] = "cur_ld";
const char preope_aCurrd_800C925C[] = "cur_rd";
const char preope_aCuru_800C9264[] = "cur_u";
const char preope_aCurd_800C926C[] = "cur_d";
const char preope_aCurl_800C9274[] = "cur_l";
const char preope_aCurr_800C927C[] = "cur_r";
const char preope_aCurc_800C9284[] = "cur_c";

#pragma INCLUDE_ASM("asm/overlays/preope/pre_met1_800C68C4.s")
int pre_met1_800C68C4(PreMet1Work *, int, int, int); // PreMet1GetReources_800C68C4

GV_ACT *NewPreMet1_800C6F20(int arg0, int arg1, int arg2)
{
    PreMet1Work *work;

    work = (PreMet1Work *)GV_NewActor_800150E4(5, sizeof(PreMet1Work));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)PreMet1Act_800C65A8,
                                  (TActorFunction)PreMet1Die_800C6634, "pre_met1.c");

        if (pre_met1_800C68C4(work, arg0, arg1, arg2) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
