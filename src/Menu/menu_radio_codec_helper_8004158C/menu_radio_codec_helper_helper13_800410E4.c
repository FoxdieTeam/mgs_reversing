#include "linker.h"

void font_update_8004695C(int param_1);
void sub_800469A4(int param_1, char *param_2);

extern int dword_800ABB04;
int SECTION(".sbss") dword_800ABB04;

void menu_radio_codec_helper__helper13_800410E4(int param_1, int param_2)
{
    int iVar1;

    iVar1 = *(int *)(param_1 + 0x214);
    dword_800ABB04 = param_2;
    sub_800469A4(iVar1, (char *)param_2);
    font_update_8004695C(iVar1);
    return;
}
