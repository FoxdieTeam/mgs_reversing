#include "linker.h"
#include "Menu/menuMan.h"

RadioMemory *menu_radio_table_find_8004D380(int frequency)
{
    RadioMemory *contact;
    int         i;

    contact = &gRadioMemory_800BDB38[0];
    for (i = 0; i < RADIO_MEMORY_COUNT; i++)
    {
        if (contact->frequency == frequency)
        {
            return contact;
        }
        contact++;
    }
    return 0;
}

RadioMemory *menu_radio_table_next_free_8004D3B8(void)
{
    // Try to find a free entry
    return menu_radio_table_find_8004D380(0);
}
