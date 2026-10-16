#include <stdio.h>
#include <stddef.h>
#include <libspu.h>

#include "sd_incl.h"
#include "sd_ext.h"

#include "../mts/mts.h"
#include "../mts/taskid.h"

/*--------------------*/
/*--- Song Control ---*/
/*--------------------*/
/*SONG PAUSE*/
#define SNG_PAUSEON     0x01FFFF01
#define SNG_PAUSEOFF    0x01FFFF02
/*SONG FADE IN*/
#define SNG_FIN_S       0x01FFFF03
#define SNG_FIN_M       0x01FFFF04
#define SNG_FIN_L       0x01FFFF05
/*SONG FADE OUT & PAUSE*/
#define SNG_FOUTP_SS    0x01FFFF06
#define SNG_FOUTP_S     0x01FFFF07
#define SNG_FOUTP_M     0x01FFFF08
#define SNG_FOUTP_L     0x01FFFF09
/*SONG FADE OUT & STOP*/
#define SNG_FOUTS_SS    0x01FFFF0A
#define SNG_FOUTS_S     0x01FFFF0B
#define SNG_FOUTS_M     0x01FFFF0C
#define SNG_FOUTS_L     0x01FFFF0D
/*Kaihi MODE*/
#define SNG_KAIHI_01    0x01FFFF10
/*Syukan MODE*/
#define SNG_SYUKAN_ON   0x01FFFF20
#define SNG_SYUKAN_OFF  0x01FFFF21

/*SONG STOP*/
#define SNG_STOP        0x01FFFFFF
/*SONG PLAY CODE*/
#define SNG_PLAY_01     0x01000001
#define SNG_PLAY_02     0x01000002
#define SNG_PLAY_03     0x01000003
#define SNG_PLAY_04     0x01000004
#define SNG_PLAY_05     0x01000005
#define SNG_PLAY_06     0x01000006
#define SNG_PLAY_07     0x01000007
#define SNG_PLAY_08     0x01000008

/*---------------------- External Declarations -------------------------*/

/* in sd_ioset.c */
extern void spuwr(void);
extern void sng_off(void);
extern void se_off(int i);
extern void sng_pause(void);
extern void sng_pause_off(void);

/* in sd_sub1.c */
extern int sound_sub(void);

/* in sd_file.c */
extern int PcmOpen(int code, int kind);
extern int PcmRead(int fd, unsigned char *buf, int size);
extern int PcmClose(int fd, int kind);

/*---------------------- Prototype Declarations ------------------------*/

void IntSdMain(void);
void SngFadeIn(unsigned int kind);
int SngFadeOutP(unsigned int kind);
int SngFadeOutS(unsigned int kind);
int SngKaihiP(void);
void SngFadeWkSet(void);
void SngFadeInt(void);
void SngTempoInt(void);
int LoadSngData(void);
void init_sng_work(void);
void sng_adrs_set(int idx);
void se_adrs_set(int idx);
void sng_track_init(struct SOUND_W *ptr);

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/

void IntSdMain(void)
{
    int sd_sng_code;
    int pSngData;
    int i;
    unsigned char *track_ptr;
    int new_sng_status;
    struct SOUND_W *wTmp;

    if (sd_sng_code_buf[sd_code_read])
    {
        sd_sng_code = sd_sng_code_buf[sd_code_read];
        sd_sng_code_buf[sd_code_read] = 0;
        sd_code_read = (sd_code_read + 1) & 0xF;
        printf("SngCode=%x\n", sd_sng_code);
    }
    else
    {
        sd_sng_code = 0;
    }

    if (sd_sng_code)
    {
        switch (sd_sng_code)
        {
        case SNG_PAUSEON:
            sng_pause_fg = 1;
            sng_pause();
            printf("SongPauseOn\n");
            break;

        case SNG_PAUSEOFF:
            sng_pause_off();
            sng_pause_fg = 0;
            printf("SongPauseOff\n");
            break;

        case SNG_FIN_S: /* fallthrough */
        case SNG_FIN_M: /* fallthrough */
        case SNG_FIN_L:
            if (sng_play_code != 0xFFFFFFFF)
            {
                sng_fout_fg = 0;
                if (sng_status < 3)
                {
                    sng_fadein_fg = sd_sng_code;
                }
                else
                {
                    SngFadeIn(sd_sng_code);
                }
                sng_kaihi_fg = 0;
                sng_tempo_move = 0;
            }
            printf("SongFadein\n");
            break;

        case SNG_FOUTP_SS:  /* fallthrough */
        case SNG_FOUTP_S:   /* fallthrough */
        case SNG_FOUTP_M:   /* fallthrough */
        case SNG_FOUTP_L:
            SngFadeOutP(sd_sng_code);
            printf("SongFadeout&Pause\n");
            break;

        case SNG_FOUTS_SS:  /* fallthrough */
        case SNG_FOUTS_S:   /* fallthrough */
        case SNG_FOUTS_M:   /* fallthrough */
        case SNG_FOUTS_L:
            SngFadeOutS(sd_sng_code);
            printf("SongFadeout&Stop\n");
            break;

        case SNG_KAIHI_01:
            SngKaihiP();
            printf("SongKaihiMode\n");
            break;

        case SNG_SYUKAN_ON:
            sng_syukan_fg = 1;
            printf("SongSyukanMode On\n");
            break;

        case SNG_SYUKAN_OFF:
            sng_syukan_fg = 0;
            printf("SongSyukanMode Off\n");
            break;

        case SNG_STOP:
            sng_play_code = 0;
            sng_off();
            printf("SongStop\n");
            break;

        case SNG_PLAY_01: /* fallthrough */
        case SNG_PLAY_02: /* fallthrough */
        case SNG_PLAY_03: /* fallthrough */
        case SNG_PLAY_04: /* fallthrough */
        case SNG_PLAY_05: /* fallthrough */
        case SNG_PLAY_06: /* fallthrough */
        case SNG_PLAY_07: /* fallthrough */
        case SNG_PLAY_08:
            if (sng_play_code != sd_sng_code)
            {
                if (sng_status >= 2)
                {
                    pSngData = sng_data[0];
                    if (pSngData < (sd_sng_code & 0xF))
                    {
                        printf("ERROR:SNG PLAY CODE(%x/%x)\n", sd_sng_code, pSngData);
                    }
                    else
                    {
                        sng_status = 2;
                        if (sng_play_code == -1)
                        {
                            for (i=0; i < SNG_TRACK_NUM; i++)
                            {
                                sng_fade_time[i] = 0;
                                sng_fade_value[i] = 0;
                                sng_master_vol[i] = 0;
                            }
                            sng_fout_term = 0;
                        }
                        sng_play_code = sd_sng_code;
                        sng_off();
                        sng_pause_fg = 0;
                        sng_kaihi_fg = 0;
                        sng_tempo_move = 0;
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
            if (sng_load_code != sd_sng_code)
            {
                sng_load_code = sd_sng_code;
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
            while ((unsigned int)mtrack < SNG_TRACK_NUM);

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

    for (mtrack = SE_START_TRACK; mtrack < INTERNAL_TRACK_NUM; mtrack++)
    {
        if (se_tracks < 2 && se_request[mtrack - SNG_TRACK_NUM].code)
        {
            se_off(mtrack - SNG_TRACK_NUM);
            se_adrs_set(mtrack - SNG_TRACK_NUM);
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

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/

static inline void SngFadeIn_helper(unsigned int kind)
{
    int i;

    switch (kind)
    {
    case SNG_FIN_S:
        sng_fadein_time = SNG_VOL / (INT1SEC);
        break;
    case SNG_FIN_M:
        sng_fadein_time = SNG_VOL / (INT1SEC*3);
        break;
    case SNG_FIN_L:
        sng_fadein_time = SNG_VOL / (INT1SEC*5);
        break;
    }

    if (sng_fadein_time == 0)
    {
        sng_fadein_time = 1;
    }

    for (i = 0; i < SNG_TRACK_NUM; i++)
    {
        sng_fade_time[i] = 0;
    }

    sng_fout_term = 0;
}

void SngFadeIn(unsigned int kind)
{
    SngFadeIn_helper(kind);
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/

int SngFadeOutP(unsigned int kind)
{
    int fade_time;
    int i;

    if (sng_status && sng_fout_term != 0x1FFF)
    {
        switch (kind)
        {
        case SNG_FOUTP_SS:
            fade_time = SNG_VOL / (INT1SEC/2);
            break;
        case SNG_FOUTP_S:
            fade_time = SNG_VOL / (INT1SEC);
            break;
        case SNG_FOUTP_M:
            fade_time = SNG_VOL / (INT1SEC*3);
            break;
        case SNG_FOUTP_L:
            fade_time = SNG_VOL / (INT1SEC*5);
            break;
        //default: fade_time = 0; break; // we like UB
        }

        if (!fade_time)
        {
            fade_time = 1;
        }

        for (i = 0; i < SNG_TRACK_NUM; i++)
        {
            if (!(sng_fout_term & (1 << i)))
            {
                sng_fade_time[i] = fade_time;
            }
        }

        sng_fadein_time = 0;
        return 0;
    }

    return -1;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/

int SngFadeOutS(unsigned int code)
{
    int fade_time;
    int i;

    if ((sng_status != 0) && ((sng_fout_term != 0x1FFF) || (sng_fadein_time != 0)))
    {
        switch (code)
        {
        case SNG_FOUTS_SS:
            fade_time = SNG_VOL / (INT1SEC/2);
            break;
        case SNG_FOUTS_S:
            fade_time = SNG_VOL / (INT1SEC);
            break;
        case SNG_FOUTS_M:
            fade_time = SNG_VOL / (INT1SEC*3);
            break;
        case SNG_FOUTS_L:
            fade_time = SNG_VOL / (INT1SEC*5);
            break;
        }

        if (fade_time == 0)
        {
            fade_time = 1;
        }

        for (i = 0; i < SNG_TRACK_NUM; i++)
        {
            if (!(sng_fout_term & (1 << i)))
            {
                sng_fade_time[i] = fade_time;
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

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
#define KAIHI_FO_RYTHM  (SNG_VOL/(INT1SEC*15))
#define KAIHI_FO_CHORD  (SNG_VOL/(INT1SEC*8))

int SngKaihiP(void)
{
    int i;

    if (sng_status == 0)
    {
        return -1;
    }

    if (sng_fout_term != 0x1FFF)
    {
        sng_fade_time[2] = KAIHI_FO_RYTHM;
        sng_fade_time[3] = KAIHI_FO_RYTHM;

        for (i = 4; i < SNG_TRACK_NUM; i++)
        {
            if (!(sng_fout_term & (1 << i)))
            {
                sng_fade_time[i] = KAIHI_FO_CHORD;
            }
        }

        sng_fadein_time = 0;
        sng_kaihi_fg = 1;
        return 0;
    }

    return -1;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/

void SngFadeWkSet(void)
{
    int i;

    if (sng_fadein_fg == 0)
    {
         sng_fadein_time = 0;

        for (i = 0; i < SNG_TRACK_NUM; i++)
        {
            sng_fade_time[i] = 0;
        }

        for (i = 0; i < SNG_TRACK_NUM; i++)
        {
            sng_fade_value[i] = 0;
        }

        sng_fout_term = 0;
        sng_fout_fg = 0;
        return;
    }

    switch (sng_fadein_fg)
    {
    case SNG_FIN_S: /* fallthrough */
    case SNG_FIN_M: /* fallthrough */
    case SNG_FIN_L:
        SngFadeIn_helper(sng_fadein_fg);

        for (i = 0; i < SNG_TRACK_NUM; i++)
        {
            sng_fade_value[i] = SNG_VOL;
        }

        sng_fadein_fg = 0;
        break;
    }

    sng_fout_term = 0;
    sng_fout_fg = 0;
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/

#define SYUKAN_MINUS_VOL    0x5000
#define VOX_MINUS_VOL       0x6000

void SngFadeInt(void)
{
    char temp[64]; // This function allocates 64 bytes of unused stack space
    int fout_on;
    int fin_off;
    int i;
    unsigned int var_t0;
    unsigned int vol1;
    unsigned int vol2;

    fout_on = 0;
    fin_off = 0;

    if (sng_status < 3)
    {
        return;
    }

    for (i = 0; i < SNG_TRACK_NUM; i++)
    {
        fout_on |= sng_fade_time[i];
    }

    if (fout_on != 0)
    {
        for (i = 0; i < SNG_TRACK_NUM; i++)
        {
            if (sng_fade_time[i] == 0)
            {
                continue;
            }

            sng_fade_value[i] += sng_fade_time[i];

            if (sng_fade_value[i] >= SNG_VOL)
            {
                sng_fout_term |= (1 << i);
                sng_fade_value[i] = SNG_VOL;
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
            if (vox_on_vol < VOX_MINUS_VOL)
            {
                vox_on_vol += (VOX_MINUS_VOL/INT1SEC);

                if (vox_on_vol > VOX_MINUS_VOL)
                {
                    vox_on_vol = VOX_MINUS_VOL;
                }
            }
        }
        else
        {
            if (vox_on_vol != 0)
            {
                vox_on_vol -= (VOX_MINUS_VOL/INT1SEC);

                if (vox_on_vol < 0)
                {
                    vox_on_vol = 0;
                }
            }
        }

        if (sng_fadein_time != 0)
        {
            for (i = 0; i < SNG_TRACK_NUM; i++)
            {
                if (sng_fadein_time >= sng_fade_value[i])
                {
                    sng_fade_value[i] = 0;
                }
                else
                {
                    sng_fade_value[i] -= sng_fadein_time;
                }

                fin_off |= sng_fade_value[i];
            }

            if (fin_off == 0)
            {
                sng_fadein_time = 0;
            }
        }
    }

    if (sng_syukan_fg != 0)
    {
        if (sng_syukan_vol < SYUKAN_MINUS_VOL)
        {
            sng_syukan_vol += (SYUKAN_MINUS_VOL/INT1SEC);

            if (sng_syukan_vol > SYUKAN_MINUS_VOL)
            {
                sng_syukan_vol = SYUKAN_MINUS_VOL;
            }
        }
    }
    else
    {
        if (sng_syukan_vol != 0)
        {
            sng_syukan_vol -= (SYUKAN_MINUS_VOL/INT1SEC);

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

    for (i = 0; i < SNG_TRACK_NUM; i++)
    {
        vol1 = SNG_VOL;

        if (var_t0 < sng_fade_value[i])
        {
            vol2 = sng_fade_value[i];
        }
        else
        {
            vol2 = var_t0;
        }

        if (vol2 > vol1)
        {
            vol1 = 0;
        }
        else
        {
            vol1 -= vol2;
        }

        sng_master_vol[i] = vol1;
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/
#define MOVE_TEMPO_VALUE    0x10

void SngTempoInt(void)
{
    if (sng_kaihi_fg != 0)
    {
        if (sng_tempo_move < (MOVE_TEMPO_VALUE*0x10))
        {
            sng_tempo_move++;
        }
    }
    else if (sng_tempo_move != 0)
    {
        if (sng_tempo_move <= MOVE_TEMPO_VALUE)
        {
            sng_tempo_move = 0;
        }
        else
        {
            sng_tempo_move -= MOVE_TEMPO_VALUE;
        }
    }
}

/*----------------------------------------------------------------------*/

int LoadSngData(void)
{
    sng_fp = PcmOpen(sng_load_code, KIND_MDX);

    if (sng_fp < 0)
    {
        sng_fp = 0;
        printf("LoadSngData:File Open Error(%x)\n", sng_load_code);
        sng_load_code = 0;
        return -1;
    }
    else
    {
        PcmRead(sng_fp, sng_data, SNG_DATA_SIZE);
        PcmClose(sng_fp, KIND_MDX);
        sng_fp = 0;
        printf("CompletedLoadSong(%x)\n", sng_load_code);
        return 0;
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/

void init_sng_work(void)
{
    struct SOUND_W *ptr;

    for (mtrack = 0; mtrack < INTERNAL_TRACK_NUM; mtrack++)
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

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/

void sng_adrs_set(int idx)
{
    int i;
    int addr;
    int addr2;

    addr = sng_data[(idx & 0xF) * 4 + 1] << 8;
    addr += sng_data[(idx & 0xF) * 4];

    song_end &= ~0x1fff;

    for (i = 0; i < SNG_TRACK_NUM; i++)
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

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/

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

    sng_track_init(&sound_w[idx + SNG_TRACK_NUM]);

    se_vol[idx] = 2 * (se_playing[idx].code & 0x3f00);

    song_end &= ~(1 << (idx + SNG_TRACK_NUM));
    keyons &= ~(1 << (idx + SNG_TRACK_NUM));
    se_pan[idx] = ((se_playing[idx].code >> 16) + 32) & 0x3f;
    keyoffs = keyoffs & ~(1 << (idx + SNG_TRACK_NUM));

    sound_w[idx + SNG_TRACK_NUM].mpointer = se_playing[idx].addr;

    if (se_playing[idx].kind)
    {
        if (se_rev_on)
        {
            rev_on_bit |= spu_ch_tbl[mtrack + 1];
        }
        else
        {
            rev_off_bit |= spu_ch_tbl[mtrack + 1];
        }
    }
}

/*----------------------------------------------------------------------*/
/*                                                                      */
/*----------------------------------------------------------------------*/

void sng_track_init(struct SOUND_W *ptr)
{
    ptr->ngc = 1;       /* sweep counter */
    ptr->pvod = 0x7F;   /* volume move data */
    ptr->vol = 0x7F;    /* volume (velosity) */
    ptr->pand = 2560;   /* pan data */
    ptr->panf = 10;     /* pan phase */
    ptr->tmpd = 1;      /* tempo counter */
    ptr->rdmd = 0;      /* LFO data */
    ptr->ngo = 0;       /* keyoff counter */
    ptr->ngs = 0;       /* step time */
    ptr->ngg = 0;       /* gate time */
    ptr->lp1_cnt = 0;   /* loop counter */
    ptr->lp2_cnt = 0;
    ptr->lp1_vol = 0;   /* loop volume */
    ptr->lp2_vol = 0;
    ptr->lp1_freq = 0;  /* loop frequency */
    ptr->lp2_freq = 0;
    ptr->pvoc = 0;      /* volume move counter */
    ptr->panoff = 0;    /* pan off flag */
    ptr->panmod = 0;    /* pan mode */
    ptr->swsk = 0;      /* sweep flag */
    ptr->swsc = 0;      /* sweep counter */
    ptr->vibd = 0;      /* vibrato depth */
    ptr->vibdm = 0;     /* vibrato depth memory */
    ptr->tred = 0;      /* tremolo depth */
    ptr->snos = 0;      /* tone number */
    ptr->ptps = 0;      /* part-transpose value */
    ptr->dec_vol = 0;   /* volume correction value */
    ptr->tund = 0;      /* tuning data */
    ptr->tmp = 0xFF;    /* tempo data */
    ptr->tmpc = 0;      /* tempo movement counter */
}
