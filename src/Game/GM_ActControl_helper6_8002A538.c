#include "unknown.h"
#include "libhzd/libhzd.h"
#include "Game/control.h"

void GM_ActControl_helper6_8002A538(HZD_MAP *pMap, Res_Control_unknown *arg1)
{
    SVECTOR *pSrcVec;
    short   *pArr;
    short   *pScr;
    short    tmp;
    int      i;

    pSrcVec = &arg1->field_14_vec;

    *(short *)0x1F800000 = pSrcVec->vx;
    do {} while (0);

    *(short *)0x1F800004 = pSrcVec->vy;
    pArr = arg1->field_8_array;
    do {} while (0);

    tmp = pSrcVec->vz;
    pScr = (short *)getScratchAddr(7);

    do {} while (0);

    *(short *)0x1F800002 = tmp;
    *getScratchAddr(6) = arg1->field_6_count;

    for (i = arg1->field_6_count; i > 0; i--)
    {
        *pScr++ = *pArr++;
    }

    GM_ActControl_helper6_helper_8002A27C(pMap, arg1);
    GM_ActControl_helper6_helper2_8002A4B8(pMap, arg1);
}
