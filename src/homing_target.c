#include "homing_target.h"
#include "linker.h"

Homing_Target SECTION(".gHomingTargets_800B8230") gHomingTargets_800B8230[8];

void HomingTarget_Clear_All_80032C68()
{
    Homing_Target *pIter; // $v0
    int i; // $v1

    pIter = gHomingTargets_800B8230;
    for ( i = 8; i > 0; --i )
    {
        pIter->field_C_bUsed = 0;
        ++pIter;
    }
}

#pragma INCLUDE_ASM("asm/Game/HomingTarget_Alloc_80032C8C.s")

void HomingTarget_Free_80032CFC(Homing_Target *pTarget)
{
    if ( pTarget )
    {
        pTarget->field_C_bUsed = 0;
    }
}

#pragma INCLUDE_ASM("asm/HomingTarget_1_80032D10.s")
#pragma INCLUDE_ASM("asm/HomingTarget_2_80032EAC.s")
