#include "linker.h"

extern int gMapsChanged_800ABAAC;
int        SECTION(".sbss") gMapsChanged_800ABAAC;

int Map_light_80030C6C(int a1);

void Map_80030FA4()
{
    if (gMapsChanged_800ABAAC)
    {
        Map_light_80030C6C(gMapsChanged_800ABAAC - 1);
        gMapsChanged_800ABAAC = 0;
    }
}
