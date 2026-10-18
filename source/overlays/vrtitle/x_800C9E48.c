#include "game/game.h"
#include "libgcl/libgcl.h"

void vrtitle_800C9E48( char *work )
{
    GCL_ExecProc( *(int *)( work + 0x64 ), NULL );
    GV_DestroyActor( work );
}
