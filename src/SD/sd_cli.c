#include "SD/sd.h"
#include "linker.h"
#include "unknown.h"

extern char byte_800C0468[];
extern unsigned int sng_status_800C04F8;

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

#pragma INCLUDE_ASM("asm/SD/sub_80088868.s")
#pragma INCLUDE_ASM("asm/sub_800888B4.s")
#pragma INCLUDE_ASM("asm/SD/SePlay_800888F8.s")

extern int dword_8009F7B4;

int get_str_counter_80088CA0(void)
{
    return dword_8009F7B4;
}

#pragma INCLUDE_ASM("asm/SD/sd_set_80088CB0.s")
