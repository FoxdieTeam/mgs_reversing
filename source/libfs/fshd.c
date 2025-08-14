// This module isn't linked into CD-ROM builds, as it's an alternate
// implementation of fscd.c for hard disk builds (only used in development
// and the Win32 port by Digital Dialect).
//
// I'm assuming conditional compilation in select.c determines whether
// FS_CDInit or FS_HDInit is called by FS_StartDaemon and thus the linker
// discards either fshd.obj or fscd.obj, respectively.
//
// It's known to contain the following public functions:
// -------------------------------------------------------------
// FS_LoadFileRequest
// FS_LoadFileSync
// FS_ResetCdFilePosition
// FS_HDInit
//
// NOTE: These labels were recovered from a memleak'd linker map fragment.
//       Symbols were listed by address order, which is reflected above.
//

#if 0
#include "file.cnf"

void FS_LoadFileRequest( int fileno, int offset, int size, void *buffer )
{
    // todo: implement
}

int FS_LoadFileSync( void )
{
    // todo: implement
    return 0;
}

int FS_ResetCdFilePosition( void *ptr )
{
    // todo: implement
    return -1;
}

void FS_HDInit( void )
{
    // todo: implement
}
#endif
