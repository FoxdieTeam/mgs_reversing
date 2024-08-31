#include "libgv.h"
#include "psyq.h"

void GV_AddVec3(SVECTOR *vec1, SVECTOR *vec2, SVECTOR *dst)
{
    dst->vx = vec1->vx + vec2->vx;
    dst->vy = vec1->vy + vec2->vy;
    dst->vz = vec1->vz + vec2->vz;
}

void GV_SubVec3(SVECTOR *vec1, SVECTOR *vec2, SVECTOR *dst)
{
    dst->vx = vec1->vx - vec2->vx;
    dst->vy = vec1->vy - vec2->vy;
    dst->vz = vec1->vz - vec2->vz;
}

int GV_VecLen3(SVECTOR *vec)
{
    int    length;
    VECTOR vec2;

    vec2.vx = vec->vx;
    vec2.vy = vec->vy;
    vec2.vz = vec->vz;
    Square0(&vec2, &vec2);
    length = SquareRoot0(vec2.vx + vec2.vy + vec2.vz);
    return length;
}

void GV_LenVec3(SVECTOR *in, SVECTOR *out, int denom, int num)
{
    int ratio;

    ratio = num * 4096;

    if (denom == 0)
    {
        denom = 1;
    }

    ratio /= denom;

    out->vx = in->vx * ratio / 4096;
    out->vy = in->vy * ratio / 4096;
    out->vz = in->vz * ratio / 4096;
}

int GV_DiffVec3(SVECTOR *vec1, SVECTOR *vec2)
{
    VECTOR diff;

    diff.vx = vec1->vx - vec2->vx;
    diff.vy = vec1->vy - vec2->vy;
    diff.vz = vec1->vz - vec2->vz;

    Square0(&diff, &diff);
    return SquareRoot0(diff.vx + diff.vy + diff.vz);
}

int GV_VecDir2(SVECTOR *vec)
{
    return ratan2(vec->vx, vec->vz) & (4096 - 1);
}

void GV_DirVec2(int angle, int radius, SVECTOR *out)
{
    out->vx = radius * rsin(angle) / 4096;
    out->vy = 0;
    out->vz = radius * rcos(angle) / 4096;
}

void GV_DirVec3(SVECTOR *angle, int length, SVECTOR *out)
{
    MATRIX matrix;

    RotMatrixYXZ(angle, &matrix);
    out->vx = length * matrix.m[0][2] / 4096;
    out->vy = length * matrix.m[1][2] / 4096;
    out->vz = length * matrix.m[2][2] / 4096;
}

unsigned int GV_DiffDirU(int from, int to)
{
    return (to - from) & 0xfff;
}

int GV_DiffDirS(int from, int to)
{
    int result = (to - from) & (4096 - 1);
    if (result > (4096 / 2))
    {
        result -= 4096;
    }
    return result;
}

int GV_DiffDirAbs(int from, int to)
{
    int diff = (to - from) & 4095;

    if (diff <= 2048)
    {
        return diff;
    }
    else
    {
        return 4096 - diff;
    }
}

int GV_RandU(unsigned int input)
{
    return (input - 1) & rand();
}

int GV_RandS(int input)
{
    return (((input * 2) - 1) & rand()) - input;
}
