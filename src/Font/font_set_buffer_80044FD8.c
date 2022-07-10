#include "kcb.h"

void font_set_buffer_80044FD8(KCB* kcb, void* buffer)
{
    kcb->font_clut_buffer = buffer;
    kcb->font_buffer = buffer + 0x20;
    return;
}
