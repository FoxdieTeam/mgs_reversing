#include "linker.h"
#include "menuMan.h"

extern int game_state_flags_800AB3CC;

void menu_sub_menu_update_8003DA0C(struct Actor_MenuMan *pActor, int a2, struct menu_left_right *pSubMenu)
{
    if ((game_state_flags_800AB3CC & 0x1020) != 0x20)
    {
        pSubMenu->field_8_pStru->field_18_pFnUpdate(
            pActor,
            a2,
            pSubMenu->field_8_pStru->field_0,
            pSubMenu->field_8_pStru->field_2,
            pSubMenu);
    }
}

void sub_8003DA60(struct Actor_MenuMan *pActor, int a2, struct menu_left_right *pLeftRight, int off1, int off2)
{
    pLeftRight->field_8_pStru->field_18_pFnUpdate(
        pActor,
        a2,
        pLeftRight->field_8_pStru->field_0 + off1,
        pLeftRight->field_8_pStru->field_2 + off2,
        pLeftRight);
}
