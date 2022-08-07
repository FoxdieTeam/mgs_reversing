#include "menuman.h"
#include "linker.h"
#include "Script_tbl_map_8002BB44.h"

MenuMan_Inventory_14h_Unk SECTION(".gMenuMan_800BD5A0") dword_800BD5A0;
MenuMan_Inventory_14h_Unk SECTION(".stru_800BD4B0") stru_800BD4B0[6]; // TODO: Based on gItemInfos_8009E484 field_4 this could be up to 30?
extern menu_weapon_rpk_info gMenuItemRpkInfo_8009E484[];
extern GameState_800B4D98 gGameState_800B4D98;

extern int dword_800ABAD0;
int        SECTION(".sbss") dword_800ABAD0;

void menu_sub_8003B568(void)
{
    int   imgIdx;
    u_long palIdx;
    int   i;

    for (i = 0; i < 0x15; i++)
    {
        imgIdx = 0xc + i;
        palIdx = 0x2e;
        if (imgIdx != 0x16)
        {
            palIdx = 0;
            if (imgIdx == 0x1b)
            {
                palIdx = 0x2f;
            }
        }
        menu_init_rpk_item_8003DDCC(&dword_800BD5A0 + i, imgIdx, palIdx);
    }
}

MenuMan_Inventory_14h_Unk *menu_rpk_8003B5E0(int idx)
{
    return &stru_800BD4B0[gMenuItemRpkInfo_8009E484[idx].field_4_rpk_idx];
}

#pragma INCLUDE_ASM("asm/menu_8003B614.s")
#pragma INCLUDE_ASM("asm/menu_inventory_Is_Item_Disabled_8003B6D0.s")
#pragma INCLUDE_ASM("asm/menu_8003B794.s")
#pragma INCLUDE_ASM("asm/menu_inventory_left_helper_8003B8F0.s")

#pragma INCLUDE_ASM("asm/menu_8003BBEC.s")

#pragma INCLUDE_ASM("asm/menu_inventory_left_update_helper_8003BCD4.s")
#pragma INCLUDE_ASM("asm/menu_inventory_left_update_helper2_8003BF1C.s")
#pragma INCLUDE_ASM("asm/menu_inventory_left_update_helper3_8003C24C.s")
#pragma INCLUDE_ASM("asm/menu_inventory_left_update_helper4_8003C4EC.s")
#pragma INCLUDE_ASM("asm/menu_inventory_left_update_8003C95C.s")

int sub_8003CB98(struct Actor_MenuMan *pActor)
{
    int field_0_item_id_idx; // $a0
    MenuMan_Inventory_14h_Unk *pItem; // $v0
    int result;

    menu_restore_nouse_80043470();
    field_0_item_id_idx = pActor->field_1DC_menu_left.field_0.field_0_item_id_idx;
    result = -1;
    if ( field_0_item_id_idx != -1
      || (field_0_item_id_idx = pActor->field_1DC_menu_left.field_11, field_0_item_id_idx != -1) )
    {
        pItem = menu_rpk_8003B5E0(field_0_item_id_idx);
        result = sub_8003CFE0(pItem, 0);
    }
    return result;
}

void menu_inventory_left_8003CBF0(struct Actor_MenuMan *menuMan)
{
    short val = -1;
    menuMan->m7FnPtrs_field_2C[2] = (TMenuUpdateFn)menu_inventory_left_update_8003C95C;
    menuMan->field_1DC_menu_left.field_0.field_0_item_id_idx = val;
    menuMan->field_1DC_menu_left.field_10 = 0;
    menuMan->field_1DC_menu_left.field_0.field_4 = 0;
    menuMan->field_1DC_menu_left.field_0.field_6 = 1;
    menuMan->field_1DC_menu_left.field_11 = val;
    menuMan->field_28_flags |= 4;
    dword_800ABAD0 = 0;
    sub_8003D6A8(&menuMan->field_1DC_menu_left, 0, (int *)menu_inventory_left_helper_8003B8F0);
    menu_sub_8003B568();
    sub_8003CB98(menuMan);
    menu_init_nouse_800434A8();
}

void menu_left_kill_8003CC74(Actor_MenuMan *pMenu)
{
    pMenu->field_28_flags &= ~4u;
}
