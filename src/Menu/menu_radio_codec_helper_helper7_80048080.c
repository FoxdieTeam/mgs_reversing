#include "menuman.h"
#include "libgv/libgv.h"

menu_chara_struct* dword_800ABB38;
menu_chara_struct        *SECTION(".sbss") dword_800ABB38; // force gp

void menu_radio_codec_helper_helper7_helper_80046A98(menu_chara_struct *pStru);

void menu_radio_codec_helper_helper7_80048080()
{
    menu_radio_codec_helper_helper7_helper_80046A98(dword_800ABB38);
    GV_FreeMemory_80015FD0(0, dword_800ABB38->field_24_pImgData256);
    GV_FreeMemory_80015FD0(0, dword_800ABB38->field_28_pStack);
    GV_FreeMemory_80015FD0(0, dword_800ABB38->field_20_pFaceMemory);
    GV_FreeMemory_80015FD0(0, dword_800ABB38->field_1C);
    dword_800ABB38->field_1C = 0;
}