// This module isn't linked into CD-ROM builds, as it's an alternate
// implementation of fscd.c for hard disk builds (only used in development
// and the Win32 port by Digital Dialect).
//
// I'm assuming conditional compilation in select.c determines whether
// FS_CDInit or FS_HDInit is called by FS_StartDaemon and thus the linker
// discards either fshd.obj or fscd.obj, respectively.
//
// It's known the contain the following public functions:
// -------------------------------------------------------------
// FS_LoadFileRequest
// FS_LoadFileSync
// FS_ResetCdFilePosition
// FS_HDInit
//
