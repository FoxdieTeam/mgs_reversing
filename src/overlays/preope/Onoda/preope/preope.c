#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"

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

typedef struct PreopeWork
{
    GV_ACT   actor;
    GV_PAD  *pad;
    DG_PRIM *field_24;
    DG_PRIM *field_28;
    POLY_FT4 field_2C[6];
    POLY_FT4 field_11C[9];
    int      field_284[6];
    int      field_29C[9];
    int      field_2C0;
    int      field_2C4;
    KCB      field_2C8[4];
    char     pad378[0x14];
    DR_TPAGE field_38C;
    Unknown  field_394[4];
    Unknown  field_714[72];
    Unknown  field_4614[112];
    int      field_A814;
    int      field_A818;
    int      clut_x;
    int      clut_y;
    int      field_A824;
    int      field_A828;
    int      field_A82C;
    GV_ACT  *field_A830;
    GV_ACT  *field_A834;
    int      field_A838;
    int      field_A83C;
    int      map;
} PreopeWork;

// FIXME: it's the same struct (but different data) as in change.c (in change overlay)
typedef struct _Unknown2
{
    int   num;
    short x;
    short y;
    int   color;
} Unknown2;

Unknown2 dword_800C3218[4] = {
    {1, 160, 195, 0x6739},
    {1, 160, 185, 0x6739},
    {1, 160, 205, 0x6739},
    {1, 160, 195, 0x6739},
};

// Same as byte_800C3260 in change overlay
signed char byte_800C3248[] = {
    -1, 0, 1, 0, 0, 1, 0, -1,
};

extern int    GM_GameStatus_800AB3CC;
extern int    GV_Clock_800AB920;
extern GV_PAD GV_PadData_800B05C0[4];

GV_ACT * NewPreMet1_800C6F20(int, int *, Unknown *);
GV_ACT * NewPreMet2_800C6F20(int, int *, Unknown *);

#define EXEC_LEVEL 1

// Duplicate of Change_800C364C
void Preope_800C32E0(PreopeWork *work, int index)
{
    RECT rect;
    KCB *kcb;

    kcb = &work->field_2C8[index];

    rect.x = work->field_A814;
    rect.y = work->field_A818;
    rect.w = 64;
    rect.h = 21;

    work->field_394[index].f0 = work->field_A814;
    work->field_394[index].f2 = work->field_A818;
    work->field_A818 += 21;

    font_init_kcb_80044BE0(kcb, &rect, work->clut_x, work->clut_y);

    work->field_394[index].f4 = work->clut_x;
    work->field_394[index].f6 = work->clut_y;
    work->clut_y += 21;

    font_set_kcb_80044C90(kcb, -1, -1, 0, 6, 2, 0);

    font_set_buffer_80044FD8(kcb, GV_AllocMemory_80015EB8(2, font_get_buffer_size_80044F38(kcb)));
    font_set_color_80044DC4(kcb, 0, dword_800C3218[index].color, 0);
    font_clut_update_80046980(kcb);
}

// Duplicate of Change_800C378C
void Preope_800C3428(PreopeWork *work, int index)
{
    KCB      *kcb;
    char     *string;
    Unknown2 *unknown;

    string = work->field_394[index].string;

    if (string)
    {
        kcb = &work->field_2C8[index];

        font_print_string_800469A4(kcb, string);
        font_update_8004695C(kcb);
        font_clut_update_80046980(kcb);

        work->field_394[index].rect.w = kcb->char_arr[7];
        work->field_394[index].rect.h = kcb->short3 - 1;

        unknown = &dword_800C3218[index];

        if (unknown->num == 0)
        {
            work->field_394[index].rect.x = unknown->x;
            work->field_394[index].rect.y = unknown->y;
        }
        else if (unknown->num == 1)
        {
            work->field_394[index].rect.x = unknown->x - kcb->char_arr[7] / 2;
            work->field_394[index].rect.y = unknown->y - kcb->short3 / 2;
        }

        work->field_394[index].string = NULL;
        work->field_394[index].num = 1;
    }
}

// Duplicate of Change_800C38D0
void Preope_800C356C(PreopeWork *work, char *ot)
{
    int       found;
    int       index;
    int       i;
    SPRT     *sprt;
    SPRT     *sprt2;
    int       j;
    DR_TPAGE *tpage;

    found = 0;

    index = 0;
    for (i = 0; i < 4; i++)
    {
        // BUG: The index doesn't increment on continue
        if (work->field_394[index].num != 1)
        {
            continue;
        }

        found = 1;

        sprt = &work->field_394[index].sprt[GV_Clock_800AB920];
        LSTORE(0x808080, &sprt->r0);
        LCOPY(&work->field_394[index].rect.x, &sprt->x0);
        LCOPY(&work->field_394[index].rect.w, &sprt->w);
        sprt->u0 = 0;
        sprt->v0 = work->field_394[index].f2;
        sprt->clut = getClut(work->field_394[index].f4, work->field_394[index].f6);
        setSprt(sprt);
        addPrim(ot, sprt);

        sprt2 = work->field_394[index].sprt2[GV_Clock_800AB920];
        for (j = 0; j < 8; j += 2)
        {
            *sprt2 = *sprt;
            LSTORE(0x64000000, &sprt2->r0);
            sprt2->x0 += byte_800C3248[j];
            sprt2->y0 += byte_800C3248[j + 1];
            addPrim(ot, sprt2);
            sprt2++;
        }

        index++;
    }

    if (found != 0)
    {
        tpage = &work->field_38C;
        setDrawTPage(tpage, 1, 0, getTPage(0, 0, 832, 256));
        addPrim(ot, tpage);
    }
}

// Duplicate of PreMet1SetColor_800C5738
void PreopeSetColor_800C37D0(PreopeWork *work, int index, int fore)
{
    KCB *kcb;

    kcb = &work->field_2C8[index];
    font_set_color_80044DC4(kcb, 0, fore, 0);
    font_clut_update_80046980(kcb);
}

// Similar to PreMet1_800C5794
void Preope_800C3820(PreopeWork *work)
{
    int i;
    for (i = 5; i >= 0; i--)
    {
        work->field_284[i] = 0;
    }
}

// Similar to PreMet1_800C5794
void Preope_800C3840(PreopeWork *work)
{
    int i;
    for (i = 8; i >= 0; i--)
    {
        work->field_29C[i] = 0;
    }
}

// Identical to title_open_800C4C38
void Preope_800C3860(PreopeWork *work, int x0, int y0, int xsize, int ysize, int color, int mode)
{
    POLY_FT4 *polys;
    int       i;

    polys = work->field_11C;
    for (i = 0; i < 9; i++)
    {
        work->field_29C[i] = 0x200;
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

void PreopeShadePacks_800C3B44(PreopeWork *work)
{
    POLY_FT4 *poly_dst;
    POLY_FT4 *poly_src;
    int       i;
    int       r0, g0, b0;

    poly_dst = &work->field_24->field_40_pBuffers[GV_Clock_800AB920]->poly_ft4;
    poly_src = work->field_2C;

    for (i = 0; i < 6; poly_dst++, poly_src++, i++)
    {
        *poly_dst = *poly_src;

        if (work->field_2C4 == 3)
        {
            r0 = poly_dst->r0;
            g0 = poly_dst->g0;
            b0 = poly_dst->b0;
            setRGB0(poly_dst, r0 - r0 * work->field_A824 / 16,
                              g0 - g0 * work->field_A824 / 16,
                              b0 - b0 * work->field_A824 / 16);
        }
        else if (work->field_2C4 == 4 && work->field_A828 == 0)
        {
            r0 = poly_dst->r0;
            g0 = poly_dst->g0;
            b0 = poly_dst->b0;
            setRGB0(poly_dst, r0 - r0 * work->field_A824 / 16,
                              g0 - g0 * work->field_A824 / 16,
                              b0 - b0 * work->field_A824 / 16);
        }
        else if (work->field_2C4 == 5 && work->field_A82C == 0)
        {
            r0 = poly_dst->r0;
            g0 = poly_dst->g0;
            b0 = poly_dst->b0;
            setRGB0(poly_dst, r0 - r0 * work->field_A824 / 16,
                              g0 - g0 * work->field_A824 / 16,
                              b0 - b0 * work->field_A824 / 16);
        }
        else if (work->field_2C4 == 4 && work->field_A828 == 2 && work->field_A824 >= 16)
        {
            r0 = poly_dst->r0;
            g0 = poly_dst->g0;
            b0 = poly_dst->b0;
            setRGB0(poly_dst, r0 * (work->field_A824 - 16) / 16,
                              g0 * (work->field_A824 - 16) / 16,
                              b0 * (work->field_A824 - 16) / 16);
        }
        else if (work->field_2C4 == 5 && work->field_A82C == 2 && work->field_A824 >= 16)
        {
            r0 = poly_dst->r0;
            g0 = poly_dst->g0;
            b0 = poly_dst->b0;
            setRGB0(poly_dst, r0 * (work->field_A824 - 16) / 16,
                              g0 * (work->field_A824 - 16) / 16,
                              b0 * (work->field_A824 - 16) / 16);
        }

        SSTOREL(work->field_284[i], poly_dst); // some modification of POLY_FT4 tag?
    }

    poly_dst = &work->field_28->field_40_pBuffers[GV_Clock_800AB920]->poly_ft4;
    poly_src = work->field_11C;

    for (i = 0; i < 9; poly_dst++, poly_src++, i++)
    {
        *poly_dst = *poly_src;
        SSTOREL(work->field_29C[i], poly_dst); // some modification of POLY_FT4 tag?
    }
}

static inline int get_color(int shade)
{
    return (shade << 10) | (shade << 5) | shade;
}

void Preope_800C3F34(PreopeWork *work)
{
    int i;

    for (i = 0; i < 4; i++)
    {
        PreopeSetColor_800C37D0(work, i, get_color(0));
    }

    switch (work->field_2C4)
    {
    case 0:
        PreopeSetColor_800C37D0(work, 0, get_color(25));
        break;
    case 1:
        PreopeSetColor_800C37D0(work, 1, get_color(25));
        PreopeSetColor_800C37D0(work, 2, get_color(25));
        break;
    case 2:
        PreopeSetColor_800C37D0(work, 3, get_color(25));
        break;
    }
}

void preope_800C3FE0(PreopeWork *work)
{
    int press;

    press = work->pad->press;
    switch (work->field_2C4)
    {
    case 0:
        if ((press & PAD_DOWN) != 0)
        {
            work->field_2C4 = 1;
            Preope_800C3860(work, -90, 6, 180, 6, 255, 0);
            GM_SeSet2_80032968(0, 63, 31);
        }
        else if ((press & PAD_CIRCLE) != 0)
        {
            work->field_2C4 = 4;
            work->field_A828 = 0;
            work->field_A824 = 0;
            Preope_800C3840(work);
            GM_SeSet2_80032968(0, 63, 32);
        }
        else if ((press & PAD_CROSS) != 0)
        {
            work->field_2C4 = 3;
            GM_SeSet2_80032968(0, 63, 33);
            work->field_A824 = 0;
            Preope_800C3840(work);
        }
        break;

    case 1:
        if ((press & PAD_DOWN) != 0)
        {
            work->field_2C4 = 2;
            Preope_800C3860(work, -28, 46, 56, 12, 255, 1);
            GM_SeSet2_80032968(0, 63, 31);
        }
        else if ((press & PAD_UP) != 0)
        {
            work->field_2C4 = 0;
            Preope_800C3860(work, -42, -42, 84, 6, 255, 0);
            GM_SeSet2_80032968(0, 63, 31);
        }
        else if ((press & PAD_CIRCLE) != 0)
        {
            work->field_2C4 = 5;
            work->field_A82C = 0;
            work->field_A824 = 0;
            Preope_800C3840(work);
            GM_SeSet2_80032968(0, 63, 32);
        }
        else if ((press & PAD_CROSS) != 0)
        {
            work->field_2C4 = 3;
            GM_SeSet2_80032968(0, 63, 33);
            work->field_A824 = 0;
            Preope_800C3840(work);
        }
        break;

    case 2:
        if ((press & PAD_UP) != 0)
        {
            work->field_2C4 = 1;
            Preope_800C3860(work, -90, 6, 180, 6, 255, 0);
            GM_SeSet2_80032968(0, 63, 31);
        }
        else if ((press & PAD_CIRCLE) != 0)
        {
            work->field_2C4 = 3;
            GM_SeSet2_80032968(0, 63, 33);
            work->field_A824 = 0;
            Preope_800C3840(work);
        }
        else if ((press & PAD_CROSS) != 0)
        {
            work->field_2C4 = 3;
            GM_SeSet2_80032968(0, 63, 33);
            work->field_A824 = 0;
            Preope_800C3840(work);
        }
        break;

    case 3:
        if (work->field_A824 > 16)
        {
            GCL_ExecProc_8001FF2C(work->field_2C0, NULL);
            GV_DestroyActor_800151C8(&work->actor);
        }
        break;
    }
}

void preope_800C41D4(PreopeWork *work)
{
    switch (work->field_2C4)
    {
    case 4:
        switch (work->field_A828)
        {
        case 0:
            if (work->field_A824 == 16)
            {
                Preope_800C3820(work);
                work->field_A838 = 0;
                work->field_A830 = NewPreMet1_800C6F20(work->map, &work->field_A838, work->field_714);
                work->field_A828 = 1;
            }
            break;

        case 1:
            if (work->field_A838 == work->field_A828)
            {
                work->field_A828 = 2;
                work->field_A824 = 0;
            }
            break;

        case 2:
            if (work->field_A824 == 16)
            {
                work->field_284[0] = 768;
                work->field_284[1] = 768;
                work->field_284[2] = 256;
                work->field_284[3] = 256;
                work->field_284[4] = 256;
                work->field_284[5] = 256;
                GV_DestroyActor_800151C8(work->field_A830);
            }
            else if (work->field_A824 == 32)
            {
                work->field_2C4 = 0;
                Preope_800C3860(work, -42, -42, 84, 6, 255, 0);
                work->field_A824 = 0;
            }
        }
        break;

    case 5:
        switch (work->field_A82C)
        {
        case 0:
            if (work->field_A824 == 16)
            {
                Preope_800C3820(work);
                work->field_A83C = 0;
                work->field_A834 = NewPreMet2_800C6F20(work->map, &work->field_A83C, work->field_4614);
                work->field_A82C = 1;
            }
            break;

        case 1:
            if (work->field_A83C == 1)
            {
                work->field_A82C = 2;
                work->field_A824 = 0;
            }
            break;

        case 2:
            if (work->field_A824 == 16)
            {
                work->field_284[0] = 768;
                work->field_284[1] = 768;
                work->field_284[2] = 256;
                work->field_284[3] = 256;
                work->field_284[4] = 256;
                work->field_284[5] = 256;
                GV_DestroyActor_800151C8(work->field_A834);
            }
            else if (work->field_A824 == 32)
            {
                work->field_2C4 = 1;
                Preope_800C3860(work, -90, 6, 180, 6, 255, 0);
                work->field_A824 = 0;
            }
            break;
        }
        break;
    }
}

void PreopeAct_800C4424(PreopeWork *work)
{
    preope_800C3FE0(work);
    preope_800C41D4(work);
    Preope_800C3F34(work);
    Preope_800C356C(work, DG_ChanlOTag(1));
    PreopeShadePacks_800C3B44(work);
    work->field_A824++;
}

void PreopeDie_800C449C(PreopeWork *work)
{
    DG_PRIM *prim;

    prim = work->field_24;
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
}

// Duplicate of camera_800CE4F8
void Preope_800C4504(PreopeWork *work, POLY_FT4 *pPoly, int x0, int y0, int x1, int y1, int semiTrans)
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
void Preope_800C4574(PreopeWork *work, int hashCode, POLY_FT4 *pPoly, int x0, int y0, int x1, int y1, int semiTrans, int arg9)
{
    DG_TEX *tex;
    Preope_800C4504(work, pPoly, x0, y0, x1, y1, semiTrans);
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

int PreopeGetResources_800C46F8(PreopeWork *work, int map)
{
    POLY_FT4 *poly, *poly2;
    int       i, j;
    int       index;

    GM_CurrentMap_800AB9B0 = map;

    work->map = map;
    work->field_A814 = 832;
    work->clut_x = 832;
    work->field_A818 = 256;
    work->clut_y = 276;

    work->field_24 = DG_GetPrim(0x812, 6, 0, NULL, NULL);
    work->field_28 = DG_GetPrim(0x812, 9, 0, NULL, NULL);

    poly = work->field_2C;
    i = 0;

    Preope_800C4574(work, GV_StrCode_80016CCC("pre_back_l"), poly, -160, -112, 0, 112, 0, 0);
    poly++;
    work->field_284[i] = 768;
    i++;

    Preope_800C4574(work, GV_StrCode_80016CCC("pre_back_r"), poly, 0, -112, 160, 112, 0, 0);
    poly++;
    work->field_284[i] = 768;
    i++;

    Preope_800C4574(work, GV_StrCode_80016CCC("pre_pre"), poly, -82, -94, 82, -82, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_284[i] = 256;
    i++;

    Preope_800C4574(work, GV_StrCode_80016CCC("pre_met"), poly, -42, -42, 42, -36, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_284[i] = 256;
    i++;

    Preope_800C4574(work, GV_StrCode_80016CCC("pre_met2"), poly, -90, 6, 90, 12, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_284[i] = 256;
    i++;

    Preope_800C4574(work, GV_StrCode_80016CCC("pre_exit"), poly, -28, 46, 28, 58, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_284[i] = 256;
    i++;

    poly2 = work->field_11C;
    i = 0;

    Preope_800C4574(work, GV_StrCode_80016CCC("cur_lu"), poly2, 0, 0, 0, 0, 1, 0);
    poly2++;
    work->field_29C[i] = 0;
    i++;

    Preope_800C4574(work, GV_StrCode_80016CCC("cur_ru"), poly2, 0, 0, 0, 0, 1, 0);
    poly2++;
    work->field_29C[i] = 0;
    i++;

    Preope_800C4574(work, GV_StrCode_80016CCC("cur_ld"), poly2, 0, 0, 0, 0, 1, 0);
    poly2++;
    work->field_29C[i] = 0;
    i++;

    Preope_800C4574(work, GV_StrCode_80016CCC("cur_rd"), poly2, 0, 0, 0, 0, 1, 0);
    poly2++;
    work->field_29C[i] = 0;
    i++;

    Preope_800C4574(work, GV_StrCode_80016CCC("cur_u"), poly2, 0, 0, 0, 0, 1, 2);
    poly2++;
    work->field_29C[i] = 0;
    i++;

    Preope_800C4574(work, GV_StrCode_80016CCC("cur_d"), poly2, 0, 0, 0, 0, 1, 2);
    poly2++;
    work->field_29C[i] = 0;
    i++;

    Preope_800C4574(work, GV_StrCode_80016CCC("cur_l"), poly2, 0, 0, 0, 0, 1, 1);
    poly2++;
    work->field_29C[i] = 0;
    i++;

    Preope_800C4574(work, GV_StrCode_80016CCC("cur_r"), poly2, 0, 0, 0, 0, 1, 1);
    poly2++;
    work->field_29C[i] = 0;
    i++;

    Preope_800C4574(work, GV_StrCode_80016CCC("cur_c"), poly2, 0, 0, 0, 0, 1, 3);
    poly2++;
    work->field_29C[i] = 0;
    i++;

    if (GCL_GetOption_80020968('e'))
    {
        work->field_2C0 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else
    {
        work->field_2C0 = -1;
    }

    for (i = 0; i < 4; i++)
    {
        work->field_394[i].string = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());
        work->field_394[i].num = 0;
        Preope_800C32E0(work, i);
    }

    index = 0;
    for (j = 0; j < 9; j++)
    {
        for (i = 0; i < 8; i++)
        {
            work->field_714[index].string = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());
            index++;
        }
    }

    index = 0;
    for (j = 0; j < 14; j++)
    {
        for (i = 0; i < 8; i++)
        {
            work->field_4614[index].string = GCL_Read_String_80020A70(GCL_Get_Param_Result_80020AA4());
            index++;
        }
    }

    for (i = 0; i < 4; i++)
    {
        Preope_800C3428(work, i);
    }

    work->pad = &GV_PadData_800B05C0[2];

    work->field_2C4 = 0;
    Preope_800C3860(work, -42, -42, 84, 6, 255, 0);
    work->field_A824 = 0;
    return 0;
}

GV_ACT *NewPreope_800C4DA4(int name, int where, int argc, char **argv)
{
    PreopeWork *work;

    GM_GameStatus_800AB3CC |=
        GAME_FLAG_BIT_23 | GAME_FLAG_BIT_14 | GAME_FLAG_BIT_15 | GAME_FLAG_BIT_20 | GAME_FLAG_BIT_18;

    work = (PreopeWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(PreopeWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)PreopeAct_800C4424, (TActorFunction)PreopeDie_800C449C,
                                  "preope.c");
        if (PreopeGetResources_800C46F8(work, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
