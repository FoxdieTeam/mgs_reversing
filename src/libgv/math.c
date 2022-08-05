#include "libgv.h"
#include "psyq.h"

MATRIX *RotMatrixYXZ_80093798(SVECTOR *r, MATRIX *m);

void GV_AddVec3_80016D00(SVECTOR* vec1, SVECTOR* vec2, SVECTOR* dst)
{
    dst->vx = vec1->vx + vec2->vx;
    dst->vy = vec1->vy + vec2->vy;
    dst->vz = vec1->vz + vec2->vz;
}

void GV_SubVec3_80016D40(SVECTOR* vec1, SVECTOR* vec2, SVECTOR* dst)
{
    dst->vx = vec1->vx - vec2->vx;
    dst->vy = vec1->vy - vec2->vy;
    dst->vz = vec1->vz - vec2->vz;
}

int GV_VecLen3_80016D80(SVECTOR* vec)
{
    int length;
    VECTOR vec2;

    vec2.vx = vec->vx;
    vec2.vy = vec->vy;
    vec2.vz = vec->vz;
    Square0_80093340(&vec2,&vec2);
    length = SquareRoot0_80092708(vec2.vx + vec2.vy + vec2.vz);
    return length;
}

void GV_LenVec3_80016DDC(SVECTOR *pSrcVec, SVECTOR *pDstVec, int param_3, int param_4)
{
    param_4 = param_4 * 4096;
    if (param_3 == 0)
    {
        param_3 = 1;
    }
    param_4 /= param_3;

    pDstVec->vx = pSrcVec->vx * param_4 / 4096;
    pDstVec->vy = pSrcVec->vy * param_4 / 4096;
    pDstVec->vz = pSrcVec->vz * param_4 / 4096;
}

int GV_DiffVec3_80016E84(SVECTOR* vec1, SVECTOR* vec2)
{
    VECTOR diff;
    diff.vx = vec1->vx - vec2->vx;
    diff.vy = vec1->vy - vec2->vy;
    diff.vz = vec1->vz - vec2->vz;
    
    Square0_80093340(&diff, &diff);
    return SquareRoot0_80092708(diff.vx + diff.vy + diff.vz);
}



int GV_VecDir2_80016EF8(SVECTOR* vec)
{
   return ratan2_80094308(vec->vx,vec->vz) & (4096-1);
}

void GV_DirVec2_80016F24(int a1, int a2, SVECTOR *a3)
{
    a3->vx = a2 * rsin_80092508(a1) / 4096;
    a3->vy = 0;
    a3->vz = a2 * rcos_800925D8(a1) / 4096;
}

void GV_DirVec3_80016FA0(SVECTOR *pSrcVec, int param_2, SVECTOR *pDstVec)
{
    MATRIX matrix;

    RotMatrixYXZ_80093798(pSrcVec, &matrix);
    pDstVec->vx = param_2 * matrix.m[0][2] / 4096;
    pDstVec->vy = param_2 * matrix.m[1][2] / 4096;
    pDstVec->vz = param_2 * matrix.m[2][2] / 4096;
}

unsigned int GV_DiffDirU_80017040(int param_1, int param_2)
{
    return (param_2 - param_1) & 0xfff;
}

int GV_DiffDirS_8001704C(int param_1, int param_2)
{
    int uVar1 = (param_2 - param_1) & (4096 - 1);
    if (uVar1 > (4096 / 2))
    {
        uVar1 -= 4096;
    }
    return uVar1;
}

int GV_DiffDirAbs_8001706C(int a1, int a2)
{
    int v2 = (a2 - a1) & 4095;

    if ( v2 < 2049 )
    {
        return v2;
    }
    else
    {
        return 4096 - v2;
    }
}

unsigned int GV_RandU_80017090(unsigned int input)
{
    return (input - 1) & rand_8008E6B8();
}

int GV_RandS_800170BC(int input)
{
    return (((input * 2) - 1) & rand_8008E6B8()) - input;
}
