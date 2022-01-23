#include "linker.h"
#include "menuMan.h"

extern struct menu_rpk_item *gRadar_rpk_800ABAC8;
struct menu_rpk_item *SECTION(".sbss") gRadar_rpk_800ABAC8;
struct menu_rpk_item* menu_rpk_get_img_8003DDB4(int idx);

extern void LoadImage_8008FB10(RECT *, unsigned char *);

void menu_radar_load_rpk_8003AD64()
{
    RECT rect;
    rect.x = 992;
    rect.y = 336;
    rect.w = gRadar_rpk_800ABAC8->field_2_w;
    rect.h = gRadar_rpk_800ABAC8->field_3_h;
    LoadImage_8008FB10(&rect, (unsigned char*)&gRadar_rpk_800ABAC8[1]);
}

void menu_init_radar_helper_8003ADAC()
{
    gRadar_rpk_800ABAC8 = menu_rpk_get_img_8003DDB4(41);
    menu_radar_load_rpk_8003AD64();
}
