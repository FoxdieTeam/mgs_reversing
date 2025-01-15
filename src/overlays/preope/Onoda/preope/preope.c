#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"
#include "SD/g_sound.h"

// FIXME: it's the same struct as in change.c (in change overlay)
typedef struct _Unknown
{
    SPRT  text_sprt[2];
    SPRT  text_outline_sprt[2][4]; // there's a subtle black outline around the text
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
    POLY_FT4 button_highlight_parts[9];
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
    int      fadeout_timer; // when a menu item is clicked, the buttons/screen nicely fade out
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
signed char text_outline_direction_offsets_800C3248[] = {
    -1,  0,
     1,  0,
     0,  1,
     0, -1,
};

extern int    GV_Clock;
extern GV_PAD GV_PadData_800B05C0[4];

GV_ACT *NewPreMet1_800C6F20(int, int *, Unknown *);
GV_ACT *NewPreMet2_800C6F20(int, int *, Unknown *);

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

    font_init_kcb(kcb, &rect, work->clut_x, work->clut_y);

    work->field_394[index].f4 = work->clut_x;
    work->field_394[index].f6 = work->clut_y;
    work->clut_y += 21;

    font_set_kcb(kcb, -1, -1, 0, 6, 2, 0);

    font_set_buffer(kcb, GV_AllocMemory(GV_NORMAL_MEMORY, font_get_buffer_size(kcb)));
    font_set_color(kcb, 0, dword_800C3218[index].color, 0);
    font_clut_update(kcb);
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

        font_print_string(kcb, string);
        font_update(kcb);
        font_clut_update(kcb);

        work->field_394[index].rect.w = kcb->max_width;
        work->field_394[index].rect.h = kcb->short3 - 1;

        unknown = &dword_800C3218[index];

        if (unknown->num == 0)
        {
            work->field_394[index].rect.x = unknown->x;
            work->field_394[index].rect.y = unknown->y;
        }
        else if (unknown->num == 1)
        {
            work->field_394[index].rect.x = unknown->x - kcb->max_width / 2;
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
    SPRT     *text_sprt;
    SPRT     *text_outline_sprt;
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

        text_sprt = &work->field_394[index].text_sprt[GV_Clock];
        LSTORE(0x808080, &text_sprt->r0);
        LCOPY(&work->field_394[index].rect.x, &text_sprt->x0);
        LCOPY(&work->field_394[index].rect.w, &text_sprt->w);
        text_sprt->u0 = 0;
        text_sprt->v0 = work->field_394[index].f2;
        text_sprt->clut = getClut(work->field_394[index].f4, work->field_394[index].f6);
        setSprt(text_sprt);
        addPrim(ot, text_sprt);

        // There's a subtle black outline around the text (the sprite added a couple lines above).
        // To display it there's a neat trick here: just display the same text sprite but
        // black and shifted by a ~pixel in each direction.
        text_outline_sprt = work->field_394[index].text_outline_sprt[GV_Clock];
        for (j = 0; j < 8; j += 2)
        {
            *text_outline_sprt = *text_sprt;
            LSTORE(0x64000000, &text_outline_sprt->r0);
            text_outline_sprt->x0 += text_outline_direction_offsets_800C3248[j];
            text_outline_sprt->y0 += text_outline_direction_offsets_800C3248[j + 1];
            addPrim(ot, text_outline_sprt);
            text_outline_sprt++;
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
    font_set_color(kcb, 0, fore, 0);
    font_clut_update(kcb);
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
void PreopeHideButtonHighlight_800C3840(PreopeWork *work)
{
    int i;
    for (i = 8; i >= 0; i--)
    {
        work->field_29C[i] = 0;
    }
}

// Identical to title_open_800C4C38
void PreopeMoveButtonHighlight_800C3860(PreopeWork *work, int x0, int y0, int xsize, int ysize, int color, int mode)
{
    POLY_FT4 *polys;
    int       i;

    polys = work->button_highlight_parts;
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

    poly_dst = &work->field_24->packs[GV_Clock]->poly_ft4;
    poly_src = work->field_2C;

    for (i = 0; i < 6; poly_dst++, poly_src++, i++)
    {
        *poly_dst = *poly_src;

        if (work->field_2C4 == 3)
        {
            r0 = poly_dst->r0;
            g0 = poly_dst->g0;
            b0 = poly_dst->b0;
            setRGB0(poly_dst, r0 - r0 * work->fadeout_timer / 16,
                              g0 - g0 * work->fadeout_timer / 16,
                              b0 - b0 * work->fadeout_timer / 16);
        }
        else if (work->field_2C4 == 4 && work->field_A828 == 0)
        {
            r0 = poly_dst->r0;
            g0 = poly_dst->g0;
            b0 = poly_dst->b0;
            setRGB0(poly_dst, r0 - r0 * work->fadeout_timer / 16,
                              g0 - g0 * work->fadeout_timer / 16,
                              b0 - b0 * work->fadeout_timer / 16);
        }
        else if (work->field_2C4 == 5 && work->field_A82C == 0)
        {
            r0 = poly_dst->r0;
            g0 = poly_dst->g0;
            b0 = poly_dst->b0;
            setRGB0(poly_dst, r0 - r0 * work->fadeout_timer / 16,
                              g0 - g0 * work->fadeout_timer / 16,
                              b0 - b0 * work->fadeout_timer / 16);
        }
        else if (work->field_2C4 == 4 && work->field_A828 == 2 && work->fadeout_timer >= 16)
        {
            r0 = poly_dst->r0;
            g0 = poly_dst->g0;
            b0 = poly_dst->b0;
            setRGB0(poly_dst, r0 * (work->fadeout_timer - 16) / 16,
                              g0 * (work->fadeout_timer - 16) / 16,
                              b0 * (work->fadeout_timer - 16) / 16);
        }
        else if (work->field_2C4 == 5 && work->field_A82C == 2 && work->fadeout_timer >= 16)
        {
            r0 = poly_dst->r0;
            g0 = poly_dst->g0;
            b0 = poly_dst->b0;
            setRGB0(poly_dst, r0 * (work->fadeout_timer - 16) / 16,
                              g0 * (work->fadeout_timer - 16) / 16,
                              b0 * (work->fadeout_timer - 16) / 16);
        }

        SSTOREL(work->field_284[i], poly_dst); // some modification of POLY_FT4 tag?
    }

    poly_dst = &work->field_28->packs[GV_Clock]->poly_ft4;
    poly_src = work->button_highlight_parts;

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

void PreopeProcessPad_800C3FE0(PreopeWork *work)
{
    int press;

    press = work->pad->press;
    switch (work->field_2C4)
    {
    case 0:
        if (press & PAD_DOWN)
        {
            work->field_2C4 = 1;
            PreopeMoveButtonHighlight_800C3860(work, -90, 6, 180, 6, 255, 0);
            GM_SeSet2(0, 63, SE_MENU_CURSOR);
        }
        else if (press & PAD_CIRCLE)
        {
            work->field_2C4 = 4;
            work->field_A828 = 0;
            work->fadeout_timer = 0;
            PreopeHideButtonHighlight_800C3840(work);
            GM_SeSet2(0, 63, SE_MENU_SELECT);
        }
        else if (press & PAD_CROSS)
        {
            work->field_2C4 = 3;
            GM_SeSet2(0, 63, SE_MENU_EXIT);
            work->fadeout_timer = 0;
            PreopeHideButtonHighlight_800C3840(work);
        }
        break;

    case 1:
        if (press & PAD_DOWN)
        {
            work->field_2C4 = 2;
            PreopeMoveButtonHighlight_800C3860(work, -28, 46, 56, 12, 255, 1);
            GM_SeSet2(0, 63, SE_MENU_CURSOR);
        }
        else if (press & PAD_UP)
        {
            work->field_2C4 = 0;
            PreopeMoveButtonHighlight_800C3860(work, -42, -42, 84, 6, 255, 0);
            GM_SeSet2(0, 63, SE_MENU_CURSOR);
        }
        else if (press & PAD_CIRCLE)
        {
            work->field_2C4 = 5;
            work->field_A82C = 0;
            work->fadeout_timer = 0;
            PreopeHideButtonHighlight_800C3840(work);
            GM_SeSet2(0, 63, SE_MENU_SELECT);
        }
        else if (press & PAD_CROSS)
        {
            work->field_2C4 = 3;
            GM_SeSet2(0, 63, SE_MENU_EXIT);
            work->fadeout_timer = 0;
            PreopeHideButtonHighlight_800C3840(work);
        }
        break;

    case 2:
        if (press & PAD_UP)
        {
            work->field_2C4 = 1;
            PreopeMoveButtonHighlight_800C3860(work, -90, 6, 180, 6, 255, 0);
            GM_SeSet2(0, 63, SE_MENU_CURSOR);
        }
        else if (press & PAD_CIRCLE)
        {
            work->field_2C4 = 3;
            GM_SeSet2(0, 63, SE_MENU_EXIT);
            work->fadeout_timer = 0;
            PreopeHideButtonHighlight_800C3840(work);
        }
        else if (press & PAD_CROSS)
        {
            work->field_2C4 = 3;
            GM_SeSet2(0, 63, SE_MENU_EXIT);
            work->fadeout_timer = 0;
            PreopeHideButtonHighlight_800C3840(work);
        }
        break;

    case 3:
        if (work->fadeout_timer > 16)
        {
            GCL_ExecProc(work->field_2C0, NULL);
            GV_DestroyActor(&work->actor);
        }
        break;
    }
}

void Preope_800C41D4(PreopeWork *work)
{
    switch (work->field_2C4)
    {
    case 4:
        switch (work->field_A828)
        {
        case 0:
            if (work->fadeout_timer == 16)
            {
                Preope_800C3820(work);
                work->field_A838 = 0;
                work->field_A830 = NewPreMet1_800C6F20(work->map, &work->field_A838, work->field_714);
                work->field_A828 = 1;
            }
            break;

        case 1:
            if (work->field_A838 == 1)
            {
                work->field_A828 = 2;
                work->fadeout_timer = 0;
            }
            break;

        case 2:
            if (work->fadeout_timer == 16)
            {
                work->field_284[0] = 768;
                work->field_284[1] = 768;
                work->field_284[2] = 256;
                work->field_284[3] = 256;
                work->field_284[4] = 256;
                work->field_284[5] = 256;
                GV_DestroyActor(work->field_A830);
            }
            else if (work->fadeout_timer == 32)
            {
                work->field_2C4 = 0;
                PreopeMoveButtonHighlight_800C3860(work, -42, -42, 84, 6, 255, 0);
                work->fadeout_timer = 0;
            }
        }
        break;

    case 5:
        switch (work->field_A82C)
        {
        case 0:
            if (work->fadeout_timer == 16)
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
                work->fadeout_timer = 0;
            }
            break;

        case 2:
            if (work->fadeout_timer == 16)
            {
                work->field_284[0] = 768;
                work->field_284[1] = 768;
                work->field_284[2] = 256;
                work->field_284[3] = 256;
                work->field_284[4] = 256;
                work->field_284[5] = 256;
                GV_DestroyActor(work->field_A834);
            }
            else if (work->fadeout_timer == 32)
            {
                work->field_2C4 = 1;
                PreopeMoveButtonHighlight_800C3860(work, -90, 6, 180, 6, 255, 0);
                work->fadeout_timer = 0;
            }
            break;
        }
        break;
    }
}

void PreopeAct_800C4424(PreopeWork *work)
{
    PreopeProcessPad_800C3FE0(work);
    Preope_800C41D4(work);
    Preope_800C3F34(work);
    Preope_800C356C(work, DG_ChanlOTag(1));
    PreopeShadePacks_800C3B44(work);
    work->fadeout_timer++;
}

void PreopeDie_800C449C(PreopeWork *work)
{
    DG_PRIM *prim;

    prim = work->field_24;
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
}

// Duplicate of camera_800CE4F8
void PreopeSetPolyFT4_800C4504(PreopeWork *work, POLY_FT4 *pPoly, int x0, int y0, int x1, int y1, int semiTrans)
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
void PreopeInitRes_800C4574(PreopeWork *work, int hashCode, POLY_FT4 *pPoly, int x0, int y0, int x1, int y1, int semiTrans, int arg9)
{
    DG_TEX *tex;
    PreopeSetPolyFT4_800C4504(work, pPoly, x0, y0, x1, y1, semiTrans);
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

    work->field_24 = DG_GetPrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 6, 0, NULL, NULL);
    work->field_28 = DG_GetPrim(DG_PRIM_SORTONLY | DG_PRIM_POLY_FT4, 9, 0, NULL, NULL);

    poly = work->field_2C;
    i = 0;

    // pre_back_l = left side of the menu background
    PreopeInitRes_800C4574(work, GV_StrCode("pre_back_l"), poly, -160, -112, 0, 112, 0, 0);
    poly++;
    work->field_284[i] = 768;
    i++;

    // pre_back_r = right side of the menu background
    PreopeInitRes_800C4574(work, GV_StrCode("pre_back_r"), poly, 0, -112, 160, 112, 0, 0);
    poly++;
    work->field_284[i] = 768;
    i++;

    // "pre_pre" = the title of the menu ("PREVIOUS OPERATIONS")
    PreopeInitRes_800C4574(work, GV_StrCode("pre_pre"), poly, -82, -94, 82, -82, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_284[i] = 256;
    i++;

    // "pre_met" = the first button, representing pre_met1 ("METAL GEAR")
    PreopeInitRes_800C4574(work, GV_StrCode("pre_met"), poly, -42, -42, 42, -36, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_284[i] = 256;
    i++;

    // "pre_met2" = the second button, representing pre_met2 ("METAL GEAR2 SOLID SNAKE")
    PreopeInitRes_800C4574(work, GV_StrCode("pre_met2"), poly, -90, 6, 90, 12, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_284[i] = 256;
    i++;

    // "pre_exit" = "EXIT" button
    PreopeInitRes_800C4574(work, GV_StrCode("pre_exit"), poly, -28, 46, 28, 58, 1, 0);
    setRGB0(poly, 86, 137, 116);
    poly++;
    work->field_284[i] = 256;
    i++;

    // A button on the menu can be highlighted (currently focused button).
    // This corresponds to the green highlight (rounded rectangle) of a menu item.
    poly2 = work->button_highlight_parts;
    i = 0;

    // Top left rounded corner of a highlighted button
    PreopeInitRes_800C4574(work, GV_StrCode("cur_lu"), poly2, 0, 0, 0, 0, 1, 0);
    poly2++;
    work->field_29C[i] = 0;
    i++;

    // Top right rounded corner of a highlighted button
    PreopeInitRes_800C4574(work, GV_StrCode("cur_ru"), poly2, 0, 0, 0, 0, 1, 0);
    poly2++;
    work->field_29C[i] = 0;
    i++;

    // Bottom left rounded corner of a highlighted button
    PreopeInitRes_800C4574(work, GV_StrCode("cur_ld"), poly2, 0, 0, 0, 0, 1, 0);
    poly2++;
    work->field_29C[i] = 0;
    i++;

    // Bottom right rounded corner of a highlighted button
    PreopeInitRes_800C4574(work, GV_StrCode("cur_rd"), poly2, 0, 0, 0, 0, 1, 0);
    poly2++;
    work->field_29C[i] = 0;
    i++;

    // Top middle part of a highlighted button
    PreopeInitRes_800C4574(work, GV_StrCode("cur_u"), poly2, 0, 0, 0, 0, 1, 2);
    poly2++;
    work->field_29C[i] = 0;
    i++;

    // Bottom middle part of a highlighted button
    PreopeInitRes_800C4574(work, GV_StrCode("cur_d"), poly2, 0, 0, 0, 0, 1, 2);
    poly2++;
    work->field_29C[i] = 0;
    i++;

    // Left middle part of a highlighted button
    PreopeInitRes_800C4574(work, GV_StrCode("cur_l"), poly2, 0, 0, 0, 0, 1, 1);
    poly2++;
    work->field_29C[i] = 0;
    i++;

    // Right middle part of a highlighted button
    PreopeInitRes_800C4574(work, GV_StrCode("cur_r"), poly2, 0, 0, 0, 0, 1, 1);
    poly2++;
    work->field_29C[i] = 0;
    i++;

    // Central part of a highlighted button
    PreopeInitRes_800C4574(work, GV_StrCode("cur_c"), poly2, 0, 0, 0, 0, 1, 3);
    poly2++;
    work->field_29C[i] = 0;
    i++;

    if (GCL_GetOption('e'))
    {
        work->field_2C0 = GCL_StrToInt(GCL_GetParamResult());
    }
    else
    {
        work->field_2C0 = -1;
    }

    for (i = 0; i < 4; i++)
    {
        work->field_394[i].string = GCL_ReadString(GCL_GetParamResult());
        work->field_394[i].num = 0;
        Preope_800C32E0(work, i);
    }

    index = 0;
    for (j = 0; j < 9; j++)
    {
        for (i = 0; i < 8; i++)
        {
            work->field_714[index].string = GCL_ReadString(GCL_GetParamResult());
            index++;
        }
    }

    index = 0;
    for (j = 0; j < 14; j++)
    {
        for (i = 0; i < 8; i++)
        {
            work->field_4614[index].string = GCL_ReadString(GCL_GetParamResult());
            index++;
        }
    }

    for (i = 0; i < 4; i++)
    {
        Preope_800C3428(work, i);
    }

    work->pad = &GV_PadData_800B05C0[2];

    work->field_2C4 = 0;
    PreopeMoveButtonHighlight_800C3860(work, -42, -42, 84, 6, 255, 0);
    work->fadeout_timer = 0;
    return 0;
}

GV_ACT *NewPreope_800C4DA4(int name, int where, int argc, char **argv)
{
    PreopeWork *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = (PreopeWork *)GV_NewActor(EXEC_LEVEL, sizeof(PreopeWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)PreopeAct_800C4424,
                         (GV_ACTFUNC)PreopeDie_800C449C, "preope.c");
        if (PreopeGetResources_800C46F8(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
