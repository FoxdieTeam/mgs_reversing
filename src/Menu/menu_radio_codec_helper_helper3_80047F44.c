#include "Menu/menuman.h"
#include "Game/game.h"

void menu_radio_codec_helper_helper3_80047F44(Actor_MenuMan *pActor, int param_2)
{
    int                    i;
    menu_chara_struct     *pStru;
    menu_chara_struct_sub *pSub;

    pStru = pActor->field_218;

    for (i = 0; i < 2; i++)
    {
        pSub = &pStru->field_3C[i];
        if (pSub->field_0_animState != 0)
        {
            pSub->field_0_animState = 4;
            if (param_2 != 0)
            {
                pSub->field_6 = -1;
                GM_Sound_80032968(0, 63, 87);
            }
            else
            {
                pSub->field_4 = 0;
            }
        }
    }
}
