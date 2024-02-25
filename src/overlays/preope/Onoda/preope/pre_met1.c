#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Font/font.h"
#include "Menu/menuman.h"

typedef struct _PreMet1Work
{
    GV_ACT   actor;
    DG_PRIM *field_20;
    DG_PRIM *field_24;
    int      field_28[6];
    int      field_40[9];
    int      field_64;
    POLY_FT4 field_68[6];
    POLY_FT4 field_158[9];
    int      field_2C0;
    int     *field_2C4;
    int      field_2C8;
    int      field_2CC;
    KCB      field_2D0[8];
    char     pad430[0x916C];
} PreMet1Work;

#define EXEC_LEVEL 5

extern char preope_aPremetc_800C928C[];
extern char preope_aD_800C91F0[];
extern char preope_a_800C91F4[];
extern char preope_aD_800C91F8[];

#pragma INCLUDE_ASM("asm/overlays/preope/pre_met1_800C4E40.s")
#pragma INCLUDE_ASM("asm/overlays/preope/pre_met1_800C4F58.s")
#pragma INCLUDE_ASM("asm/overlays/preope/pre_met1_800C4FD4.s")
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

#pragma INCLUDE_ASM("asm/overlays/preope/pre_met1_800C5794.s")

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

#pragma INCLUDE_ASM("asm/overlays/preope/pre_met1_800C5A98.s")
void pre_met1_800C5A98(PreMet1Work *work);

#pragma INCLUDE_ASM("asm/overlays/preope/pre_met1_800C5CE4.s")
void pre_met1_800C5CE4(PreMet1Work *work);

#pragma INCLUDE_ASM("asm/overlays/preope/pre_met1_800C62B0.s")
void pre_met1_800C62B0(PreMet1Work *work);

void PreMet1_800C63B4(PreMet1Work *work)
{
    int r, g, b;

    if (work->field_2C8 == 0)
    {
        r = work->field_64 * 86 / 16;
        g = work->field_64 * 137 / 16;
        b = work->field_64 * 116 / 16;
    }
    else
    {

        if (*work->field_2C4 == 1)
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
    }

    MENU_Locate_80038B34(134, 202, 16);
    MENU_Color_80038B4C(r, g, b);
    MENU_Printf_80038C38(preope_aD_800C91F0, work->field_2CC); // "%2d"

    MENU_Locate_80038B34(156, 202, 16);
    MENU_Color_80038B4C(r, g, b);
    MENU_Printf_80038C38(preope_a_800C91F4); // "/"

    MENU_Locate_80038B34(167, 202, 16);
    MENU_Color_80038B4C(r, g, b);
    MENU_Printf_80038C38(preope_aD_800C91F8, 9); // "%d"
}

void PreMet1Act_800C65A8(PreMet1Work *work)
{
    if (*work->field_2C4 == 0)
    {
        pre_met1_800C5CE4(work);
    }
    pre_met1_800C62B0(work);
    PreMet1_800C63B4(work);
    pre_met1_800C50D4(work, DG_ChanlOTag(1));
    pre_met1_800C5A98(work);
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

#pragma INCLUDE_ASM("asm/overlays/preope/pre_met1_800C68C4.s")
int pre_met1_800C68C4(PreMet1Work *, int, int, int); // PreMet1GetReources_800C68C4

GV_ACT *NewPreMet1_800C6F20(int arg0, int arg1, int arg2)
{
    PreMet1Work *work;

    work = (PreMet1Work *)GV_NewActor_800150E4(5, sizeof(PreMet1Work));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)PreMet1Act_800C65A8,
                                  (TActorFunction)PreMet1Die_800C6634, preope_aPremetc_800C928C);

        if (pre_met1_800C68C4(work, arg0, arg1, arg2) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
