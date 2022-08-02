#include "tenage.h"

#pragma INCLUDE_ASM("asm/tenage_act_800699A4.s") // 1048 bytes

GM_Control* SECTION(".tenage_ctrls_800BDD30") tenage_ctrls_800BDD30[16];
int SECTION(".tenage_ctrls_800BDD30") tenage_ctrls_count_800BDD70;

void GM_ClearBulName_8004FBE4(int idx);

void tenage_kill_80069DBC(Actor_tenage *pActor)
{
    GM_FreeControl_800260CC(&pActor->field_20_ctrl);
    GM_ClearBulName_8004FBE4(pActor->field_20_ctrl.field_30_scriptData);
    GM_FreeObject_80034BF8(&pActor->field_9C_obj);
    if ( pActor->field_120_ctrl_idx >= 0 )
    {
        tenage_ctrls_800BDD30[pActor->field_120_ctrl_idx] = 0;
        tenage_ctrls_count_800BDD70--;
    }
}

#pragma INCLUDE_ASM("asm/tenage_init_helper_80069E28.s") // 60 bytes
#pragma INCLUDE_ASM("asm/tenage_init_helper_80069E64.s") // 428 bytes
#pragma INCLUDE_ASM("asm/NewTenage_8006A010.s") // 240 bytes
#pragma INCLUDE_ASM("asm/sub_8006A100.s") // 40 bytes
#pragma INCLUDE_ASM("asm/NewTenage3_8006A128.s") // 240 bytes
