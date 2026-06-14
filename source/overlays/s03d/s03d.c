#include "common.h"
#include "game/game.h"

typedef struct _Work
{
    char            pad_0[0xB6];
    short           field_B6;       /* 0x0B6 */
    char            pad_B8[0xAC8 - 0xB8];
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
    char            pad_AE8[0xB48 - 0xAE8];
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
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D2D84.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D2DBC.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D307C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D311C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3184.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D31F4.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D327C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3310.s")
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
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3508.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3570.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D367C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3724.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3754.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3848.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3984.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3A7C.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3ACC.s")
#pragma INCLUDE_ASM("asm/overlays/s03d/s03d_800D3B5C.s")
