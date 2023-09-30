#include "libgcl/libgcl.h"

#pragma INCLUDE_ASM("asm/overlays/select/select_800C34F0.s")
#pragma INCLUDE_ASM("asm/overlays/select/select_800C36BC.s")
#pragma INCLUDE_ASM("asm/overlays/select/select_800C3974.s")
#pragma INCLUDE_ASM("asm/overlays/select/select_800C3BB8.s")
#pragma INCLUDE_ASM("asm/overlays/select/select_800C3BF4.s")
#pragma INCLUDE_ASM("asm/overlays/select/select_800C3C28.s")
#pragma INCLUDE_ASM("asm/overlays/select/select_800C3C74.s")
#pragma INCLUDE_ASM("asm/overlays/select/select_800C3CBC.s")
#pragma INCLUDE_ASM("asm/overlays/select/select_800C3D20.s")
#pragma INCLUDE_ASM("asm/overlays/select/select_800C3D84.s")
#pragma INCLUDE_ASM("asm/overlays/select/select_800C4720.s")
#pragma INCLUDE_ASM("asm/overlays/select/select_800C47B4.s")

int select_800C4848(int arg0, int arg1)
{
    if (GCL_GetParam_80020968(arg0 & 0xFF) != 0)
    {
        return GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    return arg1;
}

void select_800C4888(int arg0)
{
    select_800C4848(arg0 & 0xFF, 0);
}

int select_800C48AC(int arg0, int arg1)
{
    unsigned char *temp_v0;

    temp_v0 = (unsigned char *)GCL_GetParam_80020968(arg0 & 0xFF);
    if (temp_v0 != 0)
    {
        return GCL_GetNextInt_800209E8(temp_v0) & 0xFFFF;
    }
    return arg1 & 0xFFFF;
}

#pragma INCLUDE_ASM("asm/overlays/select/select_800C48F0.s")
#pragma INCLUDE_ASM("asm/overlays/select/select_800C4914.s")

int select_800C4D04(int arg0, int arg1, int arg2)
{
    int var_a1;
    int var_a2;

    var_a1 = arg1;
    var_a2 = arg2;
    while (var_a1 > 0)
    {
        var_a1--;
        if (var_a2 == arg0)
        {
            return 1;
        }
        var_a2 += 16;
    }
    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/select/select_800C4D2C.s")

// PSYQ!!!
#pragma INCLUDE_ASM("asm/overlays/select/select_800C4F28.s")
#pragma INCLUDE_ASM("asm/overlays/select/select_800C4F48.s")
#pragma INCLUDE_ASM("asm/overlays/select/select_800C4FDC.s")
#pragma INCLUDE_ASM("asm/overlays/select/select_800C5008.s")
// PSYQ!!!
