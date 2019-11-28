#include <sys/types.h>
#include <LIBGTE.h>
#include <LIBGPU.h>

#include "actor.h"

#include "util/idaTypes.h"

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

typedef void(*TMenuUpdateFn)(void); //todo
typedef void(*MenuPrimBuffer)(void); //todo
typedef void(*ButtonStates)(void); //todo
typedef struct MenuMan
{
    Actor mBase;
    MenuPrimBuffer* field_20_prim_buffer;
    ButtonStates* field_24_input;
    BYTE field_28_flags;
    BYTE field_29;
    BYTE field_2A_state;
    BYTE field_2B;
    TMenuUpdateFn m7FnPtrs_field_2C[7];
    DR_ENV mDR_ENV_field_48[2];
    DR_ENV DR_ENV_field_C8;
    DWORD field_108;
    DWORD field_10C;
    DWORD field_110;
    DWORD field_114;
    DWORD field_118;
    DWORD field_11C;
    DWORD field_120;
    DWORD field_124;
    DWORD field_128;
    DWORD field_12C;
    DWORD field_130;
    DWORD field_134;
    DWORD field_138;
    DWORD field_13C;
    DWORD field_140;
    DWORD field_144;
    RECT field_148_rect;
    DR_ENV mDrEnvDst_field_150;
    DR_ENV mDrEnvDst_field_190;
    WORD field_1D0;
    WORD field_1D2;
    BYTE field_1D4;
    BYTE field_1D5;
    WORD field_1D6;
    MenuMan_Inventory_Menu_0x14 field_1D8_invetory_menus[2];
    MenuMan_MenuBars field_200_hp_bars_info;
    WORD field_20C_codec_state;
    WORD field_20E;
    DWORD field_210_size_19F2_font;
    DWORD field_214_108bytes;
    DWORD field_218;
} MenuMan;
