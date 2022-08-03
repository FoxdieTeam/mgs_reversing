#include "linker.h"

void init_file_mode_helper_8004A424(int param_1);
void init_file_mode_helper2_8004A800(void);

extern int dword_800ABB80;
extern int dword_800ABB4C;

int SECTION(".sbss") dword_800ABB80;
int SECTION(".sbss") dword_800ABB4C;

void init_file_mode_8004D24C(int param_1, int param_2)
{
    dword_800ABB80 = 0;
    dword_800ABB4C = param_1;
    init_file_mode_helper2_8004A800();
    init_file_mode_helper_8004A424(param_2);
    return;
}
