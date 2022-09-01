#include "psyq.h"

void sub_8001EB38(MATRIX *pMatrixOut, MATRIX *pMatrixIn, int param_3)
{
    int x, y, z;
    short *pElement;
    int count;
    int iVar1;
    int iVar2;
    int iVar3;
    
    x = pMatrixIn->m[0][0] + pMatrixIn->m[1][0] + pMatrixIn->m[2][0];
    y = pMatrixIn->m[0][1] + pMatrixIn->m[1][1] + pMatrixIn->m[2][1];
    z = pMatrixIn->m[0][2] + pMatrixIn->m[1][2] + pMatrixIn->m[2][2];
    
    if (y < 0)
    {
        pElement = pMatrixOut->m;

        for (count = 3; count > 0; count--)
        {
            iVar1 =  (pElement[3] << 12) / y;
            iVar2 = x * iVar1;

            if (iVar2 < 0)
            {
                iVar2 += 0xfff;
            }

            iVar3 = z * iVar1;
            pElement[0] -= iVar2 >> 12;

            if (iVar3 < 0)
            {
                iVar3 += 0xfff;
            }

            pElement[6] -= iVar3 >> 12;
            pElement++;
        }

        iVar1 = (param_3 << 12) / y;
        iVar2 = x * iVar1;
    
        if (iVar2 < 0)
        {
            iVar2 += 0xfff;
        }
    
        iVar3 = z * iVar1;
        pMatrixOut->t[0] -= iVar2 >> 12;
    
        if (iVar3 < 0)
        {
            iVar3 += 0xfff;
        }
    
        pMatrixOut->t[2] -= iVar3 >> 12;
    }

    pMatrixOut->t[1] -= param_3;

    pMatrixOut->m[1][0] = 0;
    pMatrixOut->m[1][1] = 0;
    pMatrixOut->m[1][2] = 0;
}
