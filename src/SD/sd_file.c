#include "SD/sound.h"
#include "SD/sd_incl.h"
#include "libfs/libfs.h"
#include "psyq.h"
#include "unknown.h"

extern char            *cdload_buf_800BF010;
extern int              spu_load_offset_800BF140;
extern int              sng_status_800BF158;
extern WAVE_W          *voice_tbl_800BF1E0;
extern int              wave_unload_size_800BF274;
extern unsigned int     dword_800BF27C;
extern int              se_load_code_800BF28C;
extern unsigned char   *sd_sng_data_800C0420;
extern unsigned int     sng_status_800C04F8;
extern char            *wave_load_ptr_800C0508;
extern unsigned char   *se_exp_table_800C0520;
extern int              wave_load_code_800C0528;
extern int              spu_wave_start_ptr_800C052C;
extern unsigned char    byte_800C056C;
extern int              wave_save_code_800C0578;
extern int              dword_800C0650;

void sng_off_80087E2C(void); /* in sd_ioset.c */

char num2char_80083E68(unsigned int num);

void code2name_80083BB4(unsigned int code, char *name)
{
    if ((code + 0xff000000) <= 0xffff)
    {
        name[ 0] = 'S';
        name[ 1] = 'G';
        name[ 2] = num2char_80083E68((code >> 20) & 0x0f);
        name[ 3] = num2char_80083E68((code >> 16) & 0x0f);
        name[ 4] = num2char_80083E68((code >> 12) & 0x0f);
        name[ 5] = num2char_80083E68((code >>  8) & 0x0f);
        name[ 6] = num2char_80083E68((code >>  4) & 0x0f);
        name[ 7] = num2char_80083E68(code & 0x0f);
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
        name[ 2] = num2char_80083E68((code >> 20) & 0x0f);
        name[ 3] = num2char_80083E68((code >> 16) & 0x0f);
        name[ 4] = num2char_80083E68((code >> 12) & 0x0f);
        name[ 5] = num2char_80083E68((code >>  8) & 0x0f);
        name[ 6] = num2char_80083E68((code >>  4) & 0x0f);
        name[ 7] = num2char_80083E68(code & 0x0f);
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
        name[ 2] = num2char_80083E68((code >> 20) & 0x0f);
        name[ 3] = num2char_80083E68((code >> 16) & 0x0f);
        name[ 4] = num2char_80083E68((code >> 12) & 0x0f);
        name[ 5] = num2char_80083E68((code >>  8) & 0x0f);
        name[ 6] = num2char_80083E68((code >>  4) & 0x0f);
        name[ 7] = num2char_80083E68(code & 0x0f);
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
        name[ 2] = num2char_80083E68((code >> 20) & 0x0f);
        name[ 3] = num2char_80083E68((code >> 16) & 0x0f);
        name[ 4] = num2char_80083E68((code >> 12) & 0x0f);
        name[ 5] = num2char_80083E68((code >>  8) & 0x0f);
        name[ 6] = num2char_80083E68((code >>  4) & 0x0f);
        name[ 7] = num2char_80083E68(code & 0x0f);
        name[ 8] = '.';
        name[ 9] = 'W';
        name[10] = 'V';
        name[11] = 'X';
        name[12] = '\0';
        return;
    }
}

char num2char_80083E68(unsigned int num)
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

unsigned char *SD_SngDataLoadInit_80083E8C(unsigned short unused)
{
    sng_status_800C04F8 = 0;
    sng_status_800BF158 = 0;
    sng_off_80087E2C();
    printf("SD_SngDataLoadInit\n");
    return sd_sng_data_800C0420;
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

char *LoadInit_80083F08(unsigned short unused)
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
    char        *src;
    char        *dst;
    int          offset;
    int          size;
    unsigned int used;

    byte_800C056C = 0x4F;

    src = cdload_buf_800BF010 + 16;

    offset = cdload_buf_800BF010[0] << 24;
    offset |= cdload_buf_800BF010[1] << 16;
    offset |= cdload_buf_800BF010[2] << 8;
    offset |= cdload_buf_800BF010[3];

    dst = (char *)voice_tbl_800BF1E0 + offset;

    size = cdload_buf_800BF010[4] << 24;
    size |= cdload_buf_800BF010[5] << 16;
    size |= cdload_buf_800BF010[6] << 8;
    size |= cdload_buf_800BF010[7];

    wave_load_ptr_800C0508 = cdload_buf_800BF010 + 16;

    if ((src + size) >= end)
    {
        return 0;
    }

    memcpy(dst, src, size);

    wave_load_ptr_800C0508 += size;

    spu_load_offset_800BF140 = wave_load_ptr_800C0508[0] << 24;
    spu_load_offset_800BF140 |= wave_load_ptr_800C0508[1] << 16;
    spu_load_offset_800BF140 |= wave_load_ptr_800C0508[2] << 8;
    spu_load_offset_800BF140 |= wave_load_ptr_800C0508[3];

    wave_unload_size_800BF274 = wave_load_ptr_800C0508[4] << 24;
    wave_unload_size_800BF274 |= wave_load_ptr_800C0508[5] << 16;
    wave_unload_size_800BF274 |= wave_load_ptr_800C0508[6] << 8;
    wave_unload_size_800BF274 |= wave_load_ptr_800C0508[7];

    wave_load_ptr_800C0508 += 16;

    used = (end - cdload_buf_800BF010) - (size + 32);
    if (used < wave_unload_size_800BF274)
    {
        dword_800C0650 = used;
    }
    else
    {
        dword_800C0650 = wave_unload_size_800BF274;
    }

    wave_unload_size_800BF274 -= dword_800C0650;
    wave_save_code_800C0578 = wave_load_code_800C0528;

    if (!SpuIsTransferCompleted(SPU_TRANSFER_PEEK))
    {
        printf("$");
    }

    SpuSetTransferStartAddr(spu_wave_start_ptr_800C052C + spu_load_offset_800BF140);
    SpuWrite(wave_load_ptr_800C0508, dword_800C0650);

    spu_load_offset_800BF140 += dword_800C0650;
    wave_load_ptr_800C0508 += dword_800C0650;

    return 1;
}

char *SD_WavLoadBuf_800841D4(char *arg0)
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
            dword_800C0650 = 0x18000 + cdload_buf_800BF010 - (wave_load_ptr_800C0508);
        }
        else
        {
            dword_800C0650 = arg0 - wave_load_ptr_800C0508;
        }
        wave_unload_size_800BF274 -= dword_800C0650;
        SpuSetTransferStartAddr(spu_wave_start_ptr_800C052C + spu_load_offset_800BF140);
        SpuWrite(wave_load_ptr_800C0508, dword_800C0650);
        spu_load_offset_800BF140 += dword_800C0650;
        wave_load_ptr_800C0508 += dword_800C0650;
        break;
    }

    if (arg0 >= cdload_buf_800BF010 + 0x18000)
    {
        arg0 = cdload_buf_800BF010;
    }
    return arg0;
}

void SD_Unload_800843BC(void)
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
