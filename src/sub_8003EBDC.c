#include "menuMan.h"

MenuMan_Inventory_14h_Unk *menu_right_get_weapon_rpk_info_8003DED8(int weaponIdx);
void sub_8003CFE0(unsigned int **images, int index);

void sub_8003EBDC(struct Actor_MenuMan *menuMan)
{
    MenuMan_Inventory_14h_Unk *inventory_unk;
    int weapon_index;

    weapon_index = (int)(menuMan->field_1F0_menu_right).field_0_rpk_idx;
    if ((weapon_index != -1) ||
        (weapon_index = *(signed char *)&((menuMan->field_1F0_menu_right).field_11), weapon_index != -1))
    {
        inventory_unk = menu_right_get_weapon_rpk_info_8003DED8(weapon_index);
        sub_8003CFE0((unsigned int **)&inventory_unk->field_0_pixels, 1);
    }
}
