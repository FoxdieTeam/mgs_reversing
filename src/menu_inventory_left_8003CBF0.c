#include "menuMan.h"

extern void menu_inventory_left_update_8003C95C(struct Actor_MenuMan *menuMan, unsigned int *param_2);
extern void menu_inventory_left_helper_8003B8F0(struct Actor_MenuMan *menuMan, unsigned int *param_2, int param_3,
                                                int param_4, short *param_5);
extern int *sub_8003D6A8(struct menu_left_right *a1, int a2, int *a3);
extern void menu_sub_8003B568(void);
extern int sub_8003CB98(struct Actor_MenuMan *a1);
extern void menu_init_nouse_800434A8(void);

extern int dword_800ABAD0;
int SECTION(".sbss") dword_800ABAD0;

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
