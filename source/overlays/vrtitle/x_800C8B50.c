// vrtitle: VR revision copy of chara/torture/sne_03c.c
// (Snake03c1_800CD914), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "libgcl/libgcl.h"

typedef struct VrProcsWork1A24
{
    /* 0x0 */ char pad[ 0x1A24 ];
    /* 0x1A24 */ int  procs[ 7 ];
} VrProcsWork1A24;

void vrtitle_800C8B50( VrProcsWork1A24 *work )
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
        if ( i == 7 )
        {
            break;
        }

        *out++ = GCL_StrToInt( res );
        i++;
    }
}
