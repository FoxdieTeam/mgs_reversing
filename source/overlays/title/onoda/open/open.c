#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "font/font.h"
#include "menu/menuman.h"
#include "game/game.h"
#include "sound/sd_cli.h"
#include "sound/g_sound.h"

#include "openwork.h"

typedef struct _Desc
{
    int     f0;
    DVECTOR f4;
    int     color;
} Desc;

extern Desc        open_800C32B4[24];
extern signed char open_800C3400[16];

extern int title_dword_800D92D0;
extern int title_dword_800C33D4;

extern const char title_aVeryeasy_800D8F6C[];            // = "VERY EASY"
extern const char title_aEasy_800D8F78[];                // = "EASY"
extern const char title_aNormal_800D8F80[];              // = "NORMAL"
extern const char title_aHard_800D8F88[];                // = "HARD"
extern const char title_aExtreme_800D8F90[];             // = "EXTREME"

extern const char title_aClearflagd_800D8B30[];          // = "clear flag %d\n"
extern const char title_aCleardataexistss_800D8B40[];    // = "clear data exists %s\n"
extern const char title_aBislpm_800D8B58[];              // = "BISLPM-86111"
extern const char title_aOldclearflagd_800D8B68[];       // = "old clear flag %d\n"
extern const char title_aOldcleardataexistss_800D8B7C[]; // = "old clear data exists %s\n"

extern const char title_aMemorycardslot_800D8FAC[];      // = "MEMORY CARD SLOT 1  :  "
extern const char title_aFull_800D8FC4[];                // = "   FULL"
extern const char title_aNocard_800D8FCC[];              // = "NO CARD"
extern const char title_aMemorycardslot_800D8FD4[];      // = "MEMORY CARD SLOT 2  :  "
extern const char title_aDoyouwanttocontinue_800D8FEC[]; // = "DO YOU WANT TO CONTINUE\n"
extern const char title_aYourgamelikethis_800D9008[];    // = "YOUR GAME LIKE THIS?"
extern const char title_aYes_800D9020[];                 // = "YES"
extern const char title_aNo_800D9024[];                  // = "NO"
extern const char aOpenC[];                              // = "open.c"

extern char *MGS_MemoryCardName; /* in main.c */
extern int   FS_DiskNum;

#define EXEC_LEVEL GV_ACTOR_MANAGER

void Open_800C4500(OpenWork *work, int index)
{
    RECT  rect;
    KCB  *kcb;
    void *buffer;

    kcb = &work->kcb[index];

    if ((work->f249C + 21) >= 512)
    {
        work->f249C = 256;
        work->f2498 = 896;
        work->f24A4 = 276;
        work->f24A0 = work->f2498;
    }

    rect.x = work->f2498;
    rect.y = work->f249C;
    rect.w = 64;
    rect.h = 21;

    work->unk[index].f0 = work->f2498;
    work->unk[index].f2 = work->f249C;
    work->f249C += 21;

    font_init_kcb(kcb, &rect, work->f24A0, work->f24A4);
    work->unk[index].f4 = work->f24A0;
    work->unk[index].f6 = work->f24A4;
    work->f24A4 += 21;

    font_set_kcb(kcb, -1, -1, 0, 6, 2, 0);

    buffer = GV_AllocMemory(GV_NORMAL_MEMORY, font_get_buffer_size(kcb));
    font_set_buffer(kcb, buffer);

    font_set_color(kcb, 0, open_800C32B4[index].color, 0);
    font_clut_update(kcb);
}

void Open_800C4674(OpenWork *work, int index)
{
    KCB *kcb;

    if (!work->unk[index].string)
    {
        return;
    }

    kcb = &work->kcb[index];

    font_print_string(kcb, work->unk[index].string);
    font_update(kcb);
    font_clut_update(kcb);

    work->unk[index].rect.w = kcb->max_width;
    work->unk[index].rect.h = kcb->max_height - 1;

    if (open_800C32B4[index].f0 == 0)
    {
        work->unk[index].rect.x = open_800C32B4[index].f4.vx;
        work->unk[index].rect.y = open_800C32B4[index].f4.vy;
    }
    else if (open_800C32B4[index].f0 == 1)
    {
        work->unk[index].rect.x = open_800C32B4[index].f4.vx - kcb->max_width / 2;
        work->unk[index].rect.y = open_800C32B4[index].f4.vy - kcb->max_height / 2;
    }

    work->unk[index].string = 0;
    work->unk[index].num = 1;
}

static inline void AddTpage(OpenWork *work, u_long *ot, int found, int i)
{
    int       tp;
    DR_TPAGE *tpage;

    if (found != 0)
    {
        tp = getTPage(0, 0, 832 + i * 64, 256);
        tpage = &work->tpage[i];
        setDrawTPage(tpage, 1, 0, tp);
        addPrim(ot, tpage);
    }
}

void title_open_800C47B8(OpenWork *work, u_long *ot)
{
    int   count;
    int   found;
    int   i, j, k;
    SPRT *sprt;
    SPRT *sprt2;

    count = 0;
    for (i = 0; i < 2; i++)
    {
        found = 0;
        for (j = 0; j < 12; j++)
        {
            if (work->unk[count].num == 1)
            {
                found = 1;

                sprt = &work->unk[count].sprt[GV_Clock];
                LSTORE(0x808080, &sprt->r0);
                LCOPY(&work->unk[count].rect.x, &sprt->x0);
                LCOPY(&work->unk[count].rect.w, &sprt->w);
                setUV0(sprt, 0, work->unk[count].f2);
                setClut(sprt, work->unk[count].f4, work->unk[count].f6);
                setSprt(sprt);
                addPrim(ot, sprt);

                sprt2 = work->unk[count].sprt2[GV_Clock];
                for (k = 0; k < 8; k += 2)
                {
                    *sprt2 = *sprt;
                    LSTORE(0x64000000, &sprt2->r0);
                    sprt2->x0 += open_800C3400[k + 0];
                    sprt2->y0 += open_800C3400[k + 1];
                    addPrim(ot, sprt2);
                    sprt2++;
                }

                count++;
            }
        }

        AddTpage(work, ot, found, i);
    }

    asm("" : "=r"(found)); // TODO: fix
    AddTpage(work, ot, found, i);
}

void title_open_800C4AD0(OpenWork *work, int index, int color)
{
    KCB *kcb;

    kcb = &work->kcb[index];
    font_set_color(kcb, 0, color, 0);
    font_clut_update(kcb);
}

void * title_open_800C4B20(KCB *kcb)
{
    return kcb->cbuffer;
}

int title_open_800C4B2C(int val)
{
    int ret;
    int pow2;
    int val2;

    val2 = val;
    pow2 = 1;
    while (val2 >= 2)
    {
        val2 /= 2;
        pow2 *= 2;
    }
    pow2 *= 2;

    do
    {
        ret = GV_RandU(pow2) - (pow2 - val);
    } while (ret < 0);

    return ret;
}

void title_open_800C4B94(POLY_GT4 *poly, int r0, int g0, int b0, int r2, int g2, int b2)
{
    setRGB0(poly, r0, g0, b0);
    setRGB1(poly, r0, g0, b0);
    setRGB2(poly, r2, g2, b2);
    setRGB3(poly, r2, g2, b2);
}

void title_open_800C4BD4(POLY_GT4 *poly, int shade3, int shade4)
{
    int shade1, shade2;

    shade1 = shade3 * 192 / 128;
    shade2 = shade4 * 192 / 128;

    setRGB0(poly, shade3, shade1, shade3);
    setRGB1(poly, shade3, shade1, shade3);
    setRGB2(poly, shade4, shade2, shade4);
    setRGB3(poly, shade4, shade2, shade4);
}

// Identical to title_open_800C4F1C, but sets 0x200 to f140[] elements
void title_open_800C4C38(OpenWork *work, int x0, int y0, int xsize, int ysize, int color, int mode)
{
    POLY_FT4 *polys;
    int i;

    polys = work->f7CC_polys;
    for (i = 0; i < 9; i++)
    {
        work->f140[i] = 0x200;
        setRGB0(&polys[i], color, color, color);
    }

    if (mode == 0)
    {
        setXY4(&polys[0], x0 - 8, y0 - 8, x0, y0 - 8, x0 - 8, y0, x0, y0);
        setXY4(&polys[1], x0 + xsize, y0 - 8, x0 + xsize + 8, y0 - 8, x0 + xsize, y0, x0 + xsize + 8, y0);
        setXY4(&polys[2], x0 - 8, y0 + ysize, x0, y0 + ysize, x0 - 8, y0 + ysize + 8, x0, y0 + ysize + 8);
        setXY4(&polys[3], x0 + xsize, y0 + ysize, x0 + xsize + 8, y0 + ysize, x0 + xsize, y0 + ysize + 8, x0 + xsize + 8, y0 + ysize + 8);
        setXY4(&polys[4], x0, y0 - 8, x0 + xsize, y0 - 8, x0, y0, x0 + xsize, y0);
        setXY4(&polys[5], x0, y0 + ysize, x0 + xsize, y0 + ysize, x0, y0 + ysize + 8, x0 + xsize, y0 + ysize + 8);
        setXY4(&polys[6], x0 - 8, y0, x0, y0, x0 - 8, y0 + ysize, x0, y0 + ysize);
        setXY4(&polys[7], x0 + xsize, y0, x0 + xsize + 8, y0, x0 + xsize, y0 + ysize, x0 + xsize + 8, y0 + ysize);
        setXY4(&polys[8], x0, y0, x0 + xsize, y0, x0, y0 + ysize, x0 + xsize, y0 + ysize);
    }
    else if (mode == 1)
    {
        setXY4(&polys[0], x0 - 6, y0 - 6, x0 + 2, y0 - 6, x0 - 6, y0 + 2, x0 + 2, y0 + 2);
        setXY4(&polys[1], x0 + xsize - 2, y0 - 6, x0 + xsize + 6, y0 - 6, x0 + xsize - 2, y0 + 2, x0 + xsize + 6, y0 + 2);
        setXY4(&polys[2], x0 - 6, y0 + ysize - 2, x0 + 2, y0 + ysize - 2, x0 - 6, y0 + ysize + 6, x0 + 2, y0 + ysize + 6);
        setXY4(&polys[3], x0 + xsize - 2, y0 + ysize - 2, x0 + xsize + 6, y0 + ysize - 2, x0 + xsize - 2, y0 + ysize + 6, x0 + xsize + 6, y0 + ysize + 6);
        setXY4(&polys[4], x0 + 2, y0 - 6, x0 + xsize - 2, y0 - 6, x0 + 2, y0 + 2, x0 + xsize - 2, y0 + 2);
        setXY4(&polys[5], x0 + 2, y0 + ysize - 2, x0 + xsize - 2, y0 + ysize - 2, x0 + 2, y0 + ysize + 6, x0 + xsize - 2, y0 + ysize + 6);
        setXY4(&polys[6], x0 - 6, y0 + 2, x0 + 2, y0 + 2, x0 - 6, y0 + ysize - 2, x0 + 2, y0 + ysize - 2);
        setXY4(&polys[7], x0 + xsize - 2, y0 + 2, x0 + xsize + 6, y0 + 2, x0 + xsize - 2, y0 + ysize - 2, x0 + xsize + 6, y0 + ysize - 2);
        setXY4(&polys[8], x0 + 2, y0 + 2, x0 + xsize - 2, y0 + 2, x0 + 2, y0 + ysize - 2, x0 + xsize - 2, y0 + ysize - 2);
    }
}

void title_open_800C4F1C(OpenWork *work, int x0, int y0, int xsize, int ysize, int color, int mode)
{
    POLY_FT4 *polys;
    int i;

    polys = work->f7CC_polys;
    for (i = 0; i < 9; i++)
    {
        work->f140[i] = 0x100;
        setRGB0(&polys[i], color, color, color);
    }

    if (mode == 0)
    {
        setXY4(&polys[0], x0 - 8, y0 - 8, x0, y0 - 8, x0 - 8, y0, x0, y0);
        setXY4(&polys[1], x0 + xsize, y0 - 8, x0 + xsize + 8, y0 - 8, x0 + xsize, y0, x0 + xsize + 8, y0);
        setXY4(&polys[2], x0 - 8, y0 + ysize, x0, y0 + ysize, x0 - 8, y0 + ysize + 8, x0, y0 + ysize + 8);
        setXY4(&polys[3], x0 + xsize, y0 + ysize, x0 + xsize + 8, y0 + ysize, x0 + xsize, y0 + ysize + 8, x0 + xsize + 8, y0 + ysize + 8);
        setXY4(&polys[4], x0, y0 - 8, x0 + xsize, y0 - 8, x0, y0, x0 + xsize, y0);
        setXY4(&polys[5], x0, y0 + ysize, x0 + xsize, y0 + ysize, x0, y0 + ysize + 8, x0 + xsize, y0 + ysize + 8);
        setXY4(&polys[6], x0 - 8, y0, x0, y0, x0 - 8, y0 + ysize, x0, y0 + ysize);
        setXY4(&polys[7], x0 + xsize, y0, x0 + xsize + 8, y0, x0 + xsize, y0 + ysize, x0 + xsize + 8, y0 + ysize);
        setXY4(&polys[8], x0, y0, x0 + xsize, y0, x0, y0 + ysize, x0 + xsize, y0 + ysize);
    }
    else if (mode == 1)
    {
        setXY4(&polys[0], x0 - 6, y0 - 6, x0 + 2, y0 - 6, x0 - 6, y0 + 2, x0 + 2, y0 + 2);
        setXY4(&polys[1], x0 + xsize - 2, y0 - 6, x0 + xsize + 6, y0 - 6, x0 + xsize - 2, y0 + 2, x0 + xsize + 6, y0 + 2);
        setXY4(&polys[2], x0 - 6, y0 + ysize - 2, x0 + 2, y0 + ysize - 2, x0 - 6, y0 + ysize + 6, x0 + 2, y0 + ysize + 6);
        setXY4(&polys[3], x0 + xsize - 2, y0 + ysize - 2, x0 + xsize + 6, y0 + ysize - 2, x0 + xsize - 2, y0 + ysize + 6, x0 + xsize + 6, y0 + ysize + 6);
        setXY4(&polys[4], x0 + 2, y0 - 6, x0 + xsize - 2, y0 - 6, x0 + 2, y0 + 2, x0 + xsize - 2, y0 + 2);
        setXY4(&polys[5], x0 + 2, y0 + ysize - 2, x0 + xsize - 2, y0 + ysize - 2, x0 + 2, y0 + ysize + 6, x0 + xsize - 2, y0 + ysize + 6);
        setXY4(&polys[6], x0 - 6, y0 + 2, x0 + 2, y0 + 2, x0 - 6, y0 + ysize - 2, x0 + 2, y0 + ysize - 2);
        setXY4(&polys[7], x0 + xsize - 2, y0 + 2, x0 + xsize + 6, y0 + 2, x0 + xsize - 2, y0 + ysize - 2, x0 + xsize + 6, y0 + ysize - 2);
        setXY4(&polys[8], x0 + 2, y0 + 2, x0 + xsize - 2, y0 + 2, x0 + 2, y0 + ysize - 2, x0 + xsize - 2, y0 + ysize - 2);
    }
}

void title_open_800C5200(POLY_FT4 *poly, int arg1)
{
    int tpage;
    unsigned short tpage2;

    tpage = tpage2 = poly->tpage;
    poly->tpage = (tpage & 0x180) | ((arg1 & 3) << 5) | (poly->tpage & 0x10) | (poly->tpage & 0xF) | (tpage & 0x800);
}

void title_open_800C5238(POLY_FT4 *poly, DG_TEX *tex, int scale, int width, int height)
{
    int x, y, w, h;
    int xoff, yoff;

    width /= scale;
    height /= scale;

    x = tex->off_x;
    w = tex->w + 1;
    y = tex->off_y;
    h = tex->h + 1;

    xoff  = title_open_800C4B2C(w - width);
    yoff = title_open_800C4B2C(h - height);

    setUVWH(poly, x + xoff, y + yoff, width, height);

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}

void title_open_800C5360(OpenWork *work, int texid, POLY_FT4 *poly)
{
    DG_TEX *tex;
    int u0, u1;
    int v0, v1;

    tex = DG_GetTexture(texid);

    u0 = tex->off_x;
    u1 = u0 + tex->w + 1;
    v0 = tex->off_y;
    v1 = v0 + tex->h + 1;

    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}

void title_open_800C53E0(OpenWork *work)
{
    POLY_FT4 *src_ft4;
    POLY_FT4 *dst_ft4;
    int       i;
    POLY_GT4 *dst_gt4;
    POLY_GT4 *src_gt4;

    src_ft4 = work->f18C_polys;
    dst_ft4 = work->prim[0]->packs[GV_Clock];
    for (i = 0; i < 22; i++)
    {
        *dst_ft4 = *src_ft4;
        SSTOREL(work->f30[i], &dst_ft4->tag);
        dst_ft4++;
        src_ft4++;
    }

    src_ft4 = work->f4FC_polys;
    dst_ft4 = work->prim[2]->packs[GV_Clock];
    for (i = 0; i < 18; i++)
    {
        *dst_ft4 = *src_ft4;
        SSTOREL(work->fF8[i], &dst_ft4->tag);
        dst_ft4++;
        src_ft4++;
    }

    src_ft4 = work->f7CC_polys;
    dst_ft4 = work->prim[3]->packs[GV_Clock];
    for (i = 0; i < 9; i++)
    {
        *dst_ft4 = *src_ft4;
        SSTOREL(work->f140[i], &dst_ft4->tag);
        dst_ft4++;
        src_ft4++;
    }

    src_gt4 = work->f934_polys;
    dst_gt4 = work->prim[1]->packs[GV_Clock];
    for (i = 0; i < 6; i++)
    {
        *dst_gt4 = *src_gt4;
        SSTOREL(work->fE0[i], &dst_gt4->tag);
        dst_gt4++;
        src_gt4++;
    }
}

int title_open_800C5620(int val)
{
    return title_open_800C4B2C(val) == 1;
}

static inline void ShadePack(POLY_FT4 *poly, DG_TEX *tex)
{
    int x0, x1;
    int y0, y1;

    x0 = tex->off_x;
    x1 = x0 + tex->w + 1;
    y0 = tex->off_y;
    y1 = y0 + tex->h + 1;
    setUV4(poly, x0, y0, x1, y0, x0, y1, x1, y1);

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}

void title_open_800C5644(OpenWork *work, int index)
{
    POLY_FT4 *poly;
    int       name;
    DG_TEX   *tex;

    poly = work->f18C_polys;
    poly += index;

    switch (work->fAB8)
    {
    case 0:
        work->fAB8 = title_open_800C5620(150);
        break;

    case 1:
        name = GV_StrCode("op_eye_close");
        tex = DG_GetTexture(name);
        ShadePack(poly, tex);
        work->fAB8++;
        break;

    case 3:
        name = GV_StrCode("op_eye_half");
        tex = DG_GetTexture(name);
        ShadePack(poly, tex);
        work->fAB8++;
        break;

    case 5:
        name = GV_StrCode("op_eye_open");
        tex = DG_GetTexture(name);
        ShadePack(poly, tex);
        work->fAB8++;
        break;

    case 2:
    case 4:
        work->fAB8++;
        break;

    case 6:
        work->fAB8 = 0;
        break;
    }
}

void title_open_800C5760(OpenWork *work)
{
    int r, g, b;

    if (work->fA6C[4] >= 0 && work->fA6C[4] < 512)
    {
        work->fA70 = 0;
        r = work->fAA8 - 10;
        g = work->fAA9 + 5;
        b = work->fAAA + 5;
    }
    else if (work->fA6C[4] >= 512 && work->fA6C[4] < 1024)
    {
        work->fA70 = 0;
        r = work->fAA8 - 5;
        g = work->fAA9;
        b = work->fAAA + 10;
    }
    else if (work->fA6C[4] >= 1024 && work->fA6C[4] < 1536)
    {
        work->fA70 = 0;
        r = work->fAA8;
        g = work->fAA9 - 5;
        b = work->fAAA + 5;
    }
    else if (work->fA6C[4] >= 1536 && work->fA6C[4] < 2048)
    {
        work->fA70 = 0;
        r = work->fAA8 + 5;
        g = work->fAA9 - 10;
        b = work->fAAA;
    }
    else if (work->fA6C[4] >= 2048 && work->fA6C[4] < 2560)
    {
        work->fA70 = 0;
        r = work->fAA8 + 10;
        g = work->fAA9 - 5;
        b = work->fAAA - 5;
    }
    else if (work->fA6C[4] >= 2560 && work->fA6C[4] < 3072)
    {
        work->fA70 = 0;
        r = work->fAA8 + 5;
        g = work->fAA9;
        b = work->fAAA - 10;
    }
    else if (work->fA6C[4] >= 3072 && work->fA6C[4] < 3584)
    {
        work->fA70 = 0;
        r = work->fAA8;
        g = work->fAA9 + 5;
        b = work->fAAA - 5;
    }
    else if (work->fA6C[4] >= 3584 && work->fA6C[4] < 4096)
    {
        work->fA70 = 0;
        r = work->fAA8 - 5;
        g = work->fAA9 + 10;
        b = work->fAAA;
    }
    else if (work->fA6C[4] == -1)
    {
        work->fA70++;
        r = work->fAA8;
        g = work->fAA9;
        b = work->fAAA;
    }
    else
    {
        r = work->fAA8;
        g = work->fAA9;
        b = work->fAAA;
    }

    if (r >= 0 && r < 255)
    {
        work->fAA8 = r;
    }

    if (g >= 0 && g < 255)
    {
        work->fAA9 = g;
    }

    if (b >= 0 && b < 255)
    {
        work->fAAA = b;
    }
}

void title_open_800C593C(OpenWork *work)
{
    POLY_FT4 *polys1;
    POLY_GT4 *polys2;
    POLY_FT4 *polys3;
    POLY_FT4 *polys4;
    int       scale;
    int       r, g, b;
    int       i;

    polys1 = work->f18C_polys;
    polys2 = work->f934_polys;
    polys3 = work->f4FC_polys;
    polys4 = work->f7CC_polys;

    if (work->fB04 <= 96)
    {
        scale = 128 - work->fB04 * 4 / 3;
        for (i = 0; i < 22; i++)
        {
            r = polys1[i].r0 * scale / 128;
            g = polys1[i].g0 * scale / 128;
            b = polys1[i].b0 * scale / 128;
            setRGB0(&polys1[i], r, g, b);
        }

        for (i = 0; i < 6; i++)
        {
            r = polys2[i].r0 * scale / 128;
            g = polys2[i].g0 * scale / 128;
            b = polys2[i].b0 * scale / 128;
            setRGB0(&polys2[i], r, g, b);

            r = polys2[i].r1 * scale / 128;
            g = polys2[i].g1 * scale / 128;
            b = polys2[i].b1 * scale / 128;
            setRGB1(&polys2[i], r, g, b);

            r = polys2[i].r2 * scale / 128;
            g = polys2[i].g2 * scale / 128;
            b = polys2[i].b2 * scale / 128;
            setRGB2(&polys2[i], r, g, b);

            r = polys2[i].r3 * scale / 128;
            g = polys2[i].g3 * scale / 128;
            b = polys2[i].b3 * scale / 128;
            setRGB3(&polys2[i], r, g, b);
        }

        for (i = 0; i < 18; i++)
        {
            r = polys3[i].r0 * scale / 128;
            g = polys3[i].g0 * scale / 128;
            b = polys3[i].b0 * scale / 128;
            setRGB0(&polys3[i], r, g, b);
        }

        for (i = 0; i < 9; i++)
        {
            r = polys4[i].r0 * scale / 128;
            g = polys4[i].g0 * scale / 128;
            b = polys4[i].b0 * scale / 128;
            setRGB0(&polys4[i], r, g, b);
        }

        work->fB04++;
    }
    else
    {
        work->f164 = 0;
        work->fA74 = 0;
        work->fB0C = 1;
    }
}

void title_open_800C5CB8(OpenWork *work)
{
    int i;

    for (i = 21; i >= 0; i--)
    {
        work->f30[i] = 0;
    }

    for (i = 5; i >= 0; i--)
    {
        work->fE0[i] = 0;
    }
}

void title_open_800C5CF0(OpenWork *work)
{
    int i;

    for (i = 17; i >= 0; i--)
    {
        work->fF8[i] = 0;
    }
}

void title_open_800C5D10(OpenWork *work)
{
    int i;

    for (i = 0; i < 9; i++)
    {
        work->f140[i] = 0;
    }
}

void title_open_800C5D30(OpenWork *work)
{
    MEM_CARD card1, card2;
    int      check1, check2;
    int      max1, max2;
    int      error1, error2;
    char    *name;
    int      found;
    int      i, j;
    int      mismatch;

    check1 = memcard_check(0);
    check2 = memcard_check(1);

    printf("check1 = %x\n", check1);
    printf("check2 = %x\n", check2);

    max1 = 0;
    max2 = 0;

    error1 = 0;
    error2 = 0;

    name = MGS_MemoryCardName;

    if ((check1 & 0x3) == 0x3)
    {
        error1 = 1;
    }
    else if (check1 >= 0)
    {
        printf("this memcard is OK\n");

        card1 = *memcard_get_files(0);
        printf("free = %d\n", card1.free_blocks);

        if (card1.free_blocks == 0)
        {
            found = 0;
            for (i = 0; i < card1.file_count; i++)
            {
                printf("name = %s\n", card1.files[i].name);

                mismatch = 0;
                for (j = 0; j < 12; j++)
                {
                    if (card1.files[i].name[j] != name[j])
                    {
                        mismatch = 1;
                        break;
                    }
                }

                if (mismatch == 0 && card1.files[i].name[12] == 'G')
                {
                    found = 1;
                }
            }

            if (found == 0)
            {
                max1 = 1;
            }
        }
    }

    if ((check2 & 0x3) == 0x3)
    {
        error2 = 1;
    }
    else if (check2 >= 0)
    {
        printf("this memcard is OK\n");

        card2 = *memcard_get_files(1);
        printf("free = %d\n", card2.free_blocks);

        if (card2.free_blocks == 0)
        {
            found = 0;
            for (i = 0; i < card2.file_count; i++)
            {
                printf("name = %s\n", card2.files[i].name);

                mismatch = 0;
                for (j = 0; j < 12; j++)
                {
                    if (card2.files[i].name[j] != name[j])
                    {
                        mismatch = 1;
                        break;
                    }
                }

                if (mismatch == 0 && card2.files[i].name[12] == 'G')
                {
                    found = 1;
                }
            }

            if (found == 0)
            {
                max2 = 1;
            }
        }
    }

    work->f24D8 = 0;
    work->f24DC = 0;

    printf("error flag card1 = %d card2 = %d\n", error1, error2);
    printf("max flag card1 = %d card2 = %d\n", max1, max2);

    if (max1 == 1 && max2 == 1)
    {
        work->f24D8 = 1;
        printf("MemCard is MAX!!\n");
        work->fA74 = 18;
        work->f24E0 = 1;
        work->f24F0 = 3;
        work->f24F4 = 3;
    }

    if (max1 == 1 && error2 == 1)
    {
        work->f24D8 = 1;
        printf("MemCard is MAX!!\n");
        work->fA74 = 18;
        work->f24E0 = 1;
        work->f24F0 = 3;
        work->f24F4 = 2;
    }

    if (max2 == 1 && error1 == 1)
    {
        work->f24D8 = 1;
        printf("MemCard is MAX!!\n");
        work->fA74 = 18;
        work->f24E0 = 1;
        work->f24F0 = 2;
        work->f24F4 = 3;
    }

    if (error1 == 1 && error2 == 1)
    {
        work->f24DC = 1;
        printf("MemCard is not found!!\n");
        work->fA74 = 19;
        work->f24E0 = 1;
        work->f24F0 = 2;
        work->f24F4 = 2;
    }

    if (work->f24DC == 0 && work->f24D8 == 0)
    {
        work->fA74 = 8;
    }
}

void title_open_800C61E0(OpenWork *work, GCL_ARGS *args)
{
    GM_SeSet2(0, 0x3F, SE_MENU_GUNSHOT);
    if (FS_DiskNum == 0)
    {
        if (sd_sng_play() == 0)
        {
            GCL_ExecProc(work->f24F8_proc, args);
            GV_DestroyActor(&work->actor);
        }
    }
    else
    {
        work->fB0C = 1;
        work->fA74 = 9;
        work->f24EC = 0;
        work->f24AC = 0;
        work->f24B0 = 0;
        work->f24B4 = 0;
        work->f24B8 = 0;
        work->f24BC = 0;
        title_dword_800C33D4 = work->f24F8_proc;
    }
}

#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C628C.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CCDC8.s")

void title_open_800CD074(OpenWork *work)
{
    int sqrt1, sqrt2;
    int val1, val2, val3;
    int val1_2, val2_2, val3_2;

    val1 = work->fAA8;
    val2 = work->fAA9;
    val3 = work->fAAA;
    sqrt1 = SquareRoot0(val1 * val1 + val2 * val2 + val3 * val3);

    val1_2 = 0xFF - val1;
    val2_2 = 0xFF - val2;
    val3_2 = 0xFF - val3;
    sqrt2 = SquareRoot0(val1_2 * val1_2 + val2_2 * val2_2 + val3_2 * val3_2);

    if (sqrt2 != 0)
    {
        val1_2 = (val1_2 * sqrt1) / sqrt2;
        if (val1_2 > 0xFF)
        {
            val1_2 = 0xFF;
        }
        val2_2 = (val2_2 * sqrt1) / sqrt2;
        if (val2_2 > 0xFF)
        {
            val2_2 = 0xFF;
        }
        val3_2 = (val3_2 * sqrt1) / sqrt2;
        if (val3_2 > 0xFF)
        {
            val3_2 = 0xFF;
        }
    }
    else
    {
        val1_2 = 0xFF;
        val2_2 = 0xFF;
        val3_2 = 0xFF;
    }

    work->fAAC = val1_2;
    work->fAAD = val2_2;
    work->fAAE = val3_2;
}

void title_open_800CD23C(OpenWork *work, int index, int arg3)
{
    GCL_ARGS args;
    long argv[2];
    POLY_FT4 *polys;
    int shade;

    args.argc = 2;
    args.argv = argv;
    argv[0] = work->f24D0;
    argv[1] = work->fB28;

    polys = work->f18C_polys;
    polys += index;

    if (work->f164 <= 20)
    {
        shade = work->f164 * 6;
        setRGB0(&polys[0], shade, shade, shade);
        setRGB0(&polys[1], shade, shade, shade);
    }
    else if (work->f164 <= 82)
    {
        setRGB0(&polys[0], 128, 128, 128);
        setRGB0(&polys[1], 128, 128, 128);
    }
    else if (work->f164 <= 102)
    {
        shade = 120 - (work->f164 - 82) * 6;
        setRGB0(&polys[0], shade, shade, shade);
        setRGB0(&polys[1], shade, shade, shade);
    }
    else
    {
        work->fB0C = 1;
        work->f164 = 0;
        work->fA74 = arg3;
        if (arg3 == 15)
        {
            GCL_ExecProc(work->fAD8, &args);
            GV_DestroyActor(&work->actor);
        }
    }
}

void title_open_800CD320(OpenWork *work, int index)
{
    POLY_FT4 *polys;
    int shade;

    polys = work->f18C_polys;
    polys += index;

    if (work->f164 <= 20)
    {
        shade = work->f164 * 6;

        polys[0].r0 = shade;
        polys[0].g0 = shade;
        polys[0].b0 = shade;
        polys[1].r0 = shade;
        polys[1].g0 = shade;
        polys[1].b0 = shade;
    }
    else if (work->f164 <= 82)
    {
        work->f164 = 82;
    }
    else if (work->f164 <= 102)
    {
        shade = 120 - (work->f164 - 82) * 6;

        polys[0].r0 = shade;
        polys[0].g0 = shade;
        polys[0].b0 = shade;
        polys[1].r0 = shade;
        polys[1].g0 = shade;
        polys[1].b0 = shade;
    }
    else
    {
        work->fA74 = 6;
        work->f164 = 0;
        work->fB0C = 1;
    }
}

#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CD3B8.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CD800.s")

void title_open_800CDB4C(POLY_FT4 *poly, DG_TEX *tex, int arg2)
{
    int u0, u1;
    int v0, v1;
    int height;

    u0 = tex->off_x;
    u1 = tex->off_x + arg2;

    v0 = tex->off_y;
    height = tex->h + 1;
    v1 = v0 + height;

    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}


void title_open_800CDB9C(POLY_FT4 *poly, DG_TEX *tex, int arg2)
{
    int u0, u1;
    int v0, v1;
    int height, width;

    u0 = tex->off_x + arg2;
    width = tex->w + 1;
    u1 = tex->off_x + width;

    v0 = tex->off_y;
    height = tex->h + 1;
    v1 = v0 + height;

    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}

#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CDBF8.s")
extern void title_open_800CDBF8(OpenWork *work, int index);

void title_open_800CDE44(OpenWork *work, int index)
{
    POLY_FT4 *pack;
    int       shade;
    int       left;
    int       right;
    int       top;
    int       bot;
    int       t3;
    int       x_aa0;
    int       x_aa4;
    int       v;

    pack = work->f18C_polys;
    pack += index;

    switch (work->fA84)
    {
    case 0:
        if (work->f170 < 0x80)
        {
            break;
        }
        v = work->f168;
        work->f170 = 0;
        work->fA84 = 1;
        work->fAA0 = -v;
        work->fAA4 = (-v) + 0xA0;
        title_open_800CDBF8(work, index);
        break;

    case 1:
        shade = work->f170 * 2;
        setRGB0(&pack[0], shade, shade, shade);
        setRGB0(&pack[1], shade, shade, shade);
        setRGB0(&pack[2], shade, shade, shade);
        t3 = work->f170 + 0xC8;
        left = (-(t3 * 0xA0)) / 200;
        top = (-(t3 * 0x70)) / 200;
        right = (t3 * 0xA0) / 200;
        bot = (t3 * 0x70) / 200;
        x_aa0 = (work->fAA0 * t3) / 200;
        x_aa4 = (work->fAA4 * t3) / 200;
        setXY4(&pack[0], left,  top, x_aa0, top, left,  bot, x_aa0, bot);
        setXY4(&pack[1], x_aa0, top, x_aa4, top, x_aa0, bot, x_aa4, bot);
        setXY4(&pack[2], x_aa4, top, right, top, x_aa4, bot, right, bot);
        if (work->f170 < 0x40)
        {
            break;
        }
        work->fA84 = 2;
        work->f170 = 0;
        break;

    case 2:
        setRGB0(&pack[0], 0x80, 0x80, 0x80);
        setRGB0(&pack[1], 0x80, 0x80, 0x80);
        setRGB0(&pack[2], 0x80, 0x80, 0x80);
        t3 = work->f170 + 0x108;
        left = (-(t3 * 0xA0)) / 200;
        top = (-(t3 * 0x70)) / 200;
        right = (t3 * 0xA0) / 200;
        bot = (t3 * 0x70) / 200;
        x_aa0 = (work->fAA0 * t3) / 200;
        x_aa4 = (work->fAA4 * t3) / 200;
        setXY4(&pack[0], left,  top, x_aa0, top, left,  bot, x_aa0, bot);
        setXY4(&pack[1], x_aa0, top, x_aa4, top, x_aa0, bot, x_aa4, bot);
        setXY4(&pack[2], x_aa4, top, right, top, x_aa4, bot, right, bot);
        if (work->f170 < 0x40)
        {
            break;
        }
        work->fA84 = 3;
        work->f170 = 0;
        break;

    case 3:
        shade = 0x80 - work->f170;
        setRGB0(&pack[0], shade, shade, shade);
        setRGB0(&pack[1], shade, shade, shade);
        setRGB0(&pack[2], shade, shade, shade);
        t3 = work->f170 + 0x148;
        left = (-(t3 * 0xA0)) / 200;
        top = (-(t3 * 0x70)) / 200;
        right = (t3 * 0xA0) / 200;
        bot = (t3 * 0x70) / 200;
        x_aa0 = (work->fAA0 * t3) / 256;
        x_aa4 = (work->fAA4 * t3) / 256;
        setXY4(&pack[0], left,  top, x_aa0, top, left,  bot, x_aa0, bot);
        setXY4(&pack[1], x_aa0, top, x_aa4, top, x_aa0, bot, x_aa4, bot);
        setXY4(&pack[2], x_aa4, top, right, top, x_aa4, bot, right, bot);
        if (work->f170 < 0x80)
        {
            break;
        }
        v = work->f168;
        work->fA84 = 1;
        work->f170 = 0;
        work->fAA0 = -v;
        work->fAA4 = (-v) + 0xA0;
        title_open_800CDBF8(work, index);
        break;
    }
}
/* Strings + reverse-transcribed tables that previously lived at
 * 0x800D8848..0x800D8AE7 in openact.c. Moved here so open.obj's rdata
 * grows by 0x2A0 bytes. gcc's auto-emitted switch jump table for
 * title_open_800CE378's switch (5 entries, 0x14 bytes) then lands at
 * 0x800D8848 + 0x2A0 = 0x800D8AE8, replacing the 5 manual entries that
 * were removed from openact.c. Placed BEFORE the function definition so
 * gcc emits these strings first, then the function's switch table.
 * Placed AFTER all preceding C functions in source order so their auto-
 * emitted switch tables come first in open.obj.rdata, leaving the strings
 * to land starting at 0x800D8848.
 */
const char title_aGameleveld_800D8848[] = "\n Game Level = %d\n\n";
const char title_aErrormemcardcheckerror_800D885C[] = "ERROR!!!! MEMCARD Check ERROR!!!\n";
const char title_aSppre_800D8880[] = "sp_pre";
const char title_aSpexit_800D8888[] = "sp_exit";
const char title_aSpalbum_800D8890[] = "sp_album";
const char title_aSpdemo_800D889C[] = "sp_demo";
const char title_aSpon_800D88A4[] = "sp_on";
const char title_aSpoffw_800D88AC[] = "sp_off_w";
const char title_aSponw_800D88B8[] = "sp_on_w";
const char title_aSpoff_800D88C0[] = "sp_off";
const char title_aDsppmode_800D88C8[] = "d3_sp_1p_mode";
const int title_dword_800D88D8 = 0x800C6398;
const int title_dword_800D88DC = 0x800C63C0;
const int title_dword_800D88E0 = 0x800CCDA0;
const int title_dword_800D88E4 = 0x800CCDA0;
const int title_dword_800D88E8 = 0x800C63E8;
const int title_dword_800D88EC = 0x800C6414;
const int title_dword_800D88F0 = 0x800C6440;
const int title_dword_800D88F4 = 0x800C6C50;
const int title_dword_800D88F8 = 0x800C805C;
const int title_dword_800D88FC = 0x800C8104;
const int title_dword_800D8900 = 0x800C8110;
const int title_dword_800D8904 = 0x800C812C;
const int title_dword_800D8908 = 0x800C8148;
const int title_dword_800D890C = 0x800C8164;
const int title_dword_800D8910 = 0x800CCCE4;
const int title_dword_800D8914 = 0x800CCD10;
const int title_dword_800D8918 = 0x800C8104;
const int title_dword_800D891C = 0x800CCDA0;
const int title_dword_800D8920 = 0x800C7A5C;
const int title_dword_800D8924 = 0x800C7A5C;
const int title_dword_800D8928 = 0x800C7A0C;
const int title_dword_800D892C = 0x800C760C;
const int title_dword_800D8930 = 0x800C6484;
const int title_dword_800D8934 = 0x800C65CC;
const int title_dword_800D8938 = 0x800C6714;
const int title_dword_800D893C = 0x800C6868;
const int title_dword_800D8940 = 0x800C69B0;
const int title_dword_800D8944 = 0x800C6B00;
const int title_dword_800D8948 = 0x800C6C80;
const int title_dword_800D894C = 0x800C6E48;
const int title_dword_800D8950 = 0x800C6FB4;
const int title_dword_800D8954 = 0x800C7128;
const int title_dword_800D8958 = 0x800C72AC;
const int title_dword_800D895C = 0x800C7440;
const int title_dword_800D8960 = 0x800C8194;
const int title_dword_800D8964 = 0x800C88F4;
const int title_dword_800D8968 = 0x800C911C;
const int title_dword_800D896C = 0x800C9C98;
const int title_dword_800D8970 = 0x800CA8A4;
const int title_dword_800D8974 = 0x800CB0B8;
const int title_dword_800D8978 = 0x800CB99C;
const int title_dword_800D897C = 0x800CC2B8;
const int title_dword_800D8980 = 0x800C8924;
const int title_dword_800D8984 = 0x800C8D80;
const int title_dword_800D8988 = 0x800C8D88;
const int title_dword_800D898C = 0x800C906C;
const int title_dword_800D8990 = 0x800C906C;
const int title_dword_800D8994 = 0x800C906C;
const int title_dword_800D8998 = 0x800C906C;
const int title_dword_800D899C = 0x800C8DE0;
const int title_dword_800D89A0 = 0x800C8E34;
const char title_dword_800D89A4[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D89A8 = 0x800C914C;
const int title_dword_800D89AC = 0x800C95C8;
const int title_dword_800D89B0 = 0x800C9AE4;
const int title_dword_800D89B4 = 0x800C95D0;
const int title_dword_800D89B8 = 0x800C9AE4;
const int title_dword_800D89BC = 0x800C9628;
const int title_dword_800D89C0 = 0x800C9AE4;
const int title_dword_800D89C4 = 0x800C9854;
const int title_dword_800D89C8 = 0x800C98AC;
const char title_dword_800D89CC[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D89D0 = 0x800C9CC8;
const int title_dword_800D89D4 = 0x800CA1A0;
const int title_dword_800D89D8 = 0x800CA1C0;
const int title_dword_800D89DC = 0x800CA1FC;
const int title_dword_800D89E0 = 0x800CA678;
const int title_dword_800D89E4 = 0x800CA240;
const int title_dword_800D89E8 = 0x800CA678;
const int title_dword_800D89EC = 0x800CA3EC;
const int title_dword_800D89F0 = 0x800CA440;
const char title_dword_800D89F4[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D89F8 = 0x800CA8D4;
const int title_dword_800D89FC = 0x800CAD4C;
const int title_dword_800D8A00 = 0x800CB038;
const int title_dword_800D8A04 = 0x800CB038;
const int title_dword_800D8A08 = 0x800CB038;
const int title_dword_800D8A0C = 0x800CB038;
const int title_dword_800D8A10 = 0x800CAD54;
const int title_dword_800D8A14 = 0x800CADAC;
const int title_dword_800D8A18 = 0x800CAE00;
const char title_dword_800D8A1C[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D8A20 = 0x800CB0E8;
const int title_dword_800D8A24 = 0x800CB5BC;
const int title_dword_800D8A28 = 0x800CB5DC;
const int title_dword_800D8A2C = 0x800CB8E8;
const int title_dword_800D8A30 = 0x800CB8E8;
const int title_dword_800D8A34 = 0x800CB8E8;
const int title_dword_800D8A38 = 0x800CB618;
const int title_dword_800D8A3C = 0x800CB65C;
const int title_dword_800D8A40 = 0x800CB6B0;
const char title_dword_800D8A44[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D8A48 = 0x800CB9CC;
const int title_dword_800D8A4C = 0x800CBEC0;
const int title_dword_800D8A50 = 0x800CC1EC;
const int title_dword_800D8A54 = 0x800CBEE0;
const int title_dword_800D8A58 = 0x800CC1EC;
const int title_dword_800D8A5C = 0x800CC1EC;
const int title_dword_800D8A60 = 0x800CBF1C;
const int title_dword_800D8A64 = 0x800CBF60;
const int title_dword_800D8A68 = 0x800CBFB4;
const char title_dword_800D8A6C[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D8A70 = 0x800CC2E8;
const int title_dword_800D8A74 = 0x800CC838;
const int title_dword_800D8A78 = 0x800CC858;
const int title_dword_800D8A7C = 0x800CC8A8;
const int title_dword_800D8A80 = 0x800CCBA0;
const int title_dword_800D8A84 = 0x800CCBA0;
const int title_dword_800D8A88 = 0x800CC8D0;
const int title_dword_800D8A8C = 0x800CC914;
const int title_dword_800D8A90 = 0x800CC968;
const char title_dword_800D8A94[] = {0x0, 0x0, 0x0, 0x0};
const int title_dword_800D8A98 = 0x800CCE20;
const int title_dword_800D8A9C = 0x800CCFB0;
const int title_dword_800D8AA0 = 0x800CCE58;
const int title_dword_800D8AA4 = 0x800CCEC0;
const int title_dword_800D8AA8 = 0x800CCF5C;
const int title_dword_800D8AAC = 0x800CCFB0;
const char title_aOpbackr_800D8AB0[] = "op_back_r";
const char title_aOpbackl_800D8ABC[] = "op_back_l";
const int title_dword_800D8AC8 = 0x800CD850;
const int title_dword_800D8ACC = 0x800CD86C;
const int title_dword_800D8AD0 = 0x800CD8CC;
const int title_dword_800D8AD4 = 0x800CD928;
const int title_dword_800D8AD8 = 0x800CD994;
const int title_dword_800D8ADC = 0x800CDA08;
const int title_dword_800D8AE0 = 0x800CDA68;
const char title_dword_800D8AE4[] = {0x0, 0x0, 0x0, 0x0};

void title_open_800CE378(OpenWork *work, int idx)
{
    POLY_FT4 *poly = work->f18C_polys;
    int       v;

    poly += idx;

    switch (work->fA8C)
    {
    case 0:
        if (work->f178 >= 0x80)
        {
            work->fA8C = 1;
            work->f178 = 0;
        }
        break;
    case 1:
        v = work->f178;
        poly->r0 = v;
        poly->g0 = v;
        poly->b0 = v;
        if (work->f178 >= 0x80)
        {
            work->fA8C = 2;
            work->f178 = 0;
        }
        break;
    case 2:
        v = work->f178 * 4 + 0x80;
        poly->r0 = v;
        poly->g0 = v;
        poly->b0 = v;
        if (work->f178 >= 0x1F)
        {
            work->fA8C = 3;
            work->f178 = 0;
        }
        break;
    case 3:
        v = 0xFF - (work->f178 * 4) / 3;
        poly->r0 = v;
        poly->g0 = v;
        poly->b0 = v;
        if (work->f178 >= 0x60)
        {
            work->fA8C = 4;
            work->f178 = 0;
            poly->r0 = 0x80;
            poly->g0 = 0x80;
            poly->b0 = 0x80;
        }
        break;
    case 4:
        break;
    }
}

/* Tail-piece moved from openact.c. Placed after 800CE378's auto-emitted
 * switch table so it lands at 0x800D8AFC (right after the table at
 * 0x800D8AE8..0x800D8AFB). This makes openact.obj.rdata start at 0x800D8B00
 * (8-byte aligned) so the .obj-local offset of title_aNo_800D9024 keeps the
 * same alignment-mod-8 as in the original openact.obj.
 */
const char title_dword_800D8AFC[] = {0x0, 0x0, 0x0, 0x0};

void title_open_800CE4A8(OpenWork *work, int index)
{
    POLY_FT4 *polys;
    int shade;

    polys = work->f18C_polys;
    polys += index;

    switch (work->fA90)
    {
    case 0:
        if (work->f17C >= 256)
        {
            work->fA90 = 1;
            work->f17C = 0;
        }
        break;
    case 1:
        shade = work->f17C;
        setRGB0(polys, shade, shade, shade);
        if (work->f17C >= 128)
        {
            work->fA90 = 2;
            work->f17C = 0;
            setRGB0(polys, 128, 128, 128);
        }
        break;
    case 2:
        break;
    }
}

void title_open_800CE544(OpenWork *work, int index)
{
    POLY_FT4 *polys;
    int shade;

    polys = work->f18C_polys;
    polys += index;

    switch (work->fA94)
    {
    case 0:
        if (work->f180 >= 256)
        {
            work->fA94 = 1;
            work->f180 = 0;
        }
        break;
    case 1:
        shade = work->f180;
        setRGB0(&polys[0], shade, shade, shade);
        setRGB0(&polys[1], shade, shade, shade);

        if (work->f180 >= 128)
        {
            work->fA94 = 2;
            work->f180 = 0;
            setRGB0(&polys[0], 128, 128, 128);
            setRGB0(&polys[1], 128, 128, 128);
        }
        break;
    case 2:
        break;
    }
}

void title_open_800CE5F8(OpenWork *work, int index)
{
    POLY_FT4 *polys;
    int f184;
    int r;

    polys = work->f18C_polys;
    polys += index;

    switch (work->fA98)
    {
    case 0:
        if (work->f184 >= 376)
        {
            work->fA98 = 1;
            work->f184 = 0;
        }
        break;
    case 1:
        f184 = work->f184;

        r = f184 * 8;
        if (r > 255)
        {
            r = 255;
        }
        setRGB0(polys, r, f184 * 2, f184 * 2);

        if (work->f184 >= 31)
        {
            work->fA98 = 2;
            work->f184 = 0;
            setRGB0(polys, 255, 64, 64);
        }
        break;
    case 2:
        break;
    }
}

void title_open_800CE6AC(OpenWork *work, int index)
{
    POLY_FT4 *polys;
    int shade;

    polys = work->f18C_polys;
    polys += index;

    switch (work->fA9C)
    {
    case 0:
        if (work->f188 >= 160)
        {
            work->fA9C = 1;
            work->f188 = 0;
        }
        break;
    case 1:
        shade = work->f188;
        setRGB0(polys, shade, shade, shade);
        if (work->f188 >= 128)
        {
            work->fA9C = 2;
            work->f188 = 0;
            setRGB0(polys, 128, 128, 128);
        }
        break;
    case 2:
        break;
    }
}

#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CE748.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CEB14.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CEF54.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CF504.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CF610.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CF794.s")
void title_open_800D1B74(char *name)
{
    int   i;
    char *str;

    if (title_dword_800D92D0 == 1)
    {
        return;
    }

    str = MGS_MemoryCardName;
    for (i = 0; i < 12; i++)
    {
        if (name[i] != str[i])
        {
            goto skip;
        }
    }

    printf((char *)title_aClearflagd_800D8B30, name[17] - '@');

    if (name[12] == 'G' && ((name[17] - '@') & 0x7))
    {
        title_dword_800D92D0 = 1;
        printf((char *)title_aCleardataexistss_800D8B40, name);
    }

    return;

skip:
    str = (char *)title_aBislpm_800D8B58;
    for (i = 0; i < 12; i++)
    {
        if (name[i] != str[i])
        {
            return;
        }
    }

    printf((char *)title_aOldclearflagd_800D8B68, name[17] - '@');

    if (name[12] == 'G' && ((name[17] - '@') & 0x7))
    {
        title_dword_800D92D0 = 1;
        printf((char *)title_aOldcleardataexistss_800D8B7C, name);
    }
}
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D1CB4.s")
/* Moved from openact.c to open.c so open.obj's rdata extends to 0x800D8CD0,
 * where gcc's auto-emitted switch table for 800D2374 lands. */
const int  title_dword_800D8B00 = 0x800CEB74;
const int  title_dword_800D8B04 = 0x800CEC14;
const int  title_dword_800D8B08 = 0x800CEC68;
const int  title_dword_800D8B0C = 0x800CED18;
const int  title_dword_800D8B10 = 0x800CEDC8;
const int  title_dword_800D8B14 = 0x800CEE20;
const int  title_dword_800D8B18 = 0x800CF808;
const int  title_dword_800D8B1C = 0x800CFDE4;
const int  title_dword_800D8B20 = 0x800D03C0;
const int  title_dword_800D8B24 = 0x800D09A8;
const int  title_dword_800D8B28 = 0x800D0F80;
const int  title_dword_800D8B2C = 0x800D1550;
const char title_aClearflagd_800D8B30[] = "clear flag %d\n";
const char title_aCleardataexistss_800D8B40[] = "clear data exists %s\n";
const char title_aBislpm_800D8B58[] = "BISLPM-86111";
const char title_aOldclearflagd_800D8B68[] = "old clear flag %d\n";
const char title_aOldcleardataexistss_800D8B7C[] = "old clear data exists %s\n";
const char title_aGamedatafind_800D8B98[] = "gamedata find!\n";
const char title_aFlagx_800D8BA8[] = "flag = %x\n";
const char title_aFlagnewx_800D8BB4[] = "flag_new = %x\n";
const char title_aThisisrank_800D8BC4[] = "This Is Rank 0\n";
const char title_aThisisrank_800D8BD4[] = "This Is Rank 1\n";
const char title_aThisisrank_800D8BE4[] = "This Is Rank 2\n";
const char title_aThisisrank_800D8BF4[] = "This Is Rank 3\n";
const char title_aThisisrank_800D8C04[] = "This Is Rank 4\n";
const char title_aThisisrank_800D8C14[] = "This Is Rank 5\n";
const char title_aThisisrank_800D8C24[] = "This Is Rank 6\n";
const char title_aPhotodatafind_800D8C34[] = "photodata find!\n";
const char title_aVrfind_800D8C48[] = "VR find!\n";
const char title_aTitlememcardcheckreult_800D8C54[] = "-- Title MemCard Check Reult! --\n";
const char title_aSaveflagd_800D8C78[] = "save_flag = %d\n";
const char title_aPhotoflagd_800D8C88[] = "photo_flag = %d\n";
const char title_aVrflagd_800D8C9C[] = "vr_flag = %d\n";
const char title_aSperankd_800D8CAC[] = "spe_rank = %d\n";
const char title_aDemorankd_800D8CBC[] = "demo_rank = %d\n";
const char title_dword_800D8CCC[] = {0x0, 0x0, 0x0, 0x0};

void title_open_800D2374(OpenWork *work)
{
    int i;

    for (i = 0; i < 24; i++)
    {
        title_open_800C4AD0(work, i, 0);
    }

    if (work->f24BC)
    {
        register int dummy asm("$4") = work->f24B4;
        asm volatile ("" : : "r" (dummy));
        return;
    }

    if (work->f24EC == 0)
    {
        return;
    }

    switch (work->f24AC)
    {
    case 0:
    case 1:
    case 2:
        title_open_800C4AD0(work, 0, 0x6739);
        break;
    case 3:
    case 4:
        title_open_800C4AD0(work, 1, 0x6739);
        title_open_800C4AD0(work, 2, 0x6739);
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        title_open_800C4AD0(work, 3, 0x6739);
        break;
    case 9:
        break;
    case 10:
        title_open_800C4AD0(work, 5, 0x6739);
        break;
    }
}

/* Tail strings moved from openact.c so openact.obj.rdata starts at
 * 0x800D8D58 (mod 8 = 0), preserving .align 3 for OpenAct's switch table. */
const char title_aCdcaseopen_800D8CFC[] = "CD CASE OPEN!!\n";
const char title_aCdnormalspeedsetfailed_800D8D0C[] = "CD NORMAL SPEED SET FAILED!!\n";
const char title_aCdnormalspeedsetsuccess_800D8D2C[] = "CD NORMAL SPEED SET SUCCESS!!\n";
const char title_a_800D8D4C[] = "???????\n";

#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D2460.s")
extern void title_open_800D2460(OpenWork *work);

void title_open_800D2A00(OpenWork *work)
{
    GCL_ARGS args;
    long     argv[3];

    args.argc = 3;
    args.argv = argv;
    argv[0] = work->f24D0;
    argv[1] = work->fB28;
    argv[2] = title_dword_800D92D0;

    if (work->f24BC)
    {
        work->f24B4++;
    }

    title_open_800D2374(work);
    title_open_800C47B8(work, DG_ChanlOTag(1));
    title_open_800D2460(work);

    if (work->f24EC == 0)
    {
        if (work->f24B0 >= 0xA0)
        {
            work->f24EC = 1;
        }
    }

    work->f24B0++;

    if (work->f24B4 >= 0x48)
    {
        GCL_ExecProc(title_dword_800C33D4, &args);
        GV_DestroyActor(work);
    }
}
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D2AFC.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D2CA8.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D2E44.s")

void title_open_800D3500(OpenWork *work, u_long *ot)
{
    int i;

    for (i = 0; i < 24; i++)
    {
        title_open_800C4AD0(work, i, 0);
    }

    if (work->fA74 >= 18 && work->fA74 <= 19)
    {
        title_open_800C4AD0(work, 21, 0x6739);

        MENU_Locate(54, 60, 0x10);
        MENU_Color(100, 160, 135);
        MENU_Printf(title_aMemorycardslot_800D8FAC);

        if (work->f24F0 == 3)
        {
            MENU_Locate(223, 60, 0x10);
            MENU_Color(181, 85, 42);
            MENU_Printf(title_aFull_800D8FC4);
        }
        else
        {
            MENU_Locate(223, 60, 0x10);
            MENU_Color(181, 85, 42);
            MENU_Printf(title_aNocard_800D8FCC);
        }

        MENU_Locate(54, 75, 0x10);
        MENU_Color(100, 160, 135);
        MENU_Printf(title_aMemorycardslot_800D8FD4);

        if (work->f24F4 == 3)
        {
            MENU_Locate(223, 75, 0x10);
            MENU_Color(181, 85, 42);
            MENU_Printf(title_aFull_800D8FC4);
        }
        else
        {
            MENU_Locate(223, 75, 0x10);
            MENU_Color(181, 85, 42);
            MENU_Printf(title_aNocard_800D8FCC);
        }

        MENU_Locate(70, 100, 0x10);
        MENU_Color(100, 160, 135);
        MENU_Printf(title_aDoyouwanttocontinue_800D8FEC);

        MENU_Locate(85, 115, 0x10);
        MENU_Color(100, 160, 135);
        MENU_Printf(title_aYourgamelikethis_800D9008);

        if (work->f24E0 == 0)
        {
            MENU_Locate(100, 150, 0x10);
            MENU_Color(192, 192, 192);
            MENU_Printf(title_aYes_800D9020);

            MENU_Locate(200, 150, 0x10);
            MENU_Color(46, 72, 61);
            MENU_Printf(title_aNo_800D9024);

            title_open_800C4F1C(work, -68, 33, 40, 15, 255, 1);
        }
        else
        {
            MENU_Locate(100, 150, 0x10);
            MENU_Color(46, 72, 61);
            MENU_Printf(title_aYes_800D9020);

            MENU_Locate(200, 150, 0x10);
            MENU_Color(192, 192, 192);
            MENU_Printf(title_aNo_800D9024);

            title_open_800C4F1C(work, 28, 33, 40, 15, 255, 1);
        }
    }

    title_open_800C47B8(work, ot);
}
