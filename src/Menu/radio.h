#ifndef _RADIO_H
#define _RADIO_H

#include "menuman.h"

typedef struct RadioIncomingCall // @ 8009E708
{
    short field_0;
    short field_2_timer; // counts down then call is missed
    int field_4;
    int field_8;
} RadioIncomingCall;

void           sub_8004124C(Actor_MenuMan *pActor);
void           menu_radio_codec_create_state_80047CE4(Actor_MenuMan *menuMan);
void           menu_radio_update_80042198(void);
void           sub_800470B4(int param_1, void *param_2, int param_3, int param_4, int param_5, int param_6);
unsigned char *radio_moveToNext_80047880(menu_chara_struct *unk, unsigned char *pScript);
void           menu_radio_codec_task_proc_80047AA0(void);
void           menu_radio_compact_free_vars_8004D3D8(void);
void           init_radio_message_board_80040F74(Actor_MenuMan *pActor);
void           init_file_mode_8004D24C(menu_save_mode_data *pSaveMode, int param_2);
void           sub_800434F4(MenuGlue *pGlue, int param_2, int param_3, MenuMan_Inventory_14h_Unk *param_4);
void           menu_RadioCall_helper_800403E4();
int           *sub_8004969C(int param_1, int param_2);
void           menu_radio_codec_helper_helper14_helper6_helper_8004064C(MenuGlue *pGlue, int xpos, int ypos, int colour,
                                                                        int param_5);
int            menu_GetRadioCode_800497C4(int param_1);
void           sub_80047D70(Actor_MenuMan *pActor, int param_2, int pRadioCode);

int menu_number_draw_80042F78(Actor_MenuMan *pActor, int a2, int xpos, int ypos, int number, int flags);
void menu_draw_nouse_800435A4(MenuGlue *pGlue, int offset_x, int offset_y);
void menu_draw_frozen_800435C8(MenuGlue *pGlue, int offset_x, int offset_y);

#endif // _RADIO_H
