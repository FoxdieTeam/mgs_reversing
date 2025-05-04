#include "sd/sd_incl.h"
#include "sd/sd_ext.h"

#include <stdio.h>
#include <libspu.h>
#include "common.h"
#include "mts/mts.h"
#include "mts/taskid.h"
#include "libfs/libfs.h"

int dword_8009F7B4 = -1;
char *dword_8009F7B8 = 0;

void StrFadeIn(unsigned int fade_speed)
{
    str_fadein_time_800BF0CC = str_volume_800BF15C / fade_speed;
    if (!(str_volume_800BF15C / fade_speed))
    {
        str_fadein_time_800BF0CC = 1;
    }
    str_fade_time_800C04F4 = 0;
}

int StrFadeOut(unsigned int fade_speed)
{
    if (str_status_800BF16C)
    {
        if (str_fade_value_800C0584 != str_volume_800BF15C)
        {
            str_fade_time_800C04F4 = str_volume_800BF15C / fade_speed;
            if (!(str_volume_800BF15C / fade_speed))
            {
                str_fade_time_800C04F4 = 1;
            }
            str_fadein_time_800BF0CC = 0;
            return 0;
        }
    }
    return -1;
}

int StrFadeOutStop(unsigned int fade_speed)
{
    if (str_status_800BF16C &&
         (str_fade_value_800C0584 != str_volume_800BF15C || str_fadein_time_800BF0CC))
    {
        str_fade_time_800C04F4 = str_volume_800BF15C / fade_speed;
        if (!(str_volume_800BF15C / fade_speed))
        {
            str_fade_time_800C04F4 = 1;
        }
        str_fadein_time_800BF0CC = 0;
        str_load_code_800C04F0 = -1;
        return 0;
    }
    else
    {
        printf("Canceled STR FadeOut(%x:%x:%x)",
                             str_status_800BF16C,
                             str_fade_value_800C0584,
                             str_volume_800BF15C);
        return -1;
    }
}

int StartStream(void)
{
    if (!str_fadein_fg_800C04EC)
    {
        str_fadein_time_800BF0CC = 0;
        str_fade_value_800C0584 = 0;
        str_fade_time_800C04F4 = 0;
    }
    str_fout_fg_800BF26C = 0;
    dword_8009F7B4 = -1;
    FS_StreamOpen();

    str_header_800BF058 = FS_StreamGetData(2);

    if (!str_header_800BF058)
    {
        printf("Stream:File Pos Error\n");
        FS_StreamClose();
        return -1;
    }

    // Consume big-endian int from str_header_800BF058
    str_wave_size_800C051C = str_header_800BF058[0] << 24;
    str_wave_size_800C051C |= str_header_800BF058[1] << 16;
    str_wave_size_800C051C |= str_header_800BF058[2] << 8;
    str_wave_size_800C051C |= str_header_800BF058[3];

    str_unplay_size_800BF1AC = str_unload_size_800BF168 = str_wave_size_800C051C;

    // Consume big-endian short from str_header_800BF058
    str_volume_800BF15C = str_header_800BF058[4] << 8;
    str_volume_800BF15C |= str_header_800BF058[5];

    // Consume big-endian short from str_header_800BF058
    str_freq_800C0504 = str_header_800BF058[6] << 8;
    str_freq_800C0504 |= str_header_800BF058[7];

    // Consume byte from str_header_800BF058
    if (str_header_800BF058[8] == 1)
    {
        str_mono_fg_800BF268 = str_header_800BF058[8];
    }
    else
    {
        str_mono_fg_800BF268 = 0;
    }

    // Consume byte from str_header_800BF058
    dword_800C0580 = str_header_800BF058[9];

    printf("StartStream(%x:vol=%x)\n", str_load_code_800C04F0, str_volume_800BF15C);
    if (str_fadein_fg_800C04EC)
    {
        StrFadeWkSet();
    }

    keyOff(SPU_21CH | SPU_22CH);
    str_mute_fg_800BEFF0 = NULL;
    FS_StreamClear(str_header_800BF058);
    str_mute_ctr_800C0418 = NULL;
    str_mute_status_800BF1DC = NULL;
    return 0;
}

void UserSpuIRQProc(void)
{
    switch (str_status_800BF16C & 0x0f)
    {
    case 2: /* fallthrough */
    case 3:
        break;

    case 4:
        str_int_ctr_800BEFF4 = 0;
        break;

    case 5:
        switch (str_freq_800C0504)
        {
        case 0x800:
            if ((str_int_ctr_800BEFF4++ & 1) != 0)
            {
                dword_800BF270 += 0x100;
                dword_800BF270 &= 0x1fff;
            }
            break;

        case 0xc00:
            if ((str_int_ctr_800BEFF4++ & 3) != 0)
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
        switch (str_freq_800C0504)
        {
        case 0x800:
            if ((str_int_ctr_800BEFF4++ & 1) != 0)
            {
                dword_800BF270 += 0x100;
                dword_800BF270 &= 0x1fff;
            }
            break;

        case 0xc00:
            if ((str_int_ctr_800BEFF4++ & 3) != 0)
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

    mts_isend(MTSID_SOUND_INT);

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

void sub_800827A4(void)
{
    /* do nothing */
}

int StrSpuTransWithNoLoop(void)
{
    SpuVoiceAttr attr;
    int          result;
    int          bVar1;
    u_long       start_addr;

    result = 0;

    if (dword_8009F7B8 != 0)
    {
        FS_StreamClear(dword_8009F7B8);
        dword_8009F7B8 = 0;
    }

    switch (str_status_800BF16C & 0xf)
    {
    case 2:
        if (dword_800BF1A4 == 0)
        {
            if ((se_rev_on_800C0574 != 0) && (str_vox_on_800BF160 != 0) && (vox_rev_on_800BF144 != 0))
            {
                SpuSetReverbVoice(SPU_ON, SPU_21CH | SPU_22CH);
            }
            else
            {
                SpuSetReverbVoice(SPU_OFF, SPU_21CH | SPU_22CH);
            }

            stream_data_ptr_800BEFE4 = FS_StreamGetData(1);

            if (stream_data_ptr_800BEFE4)
            {
                str_play_idx_800C040C = 0;
                str_play_offset_800BF164 = 0;
                stream_data_ptr_800BEFE4[1] |= 0x4;
                SpuSetTransferStartAddr(spu_bgm_start_ptr_r_800BF0C8);
                SpuWrite(stream_data_ptr_800BEFE4, 4096);

                if (str_mono_fg_800BF268 == 0)
                {
                    str_play_offset_800BF164 = 4096;
                    str_unplay_size_800BF1AC -= 4096;
                }

                dword_800BF1A4 = 1;
                dword_8009F7B4 = -1;
            }
            else
            {
                str_status_800BF16C = 7;
                break;
            }
        }
        else
        {
            stream_data_ptr_800BEFE4[str_play_offset_800BF164 + 1] |= 0x4;
            SpuSetTransferStartAddr(spu_bgm_start_ptr_l_800BF060);
            SpuWrite(stream_data_ptr_800BEFE4 + str_play_offset_800BF164, 4096);
            str_play_offset_800BF164 += 4096;
            str_unplay_size_800BF1AC -= 4096;

            if (str_mono_fg_800BF268 == 0)
            {
                dword_8009F7B8 = stream_data_ptr_800BEFE4;
                stream_data_ptr_800BEFE4 = FS_StreamGetData(1);

                if (!stream_data_ptr_800BEFE4)
                {
                    str_status_800BF16C = 7;
                    break;
                }

                str_play_offset_800BF164 = 0;
            }

            dword_800BF1A4 = 0;
            str_status_800BF16C++;
        }

        result = 1;
        break;

    case 3:
        if ((str_unplay_size_800BF1AC == 0) || (str_unplay_size_800BF1AC < 0))
        {
            str_status_800BF16C++;
        }

        if (dword_800BF1A4 == 0)
        {
            stream_data_ptr_800BEFE4[str_play_offset_800BF164 + 4081] |= 0x1;
            SpuSetTransferStartAddr(spu_bgm_start_ptr_r_800BF0C8 + 4096);
            SpuWrite(stream_data_ptr_800BEFE4 + str_play_offset_800BF164, 4096);

            if (str_mono_fg_800BF268 == 0)
            {
                str_play_offset_800BF164 += 4096;
                str_unplay_size_800BF1AC -= 4096;
            }

            dword_800BF1A4 = 1;
            result = 1;
        }
        else
        {
            stream_data_ptr_800BEFE4[str_play_offset_800BF164 + 4081] |= 0x1;
            SpuSetTransferStartAddr(spu_bgm_start_ptr_l_800BF060 + 4096);
            SpuWrite(stream_data_ptr_800BEFE4 + str_play_offset_800BF164, 4096);
            str_unplay_size_800BF1AC -= 4096;
            dword_8009F7B8 = stream_data_ptr_800BEFE4;
            stream_data_ptr_800BEFE4 = FS_StreamGetData(1);
            str_play_offset_800BF164 = 0;
            dword_800BF1A4 = 0;
            result = 1;
            str_status_800BF16C++;
        }
        break;

    case 4:
        attr.mask = SPU_VOICE_VOLL | SPU_VOICE_VOLR | SPU_VOICE_PITCH | SPU_VOICE_WDSA |
                    SPU_VOICE_ADSR_AMODE | SPU_VOICE_ADSR_SMODE | SPU_VOICE_ADSR_RMODE | SPU_VOICE_ADSR_AR |
                    SPU_VOICE_ADSR_DR | SPU_VOICE_ADSR_SR | SPU_VOICE_ADSR_RR | SPU_VOICE_ADSR_SL;
        attr.voice = SPU_21CH;
        attr.volume.left = 0;
        attr.volume.right = 0;
        attr.a_mode = SPU_VOICE_LINEARIncN;
        attr.s_mode = SPU_VOICE_LINEARIncN;
        attr.r_mode = SPU_VOICE_LINEARDecN;
        attr.ar = 0x10;
        attr.dr = 0;
        attr.sr = 0;
        attr.rr = 8;
        attr.sl = 0xf;
        attr.pitch = str_freq_800C0504;
        attr.addr = spu_bgm_start_ptr_r_800BF0C8;
        SpuSetVoiceAttr(&attr);

        attr.mask = SPU_VOICE_VOLL | SPU_VOICE_VOLR | SPU_VOICE_PITCH | SPU_VOICE_WDSA |
                    SPU_VOICE_ADSR_AMODE | SPU_VOICE_ADSR_SMODE | SPU_VOICE_ADSR_RMODE | SPU_VOICE_ADSR_AR |
                    SPU_VOICE_ADSR_DR | SPU_VOICE_ADSR_SR | SPU_VOICE_ADSR_RR | SPU_VOICE_ADSR_SL;
        attr.voice = SPU_22CH;
        attr.volume.left = 0;
        attr.volume.right = 0;
        attr.a_mode = SPU_VOICE_LINEARIncN;
        attr.s_mode = SPU_VOICE_LINEARIncN;
        attr.r_mode = SPU_VOICE_LINEARDecN;
        attr.ar = 0x10;
        attr.dr = 0;
        attr.sr = 0;
        attr.rr = 8;
        attr.sl = 0xf;
        attr.pitch = (u_short)str_freq_800C0504;
        attr.addr = spu_bgm_start_ptr_l_800BF060;
        SpuSetVoiceAttr(&attr);

        dword_800BF270 = 0;
        keyOn(SPU_21CH | SPU_22CH);
        str_next_idx_800C0414 = 4096;
        mute_l_r_fg = 0;
        dword_8009F7B4 = 0;
        str_status_800BF16C++;

        if ((str_unplay_size_800BF1AC == 0) || (str_unplay_size_800BF1AC < 0))
        {
            if ((str_wave_size_800C051C < 0) || (str_wave_size_800C051C > 768))
            {
                str_off_idx_800BF264 = (str_wave_size_800C051C - 768) & ~0xff;
            }
            else
            {
                str_off_idx_800BF264 = 256;
            }

            str_status_800BF16C++;
        }
        break;

    case 5:
        if (stream_data_ptr_800BEFE4 && (mute_l_r_fg == 0))
        {
            dword_8009F7B4++;
        }

        if (((str_next_idx_800C0414 == (dword_800BF270 & 4096)) || (dword_800BF1A4 != 0)) ||
             (mute_l_r_fg != 0))
        {
            result = 1;

            if ((stream_data_ptr_800BEFE4) && (mute_l_r_fg == 0))
            {
                str_mute_fg_800BEFF0 = 0;
                bVar1 = 0;

                if (str_mono_fg_800BF268 != 0)
                {
                    str_mono_offset_800BEFE8 = 0;
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
                        str_next_idx_800C0414 = (str_next_idx_800C0414 + 4096) & 0x1fff;

                        if (str_mono_fg_800BF268 == 0)
                        {
                            bVar1 = 1;
                        }
                        else
                        {
                            str_mono_offset_800BEFE8 = 1;
                        }
                    }

                    (stream_data_ptr_800BEFE4 + str_play_offset_800BF164)[1] |= 4; // (temporary?) hack, maybe this was an inline like STOREL?
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
                        str_next_idx_800C0414 = (str_next_idx_800C0414 + 4096) & 0x1fff;
                        SpuSetTransferStartAddr(spu_bgm_start_ptr_l_800BF060 + 4096);
                        bVar1 = 1;

                        if (str_mono_fg_800BF268 != 0)
                        {
                            str_mono_offset_800BEFE8 = 1;
                        }
                    }

                    (stream_data_ptr_800BEFE4 + str_play_offset_800BF164)[4081] |= 1; // (temporary?) hack
                }

                SpuWrite(stream_data_ptr_800BEFE4 + str_play_offset_800BF164, 4096);

                if (str_mono_fg_800BF268 != 0)
                {
                    if (str_mono_offset_800BEFE8 != 0)
                    {
                        str_play_offset_800BF164 = str_play_offset_800BF164 + 4096;

                        if (str_unplay_size_800BF1AC > 4096u)
                        {
                            str_unplay_size_800BF1AC -= 4096;
                        }
                        else
                        {
                            str_play_offset_800BF164 = 0;

                            str_off_idx_800BF264 = 4096 + dword_800BF270 + str_unplay_size_800BF1AC;
                            str_off_idx_800BF264 &= 0xffffff00;
                            str_off_idx_800BF264 -= 0x300;
                            str_off_idx_800BF264 &= 0x1fff;

                            str_status_800BF16C++;
                        }
                    }
                }
                else
                {
                    str_play_offset_800BF164 += 4096;

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

                        str_play_offset_800BF164 = 0;

                        str_off_idx_800BF264 = 4096 + dword_800BF270 + str_unplay_size_800BF1AC;
                        str_off_idx_800BF264 &= 0xffffff00;
                        str_off_idx_800BF264 -= 0x300;
                        str_off_idx_800BF264 &= 0x1fff;

                        str_status_800BF16C++;
                    }
                }

                if (bVar1)
                {
                    dword_8009F7B8 = stream_data_ptr_800BEFE4;
                    stream_data_ptr_800BEFE4 = FS_StreamGetData(1);
                    str_play_offset_800BF164 = 0;
                }
            }
            else
            {
                str_mute_fg_800BEFF0 = 1;
                printf("*");

                if (dword_800BF270 >= 4096u)
                {
                    if (mute_l_r_fg == 0)
                    {
                        SpuSetTransferStartAddr(spu_bgm_start_ptr_r_800BF0C8);
                        start_addr = spu_bgm_start_ptr_r_800BF0C8;
                        mute_l_r_fg = 1;
                    }
                    else
                    {
                        SpuSetTransferStartAddr(spu_bgm_start_ptr_l_800BF060);
                        start_addr = spu_bgm_start_ptr_l_800BF060;
                        str_next_idx_800C0414 = (str_next_idx_800C0414 + 4096) & 0x1fff;
                        mute_l_r_fg = 0;
                    }

                    dummy_data[1] = 6;
                    dummy_data[4081] = 2;
                    SpuWrite(dummy_data, 4096);
                }
                else
                {
                    if (mute_l_r_fg == 0)
                    {
                        start_addr = spu_bgm_start_ptr_r_800BF0C8 + 4096;
                        mute_l_r_fg = 1;
                        SpuSetTransferStartAddr(start_addr);
                    }
                    else
                    {
                        str_next_idx_800C0414 = (str_next_idx_800C0414 + 4096) & 0x1fff;
                        start_addr = spu_bgm_start_ptr_l_800BF060 + 4096;
                        mute_l_r_fg = 0;
                        SpuSetTransferStartAddr(start_addr);
                    }

                    dummy_data[1] = 2;
                    dummy_data[4081] = 3;
                    SpuWrite(dummy_data, 4096);
                }

                if ((mute_l_r_fg == 0) && (str_next_idx_800C0414 != 0))
                {
                    dword_8009F7B8 = stream_data_ptr_800BEFE4;
                    stream_data_ptr_800BEFE4 = FS_StreamGetData(1);

                    if ((stream_data_ptr_800BEFE4 == NULL) && FS_StreamGetEndFlag())
                    {
                        str_off_idx_800BF264 = -1;
                        str_status_800BF16C++;
                        break;
                    }
                }
            }
        }

        if (FS_StreamIsForceStop())
        {
            str_off_idx_800BF264 = -1;
            str_status_800BF16C++;
        }
        break;

    case 6:
        if ((dword_800BF270 == str_off_idx_800BF264) || (str_off_idx_800BF264 == -1))
        {
            attr.mask = SPU_VOICE_ADSR_RR;
            attr.voice = SPU_21CH;
            attr.rr = 8;
            SpuSetVoiceAttr(&attr);

            attr.mask = SPU_VOICE_ADSR_RR;
            attr.voice = SPU_22CH;
            attr.rr = 8;
            SpuSetVoiceAttr(&attr);

            keyOff(SPU_21CH | SPU_22CH);
            dword_8009F7B4 = -1;
            str_status_800BF16C++;
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

void StrSpuTransClose(void)
{
    if (stream_data_ptr_800BEFE4)
    {
        FS_StreamClear(stream_data_ptr_800BEFE4);
        stream_data_ptr_800BEFE4 = NULL;
    }

    if (dword_8009F7B8)
    {
        FS_StreamClear(dword_8009F7B8);
        dword_8009F7B8 = NULL;
    }

    str_mute_fg_800BEFF0 = 0;
    FS_StreamClose();
}

void StrSpuTrans(void)
{
    StrSpuTransWithNoLoop();
}
