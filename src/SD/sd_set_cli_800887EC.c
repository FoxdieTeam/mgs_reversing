#include "linker.h"

void sd_set_80088CB0(int sdCode);

int sd_set_cli_800887EC(int sdCode, int unused)
{
    sd_set_80088CB0(sdCode);
    return 0;
}
