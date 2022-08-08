#include "SD/sd.h"

extern int keyoffs_800BF29C;
extern int keyd_800C0524;
extern SOUND_W* sptr_800C057C;
extern int mtrack_800BF1EC;
extern SPU_TRACK_REG spu_tr_wk_800C0658[];
extern int mdata2_800BF0D4;
extern int mdata3_800BF0D8;
extern int mdata4_800BF0DC;

#pragma INCLUDE_ASM("asm/SD/SD_MDX_F2_80086D18.s")
#pragma INCLUDE_ASM("asm/SD/tie_set_80086D9C.s")
#pragma INCLUDE_ASM("asm/SD/SD_MDX_D2_80086E38.s")
#pragma INCLUDE_ASM("asm/SD/svl_set_80086E78.s")
#pragma INCLUDE_ASM("asm/SD/svp_set_80086EB8.s")

void use_set_80086EF8(void)
{

}

#pragma INCLUDE_ASM("asm/SD/SD_80086F00.s")
#pragma INCLUDE_ASM("asm/SD/SD_MDX_DE_80086F50.s")
#pragma INCLUDE_ASM("asm/SD/SD_MDX_E1_80087018.s")
#pragma INCLUDE_ASM("asm/SD/SD_MDX_E2_80087120.s")
#pragma INCLUDE_ASM("asm/SD/SD_MDX_E3_8008716C.s")
#pragma INCLUDE_ASM("asm/SD/SD_MDX_E7_800871B4.s")
#pragma INCLUDE_ASM("asm/SD/SD_MDX_E8_800871E0.s")
#pragma INCLUDE_ASM("asm/SD/SD_MDX_E9_800872C0.s")
#pragma INCLUDE_ASM("asm/SD/SD_MDX_EA_800872EC.s")
#pragma INCLUDE_ASM("asm/SD/SD_MDX_EB_8008736C.s")
#pragma INCLUDE_ASM("asm/SD/SD_MDX_EC_80087384.s")
#pragma INCLUDE_ASM("asm/SD/tempo_set_800873CC.s")
#pragma INCLUDE_ASM("asm/SD/tempo_move_800873E4.s")
#pragma INCLUDE_ASM("asm/SD/trans_set_8008750C.s")
#pragma INCLUDE_ASM("asm/sub_80087524.s")
#pragma INCLUDE_ASM("asm/SD/se_adrs_set_8008756C.s")
#pragma INCLUDE_ASM("asm/SD/SD_MDX_D6_8008758C.s")
#pragma INCLUDE_ASM("asm/SD/SD_MDX_E6_80087670.s")
#pragma INCLUDE_ASM("asm/SD/sws_set_800876D4.s")
#pragma INCLUDE_ASM("asm/SD/SD_MDX_E0_80087730.s")

void swp_set_8008774C(void)
{

}

void echo_set1_80087754(void)
{

}

void echo_set2_8008775C(void)
{

}

#pragma INCLUDE_ASM("asm/SD/SD_MDX_F6_80087764.s")
#pragma INCLUDE_ASM("asm/SD/SD_MDX_F7_800877CC.s")
#pragma INCLUDE_ASM("asm/SD/SD_MDX_ED_80087834.s")
#pragma INCLUDE_ASM("asm/SD/SD_MDX_EE_80087854.s")

void sub_800878FC(void)
{

}

void SD_MDX_D7_80087904()
{
    spu_tr_wk_800C0658[mtrack_800BF1EC].field_18_a_mode = 1;
    spu_tr_wk_800C0658[mtrack_800BF1EC].field_1C_ar = ~mdata2_800BF0D4 & 0x7F;
    spu_tr_wk_800C0658[mtrack_800BF1EC].field_1E_dr = ~mdata3_800BF0D8 & 0xF;
    spu_tr_wk_800C0658[mtrack_800BF1EC].field_2A_sl = mdata4_800BF0DC & 0xF;
    spu_tr_wk_800C0658[mtrack_800BF1EC].field_20_env1_fg = 1;
}

void SD_MDX_D8_srs_set_8008798C()
{
    spu_tr_wk_800C0658[mtrack_800BF1EC].field_24_s_mode = 3;
    spu_tr_wk_800C0658[mtrack_800BF1EC].field_28_sr = ~mdata2_800BF0D4 & 0x7F;
    spu_tr_wk_800C0658[mtrack_800BF1EC].field_2C_env2_fg = 1;
}

void SD_MDX_D9_800879E4()
{
    const short flags = ~mdata2_800BF0D4 & 0x1F;
    spu_tr_wk_800C0658[mtrack_800BF1EC].field_30_r_mode = 3;
    spu_tr_wk_800C0658[mtrack_800BF1EC].field_34_rr = flags;
    sptr_800C057C->field_D2_rrd = flags;
    spu_tr_wk_800C0658[mtrack_800BF1EC].field_38_env3_fg = 1;
}

void sub_80087A48(void)
{

}

void sub_80087A50(void)
{

}

void SD_MDX_FF_block_end_80087A58()
{
    keyoffs_800BF29C |= keyd_800C0524;
}

void no_cmd_80087A80(void)
{

}
