#include "radio.h"
#include "Game/game.h"

void sub_8004B9C4(Stru_800ABB74 *pStru, int param_2)
{
    short field_6;
    short new_field_6;
    int   field_4;

    field_4 = pStru->field_4;
    new_field_6 = pStru->field_4 + param_2;
    pStru->field_4 = new_field_6;
    if (new_field_6 < 0)
    {
        pStru->field_4 = 0;
    }
    else if (new_field_6 >= pStru->field_8)
    {
        pStru->field_4 = pStru->field_8 - 1;
    }
    else
    {
        field_6 = pStru->field_6;
        if (new_field_6 < field_6)
        {
            pStru->field_6 = new_field_6;
        }
        else if (new_field_6 >= (field_6 + 6))
        {
            pStru->field_6 = new_field_6 - 5;
        }
    }
    if (pStru->field_4 != field_4)
    {
        GM_SeSet2_80032968(0, 0x3F, 0x1F);
    }
    sub_8004AEA8(pStru);
}
