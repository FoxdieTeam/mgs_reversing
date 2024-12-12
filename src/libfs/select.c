#include "libfs.h"

#include <stdio.h>
#include <sys/types.h>
#include <libapi.h>
#include <libcd.h>

#include "common.h"
#include "libsio/isio.h"

void FS_StartDaemon( void )
{
    SetMem(2);          // Set effective memory to 2MB (DTL-H2X00 has 8MB)
    FS_CDInit();        // Init CD read system
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
