#include "sna_init.h"

#pragma INCLUDE_ASM("asm/OPERATOR_8004F6E8.s")
#pragma INCLUDE_ASM("asm/sub_8004F8E4.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk_helper4_8004FA3C.s")

extern void GM_ClearPlayerStatusFlag_8004E2D4(unsigned int param_1);
extern void sna_init_clear_flags_8004E344(Actor_SnaInit* param_1, unsigned int param_2);

void sub_8004FA74(Actor_SnaInit* param_1)
{
    sna_init_clear_flags_8004E344(param_1, 0x20);
    GM_ClearPlayerStatusFlag_8004E2D4(0x8408);
}

extern void sub_80051FD0(Actor_SnaInit *snake);
extern void sna_init_sub_8004E330(Actor_SnaInit *snake, unsigned int flag);

void sub_8004FA9C(Actor_SnaInit *snake)
{
    ushort action = *snake->field_9B0_pad_bits;
    sub_80051FD0(snake);
    if (action & 0x4000)
    {
        sna_init_sub_8004E330(snake, 1);
    }
}

#pragma INCLUDE_ASM("asm/sub_8004FAE8.s")
#pragma INCLUDE_ASM("asm/sub_8004FB38.s")
#pragma INCLUDE_ASM("asm/sub_8004FB4C.s")
#pragma INCLUDE_ASM("asm/sub_8004FB90.s")
#pragma INCLUDE_ASM("asm/sub_8004FBA0.s")
#pragma INCLUDE_ASM("asm/Game/GM_ClearBulName_8004FBE4.s")
#pragma INCLUDE_ASM("asm/Game/GM_CheckShukanReverse_8004FBF8.s")
#pragma INCLUDE_ASM("asm/Game/GM_CheckShukanReverseAnalog_8004FC70.s")
#pragma INCLUDE_ASM("asm/sub_8004FCB8.s")
#pragma INCLUDE_ASM("asm/sub_8004FDE8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper5_8004FF88.s")
#pragma INCLUDE_ASM("asm/sub_8005009C.s")
#pragma INCLUDE_ASM("asm/sub_800501F8.s")
#pragma INCLUDE_ASM("asm/sub_8005027C.s")
#pragma INCLUDE_ASM("asm/sub_80050398.s")
#pragma INCLUDE_ASM("asm/sub_80050440.s")
#pragma INCLUDE_ASM("asm/sub_80050568.s")
#pragma INCLUDE_ASM("asm/sub_80050668.s")
#pragma INCLUDE_ASM("asm/sub_800507D8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper3_80050878.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk_80050A64.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk2_80051170.s")
#pragma INCLUDE_ASM("asm/sna_init_weapon_switching_800511BC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_800515BC.s")
#pragma INCLUDE_ASM("asm/sub_80051A10.s")
#pragma INCLUDE_ASM("asm/sub_80051BA4.s")
#pragma INCLUDE_ASM("asm/sub_80051DA0.s")
#pragma INCLUDE_ASM("asm/sub_80051FD0.s")
#pragma INCLUDE_ASM("asm/sub_80052120.s")
#pragma INCLUDE_ASM("asm/sub_8005230C.s")
#pragma INCLUDE_ASM("asm/sub_80052468.s")
#pragma INCLUDE_ASM("asm/sub_80052540.s")
#pragma INCLUDE_ASM("asm/sub_800525F8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper_helper_800526BC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_idle_8005275C.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_crouch_800527DC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_prone_idle_800528BC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_run_8005292C.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_prone_move_800529C0.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_wall_idle_and_c4_80052A5C.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_wall_move_80052BA8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_wall_crouch_80052CCC.s")
#pragma INCLUDE_ASM("asm/sub_80052E58.s")
#pragma INCLUDE_ASM("asm/sub_80053014.s")
#pragma INCLUDE_ASM("asm/sub_800531F4.s")
#pragma INCLUDE_ASM("asm/sub_80053360.s")
#pragma INCLUDE_ASM("asm/sub_800535B8.s")
#pragma INCLUDE_ASM("asm/sub_800537D4.s")
#pragma INCLUDE_ASM("asm/sub_800538CC.s")
#pragma INCLUDE_ASM("asm/sub_80053A54.s")
