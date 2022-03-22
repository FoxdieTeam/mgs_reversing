#include "linker.h"
#include <sys/types.h>
#include <libgte.h>

extern MATRIX DG_LightMatrix_8009D384;

void VectorNormal_80092838(VECTOR* v0, VECTOR* v1);

void DG_SetMainLightDir_80019FF8(int x, int y, int z)
{
    VECTOR in;
    VECTOR out;

    in.vx = x;
    in.vy = y;
    in.vz = z;

    VectorNormal_80092838(&in, &out);
    DG_LightMatrix_8009D384.m[0][0] = out.vx;
    DG_LightMatrix_8009D384.m[0][1] = out.vy;
    DG_LightMatrix_8009D384.m[0][2] = out.vz;
}
