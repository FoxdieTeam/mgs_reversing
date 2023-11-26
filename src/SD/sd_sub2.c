#include "SD/sd.h"

extern int keyoffs_800BF29C;
extern int keyd_800C0524;
extern SOUND_W* sptr_800C057C;
extern unsigned int mtrack_800BF1EC;
extern SPU_TRACK_REG spu_tr_wk_800C0658[];
extern int mdata2_800BF0D4;
extern int mdata3_800BF0D8;
extern int mdata4_800BF0DC;
extern unsigned char* mptr_800C0570;
extern int spu_ch_tbl_800A2AC8[];
extern int dword_800BF210;
extern SEPLAYTBL se_playing_800BF068[8];
extern int dword_800BF064;
extern int stop_jouchuu_se_800BF1A0;

void tone_set_80087FA8(unsigned char a1);
void SD_MDX_FF_block_end_80087A58();

void SD_MDX_F2_rest_set_80086D18()
{
    sptr_800C057C->field_CC_rest_fg = 1;
    keyoff_80087F80();
    sptr_800C057C->field_6_ngs = mdata2_800BF0D4;
    sptr_800C057C->field_7_ngg = 0;
    sptr_800C057C->field_44_vol = 0;
    sptr_800C057C->field_4_ngc = sptr_800C057C->field_6_ngs;
    sptr_800C057C->field_5_ngo = 0;
}

void tie_set_80086D9C()
{
    int temp1; // $v1

    sptr_800C057C->field_CC_rest_fg = 1;
    sptr_800C057C->field_6_ngs = mdata2_800BF0D4;
    sptr_800C057C->field_7_ngg = mdata3_800BF0D8;
    sptr_800C057C->field_4_ngc = sptr_800C057C->field_6_ngs;
    temp1 = (sptr_800C057C->field_7_ngg * sptr_800C057C->field_4_ngc) / 100;
    if ( !temp1 )
    {
       temp1 = 1;
    }

    sptr_800C057C->field_5_ngo = temp1;
}

void SD_MDX_D2_sno_set_80086E38()
{
    sptr_800C057C->field_A4_snos = mdata2_800BF0D4;
    keyoff_80087F80();
    tone_set_80087FA8(mdata2_800BF0D4);
}

void svl_set_80086E78()
{
    sptr_800C057C->field_A4_snos = mdata2_800BF0D4;
    keyoff_80087F80();
    tone_set_80087FA8(mdata2_800BF0D4);
}

void svp_set_80086EB8()
{
    sptr_800C057C->field_A4_snos = mdata2_800BF0D4;
    keyoff_80087F80();
    tone_set_80087FA8(mdata2_800BF0D4);
}

void use_set_80086EF8()
{

}
void SD_pan_set_80086F00()
{
    sptr_800C057C->field_56_panmod = mdata2_800BF0D4;
    sptr_800C057C->field_54_panf = mdata3_800BF0D8 + 20;
    sptr_800C057C->field_48_pand = sptr_800C057C->field_54_panf << 8;
    sptr_800C057C->field_45_panc = 0;
}

void SD_MDX_DE_pan_move_80086F50()
{
    unsigned char temp1; // $v0
    int temp2; // $v0

    sptr_800C057C->field_45_panc = mdata2_800BF0D4;
    temp1 = (mdata3_800BF0D8 + 0x14);
    sptr_800C057C->field_50_panm = temp1 << 8;
    temp2 = temp1 - sptr_800C057C->field_54_panf;

    if ( temp2 < 0 )
    {
        sptr_800C057C->field_4C_panad = -(((-temp2) << 8) / (unsigned int)mdata2_800BF0D4);
        if ( sptr_800C057C->field_4C_panad < -2032 )
        {
            sptr_800C057C->field_4C_panad = -2032;
        }
    }
    else
    {
        sptr_800C057C->field_4C_panad = (temp2 << 8) / (unsigned int)mdata2_800BF0D4;
        if ( sptr_800C057C->field_4C_panad > 2032 )
        {
            sptr_800C057C->field_4C_panad = 2032;
        }
        
    }
}

void SD_MDX_E1_vib_set_80087018()
{
    sptr_800C057C->field_84_vibhs = mdata2_800BF0D4;
    sptr_800C057C->field_86_vibcad = mdata3_800BF0D8;
    if ( sptr_800C057C->field_86_vibcad < 64 )
    {
        if ( sptr_800C057C->field_86_vibcad < 32 )
        {
            sptr_800C057C->field_79_vib_tc_ofst = 1;
            sptr_800C057C->field_86_vibcad = sptr_800C057C->field_86_vibcad << 3;
        }
        else
        {
            sptr_800C057C->field_79_vib_tc_ofst = 2;
            sptr_800C057C->field_86_vibcad = sptr_800C057C->field_86_vibcad << 2;
        }
    }
    else
    {
        if ( sptr_800C057C->field_86_vibcad < 128 )
        {
            sptr_800C057C->field_79_vib_tc_ofst = 4;
            sptr_800C057C->field_86_vibcad = sptr_800C057C->field_86_vibcad << 1;
        }
        else if ( sptr_800C057C->field_86_vibcad != 255 )
        {
            sptr_800C057C->field_79_vib_tc_ofst = 8;
        }
        else
        {
            sptr_800C057C->field_79_vib_tc_ofst = 16;
        }
    }

    sptr_800C057C->field_7C_vibd = mdata4_800BF0DC << 8;
    sptr_800C057C->field_80_vibdm = mdata4_800BF0DC << 8;
}

void SD_MDX_E2_vib_change_80087120()
{
    sptr_800C057C->field_85_vibcs = mdata2_800BF0D4;
    sptr_800C057C->field_88_vibad = sptr_800C057C->field_80_vibdm / (unsigned int)mdata2_800BF0D4;
}

void SD_MDX_E3_rdm_set_8008716C()
{
    sptr_800C057C->field_94_rdms = mdata2_800BF0D4;
    sptr_800C057C->field_98_rdmd = (mdata3_800BF0D8 << 8) + mdata4_800BF0DC;
    sptr_800C057C->field_8C_rdmc = 0;
    sptr_800C057C->field_90_rdmo = 0;
}

void SD_MDX_E7_lp1_start_800871B4()
{
    sptr_800C057C->field_1C_lp1_addr = mptr_800C0570;
    sptr_800C057C->field_8_lp1_cnt = 0;
    sptr_800C057C->field_14_lp1_freq = 0;
    sptr_800C057C->field_C_lp1_vol = 0;
}

void SD_MDX_E8_800871E0()
{
    char v1;

    if ( stop_jouchuu_se_800BF1A0 && !mdata2_800BF0D4 )
    {
        sptr_800C057C->field_C_lp1_vol = 0;
        sptr_800C057C->field_14_lp1_freq = 0;
        ++stop_jouchuu_se_800BF1A0;
    }
    else
    {
        v1 = sptr_800C057C->field_8_lp1_cnt + 1;
        sptr_800C057C->field_8_lp1_cnt = v1;
        
        if ( v1 != mdata2_800BF0D4 || v1  == 0 )
        {
            sptr_800C057C->field_C_lp1_vol += (signed char)mdata3_800BF0D8;
            sptr_800C057C->field_14_lp1_freq += (signed char)mdata4_800BF0DC * 8;
            mptr_800C0570 = sptr_800C057C->field_1C_lp1_addr;
        }
        else
        {
            sptr_800C057C->field_C_lp1_vol = 0;
            sptr_800C057C->field_14_lp1_freq = 0;
        }
    }
}

void SD_MDX_E9_lp2_start_800872C0()
{
    sptr_800C057C->field_20_lp2_addr = mptr_800C0570;
    sptr_800C057C->field_9_lp2_cnt = 0;
    sptr_800C057C->field_18_lp2_freq = 0;
    sptr_800C057C->field_10_lp2_vol = 0;
}

void SD_MDX_EA_lp2_end_800872EC()
{
    unsigned char cnt; // $v1
    cnt = sptr_800C057C->field_9_lp2_cnt + 1;
    sptr_800C057C->field_9_lp2_cnt = cnt;
    if ( cnt != mdata2_800BF0D4 || !cnt )
    {
        sptr_800C057C->field_10_lp2_vol += (signed char)mdata3_800BF0D8;
        sptr_800C057C->field_18_lp2_freq +=  8 * (signed char)mdata4_800BF0DC;
        mptr_800C0570 =  sptr_800C057C->field_20_lp2_addr;
    }
}

void SD_MDX_EB_l3s_set_8008736C()
{
    sptr_800C057C->field_24_lp3_addr = mptr_800C0570;
}

void SD_MDX_EC_l3e_set_80087384()
{
    if ( sptr_800C057C->field_24_lp3_addr )
    {
        mptr_800C0570 = sptr_800C057C->field_24_lp3_addr;
    }
    else
    {
        SD_MDX_FF_block_end_80087A58();
    }
}

void tempo_set_800873CC()
{
    sptr_800C057C->field_B8_tmp = mdata2_800BF0D4;
}


void tempo_move_800873E4()
{
    int temp; // $a0

    sptr_800C057C->field_C0_tmpc = mdata2_800BF0D4;
    sptr_800C057C->field_C8_tmpm = mdata3_800BF0D8;
    sptr_800C057C->field_C4_tmpw = sptr_800C057C->field_B8_tmp << 8;


    temp = (unsigned char)sptr_800C057C->field_C8_tmpm - (unsigned char)sptr_800C057C->field_B8_tmp;
    if ( temp < 0 )
    {
        if ( temp < -127 )
        {
            temp = -127;
        }
        sptr_800C057C->field_BC_tmpad = -((-temp << 8) / (unsigned char)sptr_800C057C->field_C0_tmpc);
        if ( (unsigned int)sptr_800C057C->field_BC_tmpad < -2032 ) // madness, but works
        {
            sptr_800C057C->field_BC_tmpad = -2032;
        }
       
    }
    else
    {
        if ( temp > 127 )
        {
            temp = 127;
        }

        sptr_800C057C->field_BC_tmpad =  (temp << 8) / (unsigned char)sptr_800C057C->field_C0_tmpc;
        if ((unsigned int)sptr_800C057C->field_BC_tmpad > 0x7F0 )
        {
            sptr_800C057C->field_BC_tmpad = 0x7F0;
        }    
    }
}

void trans_set_8008750C()
{
    sptr_800C057C->field_A8_ptps = (signed char)mdata2_800BF0D4;
}

void tre_set_80087524()
{
    sptr_800C057C->field_A0_trehs = mdata2_800BF0D4;
    sptr_800C057C->field_9F_trecad = mdata3_800BF0D8;
    sptr_800C057C->field_9E_tred = mdata4_800BF0DC;
}

void vol_chg_8008756C()
{
    sptr_800C057C->field_38_pvod = mdata2_800BF0D4 << 8;
    sptr_800C057C->field_34_pvoc = 0;
}

void SD_MDX_D6_vol_move_8008758C()
{
    int temp; // $a0

    sptr_800C057C->field_34_pvoc = mdata2_800BF0D4;
    sptr_800C057C->field_40_pvom = mdata3_800BF0D8;
    temp = (mdata3_800BF0D8 << 8);
    temp = temp - sptr_800C057C->field_38_pvod;
    if ( temp < 0 )
    {
        sptr_800C057C->field_3C_pvoad = -(-temp / sptr_800C057C->field_34_pvoc);
        if ( sptr_800C057C->field_3C_pvoad < -2032 )
        {
            sptr_800C057C->field_3C_pvoad = -2032;
        }
    }
    else
    {
        sptr_800C057C->field_3C_pvoad = temp / sptr_800C057C->field_34_pvoc;
        if ( sptr_800C057C->field_3C_pvoad > 0x7F0 )
        {
            sptr_800C057C->field_3C_pvoad = 0x7F0;
        }
       
    }
}

void SD_MDX_E6_por_set_80087670()
{
    sptr_800C057C->field_69_swshc = 0;
    sptr_800C057C->field_68_swsc = mdata2_800BF0D4;
    if ( !mdata2_800BF0D4 )
    {
        sptr_800C057C->field_6A_swsk = 0;
    }
    else
    {
        sptr_800C057C->field_6A_swsk = 1;
    }
}

void sws_set_800876D4()
{
    sptr_800C057C->field_6A_swsk = 0;
    sptr_800C057C->field_69_swshc = mdata2_800BF0D4;
    sptr_800C057C->field_68_swsc = mdata3_800BF0D8;
    sptr_800C057C->field_6C_swss = mdata4_800BF0DC << 8;
}

void SD_MDX_E0_detune_set_80087730()
{
    sptr_800C057C->field_B0_tund = (signed char)mdata2_800BF0D4 << 2;
}

void swp_set_8008774C()
{

}

void echo_set1_80087754()
{

}

void echo_set2_8008775C()
{

}

void SD_MDX_F6_80087764()
{
    if ( (unsigned int)(mtrack_800BF1EC - 13) < 8 && !se_playing_800BF068[mtrack_800BF1EC - 13].field_1_kind )
    {
        dword_800BF064 |= spu_ch_tbl_800A2AC8[mtrack_800BF1EC + 1];
    }
}

void SD_MDX_F7_800877CC()
{
    if ( (unsigned int)(mtrack_800BF1EC - 13) < 8 && !se_playing_800BF068[mtrack_800BF1EC - 13].field_1_kind )
    {
        dword_800BF210 |= spu_ch_tbl_800A2AC8[mtrack_800BF1EC + 1];
    }
}

void SD_MDX_ED_kakko_start_80087834()
{
    sptr_800C057C->field_2C_kak1ptr = mptr_800C0570;
    sptr_800C057C->field_28_kakfg = 0;
}

void SD_MDX_EE_kakko_end_80087854()
{
    switch (sptr_800C057C->field_28_kakfg)
    {
    case 0:
        sptr_800C057C->field_28_kakfg++;
        break;

    case 1:
        sptr_800C057C->field_28_kakfg++;
        sptr_800C057C->field_30_kak2ptr = mptr_800C0570;
        mptr_800C0570 = sptr_800C057C->field_2C_kak1ptr;
        break;

    case 2:
        sptr_800C057C->field_28_kakfg--;
        mptr_800C0570 = sptr_800C057C->field_30_kak2ptr;
        break;
    }
}

void sub_800878FC()
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

void sub_80087A48()
{

}

void sub_80087A50()
{

}

void SD_MDX_FF_block_end_80087A58()
{
    keyoffs_800BF29C |= keyd_800C0524;
}

void no_cmd_80087A80()
{

}
