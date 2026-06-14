#include "common.h"
#include "game/game.h"

typedef struct _Work
{
    char            pad_0[0x20];
    SVECTOR         field_20;       /* 0x020 */
    char            pad_28[0x4C - 0x28];
    MAP            *field_4C;       /* 0x04C */
    char            pad_50[0x5A - 0x50];
    short           field_5A;       /* 0x05A */
    char            pad_5C[0x9C - 0x5C];
    char           *field_9C;       /* 0x09C */
    char            pad_A0[0xB6 - 0xA0];
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
    short           field_AE8;      /* 0xAE8 */
    char            pad_AEA[0xB08 - 0xAEA];
    signed char     field_B08;      /* 0xB08 */
    char            pad_B09[0xB0B - 0xB09];
    signed char     field_B0B;      /* 0xB0B */
    unsigned char   field_B0C[0xB28 - 0xB0C];   /* 0xB0C */
    int             field_B28;      /* 0xB28 */
    char            pad_B2C[0xB48 - 0xB2C];
    SVECTOR         field_B48;      /* 0xB48 */
    char            pad_B50[0xB58 - 0xB50];
    int             field_B58;      /* 0xB58 */
    int             field_B5C;      /* 0xB5C */
    int             field_B60;      /* 0xB60 */
    char            pad_B64[0xB68 - 0xB64];
    SVECTOR         field_B68;      /* 0xB68 */
    int             field_B70;      /* 0xB70 */
    char            pad_B74[0xB94 - 0xB74];
    unsigned short  field_B94;      /* 0xB94 */
} Work;

extern int s03d_dword_800DC2FC;
extern int s03d_dword_800DC300;
extern SVECTOR s03d_dword_800DC308;
extern SVECTOR s03d_dword_800C3B68[];
extern const char s03d_dword_800DBAB0[];
extern int s03d_dword_800DC32C;
void s03d_800D3F14(void *dest, SVECTOR *pos, const char *name, int flag);
void s03d_800D2CCC(Work *work);

int s03d_800D3184(Work *work);
void s03d_800D367C(Work *work);
void s03d_800D2C68(Work *work);
void s03d_800D3ACC(Work *work);
void s03d_800D0C90(Work *work, int arg);
int s03d_800D2DBC(Work *work);

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
int s03d_800D307C(Work *work)
{
    if (work->field_AD0 == 0)
    {
        s03d_800D0C90(work, 0);
        GM_SeSet(&work->field_20, 0x53);
        s03d_800D3F14(work->field_9C + 0x270, &work->field_20, s03d_dword_800DBAB0, 0);
    }
    if (work->field_AD0 < 20)
    {
        work->field_AD8 |= 0x20;
        work->field_AD0++;
        return 0;
    }
    return 1;
}
int s03d_800D311C(Work *work)
{
    if (work->field_AD0 == 0)
    {
        GM_SeSet(&work->field_20, 0x53);
        s03d_800D0C90(work, 0);
    }
    if (work->field_AD0 >= 21)
    {
        return 1;
    }
    work->field_AD0++;
    return 0;
}
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3184.s")
int s03d_800D31F4(Work *work, int range)
{
    SVECTOR local;
    int dx = work->field_B48.vx - work->field_20.vx;
    int dz;

    local.vx = dx;
    dz = work->field_B48.vz - work->field_20.vz;
    local.vz = dz;
    if (-range < dx && dx < range && -range < dz && dz < range)
    {
        return 1;
    }
    work->field_AE6 = GV_VecDir2(&local);
    work->field_AD0++;
    return 0;
}
int s03d_800D327C(Work *work)
{
    s03d_800D2C20(work);
    if (work->field_4C->index != work->field_B60)
    {
        return -1;
    }
    if (work->field_AD0 & 0x10)
    {
        work->field_B70 = HZD_GetAddress(work->field_4C->hzd, &work->field_20, -1);
        if (HZD_ReachTo(work->field_4C->hzd, work->field_B70, work->field_B5C) >= 2)
        {
            return -1;
        }
    }
    return s03d_800D31F4(work, 0x5DC);
}
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
int s03d_800D33E8(Work *work)
{
    work->field_AD8 |= 0x10000;
    if (work->field_AD0 == 30)
    {
        work->field_AD8 |= 0x100000;
        work->field_B68 = s03d_dword_800C3B68[work->field_B08];
    }
    else if (work->field_B6 != 0)
    {
        return 1;
    }
    work->field_AE6 = s03d_800D2D84(&work->field_20, &s03d_dword_800C3B68[work->field_B08]);
    work->field_AD0++;
    return 0;
}
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
void s03d_800D3754(Work *work)
{
    switch (work->field_ACC)
    {
    case 1:
        if (s03d_800D307C(work) != 0)
        {
            s03d_800D2CCC(work);
            if (s03d_dword_800DC32C != 0)
            {
                work->field_AE8 = 0xF6;
            }
            else
            {
                work->field_AE8 = 0xF0;
            }
            work->field_B28 = 0xFF;
        }
        break;
    case 2:
        if (s03d_800D311C(work) != 0)
        {
            work->field_ACA = 3;
            work->field_ACC = 0xD;
            work->field_ADC = 1;
            work->field_AE8 = 0xF0;
            work->field_AC8 = 0;
            work->field_AD0 = 0;
            work->field_B28 = 0xFF;
        }
        break;
    case 3:
        if (s03d_800D311C(work) != 0)
        {
            s03d_800D2CCC(work);
            work->field_AE8 = 0xF0;
            work->field_B28 = 0xFF;
        }
        break;
    }
}
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
