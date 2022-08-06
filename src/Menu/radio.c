#include "linker.h"
#include "menuman.h"
#include "radio.h"
#include "unknown.h"

int SECTION(".sdata") dword_800AB63C = 0; // declared

extern int dword_800ABB04;
int        SECTION(".sbss") dword_800ABB04;

extern int dword_800ABB08;
int        SECTION(".sbss") dword_800ABB08;

extern int dword_800ABB10;
int        SECTION(".sbss") dword_800ABB10; // declared

extern unsigned char dword_800ABB20;
unsigned char        SECTION(".sbss") dword_800ABB20;

#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper16_8003FC54.s")
#pragma INCLUDE_ASM("asm/sub_8003FD50.s")
#pragma INCLUDE_ASM("asm/sub_8003FFB0.s")
#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_helper_80040034.s")
#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_helper2_800401AC.s")
#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_helper5_800402A0.s")
#pragma INCLUDE_ASM("asm/Menu/menu_RadioCall_helper_800403E4.s")
#pragma INCLUDE_ASM("asm/menu_radio_update_helper3_80040498.s")
#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_helper3_80040590.s")
#pragma INCLUDE_ASM(                                                                                                   \
    "asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_helper6_helper_8004064C.s")
#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_helper6_800407A4.s")
#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_helper4_800408BC.s")
#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper15_80040B8C.s")
#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_80040DC4.s")
#pragma INCLUDE_ASM("asm/init_radio_message_board_80040F74.s")

void menu_radio_codec_helper__helper13_800410E4(int param_1, int param_2)
{
    int iVar1;

    iVar1 = *(int *)(param_1 + 0x214);
    dword_800ABB04 = param_2;
    sub_800469A4(iVar1, (char *)param_2);
    font_update_8004695C((KCB *)iVar1); // TODO: iVar1 is KCB*
    return;
}

void sub_80041118(int param_1)
{
    int iVar1;

    iVar1 = *(int *)(param_1 + 0x214);
    dword_800ABB04 = 0;
    font_clear_800468FC((KCB *)iVar1); // TODO: iVar1 is KCB*
    font_update_8004695C((KCB *)iVar1);
    return;
}

#pragma INCLUDE_ASM("asm/draw_radio_message_8004114C.s")

void sub_8004124C(int param_1)
{
    GV_FreeMemory_80015FD0(0, *(void **)(param_1 + 0x214));
    *(int *)(param_1 + 0x214) = 0;
    dword_800ABB04 = 0;
    return;
}

#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper12_80041280.s")
#pragma INCLUDE_ASM("asm/draw_radio_wait_mark_8004143C.s")
#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper11_8004150C.s")
#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_8004158C.s")

void menu_radio_update_helper5_80042160(Actor_MenuMan *menuMan)
{
    dword_800AB63C = 0;
    dword_800ABB10 = 0;
    menuMan->field_212 = 8;
    menuMan->field_210 = 0;
    menu_radio_codec_create_state_80047CE4(menuMan);
}

void menu_radio_init_nullsub_80042190(void)
{
}

#pragma INCLUDE_ASM("asm/menu_radio_update_80042198.s")

void menu_radio_init_80042700(Actor_MenuMan *pMenu)
{
    pMenu->m7FnPtrs_field_2C[4] = (TMenuUpdateFn)menu_radio_update_80042198;
    pMenu->field_28_flags |= 0x10u;
}

void menu_radio_kill_8004271C(Actor_MenuMan *pMenu)
{
    pMenu->field_28_flags &= ~0x10u;
}

#pragma INCLUDE_ASM("asm/Menu/menu_RadioCall_80042730.s")
#pragma INCLUDE_ASM("asm/Menu/menu_SetLoad_800427E8.s")
#pragma INCLUDE_ASM("asm/Menu/menu_ResetCall_80042814.s")

void menu_SetRadioCallbackProc_8004283C(int param_1)
{
    dword_800ABB08 = param_1;
    return;
}

#pragma INCLUDE_ASM("asm/Menu/menu_number_init_80042848.s")

void menu_number_kill_80042980(void)
{
}

#pragma INCLUDE_ASM("asm/Menu/menu_number_draw_80042988.s")
#pragma INCLUDE_ASM("asm/menu_draw_number_draw_helper_80042B64.s")
#pragma INCLUDE_ASM("asm/Menu/menu_number_draw_string_80042BF4.s")
#pragma INCLUDE_ASM("asm/Menu/menu_number_draw_magazine_80042E38.s")
#pragma INCLUDE_ASM("asm/Menu/menu_number_draw_80042F78.s")
#pragma INCLUDE_ASM("asm/Menu/menu_number_draw_number2_80042FC0.s")
#pragma INCLUDE_ASM("asm/Menu/menu_number_draw_string_800430F0.s")
#pragma INCLUDE_ASM("asm/Menu/menu_set_string2_80043138.s")
#pragma INCLUDE_ASM("asm/Menu/menu_number_draw_string2_80043220.s")
#pragma INCLUDE_ASM("asm/Menu/menu_restore_nouse_80043470.s")
#pragma INCLUDE_ASM("asm/Menu/menu_init_nouse_800434A8.s")
#pragma INCLUDE_ASM("asm/sub_800434F4.s")
#pragma INCLUDE_ASM("asm/Menu/menu_draw_nouse_800435A4.s")
#pragma INCLUDE_ASM("asm/Menu/menu_draw_frozen_800435C8.s")
#pragma INCLUDE_ASM("asm/Menu/menu_draw_triangle_800435EC.s")
#pragma INCLUDE_ASM("asm/sub_80043678.s")
#pragma INCLUDE_ASM("asm/sub_80043A24.s")
#pragma INCLUDE_ASM("asm/sub_80043FD0.s")
#pragma INCLUDE_ASM("asm/sub_800442E4.s")
#pragma INCLUDE_ASM("asm/sub_800445F8.s")
#pragma INCLUDE_ASM("asm/sub_800448C0.s")
#pragma INCLUDE_ASM("asm/Menu/menu_viewer_init_80044A70.s")

void menu_viewer_kill_80044A90(Actor_MenuMan *pActor)
{
    dword_800ABB20 = 0;
    return;
}

#pragma INCLUDE_ASM("asm/Font/font_load_80044A9C.s")
#pragma INCLUDE_ASM("asm/Font/font_set_font_addr_80044BC0.s")

void sub_80044BD8(void)
{
    return;
}
