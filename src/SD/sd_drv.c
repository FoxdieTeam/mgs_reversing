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
extern const char aSngStatusX[];
extern const char aSongkaihimode[];
extern const char aSongfadeoutSto[];
extern const char aSongfadeoutPau[];
extern const char aSongstop[];
extern const char aSongpauseon[];
extern const char aSongpauseoff[];
extern const char aSongfadein[];
extern const char aSamesonghasalr[];
extern const char aSoundWorkIsBro[];
extern const char aSongsyukanmode_0[];
extern const char aSongsyukanmode[];
extern const char aSongEndXX[];
extern const char aSngcodeX[];
extern const char aErrorSngPlayCo[];
extern const char aSngFadeoutStar[]; // = "SNG FADEOUT START(status=%x)\n"
extern const char aSngFadeoutCanc[]; // = "SNG FADEOUT CANCELED(status=%x)\n"

extern int sd_sng_code_buf_800BF018[16];
extern int sng_syukan_fg_800C0510;
extern int sng_pause_fg_800BF298;
extern int sng_fout_fg_800BF25C;
extern int sng_fadein_fg_800C041C;
extern int sng_status_800BF158;
extern int sng_fadein_fg_800C041C;
extern int sng_fade_in_2_800BF290;
extern int song_end_800C04E8;
extern int se_tracks_800BF004;
extern int keyd_800C0524;
extern int sng_fade_in_2_800C0BC0;
extern int dword_800C0428;
extern int sd_sng_data_800C0420;
extern int sd_code_read_800BF288;
extern int stop_jouchuu_se_800BF1A0;
extern int sng_fout_term_800C0518;
extern int dword_800BEFF8;

extern unsigned int   mtrack_800BF1EC;
extern unsigned char *mptr_800C0570;

extern int spu_ch_tbl_800A2AC8[];
extern int fade_unk_1_800C0BC8[13];
extern int sng_fade_time_800C0430[14];
extern int sng_fade_value_800C0538[13];

extern SOUND_W * sptr_800C057C;
extern SOUND_W   sound_w_800BF2A8[21];
extern SEPLAYTBL se_request_800BF0E0[8]; // 0x60 (96) bytes

void sng_track_init_800859B8(SOUND_W *pSoundW);
int  SD_8008395C(int a1, int a2);
void SD_80085480();
void sng_pause_80087EF4();
void sng_pause_off_80087F24();
void SD_SongFadeIn_80084CCC();
int  SngFadeOutP_80084D60(unsigned int a1);
int  SD_SongFadeoutAndStop_80084E48(unsigned int code);
void SD_SongKaihiMode_80084F88();
void sng_off_80087E2C();
void sng_adrs_set_80085658();
void SngFadeWkSet_80085020();
void SD_80085164();
int  SD_80085A50();
void se_off_80087E94(int a1);
void se_adrs_set_8008576C();
void SD_spuwr_80087A88();

void IntSdMain_80084494()
{
    int temp; // $v0
    int pSngData; // $a2
    int k13Counter; // $a2
    unsigned char *field_0_mpointer; // $v1
    int new_sng_status; // $v0
    unsigned char *track_ptr; // $v1
    SOUND_W* wTmp;

    if ( sd_sng_code_buf_800BF018[sd_code_read_800BF288] )
    {
        temp = sd_sng_code_buf_800BF018[sd_code_read_800BF288];
        sd_sng_code_buf_800BF018[sd_code_read_800BF288] = 0;
        sd_code_read_800BF288 = (sd_code_read_800BF288 + 1) & 0xF;
        mts_printf_8008BBA0(aSngcodeX, temp);
    }
    else
    {
        temp = 0;
    }

    if (temp)
    {
    switch(temp)
    {  
        // Pause
        case 0x1FFFF01:
            sng_pause_fg_800BF298 = 1;
            sng_pause_80087EF4();
            mts_printf_8008BBA0(aSongpauseon);
            break;

        // Unpause
        case 0x1FFFF02:
            sng_pause_off_80087F24();
            sng_pause_fg_800BF298 = 0;
            mts_printf_8008BBA0(aSongpauseoff);
            break;

        // Fade in
        case 0x1FFFF03:
        case 0x1FFFF04:
        case 0x1FFFF05:
            if ( sng_status_800C04F8 != 0xFFFFFFFF ) 
            {
                sng_fout_fg_800BF25C = 0;
                if ( sng_status_800BF158 < 3 )
                {
                    sng_fadein_fg_800C041C = temp;
                }
                else
                {
                    SD_SongFadeIn_80084CCC(temp);
                }
               sng_fade_in_2_800BF290 = 0;
                sng_fade_in_2_800C0BC0 = 0;
            }
            mts_printf_8008BBA0(aSongfadein);
            break;
        
        // Fade out
        case 0x1FFFF06:
        case 0x1FFFF07:
        case 0x1FFFF08:
        case 0x1FFFF09:            
            SngFadeOutP_80084D60(temp);
            mts_printf_8008BBA0(aSongfadeoutPau);
            break;

        // Fade out and stop
        case 0x1FFFF0A:
        case 0x1FFFF0B:
        case 0x1FFFF0C:
        case 0x1FFFF0D:
            SD_SongFadeoutAndStop_80084E48(temp);
            mts_printf_8008BBA0(aSongfadeoutSto);
            break;

        // Evasion Mode
        case 0x1FFFF10:
            SD_SongKaihiMode_80084F88();
            mts_printf_8008BBA0(aSongkaihimode);
            break;

        // First Person Mode
        case 0x1FFFF20:
            sng_syukan_fg_800C0510 = 1;
            mts_printf_8008BBA0(aSongsyukanmode);
            break;

        // Exit first person
        case 0x1FFFF21:
            sng_syukan_fg_800C0510 = 0;
            mts_printf_8008BBA0(aSongsyukanmode_0);
            break;
        
        case 0x1FFFFFF:
            sng_status_800C04F8 = 0;
            sng_off_80087E2C();
            mts_printf_8008BBA0(aSongstop);
            break;

        case 0x1000001:
        case 0x1000002:
        case 0x1000003:
        case 0x1000004:
        case 0x1000005:
        case 0x1000006:
        case 0x1000007:
        case 0x1000008:

            if ( sng_status_800C04F8 != temp )
            {
                if ( sng_status_800BF158 >= 2 )
                {
                    pSngData = *(unsigned char *)sd_sng_data_800C0420;
                    if ( pSngData < (temp & 0xF) )
                    {
                        mts_printf_8008BBA0(aErrorSngPlayCo, temp, pSngData);
                    }
                    else
                    {
                        sng_status_800BF158 = 2;
                        if ( sng_status_800C04F8 == -1 )
                        {
                            for (k13Counter=0; k13Counter < 13; k13Counter++)
                            {
                                sng_fade_time_800C0430[k13Counter] = 0;
                                sng_fade_value_800C0538[k13Counter] = 0;
                                fade_unk_1_800C0BC8[k13Counter] = 0;
                            }
                            sng_fout_term_800C0518 = 0;
                        }
                        sng_status_800C04F8 = temp;
                        sng_off_80087E2C();
                        sng_pause_fg_800BF298 = 0;
                        sng_fade_in_2_800BF290 = 0;
                        sng_fade_in_2_800C0BC0 = 0;  
                    }
                }
                else
                {
                  mts_printf_8008BBA0(aSngStatusX, sng_status_800BF158);
                }
            }
            else
            {
                mts_printf_8008BBA0(aSamesonghasalr);
            }    
        break;
        
    default:
            if ( dword_800C0428 != temp )
            {
                dword_800C0428 = temp;
                sng_status_800C04F8 = 0;
                sng_status_800BF158 = 1;
                sng_off_80087E2C();
                mts_wup_tsk_8008A540(5);
            }

            break;
    }
    }

    switch(sng_status_800BF158)
    {
        case 2:
            if ( sng_status_800C04F8 == 0 )
            {
                break;
            }
            
            if ( sng_status_800C04F8 == -1 )
            {
                break;
            }
            
            sng_adrs_set_80085658(sng_status_800C04F8);
            SngFadeWkSet_80085020();
            sng_status_800BF158 = 3;
            dword_800BEFF8 = 0;
            break;

        case 3:
            if ( dword_800BEFF8 )
            {
                if ( (dword_800BEFF8 & 0x1FFF) != (song_end_800C04E8 & 0x1FFF) )
                {
                    mts_printf_8008BBA0(aSoundWorkIsBro);
                    mts_printf_8008BBA0(aSoundWorkIsBro);
                    mts_printf_8008BBA0(
                        aSongEndXX,
                        song_end_800C04E8 & 0x1FFF,
                        dword_800BEFF8 & 0x1FFF);
                    mts_printf_8008BBA0(aSoundWorkIsBro);
                    mts_printf_8008BBA0(aSoundWorkIsBro);
                }
            }
        
            SD_80085164();
            SD_80085480();

            mtrack_800BF1EC = 0;

            do
            {
                keyd_800C0524 = spu_ch_tbl_800A2AC8[mtrack_800BF1EC];
                if ( (song_end_800C04E8 & keyd_800C0524) == 0 )
                {
                    sptr_800C057C = &sound_w_800BF2A8[mtrack_800BF1EC];
                    field_0_mpointer = sptr_800C057C->field_0_mpointer;
                    if ( !field_0_mpointer )
                    {
                        song_end_800C04E8 |= keyd_800C0524;
                    }
                    else
                    {
                         mptr_800C0570 = field_0_mpointer;
                        if ( SD_80085A50() )
                        {
                            song_end_800C04E8 |= keyd_800C0524;
                            sptr_800C057C->field_0_mpointer = 0;
                        }
                        else
                        {
                            sptr_800C057C->field_0_mpointer = mptr_800C0570;
                        }
                    }
                }
                ++mtrack_800BF1EC;
            }
            while ( (unsigned int)mtrack_800BF1EC < 13 );

            dword_800BEFF8 = song_end_800C04E8;
            if ( (song_end_800C04E8 & 0x1FFF) == 0x1FFF )
            {
                new_sng_status = 4;
                sng_status_800BF158 = new_sng_status;
            }    
            break;

                
        case 4:
            sng_off_80087E2C();
            new_sng_status = 2;
            sng_status_800C04F8 = 0;
            sng_status_800BF158 = new_sng_status;
            break;
        
    }

    for (mtrack_800BF1EC=13; mtrack_800BF1EC < 21; mtrack_800BF1EC++)
    {
        if ( se_tracks_800BF004 < 2 && se_request_800BF0E0[mtrack_800BF1EC - 13].field_8_code )
        {
            se_off_80087E94(mtrack_800BF1EC - 13);
            se_adrs_set_8008576C(mtrack_800BF1EC - 13);
        }
        else
        {
            keyd_800C0524 = spu_ch_tbl_800A2AC8[mtrack_800BF1EC];
            if ( (song_end_800C04E8 & keyd_800C0524) == 0 )
            {
                wTmp = &sound_w_800BF2A8[mtrack_800BF1EC];
                track_ptr = wTmp->field_0_mpointer;
                sptr_800C057C = wTmp;
                if ( !track_ptr )
                {
                    song_end_800C04E8 |= keyd_800C0524;
                }
                else
                {
                    mptr_800C0570 = track_ptr;
                    if ( SD_80085A50() )
                    {
                        song_end_800C04E8 |= keyd_800C0524;
                        sptr_800C057C->field_0_mpointer = 0;
                    }
                    else
                    {
                        sptr_800C057C->field_0_mpointer = mptr_800C0570;
                    }
             
                }
            }
        }
    }

    if ( stop_jouchuu_se_800BF1A0 >= 2 )
    {
        stop_jouchuu_se_800BF1A0 = 0;
    }
    
    SD_spuwr_80087A88();
}



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

int SD_SongFadeoutAndStop_80084E48(unsigned int code)
{
    int i;
    int fade;

    if ((sng_status_800BF158 != 0) && ((sng_fout_term_800C0518 != 0x1FFF) || (sd_KaihiMode_800BF05C != 0)))
    {
        switch (code)
        {
        case 0x1FFFF0A:
            fade = 0x51E;
            break;
        case 0x1FFFF0B:
            fade = 0x28F;
            break;
        case 0x1FFFF0C:
            fade = 0xDA;
            break;
        case 0x1FFFF0D:
            fade = 0x83;
            break;
        }

        if (fade == 0)
        {
            fade = 1;
        }

        for (i = 0; i < 13; i++)
        {
            if (!((sng_fout_term_800C0518 >> i) & 1))
            {
                sng_fade_time_800C0430[i] = fade;
            }
        }

        sd_KaihiMode_800BF05C = 0;
        sng_status_800C04F8 = -1;
    
        mts_printf_8008BBA0(aSngFadeoutStar, sng_status_800BF158);
        return 0;
    }

    mts_printf_8008BBA0(aSngFadeoutCanc, sng_status_800BF158);
    return -1;
}

#pragma INCLUDE_ASM("asm/SD/SD_SongKaihiMode_80084F88.s") // 152 bytes
#pragma INCLUDE_ASM("asm/SD/SngFadeWkSet_80085020.s") // 324 bytes
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
#pragma INCLUDE_ASM("asm/SD/se_adrs_set_8008576C.s") // 588 bytes


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
