#include "linker.h"
#include "menuMan.h"

extern menu_chara_struct* dword_800ABB38;
menu_chara_struct* SECTION(".sbss") dword_800ABB38;

extern void sub_80047CB4(int *param_1);

void sub_80048100(void)

{
    sub_80047CB4((int*)dword_800ABB38);
    return;
}
