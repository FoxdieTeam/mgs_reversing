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
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8724.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D87A4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D88D8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8918.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D899C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8A48.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8A88.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8AAC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8ACC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8AEC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8B54.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8BC8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8CEC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8E10.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8F34.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D8FB0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D902C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D90A8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9148.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D91DC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D92C8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D932C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9390.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9434.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D94C8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9558.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D95FC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D964C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9680.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9704.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D97A8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D985C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9910.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D99C4.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9A30.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9A74.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9AA8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9B38.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9B88.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9C04.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9C90.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800D9EC0.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_spark2_m_800DA0B4.s")

