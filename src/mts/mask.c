// I think this object was originally implemented in assembly.
//
// mask.obj in 5thMix's MTS builds have no source filename (as GCC inserts
// a .file directive in the assembly output) and PSY-Q object parsers usually
// complain about an unknown record type or some other bullshit.

void SetExMask()
{
    // unknown psyq-specific debug function ?
    __asm__("break 1030");
}

// Defined in the linker script
extern char _bss_orgend[];

char *mts_get_bss_tail()
{
#ifdef DEV_EXE
    extern char devOverlayCharas[];
    return devOverlayCharas;
#endif

    return _bss_orgend;
}
