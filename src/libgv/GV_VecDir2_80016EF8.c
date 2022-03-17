#include <util/idaTypes.h>
#include <sys/types.h>
#include <libgte.h>

extern int ratan2_80094308(DWORD,DWORD);
extern int rsin_80092508(int a1);

DWORD GV_VecDir2_80016EF8(SVECTOR* vec)
{
   return ratan2_80094308(vec->vx,vec->vz) & (ONE-1);
}

void GV_DirVec2_80016F24(int a1, int a2, SVECTOR *a3)
{
    a3->vx = a2 * rsin_80092508(a1) / ONE;
    a3->vy = 0;
    a3->vz = a2 * rcos_800925D8(a1) / ONE;
}
