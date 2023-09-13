#include "Menu/menuman.h"
#include "psyq.h"

extern RECT rect_800AB6C8;
RECT        rect_800AB6C8;

extern RECT rect_800AB6D0;
RECT        rect_800AB6D0;

extern const char aNoMemoryForSav[]; // = "NO MEMORY FOR SAVE TEX\n";

void sub_800469F0(menu_chara_struct *pStru)
{
    int    offsetImage2;
    int    totalSize;
    short *pSaveText;
    char  *pSaveTextCopy;

    offsetImage2 = rect_800AB6C8.w * rect_800AB6C8.h * 2; // 16-bit per pixel
    totalSize = offsetImage2 + rect_800AB6D0.w * rect_800AB6D0.h * 2;
    pSaveText = (short *)GV_AllocMemory_80015EB8(0, totalSize);

    pStru->field_2C_pSaveText = pSaveText;
    if (pSaveText == NULL)
    {
        printf(aNoMemoryForSav);
    }

    pSaveTextCopy = (char *)pStru->field_2C_pSaveText;
    StoreImage(&rect_800AB6C8, (u_long *)pSaveTextCopy);
    StoreImage(&rect_800AB6D0, (u_long *)(pSaveTextCopy + offsetImage2));
}
