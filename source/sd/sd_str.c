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
    str_fadein_time = str_volume / fade_speed;
    if (!(str_volume / fade_speed))
    {
        str_fadein_time = 1;
    }
    str_fade_time = 0;
}

int StrFadeOut(unsigned int fade_speed)
{
    if (str_status)
    {
        if (str_fade_value != str_volume)
        {
            str_fade_time = str_volume / fade_speed;
            if (!(str_volume / fade_speed))
            {
                str_fade_time = 1;
            }
            str_fadein_time = 0;
            return 0;
        }
    }
    return -1;
}

int StrFadeOutStop(unsigned int fade_speed)
{
    if (str_status &&
         (str_fade_value != str_volume || str_fadein_time))
    {
        str_fade_time = str_volume / fade_speed;
        if (!(str_volume / fade_speed))
        {
            str_fade_time = 1;
        }
        str_fadein_time = 0;
        str_load_code = -1;
        return 0;
    }
    else
    {
        printf("Canceled STR FadeOut(%x:%x:%x)",
                             str_status,
                             str_fade_value,
                             str_volume);
        return -1;
    }
}

int StartStream(void)
{
    if (!str_fadein_fg)
    {
        str_fadein_time = 0;
        str_fade_value = 0;
        str_fade_time = 0;
    }
    str_fout_fg = 0;
    dword_8009F7B4 = -1;
    FS_StreamOpen();

    str_header = FS_StreamGetData(2);

    if (!str_header)
    {
        printf("Stream:File Pos Error\n");
        FS_StreamClose();
        return -1;
    }

    // Consume big-endian int from str_header
    str_wave_size = str_header[0] << 24;
    str_wave_size |= str_header[1] << 16;
    str_wave_size |= str_header[2] << 8;
    str_wave_size |= str_header[3];

    str_unplay_size = str_unload_size = str_wave_size;

    // Consume big-endian short from str_header
    str_volume = str_header[4] << 8;
    str_volume |= str_header[5];

    // Consume big-endian short from str_header
    str_freq = str_header[6] << 8;
    str_freq |= str_header[7];

    // Consume byte from str_header
    if (str_header[8] == 1)
    {
        str_mono_fg = str_header[8];
    }
    else
    {
        str_mono_fg = 0;
    }

    // Consume byte from str_header
    dword_800C0580 = str_header[9];

    printf("StartStream(%x:vol=%x)\n", str_load_code, str_volume);
    if (str_fadein_fg)
    {
        StrFadeWkSet();
    }

    keyOff(SPU_21CH | SPU_22CH);
    str_mute_fg = NULL;
    FS_StreamClear(str_header);
    str_mute_ctr = NULL;
    str_mute_status = NULL;
    return 0;
}

void UserSpuIRQProc(void)
{
    switch (str_status & 0x0f)
    {
    case 2: /* fallthrough */
    case 3:
        break;

    case 4:
        str_int_ctr = 0;
        break;

    case 5:
        switch (str_freq)
        {
        case 0x800:
            if ((str_int_ctr++ & 1) != 0)
            {
                dword_800BF270 += 0x100;
                dword_800BF270 &= 0x1fff;
            }
            break;

        case 0xc00:
            if ((str_int_ctr++ & 3) != 0)
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
        switch (str_freq)
        {
        case 0x800:
            if ((str_int_ctr++ & 1) != 0)
            {
                dword_800BF270 += 0x100;
                dword_800BF270 &= 0x1fff;
            }
            break;

        case 0xc00:
            if ((str_int_ctr++ & 3) != 0)
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
        SpuSetIRQAddr(blank_data_addr + 256);
    }
    else
    {
        SpuSetIRQAddr(blank_data_addr);
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

    switch (str_status & 0xf)
    {
    case 2:
        if (dword_800BF1A4 == 0)
        {
            if ((se_rev_on != 0) && (str_vox_on != 0) && (vox_rev_on != 0))
            {
                SpuSetReverbVoice(SPU_ON, SPU_21CH | SPU_22CH);
            }
            else
            {
                SpuSetReverbVoice(SPU_OFF, SPU_21CH | SPU_22CH);
            }

            str_data_ptr = FS_StreamGetData(1);

            if (str_data_ptr)
            {
                str_play_idx = 0;
                str_play_offset = 0;
                str_data_ptr[1] |= 0x4;
                SpuSetTransferStartAddr(spu_bgm_start_ptr_r);
                SpuWrite(str_data_ptr, 4096);

                if (str_mono_fg == 0)
                {
                    str_play_offset = 4096;
                    str_unplay_size -= 4096;
                }

                dword_800BF1A4 = 1;
                dword_8009F7B4 = -1;
            }
            else
            {
                str_status = 7;
                break;
            }
        }
        else
        {
            str_data_ptr[str_play_offset + 1] |= 0x4;
            SpuSetTransferStartAddr(spu_bgm_start_ptr_l);
            SpuWrite(str_data_ptr + str_play_offset, 4096);
            str_play_offset += 4096;
            str_unplay_size -= 4096;

            if (str_mono_fg == 0)
            {
                dword_8009F7B8 = str_data_ptr;
                str_data_ptr = FS_StreamGetData(1);

                if (!str_data_ptr)
                {
                    str_status = 7;
                    break;
                }

                str_play_offset = 0;
            }

            dword_800BF1A4 = 0;
            str_status++;
        }

        result = 1;
        break;

    case 3:
        if ((str_unplay_size == 0) || (str_unplay_size < 0))
        {
            str_status++;
        }

        if (dword_800BF1A4 == 0)
        {
            str_data_ptr[str_play_offset + 4081] |= 0x1;
            SpuSetTransferStartAddr(spu_bgm_start_ptr_r + 4096);
            SpuWrite(str_data_ptr + str_play_offset, 4096);

            if (str_mono_fg == 0)
            {
                str_play_offset += 4096;
                str_unplay_size -= 4096;
            }

            dword_800BF1A4 = 1;
            result = 1;
        }
        else
        {
            str_data_ptr[str_play_offset + 4081] |= 0x1;
            SpuSetTransferStartAddr(spu_bgm_start_ptr_l + 4096);
            SpuWrite(str_data_ptr + str_play_offset, 4096);
            str_unplay_size -= 4096;
            dword_8009F7B8 = str_data_ptr;
            str_data_ptr = FS_StreamGetData(1);
            str_play_offset = 0;
            dword_800BF1A4 = 0;
            result = 1;
            str_status++;
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
        attr.pitch = str_freq;
        attr.addr = spu_bgm_start_ptr_r;
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
        attr.pitch = (u_short)str_freq;
        attr.addr = spu_bgm_start_ptr_l;
        SpuSetVoiceAttr(&attr);

        dword_800BF270 = 0;
        keyOn(SPU_21CH | SPU_22CH);
        str_next_idx = 4096;
        mute_l_r_fg = 0;
        dword_8009F7B4 = 0;
        str_status++;

        if ((str_unplay_size == 0) || (str_unplay_size < 0))
        {
            if ((str_wave_size < 0) || (str_wave_size > 768))
            {
                str_off_idx = (str_wave_size - 768) & ~0xff;
            }
            else
            {
                str_off_idx = 256;
            }

            str_status++;
        }
        break;

    case 5:
        if (str_data_ptr && (mute_l_r_fg == 0))
        {
            dword_8009F7B4++;
        }

        if (((str_next_idx == (dword_800BF270 & 4096)) || (dword_800BF1A4 != 0)) ||
             (mute_l_r_fg != 0))
        {
            result = 1;

            if ((str_data_ptr) && (mute_l_r_fg == 0))
            {
                str_mute_fg = 0;
                bVar1 = 0;

                if (str_mono_fg != 0)
                {
                    str_mono_offset = 0;
                }

                if (dword_800BF270 >= 4096u)
                {
                    if (dword_800BF1A4 == 0)
                    {
                        SpuSetTransferStartAddr(spu_bgm_start_ptr_r);
                        dword_800BF1A4 = 1;
                    }
                    else
                    {
                        SpuSetTransferStartAddr(spu_bgm_start_ptr_l);
                        dword_800BF1A4 = 0;
                        str_next_idx = (str_next_idx + 4096) & 0x1fff;

                        if (str_mono_fg == 0)
                        {
                            bVar1 = 1;
                        }
                        else
                        {
                            str_mono_offset = 1;
                        }
                    }

                    (str_data_ptr + str_play_offset)[1] |= 4; // (temporary?) hack, maybe this was an inline like STOREL?
                }
                else
                {
                    if (dword_800BF1A4 == 0)
                    {
                        dword_800BF1A4 = 1;
                        SpuSetTransferStartAddr(spu_bgm_start_ptr_r + 4096);
                    }
                    else
                    {
                        dword_800BF1A4 = 0;
                        str_next_idx = (str_next_idx + 4096) & 0x1fff;
                        SpuSetTransferStartAddr(spu_bgm_start_ptr_l + 4096);
                        bVar1 = 1;

                        if (str_mono_fg != 0)
                        {
                            str_mono_offset = 1;
                        }
                    }

                    (str_data_ptr + str_play_offset)[4081] |= 1; // (temporary?) hack
                }

                SpuWrite(str_data_ptr + str_play_offset, 4096);

                if (str_mono_fg != 0)
                {
                    if (str_mono_offset != 0)
                    {
                        str_play_offset = str_play_offset + 4096;

                        if (str_unplay_size > 4096u)
                        {
                            str_unplay_size -= 4096;
                        }
                        else
                        {
                            str_play_offset = 0;

                            str_off_idx = 4096 + dword_800BF270 + str_unplay_size;
                            str_off_idx &= 0xffffff00;
                            str_off_idx -= 0x300;
                            str_off_idx &= 0x1fff;

                            str_status++;
                        }
                    }
                }
                else
                {
                    str_play_offset += 4096;

                    if (str_unplay_size > 4096u)
                    {
                        str_unplay_size -= 4096;
                    }
                    else
                    {
                        if (dword_800BF1A4 != 0)
                        {
                            printf("\nSOUND STREAMING ERROR:NO LAST LEFT DATA\n");
                        }

                        printf("str_unplay_size=%x\n", str_unplay_size);

                        str_play_offset = 0;

                        str_off_idx = 4096 + dword_800BF270 + str_unplay_size;
                        str_off_idx &= 0xffffff00;
                        str_off_idx -= 0x300;
                        str_off_idx &= 0x1fff;

                        str_status++;
                    }
                }

                if (bVar1)
                {
                    dword_8009F7B8 = str_data_ptr;
                    str_data_ptr = FS_StreamGetData(1);
                    str_play_offset = 0;
                }
            }
            else
            {
                str_mute_fg = 1;
                printf("*");

                if (dword_800BF270 >= 4096u)
                {
                    if (mute_l_r_fg == 0)
                    {
                        SpuSetTransferStartAddr(spu_bgm_start_ptr_r);
                        start_addr = spu_bgm_start_ptr_r;
                        mute_l_r_fg = 1;
                    }
                    else
                    {
                        SpuSetTransferStartAddr(spu_bgm_start_ptr_l);
                        start_addr = spu_bgm_start_ptr_l;
                        str_next_idx = (str_next_idx + 4096) & 0x1fff;
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
                        start_addr = spu_bgm_start_ptr_r + 4096;
                        mute_l_r_fg = 1;
                        SpuSetTransferStartAddr(start_addr);
                    }
                    else
                    {
                        str_next_idx = (str_next_idx + 4096) & 0x1fff;
                        start_addr = spu_bgm_start_ptr_l + 4096;
                        mute_l_r_fg = 0;
                        SpuSetTransferStartAddr(start_addr);
                    }

                    dummy_data[1] = 2;
                    dummy_data[4081] = 3;
                    SpuWrite(dummy_data, 4096);
                }

                if ((mute_l_r_fg == 0) && (str_next_idx != 0))
                {
                    dword_8009F7B8 = str_data_ptr;
                    str_data_ptr = FS_StreamGetData(1);

                    if ((str_data_ptr == NULL) && FS_StreamGetEndFlag())
                    {
                        str_off_idx = -1;
                        str_status++;
                        break;
                    }
                }
            }
        }

        if (FS_StreamIsForceStop())
        {
            str_off_idx = -1;
            str_status++;
        }
        break;

    case 6:
        if ((dword_800BF270 == str_off_idx) || (str_off_idx == -1))
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
            str_status++;
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
    if (str_data_ptr)
    {
        FS_StreamClear(str_data_ptr);
        str_data_ptr = NULL;
    }

    if (dword_8009F7B8)
    {
        FS_StreamClear(dword_8009F7B8);
        dword_8009F7B8 = NULL;
    }

    str_mute_fg = 0;
    FS_StreamClose();
}

void StrSpuTrans(void)
{
    StrSpuTransWithNoLoop();
}
