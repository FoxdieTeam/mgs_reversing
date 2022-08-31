#include "psyq.h"

void DG_MatrixRotYXZ_8001E734(MATRIX *pMatrix, SVECTOR *pVector)
{
    int iVar1;
    int iVar2;
    int iVar3;

    iVar1 = -pMatrix->m[1][2];
    iVar2 = SquareRoot0_80092708(0x1000000 - iVar1 * iVar1);

    if (iVar2 < 0x80)
    {
        iVar3 = 0x400;
    
        if (iVar1 <= 0)
        {
            iVar3 = 0xc00;
        }
    
        pVector->vx = iVar3;
        pVector->vy = ratan2_80094308(-pMatrix->m[2][0], pMatrix->m[0][0]);
        pVector->vz = 0;
    }
    else
    {
        pVector->vx = ratan2_80094308(iVar1, iVar2) & 0xfff;
        pVector->vy = ratan2_80094308((pMatrix->m[0][2] << 12) / iVar2, (pMatrix->m[2][2] << 12) / iVar2) & 0xfff;
        pVector->vz = ratan2_80094308((pMatrix->m[1][0] << 12) / iVar2, (pMatrix->m[1][1] << 12) / iVar2) & 0xfff;
    }
    
    if (abs(pVector->vz) > 0x400)
    {
        pVector->vz = (pVector->vz + 0x800) & 0xfff;
        pVector->vy = (pVector->vy + 0x800) & 0xfff;
        pVector->vx = (0x800 - pVector->vx) & 0xfff;
    }
}
