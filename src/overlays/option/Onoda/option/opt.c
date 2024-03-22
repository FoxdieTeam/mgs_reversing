#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "mts/pad/pad.h"
#include "Font/font.h"
#include "Game/linkvarbuf.h"

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
    char     pad2[0x6C];
    int      f2AFC[4];
    int      f2B0C[17];
    int      f2B50;
    int      f2B54;
    int      f2B58;
    char     pad3[0x4];
    int      f2B60;
} OptionWork;

typedef struct _Unknown2
{
    int   num;
    short x;
    short y;
    int   color;
} Unknown2;

extern int    GM_GameStatus_800AB3CC;
extern int    GV_Clock_800AB920;
extern int    GM_CurrentMap_800AB9B0;
extern int    GM_PadVibration_800ABA3C;
extern int    GM_PadVibration2_800ABA54;
extern GV_PAD GV_PadData_800B05C0[4];

extern Unknown2    dword_800C3218[];
extern signed char byte_800C338C[];
extern signed char byte_800C3394[];

extern const char option_aOnw_800C9408[];            // = "on_w"
extern const char option_aOff_800C9410[];            // = "off"
extern const char option_aOn_800C9414[];             // = "on"
extern const char option_aOffw_800C9418[];           // = "off_w"
extern const char option_aIntoplanguagew_800C9420[]; // = "int_op_language1_w"
extern const char option_aIntoplanguage_800C9434[];  // = "int_op_language3"
extern const char option_aIntoplanguage_800C9448[];  // = "int_op_language1"
extern const char option_aIntoplanguagew_800C945C[]; // = "int_op_language3_w"
extern const char option_aStereow_800C9470[];        // = "stereo_w"
extern const char option_aMonaural_800C947C[];       // = "monaural"
extern const char option_aStereo_800C9488[];         // = "stereo"
extern const char option_aMonauralw_800C9490[];      // = "monaural_w"
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

    font_init_kcb_80044BE0(kcb, &rect, work->f29F8, work->f29FC);

    work->fEC4[index].f4 = work->f29F8;
    work->fEC4[index].f6 = work->f29FC;
    work->f29FC += 21;

    font_set_kcb_80044C90(kcb, -1, -1, 0, 6, 2, 0);

    font_set_buffer_80044FD8(kcb, GV_AllocMemory_80015EB8(2, font_get_buffer_size_80044F38(kcb)));

    font_set_color_80044DC4(kcb, 0, dword_800C3218[index].color, 0);
    font_clut_update_80046980(kcb);
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

        font_print_string_800469A4(kcb, string);
        font_update_8004695C(kcb);

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
    font_set_color_80044DC4( kcb, 0, color, 0 );
    font_clut_update_80046980( kcb );
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
    poly_dst = &work->field_24->field_40_pBuffers[GV_Clock_800AB920]->poly_ft4;

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
    poly_dst = &work->field_2C->field_40_pBuffers[GV_Clock_800AB920]->poly_ft4;

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
    poly_dst = &work->field_30->field_40_pBuffers[GV_Clock_800AB920]->poly_ft4;

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
    poly_dst = &work->field_28->field_40_pBuffers[GV_Clock_800AB920]->poly_ft4;

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

#pragma INCLUDE_ASM("asm/overlays/option/option_800C4130.s")
#pragma INCLUDE_ASM("asm/overlays/option/option_800C449C.s")
#pragma INCLUDE_ASM("asm/overlays/option/option_800C4780.s")

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

    tex = DG_GetTexture_8001D830(name);

    x = tex->field_8_offx;
    w = tex->field_A_width;
    y = tex->field_9_offy;
    h = tex->field_B_height;

    poly->u0 = x;
    poly->v0 = y;
    poly->u1 = x + w + 1;
    poly->v1 = y;
    poly->u2 = x;
    poly->v2 = y + h + 1;
    poly->u3 = x + w + 1;
    poly->v3 = y + h + 1;

    poly->tpage = tex->field_4_tPage;
    poly->clut = tex->field_6_clut;
}

#pragma INCLUDE_ASM("asm/overlays/option/option_800C4B68.s")
#pragma INCLUDE_ASM("asm/overlays/option/option_800C5150.s")
#pragma INCLUDE_ASM("asm/overlays/option/option_800C5698.s")
#pragma INCLUDE_ASM("asm/overlays/option/option_800C5950.s")
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
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    prim = work->field_2C;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    prim = work->field_30;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    prim = work->field_28;
    if (prim != NULL)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }

    for (i = 0; i < 31; i++)
    {
        buf = option_800C3B8C(&work->kcb[i]);
        GV_FreeMemory_80015FD0(2, buf);
    }

    GM_PadVibration_800ABA3C = 0;
    GM_PadVibration2_800ABA54 = 0;

    mts_set_pad_vibration_8008C408(1, 0);
    mts_set_pad_vibration2_8008C454(1, 0);

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

    u0 = tex->field_8_offx;
    u1 = u0 + tex->field_A_width + uo;
    v0 = tex->field_9_offy;
    v1 = v0 + tex->field_B_height + vo;
    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);

    poly->tpage = tex->field_4_tPage;
    poly->clut = tex->field_6_clut;
}

void option_800C7E04(OptionWork *work, int name, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe, int type)
{
    DG_TEX *tex;

    option_800C7D94(work, poly, x0, y0, x1, y1, abe);

    tex = DG_GetTexture_8001D830(name);
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

    work->field_24 = DG_GetPrim(0x812, 27, 0, NULL, NULL);
    work->field_28 = DG_GetPrim(0x812, 9, 0, NULL, NULL);
    work->field_2C = DG_GetPrim(0x812, 4, 0, NULL, NULL);
    work->field_30 = DG_GetPrim(0x812, 17, 0, NULL, NULL);

    poly = work->field_34;
    i = 0;

    option_800C7E04(work, GV_StrCode_80016CCC("op_opt"), poly, -44, -12, 44, 0, 1, 0);
    setRGB0(poly, 70, 100, 90);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("op_opt"), poly, -44, -12, 44, 0, 1, 0);
    setRGB0(poly, 70, 100, 90);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC(option_aOpcaption_800C950C), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC(option_aOpsound_800C9518), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC(option_aOpvib_800C9524), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC(option_aOpvibtest_800C952C), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC(option_aOpscreen_800C9538), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC(option_aOpkeyconfig_800C9544), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC(option_aOpexit_800C9554), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC(option_aOn_800C9414), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC(option_aOff_800C9410), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC(option_aStereo_800C9488), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC(option_aMonaural_800C947C), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC(option_aOn_800C9414), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC(option_aOff_800C9410), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("weak"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("strong"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("line"), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("line"), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("line"), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("line"), poly, 0, 0, 0, 0, 1, 2);
    setRGB0(poly, 0, 0, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("op_back_l"), poly, 0, 0, 0, 0, 0, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("op_back_r"), poly, 0, 0, 0, 0, 0, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC(option_aIntoplanguage_800C955C), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC(option_aIntoplanguage_800C9448), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC(option_aIntoplanguage_800C9434), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A00[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("line"), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A00[i] = 0;
    i++;

    poly = work->field_5D4;
    i = 0;

    option_800C7E04(work, GV_StrCode_80016CCC("sc_back_l"), poly, -160, -112, 0, 112, 0, 0);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("sc_back_r"), poly, 0, -112, 160, 112, 0, 0);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("sc_option"), poly, -141, -101, -53, -60, 1, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC(option_aOpexit_800C9554), poly, 90, 86, 146, 98, 1, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    poly = work->field_674;
    i = 0;

    option_800C7E04(work, GV_StrCode_80016CCC("key_back_l"), poly, -160, -112, 0, 112, 0, 0);
    poly++;
    work->f2B0C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("key_back_r"), poly, 0, -112, 160, 112, 0, 0);
    poly++;
    work->f2B0C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("key_option"), poly, -148, -100, 64, -88, 0, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2B0C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("key_button"), poly, -149, -70, -61, -58, 1, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2B0C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("key_sykan"), poly, -149, 38, -61, 50, 1, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2B0C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("key_reverse"), poly, 29, 41, 93, 47, 1, 0);
    setRGB0(poly, 70, 100, 90);
    poly++;
    work->f2B0C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("key_normal"), poly, -35, 41, 17, 47, 1, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2B0C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC(option_aOpexit_800C9554), poly, 90, 66, 146, 78, 1, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("key_symbol"), poly, -24, -44, 32, 13, 0, 0);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("key_pad"), poly, -51, -63, 49, 66, 1, 0);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("key_a"), poly, -35, -69, -11, -59, 1, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("key_b"), poly, 14, -69, 38, -59, 1, 0);
    setRGB0(poly, 70, 100, 90);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("key_c"), poly, 63, -69, 87, -59, 1, 0);
    setRGB0(poly, 70, 100, 90);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("key_action"), poly, 74, -18, 138, -11, 0, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("key_buki"), poly, -136, -18, -92, -11, 0, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("key_hohuku"), poly, -136, 2, -84, 9, 0, 0);
    setRGB0(poly, 100, 160, 135);
    poly++;
    work->f2AFC[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("key_syukan"), poly, 78, -39, 138, -32, 0, 0);
    setRGB0(poly, 100, 160, 135);
    poly->b0 = 135;
    poly++;
    work->f2AFC[i] = 0;
    i++;

    poly = work->field_46C;
    i = 0;

    option_800C7E04(work, GV_StrCode_80016CCC("cur_lu"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A6C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("cur_ru"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A6C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("cur_ld"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A6C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("cur_rd"), poly, 0, 0, 0, 0, 1, 0);
    poly++;
    work->f2A6C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("cur_u"), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A6C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("cur_d"), poly, 0, 0, 0, 0, 1, 2);
    poly++;
    work->f2A6C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("cur_l"), poly, 0, 0, 0, 0, 1, 1);
    poly++;
    work->f2A6C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("cur_r"), poly, 0, 0, 0, 0, 1, 1);
    poly++;
    work->f2A6C[i] = 0;
    i++;

    option_800C7E04(work, GV_StrCode_80016CCC("cur_c"), poly, 0, 0, 0, 0, 1, 3);
    poly++;
    work->f2A6C[i] = 0;
    i++;

    work->f29F0 = 768;
    work->f29F4 = 256;
    work->f29F8 = 768;
    work->f29FC = 276;

    if (GCL_GetOption_80020968('e'))
    {
        work->f91C = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        work->f91C = -1;
    }

    for (i = 0; i < 31; i++)
    {
        work->fEC4[i].string = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());
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

    switch (mts_get_pad_vibration_type_8008C4BC(1))
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

GV_ACT * NewOption_800C9344(int name, int where)
{
    OptionWork *work;

    GM_GameStatus_800AB3CC |= 0x4A6000;

    work = (OptionWork *)GV_NewActor_800150E4(1, sizeof(OptionWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)option_800C6784, (TActorFunction)OptionDie_800C7C8C, "opt.c");

        if (OptionGetResources_800C7F88(work, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
