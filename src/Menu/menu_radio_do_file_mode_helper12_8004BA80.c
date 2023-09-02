#include "Menu/radio.h"
#include "psyq.h"

extern menu_save_mode_data *dword_800ABB4C;
menu_save_mode_data        *dword_800ABB4C;

extern int dword_800AB6EC;
int        dword_800AB6EC;

extern int dword_800ABB48;
int        dword_800ABB48;

extern char  aBislpm99999[];
extern char  aFileS[];
extern char *MGS_MemoryCardName_800AB2EC;
extern char  dword_800AB73C[];

int menu_radio_do_file_mode_helper12_8004BA80(Actor_MenuMan *pActor, RadioFileModeUnkStru *pStru1, char *param_3,
                                              Stru_800ABB74 *pStru2)
{
    Stru_800ABB74_child       *pIter;
    RadioFileModeUnkStruChild *pChild;
    int                        i;

    pIter = pStru2->field_24;

    strcpy(aBislpm99999, MGS_MemoryCardName_800AB2EC);
    aBislpm99999[12] = dword_800ABB4C->field_0[0];

    for (i = 0; i < pStru1->field_2; i++)
    {
        pChild = &pStru1->field_4[i];
        mts_printf_8008BBA0(aFileS, pChild->field_0);

        if (strncmp(pChild->field_0, aBislpm99999, 13) == 0)
        {
            menu_radio_do_file_mode_helper12_helper_8004B8FC(pIter->field_0_name, pChild->field_0);
            pIter->field_20 = i;
            pIter++;
        }
    }

    if (dword_800ABB48 == 0 && pStru1->field_3 >= dword_800ABB4C->field_3)
    {
        pIter->field_0_name[0] = dword_800AB73C[0];
        pIter->field_20 = 16;
        pIter++;
    }

    pStru2->field_1C_kcb = pActor->field_214_font;
    pStru2->field_8 = pIter - pStru2->field_24;

    if (dword_800ABB4C->field_0[0] != 71)
    {
        if (pStru2->field_8 && pIter[-1].field_20 == 16)
        {
            pStru2->field_4 = pStru2->field_8 - 1;
        }
        else
        {
            pStru2->field_4 = 0;
        }
    }
    else if (dword_800AB6EC == -1 || dword_800AB6EC >= pStru2->field_8)
    {
        if (dword_800ABB48 == 0 && pStru2->field_8 && pIter[-1].field_20 == 16)
        {
            pStru2->field_4 = pStru2->field_8 - 1;
        }
        else
        {
            pStru2->field_4 = 0;
        }
    }
    else
    {
        pStru2->field_4 = dword_800AB6EC;
    }

    pStru2->field_6 = 0;
    pStru2->field_20 = param_3;
    pStru2->field_E = -1;
    pStru2->field_0_xpos = 40;
    pStru2->field_2_ypos = 40;
    pStru2->field_16 = 8;
    pStru2->field_A = 0;
    pStru2->field_18 = -1;
    pStru2->field_12 = 240;
    pStru2->field_14 = 1;
    sub_8004B9C4(pStru2, 0);
    return pStru2->field_8 != 0;
}
