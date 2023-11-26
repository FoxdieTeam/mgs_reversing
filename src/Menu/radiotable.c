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

void menu_ClearRadioTable_8004967C()
{
    menu_InitRadioTable_80049644();
}

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

radio_table_entry* sub_80049710(radio_table *pData, int contactFrequency, int radioTableCode)
{
    radio_table_entry *pFound; // $v0

    pFound = sub_8004969C(pData, contactFrequency);
    if ( pFound )
    {
        if ( radioTableCode >= 0 )
        {
            pFound->field_0_contactFrequency = contactFrequency;
            pFound->field_4_radioTableCode = radioTableCode;

        }
        else
        {
            pFound->field_0_contactFrequency = 0;
            pFound->field_4_radioTableCode = 0;

        }
    }
    return pFound;
}

void menu_SetRadioBaseCall_80049764(int contactFrequency, int radioTableCode)
{
    sub_80049710(&gRadioBaseTable_800BDAB8, contactFrequency, radioTableCode);
}

void menu_SetRadioOverCall_80049794(int contactFrequency, int radioTableCode)
{
    sub_80049710(&gRadioOverTable_800BDAF8, contactFrequency, radioTableCode);
}

int menu_GetRadioCode_800497C4(int contactFrequency)
{
    radio_table_entry *pFound; // $v0

    pFound = sub_8004969C(&gRadioOverTable_800BDAF8, contactFrequency);
    if ( pFound )
    {
        if ( pFound->field_0_contactFrequency == contactFrequency )
        {
            return pFound->field_4_radioTableCode;
        }
    }
    
    pFound = sub_8004969C(&gRadioBaseTable_800BDAB8, contactFrequency);
    if ( pFound )
    {
        if ( pFound->field_0_contactFrequency == contactFrequency )
        {
            return pFound->field_4_radioTableCode;
        }
    }
    return -1;
}
