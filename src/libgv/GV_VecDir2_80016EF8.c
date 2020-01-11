#include <util/idaTypes.h>
#include <sys/types.h>
#include <libgte.h>

extern int ratan2_80094308(DWORD,DWORD);

DWORD GV_VecDir2_80016EF8(SVECTOR* vec)
{
   return ratan2_80094308(vec->vx,vec->vz) & (ONE-1);
}
