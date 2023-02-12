#include "menuman.h"

extern radio_table gRadioOverTable_800BDAF8;
extern radio_table gRadioBaseTable_800BDAB8;

void menu_InitRadioTable_80049644()
{
    int idx; // $a1
    for (idx = 0; idx < 8; idx++)
    {
        gRadioBaseTable_800BDAB8.field_0_entries[idx].field_0_contactFrequency = 0;
        gRadioOverTable_800BDAF8.field_0_entries[idx].field_0_contactFrequency = 0;
    }
}
