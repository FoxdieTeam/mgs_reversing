#include "psyq.h"
#include "libdg/inline_n.h"

void sub_80028CF8(void)
{
    gte_lddp((*(int *)0x1F8000A8 * 4096) / (*(int *)0x1F8000AC));
    gte_ld_intpol_sv0((SVECTOR *)0x1F800030);
    gte_ldopv2SV((SVECTOR *)0x1F800028);
    gte_intpl();
    gte_stsv((SVECTOR *)0x1F800028);

    return;
}