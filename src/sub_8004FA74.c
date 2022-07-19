#include "sna_init.h"

extern void GM_ClearPlayerStatusFlag_8004E2D4(unsigned int param_1);
extern void sna_init_clear_flags_8004E344(Actor_SnaInit* param_1, unsigned int param_2);

void sub_8004FA74(Actor_SnaInit* param_1)
{
    sna_init_clear_flags_8004E344(param_1, 0x20);
    GM_ClearPlayerStatusFlag_8004E2D4(0x8408);
}
