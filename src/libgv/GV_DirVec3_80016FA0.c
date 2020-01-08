#include <util/idaTypes.h>
#include <sys/types.h>
#include <libgte.h>

extern MATRIX *RotMatrixYXZ_80093798(SVECTOR *r, MATRIX *m);

void GV_DirVec3_80016FA0(SVECTOR *pSrcVec, int param_2, SVECTOR *pDstVec)
{
    MATRIX matrix;
    int iVar1;

    RotMatrixYXZ_80093798(pSrcVec, &matrix);
    pDstVec->vx = param_2 * matrix.m[0][2] / ONE;
    pDstVec->vy =  param_2 * matrix.m[1][2] / ONE;
    pDstVec->vz = param_2 * matrix.m[2][2] / ONE;
}
