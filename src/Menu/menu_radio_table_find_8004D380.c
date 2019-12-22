#include "linker.h"
#include "menuMan.h"

RadioMemory *menu_radio_table_find_8004D380(int toFind)
{
    RadioMemory *pIter = gRadioMemory_800BDB38;
    int i;
    for (i = 0; i < RADIO_MEMORY_COUNT; i++)
    {
        if (pIter->field_0_id == toFind)
        {
            return pIter;
        }
        pIter++;
    }
    return 0;
}

RadioMemory *menu_radio_table_next_free_8004D3B8(void)
{
    // Try to find a free entry
    return menu_radio_table_find_8004D380(0);
}

// sub_8004E110 set or clear named var
// sub_80047768 menu_gcl_set_radio_memory ??

