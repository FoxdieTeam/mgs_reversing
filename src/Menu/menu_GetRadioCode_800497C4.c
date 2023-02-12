#include "menuman.h"
#include "radio.h"

extern radio_table gRadioOverTable_800BDAF8;
extern radio_table gRadioBaseTable_800BDAB8;

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
