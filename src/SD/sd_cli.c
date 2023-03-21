#include "SD/sd.h"
#include "linker.h"
#include "unknown.h"
#include "mts/mts_new.h"

extern char byte_800C0468[];
extern unsigned int sng_status_800C04F8;
extern const char aXaSoundStart[];
extern const char aXaSoundStop[];
extern int dword_8009F7B4;

int sd_set_cli_800887EC(int sdCode, int unused)
{
    sd_set_80088CB0(sdCode);
    return 0;
}

void sd_set_path_8008880C(const char *pName)
{
    strcpy_8008E768(byte_800C0468, pName);
}

unsigned int sub_80088838()
{
    if ( sng_status_800C04F8 == -1 || sng_status_800C04F8 == 0  )
    {
        return 0;
    }

    return sng_status_800C04F8;
}

void sub_80088860(void)
{

}

void XA_Start_80088868()
{
    SpuCommonAttr attr; // [sp+10h] [-28h] BYREF

    attr.mask = 704;
    attr.cd.volume.left = 0x7FFF;
    attr.cd.volume.right = 0x7FFF;
    attr.cd.mix = 1;
    SpuSetCommonAttr_80097038(&attr);
    mts_printf_8008BBA0(aXaSoundStart);
}

void XA_Stop_800888B4()
{
    SpuCommonAttr attr; // [sp+10h] [-28h] BYREF

    attr.mask = 704;
    attr.cd.volume.left = 0;
    attr.cd.volume.right = 0;
    attr.cd.mix = 0;
    SpuSetCommonAttr_80097038(&attr);
    mts_printf_8008BBA0(aXaSoundStop);
}

#pragma INCLUDE_ASM("asm/SD/SePlay_800888F8.s") // 936 bytes

int get_str_counter_80088CA0(void)
{
    return dword_8009F7B4;
}

extern const char aSdcodeX[];
extern const char aToomuchbgmsoun[];
extern const char aSdsetSameStrea[];
extern const char aSdsetLastStrea[];
extern const char aStrFoS[];
extern const char aStrFoLl[];
extern const char aStrFiLAtNextSt[];
extern const char aStrFiLStart[];
extern const char aErrStrFiL[];
extern const char aStrFoSStop[];
extern const char aStrFoM[];
extern const char aStrFoL[];
extern const char aStrFiMAtNextSt[];
extern const char aStrFoLlStop[];
extern const char aStrFoMStop[];
extern const char aStrFoLStop[];
extern const char aErrStrFiM[];
extern const char aStrFiMStart[];

extern int stop_jouchuu_se_800BF1A0;

extern int dword_800BF000;
extern int dword_800C04EC;
extern int dword_800BF160;
extern int dword_800BF26C;
extern int dword_800C050C;
extern int dword_800C04F4;
extern int dword_800C0410;
extern int dword_800BF27C;
extern int gStr_FadeOut1_800BF16C;
extern int gStr_fadeout_2_800C0584;
extern int gStream_800C04F0;
extern int se_rev_on_800C0574;
extern int sd_sng_code_buf_800BF018[16];
extern int bgm_idx_800BF1E8;
extern int dword_800BF144;
extern int se_load_code_800BF28C;
extern int wave_load_code_800C0528;
extern int wave_save_code_800C0578;

void sd_set_80088CB0(int sdCode)
{
    int sdCodeTopByte, new_bgm_idx;

    if (dword_800BF000 != 0)
    {
        mts_printf_8008BBA0(aSdcodeX, sdCode);
    }

    sdCodeTopByte = sdCode & 0xFF000000;
    if (sdCodeTopByte == 0)
    {
        if (sdCode & 0xFF)
        {
            SePlay_800888F8(sdCode);
        }
    }
    else if (sdCodeTopByte == 0x1000000)
    {
        if (sd_sng_code_buf_800BF018[bgm_idx_800BF1E8] == 0)
        {
            new_bgm_idx = (bgm_idx_800BF1E8 + 1) & 0xF;
            sd_sng_code_buf_800BF018[bgm_idx_800BF1E8] = sdCode;
            bgm_idx_800BF1E8 = new_bgm_idx;
            return;
        }

        mts_printf_8008BBA0(aToomuchbgmsoun, sdCode);
    }
    else if (sdCodeTopByte == 0x2000000)
    {
        mts_printf_8008BBA0(aSdcodeX, sdCode);
        se_load_code_800BF28C = sdCode;
    }
    else if (sdCodeTopByte == 0xFE000000)
    {
        if (wave_save_code_800C0578 != sdCode && dword_800C0410 != sdCode)
        {
            wave_load_code_800C0528 = sdCode;
            dword_800BF27C = 1;
            mts_wup_tsk_8008A540(5);
            return;
        }
    }
    else
    {
        if (sdCode >= 0xE0000000 && sdCode < 0xE1000000)
        {
            if (gStr_FadeOut1_800BF16C == 0)
            {
                if (gStream_800C04F0 == -1)
                {
                    dword_800C04F4 = 0;
                    gStr_fadeout_2_800C0584 = 0;
                }
                dword_800BF160 = sdCode & 1;
                gStream_800C04F0 = sdCode;
                gStr_FadeOut1_800BF16C = 1;
                mts_wup_tsk_8008A540(5);
                return;
            }
            if (gStream_800C04F0 != sdCode)
            {
                mts_printf_8008BBA0(aSdsetLastStrea, gStr_FadeOut1_800BF16C);
                return;
            }
            mts_printf_8008BBA0(aSdsetSameStrea, sdCode);
            return;
        }

        switch (sdCode)
        {
        case 0xFF000005:
            dword_800C050C = 1;
            return;
        case 0xFF000006:
            dword_800C050C = 0;
            return;
        case 0xFF000007:
            se_rev_on_800C0574 = 1;
            dword_800BF144 = 0;
            return;
        case 0xFF000008:
            se_rev_on_800C0574 = 0;
            dword_800BF144 = 0;
            return;
        case 0xFF000009:
            se_rev_on_800C0574 = 1;
            dword_800BF144 = 1;
            return;

        case 0xFF0000F4:
            StrFadeOut_80082310(0x64);
            mts_printf_8008BBA0(aStrFoS);
            return;
        case 0xFF0000F5:
            StrFadeOut_80082310(0xC8);
            mts_printf_8008BBA0(aStrFoM);
            return;
        case 0xFF0000F6:
            StrFadeOut_80082310(0x1F4);
            mts_printf_8008BBA0(aStrFoL);
            return;
        case 0xFF0000F7:
            StrFadeOut_80082310(0x3E8);
            mts_printf_8008BBA0(aStrFoLl);
            return;
        case 0xFF0000F8:
            if (gStream_800C04F0 != -1)
            {
                dword_800BF26C = 0;
                if (gStr_FadeOut1_800BF16C == 0)
                {
                    dword_800C04EC = sdCode;
                    mts_printf_8008BBA0(aStrFiMAtNextSt);
                    return;
                }
                StrFadeIn_800822C8(0xC8);
                mts_printf_8008BBA0(aStrFiMStart);
                return;
            }
            mts_printf_8008BBA0(aErrStrFiM);
            return;
        case 0xFF0000F9:
            if (gStream_800C04F0 != -1)
            {
                dword_800BF26C = 0;
                if (gStr_FadeOut1_800BF16C == 0)
                {
                    dword_800C04EC = sdCode;
                    mts_printf_8008BBA0(aStrFiLAtNextSt);
                    return;
                }
                StrFadeIn_800822C8(0x1F4);
                mts_printf_8008BBA0(aStrFiLStart);
                return;
            }
            mts_printf_8008BBA0(aErrStrFiL);
            return;
        case 0xFF0000FA:
            StrFadeOutStop_80082380(0x64);
            mts_printf_8008BBA0(aStrFoSStop);
            return;
        case 0xFF0000FB:
            StrFadeOutStop_80082380(0xC8);
            mts_printf_8008BBA0(aStrFoMStop);
            return;
        case 0xFF0000FC:
            StrFadeOutStop_80082380(0x1F4);
            mts_printf_8008BBA0(aStrFoLStop);
            return;
        case 0xFF0000FD:
            StrFadeOutStop_80082380(0x3E8);
            mts_printf_8008BBA0(aStrFoLlStop);
            return;
        case 0xFF0000FE:
            stop_jouchuu_se_800BF1A0 = 1;
            return;

        case 0xFFFFFFEC:
            SpuSetIRQ_80096A28(0);
            return;
        case 0xFFFFFFED:
            SpuSetIRQ_80096A28(1);
            return;
        case 0xFFFFFFFD:
            StrFadeOutStop_80082380(0x32);
            break;
        }
    }
}
