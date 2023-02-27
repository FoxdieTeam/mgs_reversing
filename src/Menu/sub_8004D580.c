#include "Menu/radio.h"
#include "Game/game.h"

extern RadioCodecStru_800ABB98 *stru_800ABB98;
RadioCodecStru_800ABB98        *stru_800ABB98;

void sub_8004D580(int pressed)
{
    int                      new_idx;
    RadioCodecStru_800ABB98 *pStru;

    if (pressed != 0)
    {
        GM_Sound_80032968(0, 0x3f, 0x69);
    }

    pStru = stru_800ABB98;
    stru_800ABB98->field_0_idx += pressed;
    new_idx = stru_800ABB98->field_0_idx;

    if (new_idx < 0 || new_idx >= pStru->field_4_count)
    {
        pStru->field_0_idx -= pressed;
    }
    else if (new_idx < pStru->field_2)
    {
        pStru->field_2 -= 2;
    }
    else if (pStru->field_2 + 8 <= new_idx)
    {
        pStru->field_2 += 2;
    }

    sub_8004D4A0(pStru);
}
