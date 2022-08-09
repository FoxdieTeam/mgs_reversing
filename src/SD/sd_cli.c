#include "SD/sd.h"
#include "linker.h"
#include "unknown.h"
#include "mts/mts_new.h"

extern char byte_800C0468[];
extern unsigned int sng_status_800C04F8;
extern const char aXaSoundStart[];
extern const char aXaSoundStop[];
extern int dword_8009F7B4;

void mts_wup_tsk_8008A540(int taskNr); // TODO mts_new.h

// TODO: psyq.h
long SpuSetIRQ_80096A28(long on_off);

void StrFadeIn_800822C8(unsigned int a1);
int StrFadeOutStop_80082380(unsigned int fadeSpeed);
int SePlay_800888F8(int a1);
int StrFadeOut_80082310(unsigned int a1);

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

#pragma INCLUDE_ASM("asm/SD/SePlay_800888F8.s")

int get_str_counter_80088CA0(void)
{
    return dword_8009F7B4;
}

#pragma INCLUDE_ASM("asm/SD/sd_set_80088CB0.s")

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
