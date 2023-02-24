#include "Menu/menuman.h"

extern RadioMemory gRadioMemory_800BDB38[RADIO_MEMORY_COUNT];

extern int dword_800AB770;
int        dword_800AB770;

void menu_radio_codec_helper_helper_8004E198(int toFind)
{
    RadioMemory *contact;

    contact = menu_radio_table_find_8004D380(toFind);
    if (contact)
    {
        dword_800AB770 = contact - gRadioMemory_800BDB38;
    }
}
