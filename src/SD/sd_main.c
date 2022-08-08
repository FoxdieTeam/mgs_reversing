#include "SD/sd.h"
#include "psyq.h"
#include "unknown.h"

#pragma INCLUDE_ASM("asm/SD/sd_init_80081C7C.s")
#pragma INCLUDE_ASM("asm/SD/sub_80081F8C.s")

void SD_80081FC4(int param_1)
{
    SpuSetKey_80096C18(0, param_1);
}

#pragma INCLUDE_ASM("asm/SD/KeyOffStr_80081FE8.s")
#pragma INCLUDE_ASM("asm/SD/sub_800820EC.s")

void SD_80082170(int param_1)
{
    SpuSetKey_80096C18(1, param_1);
}

#pragma INCLUDE_ASM("asm/SD/sd_sng_alloc_80082194.s")
#pragma INCLUDE_ASM("asm/SD/StrFadeIn_800822C8.s")
#pragma INCLUDE_ASM("asm/SD/StrFadeOut_80082310.s")
#pragma INCLUDE_ASM("asm/SD/StrFadeOutStop_80082380.s")
#pragma INCLUDE_ASM("asm/SD/StartStream_80082448.s")
#pragma INCLUDE_ASM("asm/SD/UserSpuIRQProc_80082640.s")

void sub_8008279C(void)
{

}

void SD_nullsub_20_800827A4()
{
    
}

#pragma INCLUDE_ASM("asm/SD/StrSpuTransWithNoLoop_800827AC.s")
#pragma INCLUDE_ASM("asm/SD/StrSpuTransClose_80083394.s")

void StrSpuTrans_800833FC(void)
{
    StrSpuTransWithNoLoop_800827AC();
}

#pragma INCLUDE_ASM("asm/SD/SD_8008341C.s")
#pragma INCLUDE_ASM("asm/sub_800834FC.s")
#pragma INCLUDE_ASM("asm/SD/sub_80083804.s")

void WaveSpuTrans_80083944(void)
{

}

int SD_SongLoadData_8008394C(void)
{
    return -1;
}

int SD_80083954(void)
{
    return -1;
}

int SD_8008395C(void)
{
    return -1;
}

#pragma INCLUDE_ASM("asm/SD/StrFadeWkSet_80083964.s")
#pragma INCLUDE_ASM("asm/SD/StrFadeInt_800839C8.s")
#pragma INCLUDE_ASM("asm/SD/sub_80083BB4.s")

int num2char_80083E68(unsigned int num)
{
    num &= 0xf;
    if (num < 10)
    {
        num += 0x30;
    }
    else
    {
        num += 0x57;
    }
    return num & 0xff;
}

#pragma INCLUDE_ASM("asm/SD/SD_SngDataLoadInit_80083E8C.s")
#pragma INCLUDE_ASM("asm/SD/SD_80083ED4.s")
#pragma INCLUDE_ASM("asm/SD/SD_80083EE8.s")
#pragma INCLUDE_ASM("asm/sub_80083EF8.s")
#pragma INCLUDE_ASM("asm/SD/LoadInit_80083F08.s")
#pragma INCLUDE_ASM("asm/SD/SD_80083F54.s")
#pragma INCLUDE_ASM("asm/SD/SD_WavLoadBuf_800841D4.s")
#pragma INCLUDE_ASM("asm/SD/SD_Unload_800843BC.s")
