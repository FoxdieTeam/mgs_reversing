#include "libgv.h"
#include <stdio.h>

const char *GV_DebugMes = "none";

void GV_Assert( char *file, int line )
{
    printf( "Assertion failed: %s, line %d\n", file, line );

#ifdef DEV_EXE
    HANGUP();
#endif
}

void GV_Warning( char *format, int id )
{
    printf( format, id );
}

void GV_Error( char *format, int id )
{
    GV_Warning( format, id );
}
