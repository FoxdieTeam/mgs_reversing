#include <stdio.h>
#include <stddef.h>
#include <libspu.h>

#include "sd_incl.h"
#include "sd_ext.h"

#include "../mts/mts.h"
#include "../mts/taskid.h"

/* in sd_str.c */
extern int str_tick_count;
extern void StrFadeIn(unsigned int fade_speed);
extern int StrFadeOut(unsigned int fade_speed);
extern int StrFadeOutStop(unsigned int fade_speed);

/* in se_tbl.c */
extern struct SETBL se_tbl[128];

void sd_set(int sound_code);

/*----------------------------------------------------------------------*/

int sd_task_active(void)
{
    if (sd_task_status & SD_TASK_ACTIVE) {
        return 1;
    }
    return 0;
}

/*----------------------------------------------------------------------*/

int sd_str_play(void)
{
    return (str_status > 4);
}

int sd_sng_play(void)
{
    return (sng_status > 2);
}

int sd_se_play(void)
{
    int i;
    int bits;

    i = 0;
    bits = song_end >> SE_START_TRACK;
    for (i = 0; i < SE_TRACK_NUM; i++) {
        if ((bits & 1) == 0 && se_playing[i].pri != 255) {
            return se_playing[i].code;
        }
        bits >>= 1;
    }
    return 0;
}

int sd_se_play2(void)
{
    int i;
    int bits;

    i = 0;
    bits = song_end >> SE_START_TRACK;
    for (i = 0; i < SE_TRACK_NUM; i++) {
        if ((bits & 1) == 0 && se_playing[i].pri == 255) {
            return se_playing[i].code;
        }
        bits >>= 1;
    }
    return 0;
}

/*----------------------------------------------------------------------*/

int sd_set_cli(int sound_code, int sync_mode)
{
    sd_set(sound_code);
    return 0;
}

/*----------------------------------------------------------------------*/

void sd_set_path(const char *str)
{
    strcpy(pcm_path, str);
}

/*----------------------------------------------------------------------*/

int get_sng_code(void)
{
    if ((sng_play_code == 0xFFFFFFFF) || (sng_play_code == 0)) {
        return 0;
    } else {
        return sng_play_code;
    }
}

/*----------------------------------------------------------------------*/

unsigned char *get_sd_buf(int size)
{
    /* do nothing */
}

/*----------------------------------------------------------------------*/

void start_xa_sd(void)
{
    SpuCommonAttr c_attr;

    c_attr.mask = SPU_COMMON_CDVOLL | SPU_COMMON_CDVOLR | SPU_COMMON_CDMIX;
    c_attr.cd.volume.left = 0x7FFF;
    c_attr.cd.volume.right = 0x7FFF;
    c_attr.cd.mix = SPU_ON;
    SpuSetCommonAttr(&c_attr);
    printf("***XA Sound Start***\n");
}

void stop_xa_sd(void)
{
    SpuCommonAttr c_attr;

    c_attr.mask = SPU_COMMON_CDVOLL | SPU_COMMON_CDVOLR | SPU_COMMON_CDMIX;
    c_attr.cd.volume.left = 0;
    c_attr.cd.volume.right = 0;
    c_attr.cd.mix = SPU_OFF;
    SpuSetCommonAttr(&c_attr);
    printf("***XA Sound Stop***\n");
}

/*----------------------------------------------------------------------*/

int SePlay(int sound_code)
{
    int                 priority;
    int                 i, j;
    unsigned int        idx;
    int                 se_code;
    struct SEPLAYTBL    se_tmp;

    j = song_end >> SE_START_TRACK;
    for (i = 0; i < SE_TRACK_NUM; i++) {
        if (j & 1) {
            se_playing[i].code = 0;
            se_playing[i].pri = 0;
            se_playing[i].character = 0;
        }
        j >>= 1;
    }

    se_code = sound_code & 0xFF;

    se_tmp.code = sound_code;
    if (se_code < 0x80) {
        se_tracks = se_tbl[se_code].tracks;
        se_tmp.character = se_tbl[se_code].character;
    } else {
        se_tracks = se_header[se_code - 128].tracks;
        se_tmp.character = se_header[se_code - 128].character;
    }

    for (idx = 0; idx < se_tracks; idx++) {
        if (se_code < 0x80) {
            se_tmp.pri = se_tbl[se_code].pri;
            se_tmp.kind = se_tbl[se_code].kind;
            se_tmp.addr = se_tbl[se_code].addr[idx];
        } else {
            se_tmp.pri = se_header[se_code - 128].pri;
            se_tmp.kind = se_header[se_code - 128].kind;
            se_tmp.addr = (unsigned int)se_header[se_code - 128].addr[idx] + se_data;
        }
        priority = 0x100;
        j = 0;

        for (i = 0; i < SE_TRACK_NUM; i++) {
            if (((se_playing[i].code & 0xFF) == se_code) && !se_request[i].code) {
                priority = 0;
                j = i;
                break;
            }
            else if (se_tracks == 1 && ((se_request[i].code & 0xFF) == se_code))
            {
                priority = 0;
                j = i;
                break;
            }

            if (se_tmp.character) {
                if (se_playing[i].character == se_tmp.character) {
                    priority = 0;
                    j = i;
                    break;
                } else {
                    if (se_request[i].character == se_tmp.character) {
                        priority = 0;
                        j = i;
                        break;
                    }
                }
            }
        }

        if (j != i) {
            for (i = 0; i < SE_TRACK_NUM; i++) {
                if ((se_playing[i].code != 0) || (se_request[i].code != 0)) {
                    continue;
                }
                priority = 0;
                j = i;
                break;
            }

            if (j != i) {
                for (i = 0; i < SE_TRACK_NUM; i++) {
                    if (se_request[i].code == 0) {
                        if (se_playing[i].pri <= priority) {
                            priority = se_playing[i].pri;
                            j = i;
                        }
                    } else {
                        if (se_request[i].pri <= priority) {
                            priority = se_request[i].pri;
                            j = i;
                        }
                    }
                }
            }
        }

        if (se_tmp.pri >= priority) {
            se_request[j].pri = se_tmp.pri;
            se_request[j].kind = se_tmp.kind;
            se_request[j].character = se_tmp.character;
            se_tmp.character = 0;
            se_request[j].addr = se_tmp.addr;
            se_request[j].code = se_tmp.code;
            if (se_tmp.pri == 0xFF) {
                stop_jouchuu_se = 0;
            }
        }
    }

    se_tracks = 0;
    return 0;
}

/*----------------------------------------------------------------------*/

int get_str_counter(void)
{
    return str_tick_count;
}

/*----------------------------------------------------------------------*/

void sd_set(int sound_code)
{
    int new_bgm_idx;

    if (sd_print_fg != 0) {
        printf("SdCode=%x\n", sound_code);
    }

    if ((sound_code & 0xFF000000) == 0x00000000) {
        if ((sound_code & 0xFF) == 0) goto SdSetEnd;
    #ifdef VR_EXE
        if (se_stop_fg) goto SdSetEnd;
    #endif
        SePlay(sound_code);
        goto SdSetEnd;
    }
    if ((sound_code & 0xFF000000) == 0x01000000) {
        if (sd_sng_code_buf[bgm_idx] == 0) {
            new_bgm_idx = (bgm_idx + 1) & 0x0F;
            sd_sng_code_buf[bgm_idx] = sound_code;
            bgm_idx = new_bgm_idx;
            goto SdSetEnd;
        }
        printf("***TooMuchBGMSoundCode(%x)***\n", sound_code);
        goto SdSetEnd;
    }
    if ((sound_code & 0xFF000000) == 0x02000000) {
        printf("SdCode=%x\n", sound_code);
        se_load_code = sound_code;
        goto SdSetEnd;
    }
    if ((sound_code & 0xFF000000) == 0xFE000000) {
        if (wave_save_code != sound_code && se_save_code2 != sound_code)
        {
            wave_load_code = sound_code;
            wave_load_status = 1;
            mts_wup_tsk(MTSID_SOUND_MAIN);
        }
        goto SdSetEnd;
    }

    if ((sound_code >= 0xE0000000) && (sound_code < 0xE1000000)) {
        if (str_status == 0) {
            if (str_load_code == -1) {
                str_fade_time = 0;
                str_fade_value = 0;
            }
            str_vox_on = sound_code & 1;
            str_load_code = sound_code;
            str_status = 1;
            mts_wup_tsk(MTSID_SOUND_MAIN);
            goto SdSetEnd;
        }
        if (str_load_code != sound_code) {
            printf("SdSet:Last Stream Not Terminated.(status=%x)\n", str_status);
            goto SdSetEnd;
        }
        printf("SdSet:Same Stream is Already Played.(code=%x)\n", sound_code);
        goto SdSetEnd;
    }

    switch (sound_code) {
#ifdef VR_EXE
    case 0xFF000003:
        se_stop_fg = 1;
        break;
    case 0xFF000004:
        se_stop_fg = 0;
        break;
#endif
    case 0xFF000005:
        sound_mono_fg = 1;
        break;
    case 0xFF000006:
        sound_mono_fg = 0;
        break;
    case 0xFF000007:
        se_rev_on = 1;
        vox_rev_on = 0;
        break;
    case 0xFF000008:
        se_rev_on = 0;
        vox_rev_on = 0;
        break;
    case 0xFF000009:
        se_rev_on = 1;
        vox_rev_on = 1;
        break;
    case 0xFF0000F4:
        StrFadeOut(INT1SEC);
        printf("*** STR FO(S) ***\n");
        break;
    case 0xFF0000F5:
        StrFadeOut(INT1SEC*2);
        printf("*** STR FO(M) ***\n");
        break;
    case 0xFF0000F6:
        StrFadeOut(INT1SEC*5);
        printf("*** STR FO(L) ***\n");
        break;
    case 0xFF0000F7:
        StrFadeOut(INT1SEC*10);
        printf("*** STR FO(LL) ***\n");
        break;
    case 0xFF0000F8:
        if (str_load_code != -1) {
            str_fout_fg = 0;
            if (str_status == 0) {
                str_fadein_fg = sound_code;
                printf("*** STR FI(M) at Next STR ***\n");
                break;
            }
            StrFadeIn(INT1SEC*2);
            printf("*** STR FI(M) Start ***\n");
            break;
        }
        printf("*** ERR:STR FI(M) ***\n");
        break;
    case 0xFF0000F9:
        if (str_load_code != -1) {
            str_fout_fg = 0;
            if (str_status == 0) {
                str_fadein_fg = sound_code;
                printf("*** STR FI(L) at Next STR***\n");
                break;
            }
            StrFadeIn(INT1SEC*5);
            printf("*** STR FI(L) Start ***\n");
            break;
        }
        printf("*** ERR:STR FI(L) ***\n");
        break;
    case 0xFF0000FA:
        StrFadeOutStop(INT1SEC);
        printf("*** STR FO(S)+STOP ***\n");
        break;
    case 0xFF0000FB:
        StrFadeOutStop(INT1SEC*2);
        printf("*** STR FO(M)+STOP ***\n");
        break;
    case 0xFF0000FC:
        StrFadeOutStop(INT1SEC*5);
        printf("*** STR FO(L)+STOP ***\n");
        break;
    case 0xFF0000FD:
        StrFadeOutStop(INT1SEC*10);
        printf("*** STR FO(LL)+STOP ***\n");
        break;
    case 0xFF0000FE:
        stop_jouchuu_se = 1;
        break;
    case 0xFFFFFFEC:
        SpuSetIRQ(SPU_OFF);
        break;
    case 0xFFFFFFED:
        SpuSetIRQ(SPU_ON);
        break;
    case 0xFFFFFFFD:
        StrFadeOutStop(INT1SEC/2);
        break;
    }

SdSetEnd:
    return;
}
