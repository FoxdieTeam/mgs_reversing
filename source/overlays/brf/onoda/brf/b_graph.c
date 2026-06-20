#include "game/game.h"
#include <stdio.h>

typedef struct _Work
{
    GV_ACT  actor;           /* 0x000 */
    void   *field_20;        /* 0x020 */
    void   *field_24;        /* 0x024 */
    void   *field_28;        /* 0x028 */
    void   *field_2C;        /* 0x02C */
    void   *field_30;        /* 0x030 */
    char    pad_34[0x84 - 0x34];  /* 0x034 */
    POLY_FT4 field_84;            /* 0x084 */
    char    pad_AC[0x28C - 0xAC]; /* 0x0AC */
    POLY_FT4 field_28C[291];      /* 0x28C */
    char    pad_3004[0xA588 - 0x3004]; /* 0x3004 */
    int     field_A588;                /* 0xA588 */
    char    pad_A58C[0xA595 - 0xA58C]; /* 0xA58C */
    unsigned char field_A595;          /* 0xA595 */
    char    pad_A596[0xA597 - 0xA596]; /* 0xA596 */
    unsigned char field_A597[0xA9A7 - 0xA597]; /* 0xA597 */
    unsigned char field_A9A7[0xA9B6 - 0xA9A7]; /* 0xA9A7 */
    unsigned char field_A9B6[0xAD00 - 0xA9B6]; /* 0xA9B6 */
    GV_PAD *field_AD00;      /* 0xAD00 */
    int     field_AD04;      /* 0xAD04 */
    void   *field_AD08;      /* 0xAD08 */
    int    *field_AD0C;      /* 0xAD0C */
    int     field_AD10;      /* 0xAD10 */
    int     field_AD14;      /* 0xAD14 */
    int    *field_AD18;      /* 0xAD18 */
    void  **field_AD1C;      /* 0xAD1C */
    int     field_AD20;      /* 0xAD20 */
    char    pad_AD24[0x4];   /* 0xAD24 */
    int     field_AD28;      /* 0xAD28 */
    int     field_AD2C;      /* 0xAD2C */
    int     field_AD30;      /* 0xAD30 */
    int     field_AD34;      /* 0xAD34 */
    int     field_AD38;      /* 0xAD38 */
    int     field_AD3C;      /* 0xAD3C */
    int     field_AD40;      /* 0xAD40 */
    int     field_AD44;      /* 0xAD44 */
    int     field_AD48;      /* 0xAD48 */
    char    pad_AD4C[0x4];   /* 0xAD4C */
    int     field_AD50;      /* 0xAD50 */
    int     field_AD54;      /* 0xAD54 */
    int     field_AD58;      /* 0xAD58 */
    int     field_AD5C;      /* 0xAD5C */
    int     field_AD60;      /* 0xAD60 */
    char    pad_AD64[0x10];  /* 0xAD64 */
    int     field_AD74;      /* 0xAD74 */
    int     field_AD78;      /* 0xAD78 */
    int     field_AD7C;      /* 0xAD7C */
    int     field_AD80;      /* 0xAD80 */
    int     field_AD84;      /* 0xAD84 */
    int     field_AD88;      /* 0xAD88 */
    char    pad_AD8C[0x4];   /* 0xAD8C */
    int     field_AD90;      /* 0xAD90 */
    int     field_AD94;      /* 0xAD94 */
    char    pad_AD98[0x4];   /* 0xAD98 */
    int     field_AD9C;      /* 0xAD9C */
    int     field_ADA0;      /* 0xADA0 */
    int     field_ADA4;      /* 0xADA4 */
    int     field_ADA8;      /* 0xADA8 */
    int     field_ADAC;      /* 0xADAC */
    int     field_ADB0;      /* 0xADB0 */
    char    pad_ADB4[0x4];   /* 0xADB4 */
    int     field_ADB8;      /* 0xADB8 */
    int     field_ADBC;      /* 0xADBC */
    int     field_ADC0;      /* 0xADC0 */
    char    field_ADC4;      /* 0xADC4 */
    char    pad_ADC5[0x3];   /* 0xADC5 */
} Work;

typedef struct
{
    short field_0;
    short field_2;
} BrfKeyframe;

typedef struct
{
    char    pad_0[4];
    u_short field_4;  /* tpage */
    u_short field_6;  /* clut */
    u_char  field_8;  /* u */
    u_char  field_9;  /* v */
    u_char  field_A;  /* w */
    u_char  field_B;  /* h */
} BrfGlyph;
BrfGlyph *brf_800CABF4();
extern char brf_dword_800E1BF0[];

BrfGlyph *brf_800CABF4(work, key)
Work *work;
int key;
{
    int i;
    int found = 0;
    for (i = 0; i < work->field_AD10; i++)
    {
        if (work->field_AD0C[i] == key)
        {
            return (BrfGlyph *)((char *)work->field_AD08 + i * 12);
        }
    }
    if (!found)
    {
        printf(brf_dword_800E1BF0, key);
    }
    return 0;
}
void brf_800CAC7C(Work *work, int key)
{
    int i;
    int found = 0;
    void *result = 0;
    for (i = 0; i < work->field_AD14; i++)
    {
        if (work->field_AD18[i] == key)
        {
            result = work->field_AD1C[i];
            found = 1;
        }
    }
    if (found)
    {
        LoadImage((RECT *)result, (u_long *)((char *)result + 8));
        LoadImage((RECT *)((char *)result + 0x208), (u_long *)((char *)result + 0x210));
    }
    else
    {
        printf(brf_dword_800E1BF0, key);
    }
}
extern const char brf_dword_800E1C14[];
int jimctrl_helper_80037F68();
extern int brf_dword_800C5094;

void brf_800CAD24(Work *work, POLY_FT4 *dest, int a2, int a3, int a4)
{
    BrfGlyph *g;
    int u, uw, v, vh;

    work->field_AD48 = a2;
    g = brf_800CABF4(work, ((unsigned short *)((int *)&brf_dword_800C5094)[a4])[a3]);
    u = g->field_8;
    uw = u + g->field_A + 1;
    v = g->field_9;
    vh = v + g->field_B + 1;

    dest->u0 = u;
    dest->v0 = v;
    dest->u1 = uw;
    dest->v1 = v;
    dest->u2 = u;
    dest->v2 = vh;
    dest->u3 = uw;
    dest->v3 = vh;
    dest->tpage = g->field_4;
    dest->clut = g->field_6;
}

void brf_800CADD4(Work *work, void *a1, int a2)
{
    int v0 = jimctrl_helper_80037F68(GV_StrCode(brf_dword_800E1C14));
    int s0 = v0 & 0xFF;

    work->field_AD60 = v0;
    if (work->field_AD44 != s0)
    {
        brf_800CAD24(work, a1, 0, s0, a2);
    }
    else if (work->field_AD48 != 0)
    {
        brf_800CAD24(work, a1, 1, s0, a2);
    }
    work->field_AD44 = s0;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CAE84.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CB23C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CB5F4.s")
extern int brf_dword_800C50DC;

void brf_800CBA84(Work *work, POLY_FT4 *dest, int idx)
{
    BrfGlyph *g = brf_800CABF4(work, ((unsigned short *)((int *)&brf_dword_800C50DC)[idx])[(work->field_AD40 - 1) / 2]);
    int u = g->field_8;
    int uw = u + g->field_A + 1;
    int v = g->field_9;
    int vh = v + g->field_B + 1;

    dest->u0 = u;
    dest->v0 = v;
    dest->u1 = uw;
    dest->v1 = v;
    dest->u2 = u;
    dest->v2 = vh;
    dest->u3 = uw;
    dest->v3 = vh;
    dest->tpage = g->field_4;
    dest->clut = g->field_6;

    work->field_AD40++;
    if (work->field_AD40 >= 7)
    {
        work->field_AD40 = 0;
    }
}
extern const char brf_dword_800E1C90[];

void brf_800CBB68(Work *work, void *a1, int a2)
{
    if (work->field_AD60 >> 8)
    {
        if (work->field_AD40)
        {
            printf((char *)brf_dword_800E1C90);
        }
        else
        {
            work->field_AD40 = 1;
        }
    }
    if (work->field_AD40)
    {
        brf_800CBA84(work, a1, a2);
    }
}
extern int brf_dword_800C50E8;
extern int brf_dword_800C50F4;

void brf_800CBC04(Work *work, POLY_FT4 *dest, int idx)
{
    unsigned short *tbl = (unsigned short *)&brf_dword_800C50E8;
    BrfGlyph *g = brf_800CABF4(work, tbl[idx / 3]);
    int u = g->field_8;
    int uw = u + g->field_A + 1;
    int v = g->field_9;
    int vh = v + g->field_B + 1;

    dest->u0 = u;
    dest->v0 = v;
    dest->u1 = uw;
    dest->v1 = v;
    dest->u2 = u;
    dest->v2 = vh;
    dest->u3 = uw;
    dest->v3 = vh;
    dest->tpage = g->field_4;
    dest->clut = g->field_6;
}
void brf_800CBCB0(Work *work, POLY_FT4 *dest, int idx)
{
    unsigned short *tbl = (unsigned short *)&brf_dword_800C50F4;
    BrfGlyph *g = brf_800CABF4(work, tbl[idx / 3]);
    int u = g->field_8;
    int uw = u + g->field_A + 1;
    int v = g->field_9;
    int vh = v + g->field_B + 1;

    dest->u0 = u;
    dest->v0 = v;
    dest->u1 = uw;
    dest->v1 = v;
    dest->u2 = u;
    dest->v2 = vh;
    dest->u3 = uw;
    dest->v3 = vh;
    dest->tpage = g->field_4;
    dest->clut = g->field_6;
}

void brf_800CBD5C(Work *work, void *a1)
{
    if (work->field_AD34 % 3 == 2)
    {
        brf_800CBC04(work, a1, work->field_AD34);
    }
    work->field_AD34++;
}
void brf_800CBDC8(Work *work, void *a1)
{
    if (work->field_AD34 % 3 == 2)
    {
        brf_800CBCB0(work, a1, work->field_AD34);
    }
    work->field_AD34++;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CBE34.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CBF48.s")
extern const char brf_dword_800E1D58[];

void brf_800CC070(Work *work, int idx)
{
    POLY_FT4 *p = &work->field_84;
    DG_TEX *tex = DG_GetTexture(GV_StrCode(brf_dword_800E1D58));
    int w1 = tex->w + 1;
    int ul = tex->off_x + w1 * idx / 3;
    int ur = tex->off_x + w1 * (idx + 1) / 3;
    int vt = tex->off_y;
    int h1 = tex->h + 1;
    int vb = tex->off_y + h1;

    p->u0 = ul;
    p->v0 = vt;
    p->u1 = ur;
    p->v1 = vt;
    p->u2 = ul;
    p->v2 = vb;
    p->u3 = ur;
    p->v3 = vb;
    p->tpage = tex->tpage;
    p->clut = tex->clut;
}
void brf_800CC150(Work *work)
{
    int i;

    work->field_A595 = 0;
    work->field_A9A7[0] = 0;

    for (i = 1; i < 15; i++)
    {
        work->field_A9A7[i] = 2;
    }
}
void brf_800CC070();
extern int brf_dword_800C3508;

void brf_800CC190(Work *work)
{
    int i;

    work->field_AD5C = 0;
    work->field_AD2C = 0;
    work->field_AD44 = 0;
    work->field_AD48 = 0;
    work->field_ADB8 = 0;
    work->field_ADBC = 0;

    for (i = 1; i < 15; i++)
    {
        work->field_A9A7[i] = 2;
    }

    brf_800CC070(work, 0);
    GM_SeSet2(0, 0x3F, 0xC1);

    {
        short *tbl = (short *)&brf_dword_800C3508;
        for (i = 0; i < tbl[work->field_A588]; i++)
        {
            work->field_A597[i] = 0;
        }
    }

    work->field_ADC0 = GV_RandU(8) + 8;
}

void brf_800CC28C(Work *work)
{
    int i;

    work->field_AD5C = 0;
    work->field_AD40 = 0;
    work->field_AD44 = 0;
    work->field_AD48 = 0;
    work->field_ADB8 = 0;
    work->field_ADBC = 0;

    for (i = 1; i < 15; i++)
    {
        work->field_A9A7[i] = 2;
    }

    brf_800CC070(work, 1);
    GM_SeSet2(0, 0x3F, 0xC1);

    {
        short *tbl = (short *)&brf_dword_800C3508;
        for (i = 0; i < tbl[work->field_A588]; i++)
        {
            work->field_A597[i] = 0;
        }
    }

    work->field_ADC0 = GV_RandU(8) + 8;
}

void brf_800CC388(Work *work)
{
    int i;

    work->field_AD5C = 0;
    work->field_AD44 = 0;
    work->field_AD48 = 0;
    work->field_ADB8 = 0;
    work->field_ADBC = 0;

    for (i = 1; i < 15; i++)
    {
        work->field_A9A7[i] = 2;
    }

    brf_800CC070(work, 2);
    GM_SeSet2(0, 0x3F, 0xC1);

    {
        short *tbl = (short *)&brf_dword_800C3508;
        for (i = 0; i < tbl[work->field_A588]; i++)
        {
            work->field_A597[i] = 0;
        }
    }

    work->field_ADC0 = GV_RandU(8) + 8;
}

void brf_800CC480(Work *work)
{
    int i;

    work->field_AD5C = 0;
    work->field_ADB8 = 0;
    work->field_ADBC = 0;

    for (i = 1; i < 15; i++)
    {
        work->field_A9A7[i] = 0;
    }

    GM_SeSet2(0, 0x3F, 0xC1);

    {
        short *tbl = (short *)&brf_dword_800C3508;
        for (i = 0; i < tbl[work->field_A588]; i++)
        {
            work->field_A597[i] = 0;
        }
    }

    work->field_ADC0 = GV_RandU(8) + 8;
}

void brf_800CC560(Work *work)
{
    int i;

    work->field_AD5C = 0;

    for (i = 0; i < ((short *)&brf_dword_800C3508)[work->field_A588]; i++)
    {
        work->field_A597[i] = 0;
    }
}
int brf_800CC5CC(int a)
{
    if (a < 0 || a > 9)
    {
        a = 0;
    }

    return a;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CC5E4.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CCBD4.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CD164.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CD734.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CD7DC.s")
void brf_800CD870(Work *work, int idx)
{
    POLY_FT4 *base = work->field_28C;

    base[idx].y0 -= 12;
    base[idx].y1 -= 12;
    base[idx].y2 -= 12;
    base[idx].y3 -= 12;
}
void brf_800CD8B8(Work *work, int a1, int a2, int a3)
{
    POLY_FT4 *base = work->field_28C;
    int v = work->field_AD30;

    if (a1 >= v)
    {
        int q = v * 128 / a1;
        int c = 128 - q;

        setRGB0(&base[a2], c, c, c);
        setRGB0(&base[a3], q, q, q);
    }

    work->field_AD30++;
}
void brf_800CD958(Work *work, int a1, int a2, int a3)
{
    int n = work->field_AD30;
    if (n < 0x11)
    {
        POLY_FT4 *base = work->field_28C;
        int c3 = n * 8;
        int c1 = base[a1].r0 * (0x10 - n) / 16;
        int c2 = base[a2].r0 * (0x10 - n) / 16;
        setRGB0(&base[a1], c1, c1, c1);
        setRGB0(&base[a2], c2, c2, c2);
        setRGB0(&base[a3], c3, c3, c3);
    }
}
void brf_800CDA10(Work *work, int a1, int a2)
{
    POLY_FT4 *base = work->field_28C;
    int v = work->field_AD30;

    if (v < 17)
    {
        int c1 = base[a1].r0 * (16 - v) / 16;
        int c2 = base[a2].r0 * (16 - v) / 16;

        setRGB0(&base[a1], c1, c1, c1);
        setRGB0(&base[a2], c2, c2, c2);
    }
}
void brf_800CDAA8(Work *work, int idx)
{
    int v = work->field_AD30;
    POLY_FT4 *base = work->field_28C;

    if (v < 0x11)
    {
        v <<= 3;
        setRGB0(&base[idx], v, v, v);
    }
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CDAEC.s")
void brf_800CDC8C(Work *work, POLY_FT4 *poly)
{
    int n = work->field_AD2C;
    int mul = n * 2 + 5;
    int dx = n * 2 + 3;
    int rx0 = poly->x0 * mul / dx;
    int rx1 = poly->x1 * mul / dx;
    int my = 3 - n;
    int dy = my + 1;
    int ry0 = poly->y0 * my / dy;
    int ry2 = poly->y2 * my / dy;

    poly->x0 = rx0;
    poly->x2 = rx0;
    poly->x1 = rx1;
    poly->x3 = rx1;
    poly->y0 = ry0;
    poly->y1 = ry0;
    poly->y2 = ry2;
    poly->y3 = ry2;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CDDD4.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CDF34.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CDFE4.s")
extern int brf_dword_800C35F4, brf_dword_800C360C, brf_dword_800C3690;
void brf_800CDAEC();

void brf_800CE1C4(Work *work)
{
    POLY_FT4 *base = work->field_28C;
    int x = work->field_AD78;
    int y = work->field_AD7C;
    int m = work->field_AD80;

    brf_800CDAEC(base, 2, &brf_dword_800C35F4, x, y, m, 0xc8);
    brf_800CDAEC(base, 0xb, &brf_dword_800C360C, x * 12 / 10, y, m, 0xc8);
    brf_800CDAEC(base, 2, &brf_dword_800C3690, x * 15 / 10, y, m, 0xc8);
    if (work->field_ADB0 & 3)
    {
        GM_SeSet2(0, 0x30, 0x24);
    }
}
extern int brf_dword_800C36A8, brf_dword_800C36C0, brf_dword_800C372C;

void brf_800CE2F8(Work *work)
{
    POLY_FT4 *base = work->field_28C;
    int x = work->field_AD78;
    int y = work->field_AD7C;
    int m = work->field_AD80;

    brf_800CDAEC(base, 2, &brf_dword_800C36A8, x, y, m, 0xc8);
    brf_800CDAEC(base, 9, &brf_dword_800C36C0, x * 12 / 10, y, m, 0xc8);
    brf_800CDAEC(base, 2, &brf_dword_800C372C, x * 15 / 10, y, m, 0xc8);
    if (work->field_ADB0 && (work->field_ADB0 & 3))
    {
        GM_SeSet2(0, 0x30, 0x24);
    }
}
void brf_800CE430(work)
Work *work;
{
    unsigned short status = work->field_AD00->status;

    if (work->field_ADA0 == 1 || work->field_ADA0 == 2)
    {
        switch (work->field_AD9C)
        {
        case 0:
            if (status & 0x2000) work->field_ADA0++;
            else { work->field_ADA0--; work->field_ADB8 = 0; work->field_ADBC = 1; }
            break;
        case 1:
            if (status & 0x8000) work->field_ADA0++;
            else { work->field_ADA0--; work->field_ADB8 = 0; work->field_ADBC = 1; }
            break;
        case 2:
            if (status & 0x1000) work->field_ADA0++;
            else { work->field_ADA0--; work->field_ADB8 = 0; work->field_ADBC = 1; }
            break;
        case 3:
            if (status & 0x4000) work->field_ADA0++;
            else { work->field_ADA0--; work->field_ADB8 = 0; work->field_ADBC = 1; }
            break;
        }
    }
    else if (work->field_ADA0 == 3)
    {
        switch (work->field_AD9C)
        {
        case 0:
            if (!(status & 0x2000)) { work->field_ADA0 = 2; work->field_ADB8 = 0; work->field_ADBC = 1; }
            break;
        case 1:
            if (!(status & 0x8000)) { work->field_ADA0 = 2; work->field_ADB8 = 0; work->field_ADBC = 1; }
            break;
        case 2:
            if (!(status & 0x1000)) { work->field_ADA0--; work->field_ADB8 = 0; work->field_ADBC = 1; }
            break;
        case 3:
            if (!(status & 0x4000)) { work->field_ADA0--; work->field_ADB8 = 0; work->field_ADBC = 1; }
            break;
        }
    }

    if (work->field_ADAC == 1 || work->field_ADAC == 2)
    {
        switch (work->field_ADA8)
        {
        case 4:
            if (status & 0x10) { work->field_ADAC++; work->field_ADB0++; return; }
            work->field_ADAC--; work->field_ADB0 = 0; work->field_ADB8 = 0; work->field_ADBC = 1;
            break;
        case 5:
            if (status & 0x80) { work->field_ADAC++; work->field_ADB0++; return; }
            work->field_ADAC--; work->field_ADB0 = 0; work->field_ADB8 = 0; work->field_ADBC = 1;
            break;
        }
    }
    else if (work->field_ADAC == 3)
    {
        switch (work->field_ADA8)
        {
        case 4:
            if (status & 0x10) return;
            work->field_ADAC = 2; work->field_ADB0 = 0; work->field_ADB8 = 0; work->field_ADBC = 1;
            break;
        case 5:
            if (status & 0x80) return;
            work->field_ADAC = 2; work->field_ADB0 = 0; work->field_ADB8 = 0; work->field_ADBC = 1;
            break;
        }
    }
}
void brf_800CE648(work, idx, mode, delta)
Work *work;
int idx;
int mode;
int delta;
{
    if (work->field_28C[idx].x0 < -127)
    {
        switch (mode)
        {
        case 1:
            work->field_AD78 += delta;
            break;
        case 2:
            work->field_AD84 += delta;
            break;
        case 3:
            work->field_AD90 += delta;
            break;
        }
    }
}

void brf_800CE6F0(work, idx, mode, delta)
Work *work;
int idx;
int mode;
int delta;
{
    if (work->field_28C[idx].x1 >= 0x80)
    {
        switch (mode)
        {
        case 1:
            work->field_AD78 -= delta;
            break;
        case 2:
            work->field_AD84 -= delta;
            break;
        case 3:
            work->field_AD90 -= delta;
            break;
        }
    }
}

void brf_800CE798(work, a1, a2, a3)
Work *work;
int a1;
int a2;
int a3;
{
    POLY_FT4 *base = work->field_28C;
    if (base[a1 + 1].y2 < 0x59)
    {
        return;
    }
    switch (a2)
    {
    case 1:
        work->field_AD7C -= a3;
        break;
    case 2:
        work->field_AD88 -= a3;
        break;
    case 3:
        work->field_AD94 -= a3;
        break;
    }
}

void brf_800CE840(work, idx, mode, delta)
Work *work;
int idx;
int mode;
int delta;
{
    if (work->field_28C[idx].y0 < -104)
    {
        switch (mode)
        {
        case 1:
            work->field_AD7C += delta;
            break;
        case 2:
            work->field_AD88 += delta;
            break;
        case 3:
            work->field_AD94 += delta;
            break;
        }
    }
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CE8E8.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CE9A0.s")

void brf_800CE798();

void brf_800CEA58(work)
Work *work;
{
    switch (work->field_AD9C)
    {
    case 1:
        brf_800CE648(work);
        break;
    case 0:
        brf_800CE6F0(work);
        break;
    case 2:
        brf_800CE840(work);
        break;
    case 3:
        brf_800CE798(work);
        break;
    }
}
void brf_800CE8E8();
void brf_800CE2F8(Work *work);
void brf_800CE9A0(Work *work);

void brf_800CEAF4(work)
Work *work;
{
    switch (work->field_ADA8)
    {
    case 4:
        brf_800CE8E8(work);
        break;
    case 5:
        brf_800CE9A0(work);
        break;
    }
}
void brf_800CE430();

void brf_800CEB4C(Work *work, int a1, int a2)
{
    brf_800CE430(work, a2);

    switch (work->field_ADAC)
    {
    case 0:
        break;
    case 1:
        brf_800CEAF4(work, a2, 1);
        break;
    case 2:
        brf_800CEAF4(work, a2, 2);
        break;
    default:
        brf_800CEAF4(work, a2, 3);
        break;
    }

    switch (work->field_ADA0)
    {
    case 0:
        break;
    case 1:
        brf_800CEA58(work, a1, a2, 1);
        break;
    case 2:
        brf_800CEA58(work, a1, a2, 2);
        break;
    default:
        brf_800CEA58(work, a1, a2, 3);
        break;
    }
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CEC68.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CECE4.s")
void brf_800CE1C4(Work *work);

void brf_800CF22C(work, a1)
Work *work;
int a1;
{
    unsigned short press = work->field_AD00->press;

    if (press & 0x2000)
    {
        work->field_AD9C = 0;
        work->field_ADA0 = 1;
    }
    else if (press & 0x8000)
    {
        work->field_AD9C = 1;
        work->field_ADA0 = 1;
    }
    else if (press & 0x1000)
    {
        work->field_AD9C = 2;
        work->field_ADA0 = 1;
    }
    else if (press & 0x4000)
    {
        work->field_AD9C = 3;
        work->field_ADA0 = 1;
    }

    if (press & 0x10)
    {
        work->field_ADA8 = 4;
        work->field_ADAC = 1;
    }
    else if (press & 0x80)
    {
        work->field_ADA8 = 5;
        work->field_ADAC = 1;
    }

    if (work->field_ADA0 != 0 || work->field_ADAC != 0)
    {
        brf_800CEB4C(work, 0, 1);
    }

    if (a1 == 2)
    {
        brf_800CE1C4(work);
    }
    else if (a1 == 3)
    {
        brf_800CE2F8(work);
    }
}

void brf_800CF354(Work *work)
{
    if (work->field_AD00->press != 0)
    {
        work->field_ADA4 = 1;
        brf_800CF22C(work);
    }
}
void brf_800CC190(Work *work);
void brf_800CC388(Work *work);
void brf_800CECE4(Work *work);

void brf_800CF394(Work *work, int a1)
{
    unsigned short press = work->field_AD00->press;

    if (a1)
    {
        if (press & 0x20)
        {
            work->field_ADA4 = 1;
            brf_800CC190(work);
            GM_SeSet2(0, 0x3F, 0xB0);
        }
        else if (press & 0xFFFF)
        {
            work->field_ADA4 = 3;
            brf_800CECE4(work);
        }
    }
    else
    {
        if (press & 0x20)
        {
            work->field_ADA4 = 3;
            brf_800CC388(work);
            GM_SeSet2(0, 0x3F, 0xB0);
        }
        else if (press & 0xFFFF)
        {
            work->field_ADA4 = 2;
            brf_800CECE4(work);
        }
    }
}
void brf_800CC28C(Work *work);

void brf_800CF430(Work *work)
{
    unsigned short press = work->field_AD00->press;

    if (press & 0x20)
    {
        work->field_ADA4 = 2;
        brf_800CC28C(work);
        GM_SeSet2(0, 0x3F, 0xB0);
    }
    else if (press & 0xFFFF)
    {
        work->field_ADA4 = 1;
        brf_800CECE4(work);
    }
}
void brf_800CDAEC();

void brf_800CF4A0(Work *work, int a, int b, int c, int d, int e, int f)
{
    brf_800CDAEC(work->field_28C, e, f, a, b, d, c);
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CF4E0.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CF5A8.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D0234.s")
void brf_800D1764(Work *work)
{
    if (work->field_AD34 < 0xBE)
    {
        brf_800CE8E8(work, 1, 1);
    }
    else if (work->field_AD34 == 0xBE)
    {
        work->field_ADB8 = 0;
        work->field_ADBC = 1;
    }
    brf_800CE2F8(work);
    work->field_AD34++;
}
void brf_800D17E8(Work *work, int idx1, int idx2)
{
    POLY_FT4 *base = work->field_28C;
    int v = work->field_AD3C << 2;

    setRGB0(&base[idx1], v, v, v);
    setRGB0(&base[idx2], v, v, v);
}
void brf_800D1838(Work *work)
{
    int n = work->field_AD3C - 0x20;
    int i;

    for (i = 0; i < n; i++)
    {
        work->field_A597[i + 0xF] = 2;
        if (work->field_A9B6[i + 0xF] != 0)
        {
            GM_SeSet2(0, 0x30, 0xB6);
        }
    }
}
void brf_800D18D8(Work *work, int a1, int a2, int a3)
{
    int diff = work->field_AD3C - a1;
    int i;

    for (i = 0; i < 0x334; i++)
    {
        work->field_A597[i + 0xF] = 0;
    }

    for (i = 0; i < 0x11; i++)
    {
        work->field_A597[i + 0xF] = 2;
    }

    for (i = a2; i < a3; i++)
    {
        work->field_A597[i] = 2;
    }

    for (i = 0; i < diff; i++)
    {
        work->field_A597[i + a3] = 2;
        if (work->field_A9B6[i + a3] != 0)
        {
            GM_SeSet2(0, 0x30, 0xB6);
        }
    }
}
void brf_800D1A04(Work *work, int a1, int a2)
{
    int i;

    for (i = 0; i < 0x335; i++)
    {
        work->field_A597[i + 0xF] = 0;
    }

    for (i = 0; i < 0x11; i++)
    {
        work->field_A597[i + 0xF] = 2;
    }

    for (i = a1; i < a2; i++)
    {
        work->field_A597[i] = 2;
        brf_800CD870(work, i);
    }
}
void brf_800D1AD8(Work *work)
{
    int v = work->field_AD3C;
    int i;

    if (v < 0x3E9)
    {
        return;
    }

    if (v < 0x409)
    {
        POLY_FT4 *base = work->field_28C;
        int c = 0x80 - ((v - 0x3E8) << 2);

        for (i = 0; i < 0x335; i++)
        {
            work->field_A597[i + 0xF] = 0;
        }

        for (i = 0xD; i < 0x20; i++)
        {
            work->field_A597[i] = 2;
            setRGB0(&base[i], c, c, c);
        }

        for (i = 0x2E6; i < 0x344; i++)
        {
            work->field_A597[i] = 2;
            setRGB0(&base[i], c, c, c);
        }
    }
    else
    {
        for (i = 0; i < 0x335; i++)
        {
            work->field_A597[i + 0xF] = 0;
        }
    }
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D1BDC.s")
void brf_800D2E70(Work *work)
{
    POLY_FT4 *base = work->field_28C;
    int x = 0x7F - work->field_AD34 * 3;

    base[3].y0 = -0x96;
    base[3].y1 = -0x96;
    base[3].y2 = 0x69;
    base[3].y3 = 0x69;
    base[3].x0 = x;
    base[3].x1 = x + 0xFE;
    base[3].x2 = x;
    base[3].x3 = x + 0xFE;
    work->field_AD34++;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D2ED0.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D30A0.s")
void brf_800D39F0(Work *work, POLY_FT4 *a1, POLY_FT4 *a2)
{
    int v = work->field_AD30 << 2;

    setRGB0(a1, v, v, v);
    setRGB0(a2, v, v, v);
    work->field_AD30++;
}
void brf_800D3A30(Work *work)
{
    POLY_FT4 *base = work->field_28C;
    int c = 0x80 - (work->field_AD30 << 2);
    int i;

    setRGB0(&base[4], c, c, c);
    setRGB0(&base[5], c, c, c);
    for (i = 6; i < 22; i++)
    {
        work->field_A597[i] = 2;
        setRGB0(&base[i], c, c, c);
    }
    for (i = 180; i < 291; i++)
    {
        work->field_A597[i] = 2;
        setRGB0(&base[i], c, c, c);
    }
    work->field_AD30++;
}
void brf_800D3AF0(Work *work)
{
    int n = work->field_AD3C;
    int i;

    for (i = 0; i < n; i++)
    {
        work->field_A597[i + 6] = 2;
        if (work->field_A9B6[i + 6] != 0)
        {
            GM_SeSet2(0, 0x30, 0xB6);
        }
    }
}
void brf_800D3B8C(Work *work, int a1, int a2, int a3)
{
    int diff = work->field_AD3C - a1;
    int i;

    for (i = 0; i < 0x11D; i++)
    {
        work->field_A597[i + 6] = 0;
    }

    for (i = 0; i < 0x10; i++)
    {
        work->field_A597[i + 6] = 2;
    }

    for (i = a2; i < a3; i++)
    {
        work->field_A597[i] = 2;
    }

    for (i = 0; i < diff; i++)
    {
        work->field_A597[i + a3] = 2;
        if (work->field_A9B6[i + a3] != 0)
        {
            GM_SeSet2(0, 0x30, 0xB6);
        }
    }
}
void brf_800D3CB8(Work *work, int a1, int a2)
{
    int i;

    for (i = 0; i < 0x11D; i++)
    {
        work->field_A597[i + 6] = 0;
    }

    for (i = 0; i < 0x10; i++)
    {
        work->field_A597[i + 6] = 2;
    }

    for (i = a1; i < a2; i++)
    {
        work->field_A597[i] = 2;
        brf_800CD870(work, i);
    }
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D3D8C.s")
extern int brf_dword_800C37D4;

void brf_800D45C4(Work *work)
{
    if (work->field_AD38 < 0x1f4)
    {
        int mul = 0x2ee - work->field_AD38;
        brf_800CDAEC(work->field_28C, 6, &brf_dword_800C37D4, 0, 0x5a, mul, 0xfa);
    }
    else if (work->field_AD38 == 0x1f4)
    {
        work->field_ADB8 = 0;
        work->field_ADBC = 1;
    }
    work->field_AD38++;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D4664.s")
void brf_800D486C(Work *work, POLY_FT4 *a1, POLY_FT4 *a2)
{
    int v = work->field_AD30 << 2;

    setRGB0(a1, v, v, v);
    setRGB0(a2, v, v, v);
    work->field_AD30++;
}
void brf_800D48AC(Work *work)
{
    POLY_FT4 *base = work->field_28C;
    int c = 0x80 - (work->field_AD30 << 2);
    int i;

    setRGB0(&base[2], c, c, c);
    setRGB0(&base[3], c, c, c);
    setRGB0(&base[7], c, c, c);
    setRGB0(&base[8], c, c, c);
    for (i = 9; i < 38; i++)
    {
        setRGB0(&base[i], c, c, c);
    }
    work->field_AD30++;
}
void brf_800D493C(Work *work)
{
    work->field_A597[work->field_AD34 + 9] = 2;
    if (work->field_A9B6[work->field_AD34 + 9] != 0)
    {
        GM_SeSet2(0, 0x30, 0xB6);
    }
    work->field_AD34++;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D49B8.s")
void brf_800D5CC4(Work *work)
{
    POLY_FT4 *base = work->field_28C;
    int v = work->field_AD30;

    if (v < 0x11)
    {
        int c;
        v <<= 3;
        c = 0x80 - v;
        setRGB0(&base[0], c, c, c);
        setRGB0(&base[1], c, c, c);
        setRGB0(&base[2], c, c, c);
        setRGB0(&base[3], v, v, v);
    }
    work->field_AD30++;
}
void brf_800D5D30(Work *work)
{
    POLY_FT4 *base = work->field_28C;
    int v = work->field_AD30;

    if (v < 0x11)
    {
        int c;
        v <<= 3;
        c = 0x80 - v;
        setRGB0(&base[3], c, c, c);
        setRGB0(&base[4], v, v, v);
        setRGB0(&base[5], v, v, v);
        setRGB0(&base[6], v, v, v);
    }
    work->field_AD30++;
}
void brf_800D5D9C(Work *work, POLY_FT4 *a1, POLY_FT4 *a2)
{
    int v = work->field_AD30 << 2;

    setRGB0(a1, v, v, v);
    setRGB0(a2, v, v, v);
    work->field_AD30++;
}
void brf_800D5DDC(Work *work)
{
    POLY_FT4 *base = work->field_28C;
    int c = 0x80 - (work->field_AD30 << 2);
    int i;

    setRGB0(&base[10], c, c, c);
    setRGB0(&base[11], c, c, c);
    for (i = 12; i < 20; i++)
    {
        setRGB0(&base[i], c, c, c);
    }
    work->field_AD30++;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D5E54.s")
void brf_800D68D0(Work *work)
{
    POLY_FT4 *base = work->field_28C;
    int v = work->field_AD30;

    if (v < 0x11)
    {
        int c;
        v <<= 3;
        c = 0x80 - v;
        setRGB0(&base[0], c, c, c);
        setRGB0(&base[1], c, c, c);
        setRGB0(&base[2], c, c, c);
        setRGB0(&base[3], v, v, v);
    }
    work->field_AD30++;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D693C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D6F98.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D75F0.s")
void brf_800D8274(Work *work)
{
    int v = work->field_AD3C;
    POLY_FT4 *base = work->field_28C;

    if (v < 0x258)
    {
        if ((v & 3) == 0)
        {
            base[4].x0--;
            base[4].x1--;
            base[4].x2--;
            base[4].x3--;
        }
        if (work->field_AD3C % 3 == 0)
        {
            base[5].x0--;
            base[5].x1--;
            base[5].x2--;
            base[5].x3--;
        }
    }
    else if (v == 0x258)
    {
        work->field_ADB8 = 0;
        work->field_ADBC = 1;
    }
    else if (v < 0x320)
    {
    }
    else if (v < 0x578)
    {
        if ((v & 3) == 0)
        {
            base[4].x0++;
            base[4].x1++;
            base[4].x2++;
            base[4].x3++;
        }
        if (work->field_AD3C % 3 == 0)
        {
            base[5].x0++;
            base[5].x1++;
            base[5].x2++;
            base[5].x3++;
        }
    }
    else if (v == 0x578)
    {
        work->field_ADB8 = 0;
        work->field_ADBC = 1;
    }
    else if (v == 0x640)
    {
        work->field_AD3C = 0;
    }

    work->field_AD3C++;
}
void brf_800D8420(Work *work)
{
    POLY_FT4 *base = work->field_28C;
    int v = work->field_AD38;

    if (v < 0x21)
    {
        int c = v << 2;
        setRGB0(&base[8], c, c, c);
        setRGB0(&base[9], c, c, c);
        setRGB0(&base[10], c, c, c);
        setRGB0(&base[11], c, c, c);
        setRGB0(&base[12], c, c, c);
        setRGB0(&base[13], c, c, c);
    }
    work->field_AD38++;
}
void brf_800D849C(Work *work)
{
    POLY_FT4 *base = work->field_28C;
    int v = work->field_AD38;

    if (v < 0x21)
    {
        int c = 0x80 - (v << 2);
        int i;
        for (i = 8; i < 14; i++)
        {
            setRGB0(&base[i], c, c, c);
        }
        for (i = 16; i < 28; i++)
        {
            setRGB0(&base[i], c, c, c);
            work->field_A597[i] = 2;
        }
    }
    work->field_AD38++;
}
void brf_800D853C(Work *work)
{
    POLY_FT4 *base = work->field_28C;
    int v = work->field_AD30;

    if (v < 0x11)
    {
        int c;
        v <<= 3;
        c = 0x80 - v;
        setRGB0(&base[0], c, c, c);
        setRGB0(&base[1], c, c, c);
        setRGB0(&base[2], c, c, c);
        setRGB0(&base[3], v, v, v);
    }
    work->field_AD30++;
}
void brf_800D85A8(Work *work)
{
    POLY_FT4 *base = work->field_28C;
    int v = work->field_AD30;

    if (v < 0x11)
    {
        int v8 = v << 3;
        int c = 0x80 - v8;
        setRGB0(&base[0], v8, v8, v8);
        setRGB0(&base[1], v8, v8, v8);
        setRGB0(&base[2], v8, v8, v8);
        setRGB0(&base[3], c, c, c);
    }
    work->field_AD30++;
}
void brf_800D8614(Work *work)
{
    POLY_FT4 *base = work->field_28C;
    int v = work->field_AD30;

    if (v < 0xD)
    {
        int q = (v << 7) / 12;
        int c = 0x80 - q;
        setRGB0(&base[14], c, c, c);
        setRGB0(&base[15], c, c, c);
        setRGB0(&base[7], q, q, q);
    }
    work->field_AD30++;
}
void brf_800D8690(Work *work)
{
    int n = work->field_AD38;
    int i;

    for (i = 0; i < n; i++)
    {
        work->field_A597[i + 0x10] = 2;
        if (work->field_A9B6[i + 0x10] != 0)
        {
            GM_SeSet2(0, 0x30, 0xB6);
        }
    }
}
void brf_800D872C(Work *work, int a1, int a2, int a3)
{
    int diff = work->field_AD38 - a1;
    int i;

    for (i = 0; i < 0x29C; i++)
    {
        work->field_A597[i + 0x10] = 0;
    }

    for (i = 0; i < 0xC; i++)
    {
        work->field_A597[i + 0x10] = 2;
    }

    for (i = a2; i < a3; i++)
    {
        work->field_A597[i] = 2;
    }

    for (i = 0; i < diff; i++)
    {
        work->field_A597[i + a3] = 2;
        if (work->field_A9B6[i + a3] != 0)
        {
            GM_SeSet2(0, 0x30, 0xB6);
        }
    }
}
void brf_800D8858(Work *work, int a1, int a2)
{
    int i;

    for (i = 0; i < 0x29C; i++)
    {
        work->field_A597[i + 0x10] = 0;
    }

    for (i = 0; i < 0xC; i++)
    {
        work->field_A597[i + 0x10] = 2;
    }

    for (i = a1; i < a2; i++)
    {
        work->field_A597[i] = 2;
        brf_800CD870(work, i);
    }
}
void brf_800D892C(Work *work)
{
    POLY_FT4 *base = work->field_28C;
    int i;

    for (i = 0; i < 0x29C; i++)
    {
        work->field_A597[i + 0x10] = 0;
    }

    for (i = 0; i < 0xC; i++)
    {
        work->field_A597[i + 0x10] = 2;
    }

    if (work->field_AD38 < 0x385)
    {
        for (i = 0x250; i < 0x2AC; i++)
        {
            work->field_A597[i] = 2;
        }
    }
    else if (work->field_AD38 < 0x3A5)
    {
        int c = 0x80 - ((work->field_AD38 - 0x384) << 2);

        for (i = 0x250; i < 0x2AC; i++)
        {
            setRGB0(&base[i], c, c, c);
            work->field_A597[i] = 2;
        }
    }
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D8A24.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DA04C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DA3A8.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DA4E8.s")
void brf_800DA638(Work *work, POLY_FT4 *poly)
{
    if (work->field_AD34 % 4 == 0)
    {
        poly->y0 += 12;
        poly->y1 += 12;
    }
    else if (work->field_AD34 % 4 == 1)
    {
        poly->y0 -= 12;
        poly->y1 -= 12;
    }
    else if (work->field_AD34 % 4 == 2)
    {
        poly->y0 -= 12;
        poly->y1 -= 12;
    }
    else if (work->field_AD34 % 4 == 3)
    {
        poly->y0 += 12;
        poly->y1 += 12;
    }
    work->field_AD34++;
}
void brf_800DA6E4(int a, POLY_FT4 *poly)
{
    poly->y0 += 12;
    poly->y1 += 12;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DA700.s")
void brf_800DCAA8(Work *work)
{
    if (work->field_AD34 % 3 == 0)
    {
        POLY_FT4 *base = work->field_28C;
        int i;
        for (i = 0; i < 8; i++)
        {
            base[i].y0++;
            base[i].y1++;
            base[i].y2++;
            base[i].y3++;
        }
    }
    work->field_AD34++;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DCB44.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DCD70.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DCED4.s")
extern int brf_dword_800C4CB0;

void brf_800DD6DC(Work *work)
{
    work->field_AD28++;
    if (work->field_AD28 != work->field_AD54)
    {
        return;
    }
    if (work->field_AD20 == -1)
    {
        return;
    }

    work->field_AD5C = 1;
    work->field_AD20 = work->field_AD58;
    work->field_AD54 = ((BrfKeyframe **)&brf_dword_800C4CB0)[work->field_A588][work->field_AD50].field_0;
    work->field_AD58 = ((BrfKeyframe **)&brf_dword_800C4CB0)[work->field_A588][work->field_AD50].field_2;
    work->field_AD50++;
}
void brf_800DD77C(Work *work)
{
    int press = work->field_AD00->press;

    if (work->field_ADC4 != 1 && (press & 0x40) && work->field_AD28 >= 0x33)
    {
        work->field_AD20 = -1;
        work->field_AD5C = 1;
    }
}
void brf_800DD7C8(POLY_FT4 *p, int scale)
{
    p->r0 = p->r0 * scale / 128;
    p->g0 = p->g0 * scale / 128;
    p->b0 = p->b0 * scale / 128;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DD830.s")
extern const char brf_dword_800E23E4[];

void brf_800DDBC8(Work *work)
{
    int i;

    for (i = 0; i < work->field_AD14; i++)
    {
        GV_Free(work->field_AD1C[i]);
    }
    printf((char *)brf_dword_800E23E4);
}

#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DDC40.s")
void brf_800DDC40(Work *work); // Act

void brf_800DDCA8(Work *work)
{
    void *p;

    p = work->field_28;
    if (p)
    {
        DG_DequeuePrim(p);
        DG_FreePrim(p);
    }
    p = work->field_2C;
    if (p)
    {
        DG_DequeuePrim(p);
        DG_FreePrim(p);
    }
    p = work->field_20;
    if (p)
    {
        DG_DequeuePrim(p);
        DG_FreePrim(p);
    }
    p = work->field_24;
    if (p)
    {
        DG_DequeuePrim(p);
        DG_FreePrim(p);
    }
    p = work->field_30;
    if (p)
    {
        DG_DequeuePrim(p);
        DG_FreePrim(p);
    }
    brf_800DDBC8(work);
}
void brf_800DDCA8(Work *work); // Die

void brf_800DDD78(int a0, POLY_FT4 *poly, int x0, int y0, int x1, int y2, int abe)
{
    setPolyFT4(poly);
    setRGB0(poly, 0x80, 0x80, 0x80);
    poly->x0 = x0;
    poly->y0 = y0;
    poly->y1 = y0;
    poly->x2 = x0;
    poly->x1 = x1;
    poly->y2 = y2;
    poly->x3 = x1;
    poly->y3 = y2;
    SetSemiTrans(poly, abe);
}
void brf_800DDDE8(int a0, POLY_FT4 *poly, int x0, int y0, int x1, int y2, int abe)
{
    setPolyFT4(poly);
    setRGB0(poly, 0xFF, 0xD0, 0xD0);
    poly->x0 = x0;
    poly->y0 = y0;
    poly->y1 = y0;
    poly->x2 = x0;
    poly->x1 = x1;
    poly->y2 = y2;
    poly->x3 = x1;
    poly->y3 = y2;
    SetSemiTrans(poly, abe);
}
void brf_800DDE5C(int prim, int tex_id, POLY_FT4 *poly, int x0, int y0, int x1, int y2, int abe, int orient, int use_dg)
{
    DG_TEX *tex;

    brf_800DDD78(prim, poly, x0, y0, x1, y2, abe);
    if (!use_dg)
    {
        tex = (DG_TEX *)brf_800CABF4(prim, tex_id);
    }
    else
    {
        tex = DG_GetTexture(tex_id);
    }

    switch (orient)
    {
    case 0:
        {
            int u = tex->off_x, w = tex->w, v = tex->off_y, h = tex->h;
            poly->u0 = u;
            poly->v0 = v;
            poly->u1 = u + w + 1;
            poly->v1 = v;
            poly->u2 = u;
            poly->v2 = v + h + 1;
            poly->u3 = u + w + 1;
            poly->v3 = v + h + 1;
        }
        break;
    case 1:
        {
            int u = tex->off_x, w = tex->w, v = tex->off_y, h = tex->h;
            poly->u0 = u;
            poly->v0 = v;
            poly->u1 = u + w + 1;
            poly->v1 = v;
            poly->u2 = u;
            poly->v2 = v + h;
            poly->u3 = u + w + 1;
            poly->v3 = v + h;
        }
        break;
    case 2:
        {
            int u = tex->off_x, w = tex->w, v = tex->off_y, h = tex->h;
            poly->u0 = u;
            poly->v0 = v;
            poly->u1 = u + w;
            poly->v1 = v;
            poly->u2 = u;
            poly->v2 = v + h + 1;
            poly->u3 = u + w;
            poly->v3 = v + h + 1;
        }
        break;
    default:
        return;
    }

    poly->tpage = tex->tpage;
    poly->clut = tex->clut;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DE004.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DE0F4.s")
void brf_800DE270(int a0, POLY_F4 *poly, int x0, int y0, int x1, int y2, int abe, int gray)
{
    setPolyF4(poly);
    poly->x0 = x0;
    poly->y0 = y0;
    poly->y1 = y0;
    poly->x2 = x0;
    setRGB0(poly, gray, gray, gray);
    poly->x1 = x1;
    poly->y2 = y2;
    poly->x3 = x1;
    poly->y3 = y2;
    SetSemiTrans(poly, abe);
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DE2E0.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DECF8.s")

void brf_800DE2E0(Work *work);
void brf_800DECF8(Work *work, int a1);

int brf_800DFCF8(Work *work, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9) // GetResources
{
    work->field_AD10 = p2;
    work->field_AD0C = (int *)p3;
    work->field_AD00 = &GV_PadData[2];
    work->field_AD04 = p1;
    work->field_AD28 = 0;
    work->field_AD5C = 0;
    work->field_ADB0 = 0;
    work->field_ADB8 = 0x64;
    work->field_ADC4 = 0;
    GM_CurrentMap = p1;
    work->field_A588 = p5;
    work->field_AD08 = (void *)p4;
    work->field_AD14 = p7;
    work->field_AD18 = (int *)p8;
    work->field_AD1C = (void **)p9;
    brf_800DE2E0(work);
    brf_800DECF8(work, p5);
    return 0;
}

void *NewBriefingGraph(int arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, brf_800DDC40, brf_800DDCA8, "b_graph.c");
        if (brf_800DFCF8(work, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }
    return (void *)work;
}
