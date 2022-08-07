#include <SYS/TYPES.H>

void face_item_helper_80060CB8(u_short *in, u_short *out)
{
    u_short i;
    for (i = 0; i < 5; i++)
    {
        *out++ = *in++;
    }
}
