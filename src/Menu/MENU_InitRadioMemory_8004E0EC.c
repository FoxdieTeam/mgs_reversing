#include "linker.h"
#include "menuMan.h"

typedef struct RadioMemory
{
    short field_0_id;
    char field_2_name[18];
} RadioMemory;

#define RADIO_MEMORY_COUNT 16

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
