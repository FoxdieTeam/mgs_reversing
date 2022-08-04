#include "util/idaTypes.h"

void face_item_helper_80060CB8(WORD *in, WORD *out)
{
    WORD i;
    for (i = 0; i < 5; i++)
    {
        *out++ = *in++;
    }
}
