#include "linker.h"

void SD_Set_80088CB0(int sdCode);

int SD_800887EC(int sdCode)
{
    SD_Set_80088CB0(sdCode);
    return 0;
}
