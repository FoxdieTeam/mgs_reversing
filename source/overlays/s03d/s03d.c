#include "common.h"
#include "game/game.h"

typedef struct _Work
{
    char            pad_0[0x5A];
    short           field_5A;       /* 0x05A */
    char            pad_5C[0xB6 - 0x5C];
    short           field_B6;       /* 0x0B6 */
    char            pad_B8[0x8E4 - 0xB8];
    short           field_8E4;      /* 0x8E4 */
    char            pad_8E6[0xAC8 - 0x8E6];
    short           field_AC8;      /* 0xAC8 */
    short           field_ACA;      /* 0xACA */
    short           field_ACC;      /* 0xACC */
    char            pad_ACE[0xAD0 - 0xACE];
    int             field_AD0;      /* 0xAD0 */
    char            pad_AD4[0xAD8 - 0xAD4];
    int             field_AD8;      /* 0xAD8 */
    int             field_ADC;      /* 0xADC */
    char            pad_AE0[0xAE6 - 0xAE0];
    short           field_AE6;      /* 0xAE6 */
    char            pad_AE8[0xB08 - 0xAE8];
    signed char     field_B08;      /* 0xB08 */
    char            pad_B09[0xB0B - 0xB09];
    signed char     field_B0B;      /* 0xB0B */
    unsigned char   field_B0C[0xB28 - 0xB0C];   /* 0xB0C */
    int             field_B28;      /* 0xB28 */
    char            pad_B2C[0xB48 - 0xB2C];
    SVECTOR         field_B48;      /* 0xB48 */
    char            pad_B50[0xB5C - 0xB50];
    int             field_B5C;      /* 0xB5C */
    int             field_B60;      /* 0xB60 */
    char            pad_B64[0xB94 - 0xB64];
    unsigned short  field_B94;      /* 0xB94 */
} Work;

extern int s03d_dword_800DC2FC;
extern int s03d_dword_800DC300;
extern SVECTOR s03d_dword_800DC308;

int s03d_800D3184(Work *work);
void s03d_800D367C(Work *work);
void s03d_800D2C68(Work *work);
void s03d_800D3ACC(Work *work);

void s03d_800D2C20(Work *work)
{
    work->field_B5C = s03d_dword_800DC2FC;
    work->field_B48 = s03d_dword_800DC308;
    work->field_B60 = s03d_dword_800DC300;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D2C68.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D2CCC.s")
void s03d_800D2D44(Work *work)
{
    work->field_ACA = 2;
    work->field_ACC = 9;
    work->field_AC8 = 0;
    work->field_AD0 = 0;
    work->field_ADC = 1;
}
void s03d_800D2D68(Work *work)
{
    work->field_AC8 = 0;
    work->field_ACA = 0;
    work->field_ACC = 0;
    work->field_AD0 = 0;
    work->field_ADC = 1;
}
int s03d_800D2D84(SVECTOR *a, SVECTOR *b)
{
    SVECTOR diff;

    GV_SubVec3(b, a, &diff);
    diff.vy = 0;
    return GV_VecDir2(&diff);
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D2DBC.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D307C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D311C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3184.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D31F4.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D327C.s")
int s03d_800D3310(Work *work)
{
    if (work->field_B08 == 2)
    {
        work->field_AD8 |= 0x20000;
    }
    else
    {
        work->field_AD8 |= 0x10000;
    }
    if (work->field_AD0 < 4)
    {
        if ((work->field_AD0 & 1) != 0)
        {
            work->field_AD8 |= 0x40000;
        }
    }
    else if (work->field_AD0 >= 21)
    {
        return 1;
    }
    work->field_AD0++;
    return 0;
}
int s03d_800D3390(Work *work)
{
    work->field_AD8 |= 0x20000;
    if (work->field_AD0 == 0)
    {
        work->field_AD8 |= 0x80000;
    }
    else if (work->field_AD0 == 8)
    {
        return 1;
    }
    work->field_AE6 = work->field_B94;
    work->field_AD0++;
    return 0;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D33E8.s")
int s03d_800D34AC(Work *work)
{
    work->field_AD8 |= 0x10000;
    if (work->field_AD0 == 0)
    {
        work->field_AD8 |= 0x200000;
    }
    else if (work->field_B6 != 0)
    {
        return 1;
    }
    work->field_AE6 = work->field_B94;
    work->field_AD0++;
    return 0;
}
int s03d_800D3508(Work *work)
{
    work->field_AD8 |= 0x10000;
    if (work->field_AD0 < 10)
    {
        if ((work->field_AD0 & 1) == 0)
        {
            work->field_AD8 |= 0x40000;
        }
    }
    else if (work->field_AD0 >= 20)
    {
        return 1;
    }
    work->field_AE6 = work->field_B94;
    work->field_AD0++;
    return 0;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3570.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D367C.s")
void s03d_800D3724(Work *work)
{
    if (work->field_ACC == 0)
    {
        s03d_800D367C(work);
    }
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3754.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3848.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3984.s")
void s03d_800D3A7C(Work *work)
{
    if (work->field_ACC == 13)
    {
        if (s03d_800D3184(work))
        {
            work->field_ACA = 2;
            work->field_ACC = 12;
            work->field_AD0 = 0;
        }
    }
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3ACC.s")
void s03d_800D3B5C(Work *work)
{
    work->field_AE6 = -1;
    work->field_5A = 5;
    work->field_AD8 = 0;
    work->field_B28 = 0xFF;
    if (work->field_AC8 == 0)
    {
        work->field_8E4 = 1;
        s03d_800D3ACC(work);
    }
}
