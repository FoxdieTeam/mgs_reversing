#include <sys/types.h>
#include <libgte.h>

extern int  sub_80026440(int param_1, int param_2, int param_3);

void sub_8002EB80(SVECTOR *vec_1, SVECTOR *vec_2)
{
    int iVar1;
    
    iVar1 = sub_80026440((int)vec_1->vx,(int)vec_2->vx,500);
    vec_1->vx = (short)iVar1;
    iVar1 = sub_80026440((int)vec_1->vz,(int)vec_2->vz,500);
    vec_1->vz = (short)iVar1;
    iVar1 = sub_80026440((int)vec_1->vy,(int)vec_2->vy,0x96);
    vec_1->vy = (short)iVar1;
}


