#include "sd_incl.h"
#include "sd_ext.h"

#include <stdio.h>
#include <libspu.h>
#include "common.h"
#include "mts/mts.h"
#include "mts/taskid.h"

void IntSdMain(void)
{
    int temp;
    int pSngData;
    int i;
    unsigned char *track_ptr;
    int new_sng_status;
    SOUND_W* wTmp;

    if (sd_sng_code_buf[sd_code_read])
    {
        temp = sd_sng_code_buf[sd_code_read];
        sd_sng_code_buf[sd_code_read] = 0;
        sd_code_read = (sd_code_read + 1) & 0xF;
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
            sng_pause_fg = 1;
            sng_pause();
            printf("SongPauseOn\n");
            break;

        // Unpause
        case 0x01FFFF02:
            sng_pause_off();
            sng_pause_fg = 0;
            printf("SongPauseOff\n");
            break;

        // Fade in
        case 0x01FFFF03: /* fallthrough */
        case 0x01FFFF04: /* fallthrough */
        case 0x01FFFF05:
            if (sng_play_code != 0xFFFFFFFF)
            {
                sng_fout_fg = 0;
                if (sng_status < 3)
                {
                    sng_fadein_fg = temp;
                }
                else
                {
                    SngFadeIn(temp);
                }
                sng_kaihi_fg = 0;
                sng_kaihi_time = 0;
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
            SngFadeOutS(temp);
            printf("SongFadeout&Stop\n");
            break;

        // Evasion Mode
        case 0x01FFFF10:
            SngKaihiP();
            printf("SongKaihiMode\n");
            break;

        // First Person Mode
        case 0x01FFFF20:
            sng_syukan_fg = 1;
            printf("SongSyukanMode On\n");
            break;

        // Exit first person
        case 0x01FFFF21:
            sng_syukan_fg = 0;
            printf("SongSyukanMode Off\n");
            break;

        case 0x01FFFFFF:
            sng_play_code = 0;
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

            if (sng_play_code != temp)
            {
                if (sng_status >= 2)
                {
                    pSngData = sng_data[0];
                    if (pSngData < (temp & 0xF))
                    {
                        printf("ERROR:SNG PLAY CODE(%x/%x)\n", temp, pSngData);
                    }
                    else
                    {
                        sng_status = 2;
                        if (sng_play_code == -1)
                        {
                            for (i=0; i < 13; i++)
                            {
                                sng_fade_time[i] = 0;
                                sng_fade_value[i] = 0;
                                sng_master_vol[i] = 0;
                            }
                            sng_fout_term = 0;
                        }
                        sng_play_code = temp;
                        sng_off();
                        sng_pause_fg = 0;
                        sng_kaihi_fg = 0;
                        sng_kaihi_time = 0;
                    }
                }
                else
                {
                  printf("sng_status=%x\n", sng_status);
                }
            }
            else
            {
                printf("SameSongHasAlreadyPlayed\n");
            }
        break;

    default:
            if (sng_load_code != temp)
            {
                sng_load_code = temp;
                sng_play_code = 0;
                sng_status = 1;
                sng_off();
                mts_wup_tsk(MTSID_SOUND_MAIN);
            }

            break;
    }
    }

    switch (sng_status)
    {
        case 2:
            if (sng_play_code == 0)
            {
                break;
            }

            if (sng_play_code == -1)
            {
                break;
            }

            sng_adrs_set(sng_play_code);
            SngFadeWkSet();
            sng_status = 3;
            song_end_last = 0;
            break;

        case 3:
            if (song_end_last)
            {
                if ((song_end_last & 0x1FFF) != (song_end & 0x1FFF))
                {
                    printf("*** SOUND WORK IS BROKEN !!! ***\n");
                    printf("*** SOUND WORK IS BROKEN !!! ***\n");
                    printf("*** song_end:%x -> %x        ***\n",
                        song_end & 0x1FFF, song_end_last & 0x1FFF);
                    printf("*** SOUND WORK IS BROKEN !!! ***\n");
                    printf("*** SOUND WORK IS BROKEN !!! ***\n");
                }
            }

            SngFadeInt();
            SngTempoInt();

            mtrack = 0;

            do
            {
                keyd = spu_ch_tbl[mtrack + 1];
                if ((song_end & keyd) == 0)
                {
                    sptr = &sound_w[mtrack];
                    track_ptr = sptr->mpointer;
                    if (!track_ptr)
                    {
                        song_end |= keyd;
                    }
                    else
                    {
                        mptr = track_ptr;
                        if (sound_sub())
                        {
                            song_end |= keyd;
                            sptr->mpointer = 0;
                        }
                        else
                        {
                            sptr->mpointer = mptr;
                        }
                    }
                }
                ++mtrack;
            }
            while ((unsigned int)mtrack < 13);

            song_end_last = song_end;
            if ((song_end & 0x1FFF) == 0x1FFF)
            {
                new_sng_status = 4;
                sng_status = new_sng_status;
            }
            break;


        case 4:
            sng_off();
            new_sng_status = 2;
            sng_play_code = 0;
            sng_status = new_sng_status;
            break;

    }

    for (mtrack=13; mtrack < 21; mtrack++)
    {
        if (se_tracks < 2 && se_request[mtrack - 13].code)
        {
            se_off(mtrack - 13);
            se_adrs_set(mtrack - 13);
        }
        else
        {
            keyd = spu_ch_tbl[mtrack + 1];
            if ((song_end & keyd) == 0)
            {
                wTmp = &sound_w[mtrack];
                track_ptr = wTmp->mpointer;
                sptr = wTmp;
                if (!track_ptr)
                {
                    song_end |= keyd;
                }
                else
                {
                    mptr = track_ptr;
                    if (sound_sub())
                    {
                        song_end |= keyd;
                        sptr->mpointer = 0;
                    }
                    else
                    {
                        sptr->mpointer = mptr;
                    }

                }
            }
        }
    }

    if (stop_jouchuu_se >= 2)
    {
        stop_jouchuu_se = 0;
    }

    spuwr();
}

static inline void SngFadeIn_helper(unsigned int mode)
{
    int i;

    switch (mode)
    {
    case 0x01FFFF03:
        sng_fadein_time = 655;
        break;
    case 0x01FFFF04:
        sng_fadein_time = 218;
        break;
    case 0x01FFFF05:
        sng_fadein_time = 131;
        break;
    }

    if (sng_fadein_time == 0)
    {
        sng_fadein_time = 1;
    }

    for (i = 0; i < 13; i++)
    {
        sng_fade_time[i] = 0;
    }

    sng_fout_term = 0;
}

void SngFadeIn(unsigned int mode)
{
    SngFadeIn_helper(mode);
}

int SngFadeOutP(unsigned int code)
{
    int temp;
    int i;

    if (sng_status && sng_fout_term != 0x1FFF)
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
            if (!(sng_fout_term & (1 << i)))
            {
                sng_fade_time[i] = temp;
            }
        }

        sng_fadein_time = 0;
        return 0;
    }

    return -1;
}

int SngFadeOutS(unsigned int code)
{
    int temp;
    int i;

    if ((sng_status != 0) && ((sng_fout_term != 0x1FFF) || (sng_fadein_time != 0)))
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
            if (!(sng_fout_term & (1 << i)))
            {
                sng_fade_time[i] = temp;
            }
        }

        sng_fadein_time = 0;
        sng_play_code = -1;

        printf("SNG FADEOUT START(status=%x)\n", sng_status);
        return 0;
    }

    printf("SNG FADEOUT CANCELED(status=%x)\n", sng_status);
    return -1;
}

int SngKaihiP(void)
{
    int i;

    if (sng_status == 0)
    {
        return -1;
    }

    if (sng_fout_term != 0x1FFF)
    {
        sng_fade_time[2] = 43;
        sng_fade_time[3] = 43;

        for (i = 4; i < 13; i++)
        {
            if (!(sng_fout_term & (1 << i)))
            {
                sng_fade_time[i] = 81;
            }
        }

        sng_fadein_time = 0;
        sng_kaihi_fg = 1;
        return 0;
    }

    return -1;
}

void SngFadeWkSet(void)
{
    int i;

    if (sng_fadein_fg == 0)
    {
         sng_fadein_time = 0;

        for (i = 0; i < 13; i++)
        {
            sng_fade_time[i] = 0;
        }

        for (i = 0; i < 13; i++)
        {
            sng_fade_value[i] = 0;
        }

        sng_fout_term = 0;
        sng_fout_fg = 0;
        return;
    }

    switch (sng_fadein_fg)
    {
    case 0x01FFFF03: /* fallthrough */
    case 0x01FFFF04: /* fallthrough */
    case 0x01FFFF05:
        SngFadeIn_helper(sng_fadein_fg);

        for (i = 0; i < 13; i++)
        {
            sng_fade_value[i] = 65536;
        }

        sng_fadein_fg = 0;
        break;
    }

    sng_fout_term = 0;
    sng_fout_fg = 0;
}

void SngFadeInt(void)
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

    if (sng_status < 3)
    {
        return;
    }

    for (i = 0; i < 13; i++)
    {
        fade_time_bitmap |= sng_fade_time[i];
    }

    if (fade_time_bitmap != 0)
    {
        for (i = 0; i < 13; i++)
        {
            if (sng_fade_time[i] == 0)
            {
                continue;
            }

            sng_fade_value[i] += sng_fade_time[i];

            if (sng_fade_value[i] >= 0x10000)
            {
                sng_fout_term |= (1 << i);
                sng_fade_value[i] = 0x10000;
                sng_fade_time[i] = 0;
            }

            if (sng_fout_term == 0x1fff)
            {
                if (sng_play_code == -1)
                {
                    sng_status = 4;
                }
                else
                {
                    sng_fout_fg = 1;
                }
            }
            else
            {
                sng_fout_fg = 0;
            }
        }
    }
    else
    {
        if ((dword_800C0580 != 0) && (str_status != 0))
        {
            if (vox_on_vol < 0x6000)
            {
                vox_on_vol += 245;

                if (vox_on_vol > 0x6000)
                {
                    vox_on_vol = 0x6000;
                }
            }
        }
        else
        {
            if (vox_on_vol != 0)
            {
                vox_on_vol -= 245;

                if (vox_on_vol < 0)
                {
                    vox_on_vol = 0;
                }
            }
        }

        if (sng_fadein_time != 0)
        {
            for (i = 0; i < 13; i++)
            {
                if (sng_fadein_time >= sng_fade_value[i])
                {
                    sng_fade_value[i] = 0;
                }
                else
                {
                    sng_fade_value[i] -= sng_fadein_time;
                }

                fade_value_bitmap |= sng_fade_value[i];
            }

            if (fade_value_bitmap == 0)
            {
                sng_fadein_time = 0;
            }
        }
    }

    if (sng_syukan_fg != 0)
    {
        if (sng_syukan_vol < 0x5000)
        {
            sng_syukan_vol += 204;

            if (sng_syukan_vol > 0x5000)
            {
                sng_syukan_vol = 0x5000;
            }
        }
    }
    else
    {
        if (sng_syukan_vol != 0)
        {
            sng_syukan_vol -= 204;

            if (sng_syukan_vol < 0)
            {
                sng_syukan_vol = 0;
            }
        }
    }

    if (vox_on_vol <= sng_syukan_vol)
    {
        var_t0 = sng_syukan_vol;
    }
    else
    {
        var_t0 = vox_on_vol;
    }

    for (i = 0; i < 13; i++)
    {
        var_a0_3 = 0x10000;

        if (var_t0 < sng_fade_value[i])
        {
            var_v1_3 = sng_fade_value[i];
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

        sng_master_vol[i] = var_a0_3;
    }
}

void SngTempoInt(void)
{
    if (sng_kaihi_fg != 0)
    {
        if (sng_kaihi_time < 256)
        {
            sng_kaihi_time++;
        }
    }
    else if (sng_kaihi_time != 0)
    {
        if (sng_kaihi_time <= 16)
        {
            sng_kaihi_time = 0;
        }
        else
        {
            sng_kaihi_time -= 16;
        }
    }
}

int LoadSngData(void)
{
    sng_fp = PcmOpen(sng_load_code, 3);

    if (sng_fp < 0)
    {
        sng_fp = 0;
        printf("LoadSngData:File Open Error(%x)\n", sng_load_code);
        sng_load_code = 0;
        return -1;
    }
    else
    {
        PcmRead(sng_fp, sng_data, 0x4000);
        PcmClose(sng_fp, 3);
        sng_fp = 0;
        printf("CompletedLoadSong(%x)\n", sng_load_code);
        return 0;
    }
}

void init_sng_work(void)
{
    SOUND_W *ptr;

    for (mtrack = 0; mtrack < 21; mtrack++)
    {
        ptr = &sound_w[mtrack];
        sptr = ptr;
        ptr->mpointer = 0;
        ptr->lp3_addr = 0;
        ptr->lp2_addr = 0;
        ptr->lp1_addr = 0;
        sng_track_init(ptr);
    }

    keyons = 0;
    keyoffs = 0;
    sng_play_code = 0;
    sng_load_code = 0;
}

void sng_adrs_set(int idx)
{
    int i;
    int addr;
    int addr2;

    addr = sng_data[(idx & 0xF) * 4 + 1] << 8;
    addr += sng_data[(idx & 0xF) * 4];

    song_end &= ~0x1fff;

    for (i = 0; i < 13; i++)
    {
        addr2 =  sng_data[addr + i * 4 + 2] << 16;
        addr2 += sng_data[addr + i * 4 + 1] << 8;
        addr2 += sng_data[addr + i * 4];

        if (addr2 != 0)
        {
            sound_w[i].mpointer = &sng_data[addr2];
            sng_track_init(&sound_w[i]);
        }
        else
        {
            song_end |= 1 << i;
        }
    }

    keyons &= ~0x1fff;
}

void se_adrs_set(int idx)
{
    se_playing[idx].code = se_request[idx].code;
    se_playing[idx].pri = se_request[idx].pri;
    se_playing[idx].kind = se_request[idx].kind;
    se_playing[idx].character = se_request[idx].character;
    se_playing[idx].addr = se_request[idx].addr;

    se_request[idx].code = 0;
    se_request[idx].pri = 0;
    se_request[idx].character = 0;

    sng_track_init(&sound_w[idx + 13]);

    se_vol[idx] = 2 * (se_playing[idx].code & 0x3f00);

    song_end &= ~(1 << (idx + 13));
    keyons &= ~(1 << (idx + 13));
    se_pan[idx] = ((se_playing[idx].code >> 16) + 32) & 0x3f;
    keyoffs = keyoffs & ~(1 << (idx + 13));

    sound_w[idx + 13].mpointer = se_playing[idx].addr;

    if (se_playing[idx].kind)
    {
        if (se_rev_on)
        {
            eons |= spu_ch_tbl[mtrack + 1];
        }
        else
        {
            eoffs |= spu_ch_tbl[mtrack + 1];
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
