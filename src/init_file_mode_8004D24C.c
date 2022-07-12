#include "linker.h"

extern void init_file_mode_helper_8004A424(int param_1);
extern void sub_8004A800(void);

extern int dword_800ABB84;
extern int dword_800ABB4C;

int SECTION(".sbss") dword_800ABB84;
int SECTION(".sbss") dword_800ABB4C;

void init_file_mode_8004D24C(int param_1, int param_2)
{
    dword_800ABB84 = 0;
    dword_800ABB4C = param_1;
    sub_8004A800();
    init_file_mode_helper_8004A424(param_2);
    return;
}
