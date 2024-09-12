#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Font/font.h"
#include "Menu/menuman.h"
#include "Game/game.h"
#include "SD/sound.h"
#include "SD/g_sound.h"

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

typedef struct _OpenWork
{
    GV_ACT   actor;
    DG_PRIM *prim[4];
    int      f30[22];
    char     pad[0x58];
    int      fE0[6];
    int      fF8[18];
    int      f140[9];
    int      f164;
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
    short   *fA6C;
    int      fA70;
    int      fA74;
    int      fA78;
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
    char     fAA8; // Could be array or part of some struct (KCB?)
    char     fAA9;
    char     fAAA;
    char     fAAB;
    char     fAAC;
    char     fAAD;
    char     fAAE;
    char     fAAF;
    char     pad6[0x8]; // AB0
    int      fAB8;
    char     pad7[0x1C]; // ABC
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
    int      fB0C;
    int      fB10;
    int      fB14;
    int      fB18;
    int      fB1C;
    int      fB20;
    int      fB24;
    int      fB28;
    int      fB2C;
    int      fB30;
    int      fB34;
    int      fB38;
    int      fB3C;
    int      fB40;
    int      fB44;
    int      fB48;
    KCB      kcb[24]; // B4C
    char     pad8[0x2C]; // enough space for another KCB here, but code loops over 24?
    Unknown  unk[24];
    int      f2498;
    int      f249C;
    int      f24A0;
    int      f24A4;
    char     pad9[0x4];
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
    char     pad10[8];
} OpenWork;

typedef struct _Desc
{
    int     f0;
    DVECTOR f4;
    int     color;
} Desc;

extern Desc open_800C32B4[24];

extern int title_dword_800D92D0;
extern int title_dword_800C33D4;

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
extern int   GM_GameStatus;
extern int   GV_Clock_800AB920;
extern int   gDiskNum_800ACBF0;

#define EXEC_LEVEL 1

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

    buffer = GV_AllocMemory(2, font_get_buffer_size(kcb));
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

    work->unk[index].rect.w = kcb->char_arr[7];
    work->unk[index].rect.h = kcb->short3 - 1;

    if (open_800C32B4[index].f0 == 0)
    {
        work->unk[index].rect.x = open_800C32B4[index].f4.vx;
        work->unk[index].rect.y = open_800C32B4[index].f4.vy;
    }
    else if (open_800C32B4[index].f0 == 1)
    {
        work->unk[index].rect.x = open_800C32B4[index].f4.vx - kcb->char_arr[7] / 2;
        work->unk[index].rect.y = open_800C32B4[index].f4.vy - kcb->short3 / 2;
    }

    work->unk[index].string = 0;
    work->unk[index].num = 1;
}

#pragma INCLUDE_ASM("asm/overlays/title/title_open_800C47B8.s")
void title_open_800C47B8(OpenWork *, int);

void title_open_800C4AD0(OpenWork *work, int index, int color)
{
    KCB *kcb;

    kcb = &work->kcb[index];
    font_set_color(kcb, 0, color, 0);
    font_clut_update(kcb);
}

void * title_open_800C4B20(KCB *kcb)
{
    return kcb->font_clut_buffer;
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

    poly->u0 = x + xoff;
    poly->v0 = y + yoff;

    poly->u1 = x + xoff + width;
    poly->v1 = y + yoff;

    poly->u2 = x + xoff;
    poly->v2 = y + yoff + height;

    poly->u3 = x + xoff + width;
    poly->v3 = y + yoff + height;

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
    dst_ft4 = &work->prim[0]->packs[GV_Clock_800AB920]->poly_ft4;
    for (i = 0; i < 22; i++)
    {
        *dst_ft4 = *src_ft4;
        SSTOREL(work->f30[i], &dst_ft4->tag);
        dst_ft4++;
        src_ft4++;
    }

    src_ft4 = work->f4FC_polys;
    dst_ft4 = &work->prim[2]->packs[GV_Clock_800AB920]->poly_ft4;
    for (i = 0; i < 18; i++)
    {
        *dst_ft4 = *src_ft4;
        SSTOREL(work->fF8[i], &dst_ft4->tag);
        dst_ft4++;
        src_ft4++;
    }

    src_ft4 = work->f7CC_polys;
    dst_ft4 = &work->prim[3]->packs[GV_Clock_800AB920]->poly_ft4;
    for (i = 0; i < 9; i++)
    {
        *dst_ft4 = *src_ft4;
        SSTOREL(work->f140[i], &dst_ft4->tag);
        dst_ft4++;
        src_ft4++;
    }

    src_gt4 = work->f934_polys;
    dst_gt4 = &work->prim[1]->packs[GV_Clock_800AB920]->poly_gt4;
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
    mem_card card1, card2;
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
        printf("free = %d\n", card1.field_3_free_blocks);

        if (card1.field_3_free_blocks == 0)
        {
            found = 0;
            for (i = 0; i < card1.field_2_file_count; i++)
            {
                printf("name = %s\n", card1.field_4_blocks[i].field_0_name);

                mismatch = 0;
                for (j = 0; j < 12; j++)
                {
                    if (card1.field_4_blocks[i].field_0_name[j] != name[j])
                    {
                        mismatch = 1;
                        break;
                    }
                }

                if (mismatch == 0 && card1.field_4_blocks[i].field_0_name[12] == 'G')
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
        printf("free = %d\n", card2.field_3_free_blocks);

        if (card2.field_3_free_blocks == 0)
        {
            found = 0;
            for (i = 0; i < card2.field_2_file_count; i++)
            {
                printf("name = %s\n", card2.field_4_blocks[i].field_0_name);

                mismatch = 0;
                for (j = 0; j < 12; j++)
                {
                    if (card2.field_4_blocks[i].field_0_name[j] != name[j])
                    {
                        mismatch = 1;
                        break;
                    }
                }

                if (mismatch == 0 && card2.field_4_blocks[i].field_0_name[12] == 'G')
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
    if (gDiskNum_800ACBF0 == 0)
    {
        if (SD_800886F4() == 0)
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
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CDE44.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CE378.s")

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
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800CF794.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D1B74.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D1CB4.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D2374.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D2460.s")
#pragma INCLUDE_ASM("asm/overlays/title/title_open_800D2E44.s")

void title_open_800D3500(OpenWork *work, int arg1)
{
    int i;

    for (i = 0; i < 24; i++)
    {
        title_open_800C4AD0(work, i, 0);
    }

    if (work->fA74 >= 18 && work->fA74 <= 19)
    {
        title_open_800C4AD0(work, 21, 0x6739);

        MENU_Locate_80038B34(54, 60, 0x10);
        MENU_Color_80038B4C(100, 160, 135);
        MENU_Printf_80038C38(title_aMemorycardslot_800D8FAC);

        if (work->f24F0 == 3)
        {
            MENU_Locate_80038B34(223, 60, 0x10);
            MENU_Color_80038B4C(181, 85, 42);
            MENU_Printf_80038C38(title_aFull_800D8FC4);
        }
        else
        {
            MENU_Locate_80038B34(223, 60, 0x10);
            MENU_Color_80038B4C(181, 85, 42);
            MENU_Printf_80038C38(title_aNocard_800D8FCC);
        }

        MENU_Locate_80038B34(54, 75, 0x10);
        MENU_Color_80038B4C(100, 160, 135);
        MENU_Printf_80038C38(title_aMemorycardslot_800D8FD4);

        if (work->f24F4 == 3)
        {
            MENU_Locate_80038B34(223, 75, 0x10);
            MENU_Color_80038B4C(181, 85, 42);
            MENU_Printf_80038C38(title_aFull_800D8FC4);
        }
        else
        {
            MENU_Locate_80038B34(223, 75, 0x10);
            MENU_Color_80038B4C(181, 85, 42);
            MENU_Printf_80038C38(title_aNocard_800D8FCC);
        }

        MENU_Locate_80038B34(70, 100, 0x10);
        MENU_Color_80038B4C(100, 160, 135);
        MENU_Printf_80038C38(title_aDoyouwanttocontinue_800D8FEC);

        MENU_Locate_80038B34(85, 115, 0x10);
        MENU_Color_80038B4C(100, 160, 135);
        MENU_Printf_80038C38(title_aYourgamelikethis_800D9008);

        if (work->f24E0 == 0)
        {
            MENU_Locate_80038B34(100, 150, 0x10);
            MENU_Color_80038B4C(192, 192, 192);
            MENU_Printf_80038C38(title_aYes_800D9020);

            MENU_Locate_80038B34(200, 150, 0x10);
            MENU_Color_80038B4C(46, 72, 61);
            MENU_Printf_80038C38(title_aNo_800D9024);

            title_open_800C4F1C(work, -68, 33, 40, 15, 255, 1);
        }
        else
        {
            MENU_Locate_80038B34(100, 150, 0x10);
            MENU_Color_80038B4C(46, 72, 61);
            MENU_Printf_80038C38(title_aYes_800D9020);

            MENU_Locate_80038B34(200, 150, 0x10);
            MENU_Color_80038B4C(192, 192, 192);
            MENU_Printf_80038C38(title_aNo_800D9024);

            title_open_800C4F1C(work, 28, 33, 40, 15, 255, 1);
        }
    }

    title_open_800C47B8(work, arg1);
}

#pragma INCLUDE_ASM("asm/overlays/title/OpenAct_800D37F4.s")
void OpenAct_800D37F4(OpenWork *work);

void OpenDie_800D4098(OpenWork *work)
{
    DG_PRIM *prim;
    int      i;
    void    *buf;

    prim = work->prim[0];
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    prim = work->prim[2];
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    prim = work->prim[3];
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    prim = work->prim[1];
    if (prim != NULL)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }

    for (i = 0; i < 24; i++)
    {
        buf = title_open_800C4B20(&work->kcb[i]);
        GV_FreeMemory(2, buf);
    }
}

void title_open_800D4174(OpenWork *work, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe)
{
    setPolyFT4(poly);
    setRGB0(poly, 128, 128, 128);
    setXY4(poly, x0, y0, x1, y0, x0, y1, x1, y1);
    SetSemiTrans(poly, abe);
}

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

void title_open_800D41E4(OpenWork *work, int name, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe, int type)
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

void title_open_800D4368(OpenWork *work, int name, POLY_FT4 *poly, int x0, int y0, int x1, int y1, int abe)
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

void title_open_800D4464(OpenWork *work, int name, POLY_GT4 *poly, int x0, int y0, int x1, int y1, int abe)
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

#pragma INCLUDE_ASM("asm/overlays/title/OpenGetResources_800D4584.s")
int  OpenGetResources_800D4584(OpenWork *work, int);

GV_ACT *NewOpen_800D6814(int arg0, int arg1)
{
    OpenWork *work;

    GM_GameStatus |= STATE_ALL_OFF;

    work = (OpenWork *)GV_NewActor(EXEC_LEVEL, sizeof(OpenWork));
    title_dword_800D92D0 = 0;

    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)OpenAct_800D37F4, (TActorFunction)OpenDie_800D4098, aOpenC);

        if (OpenGetResources_800D4584(work, arg1) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
