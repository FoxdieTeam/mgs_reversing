#include "game.h"

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_start_anim_8004E1F4.s")

extern int  GM_PlayerStatus_800ABA50;

extern void GM_ConfigObjectAction_80034CD4( OBJECT *obj, int action_flag, int motion, int interp );

void sub_8004E22C(int param_1, int param_2, int param_3)
{
    if (*(short *)(param_1 + 0xaa) != param_2)
    {
        GM_ConfigObjectAction_80034CD4((OBJECT *)(param_1 + 0x9c), param_2, 0, param_3);
    }
    return;
}
#pragma INCLUDE_ASM("asm/sub_8004E260.s")

int GM_CheckPlayerStatusFlag_8004E29C(int arg0)
{
    return (GM_PlayerStatus_800ABA50 & arg0) != 0;
}

int GM_SetPlayerStatusFlag_8004E2B4(int arg0)
{
    int temp_v0;

    temp_v0 = GM_PlayerStatus_800ABA50 | arg0;
    GM_PlayerStatus_800ABA50 = temp_v0;
    return temp_v0;
}

int GM_ClearPlayerStatusFlag_8004E2D4(int flag)
{
    GM_PlayerStatus_800ABA50 &= ~flag;
}
