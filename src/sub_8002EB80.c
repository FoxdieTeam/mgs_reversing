#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include "unknown.h"

void sub_8002EB80(SVECTOR *vec_1, SVECTOR *vec_2)
{
    int iVar1;

    iVar1 = sub_80026440((int)vec_1->vx, (int)vec_2->vx, 500);
    vec_1->vx = (short)iVar1;
    iVar1 = sub_80026440((int)vec_1->vz, (int)vec_2->vz, 500);
    vec_1->vz = (short)iVar1;
    iVar1 = sub_80026440((int)vec_1->vy, (int)vec_2->vy, 0x96);
    vec_1->vy = (short)iVar1;
}
