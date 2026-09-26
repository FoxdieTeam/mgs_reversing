#include "libgv/libgv.h"

void rank_800D4808(unsigned short address, unsigned short message)
{
    GV_MSG msg;

    msg.address = address;
    msg._len = 1;
    msg.message[0] = message;
    GV_SendMessage(&msg);
}
