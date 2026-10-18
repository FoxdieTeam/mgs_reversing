// vrsave: VR revision copy of menu/datasave.c
// (menu_radio_do_file_mode_helper12_helper_8004B8FC area), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include <stdio.h>

#include "libgv/libgv.h"
#include "overlays/vrsave/vrsave.h"

extern char vrsave_dword_800D13C4[]; // "NO MEMORY FOR INFO\n"

void vrsave_800C7E48( VR_SELECT_INFO *info )
{
    if ( info != NULL )
    {
        GV_FreeMemory( GV_NORMAL_MEMORY, info );
    }
}

void vrsave_800C7E70( VR_SELECT_INFO **info, int num )
{
    if ( *info != NULL )
    {
        return;
    }

    *info = GV_AllocMemory( GV_NORMAL_MEMORY, sizeof( VR_SELECT_INFO ) + num * sizeof( VR_MENU_CURPOS ) );
    if ( *info == NULL )
    {
        printf( vrsave_dword_800D13C4 );
    }
}
