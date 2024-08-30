#ifndef _MENUMAN_H
#define _MENUMAN_H

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "libgv/libgv.h"
#include "Font/font.h"
#include "face.h"
#include "memcard/memcard.h"

#define UNTAG_PTR(Type, Ptr) (Type *)((unsigned int)Ptr & 0x7FFFFFFF)

typedef struct
{
    const char *field_0_weapon_name;
    int         field_4_rpk_idx;
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

#define MENU_ITEM_COUNT  21
#define MENU_WEAPON_COUNT 11

typedef struct menu_chara_struct_sub
{
  // 1 = field_14_face_anim is FACE_ANIM_SIMPLE
  // 2 = field_14_face_anim is FACE_ANIM_FULL
  short          field_0_animState;

  unsigned short field_2_chara;
  short          field_4;
  short          field_6;
  short          field_8_animFrameNum;
  short          field_A;
  short          field_C;
  short          field_E;
  short          field_4C_leftCodecPortraitFrame; // Animation frame of left/right Codec portrait, valid values 0-3.
  short          field_12;
  face_anim      field_14_face_anim;
} menu_chara_struct_sub;

typedef struct menu_chara_struct
{
    int            field_0_state;
    int            field_4;
    char          *field_8_radioDatFragment;
    unsigned char *field_C_pScript;
    void          *field_10_subtitles;    // Points to subtitle data.
    int            field_14_bInExecBlock; // to prevent re-entering?
    unsigned short field_18;
    short          field_1A_index;
    char          *field_1C_radioDatFragment;
    faces_group   *field_20_pFacesGroup;
    void          *field_24_pImgData256;
    int           *field_28_pStack;
    short         *field_2C_pSaveText;
    int            field_30_face_count;
    face_header   *field_34_faces;
    int            field_38;
    menu_chara_struct_sub field_3C[2];
} menu_chara_struct;

typedef struct PANEL_TEXTURE
{
    u_long       *field_0_pixels;
    u_long       *field_4_word_ptr_pixels;
    signed char   field_8_bufid;
    signed char   field_9_xofs;
    signed char   field_A_yofs;
    char          field_B_pad;
    unsigned long field_C_uvclut;
    short         field_10_w;
    short         field_12_h;
} PANEL_TEXTURE;

typedef struct menu_0x14
{
  short field_0_bUnknown;
  short field_2_bTaskWup;
  int field_4_chara;
  int field_8_code;
  int field_C;
  menu_chara_struct *field_10_pCharaStru;
} menu_0x14;

typedef struct array_800BD748_child
{
    char           field_0_u;
    char           field_1_v;
    short          field_2_clut;
    PANEL_TEXTURE *field_4_panelTexture;
    RECT           field_8_rect1;
    RECT           field_10_rect2;
} array_800BD748_child;

void menuman_init_80038954(void);

struct MenuWork;
struct Menu_Inventory;
struct PANEL;
struct PANEL_CONF;

typedef void (*PANEL_CONF_update)(struct MenuWork *, unsigned int *, int, int, struct PANEL *);
typedef void (*PANEL_CONF_fn2)(struct PANEL_CONF *, int, int*, int*);

typedef struct PANEL_CONF
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
    PANEL_CONF_fn2       field_10_pFn2;
    PANEL_CONF_fn2       field_14_pFn2;
    PANEL_CONF_update field_18_pFnUpdate;
} PANEL_CONF;

typedef void (*TMenuSaveModeDataUnknownFn1)(char *, struct mem_card *, int, int);
typedef void (*TMenuSaveModeDataUnknownFn2)(char *, char *);
typedef void (*TMenuSaveModeDataUnknownFn3)(char *);

typedef struct DATA_INFO
{
  char                        field_0[2];
  char                        field_2;
  char                        field_3;
  const char                 *field_4_name; // "SAVE DATA", "SAVE PHOTO"
  TMenuSaveModeDataUnknownFn1 field_8;
  TMenuSaveModeDataUnknownFn2 make_menu;
  TMenuSaveModeDataUnknownFn3 field_10;
} DATA_INFO;

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

typedef struct PANEL
{
    short field_0_id;
    short field_2_num;
    short field_4_pos;
    short field_6_current;
} PANEL;

typedef struct Menu_Item_Unknown
{
    Menu_Item_Unknown_Main       field_0_main;
    PANEL field_20_array[0];
} Menu_Item_Unknown;

typedef struct Menu_Inventory
{
    PANEL              field_0_current;
    PANEL_CONF        *field_8_panel_conf;
    Menu_Item_Unknown *field_C_alloc;
    char               field_10_state;
    signed char        field_11; // item_idx ?
    // Current frame of the "flashing" animation played when the menu is closed, counts down from 0xa to 0x0.
    unsigned short     field_12_flashingAnimationFrame;
} Menu_Inventory;

typedef struct
{
    DR_ENV  dr_env[ 2 ]; // 0x00
    RECT    clip_rect; // 0x80
    DR_ENV  org_env[ 2 ]; // 0x88
    // Radar X offset from default X position (not from top of screen).
    short   pos_x; // 0x108
    // Radar Y offset from default Y position (not from left of screen).
    short   pos_y; // 0x10A
    // Health bar display countdown from 0x96 to 0x0, handled by 8003F530():
    // - 0x8003f784: resets the countdown to 0x96;
    // - 0x8003f7a0: decrements the value.
    char    display_flag; // 0x10C
    char    prev_mode; // 0x10D
    short   counter; // 0x10E
} RADAR_T;

struct MenuWork;

typedef void (*TMenuUpdateFn)(struct MenuWork *, unsigned char *); // todo
typedef void (*ButtonStates)(void); // todo

typedef struct MenuPrimBuffer
{
    unsigned char *mFreeLocation;
    unsigned char *mOt;
    unsigned char *mOtEnd;
} MenuPrimBuffer;

typedef struct MenuPrim
{
    MenuPrimBuffer mPrimBuf;
    unsigned char *mPrimPtrs[2];
} MenuPrim;

typedef struct _Menu_rpk_item
{
    char   field_0_x;
    char   field_1_y;
    char   field_2_w;
    char   field_3_h;
    u_long field_4_pixel_ptr[0];
} Menu_rpk_item;

// This struct describes the structure of
// ".rpk" files (".rpk", 'r', 0x72). Note
// that 'r' (0x72) can be either a ".rar",
// ".res" or ".rpk" file.
typedef struct
{
    unsigned char  field_0_count1;
    unsigned char  field_1_count2;
    short          pad;
    Menu_rpk_item *items[0]; // pointers ??
} RpkHeader;

typedef struct _MENU_BAR_CONF
{
    const char   *field_0_text;
    unsigned char field_4_rgb_left[3];
    unsigned char field_7_rgb_right[3];
    short         field_A_bar_height;
} MENU_BAR_CONF;

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

struct MenuWork;
typedef void (*TInitKillFn)(struct MenuWork *);

enum
{
    MENUFLAGS_CAN_OPEN_RIGHT_MENU = 0x2,
    MENUFLAGS_CAN_OPEN_LEFT_MENU = 0x4,
    MENUFLAGS_CAN_SEE_RADAR = 0x8,
    MENUFLAGS_CAN_OPEN_CODEC = 0x10
};

enum // MenuWork->field_2C_modules
{
    MENU_LIFE = 0,       // Life bars
    MENU_WEAPON = 1,     // Weapons inventory
    MENU_ITEM = 2,       // Items inventory
    MENU_RADAR = 3,      // Radar
    MENU_RADIO = 4,      // Codec
    MENU_CARD = 5,       // Memcard ?
    MENU_JIMAKU = 6,     // Subtitle
    MENU_VIEWER = 7,     // Photo viewer
};
#define MENU_MODULE_MAX 8

typedef unsigned char MenuFlags;

typedef struct             MenuWork
{
    GV_ACT                 actor;
    MenuPrim              *field_20_otBuf;
    GV_PAD                *field_24_pInput; // Points to 0x800b05e0, ie gPad1_800B05C0[2].
    MenuFlags              field_28_flags;
    char                   field_29;
    // Bit 0: browsing right menu.
    // Bit 1: browsing left menu.
    // Bit 2: using Codec.
    unsigned char          field_2A_state;
    char                   field_2B;
    TMenuUpdateFn          field_2C_modules[ MENU_MODULE_MAX ];
//    int                    field_48;
    DR_ENV                 field_4C_drawEnv[ 2 ];
    RADAR_T                field_CC_radar_data;
    Menu_Inventory         field_1DC_menu_item;
    Menu_Inventory         field_1F0_menu_weapon;
    MenuMan_MenuBars       field_204_bars;
    short                  field_210;
    short                  field_212;
    KCB                   *field_214_font;
    menu_chara_struct     *field_218;
    int                    field_21C;
} MenuWork;

// here or jimctl.h?
typedef struct UnkJimakuStruct // @ 800BDA70
{
    char field_0_active; // if true, display on screen and count down timer
    char field_1_type; // 0, 1, 2? - 1: pause
    short field_2_timer; // how many frames to be active
    short field_4_x; // location on screen
    short field_6_y;
    short field_8_w;
    short field_A_h;
    KCB field_C_font;
    char *field_38_str; // the string to display
    int field_3C; // hashed proc name used as first arg to GCL_ExecProc_8001FF2C
    char *field_40; // char * gcl string?
    // int field_44 // padding?
} UnkJimakuStruct;

typedef struct MenuCallbackProc_800ABB08
{
    int procNameHashed;
    short type;
    short param2;
} MenuCallbackProc_800ABB08;

enum TextConfig_Flags
{
    TextConfig_Flags_eRightAlign_01 = 0x01,
    TextConfig_Flags_eCentreAlign_02 = 0x02,
    TextConfig_Flags_eLargeFont_10 = 0x10,
    TextConfig_Flags_eSemiTransparent_20 = 0x20,
    TextConfig_Flags_ePadding_40 = 0x40,
};

typedef struct TextConfig
{
    int xpos;
    int ypos;
    int flags;
    int colour;
} TextConfig;

typedef struct Menu_Triangle
{
    short        field_0_x0;
    short        field_2_y0;
    short        field_4_x1;
    short        field_6_y1;
    short        field_8_x2;
    short        field_A_y2;
    unsigned int field_C_rgb;
} Menu_Triangle;

PANEL_TEXTURE *menu_weapon_get_weapon_rpk_info_8003DED8(int weaponIdx);
Menu_rpk_item            **menu_rpk_init_8003DD1C(const char *pFileName);
void                       menu_restore_nouse_80043470();
PANEL_TEXTURE *menu_rpk_8003B5E0(int idx);
void         sub_8003CB98(struct MenuWork *a1);
int          menu_radio_do_file_mode_8004C418(MenuWork *work, GV_PAD *pPad);
void         sub_8003CFE0(PANEL_TEXTURE *images, int index);
void         draw_life_defaultX_8003F408(MenuPrim *prim, long y, long rest, long now, long max, MENU_BAR_CONF *bconf);
void         draw_life_8003F464(MenuPrim *prim, long x, long y, long rest, long now, long max, MENU_BAR_CONF *bconf);
void         menu_draw_bar_8003ED4C(MenuPrim *prim, long x, long y, long rest, long now, long max, MENU_BAR_CONF *bconf);
void         MENU_InitRadioTable_80049644();
void         set_sprt_default_8004AE14(SPRT *pSprt);
void         move_coord_8004A494(int *arr, int len);
void         MENU_ResetSystem_80038A88(void);
void         MENU_SetRadarScale_80038E28(int);
void         MENU_StartDeamon_80038A20(void);
void         menu_Text_Init_80038B98(void);
void         menu_Text_PrimUnknown_80038BB4(void);
void         menu_init_nouse_800434A8(void);
void         menu_init_rpk_item_8003DDCC(PANEL_TEXTURE *pUnk, int imgIdx, int palIdx);
int          menu_draw_num_80038D10(int number);

void menu_radio_draw_face_helper_800470F4(int idx);
void menu_radio_draw_face_helper2_800486F4(menu_chara_struct_sub *pSub, int idx);
void menu_radio_draw_face_helper3_800487DC(menu_chara_struct *pStru, int idx);
void menu_radio_draw_face_helper4_80048868(MenuPrim *prim, menu_chara_struct_sub *a2, int idx);
void menu_radio_draw_face_helper5_8004896C(MenuPrim *prim, menu_chara_struct_sub *a2, int idx);
void menu_radio_draw_face_helper6_800486A0(menu_chara_struct_sub *a1, int idx);

void menu_item_helper_8003B8F0(struct MenuWork *work, unsigned int *pOt, int xpos, int ypos, Menu_Inventory *pMenuSub);
void menu_item_update_8003C95C(struct MenuWork *menuMan, unsigned int *param_2);
void menu_item_update_helper2_8003BF1C(MenuWork *work, unsigned int *arg1);
void menu_item_update_helper3_8003C24C(Menu_Item_Unknown *, unsigned short);
void menu_item_update_helper4_8003C4EC();
void menu_inventory_right_init_items_8003DE50(void);
void menu_jimaku_act_80048FD4(MenuWork *work, unsigned int *pOt);
void MENU_JimakuWrite_800494E8(char *str, int frames);
void _menu_number_draw_80042988(MenuPrim *pOt, TextConfig *pSettings, int number);
void _menu_number_draw_string2_80043220(MenuPrim *pGlue, TextConfig *pTextConfig, const char *str);
void _menu_number_draw_string_80042BF4(MenuPrim *pGlue, TextConfig *pTextConfig, const char *str);
void menu_weapon_init_helper_8003E0E8(MenuWork *param_1, unsigned int *param_2, int param_3, int param_4, PANEL *param_5);
void menu_weapon_unknown_8003DEB0(void);
void menu_weapon_update_8003E990(struct MenuWork *menuMan, unsigned char *param_2);
int  menu_8003DA9C(struct Menu_Inventory *pMenu, GV_PAD *pPad);
void menu_sub_8003B568(void);
int  sub_8003DAFC(Menu_Inventory *pLeftRight, GV_PAD *pPad);
int  sub_8003D52C(void);
void sub_8003D6CC(Menu_Inventory *pLeftRight, GV_PAD *pPad);
void sub_8003DA60(struct MenuWork *work, unsigned int *pOt, Menu_Inventory *pLeftRight, int off1, int off2);
void menu_viewer_init_80044A70(MenuWork *);
void menu_viewer_kill_80044A90(MenuWork *work);
void menuman_act_800386A4(MenuWork *);
void menuman_kill_800387E8(MenuWork *);
void sub_8003CE40(PANEL_TEXTURE *, int);
void sub_8003D6A8(struct Menu_Inventory *pMenuLeft, int bIsRight, void *pUpdateFn);
void sub_8003EBDC(struct MenuWork *a1);
void menu_radio_load_palette_80046B74(void *image, int idx);
void sub_80046B10(face_anim_image *image, int idx);
void sub_80046BD8(int idx);
int sub_80046C90(menu_chara_struct_sub *pSub, int idx, face_full_anim *pFullAnim, int pFrameNum);
void menuman_Reset_800389A8(void);
void menu_life_update_8003F530(MenuWork *work, unsigned char *pOt);
void draw_player_life_8003F4B8(MenuPrim *prim, long x, long y);
void init_file_mode_helper_8004A424(int param_1);
void init_file_mode_helper_helper_80049EDC(void);
void init_file_mode_helper2_8004A800(void);
void sub_80047CB4(menu_chara_struct *unknown);
void NewJimakuStr_8004955C(char *str, int int_1);
void NewJimaku_800495A8(void);
void MENU_ClearRadioTable_8004967C(void);
void menu_RadioCall_80042730(int param_1, int param_2, int param_3);
void MENU_ResetCall_80042814(void);
void MENU_SetRadioCallbackProc_8004283C(int param_1);
void MENU_SetRadioBaseCall_80049764(int contactFrequency, int radioTableCode);
void MENU_SetRadioOverCall_80049794(int contactFrequency, int radioTableCode);
void MENU_InitRadioMemory_8004E0EC(void);
void menu_radio_update_helper_80038A6C(void);
TILE          *menu_render_rect_8003DB2C(MenuPrim *pOt, int x, int y, int w, int h, int rgb);
Menu_rpk_item *menu_rpk_get_img_8003DDB4(int id);
Menu_rpk_item *menu_rpk_get_pal_8003DD9C(int id);
void           MENU_JimakuClear_80049518(void);
void           MENU_Locate_80038B34(int xpos, int ypos, int flags);
void           MENU_Color_80038B4C(int r, int g, int b);
void           menu_radio_codec_start_task_80047C3C(void);
void           menu_life_init_8003F7E0(MenuWork *work);
RadioMemory   *menu_radio_table_find_8004D380(int toFind);
RadioMemory   *menu_radio_table_next_free_8004D3B8(void);
unsigned char *menu_gcl_read_word_80047098(int *pOut, unsigned char *pScript);
void           MENU_SetRadioMemory_8004E110(int varId, const char *pVarName);
void           menu_gcl_set_radio_var_80047768(menu_chara_struct *unknown, unsigned char *pScript);
unsigned char *menu_gcl_exec_block_800478B4(menu_chara_struct *unknown, unsigned char *pScript);
int            menu_item_IsItemDisabled_8003B6D0(int item_idx);
void           MENU_ResetTexture_80038A00(void);
void           menu_jimaku_init_helper_800493F8(KCB *kcb);
void           menu_font_kill_helper_8003F50C(void);
void           menu_radio_8004D2FC(DATA_INFO *pSaveMode);
int            menu_radio_8004D334(GV_PAD *pPad);
void           menu_radio_8004D35C(void);
void           menu_panel_free_8003D184(Menu_Item_Unknown *pPanel);
void           menu_font_kill_8003FC0C(void);
void           AssignXY_8003D1A8(PANEL *pArray, int idx, short amount);
int            menu_panel_8003D2BC(Menu_Item_Unknown *, int);
void           sub_8003D520(void);
int            sub_8003F84C(int);
void           sub_8003F97C(char *param_1);
void           sub_8004CF20(int code, char **param_2, char **param_3);
void           sub_80048124(void);
void           sub_800469F0(menu_chara_struct *pStru);
void           menu_8003F9B4(MenuWork *work, unsigned int *pOt, const char *str);
void           MENU_DrawBar_80038D74(int xpos, int ypos, int rest, int now, MENU_BAR_CONF *bconf);
void           MENU_DrawBar2_80038DE0(int ypos, int rest, int now, int max, MENU_BAR_CONF *bconf);

void sub_8003D594(PANEL_CONF *pPanelConf, int pos, int *xoff, int *yoff);
void sub_8003D5F0(PANEL_CONF *pPanelConf, int pos, int *xoff, int *yoff);
void sub_8003D64C(PANEL_CONF *pPanelConf, int pos, int *xoff, int *yoff);

void sub_8004D008(char *outStr, mem_card *pMemcard, int arg2, int arg3);
void sub_8004D14C(char *outstr, char *param_2);
void sub_8004D1D0(char *saveBuf);

Menu_Item_Unknown * menu_alloc_panel_8003D124(int count);

void AssignXYFromVec_8003D1B8(PANEL *pArray, PANEL *pOther);

#ifdef _BUILDING_MENUMAN_
int MENU_Printf_80038C38(const char *fmt, const char *str, int param_3, int param_4, int param_5);
#else
int MENU_Printf_80038C38(const char *fmt, ...);
#endif

// For MenuPrim
#define _NEW_PRIM(prim, buf)                               \
    {                                                      \
        typeof(prim) p;                                    \
        p = (typeof(prim))buf->mPrimBuf.mFreeLocation;     \
        buf->mPrimBuf.mFreeLocation += sizeof(*prim);      \
        prim = p;                                          \
    }

// For MenuMan
#define NEW_PRIM(prim, buf) _NEW_PRIM(prim, buf->field_20_otBuf)

#endif // _MENUMAN_H
