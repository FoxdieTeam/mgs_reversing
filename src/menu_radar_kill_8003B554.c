#include "menuMan.h"

void menu_radar_update_8003B350(struct Actor_MenuMan *a1, int a2);
void menu_init_radar_helper_8003ADAC(void);
void Menu_scale_80038E28(int);
void menu_radar_helper_8003ADD8(struct Actor_MenuMan *a1, int a2);

extern int gFn_radar_800AB48C;
int SECTION(".sdata") gFn_radar_800AB48C;

void menu_radar_init_8003B474(struct Actor_MenuMan *pActor)
{
    unsigned char field_28_flags; // $v1

    field_28_flags = pActor->field_28_flags;
    pActor->m7FnPtrs_field_2C[3]  = menu_radar_update_8003B350;
    pActor->field_1D8 = 1;
    pActor->field_1D4_clipX1 = 0;
    pActor->field_1D6_clipY1 = 0;
    pActor->field_28_flags = field_28_flags | 8;
    menu_radar_helper_8003ADD8(pActor, 0);
    menu_radar_helper_8003ADD8(pActor, 1);

    pActor->field_154 = pActor->field_4C_drawEnv[0];
    pActor->field_194 = pActor->field_4C_drawEnv[1];

    menu_init_radar_helper_8003ADAC();
    gFn_radar_800AB48C = 0;
    Menu_scale_80038E28(4096);
}

void menu_radar_kill_8003B554(struct Actor_MenuMan *pActor)
{
    pActor->field_28_flags &= ~8u;
}
