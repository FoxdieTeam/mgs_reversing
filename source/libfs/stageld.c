// This module isn't linked into CD-ROM builds, as it's an alternate
// implementation of cdstage.c for hard disk builds (only used in development
// and the Win32 port by Digital Dialect).
//
// It's known to contain the following public functions:
// -------------------------------------------------------------
// FS_LoadStageRequest
// FS_LoadStageSync
// FS_LoadStageComplete
//

#if 0
#include "libfs.h"
#include "datacnf.h"

void *FS_LoadStageRequest( const char *dirname )
{
    // todo: implement
    return NULL;
}

int FS_LoadStageSync( void *info )
{
    // todo: implement
    return 0;
}

void FS_LoadStageComplete( void *info )
{
    // todo: implement
}

#endif
