#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

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

int s01a_800E1FCC(SVECTOR *in0, VECTOR *in1, SVECTOR *out, int len)
{
    VECTOR clampv;
    VECTOR diff;
    int    clamped;
    int    coord;
    int    clamp;
    int    mul;

    clamped = 0;
    clampv = *in1;

    coord = clampv.vx;
    if (coord < -0x7FF0)
    {
        clamp = -0x7FF0;
        clampv.vx = clamp;

        mul = (clampv.vx - in0->vx) >> 4;
        coord = (coord - in0->vx) >> 4;

        clampv.vy = ((clampv.vy - in0->vy) * mul) / coord + in0->vy;
        clampv.vz = ((clampv.vz - in0->vz) * mul) / coord + in0->vz;

        clamped = 1;
    }
    else if (coord > 0x7FEF)
    {
        clamp = 0x7FEF;
        clampv.vx = clamp;

        mul = (clampv.vx - in0->vx) >> 4;
        coord = (coord - in0->vx) >> 4;

        clampv.vy = ((clampv.vy - in0->vy) * mul) / coord + in0->vy;
        clampv.vz = ((clampv.vz - in0->vz) * mul) / coord + in0->vz;

        clamped = 1;
    }

    coord = clampv.vy;
    if (coord < -0x7FF0)
    {
        clamp = -0x7FF0;
        clampv.vy = clamp;

        mul = (clampv.vy - in0->vy) >> 4;
        coord = (coord - in0->vy) >> 4;

        clampv.vx = ((clampv.vx - in0->vx) * mul) / coord + in0->vx;
        clampv.vz = ((clampv.vz - in0->vz) * mul) / coord + in0->vz;

        clamped = 1;
    }
    else if (coord > 0x7FEF)
    {
        clamp = 0x7FEF;
        clampv.vy = clamp;

        mul = (clampv.vy - in0->vy) >> 4;
        coord = (coord - in0->vy) >> 4;

        clampv.vx = ((clampv.vx - in0->vx) * mul) / coord + in0->vx;
        clampv.vz = ((clampv.vz - in0->vz) * mul) / coord + in0->vz;

        clamped = 1;
    }

    coord = clampv.vz;
    if (coord < -0x7FF0)
    {
        clamp = -0x7FF0;
        clampv.vz = clamp;

        mul = (clampv.vz - in0->vz) >> 4;
        coord = (coord - in0->vz) >> 4;

        clampv.vy = ((clampv.vy - in0->vy) * mul) / coord + in0->vy;
        clampv.vx = ((clampv.vx - in0->vx) * mul) / coord + in0->vx;

        clamped = 1;
    }
    else if (coord > 0x7FEF)
    {
        clamp = 0x7FEF;
        clampv.vz = clamp;

        mul = (clampv.vz - in0->vz) >> 4;
        coord = (coord - in0->vz) >> 4;

        clampv.vy = ((clampv.vy - in0->vy) * mul) / coord + in0->vy;
        clampv.vx = ((clampv.vx - in0->vx) * mul) / coord + in0->vx;

        clamped = 1;
    }

    if (clamped == 1 || len == -1)
    {
        diff.vx = (clampv.vx - in0->vx) >> 4;
        diff.vy = (clampv.vy - in0->vy) >> 4;
        diff.vz = (clampv.vz - in0->vz) >> 4;

        Square0(&diff, &diff);
        len = SquareRoot0(diff.vx + diff.vy + diff.vz) * 16;
    }

    out->vx = clampv.vx;
    out->vy = clampv.vy;
    out->vz = clampv.vz;

    return len;
}

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
