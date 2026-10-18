#include "onoda/change/safety.h"

#include <stdio.h>
#include <sys/types.h>
#include <libcd.h>
#include <libetc.h>

#include "mts/mts.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"

/* in safechk.obj */

void vrtitle_800C1E84( void )
{
    char param;

    param = CdlModeSpeed | CdlModeSize1;
    while ( !CdControl( CdlSetmode, &param, NULL ) );
    mts_wait_vbl(3);
    while ( !CdControl( CdlDemute, NULL, NULL ) );
}
