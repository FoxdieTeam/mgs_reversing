#include <util/idaTypes.h>
#include <sys/types.h>
#include <libgte.h>

extern MATRIX *RotMatrixYXZ_80093798(SVECTOR *r, MATRIX *m);

void GV_DirVec3_80016FA0(SVECTOR *pSrcVec, int param_2, SVECTOR *pDstVec)
{
    MATRIX matrix;
    int iVar1;

    RotMatrixYXZ_80093798(pSrcVec, &matrix);

    iVar1 = param_2 * matrix.m[0][2];
    if (iVar1 < 0)
    {
        iVar1 += ONE - 1;
    }
    pDstVec->vx = (short)(iVar1 >> 0xc);

    iVar1 = param_2 * matrix.m[1][2];
    if (iVar1 < 0)
    {
        iVar1 += ONE - 1;
    }
    pDstVec->vy = (short)(iVar1 >> 0xc);

    iVar1 = param_2 * matrix.m[2][2];
    if (iVar1 < 0)
    {
        iVar1 += ONE - 1;
    }
    pDstVec->vz = (short)(iVar1 >> 0xc);
}
