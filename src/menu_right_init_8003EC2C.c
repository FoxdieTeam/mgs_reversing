#include "menuMan.h"

extern void menu_right_update_8003E990(struct Actor_MenuMan *menuMan, unsigned int *param_2);
extern void menu_right_init_helper_8003E0E8(struct Actor_MenuMan *menuMan, unsigned int *param_2, int param_3,
                                            int param_4, short *param_5);

extern void menu_inventory_left_update_8003C95C(struct Actor_MenuMan *menuMan, unsigned int *param_2);
extern void menu_inventory_left_helper_8003B8F0(struct Actor_MenuMan *menuMan, unsigned int *param_2, int param_3,
                                                int param_4, short *param_5);
extern int *sub_8003D6A8(struct menu_left_right *a1, int a2, int *a3);
extern void menu_inventory_right_init_items_8003DE50(void);
extern int sub_8003EBDC(struct Actor_MenuMan *a1);

extern int dword_800ABAE8;
int SECTION(".sbss") dword_800ABAE8;

void menu_right_init_8003EC2C(struct Actor_MenuMan *menuMan)

{
    short val = -1;
    menuMan->m7FnPtrs_field_2C[1] = menu_right_update_8003E990;
    menuMan->field_1F0_menu_right.field_0_rpk_idx = val;
    menuMan->field_1F0_menu_right.field_10 = 0;
    menuMan->field_1F0_menu_right.field_12 = 0;
    menuMan->field_1F0_menu_right.field_4 = 0;
    menuMan->field_1F0_menu_right.field_6 = 1;
    menuMan->field_1F0_menu_right.field_11 = val;
    menuMan->field_28_flags |= 2;
    dword_800ABAE8 = 0;
    sub_8003D6A8(&menuMan->field_1F0_menu_right, 1, (int *)menu_right_init_helper_8003E0E8);
    menu_inventory_right_init_items_8003DE50();
    sub_8003EBDC(menuMan);
}
