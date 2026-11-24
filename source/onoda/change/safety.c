#include "safety.h"

#include <stdio.h>
#include <sys/types.h>
#include <libcd.h>
#include <libetc.h>

#include "mts/mts.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"

/* in safechk.obj */
extern int SafetyCheck( int, int, int );

int SafeCheck( int lba, int timeout )
{
    CdlLOC loc;
    char result[8];
    int start;

    printf( "SafeCheckStart\n" );
    CdIntToPos( lba, &loc );

    while ( 1 )
    {
        printf( "TRY\n" );
        start = VSync( -1 );

        while ( 1 )
        {
            if ( SafetyCheck( loc.minute, loc.second, loc.sector ) >= 0 )
            {
                break;
            }

            if ( timeout > 0 && ( VSync( -1 ) - start ) > timeout )
            {
                printf( "TIMEOUT\n" );
                break;
            }
        }

        CdControlB( CdlNop, NULL, result );
        CdControlB( CdlNop, NULL, result );

        if ( !(result[ 0 ] & ( CdlStatShellOpen | CdlStatError )) )
        {
            printf( "TRY END\n" );
            break;
        }

        printf( "OPEN\n" );
    }

    printf( "SafeCheckEND\n" );
    return 1;
}

void SafetyReset( void )
{
    char param;

    param = CdlModeSpeed | CdlModeSize1;
    while ( !CdControl( CdlSetmode, &param, NULL ) );
    mts_wait_vbl(3);
    while ( !CdControl( CdlDemute, NULL, NULL ) );
}

static void CheckStage( int timeout )
{
    SafeCheck( fs_file_info[ FS_FILE_STAGE ].pos, timeout );
    SafetyReset();
}

int NewSafetyCheck( void )
{
    int timeout;

    timeout = 0;
    if ( GCL_GetOption( 't' ) )
    {
        timeout = GCL_GetNextInt() * 60;
    }

    CheckStage( timeout );
    return 1;
}
