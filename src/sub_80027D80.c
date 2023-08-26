#include "libdg/libdg.h"

int sub_80027D80(char *ptr)
{
    long  sxy_0;
    long  sxy_1;
    long  sxy_2;
    long  sxy_3;
    long  sxy_4;
    long *pZ;

    sxy_1 = *(long *)getScratchAddr(19);
    sxy_3 = *(long *)(ptr + 0x10);
    sxy_0 = *(long *)(ptr + 0x18);

    gte_ldsxy3(sxy_3, sxy_0, sxy_1);
    gte_nclip();
    sxy_2 = *(long *)(ptr + 0x20);
    gte_stopz(getScratchAddr(2));

    pZ = (long *)getScratchAddr(2);

    if (*pZ >= 0)
    {
        gte_ldsxy3(sxy_0, sxy_2, sxy_1);
        gte_nclip();
        sxy_4 = *(long *)(ptr + 0x28);
        gte_stopz(getScratchAddr(2));

        if (*pZ < 0)
        {
            return 0;
        }

        gte_NormalClip(sxy_2, sxy_4, sxy_1, getScratchAddr(2));
        if(*pZ < 0)
        {
            return 0;
        }

        gte_NormalClip(sxy_4, sxy_3, sxy_1, getScratchAddr(2));
        return *pZ >= 0;
    }
    else
    {
        gte_ldsxy3(sxy_0, sxy_2, sxy_1);
        gte_nclip();
        sxy_4 = *(long *)(ptr + 0x28);
        gte_stopz(getScratchAddr(2));

        if (*pZ > 0)
        {
            return 0;
        }

        gte_NormalClip(sxy_2, sxy_4, sxy_1, getScratchAddr(2));
        if (*pZ > 0)
        {
            return 0;
        }

        gte_NormalClip(sxy_4, sxy_3, sxy_1, getScratchAddr(2));
        return *pZ <= 0;
    }
}
