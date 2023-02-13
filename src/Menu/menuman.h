#ifndef _MENUMAN_H
#define _MENUMAN_H

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>
#include "libgv/libgv.h"
#include "Font/font.h"
#include "data/data/data.h" // needed for TextConfig struct. move those structs to an actual header

#define UNTAG_PTR(Type, Ptr) (Type *)((unsigned int)Ptr & 0x7FFFFFFF)

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

typedef struct radio_table_entry
{
  int field_0_contactFrequency;
  int field_4_radioTableCode;
} radio_table_entry;

typedef struct radio_table
{
  radio_table_entry field_0_entries[8];
} radio_table;

#define RADIO_MEMORY_COUNT     16

#define MENU_ITEMS_LEFT_COUNT  21
#define MENU_ITEMS_RIGHT_COUNT 11

typedef struct menu_chara_struct_sub
{
  short field_0_state;
  unsigned short field_2_chara;
  short field_4;
  short field_6;
  short field_8;
  short field_A;
  short field_C;
  short field_E;
  short field_4C_leftCodecPortraitFrame; // Animation frame of left/right Codec portrait, valid values 0-3.
  short field_12;
  void *field_14;
} menu_chara_struct_sub;

typedef struct menu_chara_struct
{
    int            field_0_state;
    int            field_4;
    void          *field_8;
    unsigned char *field_C_pScript;
    void          *field_10_subtitles;    // Points to subtitle data.
    int            field_14_bInExecBlock; // to prevent re-entering?
    unsigned short field_18;
    unsigned short field_1A;
    void          *field_1C;
    void*           field_20_pFaceMemory;
    void          *field_24_pImgData256;
    int           *field_28_pStack;
    short          *field_2C_pSaveText;
    int            field_30_face_data_num;
    void         **field_34;
    int            field_38;
    menu_chara_struct_sub field_3C[2];
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

typedef struct menu_0x14
{
  short field_0_bUnknown;
  short field_2_bTaskWup;
  int field_4_chara;
  int field_8_code;
  int field_C;
  menu_chara_struct *field_10_pCharaStru;
} menu_0x14;

void menuman_init_80038954(void);

struct Actor_MenuMan;
struct menu_left_right;

typedef void (*menu_8009E544_update)(struct Actor_MenuMan *, int, int, int, struct menu_left_right *);

typedef struct menu_8009E544
{
    // X offset from left of screen.
    short field_0_xOffset;
    // Y offset from top of screen.
    short field_2_yOffset;
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

typedef struct menu_save_mode_data
{
  char field_0[2];
  char field_2;
  char field_3;
  void *field_4;
  void* field_8;
  void* field_C;
  void* field_10;
} menu_save_mode_data;

struct Menu_Item_Unknown;
typedef void (*TMenuItemUnknownFn)(struct Menu_Item_Unknown *, int);

typedef struct Menu_Item_Unknown_Main
{
    int                field_0_array_count;
    int                field_4_selected_idx;
    int                field_8;
    int                field_C;
    int                field_10;
    int                field_14_fn_ctx;
    int                field_18;
    TMenuItemUnknownFn field_1C_fn;
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
    Menu_Item_Unknown_Array_Item field_20_array[0];
} Menu_Item_Unknown;

typedef struct menu_left_right // aka MenuMan_Inventory_Menu_0x14
{
    Menu_Item_Unknown_Array_Item field_0;
    struct menu_8009E544        *field_8_pStru;
    struct Menu_Item_Unknown    *field_C_alloc;
    char                         field_10_state;
    signed char                  field_11; // item_idx ?
    // Current frame of the "flashing" animation played when the menu is closed, counts down from 0xa to 0x0.
    short field_12_flashingAnimationFrame;
} menu_left_right;

typedef struct menu_radar_data {
    DR_ENV        field_0[2]; // offset CC in Actor_MenuMan
    RECT          field_80;   // offset 14C in Actor_MenuMan
    DR_ENV        field_88;   // offset 154 in Actor_MenuMan
    DR_ENV        field_C8;   // offset 194 in Actor_MenuMan

    // Radar X offset from default X position (not from top of screen).
    short field_108_radarXOffsetFromDefault; // offset 1D4 in Actor_MenuMan

    // Radar Y offset from default Y position (not from left of screen).
    short field_10A_radarYOffsetFromDefault; // offset 1D6 in Actor_MenuMan
} menu_radar_data;

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
    u_char      field_0_state;
    u_char      field_1_O2_hp;
    short int field_2_bar_x;
    short int field_4_bar_y;
    short int field_6_snake_hp;
    short int field_8;
    short int field_A_k10_decrement;
} MenuMan_MenuBars;

struct Actor_MenuMan;
typedef void (*TInitKillFn)(struct Actor_MenuMan *);

enum
{
    MENUFLAGS_CAN_OPEN_RIGHT_MENU = 0x2,
    MENUFLAGS_CAN_OPEN_LEFT_MENU = 0x4,
    MENUFLAGS_CAN_SEE_RADAR = 0x8,
    MENUFLAGS_CAN_OPEN_CODEC = 0x10
};

typedef unsigned char MenuFlags;

typedef struct Actor_MenuMan
{
    Actor           field_0_actor;
    MenuGlue       *field_20_otBuf;
    GV_PAD           *field_24_pInput; // Points to 0x800b05e0, ie gPad1_800B05C0[2].
    MenuFlags       field_28_flags;
    char            field_29;
    // Bit 0: browsing right menu.
    // Bit 1: browsing left menu.
    // Bit 2: using Codec.
    unsigned char field_2A_state;
    char          field_2B;
    TMenuUpdateFn m7FnPtrs_field_2C[7];
    int           field_48;
    DR_ENV        field_4C_drawEnv[2];
    menu_radar_data        field_CC_radar_data;
    // Health bar display countdown from 0x96 to 0x0, handled by 8003F530():
    // - 0x8003f784: resets the countdown to 0x96;
    // - 0x8003f7a0: decrements the value.
    char                   field_1D8_healthBarDisplayCountdown;
    char                   field_1D9;
    short                  field_1DA;
    struct menu_left_right field_1DC_menu_left;
    struct menu_left_right field_1F0_menu_right;
    MenuMan_MenuBars       field_204_bars;
    short                  field_210;
    short                  field_212;
    KCB                   *field_214_font;
    menu_chara_struct     *field_218;
    int                    field_21C;
    // Some kind of radar horizontal stretch value.
    int field_220;
} Actor_MenuMan;

// here or jimctl.h?
typedef struct UnkJimakuStruct // @ 800BDA70
{
    char field_0_active; // if true, display on screen and count down timer
    char field_1_type; // 0, 1, 2? - 1: pause
    short field_2_timer; // how many frames to be active
    int field_4_x; // location on screen
    int field_8_y;
    KCB field_C_font;
    const char *field_38_str; // the string to display
    int field_3C; // hashed proc name used as first arg to GCL_ExecProc_8001FF2C
    int field_40; // char * gcl string?
    // int field_44 // padding?
} UnkJimakuStruct;

MenuMan_Inventory_14h_Unk *menu_right_get_weapon_rpk_info_8003DED8(int weaponIdx);
Menu_rpk_item            **menu_rpk_init_8003DD1C(const char *pFileName);
void                       menu_restore_nouse_80043470();
MenuMan_Inventory_14h_Unk *menu_rpk_8003B5E0(int idx);
int                        sub_8003CB98(struct Actor_MenuMan *a1);
int          menu_radio_do_file_mode_8004C418(int param_1, GV_PAD *pPad);
int          sub_8003CFE0(MenuMan_Inventory_14h_Unk *images, int index);
unsigned int menu_8003F408(MenuGlue *ot, int xpos, int ypos, int a4, int a5, BarConfig *pConfig);
unsigned int menu_8003F464(MenuGlue *ot, int xpos, int ypos, int a4, int a5, int a6, BarConfig *pBarConfig);
unsigned int menu_bar_draw_8003ED4C(MenuGlue *pBuffer, int xpos, int ypos, int hp1, int hp2, int maxHp,
                                    BarConfig *pConfig);
void         menu_InitRadioTable_80049644();
void         menu_ResetSystem_80038A88();
void         menu_SetRadarScale_80038E28(int);
void         menu_StartDeamon_80038A20(void);
void         menu_Text_Init_80038B98(void);
void         menu_Text_PrimUnknown_80038BB4(void);
void         menu_init_nouse_800434A8(void);
void         menu_init_rpk_item_8003DDCC(MenuMan_Inventory_14h_Unk *pUnk, int imgIdx, int palIdx);


void menu_inventory_left_helper_8003B8F0(struct Actor_MenuMan *pActor, unsigned int *pOt, int xpos, int ypos, menu_left_right *pMenuSub);

void menu_inventory_left_update_8003C95C(struct Actor_MenuMan *menuMan, unsigned int *param_2);
void menu_inventory_right_init_items_8003DE50(void);
void menu_jimaku_act_80048FD4(Actor_MenuMan *pActor, unsigned int *pOt);
void menu_JimakuWrite_800494E8(const char *str, int frames);
void menu_number_draw_80042988(MenuGlue *pOt, TextConfig *pSettings, int number);
void menu_number_draw_string2_80043220(MenuGlue *pGlue, TextConfig *pTextConfig, char *str);
void menu_number_draw_string_80042BF4(MenuGlue *pGlue, TextConfig *pTextConfig, const char *str);
void menu_right_init_helper_8003E0E8(struct Actor_MenuMan *menuMan, unsigned int *param_2, int param_3, int param_4,
                                     short *param_5);
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
void sub_800469A4(KCB *param_1, char *param_2); // probably a font func, move if so
void menuman_Reset_800389A8(void);
void menu_bars_update_8003F530(Actor_MenuMan *pActor, unsigned char *ot);
void init_file_mode_helper_8004A424(int param_1);
void init_file_mode_helper_helper_80049EDC(void);
void init_file_mode_helper2_8004A800(void);
void sub_80047CB4(menu_chara_struct *unknown);
void NewJimakuStr_8004955C(const char *str, int int_1);
void NewJimaku_800495A8(void);
void menu_ClearRadioTable_8004967C(void);
void menu_RadioCall_80042730(int param_1, int param_2, int param_3);
void menu_ResetCall_80042814(void);
void menu_SetRadioCallbackProc_8004283C(int param_1);
void menu_SetRadioBaseCall_80049764(int contactFrequency, int radioTableCode);
void menu_SetRadioOverCall_80049794(int contactFrequency, int radioTableCode);
void menu_InitRadioMemory_8004E0EC(void);
TILE          *menu_render_rect_8003DB2C(MenuGlue *pOt, int x, int y, int w, int h, int rgb);
Menu_rpk_item *menu_rpk_get_img_8003DDB4(int id);
Menu_rpk_item *menu_rpk_get_pal_8003DD9C(int id);
void           menu_JimakuClear_80049518(void);
void           menu_Text_XY_Flags_80038B34(int xpos, int ypos, int flags);
void           menu_Color_80038B4C(int r, int g, int b);
void           menu_radio_codec_start_task_80047C3C(void);
void           menu_bars_init_8003F7E0(Actor_MenuMan *pActor);
RadioMemory   *menu_radio_table_find_8004D380(int toFind);
RadioMemory   *menu_radio_table_next_free_8004D3B8(void);
unsigned char *menu_gcl_read_word_80047098(int *pOut, unsigned char *pScript);
void           menu_SetRadioMemory_8004E110(int varId, const char *pVarName);
void           menu_gcl_set_radio_var_80047768(menu_chara_struct *unknown, unsigned char *pScript);
unsigned char *menu_gcl_exec_block_800478B4(menu_chara_struct *unknown, unsigned char *pScript);
int            menu_inventory_Is_Item_Disabled_8003B6D0(int item_idx);
void           menu_ResetTexture_80038A00(void);
void           menu_jimaku_init_helper_800493F8(KCB *kcb);
void           menu_font_kill_helper_8003F50C(void);
void           menu_radio_8004D2FC(menu_save_mode_data *pSaveMode);
int            menu_radio_8004D334(GV_PAD *pPad);
void           menu_radio_8004D35C(void);
void           menu_panel_free_8003D184(Menu_Item_Unknown *pPanel);
void           menu_font_kill_8003FC0C(void);
int            sub_8003CFE0(MenuMan_Inventory_14h_Unk *images, int index);
void           AssignXY_8003D1A8(Menu_Item_Unknown_Array_Item *pArray, int idx, short amount);
void           sub_8003D2BC(Menu_Item_Unknown *, short);
void           sub_8003D520(void);
int            sub_8003F84C(int);

Menu_Item_Unknown * menu_alloc_panel_8003D124(int count);

void AssignXYFromVec_8003D1B8(Menu_Item_Unknown_Array_Item *pArray, Menu_Item_Unknown_Array_Item *pOther);

#ifdef _BUILDING_MENUMAN_
int menu_Text_80038C38(const char *fmt, const char *str, int param_3, int param_4, int param_5);
#else
int menu_Text_80038C38(const char *fmt, ...);
#endif

#endif // _MENUMAN_H
