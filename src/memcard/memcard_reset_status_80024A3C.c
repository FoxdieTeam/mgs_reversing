#include "memcard/memcard.h"

extern struct mem_card gMemCards_800B52F8[2];

void memcard_reset_status_80024A3C(void)
{
    gMemCards_800B52F8[0].field_1_last_op = 2;
    gMemCards_800B52F8[1].field_1_last_op = 2;
}
