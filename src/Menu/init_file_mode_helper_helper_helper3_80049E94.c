#include "linker.h"
#include "mts/mts_new.h"

extern int dword_800ABB58;
int SECTION(".sbss") dword_800ABB58;

extern int dword_800ABB5C;
int SECTION(".sbss") dword_800ABB5C;

extern char aRequestX[];
extern char aResultX[];

int init_file_mode_helper_helper_helper3_80049E94(int param_1)
{
    dword_800ABB58 = param_1;
    mts_printf_8008BBA0(aRequestX, param_1);  // = "REQUEST %X\n"
    mts_slp_tsk_8008A400();
    mts_printf_8008BBA0(aResultX, dword_800ABB5C); // = "RESULT %X\n"
    return dword_800ABB5C;
}
