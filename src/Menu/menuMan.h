#include <sys/types.h>
#include <LIBGTE.h>
#include <LIBGPU.h>

#include "actor.h"

#include "util/idaTypes.h"

typedef struct
{
    char *field_0_weapon_name;
    int field_4_rpk_idx;
} menu_weapon_rpk_info;

typedef struct RadioMemory
{
    short field_0_id;
    char field_2_name[18];
} RadioMemory;

#define RADIO_MEMORY_COUNT 16

extern RadioMemory gRadioMemory_800BDB38[RADIO_MEMORY_COUNT];

typedef struct menu_chara_struct
{
    int field_0_state;
    int field_4;
    int field_8;
    unsigned char *field_C_pScript;
    int field_10;
    int field_14_bInExecBlock; // to prevent re-entering?
    unsigned short field_18;
    unsigned short field_1A;
    int field_1C;
    int field_20_pFaceMemory;
    int field_24;
    int *field_28_pStack;
    int field_2C;
    int field_30_face_data_num;
    int field_34;
    int field_38;
    short field_3C;
    short field_3E;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;
    short field_54;
    short field_56;
    int field_58;
    int field_5C;
    int field_60;
    int field_64;
    int field_68;
} menu_chara_struct;

typedef struct
{
    unsigned char *field_0_pixels;
    unsigned short int *field_4_word_ptr_pixels;
    char field_8_index;
    char field_9_x;
    char field_A_y;
    unsigned char field_B; // Padding?
    unsigned char field_C_u;
    unsigned char field_D_v;
    short field_E_clut;
    short field_10_w;
    short field_12_h;
} MenuMan_Inventory_14h_Unk;

RadioMemory *menu_radio_table_find_8004D380(int toFind);
RadioMemory *menu_radio_table_next_free_8004D3B8(void);
unsigned char *menu_gcl_read_word_80047098(int *pOut, unsigned char *pScript);
void menu_radio_clear_or_set_var_8004E110(int varId, const char *pVarName);
void menu_gcl_set_radio_var_80047768(menu_chara_struct *unknown, unsigned char *pScript);
unsigned char *menu_gcl_exec_block_800478B4(menu_chara_struct *unknown, unsigned char *pScript);

void menuman_init_80038954(void);

struct menu_8009E544
{
    short field_0;
    short field_2;
    int field_4_input;
    int field_8;
    int field_C;
    void *field_10;
    void *field_14;
    int field_18_pFnUpdate;
};

struct menu_left_right
{
    short field_0_rpk_idx;
    short field_2;
    int field_4;
    struct menu_8009E544 *field_8_pStru;
    int field_C_alloc;
    char field_10;
    char field_11;
    short field_12;
};

typedef struct MenuMan_MenuBars
{
    BYTE field_0_state;
    BYTE field_1_O2_hp;
    short int field_2_bar_x;
    short int field_4_bar_y;
    short int field_6_snake_hp;
    short int field_8;
    short int field_A_k10_decrement;
} MenuMan_MenuBars;

typedef struct MenuMan_Inventory_Menu_0x14
{
    //MenuMan_Inventory_Sub field_0_invent;
    //Menu_Item_Unknown* field_C_pItem_sys_alloc;
    int a[4]; //todo remove, return the other ones
    char field_10_state;
    char field_11_item_idx;
    short field_12;
} MenuMan_Inventory_Menu_0x14;

typedef void (*TMenuUpdateFn)(void); //todo
typedef void (*ButtonStates)(void);  //todo

typedef struct
{
    unsigned char *mFreeLocation;
    unsigned char *mOt;
    unsigned char *mOtEnd;
} MenuPrimBuffer;

typedef struct
{
    MenuPrimBuffer mPrimBuf;
    unsigned char *mPrimPtrs[2];
} MenuGlue;

typedef struct Actor_MenuMan
{
    Actor mBase;
    MenuPrimBuffer *field_20_prim_buffer;
    ButtonStates *field_24_input;
    BYTE field_28_flags;
    BYTE field_29;
    BYTE field_2A_state;
    BYTE field_2B;
    TMenuUpdateFn m7FnPtrs_field_2C[8];
    DR_ENV mDR_ENV_field_4C[2];
    DR_ENV DR_ENV_field_CC;
    int field_14C;
    int field_150;
    DR_ENV field_154;
    DR_ENV field_194;
    short field_1D4_clipX1;
    short field_1D6_clipY1;
    char field_1D8;
    char field_1D9;
    char field_1DA;
    char field_1DB;
    struct menu_left_right field_1DC_menu_left;
    struct menu_left_right field_1F0_menu_right;
    char field_204;
    char field_205;
    short field_206;
    short field_208;
    short field_20A_snake_current_health;
    short field_20C;
    short field_20E;
    short field_210;
    short field_212;
    int field_214_font;
    int field_218;
    int field_21C;
    int field_220;
} MenuMan;
typedef void (*TInitKillFn)(MenuMan *);
