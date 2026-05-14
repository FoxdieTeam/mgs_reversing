#include "common.h"

typedef struct _JeepLiqWork
{
    char pad0[0x3D4];
    int  field_3D4;
    int  field_3D8;
    int  field_3DC;
    int  field_3E0;
    int  field_3E4;
    int  field_3E8;
} JeepLiqWork;

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D6FB8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7114.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7200.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7330.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D769C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D76B0.s")
void s19b_jeep_liq_800D76F8(JeepLiqWork *work, int arg1)
{
    if (work->field_3DC != arg1)
    {
        work->field_3DC = arg1;
        work->field_3D8 = 0;
        work->field_3D4 = 0;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D771C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D77F0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7860.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D797C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D79EC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7A5C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7ACC.s")
void s19b_jeep_liq_800D7B3C(JeepLiqWork *work, int arg1)
{
    if (work->field_3E8 != arg1)
    {
        work->field_3E8 = arg1;
        work->field_3E4 = 0;
        work->field_3E0 = 0;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7B60.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7BB0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7C0C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7CBC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7D68.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7E2C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D7F20.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D8014.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D8044.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D8118.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D81A8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D8250.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D8420.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D8620.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_liq_800D8670.s")
