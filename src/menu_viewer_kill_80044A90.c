#include "linker.h"

extern unsigned char dword_800ABB20;
unsigned char SECTION(".sbss") dword_800ABB20;

void menu_viewer_kill_80044A90(void)

{
    dword_800ABB20 = 0;
    return;
}
