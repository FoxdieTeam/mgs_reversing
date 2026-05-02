#include "game/game.h"

typedef struct _Work
{
    GV_ACT actor;       // 0x00
    OBJECT body;        // 0x20
    char   pad1[0x196E - 0x20 - sizeof(OBJECT)];
    short  field_196E;
    char   pad2[0x19A8 - 0x196E - sizeof(short)];
    int    field_19A8;
    char   pad2b[0x19B0 - 0x19A8 - sizeof(int)];
    int    field_19B0;
    char   pad3[0x19CC - 0x19B0 - sizeof(int)];
    int    field_19CC;
    int    field_19D0;
} Work;

int Bunsin2_800C8F04(void) 
{
    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C8F0C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C8FF8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C908C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C9120.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C933C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C9514.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C9548.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C9588.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C9978.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C9B38.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800C9BF8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CA8F8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAA78.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAB50.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAC3C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAD28.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAE14.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAF6C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CAFF8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB0A8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB158.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB210.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB2AC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB38C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB444.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB52C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB7A0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CB914.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CBAA4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CBCEC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CBE30.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC080.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC2F8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC434.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC578.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC71C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC7EC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CC90C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CCA4C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CCAF0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CCD18.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CCD40.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CCD74.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CCDBC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CCE34.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CCF8C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD000.s")
int s08b_bunsin2_800CD298(int a, int b, int c)
{
    if (b < a) b = a;
    if (c < b) c = b;
    return c;
}

int s08b_bunsin2_800CD2C0(int a, int b, int c)
{
    if (a < b) b = a;
    if (b < c) c = b;
    return c;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD2E8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD544.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD5AC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD614.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD690.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD770.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD808.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD87C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD8D8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD914.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD95C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD990.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CD9F0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CDA40.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CDB10.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CDB54.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CDBAC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CDDD8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CDE74.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CDF68.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CDFA0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CDFF8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE024.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE064.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE0A4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE180.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE21C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE2E8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE398.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE584.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE800.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE8A0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CE9BC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CEA34.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CEB40.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CECB4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CEE18.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CEE68.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CEEB8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CEF34.s")
int s08b_bunsin2_800CEF94(int *p, int n, int initial)
{
    int sum = 0;
    int i;
    for (i = 0; i < n; i++)
    {
        sum += *p;
        p = (int *)((char *)p + 0x104);
    }
    return sum + initial;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CEFC0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CEFF4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF150.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF254.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF354.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF464.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF54C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF660.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF704.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF880.s")

int s08b_bunsin2_800CF950(void)
{
    return 1;
}

int s08b_bunsin2_800CF958(void)
{
    return 1;
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CF960.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CFA30.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CFA80.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CFB98.s")
extern void s08b_bunsin2_800CEEB8(Work *work, int arg);

void s08b_bunsin2_800CFC64(Work *work)
{
    work->field_19D0++;
    s08b_bunsin2_800CEEB8(work, 500);
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CFC90.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CFCF8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CFD88.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CFDE0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800CFE54.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0004.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0078.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D018C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0200.s")
int s08b_bunsin2_800D0278(Work *work)
{
    if (work->field_19D0 >= 0x79)
    {
        return 1;
    }
    return work->field_19A8;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D02A0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D02E8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0330.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0410.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D044C.s")
int s08b_bunsin2_800D0530(Work *work)
{
    int v;

    v = work->field_19D0;
    work->field_19B0 = 22;
    v++;
    work->field_19D0 = v;
    return v >= 0x1F;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0550.s")
int s08b_bunsin2_800D0688(Work *work)
{
    return work->field_19D0++;
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D06A0.s")

int s08b_bunsin2_800D0720(Work *work)
{
    int val;

    val = work->field_196E;
    return val & 0x1F;
}

#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D072C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0784.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0814.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0864.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D08C8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D093C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D09C4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0A54.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0A90.s")
void s08b_bunsin2_800D0B1C(Work *work)
{
    work->field_19B0 = 7;
    if (work->field_19D0 >= 11)
    {
        work->field_19CC = 5;
        work->field_19D0 = 0;
    }
    else
    {
        work->field_19D0++;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0B4C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0CD8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0D80.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0EB8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0F54.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D0F88.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1014.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D10C4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1138.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D11A8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1218.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D125C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D12A0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D12EC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1348.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D138C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1400.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1514.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1588.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1638.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1738.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D17F8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D195C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1A18.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1AF8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1CF4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1D44.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1DE0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1EC8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D1F9C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2104.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2158.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D21B8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D231C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2420.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2510.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2600.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2860.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D29DC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2AB4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2B24.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2BFC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2D3C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2DB0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2EA0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D2F80.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3064.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D30E0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3160.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D31EC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3394.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3468.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D367C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D37F0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D38F0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D39F8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3A84.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3B00.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3BD4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3C44.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3CCC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3DBC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3EA4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D3F5C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D401C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4128.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D41DC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D42D8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D43D8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4460.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D44D0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D452C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4638.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D468C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D47E0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4884.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4984.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4A34.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4AF4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4BD4.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4C84.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4D18.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4DA8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4E3C.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4ED0.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D4FBC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D53E8.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D5434.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D5498.s")
void s08b_bunsin2_800D54CC(void *arg0)
{
    int i;
    char *p = (char *)arg0;
    for (i = 0; i < 16; i++)
    {
        int *q = *(int **)(p + 0x88);
        *q |= 2;
        p += 0x5C;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D54FC.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D5530.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D5600.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D5734.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D57F0.s")
void s08b_bunsin2_800D5830(Work *work)
{
    GM_FreeObject(&work->body);
}
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D5850.s")
#pragma INCLUDE_ASM("asm/overlays/s08b/s08b_bunsin2_800D594C.s")
