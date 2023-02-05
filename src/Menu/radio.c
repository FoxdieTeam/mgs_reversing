#include "linker.h"
#include "menuman.h"
#include "radio.h"
#include "unknown.h"

int SECTION(".sdata") dword_800AB63C = 0; // declared

extern int dword_800ABB04;
int        SECTION(".sbss") dword_800ABB04;

extern int dword_800ABB08;
int        SECTION(".sbss") dword_800ABB08;

extern short word_800ABB0C;
short SECTION(".sbss") word_800ABB0C;

extern int dword_800ABB10;
int        SECTION(".sbss") dword_800ABB10; // declared

extern unsigned char dword_800ABB20;
unsigned char        SECTION(".sbss") dword_800ABB20;

extern short word_800ABB22;
short        SECTION(".sbss") word_800ABB22;

extern int dword_800ABB24;
int SECTION(".sbss") dword_800ABB24;

extern int GV_Time_800AB330;
extern void *dword_8009E75C[];

extern DG_TEX gTextureRecs_800B1F50[512];

extern MenuMan_Inventory_14h_Unk dword_800BDA10;
extern MenuMan_Inventory_14h_Unk dword_800BDA30;
extern RadioIncomingCall gRadioIncomingCall_8009E708;
extern int GV_PadMask_800AB374;

#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper16_8003FC54.s") // 252 bytes
#pragma INCLUDE_ASM("asm/sub_8003FD50.s") // 608 bytes
#pragma INCLUDE_ASM("asm/sub_8003FFB0.s") // 132 bytes
#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_helper_80040034.s") // 376 bytes
#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_helper2_800401AC.s") // 244 bytes
#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_helper5_800402A0.s") // 324 bytes
#pragma INCLUDE_ASM("asm/Menu/menu_RadioCall_helper_800403E4.s") // 180 bytes
#pragma INCLUDE_ASM("asm/menu_radio_update_helper3_80040498.s") // 248 bytes
#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_helper3_80040590.s") // 188 bytes
#pragma INCLUDE_ASM(                                                                                                   \
    "asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_helper6_helper_8004064C.s") // 344 bytes

extern char aP3t3t[];  // = "P#3T#3T";
extern char aMemory[]; // = "MEMORY";

void menu_radio_codec_helper_helper14_helper6_800407A4(MenuGlue *pGlue, int xpos, int ypos, int flags)
{
    unsigned colour;

    if (flags < 0)
    {
        flags = 0xf; // Go into all branches below
        colour = 0x3d472e;
    }
    else
    {
        colour = 0x3d472e;
    }

    if (flags & 1)
    {
        TextConfig conf;
        conf.xpos = xpos + 0x90;
        conf.ypos = ypos + 0x28;
        conf.colour = 0x64000000 | colour;
        conf.flags = 0;
        menu_number_draw_string2_80043220(pGlue, &conf, aP3t3t);
    }
    if (flags & 2)
    {
        TextConfig conf;
        conf.xpos = xpos + 0x86;
        conf.ypos = ypos + 0x77;
        conf.colour = 0x64000000 | colour;
        conf.flags = 0;
        menu_number_draw_string2_80043220(pGlue, &conf, aMemory);
    }
    if (flags & 4)
    {
        menu_radio_codec_helper_helper14_helper6_helper_8004064C(pGlue, xpos, ypos, colour, 0);
    }
    if (flags & 8)
    {
        menu_radio_codec_helper_helper14_helper6_helper_8004064C(pGlue, xpos, ypos, colour, 1);
    }
    return;
}

#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_helper4_800408BC.s") // 720 bytes
#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper15_80040B8C.s") // 568 bytes
#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper14_80040DC4.s") // 432 bytes
#pragma INCLUDE_ASM("asm/init_radio_message_board_80040F74.s") // 368 bytes

void menu_radio_codec_helper__helper13_800410E4(Actor_MenuMan *pActor, int param_2)
{
    KCB *kcb = pActor->field_214_font;
    dword_800ABB04 = param_2;
    sub_800469A4(kcb, (char *)param_2);
    font_update_8004695C(kcb);
}

void sub_80041118(Actor_MenuMan *pActor)
{
    KCB *kcb = pActor->field_214_font;
    dword_800ABB04 = 0;
    font_clear_800468FC(kcb);
    font_update_8004695C(kcb);
}

#pragma INCLUDE_ASM("asm/draw_radio_message_8004114C.s") // 256 bytes

void sub_8004124C(Actor_MenuMan *pActor)
{
    GV_FreeMemory_80015FD0(0, pActor->field_214_font);
    pActor->field_214_font = NULL;
    dword_800ABB04 = 0;
}

#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_helper12_80041280.s") // 444 bytes

void draw_radio_wait_mark_8004143C(Actor_MenuMan *pActor, unsigned int *pOt)
{
    MenuGlue *pOtBuffer; // $v1
    POLY_F3 *pPrim; // $a0

    if ( GV_Time_800AB330 % 16 >= 4 )
    {
        pOtBuffer = pActor->field_20_otBuf;
        pPrim = (POLY_F3 *)pOtBuffer->mPrimBuf.mFreeLocation;
        pOtBuffer->mPrimBuf.mFreeLocation += sizeof(POLY_F3);
        pPrim->x1 = 288;
        pPrim->y1 = 210;

        pPrim->x0 = pPrim->x1 - 4;
        pPrim->x2 = pPrim->x1 + 4;

        pPrim->y0 = pPrim->y2 = pPrim->y1 - 4;

         *(int *)&pPrim->r0 = 0x80808080;
        setPolyF3(pPrim);
        addPrim(pOt, pPrim);
    }
}

extern short word_800ABB0C;
short        SECTION(".sbss") word_800ABB0C;

extern short word_800ABB0E;
short        SECTION(".sbss") word_800ABB0E;

extern int dword_800AB638;
int        SECTION(".sbss") dword_800AB638;

void menu_radio_codec_helper_helper11_8004150C(Actor_MenuMan *pActor)
{
    int   pRadioCode;
    short dword_800AB638_copy;

    init_radio_message_board_80040F74(pActor);
    pActor->field_212 = 0x1e;
    GM_Sound_80032968(0, 0x3f, 0x56);
    pRadioCode = menu_GetRadioCode_800497C4(dword_800AB638);
    if (pRadioCode >= 0)
    {
        sub_80047D70(pActor, dword_800AB638, pRadioCode);
        dword_800AB638_copy = dword_800AB638;
        pActor->field_210 = 2;
        word_800ABB0C = 0;
        word_800ABB0E = dword_800AB638_copy;
        return;
    }

    pActor->field_210 = 9;
}

#pragma INCLUDE_ASM("asm/Menu/menu_radio_codec_helper_8004158C/menu_radio_codec_helper_8004158C.s") // 3028 bytes

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

#pragma INCLUDE_ASM("asm/menu_radio_update_80042198.s") // 1384 bytes

void menu_radio_init_80042700(Actor_MenuMan *pMenu)
{
    pMenu->m7FnPtrs_field_2C[4] = (TMenuUpdateFn)menu_radio_update_80042198;
    pMenu->field_28_flags |= 0x10u;
}

void menu_radio_kill_8004271C(Actor_MenuMan *pMenu)
{
    pMenu->field_28_flags &= ~0x10u;
}

void menu_RadioCall_80042730(int param_1, int param_2, int time)
{
    gRadioIncomingCall_8009E708.field_0 = param_1;
    gRadioIncomingCall_8009E708.field_4 = param_2;

    if (time == 0)
    {
        gRadioIncomingCall_8009E708.field_2_timer = 360;
        gRadioIncomingCall_8009E708.field_8 = 0;
        menu_RadioCall_helper_800403E4();
    }

    else
    {
        if (time >= 5)
        {
            menu_RadioCall_helper_800403E4();
            gRadioIncomingCall_8009E708.field_8 = 1;
            gRadioIncomingCall_8009E708.field_2_timer = 40;
            GV_PadMask_800AB374 = 0x100;
            GM_GameStatus_800AB3CC |= 0x8000000;
        }
        else
        {
            gRadioIncomingCall_8009E708.field_2_timer = -time;
            gRadioIncomingCall_8009E708.field_8 = 0;
        }

        GM_GameStatus_800AB3CC |= 0x80000;
    }
}

void menu_SetLoad_800427E8(int param_1, int param_2, short param_3)
{
    gRadioIncomingCall_8009E708.field_0 = param_3;
    gRadioIncomingCall_8009E708.field_2_timer = -1;
    gRadioIncomingCall_8009E708.field_4 = param_2;
    dword_800ABB08 = param_1;
    word_800ABB0C = 1;
}

void menu_ResetCall_80042814()
{
    gRadioIncomingCall_8009E708.field_0 = 0;
    gRadioIncomingCall_8009E708.field_4 = 0;
    gRadioIncomingCall_8009E708.field_2_timer = 0;
    gRadioIncomingCall_8009E708.field_8 = 0;
    
    dword_800ABB08 = -1;
}

void menu_SetRadioCallbackProc_8004283C(int param_1)
{
    dword_800ABB08 = param_1;
    return;
}

#pragma INCLUDE_ASM("asm/Menu/menu_number_init_80042848.s") // 312 bytes

void menu_number_kill_80042980(void)
{
}

#pragma INCLUDE_ASM("asm/Menu/menu_number_draw_80042988.s") // 476 bytes
#pragma INCLUDE_ASM("asm/menu_draw_number_draw_helper_80042B64.s") // 144 bytes
#pragma INCLUDE_ASM("asm/Menu/menu_number_draw_string_80042BF4.s") // 580 bytes
#pragma INCLUDE_ASM("asm/Menu/menu_number_draw_magazine_80042E38.s") // 320 bytes

int menu_number_draw_80042F78(Actor_MenuMan *pActor, int a2, int xpos, int ypos, int number, int flags)
{
    TextConfig textConfig; // [sp+10h] [-10h] BYREF

    textConfig.xpos = xpos;
    textConfig.ypos = ypos;
    textConfig.colour = 0x64808080;
    textConfig.flags = flags;
    menu_number_draw_80042988(pActor->field_20_otBuf, &textConfig, number);
    return textConfig.xpos;
}

#pragma INCLUDE_ASM("asm/Menu/menu_number_draw_number2_80042FC0.s") // 304 bytes

int menu_number_draw_string_800430F0(Actor_MenuMan *pActor, int a2, int xpos, int ypos, char *str, int flags)
{
    TextConfig textConfig;

    textConfig.xpos = xpos;
    textConfig.ypos = ypos;
    textConfig.colour = 0x64808080;
    textConfig.flags = flags;
    menu_number_draw_string_80042BF4(pActor->field_20_otBuf, &textConfig, str);
    return textConfig.xpos;
}

#pragma INCLUDE_ASM("asm/Menu/menu_set_string2_80043138.s") // 232 bytes
#pragma INCLUDE_ASM("asm/Menu/menu_number_draw_string2_80043220.s") // 592 bytes

void menu_restore_nouse_80043470()
{
    sub_8003CFE0(&dword_800BDA10, 2);
    sub_8003CFE0(&dword_800BDA30, 3);
}

void menu_init_nouse_800434A8()
{
    dword_800BDA10.field_8_index = 0;
    menu_init_rpk_item_8003DDCC(&dword_800BDA10, 40, 39);
    menu_init_rpk_item_8003DDCC(&dword_800BDA30, 48, 39);
    menu_restore_nouse_80043470();
}

void sub_800434F4(MenuGlue *pGlue, int param_2, int param_3, MenuMan_Inventory_14h_Unk *param_4)
{
    SPRT *pPrim;

    pPrim = (SPRT *)pGlue->mPrimBuf.mFreeLocation;
    pGlue->mPrimBuf.mFreeLocation += sizeof(SPRT);

    *(int *)&pPrim->r0 = 0x80808080;
    sub_8003D0D0(pPrim, param_4, param_2 - 2, param_3 + 6);

    setSprt(pPrim);
    addPrim(pGlue->mPrimBuf.mOt, pPrim);
}

void menu_draw_nouse_800435A4(MenuGlue *pGlue, int param_2, int param_3)
{
    sub_800434F4(pGlue, param_2, param_3, &dword_800BDA10);
}

void menu_draw_frozen_800435C8(MenuGlue *pGlue, int param_2, int param_3)
{
    sub_800434F4(pGlue, param_2, param_3, &dword_800BDA30);
}

#pragma INCLUDE_ASM("asm/Menu/menu_draw_triangle_800435EC.s") // 140 bytes
#pragma INCLUDE_ASM("asm/sub_80043678.s") // 940 bytes
#pragma INCLUDE_ASM("asm/sub_80043A24.s") // 1452 bytes
#pragma INCLUDE_ASM("asm/sub_80043FD0.s") // 788 bytes
#pragma INCLUDE_ASM("asm/sub_800442E4.s") // 788 bytes
#pragma INCLUDE_ASM("asm/sub_800445F8.s") // 712 bytes
#pragma INCLUDE_ASM("asm/sub_800448C0.s") // 432 bytes

void menu_viewer_init_80044A70(Actor_MenuMan *param_1)
{
    dword_800ABB20 = 0;
    dword_800ABB24 = (int)gTextureRecs_800B1F50;
    word_800ABB22 = -1;
}

void menu_viewer_kill_80044A90(Actor_MenuMan *pActor)
{
    dword_800ABB20 = 0;
    return;
}

#pragma INCLUDE_ASM("asm/Font/font_load_80044A9C.s") // 292 bytes

void font_set_font_addr_80044BC0(int arg1, void *data)
{
    dword_8009E75C[arg1] = data;
}

void sub_80044BD8(void)
{
    return;
}
