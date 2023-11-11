#include "psyq.h"

// Unsure of type for in
void s01a_800E1E4C(short *in, SVECTOR *out)
{
    short x, z;

    x = -in[1];
    z = -in[7];

    if (x == 0 && z == 0)
    {
        out->vy = 0;
    }
    else
    {
        out->vy = ratan2(x, z) & 0xFFF;
    }

    out->vx = ratan2(in[4], SquareRoot0(x * x + z * z)) & 0xFFF;
    out->vz = 0;
}

// Unsure of type for in
void s01a_800E1F18(short *in, SVECTOR *out)
{
    short x, z;

    x = in[1];
    z = in[7];

    if (x == 0 && z == 0)
    {
        out->vy = 0;
    }
    else
    {
        out->vy = ratan2(x, z) & 0xFFF;
    }

    out->vx = ratan2(SquareRoot0(x * x + z * z), in[4]);
    out->vz = 0;
}

#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_800E1FCC.s")

void s01a_800E2364(MATRIX *mtx, SVECTOR *in, VECTOR *out)
{
    MATRIX trpose;
    VECTOR dist;

    trpose.m[0][0] = mtx->m[0][0];
    trpose.m[0][1] = mtx->m[1][0];
    trpose.m[0][2] = mtx->m[2][0];
    trpose.m[1][0] = mtx->m[0][1];
    trpose.m[1][1] = mtx->m[1][1];
    trpose.m[1][2] = mtx->m[2][1];
    trpose.m[2][0] = mtx->m[0][2];
    trpose.m[2][1] = mtx->m[1][2];
    trpose.m[2][2] = mtx->m[2][2];

    dist.vx = in->vx - mtx->t[0];
    dist.vy = in->vy - mtx->t[1];
    dist.vz = in->vz - mtx->t[2];

    ApplyMatrixLV(&trpose, &dist, out);
}
