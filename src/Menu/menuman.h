#ifndef _MENUMAN_H
#define _MENUMAN_H

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "libgv/actor.h"
#include "util/idaTypes.h"
#include "data/data/data.h" // needed for TextConfig struct. move those structs to an actual header

#define MAX_HISTORY 8

#define UNTAG_PTR(Type, Ptr) (Type *)((unsigned int)Ptr & 0x7FFFFFFF)

typedef struct AreaHistory
{
    short history[MAX_HISTORY];
} AreaHistory;

typedef struct
{
    char *field_0_weapon_name;
    int   field_4_rpk_idx;
} menu_weapon_rpk_info;

typedef struct RadioMemory
{
    short frequency;
    char  name[18];
} RadioMemory;

#define RADIO_MEMORY_COUNT 16

extern RadioMemory gRadioMemory_800BDB38[RADIO_MEMORY_COUNT];

typedef struct menu_chara_struct
{
    int            field_0_state;
    int            field_4;
    int            field_8;
    unsigned char *field_C_pScript;
    int            field_10;
    int            field_14_bInExecBlock; // to prevent re-entering?
    unsigned short field_18;
    unsigned short field_1A;
    int            field_1C;
    int            field_20_pFaceMemory;
    int            field_24;
    int           *field_28_pStack;
    int            field_2C;
    int            field_30_face_data_num;
    int            field_34;
    int            field_38;
    short          field_3C;
    short          field_3E;
    int            field_40;
    int            field_44;
    int            field_48;
    int            field_4C;
    int            field_50;
    short          field_54;
    short          field_56;
    int            field_58;
    int            field_5C;
    int            field_60;
    int            field_64;
    int            field_68;
} menu_chara_struct;

typedef struct MenuMan_Inventory_14h_Unk
{
    unsigned char  *field_0_pixels;
    unsigned short *field_4_word_ptr_pixels;
    char            field_8_index;
    char            field_9_x;
    char            field_A_y;
    unsigned char   field_B; // Padding?
    unsigned char   field_C_u;
    unsigned char   field_D_v;
    short           field_E_clut;
    short           field_10_w;
    short           field_12_h;
} MenuMan_Inventory_14h_Unk;

RadioMemory   *menu_radio_table_find_8004D380(int toFind);
RadioMemory   *menu_radio_table_next_free_8004D3B8(void);
unsigned char *menu_gcl_read_word_80047098(int *pOut, unsigned char *pScript);
void           menu_SetRadioMemory_8004E110(int varId, const char *pVarName);
void           menu_gcl_set_radio_var_80047768(menu_chara_struct *unknown, unsigned char *pScript);
unsigned char *menu_gcl_exec_block_800478B4(menu_chara_struct *unknown, unsigned char *pScript);

void menuman_init_80038954(void);

struct Actor_MenuMan;
struct menu_left_right;

typedef void (*menu_8009E544_update)(struct Actor_MenuMan *, int, int, int, struct menu_left_right *);

typedef struct menu_8009E544
{
    // X offset from left of screen.
    short field_0;
    // Y offset from top of screen.
    short field_2;
    // 8003D6CC() reads this in the following instructions and, if the field is set to 0:
    // - @ 0x8003d700, it will not allow the menu to open;
    // - @ 0x8003d768, it will not allow the menu to remain open.
    int                  field_4_input;
    int                  field_8;
    int                  field_C;
    void                *field_10;
    void                *field_14;
    menu_8009E544_update field_18_pFnUpdate;
} menu_8009E544;

typedef struct Menu_Item_Unknown_Main
{
    int   field_0_array_count;
    int   field_4_selected_idx;
    int   field_8;
    int   field_C;
    int   field_10;
    int   field_14_fn_ctx;
    int   field_18;
    void *field_1C_fn;
} Menu_Item_Unknown_Main;

typedef struct Menu_Item_Unknown_Array_Item
{
    short field_0_item_id_idx;
    short field_2_current_amount;
    short field_4; // max amount ?
    short field_6;
} Menu_Item_Unknown_Array_Item;

typedef struct Menu_Item_Unknown
{
    Menu_Item_Unknown_Main       field_0_main;
    Menu_Item_Unknown_Array_Item field_20_array;
} Menu_Item_Unknown;

typedef struct menu_left_right // aka MenuMan_Inventory_Menu_0x14
{
    Menu_Item_Unknown_Array_Item field_0;
    struct menu_8009E544        *field_8_pStru;
    struct Menu_Item_Unknown    *field_C_alloc;
    char                         field_10; // state ?
    signed char                  field_11; // item_idx ?
    // Current frame of the "flashing" animation played when the menu is closed, counts down from 0xa to 0x0.
    short field_12;
} menu_left_right;

struct Actor_MenuMan;

typedef void (*TMenuUpdateFn)(struct Actor_MenuMan *, unsigned char *); // todo
typedef void (*ButtonStates)(void);                                     // todo

typedef struct MenuPrimBuffer
{
    unsigned char *mFreeLocation;
    unsigned char *mOt;
    unsigned char *mOtEnd;
} MenuPrimBuffer;

typedef struct MenuGlue
{
    MenuPrimBuffer mPrimBuf;
    unsigned char *mPrimPtrs[2];
} MenuGlue;

typedef struct _Menu_rpk_item
{
    char          field_0_x;
    char          field_1_y;
    char          field_2_w;
    char          field_3_h;
    unsigned char field_4_pixel_ptr[0];
} Menu_rpk_item;

typedef struct
{
    unsigned char  field_0_count1;
    unsigned char  field_1_count2;
    short          pad;
    Menu_rpk_item *items[0]; // pointers ??
} RpkHeader;

typedef struct BarConfig
{
    const char   *field_0_text;
    unsigned char field_4_rgb_left[3];
    unsigned char field_7_rgb_right[3];
    short         field_A_bar_height;
} BarConfig;

typedef struct MenuMan_MenuBars
{
    BYTE      field_0_state;
    BYTE      field_1_O2_hp;
    short int field_2_bar_x;
    short int field_4_bar_y;
    short int field_6_snake_hp;
    short int field_8;
    short int field_A_k10_decrement;
} MenuMan_MenuBars;

struct Actor_MenuMan;
typedef void (*TInitKillFn)(struct Actor_MenuMan *);

typedef struct Actor_MenuMan
{
    Actor           field_0_actor;
    MenuPrimBuffer *field_20_otBuf;
    int             field_24_pInput;
    // Bit 0: ?
    // Bit 1: can open right menu.
    // Bit 2: can open left menu.
    // Bit 4: can open codec.
    unsigned char field_28_flags;
    char          field_29;
    // Bit 0: browsing right menu.
    // Bit 1: browsing left menu.
    // Bit 2: using codec.
    unsigned char field_2A_state;
    char          field_2B;
    TMenuUpdateFn m7FnPtrs_field_2C[7];
    int           field_48;
    DR_ENV        field_4C_drawEnv[2];
    DR_ENV        field_CC[2];
    int           field_14C; // RECT ?
    int           field_150;
    DR_ENV        field_154;
    DR_ENV        field_194;
    // Radar X offset from default X position (not from top of screen).
    short field_1D4_clipX1;
    // Radar Y offset from default Y position (not from left of screen).
    short field_1D6_clipY1;
    // Health bar display countdown from 0x96 to 0x0, handled by 8003F530():
    // - 0x8003f784: resets the countdown to 0x96;
    // - 0x8003f7a0: decrements the value.
    char                   field_1D8;
    char                   field_1D9;
    char                   field_1DA;
    char                   field_1DB;
    struct menu_left_right field_1DC_menu_left;
    struct menu_left_right field_1F0_menu_right;
    MenuMan_MenuBars       field_204_bars;
    short                  field_210;
    short                  field_212;
    int                    field_214_font;
    menu_chara_struct     *field_218;
    int                    field_21C;
    // Some kind of radar horizontal stretch value.
    int field_220;
} Actor_MenuMan;

MenuMan_Inventory_14h_Unk *menu_right_get_weapon_rpk_info_8003DED8(int weaponIdx);
Menu_rpk_item **menu_rpk_init_8003DD1C(const char *pFileName);
int  menu_restore_nouse_80043470();
int  sub_8003B5E0(int a1);
int  sub_8003CB98(struct Actor_MenuMan *a1);
int menu_radio_do_file_mode_8004C418(int param_1, unsigned short *param_2, int param_3, void *param_4);
int sub_8003CFE0(unsigned int **images, int index);
unsigned int menu_8003F408(MenuGlue *ot, int xpos, int ypos, int a4, int a5, BarConfig *pConfig);
unsigned int menu_8003F464(MenuGlue *ot, int xpos, int ypos, int a4, int a5, int a6, BarConfig *pBarConfig);
unsigned int menu_bar_draw_8003ED4C(MenuGlue *pBuffer, int xpos, int ypos, int hp1, int hp2, int maxHp, BarConfig *pConfig);
void menu_InitRadioTable_80049644();
void menu_ResetSystem_80038A88();
void menu_SetRadarScale_80038E28(int);
void menu_StartDeamon_80038A20(void);
void menu_Text_Init_80038B98(void);
void menu_Text_PrimUnknown_80038BB4(void);
void menu_init_nouse_800434A8(void);
void menu_init_rpk_item_8003DDCC(MenuMan_Inventory_14h_Unk *pUnk, int imgIdx, int palIdx);
void menu_inventory_left_helper_8003B8F0(struct Actor_MenuMan *menuMan, unsigned int *param_2, int param_3, int param_4, short *param_5);
void menu_inventory_left_update_8003C95C(struct Actor_MenuMan *menuMan, unsigned int *param_2);
void menu_inventory_right_init_items_8003DE50(void);
void menu_jimaku_act_80048FD4(Actor_MenuMan *pActor, unsigned int *pOt);
void menu_number_draw_80042988(MenuGlue *pOt, TextConfig *pSettings, int number);
void menu_number_draw_string2_80043220(MenuGlue *param_1, int *param_2, char *param_3);
void menu_number_draw_string_80042BF4(MenuGlue *param_1, int *param_2, char *param_3);
void menu_right_init_helper_8003E0E8(struct Actor_MenuMan *menuMan, unsigned int *param_2, int param_3, int param_4, short *param_5);
void menu_right_unknown_8003DEB0(void);
void menu_right_update_8003E990(struct Actor_MenuMan *menuMan, unsigned char *param_2);
void menu_sub_8003B568(void);
void menu_viewer_init_80044A70(Actor_MenuMan *);
void menu_viewer_kill_80044A90(Actor_MenuMan *pActor);
void menuman_act_800386A4(Actor_MenuMan *);
void menuman_kill_800387E8(Actor_MenuMan *);
void sub_8003CE40(MenuMan_Inventory_14h_Unk *, int);
void sub_8003D6A8(struct menu_left_right *pMenuLeft, int bIsRight, void *pUpdateFn);
void sub_8003EBDC(struct Actor_MenuMan *a1);
void sub_800469A4(int param_1, char *param_2); // probably a font func, move if so
void menu_bars_update_8003F530(Actor_MenuMan *pActor, unsigned char *ot);
void init_file_mode_helper_8004A424(int param_1);
void init_file_mode_helper2_8004A800(void);
void sub_80047CB4(menu_chara_struct *unknown);
int  NewJimakuStr_8004955C(char *, int);
void NewJimaku_800495A8(void);
void menu_ClearRadioTable_8004967C(void);
void menu_RadioCall_80042730(int param_1, int param_2, int param_3);
void menu_ResetCall_80042814(void);
void menu_SetRadioCallbackProc_8004283C(int param_1);
void menu_SetRadioBaseCall_80049764(int param_1, int param_2);
void menu_SetRadioOverCall_80049794(int param_1, int param_2);
void menu_InitRadioMemory_8004E0EC(void);
TILE *menu_render_rect_8003DB2C(MenuGlue *pOt, int x, int y, int w, int h, int rgb);
Menu_rpk_item *menu_rpk_get_img_8003DDB4(int idx);

#endif // _MENUMAN_H
