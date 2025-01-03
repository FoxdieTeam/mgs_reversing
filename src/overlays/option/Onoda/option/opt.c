#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "mts/mts.h"
#include "mts/mts_pad.h"
#include "Font/font.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "SD/g_sound.h"

// FIXME: it's the same struct as in change.c (in change overlay)
typedef struct _Unknown
{
    SPRT  sprt[2];
    SPRT  sprt2[2][4];
    char *string;
    short num;
    short num2;
    RECT  rect;
    short f0;
    short f2;
    short f4;
    short f6;
} Unknown;

typedef struct _OptionWork
{
    GV_ACT   actor;
    GV_PAD  *pad;
    DG_PRIM *field_24;
    DG_PRIM *field_28;
    DG_PRIM *field_2C;
    DG_PRIM *field_30;
    POLY_FT4 field_34[27];
    POLY_FT4 field_46C[9];
    POLY_FT4 field_5D4[4];
    POLY_FT4 field_674[17];
    int      f91C;
    int      f920;
    int      f924[8];
    KCB      kcb[31];
    char     pad1[0x14];
    DR_TPAGE tpage[3];
    Unknown  fEC4[31];
    int      f29E4;
    int      f29E8;
    int      f29EC;
    int      f29F0;
    int      f29F4;
    int      f29F8;
    int      f29FC;
    int      f2A00[27];
    int      f2A6C[9];
    int      f2A90[27];
    int      f2AFC[4];
    int      f2B0C[17];
    int      f2B50;
    int      f2B54;
    int      f2B58;
    char     pad2[0x4];
    int      f2B60;
} OptionWork;

typedef struct _Unknown2
{
    int   num;
    short x;
    short y;
    int   color;
} Unknown2;

extern int    GM_GameStatus;
extern int    GV_Clock_800AB920;
extern int    GM_CurrentMap_800AB9B0;
extern int    GM_PadVibration_800ABA3C;
extern int    GM_PadVibration2_800ABA54;
extern GV_PAD GV_PadData_800B05C0[4];

extern Unknown2 dword_800C3218[];

signed char byte_800C338C[] = {-1, 0, 1, 0, 0, 1, 0, -1};
signed char byte_800C3394[] = {-1, 0, 1, 0, 0, 1, 0, -1};

extern const char option_aOpcaption_800C950C[];      // = "op_caption"
extern const char option_aOpsound_800C9518[];        // = "op_sound"
extern const char option_aOpvib_800C9524[];          // = "op_vib"
extern const char option_aOpvibtest_800C952C[];      // = "op_vib_test"
extern const char option_aOpscreen_800C9538[];       // = "op_screen"
extern const char option_aOpkeyconfig_800C9544[];    // = "op_keyconfig"
extern const char option_aOpexit_800C9554[];         // = "op_exit"
extern const char option_aIntoplanguage_800C955C[];  // = "int_op_language2"

void option_800C339C(OptionWork *work, int index)
{
    RECT rect;
    KCB *kcb;

    kcb = &work->kcb[index];

    if (index == 12)
    {
        work->f29F4 = 256;
        work->f29F0 = 832;
        work->f29FC = 276;
        work->f29F8 = work->f29F0;
    }
    else if (index == 24)
    {
        work->f29F4 = 256;
        work->f29F0 = 896;
        work->f29FC = 276;
        work->f29F8 = work->f29F0;
    }

    rect.x = work->f29F0;
    rect.y = work->f29F4;
    rect.w = 64;
    rect.h = 21;

    work->fEC4[index].f0 = work->f29F0;
    work->fEC4[index].f2 = work->f29F4;
    work->f29F4 += 21;

    font_init_kcb(kcb, &rect, work->f29F8, work->f29FC);

    work->fEC4[index].f4 = work->f29F8;
    work->fEC4[index].f6 = work->f29FC;
    work->f29FC += 21;

    font_set_kcb(kcb, -1, -1, 0, 6, 2, 0);

    font_set_buffer(kcb, GV_AllocMemory(2, font_get_buffer_size(kcb)));

    font_set_color(kcb, 0, dword_800C3218[index].color, 0);
    font_clut_update(kcb);
}

void option_800C352C(OptionWork *work, int index)
{
    char     *string;
    KCB      *kcb;
    Unknown2 *unknown;

    string = work->fEC4[index].string;
    if (string != NULL)
    {
        kcb = &work->kcb[index];

        font_print_string(kcb, string);
        font_update(kcb);

        work->fEC4[ index ].rect.w = kcb->char_arr[7];
        work->fEC4[ index ].rect.h = kcb->short3;

        unknown = &dword_800C3218[ index ];
        if (unknown->num == 0)
        {
            work->fEC4[index].rect.x = unknown->x;
            work->fEC4[index].rect.y = unknown->y;
        }
        else if (unknown->num == 1)
        {
            work->fEC4[index].rect.x = unknown->x - kcb->char_arr[7] / 2;
            work->fEC4[index].rect.y = unknown->y - kcb->short3 / 2;
        }

        work->fEC4[index].string = NULL;
        work->fEC4[index].num = 1;
    }
}

void option_800C3664(OptionWork *work, char *ot)
{
    int       index;
    int       i, j, k;
    int       found;
    SPRT     *sprt;
    SPRT     *sprt2;
    DR_TPAGE *tpage;
    DR_TPAGE *tpage2;

    index = 0;

    for (i = 0; i < 2; i++)
    {
        found = 0;

        for (j = 0; j < 12; j++)
        {
            // BUG: The index doesn't increment on continue
            if (work->fEC4[index].num != 1)
            {
                continue;
            }

            found = 1;

            sprt = &work->fEC4[index].sprt[GV_Clock_800AB920];
            LSTORE(0x808080, &sprt->r0);
            LCOPY(&work->fEC4[index].rect.x, &sprt->x0);
            LCOPY(&work->fEC4[index].rect.w, &sprt->w);
            sprt->u0 = 0;
            sprt->v0 = work->fEC4[index].f2;
            sprt->clut = getClut(work->fEC4[index].f4, work->fEC4[index].f6);
            setSprt(sprt);
            addPrim(ot, sprt);

            sprt2 = work->fEC4[index].sprt2[GV_Clock_800AB920];
            for (k = 0; k < 8; k += 2)
            {
                *sprt2 = *sprt;
                LSTORE(0x64000000, &sprt2->r0);
                sprt2->x0 += byte_800C338C[k];
                sprt2->y0 += byte_800C338C[k + 1];
                addPrim(ot, sprt2);
                sprt2++;
            }

            index++;
        }

        if (found != 0)
        {
            tpage = &work->tpage[i];
            setDrawTPage(tpage, 1, 0, getTPage(0, 0, 768 + i * 64, 256));
            addPrim(ot, tpage);
        }
    }

    found = 0;

    for (j = 0; j < 7; j++)
    {
        // BUG: The index doesn't increment on continue
        if (work->fEC4[index].num != 1)
        {
            continue;
        }

        found = 1;

        sprt = &work->fEC4[index].sprt[GV_Clock_800AB920];
        LSTORE(0x808080, &sprt->r0);
        LCOPY(&work->fEC4[index].rect.x, &sprt->x0);
        LCOPY(&work->fEC4[index].rect.w, &sprt->w);
        sprt->u0 = 0;
        sprt->v0 = work->fEC4[index].f2;
        sprt->clut = getClut(work->fEC4[index].f4, work->fEC4[index].f6);
        setSprt(sprt);
        addPrim(ot, sprt);

        sprt2 = work->fEC4[index].sprt2[GV_Clock_800AB920];
        for (k = 0; k < 8; k += 2)
        {
            *sprt2 = *sprt;
            LSTORE(0x64000000, &sprt2->r0);
            sprt2->x0 += byte_800C3394[k];
            sprt2->y0 += byte_800C3394[k + 1];
            addPrim(ot, sprt2);
            sprt2++;
        }

        index++;
    }

    if (found != 0)
    {
        tpage2 = &work->tpage[i];
        setDrawTPage(tpage2, 1, 0, getTPage(0, 0, 768 + i * 64, 256));
        addPrim(ot, tpage2);
    }
}

void option_800C3B3C(OptionWork *work, int index, int color)
{
    KCB *kcb;

    kcb = &work->kcb[ index ];
    font_set_color( kcb, 0, color, 0 );
    font_clut_update( kcb );
}

void * option_800C3B8C(KCB *kcb)
{
    return kcb->font_clut_buffer;
}

void option_800C3B98(OptionWork *work)
{
    POLY_FT4 *polys;

    polys = work->field_34;
    if (work->f2B50 != 0)
    {
        if (work->f924[5] == 0)
        {
            GM_PadVibration_800ABA3C = 0x1;

            setRGB0(&polys[15], 100, 160, 135);
            setRGB0(&polys[16], 70, 100, 90);
        }
        else
        {
            GM_PadVibration2_800ABA54 = 0xFF;

            setRGB0(&polys[15], 70, 100, 90);
            setRGB0(&polys[16], 100, 160, 135);
        }


        if (++work->f2B50 > 9)
        {
            work->f2B50 = 0;
        }
    }
    else
    {
        setRGB0(&polys[15], 70, 100, 90);
        setRGB0(&polys[16], 70, 100, 90);
    }
}

void option_800C3C74(OptionWork *work)
{
    POLY_FT4 *poly_dst, *poly_src;
    int       r0, g0, b0;
    int       i;

    poly_src = work->field_34;
    poly_dst = &work->field_24->packs[GV_Clock_800AB920]->poly_ft4;

    work->f2A00[20] = 0;

    for (i = 0; i < 27; poly_dst++, poly_src++, i++)
    {
        *poly_dst = *poly_src;

        if (work->f920 == 11)
        {
            r0 = poly_dst->r0;
            g0 = poly_dst->g0;
            b0 = poly_dst->b0;
            setRGB0(poly_dst, r0 - r0 * work->f2B58 / 16,
                              g0 - g0 * work->f2B58 / 16,
                              b0 - b0 * work->f2B58 / 16);
        }

        SSTOREL(work->f2A00[i], poly_dst);
    }

    poly_src = work->field_5D4;
    poly_dst = &work->field_2C->packs[GV_Clock_800AB920]->poly_ft4;

    for (i = 0; i < 4; poly_dst++, poly_src++, i++)
    {
        *poly_dst = *poly_src;

        if (work->f920 == 11)
        {
            r0 = poly_dst->r0;
            g0 = poly_dst->g0;
            b0 = poly_dst->b0;
            setRGB0(poly_dst, r0 - r0 * work->f2B58 / 16,
                              g0 - g0 * work->f2B58 / 16,
                              b0 - b0 * work->f2B58 / 16);
        }

        SSTOREL(work->f2AFC[i], poly_dst);
    }

    poly_src = work->field_674;
    poly_dst = &work->field_30->packs[GV_Clock_800AB920]->poly_ft4;

    for (i = 0; i < 17; poly_dst++, poly_src++, i++)
    {
        *poly_dst = *poly_src;

        if (work->f920 == 11)
        {
            r0 = poly_dst->r0;
            g0 = poly_dst->g0;
            b0 = poly_dst->b0;
            setRGB0(poly_dst, r0 - r0 * work->f2B58 / 16,
                              g0 - g0 * work->f2B58 / 16,
                              b0 - b0 * work->f2B58 / 16);
        }

        SSTOREL(work->f2B0C[i], poly_dst);
    }

    poly_src = work->field_46C;
    poly_dst = &work->field_28->packs[GV_Clock_800AB920]->poly_ft4;

    for (i = 0; i < 9; poly_dst++, poly_src++, i++)
    {
        *poly_dst = *poly_src;

        if (work->f920 == 11)
        {
            r0 = poly_dst->r0;
            g0 = poly_dst->g0;
            b0 = poly_dst->b0;
            setRGB0(poly_dst, r0 - r0 * work->f2B58 / 16,
                              g0 - g0 * work->f2B58 / 16,
                              b0 - b0 * work->f2B58 / 16);
        }

        SSTOREL(work->f2A6C[i], poly_dst);
    }
}

void option_800C4130(OptionWork *work, char *ot)
{
    int i;

    for (i = 0; i < 31; i++)
    {
        option_800C3B3C(work, i, 0);
    }

    switch(work->f920)
    {
    case 1:
        option_800C3B3C(work, 0, 0x6739);
        option_800C3B3C(work, 7, 0x6739);

        if (work->f924[work->f920] == 0)
        {
            option_800C3B3C(work, 8, 0x6739);
        }
        else
        {
            option_800C3B3C(work, 9, 0x6739);
        }
        break;

    case 2:
        option_800C3B3C(work, 7, 0x6739);
        option_800C3B3C(work, 28, 0x6739);

        if (work->f924[work->f920] == 0)
        {
            option_800C3B3C(work, 29, 0x6739);
        }
        else
        {
            option_800C3B3C(work, 30, 0x6739);
        }
        break;

    case 3:
        option_800C3B3C(work, 1, 0x6739);
        option_800C3B3C(work, 7, 0x6739);

        if (work->f924[work->f920] == 0)
        {
            option_800C3B3C(work, 10, 0x6739);
        }
        else
        {
            option_800C3B3C(work, 11, 0x6739);
        }
        break;

    case 4:
        option_800C3B3C(work, 2, 0x6739);
        option_800C3B3C(work, 7, 0x6739);

        if (work->f924[work->f920] == 0)
        {
            option_800C3B3C(work, 8, 0x6739);
        }
        else
        {
            option_800C3B3C(work, 9, 0x6739);
        }
        break;

    case 5:
        option_800C3B3C(work, 3, 0x6739);
        option_800C3B3C(work, 27, 0x6739);

        if (work->f924[work->f920] == 0)
        {
            option_800C3B3C(work, 12, 0x6739);
        }
        else
        {
            option_800C3B3C(work, 26, 0x6739);
        }
        break;

    case 6:
        option_800C3B3C(work, 4, 0x6739);
        break;

    case 7:
        option_800C3B3C(work, 13, 0x6739);
        option_800C3B3C(work, 14, 0x6739);
        option_800C3B3C(work, 15, 0x6739);
        option_800C3B3C(work, 16, 0x6739);
        option_800C3B3C(work, 24, 0x6739);
        break;

    case 8:
        option_800C3B3C(work, 5, 0x6739);
        break;

    case 9:
        switch (work->f29E4)
        {
        case 0:
            option_800C3B3C(work, 7, 0x6739);
            option_800C3B3C(work, 17, 0x6739);

            if (work->f29E8 == 0)
            {
                option_800C3B3C(work, 18, 0x6739);
            }
            else if (work->f29E8 == 1)
            {
                option_800C3B3C(work, 19, 0x6739);
            }
            else
            {
                option_800C3B3C(work, 20, 0x6739);
            }
            break;

        case 1:
            option_800C3B3C(work, 7, 0x6739);
            option_800C3B3C(work, 21, 0x6739);

            if (work->f29EC == 0)
            {
                option_800C3B3C(work, 22, 0x6739);
            }
            else
            {
                option_800C3B3C(work, 23, 0x6739);
            }
            break;

        case 2:
            option_800C3B3C(work, 25, 0x6739);
            break;
        }
        break;

    case 10:
        option_800C3B3C(work, 6, 0x6739);
        break;
    }

    option_800C3664(work, ot);
}

void option_800C449C(OptionWork *work, int x, int y, int w, int h, int shade, int type)
{
    POLY_FT4 *poly;
    int       i;

    poly = work->field_46C;

    for (i = 0; i < 9; i++)
    {
        work->f2A6C[i] = 512;
        setRGB0(&poly[i], shade, shade, shade);
    }

    if (type == 0)
    {
        poly[0].x0 = x - 8;
        poly[0].y0 = y - 8;
        poly[0].x1 = x;
        poly[0].y1 = y - 8;
        poly[0].x2 = x - 8;
        poly[0].y2 = y;
        poly[0].x3 = x;
        poly[0].y3 = y;

        poly[1].x0 = x + w;
        poly[1].y0 = y - 8;
        poly[1].x1 = x + w + 8;
        poly[1].y1 = y - 8;
        poly[1].x2 = x + w;
        poly[1].y2 = y;
        poly[1].x3 = x + w + 8;
        poly[1].y3 = y;

        poly[2].x0 = x - 8;
        poly[2].y0 = y + h;
        poly[2].x1 = x;
        poly[2].y1 = y + h;
        poly[2].x2 = x - 8;
        poly[2].y2 = y + h + 8;
        poly[2].x3 = x;
        poly[2].y3 = y + h + 8;

        poly[3].x0 = x + w;
        poly[3].y0 = y + h;
        poly[3].x1 = x + w + 8;
        poly[3].y1 = y + h;
        poly[3].x2 = x + w;
        poly[3].y2 = y + h + 8;
        poly[3].x3 = x + w + 8;
        poly[3].y3 = y + h + 8;

        poly[4].x0 = x;
        poly[4].y0 = y - 8;
        poly[4].x1 = x + w;
        poly[4].y1 = y - 8;
        poly[4].x2 = x;
        poly[4].y2 = y;
        poly[4].x3 = x + w;
        poly[4].y3 = y;

        poly[5].x0 = x;
        poly[5].y0 = y + h;
        poly[5].x1 = x + w;
        poly[5].y1 = y + h;
        poly[5].x2 = x;
        poly[5].y2 = y + h + 8;
        poly[5].x3 = x + w;
        poly[5].y3 = y + h + 8;

        poly[6].x0 = x - 8;
        poly[6].y0 = y;
        poly[6].x1 = x;
        poly[6].y1 = y;
        poly[6].x2 = x - 8;
        poly[6].y2 = y + h;
        poly[6].x3 = x;
        poly[6].y3 = y + h;

        poly[7].x0 = x + w;
        poly[7].y0 = y;
        poly[7].x1 = x + w + 8;
        poly[7].y1 = y;
        poly[7].x2 = x + w;
        poly[7].y2 = y + h;
        poly[7].x3 = x + w + 8;
        poly[7].y3 = y + h;

        poly[8].x0 = x;
        poly[8].y0 = y;
        poly[8].x1 = x + w;
        poly[8].y1 = y;
        poly[8].x2 = x;
        poly[8].y2 = y + h;
        poly[8].x3 = x + w;
        poly[8].y3 = y + h;
    }
    else if (type == 1)
    {
        poly[0].x0 = x - 6;
        poly[0].y0 = y - 6;
        poly[0].x1 = x + 2;
        poly[0].y1 = y - 6;
        poly[0].x2 = x - 6;
        poly[0].y2 = y + 2;
        poly[0].x3 = x + 2;
        poly[0].y3 = y + 2;

        poly[1].x0 = x + w - 2;
        poly[1].y0 = y - 6;
        poly[1].x1 = x + w + 6;
        poly[1].y1 = y - 6;
        poly[1].x2 = x + w - 2;
        poly[1].y2 = y + 2;
        poly[1].x3 = x + w + 6;
        poly[1].y3 = y + 2;

        poly[2].x0 = x - 6;
        poly[2].y0 = y + h - 2;
        poly[2].x1 = x + 2;
        poly[2].y1 = y + h - 2;
        poly[2].x2 = x - 6;
        poly[2].y2 = y + h + 6;
        poly[2].x3 = x + 2;
        poly[2].y3 = y + h + 6;

        poly[3].x0 = x + w - 2;
        poly[3].y0 = y + h - 2;
        poly[3].x1 = x + w + 6;
        poly[3].y1 = y + h - 2;
        poly[3].x2 = x + w - 2;
        poly[3].y2 = y + h + 6;
        poly[3].x3 = x + w + 6;
        poly[3].y3 = y + h + 6;

        poly[4].x0 = x + 2;
        poly[4].y0 = y - 6;
        poly[4].x1 = x + w - 2;
        poly[4].y1 = y - 6;
        poly[4].x2 = x + 2;
        poly[4].y2 = y + 2;
        poly[4].x3 = x + w - 2;
        poly[4].y3 = y + 2;

        poly[5].x0 = x + 2;
        poly[5].y0 = y + h - 2;
        poly[5].x1 = x + w - 2;
        poly[5].y1 = y + h - 2;
        poly[5].x2 = x + 2;
        poly[5].y2 = y + h + 6;
        poly[5].x3 = x + w - 2;
        poly[5].y3 = y + h + 6;

        poly[6].x0 = x - 6;
        poly[6].y0 = y + 2;
        poly[6].x1 = x + 2;
        poly[6].y1 = y + 2;
        poly[6].x2 = x - 6;
        poly[6].y2 = y + h - 2;
        poly[6].x3 = x + 2;
        poly[6].y3 = y + h - 2;

        poly[7].x0 = x + w - 2;
        poly[7].y0 = y + 2;
        poly[7].x1 = x + w + 6;
        poly[7].y1 = y + 2;
        poly[7].x2 = x + w - 2;
        poly[7].y2 = y + h - 2;
        poly[7].x3 = x + w + 6;
        poly[7].y3 = y + h - 2;

        poly[8].x0 = x + 2;
        poly[8].y0 = y + 2;
        poly[8].x1 = x + w - 2;
        poly[8].y1 = y + 2;
        poly[8].x2 = x + 2;
        poly[8].y2 = y + h - 2;
        poly[8].x3 = x + w - 2;
        poly[8].y3 = y + h - 2;
    }
}

void option_800C4780(OptionWork *work)
{
    POLY_FT4 *poly;
    int       f29E8;

    poly = work->field_674;
    f29E8 = work->f29E8;

    if (f29E8 == 0)
    {
        setRGB0(&poly[10], 100, 160, 135);
        setRGB0(&poly[11], 70, 100, 90);
        setRGB0(&poly[12], 70, 100, 90);

        poly[13].x0 = 74;
        poly[13].y0 = -18;
        poly[13].x1 = 138;
        poly[13].y1 = -18;
        poly[13].x2 = 74;
        poly[13].y2 = -11;
        poly[13].x3 = 138;
        poly[13].y3 = -11;

        poly[14].x0 = -136;
        poly[14].y0 = -18;
        poly[14].x1 = -92;
        poly[14].y1 = -18;
        poly[14].x2 = -136;
        poly[14].y2 = -11;
        poly[14].x3 = -92;
        poly[14].y3 = -11;

        poly[15].x0 = -136;
        poly[15].y0 = 2;
        poly[15].x1 = -84;
        poly[15].y1 = 2;
        poly[15].x2 = -136;
        poly[15].y2 = 9;
        poly[15].x3 = -84;
        poly[15].y3 = 9;

        poly[16].x0 = 78;
        poly[16].y0 = -39;
        poly[16].x1 = 138;
        poly[16].y1 = -39;
        poly[16].x2 = 78;
        poly[16].y2 = -32;
        poly[16].x3 = 138;
        poly[16].y3 = -32;
    }
    else if (f29E8 == 1)
    {
        setRGB0(&poly[10], 70, 100, 90);
        setRGB0(&poly[11], 100, 160, 135);
        setRGB0(&poly[12], 70, 100, 90);

        poly[13].x0 = -135;
        poly[13].y0 = 2;
        poly[13].x1 = -71;
        poly[13].y1 = 2;
        poly[13].x2 = -135;
        poly[13].y2 = 9;
        poly[13].x3 = -71;
        poly[13].y3 = 9;

        poly[14].x0 = -136;
        poly[14].y0 = -18;
        poly[14].x1 = -92;
        poly[14].y1 = -18;
        poly[14].x2 = -136;
        poly[14].y2 = -11;
        poly[14].x3 = -92;
        poly[14].y3 = -11;

        poly[15].x0 = 86;
        poly[15].y0 = -18;
        poly[15].x1 = 138;
        poly[15].y1 = -18;
        poly[15].x2 = 86;
        poly[15].y2 = -11;
        poly[15].x3 = 138;
        poly[15].y3 = -11;

        poly[16].x0 = 78;
        poly[16].y0 = -39;
        poly[16].x1 = 138;
        poly[16].y1 = -39;
        poly[16].x2 = 78;
        poly[16].y2 = -32;
        poly[16].x3 = 138;
        poly[16].y3 = -32;
    }
    else if (f29E8 == 2)
    {
        setRGB0(&poly[10], 70, 100, 90);
        setRGB0(&poly[11], 70, 100, 90);
        setRGB0(&poly[12], 100, 160, 135);

        poly[13].x0 = -135;
        poly[13].y0 = -18;
        poly[13].x1 = -71;
        poly[13].y1 = -18;
        poly[13].x2 = -135;
        poly[13].y2 = -11;
        poly[13].x3 = -71;
        poly[13].y3 = -11;

        poly[14].x0 = 94;
        poly[14].y0 = -18;
        poly[14].x1 = 138;
        poly[14].y1 = -18;
        poly[14].x2 = 94;
        poly[14].y2 = -11;
        poly[14].x3 = 138;
        poly[14].y3 = -11;

        poly[15].x0 = -136;
        poly[15].y0 = f29E8;
        poly[15].x1 = -84;
        poly[15].y1 = f29E8;
        poly[15].x2 = -136;
        poly[15].y2 = 9;
        poly[15].x3 = -84;
        poly[15].y3 = 9;

        poly[16].x0 = 78;
        poly[16].y0 = -39;
        poly[16].x1 = 138;
        poly[16].y1 = -39;
        poly[16].x2 = 78;
        poly[16].y2 = -32;
        poly[16].x3 = 138;
        poly[16].y3 = -32;
    }
}

void option_800C4A6C(OptionWork *work)
{
    POLY_FT4 *polys;

    polys = work->field_674;
    if (work->f29EC == 0)
    {
        setRGB0(&polys[5], 70, 100, 90);
        setRGB0(&polys[6], 100, 160, 135);
    }
    else if (work->f29EC == 1)
    {
        setRGB0(&polys[5], 100, 160, 135);
        setRGB0(&polys[6], 70, 100, 90);
    }
}

void option_800C4AE8(OptionWork *work, int name, POLY_FT4 *poly)
{
    DG_TEX *tex;
    int     x, y, w, h;

    tex = DG_GetTexture(name);

    x = tex->off_x;
    w = tex->w;
    y = tex->off_y;
    h = tex->h;

    poly->u0 = x;
    poly->v0 = y;
    poly->u1 = x + w + 1;
    poly->v1 = y;
    poly->u2 = x;
    poly->v2 = y + h + 1;
    poly->u3 = x + w + 1;
    poly->v3 = y + h + 1;

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}


void option_800C4B68(OptionWork *work)
{
    POLY_FT4 *poly;

    poly = work->field_34;

    if (work->f924[work->f920] == 0)
    {
        work->f924[work->f920] = 1;
    }
    else
    {
        work->f924[work->f920] = 0;
    }

    switch(work->f920)
    {
    case 1:
        if (work->f924[work->f920] == 0)
        {
            option_800C4AE8(work, GV_StrCode("on_w"), &poly[9]);
            setRGB0(&poly[9], 100, 160, 135);

            option_800C4AE8(work, GV_StrCode("off"), &poly[10]);
            setRGB0(&poly[10], 70, 100, 90);

            poly[17].x0 = -96;
            poly[17].y0 = -55;
            poly[17].x1 = -48;
            poly[17].y1 = -55;
            poly[17].x2 = -96;
            poly[17].y2 = -53;
            poly[17].x3 = -48;
            poly[17].y3 = -53;
        }
        else
        {
            option_800C4AE8(work, GV_StrCode("on"), &poly[9]);
            setRGB0(&poly[9], 70, 100, 90);

            option_800C4AE8(work, GV_StrCode("off_w"), &poly[10]);
            setRGB0(&poly[10], 100, 160, 135);

            poly[17].x0 = 48;
            poly[17].y0 = -55;
            poly[17].x1 = 92;
            poly[17].y1 = -55;
            poly[17].x2 = 48;
            poly[17].y2 = -53;
            poly[17].x3 = 92;
            poly[17].y3 = -53;
        }
        break;

    case 2:
        if (work->f924[work->f920] == 0)
        {
            option_800C4AE8(work, GV_StrCode("int_op_language1_w"), &poly[24]);
            setRGB0(&poly[24], 100, 160, 135);

            option_800C4AE8(work, GV_StrCode("int_op_language3"), &poly[25]);
            setRGB0(&poly[25], 70, 100, 90);

            poly[26].x0 = -71;
            poly[26].y0 = -39;
            poly[26].x1 = -55;
            poly[26].y1 = -39;
            poly[26].x2 = -71;
            poly[26].y2 = -37;
            poly[26].x3 = -55;
            poly[26].y3 = -37;
        }
        else
        {
            option_800C4AE8(work, GV_StrCode("int_op_language1"), &poly[24]);
            setRGB0(&poly[24], 70, 100, 90);

            option_800C4AE8(work, GV_StrCode("int_op_language3_w"), &poly[25]);
            setRGB0(&poly[25], 100, 160, 135);

            poly[26].x0 = 55;
            poly[26].y0 = -39;
            poly[26].x1 = 78;
            poly[26].y1 = -39;
            poly[26].x2 = 55;
            poly[26].y2 = -37;
            poly[26].x3 = 78;
            poly[26].y3 = -37;
        }
        break;

    case 3:
        if (work->f924[work->f920] == 0)
        {
            option_800C4AE8(work, GV_StrCode("stereo_w"), &poly[11]);
            setRGB0(&poly[11], 100, 160, 135);

            option_800C4AE8(work, GV_StrCode("monaural"), &poly[12]);
            setRGB0(&poly[12], 70, 100, 90);

            poly[18].x0 = -80;
            poly[18].y0 = -23;
            poly[18].x1 = -42;
            poly[18].y1 = -23;
            poly[18].x2 = -80;
            poly[18].y2 = -21;
            poly[18].x3 = -42;
            poly[18].y3 = -21;
        }
        else
        {
            option_800C4AE8(work, GV_StrCode("stereo"), &poly[11]);
            setRGB0(&poly[11], 70, 100, 90);

            option_800C4AE8(work, GV_StrCode("monaural_w"), &poly[12]);
            setRGB0(&poly[12], 100, 160, 135);

            poly[18].x0 = 42;
            poly[18].y0 = -23;
            poly[18].x1 = 76;
            poly[18].y1 = -23;
            poly[18].x2 = 42;
            poly[18].y2 = -21;
            poly[18].x3 = 76;
            poly[18].y3 = -21;
        }
        break;

    case 4:
        if (work->f924[work->f920] == 0)
        {
            option_800C4AE8(work, GV_StrCode("on_w"), &poly[13]);
            setRGB0(&poly[13], 100, 160, 135);

            option_800C4AE8(work, GV_StrCode("off"), &poly[14]);
            setRGB0(&poly[14], 70, 100, 90);

            poly[19].x0 = -96;
            poly[19].y0 = -7;
            poly[19].x1 = -55;
            poly[19].y1 = -7;
            poly[19].x2 = -96;
            poly[19].y2 = -5;
            poly[19].x3 = -55;
            poly[19].y3 = -5;
        }
        else
        {
            option_800C4AE8(work, GV_StrCode("on"), &poly[13]);
            setRGB0(&poly[13], 70, 100, 90);

            option_800C4AE8(work, GV_StrCode("off_w"), &poly[14]);
            setRGB0(&poly[14], 100, 160, 135);

            poly[19].x0 = 55;
            poly[19].y0 = -7;
            poly[19].x1 = 92;
            poly[19].y1 = -7;
            poly[19].x2 = 55;
            poly[19].y2 = -5;
            poly[19].x3 = 92;
            poly[19].y3 = -5;
        }
        break;

    case 5:
        if (work->f2B54 == 1)
        {
            if (work->f924[work->f920] == 0)
            {
                poly[20].x0 = -88;
                poly[20].y0 = 9;
                poly[20].x1 = -74;
                poly[20].y1 = 9;
                poly[20].x2 = -88;
                poly[20].y2 = 11;
                poly[20].x3 = -74;
                poly[20].y3 = 11;
            }
            else
            {
                poly[20].x0 = 74;
                poly[20].y0 = 9;
                poly[20].x1 = 80;
                poly[20].y1 = 9;
                poly[20].x2 = 74;
                poly[20].y2 = 11;
                poly[20].x3 = 80;
                poly[20].y3 = 11;
            }
        }
        else
        {
            work->f924[work->f920] = 0;
        }
    }
}


void option_800C5150(OptionWork *work, int param_2)
{
    POLY_FT4 *poly;
    int       i;

    poly = work->field_34;

    switch(work->f920)
    {
    case 1:
        option_800C449C(work, -56, -44, 112, 13, 255, 1);
        work->f920 = 2;
        break;

    case 2:
        if (param_2 == 0)
        {
            option_800C449C(work, -50, -60, 100, 12, 255, 1);
            work->f920 = 1;
        }
        else
        {
            option_800C449C(work, -42, -28, 84, 12, 255, 1);
            work->f920 = 3;
        }
        break;

    case 3:
        if (param_2 == 0)
        {
            option_800C449C(work, -56, -44, 112, 13, 255, 1);
            work->f920 = 2;
        }
        else if (work->f2B54 == 0)
        {
            option_800C449C(work, -30, 24, 60, 12, 255, 1);
            work->f920 = 6;
        }
        else
        {
            option_800C449C(work, -56, -12, 112, 12, 255, 1);
            work->f920 = 4;
        }
        break;

    case 4:
        if (param_2 == 0)
        {
            option_800C449C(work, -42, -28, 84, 12, 255, 1);
            work->f920 = 3;
        }
        else
        {
            option_800C449C(work, -74, 4, 148, 12, 255, 1);
            work->f920 = 5;
            setRGB0(&poly[20], 100, 160, 135);
        }
        break;

    case 5:
        if (param_2 == 0)
        {
            option_800C449C(work, -56, -12, 112, 12, 255, 1);
            work->f920 = 4;
        }
        else
        {
            option_800C449C(work, -30, 24, 60, 12, 255, 1);
            work->f920 = 6;
        }

        setRGB0(&poly[20], 0, 0, 0);
        break;

    case 6:
        if (param_2 == 0)
        {
            if (work->f2B54 == 0)
            {
                option_800C449C(work, -42, -28, 84, 12, 255, 1);
                work->f920 = 3;
            }
            else
            {
                option_800C449C(work, -74, 4, 148, 12, 255, 1);
                work->f920 = 5;
                setRGB0(&poly[20], 100, 160, 135);
            }
        }
        else if (param_2 == 1)
        {
            option_800C449C(work, -44, 40, 88, 12, 255, 1);
            work->f920 = 8;
        }
        else
        {
            option_800C449C(work, 90, 86, 54, 12, 255, 1);
            work->f920 = 7;

            work->f2AFC[0] = 768;
            work->f2AFC[1] = 768;
            work->f2AFC[2] = 256;
            work->f2AFC[3] = 256;
        }
        break;

    case 8:
        if (param_2 == 0)
        {
            option_800C449C(work,-30, 24, 60, 12, 255, 1);
            work->f920 = 6;
        }
        else if (param_2 == 1)
        {
            option_800C449C(work, -28, 60, 56, 12, 255, 1);
            work->f920 = 10;
        }
        else
        {
            option_800C449C(work, -149, -70, 88, 12, 255, 1);

            work->f920 = 9;
            work->f29E4 = 0;
            work->f2B60 = 1;

            work->f2B0C[0] = 768;
            work->f2B0C[1] = 768;
            work->f2B0C[2] = 256;
            work->f2B0C[3] = 256;
            work->f2B0C[4] = 256;
            work->f2B0C[5] = 256;
            work->f2B0C[6] = 256;
            work->f2B0C[7] = 256;
            work->f2B0C[8] = 512;
            work->f2B0C[9] = 256;
            work->f2B0C[10] = 256;
            work->f2B0C[11] = 256;
            work->f2B0C[12] = 256;
            work->f2B0C[13] = 256;
            work->f2B0C[14] = 256;
            work->f2B0C[15] = 256;
            work->f2B0C[16] = 256;

            option_800C4780(work);
            option_800C4A6C(work);
        }
        break;

    case 7:
        for (i = 0; i < 4; i++)
        {
            work->f2AFC[i] = 0;
        }

        for(i = 0; i < 27; i++)
        {
            work->f2A00[i] = work->f2A90[i];
        }

        option_800C449C(work, -30, 24, 60, 12, 255, 1);
        work->f920 = 6;
        break;

    case 9:
        for (i = 0; i < 17; i++)
        {
            work->f2B0C[i] = 0;
        }

        for (i = 0; i < 27; i++)
        {
            work->f2A00[i] = work->f2A90[i];
        }

    case 10:
        option_800C449C(work, -44, 40, 88, 12, 255, 1);
        work->f920 = 8;
        break;
    }
}

void option_800C5698(OptionWork *work)
{
    int press;

    press = work->pad->press;

    switch (work->f29E4)
    {
    case 0:
        if (press & PAD_DOWN)
        {
            work->f29E4 = 1;
            option_800C449C(work, -149, 38, 88, 12, 255, 1);
            GM_SeSet2(0, 63, SE_MENU_CURSOR);
        }
        else if (press & (PAD_LEFT | PAD_RIGHT))
        {
            switch (work->f29E8)
            {
            case 0:
                if (press & PAD_RIGHT)
                {
                    work->f29E8 = 1;
                    option_800C4780(work);
                    GM_SeSet2(0, 63, SE_MENU_TOGGLE);
                }
                break;

            case 1:
                if (press & PAD_RIGHT)
                {
                    work->f29E8 = 2;
                    option_800C4780(work);
                    GM_SeSet2(0, 63, SE_MENU_TOGGLE);
                }
                else if (press & PAD_LEFT)
                {
                    work->f29E8 = 0;
                    option_800C4780(work);
                    GM_SeSet2(0, 63, SE_MENU_TOGGLE);
                }
                break;

            case 2:
                if (press & PAD_LEFT)
                {
                    work->f29E8 = 1;
                    option_800C4780(work);
                    GM_SeSet2(0, 63, SE_MENU_TOGGLE);
                }
                break;
            }
        }
        else if (press & PAD_CROSS)
        {
            option_800C5150(work, 3);
            GM_SeSet2(0, 63, SE_MENU_EXIT);
        }
        break;

    case 1:
        if (press & PAD_UP)
        {
            work->f29E4 = 0;
            option_800C449C(work, -149, -70, 88, 12, 255, 1);
            GM_SeSet2(0, 63, SE_MENU_CURSOR);
        }
        else if (press & PAD_DOWN)
        {
            work->f29E4 = 2;
            option_800C449C(work, 90, 66, 56, 12, 255, 1);
            GM_SeSet2(0, 63, SE_MENU_CURSOR);
        }
        else if (press & (PAD_LEFT | PAD_RIGHT))
        {
            if (work->f29EC == 0)
            {
                if (press & PAD_RIGHT)
                {
                    work->f29EC = 1;
                    option_800C4A6C(work);
                    GM_SeSet2(0, 63, SE_MENU_TOGGLE);
                }
            }
            else if (press & PAD_LEFT)
            {
                work->f29EC = 0;
                option_800C4A6C(work);
                GM_SeSet2(0, 63, SE_MENU_TOGGLE);
            }
        }
        else if (press & PAD_CROSS)
        {
            option_800C5150(work, 3);
            GM_SeSet2(0, 63, SE_MENU_EXIT);
        }
        break;

    case 2:
        if (press & PAD_UP)
        {
            work->f29E4 = 1;
            option_800C449C(work, -149, 38, 88, 12, 255, 1);
            GM_SeSet2(0, 63, SE_MENU_CURSOR);
        }
        else if (!(press & PAD_CIRCLE))
        {
            if (press & PAD_CROSS)
            {
                option_800C5150(work, 3);
                GM_SeSet2(0, 63, SE_MENU_EXIT);
            }
        }
        else
        {
            option_800C5150(work, 3);
            GM_SeSet2(0, 63, SE_MENU_EXIT);
        }
        break;
    }
}

static inline void SetGameStatusFlags( OptionWork *work )
{
            GM_SeSet2( 0, 0x3F, 0x21 ) ;
            if ( work->f924[3] == 0 )
            {
                GM_SetSound( 0xFF000006, 0 ) ;
            }
            else
            {
                GM_SetSound( 0xFF000005, 0 ) ;
            }
            
            if ( work->f924[4] == 1 )
            {
                GM_GameStatusFlag |= STATE_RADIO_OFF;
            }
            else
            {
                GM_GameStatusFlag &= ~( STATE_RADIO_OFF );
            }

            if ( !( work->f2B54 ) )
            {
                GM_GameStatusFlag |= STATE_RADIO_OFF;
            }
            
            if ( work->f924[3] == 1 )
            {
                GM_GameStatusFlag |= STATE_SHOW_LIFEBAR;
            }
            else
            {
                GM_GameStatusFlag &= ~( STATE_SHOW_LIFEBAR );
            }

            if ( work->f924[1] == 1 )
            {
                GM_GameStatusFlag |= STATE_PAUSE_OFF;
            }
            else
            {
                GM_GameStatusFlag &= ~( STATE_PAUSE_OFF );
            }

            if ( work->f924[2] == 1 )
            {
                GM_GameStatusFlag |= 0x100; 
            }
            else
            {
                GM_GameStatusFlag &= ~( 0x100 ); 
            }

            switch ( work->f29E8 )
            {
                case 0:
                GM_GameStatusFlag &= ~( 0x1000 | STATE_NVG | STATE_STUN | STATE_CHAFF ); 
                if ( work->f2B60 )
                {
                    GM_GameStatusFlag |= STATE_THERMG;
                }
                break;
                case 1:
                GM_GameStatusFlag &= ~( 0x1000 | STATE_NVG | STATE_STUN | STATE_CHAFF );
                GM_GameStatusFlag |= STATE_CHAFF ; 
                if ( work->f2B60 )
                {
                    GM_GameStatusFlag |= (STATE_THERMG | STATE_CHAFF ); 
                }
                break;
                case 2:
                GM_GameStatusFlag &= ~( 0x1000 | STATE_NVG | STATE_STUN | STATE_CHAFF );
                GM_GameStatusFlag |= STATE_STUN; 
                if ( work->f2B60 )
                {
                    GM_GameStatusFlag |= (STATE_THERMG | STATE_STUN ); 
                }
                break;
            }

            if ( work->f29EC == 1 )
            {
                GM_GameStatusFlag |= 0x1000;
            }
            else
            {
                GM_GameStatusFlag &= ~( 0x1000 );
            }

            work->f920 = 11;
            work->f2B58 = 0;

            //loc_800C675C
            GM_PadVibration_800ABA3C = 0;
            GM_PadVibration2_800ABA54 = 0;
            mts_set_pad_vibration( 1, 0 );
            mts_set_pad_vibration2( 1, 0 );
            work->f2B50 = 0;    
}


void option_800C5950( OptionWork *work )
{
    int press  = work->pad->press;
    int status = work->pad->status;
    
    switch( work->f920 )
    {
    case 1:
        if ( press & PAD_RIGHT )
        {
            if ( work->f924[ work->f920 ] == 0 )
            {
                option_800C4B68( work ) ;
                GM_SeSet2( 0, 0x3F, SE_MENU_TOGGLE ) ;
            }
        }
        else if ( press & PAD_LEFT )
        {
            if ( work->f924[ work->f920 ] == 1 )
            {
                option_800C4B68( work ) ;
                GM_SeSet2( 0, 0x3F, SE_MENU_TOGGLE ) ;
            }
        }
        else if ( press & PAD_DOWN )
        {
            option_800C5150( work, 1 ) ;
            GM_SeSet2( 0, 0x3F, SE_MENU_CURSOR ) ;
        }
        else if ( press & PAD_CROSS )
        {
            SetGameStatusFlags( work ) ;
        }
    break;
    case 2:
    case 3:
    case 4:
        if ( press & PAD_RIGHT )
        {
            if ( work->f924[ work-> f920 ] == 0 )
            {
                option_800C4B68( work ) ;
                GM_SeSet2( 0, 0x3F, SE_MENU_TOGGLE ) ;
            }
        }
        else if ( press & PAD_LEFT )
        {
            if ( work->f924[ work-> f920 ] == 1 )
            {
                option_800C4B68( work ) ;
                GM_SeSet2( 0, 0x3F, SE_MENU_TOGGLE ) ;
            }
        }
        else if ( press & PAD_UP )
        {
            option_800C5150( work, 0 ) ;
            GM_SeSet2( 0, 0x3F, SE_MENU_CURSOR ) ;
        }       
        else if ( press & PAD_DOWN )
        {
            option_800C5150( work, 1 ) ;
            GM_SeSet2( 0, 0x3F, SE_MENU_CURSOR ) ;
        }     
        else if ( press & PAD_CROSS )
        {
            SetGameStatusFlags( work ) ;
        }
    break;
    case 5:
        if ( status & PAD_RIGHT )
        {
            work->f2B50 = 1;
            if ( work->f924[ work-> f920 ] == 0 )
            {
                option_800C4B68( work ) ;
            }
        }
        else if ( status & PAD_LEFT )
        {
            work->f2B50 = 1;  
            if ( work->f924[ work-> f920 ] == 1 )
            {
                option_800C4B68( work ) ;
            }
        }
        else if ( press & PAD_UP )
        {
            option_800C5150( work, 0 ) ;
            GM_SeSet2( 0, 0x3F, SE_MENU_CURSOR ) ;
        }       
        else if ( press & PAD_DOWN )
        {
            option_800C5150( work, 1 ) ;
            GM_SeSet2( 0, 0x3F, SE_MENU_CURSOR ) ;
        }     
        else if ( press & PAD_CROSS )
        {
            SetGameStatusFlags( work ) ;
        }
    break;
    case 6:
    case 8:
        if ( press & PAD_UP )
        {
            option_800C5150( work, 0 ) ;
            GM_SeSet2( 0, 0x3F, SE_MENU_CURSOR ) ;
        }
        else if ( press & PAD_DOWN )
        {
            option_800C5150( work, 1 ) ;
            GM_SeSet2( 0, 0x3F, SE_MENU_CURSOR ) ;
        }
        else if ( press & PAD_CIRCLE )
        {
            option_800C5150( work, 2 ) ;
            GM_SeSet2( 0, 0x3F, SE_MENU_SELECT ) ;
        }
        else if ( press & PAD_CROSS )
        {
            SetGameStatusFlags( work ) ;
        }
    break;
    case 7:
        if ( press & PAD_CIRCLE )
        {
            option_800C5150( work, 3 ) ;
            GM_SeSet2( 0, 0x3F, SE_MENU_EXIT ) ;
        }        
        else if ( press & PAD_CROSS )
        {
            option_800C5150( work, 3 ) ;
            GM_SeSet2( 0, 0x3F, SE_MENU_EXIT ) ;
        }
    break;
    case 9:
        option_800C5698( work );
    break;
    case 10:
        if ( press & ( PAD_START | PAD_CROSS | PAD_CIRCLE ) )
        {
            SetGameStatusFlags( work ) ;
        }
        else if ( press & PAD_UP )
        {
            option_800C5150( work, 0 ) ;
            GM_SeSet2( 0, 0x3F, SE_MENU_CURSOR ) ;
        }
    break;
    case 11:
        GM_PadVibration_800ABA3C = 0;
        GM_PadVibration2_800ABA54 = 0;
        mts_set_pad_vibration( 1, 0 );
        mts_set_pad_vibration2( 1, 0 );
        work->f2B50 = 0;   
    break;
    }
}

const char option_aOpcaption_800C950C[] = "op_caption";
const char option_aOpsound_800C9518[] = "op_sound";
const char option_aOpvib_800C9524[] = "op_vib";
const char option_aOpvibtest_800C952C[] = "op_vib_test";
const char option_aOpscreen_800C9538[] = "op_screen";
const char option_aOpkeyconfig_800C9544[] = "op_keyconfig";
const char option_aOpexit_800C9554[] = "op_exit";
const char option_aIntoplanguage_800C955C[] = "int_op_language2";

const int option_dword_800C9570 = 0x800C6804;
const int option_dword_800C9574 = 0x800C7990;
const int option_dword_800C9578 = 0x800C7990;
const int option_dword_800C957C = 0x800C7990;
const int option_dword_800C9580 = 0x800C7990;
const int option_dword_800C9584 = 0x800C7990;
const int option_dword_800C9588 = 0x800C7990;
const int option_dword_800C958C = 0x800C7BF8;
const int option_dword_800C9590 = 0x800C7990;
const int option_dword_800C9594 = 0x800C7BF8;
const int option_dword_800C9598 = 0x800C7990;
const int option_dword_800C959C = 0x800C7C14;

#pragma INCLUDE_ASM("asm/overlays/option/option_800C6784.s")
void option_800C6784(OptionWork *work);

void OptionDie_800C7C8C(OptionWork *work)
{
    DG_PRIM *prim;
    int      i;
    void    *buf;

    prim = work->field_24;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    prim = work->field_2C;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    prim = work->field_30;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    prim = work->field_28;
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    for (i = 0; i < 31; i++)
    {
        buf = option_800C3B8C(&work->kcb[i]);
        GV_FreeMemory(2, buf);
    }

    GM_PadVibration_800ABA3C = 0;
    GM_PadVibration2_800ABA54 = 0;

    mts_set_pad_vibration(1, 0);
    mts_set_pad_vibration2(1, 0);

    work->f2B50 = 0;
}

void option_800C7D94(OptionWork *work, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe)
{
    setPolyFT4(poly);
    setRGB0(poly, 128, 128, 128);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);
}

static inline void option_helper_800C7E04(POLY_FT4 *poly, DG_TEX *tex, int uo, int vo)
{
    int u0, u1;
    int v0, v1;

    u0 = tex->off_x;
    u1 = u0 + tex->w + uo;
    v0 = tex->off_y;
    v1 = v0 + tex->h + vo;
    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}

void option_800C7E04(OptionWork *work, int name, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe, int type)
{
    DG_TEX *tex;

    option_800C7D94(work, poly, x0, y0, x1, y1, abe);

    tex = DG_GetTexture(name);
    if (type == 0)
    {
        option_helper_800C7E04(poly, tex, 1, 1);
    }
    else if (type == 1)
    {
        option_helper_800C7E04(poly, tex, 1, 0);
    }
    else if (type == 2)
    {
        option_helper_800C7E04(poly, tex, 0, 1);
    }
    else if (type == 3)
    {
        option_helper_800C7E04(poly, tex, 0, 0);
    }
}

int OptionGetResources_800C7F88(OptionWork *work, int map)
{
    POLY_FT4 *poly;
    int       i;

    GM_CurrentMap_800AB9B0 = map;

    work->field_24 = DG_GetPrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 27, 0, NULL, NULL);
    work->field_28 = DG_GetPrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 9, 0, NULL, NULL);
    work->field_2C = DG_GetPrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 4, 0, NULL, NULL);
    work->field_30 = DG_GetPrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 17, 0, NULL, NULL);

    poly = work->field_34;
    i = 0;

    option_800C7E04(work, GV_StrCode("op_opt"), poly, -44, -12, 44, 0, 1, 0);
    setRGB0(poly, 70, 100, 90);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("op_opt"), poly, -44, -12, 44, 0, 1, 0);
    setRGB0(poly, 70, 100, 90);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode(option_aOpcaption_800C950C), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode(option_aOpsound_800C9518), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode(option_aOpvib_800C9524), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode(option_aOpvibtest_800C952C), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode(option_aOpscreen_800C9538), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode(option_aOpkeyconfig_800C9544), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode(option_aOpexit_800C9554), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("on"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("off"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("stereo"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("monaural"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("on"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("off"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("weak"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("strong"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("line"), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("line"), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("line"), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("line"), poly, 0, 0, 0, 0, 1, 2);
    setRGB0(poly, 0, 0, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("op_back_l"), poly, 0, 0, 0, 0, 0, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("op_back_r"), poly, 0, 0, 0, 0, 0, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode(option_aIntoplanguage_800C955C), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("int_op_language1"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("int_op_language3"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("line"), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    poly = work->field_5D4;
    i = 0;

    option_800C7E04(work, GV_StrCode("sc_back_l"), poly, -160, -112, 0, 112, 0, 0);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("sc_back_r"), poly, 0, -112, 160, 112, 0, 0);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("sc_option"), poly, -141, -101, -53, -60, 1, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode(option_aOpexit_800C9554), poly, 90, 86, 146, 98, 1, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    poly = work->field_674;
    i = 0;

    option_800C7E04(work, GV_StrCode("key_back_l"), poly, -160, -112, 0, 112, 0, 0);
    poly++;
    work->f2B0C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("key_back_r"), poly, 0, -112, 160, 112, 0, 0);
    poly++;
    work->f2B0C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("key_option"), poly, -148, -100, 64, -88, 0, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2B0C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("key_button"), poly, -149, -70, -61, -58, 1, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2B0C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("key_sykan"), poly, -149, 38, -61, 50, 1, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2B0C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("key_reverse"), poly, 29, 41, 93, 47, 1, 0);
    setRGB0(poly, 70, 100, 90);
    poly++;
    work->f2B0C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("key_normal"), poly, -35, 41, 17, 47, 1, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2B0C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode(option_aOpexit_800C9554), poly, 90, 66, 146, 78, 1, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("key_symbol"), poly, -24, -44, 32, 13, 0, 0);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("key_pad"), poly, -51, -63, 49, 66, 1, 0);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("key_a"), poly, -35, -69, -11, -59, 1, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("key_b"), poly, 14, -69, 38, -59, 1, 0);
    setRGB0(poly, 70, 100, 90);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("key_c"), poly, 63, -69, 87, -59, 1, 0);
    setRGB0(poly, 70, 100, 90);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("key_action"), poly, 74, -18, 138, -11, 0, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("key_buki"), poly, -136, -18, -92, -11, 0, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("key_hohuku"), poly, -136, 2, -84, 9, 0, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("key_syukan"), poly, 78, -39, 138, -32, 0, 0);
    setRGB0(poly, 100, 160, 135);
    poly->b0 = 135;
    poly++;
    work->f2AFC[i] = 0;
    i++;

    poly = work->field_46C;
    i = 0;

    option_800C7E04(work, GV_StrCode("cur_lu"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A6C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("cur_ru"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A6C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("cur_ld"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A6C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("cur_rd"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A6C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("cur_u"), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A6C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("cur_d"), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A6C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("cur_l"), poly, 0, 0, 0, 0, 1, 1);
    poly++;
    work->f2A6C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("cur_r"), poly, 0, 0, 0, 0, 1, 1);
    poly++;
    work->f2A6C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode("cur_c"), poly, 0, 0, 0, 0, 1, 3);
    poly++;
    work->f2A6C[i] = 0;
    i++;

    work->f29F0 = 768;
    work->f29F4 = 256;
    work->f29F8 = 768;
    work->f29FC = 276;

    if (GCL_GetOption('e'))
    {
        work->f91C = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->f91C = -1;
    }

    for (i = 0; i < 31; i++)
    {
        work->fEC4[i].string = GCL_ReadString(GCL_GetParamResult());
        work->fEC4[i].num = 0;
        option_800C339C(work, i);
    }

    work->pad = &GV_PadData_800B05C0[2];
    work->f920 = 0;
    work->f29E4 = 0;
    work->f29E8 = 0;
    work->f29EC = 0;
    work->f2B50 = 0;

    for (i = 7; i >= 0; i--)
    {
        work->f924[i] = 0;
    }

    if (GM_GameStatusFlag & 0x4000)
    {
        work->f924[1] = 1;
    }

    if (GM_GameStatusFlag & 0x100)
    {
        work->f924[2] = 1;
    }

    if (GM_GameStatusFlag & 0x2000)
    {
        work->f924[4] = 1;
    }

    if (GM_GameStatusFlag & 0x8000)
    {
        work->f924[3] = 1;
    }

    if (GM_GameStatusFlag & 0x1000)
    {
        work->f29EC = 1;
    }

    if (GM_GameStatusFlag & 0x1)
    {
        work->f29E8 = 1;
    }

    if (GM_GameStatusFlag & 0x2)
    {
        work->f29E8 = 2;
    }

    for (i = 0; i < 31; i++)
    {
        option_800C352C(work, i);
    }

    for (i = 0; i < 31; i++)
    {
        option_800C3B3C(work, i, 0);
    }

    switch (mts_get_pad_vibration_type(1))
    {
    case 0:
        work->f2B54 = 0;
        break;

    case 1:
        work->f2B54 = 1;
        break;

    case 2:
        work->f2B54 = 2;
        break;
    }

    GM_PadVibration_800ABA3C = 0;
    GM_PadVibration2_800ABA54 = 0;

    GM_GameStatusFlag &= ~0x2000;

    work->f2B58 = 0;

    if (GM_GameStatusFlag & 0x8)
    {
        work->f2B60 = 1;
    }
    else
    {
        work->f2B60 = 0;
    }

    return 0;
}

GV_ACT *NewOption_800C9344(int name, int where)
{
    OptionWork *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = (OptionWork *)GV_NewActor(1, sizeof(OptionWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)option_800C6784, (GV_ACTFUNC)OptionDie_800C7C8C, "opt.c");

        if (OptionGetResources_800C7F88(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
