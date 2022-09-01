#include "inline_n.h"
#include "libdg.h"

static inline void DG_ReflectMatrix_8001EDCC_helper(MATRIX *pMatrixIn, MATRIX *pMatrixOut, int m, int n, int v)
{   
	if (v < 0)
	{
        v += 0x7ff;
	}    
    
	pMatrixOut->m[m][n] = pMatrixIn->m[m][n] - (v >> 11);
}

void DG_ReflectMatrix_8001EDCC(SVECTOR *pVector, MATRIX *pMatrixIn, MATRIX *pMatrixOut)
{
    MATRIX transpose;
    SVECTOR reflected;
    int element;
    
    DG_TransposeMatrix_8001EAD8(pMatrixIn, &transpose);
    gte_SetRotMatrix(&transpose);
    gte_ldsv(pVector);
    gte_rtir();
    gte_stsv(&reflected);

    element = reflected.vx;
    DG_ReflectMatrix_8001EDCC_helper(pMatrixIn, pMatrixOut, 0, 0, pVector->vx * element);
    DG_ReflectMatrix_8001EDCC_helper(pMatrixIn, pMatrixOut, 1, 0, pVector->vy * element);
    DG_ReflectMatrix_8001EDCC_helper(pMatrixIn, pMatrixOut, 2, 0, pVector->vz * element);

    element = reflected.vy;
    DG_ReflectMatrix_8001EDCC_helper(pMatrixIn, pMatrixOut, 0, 1, pVector->vx * element);
    DG_ReflectMatrix_8001EDCC_helper(pMatrixIn, pMatrixOut, 1, 1, pVector->vy * element);
    DG_ReflectMatrix_8001EDCC_helper(pMatrixIn, pMatrixOut, 2, 1, pVector->vz * element);

    element = reflected.vz;
    DG_ReflectMatrix_8001EDCC_helper(pMatrixIn, pMatrixOut, 0, 2, pVector->vx * element);
    DG_ReflectMatrix_8001EDCC_helper(pMatrixIn, pMatrixOut, 1, 2, pVector->vy * element);
    DG_ReflectMatrix_8001EDCC_helper(pMatrixIn, pMatrixOut, 2, 2, pVector->vz * element);
}
