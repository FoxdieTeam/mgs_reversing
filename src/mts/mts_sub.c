#include <libsn.h>
#include "linker.h"
#include "psyq.h"

// Each overlay defines this symbol
//extern char OverlayCharas[];

// BSS
extern int dword_800A3DCC;
int dword_800A3DCC = 0;

void mts_reset_graph(void)
{
    if (dword_800A3DCC == 0)
    {
        ResetGraph(0);
        SetGraphDebug(0);
        InitGeom();
        dword_800A3DCC = 1;
    }
    else
    {
        ResetGraph(1);
    }
}

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