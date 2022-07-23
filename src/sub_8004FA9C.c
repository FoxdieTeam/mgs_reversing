#include "sna_init.h"

extern void sub_80051FD0(Actor_SnaInit *snake);
extern void sna_init_sub_8004E330(Actor_SnaInit *snake, unsigned int flag);

void sub_8004FA9C(Actor_SnaInit *snake)
{
    ushort action = *snake->field_9B0_pad_bits;
    sub_80051FD0(snake);
    if (action & 0x4000)
    {
        sna_init_sub_8004E330(snake, 1);
    }
}
