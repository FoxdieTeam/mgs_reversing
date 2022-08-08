#include "SD/sd.h"
#include "linker.h"
#include "unknown.h"

int sd_set_cli_800887EC(int sdCode, int unused)
{
    sd_set_80088CB0(sdCode);
    return 0;
}
#pragma INCLUDE_ASM("asm/SD/sd_set_path_8008880C.s")
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
