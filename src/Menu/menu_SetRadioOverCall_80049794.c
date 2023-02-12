#include "menuman.h"

extern radio_table gRadioOverTable_800BDAF8;

radio_table_entry* sub_80049710(radio_table *pData, int contactFrequency, int radioTableCode);

void menu_SetRadioOverCall_80049794(int contactFrequency, int radioTableCode)
{
    sub_80049710(&gRadioOverTable_800BDAF8, contactFrequency, radioTableCode);
}
