#include "linker.h"

extern void font_clear_800468FC(int param_1);
extern void font_update_8004695C(int param_1);

extern int dword_800ABB04;
int SECTION(".sbss") dword_800ABB04;

void sub_80041118(int param_1)

{
    int iVar1;

    iVar1 = *(int *)(param_1 + 0x214);
    dword_800ABB04 = 0;
    font_clear_800468FC(iVar1);
    font_update_8004695C(iVar1);
    return;
}
