#include "Menu/menuman.h"
#include "psyq.h"

extern RECT rect_800AB6C8;
RECT        SECTION(".sdata") rect_800AB6C8;

extern RECT rect_800AB6D0;

void menu_radio_codec_helper_helper7_helper_80046A98(menu_chara_struct *pStru)
{
    char *pSaveText;
    int   imageSize;

    imageSize = rect_800AB6C8.w * rect_800AB6C8.h * 2; // 16-bit per pixel

    LoadImage(&rect_800AB6C8, (char *)pStru->field_2C_pSaveText);

    pSaveText = (char *)pStru->field_2C_pSaveText;
    LoadImage(&rect_800AB6D0, pSaveText + imageSize);

    DrawSync(0);
    GV_FreeMemory_80015FD0(0, pStru->field_2C_pSaveText);
}
