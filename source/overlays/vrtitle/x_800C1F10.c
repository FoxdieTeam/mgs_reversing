#include "onoda/change/safety.h"

#include <stdio.h>
#include <sys/types.h>
#include <libcd.h>
#include <libetc.h>

#include "mts/mts.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"

/* in safechk.obj */

int vrtitle_800C1F10( void )
{
    int timeout;

    timeout = 0;
    if ( GCL_GetOption( 't' ) )
    {
        timeout = GCL_GetNextInt() * 60;
    }

    vrtitle_800C1EDC( timeout );
    return 1;
}
