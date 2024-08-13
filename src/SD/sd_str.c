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
extern char            *CDLOAD_BUF_800BF058;
extern int              spu_bgm_start_ptr_l_800BF060;
extern int              spu_bgm_start_ptr_r_800BF0C8;
extern int              blank_data_addr_800BF00C;
extern int              bstr_fade_inProgress_800BF0CC;
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
extern int              dword_800BF264;
extern int              dword_800BF268;
extern int              dword_800BF26C;
extern int              dword_800BF270;
extern int              dword_800C040C;
extern int              dword_800C0414;
extern int              dword_800C0418;
extern int              dword_800C04EC;
extern int              gStream_800C04F0;
extern int              dword_800C04F4;
extern int              dword_800C0504;
extern int              dword_800C051C;
extern int              se_rev_on_800C0574;
extern int              dword_800C0580;
extern unsigned int     gStr_fadeout_2_800C0584;


/* in sd_main.c */
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
    switch (gStr_FadeOut1_800BF16C & 0x0f)
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
    /* do nothing */
}

void SD_nullsub_20_800827A4(void)
{
    /* do nothing */
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
