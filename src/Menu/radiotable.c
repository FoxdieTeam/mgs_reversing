#include <stdio.h>
#include "common.h"
#include "menuman.h"

extern radio_table gRadioOverTable_800BDAF8;
extern radio_table gRadioBaseTable_800BDAB8;

void MENU_InitRadioTable(void)
{
    int i;
    for (i = 0; i < 8; i++)
    {
        gRadioBaseTable_800BDAB8.field_0_entries[i].field_0_contactFrequency = 0;
        gRadioOverTable_800BDAF8.field_0_entries[i].field_0_contactFrequency = 0;
    }
}

void MENU_ClearRadioTable(void)
{
    MENU_InitRadioTable();
}

STATIC radio_table_entry *sub_8004969C(radio_table *pRadioTable, int contactFrequency)
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

STATIC radio_table_entry* sub_80049710(radio_table *pData, int contactFrequency, int radioTableCode)
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

void MENU_SetRadioBaseCall(int contactFrequency, int radioTableCode)
{
    sub_80049710(&gRadioBaseTable_800BDAB8, contactFrequency, radioTableCode);
}

void MENU_SetRadioOverCall(int contactFrequency, int radioTableCode)
{
    sub_80049710(&gRadioOverTable_800BDAF8, contactFrequency, radioTableCode);
}

int MENU_GetRadioCode(int contactFrequency)
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
