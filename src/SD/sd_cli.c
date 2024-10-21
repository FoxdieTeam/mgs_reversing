#include "SD/sd_incl.h"
#include "SD/sd_ext.h"

#include <stdio.h>
#include <libspu.h>
#include "common.h"
#include "mts/mts.h"
#include "mts/taskid.h"

extern SETBL *se_exp_table_800C0520;

int sd_task_active(void)
{
    if (sd_task_status_800C0BFC & 0x80)
    {
        return 1;
    }
    return 0;
}

int sd_str_play(void)
{
    return str_status_800BF16C > 4;
}

int sd_sng_play(void)
{
    return sng_status_800BF158 > 2;
}

int sd_se_play(void)
{
    int i;    // $a1
    int bits; // $a0

    i = 0;
    bits = song_end_800C04E8 >> 13;
    for (i = 0; i < 8; i++)
    {
        if ((bits & 1) == 0 && se_playing_800BF068[i].pri != 255)
        {
            return se_playing_800BF068[i].code;
        }
        bits >>= 1;
    }
    return 0;
}

int sd_se_play2(void)
{
    int i;    // $a1
    int bits; // $a0

    i = 0;
    bits = song_end_800C04E8 >> 13;
    for (i = 0; i < 8; i++)
    {
        if ((bits & 1) == 0 && se_playing_800BF068[i].pri == 255)
        {
            return se_playing_800BF068[i].code;
        }
        bits >>= 1;
    }
    return 0;
}

void sd_set(int sound_code);

int sd_set_cli(int sound_code, int sync_mode)
{
    sd_set(sound_code);
    return 0;
}

void sd_set_path(const char *str)
{
    strcpy(byte_800C0468, str);
}

int get_sng_code(void)
{
    if (sng_play_code_800C04F8 == -1 || sng_play_code_800C04F8 == 0)
    {
        return 0;
    }

    return sng_play_code_800C04F8;
}

unsigned char *get_sd_buf(int size)
{
    /* do nothing */
}

void start_xa_sd(void)
{
    SpuCommonAttr c_attr;

    c_attr.mask = 704;
    c_attr.cd.volume.left = 0x7FFF;
    c_attr.cd.volume.right = 0x7FFF;
    c_attr.cd.mix = 1;
    SpuSetCommonAttr(&c_attr);
    printf("***XA Sound Start***\n");
}

void stop_xa_sd(void)
{
    SpuCommonAttr c_attr;

    c_attr.mask = 704;
    c_attr.cd.volume.left = 0;
    c_attr.cd.volume.right = 0;
    c_attr.cd.mix = 0;
    SpuSetCommonAttr(&c_attr);
    printf("***XA Sound Stop***\n");
}

int SePlay(int sound_code)
{
    SEPLAYTBL     se_tmp;
    int           i;
    unsigned int  idx;
    int           j;
    int           priority;
    int           pri;

    j = song_end_800C04E8 >> 13;
    for (i = 0; i < 8; j >>= 1, i++)
    {
        if ((j & 1) != 0)
        {
            se_playing_800BF068[i].code = 0;
            se_playing_800BF068[i].pri = 0;
            se_playing_800BF068[i].character = 0;
        }
    }

    se_tmp.code = sound_code;
    sound_code &= 0xFF;
    if (sound_code < 128)
    {
        se_tracks_800BF004 = se_tbl[sound_code].tracks;
        se_tmp.character = se_tbl[sound_code].character;
    }
    else
    {
        se_tracks_800BF004 = se_exp_table_800C0520[sound_code - 128].tracks;
        se_tmp.character = se_exp_table_800C0520[sound_code - 128].character;
    }
    for (idx = 0; idx < se_tracks_800BF004; idx++)
    {
        if (sound_code < 128)
        {
            se_tmp.pri = se_tbl[sound_code].pri;
            se_tmp.kind = se_tbl[sound_code].kind;
            se_tmp.addr = (char *)se_tbl[sound_code].addr[idx];
        }
        else
        {
            se_tmp.pri = se_exp_table_800C0520[sound_code - 128].pri;
            se_tmp.kind = se_exp_table_800C0520[sound_code - 128].kind;
            se_tmp.addr = se_exp_table_800C0520[sound_code - 128].addr[idx] + se_header_800BF284;
        }
        priority = 256;
        j = 0;
        for (i = 0; i < 8; i++)
        {
            if (((se_playing_800BF068[i].code & 0xFF) == sound_code) && !se_request_800BF0E0[i].code)
            {
                priority = 0;
                j = i;
                break;
            }
            else if (se_tracks_800BF004 == 1 && ((se_request_800BF0E0[i].code & 0xFF) == sound_code))
            {
                priority = 0;
                j = i;
                break;
            }
            if (se_tmp.character)
            {
                if (se_playing_800BF068[i].character == se_tmp.character)
                {
                    priority = 0;
                    j = i;
                    break;
                }
                else if (se_request_800BF0E0[i].character == se_tmp.character)
                {
                    priority = 0;
                    j = i;
                    break;
                }
            }
        }

        if (j != i)
        {
            for (i = 0; i < 8; i++)
            {
                if ((se_playing_800BF068[i].code != 0) ||
                     (se_request_800BF0E0[i].code != 0))
                {
                    continue;
                }
                priority = 0;
                j = i;
                break;
            }

            if (j != i)
            {
                for (i = 0; i < 8; i++)
                {
                    if (se_request_800BF0E0[i].code == 0)
                    {
                        pri = se_playing_800BF068[i].pri;
                    }
                    else
                    {
                        pri = se_request_800BF0E0[i].pri;
                    }
                    if (pri <= priority)
                    {
                        priority = pri;
                        j = i;
                    }
                }
            }
        }
        if (se_tmp.pri < priority)
        {
            continue;
        }
        se_request_800BF0E0[j].pri = se_tmp.pri;
        se_request_800BF0E0[j].kind = se_tmp.kind;
        se_request_800BF0E0[j].character = se_tmp.character;
        se_tmp.character = 0;
        se_request_800BF0E0[j].addr = se_tmp.addr;
        se_request_800BF0E0[j].code = se_tmp.code;
        if (se_tmp.pri == 0xFF)
        {
            stop_jouchuu_se_800BF1A0 = 0;
        }
    }

    se_tracks_800BF004 = 0;
    return 0;
}

int get_str_counter(void)
{
    return dword_8009F7B4;
}

void sd_set(int sound_code)
{
    int mode, new_bgm_idx;

    if (sd_print_fg != 0)
    {
        printf("SdCode=%x\n", sound_code);
    }

    mode = sound_code & 0xFF000000;
    if (mode == 0)
    {
        if (sound_code & 0xFF)
        {
        #ifdef VR_EXE
            if (dword_800BEFFC)
            {
                return;
            }
        #endif
            SePlay(sound_code);
        }
    }
    else if (mode == 0x01000000)
    {
        if (sd_sng_code_buf_800BF018[bgm_idx_800BF1E8] == 0)
        {
            new_bgm_idx = (bgm_idx_800BF1E8 + 1) & 0x0F;
            sd_sng_code_buf_800BF018[bgm_idx_800BF1E8] = sound_code;
            bgm_idx_800BF1E8 = new_bgm_idx;
            return;
        }

        printf("***TooMuchBGMSoundCode(%x)***\n", sound_code);
    }
    else if (mode == 0x02000000)
    {
        printf("SdCode=%x\n", sound_code);
        se_load_code_800BF28C = sound_code;
    }
    else if (mode == 0xFE000000)
    {
        if (wave_save_code_800C0578 != sound_code && dword_800C0410 != sound_code)
        {
            wave_load_code_800C0528 = sound_code;
            dword_800BF27C = 1;
            mts_wup_tsk(MTSID_SOUND_MAIN);
            return;
        }
    }
    else
    {
        if (sound_code >= 0xE0000000 && sound_code < 0xE1000000)
        {
            if (str_status_800BF16C == 0)
            {
                if (str_load_code_800C04F0 == -1)
                {
                    str_fade_time_800C04F4 = 0;
                    str_fade_value_800C0584 = 0;
                }
                str_vox_on_800BF160 = sound_code & 1;
                str_load_code_800C04F0 = sound_code;
                str_status_800BF16C = 1;
                mts_wup_tsk(MTSID_SOUND_MAIN);
                return;
            }
            if (str_load_code_800C04F0 != sound_code)
            {
                printf("SdSet:Last Stream Not Terminated.(status=%x)\n", str_status_800BF16C);
                return;
            }
            printf("SdSet:Same Stream is Already Played.(code=%x)\n", sound_code);
            return;
        }

        switch (sound_code)
        {
    #ifdef VR_EXE
        case 0xFF000003:
            dword_800BEFFC = 1;
            return;
        case 0xFF000004:
            dword_800BEFFC = 0;
            return;
    #endif
        case 0xFF000005:
            sound_mono_fg_800C050C = 1;
            return;
        case 0xFF000006:
            sound_mono_fg_800C050C = 0;
            return;
        case 0xFF000007:
            se_rev_on_800C0574 = 1;
            vox_rev_on_800BF144 = 0;
            return;
        case 0xFF000008:
            se_rev_on_800C0574 = 0;
            vox_rev_on_800BF144 = 0;
            return;
        case 0xFF000009:
            se_rev_on_800C0574 = 1;
            vox_rev_on_800BF144 = 1;
            return;

        case 0xFF0000F4:
            StrFadeOut(0x64);
            printf("*** STR FO(S) ***\n");
            return;
        case 0xFF0000F5:
            StrFadeOut(0xC8);
            printf("*** STR FO(M) ***\n");
            return;
        case 0xFF0000F6:
            StrFadeOut(0x1F4);
            printf("*** STR FO(L) ***\n");
            return;
        case 0xFF0000F7:
            StrFadeOut(0x3E8);
            printf("*** STR FO(LL) ***\n");
            return;
        case 0xFF0000F8:
            if (str_load_code_800C04F0 != -1)
            {
                str_fout_fg_800BF26C = 0;
                if (str_status_800BF16C == 0)
                {
                    str_fadein_fg_800C04EC = sound_code;
                    printf("*** STR FI(M) at Next STR ***\n");
                    return;
                }
                StrFadeIn(0xC8);
                printf("*** STR FI(M) Start ***\n");
                return;
            }
            printf("*** ERR:STR FI(M) ***\n");
            return;
        case 0xFF0000F9:
            if (str_load_code_800C04F0 != -1)
            {
                str_fout_fg_800BF26C = 0;
                if (str_status_800BF16C == 0)
                {
                    str_fadein_fg_800C04EC = sound_code;
                    printf("*** STR FI(L) at Next STR***\n");
                    return;
                }
                StrFadeIn(0x1F4);
                printf("*** STR FI(L) Start ***\n");
                return;
            }
            printf("*** ERR:STR FI(L) ***\n");
            return;
        case 0xFF0000FA:
            StrFadeOutStop(0x64);
            printf("*** STR FO(S)+STOP ***\n");
            return;
        case 0xFF0000FB:
            StrFadeOutStop(0xC8);
            printf("*** STR FO(M)+STOP ***\n");
            return;
        case 0xFF0000FC:
            StrFadeOutStop(0x1F4);
            printf("*** STR FO(L)+STOP ***\n");
            return;
        case 0xFF0000FD:
            StrFadeOutStop(0x3E8);
            printf("*** STR FO(LL)+STOP ***\n");
            return;
        case 0xFF0000FE:
            stop_jouchuu_se_800BF1A0 = 1;
            return;

        case 0xFFFFFFEC:
            SpuSetIRQ(0);
            return;
        case 0xFFFFFFED:
            SpuSetIRQ(1);
            return;
        case 0xFFFFFFFD:
            StrFadeOutStop(0x32);
            break;
        }
    }
}
