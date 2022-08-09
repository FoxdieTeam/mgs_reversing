#include "SD/sd.h"
#include "linker.h"
#include "unknown.h"

extern char byte_800C0468[];

int sd_set_cli_800887EC(int sdCode, int unused)
{
    sd_set_80088CB0(sdCode);
    return 0;
}

void sd_set_path_8008880C(const char *pName)
{
    strcpy_8008E768(byte_800C0468, pName);
}

#pragma INCLUDE_ASM("asm/sub_80088838.s")

void sub_80088860(void)
{
    return;
}
#pragma INCLUDE_ASM("asm/SD/sub_80088868.s")
#pragma INCLUDE_ASM("asm/sub_800888B4.s")
#pragma INCLUDE_ASM("asm/SD/SePlay_800888F8.s")

extern int dword_8009F7B4;

int get_str_counter_80088CA0(void)
{
    return dword_8009F7B4;
}

#pragma INCLUDE_ASM("asm/SD/sd_set_80088CB0.s")
