#include "linker.h"

// Each overlay defines this symbol
extern char OverlayCharas[];

unsigned char *mts_get_program_bottom_8008C598()
{
    return &OverlayCharas[0];
}
