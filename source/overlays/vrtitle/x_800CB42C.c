// vrtitle: VR revision copy of chara/torture/sne_03c.c
// (Snake03c1_800CD914), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "libgcl/libgcl.h"

typedef struct VrProcsWork64
{
    /* 0x0 */ char pad[ 0x64 ];
    /* 0x64 */ int  procs[ 1 ];
} VrProcsWork64;

void vrtitle_800CB42C( VrProcsWork64 *work )
{
    int   i;
    int  *out;
    char *res;

    if ( !GCL_GetOption( 'p' ) )
    {
        return;
    }

    i = 0;
    out = work->procs;
    while ( ( res = GCL_NextStr() ) )
    {
        if ( i == 1 )
        {
            break;
        }

        *out++ = GCL_StrToInt( res );
        i++;
    }
}
