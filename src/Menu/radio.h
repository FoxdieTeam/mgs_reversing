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

typedef struct RadioCoordsStru_8009E6FC
{
    char field_0;
    char field_1;
    char field_2;
    char field_3;
    char field_4;
    char field_5;
} RadioCoordsStru_8009E6FC;

typedef struct RadioFileModeStruElem
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
} RadioFileModeStruElem;

typedef struct RadioFileModeStru_800ABB7C
{
    RadioFileModeStruElem field_0_array[12]; // guessed length
    int                   field_c0;
    int                   field_c4;
    int                   field_c8;
    int                   field_cc;
    int                   field_d0;
    int                   field_d4;
    int                   field_d8;
    int                   field_dc;
    int                   field_e0;
    int                   field_e4;
    int                   field_e8;
    int                   field_ec;
    int                   field_f0;
    int                   field_f4;
    int                   field_f8;
    int                   field_fc;
    int                   field_100;
    int                   field_104;
    int                   field_108;
    int                   field_10c;
    int                   field_110;
    int                   field_114;
    int                   field_118;
    int                   field_11c;
    int                   field_120;
    int                   field_124;
    int                   field_128;
    int                   field_12c;
    int                   field_130;
    int                   field_134;
    int                   field_138;
    int                   field_13c;
    int                   field_140;
    int                   field_144;
    int                   field_148;
    int                   field_14c;
    int                   field_150;
    int                   field_154;
    int                   field_158;
    int                   field_15c;
    int                   field_160;
    int                   field_164;
    int                   field_168;
    int                   field_16c;
    int                   field_170;
    int                   field_174;
    int                   field_178;
    int                   field_17c;
    int                   field_180;
    int                   field_184;
    int                   field_188;
    int                   field_18c;
    int                   field_190;
    int                   field_194;
    int                   field_198;
    int                   field_19c;
    int                   field_1a0;
    int                   field_1a4;
    int                   field_1a8;
    int                   field_1ac;
    int                   field_1b0;
    int                   field_1b4;
    int                   field_1b8;
    int                   field_1bc;
    int                   field_1c0;
    int                   field_1c4;
    int                   field_1c8;
    int                   field_1cc;
    int                   field_1d0;
    int                   field_1d4;
    int                   field_1d8;
    int                   field_1dc;
    int                   field_1e0;
    int                   field_1e4;
    int                   field_1e8;
    int                   field_1ec;
    int                   field_1f0;
    int                   field_1f4;
    int                   field_1f8;
    int                   field_1fc;
    int                   field_200;
    int                   field_204;
    int                   field_208;
    int                   field_20c;
    int                   field_210;
    int                   field_214;
    int                   field_218;
    int                   field_21c;
    int                   field_220;
    int                   field_224;
    int                   field_228;
    int                   field_22c;
    int                   field_230;
    int                   field_234;
    int                   field_238;
    int                   field_23c;
    int                   field_240;
    int                   field_244;
    int                   field_248;
    int                   field_24c;
    int                   field_250;
    int                   field_254;
    int                   field_258;
    int                   field_25c;
} RadioFileModeStru_800ABB7C;

void           sub_8004124C(Actor_MenuMan *pActor);
void           menu_radio_codec_create_state_80047CE4(Actor_MenuMan *menuMan);
void           menu_radio_update_80042198(void);
void menu_800470B4(int idx, menu_chara_struct *pStru, int chara, int code, int faceUnk, int taskWup);
unsigned char *radio_moveToNext_80047880(menu_chara_struct *unk, unsigned char *pScript);
void           menu_radio_codec_task_proc_80047AA0(void);
void           menu_radio_compact_free_vars_8004D3D8(void);
void           init_radio_message_board_80040F74(Actor_MenuMan *pActor);
void           init_file_mode_8004D24C(menu_save_mode_data *pSaveMode, int param_2);
void           sub_800434F4(MenuGlue *pGlue, int param_2, int param_3, PANEL_TEXTURE *param_4);
void           menu_RadioCall_helper_800403E4();
radio_table_entry           *sub_8004969C(radio_table *pRadioTable, int contactFrequency);
void           menu_radio_codec_helper_helper14_helper4_800408BC(MenuGlue *pGlue, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void           menu_radio_codec_helper_helper14_helper_80040034(MenuGlue *pGlue, int param_2, int param_3, int param_4);
void           menu_radio_codec_helper_helper14_helper5_800402A0(MenuGlue *pGlue, int param_2, int param_3, int param_4);
void           menu_radio_codec_helper_helper14_helper2_800401AC(MenuGlue *pGlue, int param_2, int param_3);
void           menu_radio_codec_helper_helper14_helper3_80040590(MenuGlue *pGlue, int *param_2, int param_3, int param_4, int param_5);
void           menu_radio_codec_helper_helper14_helper6_helper_8004064C(MenuGlue *pGlue, int xpos, int ypos, int colour,
                                                                        int idx);
int            menu_GetRadioCode_800497C4(int param_1);
void           sub_80047D70(Actor_MenuMan *pActor, int param_2, int pRadioCode);

int menu_number_draw_80042F78(Actor_MenuMan *pActor, int a2, int xpos, int ypos, int number, int flags);
void menu_draw_nouse_800435A4(MenuGlue *pGlue, int offset_x, int offset_y);
void menu_draw_frozen_800435C8(MenuGlue *pGlue, int offset_x, int offset_y);

#endif // _RADIO_H
