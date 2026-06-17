#include "game/game.h"

typedef struct _Work
{
    GV_ACT  actor;           /* 0x000 */
    char    pad_20[0xACE0];  /* 0x020 */
    GV_PAD *field_AD00;      /* 0xAD00 */
    char    pad_AD04[0x10];  /* 0xAD04 */
    int     field_AD14;      /* 0xAD14 */
    char    pad_AD18[0x4];   /* 0xAD18 */
    void  **field_AD1C;      /* 0xAD1C */
    int     field_AD20;      /* 0xAD20 */
    char    pad_AD24[0x4];   /* 0xAD24 */
    int     field_AD28;      /* 0xAD28 */
    char    pad_AD2C[0x4];   /* 0xAD2C */
    int     field_AD30;      /* 0xAD30 */
    int     field_AD34;      /* 0xAD34 */
    char    pad_AD38[0x4];   /* 0xAD38 */
    int     field_AD3C;      /* 0xAD3C */
    char    pad_AD40[0x1C];  /* 0xAD40 */
    int     field_AD5C;      /* 0xAD5C */
    char    pad_AD60[0x44];  /* 0xAD60 */
    int     field_ADA4;      /* 0xADA4 */
    int     field_ADA8;      /* 0xADA8 */
    char    pad_ADAC[0x18];  /* 0xADAC */
    char    field_ADC4;      /* 0xADC4 */
    char    pad_ADC5[0x3];   /* 0xADC5 */
} Work;

#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CABF4.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CAC7C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CAD24.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CADD4.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CAE84.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CB23C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CB5F4.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CBA84.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CBB68.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CBC04.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CBCB0.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CBD5C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CBDC8.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CBE34.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CBF48.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CC070.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CC150.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CC190.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CC28C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CC388.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CC480.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CC560.s")
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
    POLY_FT4 *base = (POLY_FT4 *)((char *)work + 0x28C);

    base[idx].y0 -= 12;
    base[idx].y1 -= 12;
    base[idx].y2 -= 12;
    base[idx].y3 -= 12;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CD8B8.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CD958.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CDA10.s")
void brf_800CDAA8(Work *work, int idx)
{
    int v = work->field_AD30;
    POLY_FT4 *base = (POLY_FT4 *)((char *)work + 0x28C);

    if (v < 0x11)
    {
        v <<= 3;
        base[idx].r0 = v;
        base[idx].g0 = v;
        base[idx].b0 = v;
    }
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CDAEC.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CDC8C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CDDD4.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CDF34.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CDFE4.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CE1C4.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CE2F8.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CE430.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CE648.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CE6F0.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CE798.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CE840.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CE8E8.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CE9A0.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CEA58.s")
void brf_800CE8E8(Work *work);
void brf_800CE9A0(Work *work);

void brf_800CEAF4(Work *work)
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
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CEB4C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CEC68.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CECE4.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CF22C.s")
void brf_800CF22C(Work *work);

void brf_800CF354(Work *work)
{
    if (work->field_AD00->press != 0)
    {
        work->field_ADA4 = 1;
        brf_800CF22C(work);
    }
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CF394.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CF430.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CF4A0.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CF4E0.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800CF5A8.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D0234.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D1764.s")
void brf_800D17E8(Work *work, int idx1, int idx2)
{
    POLY_FT4 *base = (POLY_FT4 *)((char *)work + 0x28C);
    int v = work->field_AD3C << 2;

    base[idx1].r0 = v;
    base[idx1].g0 = v;
    base[idx1].b0 = v;
    base[idx2].r0 = v;
    base[idx2].g0 = v;
    base[idx2].b0 = v;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D1838.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D18D8.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D1A04.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D1AD8.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D1BDC.s")
void brf_800D2E70(Work *work)
{
    POLY_FT4 *base = (POLY_FT4 *)((char *)work + 0x28C);
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

    a1->r0 = v;
    a1->g0 = v;
    a1->b0 = v;
    a2->r0 = v;
    a2->g0 = v;
    a2->b0 = v;
    work->field_AD30++;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D3A30.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D3AF0.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D3B8C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D3CB8.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D3D8C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D45C4.s")
void brf_800D486C(Work *work, POLY_FT4 *a1, POLY_FT4 *a2)
{
    int v = work->field_AD30 << 2;

    a1->r0 = v;
    a1->g0 = v;
    a1->b0 = v;
    a2->r0 = v;
    a2->g0 = v;
    a2->b0 = v;
    work->field_AD30++;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D48AC.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D493C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D49B8.s")
void brf_800D5CC4(Work *work)
{
    POLY_FT4 *base = (POLY_FT4 *)((char *)work + 0x28C);
    int v = work->field_AD30;

    if (v < 0x11)
    {
        int c;
        v <<= 3;
        c = 0x80 - v;
        base[0].r0 = c;
        base[0].g0 = c;
        base[0].b0 = c;
        base[1].r0 = c;
        base[1].g0 = c;
        base[1].b0 = c;
        base[2].r0 = c;
        base[2].g0 = c;
        base[2].b0 = c;
        base[3].r0 = v;
        base[3].g0 = v;
        base[3].b0 = v;
    }
    work->field_AD30++;
}
void brf_800D5D30(Work *work)
{
    POLY_FT4 *base = (POLY_FT4 *)((char *)work + 0x28C);
    int v = work->field_AD30;

    if (v < 0x11)
    {
        int c;
        v <<= 3;
        c = 0x80 - v;
        base[3].r0 = c;
        base[3].g0 = c;
        base[3].b0 = c;
        base[4].r0 = v;
        base[4].g0 = v;
        base[4].b0 = v;
        base[5].r0 = v;
        base[5].g0 = v;
        base[5].b0 = v;
        base[6].r0 = v;
        base[6].g0 = v;
        base[6].b0 = v;
    }
    work->field_AD30++;
}
void brf_800D5D9C(Work *work, POLY_FT4 *a1, POLY_FT4 *a2)
{
    int v = work->field_AD30 << 2;

    a1->r0 = v;
    a1->g0 = v;
    a1->b0 = v;
    a2->r0 = v;
    a2->g0 = v;
    a2->b0 = v;
    work->field_AD30++;
}
void brf_800D5DDC(Work *work)
{
    POLY_FT4 *base = (POLY_FT4 *)((char *)work + 0x28C);
    int c = 0x80 - (work->field_AD30 << 2);
    int i;

    base[10].r0 = c;
    base[10].g0 = c;
    base[10].b0 = c;
    base[11].r0 = c;
    base[11].g0 = c;
    base[11].b0 = c;
    for (i = 12; i < 20; i++)
    {
        base[i].r0 = c;
        base[i].g0 = c;
        base[i].b0 = c;
    }
    work->field_AD30++;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D5E54.s")
void brf_800D68D0(Work *work)
{
    POLY_FT4 *base = (POLY_FT4 *)((char *)work + 0x28C);
    int v = work->field_AD30;

    if (v < 0x11)
    {
        int c;
        v <<= 3;
        c = 0x80 - v;
        base[0].r0 = c;
        base[0].g0 = c;
        base[0].b0 = c;
        base[1].r0 = c;
        base[1].g0 = c;
        base[1].b0 = c;
        base[2].r0 = c;
        base[2].g0 = c;
        base[2].b0 = c;
        base[3].r0 = v;
        base[3].g0 = v;
        base[3].b0 = v;
    }
    work->field_AD30++;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D693C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D6F98.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D75F0.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D8274.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D8420.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D849C.s")
void brf_800D853C(Work *work)
{
    POLY_FT4 *base = (POLY_FT4 *)((char *)work + 0x28C);
    int v = work->field_AD30;

    if (v < 0x11)
    {
        int c;
        v <<= 3;
        c = 0x80 - v;
        base[0].r0 = c;
        base[0].g0 = c;
        base[0].b0 = c;
        base[1].r0 = c;
        base[1].g0 = c;
        base[1].b0 = c;
        base[2].r0 = c;
        base[2].g0 = c;
        base[2].b0 = c;
        base[3].r0 = v;
        base[3].g0 = v;
        base[3].b0 = v;
    }
    work->field_AD30++;
}
void brf_800D85A8(Work *work)
{
    POLY_FT4 *base = (POLY_FT4 *)((char *)work + 0x28C);
    int v = work->field_AD30;

    if (v < 0x11)
    {
        int v8 = v << 3;
        int c = 0x80 - v8;
        base[0].r0 = v8;
        base[0].g0 = v8;
        base[0].b0 = v8;
        base[1].r0 = v8;
        base[1].g0 = v8;
        base[1].b0 = v8;
        base[2].r0 = v8;
        base[2].g0 = v8;
        base[2].b0 = v8;
        base[3].r0 = c;
        base[3].g0 = c;
        base[3].b0 = c;
    }
    work->field_AD30++;
}
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D8614.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D8690.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D872C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D8858.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D892C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800D8A24.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DA04C.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DA3A8.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DA4E8.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DA638.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DA6E4.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DA700.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DCAA8.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DCB44.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DCD70.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DCED4.s")
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DD6DC.s")
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

#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DDCA8.s")
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
#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DDE5C.s")
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

#pragma INCLUDE_ASM("asm/overlays/brf/brf_800DFCF8.s")
int brf_800DFCF8(Work *work, int, int, int, int, int, int, int, int, int); // GetResources

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
