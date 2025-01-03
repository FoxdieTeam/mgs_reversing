#ifndef _RADIO_H
#define _RADIO_H

#include "menuman.h"

typedef struct RadioIncomingCall // @ 8009E708
{
    short field_0;
    short field_2_timer; // counts down then call is missed
    int   field_4;
    int   field_8;
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

typedef struct MENU_CURPOS
{
    char mes[8];
    int  field_8;
    int  field_C;
    int  field_10;
    int  field_14;
    int  field_18;
    int  field_1C;
    int  field_20;
} MENU_CURPOS;

typedef struct SELECT_INFO
{
    short       field_0_xpos;
    short       field_2_ypos;
    short       current_index;
    short       top;
    char        max_num;
    char        field_9;
    short       current_dir;
    // Used to slow down the speed of entry selection while holding pad up/down.
    // See also struct Work in file select.c
    short       scroll_delay;
    short       field_E;
    short       field_10;
    short       field_12;
    short       field_14;
    short       open_count;
    short       field_18;
    short       field_1A;
    KCB        *field_1C_kcb;
    const char *message;
    MENU_CURPOS curpos[0];
} SELECT_INFO;

struct RadioFileModeUnk1;
struct RadioFileModeStruElem;

typedef void (*TRadioFileModeFn)(MenuPrim *, struct RadioFileModeStruElem *); // param types not final

typedef struct RadioFileModeStruElem
{
    int                       field_0;
    int                       field_4;
    TRadioFileModeFn          field_8_pFn;
    struct RadioFileModeUnk1 *field_C_unk1; // probably wrong type of pointer, it points to some smaller struct
} RadioFileModeStruElem;

typedef struct RadioFileModeUnk1 // guessed size, could be larger
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
} RadioFileModeUnk1;

typedef struct RadioFileModeUnk2
{
    int         field_0;
    const char *field_4;
    int         field_8;
    int         field_C;
    int         field_10;
    int         field_14;
    int         field_18;
} RadioFileModeUnk2;

typedef struct RadioFileModeStru_800ABB7C
{
    RadioFileModeStruElem field_0_array[12]; // guessed length
    RadioFileModeUnk2     field_c0_array[4];

    // could be larger? (but only 0..3 are explicitly indexed as far as I can tell)
    RadioFileModeUnk1 field_130_array[4];
    int               field_1d0;
    int               field_1d4;
    int               field_1d8;
    int               field_1dc;
    int               field_1e0;
    int               field_1e4;
    int               field_1e8;
    int               field_1ec;
    int               field_1f0;
    int               field_1f4;
    int               field_1f8;
    int               field_1fc;
    int               field_200;
    int               field_204;
    int               field_208;
    int               field_20c;
    int               field_210;
    int               field_214;
    int               field_218;
    int               field_21c;
    RadioFileModeUnk1 field_220_unk1; // guessed size, could be larger
    int               field_248;
    int               field_24c;
    int               field_250;
    int               field_254;
    int               field_258;
    int               field_25c;
} RadioFileModeStru_800ABB7C;

typedef struct RadioCodecStru_800ABB98
{
    short       field_0_idx;
    short       field_2;
    short       field_4_count;
    short       field_6; // Last pressed button in menu_radio_codec_helper_helper2_8004DF68
    short       field_8;
    short       field_a;
    KCB        *field_c_kcb;
    RadioMemory field_10_array[RADIO_MEMORY_COUNT];

} RadioCodecStru_800ABB98;

typedef struct _RadioUnknown
{
    char         coords[7][4];
    unsigned int color1;
    unsigned int color2;
} RadioUnknown;

typedef struct Radio_8009E664
{
    unsigned char x0, y0, w, h;
    unsigned char r0, g0, b0, code;
} Radio_8009E664;

// Those structs describe the structure of
// ".res" files.
//
// Note that 'r' (0x72) can be either a ".rar",
// ".res" or ".rpk" file. It looks like different
// ".res" files could have different data structure,
// for example "rubi.res" file has a different structure
// and it is not described by those structs.
//
// TODO: Is radio.h the right header file for this?
typedef struct ResHeader_Sub
{
    int  field_0;
    RECT field_4;
} ResHeader_Sub;

typedef struct ResHeader
{
    int           field_0;
    int           field_4;
    unsigned int  field_8;
    int           field_C;
    int           field_10;
    short         field_14[16];
    ResHeader_Sub field_34;
} ResHeader;

void           sub_8004D580(int pressed);
void           sub_8004124C(MenuWork *work);
void           menu_radio_update_helper2_80038A7C();
void           menu_radio_codec_create_state_80047CE4(MenuWork *menuMan);
// void           menu_radio_update_80042198(MenuWork *work, unsigned char *pOt);
void menu_800470B4(int idx, menu_chara_struct *pStru, int chara, int code, int faceUnk, int taskWup);
unsigned char *radio_moveToNext_80047880(menu_chara_struct *unk, unsigned char *pScript);
void           menu_radio_codec_task_proc_80047AA0(void);
void           menu_radio_codec_task_proc_helper_80046F3C(menu_chara_struct *pStru, faces_group *pFacesGroup);
void           menu_radio_compact_free_vars_8004D3D8(void);
void           init_radio_message_board_80040F74(MenuWork *work);
void           init_file_mode(DATA_INFO *pSaveMode, int param_2);
// void           sub_800434F4(MenuPrim *pGlue, int param_2, int param_3, PANEL_TEXTURE *param_4);
void           menu_RadioCall_helper_800403E4();
radio_table_entry           *sub_8004969C(radio_table *pRadioTable, int contactFrequency);
void           menu_radio_codec_helper_helper14_helper4_800408BC(MenuPrim *pGlue, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void           menu_radio_codec_helper_helper14_helper_80040034(MenuPrim *pGlue, int param_2, int param_3, int param_4);
void           menu_radio_codec_helper_helper14_helper5_800402A0(MenuPrim *pGlue, int param_2, int param_3, int param_4);
void           menu_radio_codec_helper_helper14_helper2_800401AC(MenuPrim *pGlue, int param_2, int param_3);
void           menu_radio_codec_helper_helper14_helper6_helper_8004064C(MenuPrim *pGlue, int xpos, int ypos, int colour,
                                                                        int idx);
int            MENU_GetRadioCode(int param_1);
void           sub_80047D70(MenuWork *work, int param_2, int pRadioCode);
void           sub_8004D4A0(RadioCodecStru_800ABB98 *pStru);
void           menu_radio_update_helper4_8004D2D0(int param_1);

int menu_number_draw(MenuWork *work, unsigned int *pOt, int xpos, int ypos, int number, int flags);
int menu_number_draw_number2(MenuWork *work, int xpos, int ypos, int current, int total);
int menu_number_draw_string(MenuWork *work, unsigned int *pOt, int xpos, int ypos, const char *str, int flags);
void radio_draw_face_frame(MenuPrim *pGlue, int x, int y, int w, int h);
void menu_draw_nouse(MenuPrim *pGlue, int offset_x, int offset_y);
void menu_draw_frozen(MenuPrim *pGlue, int offset_x, int offset_y);
void menu_number_draw_magazine(MenuWork *work, unsigned int *pOt, int xoff, int yoff, int pMagSize, int pAmmo, int pSubCnt2);
// void sub_8004ABF0(int param_1, int param_2, int param_3, int param_4, int divisor);
void sub_8004B9C4(SELECT_INFO *pStru, int param_2);
// void menu_radio_do_file_mode_helper12_helper_8004B8FC(char *param_1, char *param_2);
void menu_radio_init_save_mode(int param_1, int param_2);
void menu_radio_update_helper6_80047D40(MenuWork *work);

void menu_radio_codec_helper_helper4_8004DE20(MenuWork *work);
void menu_radio_draw_mem(MenuWork *work, unsigned char *pOt);
int menu_radio_codec_helper_helper2_8004DF68(MenuWork *work, GV_PAD *pPad);
void menu_radio_codec_helper__helper3_sub_8004DF44();
void menu_radio_codec_helper_helper_8004E198(int toFind);
int menu_radio_codec_helper_helper9_80047FF4();
void menu_radio_codec_state_2_helper_80048024();
void menu_radio_codec_helper_helper10_80047EFC(MenuWork *work, int param_2);
void menu_radio_codec_helper_helper8_80048044();
void menu_radio_codec_helper_helper3_80047F44(MenuWork *work, int param_2);
void menu_radio_codec_helper_helper7_80048080();
void ResetCodecState();
void *menu_radio_codec_helper_helper17_80038678();
int menu_radio_end_check(void);
void menu_radio_draw_face(MenuWork *work, menu_chara_struct *chara_struct);

// void sub_8004AEA8(SELECT_INFO *pStru);

// void menu_radio_do_file_mode_helper2_8004A87C(int idx, int param_2, int param_3, int divisor, int idx2);
// void allocMemoryForSelectInfo(SELECT_INFO **selectInfo, int num);
// int *menu_radio_do_file_mode_helper5_8004ABDC(int idx);
// void menu_radio_do_file_mode_helper4_8004AA68(int idx, int param_2, int param_3, int param_4, int param_5, int divisor);
// void menu_radio_do_file_mode_helper3_8004A994(int idx, int param_2, int param_3, int divisor, SELECT_INFO *field_14);
// int menu_radio_do_file_mode_helper17_8004C2E4(GV_PAD *pPad, int *outParam, SELECT_INFO *pStru);
// void drawCaption_8004AE3C(MenuWork *menuWork, const char *caption);
// int menu_radio_do_file_mode_helper12_8004BA80(MenuWork *work, MEM_CARD *pMemcard, const char *param_3, SELECT_INFO *pStru2);
// void menu_radio_do_file_mode_helper14_8004BE98(MenuWork *work, char *param_2, SELECT_INFO *pStru);
// void freeMemoryForSelectInfo(SELECT_INFO *selectInfo);
void draw_radio_wait_mark(MenuWork *work, unsigned char *pOt);
// void menu_radio_do_file_mode_helper15_8004C04C(MenuWork *work, const char **srcs, int cnt, int field_4, const char *field_20, SELECT_INFO *pStru);
// void menu_radio_do_file_mode_helper16_8004C164(MenuPrim *pGlue, SELECT_INFO *pStru);
// int menu_radio_do_file_mode_helper13_8004BCF8(GV_PAD *pPad, int *pOut, SELECT_INFO *pStru);
// void menu_radio_do_file_mode_helper8_8004AFE4(MenuWork *work, char *pOt, SELECT_INFO *pStru);
// void menu_radio_do_file_mode_helper6_8004AD40(MenuPrim *pGlue);
// void menu_radio_do_file_mode_save_memcard_8004B0A0(MenuWork *work, char *pOt, SELECT_INFO *pStru);
// void menu_radio_do_file_mode_helper_8004A858();
void menu_draw_triangle(MenuPrim *pGlue, Menu_Triangle *pTriangle);

#endif // _RADIO_H
