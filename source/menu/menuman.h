#ifndef __MGS_MENU_MENUMAN_H__
#define __MGS_MENU_MENUMAN_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "libgv/libgv.h"
#include "font/font.h"
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

enum ShapePalKeyState{
    SHAPE_STATE_NEUTRAL = 0,
    SHAPE_STATE_HOT = 1,
    SHAPE_STATE_COLD = 2
};

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
    short          field_E_eyesAnimFrame; // values 0-6.
    short          field_4C_mouthAnimFrame; // values 0-3.
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
    char          *stack;
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

typedef void (*TMenuSaveModeDataUnknownFn1)(char *, struct MEM_CARD *, int, int);
typedef void (*TMenuSaveModeDataUnknownFn2)(char *, char *);
typedef void (*TMenuSaveModeDataUnknownFn3)(char *);

typedef struct DATA_INFO
{
    char                        field_0[2];
    char                        field_2;
    char                        blocks_count;
    const char                 *field_4_name; // "SAVE DATA", "SAVE PHOTO"
    TMenuSaveModeDataUnknownFn1 make_title;
    TMenuSaveModeDataUnknownFn2 make_menu;
    TMenuSaveModeDataUnknownFn3 make_game_data;
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

typedef struct RPK_ITEM
{
    char   x, y, w, h;
    u_long data[0];
} RPK_ITEM;

// This struct describes the structure of
// ".rpk" files (".rpk", 'r', 0x72). Note
// that 'r' (0x72) can be either a ".rar",
// ".res" or ".rpk" file.
typedef struct RPK // resource pack?
{
    u_char    palettes;
    u_char    images;
    short     pad;
    RPK_ITEM *items[0];
} RPK;

typedef struct _MENU_BAR_CONF
{
    const char   *name;
    unsigned char left[3];
    unsigned char right[3];
    short         height;
} MENU_BAR_CONF;

enum MenuStatBarsState {
    BAR_STATE_HIDDEN = 0,
    BAR_STATE_MOVING_DOWN = 1,
    BAR_STATE_VISIBLE = 2,
    BAR_STATE_MOVING_UP = 3,
    BAR_STATE_FORCE_HIDE = 4
};

typedef struct MenuMan_MenuBars
{
    u_char      field_0_state;
    u_char      field_1_O2_hp;
    short int field_2_bar_x;
    short int field_4_bar_y;
    short int field_6_snake_hp;
    short int field_8_hide_bar_delay_counter;
    short int health_delay_counter;
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

enum MenuState
{
    MENU_CLOSED = 0,
    MENU_RIGHT_OPEN = 1,
    MENU_LEFT_OPEN = 2,
    MENU_CODEC_OPEN = 4
};

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
    short                  field_210_codec_state;
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
    int field_3C; // hashed proc name used as first arg to GCL_ExecProc
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
    TextConfig_Flags_eLeftAlign_00 = 0x00,
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
    int flags; // 0xF = alignement
    // the first byte is a flag or an offset (0x64 opaque, 0x65 semi-transparent)
    // the rest is BGR
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

/*---------------------------------------------------------------------------*/

/* menuman.c */
void menuman_act_800386A4(MenuWork *);
void menuman_kill_800387E8(MenuWork *);
void menu_init_subsystems_8003884C(MenuWork *work);
void menuman_init_80038954(void);
void menuman_Reset(void);
void MENU_ResetTexture(void);
void MENU_StartDeamon(void);
void menu_radio_update_helper_80038A6C(void);
void menu_radio_update_helper2_80038A7C(void);
void MENU_ResetSystem(void);
void MENU_Locate(int xpos, int ypos, int flags);
void MENU_Color(int r, int g, int b);
void menu_Text_Init_80038B98(void);
void menu_Text_PrimUnknown_80038BB4(void);
#ifdef _BUILDING_MENUMAN_
int MENU_Printf(const char *fmt, const char *str, int param_3, int param_4, int param_5);
#else
int MENU_Printf(const char *fmt, ...);
#endif
int menu_draw_num(int number);
MenuPrim *MENU_GetPrimInfo(void);
void MENU_DrawBar(int xpos, int ypos, int rest, int now, MENU_BAR_CONF *bconf);
void MENU_DrawBar2(int ypos, int rest, int now, int max, MENU_BAR_CONF *bconf);

/* radar.c */
void MENU_SetRadarScale(int);
// void MENU_SetRadarFunc(TRadarFn_800AB48C func);
// void draw_radar_vision_cone_80038F3C(MenuWork *work, char *ot, RADAR_CONE *cone, int x, int y, int color, int fadeColor, int scale);
// void drawBorder_800390FC(MenuWork *menuMan, unsigned char *ot);
// void drawMap_800391D0(MenuWork *work, unsigned char *ot, int arg2);
// void initSprt_80039D5C(SPRT *pSprt, int x, int y, radar_uv *pRadarUV, int rgb);
// void drawHeader_helper_helper_80039DB4(MenuPrim *prim, SPRT *pSprt, radar_uv *pRadarUV);
// void drawHeader_80039EC4(MenuPrim *pGlue, int y, int idx);
// void drawConsole_alertEvasion_8003A0BC(MenuPrim *prim, int code);
// void drawConsole_jamming_8003A2D0(MenuPrim *pGlue, int idx);
// void drawCounter_8003A664(MenuPrim *pGlue, int alertLevel, int code);
// void drawSymbols_8003A978(MenuPrim *prim, int x, int code);
// void drawAlertEvasionJammingPanel_8003AA2C(MenuWork *work, char *ot, int radarMode, int alertLevel);
// void menu_radar_load_rpk_8003AD64(void);
// void menu_init_radar_helper_8003ADAC(void);
// void menu_radar_helper_8003ADD8(MenuWork *work, int index);
// void draw_radar(MenuWork *work, unsigned char * pOt);
// void menu_radar_update_8003B350(MenuWork *work, unsigned char *ot);
// void menu_radar_init_8003B474(MenuWork *work);
// void menu_radar_kill_8003B554(MenuWork *work);

/* item.c */
void menu_sub_8003B568(void);
PANEL_TEXTURE *menu_rpk_8003B5E0(int idx);
void menu_item_printDescription_8003B614(int itemIndex);
int menu_item_IsItemDisabled_8003B6D0(int item_idx);
void menu_drawPalKey_8003B794(MenuWork *work, unsigned int *pOt, int id);
void menu_item_helper_8003B8F0(struct MenuWork *work, unsigned int *pOt, int xpos, int ypos, Menu_Inventory *pMenuSub);
void menu_8003BBEC(MenuWork *work);
int menu_item_update_helper_8003BCD4(MenuWork *work);
void menu_item_update_helper2_8003BF1C(MenuWork *work, unsigned int *arg1);
void UseConsumableItem_8003C24C(Menu_Item_Unknown *pPanels, unsigned short press);
void UpdateEnvironmentalEffects_8003C4EC(void);
void menu_item_update_8003C95C(struct MenuWork *menuMan, unsigned int *param_2);
void sub_8003CB98(MenuWork *work);
void menu_item_init_8003CBF0(MenuWork *work);
void menu_item_kill_8003CC74(MenuWork *work);
void MENU_ResetItemPos(void);

/* weapon.c */
void menu_texture_init_8003CC94(MenuWork *work);
void sub_8003CE40(PANEL_TEXTURE *, int);
void sub_8003CE78(void);
void sub_8003CE84(void);
void menu_draw_texture_8003CEF8(PANEL_TEXTURE *);
void sub_8003CFE0(PANEL_TEXTURE *images, int index);
// void sub_8003D070(PANEL_TEXTURE *pPanelTex, TIM *tim);
void menu_init_sprt_8003D0D0(SPRT *pPrim, PANEL_TEXTURE *pPanelTex, int offset_x, int offset_y);
Menu_Item_Unknown *menu_alloc_panel_8003D124(int count);
void menu_panel_free_8003D184(Menu_Item_Unknown *pPanel);
void AssignXY_8003D1A8(PANEL *pArray, int idx, short amount);
void AssignXYFromVec_8003D1B8(PANEL *pArray, PANEL *pOther);
void sub_8003D1DC(Menu_Item_Unknown *pMenuItem);
int menu_panel_8003D2BC(Menu_Item_Unknown *, int);
void sub_8003D34C(Menu_Item_Unknown *pItem, int a2);
void sub_8003D3A4(Menu_Item_Unknown *pItem, int a2);
void sub_8003D3FC(Menu_Item_Unknown *pMenu, int a2);
void sub_8003D44C(Menu_Item_Unknown *pMenu, int a2, int a3);
int sub_8003D4CC(Menu_Item_Unknown *pMenuItem);
void sub_8003D520(void);
int sub_8003D52C(void);
int menu_8003D538(void);
int sub_8003D568(void);
void sub_8003D594(PANEL_CONF *pPanelConf, int pos, int *xoff, int *yoff);
void sub_8003D5F0(PANEL_CONF *pPanelConf, int pos, int *xoff, int *yoff);
void sub_8003D64C(PANEL_CONF *pPanelConf, int pos, int *xoff, int *yoff);
void menu_set_panel_config_8003D6A8(struct Menu_Inventory *pMenuLeft, int bIsRight, void *pUpdateFn);
void menu_navigation_8003D6CC(Menu_Inventory *pLeftRight, GV_PAD *pPad);
void menu_8003D7DC(MenuWork *work, unsigned int *pOt, Menu_Inventory *pSubMenu);
void menu_sub_menu_update_8003DA0C(MenuWork *work, unsigned int *pOt, Menu_Inventory *pSubMenu);
void sub_8003DA60(struct MenuWork *work, unsigned int *pOt, Menu_Inventory *pLeftRight, int off1, int off2);
int menu_8003DA9C(struct Menu_Inventory *pMenu, GV_PAD *pPad);
int sub_8003DAFC(Menu_Inventory *pLeftRight, GV_PAD *pPad);
TILE *menu_render_rect_8003DB2C(MenuPrim *pOt, int x, int y, int w, int h, int rgb);
void Menu_item_render_frame_rects_8003DBAC(MenuPrim *pGlue, int x, int y, int param_4);
RPK_ITEM **menu_rpk_init_8003DD1C(const char *pFileName);
RPK_ITEM *menu_rpk_get_pal_8003DD9C(int id);
RPK_ITEM *menu_rpk_get_img_8003DDB4(int id);
void menu_init_rpk_item_8003DDCC(PANEL_TEXTURE *pUnk, int imgIdx, int palIdx);
void menu_inventory_right_init_items_8003DE50(void);
void menu_weapon_unknown_8003DEB0(void);
PANEL_TEXTURE *menu_weapon_get_weapon_rpk_info_8003DED8(int weaponIdx);
int menu_weapon_isWeaponDisabled_8003DF30(int weaponId);
void menu_weapon_printDescription_8003E030(int wpn_id);
void menu_weapon_init_helper_8003E0E8(MenuWork *param_1, unsigned int *param_2, int param_3, int param_4, PANEL *param_5);
void menu_weapon_update_helper2_helper2_8003E3B0(MenuWork *work);
int menu_weapon_update_helper_8003E4B8(MenuWork *work);
void menu_weapon_update_helper2_8003E674(MenuWork *work, unsigned int *pOt);
void menu_weapon_update_8003E990(struct MenuWork *menuMan, unsigned char *param_2);
void sub_8003EBDC(struct MenuWork *a1);
void menu_weapon_init_8003EC2C(MenuWork *work);
void menu_weapon_kill_8003ECAC(MenuWork *work);
void MENU_ResetWeaponPos(void);

/* life.c */
int menu_life_update_helper_8003ECCC(MenuMan_MenuBars *pBars);
void menu_draw_bar(MenuPrim *prim, long x, long y, long rest, long now, long max, MENU_BAR_CONF *bconf);
void menu_life_update_helper2_8003F30C(MenuPrim *prim, MenuMan_MenuBars *pBars);
void draw_life_defaultX_8003F408(MenuPrim *prim, long y, long rest, long now, long max, MENU_BAR_CONF *bconf);
void draw_life_8003F464(MenuPrim *prim, long x, long y, long rest, long now, long max, MENU_BAR_CONF *bconf);
void draw_player_life_8003F4B8(MenuPrim *prim, long x, long y);
void menu_font_kill_helper_8003F50C(void);
void menu_life_update_8003F530(MenuWork *work, unsigned char *pOt);
void menu_life_init_8003F7E0(MenuWork *work);
void menu_life_kill_8003F838(MenuWork *work);
int sub_8003F84C(int);
void menu_printDescription_8003F97C(char *description);
void menu_drawDescriptionPanel_8003F9B4(MenuWork *work, unsigned int *pOt, const char *str);
void menu_font_kill_8003FC0C(void);

/* radio.c */
// ...in radio.h
void MENU_RadioCall(int param_1, int param_2, int param_3);
void MENU_ResetCall(void);
void MENU_SetRadioCallbackProc(int proc_id);
void _menu_number_draw(MenuPrim *pOt, TextConfig *pSettings, int number);
void _menu_number_draw_string(MenuPrim *pGlue, TextConfig *pTextConfig, const char *str);
void _menu_number_draw_string2(MenuPrim *pGlue, TextConfig *pTextConfig, const char *str);
void menu_restore_nouse(void);
void menu_init_nouse(void);

/* debug.c */
void menu_viewer_init(MenuWork *work);
void menu_viewer_kill(MenuWork *work);

/* radiotex.c */
void sub_800469F0(menu_chara_struct *pStru);
void menu_radio_codec_helper_helper7_helper_80046A98(menu_chara_struct *pStru);
void LoadFaceAnimImage_80046B10(face_anim_image *image, int idx);
void menu_radio_load_palette_80046B74(void *image, int idx);
void sub_80046BD8(int idx);

/* radioanim.c */
int sub_80046C90(menu_chara_struct_sub *pSub, int idx, face_full_anim *pFullAnim, int pFrameNum);
void menu_radio_draw_face_helper_helper_80046DF4(int idx, menu_chara_struct *pChara, int chara, int code, int a5);
void menu_radio_codec_task_proc_helper_80046F3C(menu_chara_struct *pStru, faces_group *pFacesGroup);
unsigned char *menu_gcl_read_word_80047098(int *pOut, unsigned char *pScript);
void menu_800470B4(int idx, menu_chara_struct *pStru, int chara, int code, int faceUnk, int taskWup);
void menu_radio_draw_face_helper_800470F4(int idx);

/* radiomes.c */
void radio_anim_with_subtitles_800471AC(menu_chara_struct *unk, unsigned char *pScript);
void radio_anim_face_80047280(menu_chara_struct *unk, unsigned char *pScript);
void radio_voice_80047330(menu_chara_struct *unk, unsigned char *pScript);
void radio_sound_80047414(menu_chara_struct *unk, unsigned char *pScript);
unsigned char *radio_getNextValue_800474EC(int *retValue, unsigned char *pScript);
void radio_if_80047514(menu_chara_struct *unk, unsigned char *pScript);
void radio_switch_800475B8(menu_chara_struct *unk, unsigned char *pScript);
void radio_randSwitch_80047660(menu_chara_struct *unk, unsigned char *pScript);
void radio_eval_80047748(menu_chara_struct *unk, unsigned char *pScript);
void radio_add_contact_80047768(menu_chara_struct *unk, unsigned char *pScript);
void radio_memsave_800477B0(menu_chara_struct *unk, unsigned char *pScript);
void radio_prompt_8004780C(menu_chara_struct *unk, unsigned char *pScript);
void radio_varsave_80047838(menu_chara_struct *unk, unsigned char *pScript);
unsigned char *radio_moveToNext_80047880(menu_chara_struct *unk, unsigned char *pScript);
unsigned char *menu_gcl_exec_block_800478B4(menu_chara_struct *unknown, unsigned char *pScript);
void menu_radio_codec_task_proc_80047AA0(void);
void menu_radio_codec_start_task_80047C3C(void);
void ResetCharacterCodecStruct(menu_chara_struct *unknown);
void menu_radio_codec_create_state_80047CE4(MenuWork *menuMan);
void menu_radio_update_helper6_80047D40(MenuWork *work);
void sub_80047D70(MenuWork *work, int param_2, int pRadioCode);
void menu_radio_codec_helper_helper10_80047EFC(MenuWork *work, int param_2);
void menu_radio_codec_helper_helper3_80047F44(MenuWork *work, int param_2);
int menu_radio_codec_helper_helper9_80047FF4();
void menu_radio_codec_state_2_helper_80048024();
void menu_radio_codec_helper_helper8_80048044();
void menu_radio_codec_helper_helper7_80048080();
void ResetCodecState();

/* radiofacedraw.c */
void sub_80048124(void);
void radio_draw_face_frame(MenuPrim *pGlue, int x, int y, int w, int h);
void menu_radio_draw_face_helper6_800486A0(menu_chara_struct_sub *a1, int idx);
void menu_radio_draw_face_helper2_800486F4(menu_chara_struct_sub *pSub, int idx);
void menu_radio_draw_face_helper3_800487DC(menu_chara_struct *pStru, int idx);
void menu_radio_draw_face_helper4_80048868(MenuPrim *prim, menu_chara_struct_sub *a2, int idx);
void menu_radio_draw_face_helper5_8004896C(MenuPrim *prim, menu_chara_struct_sub *a2, int idx);
void menu_radio_draw_face(MenuWork *work, menu_chara_struct *chara_struct);
int menu_radio_end_check(void);

/* jimaku.c */
void menu_jimaku_act(MenuWork *work, unsigned int *pOt);
void menu_jimaku_init(MenuWork *work);
void MENU_JimakuWrite(char *str, int frames);
void MENU_JimakuClear(void);
void MENU_AreaNameWrite(char *areaName);
void NewJimakuStr(char *str, int int_1);
void NewJimaku(void);

/* radiotable.c */
void MENU_InitRadioTable(void);
void MENU_ClearRadioTable(void);
radio_table_entry *sub_8004969C(radio_table *pRadioTable, int contactFrequency);
void MENU_SetRadioBaseCall(int contactFrequency, int radioTableCode);
void MENU_SetRadioOverCall(int contactFrequency, int radioTableCode);
int MENU_GetRadioCode(int param_1);

/* datasave.c */
void move_coord(int *arr, int len);
int menu_radio_do_file_mode(MenuWork *work, GV_PAD *pPad);
void init_file_mode(DATA_INFO *pSaveMode, int param_2);
void menu_radio_init_save_mode(int param_1, int param_2);
void menu_radio_update_helper4_8004D2D0(int param_1);
void menu_radio_8004D2FC(DATA_INFO *pSaveMode);
int menu_radio_8004D334(GV_PAD *pPad);
void menu_radio_8004D35C(void);

/* radiomem.c */
RadioMemory *menu_radio_table_find_8004D380(int toFind);
RadioMemory *menu_radio_table_next_free_8004D3B8(void);
void menu_radio_compact_free_vars_8004D3D8(void);
// void sub_8004D4A0(RadioCodecStru_800ABB98 *pStru);
void sub_8004D580(int pressed);
void menu_radio_draw_mem(MenuWork *work, unsigned char *pOt);
void menu_radio_codec_helper_helper4_8004DE20(MenuWork *work);
void menu_radio_codec_helper__helper3_sub_8004DF44();
int menu_radio_codec_helper_helper2_8004DF68(MenuWork *work, GV_PAD *pPad);
void MENU_InitRadioMemory(void);
void MENU_SetRadioMemory(int varId, const char *pVarName);
void menu_radio_codec_helper_helper_8004E198(int toFind);

/*---------------------------------------------------------------------------*/

// For MenuPrim
#define _NEW_PRIM(prim, buf)                               \
    {                                                      \
        typeof(prim) p;                                    \
        p = (typeof(prim))buf->mPrimBuf.mFreeLocation;     \
        buf->mPrimBuf.mFreeLocation += sizeof(*prim);      \
        prim = p;                                          \
    }

// For MenuWork
#define NEW_PRIM(prim, buf) _NEW_PRIM(prim, buf->field_20_otBuf)

#endif // __MGS_MENU_MENUMAN_H__
