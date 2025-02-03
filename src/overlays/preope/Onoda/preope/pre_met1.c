// CAUTION: this file is nearly identical to pre_met2.c
// If you make any changes, also modify pre_met2.c

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Font/font.h"
#include "Menu/menuman.h"
#include "Game/game.h"
#include "SD/g_sound.h"

#define PAGE_COUNT 9

typedef struct PreMet1Prims
{
    SPRT           field_0[2];
    SPRT           field_28[2][4];
    SPRT           field_C8[2];
    SPRT           field_F0[2][4];
    char           pad190[0x50];
    char          *field_1E0;
    short          field_1E4;
    unsigned short field_1E6;
    short          field_1E8;
    short          field_1EA;
    short          field_1EC;
    short          field_1EE;
    short          field_1F0;
    short          field_1F2;
    unsigned short field_1F4;
    unsigned short field_1F6;
    unsigned short field_1F8;
    unsigned short field_1FA;
    short          field_1FC;
    short          field_1FE;
    short          field_200;
    unsigned short field_202;
} PreMet1Prims;

typedef struct _PreMet1Work
{
    GV_ACT       actor;
    DG_PRIM     *field_20;
    DG_PRIM     *field_24;
    int          field_28[6];
    int          field_40[9];
    int          field_64;
    POLY_FT4     field_68[6];
    POLY_FT4     field_158[9];
    GV_PAD      *field_2C0;
    int         *field_2C4;
    int          field_2C8;
    int          current_page_number;
    KCB          field_2D0[8];
    char         pad430[0x14];
    DR_TPAGE     field_444;
    DR_TPAGE     field_44C;
    DR_TPAGE     field_454;
    DR_TPAGE     field_45C;
    PreMet1Prims field_464[PAGE_COUNT * 8];
    int          field_9584;
    int          field_9588;
    int          field_958C;
    int          field_9590;
    int          field_9594;
    int          field_9598;
} PreMet1Work;

typedef struct PreEntry
{
    char  pad_0[0xC8];
    char *field_C8;
    char  pad_CC[0x14];
} PreEntry;

typedef struct PreEntries
{
    PreEntry entries[8];
} PreEntries;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct PreMet1Unk
{
    short field_0;
    short field_2;
    int   fore_color;
} PreMet1Unk;

PreMet1Unk premet1_800C3250[8] = {
    {0x0010, 0x0023, 0x00000000}, {0x0010, 0x0036, 0x00000000}, {0x0010, 0x0049, 0x00000000},
    {0x0010, 0x005C, 0x00000000}, {0x0010, 0x006F, 0x00000000}, {0x0010, 0x0082, 0x00000000},
    {0x0010, 0x0095, 0x00000000}, {0x0010, 0x00A8, 0x00000000},
};

signed char premet1_800C3290[8] = {-1, 0, 1, 0, 0, 1, 0, -1};

extern int    GV_Clock;
extern GV_PAD GV_PadData_800B05C0[4];

void PreMet1_800C4E40(PreMet1Work *work, int index)
{
    RECT rect;
    KCB *kcb;

    kcb = &work->field_2D0[index];
    rect.x = work->field_9584;
    rect.y = work->field_9588;
    rect.w = 128;
    rect.h = 21;

    work->field_9588 += 21;
    font_init_kcb(kcb, &rect, work->field_958C, work->field_9590);
    work->field_9590 += 21;

    font_set_kcb(kcb, -1, -1, 0, 6, 2, 0);
    font_set_buffer(kcb, GV_AllocMemory(GV_NORMAL_MEMORY, font_get_buffer_size(kcb)));
    font_set_color(kcb, 0, premet1_800C3250[index].fore_color, 0);
    font_clut_update(kcb);
}

void PreMet1_800C4F58(PreMet1Work *work, int index)
{
    work->field_464[index].field_1F4 = work->field_9584;
    work->field_464[index].field_1F6 = work->field_9588;
    work->field_464[index].field_200 = work->field_9584 + 64;
    work->field_464[index].field_202 = work->field_9588;
    work->field_9588 += 21;
    work->field_464[index].field_1F8 = work->field_958C;
    work->field_464[index].field_1FA = work->field_9590;
    work->field_9590 += 21;
}

void PreMet1_800C4FD4(PreMet1Work *work, int index)
{
    KCB *kcb;
    int  i;

    i = (work->current_page_number - 1) * 8 + index;
    if (work->field_464[i].field_1E0 != NULL)
    {
        kcb = &work->field_2D0[index];

        font_print_string(kcb, work->field_464[i].field_1E0);
        font_update(kcb);
        font_clut_update(kcb);

        work->field_464[i].field_1F0 = 256;
        work->field_464[i].field_1F2 = kcb->short3 - 1;
        work->field_464[i].field_1E8 = premet1_800C3250[index].field_0;
        work->field_464[i].field_1EA = premet1_800C3250[index].field_2;

        work->field_464[i].field_1FC = 128;
        work->field_464[i].field_1FE = kcb->short3 - 1;
        work->field_464[i].field_1EC = premet1_800C3250[index].field_0 + 256;
        work->field_464[i].field_1EE = premet1_800C3250[index].field_2;

        work->field_464[i].field_1E4 = 1;
    }
}

void PreMet1_800C50D4(PreMet1Work *work, char *pOt)
{
    int       i, j, k;
    int       page_number;
    DR_TPAGE *tpage;
    SPRT     *sprt, *sprt2;

    page_number = work->current_page_number - 1;

    j = page_number * 8;
    for (i = 0; i < 8; i++)
    {
        if (work->field_464[j].field_1E4 == 1)
        {
            sprt = &work->field_464[j].field_0[GV_Clock];

            setSprt(sprt);

            setRGB0(sprt, 128, 128, 128);
            setSemiTrans(sprt, 1);

            LCOPY(&work->field_464[j].field_1E8, &sprt->x0);
            LCOPY(&work->field_464[j].field_1F0, &sprt->w);

            sprt->u0 = 0;
            sprt->v0 = work->field_464[j].field_1F6;

            sprt->clut = getClut(work->field_464[j].field_1F8, work->field_464[j].field_1FA);

            sprt->x0 += work->field_9594;

            addPrim(pOt, sprt);
            j++;
        }
    }

    tpage = &work->field_444;
    setDrawTPage(tpage, 1, 0, getTPage(0, 1, 704, 256));
    addPrim(pOt, tpage);

    j = page_number * 8;
    for (i = 0; i < 8; i++)
    {
        if (work->field_464[j].field_1E4 == 1)
        {
            sprt = &work->field_464[j].field_C8[GV_Clock];

            setSprt(sprt);

            setRGB0(sprt, 128, 128, 128);
            setSemiTrans(sprt, 1);

            LCOPY(&work->field_464[j].field_1EC, &sprt->x0);
            LCOPY(&work->field_464[j].field_1FC, &sprt->w);

            sprt->u0 = 0;
            sprt->v0 = work->field_464[j].field_202;

            sprt->clut = getClut(work->field_464[j].field_1F8, work->field_464[j].field_1FA);

            sprt->x0 += work->field_9594;

            addPrim(pOt, sprt);
            j++;
        }
    }

    tpage = &work->field_44C;
    setDrawTPage(tpage, 1, 0, getTPage(0, 1, 768, 256));
    addPrim(pOt, tpage);

    j = page_number * 8;
    for (i = 0; i < 8; i++)
    {
        if (work->field_464[j].field_1E4 == 1)
        {
            sprt2 = work->field_464[j].field_28[GV_Clock];
            sprt = &work->field_464[j].field_0[GV_Clock];

            for (k = 0; k < 8; k += 2)
            {
                *sprt2 = *sprt;

                // We just copied it anyways...
                setSprt(sprt2);
                setRGB0(sprt2, 128, 128, 128);
                setSemiTrans(sprt2, 1);

                sprt2->x0 += premet1_800C3290[k];
                sprt2->y0 += premet1_800C3290[k + 1];

                addPrim(pOt, sprt2);
                sprt2++;
            }
            j++;
        }
    }

    tpage = &work->field_454;
    setDrawTPage(tpage, 1, 0, getTPage(0, 2, 704, 256));
    addPrim(pOt, tpage);

    j = page_number * 8;
    for (i = 0; i < 8; i++)
    {
        if (work->field_464[j].field_1E4 == 1)
        {
            sprt2 = work->field_464[j].field_F0[GV_Clock];
            sprt = &work->field_464[j].field_C8[GV_Clock];

            for (k = 0; k < 8; k += 2)
            {
                *sprt2 = *sprt;

                // We just copied it anyways...
                setSprt(sprt2);
                setRGB0(sprt2, 128, 128, 128);
                setSemiTrans(sprt2, 1);

                sprt2->x0 += premet1_800C3290[k];
                sprt2->y0 += premet1_800C3290[k + 1];

                addPrim(pOt, sprt2);
                sprt2++;
            }
            j++;
        }
    }

    tpage = &work->field_45C;
    setDrawTPage(tpage, 1, 0, getTPage(0, 2, 768, 256));
    addPrim(pOt, tpage);
}

void PreMet1SetColor_800C5738(PreMet1Work *work, int index, int fore)
{
    KCB *kcb;

    kcb = &work->field_2D0[index];
    font_set_color(kcb, 0, fore, 0);
    font_clut_update(kcb);
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
    poly_dst = &work->field_20->packs[GV_Clock]->poly_ft4;

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
    poly_dst = &work->field_24->packs[GV_Clock]->poly_ft4;

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
    int            i;
    unsigned short press;

    press = work->field_2C0->press;

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
        if (press & PAD_LEFT)
        {
            work->field_2C8 = 2;
            PreMet1_800C57B4(work, -46, 86, 16, 14, 0xFF, 1);
            GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
        }
        else if (press & PAD_RIGHT)
        {
            work->field_2C8 = 3;
            PreMet1_800C57B4(work, 90, 87, 54, 12, 0xFF, 1);
            GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
        }
        else if (press & (PAD_CIRCLE | PAD_R1))
        {
            if (work->current_page_number != PAGE_COUNT)
            {
                work->field_2C8 = 4;
                GM_SeSet2(0, 0x3F, 0xB0);
                work->field_64 = 0;
            }
        }
        else if (press & PAD_L1)
        {
            if (work->current_page_number != 1)
            {
                work->field_2C8 = 5;
                PreMet1_800C57B4(work, -46, 86, 16, 14, 0xFF, 1);
                GM_SeSet2(0, 0x3F, 0xB0);
                work->field_64 = 0;
            }
        }
        else if (!(press & PAD_CROSS))
        {
            if (press & PAD_SELECT)
            {
                if (work->field_9598 == 0)
                {
                    work->field_9598 = 1;
                }
                else
                {
                    work->field_9598 = 0;
                }
            }
        }
        else
        {
            *work->field_2C4 = 1;
            work->field_64 = 0;
            PreMet1_800C5794(work);
            GM_SeSet2(0, 0x3F, SE_MENU_EXIT);
        }
        break;
    case 2:
        if (!(press & PAD_RIGHT))
        {
            if (press & (PAD_CIRCLE | PAD_L1))
            {
                if (work->current_page_number != 1)
                {
                    work->field_2C8 = 5;
                    GM_SeSet2(0, 0x3F, 0xB0);
                    work->field_64 = 0;
                }
            }
            else if (!(press & PAD_R1))
            {
                if (!(press & PAD_CROSS))
                {
                    if (press & PAD_SELECT)
                    {
                        if (work->field_9598 == 0)
                        {
                            work->field_9598 = 1;
                        }
                        else
                        {
                            work->field_9598 = 0;
                        }
                    }
                }
                else
                {
                    *work->field_2C4 = 1;
                    work->field_64 = 0;
                    PreMet1_800C5794(work);
                    GM_SeSet2(0, 0x3F, SE_MENU_EXIT);
                }
            }
            else if (work->current_page_number != PAGE_COUNT)
            {
                work->field_2C8 = 4;
                GM_SeSet2(0, 0x3F, 0xB0);
                work->field_64 = 0;
                PreMet1_800C57B4(work, 30, 86, 16, 14, 0xFF, 1);
            }
        }
        else
        {
            work->field_2C8 = 1;
            PreMet1_800C57B4(work, 30, 86, 16, 14, 0xFF, 1);
            GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
        }
        break;
    case 4:
        if (work->field_64 < 9)
        {
            work->field_9594 = -(work->field_64 * 40);
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
            work->current_page_number++;
            for (i = 0; i < 8; i++)
            {

                PreMet1_800C4FD4(work, i);
            }
            work->field_9598 = 0;
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
            work->field_9594 = (19 - work->field_64) * 40;
        }
        else
        {
            work->field_9594 = 0;
            work->field_2C8 = 1;
        }
        break;
    case 5:
        if (work->field_64 < 9)
        {
            work->field_9594 = work->field_64 * 40;
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
            work->current_page_number--;
            for (i = 0; i < 8; i++)
            {

                PreMet1_800C4FD4(work, i);
            }
            work->field_9598 = 0;
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
            work->field_9594 = -((19 - work->field_64) * 40);
        }
        else
        {
            work->field_9594 = 0;
            work->field_2C8 = 2;
        }
        break;
    case 3:
        if (press & PAD_LEFT)
        {
            work->field_2C8 = 1;
            PreMet1_800C57B4(work, 30, 86, 16, 14, 0xFF, 1);
            GM_SeSet2(0, 0x3F, SE_MENU_CURSOR);
        }
        else if (press & PAD_CIRCLE)
        {
            *work->field_2C4 = 1;
            work->field_64 = 0;
            PreMet1_800C5794(work);
            GM_SeSet2(0, 0x3F, SE_MENU_EXIT);
        }
        else if (press & PAD_L1)
        {
            if (work->current_page_number != 1)
            {
                work->field_2C8 = 5;
                GM_SeSet2(0, 0x3F, 0xB0);
                PreMet1_800C57B4(work, -46, 86, 16, 14, 0xFF, 1);
                work->field_64 = 0;
            }
        }
        else if (press & PAD_R1)
        {
            if (work->current_page_number != PAGE_COUNT)
            {
                work->field_2C8 = 4;
                GM_SeSet2(0, 0x3F, 0xB0);
                work->field_64 = 0;
                PreMet1_800C57B4(work, 30, 86, 16, 14, 0xFF, 1);
            }
        }
        else if (press & PAD_CROSS)
        {
            *work->field_2C4 = 1;
            work->field_64 = 0;
            PreMet1_800C5794(work);
            GM_SeSet2(0, 0x3F, SE_MENU_EXIT);
        }
        else if (press & PAD_SELECT)
        {
            if (work->field_9598 == 0)
            {
                work->field_9598 = 1;
            }
            else
            {
                work->field_9598 = 0;
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

    if (work->field_9598 == 1)
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

    MENU_Locate(134, 202, 16);
    MENU_Color(r, g, b);
    MENU_Printf("%2d", work->current_page_number);

    MENU_Locate(156, 202, 16);
    MENU_Color(r, g, b);
    MENU_Printf("/");

    MENU_Locate(167, 202, 16);
    MENU_Color(r, g, b);
    MENU_Printf("%d", PAGE_COUNT);
}

void PreMet1Act_800C65A8(PreMet1Work *work)
{
    if (*work->field_2C4 == 0)
    {
        PreMet1_800C5CE4(work);
    }
    PreMet1_800C62B0(work);
    PreMet1_800C63B4(work);
    PreMet1_800C50D4(work, DG_ChanlOTag(1));
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
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    prim = work->field_24;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    for (i = 0; i < 8; i++)
    {
        GV_FreeMemory(GV_NORMAL_MEMORY, PreMet1GetClutBuffer_800C5788(&work->field_2D0[i]));
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
    tex = DG_GetTexture(hashCode);

    if (arg9 == 0)
    {
        int offx, offx2, offx3;
        int offy, offy2;

        offx = tex->off_x;
        offx2 = offx + tex->w;
        offy = tex->off_y;
        offx3 = offx2 + 1;
        offy2 = offy + tex->h + 1;

        setUV4(pPoly, offx, offy, offx3, offy, offx, offy2, offx3, offy2);
        pPoly->tpage = tex->tpage;
        pPoly->clut = tex->clut;
    }

    else if (arg9 == 1)
    {
        int offx, offx2, offx3;
        int offy, offy2;

        offx = tex->off_x;
        offx2 = offx + tex->w;
        offy = tex->off_y;
        offx3 = offx2 + 1;
        offy2 = offy + tex->h;

        setUV4(pPoly, offx, offy, offx3, offy, offx, offy2, offx3, offy2);
        pPoly->tpage = tex->tpage;
        pPoly->clut = tex->clut;
    }

    else if (arg9 == 2)
    {
        int offx, offx2;
        int offy, offy2;

        offx = tex->off_x;
        offx2 = offx + tex->w;
        offy = tex->off_y;
        offy2 = offy + tex->h + 1;

        setUV4(pPoly, offx, offy, offx2, offy, offx, offy2, offx2, offy2);
        pPoly->tpage = tex->tpage;
        pPoly->clut = tex->clut;
    }

    else if (arg9 == 3)
    {
        int offx, offx2;
        int offy, offy2;

        offx = tex->off_x;
        offx2 = offx + tex->w;
        offy = tex->off_y;
        offy2 = offy + tex->h;

        setUV4(pPoly, offx, offy, offx2, offy, offx, offy2, offx2, offy2);
        pPoly->tpage = tex->tpage;
        pPoly->clut = tex->clut;
    }
}

int PreMet1GetResources_800C68C4(PreMet1Work *work, int arg1, int *arg2, PreEntries *arg3)
{
    POLY_FT4 *poly, *poly2;
    int       i, j, k;

    GM_CurrentMap = arg1;
    work->field_20 = DG_GetPrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 6, 0, NULL, NULL);
    work->field_24 = DG_GetPrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 9, 0, NULL, NULL);

    poly = work->field_68;
    i = 0;

    PreMet1_800C6740(work, GV_StrCode("pre_up1_l"), poly, -160, -112, 0, -82, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_28[i] = 768;
    i++;

    PreMet1_800C6740(work, GV_StrCode("pre_up_r"), poly, 0, -112, 160, -82, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_28[i] = 768;
    i++;

    PreMet1_800C6740(work, GV_StrCode("pre_down_l"), poly, -160, 82, 0, 112, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_28[i] = 768;
    i++;

    PreMet1_800C6740(work, GV_StrCode("pre_down_r"), poly, 0, 82, 160, 112, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_28[i] = 768;
    i++;

    PreMet1_800C6740(work, GV_StrCode("pre_met1_l"), poly, -160, -82, 0, 82, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_28[i] = 768;
    i++;

    PreMet1_800C6740(work, GV_StrCode("pre_met1_r"), poly, 0, -82, 160, 82, 0, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_28[i] = 768;
    i++;

    poly2 = work->field_158;
    i = 0;

    PreMet1_800C6740(work, GV_StrCode("cur_lu"), poly2, 0, 0, 0, 0, 1, 0);
    poly2++;
    work->field_40[i] = 0;
    i++;

    PreMet1_800C6740(work, GV_StrCode("cur_ru"), poly2, 0, 0, 0, 0, 1, 0);
    poly2++;
    work->field_40[i] = 0;
    i++;

    PreMet1_800C6740(work, GV_StrCode("cur_ld"), poly2, 0, 0, 0, 0, 1, 0);
    poly2++;
    work->field_40[i] = 0;
    i++;

    PreMet1_800C6740(work, GV_StrCode("cur_rd"), poly2, 0, 0, 0, 0, 1, 0);
    poly2++;
    work->field_40[i] = 0;
    i++;

    PreMet1_800C6740(work, GV_StrCode("cur_u"), poly2, 0, 0, 0, 0, 1, 2);
    poly2++;
    work->field_40[i] = 0;
    i++;

    PreMet1_800C6740(work, GV_StrCode("cur_d"), poly2, 0, 0, 0, 0, 1, 2);
    poly2++;
    work->field_40[i] = 0;
    i++;

    PreMet1_800C6740(work, GV_StrCode("cur_l"), poly2, 0, 0, 0, 0, 1, 1);
    poly2++;
    work->field_40[i] = 0;
    i++;

    PreMet1_800C6740(work, GV_StrCode("cur_r"), poly2, 0, 0, 0, 0, 1, 1);
    poly2++;
    work->field_40[i] = 0;
    i++;

    PreMet1_800C6740(work, GV_StrCode("cur_c"), poly2, 0, 0, 0, 0, 1, 3);
    poly2++;
    work->field_40[i] = 0;
    i++;

    work->field_2C4 = arg2;
    work->field_2C0 = &GV_PadData_800B05C0[2];
    work->field_2C8 = 0;
    work->current_page_number = 1;
    work->field_64 = 0;

    k = 0;
    for (j = 0; j < PAGE_COUNT; j++)
    {
        work->field_9584 = 704;
        work->field_9588 = 256;
        work->field_958C = 704;
        work->field_9590 = 276;

        for (i = 0; i < 8; i++)
        {
            work->field_464[k].field_1E0 = arg3[j].entries[i].field_C8;
            work->field_464[k].field_1E4 = 0;

            PreMet1_800C4F58(work, k);
            k++;
        }
    }

    work->field_9584 = 704;
    work->field_9588 = 256;
    work->field_958C = 704;
    work->field_9590 = 276;

    for (i = 0; i < 8; i++)
    {
        PreMet1_800C4E40(work, i);
    }
    for (i = 0; i < 8; i++)
    {
        PreMet1_800C4FD4(work, i);
    }
    for (i = 0; i < 8; i++)
    {
        PreMet1SetColor_800C5738(work, i, get_color(25));
    }
    work->field_9594 = 0;
    work->field_9598 = 0;
    return 0;
}

void *NewPreMet1_800C6F20(int arg0, int *arg1, PreEntries *arg2)
{
    PreMet1Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(PreMet1Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, PreMet1Act_800C65A8, PreMet1Die_800C6634, "pre_met1.c");

        if (PreMet1GetResources_800C68C4(work, arg0, arg1, arg2) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
