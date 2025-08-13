#ifndef __MGS_MENU_RADIO_H__
#define __MGS_MENU_RADIO_H__

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
    MENU_CURPOS menu[0];
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
typedef struct TIM_DATA
{
    u_int   bnum;
    RECT    rect;
    u_short data[0];
} TIM_DATA;

typedef struct TIM
{
    int      id;
    int      flag;
    TIM_DATA clut;
    u_short  clut_data[16];
    TIM_DATA pixel;
} TIM;

/* radio.c */
void FadeCodecScreen(MenuWork *work, unsigned char *pOt, int opacity);
void sub_8003FD50(MenuPrim *pMenuPrim, int xoff, int yoff, int param_4, RadioUnknown *pRadioUnknown, int abe);
void sub_8003FFB0(MenuPrim *pGlue, int x0, int y0, int rgb);
void menu_radio_codec_helper_helper14_helper_80040034(MenuPrim *pGlue, int param_2, int param_3, int param_4);
void menu_radio_codec_helper_helper14_helper2_800401AC(MenuPrim *pGlue, int param_2, int param_3);
void menu_radio_codec_helper_helper14_helper5_800402A0(MenuPrim *pGlue, int param_2, int param_3, int param_4);
void menu_RadioCall_helper_800403E4(void);
void menu_radio_update_helper3_80040498(MenuPrim *pGlue);
void menu_radio_codec_helper_helper14_helper3_80040590(MenuPrim *pGlue, Radio_8009E664 *param_2, int cnt, int xoff, int yoff);
void menu_radio_codec_helper_helper14_helper6_helper_8004064C(MenuPrim *pGlue, int xpos, int ypos, int colour, int idx);
void menu_radio_codec_helper_helper14_helper6_800407A4(MenuPrim *pGlue, int xpos, int ypos, int flags);
void menu_radio_codec_helper_helper14_helper4_800408BC(MenuPrim *pGlue, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7);
void menu_radio_codec_helper_helper15_80040B8C(MenuPrim *pGlue);
void menu_radio_codec_helper_helper14_80040DC4(MenuWork *work, int param_2);
void init_radio_message_board_80040F74(MenuWork *work);
void menu_radio_codec_helper__helper13_800410E4(MenuWork *work, char *string);
void sub_80041118(MenuWork *work);
int draw_radio_message(MenuWork *work, unsigned char *pOt);
void sub_8004124C(MenuWork *work);
int menu_radio_codec_helper_helper12_80041280(MenuWork *work, unsigned char *pOt, GV_PAD *pPad);
void draw_radio_wait_mark(MenuWork *work, unsigned char *pOt);
void menu_radio_init(MenuWork *work);
void menu_radio_kill(MenuWork *work);
// void MENU_RadioCall(int param_1, int param_2, int param_3);
void MENU_SetLoad(int procNameHashed, int param_2, short param_3);
// void MENU_ResetCall(void);
// void MENU_SetRadioCallbackProc(int proc_id);
void menu_number_init(MenuWork *work);
void menu_number_kill(MenuWork *work);
// void _menu_number_draw(MenuPrim *pOt, TextConfig *pSettings, int number);
// void _menu_number_draw_string(MenuPrim *pGlue, TextConfig *pTextConfig, const char *str);
void menu_number_draw_magazine(MenuWork *work, unsigned int *pOt, int xoff, int yoff, int pMagSize, int pAmmo, int pSubCnt2);
int menu_number_draw(MenuWork *work, unsigned int *pOt, int xpos, int ypos, int number, int flags);
int menu_number_draw_number2(MenuWork *work, int xpos, int ypos, int current, int total);
int menu_number_draw_string(MenuWork *work, unsigned int *pOt, int xpos, int ypos, const char *str, int flags);
void menu_set_string2(void);
// void _menu_number_draw_string2(MenuPrim *pGlue, TextConfig *pTextConfig, const char *str);
// void menu_restore_nouse(void);
// void menu_init_nouse(void);
void menu_draw_nouse(MenuPrim *pGlue, int offset_x, int offset_y);
void menu_draw_frozen(MenuPrim *pGlue, int offset_x, int offset_y);
void menu_draw_triangle(MenuPrim *pGlue, Menu_Triangle *pTriangle);

// from game/jimctrl.c
void *menu_radio_codec_helper_helper17_80038678(void);

#endif // __MGS_MENU_RADIO_H__
