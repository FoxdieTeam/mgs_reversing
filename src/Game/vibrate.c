#include "linker.h"
#include "vibrate.h"
#include "libgcl/gcl.h"

#pragma INCLUDE_ASM("asm/vibrate_act_helper_8005D358.s") // 76 bytes

int vibrate_act_helper_8005D3A4(int pActor)
{
    GCL_SetArgTop_80020690(*(char **)(pActor + 0x24));

    if (*(int *)(pActor + 0x24) == 0 || GCL_Get_Param_Result_80020AA4() == 0)
    {
        return 0;
    }
    
    *(char *)(pActor + 0x21) = GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
    *(short *)(pActor + 0x22) = GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4()) * 2;
    *(char **)(pActor + 0x24) = GCL_Get_Param_Result_80020AA4();
    
    return 1;
}

#pragma INCLUDE_ASM("asm/vibrate_act_8005D424.s")        // 228 bytes
#pragma INCLUDE_ASM("asm/vibrate_init_8005D508.s")       // 132 bytes
#pragma INCLUDE_ASM("asm/vibrate_init2_8005D58C.s")      // 120 bytes
