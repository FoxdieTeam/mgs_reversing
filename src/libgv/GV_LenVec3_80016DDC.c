#include <sys/types.h>
#include <libgte.h>

void GV_LenVec3_80016DDC(SVECTOR *pSrcVec, SVECTOR *pDstVec, int param_3, int param_4)
{
    param_4 = param_4 * ONE;
    if (param_3 == 0)
    {
        param_3 = 1;
    }
    param_4 /= param_3;

    pDstVec->vx = pSrcVec->vx * param_4 / ONE;
    pDstVec->vy = pSrcVec->vy * param_4 / ONE;
    pDstVec->vz = pSrcVec->vz * param_4 / ONE;
}
