#include "common.h"
#include "mts/mts.h"
#include "libsio/isio.h"
#include "psyq.h"
#include "libfs.h"

void FS_StartDaemon( void )
{
    // CPU exception if >= 2MB ram range is used
    // since retail consoles have 2MB and dev have 8MB.
    SetMem(2);
    FS_CDInit();        // init cd and the likes
    sio_output_stop();
}

void FS_CdStageProgBinFix( void )
{
    /* do nothing */
}

CdlCB CdReadCallback( CdlCB func )
{
    return 0;
}

CdlCB CdReadMode( CdlCB func )
{
    /* do nothing */
}

//DslCB DsReadyCallback( DslCB func );
void DsReadyCallback( void (*func)(u_char, u_char*) )
{
    printf( "DsReadyCallback %x\n", func );
}

//void ( *DsDataCallback( void ( *func )() ) );
void DsDataCallback( void (*func)(u_char, u_char*) )
{
    printf( "DsDataCallback %x\n", func );
}

int PCinit(void)
{
    return -1;
}

int PCopen(const char *name, int flags, int perms)
{
    return 0;
}

int PCread(int fd, char *buff, int len)
{
    return 0;
}

int PCclose(int fd)
{
    return 0;
}
