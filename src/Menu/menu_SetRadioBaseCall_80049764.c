#include "menuman.h"

extern radio_table gRadioBaseTable_800BDAB8;

radio_table_entry* sub_80049710(radio_table *pData, int contactFrequency, int radioTableCode);

void menu_SetRadioBaseCall_80049764(int contactFrequency, int radioTableCode)
{
    sub_80049710(&gRadioBaseTable_800BDAB8, contactFrequency, radioTableCode);
}
