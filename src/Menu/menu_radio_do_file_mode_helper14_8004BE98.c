#include "Menu/radio.h"
#include "psyq.h"

extern int dword_800AB6F0;
int        dword_800AB6F0;

extern int dword_800AB700;
int        dword_800AB700;

extern int   aNoCard[]; // CAUTION: does not match with "extern char aNoCard[]"
extern char *gMemoryCardNames_8009EC00[];

void menu_radio_do_file_mode_helper14_8004BE98(Actor_MenuMan *pActor, char *param_2, Stru_800ABB74 *pStru)
{
    Stru_800ABB74_child *pStruChild;
    int                  idx, idx_copy;
    int                  memoryCardNo;
    int                  bit;
    int                  minusOne;

    pStruChild = pStru->field_24;
    idx = -1;
    for (memoryCardNo = 0; memoryCardNo < 2; memoryCardNo++)
    {
        bit = 1;
        bit <<= memoryCardNo;

        if (dword_800AB700 & bit)
        {
            strcpy(pStruChild->field_0_name, gMemoryCardNames_8009EC00[memoryCardNo]);
            pStruChild->field_20 = memoryCardNo;
            if (memoryCardNo == dword_800AB6F0)
            {
                idx = pStruChild - pStru->field_24;
            }
            pStruChild++;
        }
    }

    idx_copy = idx;
    if (pStruChild == pStru->field_24)
    {
        memcpy(&pStru->field_24[0].field_0_name, aNoCard, 8);
        pStruChild->field_20 = 2;
        pStruChild = &pStru->field_24[1];
    }

    pStru->field_1C_kcb = pActor->field_214_font;
    pStru->field_8 = pStruChild - pStru->field_24;

    if (idx_copy < 0)
    {
        idx_copy = 0;
    }

    minusOne = -1;
    do {} while (0);

    pStru->field_0_xpos = 160;
    pStru->field_2_ypos = 100;
    pStru->field_4 = idx_copy;
    pStru->field_6 = 0;
    pStru->field_20 = param_2;
    pStru->field_E = minusOne;
    pStru->field_10 = 128;
    pStru->field_18 = minusOne;
    pStru->field_16 = 4;
    pStru->field_12 = 128;
    pStru->field_14 = 1;
    pStru->field_A = 0;
}
