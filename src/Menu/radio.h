#ifndef _RADIO_H
#define _RADIO_H

#include "menuman.h"

void sub_8004124C(int param_1);
void menu_radio_codec_create_state_80047CE4(Actor_MenuMan *menuMan);
void menu_radio_update_80042198(void);
void sub_800470B4(int param_1, void *param_2, int param_3, int param_4, int param_5, int param_6);
unsigned char *radio_moveToNext_80047880(menu_chara_struct *unk, unsigned char *pScript);
void menu_radio_codec_task_proc_80047AA0(void);
void  menu_radio_compact_free_vars_8004D3D8(void);

#endif // _RADIO_H
