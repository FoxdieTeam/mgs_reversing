#include "sd/sd_incl.h"
#include "sd/sd_ext.h"

#include <stdio.h>
#include <libspu.h>
#include "common.h"
#include "mts/mts.h"
#include "libfs/libfs.h"

extern unsigned char *se_header;

int LoadSeFile(void)
{
    if (se_fp)
    {
        printf("ERROR:SE File Already Opened.\n");
        PcmClose(se_fp, 4);
        se_fp = 0;
    }
    se_fp = PcmOpen(se_load_code, 4);
    if (se_fp < 0)
    {
        se_fp = 0;
        printf("LoadSeFile:File Open Error(%x)\n", se_load_code);
        sub_80081A10(&dword_800C0500, -4, se_load_code);
        return -1;
    }
    else
    {
        PcmRead(se_fp, se_header, 0x2800);
        PcmClose(se_fp, 4);
        se_load_code = 0;
        se_fp = 0;
        return 0;
    }
}

int LoadWaveHeader(void)
{
    unsigned char *dst_ptr;
    unsigned int offset;
    unsigned int size;

    if (wave_data != 0)
    {
        printf("ERROR:Wave File Already Opened.\n");
        PcmClose(wave_data, 2);
        wave_data = 0;
    }

    wave_data = PcmOpen(wave_load_code, 2);

    if (wave_data < 0)
    {
        wave_data = 0;
        printf("LoadWaveFile:File Open Error(%x)\n", wave_load_code);
        sub_80081A10(&dword_800C0500, -4, wave_load_code);
        wave_load_code = 0;
        return -1;
    }

    PcmRead(wave_data, cdload_buf, 0x18000);
    wavs = 0x4F;

    offset =  cdload_buf[0] << 24;
    offset |= cdload_buf[1] << 16;
    offset |= cdload_buf[2] << 8;
    offset |= cdload_buf[3];

    size =  cdload_buf[4] << 24;
    size |= cdload_buf[5] << 16;
    size |= cdload_buf[6] << 8;
    size |= cdload_buf[7];

    printf("SUP OFFSET=%x:SIZE=%x\n", offset, size);

    wave_load_ptr = cdload_buf + 16;
    dst_ptr = (char *)wave_header + offset;
    memcpy(dst_ptr, wave_load_ptr, size);

    printf("    SRC=%x:DST=%x\n", (unsigned int)wave_load_ptr, (unsigned int)dst_ptr);

    wave_load_ptr += size;

    spu_load_offset =  wave_load_ptr[0] << 24;
    spu_load_offset |= wave_load_ptr[1] << 16;
    spu_load_offset |= wave_load_ptr[2] << 8;
    spu_load_offset |= wave_load_ptr[3];

    wave_unload_size =  wave_load_ptr[4] << 24;
    wave_unload_size |= wave_load_ptr[5] << 16;
    wave_unload_size |= wave_load_ptr[6] << 8;
    wave_unload_size |= wave_load_ptr[7];

    printf("BIN OFFSET=%x\n", (unsigned int)wave_load_ptr);
    printf("SPU OFFSET=%x:SIZE=%x\n", spu_load_offset, wave_unload_size);

    wave_load_ptr += 16;

    if (wave_unload_size > (CDLOAD_BUF_SIZE - (size + 0x20)))
    {
        wave_load_size = CDLOAD_BUF_SIZE - (size + 0x20);
    }
    else
    {
        wave_load_size = wave_unload_size;
    }

    wave_unload_size -= wave_load_size;
    wave_save_code = wave_load_code;
    return 0;
}

void WaveCdLoad(void)
{
    int temp;

    if (wave_unload_size > 0x18000U)
    {
        PcmRead(wave_data, cdload_buf, 0x18000);
        wave_load_size = 0x18000;
        dword_800BF27C = 2;
        wave_load_ptr = cdload_buf;
        wave_unload_size -= 0x18000U;
        return;
    }
    if (wave_unload_size != 0)
    {
        PcmRead(wave_data, cdload_buf, wave_unload_size);
        temp = wave_unload_size;
        wave_unload_size = 0;
        dword_800BF27C = 2;
        wave_load_ptr = cdload_buf;
        wave_load_size = temp;
        return;
    }
    dword_800BF27C = 0;
    PcmClose(wave_data, 2);
    printf("Complete Load Se:%x\n", wave_load_code);
    wave_data = 0;
    sub_80081A10(&dword_800C0500, 0, wave_load_code);
}

void WaveSpuTrans(void)
{
    /* do nothing */
}

int PcmOpen(int code, int path_idx)
{
    return -1;
}

int PcmRead(int fd, unsigned char *buf, int size)
{
    return -1;
}

int PcmClose(int fd, int path_idx)
{
    return -1;
}

void StrFadeWkSet(void)
{
    unsigned int amount;

    if (str_fadein_fg == 0xFF0000F8)
    {
        amount = 100;
    }
    else
    {
        amount = 400;
        if (str_fadein_fg != 0xFF0000F9)
        {
            return;
        }
    }
    StrFadeIn(amount);
    str_fadein_fg = 0;
    str_fade_value = str_volume;
}

int StrFadeInt(void)
{
    SpuVoiceAttr attr;
    unsigned int diff;

    if (str_status < 5)
    {
        return 0;
    }

    if (str_fade_time != 0)
    {
        str_fade_value += str_fade_time;

        if (str_fade_value >= str_volume)
        {
            if (str_load_code == -1)
            {
                keyOff(SPU_21CH | SPU_22CH);
                str_status = 7;
            }
            else
            {
                str_fout_fg = 1;
            }

            str_fade_time = 0;
            str_fade_value = str_volume;
        }
        else
        {
            str_fout_fg = 0;
        }
    }

    attr.mask = SPU_VOICE_VOLL | SPU_VOICE_VOLR;
    attr.voice = SPU_21CH;

    diff = str_volume - str_fade_value;

    if ((str_mute_status != 0) && (str_mute_ctr < 2))
    {
        attr.volume.left = 0;
        attr.volume.right = 0;
    }
    else if (sound_mono_fg != 0)
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

    if ((str_mute_status != 0) && (str_mute_ctr < 2))
    {
        attr.volume.left = 0;
        attr.volume.right = 0;
    }
    else if (sound_mono_fg != 0)
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

void code2name(unsigned int code, char *name)
{
    /* forward declaration */
    extern char num2char(unsigned int num);

    if ((code + 0xff000000) <= 0xffff)
    {
        name[ 0] = 'S';
        name[ 1] = 'G';
        name[ 2] = num2char((code >> 20) & 0x0f);
        name[ 3] = num2char((code >> 16) & 0x0f);
        name[ 4] = num2char((code >> 12) & 0x0f);
        name[ 5] = num2char((code >>  8) & 0x0f);
        name[ 6] = num2char((code >>  4) & 0x0f);
        name[ 7] = num2char(code & 0x0f);
        name[ 8] = '.';
        name[ 9] = 'M';
        name[10] = 'D';
        name[11] = 'X';
        name[12] = '\0';
        return;
    }
    if ((code + 0xfe000000) <= 0xffff)
    {
        name[ 0] = 'S';
        name[ 1] = 'E';
        name[ 2] = num2char((code >> 20) & 0x0f);
        name[ 3] = num2char((code >> 16) & 0x0f);
        name[ 4] = num2char((code >> 12) & 0x0f);
        name[ 5] = num2char((code >>  8) & 0x0f);
        name[ 6] = num2char((code >>  4) & 0x0f);
        name[ 7] = num2char(code & 0x0f);
        name[ 8] = '.';
        name[ 9] = 'E';
        name[10] = 'F';
        name[11] = 'X';
        name[12] = '\0';
        return;
    }
    if ((code + 0x20000000) <= 0xffff)
    {
        name[ 0] = 'S';
        name[ 1] = 'D';
        name[ 2] = num2char((code >> 20) & 0x0f);
        name[ 3] = num2char((code >> 16) & 0x0f);
        name[ 4] = num2char((code >> 12) & 0x0f);
        name[ 5] = num2char((code >>  8) & 0x0f);
        name[ 6] = num2char((code >>  4) & 0x0f);
        name[ 7] = num2char(code & 0x0f);
        name[ 8] = '.';
        name[ 9] = 'P';
        name[10] = 'C';
        name[11] = 'M';
        name[12] = '\0';
        //return;
    }
    if ((code + 0x02000000) <= 0xffff)
    {
        name[ 0] = 'W';
        name[ 1] = 'V';
        name[ 2] = num2char((code >> 20) & 0x0f);
        name[ 3] = num2char((code >> 16) & 0x0f);
        name[ 4] = num2char((code >> 12) & 0x0f);
        name[ 5] = num2char((code >>  8) & 0x0f);
        name[ 6] = num2char((code >>  4) & 0x0f);
        name[ 7] = num2char(code & 0x0f);
        name[ 8] = '.';
        name[ 9] = 'W';
        name[10] = 'V';
        name[11] = 'X';
        name[12] = '\0';
        return;
    }
}

char num2char(unsigned int num)
{
    num &= 0x0f;
    if (num < 10)
    {
        num += '0';
    }
    else
    {
        num += ('a' - 10);
    }
    return num;
}

unsigned char *SD_SngDataLoadInit(unsigned short id)
{
    sng_play_code = 0;
    sng_status = 0;
    sng_off();
    printf("SD_SngDataLoadInit\n");
    return sng_data;
}

void SD_80083ED4(void)
{
    sng_status = 2;
}

unsigned char *SD_SeDataLoadInit(unsigned short id)
{
    return se_header;
}

void SD_80083EF8(void)
{
    se_load_code = 0;
}

char *SD_WavDataLoadInit(unsigned short id)
{
    char *ret;

    if (dword_800BF27C != 0)
    {
        printf("LoadInit %d\n", dword_800BF27C);
        *(int *)1 = 0;
    }
    ret = cdload_buf;
    dword_800BF27C = 1;
    return ret;
}

int SD_80083F54(char *end)
{
    unsigned char *src_ptr;
    unsigned char *dst_ptr;
    unsigned int offset;
    unsigned int size;
    unsigned int used;

    wavs = 0x4F;

    src_ptr = cdload_buf + 16;

    offset =  cdload_buf[0] << 24;
    offset |= cdload_buf[1] << 16;
    offset |= cdload_buf[2] << 8;
    offset |= cdload_buf[3];

    dst_ptr = (char *)wave_header + offset;

    size =  cdload_buf[4] << 24;
    size |= cdload_buf[5] << 16;
    size |= cdload_buf[6] << 8;
    size |= cdload_buf[7];

    wave_load_ptr = cdload_buf + 16;

    if (((unsigned int)src_ptr + size) >= (unsigned int)end)
    {
        return 0;
    }

    memcpy(dst_ptr, src_ptr, size);

    wave_load_ptr += size;

    spu_load_offset =  wave_load_ptr[0] << 24;
    spu_load_offset |= wave_load_ptr[1] << 16;
    spu_load_offset |= wave_load_ptr[2] << 8;
    spu_load_offset |= wave_load_ptr[3];

    wave_unload_size =  wave_load_ptr[4] << 24;
    wave_unload_size |= wave_load_ptr[5] << 16;
    wave_unload_size |= wave_load_ptr[6] << 8;
    wave_unload_size |= wave_load_ptr[7];

    wave_load_ptr += 16;

    used = (end - cdload_buf) - (size + 32);
    if (used < wave_unload_size)
    {
        wave_load_size = used;
    }
    else
    {
        wave_load_size = wave_unload_size;
    }

    wave_unload_size -= wave_load_size;
    wave_save_code = wave_load_code;

    if (!SpuIsTransferCompleted(SPU_TRANSFER_PEEK))
    {
        printf("$");
    }

    SpuSetTransferStartAddr(spu_wave_start_ptr + spu_load_offset);
    SpuWrite(wave_load_ptr, wave_load_size);

    spu_load_offset += wave_load_size;
    wave_load_ptr += wave_load_size;

    return 1;
}

char *SD_WavLoadBuf(char *arg0)
{
    char *buf;

    if (dword_800BF27C != 1 && wave_unload_size == 0)
    {
        dword_800BF27C = 0;
        return arg0;
    }

    switch (dword_800BF27C)
    {
    case 1:
        if (SD_80083F54(arg0) != 0)
        {
            dword_800BF27C = 3;
        }
        break;

    case 2:
        break;

    case 3:
        buf = cdload_buf + 0x18000;
        if (wave_load_ptr == buf)
        {
            wave_load_ptr = cdload_buf;
        }
        else if (buf < wave_load_ptr)
        {
            printf("!!! SD WAV LOAD BUF OVER !!!\n");
            *(int *)1 = 0;
        }
        if (arg0 < wave_load_ptr)
        {
            wave_load_size = 0x18000 + cdload_buf - (wave_load_ptr);
        }
        else
        {
            wave_load_size = arg0 - wave_load_ptr;
        }
        wave_unload_size -= wave_load_size;
        SpuSetTransferStartAddr(spu_wave_start_ptr + spu_load_offset);
        SpuWrite(wave_load_ptr, wave_load_size);
        spu_load_offset += wave_load_size;
        wave_load_ptr += wave_load_size;
        break;
    }

    if (arg0 >= cdload_buf + 0x18000)
    {
        arg0 = cdload_buf;
    }
    return arg0;
}

void SD_WavUnload(void)
{
    if (wave_unload_size)
    {
        if (wave_load_ptr == cdload_buf + 0x18000)
        {
            wave_load_ptr = cdload_buf;
        }
        SpuSetTransferStartAddr(spu_wave_start_ptr + spu_load_offset);
        SpuWrite(wave_load_ptr, wave_unload_size);
        spu_load_offset += wave_unload_size;
        wave_load_ptr += wave_unload_size;
    }
    dword_800BF27C = 0;
    if (wave_unload_size)
    {
        printf("unload %d\n", wave_unload_size);
    }
}
