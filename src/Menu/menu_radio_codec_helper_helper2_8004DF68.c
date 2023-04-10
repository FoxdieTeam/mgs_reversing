#include "Menu/radio.h"
#include "Game/game.h"

extern RadioCodecStru_800ABB98 *stru_800ABB98;
RadioCodecStru_800ABB98        *stru_800ABB98;

extern int gRadioCodecIdx_800AB770;
int        gRadioCodecIdx_800AB770;

extern short word_800ABB9C;
short        word_800ABB9C;

extern short gRadioCodecFrequency_800ABB9E;
short        gRadioCodecFrequency_800ABB9E;

int menu_radio_codec_helper_helper2_8004DF68(Actor_MenuMan *pActor, GV_PAD *pPad)
{
    RadioCodecStru_800ABB98 *pStru;
    int                      pressed;

    pStru = stru_800ABB98;
    pressed = 0;
    if (pPad->status & (PAD_UP | PAD_DOWN))
    {
        if (pPad->status & PAD_UP)
        {
            pressed = -2;
        }
        else
        {
            pressed = 2;
        }
    }
    else if (pPad->status & (PAD_LEFT | PAD_RIGHT))
    {
        if (pPad->status & PAD_LEFT)
        {
            pressed = -1;
        }
        else
        {
            pressed = 1;
        }
    }

    if (pressed != 0)
    {
        if (pStru->field_6 == pressed)
        {
            pStru->field_8--;
            if (pStru->field_8 < 0)
            {
                sub_8004D580(pressed);
                pStru->field_8 = 2;
            }
        }
        else
        {
            sub_8004D580(pressed);
            pStru->field_8 = 10;
            pStru->field_6 = pressed;
        }
    }
    else
    {
        pStru->field_6 = 0;
    }

    if (pPad->press & PAD_CIRCLE)
    {
        gRadioCodecIdx_800AB770 = pStru->field_0_idx;
        gRadioCodecFrequency_800ABB9E = pStru->field_10_array[gRadioCodecIdx_800AB770].frequency;
        word_800ABB9C = 1;
        GM_SeSet2_80032968(0, 0x3f, 0x55);
    }
    if (pPad->press & PAD_CROSS)
    {
        gRadioCodecFrequency_800ABB9E = -1;
        word_800ABB9C = 1;
        GM_SeSet2_80032968(0, 0x3f, 0x68);
    }
    if (word_800ABB9C == 0 && pActor->field_212 > 4)
    {
        return gRadioCodecFrequency_800ABB9E;
    }
    else
    {
        return 0;
    }
}
