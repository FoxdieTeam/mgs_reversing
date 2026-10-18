// vrtitle: VR revision copy of onoda/change/safety.c
// (Safety_800C45F8), transplanted from the main-tree twin; offsets/constants adapted to the VR.
#include "onoda/change/safety.h"

#include <stdio.h>
#include <sys/types.h>
#include <libcd.h>
#include <libetc.h>

#include "mts/mts.h"
#include "libfs/libfs.h"
#include "libgcl/libgcl.h"

/* in safechk.obj */
extern int vrtitle_800C1F60( int, int, int );

extern char vrtitle_dword_800D8A44[]; // "SafeCheckStart\n"
extern char vrtitle_dword_800D8A54[]; // "TRY\n"
extern char vrtitle_dword_800D8A5C[]; // "TIMEOUT\n"
extern char vrtitle_dword_800D8A68[]; // "TRY END\n"
extern char vrtitle_dword_800D8A74[]; // "OPEN\n"
extern char vrtitle_dword_800D8A7C[]; // "SafeCheckEND\n"

int vrtitle_800C1D68( int lba, int timeout )
{
    CdlLOC loc;
    char   result[8];
    int    start;
    int    open;

    printf( vrtitle_dword_800D8A44 );
    CdIntToPos( lba, &loc );

    while ( 1 )
    {
        printf( vrtitle_dword_800D8A54 );
        start = VSync( -1 );

        while ( 1 )
        {
            if ( vrtitle_800C1F60( loc.minute, loc.second, loc.sector ) >= 0 )
            {
                break;
            }

            if ( timeout > 0 && ( VSync( -1 ) - start ) > timeout )
            {
                printf( vrtitle_dword_800D8A5C );
                break;
            }
        }

        CdControlB( CdlNop, NULL, result );
        CdControlB( CdlNop, NULL, result );

        open = result[0] & ( CdlStatShellOpen | CdlStatError );
        if ( !open )
        {
            printf( vrtitle_dword_800D8A68 );
            break;
        }

        printf( vrtitle_dword_800D8A74 );
    }

    printf( vrtitle_dword_800D8A7C );
    return 1;
}
