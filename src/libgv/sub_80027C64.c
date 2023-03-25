#include "libgv.h"
#include "libdg/inline_n.h"

int sub_80027BF8(SVECTOR *v);

int sub_80027C64(void)
{
    int dividend;
    int val;

    val = *(short *)getScratchAddr(0xE);

    if (val == *getScratchAddr(0x1D))
    {
        return *getScratchAddr(0x1E);
    }

    dividend = (val - *(short *)getScratchAddr(0x4)) * 4096;
    gte_lddp(dividend / (*(short *)getScratchAddr(0x6) - *(short *)getScratchAddr(0x4)));
    gte_ld_intpol_sv0((SVECTOR *)getScratchAddr(0x5));
    gte_ldopv2SV((SVECTOR *)getScratchAddr(0x3));
    gte_intpl();
    gte_stsv((SVECTOR *)getScratchAddr(0x13));
    *getScratchAddr(0x1D) = val;
    *getScratchAddr(0x1E) = sub_80027BF8((SVECTOR *)getScratchAddr(0x13));
    return *getScratchAddr(0x1E);
}
