
#include "psyq.h"
#include "libdg/inline_n.h"

void sub_8002799C(int a0)
{
    int v1;
    int v0;

    if (a0 == 1)
    {
        v0 = *(short *)0x1F80004C;
        v1 = *(short *)0x1F800034;
        v0 -= v1;
        v1 = *(short *)0x1F800048;
    }
    else
    {
        v0 = *(short *)0x1F80004E; // TODO: is this a part of (SVECTOR *)0x1f800040 ???, same case above/below
        v1 = *(short *)0x1F800036;
        v0 -= v1;
        v1 = *(short *)0x1F80004A;
    }

    v0 *= 4096;
    v1 = v0 / v1;

    gte_lddp(v1);
    gte_ld_intpol_sv0((SVECTOR *)0x1F800040);
    gte_ldopv2SV((SVECTOR *)0x1F800038);
    gte_intpl();
    gte_stsv((SVECTOR *)0x1F800038);
    return;
}