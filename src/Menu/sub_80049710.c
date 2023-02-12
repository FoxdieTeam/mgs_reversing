#include "radio.h"

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