#include "SD/sd_incl.h"
#include "SD/sd_ext.h"

#include "libfs/libfs.h"
#include "psyq.h"

extern unsigned char *se_exp_table_800C0520;

int SD_LoadSeFile(void)
{
    if (se_fp_800BF014)
    {
        printf("ERROR:SE File Already Opened.\n");
        SD_8008395C(se_fp_800BF014, 4);
        se_fp_800BF014 = 0;
    }
    se_fp_800BF014 = SD_SongLoadData(se_load_code_800BF28C, 4);
    if (se_fp_800BF014 < 0)
    {
        se_fp_800BF014 = 0;
        printf("LoadSeFile:File Open Error(%x)\n", se_load_code_800BF28C);
        sub_80081A10(&dword_800C0500, -4, se_load_code_800BF28C); // TODO: Not sure if last arg exists
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

int LoadWaveHeader(void)
{
    unsigned char *dst_ptr;
    unsigned int offset;
    unsigned int size;

    if (wave_data_800BF294 != 0)
    {
        printf("ERROR:Wave File Already Opened.\n");
        SD_8008395C(wave_data_800BF294, 2);
        wave_data_800BF294 = 0;
    }

    wave_data_800BF294 = SD_SongLoadData(wave_load_code_800C0528, 2);

    if (wave_data_800BF294 < 0)
    {
        wave_data_800BF294 = 0;
        printf("LoadWaveFile:File Open Error(%x)\n", wave_load_code_800C0528);
        sub_80081A10(&dword_800C0500, -4, wave_load_code_800C0528);
        wave_load_code_800C0528 = 0;
        return -1;
    }

    SD_80083954(wave_data_800BF294, cdload_buf_800BF010, 0x18000);
    wavs_800C056C = 0x4F;

    offset =  cdload_buf_800BF010[0] << 24;
    offset |= cdload_buf_800BF010[1] << 16;
    offset |= cdload_buf_800BF010[2] << 8;
    offset |= cdload_buf_800BF010[3];

    size =  cdload_buf_800BF010[4] << 24;
    size |= cdload_buf_800BF010[5] << 16;
    size |= cdload_buf_800BF010[6] << 8;
    size |= cdload_buf_800BF010[7];

    printf("SUP OFFSET=%x:SIZE=%x\n", offset, size);

    wave_load_ptr_800C0508 = cdload_buf_800BF010 + 16;
    dst_ptr = (char *)wave_header_800BF1E0 + offset;
    memcpy(dst_ptr, wave_load_ptr_800C0508, size);

    printf("    SRC=%x:DST=%x\n", (unsigned int)wave_load_ptr_800C0508, (unsigned int)dst_ptr);

    wave_load_ptr_800C0508 += size;

    spu_load_offset_800BF140 =  wave_load_ptr_800C0508[0] << 24;
    spu_load_offset_800BF140 |= wave_load_ptr_800C0508[1] << 16;
    spu_load_offset_800BF140 |= wave_load_ptr_800C0508[2] << 8;
    spu_load_offset_800BF140 |= wave_load_ptr_800C0508[3];

    wave_unload_size_800BF274 =  wave_load_ptr_800C0508[4] << 24;
    wave_unload_size_800BF274 |= wave_load_ptr_800C0508[5] << 16;
    wave_unload_size_800BF274 |= wave_load_ptr_800C0508[6] << 8;
    wave_unload_size_800BF274 |= wave_load_ptr_800C0508[7];

    printf("BIN OFFSET=%x\n", (unsigned int)wave_load_ptr_800C0508);
    printf("SPU OFFSET=%x:SIZE=%x\n", spu_load_offset_800BF140, wave_unload_size_800BF274);

    wave_load_ptr_800C0508 += 16;

    if (wave_unload_size_800BF274 > (CDLOAD_BUF_SIZE - (size + 0x20)))
    {
        wave_load_size_800C0650 = CDLOAD_BUF_SIZE - (size + 0x20);
    }
    else
    {
        wave_load_size_800C0650 = wave_unload_size_800BF274;
    }

    wave_unload_size_800BF274 -= wave_load_size_800C0650;
    wave_save_code_800C0578 = wave_load_code_800C0528;
    return 0;
}

void WaveCdLoad(void)
{
    int temp;

    if (wave_unload_size_800BF274 > 0x18000U)
    {
        SD_80083954(wave_data_800BF294, cdload_buf_800BF010, 0x18000);
        wave_load_size_800C0650 = 0x18000;
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
        wave_load_size_800C0650 = temp;
        return;
    }
    dword_800BF27C = 0;
    SD_8008395C(wave_data_800BF294, 2);
    printf("Complete Load Se:%x\n", wave_load_code_800C0528);
    wave_data_800BF294 = 0;
    sub_80081A10(&dword_800C0500, 0, wave_load_code_800C0528);
}

void WaveSpuTrans(void)
{
    /* do nothing */
}

int SD_SongLoadData(int a1, int a2)
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

void StrFadeWkSet(void)
{
    unsigned int amount; // $a0

    if (str_fadein_fg_800C04EC == 0xFF0000F8)
    {
        amount = 100;
    }
    else
    {
        amount = 400;
        if (str_fadein_fg_800C04EC != 0xFF0000F9)
        {
            return;
        }
    }
    StrFadeIn(amount);
    str_fadein_fg_800C04EC = 0;
    str_fade_value_800C0584 = str_volume_800BF15C;
}

int StrFadeInt(void)
{
    SpuVoiceAttr attr;
    unsigned int diff;

    if (str_status_800BF16C < 5)
    {
        return 0;
    }

    if (str_fade_time_800C04F4 != 0)
    {
        str_fade_value_800C0584 += str_fade_time_800C04F4;

        if (str_fade_value_800C0584 >= str_volume_800BF15C)
        {
            if (str_load_code_800C04F0 == -1)
            {
                keyOff(0x600000);
                str_status_800BF16C = 7;
            }
            else
            {
                str_fout_fg_800BF26C = 1;
            }

            str_fade_time_800C04F4 = 0;
            str_fade_value_800C0584 = str_volume_800BF15C;
        }
        else
        {
            str_fout_fg_800BF26C = 0;
        }
    }

    attr.mask = SPU_VOICE_VOLL | SPU_VOICE_VOLR;
    attr.voice = SPU_21CH;

    diff = str_volume_800BF15C - str_fade_value_800C0584;

    if ((str_mute_status_800BF1DC != 0) && (str_mute_ctr_800C0418 < 2))
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

    if ((str_mute_status_800BF1DC != 0) && (str_mute_ctr_800C0418 < 2))
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

unsigned char *SD_SngDataLoadInit(unsigned short unused)
{
    sng_play_code_800C04F8 = 0;
    sng_status_800BF158 = 0;
    sng_off();
    printf("SD_SngDataLoadInit\n");
    return sng_data_800C0420;
}

void SD_80083ED4(void)
{
    sng_status_800BF158 = 2;
}

unsigned char *SD_80083EE8(unsigned short unused)
{
    return se_exp_table_800C0520;
}

void SD_80083EF8(void)
{
    se_load_code_800BF28C = 0;
}

char *LoadInit(unsigned short unused)
{
    char *ret;

    if (dword_800BF27C != 0)
    {
        printf("LoadInit %d\n", dword_800BF27C);
        *(int *)1 = 0;
    }
    ret = cdload_buf_800BF010;
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

    wavs_800C056C = 0x4F;

    src_ptr = cdload_buf_800BF010 + 16;

    offset =  cdload_buf_800BF010[0] << 24;
    offset |= cdload_buf_800BF010[1] << 16;
    offset |= cdload_buf_800BF010[2] << 8;
    offset |= cdload_buf_800BF010[3];

    dst_ptr = (char *)wave_header_800BF1E0 + offset;

    size =  cdload_buf_800BF010[4] << 24;
    size |= cdload_buf_800BF010[5] << 16;
    size |= cdload_buf_800BF010[6] << 8;
    size |= cdload_buf_800BF010[7];

    wave_load_ptr_800C0508 = cdload_buf_800BF010 + 16;

    if (((unsigned int)src_ptr + size) >= (unsigned int)end)
    {
        return 0;
    }

    memcpy(dst_ptr, src_ptr, size);

    wave_load_ptr_800C0508 += size;

    spu_load_offset_800BF140 =  wave_load_ptr_800C0508[0] << 24;
    spu_load_offset_800BF140 |= wave_load_ptr_800C0508[1] << 16;
    spu_load_offset_800BF140 |= wave_load_ptr_800C0508[2] << 8;
    spu_load_offset_800BF140 |= wave_load_ptr_800C0508[3];

    wave_unload_size_800BF274 =  wave_load_ptr_800C0508[4] << 24;
    wave_unload_size_800BF274 |= wave_load_ptr_800C0508[5] << 16;
    wave_unload_size_800BF274 |= wave_load_ptr_800C0508[6] << 8;
    wave_unload_size_800BF274 |= wave_load_ptr_800C0508[7];

    wave_load_ptr_800C0508 += 16;

    used = (end - cdload_buf_800BF010) - (size + 32);
    if (used < wave_unload_size_800BF274)
    {
        wave_load_size_800C0650 = used;
    }
    else
    {
        wave_load_size_800C0650 = wave_unload_size_800BF274;
    }

    wave_unload_size_800BF274 -= wave_load_size_800C0650;
    wave_save_code_800C0578 = wave_load_code_800C0528;

    if (!SpuIsTransferCompleted(SPU_TRANSFER_PEEK))
    {
        printf("$");
    }

    SpuSetTransferStartAddr(spu_wave_start_ptr_800C052C + spu_load_offset_800BF140);
    SpuWrite(wave_load_ptr_800C0508, wave_load_size_800C0650);

    spu_load_offset_800BF140 += wave_load_size_800C0650;
    wave_load_ptr_800C0508 += wave_load_size_800C0650;

    return 1;
}

char *SD_WavLoadBuf(char *arg0)
{
    char *buf;

    if (dword_800BF27C != 1 && wave_unload_size_800BF274 == 0)
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
        buf = cdload_buf_800BF010 + 0x18000;
        if (wave_load_ptr_800C0508 == buf)
        {
            wave_load_ptr_800C0508 = cdload_buf_800BF010;
        }
        else if (buf < wave_load_ptr_800C0508)
        {
            printf("!!! SD WAV LOAD BUF OVER !!!\n");
            *(int *)1 = 0;
        }
        if (arg0 < wave_load_ptr_800C0508)
        {
            wave_load_size_800C0650 = 0x18000 + cdload_buf_800BF010 - (wave_load_ptr_800C0508);
        }
        else
        {
            wave_load_size_800C0650 = arg0 - wave_load_ptr_800C0508;
        }
        wave_unload_size_800BF274 -= wave_load_size_800C0650;
        SpuSetTransferStartAddr(spu_wave_start_ptr_800C052C + spu_load_offset_800BF140);
        SpuWrite(wave_load_ptr_800C0508, wave_load_size_800C0650);
        spu_load_offset_800BF140 += wave_load_size_800C0650;
        wave_load_ptr_800C0508 += wave_load_size_800C0650;
        break;
    }

    if (arg0 >= cdload_buf_800BF010 + 0x18000)
    {
        arg0 = cdload_buf_800BF010;
    }
    return arg0;
}

void SD_Unload(void)
{
    if (wave_unload_size_800BF274)
    {
        if (wave_load_ptr_800C0508 == cdload_buf_800BF010 + 0x18000)
        {
            wave_load_ptr_800C0508 = cdload_buf_800BF010;
        }
        SpuSetTransferStartAddr(spu_wave_start_ptr_800C052C + spu_load_offset_800BF140);
        SpuWrite(wave_load_ptr_800C0508, wave_unload_size_800BF274);
        spu_load_offset_800BF140 += wave_unload_size_800BF274;
        wave_load_ptr_800C0508 += wave_unload_size_800BF274;
    }
    dword_800BF27C = 0;
    if (wave_unload_size_800BF274)
    {
        printf("unload %d\n", wave_unload_size_800BF274);
    }
}
