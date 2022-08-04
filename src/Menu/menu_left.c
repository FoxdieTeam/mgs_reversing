#include "Menu/menuMan.h"
#include "linker.h"

MenuMan_Inventory_14h_Unk SECTION(".gMenuMan_800BD5A0") dword_800BD5A0;

extern int dword_800ABAD0;
int SECTION(".sbss") dword_800ABAD0;

void menu_init_rpk_item_8003DDCC(MenuMan_Inventory_14h_Unk *pUnk, int imgIdx, int palIdx);
int  menu_restore_nouse_80043470();
int  sub_8003CFE0(int a1, int a2);
int  sub_8003B5E0(int a1);
void menu_inventory_left_update_8003C95C(struct Actor_MenuMan *menuMan, unsigned char *param_2);
void menu_inventory_left_helper_8003B8F0(struct Actor_MenuMan *menuMan, unsigned int *param_2, int param_3, int param_4, short *param_5);
int *sub_8003D6A8(struct menu_left_right *a1, int a2, int *a3);
void menu_sub_8003B568(void);
int sub_8003CB98(struct Actor_MenuMan *a1);
void menu_init_nouse_800434A8(void);

void menu_sub_8003B568(void)
{
    int imgIdx;
    DWORD palIdx;
    int i;
    
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

#pragma INCLUDE_ASM("asm/sub_8003B5E0.s")
#pragma INCLUDE_ASM("asm/menu_8003B614.s")
#pragma INCLUDE_ASM("asm/menu_8003B6D0.s")
#pragma INCLUDE_ASM("asm/menu_8003B794.s")
#pragma INCLUDE_ASM("asm/menu_inventory_left_helper_8003B8F0.s")
#pragma INCLUDE_ASM("asm/menu_8003BBEC.s")
#pragma INCLUDE_ASM("asm/menu_inventory_left_update_helper_8003BCD4.s")
#pragma INCLUDE_ASM("asm/menu_inventory_left_update_helper2_8003BF1C.s")
#pragma INCLUDE_ASM("asm/menu_inventory_left_update_helper3_8003C24C.s")
#pragma INCLUDE_ASM("asm/menu_inventory_left_update_helper4_8003C4EC.s")
#pragma INCLUDE_ASM("asm/menu_inventory_left_update_8003C95C.s")

int sub_8003CB98(struct Actor_MenuMan* a1)
{
    int v2;
    int result;
    int v4;

    menu_restore_nouse_80043470();
    v2 = a1->field_1DC_menu_left.field_0_rpk_idx;
    result = -1;
    if (v2 != -1 || (v2 = a1->field_1DC_menu_left.field_11, v2 != -1))
    {
        v4 = sub_8003B5E0(v2);
        result = sub_8003CFE0(v4, 0);
    }
    return result;
}

void menu_inventory_left_8003CBF0(struct Actor_MenuMan *menuMan)
{
    short val = -1;
    menuMan->m7FnPtrs_field_2C[2] = menu_inventory_left_update_8003C95C;
    menuMan->field_1DC_menu_left.field_0_rpk_idx = val;
    menuMan->field_1DC_menu_left.field_10 = 0;
    menuMan->field_1DC_menu_left.field_4 = 0;
    menuMan->field_1DC_menu_left.field_6 = 1;
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
