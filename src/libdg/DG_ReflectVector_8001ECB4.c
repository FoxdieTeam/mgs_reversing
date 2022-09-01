#include "inline_n.h"
#include "psyq.h"

void DG_ReflectVector_8001ECB4(SVECTOR *pVecIn, SVECTOR *pVecTranslation, SVECTOR *pVecOut)
{
    MATRIX matrix;
    
    matrix.m[0][0] = pVecIn->vx;
    matrix.m[0][1] = matrix.m[1][0] = pVecIn->vy;
    matrix.m[0][2] = matrix.m[2][0] = pVecIn->vz;
    
    matrix.t[0] = pVecTranslation->vx;
    matrix.t[1] = pVecTranslation->vy;
    matrix.t[2] = pVecTranslation->vz;

    gte_SetRotMatrix(&matrix);
    gte_SetTransMatrix(&matrix);
    gte_ldsv(pVecTranslation);
    gte_rtir();
    gte_stsv(pVecOut);
  
    pVecOut->vz = 0;
    pVecOut->vy = 0;
    pVecOut->vx *= -2;

    gte_ldv0(pVecOut);
    gte_rt();
    gte_stsv(pVecOut);
}
