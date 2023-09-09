#include "Menu/menuman.h"

void menu_radio_codec_helper_helper10_80047EFC(Actor_MenuMan *pActor, int param_2)
{
    int                    i;
    menu_chara_struct     *pStru;
    menu_chara_struct_sub *pSub;

    pStru = pActor->field_218;
    pStru->field_38 = 1;

    for (i = 0; i < 2; i++)
    {
        pSub = &pStru->field_3C[i];
        if (param_2 != 0)
        {
            pSub->field_6 = 1;
        }
        else
        {
            pSub->field_6 = 10;
        }
    }
}
