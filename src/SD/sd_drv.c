#include "SD/sd.h"
#include "mts/mts_new.h"

extern int sng_status_800BF158;
extern int sng_fout_term_800C0518;
extern int sng_fade_time_800C0430[14];
extern int sd_KaihiMode_800BF05C;
extern unsigned int mtrack_800BF1EC;
extern SOUND_W* sptr_800C057C;
extern int keyons_800BF260;
extern int keyoffs_800BF29C;
extern SOUND_W sound_w_800BF2A8[21];
extern unsigned int sng_status_800C04F8;
extern int dword_800C0428;
extern int sd_sng_data_800C0420;
extern int dword_800BF1D8;
extern int sng_fade_in_2_800C0BC0;
extern int sng_fade_in_2_800BF290;

extern const char aLoadsngdataFil[];
extern const char aCompletedloads[];

void sng_track_init_800859B8(SOUND_W *pSoundW);
int SD_8008395C(int a1, int a2);

#pragma INCLUDE_ASM("asm/SD/IntSdMain_80084494.s") // 2104 bytes

void SD_SongFadeIn_80084CCC(unsigned int mode)
{
    int i;

    switch (mode)
    {
    case 0x1FFFF03:
        sd_KaihiMode_800BF05C = 655;
        break;
        
    case 0x1FFFF04:
        sd_KaihiMode_800BF05C = 218;
        break;
    case 0x1FFFF05:
        sd_KaihiMode_800BF05C = 131;
        break;
    }

    if (sd_KaihiMode_800BF05C == 0)
    {
        sd_KaihiMode_800BF05C = 1;
    }

    for (i = 0; i < 13; i++)
    {
        sng_fade_time_800C0430[i] = 0;
    }

    sng_fout_term_800C0518 = 0;
}

int SngFadeOutP_80084D60(unsigned int a1)
{
    int temp; // $a1
    int i;    // $v1

#ifndef NO_WARNING_WORKAROUNDS
    temp = temp; // doesn't work?
#endif

    if (sng_status_800BF158 && sng_fout_term_800C0518 != 0x1FFF)
    {
        switch (a1)
        {
        case 0x1FFFF06:
            temp = 1310;
            break;
        case 0x1FFFF07:
            temp = 655;
            break;
        case 0x1FFFF08:
            temp = 218;
            break;
        case 0x1FFFF09:
            temp = 131;
            break;
            // default: temp = 0; break; // we like UB
        }

        if (!temp)
        {
            temp = 1;
        }

        for (i = 0; i < 13; i++)
        {
            if (((sng_fout_term_800C0518 >> i) & 1) == 0)
            {
                sng_fade_time_800C0430[i] = temp;
            }
        }

        sd_KaihiMode_800BF05C = 0;
        return 0;
    }

    return -1;
}

#pragma INCLUDE_ASM("asm/SD/SD_SongFadeoutAndStop_80084E48.s") // 320 bytes
#pragma INCLUDE_ASM("asm/SD/SD_SongKaihiMode_80084F88.s") // 152 bytes
#pragma INCLUDE_ASM("asm/SD/SD_80085020.s") // 324 bytes
#pragma INCLUDE_ASM("asm/SD/SD_80085164.s") // 796 bytes

void SD_80085480()
{
    if ( sng_fade_in_2_800BF290 != 0 )
    {
        if ( sng_fade_in_2_800C0BC0 < 256 )
        {
            sng_fade_in_2_800C0BC0++;
        }
    }
    else if ( sng_fade_in_2_800C0BC0 != 0 )
    {
        if ( sng_fade_in_2_800C0BC0 <= 16 )
        {
            sng_fade_in_2_800C0BC0 = 0;
        }
        else
        {
            sng_fade_in_2_800C0BC0 -= 16;
        }
    }
}

int SD_800854F0()
{
    dword_800BF1D8 = SD_SongLoadData_8008394C(dword_800C0428, 3);

    if ( dword_800BF1D8 < 0 )
    {
        dword_800BF1D8 = 0;
        mts_printf_8008BBA0(aLoadsngdataFil, dword_800C0428);
        dword_800C0428 = 0;
        return -1;
    }
    else
    {
        SD_80083954(dword_800BF1D8, sd_sng_data_800C0420, 0x4000);
        SD_8008395C(dword_800BF1D8, 3);
        dword_800BF1D8 = 0;
        mts_printf_8008BBA0(aCompletedloads, dword_800C0428);
        return 0;
    }
}

void init_sng_work_8008559C()
{
    SOUND_W *pIter; // $a0

    for (mtrack_800BF1EC = 0; mtrack_800BF1EC < 21; mtrack_800BF1EC++)
    {
        pIter = &sound_w_800BF2A8[mtrack_800BF1EC];
        sptr_800C057C = pIter;
        pIter->field_0_mpointer = 0;
        pIter->field_24_lp3_addr = 0;
        pIter->field_20_lp2_addr = 0;
        pIter->field_1C_lp1_addr = 0;
        sng_track_init_800859B8(pIter);
    }

    keyons_800BF260 = 0;
    keyoffs_800BF29C = 0;
    sng_status_800C04F8 = 0;
    dword_800C0428 = 0; // TODO: sng_play_code?
}
#pragma INCLUDE_ASM("asm/SD/sng_adrs_set_80085658.s") // 276 bytes

extern SEPLAYTBL se_request_800BF0E0[8];
extern SEPLAYTBL se_playing_800BF068[8];
extern int se_vol_800BF1F0[8];
extern int se_pan_800BF1B8[8];
extern int song_end_800C04E8;
extern int se_rev_on_800C0574;
extern int dword_800BF064;
extern int dword_800BF210;

extern int spu_ch_tbl_800A2AC8[];

// https://decomp.me/scratch/sro0f
#pragma INCLUDE_ASM("asm/SD/SD_8008576C.s") // 588 bytes


void sng_track_init_800859B8(SOUND_W *pSoundW)
{
    pSoundW->field_4_ngc = 1;
    pSoundW->field_38_pvod = 127;
    pSoundW->field_44_vol = 127;
    pSoundW->field_48_pand = 2560;
    pSoundW->field_54_panf = 10;
    pSoundW->field_B4_tmpd = 1;
    pSoundW->field_98_rdmd = 0;
    pSoundW->field_5_ngo = 0;
    pSoundW->field_6_ngs = 0;
    pSoundW->field_7_ngg = 0;
    pSoundW->field_8_lp1_cnt = 0;
    pSoundW->field_9_lp2_cnt = 0;
    pSoundW->field_C_lp1_vol = 0;
    pSoundW->field_10_lp2_vol = 0;
    pSoundW->field_14_lp1_freq = 0;
    pSoundW->field_18_lp2_freq = 0;
    pSoundW->field_34_pvoc = 0;
    pSoundW->field_55 = 0;
    pSoundW->field_56_panmod = 0;
    pSoundW->field_6A_swsk = 0;
    pSoundW->field_68_swsc = 0;
    pSoundW->field_7C_vibd = 0;
    pSoundW->field_80_vibdm = 0;
    pSoundW->field_9E_tred = 0;
    pSoundW->field_A4_snos = 0;
    pSoundW->field_A8_ptps = 0;
    pSoundW->field_AC_dec_vol = 0;
    pSoundW->field_B0_tund = 0;
    pSoundW->field_B8_tmp = -1;
    pSoundW->field_C0_tmpc = 0;
}
