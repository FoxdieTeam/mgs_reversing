#include "linker.h"
#include "menuMan.h"

extern int GM_GameStatus_800AB3CC;

void menu_sub_menu_update_8003DA0C(struct Actor_MenuMan *pActor, int a2, struct menu_left_right *pSubMenu)
{
    if ((GM_GameStatus_800AB3CC & 0x1020) != 0x20)
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

extern struct menu_8009E544 *dword_800AB584;
struct menu_8009E544 *SECTION(".sdata") dword_800AB584;

int SECTION(".dword_800B7800") dword_800B7800;

int menu_8003DA9C(struct menu_left_right *pMenu, unsigned short *input)
{
    struct menu_8009E544 *field_8_pStru; // $a0

    if ((dword_800B7800 & 0x101) != 0)
    {
    ret_zero:
        return 0;
    }

    if ((GM_GameStatus_800AB3CC & 0x1020) == 0x20)
    {
        // TODO: probably a fake match, every return 0
        // is supposed to point to ret_zero but
        // the last one doesn't without a goto.
        goto ret_zero;
    }

    field_8_pStru = pMenu->field_8_pStru;

    if ((*input & field_8_pStru->field_4_input) == 0)
    {
        goto ret_zero;
    }
    dword_800AB584 = field_8_pStru;

    return 1;
}
