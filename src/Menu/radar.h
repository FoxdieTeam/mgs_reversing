#ifndef _RADAR_H_
#define _RADAR_H_

typedef struct radar_uv // CHARA_TABLE
{
    char          field_0_x;
    char          field_1_y;
    unsigned char field_2_w;
    unsigned char field_3_h;
} radar_uv;

typedef void (*TRadarFn_800AB48C)(Actor_MenuMan *, unsigned char *);

void menu_radar_update_8003B350(struct Actor_MenuMan* work, unsigned char * pOt);
void menu_init_radar_helper_8003ADAC();
void menu_radar_helper_8003ADD8(struct Actor_MenuMan *a1, int a2);
void menu_SetRadarFunc_80038F30(TRadarFn_800AB48C func);

void draw_radar_8003AEC0(Actor_MenuMan *work, unsigned char * pOt);
void menu_radar_load_rpk_8003AD64();

#endif // _RADAR_H_
