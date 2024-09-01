#include "SD/sd_incl.h"
#include "SD/sd_ext.h"

#include "mts/mts_new.h"
#include "mts/taskid.h"

void IntSdMain(void)
{
    int temp; // $v0
    int pSngData; // $a2
    int k13Counter; // $a2
    unsigned char *mptr; // $v1
    int new_sng_status; // $v0
    unsigned char *track_ptr; // $v1
    SOUND_W* wTmp;

    if (sd_sng_code_buf_800BF018[sd_code_read_800BF288])
    {
        temp = sd_sng_code_buf_800BF018[sd_code_read_800BF288];
        sd_sng_code_buf_800BF018[sd_code_read_800BF288] = 0;
        sd_code_read_800BF288 = (sd_code_read_800BF288 + 1) & 0xF;
        printf("SngCode=%x\n", temp);
    }
    else
    {
        temp = 0;
    }

    if (temp)
    {
    switch (temp)
    {
        // Pause
        case 0x01FFFF01:
            sng_pause_fg_800BF298 = 1;
            sng_pause();
            printf("SongPauseOn\n");
            break;

        // Unpause
        case 0x01FFFF02:
            sng_pause_off();
            sng_pause_fg_800BF298 = 0;
            printf("SongPauseOff\n");
            break;

        // Fade in
        case 0x01FFFF03: /* fallthrough */
        case 0x01FFFF04: /* fallthrough */
        case 0x01FFFF05:
            if (sng_play_code_800C04F8 != 0xFFFFFFFF)
            {
                sng_fout_fg_800BF25C = 0;
                if (sng_status_800BF158 < 3)
                {
                    sng_fadein_fg_800C041C = temp;
                }
                else
                {
                    SD_SongFadeIn(temp);
                }
                sng_kaihi_fg_800BF290 = 0;
                sng_fade_in_2_800C0BC0 = 0;
            }
            printf("SongFadein\n");
            break;

        // Fade out
        case 0x01FFFF06: /* fallthrough */
        case 0x01FFFF07: /* fallthrough */
        case 0x01FFFF08: /* fallthrough */
        case 0x01FFFF09:
            SngFadeOutP(temp);
            printf("SongFadeout&Pause\n");
            break;

        // Fade out and stop
        case 0x01FFFF0A: /* fallthrough */
        case 0x01FFFF0B: /* fallthrough */
        case 0x01FFFF0C: /* fallthrough */
        case 0x01FFFF0D:
            SD_SongFadeoutAndStop(temp);
            printf("SongFadeout&Stop\n");
            break;

        // Evasion Mode
        case 0x01FFFF10:
            SD_SongKaihiMode();
            printf("SongKaihiMode\n");
            break;

        // First Person Mode
        case 0x01FFFF20:
            sng_syukan_fg_800C0510 = 1;
            printf("SongSyukanMode On\n");
            break;

        // Exit first person
        case 0x01FFFF21:
            sng_syukan_fg_800C0510 = 0;
            printf("SongSyukanMode Off\n");
            break;

        case 0x01FFFFFF:
            sng_play_code_800C04F8 = 0;
            sng_off();
            printf("SongStop\n");
            break;

        case 0x01000001: /* fallthrough */
        case 0x01000002: /* fallthrough */
        case 0x01000003: /* fallthrough */
        case 0x01000004: /* fallthrough */
        case 0x01000005: /* fallthrough */
        case 0x01000006: /* fallthrough */
        case 0x01000007: /* fallthrough */
        case 0x01000008:

            if (sng_play_code_800C04F8 != temp)
            {
                if (sng_status_800BF158 >= 2)
                {
                    pSngData = sng_data_800C0420[0];
                    if (pSngData < (temp & 0xF))
                    {
                        printf("ERROR:SNG PLAY CODE(%x/%x)\n", temp, pSngData);
                    }
                    else
                    {
                        sng_status_800BF158 = 2;
                        if (sng_play_code_800C04F8 == -1)
                        {
                            for (k13Counter=0; k13Counter < 13; k13Counter++)
                            {
                                sng_fade_time_800C0430[k13Counter] = 0;
                                sng_fade_value_800C0538[k13Counter] = 0;
                                sng_master_vol_800C0BC8[k13Counter] = 0;
                            }
                            sng_fout_term_800C0518 = 0;
                        }
                        sng_play_code_800C04F8 = temp;
                        sng_off();
                        sng_pause_fg_800BF298 = 0;
                        sng_kaihi_fg_800BF290 = 0;
                        sng_fade_in_2_800C0BC0 = 0;
                    }
                }
                else
                {
                  printf("sng_status=%x\n", sng_status_800BF158);
                }
            }
            else
            {
                printf("SameSongHasAlreadyPlayed\n");
            }
        break;

    default:
            if (sng_load_code_800C0428 != temp)
            {
                sng_load_code_800C0428 = temp;
                sng_play_code_800C04F8 = 0;
                sng_status_800BF158 = 1;
                sng_off();
                mts_wup_tsk_8008A540(MTSID_SOUND_MAIN);
            }

            break;
    }
    }

    switch (sng_status_800BF158)
    {
        case 2:
            if (sng_play_code_800C04F8 == 0)
            {
                break;
            }

            if (sng_play_code_800C04F8 == -1)
            {
                break;
            }

            sng_adrs_set(sng_play_code_800C04F8);
            SngFadeWkSet();
            sng_status_800BF158 = 3;
            dword_800BEFF8 = 0;
            break;

        case 3:
            if (dword_800BEFF8)
            {
                if ((dword_800BEFF8 & 0x1FFF) != (song_end_800C04E8 & 0x1FFF))
                {
                    printf("*** SOUND WORK IS BROKEN !!! ***\n");
                    printf("*** SOUND WORK IS BROKEN !!! ***\n");
                    printf("*** song_end:%x -> %x        ***\n",
                        song_end_800C04E8 & 0x1FFF, dword_800BEFF8 & 0x1FFF);
                    printf("*** SOUND WORK IS BROKEN !!! ***\n");
                    printf("*** SOUND WORK IS BROKEN !!! ***\n");
                }
            }

            SD_80085164();
            SD_80085480();

            mtrack_800BF1EC = 0;

            do
            {
                keyd_800C0524 = spu_ch_tbl[mtrack_800BF1EC + 1];
                if ((song_end_800C04E8 & keyd_800C0524) == 0)
                {
                    sptr_800C057C = &sound_w_800BF2A8[mtrack_800BF1EC];
                    mptr = sptr_800C057C->mpointer;
                    if (!mptr)
                    {
                        song_end_800C04E8 |= keyd_800C0524;
                    }
                    else
                    {
                         mptr_800C0570 = mptr;
                        if (sound_sub())
                        {
                            song_end_800C04E8 |= keyd_800C0524;
                            sptr_800C057C->mpointer = 0;
                        }
                        else
                        {
                            sptr_800C057C->mpointer = mptr_800C0570;
                        }
                    }
                }
                ++mtrack_800BF1EC;
            }
            while ((unsigned int)mtrack_800BF1EC < 13);

            dword_800BEFF8 = song_end_800C04E8;
            if ((song_end_800C04E8 & 0x1FFF) == 0x1FFF)
            {
                new_sng_status = 4;
                sng_status_800BF158 = new_sng_status;
            }
            break;


        case 4:
            sng_off();
            new_sng_status = 2;
            sng_play_code_800C04F8 = 0;
            sng_status_800BF158 = new_sng_status;
            break;

    }

    for (mtrack_800BF1EC=13; mtrack_800BF1EC < 21; mtrack_800BF1EC++)
    {
        if (se_tracks_800BF004 < 2 && se_request_800BF0E0[mtrack_800BF1EC - 13].code)
        {
            se_off(mtrack_800BF1EC - 13);
            se_adrs_set(mtrack_800BF1EC - 13);
        }
        else
        {
            keyd_800C0524 = spu_ch_tbl[mtrack_800BF1EC + 1];
            if ((song_end_800C04E8 & keyd_800C0524) == 0)
            {
                wTmp = &sound_w_800BF2A8[mtrack_800BF1EC];
                track_ptr = wTmp->mpointer;
                sptr_800C057C = wTmp;
                if (!track_ptr)
                {
                    song_end_800C04E8 |= keyd_800C0524;
                }
                else
                {
                    mptr_800C0570 = track_ptr;
                    if (sound_sub())
                    {
                        song_end_800C04E8 |= keyd_800C0524;
                        sptr_800C057C->mpointer = 0;
                    }
                    else
                    {
                        sptr_800C057C->mpointer = mptr_800C0570;
                    }

                }
            }
        }
    }

    if (stop_jouchuu_se_800BF1A0 >= 2)
    {
        stop_jouchuu_se_800BF1A0 = 0;
    }

    spuwr();
}

static inline void SD_SongFadeIn_helper(unsigned int mode)
{
    int i;

    switch (mode)
    {
    case 0x01FFFF03:
        sng_fadein_time_800BF05C = 655;
        break;
    case 0x01FFFF04:
        sng_fadein_time_800BF05C = 218;
        break;
    case 0x01FFFF05:
        sng_fadein_time_800BF05C = 131;
        break;
    }

    if (sng_fadein_time_800BF05C == 0)
    {
        sng_fadein_time_800BF05C = 1;
    }

    for (i = 0; i < 13; i++)
    {
        sng_fade_time_800C0430[i] = 0;
    }

    sng_fout_term_800C0518 = 0;
}

void SD_SongFadeIn(unsigned int mode)
{
    SD_SongFadeIn_helper(mode);
}

int SngFadeOutP(unsigned int code)
{
    int temp;
    int i;    // $v1

    if (sng_status_800BF158 && sng_fout_term_800C0518 != 0x1FFF)
    {
        switch (code)
        {
        case 0x01FFFF06:
            temp = 1310;
            break;
        case 0x01FFFF07:
            temp = 655;
            break;
        case 0x01FFFF08:
            temp = 218;
            break;
        case 0x01FFFF09:
            temp = 131;
            break;
        //default: temp = 0; break; // we like UB
        }

        if (!temp)
        {
            temp = 1;
        }

        for (i = 0; i < 13; i++)
        {
            if (!(sng_fout_term_800C0518 & (1 << i)))
            {
                sng_fade_time_800C0430[i] = temp;
            }
        }

        sng_fadein_time_800BF05C = 0;
        return 0;
    }

    return -1;
}

int SD_SongFadeoutAndStop(unsigned int code)
{
    int temp;
    int i;

    if ((sng_status_800BF158 != 0) && ((sng_fout_term_800C0518 != 0x1FFF) || (sng_fadein_time_800BF05C != 0)))
    {
        switch (code)
        {
        case 0x01FFFF0A:
            temp = 1310;
            break;
        case 0x01FFFF0B:
            temp = 655;
            break;
        case 0x01FFFF0C:
            temp = 218;
            break;
        case 0x01FFFF0D:
            temp = 131;
            break;
        }

        if (temp == 0)
        {
            temp = 1;
        }

        for (i = 0; i < 13; i++)
        {
            if (!(sng_fout_term_800C0518 & (1 << i)))
            {
                sng_fade_time_800C0430[i] = temp;
            }
        }

        sng_fadein_time_800BF05C = 0;
        sng_play_code_800C04F8 = -1;

        printf("SNG FADEOUT START(status=%x)\n", sng_status_800BF158);
        return 0;
    }

    printf("SNG FADEOUT CANCELED(status=%x)\n", sng_status_800BF158);
    return -1;
}

int SD_SongKaihiMode(void)
{
    int i;

    if (sng_status_800BF158 == 0)
    {
        return -1;
    }

    if (sng_fout_term_800C0518 != 0x1FFF)
    {
        sng_fade_time_800C0430[2] = 43;
        sng_fade_time_800C0430[3] = 43;

        for (i = 4; i < 13; i++)
        {
            if (!(sng_fout_term_800C0518 & (1 << i)))
            {
                sng_fade_time_800C0430[i] = 81;
            }
        }

        sng_fadein_time_800BF05C = 0;
        sng_kaihi_fg_800BF290 = 1;
        return 0;
    }

    return -1;
}

void SngFadeWkSet(void)
{
    int i;

    if (sng_fadein_fg_800C041C == 0)
    {
         sng_fadein_time_800BF05C = 0;

        for (i = 0; i < 13; i++)
        {
            sng_fade_time_800C0430[i] = 0;
        }

        for (i = 0; i < 13; i++)
        {
            sng_fade_value_800C0538[i] = 0;
        }

        sng_fout_term_800C0518 = 0;
        sng_fout_fg_800BF25C = 0;
        return;
    }

    switch (sng_fadein_fg_800C041C)
    {
    case 0x01FFFF03: /* fallthrough */
    case 0x01FFFF04: /* fallthrough */
    case 0x01FFFF05:
        SD_SongFadeIn_helper(sng_fadein_fg_800C041C);

        for (i = 0; i < 13; i++)
        {
            sng_fade_value_800C0538[i] = 65536;
        }

        sng_fadein_fg_800C041C = 0;
        break;
    }

    sng_fout_term_800C0518 = 0;
    sng_fout_fg_800BF25C = 0;
}

void SD_80085164(void)
{
    char temp[64]; // This function allocates 64 bytes of unused stack space
    int fade_time_bitmap;
    int fade_value_bitmap;
    int i;
    unsigned int var_t0;
    unsigned int var_a0_3;
    unsigned int var_v1_3;

    fade_time_bitmap = 0;
    fade_value_bitmap = 0;

    if (sng_status_800BF158 < 3)
    {
        return;
    }

    for (i = 0; i < 13; i++)
    {
        fade_time_bitmap |= sng_fade_time_800C0430[i];
    }

    if (fade_time_bitmap != 0)
    {
        for (i = 0; i < 13; i++)
        {
            if (sng_fade_time_800C0430[i] == 0)
            {
                continue;
            }

            sng_fade_value_800C0538[i] += sng_fade_time_800C0430[i];

            if (sng_fade_value_800C0538[i] >= 0x10000)
            {
                sng_fout_term_800C0518 |= (1 << i);
                sng_fade_value_800C0538[i] = 0x10000;
                sng_fade_time_800C0430[i] = 0;
            }

            if (sng_fout_term_800C0518 == 0x1fff)
            {
                if (sng_play_code_800C04F8 == -1)
                {
                    sng_status_800BF158 = 4;
                }
                else
                {
                    sng_fout_fg_800BF25C = 1;
                }
            }
            else
            {
                sng_fout_fg_800BF25C = 0;
            }
        }
    }
    else
    {
        if ((dword_800C0580 != 0) && (str_status_800BF16C != 0))
        {
            if (dword_800BF154 < 0x6000)
            {
                dword_800BF154 += 245;

                if (dword_800BF154 > 0x6000)
                {
                    dword_800BF154 = 0x6000;
                }
            }
        }
        else
        {
            if (dword_800BF154 != 0)
            {
                dword_800BF154 -= 245;

                if (dword_800BF154 < 0)
                {
                    dword_800BF154 = 0;
                }
            }
        }

        if (sng_fadein_time_800BF05C != 0)
        {
            for (i = 0; i < 13; i++)
            {
                if (sng_fadein_time_800BF05C >= sng_fade_value_800C0538[i])
                {
                    sng_fade_value_800C0538[i] = 0;
                }
                else
                {
                    sng_fade_value_800C0538[i] -= sng_fadein_time_800BF05C;
                }

                fade_value_bitmap |= sng_fade_value_800C0538[i];
            }

            if (fade_value_bitmap == 0)
            {
                sng_fadein_time_800BF05C = 0;
            }
        }
    }

    if (sng_syukan_fg_800C0510 != 0)
    {
        if (dword_800BF008 < 0x5000)
        {
            dword_800BF008 += 204;

            if (dword_800BF008 > 0x5000)
            {
                dword_800BF008 = 0x5000;
            }
        }
    }
    else
    {
        if (dword_800BF008 != 0)
        {
            dword_800BF008 -= 204;

            if (dword_800BF008 < 0)
            {
                dword_800BF008 = 0;
            }
        }
    }

    if (dword_800BF154 <= dword_800BF008)
    {
        var_t0 = dword_800BF008;
    }
    else
    {
        var_t0 = dword_800BF154;
    }

    for (i = 0; i < 13; i++)
    {
        var_a0_3 = 0x10000;

        if (var_t0 < sng_fade_value_800C0538[i])
        {
            var_v1_3 = sng_fade_value_800C0538[i];
        }
        else
        {
            var_v1_3 = var_t0;
        }

        if (var_v1_3 > var_a0_3)
        {
            var_a0_3 = 0;
        }
        else
        {
            var_a0_3 -= var_v1_3;
        }

        sng_master_vol_800C0BC8[i] = var_a0_3;
    }
}

void SD_80085480(void)
{
    if (sng_kaihi_fg_800BF290 != 0)
    {
        if (sng_fade_in_2_800C0BC0 < 256)
        {
            sng_fade_in_2_800C0BC0++;
        }
    }
    else if (sng_fade_in_2_800C0BC0 != 0)
    {
        if (sng_fade_in_2_800C0BC0 <= 16)
        {
            sng_fade_in_2_800C0BC0 = 0;
        }
        else
        {
            sng_fade_in_2_800C0BC0 -= 16;
        }
    }
}

int SD_800854F0(void)
{
    sng_fp_800BF1D8 = SD_SongLoadData(sng_load_code_800C0428, 3);

    if (sng_fp_800BF1D8 < 0)
    {
        sng_fp_800BF1D8 = 0;
        printf("LoadSngData:File Open Error(%x)\n", sng_load_code_800C0428);
        sng_load_code_800C0428 = 0;
        return -1;
    }
    else
    {
        SD_80083954(sng_fp_800BF1D8, sng_data_800C0420, 0x4000);
        SD_8008395C(sng_fp_800BF1D8, 3);
        sng_fp_800BF1D8 = 0;
        printf("CompletedLoadSong(%x)\n", sng_load_code_800C0428);
        return 0;
    }
}

void init_sng_work(void)
{
    SOUND_W *ptr; // $a0

    for (mtrack_800BF1EC = 0; mtrack_800BF1EC < 21; mtrack_800BF1EC++)
    {
        ptr = &sound_w_800BF2A8[mtrack_800BF1EC];
        sptr_800C057C = ptr;
        ptr->mpointer = 0;
        ptr->lp3_addr = 0;
        ptr->lp2_addr = 0;
        ptr->lp1_addr = 0;
        sng_track_init(ptr);
    }

    keyons_800BF260 = 0;
    keyoffs_800BF29C = 0;
    sng_play_code_800C04F8 = 0;
    sng_load_code_800C0428 = 0;
}

void sng_adrs_set(int idx)
{
    int i;
    int addr;
    int addr2;

    addr = sng_data_800C0420[(idx & 0xF) * 4 + 1] << 8;
    addr += sng_data_800C0420[(idx & 0xF) * 4];

    song_end_800C04E8 &= ~0x1fff;

    for (i = 0; i < 13; i++)
    {
        addr2 =  sng_data_800C0420[addr + i * 4 + 2] << 16;
        addr2 += sng_data_800C0420[addr + i * 4 + 1] << 8;
        addr2 += sng_data_800C0420[addr + i * 4];

        if (addr2 != 0)
        {
            sound_w_800BF2A8[i].mpointer = &sng_data_800C0420[addr2];
            sng_track_init(&sound_w_800BF2A8[i]);
        }
        else
        {
            song_end_800C04E8 |= 1 << i;
        }
    }

    keyons_800BF260 &= ~0x1fff;
}

void se_adrs_set(int idx)
{
    se_playing_800BF068[idx].code = se_request_800BF0E0[idx].code;
    se_playing_800BF068[idx].pri = se_request_800BF0E0[idx].pri;
    se_playing_800BF068[idx].kind = se_request_800BF0E0[idx].kind;
    se_playing_800BF068[idx].character = se_request_800BF0E0[idx].character;
    se_playing_800BF068[idx].addr = se_request_800BF0E0[idx].addr;

    se_request_800BF0E0[idx].code = 0;
    se_request_800BF0E0[idx].pri = 0;
    se_request_800BF0E0[idx].character = 0;

    sng_track_init(&sound_w_800BF2A8[idx + 13]);

    se_vol_800BF1F0[idx] = 2 * (se_playing_800BF068[idx].code & 0x3f00);

    song_end_800C04E8 &= ~(1 << (idx + 13));
    keyons_800BF260 &= ~(1 << (idx + 13));
    se_pan_800BF1B8[idx] = ((se_playing_800BF068[idx].code >> 16) + 32) & 0x3f;
    keyoffs_800BF29C = keyoffs_800BF29C & ~(1 << (idx + 13));

    sound_w_800BF2A8[idx + 13].mpointer = se_playing_800BF068[idx].addr;

    if (se_playing_800BF068[idx].kind)
    {
        if (se_rev_on_800C0574)
        {
            dword_800BF064 |= spu_ch_tbl[mtrack_800BF1EC + 1];
        }
        else
        {
            dword_800BF210 |= spu_ch_tbl[mtrack_800BF1EC + 1];
        }
    }
}

void sng_track_init(SOUND_W *ptr)
{
    ptr->ngc      = 1;
    ptr->pvod     = 127;
    ptr->vol      = 127;
    ptr->pand     = 2560;
    ptr->panf     = 10;
    ptr->tmpd     = 1;
    ptr->rdmd     = 0;
    ptr->ngo      = 0;
    ptr->ngs      = 0;
    ptr->ngg      = 0;
    ptr->lp1_cnt  = 0;
    ptr->lp2_cnt  = 0;
    ptr->lp1_vol  = 0;
    ptr->lp2_vol  = 0;
    ptr->lp1_freq = 0;
    ptr->lp2_freq = 0;
    ptr->pvoc     = 0;
    ptr->panoff   = 0;
    ptr->panmod   = 0;
    ptr->swsk     = 0;
    ptr->swsc     = 0;
    ptr->vibd     = 0;
    ptr->vibdm    = 0;
    ptr->tred     = 0;
    ptr->snos     = 0;
    ptr->ptps     = 0;
    ptr->dec_vol  = 0;
    ptr->tund     = 0;
    ptr->tmp      = 255;
    ptr->tmpc     = 0;
}
