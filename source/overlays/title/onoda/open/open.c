#include <stdio.h>
#include <sys/types.h>
#include <libcd.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libdg/libdg.h"
#include "libfs/libfs.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "font/font.h"
#include "menu/menuman.h"
#include "mts/mts.h"
#include "game/game.h"
#include "linkvar.h"
#include "sound/sd_cli.h"
#include "sound/g_sound.h"

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

typedef struct _Work
{
    GV_ACT   actor;
    DG_PRIM *prim[4];
    int      f30[22];
    char     pad1[0x58];
    int      fE0[6];
    int      fF8[18];
    int      f140[9];
    int      f164;     /* main per-state frame counter; case 4/5 transitions trigger when f164 crosses thresholds */
    int      f168;
    int      f16C;
    int      f170;
    int      f174;
    int      f178;
    int      f17C;
    int      f180;
    int      f184;
    int      f188;
    POLY_FT4 f18C_polys[22];
    POLY_FT4 f4FC_polys[18];
    POLY_FT4 f7CC_polys[9];
    POLY_GT4 f934_polys[6];
    GV_PAD  *pad;
    int      fA70;
    int      fA74;     /* OpenAct state (drives the top-level switch) */
    int      fA78;     /* sub-state for case 7 (difficulty 0..5) */
    int      fA7C;
    int      fA80;
    int      fA84;
    int      fA88;
    int      fA8C;
    int      fA90;
    int      fA94;
    int      fA98;
    int      fA9C;
    int      fAA0;
    int      fAA4;
    CVECTOR  fAA8;
    u_char   fAAC;
    u_char   fAAD;
    u_char   fAAE;
    char     fAAF;
    CVECTOR  fAB0;
    CVECTOR  fAB4;
    int      fAB8;
    int      fABC;
    int      fAC0;
    int      fAC4;
    int      fAC8;
    int      fACC;
    int      fAD0;
    int      fAD4;
    int      fAD8;
    int      fADC;
    int      fAE0;
    int      fAE4;
    int      fAE8;
    int      fAEC;
    int      fAF0;
    int      fAF4;
    int      fAF8;
    int      fAFC;
    int      fB00;
    int      fB04;
    int      fB08;
    int      fB0C;     /* set on every state transition; the new state's case re-runs its one-time init then clears this back to 0 */
    int      fB10;
    int      fB14;
    int      fB18;
    int      fB1C;
    int      fB20;
    int      fB24;
    int      fB28;
    int      fB2C[4];
    int      fB3C;
    int      fB40;
    int      fB44;
    int      fB48;
    KCB      kcb[24];
    char     pad2[0x14];
    DR_TPAGE tpage[2];
    char     pad3[0x8];
    Unknown  unk[24];
    int      f2498;
    int      f249C;
    int      f24A0;
    int      f24A4;
    void    *mg_logo;
    int      f24AC;
    int      f24B0;
    int      f24B4;
    int      f24B8;
    int      f24BC;
    int      f24C0;
    int      f24C4;
    int      f24C8;
    int      f24CC;
    int      f24D0;
    int      f24D4;
    int      f24D8;
    int      f24DC;
    int      f24E0;
    int      f24E4;
    int      f24E8;
    int      f24EC;
    int      f24F0;
    int      f24F4;
    int      f24F8_proc;
    int      f24FC;
    int      f2500;
} Work;

typedef struct _Desc
{
    int     f0;
    DVECTOR f4;
    int     color;
} Desc;

extern Desc        open_800C32B4[24];
extern signed char open_800C3400[16];

int SECTION(".bss") title_dword_800D92D0 = 0;

extern int title_dword_800C33D4;

extern char *MGS_MemoryCardName; /* in main.c */
extern int   FS_DiskNum;

extern void *NewMetalGearLogo(int *exit);

extern const char title_aClearflagd_800D8B30[];          // = "clear flag %d\n"
extern const char title_aCleardataexistss_800D8B40[];    // = "clear data exists %s\n"
extern const char title_aBislpm_800D8B58[];              // = "BISLPM-86111"
extern const char title_aOldclearflagd_800D8B68[];       // = "old clear flag %d\n"
extern const char title_aOldcleardataexistss_800D8B7C[]; // = "old clear data exists %s\n"

void Open_800C4500(Work *work, int index)
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

void Open_800C4674(Work *work, int index)
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

static inline void AddTpage(Work *work, u_long *ot, int found, int i)
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

void title_open_800C47B8(Work *work, u_long *ot)
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

void title_open_800C4AD0(Work *work, int index, int color)
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
void title_open_800C4C38(Work *work, int x0, int y0, int xsize, int ysize, int color, int mode)
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

void title_open_800C4F1C(Work *work, int x0, int y0, int xsize, int ysize, int color, int mode)
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

void title_open_800C5360(Work *work, int texid, POLY_FT4 *poly)
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

void title_open_800C53E0(Work *work)
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

void title_open_800C5644(Work *work, int index)
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

void title_open_800C5760(Work *work)
{
    int r, g, b;

    if (work->pad->dir >= 0 && work->pad->dir < 512)
    {
        work->fA70 = 0;
        r = work->fAA8.r - 10;
        g = work->fAA8.g + 5;
        b = work->fAA8.b + 5;
    }
    else if (work->pad->dir >= 512 && work->pad->dir < 1024)
    {
        work->fA70 = 0;
        r = work->fAA8.r - 5;
        g = work->fAA8.g;
        b = work->fAA8.b + 10;
    }
    else if (work->pad->dir >= 1024 && work->pad->dir < 1536)
    {
        work->fA70 = 0;
        r = work->fAA8.r;
        g = work->fAA8.g - 5;
        b = work->fAA8.b + 5;
    }
    else if (work->pad->dir >= 1536 && work->pad->dir < 2048)
    {
        work->fA70 = 0;
        r = work->fAA8.r + 5;
        g = work->fAA8.g - 10;
        b = work->fAA8.b;
    }
    else if (work->pad->dir >= 2048 && work->pad->dir < 2560)
    {
        work->fA70 = 0;
        r = work->fAA8.r + 10;
        g = work->fAA8.g - 5;
        b = work->fAA8.b - 5;
    }
    else if (work->pad->dir >= 2560 && work->pad->dir < 3072)
    {
        work->fA70 = 0;
        r = work->fAA8.r + 5;
        g = work->fAA8.g;
        b = work->fAA8.b - 10;
    }
    else if (work->pad->dir >= 3072 && work->pad->dir < 3584)
    {
        work->fA70 = 0;
        r = work->fAA8.r;
        g = work->fAA8.g + 5;
        b = work->fAA8.b - 5;
    }
    else if (work->pad->dir >= 3584 && work->pad->dir < 4096)
    {
        work->fA70 = 0;
        r = work->fAA8.r - 5;
        g = work->fAA8.g + 10;
        b = work->fAA8.b;
    }
    else if (work->pad->dir == -1)
    {
        work->fA70++;
        r = work->fAA8.r;
        g = work->fAA8.g;
        b = work->fAA8.b;
    }
    else
    {
        r = work->fAA8.r;
        g = work->fAA8.g;
        b = work->fAA8.b;
    }

    if (r >= 0 && r < 255)
    {
        work->fAA8.r = r;
    }

    if (g >= 0 && g < 255)
    {
        work->fAA8.g = g;
    }

    if (b >= 0 && b < 255)
    {
        work->fAA8.b = b;
    }
}

void title_open_800C593C(Work *work)
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

void title_open_800C5CB8(Work *work)
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

void title_open_800C5CF0(Work *work)
{
    int i;

    for (i = 17; i >= 0; i--)
    {
        work->fF8[i] = 0;
    }
}

void title_open_800C5D10(Work *work)
{
    int i;

    for (i = 0; i < 9; i++)
    {
        work->f140[i] = 0;
    }
}

void title_open_800C5D30(Work *work)
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

void title_open_800C61E0(Work *work, GCL_ARGS *args)
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
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C628C.s")

extern CVECTOR title_dword_800C33D8[];

void title_open_800CCDC8(Work *work)
{
    if (work->fA70 < 3)
    {
        work->fA88 = 0;
    }

    switch (work->fA88)
    {
    case 0:
        if (work->fA70 < 3)
        {
            return;
        }

        if ((LLOAD(&work->fAA8) & 0xFFFFFF) == 0x808080)
        {
            work->fA88 = 3;
            work->f174 = 0;
            work->fAB0 = work->fAA8;
            work->fAB4 = title_dword_800C33D8[title_open_800C4B2C(8)];
        }
        else
        {
            work->fA88 = 1;
            work->f174 = 0;
            work->fAB0 = work->fAA8;
            work->fAB4 = title_dword_800C33D8[9];
        }
        break;

    case 2:
        if (work->f174 >= 128)
        {
            work->fA88 = 3;
            work->f174 = 0;
            work->fAB0 = work->fAA8;
            work->fAB4 = title_dword_800C33D8[title_open_800C4B2C(8)];
        }
        break;

    case 3:
        work->fAA8.r = work->fAB0.r + (work->fAB4.r - work->fAB0.r) * work->f174 / 128;
        work->fAA8.g = work->fAB0.g + (work->fAB4.g - work->fAB0.g) * work->f174 / 128;
        work->fAA8.b = work->fAB0.b + (work->fAB4.b - work->fAB0.b) * work->f174 / 128;

        if (work->f174 >= 128)
        {
            work->fA88 = 4;
            work->f174 = 0;
            work->fAA8 = work->fAB4;
        }
        break;

    case 4:
        if (work->f174 >= 128)
        {
            work->fA88 = 5;
            work->f174 = 0;
            work->fAB0 = work->fAA8;
            work->fAB4 = title_dword_800C33D8[9];
        }
        break;

    case 1:
    case 5:
        work->fAA8.r = work->fAB0.r + (work->fAB4.r - work->fAB0.r) * work->f174 / 128;
        work->fAA8.g = work->fAB0.g + (work->fAB4.g - work->fAB0.g) * work->f174 / 128;
        work->fAA8.b = work->fAB0.b + (work->fAB4.b - work->fAB0.b) * work->f174 / 128;

        if (work->f174 >= 128)
        {
            work->fA88 = 2;
            work->f174 = 0;
            work->fAA8 = work->fAB4;
        }
        break;
    }
}

void title_open_800CD074(Work *work)
{
    int sqrt1, sqrt2;
    int val1, val2, val3;
    int val1_2, val2_2, val3_2;

    val1 = work->fAA8.r;
    val2 = work->fAA8.g;
    val3 = work->fAA8.b;
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

void title_open_800CD23C(Work *work, int index, int arg3)
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

void title_open_800CD320(Work *work, int index)
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


void title_open_800CD3B8(Work *work, int index)
{
    POLY_FT4 *poly;
    DG_TEX   *tex;
    int       i;

    poly = work->f18C_polys;
    poly += index;

    switch (work->fA7C)
    {
    case 0:
    {
        int c = work->f168 * 2;
        setRGB0(&poly[0], c, c, c);
        setRGB0(&poly[1], c, c, c);
        setRGB0(&poly[2], c, c, c);
    }
        for (i = 0; i < 3; i++)
        {
            poly->x0--;
            poly->x1--;
            poly->x2--;
            poly->x3--;
            poly++;
        }
        if (work->f168 < 0x40)
        {
            return;
        }
        work->fA7C = 1;
        return;
    case 1:
        for (i = 0; i < 3; i++)
        {
            poly->x0--;
            poly->x1--;
            poly->x2--;
            poly->x3--;
            poly++;
        }
        if (work->f168 < 0xA0)
        {
            return;
        }
        work->fA7C = 2;
        work->f168 = 0;
        poly = &work->f18C_polys[0];
        tex = DG_GetTexture(GV_StrCode("op_back_r"));
        {
            int u0 = tex->off_x;
            int u1 = u0 + tex->w + 1;
            int v0 = tex->off_y;
            int v1 = v0 + tex->h + 1;
            setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);
        }
        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
        setXY4(poly, -0xA0, -0x70, 0, -0x70, -0xA0, 0x70, 0, 0x70);
        setRGB0(poly, 0x80, 0x80, 0x80);
        poly = &work->f18C_polys[1];
        tex = DG_GetTexture(GV_StrCode("op_back_l"));
        {
            int u0 = tex->off_x;
            int u1 = u0 + tex->w + 1;
            int v0 = tex->off_y;
            int v1 = v0 + tex->h + 1;
            setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);
        }
        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
        setXY4(poly, 0, -0x70, 0xA0, -0x70, 0, 0x70, 0xA0, 0x70);
        setRGB0(poly, 0x80, 0x80, 0x80);
        poly = &work->f18C_polys[2];
        tex = DG_GetTexture(GV_StrCode("op_back_r"));
        {
            int u0 = tex->off_x;
            int u1 = u0 + tex->w + 1;
            int v0 = tex->off_y;
            int v1 = v0 + tex->h + 1;
            setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);
        }
        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
        setXY4(poly, 0xA0, -0x70, 0x140, -0x70, 0xA0, 0x70, 0x140, 0x70);
        setRGB0(poly, 0x80, 0x80, 0x80);
        break;
    case 2:
        for (i = 0; i < 3; i++)
        {
            poly->x0--;
            poly->x1--;
            poly->x2--;
            poly->x3--;
            poly++;
        }
        if (work->f168 < 0xA0)
        {
            return;
        }
        work->fA7C = 1;
        work->f168 = 0;
        poly = &work->f18C_polys[0];
        tex = DG_GetTexture(GV_StrCode("op_back_l"));
        {
            int u0 = tex->off_x;
            int u1 = u0 + tex->w + 1;
            int v0 = tex->off_y;
            int v1 = v0 + tex->h + 1;
            setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);
        }
        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
        setXY4(poly, -0xA0, -0x70, 0, -0x70, -0xA0, 0x70, 0, 0x70);
        setRGB0(poly, 0x80, 0x80, 0x80);
        poly = &work->f18C_polys[1];
        tex = DG_GetTexture(GV_StrCode("op_back_r"));
        {
            int u0 = tex->off_x;
            int u1 = u0 + tex->w + 1;
            int v0 = tex->off_y;
            int v1 = v0 + tex->h + 1;
            setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);
        }
        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
        setXY4(poly, 0, -0x70, 0xA0, -0x70, 0, 0x70, 0xA0, 0x70);
        setRGB0(poly, 0x80, 0x80, 0x80);
        poly = &work->f18C_polys[2];
        tex = DG_GetTexture(GV_StrCode("op_back_l"));
        {
            int u0 = tex->off_x;
            int u1 = u0 + tex->w + 1;
            int v0 = tex->off_y;
            int v1 = v0 + tex->h + 1;
            setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);
        }
        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
        setXY4(poly, 0xA0, -0x70, 0x140, -0x70, 0xA0, 0x70, 0x140, 0x70);
        setRGB0(poly, 0x80, 0x80, 0x80);
        break;
    }
}


void title_open_800CD800(Work *work, int index)
{
    POLY_FT4 *poly;
    DG_TEX   *tex;
    int       shade;

    poly = work->f18C_polys;
    poly += index;

    switch (work->fA80)
    {
    case 0:
        if (work->f16C >= 0x20)
        {
            work->fA80 = 1;
            work->f16C = 0;
        }
        break;
    case 1:
        shade = work->f16C * 2;
        poly->r0 = shade;
        poly->g0 = shade;
        poly->b0 = shade;
        poly->y0--;
        poly->y1--;
        poly->y2--;
        poly->y3--;
        if (work->f16C >= 0x40)
        {
            work->fA80 = 2;
            work->f16C = 0;
            poly->r0 = 0x80;
            poly->g0 = 0x80;
            poly->b0 = 0x80;
        }
        break;
    case 2:
        poly->r0 = 0x80;
        poly->g0 = 0x80;
        poly->b0 = 0x80;
        poly->y0--;
        poly->y1--;
        poly->y2--;
        poly->y3--;
        if (work->f16C >= 0x94)
        {
            work->fA80 = 3;
            work->f16C = 0;
        }
        break;
    case 3:
        shade = 0x80 - work->f16C * 2;
        poly->r0 = shade;
        poly->g0 = shade;
        poly->b0 = shade;
        poly->y0--;
        poly->y1--;
        poly->y2--;
        poly->y3--;
        if (work->f16C >= 0x40)
        {
            work->fA80 = 4;
            work->f16C = 0;
            tex = DG_GetTexture(GV_StrCode("op_back_l"));
            title_open_800C5238(poly, tex, 6, 0x140, 0x1F4);
            setXY4(poly, -0xA0, -0x70, 0xA0, -0x70, -0xA0, 0x184, 0xA0, 0x184);
            title_open_800C5200(poly, 2);
        }
        break;
    case 4:
        shade = work->f16C * 2;
        poly->r0 = shade;
        poly->g0 = shade;
        poly->b0 = shade;
        poly->y0--;
        poly->y1--;
        poly->y2--;
        poly->y3--;
        if (work->f16C >= 0x40)
        {
            work->fA80 = 5;
            work->f16C = 0;
            poly->r0 = 0x80;
            poly->g0 = 0x80;
            poly->b0 = 0x80;
        }
        break;
    case 5:
        poly->r0 = 0x80;
        poly->g0 = 0x80;
        poly->b0 = 0x80;
        poly->y0--;
        poly->y1--;
        poly->y2--;
        poly->y3--;
        if (work->f16C >= 0x94)
        {
            work->fA80 = 6;
            work->f16C = 0;
        }
        break;
    case 6:
        shade = 0x80 - work->f16C * 2;
        poly->r0 = shade;
        poly->g0 = shade;
        poly->b0 = shade;
        poly->y0--;
        poly->y1--;
        poly->y2--;
        poly->y3--;
        if (work->f16C >= 0x40)
        {
            work->fA80 = 1;
            work->f16C = 0;
            tex = DG_GetTexture(GV_StrCode("op_back_r"));
            title_open_800C5238(poly, tex, 6, 0x140, 0x1F4);
            setXY4(poly, -0xA0, -0x70, 0xA0, -0x70, -0xA0, 0x184, 0xA0, 0x184);
            title_open_800C5200(poly, 2);
        }
        break;
    }
}

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

void title_open_800CDBF8(Work *work, int index)
{
    POLY_FT4 *poly;
    DG_TEX   *tex;

    poly = work->f18C_polys;
    poly += index;

    if (work->fA7C < 0)
    {
        return;
    }

    switch (work->fA7C)
    {
    case 0:
    case 1:
        tex = DG_GetTexture(GV_StrCode("op_back_l"));
        title_open_800CDB9C(poly, tex, work->f168);
        setXY4(poly, -0xA0, -0x70, work->fAA0, -0x70, -0xA0, 0x70, work->fAA0, 0x70);
        setRGB0(poly, 0, 0, 0);
        poly++;
        tex = DG_GetTexture(GV_StrCode("op_back_r"));
        {
            int u0 = tex->off_x;
            int u1 = u0 + tex->w + 1;
            int v0 = tex->off_y;
            int v1 = v0 + tex->h + 1;
            setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);
        }
        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
        setXY4(poly, work->fAA0, -0x70, work->fAA4, -0x70, work->fAA0, 0x70, work->fAA4, 0x70);
        setRGB0(poly, 0, 0, 0);
        poly++;
        tex = DG_GetTexture(GV_StrCode("op_back_l"));
        title_open_800CDB4C(poly, tex, work->f168);
        setXY4(poly, work->fAA4, -0x70, 0xA0, -0x70, work->fAA4, 0x70, 0xA0, 0x70);
        setRGB0(poly, 0, 0, 0);
        break;
    case 2:
        tex = DG_GetTexture(GV_StrCode("op_back_r"));
        title_open_800CDB9C(poly, tex, work->f168);
        setXY4(poly, -0xA0, -0x70, work->fAA0, -0x70, -0xA0, 0x70, work->fAA0, 0x70);
        setRGB0(poly, 0, 0, 0);
        poly++;
        tex = DG_GetTexture(GV_StrCode("op_back_l"));
        {
            int u0 = tex->off_x;
            int u1 = u0 + tex->w + 1;
            int v0 = tex->off_y;
            int v1 = v0 + tex->h + 1;
            setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);
        }
        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
        setXY4(poly, work->fAA0, -0x70, work->fAA4, -0x70, work->fAA0, 0x70, work->fAA4, 0x70);
        setRGB0(poly, 0, 0, 0);
        poly++;
        tex = DG_GetTexture(GV_StrCode("op_back_r"));
        title_open_800CDB4C(poly, tex, work->f168);
        setXY4(poly, work->fAA4, -0x70, 0xA0, -0x70, work->fAA4, 0x70, 0xA0, 0x70);
        setRGB0(poly, 0, 0, 0);
        break;
    }
}
extern void title_open_800CDBF8(Work *work, int index);

void title_open_800CDE44(Work *work, int index)
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
const char title_dword_800D8AE4[] = {0x0, 0x0, 0x0, 0x0};

void title_open_800CE378(Work *work, int idx)
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
 * (8-byte aligned) so the .obj-local offset of "NO" keeps the
 * same alignment-mod-8 as in the original openact.obj.
 */
const char title_dword_800D8AFC[] = {0x0, 0x0, 0x0, 0x0};

void title_open_800CE4A8(Work *work, int index)
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

void title_open_800CE544(Work *work, int index)
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

void title_open_800CE5F8(Work *work, int index)
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

void title_open_800CE6AC(Work *work, int index)
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

void title_open_800CE748(Work *work, int index)
{
    POLY_FT4 *poly;
    DG_TEX   *tex;
    int       r, g, b;
    int       i;

    poly = work->f18C_polys;
    poly += index;
    r = work->fAA8.r;
    g = work->fAA8.g;
    b = work->fAA8.b;

    switch (work->fA7C)
    {
    case 1:
        for (i = 0; i < 3; i++)
        {
            setRGB0(poly, r, g, b);
            poly->x0--;
            poly->x1--;
            poly->x2--;
            poly->x3--;
            poly++;
        }
        {
        int width = work->f168;
        if (width != 0xA0)
        {
            return;
        }
        work->fA7C = 2;
        work->f168 = 0;
        poly = &work->f18C_polys[0];
        tex = DG_GetTexture(GV_StrCode("op_back_r"));
        {
            int u0 = tex->off_x;
            int u1 = u0 + tex->w + 1;
            int v0 = tex->off_y;
            int v1 = v0 + tex->h + 1;
            setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);
        }
        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
        setXY4(poly, -0xA0, -0x70, 0, -0x70, -0xA0, 0x70, 0, 0x70);
        setRGB0(poly, r, g, b);
        poly = &work->f18C_polys[1];
        tex = DG_GetTexture(GV_StrCode("op_back_l"));
        {
            int u0 = tex->off_x;
            int u1 = u0 + tex->w + 1;
            int v0 = tex->off_y;
            int v1 = v0 + tex->h + 1;
            setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);
        }
        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
        setXY4(poly, 0, -0x70, width, -0x70, 0, 0x70, width, 0x70);
        setRGB0(poly, r, g, b);
        poly = &work->f18C_polys[2];
        tex = DG_GetTexture(GV_StrCode("op_back_r"));
        {
            int u0 = tex->off_x;
            int u1 = u0 + tex->w + 1;
            int v0 = tex->off_y;
            int v1 = v0 + tex->h + 1;
            setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);
        }
        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
        setXY4(poly, width, -0x70, 0x140, -0x70, width, 0x70, 0x140, 0x70);
        setRGB0(poly, r, g, b);
        }
        break;
    case 2:
        for (i = 0; i < 3; i++)
        {
            setRGB0(poly, r, g, b);
            poly->x0--;
            poly->x1--;
            poly->x2--;
            poly->x3--;
            poly++;
        }
        {
        int width = work->f168;
        if (width != 0xA0)
        {
            return;
        }
        work->fA7C = 1;
        work->f168 = 0;
        poly = &work->f18C_polys[0];
        tex = DG_GetTexture(GV_StrCode("op_back_l"));
        {
            int u0 = tex->off_x;
            int u1 = u0 + tex->w + 1;
            int v0 = tex->off_y;
            int v1 = v0 + tex->h + 1;
            setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);
        }
        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
        setXY4(poly, -0xA0, -0x70, 0, -0x70, -0xA0, 0x70, 0, 0x70);
        setRGB0(poly, r, g, b);
        poly = &work->f18C_polys[1];
        tex = DG_GetTexture(GV_StrCode("op_back_r"));
        {
            int u0 = tex->off_x;
            int u1 = u0 + tex->w + 1;
            int v0 = tex->off_y;
            int v1 = v0 + tex->h + 1;
            setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);
        }
        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
        setXY4(poly, 0, -0x70, width, -0x70, 0, 0x70, width, 0x70);
        setRGB0(poly, r, g, b);
        poly = &work->f18C_polys[2];
        tex = DG_GetTexture(GV_StrCode("op_back_l"));
        {
            int u0 = tex->off_x;
            int u1 = u0 + tex->w + 1;
            int v0 = tex->off_y;
            int v1 = v0 + tex->h + 1;
            setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);
        }
        poly->tpage = tex->tpage;
        poly->clut = tex->clut;
        setXY4(poly, width, -0x70, 0x140, -0x70, width, 0x70, 0x140, 0x70);
        setRGB0(poly, r, g, b);
        }
        break;
    }
}

const int title_dword_800D8B00 = 0x800CEB74;
const int title_dword_800D8B04 = 0x800CEC14;
const int title_dword_800D8B08 = 0x800CEC68;
const int title_dword_800D8B0C = 0x800CED18;
const int title_dword_800D8B10 = 0x800CEDC8;
const int title_dword_800D8B14 = 0x800CEE20;
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CEB14.s")

void title_open_800CEF54(Work *work, int index)
{
    POLY_FT4 *pack;
    int       r;
    int       g;
    int       b;
    int       sr;
    int       sg;
    int       sb;
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

    r = work->fAAC;
    g = work->fAAD;
    b = work->fAAE;

    switch (work->fA84)
    {
    case 1:
        sr = (r * work->f170) / 64;
        sg = (g * work->f170) / 64;
        sb = (b * work->f170) / 64;
        setRGB0(&pack[0], sr, sg, sb);
        setRGB0(&pack[1], sr, sg, sb);
        setRGB0(&pack[2], sr, sg, sb);
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
        setRGB0(&pack[0], r, g, b);
        setRGB0(&pack[1], r, g, b);
        setRGB0(&pack[2], r, g, b);
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
        sr = (r * (0x80 - work->f170)) / 128;
        sg = (g * (0x80 - work->f170)) / 128;
        sb = (b * (0x80 - work->f170)) / 128;
        setRGB0(&pack[0], sr, sg, sb);
        setRGB0(&pack[1], sr, sg, sb);
        setRGB0(&pack[2], sr, sg, sb);
        t3 = work->f170 + 0x148;
        left = (-(t3 * 0xA0)) / 200;
        top = (-(t3 * 0x70)) / 200;
        right = (t3 * 0xA0) / 200;
        bot = (t3 * 0x70) / 200;
        x_aa0 = (work->fAA0 * t3) / 200;
        x_aa4 = (work->fAA4 * t3) / 200;
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

void title_open_800CF504(Work *work, int index)
{
    POLY_FT4 *p;
    int counter, r_val;

    p = work->f18C_polys;
    p += index;

    switch (work->fA98)
    {
    case 2:
        p->r0 = 0xFF;
        p->g0 = 0x40;
        p->b0 = 0x40;
        if (work->f184 >= 0x20)
        {
            work->fA98 = 3;
            work->f184 = 0;
        }
        break;
    case 3:
        r_val = ~(work->f184 * 8);
        counter = 0x40 - work->f184 * 2;
        p->r0 = r_val;
        p->g0 = counter;
        p->b0 = counter;
        if (work->f184 >= 0x18)
        {
            work->fA98 = 4;
            work->f184 = 0;
        }
        break;
    case 4:
        r_val = work->f184 * 8 + 0x3F;
        counter = work->f184 * 2 + 0x10;
        p->r0 = r_val;
        p->g0 = counter;
        p->b0 = counter;
        if (work->f184 >= 0x18)
        {
            work->fA98 = 2;
            work->f184 = 0;
        }
        break;
    }
}
void title_open_800CF610(Work *work, int index)
{
    POLY_GT4 *p;
    int counter, r_val;

    p = work->f934_polys;
    p += index;

    switch (work->fA98)
    {
    case 2:
        p->r0 = 0xFF;
        p->g0 = 0x40;
        p->b0 = 0x40;
        p->r1 = 0xFF;
        p->g1 = 0x40;
        p->b1 = 0x40;
        p->r2 = 0xFF;
        p->g2 = 0x40;
        p->b2 = 0x40;
        p->r3 = 0xFF;
        p->g3 = 0x40;
        p->b3 = 0x40;
        if (work->f184 >= 0x20)
        {
            work->fA98 = 3;
            work->f184 = 0;
        }
        break;
    case 3:
        r_val = 0xFF - work->f184 * 8;
        counter = 0x40 - work->f184 * 2;
        p->r0 = r_val;
        p->g0 = counter;
        p->b0 = counter;
        p->r1 = r_val;
        p->g1 = counter;
        p->b1 = counter;
        p->r2 = r_val;
        p->g2 = counter;
        p->b2 = counter;
        p->r3 = r_val;
        p->g3 = counter;
        p->b3 = counter;
        if (work->f184 >= 0x18)
        {
            work->fA98 = 4;
            work->f184 = 0;
        }
        break;
    case 4:
        r_val = work->f184 * 8 + 0x3F;
        counter = work->f184 * 2 + 0x10;
        p->r0 = r_val;
        p->g0 = counter;
        p->b0 = counter;
        p->r1 = r_val;
        p->g1 = counter;
        p->b1 = counter;
        p->r2 = r_val;
        p->g2 = counter;
        p->b2 = counter;
        p->r3 = r_val;
        p->g3 = counter;
        p->b3 = counter;
        if (work->f184 >= 0x18)
        {
            work->fA98 = 2;
            work->f184 = 0;
        }
        break;
    }
}

void title_open_800CF794(Work *work)
{
    POLY_GT4 *poly = work->f934_polys;
    int top1, bot1, top2, bot2, top3, bot3, bot4;

    if (work->fB14 == 0)
    {
        return;
    }
    if (work->fB14 == 6)
    {
        return;
    }

    switch (work->fA78)
    {
    case 0:
        if (work->fB14 == 5)
        {
            setXY4(&poly[4], -0x1E, 0x37, 0x1E, 0x37, -0x1E, 0x3F, 0x1E, 0x3F);
            setXY4(&poly[0], -0x26, 0x46, 0x26, 0x46, -0x26, 0x4E, 0x26, 0x4E);
            setXY4(&poly[1], -0x28, 0x55, 0x28, 0x55, -0x28, 0x5D, 0x28, 0x5D);
            title_open_800C4B94(&poly[4], 0, 0, 0, 0x80, 0xC0, 0x80);
            title_open_800C4B94(&poly[0], 0x80, 0xC0, 0x80, 0x80, 0xC0, 0x80);
            title_open_800C4B94(&poly[1], 0x80, 0xC0, 0x80, 0, 0, 0);
            SetSemiTrans(&poly[4], 1);
            SetSemiTrans(&poly[0], 0);
            SetSemiTrans(&poly[1], 1);
            work->fE0[0] = 0x100;
            work->fE0[1] = 0x100;
            work->fE0[2] = 0;
            work->fE0[3] = 0;
            work->fE0[4] = 0x100;
            work->fE0[5] = 0;
        }
        else
        {
            int y = work->fB14 * 3;

            if (work->fB18 == 0)
            {
                setXY4(&poly[4], -0x1E, y + 0x28, 0x1E, y + 0x28, -0x1E, y + 0x30, 0x1E, y + 0x30);
                setXY4(&poly[0], -0x26, y + 0x37, 0x26, y + 0x37, -0x26, y + 0x3F, 0x26, y + 0x3F);
                setXY4(&poly[1], -0x28, y + 0x46, 0x28, y + 0x46, -0x28, y + 0x4E, 0x28, y + 0x4E);
                setXY4(&poly[2], -0x1A, y + 0x55, 0x1A, y + 0x55, -0x1A, y + 0x5D, 0x1A, y + 0x5D);
                SetSemiTrans(&poly[4], 1);
                SetSemiTrans(&poly[0], 1);
                SetSemiTrans(&poly[1], 1);
                SetSemiTrans(&poly[2], 1);
                top1 = 0;
                work->fE0[0] = 0x100;
                work->fE0[1] = 0x100;
                work->fE0[2] = 0x100;
                work->fE0[3] = 0;
                work->fE0[4] = 0x100;
                work->fE0[5] = 0;
                if (work->fB14 < 3)
                {
                    bot1 = top1;
                    work->fE0[4] = 0;
                }
                else
                {
                    bot1 = (work->fB14 - 2) * 128 / 3;
                }
                if (work->fB14 < 4)
                {
                    top2 = work->fB14 * 128 / 3;
                }
                else
                {
                    top2 = 0x80;
                }
                bot2 = 0x80;
                top3 = bot2;
                if (work->fB14 < 3)
                {
                    bot3 = 0x80;
                }
                else
                {
                    bot3 = top3 - (work->fB14 - 2) * 128 / 3;
                }
                if (work->fB14 < 4)
                {
                    bot4 = 0x80 - work->fB14 * 128 / 3;
                }
                else
                {
                    bot4 = 0;
                    work->fE0[2] = 0;
                }
                title_open_800C4BD4(&poly[4], top1, bot1);
                title_open_800C4BD4(&poly[0], top2, bot2);
                title_open_800C4BD4(&poly[1], top3, bot3);
                title_open_800C4BD4(&poly[2], bot4, 0);
            }
            else
            {
                setXY4(&poly[3], -0x20, 0x37 - y, 0x20, 0x37 - y, -0x20, 0x3F - y, 0x20, 0x3F - y);
                setXY4(&poly[4], -0x1E, 0x46 - y, 0x1E, 0x46 - y, -0x1E, 0x4E - y, 0x1E, 0x4E - y);
                setXY4(&poly[0], -0x26, 0x55 - y, 0x26, 0x55 - y, -0x26, 0x5D - y, 0x26, 0x5D - y);
                setXY4(&poly[1], -0x28, 0x64 - y, 0x28, 0x64 - y, -0x28, 0x6C - y, 0x28, 0x6C - y);
                SetSemiTrans(&poly[3], 1);
                SetSemiTrans(&poly[4], 1);
                SetSemiTrans(&poly[0], 1);
                SetSemiTrans(&poly[1], 1);
                top1 = 0;
                work->fE0[0] = 0x100;
                work->fE0[1] = 0x100;
                work->fE0[2] = 0;
                work->fE0[3] = 0x100;
                work->fE0[4] = 0x100;
                work->fE0[5] = 0;
                if (work->fB14 < 4)
                {
                    bot1 = 0x80 - work->fB14 * 128 / 3;
                    work->fE0[3] = 0; /* sic: original zeroes the exit row in this
                                       * arm; every other case does it in the else */
                }
                else
                {
                    bot1 = 0;
                }
                if (work->fB14 < 3)
                {
                    top2 = 0x80;
                }
                else
                {
                    top2 = 0x80 - (work->fB14 - 2) * 128 / 3;
                }
                bot2 = 0x80;
                top3 = bot2;
                if (work->fB14 < 4)
                {
                    bot3 = work->fB14 * 128 / 3;
                }
                else
                {
                    bot3 = 0x80;
                }
                if (work->fB14 < 3)
                {
                    bot4 = 0;
                    work->fE0[1] = 0;
                }
                else
                {
                    bot4 = (work->fB14 - 2) * 128 / 3;
                }
                title_open_800C4BD4(&poly[3], top1, bot1);
                title_open_800C4BD4(&poly[4], top2, bot2);
                title_open_800C4BD4(&poly[0], top3, bot3);
                title_open_800C4BD4(&poly[1], bot4, 0);
            }
        }
        break;

    case 1:
        if (work->fB14 == 5)
        {
            setXY4(&poly[0], -0x26, 0x37, 0x26, 0x37, -0x26, 0x3F, 0x26, 0x3F);
            setXY4(&poly[1], -0x28, 0x46, 0x28, 0x46, -0x28, 0x4E, 0x28, 0x4E);
            setXY4(&poly[2], -0x1A, 0x55, 0x1A, 0x55, -0x1A, 0x5D, 0x1A, 0x5D);
            title_open_800C4B94(&poly[0], 0, 0, 0, 0x80, 0xC0, 0x80);
            title_open_800C4B94(&poly[1], 0x80, 0xC0, 0x80, 0x80, 0xC0, 0x80);
            title_open_800C4B94(&poly[2], 0x80, 0xC0, 0x80, 0, 0, 0);
            SetSemiTrans(&poly[0], 1);
            SetSemiTrans(&poly[1], 0);
            SetSemiTrans(&poly[2], 1);
            work->fE0[0] = 0x100;
            work->fE0[1] = 0x100;
            work->fE0[2] = 0x100;
            work->fE0[3] = 0;
            work->fE0[4] = 0;
            work->fE0[5] = 0;
        }
        else
        {
            int y = work->fB14 * 3;

            if (work->fB18 == 0)
            {
                setXY4(&poly[0], -0x26, y + 0x28, 0x26, y + 0x28, -0x26, y + 0x30, 0x26, y + 0x30);
                setXY4(&poly[1], -0x28, y + 0x37, 0x28, y + 0x37, -0x28, y + 0x3F, 0x28, y + 0x3F);
                setXY4(&poly[2], -0x1A, y + 0x46, 0x1A, y + 0x46, -0x1A, y + 0x4E, 0x1A, y + 0x4E);
                setXY4(&poly[3], -0x20, y + 0x55, 0x20, y + 0x55, -0x20, y + 0x5D, 0x20, y + 0x5D);
                SetSemiTrans(&poly[0], 1);
                SetSemiTrans(&poly[1], 1);
                SetSemiTrans(&poly[2], 1);
                SetSemiTrans(&poly[3], 1);
                top1 = 0;
                work->fE0[0] = 0x100;
                work->fE0[1] = 0x100;
                work->fE0[2] = 0x100;
                work->fE0[3] = 0x100;
                work->fE0[4] = 0;
                work->fE0[5] = 0;
                if (work->fB14 < 3)
                {
                    bot1 = top1;
                    work->fE0[0] = 0;
                }
                else
                {
                    bot1 = (work->fB14 - 2) * 128 / 3;
                }
                if (work->fB14 < 4)
                {
                    top2 = work->fB14 * 128 / 3;
                }
                else
                {
                    top2 = 0x80;
                }
                bot2 = 0x80;
                top3 = bot2;
                if (work->fB14 < 3)
                {
                    bot3 = 0x80;
                }
                else
                {
                    bot3 = top3 - (work->fB14 - 2) * 128 / 3;
                }
                if (work->fB14 < 4)
                {
                    bot4 = 0x80 - work->fB14 * 128 / 3;
                }
                else
                {
                    bot4 = 0;
                    work->fE0[3] = 0;
                }
                title_open_800C4BD4(&poly[0], top1, bot1);
                title_open_800C4BD4(&poly[1], top2, bot2);
                title_open_800C4BD4(&poly[2], top3, bot3);
                title_open_800C4BD4(&poly[3], bot4, 0);
            }
            else
            {
                setXY4(&poly[4], -0x1E, 0x37 - y, 0x1E, 0x37 - y, -0x1E, 0x3F - y, 0x1E, 0x3F - y);
                setXY4(&poly[0], -0x26, 0x46 - y, 0x26, 0x46 - y, -0x26, 0x4E - y, 0x26, 0x4E - y);
                setXY4(&poly[1], -0x28, 0x55 - y, 0x28, 0x55 - y, -0x28, 0x5D - y, 0x28, 0x5D - y);
                setXY4(&poly[2], -0x1A, 0x64 - y, 0x1A, 0x64 - y, -0x1A, 0x6C - y, 0x1A, 0x6C - y);
                SetSemiTrans(&poly[4], 1);
                SetSemiTrans(&poly[0], 1);
                SetSemiTrans(&poly[1], 1);
                SetSemiTrans(&poly[2], 1);
                top1 = 0;
                work->fE0[0] = 0x100;
                work->fE0[1] = 0x100;
                work->fE0[2] = 0x100;
                work->fE0[3] = 0;
                work->fE0[4] = 0x100;
                work->fE0[5] = 0;
                if (work->fB14 < 4)
                {
                    bot1 = 0x80 - work->fB14 * 128 / 3;
                }
                else
                {
                    bot1 = 0;
                    work->fE0[4] = 0;
                }
                if (work->fB14 < 3)
                {
                    top2 = 0x80;
                }
                else
                {
                    top2 = 0x80 - (work->fB14 - 2) * 128 / 3;
                }
                bot2 = 0x80;
                top3 = bot2;
                if (work->fB14 < 4)
                {
                    bot3 = work->fB14 * 128 / 3;
                }
                else
                {
                    bot3 = 0x80;
                }
                if (work->fB14 < 3)
                {
                    bot4 = 0;
                    work->fE0[2] = 0;
                }
                else
                {
                    bot4 = (work->fB14 - 2) * 128 / 3;
                }
                title_open_800C4BD4(&poly[4], top1, bot1);
                title_open_800C4BD4(&poly[0], top2, bot2);
                title_open_800C4BD4(&poly[1], top3, bot3);
                title_open_800C4BD4(&poly[2], bot4, 0);
            }
        }
        break;

    case 2:
        if (work->fB14 == 5)
        {
            setXY4(&poly[1], -0x28, 0x37, 0x28, 0x37, -0x28, 0x3F, 0x28, 0x3F);
            setXY4(&poly[2], -0x1A, 0x46, 0x1A, 0x46, -0x1A, 0x4E, 0x1A, 0x4E);
            setXY4(&poly[3], -0x20, 0x55, 0x20, 0x55, -0x20, 0x5D, 0x20, 0x5D);
            title_open_800C4B94(&poly[1], 0, 0, 0, 0x80, 0xC0, 0x80);
            title_open_800C4B94(&poly[2], 0x80, 0xC0, 0x80, 0x80, 0xC0, 0x80);
            title_open_800C4B94(&poly[3], 0x80, 0xC0, 0x80, 0, 0, 0);
            SetSemiTrans(&poly[1], 1);
            SetSemiTrans(&poly[2], 0);
            SetSemiTrans(&poly[3], 1);
            work->fE0[0] = 0;
            work->fE0[1] = 0x100;
            work->fE0[2] = 0x100;
            work->fE0[3] = 0x100;
            work->fE0[4] = 0;
            work->fE0[5] = 0;
        }
        else
        {
            int y = work->fB14 * 3;

            if (work->fB18 == 0)
            {
                setXY4(&poly[1], -0x28, y + 0x28, 0x28, y + 0x28, -0x28, y + 0x30, 0x28, y + 0x30);
                setXY4(&poly[2], -0x1A, y + 0x37, 0x1A, y + 0x37, -0x1A, y + 0x3F, 0x1A, y + 0x3F);
                setXY4(&poly[3], -0x20, y + 0x46, 0x20, y + 0x46, -0x20, y + 0x4E, 0x20, y + 0x4E);
                setXY4(&poly[4], -0x1E, y + 0x55, 0x1E, y + 0x55, -0x1E, y + 0x5D, 0x1E, y + 0x5D);
                SetSemiTrans(&poly[1], 1);
                SetSemiTrans(&poly[2], 1);
                SetSemiTrans(&poly[3], 1);
                SetSemiTrans(&poly[4], 1);
                top1 = 0;
                work->fE0[0] = 0;
                work->fE0[1] = 0x100;
                work->fE0[2] = 0x100;
                work->fE0[3] = 0x100;
                work->fE0[4] = 0x100;
                work->fE0[5] = 0;
                if (work->fB14 < 3)
                {
                    bot1 = top1;
                    work->fE0[1] = 0;
                }
                else
                {
                    bot1 = (work->fB14 - 2) * 128 / 3;
                }
                if (work->fB14 < 4)
                {
                    top2 = work->fB14 * 128 / 3;
                }
                else
                {
                    top2 = 0x80;
                }
                bot2 = 0x80;
                top3 = bot2;
                if (work->fB14 < 3)
                {
                    bot3 = 0x80;
                }
                else
                {
                    bot3 = top3 - (work->fB14 - 2) * 128 / 3;
                }
                if (work->fB14 < 4)
                {
                    bot4 = 0x80 - work->fB14 * 128 / 3;
                }
                else
                {
                    bot4 = 0;
                    work->fE0[4] = 0;
                }
                title_open_800C4BD4(&poly[1], top1, bot1);
                title_open_800C4BD4(&poly[2], top2, bot2);
                title_open_800C4BD4(&poly[3], top3, bot3);
                title_open_800C4BD4(&poly[4], bot4, 0);
            }
            else
            {
                setXY4(&poly[0], -0x26, 0x37 - y, 0x26, 0x37 - y, -0x26, 0x3F - y, 0x26, 0x3F - y);
                setXY4(&poly[1], -0x28, 0x46 - y, 0x28, 0x46 - y, -0x28, 0x4E - y, 0x28, 0x4E - y);
                setXY4(&poly[2], -0x1A, 0x55 - y, 0x1A, 0x55 - y, -0x1A, 0x5D - y, 0x1A, 0x5D - y);
                setXY4(&poly[3], -0x20, 0x64 - y, 0x20, 0x64 - y, -0x20, 0x6C - y, 0x20, 0x6C - y);
                SetSemiTrans(&poly[0], 1);
                SetSemiTrans(&poly[1], 1);
                SetSemiTrans(&poly[2], 1);
                SetSemiTrans(&poly[3], 1);
                top1 = 0;
                work->fE0[0] = 0x100;
                work->fE0[1] = 0x100;
                work->fE0[2] = 0x100;
                work->fE0[3] = 0x100;
                work->fE0[4] = 0;
                work->fE0[5] = 0;
                if (work->fB14 < 4)
                {
                    bot1 = 0x80 - work->fB14 * 128 / 3;
                }
                else
                {
                    bot1 = 0;
                    work->fE0[0] = 0;
                }
                if (work->fB14 < 3)
                {
                    top2 = 0x80;
                }
                else
                {
                    top2 = 0x80 - (work->fB14 - 2) * 128 / 3;
                }
                bot2 = 0x80;
                top3 = bot2;
                if (work->fB14 < 4)
                {
                    bot3 = work->fB14 * 128 / 3;
                }
                else
                {
                    bot3 = 0x80;
                }
                if (work->fB14 < 3)
                {
                    bot4 = 0;
                    work->fE0[3] = 0;
                }
                else
                {
                    bot4 = (work->fB14 - 2) * 128 / 3;
                }
                title_open_800C4BD4(&poly[0], top1, bot1);
                title_open_800C4BD4(&poly[1], top2, bot2);
                title_open_800C4BD4(&poly[2], top3, bot3);
                title_open_800C4BD4(&poly[3], bot4, 0);
            }
        }
        break;

    case 3:
        if (work->fB14 == 5)
        {
            setXY4(&poly[2], -0x1A, 0x37, 0x1A, 0x37, -0x1A, 0x3F, 0x1A, 0x3F);
            setXY4(&poly[3], -0x20, 0x46, 0x20, 0x46, -0x20, 0x4E, 0x20, 0x4E);
            setXY4(&poly[4], -0x1E, 0x55, 0x1E, 0x55, -0x1E, 0x5D, 0x1E, 0x5D);
            title_open_800C4B94(&poly[2], 0, 0, 0, 0x80, 0xC0, 0x80);
            title_open_800C4B94(&poly[3], 0x80, 0xC0, 0x80, 0x80, 0xC0, 0x80);
            title_open_800C4B94(&poly[4], 0x80, 0xC0, 0x80, 0, 0, 0);
            SetSemiTrans(&poly[2], 1);
            SetSemiTrans(&poly[3], 0);
            SetSemiTrans(&poly[4], 1);
            work->fE0[0] = 0;
            work->fE0[1] = 0;
            work->fE0[2] = 0x100;
            work->fE0[3] = 0x100;
            work->fE0[4] = 0x100;
            work->fE0[5] = 0;
        }
        else
        {
            int y = work->fB14 * 3;

            if (work->fB18 == 0)
            {
                setXY4(&poly[2], -0x1A, y + 0x28, 0x1A, y + 0x28, -0x1A, y + 0x30, 0x1A, y + 0x30);
                setXY4(&poly[3], -0x20, y + 0x37, 0x20, y + 0x37, -0x20, y + 0x3F, 0x20, y + 0x3F);
                setXY4(&poly[4], -0x1E, y + 0x46, 0x1E, y + 0x46, -0x1E, y + 0x4E, 0x1E, y + 0x4E);
                setXY4(&poly[0], -0x26, y + 0x55, 0x26, y + 0x55, -0x26, y + 0x5D, 0x26, y + 0x5D);
                SetSemiTrans(&poly[2], 1);
                SetSemiTrans(&poly[3], 1);
                SetSemiTrans(&poly[4], 1);
                SetSemiTrans(&poly[0], 1);
                top1 = 0;
                work->fE0[0] = 0x100;
                work->fE0[5] = 0;
                work->fE0[1] = 0;
                work->fE0[2] = 0x100;
                work->fE0[3] = 0x100;
                work->fE0[4] = 0x100;
                if (work->fB14 < 3)
                {
                    bot1 = top1;
                    work->fE0[2] = 0;
                }
                else
                {
                    bot1 = (work->fB14 - 2) * 128 / 3;
                }
                if (work->fB14 < 4)
                {
                    top2 = work->fB14 * 128 / 3;
                }
                else
                {
                    top2 = 0x80;
                }
                bot2 = 0x80;
                top3 = bot2;
                if (work->fB14 < 3)
                {
                    bot3 = 0x80;
                }
                else
                {
                    bot3 = top3 - (work->fB14 - 2) * 128 / 3;
                }
                if (work->fB14 < 4)
                {
                    bot4 = 0x80 - work->fB14 * 128 / 3;
                }
                else
                {
                    bot4 = 0;
                    work->fE0[0] = 0;
                }
                title_open_800C4BD4(&poly[2], top1, bot1);
                title_open_800C4BD4(&poly[3], top2, bot2);
                title_open_800C4BD4(&poly[4], top3, bot3);
                title_open_800C4BD4(&poly[0], bot4, 0);
            }
            else
            {
                setXY4(&poly[1], -0x28, 0x37 - y, 0x28, 0x37 - y, -0x28, 0x3F - y, 0x28, 0x3F - y);
                setXY4(&poly[2], -0x1A, 0x46 - y, 0x1A, 0x46 - y, -0x1A, 0x4E - y, 0x1A, 0x4E - y);
                setXY4(&poly[3], -0x20, 0x55 - y, 0x20, 0x55 - y, -0x20, 0x5D - y, 0x20, 0x5D - y);
                setXY4(&poly[4], -0x1E, 0x64 - y, 0x1E, 0x64 - y, -0x1E, 0x6C - y, 0x1E, 0x6C - y);
                SetSemiTrans(&poly[1], 1);
                SetSemiTrans(&poly[2], 1);
                SetSemiTrans(&poly[3], 1);
                SetSemiTrans(&poly[4], 1);
                top1 = 0;
                work->fE0[0] = 0;
                work->fE0[1] = 0x100;
                work->fE0[2] = 0x100;
                work->fE0[3] = 0x100;
                work->fE0[4] = 0x100;
                work->fE0[5] = 0;
                if (work->fB14 < 4)
                {
                    bot1 = 0x80 - work->fB14 * 128 / 3;
                }
                else
                {
                    bot1 = 0;
                    work->fE0[1] = 0;
                }
                if (work->fB14 < 3)
                {
                    top2 = 0x80;
                }
                else
                {
                    top2 = 0x80 - (work->fB14 - 2) * 128 / 3;
                }
                bot2 = 0x80;
                top3 = bot2;
                if (work->fB14 < 4)
                {
                    bot3 = work->fB14 * 128 / 3;
                }
                else
                {
                    bot3 = 0x80;
                }
                if (work->fB14 < 3)
                {
                    bot4 = 0;
                    work->fE0[4] = 0;
                }
                else
                {
                    bot4 = (work->fB14 - 2) * 128 / 3;
                }
                title_open_800C4BD4(&poly[1], top1, bot1);
                title_open_800C4BD4(&poly[2], top2, bot2);
                title_open_800C4BD4(&poly[3], top3, bot3);
                title_open_800C4BD4(&poly[4], bot4, 0);
            }
        }
        break;

    case 4:
        if (work->fB14 == 5)
        {
            setXY4(&poly[3], -0x20, 0x37, 0x20, 0x37, -0x20, 0x3F, 0x20, 0x3F);
            setXY4(&poly[4], -0x1E, 0x46, 0x1E, 0x46, -0x1E, 0x4E, 0x1E, 0x4E);
            setXY4(&poly[0], -0x26, 0x55, 0x26, 0x55, -0x26, 0x5D, 0x26, 0x5D);
            title_open_800C4B94(&poly[3], 0, 0, 0, 0x80, 0xC0, 0x80);
            title_open_800C4B94(&poly[4], 0x80, 0xC0, 0x80, 0x80, 0xC0, 0x80);
            title_open_800C4B94(&poly[0], 0x80, 0xC0, 0x80, 0, 0, 0);
            SetSemiTrans(&poly[3], 1);
            SetSemiTrans(&poly[4], 0);
            SetSemiTrans(&poly[5], 1); /* sic: original bug, the visible row is poly[0] */
            work->fE0[0] = 0x100;
            work->fE0[5] = 0;
            work->fE0[1] = 0;
            work->fE0[2] = 0;
            work->fE0[3] = 0x100;
            work->fE0[4] = 0x100;
        }
        else
        {
            int y = work->fB14 * 3;

            if (work->fB18 == 0)
            {
                setXY4(&poly[3], -0x20, y + 0x28, 0x20, y + 0x28, -0x20, y + 0x30, 0x20, y + 0x30);
                setXY4(&poly[4], -0x1E, y + 0x37, 0x1E, y + 0x37, -0x1E, y + 0x3F, 0x1E, y + 0x3F);
                setXY4(&poly[0], -0x26, y + 0x46, 0x26, y + 0x46, -0x26, y + 0x4E, 0x26, y + 0x4E);
                setXY4(&poly[1], -0x28, y + 0x55, 0x28, y + 0x55, -0x28, y + 0x5D, 0x28, y + 0x5D);
                SetSemiTrans(&poly[3], 1);
                SetSemiTrans(&poly[4], 1);
                SetSemiTrans(&poly[5], 1); /* sic: original bug, rows are 3,4,0,1 */
                SetSemiTrans(&poly[0], 1);
                top1 = 0;
                work->fE0[0] = 0x100;
                work->fE0[1] = 0x100;
                work->fE0[2] = 0;
                work->fE0[3] = 0x100;
                work->fE0[4] = 0x100; /* sic: original never writes fE0[5] here */
                if (work->fB14 < 3)
                {
                    bot1 = top1;
                    work->fE0[3] = 0;
                }
                else
                {
                    bot1 = (work->fB14 - 2) * 128 / 3;
                }
                if (work->fB14 < 4)
                {
                    top2 = work->fB14 * 128 / 3;
                }
                else
                {
                    top2 = 0x80;
                }
                bot2 = 0x80;
                top3 = bot2;
                if (work->fB14 < 3)
                {
                    bot3 = 0x80;
                }
                else
                {
                    bot3 = top3 - (work->fB14 - 2) * 128 / 3;
                }
                if (work->fB14 < 4)
                {
                    bot4 = 0x80 - work->fB14 * 128 / 3;
                }
                else
                {
                    bot4 = 0;
                    work->fE0[1] = 0;
                }
                title_open_800C4BD4(&poly[3], top1, bot1);
                title_open_800C4BD4(&poly[4], top2, bot2);
                title_open_800C4BD4(&poly[0], top3, bot3);
                title_open_800C4BD4(&poly[1], bot4, 0);
            }
            else
            {
                setXY4(&poly[2], -0x1A, 0x37 - y, 0x1A, 0x37 - y, -0x1A, 0x3F - y, 0x1A, 0x3F - y);
                setXY4(&poly[3], -0x20, 0x46 - y, 0x20, 0x46 - y, -0x20, 0x4E - y, 0x20, 0x4E - y);
                setXY4(&poly[4], -0x1E, 0x55 - y, 0x1E, 0x55 - y, -0x1E, 0x5D - y, 0x1E, 0x5D - y);
                setXY4(&poly[0], -0x26, 0x64 - y, 0x26, 0x64 - y, -0x26, 0x6C - y, 0x26, 0x6C - y);
                SetSemiTrans(&poly[2], 1);
                SetSemiTrans(&poly[3], 1);
                SetSemiTrans(&poly[4], 1);
                SetSemiTrans(&poly[5], 1); /* sic: original bug, rows are 2,3,4,0 */
                top1 = 0;
                work->fE0[0] = 0x100;
                work->fE0[5] = 0;
                work->fE0[1] = 0;
                work->fE0[2] = 0x100;
                work->fE0[3] = 0x100;
                work->fE0[4] = 0x100;
                if (work->fB14 < 4)
                {
                    bot1 = 0x80 - work->fB14 * 128 / 3;
                }
                else
                {
                    bot1 = 0;
                    work->fE0[2] = 0;
                }
                if (work->fB14 < 3)
                {
                    top2 = 0x80;
                }
                else
                {
                    top2 = 0x80 - (work->fB14 - 2) * 128 / 3;
                }
                bot2 = 0x80;
                top3 = bot2;
                if (work->fB14 < 4)
                {
                    bot3 = work->fB14 * 128 / 3;
                }
                else
                {
                    bot3 = 0x80;
                }
                if (work->fB14 < 3)
                {
                    bot4 = 0;
                    work->fE0[0] = 0;
                }
                else
                {
                    bot4 = (work->fB14 - 2) * 128 / 3;
                }
                title_open_800C4BD4(&poly[2], top1, bot1);
                title_open_800C4BD4(&poly[3], top2, bot2);
                title_open_800C4BD4(&poly[4], top3, bot3);
                title_open_800C4BD4(&poly[0], bot4, 0);
            }
        }
        break;

    case 5:
        if (work->fB14 == 5)
        {
            setXY4(&poly[4], -0x1E, 0x37, 0x1E, 0x37, -0x1E, 0x3F, 0x1E, 0x3F);
            setXY4(&poly[5], -0x2C, 0x46, 0x2C, 0x46, -0x2C, 0x4E, 0x2C, 0x4E);
            setXY4(&poly[0], -0x26, 0x55, 0x26, 0x55, -0x26, 0x5D, 0x26, 0x5D);
            title_open_800C4B94(&poly[4], 0, 0, 0, 0x80, 0xC0, 0x80);
            title_open_800C4B94(&poly[5], 0x80, 0xC0, 0x80, 0x80, 0xC0, 0x80);
            title_open_800C4B94(&poly[0], 0x80, 0xC0, 0x80, 0, 0, 0);
            SetSemiTrans(&poly[4], 1);
            SetSemiTrans(&poly[5], 0);
            SetSemiTrans(&poly[0], 1);
            work->fE0[0] = 0x100;
            work->fE0[1] = 0;
            work->fE0[2] = 0;
            work->fE0[3] = 0;
            work->fE0[4] = 0x100;
            work->fE0[5] = 0x100;
        }
        else
        {
            int y = work->fB14 * 3;

            if (work->fB18 == 0)
            {
                setXY4(&poly[4], -0x1E, y + 0x28, 0x1E, y + 0x28, -0x1E, y + 0x30, 0x1E, y + 0x30);
                setXY4(&poly[5], -0x2C, y + 0x37, 0x2C, y + 0x37, -0x2C, y + 0x3F, 0x2C, y + 0x3F);
                setXY4(&poly[0], -0x26, y + 0x46, 0x26, y + 0x46, -0x26, y + 0x4E, 0x26, y + 0x4E);
                setXY4(&poly[1], -0x28, y + 0x55, 0x28, y + 0x55, -0x28, y + 0x5D, 0x28, y + 0x5D);
                SetSemiTrans(&poly[4], 1);
                SetSemiTrans(&poly[5], 1);
                SetSemiTrans(&poly[0], 1);
                SetSemiTrans(&poly[1], 1);
                top1 = 0;
                work->fE0[0] = 0x100;
                work->fE0[1] = 0x100;
                work->fE0[2] = 0;
                work->fE0[3] = 0;
                work->fE0[4] = 0x100;
                work->fE0[5] = 0x100;
                if (work->fB14 < 3)
                {
                    bot1 = top1;
                    work->fE0[4] = 0;
                }
                else
                {
                    bot1 = (work->fB14 - 2) * 128 / 3;
                }
                if (work->fB14 < 4)
                {
                    top2 = work->fB14 * 128 / 3;
                }
                else
                {
                    top2 = 0x80;
                }
                bot2 = 0x80;
                top3 = bot2;
                if (work->fB14 < 3)
                {
                    bot3 = 0x80;
                }
                else
                {
                    bot3 = top3 - (work->fB14 - 2) * 128 / 3;
                }
                if (work->fB14 < 4)
                {
                    bot4 = 0x80 - work->fB14 * 128 / 3;
                }
                else
                {
                    bot4 = 0;
                    work->fE0[1] = 0;
                }
                title_open_800C4BD4(&poly[4], top1, bot1);
                title_open_800C4BD4(&poly[5], top2, bot2);
                title_open_800C4BD4(&poly[0], top3, bot3);
                title_open_800C4BD4(&poly[1], bot4, 0);
            }
            else
            {
                setXY4(&poly[3], -0x20, 0x37 - y, 0x20, 0x37 - y, -0x20, 0x3F - y, 0x20, 0x3F - y);
                setXY4(&poly[4], -0x1E, 0x46 - y, 0x1E, 0x46 - y, -0x1E, 0x4E - y, 0x1E, 0x4E - y);
                setXY4(&poly[5], -0x2C, 0x55 - y, 0x2C, 0x55 - y, -0x2C, 0x5D - y, 0x2C, 0x5D - y);
                setXY4(&poly[0], -0x26, 0x64 - y, 0x26, 0x64 - y, -0x26, 0x6C - y, 0x26, 0x6C - y);
                SetSemiTrans(&poly[3], 1);
                SetSemiTrans(&poly[4], 1);
                SetSemiTrans(&poly[5], 1);
                SetSemiTrans(&poly[0], 1);
                top1 = 0;
                work->fE0[0] = 0x100;
                work->fE0[1] = 0;
                work->fE0[2] = 0;
                work->fE0[3] = 0x100;
                work->fE0[4] = 0x100;
                work->fE0[5] = 0x100;
                if (work->fB14 < 4)
                {
                    bot1 = 0x80 - work->fB14 * 128 / 3;
                }
                else
                {
                    bot1 = 0;
                    work->fE0[3] = 0;
                }
                if (work->fB14 < 3)
                {
                    top2 = 0x80;
                }
                else
                {
                    top2 = 0x80 - (work->fB14 - 2) * 128 / 3;
                }
                bot2 = 0x80;
                top3 = bot2;
                if (work->fB14 < 4)
                {
                    bot3 = work->fB14 * 128 / 3;
                }
                else
                {
                    bot3 = 0x80;
                }
                if (work->fB14 < 3)
                {
                    bot4 = 0;
                    work->fE0[0] = 0;
                }
                else
                {
                    bot4 = (work->fB14 - 2) * 128 / 3;
                }
                title_open_800C4BD4(&poly[3], top1, bot1);
                title_open_800C4BD4(&poly[4], top2, bot2);
                title_open_800C4BD4(&poly[5], top3, bot3);
                title_open_800C4BD4(&poly[0], bot4, 0);
            }
        }
        break;

    }

    work->fB14++;
}
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
extern const char title_aGamedatafind_800D8B98[];
extern const char title_aFlagx_800D8BA8[];
extern const char title_aFlagnewx_800D8BB4[];
extern const char title_aThisisrank_800D8BC4[];
extern const char title_aThisisrank_800D8BD4[];
extern const char title_aThisisrank_800D8BE4[];
extern const char title_aThisisrank_800D8BF4[];
extern const char title_aThisisrank_800D8C04[];
extern const char title_aThisisrank_800D8C14[];
extern const char title_aThisisrank_800D8C24[];
extern const char title_aPhotodatafind_800D8C34[];
extern const char title_aVrfind_800D8C48[];
extern const char title_aTitlememcardcheckreult_800D8C54[];
extern const char title_aSaveflagd_800D8C78[];
extern const char title_aPhotoflagd_800D8C88[];
extern const char title_aVrflagd_800D8C9C[];
extern const char title_aSperankd_800D8CAC[];
extern const char title_aDemorankd_800D8CBC[];

void title_open_800D1CB4(Work *work)
{
    MEM_CARD card1, card2;
    int      check1, check2;
    char    *name;
    int      found;
    int      photo, vr;
    int      i, j;
    int      mismatch;

    name = MGS_MemoryCardName;

    check1 = memcard_check(0);
    check2 = memcard_check(1);

    printf("check1 = %x\n", check1);
    printf("check2 = %x\n", check2);

    found = 0;
    photo = 0;
    vr = 0;

    if (check1 >= 0)
    {
        printf("this memcard is OK\n");

        card1 = *memcard_get_files(0);

        for (i = 0; i < card1.file_count; i++)
        {
                printf("name = %s\n", card1.files[i].name);
                title_open_800D1B74(card1.files[i].name);

                mismatch = 0;
                for (j = 0; j < 12; j++)
                {
                    if (card1.files[i].name[j] != name[j])
                    {
                        mismatch = 1;
                        break;
                    }
                }

                if (mismatch == 0)
                {
                    if (card1.files[i].name[12] == 'G')
                    {
                        unsigned char flag;
                        found = 1;
                        printf((char *)title_aGamedatafind_800D8B98);
                        flag = card1.files[i].name[17] - '@';
                        printf((char *)title_aFlagx_800D8BA8, flag);
                        flag &= 7;
                        printf((char *)title_aFlagnewx_800D8BB4, flag);
                        if (flag == 0)
                        {
                            printf((char *)title_aThisisrank_800D8BC4);
                        }
                        else if (flag == 1)
                        {
                            work->fB2C[0] = 1;
                            printf((char *)title_aThisisrank_800D8BD4);
                        }
                        else if (flag == 2)
                        {
                            work->fB2C[1] = 1;
                            printf((char *)title_aThisisrank_800D8BE4);
                        }
                        else if (flag == 3)
                        {
                            work->fB2C[0] = 1;
                            work->fB2C[1] = 1;
                            printf((char *)title_aThisisrank_800D8BF4);
                        }
                        else if (flag == 4)
                        {
                            work->fB2C[0] = 1;
                            work->fB2C[1] = 1;
                            work->fB2C[2] = 1;
                            printf((char *)title_aThisisrank_800D8C04);
                        }
                        else if (flag == 5)
                        {
                            work->fB2C[0] = 1;
                            work->fB2C[1] = 1;
                            work->fB2C[3] = 1;
                            printf((char *)title_aThisisrank_800D8C14);
                        }
                        else if (flag == 6)
                        {
                            work->fB2C[0] = 1;
                            work->fB2C[1] = 1;
                            work->fB2C[2] = 1;
                            work->fB2C[3] = 1;
                            printf((char *)title_aThisisrank_800D8C24);
                        }
                    }
                    else if (card1.files[i].name[12] == 'C')
                    {
                        photo = 1;
                        printf((char *)title_aPhotodatafind_800D8C34);
                    }
                    else if (card1.files[i].name[12] == 'V')
                    {
                        vr = 1;
                        printf((char *)title_aVrfind_800D8C48);
                    }
            }
        }
    }

    if (check2 >= 0)
    {
        printf("this memcard is OK\n");

        card2 = *memcard_get_files(1);

        for (i = 0; i < card2.file_count; i++)
        {
                printf("name = %s\n", card2.files[i].name);
                title_open_800D1B74(card2.files[i].name);

                mismatch = 0;
                for (j = 0; j < 12; j++)
                {
                    if (card2.files[i].name[j] != name[j])
                    {
                        mismatch = 1;
                        break;
                    }
                }

                if (mismatch == 0)
                {
                    if (card2.files[i].name[12] == 'G')
                    {
                        unsigned char flag;
                        found = 1;
                        printf((char *)title_aGamedatafind_800D8B98);
                        flag = card2.files[i].name[17] - '@';
                        printf((char *)title_aFlagx_800D8BA8, flag);
                        flag &= 7;
                        printf((char *)title_aFlagnewx_800D8BB4, flag);
                        if (flag == 0)
                        {
                            printf((char *)title_aThisisrank_800D8BC4);
                        }
                        else if (flag == 1)
                        {
                            work->fB2C[0] = 1;
                            printf((char *)title_aThisisrank_800D8BD4);
                        }
                        else if (flag == 2)
                        {
                            work->fB2C[1] = 1;
                            printf((char *)title_aThisisrank_800D8BE4);
                        }
                        else if (flag == 3)
                        {
                            work->fB2C[0] = 1;
                            work->fB2C[1] = 1;
                            printf((char *)title_aThisisrank_800D8BF4);
                        }
                        else if (flag == 4)
                        {
                            work->fB2C[0] = 1;
                            work->fB2C[1] = 1;
                            work->fB2C[2] = 1;
                            printf((char *)title_aThisisrank_800D8C04);
                        }
                        else if (flag == 5)
                        {
                            work->fB2C[0] = 1;
                            work->fB2C[1] = 1;
                            work->fB2C[3] = 1;
                            printf((char *)title_aThisisrank_800D8C14);
                        }
                        else if (flag == 6)
                        {
                            work->fB2C[0] = 1;
                            work->fB2C[1] = 1;
                            work->fB2C[2] = 1;
                            work->fB2C[3] = 1;
                            printf((char *)title_aThisisrank_800D8C24);
                        }
                    }
                    else if (card2.files[i].name[12] == 'C')
                    {
                        photo = 1;
                        printf((char *)title_aPhotodatafind_800D8C34);
                    }
                    else if (card2.files[i].name[12] == 'V')
                    {
                        vr = 1;
                        printf((char *)title_aVrfind_800D8C48);
                    }
            }
        }
    }

    if (found == 1)
    {
        work->fB20 = 1;
        if ((unsigned int)work->fB08 < 3)
        {
            work->fA78 = 1;
        }
    }

    if (photo == 1)
    {
        work->fB24 = 1;
    }
    if (vr == 1)
    {
        work->fB28 = 1;
    }

    if (work->fB2C[0] == 0)
    {
        if (work->fB2C[1] == 0)
        {
            work->fB48 = 0;
        }
        else
        {
            work->fB48 = 2;
        }
    }
    else if (work->fB2C[1] == 0)
    {
        work->fB48 = 1;
    }
    else if (work->fB2C[2] == 0)
    {
        if (work->fB2C[3] == 0)
        {
            work->fB48 = 3;
        }
        else
        {
            work->fB48 = 5;
        }
    }
    else
    {
        if (work->fB2C[3] == 0)
        {
            work->fB48 = 4;
        }
        else
        {
            work->fB48 = 6;
        }
    }

    if (work->fB24 == 0)
    {
        if (work->fB48 == 0)
        {
            work->fB40 = 0;
        }
        else
        {
            work->fB40 = 2;
        }
    }
    else
    {
        if (work->fB48 == 0)
        {
            work->fB40 = 1;
        }
        else
        {
            work->fB40 = 3;
        }
    }

    if (title_dword_800D92D0 == 1)
    {
        work->fB40 += 4;
    }

    printf((char *)title_aTitlememcardcheckreult_800D8C54);
    printf((char *)title_aSaveflagd_800D8C78, work->fB20);
    printf((char *)title_aPhotoflagd_800D8C88, work->fB24);
    printf((char *)title_aVrflagd_800D8C9C, work->fB28);
    printf((char *)title_aSperankd_800D8CAC, work->fB40);
    printf((char *)title_aDemorankd_800D8CBC, work->fB48);

    work->f24D0 = 1;
    work->f24D4 = 1;
}
/* Moved from openact.c to open.c so open.obj's rdata extends to 0x800D8CD0,
 * where gcc's auto-emitted switch table for 800D2374 lands. */
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

void title_open_800D2374(Work *work)
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


void title_open_800D2460(Work *work)
{
    char   result[8];
    char   result2[8];
    CdlLOC loc;
    char   param[8];
    int    press;
    int    status;
    int    intr;
    int    error;
    void  *alloc;

    press = work->pad->press;

    switch(work->f24AC)
    {
    case 0:
        param[0] = 0;
        CdControlB(CdlNop,param, result);

        if (result[0] & CdlStatShellOpen)
        {
            work->f24AC = 3;
            printf("CD CASE OPEN!!\n");
            mts_wait_vbl(3);
            break;
        }

        param[0] = 0;
        status = CdControlB(CdlSetmode, param, result);

        if (status == 0)
        {
            printf("CD NORMAL SPEED SET FAILED!!\n");
            work->f24C0++;
        }
        else if (status == 1)
        {
            work->f24AC = 1;
            printf("CD NORMAL SPEED SET SUCCESS!!\n");
            mts_wait_vbl(3);
            work->f24C0 = 0;
        }
        else
        {
            printf("???????\n");
        }

        if (work->f24C0 >= 300)
        {
            work->f24AC = 10;
            work->f24B8 = 0;
            printf("THIS IS NOT PS DISC!!\n");
        }
        break;
    case 1:
        param[0] = 0;
        CdControlB(CdlNop, param, result);

        if (result[0] & CdlStatShellOpen)
        {
            work->f24AC = 3;
            printf("CD CASE OPEN!!\n");
            mts_wait_vbl(3);
            break;
        }

        param[0] = 0;
        status = CdControlB(CdlStop, param, result);

        if (status == 0)
        {
            printf("CD STOP FAILED!!\n");
            work->f24C0++;
        }
        else if (status == 1)
        {
            work->f24AC = 2;
            printf("CD STOP SUCCESS!!\n");
            work->f24C0 = 0;
        }
        else
        {
            printf("???????\n");
        }

        if (work->f24C0 >= 300)
        {
            work->f24AC = 10;
            work->f24B8 = 0;
            printf("THIS IS NOT PS DISC!!\n");
        }
        break;
    case 2:
        param[0] = 0;
        CdControlB(CdlNop, param, result);

        if (!(result[0] & CdlStatShellOpen))
        {
            printf("CD CASE CLOSE!!\n");
        }
        else
        {
            work->f24AC = 3;
            printf("CD CASE OPEN!!\n");
        }
        break;
    case 3:
        param[0] = 0;
        CdControlB(CdlNop, param, result);

        if (!(result[0] & CdlStatShellOpen))
        {
            work->f24AC = 4;
            printf("CD CASE CLOSE!!\n");
        }
        else
        {
            printf("CD CASE OPEN!!\n");
        }
        break;
    case 4:
        if (work->f24EC != 0 && (press & PAD_START))
        {
            work->f24AC = 5;
            printf("START BUTTON PUSH!!\n");
            GM_SeSet2(0, 63, 32);
            work->f24C0 = 0;
        }
        break;
    case 5:
        param[0] = 0;
        CdControlB(CdlNop, param, result);
        work->f24C0++;

        if (result[0] & CdlStatStandby)
        {
            work->f24AC = 6;
            printf("CD SPIN START!!\n");
            work->f24C0 = 0;
        }
        else
        {
            printf("CD NOT SPIN!!\n");
        }

        if (work->f24C0 >= 300)
        {
            work->f24AC = 10;
            work->f24B8 = 0;
            printf("THIS IS NOT PS DISC!!\n");
        }
        break;
    case 6:
        param[0] = 0;
        status = CdControlB(CdlGetTN, param, result);

        if (status == 0)
        {
            printf("CD TOC READ NOT FINISH!!\n");
            work->f24C0++;
        }
        else if (status == 1)
        {
            work->f24AC = 7;
            printf("CD TOC READ SUCCESS!!\n");
            work->f24C0 = 0;
        }
        else
        {
            printf("???????\n");
        }

        if (work->f24C0 >= 300)
        {
            work->f24AC = 10;
            work->f24B8 = 0;
            printf("THIS IS NOT PS DISC!!\n");
        }
        break;
    case 7:
        param[0] = CdlModeSize1 | CdlModeSpeed;
        status = CdControlB(CdlSetmode, param, result);

        if (status == 0)
        {
            printf("CD SPEED INIT FAILED!!\n");
            work->f24C0++;
        }
        else if (status == 1)
        {
            work->f24AC = 8;
            work->f24C0 = 0;
            printf("CD SPEED INIT SUCCESS!!\n");
            mts_wait_vbl(3);
        }
        else
        {
            printf("???????\n");
        }

        if (work->f24C0 >= 300)
        {
            work->f24AC = 10;
            work->f24B8 = 0;
            printf("THIS IS NOT PS DISC!!\n");
        }
        break;
    case 8:
        CdIntToPos(16, &loc);
        status = CdControlB(CdlReadN, (char *)&loc, result);

        if (status == 0)
        {
            printf("CD CHECK FAILED!!\n");
            work->f24C0++;

            if (result[0] & CdlStatError && result[1] & CdlStatSeek)
            {
                work->f24AC = 10;
                work->f24B8 = 0;
                printf("THIS IS NOT PS DISC!!\n");
            }

            if (work->f24C0 >= 300)
            {
                work->f24AC = 10;
                work->f24B8 = 0;
                printf("THIS IS NOT PS DISC!!\n");
            }
        }
        else if (status == 1)
        {
            intr = CdReady(0, result2);
            error = 0;

            if (intr == CdlDataReady)
            {
                printf("CD CHECK OK!!\n");

                if (result[0] & CdlStatError && result[1] & CdlStatSeek)
                {
                    error = 1;
                    printf("THIS IS NOT PS DISC!!!\n");
                    work->f24AC = 10;
                    work->f24B8 = 0;
                }
            }
            else if (intr == CdlDiskError)
            {
                error = 1;
                printf("CD CHECK ERROR!!\n");
            }

            if (error)
            {
                break;
            }

            printf("THIS IS PS DISC!!\n");

            alloc = GV_Malloc(8192);
            status = FS_ResetCdFilePosition(alloc);

            if (status == 0)
            {
                printf("THIS IS DISC 1!!\n");
                work->f24AC = 9;
                FS_DiskNum = 0;
            }
            else
            {
                printf("THIS IS NOT DISC 1!!!\n");
                work->f24AC = 10;
                work->f24B8 = 0;
            }

            GV_Free(alloc);
        }
        else
        {
            printf("???????\n");
        }
        break;
    case 9:
        param[0] = 0;
        CdControlB(CdlPause, param, result);

        work->f24BC = 1;
        work->f24C4 = 1;
        printf("OK! OK!\n");
        break;
    case 10:
        work->f24B8++;
        printf("NOT OK! NOT OK!\n");

        if (work->f24B8 >= 30)
        {
            work->f24AC = 0;
        }
        break;
    }
}

void title_open_800D2A00(Work *work)
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
void title_open_800D2AFC(Work *work)
{
    GCL_ARGS args;
    long     argv[3];

    args.argc = 3;
    args.argv = argv;
    argv[0] = work->f24D0;
    if (work->f24BC) { work->f24B4++; }
    title_open_800D2374(work);
    title_open_800C47B8(work, DG_ChanlOTag(1));
    title_open_800D2460(work);
    if (work->f24EC == 0) { if (work->f24B0 >= 0xA0) { work->f24EC = 1; } }
    work->f24B0++;
    if (work->f24B4 >= 0x48)
    {
        switch (work->fB48)
        {
        case 1: argv[1] = 1; argv[2] = 0; break;
        case 2: argv[1] = 0; argv[2] = 0; break;
        case 3: case 4: case 5: case 6:
            switch (work->fB44)
            {
            case 0: argv[1] = 1; argv[2] = 0; break;
            case 1: argv[1] = 0; argv[2] = 0; break;
            case 2: argv[1] = 1; argv[2] = 1; break;
            case 3: argv[1] = 0; argv[2] = 1; break;
            }
            break;
        }
        GM_OptionFlag &= 0xF7FF;
        GCL_ExecProc(work->fAF4, &args);
        GV_DestroyActor(work);
    }
}

/* ==== merged from openact.c (single TU; resolves cross-object jump tables) ==== */

extern void  title_open_800C5644(Work *work, int index);
extern void  title_open_800C5CB8(Work *work);
extern void  title_open_800C5CF0(Work *work);
extern void  title_open_800C5D10(Work *work);
extern void  title_open_800C53E0(Work *work);
extern int   title_open_800C628C(Work *work);
extern void  title_open_800CCDC8(Work *work);
extern void  title_open_800CD074(Work *work);
extern void  title_open_800CD23C(Work *work, int index, int arg3);
extern void  title_open_800CD320(Work *work, int index);
extern void  title_open_800CD3B8(Work *work, int index);
extern void  title_open_800CD800(Work *work, int index);
extern void  title_open_800CDE44(Work *work, int index);
extern void  title_open_800CE378(Work *work, int index);
extern void  title_open_800CE4A8(Work *work, int index);
extern void  title_open_800CE544(Work *work, int index);
extern void  title_open_800CE5F8(Work *work, int index);
extern void  title_open_800CE6AC(Work *work, int index);
extern void  title_open_800CE748(Work *work, int index);
extern void  title_open_800CEB14(Work *work, int index);
extern void  title_open_800CEF54(Work *work, int index);
extern void  title_open_800CF504(Work *work, int index);
extern void  title_open_800CF610(Work *work, int index);
extern void  title_open_800CF794(Work *work);
extern void  title_open_800D1CB4(Work *work);
extern void  title_open_800D2A00(Work *work);
extern void  title_open_800D2AFC(Work *work);
extern void  title_open_800D2CA8(Work *work, u_long *ot);
extern void  title_open_800D2E44(Work *work, u_long *ot);
extern void  title_open_800D3500(Work *work, u_long *ot);
extern void  title_open_800C4AD0(Work *work, int index, int color);
extern void  title_open_800C47B8(Work *work, u_long *ot);
extern void  title_open_800C4F1C(Work *work, int x0, int y0, int xsize, int ysize, int color, int mode);

/* The strings that previously lived at 0x800D8848..0x800D9024 in overlay3.c
 * are moved here so openact.obj's rdata fills the gap up to 0x800D9028,
 * where gcc's emitted switch jump tables for OpenAct's switch then land. */

const char title_dword_800D8F2C[] = {0x0, 0x0, 0x0, 0x0};
void title_open_800D2CA8(Work *work, u_long *ot)
{
    int i;

    for (i = 0; i < 24; i++)
    {
        title_open_800C4AD0(work, i, 0);
    }

    switch (work->fB3C)
    {
    case 1: title_open_800C4AD0(work, 6, 0x6739); break;
    case 2: title_open_800C4AD0(work, 7, 0x6739); break;
    case 3: title_open_800C4AD0(work, 8, 0x6739); break;
    case 6: title_open_800C4AD0(work, 0xE, 0x6739); break;
    case 5:
        title_open_800C4AD0(work, 9, 0x6739);
        title_open_800C4AD0(work, 0xA, 0x6739);
        if (work->f24CC == 0) { title_open_800C4AD0(work, 0xB, 0x6739); }
        else                  { title_open_800C4AD0(work, 0xC, 0x6739); }
        break;
    case 7: title_open_800C4AD0(work, 0xD, 0x6739); break;
    case 4:
        if (work->fB48 >= 3 && work->fB48 < 7)
        {
            switch (work->fB44)
            {
            case 1: title_open_800C4AD0(work, 0xF, 0x654A); break;
            case 2: title_open_800C4AD0(work, 0x10, 0x2959); break;
            case 3: title_open_800C4AD0(work, 0x11, 0x2959); break;
            case 4: title_open_800C4AD0(work, 0x12, 0x6739); break;
            case 0: break;
            }
        }
        break;
    case 0: break;
    case 8: break;
    }

    title_open_800C47B8(work, ot);
}
void title_open_800D2E44(Work *work, u_long *ot)
{
    if (title_dword_800D92D0)
    {
        GCL_ExecProc(work->f24FC, 0);
    }

    title_open_800C4AD0(work, 0xF, 0);
    title_open_800C4AD0(work, 0x10, 0);
    title_open_800C4AD0(work, 0x11, 0);

    switch (work->f24E4 + 1)
    {
    case 0:
        MENU_Locate(0x7C, 0x3C, 0x10); MENU_Color(0xC0, 0xC0, 0xC0); MENU_Printf("VERY EASY");
        MENU_Locate(0x90, 0x56, 0x10); MENU_Color(0x64, 0xA0, 0x87); MENU_Printf("EASY");
        MENU_Locate(0x88, 0x70, 0x10); MENU_Color(0x64, 0xA0, 0x87); MENU_Printf("NORMAL");
        MENU_Locate(0x90, 0x8A, 0x10); MENU_Color(0x64, 0xA0, 0x87); MENU_Printf("HARD");
        MENU_Locate(0x84, 0xA4, 0x10);
        if (work->fB48) { MENU_Color(0x64, 0xA0, 0x87); } else { MENU_Color(0x40, 0x40, 0x40); }
        MENU_Printf("EXTREME");
        title_open_800C4F1C(work, -0x28, -0x36, 0x52, 9, 0xFF, 1);
        title_open_800C4AD0(work, 0xF, 0x6739);
        title_open_800C4AD0(work, 4, 0);
        break;
    case 1:
        MENU_Locate(0x7C, 0x3C, 0x10); MENU_Color(0x64, 0xA0, 0x87); MENU_Printf("VERY EASY");
        MENU_Locate(0x90, 0x56, 0x10); MENU_Color(0xC0, 0xC0, 0xC0); MENU_Printf("EASY");
        MENU_Locate(0x88, 0x70, 0x10); MENU_Color(0x64, 0xA0, 0x87); MENU_Printf("NORMAL");
        MENU_Locate(0x90, 0x8A, 0x10); MENU_Color(0x64, 0xA0, 0x87); MENU_Printf("HARD");
        MENU_Locate(0x84, 0xA4, 0x10);
        if (work->fB48) { MENU_Color(0x64, 0xA0, 0x87); } else { MENU_Color(0x40, 0x40, 0x40); }
        MENU_Printf("EXTREME");
        title_open_800C4F1C(work, -0x14, -0x1C, 0x2A, 9, 0xFF, 1);
        title_open_800C4AD0(work, 0x10, 0x6739);
        title_open_800C4AD0(work, 4, 0);
        break;
    case 2:
        MENU_Locate(0x7C, 0x3C, 0x10); MENU_Color(0x64, 0xA0, 0x87); MENU_Printf("VERY EASY");
        MENU_Locate(0x90, 0x56, 0x10); MENU_Color(0x64, 0xA0, 0x87); MENU_Printf("EASY");
        MENU_Locate(0x88, 0x70, 0x10); MENU_Color(0xC0, 0xC0, 0xC0); MENU_Printf("NORMAL");
        MENU_Locate(0x90, 0x8A, 0x10); MENU_Color(0x64, 0xA0, 0x87); MENU_Printf("HARD");
        MENU_Locate(0x84, 0xA4, 0x10);
        if (work->fB48) { MENU_Color(0x64, 0xA0, 0x87); } else { MENU_Color(0x40, 0x40, 0x40); }
        MENU_Printf("EXTREME");
        title_open_800C4F1C(work, -0x1C, -0x02, 0x3A, 9, 0xFF, 1);
        title_open_800C4AD0(work, 4, 0);
        title_open_800C4AD0(work, 0x11, 0x6739);
        break;
    case 3:
        MENU_Locate(0x7C, 0x3C, 0x10); MENU_Color(0x64, 0xA0, 0x87); MENU_Printf("VERY EASY");
        MENU_Locate(0x90, 0x56, 0x10); MENU_Color(0x64, 0xA0, 0x87); MENU_Printf("EASY");
        MENU_Locate(0x88, 0x70, 0x10); MENU_Color(0x64, 0xA0, 0x87); MENU_Printf("NORMAL");
        MENU_Locate(0x90, 0x8A, 0x10); MENU_Color(0xC0, 0xC0, 0xC0); MENU_Printf("HARD");
        MENU_Locate(0x84, 0xA4, 0x10);
        if (work->fB48) { MENU_Color(0x64, 0xA0, 0x87); } else { MENU_Color(0x40, 0x40, 0x40); }
        MENU_Printf("EXTREME");
        title_open_800C4F1C(work, -0x14, 0x18, 0x2A, 9, 0xFF, 1);
        title_open_800C4AD0(work, 4, 0x6739);
        break;
    case 4:
        MENU_Locate(0x7C, 0x3C, 0x10); MENU_Color(0x64, 0xA0, 0x87); MENU_Printf("VERY EASY");
        MENU_Locate(0x90, 0x56, 0x10); MENU_Color(0x64, 0xA0, 0x87); MENU_Printf("EASY");
        MENU_Locate(0x88, 0x70, 0x10); MENU_Color(0x64, 0xA0, 0x87); MENU_Printf("NORMAL");
        MENU_Locate(0x90, 0x8A, 0x10); MENU_Color(0x64, 0xA0, 0x87); MENU_Printf("HARD");
        MENU_Locate(0x84, 0xA4, 0x10); MENU_Color(0xC0, 0xC0, 0xC0); MENU_Printf("EXTREME");
        title_open_800C4F1C(work, -0x20, 0x32, 0x46, 9, 0xFF, 1);
        title_open_800C4AD0(work, 4, 0x6739);
        break;
    }

    title_open_800C47B8(work, ot);
}

void title_open_800D3500(Work *work, u_long *ot)
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
        MENU_Printf("MEMORY CARD SLOT 1  :  ");

        if (work->f24F0 == 3)
        {
            MENU_Locate(223, 60, 0x10);
            MENU_Color(181, 85, 42);
            MENU_Printf("   FULL");
        }
        else
        {
            MENU_Locate(223, 60, 0x10);
            MENU_Color(181, 85, 42);
            MENU_Printf("NO CARD");
        }

        MENU_Locate(54, 75, 0x10);
        MENU_Color(100, 160, 135);
        MENU_Printf("MEMORY CARD SLOT 2  :  ");

        if (work->f24F4 == 3)
        {
            MENU_Locate(223, 75, 0x10);
            MENU_Color(181, 85, 42);
            MENU_Printf("   FULL");
        }
        else
        {
            MENU_Locate(223, 75, 0x10);
            MENU_Color(181, 85, 42);
            MENU_Printf("NO CARD");
        }

        MENU_Locate(70, 100, 0x10);
        MENU_Color(100, 160, 135);
        MENU_Printf("DO YOU WANT TO CONTINUE\n");

        MENU_Locate(85, 115, 0x10);
        MENU_Color(100, 160, 135);
        MENU_Printf("YOUR GAME LIKE THIS?");

        if (work->f24E0 == 0)
        {
            MENU_Locate(100, 150, 0x10);
            MENU_Color(192, 192, 192);
            MENU_Printf("YES");

            MENU_Locate(200, 150, 0x10);
            MENU_Color(46, 72, 61);
            MENU_Printf("NO");

            title_open_800C4F1C(work, -68, 33, 40, 15, 255, 1);
        }
        else
        {
            MENU_Locate(100, 150, 0x10);
            MENU_Color(46, 72, 61);
            MENU_Printf("YES");

            MENU_Locate(200, 150, 0x10);
            MENU_Color(192, 192, 192);
            MENU_Printf("NO");

            title_open_800C4F1C(work, 28, 33, 40, 15, 255, 1);
        }
    }

    title_open_800C47B8(work, ot);
}

/* Top-level title-screen state machine. Dispatches on work->fA74; each case
 * runs its one-time init when work->fB0C is set, then renders this frame. */
static void Act(Work *work)
{
    u_long   *ot;
    POLY_FT4 *packs;

    ot = DG_ChanlOTag(1);
    packs = work->f18C_polys;

    title_open_800C628C(work);

    if (work->f24D4 == 0)
    {
        title_open_800D1CB4(work);
    }

    switch (work->fA74)
    {
    case 4:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            work->fB0C = 0;

            work->f30[0] = 1792;
            work->f30[1] = 1792;
            work->f30[2] = 1792;
            work->f30[3] = 1536;
            work->f30[4] = 1280;
            work->f30[5] = 1280;
            work->f30[6] = 1280;
            work->f30[7] = 256;

            GM_SetSound(0x1000001, 0);
        }

        title_open_800CD3B8(work, 0);
        title_open_800CD800(work, 3);
        title_open_800CDE44(work, 4);
        title_open_800CE378(work, 7);

        work->f164++;
        work->f168++;
        work->f16C++;
        work->f170++;
        work->f178++;
        work->f17C++;
        work->f180++;
        work->f184++;
        work->f188++;

        if (work->f164 >= 192)
        {
            work->fA74 = 5;
            work->fB0C = 1;
        }
        break;

    case 5:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            work->fB0C = 0;

            work->f30[0] = 1792;
            work->f30[1] = 1792;
            work->f30[2] = 1792;
            work->f30[3] = 1536;
            work->f30[4] = 1280;
            work->f30[5] = 1280;
            work->f30[6] = 1280;
            work->f30[7] = 256;
            work->f30[8] = 256;
            work->f30[9] = 768;
            work->f30[10] = 512;
            work->f30[11] = 1024;
            work->f30[12] = 256;
        }

        title_open_800CCDC8(work);
        title_open_800CD074(work);
        title_open_800CE748(work, 0);
        title_open_800CEB14(work, 3);
        title_open_800CEF54(work, 4);
        title_open_800CE378(work, 7);
        title_open_800CE4A8(work, 8);
        title_open_800CE544(work, 9);
        title_open_800CE5F8(work, 12);
        title_open_800CE6AC(work, 11);

        work->f164++;
        work->f168++;
        work->f16C++;
        work->f170++;
        work->f174++;
        work->f178++;
        work->f17C++;
        work->f180++;
        work->f184++;
        work->f188++;

        if (work->f164 > 407)
        {
            work->fA74 = 6;
            work->fA98 = 2;
            work->f184 = 0;
            work->fB0C = 1;
        }
        break;

    case 6:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            work->fB0C = 0;

            work->f30[0] = 1792;
            work->f30[1] = 1792;
            work->f30[2] = 1792;
            work->f30[3] = 1536;
            work->f30[4] = 1280;
            work->f30[5] = 1280;
            work->f30[6] = 1280;
            work->f30[7] = 256;
            work->f30[8] = 256;
            work->f30[9] = 768;
            work->f30[10] = 512;
            work->f30[11] = 1024;
            work->f30[12] = 256;

            setRGB0(&packs[7], 128, 128, 128);
            setRGB0(&packs[8], 128, 128, 128);
            setRGB0(&packs[9], 128, 128, 128);
            setRGB0(&packs[10], 128, 128, 128);
            setRGB0(&packs[11], 128, 128, 128);
            setRGB0(&packs[12], 128, 128, 128);

            if (work->fA7C == 0)
            {
                work->fA7C = 1;
            }

            if (work->fA80 == 0)
            {
                work->fA80 = 1;
                work->f170 = 0;
            }

            if (work->fA84 == 0)
            {
                work->fA84 = 1;
                work->f170 = 0;
            }

            work->fA98 = 2;
            work->f184 = 0;
            work->fB00 = 0;

            GM_SetSound(0x1000001, 0);
        }

        title_open_800CCDC8(work);
        title_open_800CD074(work);
        title_open_800CE748(work, 0);
        title_open_800CEB14(work, 3);
        title_open_800CEF54(work, 4);
        title_open_800CF504(work, 12);
        title_open_800C5644(work, 10);

        work->f164++;
        work->f168++;
        work->f16C++;
        work->f170++;
        work->f174++;
        work->f184++;
        break;

    case 7:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            work->fB0C = 0;

            work->f30[0] = 1792;
            work->f30[1] = 1792;
            work->f30[2] = 1792;
            work->f30[3] = 1536;
            work->f30[4] = 1280;
            work->f30[5] = 1280;
            work->f30[6] = 1280;
            work->f30[7] = 256;
            work->f30[8] = 256;
            work->f30[9] = 768;
            work->f30[10] = 512;
            work->f30[11] = 1024;

            if (!sd_sng_play())
            {
                GM_SetSound(0x1000001, 0);
            }

            switch (work->fA78)
            {
            case 0:
                work->fE0[0] = 256;
                work->fE0[1] = 256;
                work->fE0[2] = 0;
                work->fE0[3] = 0;
                work->fE0[4] = 256;
                work->fE0[5] = 0;
                break;

            case 1:
                work->fE0[0] = 256;
                work->fE0[1] = 256;
                work->fE0[2] = 256;
                work->fE0[3] = 0;
                work->fE0[4] = 0;
                work->fE0[5] = 0;
                break;

            case 2:
                work->fE0[0] = 0;
                work->fE0[1] = 256;
                work->fE0[2] = 256;
                work->fE0[3] = 256;
                work->fE0[4] = 0;
                work->fE0[5] = 0;
                break;

            case 3:
                work->fE0[0] = 0;
                work->fE0[1] = 0;
                work->fE0[2] = 256;
                work->fE0[3] = 256;
                work->fE0[4] = 256;
                work->fE0[5] = 0;
                break;

            case 4:
                work->fE0[0] = 256;
                work->fE0[1] = 0;
                work->fE0[2] = 0;
                work->fE0[3] = 256;
                work->fE0[4] = 256;
                work->fE0[5] = 0;
                break;

            case 5:
                work->fE0[0] = 256;
                work->fE0[1] = 0;
                work->fE0[2] = 0;
                work->fE0[3] = 0;
                work->fE0[4] = 256;
                work->fE0[5] = 256;
            }
        }

        title_open_800CCDC8(work);
        title_open_800CD074(work);
        title_open_800CE748(work, 0);
        title_open_800CEB14(work, 3);
        title_open_800CEF54(work, 4);

        switch (work->fA78)
        {
        case 0:
            title_open_800CF610(work, 0);
            break;

        case 1:
            title_open_800CF610(work, 1);
            break;

        case 2:
            title_open_800CF610(work, 2);
            break;

        case 3:
            title_open_800CF610(work, 3);
            break;

        case 4:
            title_open_800CF610(work, 4);
            break;

        case 5:
            title_open_800CF610(work, 5);
            break;
        }

        title_open_800C5644(work, 10);
        title_open_800CF794(work);

        work->f164++;
        work->f168++;
        work->f16C++;
        work->f170++;
        work->f174++;
        work->f184++;
        break;

    case 9:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            title_open_800C5CF0(work);
            title_open_800C5D10(work);

            work->fB0C = 0;
            work->f24C4 = 0;
            work->mg_logo = NewMetalGearLogo(&work->f24C4);
        }

        title_open_800D2A00(work);
        break;

    case 16:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            title_open_800C5CF0(work);
            title_open_800C5D10(work);

            work->fB0C = 0;
            work->f24C4 = 0;
            work->mg_logo = NewMetalGearLogo(&work->f24C4);
        }

        title_open_800D2AFC(work);
        break;

    case 13:
        work->fB00 = 0;
        title_open_800D2CA8(work, ot);
        break;

    case 18:
    case 19:
        work->fB00 = 0;
        title_open_800D3500(work, ot);
        break;

    case 21:
        work->fB00 = 0;
        title_open_800D2E44(work, ot);
        break;

    case 0:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            title_open_800C5CF0(work);
            work->fB0C = 0;
            work->f30[18] = 256;
            work->f30[19] = 256;
        }

        title_open_800CD23C(work, 18, 1);
        work->f164++;
        break;

    case 1:
        if (work->fB0C != 0)
        {
            title_open_800C5CB8(work);
            work->fB0C = 0;
            work->f30[20] = 256;
            work->f30[21] = 256;
        }

        title_open_800CD23C(work, 20, 15);
        work->fB00 = 0;
        work->f164++;
        break;

    case 2:
        title_open_800CD320(work, 18);
        work->fB00 = 0;
        work->f164++;
        break;

    case 3:
        title_open_800CD320(work, 20);
        work->fB00 = 0;
        work->f164++;
        break;
    }

    title_open_800C53E0(work);
}

/* Actor destructor: frees the four DG primitives and each font character
 * block's backing buffer. */
static void Die(Work *work)
{
    int      i;
    void    *buf;

    GM_FreePrim(work->prim[0]);
    GM_FreePrim(work->prim[2]);
    GM_FreePrim(work->prim[3]);
    GM_FreePrim(work->prim[1]);

    for (i = 0; i < 24; i++)
    {
        buf = title_open_800C4B20(&work->kcb[i]);
        GV_FreeMemory(GV_NORMAL_MEMORY, buf);
    }
}

/* Build a flat-shaded textured quad at neutral brightness (128,128,128 = no
 * tint) with the given vertex rectangle and semi-transparency mode. UV/tpage
 * are filled in later by the caller (typically via the helper below). */
void title_open_800D4174(Work *work, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe)
{
    setPolyFT4(poly);
    setRGB0(poly, 128, 128, 128);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);
}

/* Bind tex to poly's UV/tpage/clut. uo/vo (0 or 1) extend the U/V range past
 * the texture's nominal w/h to compensate for PS1's UV truncation when the
 * sampler clips on the right/bottom edge. */
static inline void title_open_helper_800D41E4(POLY_FT4 *poly, DG_TEX *tex, int uo, int vo)
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

void title_open_800D41E4(Work *work, int name, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe, int type)
{
    DG_TEX *tex;

    title_open_800D4174(work, poly, x0, y0, x1, y1, abe);

    tex = DG_GetTexture(name);
    if (type == 0)
    {
        title_open_helper_800D41E4(poly, tex, 1, 1);
    }
    else if (type == 1)
    {
        title_open_helper_800D41E4(poly, tex, 1, 0);
    }
    else if (type == 2)
    {
        title_open_helper_800D41E4(poly, tex, 0, 1);
    }
    else if (type == 3)
    {
        title_open_helper_800D41E4(poly, tex, 0, 0);
    }
}

/* Like title_open_800D41E4 but with RGB0 set to (0,0,0). On a textured poly
 * an all-zero RGB darkens the texture to black — used as a fade overlay. */
void title_open_800D4368(Work *work, int name, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe)
{
    DG_TEX *tex;
    int     u0, u1;
    int     v0, v1;

    tex = DG_GetTexture(name);

    setPolyFT4(poly);

    u0 = tex->off_x;
    u1 = u0 + tex->w + 1;
    v0 = tex->off_y;
    v1 = v0 + tex->h + 1;
    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;

    setRGB0(poly, 0, 0, 0);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);
}

/* Gouraud variant of title_open_800D4368: same black-tint textured quad but
 * as POLY_GT4, so the per-vertex colors can be ramped later for a gradient. */
void title_open_800D4464(Work *work, int name, POLY_GT4 *poly, int x0, int y0, int x1, int y1, int abe)
{
    DG_TEX *tex;
    int     u0, u1;
    int     v0, v1;

    tex = DG_GetTexture(name);

    setPolyGT4(poly);

    u0 = tex->off_x;
    u1 = u0 + tex->w + 1;
    v0 = tex->off_y;
    v1 = v0 + tex->h + 1;
    setUV4(poly, u0, v0, u1, v0, u0, v1, u1, v1);

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;

    setRGB0(poly, 0, 0, 0);
    setRGB1(poly, 0, 0, 0);
    setRGB2(poly, 0, 0, 0);
    setRGB3(poly, 0, 0, 0);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);
}

static int GetResources(Work *work, int where)
{
    POLY_FT4 *poly;
    POLY_GT4 *gpoly;
    POLY_GT4 *gp;
    DG_TEX   *tex;
    int       n;

    GM_CurrentMap = where;

    work->f2498 = 0x340;
    work->f249C = 0x100;
    work->f24A0 = 0x340;
    work->f24A4 = 0x114;

    work->prim[0] = GM_MakePrim(0x812, 0x16, 0, 0);
    work->prim[2] = GM_MakePrim(0x812, 0x12, 0, 0);
    work->prim[3] = GM_MakePrim(0x812, 9, 0, 0);

    n = 0;

    gpoly = &work->f934_polys[0];
    gp = &work->f934_polys[0];

    poly = &work->f18C_polys[0];
    title_open_800D4368(work, GV_StrCode("op_back_l"), poly, -0xA0, -0x70, 0, 0x70, 0);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_back_r"), poly, 0, -0x70, 0xA0, 0x70, 0);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_back_l"), poly, 0xA0, -0x70, 0x140, 0x70, 0);
    work->f30[n++] = 0;

    poly++;
    tex = DG_GetTexture(GV_StrCode("op_back_l"));
    setPolyFT4(poly);
    title_open_800C5238(poly, tex, 6, 0x140, 0x1F4);
    setRGB0(poly, 0, 0, 0);
    setXY4(poly, -0xA0, -0x70, 0xA0, -0x70, -0xA0, 0x184, 0xA0, 0x184);
    SetSemiTrans(poly, 1);
    title_open_800C5200(poly, 2);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_back_l"), poly, -0xA0, -0x70, 0xA0, 0x70, 1);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_back_r"), poly, -0xA0, -0x70, 0xA0, 0x70, 1);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_back_l"), poly, -0xA0, -0x70, 0xA0, 0x70, 1);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_title"), poly, -0x70, -0x66, 0x76, -0x2A, 1);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_copy"), poly, -0x58, 0x60, 0x58, 0x67, 0);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_snake_cut"), poly, -0x3A, -0x4C, 0x3A, 0x69, 1);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_eye_open"), poly, -0x1E, 3, 0x14, 0xF, 1);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_snake_waku"), poly, -0x4E, -0x63, 0x4E, 0x73, 1);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_p_start"), poly, -0x50, 0x46, 0x50, 0x4E, 0);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_n_game"), poly, -0x26, 0x46, -0x28, 0x4E, 0);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_l_game"), poly, -0x26, 0x46, -0x28, 0x4E, 0);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_option"), poly, -0x1A, 0x46, -0x20, 0x4E, 0);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_sellevel"), poly, -0x56, -0x55, 0x56, -0x49, 1);
    setRGB0(poly, 0x64, 0xA0, 0x87);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_warning"), poly, -0x26, 0x46, -0x28, 0x4E, 0);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_konami_l"), poly, -0xA0, -0x70, 0, 0x70, 0);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_konami_r"), poly, 0, -0x70, 0xA0, 0x70, 0);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_kcej_l"), poly, -0xA0, -0x70, 0, 0x70, 0);
    work->f30[n++] = 0;

    poly++;
    title_open_800D4368(work, GV_StrCode("op_kcej_r"), poly, 0, -0x70, 0xA0, 0x70, 0);
    work->f30[n++] = 0;

    n = 0;

    poly += 19;
    title_open_800D41E4(work, GV_StrCode("cur_lu"), poly, 0, 0, 0, 0, 1, 0);
    work->f140[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode("cur_ru"), poly, 0, 0, 0, 0, n, 0);
    work->f140[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode("cur_ld"), poly, 0, 0, 0, 0, 1, 0);
    work->f140[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode("cur_rd"), poly, 0, 0, 0, 0, 1, 0);
    work->f140[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode("cur_u"), poly, 0, 0, 0, 0, 1, 2);
    work->f140[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode("cur_d"), poly, 0, 0, 0, 0, 1, 2);
    work->f140[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode("cur_l"), poly, 0, 0, 0, 0, 1, 1);
    work->f140[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode("cur_r"), poly, 0, 0, 0, 0, 1, 1);
    work->f140[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode("cur_c"), poly, 0, 0, 0, 0, 1, 3);
    work->f140[n] = 0;

    n = 0;

    poly = &work->f4FC_polys[0];
    title_open_800D41E4(work, GV_StrCode("sp_back_l"), poly, -0xA0, -0x70, 0, 0x70, 0, 0);
    setRGB0(poly, 0x80, 0x80, 0x80);
    work->fF8[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode("sp_back_r"), poly, 0, -0x70, 0xA0, 0x70, 0, 0);
    setRGB0(poly, 0x80, 0x80, 0x80);
    work->fF8[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode("sp_special"), poly, -0x32, -0x5E, 0x32, -0x51, 1, 0);
    setRGB0(poly, 0x46, 0x64, 0x5A);
    work->fF8[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode("sp_special"), poly, -0x32, -0x5E, 0x32, -0x51, 1, 0);
    setRGB0(poly, 0x46, 0x64, 0x5A);
    work->fF8[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode(title_aSppre_800D8880), poly, -0x50, -0x35, 0x50, -0x2D, 1, 2);
    setRGB0(poly, 0x64, 0xA0, 0x87);
    work->fF8[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode(title_aSpexit_800D8888), poly, -0x1C, 0x2E, 0x1C, 0x3A, 1, 2);
    setRGB0(poly, 0x64, 0xA0, 0x87);
    work->fF8[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode(title_aSpalbum_800D8890), poly, -0x18, -0x21, 0x18, -0x19, 1, 2);
    setRGB0(poly, 0x64, 0xA0, 0x87);
    work->fF8[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode(title_aSpdemo_800D889C), poly, -0x34, -0xD, 0x34, -5, 1, 2);
    setRGB0(poly, 0x64, 0xA0, 0x87);
    work->fF8[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode("sp_radar"), poly, -0x2A, 0xB, 0x2A, 0x17, 1, 2);
    setRGB0(poly, 0x64, 0xA0, 0x87);
    work->fF8[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode(title_aSponw_800D88B8), poly, -0x6D, 0xB, -0x45, 0x17, 1, 0);
    setRGB0(poly, 0x64, 0xA0, 0x87);
    work->fF8[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode(title_aSpoff_800D88C0), poly, 0x38, 0xB, 0x68, 0x17, 1, 0);
    setRGB0(poly, 0x46, 0x64, 0x5A);
    work->fF8[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode("sp_line"), poly, -0x45, 0x10, -0x2A, 0x12, 1, 2);
    setRGB0(poly, 0x64, 0xA0, 0x87);
    work->fF8[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode("demo_demo"), poly, -0x38, -0x5E, 0x38, -0x52, 1, 0);
    setRGB0(poly, 0x64, 0xA0, 0x87);
    work->fF8[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode("demo_ra"), poly, -0x1C, -0x2A, 0x1C, -0x24, 1, 0);
    setRGB0(poly, 0x64, 0xA0, 0x87);
    work->fF8[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode("demo_rb"), poly, -0x1C, 1, 0x1C, 7, 1, 0);
    setRGB0(poly, 0x64, 0xA0, 0x87);
    work->fF8[n] = 0;

    poly++;
    n++;
    title_open_800D41E4(work, GV_StrCode("demo_roll_c"), poly, -0x1C, 4, 0x1C, 0xA, 1, 0);
    setRGB0(poly, 0x64, 0xA0, 0x87);
    work->fF8[15] = 0;

    poly++;
    title_open_800D41E4(work, GV_StrCode("demo_roll_d"), poly, -0x1C, 4, 0x1C, 0xA, 1, 0);
    setRGB0(poly, 0x64, 0xA0, 0x87);
    work->fF8[16] = 0;

    poly++;
    title_open_800D41E4(work, GV_StrCode(title_aDsppmode_800D88C8), poly, -0x46, -0x35, 0x46, -0x2D, 1, 2);
    setRGB0(poly, 0x64, 0xA0, 0x87);
    work->fF8[17] = 0;

    {
        DG_PRIM *prim;

        prim = DG_MakePrim(0x814, 6, 0, 0, 0);
        if (prim)
        {
            DG_QueuePrim(prim);
            DG_GroupPrim(prim, GM_CurrentMap);
        }
        work->prim[1] = prim;
    }

    n = 0;

    gpoly = &work->f934_polys[0];
    title_open_800D4464(work, GV_StrCode("op_n_game"), gpoly, -0x26, 0x46, 0x26, 0x4E, 1);
    work->fE0[n] = 0;

    gpoly = &work->f934_polys[1];
    n++;
    title_open_800D4464(work, GV_StrCode("op_l_game"), gpoly, -0x28, 0x46, 0x28, 0x4E, n);
    work->fE0[n] = 0;

    gpoly = &work->f934_polys[2];
    n++;
    title_open_800D4464(work, GV_StrCode("op_option"), gpoly, -0x1A, 0x46, 0x1A, 0x4E, 1);
    work->fE0[n] = 0;

    gpoly = &work->f934_polys[3];
    n++;
    title_open_800D4464(work, GV_StrCode("op_brf"), gpoly, -0x20, 0x46, 0x20, 0x4E, 1);
    work->fE0[n] = 0;

    gpoly = &work->f934_polys[4];
    n++;
    title_open_800D4464(work, GV_StrCode("op_special"), gpoly, -0x1E, 0x46, 0x1E, 0x4E, 1);
    work->fE0[n] = 0;

    gpoly = &work->f934_polys[5];
    n++;
    title_open_800D4464(work, GV_StrCode("op_vr"), gpoly, -0x2C, 0x46, 0x2C, 0x4E, 1);
    work->fE0[n] = 0;

    if (GCL_GetOption('s'))
    {
        work->f24F8_proc = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->f24F8_proc = -1;
    }

    if (GCL_GetOption('k'))
    {
        work->f24FC = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->f24FC = -1;
    }

    if (GCL_GetOption('l'))
    {
        work->f2500 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->f2500 = -1;
    }

    if (GCL_GetOption('e'))
    {
        work->fAD0 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->fAD0 = -1;
    }

    if (GCL_GetOption('b'))
    {
        work->fAD4 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->fAD4 = -1;
    }

    if (GCL_GetOption('f'))
    {
        work->fAD8 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->fAD8 = -1;
    }

    if (GCL_GetOption('o'))
    {
        work->fADC = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->fADC = -1;
    }

    if (GCL_GetOption('j'))
    {
        work->fAE4 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->fAE4 = -1;
    }

    if (GCL_GetOption('a'))
    {
        work->fAE0 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->fAE0 = -1;
    }

    if (GCL_GetOption('r'))
    {
        work->fAE8 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->fAE8 = -1;
    }

    if (GCL_GetOption('c'))
    {
        work->fAEC = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->fAEC = -1;
    }

    if (GCL_GetOption('d'))
    {
        work->fAF8 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->fAF8 = -1;
    }

    if (GCL_GetOption('x'))
    {
        work->fB08 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->fB08 = 1;
    }

    if (GCL_GetOption('p'))
    {
        work->fAF0 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->fAF0 = -1;
    }

    if (GCL_GetOption('m'))
    {
        work->fAF4 = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->fAF4 = -1;
    }

    if (GCL_GetOption('g'))
    {
        work->f24D0 = GCL_StrToInt(GCL_NextStr());
    }

    if (GCL_GetOption('h'))
    {
        work->fB28 = GCL_StrToInt(GCL_NextStr());
    }

    if (GCL_GetOption('v'))
    {
        work->fB10 = GCL_StrToInt(GCL_NextStr());
    }

    for (n = 0; n < 24; n++)
    {
        work->unk[n].string = GCL_GetString(GCL_NextStr());
        work->unk[n].num = 0;
        Open_800C4500(work, n);
    }

    for (n = 0; n < 24; n++)
    {
        Open_800C4674(work, n);
        title_open_800C4AD0(work, n, 0);
    }

    work->pad = &GV_PadData[2];
    work->f164 = 0;
    work->f168 = 0;
    work->f16C = 0;
    work->f170 = 0;
    work->f174 = 0;
    work->f178 = 0;
    work->f17C = 0;
    work->f180 = 0;
    work->f184 = 0;
    work->f188 = 0;
    work->fA7C = 0;
    work->fA80 = 0;
    work->fA84 = 0;
    work->fA88 = 0;
    work->fA8C = 0;
    work->fA90 = 0;
    work->fA94 = 0;
    work->fA98 = 0;
    work->fA9C = 0;
    work->fA78 = 0;
    work->fAB8 = 0;
    work->fABC = 0;
    work->fAC0 = 0;
    work->fA70 = 0;
    work->fAA8.r = 0x80;
    work->fAA8.g = 0x80;
    work->fAA8.b = 0x80;
    work->fB00 = 0;
    work->fB04 = 0;
    work->fB14 = 0;
    work->fB18 = 0;
    work->fB20 = 0;
    work->fB24 = 0;
    work->f24D4 = 0;

    for (n = 3; n >= 0; n--)
    {
        work->fB2C[n] = 0;
    }

    poly = &work->f18C_polys[0];
    gp = &work->f934_polys[0];
    work->f24CC = 0;

    switch (work->fB08)
    {
    case 0:
        work->fA74 = 0;
        work->fB0C = 1;
        break;

    case 1:
        work->fA74 = 4;
        work->fB0C = 1;
        break;

    case 2:
        work->fA74 = 6;
        work->fB0C = 1;
        break;

    case 4:
        work->fA74 = 7;
        work->fB0C = 1;
        title_open_800C5CB8(work);
        work->f30[0] = 0x700;
        work->f30[1] = 0x700;
        work->f30[2] = 0x700;
        work->f30[3] = 0x600;
        work->f30[4] = 0x500;
        work->f30[5] = 0x500;
        work->f30[6] = 0x500;
        work->f30[7] = 0x100;
        work->f30[8] = 0x100;
        work->f30[9] = 0x300;
        work->f30[10] = 0x200;
        work->f30[11] = 0x400;
        work->f30[12] = 0x100;
        setRGB0(&poly[7], 0x80, 0x80, 0x80);
        setRGB0(&poly[8], 0x80, 0x80, 0x80);
        setRGB0(&poly[9], 0x80, 0x80, 0x80);
        setRGB0(&poly[10], 0x80, 0x80, 0x80);
        setRGB0(&poly[11], 0x80, 0x80, 0x80);
        setRGB0(&poly[12], 0x80, 0x80, 0x80);
        if (work->fA7C == 0)
        {
            work->fA7C = 1;
        }
        if (work->fA80 == 0)
        {
            work->fA80 = 1;
            work->f170 = 0;
        }
        if (work->fA84 == 0)
        {
            work->fA84 = 1;
            work->f170 = 0;
        }
        if (sd_sng_play() == 0)
        {
            GM_SetSound(0x1000001, 0);
        }
        work->fA78 = 1;
        title_open_800C4B94(&gp[0], 0, 0, 0, 0x80, 0xC0, 0x80);
        title_open_800C4B94(&gp[1], 0x80, 0xC0, 0x80, 0x80, 0xC0, 0x80);
        title_open_800C4B94(&gp[2], 0x80, 0xC0, 0x80, 0, 0, 0);
        setXY4(&gp[0], -0x26, 0x37, 0x26, 0x37, -0x26, 0x3F, 0x26, 0x3F);
        setXY4(&gp[1], -0x28, 0x46, 0x28, 0x46, -0x28, 0x4E, 0x28, 0x4E);
        setXY4(&gp[2], -0x1A, 0x55, 0x1A, 0x55, -0x1A, 0x5D, 0x1A, 0x5D);
        SetSemiTrans(&gp[0], 1);
        SetSemiTrans(&gp[1], 0);
        SetSemiTrans(&gp[2], 1);
        work->fA98 = 2;
        work->f184 = 0;
        work->fE0[0] = 0x100;
        work->fE0[1] = 0x100;
        work->fE0[2] = 0x100;
        work->fE0[3] = 0;
        work->fE0[4] = 0;
        work->fE0[5] = 0;
        break;

    case 5:
        work->fA74 = 7;
        work->fB0C = 1;
        title_open_800C5CB8(work);
        work->f30[0] = 0x700;
        work->f30[1] = 0x700;
        work->f30[2] = 0x700;
        work->f30[3] = 0x600;
        work->f30[4] = 0x500;
        work->f30[5] = 0x500;
        work->f30[6] = 0x500;
        work->f30[7] = 0x100;
        work->f30[8] = 0x100;
        work->f30[9] = 0x300;
        work->f30[10] = 0x200;
        work->f30[11] = 0x400;
        work->f30[12] = 0x100;
        setRGB0(&poly[7], 0x80, 0x80, 0x80);
        setRGB0(&poly[8], 0x80, 0x80, 0x80);
        setRGB0(&poly[9], 0x80, 0x80, 0x80);
        setRGB0(&poly[10], 0x80, 0x80, 0x80);
        setRGB0(&poly[11], 0x80, 0x80, 0x80);
        setRGB0(&poly[12], 0x80, 0x80, 0x80);
        if (work->fA7C == 0)
        {
            work->fA7C = 1;
        }
        if (work->fA80 == 0)
        {
            work->fA80 = 1;
            work->f170 = 0;
        }
        if (work->fA84 == 0)
        {
            work->fA84 = 1;
            work->f170 = 0;
        }
        if (sd_sng_play() == 0)
        {
            GM_SetSound(0x1000001, 0);
        }
        work->fA78 = 2;
        title_open_800C4B94(&gp[1], 0, 0, 0, 0x80, 0xC0, 0x80);
        title_open_800C4B94(&gp[2], 0x80, 0xC0, 0x80, 0x80, 0xC0, 0x80);
        title_open_800C4B94(&gp[3], 0x80, 0xC0, 0x80, 0, 0, 0);
        setXY4(&gp[1], -0x28, 0x37, 0x28, 0x37, -0x28, 0x3F, 0x28, 0x3F);
        setXY4(&gp[2], -0x1A, 0x46, 0x1A, 0x46, -0x1A, 0x4E, 0x1A, 0x4E);
        setXY4(&gp[3], -0x20, 0x55, 0x20, 0x55, -0x20, 0x5D, 0x20, 0x5D);
        SetSemiTrans(&gp[1], 1);
        SetSemiTrans(&gp[2], 0);
        SetSemiTrans(&gp[3], 1);
        work->fA98 = 2;
        work->f184 = 0;
        work->fE0[0] = 0;
        work->fE0[1] = 0x100;
        work->fE0[2] = 0x100;
        work->fE0[3] = 0x100;
        work->fE0[4] = 0;
        work->fE0[5] = 0;
        break;

    case 6:
        work->fA74 = 7;
        work->fB0C = 1;
        title_open_800C5CB8(work);
        work->f30[0] = 0x700;
        work->f30[1] = 0x700;
        work->f30[2] = 0x700;
        work->f30[3] = 0x600;
        work->f30[4] = 0x500;
        work->f30[5] = 0x500;
        work->f30[6] = 0x500;
        work->f30[7] = 0x100;
        work->f30[8] = 0x100;
        work->f30[9] = 0x300;
        work->f30[10] = 0x200;
        work->f30[11] = 0x400;
        work->f30[12] = 0x100;
        setRGB0(&poly[7], 0x80, 0x80, 0x80);
        setRGB0(&poly[8], 0x80, 0x80, 0x80);
        setRGB0(&poly[9], 0x80, 0x80, 0x80);
        setRGB0(&poly[10], 0x80, 0x80, 0x80);
        setRGB0(&poly[11], 0x80, 0x80, 0x80);
        setRGB0(&poly[12], 0x80, 0x80, 0x80);
        if (work->fA7C == 0)
        {
            work->fA7C = 1;
        }
        if (work->fA80 == 0)
        {
            work->fA80 = 1;
            work->f170 = 0;
        }
        if (work->fA84 == 0)
        {
            work->fA84 = 1;
            work->f170 = 0;
        }
        if (sd_sng_play() == 0)
        {
            GM_SetSound(0x1000001, 0);
        }
        work->fA78 = 3;
        title_open_800C4B94(&gp[2], 0, 0, 0, 0x80, 0xC0, 0x80);
        title_open_800C4B94(&gp[3], 0x80, 0xC0, 0x80, 0x80, 0xC0, 0x80);
        title_open_800C4B94(&gp[4], 0x80, 0xC0, 0x80, 0, 0, 0);
        setXY4(&gp[2], -0x1A, 0x37, 0x1A, 0x37, -0x1A, 0x3F, 0x1A, 0x3F);
        setXY4(&gp[3], -0x20, 0x46, 0x20, 0x46, -0x20, 0x4E, 0x20, 0x4E);
        setXY4(&gp[4], -0x1E, 0x55, 0x1E, 0x55, -0x1E, 0x5D, 0x1E, 0x5D);
        SetSemiTrans(&gp[2], 1);
        SetSemiTrans(&gp[3], 0);
        SetSemiTrans(&gp[4], 1);
        work->fA98 = 2;
        work->f184 = 0;
        work->fE0[0] = 0;
        work->fE0[1] = 0;
        work->fE0[2] = 0x100;
        work->fE0[3] = 0x100;
        work->fE0[4] = 0x100;
        work->fE0[5] = 0;
        break;

    case 7:
        work->fA74 = 7;
        work->fB0C = 1;
        title_open_800C5CB8(work);
        work->f30[0] = 0x700;
        work->f30[1] = 0x700;
        work->f30[2] = 0x700;
        work->f30[3] = 0x600;
        work->f30[4] = 0x500;
        work->f30[5] = 0x500;
        work->f30[6] = 0x500;
        work->f30[7] = 0x100;
        work->f30[8] = 0x100;
        work->f30[9] = 0x300;
        work->f30[10] = 0x200;
        work->f30[11] = 0x400;
        work->f30[12] = 0x100;
        setRGB0(&poly[7], 0x80, 0x80, 0x80);
        setRGB0(&poly[8], 0x80, 0x80, 0x80);
        setRGB0(&poly[9], 0x80, 0x80, 0x80);
        setRGB0(&poly[10], 0x80, 0x80, 0x80);
        setRGB0(&poly[11], 0x80, 0x80, 0x80);
        setRGB0(&poly[12], 0x80, 0x80, 0x80);
        if (work->fA7C == 0)
        {
            work->fA7C = 1;
        }
        if (work->fA80 == 0)
        {
            work->fA80 = 1;
            work->f170 = 0;
        }
        if (work->fA84 == 0)
        {
            work->fA84 = 1;
            work->f170 = 0;
        }
        if (sd_sng_play() == 0)
        {
            GM_SetSound(0x1000001, 0);
        }
        work->fA78 = 4;
        title_open_800C4B94(&gp[3], 0, 0, 0, 0x80, 0xC0, 0x80);
        title_open_800C4B94(&gp[4], 0x80, 0xC0, 0x80, 0x80, 0xC0, 0x80);
        title_open_800C4B94(&gp[0], 0x80, 0xC0, 0x80, 0, 0, 0);
        setXY4(&gp[3], -0x20, 0x37, 0x20, 0x37, -0x20, 0x3F, 0x20, 0x3F);
        setXY4(&gp[4], -0x1E, 0x46, 0x1E, 0x46, -0x1E, 0x4E, 0x1E, 0x4E);
        setXY4(&gp[0], -0x26, 0x55, 0x26, 0x55, -0x26, 0x5D, 0x26, 0x5D);
        SetSemiTrans(&gp[3], 1);
        SetSemiTrans(&gp[4], 0);
        SetSemiTrans(&gp[0], 1);
        work->fA98 = 2;
        work->f184 = 0;
        work->fE0[0] = 0x100;
        work->fE0[1] = 0;
        work->fE0[2] = 0;
        work->fE0[3] = 0x100;
        work->fE0[4] = 0x100;
        work->fE0[5] = 0;
        break;

    case 8:
        work->fA74 = 7;
        work->fB0C = 1;
        title_open_800C5CB8(work);
        work->f30[0] = 0x700;
        work->f30[1] = 0x700;
        work->f30[2] = 0x700;
        work->f30[3] = 0x600;
        work->f30[4] = 0x500;
        work->f30[5] = 0x500;
        work->f30[6] = 0x500;
        work->f30[7] = 0x100;
        work->f30[8] = 0x100;
        work->f30[9] = 0x300;
        work->f30[10] = 0x200;
        work->f30[11] = 0x400;
        work->f30[12] = 0x100;
        setRGB0(&poly[7], 0x80, 0x80, 0x80);
        setRGB0(&poly[8], 0x80, 0x80, 0x80);
        setRGB0(&poly[9], 0x80, 0x80, 0x80);
        setRGB0(&poly[10], 0x80, 0x80, 0x80);
        setRGB0(&poly[11], 0x80, 0x80, 0x80);
        setRGB0(&poly[12], 0x80, 0x80, 0x80);
        if (work->fA7C == 0)
        {
            work->fA7C = 1;
        }
        if (work->fA80 == 0)
        {
            work->fA80 = 1;
            work->f170 = 0;
        }
        if (work->fA84 == 0)
        {
            work->fA84 = 1;
            work->f170 = 0;
        }
        if (sd_sng_play() == 0)
        {
            GM_SetSound(0x1000001, 0);
        }
        work->fA78 = 5;
        title_open_800C4B94(&gp[4], 0, 0, 0, 0x80, 0xC0, 0x80);
        title_open_800C4B94(&gp[5], 0x80, 0xC0, 0x80, 0x80, 0xC0, 0x80);
        title_open_800C4B94(&gp[0], 0x80, 0xC0, 0x80, 0, 0, 0);
        setXY4(&gp[4], -0x1E, 0x37, 0x1E, 0x37, -0x1E, 0x3F, 0x1E, 0x3F);
        setXY4(&gp[5], -0x2C, 0x46, 0x2C, 0x46, -0x2C, 0x4E, 0x2C, 0x4E);
        setXY4(&gp[0], -0x26, 0x55, 0x26, 0x55, -0x26, 0x5D, 0x26, 0x5D);
        SetSemiTrans(&gp[4], 1);
        SetSemiTrans(&gp[5], 0);
        SetSemiTrans(&gp[0], 1);
        work->fA98 = 2;
        work->f184 = 0;
        work->fE0[0] = 0x100;
        work->fE0[1] = 0;
        work->fE0[2] = 0;
        work->fE0[3] = 0;
        work->fE0[4] = 0x100;
        work->fE0[5] = 0x100;
        break;

    case 9:
        break;
    }

    printf("start flag = %d\n", work->fB08);
    printf("mem flag = %d\n", work->f24D0);

    work->f24D8 = 0;
    work->f24DC = 0;
    work->f24E8 = 0;

    return 0;
}

void *NewOpen(int name, int where)
{
    Work *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = GV_NewActor(GV_ACTOR_MANAGER, sizeof(Work));
    title_dword_800D92D0 = 0;

    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "open.c");

        if (GetResources(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
