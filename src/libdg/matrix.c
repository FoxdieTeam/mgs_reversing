#include "psyq.h"
#include "libdg.h"


void DG_MatrixRotXYZ_8001E588(MATRIX *pMatrix, SVECTOR *pVector)
{
    int iVar1;
    int iVar2;
    int iVar3;

    iVar1 = pMatrix->m[0][2];
    iVar2 = SquareRoot0(0x1000000 - iVar1 * iVar1);

    if (iVar2 < 0x80)
    {
        iVar3 = 0x400;

        if (iVar1 <= 0)
        {
            iVar3 = 3072;
        }

        pVector->vy = iVar3;
        pVector->vx = ratan2(pMatrix->m[1][2], pMatrix->m[1][1]);
        pVector->vz = 0;
    }
    else
    {
        pVector->vy = ratan2(iVar1, iVar2) & 0xfff;
        pVector->vx = ratan2((-pMatrix->m[1][2] << 12) / iVar2, (pMatrix->m[2][2] << 12) / iVar2) & 0xfff;
        pVector->vz = ratan2((-pMatrix->m[0][1] << 12) / iVar2, (pMatrix->m[0][0] << 12) / iVar2) & 0xfff;
    }
}

void DG_MatrixRotYXZ_8001E734(MATRIX *pMatrix, SVECTOR *pVector)
{
    int iVar1;
    int iVar2;
    int iVar3;

    iVar1 = -pMatrix->m[1][2];
    iVar2 = SquareRoot0(0x1000000 - iVar1 * iVar1);

    if (iVar2 < 0x80)
    {
        iVar3 = 0x400;

        if (iVar1 <= 0)
        {
            iVar3 = 3072;
        }

        pVector->vx = iVar3;
        pVector->vy = ratan2(-pMatrix->m[2][0], pMatrix->m[0][0]);
        pVector->vz = 0;
    }
    else
    {
        pVector->vx = ratan2(iVar1, iVar2) & 0xfff;
        pVector->vy = ratan2((pMatrix->m[0][2] << 12) / iVar2, (pMatrix->m[2][2] << 12) / iVar2) & 0xfff;
        pVector->vz = ratan2((pMatrix->m[1][0] << 12) / iVar2, (pMatrix->m[1][1] << 12) / iVar2) & 0xfff;
    }

    if (abs(pVector->vz) > 0x400)
    {
        pVector->vz = (pVector->vz + 0x800) & 0xfff;
        pVector->vy = (pVector->vy + 0x800) & 0xfff;
        pVector->vx = (0x800 - pVector->vx) & 0xfff;
    }
}

void DG_MatrixRotZYX_8001E92C(MATRIX *pMatrix, SVECTOR *pVector)
{
    int iVar1;
    int iVar2;
    int iVar3;

    iVar1 = -pMatrix->m[2][0];
    iVar2 = SquareRoot0(0x1000000 - iVar1 * iVar1);

    if (iVar2 < 0x80)
    {
        iVar3 = 0x400;

        if (iVar1 <= 0)
        {
            iVar3 = 3072;
        }

        pVector->vy = iVar3;
        pVector->vx = ratan2(-pMatrix->m[1][2], pMatrix->m[1][1]);
        pVector->vz = 0;
    }
    else
    {
        pVector->vy = ratan2(iVar1, iVar2) & 0xfff;
        pVector->vx = ratan2((pMatrix->m[2][1] << 12) / iVar2, (pMatrix->m[2][2] << 12) / iVar2) & 0xfff;
        pVector->vz = ratan2((pMatrix->m[1][0] << 12) / iVar2, (pMatrix->m[0][0] << 12) / iVar2) & 0xfff;
    }
}

void DG_TransposeMatrix_8001EAD8(MATRIX *in, MATRIX *out)
{
    short temp;

    temp = in->m[1][0];
    out->m[1][0] = in->m[0][1];
    out->m[0][1] = temp;

    temp = in->m[2][0];
    out->m[2][0] = in->m[0][2];
    out->m[0][2] = temp;

    temp = in->m[2][1];
    out->m[2][1] = in->m[1][2];
    out->m[1][2] = temp;

    if (in != out)
    {
        out->m[0][0] = in->m[0][0];
        out->m[1][1] = in->m[1][1];
        out->m[2][2] = in->m[2][2];
    }
}

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
        pElement = &pMatrixOut->m[0][0];

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
    pMatrixOut->m[0][0] = pMatrixIn->m[0][0] - pVector->vx * element / 2048;
    pMatrixOut->m[1][0] = pMatrixIn->m[1][0] - pVector->vy * element / 2048;
    pMatrixOut->m[2][0] = pMatrixIn->m[2][0] - pVector->vz * element / 2048;

    element = reflected.vy;
    pMatrixOut->m[0][1] = pMatrixIn->m[0][1] - pVector->vx * element / 2048;
    pMatrixOut->m[1][1] = pMatrixIn->m[1][1] - pVector->vy * element / 2048;
    pMatrixOut->m[2][1] = pMatrixIn->m[2][1] - pVector->vz * element / 2048;

    element = reflected.vz;
    pMatrixOut->m[0][2] = pMatrixIn->m[0][2] - pVector->vx * element / 2048;
    pMatrixOut->m[1][2] = pMatrixIn->m[1][2] - pVector->vy * element / 2048;
    pMatrixOut->m[2][2] = pMatrixIn->m[2][2] - pVector->vz * element / 2048;
}
