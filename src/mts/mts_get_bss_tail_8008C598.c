#include "linker.h"

// Each overlay defines this symbol
extern char OverlayCharas[];

unsigned char *mts_get_bss_tail_8008C598()
{
    return &OverlayCharas[0];
}
