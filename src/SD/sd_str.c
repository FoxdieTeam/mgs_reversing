#include "SD/sound.h"
#include "SD/sd_incl.h"
#include "libfs/libfs.h"
#include "mts/mts_new.h"
#include "mts/taskid.h"
#include "psyq.h"
#include "unknown.h"

extern unsigned char    dummy_data_800A2D28[4096]; /* in sd_wk.c */
extern char            *stream_data_ptr_800BEFE4;
extern int              dword_800BEFE8;
extern int              dword_800BEFEC;
extern int              dword_800BEFF0;
extern int              dword_800BEFF4;
extern char            *cdload_buf_800BF010;
extern int              se_fp_800BF014;
extern char            *CDLOAD_BUF_800BF058;
extern int              spu_bgm_start_ptr_l_800BF060;
extern int              spu_bgm_start_ptr_r_800BF0C8;
extern int              blank_data_addr_800BF00C;
extern int              bstr_fade_inProgress_800BF0CC;
extern int              spu_load_offset_800BF140;
extern int              vox_rev_on_800BF144;
extern unsigned int     gStreamVol_800BF15C;
extern int              dword_800BF160;
extern int              dword_800BF164;
extern int              dword_800BF168;
extern unsigned int     gStr_FadeOut1_800BF16C;
extern int              dword_800BF1A4;
extern int              dword_800BF1A8;
extern int              str_unplay_size_800BF1AC;
extern int              dword_800BF1DC;
extern WAVE_W          *voice_tbl_800BF1E0;
extern int              dword_800BF264;
extern int              dword_800BF268;
extern int              dword_800BF26C;
extern int              dword_800BF270;
extern int              wave_unload_size_800BF274;
extern unsigned int     dword_800BF27C;
extern int              se_load_code_800BF28C;
extern int              wave_data_800BF294;
extern int              dword_800C040C;
extern int              dword_800C0414;
extern int              dword_800C0418;
extern int              dword_800C04EC;
extern int              gStream_800C04F0;
extern int              dword_800C04F4;
extern int              dword_800C0500;
extern int              dword_800C0504;
extern char            *wave_load_ptr_800C0508;
extern int              sound_mono_fg_800C050C;
extern int              dword_800C051C;
extern unsigned char   *se_exp_table_800C0520;
extern int              wave_load_code_800C0528;
extern unsigned char    byte_800C056C;
extern int              se_rev_on_800C0574;
extern int              wave_save_code_800C0578;
extern int              dword_800C0580;
extern unsigned int     gStr_fadeout_2_800C0584;
extern int              dword_800C0650;

/* in sd_main.c */
void nullsub_7_80081A10(int *arg0, int arg1, int arg2);
void keyOff_80081FC4(unsigned int ch);
void keyOn_80082170(unsigned int ch);

int dword_8009F7B4 = -1;
char *dword_8009F7B8 = 0;

void StrFadeIn_800822C8(unsigned int a1)
{
    bstr_fade_inProgress_800BF0CC = gStreamVol_800BF15C / a1;
    if (!(gStreamVol_800BF15C / a1))
    {
        bstr_fade_inProgress_800BF0CC = 1;
    }
    dword_800C04F4 = 0;
}

int StrFadeOut_80082310(unsigned int a1)
{
    if (gStr_FadeOut1_800BF16C)
    {
        if (gStr_fadeout_2_800C0584 != gStreamVol_800BF15C)
        {
            dword_800C04F4 = gStreamVol_800BF15C / a1;
            if (!(gStreamVol_800BF15C / a1))
            {
                dword_800C04F4 = 1;
            }
            bstr_fade_inProgress_800BF0CC = 0;
            return 0;
        }
    }
    return -1;
}

int StrFadeOutStop_80082380(unsigned int fadeSpeed)
{
    if (gStr_FadeOut1_800BF16C &&
         (gStr_fadeout_2_800C0584 != gStreamVol_800BF15C || bstr_fade_inProgress_800BF0CC))
    {
        dword_800C04F4 = gStreamVol_800BF15C / fadeSpeed;
        if (!(gStreamVol_800BF15C / fadeSpeed))
        {
            dword_800C04F4 = 1;
        }
        bstr_fade_inProgress_800BF0CC = 0;
        gStream_800C04F0 = -1;
        return 0;
    }
    else
    {
        printf("Canceled STR FadeOut(%x:%x:%x)",
                             gStr_FadeOut1_800BF16C,
                             gStr_fadeout_2_800C0584,
                             gStreamVol_800BF15C);
        return -1;
    }
}

int StartStream_80082448(void)
{
    if (!dword_800C04EC)
    {
        bstr_fade_inProgress_800BF0CC = 0;
        gStr_fadeout_2_800C0584 = 0;
        dword_800C04F4 = 0;
    }
    dword_800BF26C = 0;
    dword_8009F7B4 = -1;
    FS_StreamOpen_80024060();

    CDLOAD_BUF_800BF058 = FS_StreamGetData_800240E0(2);

    if (!CDLOAD_BUF_800BF058)
    {
        printf("Stream:File Pos Error\n");
        FS_StreamClose_80024098();
        return -1;
    }

    // Consume big-endian int from CDLOAD_BUF_800BF058
    dword_800C051C = CDLOAD_BUF_800BF058[0] << 24;
    dword_800C051C |= CDLOAD_BUF_800BF058[1] << 16;
    dword_800C051C |= CDLOAD_BUF_800BF058[2] << 8;
    dword_800C051C |= CDLOAD_BUF_800BF058[3];

    str_unplay_size_800BF1AC = dword_800BF168 = dword_800C051C;

    // Consume big-endian short from CDLOAD_BUF_800BF058
    gStreamVol_800BF15C = CDLOAD_BUF_800BF058[4] << 8;
    gStreamVol_800BF15C |= CDLOAD_BUF_800BF058[5];

    // Consume big-endian short from CDLOAD_BUF_800BF058
    dword_800C0504 = CDLOAD_BUF_800BF058[6] << 8;
    dword_800C0504 |= CDLOAD_BUF_800BF058[7];

    // Consume byte from CDLOAD_BUF_800BF058
    if (CDLOAD_BUF_800BF058[8] == 1)
    {
        dword_800BF268 = CDLOAD_BUF_800BF058[8];
    }
    else
    {
        dword_800BF268 = 0;
    }

    // Consume byte from CDLOAD_BUF_800BF058
    dword_800C0580 = CDLOAD_BUF_800BF058[9];

    printf("StartStream(%x:vol=%x)\n", gStream_800C04F0, gStreamVol_800BF15C);
    if (dword_800C04EC)
    {
        StrFadeWkSet_80083964();
    }

    keyOff_80081FC4(0x600000);
    dword_800BEFF0 = NULL;
    sub_800241B4(CDLOAD_BUF_800BF058);
    dword_800C0418 = NULL;
    dword_800BF1DC = NULL;
    return 0;
}

void UserSpuIRQProc_80082640(void)
{
    switch (gStr_FadeOut1_800BF16C & 0xf)
    {
    case 2: /* fallthrough */
    case 3:
        break;

    case 4:
        dword_800BEFF4 = 0;
        break;

    case 5:
        switch (dword_800C0504)
        {
        case 0x800:
            if ((dword_800BEFF4++ & 1) != 0)
            {
                dword_800BF270 += 0x100;
                dword_800BF270 &= 0x1fff;
            }
            break;

        case 0xc00:
            if ((dword_800BEFF4++ & 3) != 0)
            {
                dword_800BF270 += 0x100;
                dword_800BF270 &= 0x1fff;
            }
            break;

        default:
            dword_800BF270 += 0x100;
            dword_800BF270 &= 0x1fff;
            break;
        }
        break;

    case 6:
        switch (dword_800C0504)
        {
        case 0x800:
            if ((dword_800BEFF4++ & 1) != 0)
            {
                dword_800BF270 += 0x100;
                dword_800BF270 &= 0x1fff;
            }
            break;

        case 0xc00:
            if ((dword_800BEFF4++ & 3) != 0)
            {
                dword_800BF270 += 0x100;
                dword_800BF270 &= 0x1fff;
            }
            break;

        default:
            dword_800BF270 += 0x100;
            dword_800BF270 &= 0x1fff;
            break;
        }
        break;
    }

    mts_isend_80089B04(1);

    if ((dword_800BF1A8 & 1) == 0)
    {
        SpuSetIRQAddr(blank_data_addr_800BF00C + 256);
    }
    else
    {
        SpuSetIRQAddr(blank_data_addr_800BF00C);
    }

    dword_800BF1A8++;
    SpuSetIRQ(SPU_RESET);
}

void sub_8008279C(void)
{
}

void SD_nullsub_20_800827A4(void)
{
}

int StrSpuTransWithNoLoop_800827AC(void)
{
    SpuVoiceAttr attr;
    int          result;
    int          bVar1;
    u_long       start_addr;

    result = 0;

    if (dword_8009F7B8 != 0)
    {
        sub_800241B4(dword_8009F7B8);
        dword_8009F7B8 = 0;
    }

    switch (gStr_FadeOut1_800BF16C & 0xf)
    {
    case 2:
        if (dword_800BF1A4 == 0)
        {
            if ((se_rev_on_800C0574 != 0) && (dword_800BF160 != 0) && (vox_rev_on_800BF144 != 0))
            {
                SpuSetReverbVoice(1, 0x600000);
            }
            else
            {
                SpuSetReverbVoice(0, 0x600000);
            }

            stream_data_ptr_800BEFE4 = FS_StreamGetData_800240E0(1);

            if (stream_data_ptr_800BEFE4)
            {
                dword_800C040C = 0;
                dword_800BF164 = 0;
                stream_data_ptr_800BEFE4[1] |= 0x4;
                SpuSetTransferStartAddr(spu_bgm_start_ptr_r_800BF0C8);
                SpuWrite(stream_data_ptr_800BEFE4, 4096);

                if (dword_800BF268 == 0)
                {
                    dword_800BF164 = 4096;
                    str_unplay_size_800BF1AC -= 4096;
                }

                dword_800BF1A4 = 1;
                dword_8009F7B4 = -1;
            }
            else
            {
                gStr_FadeOut1_800BF16C = 7;
                break;
            }
        }
        else
        {
            stream_data_ptr_800BEFE4[dword_800BF164 + 1] |= 0x4;
            SpuSetTransferStartAddr(spu_bgm_start_ptr_l_800BF060);
            SpuWrite(stream_data_ptr_800BEFE4 + dword_800BF164, 4096);
            dword_800BF164 += 4096;
            str_unplay_size_800BF1AC -= 4096;

            if (dword_800BF268 == 0)
            {
                dword_8009F7B8 = stream_data_ptr_800BEFE4;
                stream_data_ptr_800BEFE4 = FS_StreamGetData_800240E0(1);

                if (!stream_data_ptr_800BEFE4)
                {
                    gStr_FadeOut1_800BF16C = 7;
                    break;
                }

                dword_800BF164 = 0;
            }

            dword_800BF1A4 = 0;
            gStr_FadeOut1_800BF16C++;
        }

        result = 1;
        break;

    case 3:
        if ((str_unplay_size_800BF1AC == 0) || (str_unplay_size_800BF1AC < 0))
        {
            gStr_FadeOut1_800BF16C++;
        }

        if (dword_800BF1A4 == 0)
        {
            stream_data_ptr_800BEFE4[dword_800BF164 + 4081] |= 0x1;
            SpuSetTransferStartAddr(spu_bgm_start_ptr_r_800BF0C8 + 4096);
            SpuWrite(stream_data_ptr_800BEFE4 + dword_800BF164, 4096);

            if (dword_800BF268 == 0)
            {
                dword_800BF164 += 4096;
                str_unplay_size_800BF1AC -= 4096;
            }

            dword_800BF1A4 = 1;
            result = 1;
        }
        else
        {
            stream_data_ptr_800BEFE4[dword_800BF164 + 4081] |= 0x1;
            SpuSetTransferStartAddr(spu_bgm_start_ptr_l_800BF060 + 4096);
            SpuWrite(stream_data_ptr_800BEFE4 + dword_800BF164, 4096);
            str_unplay_size_800BF1AC -= 4096;
            dword_8009F7B8 = stream_data_ptr_800BEFE4;
            stream_data_ptr_800BEFE4 = FS_StreamGetData_800240E0(1);
            dword_800BF164 = 0;
            dword_800BF1A4 = 0;
            result = 1;
            gStr_FadeOut1_800BF16C++;
        }
        break;

    case 4:
        attr.mask = 0xff93;
        attr.voice = 0x200000;
        attr.volume.left = 0;
        attr.volume.right = 0;
        attr.a_mode = 1;
        attr.s_mode = 1;
        attr.r_mode = 3;
        attr.ar = 0x10;
        attr.dr = 0;
        attr.sr = 0;
        attr.rr = 8;
        attr.sl = 0xf;
        attr.pitch = dword_800C0504;
        attr.addr = spu_bgm_start_ptr_r_800BF0C8;
        SpuSetVoiceAttr(&attr);

        attr.mask = 0xff93;
        attr.voice = 0x400000;
        attr.volume.left = 0;
        attr.volume.right = 0;
        attr.a_mode = 1;
        attr.s_mode = 1;
        attr.r_mode = 3;
        attr.ar = 0x10;
        attr.dr = 0;
        attr.sr = 0;
        attr.rr = 8;
        attr.sl = 0xf;
        attr.pitch = (ushort)dword_800C0504;
        attr.addr = spu_bgm_start_ptr_l_800BF060;
        SpuSetVoiceAttr(&attr);

        dword_800BF270 = 0;
        keyOn_80082170(0x600000);
        dword_800C0414 = 4096;
        dword_800BEFEC = 0;
        dword_8009F7B4 = 0;
        gStr_FadeOut1_800BF16C++;

        if ((str_unplay_size_800BF1AC == 0) || (str_unplay_size_800BF1AC < 0))
        {
            if ((dword_800C051C < 0) || (dword_800C051C > 768))
            {
                dword_800BF264 = (dword_800C051C - 768) & ~0xff;
            }
            else
            {
                dword_800BF264 = 256;
            }

            gStr_FadeOut1_800BF16C++;
        }
        break;

    case 5:
        if (stream_data_ptr_800BEFE4 && (dword_800BEFEC == 0))
        {
            dword_8009F7B4++;
        }

        if (((dword_800C0414 == (dword_800BF270 & 4096)) || (dword_800BF1A4 != 0)) ||
             (dword_800BEFEC != 0))
        {
            result = 1;

            if ((stream_data_ptr_800BEFE4) && (dword_800BEFEC == 0))
            {
                dword_800BEFF0 = 0;
                bVar1 = 0;

                if (dword_800BF268 != 0)
                {
                    dword_800BEFE8 = 0;
                }

                if (dword_800BF270 >= 4096u)
                {
                    if (dword_800BF1A4 == 0)
                    {
                        SpuSetTransferStartAddr(spu_bgm_start_ptr_r_800BF0C8);
                        dword_800BF1A4 = 1;
                    }
                    else
                    {
                        SpuSetTransferStartAddr(spu_bgm_start_ptr_l_800BF060);
                        dword_800BF1A4 = 0;
                        dword_800C0414 = (dword_800C0414 + 4096) & 0x1fff;

                        if (dword_800BF268 == 0)
                        {
                            bVar1 = 1;
                        }
                        else
                        {
                            dword_800BEFE8 = 1;
                        }
                    }

                    (stream_data_ptr_800BEFE4 + dword_800BF164)[1] |= 4; // (temporary?) hack, maybe this was an inline like STOREL?
                }
                else
                {
                    if (dword_800BF1A4 == 0)
                    {
                        dword_800BF1A4 = 1;
                        SpuSetTransferStartAddr(spu_bgm_start_ptr_r_800BF0C8 + 4096);
                    }
                    else
                    {
                        dword_800BF1A4 = 0;
                        dword_800C0414 = (dword_800C0414 + 4096) & 0x1fff;
                        SpuSetTransferStartAddr(spu_bgm_start_ptr_l_800BF060 + 4096);
                        bVar1 = 1;

                        if (dword_800BF268 != 0)
                        {
                            dword_800BEFE8 = 1;
                        }
                    }

                    (stream_data_ptr_800BEFE4 + dword_800BF164)[4081] |= 1; // (temporary?) hack
                }

                SpuWrite(stream_data_ptr_800BEFE4 + dword_800BF164, 4096);

                if (dword_800BF268 != 0)
                {
                    if (dword_800BEFE8 != 0)
                    {
                        dword_800BF164 = dword_800BF164 + 4096;

                        if (str_unplay_size_800BF1AC > 4096u)
                        {
                            str_unplay_size_800BF1AC -= 4096;
                        }
                        else
                        {
                            dword_800BF164 = 0;

                            dword_800BF264 = 4096 + dword_800BF270 + str_unplay_size_800BF1AC;
                            dword_800BF264 &= 0xffffff00;
                            dword_800BF264 -= 0x300;
                            dword_800BF264 &= 0x1fff;

                            gStr_FadeOut1_800BF16C++;
                        }
                    }
                }
                else
                {
                    dword_800BF164 += 4096;

                    if (str_unplay_size_800BF1AC > 4096u)
                    {
                        str_unplay_size_800BF1AC -= 4096;
                    }
                    else
                    {
                        if (dword_800BF1A4 != 0)
                        {
                            printf("\nSOUND STREAMING ERROR:NO LAST LEFT DATA\n");
                        }

                        printf("str_unplay_size=%x\n", str_unplay_size_800BF1AC);

                        dword_800BF164 = 0;

                        dword_800BF264 = 4096 + dword_800BF270 + str_unplay_size_800BF1AC;
                        dword_800BF264 &= 0xffffff00;
                        dword_800BF264 -= 0x300;
                        dword_800BF264 &= 0x1fff;

                        gStr_FadeOut1_800BF16C++;
                    }
                }

                if (bVar1)
                {
                    dword_8009F7B8 = stream_data_ptr_800BEFE4;
                    stream_data_ptr_800BEFE4 = FS_StreamGetData_800240E0(1);
                    dword_800BF164 = 0;
                }
            }
            else
            {
                dword_800BEFF0 = 1;
                printf("*");

                if (dword_800BF270 >= 4096u)
                {
                    if (dword_800BEFEC == 0)
                    {
                        SpuSetTransferStartAddr(spu_bgm_start_ptr_r_800BF0C8);
                        start_addr = spu_bgm_start_ptr_r_800BF0C8;
                        dword_800BEFEC = 1;
                    }
                    else
                    {
                        SpuSetTransferStartAddr(spu_bgm_start_ptr_l_800BF060);
                        start_addr = spu_bgm_start_ptr_l_800BF060;
                        dword_800C0414 = (dword_800C0414 + 4096) & 0x1fff;
                        dword_800BEFEC = 0;
                    }

                    dummy_data_800A2D28[1] = 6;
                    dummy_data_800A2D28[4081] = 2;
                    SpuWrite(dummy_data_800A2D28, 4096);
                }
                else
                {
                    if (dword_800BEFEC == 0)
                    {
                        start_addr = spu_bgm_start_ptr_r_800BF0C8 + 4096;
                        dword_800BEFEC = 1;
                        SpuSetTransferStartAddr(start_addr);
                    }
                    else
                    {
                        dword_800C0414 = (dword_800C0414 + 4096) & 0x1fff;
                        start_addr = spu_bgm_start_ptr_l_800BF060 + 4096;
                        dword_800BEFEC = 0;
                        SpuSetTransferStartAddr(start_addr);
                    }

                    dummy_data_800A2D28[1] = 2;
                    dummy_data_800A2D28[4081] = 3;
                    SpuWrite(dummy_data_800A2D28, 4096);
                }

                if ((dword_800BEFEC == 0) && (dword_800C0414 != 0))
                {
                    dword_8009F7B8 = stream_data_ptr_800BEFE4;
                    stream_data_ptr_800BEFE4 = FS_StreamGetData_800240E0(1);

                    if ((stream_data_ptr_800BEFE4 == NULL) && FS_StreamGetEndFlag_800243B8())
                    {
                        dword_800BF264 = -1;
                        gStr_FadeOut1_800BF16C++;
                        break;
                    }
                }
            }
        }

        if (FS_StreamIsForceStop_800243C8())
        {
            dword_800BF264 = -1;
            gStr_FadeOut1_800BF16C++;
        }
        break;

    case 6:
        if ((dword_800BF270 == dword_800BF264) || (dword_800BF264 == -1))
        {
            attr.mask = 0x4000;
            attr.voice = 0x200000;
            attr.rr = 8;
            SpuSetVoiceAttr(&attr);

            attr.mask = 0x4000;
            attr.voice = 0x400000;
            attr.rr = 8;
            SpuSetVoiceAttr(&attr);

            keyOff_80081FC4(0x600000);
            dword_8009F7B4 = -1;
            gStr_FadeOut1_800BF16C++;
        }
        else
        {
            dword_8009F7B4++;
        }
        break;

    case 7:
        dword_8009F7B4 = -1;
        break;
    }

    return result;
}

void StrSpuTransClose_80083394(void)
{
    if (stream_data_ptr_800BEFE4)
    {
        sub_800241B4(stream_data_ptr_800BEFE4);
        stream_data_ptr_800BEFE4 = NULL;
    }

    if (dword_8009F7B8)
    {
        sub_800241B4(dword_8009F7B8);
        dword_8009F7B8 = NULL;
    }

    dword_800BEFF0 = 0;
    FS_StreamClose_80024098();
}

void StrSpuTrans_800833FC(void)
{
    StrSpuTransWithNoLoop_800827AC();
}

int SD_LoadSeFile_8008341C(void)
{
    if (se_fp_800BF014)
    {
        printf("ERROR:SE File Already Opened.\n");
        SD_8008395C(se_fp_800BF014, 4);
        se_fp_800BF014 = 0;
    }
    se_fp_800BF014 = SD_SongLoadData_8008394C(se_load_code_800BF28C, 4);
    if (se_fp_800BF014 < 0)
    {
        se_fp_800BF014 = 0;
        printf("LoadSeFile:File Open Error(%x)\n", se_load_code_800BF28C);
        nullsub_7_80081A10(&dword_800C0500, -4, se_load_code_800BF28C); // TODO: Not sure if last arg exists
        return -1;
    }
    else
    {
        SD_80083954(se_fp_800BF014, se_exp_table_800C0520, 0x2800);
        SD_8008395C(se_fp_800BF014, 4);
        se_load_code_800BF28C = 0;
        se_fp_800BF014 = 0;
        return 0;
    }
}

int SD_LoadWaveFile_800834FC(void)
{
    unsigned int offset;
    unsigned int size;
    char        *dst;

    if (wave_data_800BF294 != 0)
    {
        printf("ERROR:Wave File Already Opened.\n");
        SD_8008395C(wave_data_800BF294, 2);
        wave_data_800BF294 = 0;
    }

    wave_data_800BF294 = SD_SongLoadData_8008394C(wave_load_code_800C0528, 2);

    if (wave_data_800BF294 < 0)
    {
        wave_data_800BF294 = 0;
        printf("LoadWaveFile:File Open Error(%x)\n", wave_load_code_800C0528);
        nullsub_7_80081A10(&dword_800C0500, -4, wave_load_code_800C0528);
        wave_load_code_800C0528 = 0;
        return -1;
    }

    SD_80083954(wave_data_800BF294, cdload_buf_800BF010, 0x18000);
    byte_800C056C = 0x4F;

    offset = cdload_buf_800BF010[0] << 24;
    offset |= cdload_buf_800BF010[1] << 16;
    offset |= cdload_buf_800BF010[2] << 8;
    offset |= cdload_buf_800BF010[3];

    size = cdload_buf_800BF010[4] << 24;
    size |= cdload_buf_800BF010[5] << 16;
    size |= cdload_buf_800BF010[6] << 8;
    size |= cdload_buf_800BF010[7];

    printf("SUP OFFSET=%x:SIZE=%x\n", offset, size);

    wave_load_ptr_800C0508 = cdload_buf_800BF010 + 16;
    dst = (char *)voice_tbl_800BF1E0 + offset;
    memcpy(dst, wave_load_ptr_800C0508, size);

    printf("    SRC=%x:DST=%x\n", (unsigned int)wave_load_ptr_800C0508, (unsigned int)dst);

    wave_load_ptr_800C0508 += size;

    spu_load_offset_800BF140 = wave_load_ptr_800C0508[0] << 24;
    spu_load_offset_800BF140 |= wave_load_ptr_800C0508[1] << 16;
    spu_load_offset_800BF140 |= wave_load_ptr_800C0508[2] << 8;
    spu_load_offset_800BF140 |= wave_load_ptr_800C0508[3];

    wave_unload_size_800BF274 = wave_load_ptr_800C0508[4] << 24;
    wave_unload_size_800BF274 |= wave_load_ptr_800C0508[5] << 16;
    wave_unload_size_800BF274 |= wave_load_ptr_800C0508[6] << 8;
    wave_unload_size_800BF274 |= wave_load_ptr_800C0508[7];

    printf("BIN OFFSET=%x\n", (unsigned int)wave_load_ptr_800C0508);
    printf("SPU OFFSET=%x:SIZE=%x\n",
                         spu_load_offset_800BF140, wave_unload_size_800BF274);

    wave_load_ptr_800C0508 += 16;

    if (wave_unload_size_800BF274 > (0x17FE0 - size))
    {
        dword_800C0650 = 0x17FE0 - size;
    }
    else
    {
        dword_800C0650 = wave_unload_size_800BF274;
    }

    wave_unload_size_800BF274 -= dword_800C0650;
    wave_save_code_800C0578 = wave_load_code_800C0528;
    return 0;
}

void sub_80083804(void)
{
    int temp;

    if (wave_unload_size_800BF274 > 0x18000U)
    {
        SD_80083954(wave_data_800BF294, cdload_buf_800BF010, 0x18000);
        dword_800C0650 = 0x18000;
        dword_800BF27C = 2;
        wave_load_ptr_800C0508 = cdload_buf_800BF010;
        wave_unload_size_800BF274 -= 0x18000U;
        return;
    }
    if (wave_unload_size_800BF274 != 0)
    {
        SD_80083954(wave_data_800BF294, cdload_buf_800BF010, wave_unload_size_800BF274);
        temp = wave_unload_size_800BF274;
        wave_unload_size_800BF274 = 0;
        dword_800BF27C = 2;
        wave_load_ptr_800C0508 = cdload_buf_800BF010;
        dword_800C0650 = temp;
        return;
    }
    dword_800BF27C = 0;
    SD_8008395C(wave_data_800BF294, 2);
    printf("Complete Load Se:%x\n", wave_load_code_800C0528);
    wave_data_800BF294 = 0;
    nullsub_7_80081A10(&dword_800C0500, 0, wave_load_code_800C0528);
}

void WaveSpuTrans_80083944(void)
{
}

int SD_SongLoadData_8008394C(int a1, int a2)
{
    return -1;
}

int SD_80083954(int a1, unsigned char *a2, int a3)
{
    return -1;
}

int SD_8008395C(int a1, int a2)
{
    return -1;
}

void StrFadeWkSet_80083964(void)
{
    unsigned int amount; // $a0

    if (dword_800C04EC == 0xFF0000F8)
    {
        amount = 100;
    }
    else
    {
        amount = 400;
        if (dword_800C04EC != 0xFF0000F9)
        {
            return;
        }
    }
    StrFadeIn_800822C8(amount);
    dword_800C04EC = 0;
    gStr_fadeout_2_800C0584 = gStreamVol_800BF15C;
}

int StrFadeInt_800839C8(void)
{
    SpuVoiceAttr attr;
    unsigned int diff;

    if (gStr_FadeOut1_800BF16C < 5)
    {
        return 0;
    }

    if (dword_800C04F4 != 0)
    {
        gStr_fadeout_2_800C0584 += dword_800C04F4;

        if (gStr_fadeout_2_800C0584 >= gStreamVol_800BF15C)
        {
            if (gStream_800C04F0 == -1)
            {
                keyOff_80081FC4(0x600000);
                gStr_FadeOut1_800BF16C = 7;
            }
            else
            {
                dword_800BF26C = 1;
            }

            dword_800C04F4 = 0;
            gStr_fadeout_2_800C0584 = gStreamVol_800BF15C;
        }
        else
        {
            dword_800BF26C = 0;
        }
    }

    attr.mask = SPU_VOICE_VOLL | SPU_VOICE_VOLR;
    attr.voice = SPU_21CH;

    diff = gStreamVol_800BF15C - gStr_fadeout_2_800C0584;

    if ((dword_800BF1DC != 0) && (dword_800C0418 < 2))
    {
        attr.volume.left = 0;
        attr.volume.right = 0;
    }
    else if (sound_mono_fg_800C050C != 0)
    {
        attr.volume.left = (diff * 0xA6) >> 8;
        attr.volume.right = (diff * 0xA6) >> 8;
    }
    else
    {
        attr.volume.left = 0;
        attr.volume.right = diff;
    }

    SpuSetVoiceAttr(&attr);

    attr.mask = SPU_VOICE_VOLL | SPU_VOICE_VOLR;
    attr.voice = SPU_22CH;

    if ((dword_800BF1DC != 0) && (dword_800C0418 < 2))
    {
        attr.volume.left = 0;
        attr.volume.right = 0;
    }
    else if (sound_mono_fg_800C050C != 0)
    {
        attr.volume.left = (diff * 0xA6) >> 8;
        attr.volume.right = (diff * 0xA6) >> 8;
    }
    else
    {
        attr.volume.left = diff;
        attr.volume.right = 0;
    }

    SpuSetVoiceAttr(&attr);
    return 0;
}
