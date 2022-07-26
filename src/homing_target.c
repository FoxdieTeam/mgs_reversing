#include "homing_target.h"
#include "linker.h"
#include "mts_new.h"

extern const char aHomingTargetOv[];

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

Homing_Target* HomingTarget_Alloc_80032C8C(int a1, int a2)
{
    int pos; // $v1
    Homing_Target* pIter = gHomingTargets_800B8230;
    for ( pos = 8; pos > 0; --pos )
    {
        if ( !pIter->field_C_bUsed )
        {
            break;
        }
        ++pIter;
    }

    if ( !pos )
    {
        mts_printf_8008BBA0(aHomingTargetOv);
        return 0;
        
    }
  
    pIter->field_0 = a1;
    pIter->field_4 = a2;
    pIter->field_8 = 0;
    pIter->field_C_bUsed = 1;
    return pIter;
}

void HomingTarget_Free_80032CFC(Homing_Target *pTarget)
{
    if ( pTarget )
    {
        pTarget->field_C_bUsed = 0;
    }
}

#pragma INCLUDE_ASM("asm/HomingTarget_1_80032D10.s")
#pragma INCLUDE_ASM("asm/HomingTarget_2_80032EAC.s")
