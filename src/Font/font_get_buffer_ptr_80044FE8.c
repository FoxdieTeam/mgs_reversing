#include "kcb.h"

void* font_get_buffer_ptr(KCB* kcb)
{
    return kcb->font_clut_buffer;
}