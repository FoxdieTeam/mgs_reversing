#include "libdg.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

void DG_MatrixRot( MATRIX *mat, SVECTOR *svec )
{
    int iVar1;
    int iVar2;
    int iVar3;

    iVar1 = mat->m[0][2];
    iVar2 = SquareRoot0(0x1000000 - iVar1 * iVar1);

    if (iVar2 < 0x80)
    {
        iVar3 = 0x400;

        if (iVar1 <= 0)
        {
            iVar3 = 3072;
        }

        svec->vy = iVar3;
        svec->vx = ratan2(mat->m[1][2], mat->m[1][1]);
        svec->vz = 0;
    }
    else
    {
        svec->vy = ratan2(iVar1, iVar2) & 0xfff;
        svec->vx = ratan2((-mat->m[1][2] << 12) / iVar2, (mat->m[2][2] << 12) / iVar2) & 0xfff;
        svec->vz = ratan2((-mat->m[0][1] << 12) / iVar2, (mat->m[0][0] << 12) / iVar2) & 0xfff;
    }
}

void DG_MatrixRotYXZ( MATRIX *mat, SVECTOR *svec )
{
    int iVar1;
    int iVar2;
    int iVar3;

    iVar1 = -mat->m[1][2];
    iVar2 = SquareRoot0(0x1000000 - iVar1 * iVar1);

    if (iVar2 < 0x80)
    {
        iVar3 = 0x400;

        if (iVar1 <= 0)
        {
            iVar3 = 3072;
        }

        svec->vx = iVar3;
        svec->vy = ratan2(-mat->m[2][0], mat->m[0][0]);
        svec->vz = 0;
    }
    else
    {
        svec->vx = ratan2(iVar1, iVar2) & 0xfff;
        svec->vy = ratan2((mat->m[0][2] << 12) / iVar2, (mat->m[2][2] << 12) / iVar2) & 0xfff;
        svec->vz = ratan2((mat->m[1][0] << 12) / iVar2, (mat->m[1][1] << 12) / iVar2) & 0xfff;
    }

    if (abs(svec->vz) > 0x400)
    {
        svec->vz = (svec->vz + 0x800) & 0xfff;
        svec->vy = (svec->vy + 0x800) & 0xfff;
        svec->vx = (0x800 - svec->vx) & 0xfff;
    }
}

void DG_MatrixRotZYX( MATRIX *mat, SVECTOR *svec )
{
    int iVar1;
    int iVar2;
    int iVar3;

    iVar1 = -mat->m[2][0];
    iVar2 = SquareRoot0(0x1000000 - iVar1 * iVar1);

    if (iVar2 < 0x80)
    {
        iVar3 = 0x400;

        if (iVar1 <= 0)
        {
            iVar3 = 3072;
        }

        svec->vy = iVar3;
        svec->vx = ratan2(-mat->m[1][2], mat->m[1][1]);
        svec->vz = 0;
    }
    else
    {
        svec->vy = ratan2(iVar1, iVar2) & 0xfff;
        svec->vx = ratan2((mat->m[2][1] << 12) / iVar2, (mat->m[2][2] << 12) / iVar2) & 0xfff;
        svec->vz = ratan2((mat->m[1][0] << 12) / iVar2, (mat->m[0][0] << 12) / iVar2) & 0xfff;
    }
}

void DG_TransposeMatrix( MATRIX *in, MATRIX *out )
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

void DG_ShadowMatrix( MATRIX *out, MATRIX *in, int param_3 )
{
    int x, y, z;
    short *pElement;
    int count;
    int iVar1;
    int iVar2;
    int iVar3;

    x = in->m[0][0] + in->m[1][0] + in->m[2][0];
    y = in->m[0][1] + in->m[1][1] + in->m[2][1];
    z = in->m[0][2] + in->m[1][2] + in->m[2][2];

    if (y < 0)
    {
        pElement = &out->m[0][0];

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
        out->t[0] -= iVar2 >> 12;

        if (iVar3 < 0)
        {
            iVar3 += 0xfff;
        }

        out->t[2] -= iVar3 >> 12;
    }

    out->t[1] -= param_3;

    out->m[1][0] = 0;
    out->m[1][1] = 0;
    out->m[1][2] = 0;
}

void DG_ReflectVector( SVECTOR *in, SVECTOR *translation, SVECTOR *out )
{
    MATRIX mat;

    mat.m[0][0] = in->vx;
    mat.m[0][1] = mat.m[1][0] = in->vy;
    mat.m[0][2] = mat.m[2][0] = in->vz;

    mat.t[0] = translation->vx;
    mat.t[1] = translation->vy;
    mat.t[2] = translation->vz;

    gte_SetRotMatrix(&mat);
    gte_SetTransMatrix(&mat);
    gte_ldsv(translation);
    gte_rtir();
    gte_stsv(out);

    out->vz = 0;
    out->vy = 0;
    out->vx *= -2;

    gte_ldv0(out);
    gte_rt();
    gte_stsv(out);
}

void DG_ReflectMatrix( SVECTOR *svec, MATRIX *in, MATRIX *out )
{
    MATRIX transpose;
    SVECTOR reflected;
    int element;

    DG_TransposeMatrix(in, &transpose);
    gte_SetRotMatrix(&transpose);
    gte_ldsv(svec);
    gte_rtir();
    gte_stsv(&reflected);

    element = reflected.vx;
    out->m[0][0] = in->m[0][0] - svec->vx * element / 2048;
    out->m[1][0] = in->m[1][0] - svec->vy * element / 2048;
    out->m[2][0] = in->m[2][0] - svec->vz * element / 2048;

    element = reflected.vy;
    out->m[0][1] = in->m[0][1] - svec->vx * element / 2048;
    out->m[1][1] = in->m[1][1] - svec->vy * element / 2048;
    out->m[2][1] = in->m[2][1] - svec->vz * element / 2048;

    element = reflected.vz;
    out->m[0][2] = in->m[0][2] - svec->vx * element / 2048;
    out->m[1][2] = in->m[1][2] - svec->vy * element / 2048;
    out->m[2][2] = in->m[2][2] - svec->vz * element / 2048;
}
