#include <util/idaTypes.h>
#include <sys/types.h>
#include <libgte.h>

extern ratan2_80094308(DWORD,DWORD);

DWORD GV_VecDir2_80016EF8(SVECTOR* vec)
{
   DWORD ratan = ratan2_80094308(vec->vx,vec->vz);
   return ratan & 0xfff;
}