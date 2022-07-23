#include "idaTypes.h"

extern int  sub_8004E22C(int a1, int a2, int a3);
extern int  sub_8004E2B4(int a1);

void nullsub_18_80053B80(void)
{

}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_run_begin_80053B88.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_prone_begin_80053BE8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_prone_standup_80053D74.s")
#pragma INCLUDE_ASM("asm/sub_80053E9C.s")
#pragma INCLUDE_ASM("asm/sub_80053FAC.s")
#pragma INCLUDE_ASM("asm/sub_800540D0.s")
#pragma INCLUDE_ASM("asm/sub_800541A8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_chokethrow_begin1_80054210.s")
#pragma INCLUDE_ASM("asm/sub_8005425C.s")
#pragma INCLUDE_ASM("asm/sub_80054318.s")
#pragma INCLUDE_ASM("asm/sub_800543A8.s")
#pragma INCLUDE_ASM("asm/sub_80054424.s")

extern void GM_SetPlayerStatusFlag_8004E2B4(unsigned int param_1);
extern void sub_80050440(int param_1);
extern void sub_80056928(void);
extern void sub_80052468(void);

void sub_80054488(int param_1, int param_2)
{
    if (param_2 == 0)
    {
        GM_SetPlayerStatusFlag_8004E2B4(0x10);
        *(void **)(param_1 + 0x9c8) = (void*)&sub_80056928;
        *(void **)(param_1 + 0x9cc) = (void*)&sub_80052468;
    }
    *(short *)(param_1 + 0xa62) = *(short *)(param_1 + 0x98) + 0xfa;
    sub_80050440(param_1);
    return;
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_shot_flinch_800544E0.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper7_80054648.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper8_80054710.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_knockdown_idle_80054930.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_knockdown_getup_80054A10.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_knockdown_shot_80054B50.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper10_80054C08.s")
#pragma INCLUDE_ASM("asm/sub_80054D68.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper2_helper_80054EFC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_scope_80055334.s")

extern void sna_init_anim_scope_80055334(int param_1, int param_2);

void sna_init_anim_jpegcam_800553CC(int param_1, int param_2)
{
    sna_init_anim_scope_80055334(param_1, param_2);
    return;
}

#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_box_idle_800553EC.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_box_run_8005544C.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_box_stop_800554B4.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_anim_dying_80055524.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk_helper2_800559D8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_act_unk_helper3_80055DD8.s")
#pragma INCLUDE_ASM("asm/chara/snake/sna_init_act_helper3_helper_80056650.s")
#pragma INCLUDE_ASM("asm/sub_8005684C.s")
#pragma INCLUDE_ASM("asm/sub_8005688C.s")
#pragma INCLUDE_ASM("asm/sub_80056928.s")
