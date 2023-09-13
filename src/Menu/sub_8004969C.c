#include "Menu/menuman.h"

radio_table_entry *sub_8004969C(radio_table *pRadioTable, int contactFrequency)
{
    radio_table_entry *entriesIter;
    int                freq;
    int                i;
    int                found_idx;

    found_idx = -1;
    i = 7;
    entriesIter = &pRadioTable->field_0_entries[7];

    for (i = 7; i >= 0; i--, entriesIter--)
    {
        freq = entriesIter->field_0_contactFrequency;
        if (freq == contactFrequency)
        {
            found_idx = i;
            break;
        }

        if (freq == 0)
        {
            found_idx = i;
        }
    }

    if (found_idx < 0)
    {
        printf("RADIO CALL OVER!!\n");
        return NULL;
    }
    else
    {
        return &pRadioTable->field_0_entries[found_idx];
    }
}
