#include "linker.h"
#include "menuMan.h"

RadioMemory SECTION(".gRadioMemory_800BDB38") gRadioMemory_800BDB38[RADIO_MEMORY_COUNT] = {};

void MENU_InitRadioMemory_8004E0EC(void)
{
    RadioMemory* pIter = &gRadioMemory_800BDB38[0];
    int i = RADIO_MEMORY_COUNT-1;
    while (i >= 0)
    {
        pIter->field_0_id = 0;
        pIter++;
        i--;
    }
}
