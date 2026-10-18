// vrsave: VR revision copy of overlays/camera/unknown/camera.c
// (camera_800C5308), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include <stdio.h>

#include "libgv/libgv.h"
#include "mts/mts.h"
#include "mts/taskid.h"

extern int   vrsave_dword_800D1BE8;
extern void *vrsave_dword_800D1BF8;
extern char  vrsave_dword_800D1318[]; // "NO MEMORY FOR STACK\n"
extern char  vrsave_dword_800D1330[]; // "memcard_task_id = %d\n"

void vrsave_800C5F38( void );

void vrsave_800C661C( int arg0 )
{
    void *stack;

    stack = GV_AllocMemory( GV_NORMAL_MEMORY, 2048 );
    vrsave_dword_800D1BF8 = stack;

    if ( stack == NULL )
    {
        printf( vrsave_dword_800D1318 );
    }

    vrsave_dword_800D1BE8 = arg0;
    printf( vrsave_dword_800D1330, MTSID_MEMORY_CARD );
    mts_start_task( MTSID_MEMORY_CARD, vrsave_800C5F38, vrsave_dword_800D1BF8 + 2048, 2048 );
}
