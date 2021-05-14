#include <util/idaTypes.h>
#include <gvd.h>

extern void GV_FreeMemory_80015FD0(DWORD, void*);

// from leaked original MGS source code

void            GV_Free_80016230( addr )
void            *addr ;
{
        GV_FreeMemory_80015FD0( GV_NORMAL_MEMORY, addr ) ;
}
