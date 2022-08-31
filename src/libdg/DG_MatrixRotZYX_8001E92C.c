#include "psyq.h"

void DG_MatrixRotZYX_8001E92C(MATRIX *pMatrix, SVECTOR *pVector)
{
    int iVar1;
    int iVar2;
    int iVar3;

    iVar1 = -pMatrix->m[2][0];
    iVar2 = SquareRoot0_80092708(0x1000000 - iVar1 * iVar1);

    if (iVar2 < 0x80)
    {
        iVar3 = 0x400;
    
        if (iVar1 <= 0)
        {
            iVar3 = 0xc00;
        }

        pVector->vy = iVar3;
        pVector->vx = ratan2_80094308(-pMatrix->m[1][2], pMatrix->m[1][1]);
        pVector->vz = 0;
    }
    else
    {
        pVector->vy = ratan2_80094308(iVar1, iVar2) & 0xfff;
        pVector->vx = ratan2_80094308((pMatrix->m[2][1] << 12) / iVar2, (pMatrix->m[2][2] << 12) / iVar2) & 0xfff;
        pVector->vz = ratan2_80094308((pMatrix->m[1][0] << 12) / iVar2, (pMatrix->m[0][0] << 12) / iVar2) & 0xfff;
    }
}
