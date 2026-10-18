// vrtitle: VR revision copy of chara/torture/sne_03c.c
// (Snake03c1_800CD914), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "libgcl/libgcl.h"

typedef struct VrProcsWork49E8
{
    /* 0x0 */ char pad[ 0x49E8 ];
    /* 0x49E8 */ int  procs[ 2 ];
} VrProcsWork49E8;

void vrtitle_800D613C( VrProcsWork49E8 *work )
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
        if ( i == 2 )
        {
            break;
        }

        *out++ = GCL_StrToInt( res );
        i++;
    }
}
