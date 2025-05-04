#ifndef _RADAR_H_
#define _RADAR_H_

#include "menuman.h"

typedef struct radar_uv // CHARA_TABLE
{
    char          field_0_x;
    char          field_1_y;
    unsigned char field_2_w;
    unsigned char field_3_h;
} radar_uv;

typedef void (*TRadarFn_800AB48C)(MenuWork *, unsigned char *);

void menu_radar_update_8003B350(MenuWork *work, unsigned char *ot);
void menu_init_radar_helper_8003ADAC(void);
void menu_radar_helper_8003ADD8(MenuWork *work, int index);
void MENU_SetRadarFunc(TRadarFn_800AB48C func);

void draw_radar(MenuWork *work, unsigned char * pOt);
void menu_radar_load_rpk_8003AD64();

#endif // _RADAR_H_
