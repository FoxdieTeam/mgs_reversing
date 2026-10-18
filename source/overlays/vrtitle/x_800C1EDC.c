// vrtitle: VR revision copy of onoda/change/safety.c
// (Safety_800C476C), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "onoda/change/safety.h"

#include <stdio.h>
#include <sys/types.h>
#include <libcd.h>
#include <libetc.h>

#include "mts/mts.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"

int  vrtitle_800C1D68( int lba, int timeout );
void vrtitle_800C1E84( void );

void vrtitle_800C1EDC( int timeout )
{
    vrtitle_800C1D68( fs_file_info[FS_FILE_STAGE].pos, timeout );
    vrtitle_800C1E84();
}
