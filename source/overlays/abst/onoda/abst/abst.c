#include "game/game.h"
#include "libgcl/libgcl.h"

#include <stdio.h>

// FIXME: it's the same struct as in change.c (in change overlay)
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

// FIXME: it's the same struct (but without num) as in preope.c (in preope overlay)
typedef struct _Unknown2
{
    short x, y;
    int   color;
} Unknown2;

typedef struct _Work
{
    /* +0x0000 */ GV_ACT   actor;
    /* +0x0020 */ int      end_proc;
    /* +0x0024 */ GV_PAD  *pad;
    /* +0x0028 */ DG_PRIM *prim1;
    /* +0x002C */ DG_PRIM *prim2;
    /* +0x0030 */ POLY_FT4 polys1[6];
    /* +0x0120 */ POLY_FT4 polys2[9];
    /* +0x0288 */ int      attrs1[6]; /* new name needed */
    /* +0x02A0 */ int      attrs2[9]; /* new name needed */
    /* +0x02C4 */ int      field_2C4;
    /* +0x02C8 */ KCB      kcb[12];
    /* +0x04D8 */ char     pad1[0x14];
    /* +0x04EC */ DR_TPAGE tpage[6];
    /* +0x051C */ Unknown  field_51C[12];
    /* +0x1D4C */ int      font_x;
    /* +0x1D50 */ int      font_y;
    /* +0x1D54 */ int      clut_x;
    /* +0x1D58 */ int      clut_y;
    /* +0x1D5C */ int      field_1D5C;
    /* +0x1D60 */ char     pad3[0x4];
    /* +0x1D64 */ int      field_1D64;
    /* +0x1D68 */ int      field_1D68;
    /* +0x1D6C */ char     pad4[0x20];
    /* +0x1D8C */ MenuPrim primbuf;
    /* +0x1DA0 */ char     field_1DA0[0x2000];
    /* +0x3DA0 */ char     field_3DA0[0x2000];
    /* +0x5DA0 */ int      field_5DA0;
    /* +0x5DA4 */ int      field_5DA4;
} Work;

Unknown2 D_800C3238[] =
{
    {88, 0x00B4, 0x6739},
    {16, 0x0023, 0},
    {16, 0x0036, 0},
    {16, 0x0049, 0},
    {16, 0x005C, 0},
    {16, 0x006F, 0},
    {16, 0x0082, 0},
    {16, 0x0095, 0},
    {16, 0x00A8, 0},
    {16, 0x00BB, 0},
    {16, 0x00CE, 0},
    {16, 0x00E1, 0},
};

signed char D_800C3298[] = {-1, 0, 1, 0, 0, 1, 0, -1};

void func_800C464C(Work *work, int index)
{
    RECT  rect;
    KCB  *kcb;
    void *buf;

    kcb = &work->kcb[index];
    
    rect.x = work->font_x;
    rect.y = work->font_y;
    rect.w = 128;
    rect.h = 21;
    
    work->field_51C[index].x0 = work->font_x;
    work->field_51C[index].y0 = work->font_y;

    work->field_51C[index].x1 = work->font_x + 64;
    work->field_51C[index].y1 = work->font_y;
    work->font_y += 21;

    font_init_kcb(kcb, &rect, work->clut_x, work->clut_y);
    
    work->field_51C[index].cx = work->clut_x;
    work->field_51C[index].cy = work->clut_y;
    work->clut_y += 21;

    font_set_kcb(kcb, -1, -1, 0, 6, 2, 0);

    buf = GV_AllocMemory(GV_NORMAL_MEMORY, font_get_buffer_size(kcb));
    font_set_buffer(kcb, buf);

    font_set_color(kcb, 0, D_800C3238[index].color, 0);
    font_clut_update(kcb);
}

void func_800C47A8(Work *work, int index)
{
    KCB *kcb;

    if (work->field_51C[index].string)
    {
        kcb = &work->kcb[index];
        font_print_string(kcb, work->field_51C[index].string);
        font_update(kcb);
        font_clut_update(kcb);

        work->field_51C[index].unk1 = 256;
        work->field_51C[index].unk2 = kcb->max_height;
        
        work->field_51C[index].rect.x = D_800C3238[index].x;
        work->field_51C[index].rect.y = D_800C3238[index].y;

        work->field_51C[index].unk3 = 256;
        work->field_51C[index].unk4 = kcb->max_height;
        
        work->field_51C[index].rect.w = D_800C3238[index].x + 256;
        work->field_51C[index].rect.h = D_800C3238[index].y;

        work->field_51C[index].string = NULL;
        work->field_51C[index].num = 1;
    }
}

void func_800C4890(Work *work, u_long *ot, int arg2)
{
    int       i, j;
    SPRT     *sprt;
    DR_TPAGE *tpage;
    int       index;
    SPRT     *sprt1;
    SPRT     *sprt2;

    index = 0;
    for (i = 0; i < work->field_2C4 + 3; i++)
    {
        if (work->field_51C[index].num == 1)
        {
            sprt = &work->field_51C[index].text_sprt[GV_Clock];
            setSprt(sprt);
            setRGB0(sprt, 128, 128, 128);
            setSemiTrans(sprt, 1);
            LCOPY(&work->field_51C[index].rect.x, &sprt->x0);
            LCOPY(&work->field_51C[index].unk1, &sprt->w);
            setUV0(sprt, 0, work->field_51C[index].y0);
            setClut(sprt, work->field_51C[index].cx, work->field_51C[index].cy);
            addPrim(ot, sprt);
            index++;
        }
    }

    tpage = &work->tpage[0];
    setDrawTPage(tpage, 1, 0, getTPage(0, 1, 704, 256));
    addPrim(ot, tpage);

    index = 0;
    for (i = 0; i < work->field_2C4 + 3; i++)
    {
        if (work->field_51C[index].num == 1)
        {
            sprt = &work->field_51C[index].text_sprt2[GV_Clock];
            setSprt(sprt);
            setRGB0(sprt, 128, 128, 128);
            setSemiTrans(sprt, 1);
            LCOPY(&work->field_51C[index].rect.w, &sprt->x0);
            LCOPY(&work->field_51C[index].unk3, &sprt->w);
            setUV0(sprt, 0, work->field_51C[index].y1);
            setClut(sprt, work->field_51C[index].cx, work->field_51C[index].cy);
            addPrim(ot, sprt);
            index++;
        }
    }

    tpage = &work->tpage[1];
    setDrawTPage(tpage, 1, 0, getTPage(0, 1, 768, 256));
    addPrim(ot, tpage);

    index = 0;
    for (i = 0; i < work->field_2C4 + 3; i++)
    {
        if (work->field_51C[index].num == 1)
        {        
            sprt = &work->field_51C[index].text_sprt3[GV_Clock];
            setSprt(sprt);
            setRGB0(sprt, 128, 128, 128);
            setSemiTrans(sprt, 1);
            LCOPY(&work->field_51C[index].rect.x, &sprt->x0);
            LCOPY(&work->field_51C[index].unk1, &sprt->w);
            setUV0(sprt, 0, work->field_51C[index].y0);
            setClut(sprt, work->field_51C[index].cx, work->field_51C[index].cy);
            addPrim(ot, sprt);
            index++;
        }
    }

    tpage = &work->tpage[4];
    setDrawTPage(tpage, 1, 0, getTPage(0, 2, 704, 256));
    addPrim(ot, tpage);

    index = 0;
    for (i = 0; i < work->field_2C4 + 3; i++)
    {
        if (work->field_51C[index].num == 1)
        {        
            sprt = &work->field_51C[index].text_sprt4[GV_Clock];
            setSprt(sprt);
            setRGB0(sprt, 128, 128, 128);
            setSemiTrans(sprt, 1);
            LCOPY(&work->field_51C[index].rect.w, &sprt->x0);
            LCOPY(&work->field_51C[index].unk3, &sprt->w);
            setUV0(sprt, 0, work->field_51C[index].y1);
            setClut(sprt, work->field_51C[index].cx, work->field_51C[index].cy);
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
        for (i = 0; i < work->field_2C4 + 3; i++)
        {
            if (work->field_51C[index].num == 1)
            {
                sprt2 = work->field_51C[index].text_sprt_outline[GV_Clock];
                sprt1 = &work->field_51C[index].text_sprt[GV_Clock];

                for (j = 0; j < 8; j += 2)
                {
                    *sprt2 = *sprt1;
                    setSprt(sprt2);
                    setRGB0(sprt2, 128, 128, 128);
                    setSemiTrans(sprt2, 1);
                    sprt2->x0 += D_800C3298[j];
                    sprt2->y0 += D_800C3298[j + 1];
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
        for (i = 0; i < work->field_2C4 + 3; i++)
        {
            if (work->field_51C[index].num == 1)
            {
                sprt2 = work->field_51C[index].text_sprt_outline2[GV_Clock];
                sprt1 = &work->field_51C[index].text_sprt2[GV_Clock];

                for (j = 0; j < 8; j += 2, sprt++)
                {
                    *sprt2 = *sprt1;
                    setSprt(sprt2);
                    setRGB0(sprt2, 128, 128, 128);
                    setSemiTrans(sprt2, 1);
                    sprt2->x0 += D_800C3298[j];
                    sprt2->y0 += D_800C3298[j + 1];
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

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C5198.s")
void abst_800C5198(Work *work, int index, int col);

void *abst_800C51E8(KCB *kcb)
{
    return kcb->cbuffer;
}

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C51F4.s")
void abst_800C51F4(Work *work);

#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C5318.s")
void abst_800C5318(MenuPrim *prim, int x, int y, int w, int h);

void func_800C5410(Work *work)
{
    int       press;
    int       i;
    int       r, g, b;
    POLY_FT4 *poly;
    int       shade;
    int       col;

    press = work->pad->press;

    work->primbuf.next = work->primbuf.buf[GV_Clock];
    work->primbuf.ot = DG_Chanl(1)->ot[GV_Clock];

    switch (work->field_1D64)
    {
    case 0:
        if (work->field_1D5C < 5)
        {
            MENU_Locate(90, 90, 0x10);
            MENU_Color(192, 192, 192);
            MENU_Printf("READ MISSION LOG?");

            abst_800C5318(&work->primbuf, 92, 85, 130, 15);
        }
        else if (work->field_1D5C < 10)
        {
            MENU_Locate(90, 90 - (work->field_1D5C - 4) * 8, 0x10);
            MENU_Color(192, 192, 192);
            MENU_Printf("READ MISSION LOG?");

            abst_800C5318(&work->primbuf, 92, 85, 130, 15);
        }
        else if (work->field_1D5C == 10)
        {
            MENU_Locate(90, 50, 0x10);
            MENU_Color(86, 137, 116);
            MENU_Printf("READ MISSION LOG?");

            MENU_Locate(100, 105, 0x10);
            MENU_Color(192, 192, 192);
            MENU_Printf("YES");

            MENU_Locate(200, 105, 0x10);
            MENU_Color(46, 72, 61);
            MENU_Printf("NO");

            abst_800C5318(&work->primbuf, 92, 85, 130, 15);
        }
        else if (work->field_1D5C < 14)
        {
            MENU_Locate(90, 50, 0x10);
            MENU_Color(86, 137, 116);
            MENU_Printf("READ MISSION LOG?");

            MENU_Locate(100, 105, 0x10);
            MENU_Color(192, 192, 192);
            MENU_Printf("YES");

            MENU_Locate(200, 105, 0x10);
            MENU_Color(46, 72, 61);
            MENU_Printf("NO");

            abst_800C5318(&work->primbuf, 92, (work->field_1D5C - 10) * 5 + 85, 130 - (work->field_1D5C - 10) * 30, 15);
        } else {
            MENU_Locate(90, 50, 0x10);
            MENU_Color(86, 137, 116);
            MENU_Printf("READ MISSION LOG?");

            MENU_Locate(100, 105, 0x10);
            if (work->field_1D68 == 0)
            {
                MENU_Color(192, 192, 192);
            }
            else
            {
                MENU_Color(46, 72, 61);
            }
            MENU_Printf("YES");

            MENU_Locate(200, 105, 0x10);
            if (work->field_1D68 == 1)
            {
                MENU_Color(192, 192, 192);
            }
            else
            {
                MENU_Color(46, 72, 61);
            }
            MENU_Printf("NO");

            if (work->field_1D68 == 0)
            {
                abst_800C5318(&work->primbuf, 92, 100, 40, 15);
            }
            else
            {
                abst_800C5318(&work->primbuf, 188, 100, 40, 15);
            }

            if (press & (PAD_START | PAD_CIRCLE))
            {
                if (work->field_1D68 == 0)
                {
                    GM_SeSet2(0, 63, SE_MENU_SELECT);

                    work->field_1D64 = 1;

                    for (i = 0; i < 6; i++)
                    {
                        work->attrs1[i] = 0x100;
                    }
                    
                    work->field_1D5C = 0;

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
                        abst_800C5198(work, i, 0);
                    }

                    for (i = 0; i < 9; i++)
                    {
                        work->attrs2[i] = 0x200;
                    }

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

                if (work->field_1D68 == 0)
                {
                    work->field_1D68 = 1;
                }
                else
                {
                    work->field_1D68 = 0;
                }
            }

            work->field_5DA0 = 1;
        }

        work->field_1D5C++;
        break;
    case 1:
        if (work->field_1D5C < 9)
        {
            poly = work->polys2;
            shade = (work->field_1D5C * 255) / 8;
            for (i = 0; i < 9; i++)
            {
                setRGB0(poly, shade, shade, shade);
                poly++;
            }

            poly = work->polys1;
            r = (work->field_1D5C * 86) / 64;
            g = (work->field_1D5C * 137) / 64;
            b = (work->field_1D5C * 116) / 64;
            for (i = 0; i < 2; i++)
            {
                setRGB0(poly, r, g, b);
                poly++;
            }

            col = 0;
            for (i = 1; i < work->field_2C4 + 1; i++)
            {
                abst_800C5198(work, i, col);
            }

            work->field_1D5C++;
        }
        else if (work->field_1D5C < 65)
        {
            poly = work->polys1;
            r = (work->field_1D5C * 86) / 64;
            g = (work->field_1D5C * 137) / 64;
            b = (work->field_1D5C * 116) / 64;
            for (i = 0; i < 2; i++)
            {
                setRGB0(poly, r, g, b);
                poly++;
            }

            col = 0;
            for (i = 1; i < work->field_2C4 + 1; i++)
            {
                abst_800C5198(work, i, col);
            }

            work->field_1D5C++;
        }
        else if (work->field_1D5C < 81)
        {
            poly = work->polys1;
            r = 86;
            g = 137;
            b = 116;
            for (i = 0; i < 6; i++)
            {
                setRGB0(poly, r, g, b);
                poly++;
            }

            col = 0;
            for (i = 1; i < work->field_2C4 + 1; i++)
            {
                abst_800C5198(work, i, col);
            }

            work->field_1D5C++;
        }
        else if (work->field_1D5C < 145)
        {
            poly = work->polys1;
            r = 86;
            g = 137;
            b = 116;
            for (i = 0; i < 6; i++)
            {
                setRGB0(poly, r, g, b);
                poly++;
            }

            shade = ((work->field_1D5C - 80) * 25) / 64;
            col = (shade << 10) | (shade << 5) | shade;
            for (i = 1; i < work->field_2C4 + 1; i++)
            {
                abst_800C5198(work, i, col);
            }

            if (++work->field_1D5C < 89)
            {
                work->field_5DA0 = 0;
            }
            else
            {
                work->field_5DA0 = 1;
            }
        }
        else
        {
            work->field_1D64 = 2;
            work->field_5DA0 = 1;
        }
        break;

    case 2:
        if (press & PAD_SELECT)
        {
            if (work->field_5DA4 == 0)
            {
                work->field_5DA4 = 1;
                for (i = 1; i < work->field_2C4 + 1; i++)
                {
                    abst_800C5198(work, i, 0);
                }
            }
            else 
            {
                work->field_5DA4 = 0;
                for (i = 1; i < work->field_2C4 + 1; i++)
                {
                    abst_800C5198(work, i, 0x6739);
                }
            }
        }
        else if (press & (PAD_CROSS | PAD_CIRCLE))
        {
            GM_SeSet2(0, 63, SE_MENU_EXIT);
            work->field_1D64 = 3;
            work->field_1D5C = 0;
        }
        break;
    case 3:        
        if (work->field_1D5C < 97)
        {
            if (work->field_1D5C < 9)
            {
                poly = work->polys2;
                shade = 255 - (work->field_1D5C * 255) / 8;
                for (i = 0; i < 9; i++)
                {
                    setRGB0(poly, shade, shade, shade);
                    poly++;
                }
            }

            poly = work->polys1;
            r = 86 - (work->field_1D5C * 86) / 96;
            g = 137 - (work->field_1D5C * 137) / 96;
            b = 116 - (work->field_1D5C * 116) / 96;
            for (i = 0; i < 6; i++)
            {
                setRGB0(poly, r, g, b);
                poly++;
            }

            shade = 25 - (work->field_1D5C * 25) / 96;
            col = (shade << 10) | (shade << 5) | shade;
            for (i = 1; i < work->field_2C4 + 1; i++)
            {
                abst_800C5198(work, i, col);
            }

            if (work->field_5DA4 == 1)
            {
                for (i = 1; i < work->field_2C4 + 1; i++)
                {
                    abst_800C5198(work, i, 0);
                }
            }

            work->field_1D5C++;
        }
        else
        {
            GCL_ExecProc(work->end_proc, NULL);
            GV_DestroyActor(work);
        }
        break;
    }

    func_800C4890(work, DG_Chanl(1)->ot[GV_Clock], work->field_5DA0);
    abst_800C51F4(work);
}

void func_800C5F8C(Work *work)
{
    int   i;
    void *buf;

    GM_FreePrim(work->prim1);
    GM_FreePrim(work->prim2);
    
    for (i = 0; i < 12; i++)
    {
        buf = abst_800C51E8(&work->kcb[i]);
        GV_FreeMemory(GV_NORMAL_MEMORY, buf);
    }
}

// TODO: convert to struct array
int abst_dword_800C32A0 = 0x00000FD3;
int abst_dword_800C32A4 = 0x00000837;
int abst_dword_800C32A8 = 0x00002657;
int abst_dword_800C32AC = 0x00000FD9;
int abst_dword_800C32B0 = 0x0000083C;
int abst_dword_800C32B4 = 0x00002E07;
int abst_dword_800C32B8 = 0x000061D1;
int abst_dword_800C32BC = 0x00000842;
int abst_dword_800C32C0 = 0x000017D6;
int abst_dword_800C32C4 = 0x000061D7;
int abst_dword_800C32C8 = 0x00000845;
int abst_dword_800C32CC = 0x00002478;
int abst_dword_800C32D0 = 0x000088D4;
int abst_dword_800C32D4 = 0x0000084A;
int abst_dword_800C32D8 = 0x0000276E;
int abst_dword_800C32DC = 0x000088DA;
int abst_dword_800C32E0 = 0x0000084F;
int abst_dword_800C32E4 = 0x00000544;
int abst_dword_800C32E8 = 0x000035A6;
int abst_dword_800C32EC = 0x00000850;
int abst_dword_800C32F0 = 0x000021E8;
int abst_dword_800C32F4 = 0x000035AC;
int abst_dword_800C32F8 = 0x00000855;
int abst_dword_800C32FC = 0x000025DB;
int abst_dword_800C3300 = 0x000059BF;
int abst_dword_800C3304 = 0x0000085A;
int abst_dword_800C3308 = 0x00002D5A;
int abst_dword_800C330C = 0x000059C5;
int abst_dword_800C3310 = 0x00000860;
int abst_dword_800C3314 = 0x000006DF;
int abst_dword_800C3318 = 0x0000D1AF;
int abst_dword_800C331C = 0x00000861;
int abst_dword_800C3320 = 0x000026FD;
int abst_dword_800C3324 = 0x0000D1B5;
int abst_dword_800C3328 = 0x00000866;
int abst_dword_800C332C = 0x000026C0;
int abst_dword_800C3330 = 0x0000AD18;
int abst_dword_800C3334 = 0x0000086B;
int abst_dword_800C3338 = 0x00002467;
int abst_dword_800C333C = 0x0000AD1E;
int abst_dword_800C3340 = 0x00000870;
int abst_dword_800C3344 = 0x00001890;
int abst_dword_800C3348 = 0x00000F8F;
int abst_dword_800C334C = 0x00000874;
int abst_dword_800C3350 = 0x0000188C;
int abst_dword_800C3354 = 0x00000F95;
int abst_dword_800C3358 = 0x00000878;
int abst_dword_800C335C = 0x00002CC3;
int abst_dword_800C3360 = 0x0000335B;
int abst_dword_800C3364 = 0x0000087E;
int abst_dword_800C3368 = 0x0000255C;
int abst_dword_800C336C = 0x00003361;
int abst_dword_800C3370 = 0x00000883;
int abst_dword_800C3374 = 0x000021BE;
int abst_dword_800C3378 = 0x000093D1;
int abst_dword_800C337C = 0x00000888;
int abst_dword_800C3380 = 0x000026D9;
int abst_dword_800C3384 = 0x000093D7;
int abst_dword_800C3388 = 0x0000088D;
int abst_dword_800C338C = 0x00002824;
int abst_dword_800C3390 = 0x000094D4;
int abst_dword_800C3394 = 0x00000893;
int abst_dword_800C3398 = 0x000024D9;
int abst_dword_800C339C = 0x000094DA;
int abst_dword_800C33A0 = 0x00000898;
int abst_dword_800C33A4 = 0x0000304C;
int abst_dword_800C33A8 = 0x0000494D;
int abst_dword_800C33AC = 0x0000089F;
int abst_dword_800C33B0 = 0x00001AB5;
int abst_dword_800C33B4 = 0x00004953;
int abst_dword_800C33B8 = 0x000008A3;
int abst_dword_800C33BC = 0x00002546;
int abst_dword_800C33C0 = 0x00004DBE;
int abst_dword_800C33C4 = 0x000008A8;
int abst_dword_800C33C8 = 0x000027B1;
int abst_dword_800C33CC = 0x00004DC4;
int abst_dword_800C33D0 = 0x000008AD;
int abst_dword_800C33D4 = 0x00001D11;
int abst_dword_800C33D8 = 0x000018A3;
int abst_dword_800C33DC = 0x000008B1;
int abst_dword_800C33E0 = 0x00001928;
int abst_dword_800C33E4 = 0x000018A9;
int abst_dword_800C33E8 = 0x000008B5;
int abst_dword_800C33EC = 0x00002EB7;
int abst_dword_800C33F0 = 0x000086E7;
int abst_dword_800C33F4 = 0x000008BB;
int abst_dword_800C33F8 = 0x0000209B;
int abst_dword_800C33FC = 0x000086ED;
int abst_dword_800C3400 = 0x000008C0;
int abst_dword_800C3404 = 0x000021AA;
int abst_dword_800C3408 = 0x00005E14;
int abst_dword_800C340C = 0x000008C5;
int abst_dword_800C3410 = 0x00002CD1;
int abst_dword_800C3414 = 0x00005E1A;
int abst_dword_800C3418 = 0x000008CB;
int abst_dword_800C341C = 0x000029B9;
int abst_dword_800C3420 = 0x000069AB;
int abst_dword_800C3424 = 0x000008D1;
int abst_dword_800C3428 = 0x000031FB;
int abst_dword_800C342C = 0x000069B1;
int abst_dword_800C3430 = 0x000008D8;
int abst_dword_800C3434 = 0x000034F1;
int abst_dword_800C3438 = 0x00008115;
int abst_dword_800C343C = 0x000008DF;
int abst_dword_800C3440 = 0x00002CCC;
int abst_dword_800C3444 = 0x0000811B;
int abst_dword_800C3448 = 0x000008E5;
int abst_dword_800C344C = 0x000020D7;
int abst_dword_800C3450 = 0x0000CE7C;
int abst_dword_800C3454 = 0x000008EA;
int abst_dword_800C3458 = 0x000020BD;
int abst_dword_800C345C = 0x0000CE82;
int abst_dword_800C3460 = 0x000008EF;
int abst_dword_800C3464 = 0x00002345;
int abst_dword_800C3468 = 0x00007990;
int abst_dword_800C346C = 0x000008F4;
int abst_dword_800C3470 = 0x000029C8;
int abst_dword_800C3474 = 0x00007996;
int abst_dword_800C3478 = 0x000008FA;
int abst_dword_800C347C = 0x0000221E;
int abst_dword_800C3480 = 0x0000B0A2;
int abst_dword_800C3484 = 0x000008FF;
int abst_dword_800C3488 = 0x00001E4A;
int abst_dword_800C348C = 0x0000B0A8;
int abst_dword_800C3490 = 0x00000903;
int abst_dword_800C3494 = 0x00002848;
int abst_dword_800C3498 = 0x00009166;
int abst_dword_800C349C = 0x00000909;
int abst_dword_800C34A0 = 0x00001AE9;
int abst_dword_800C34A4 = 0x0000916C;
int abst_dword_800C34A8 = 0x0000090D;
int abst_dword_800C34AC = 0x00002EA3;
int abst_dword_800C34B0 = 0x00004B62;
int abst_dword_800C34B4 = 0x00000913;
int abst_dword_800C34B8 = 0x000028A1;
int abst_dword_800C34BC = 0x00004B68;
int abst_dword_800C34C0 = 0x00000919;
int abst_dword_800C34C4 = 0x00000E9B;
int abst_dword_800C34C8 = 0x0000AFBE;
int abst_dword_800C34CC = 0x0000091B;
int abst_dword_800C34D0 = 0x00001F90;
int abst_dword_800C34D4 = 0x0000AFC4;
int abst_dword_800C34D8 = 0x0000091F;
int abst_dword_800C34DC = 0x00001770;
int abst_dword_800C34E0 = 0x0000104B;
int abst_dword_800C34E4 = 0x00000922;
int abst_dword_800C34E8 = 0x000027E7;
int abst_dword_800C34EC = 0x00001051;
int abst_dword_800C34F0 = 0x00000927;
int abst_dword_800C34F4 = 0x000012C2;
int abst_dword_800C34F8 = 0x0000A854;
int abst_dword_800C34FC = 0x0000092A;
int abst_dword_800C3500 = 0x00001B64;
int abst_dword_800C3504 = 0x0000A85A;
int abst_dword_800C3508 = 0x0000092E;
int abst_dword_800C350C = 0x00001777;
int abst_dword_800C3510 = 0x0000844F;
int abst_dword_800C3514 = 0x00000931;
int abst_dword_800C3518 = 0x00002DB4;
int abst_dword_800C351C = 0x00008455;
int abst_dword_800C3520 = 0x00000937;
int abst_dword_800C3524 = 0x00002931;
int abst_dword_800C3528 = 0x00008DFD;
int abst_dword_800C352C = 0x0000093D;
int abst_dword_800C3530 = 0x0000278A;
int abst_dword_800C3534 = 0x00008E03;
int abst_dword_800C3538 = 0x00000942;
int abst_dword_800C353C = 0x000021A7;
int abst_dword_800C3540 = 0x0000B2D9;
int abst_dword_800C3544 = 0x00000947;
int abst_dword_800C3548 = 0x0000199D;
int abst_dword_800C354C = 0x0000B2DF;
int abst_dword_800C3550 = 0x0000094B;
int abst_dword_800C3554 = 0x00002A45;
int abst_dword_800C3558 = 0x00008B76;
int abst_dword_800C355C = 0x00000951;
int abst_dword_800C3560 = 0x000027C5;
int abst_dword_800C3564 = 0x00008B7C;
int abst_dword_800C3568 = 0x00000956;
int abst_dword_800C356C = 0x00000F3C;
int abst_dword_800C3570 = 0x0000C2B0;
int abst_dword_800C3574 = 0x00000958;
int abst_dword_800C3578 = 0x00001E66;
int abst_dword_800C357C = 0x0000C2B6;
int abst_dword_800C3580 = 0x0000095C;
int abst_dword_800C3584 = 0x00001F25;
int abst_dword_800C3588 = 0x0000D28A;
int abst_dword_800C358C = 0x00000960;
int abst_dword_800C3590 = 0x00002DDE;
int abst_dword_800C3594 = 0x0000D290;
int abst_dword_800C3598 = 0x00000966;
int abst_dword_800C359C = 0x000015CB;
int abst_dword_800C35A0 = 0x00001695;
int abst_dword_800C35A4 = 0x00000969;
int abst_dword_800C35A8 = 0x000020EE;
int abst_dword_800C35AC = 0x0000169B;
int abst_dword_800C35B0 = 0x0000096E;
int abst_dword_800C35B4 = 0x00000D3D;
int abst_dword_800C35B8 = 0x00007F45;
int abst_dword_800C35BC = 0x00000970;
int abst_dword_800C35C0 = 0x000014B9;
int abst_dword_800C35C4 = 0x00007F4B;
int abst_dword_800C35C8 = 0x00000973;
int abst_dword_800C35CC = 0x00002D84;
int abst_dword_800C35D0 = 0x0000CBCC;
int abst_dword_800C35D4 = 0x00000979;
int abst_dword_800C35D8 = 0x00002011;
int abst_dword_800C35DC = 0x0000CBD2;
int abst_dword_800C35E0 = 0x0000097E;
int abst_dword_800C35E4 = 0x00002044;
int abst_dword_800C35E8 = 0x0000A02C;
int abst_dword_800C35EC = 0x00000983;
int abst_dword_800C35F0 = 0x000028CF;
int abst_dword_800C35F4 = 0x0000A032;
int abst_dword_800C35F8 = 0x00000989;
int abst_dword_800C35FC = 0x000028EB;
int abst_dword_800C3600 = 0x00009664;
int abst_dword_800C3604 = 0x0000098F;
int abst_dword_800C3608 = 0x00002D22;
int abst_dword_800C360C = 0x0000966A;
int abst_dword_800C3610 = 0x00000995;
int abst_dword_800C3614 = 0x000020C4;
int abst_dword_800C3618 = 0x00001953;
int abst_dword_800C361C = 0x0000099A;
int abst_dword_800C3620 = 0x000028E7;
int abst_dword_800C3624 = 0x00001959;
int abst_dword_800C3628 = 0x000009A0;
int abst_dword_800C362C = 0x00003932;
int abst_dword_800C3630 = 0x00006B08;
int abst_dword_800C3634 = 0x000009A8;
int abst_dword_800C3638 = 0x000030AD;
int abst_dword_800C363C = 0x00006B0E;
int abst_dword_800C3640 = 0x000009AF;
int abst_dword_800C3644 = 0x0000252C;
int abst_dword_800C3648 = 0x0000876C;
int abst_dword_800C364C = 0x000009B4;
int abst_dword_800C3650 = 0x00001EB8;
int abst_dword_800C3654 = 0x00008772;
int abst_dword_800C3658 = 0x000009B8;
int abst_dword_800C365C = 0x00002582;
int abst_dword_800C3660 = 0x0000FC00;
int abst_dword_800C3664 = 0x000009BD;
int abst_dword_800C3668 = 0x00002AD0;
int abst_dword_800C366C = 0x0000FC06;
int abst_dword_800C3670 = 0x000009C3;
int abst_dword_800C3674 = 0x00002631;
int abst_dword_800C3678 = 0x00006975;
int abst_dword_800C367C = 0x000009C8;
int abst_dword_800C3680 = 0x00002B8E;
int abst_dword_800C3684 = 0x0000697B;
int abst_dword_800C3688 = 0x000009CE;
int abst_dword_800C368C = 0x00002DAE;
int abst_dword_800C3690 = 0x0000783A;
int abst_dword_800C3694 = 0x000009D4;
int abst_dword_800C3698 = 0x0000260B;
int abst_dword_800C369C = 0x00007840;
int abst_dword_800C36A0 = 0x000009D9;
int abst_dword_800C36A4 = 0x000024FD;
int abst_dword_800C36A8 = 0x00009181;
int abst_dword_800C36AC = 0x000009DE;
int abst_dword_800C36B0 = 0x00001CBF;
int abst_dword_800C36B4 = 0x00009187;
int abst_dword_800C36B8 = 0x000009E2;
int abst_dword_800C36BC = 0x000029C6;
int abst_dword_800C36C0 = 0x00009295;
int abst_dword_800C36C4 = 0x000009E8;
int abst_dword_800C36C8 = 0x0000232F;
int abst_dword_800C36CC = 0x0000929B;
int abst_dword_800C36D0 = 0x000009ED;
int abst_dword_800C36D4 = 0x00001AF0;
int abst_dword_800C36D8 = 0x00007953;
int abst_dword_800C36DC = 0x000009F1;
int abst_dword_800C36E0 = 0x00002862;
int abst_dword_800C36E4 = 0x00007959;
int abst_dword_800C36E8 = 0x000009F7;
int abst_dword_800C36EC = 0x000006F8;
int abst_dword_800C36F0 = 0x00005083;
int abst_dword_800C36F4 = 0x000009F8;
int abst_dword_800C36F8 = 0x00002902;
int abst_dword_800C36FC = 0x00005089;
int abst_dword_800C3700 = 0x000009FE;
int abst_dword_800C3704 = 0x00001801;
int abst_dword_800C3708 = 0x0000F1E2;
int abst_dword_800C370C = 0x00000A02;
int abst_dword_800C3710 = 0x00000F72;
int abst_dword_800C3714 = 0x0000F1E8;
int abst_dword_800C3718 = 0x00000A04;
int abst_dword_800C371C = 0x000025C2;
int abst_dword_800C3720 = 0x00002EC5;
int abst_dword_800C3724 = 0x00000A09;
int abst_dword_800C3728 = 0x00002DE5;
int abst_dword_800C372C = 0x00002ECB;
int abst_dword_800C3730 = 0x00000A0F;
int abst_dword_800C3734 = 0x00001EAC;
int abst_dword_800C3738 = 0x00002F87;
int abst_dword_800C373C = 0x00000A13;
int abst_dword_800C3740 = 0x00003148;
int abst_dword_800C3744 = 0x00002F8D;
int abst_dword_800C3748 = 0x00000A1A;
int abst_dword_800C374C = 0x00001FA1;

const char abst_dword_800CE42C[] = "Texture LoadImage Finish!\n";
const char abst_dword_800CE448[] = "Cannot Find Texture\n";
#pragma INCLUDE_ASM("asm/overlays/abst/abst_800C6028.s")
void abst_800C6028(Work *work, int opt);

void func_800C6114(void *work, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe)
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

static void Init_Res(void *work, int name, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe, int mode)
{
    DG_TEX *tex;
    
    func_800C6114(work, poly, x0, y0, x1, y1, abe);
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

static int GetResources(Work *work, int where)
{
    char     *opt;
    POLY_FT4 *poly;
    int       i;

    GM_CurrentMap = where;

    work->font_x = 704;
    work->font_y = 256;
    work->clut_x = 704;
    work->clut_y = 276;

    work->prim1 = GM_MakePrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 6, NULL, NULL);
    work->prim2 = GM_MakePrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 9, NULL, NULL);

    poly = work->polys1;
    i = 0;
    
    opt = GCL_GetOption('l');
    if (opt)
    {
        abst_800C6028(work, GCL_StrToInt(opt));
        Init_Res(work, GCL_StrToInt(opt), poly, -160, -82, 0, 82, 0, 0);
    }
    else
    {
        printf("Cannot Set Texture!!\n");
    }

    poly++;
    work->attrs1[i] = 0;
    i++;
    
    opt = GCL_GetOption('r');
    if (opt)
    {
        abst_800C6028(work, GCL_StrToInt(opt));
        Init_Res(work, GCL_StrToInt(opt), poly, 0, -82, 160, 82, 0, 0);
    }
    else
    {
        printf("Cannot Set Texture!!\n");
    }

    poly++;
    work->attrs1[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("abst_u_l"), poly, -160, -112, 0, -82, 0, 0);

    poly++;
    work->attrs1[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("abst_u_r"), poly, 0, -112, 160, -82, 0, 0);

    poly++;
    work->attrs1[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("abst_d_l"), poly, -160, 82, 0, 112, 1, 0);

    poly++;
    work->attrs1[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("abst_d_r"), poly, 0, 82, 160, 112, 1, 0);

    work->attrs1[i] = 0;

    poly = work->polys2;
    i = 0;

    Init_Res(work, GV_StrCode("cur_lu"), poly, -33, 81, -25, 89, 0, 0);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("cur_ru"), poly, 25, 81, 33, 89, 0, 0);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("cur_ld"), poly, -33, 97, -25, 105, 0, 0);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("cur_rd"), poly, 25, 97, 33, 105, 0, 0);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;
    
    Init_Res(work, GV_StrCode("cur_u"), poly, -25, 81, 25, 89, 0, 2);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("cur_d"), poly, -25, 97, 25, 105, 0, 2);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("cur_l"), poly, -33, 89, -25, 97, 0, 1);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("cur_r"), poly, 25, 89, 33, 97, 0, 1);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    Init_Res(work, GV_StrCode("cur_c"), poly, -25, 89, 25, 97, 0, 3);
    setRGB0(poly, 255, 255, 255);

    poly++;
    work->attrs2[i] = 0;
    i++;

    if (GCL_GetOption('e'))
    {
        work->end_proc = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->end_proc = -1;
    }

    if (GCL_GetOption('i'))
    {
        work->field_2C4 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->field_2C4 = 12;
    }

    for (i = 0; i < work->field_2C4 + 1; i++)
    {
        work->field_51C[i].string = GCL_GetString(GCL_NextStr());
        work->field_51C[i].num = 0;
        func_800C464C(work, i);
    }

    for (i = 0; i < work->field_2C4 + 1; i++)
    {
        func_800C47A8(work, i);
    }
    
    work->pad = &GV_PadData[2];
    work->field_1D5C = 0;
    work->field_1D64 = 0;
    work->field_1D68 = 0;

    for (i = 0; i < 1; i++)
    {
        abst_800C5198(work, i, 0x6739);
    }

    for (i = 1; i < work->field_2C4 + 1; i++)
    {
        abst_800C5198(work, i, 0);
    }

    work->primbuf.buf[0] = work->field_1DA0;
    work->primbuf.buf[1] = work->field_3DA0;

    sub_80048124();
    work->field_5DA4 = 0;
    return 0;
}

void *NewAbstract(int name, int where)
{
    Work *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = GV_NewActor(GV_ACTOR_MANAGER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, func_800C5410, func_800C5F8C, "abst.c");
        if (GetResources(work, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}
