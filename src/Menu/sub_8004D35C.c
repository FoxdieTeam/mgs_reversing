#include "menuMan.h"

extern MenuMan gMenuMan_800BD360;

void sub_8004124C(int param_1);

void sub_8004D35C(void)
{
    sub_8004124C((int) &gMenuMan_800BD360);
    return;
}
