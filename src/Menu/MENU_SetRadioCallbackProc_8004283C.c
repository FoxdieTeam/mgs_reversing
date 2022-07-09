#include "linker.h"

extern int dword_800ABB08;

int SECTION(".sbss") dword_800ABB08;

void MENU_SetRadioCallbackProc_8004283C(int param_1)
{
    dword_800ABB08 = param_1;
    return;
}
