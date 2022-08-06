#include "linker.h"
#include "unknown.h"

int sd_set_cli_800887EC(int sdCode, int unused)
{
    sd_set_80088CB0(sdCode);
    return 0;
}
