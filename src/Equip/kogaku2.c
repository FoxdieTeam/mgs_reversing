#include "actor.h"
#include "kogaku2.h"

extern void EQ_InvisibleUnit_80060E68(int param_1, int param_2, int param_3);
extern void DG_WriteObjPacketUV_8001A774(int param_1, int param_2);


#pragma INCLUDE_ASM("asm/Equip/kogaku2_tpage_uv_update_80060F98.s")
#pragma INCLUDE_ASM("asm/Equip/kogaku2_tpage_uv_rgb_update_800610A4.s")
#pragma INCLUDE_ASM("asm/Equip/kogaku2_update_prims1_80061204.s")
#pragma INCLUDE_ASM("asm/Equip/kogaku2_update_prims2_800612BC.s")

void kogaku2_kill_helper_80061384(int param_1)
{
    int iVar1;
    int iVar2;
    int iVar3;

    iVar1 = **(int **)(param_1 + 0x20);
    iVar2 = iVar1 + 0x48;
    iVar3 = (int) *(short *)(iVar1 + 0x2e);
    *(unsigned int *)(iVar1 + 0x28) = (*(unsigned int *)(iVar1 + 0x28) & 0x80) | (*(unsigned int *)(param_1 + 0x28) & 0xffffff7f);
    while (0 < iVar3)
    {
        DG_WriteObjPacketUV_8001A774(iVar2, 0);
        DG_WriteObjPacketUV_8001A774(iVar2, 1);
        iVar3 = iVar3 + -1;
        iVar2 = iVar2 + 0x5c;
    }
    return;
}

#pragma INCLUDE_ASM("asm/Equip/kogaku2_act_800613FC.s")

void kogaku2_kill_80061508(int param_1)
{
    kogaku2_kill_helper_80061384(param_1);
}

#pragma INCLUDE_ASM("asm/Equip/kogaku2_act_helper_80061528.s")

void kogaku2_act_nullsub_800615F4(void)
{
}

#pragma INCLUDE_ASM("asm/Equip/NewKogaku2_800615FC.s")
#pragma INCLUDE_ASM("asm/Equip/NewKogaku3_80061708.s")
