#include "libdg/libdg.h"

void sub_8003214C(SVECTOR *pVec, int *pRet)
{
    MATRIX *mtx;

    mtx = &DG_Chanl(0)->field_30_matrix;
    pVec->vx = mtx->t[0];
    pVec->vy = mtx->t[1];
    pVec->vz = mtx->t[2];
    *pRet = ratan2_80094308(mtx->m[0][2], mtx->m[2][2]);
}