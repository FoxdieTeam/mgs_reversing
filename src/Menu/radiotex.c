#include "psyq.h"
#include "Game/game.h"
#include "Menu/menuman.h"

extern RECT rect_800AB6C8;
RECT        rect_800AB6C8;

extern RECT rect_800AB6D0;
RECT        rect_800AB6D0;

#ifdef VR_EXE
char SECTION(".rdata") strin3[] = "NO MEMORY FOR SAVE TEX\n";
#endif

void sub_800469F0(menu_chara_struct *pStru)
{
#ifndef VR_EXE
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
        printf("NO MEMORY FOR SAVE TEX\n");
    }

    pSaveTextCopy = (char *)pStru->field_2C_pSaveText;
    StoreImage(&rect_800AB6C8, (u_long *)pSaveTextCopy);
    StoreImage(&rect_800AB6D0, (u_long *)(pSaveTextCopy + offsetImage2));
#else
    TEMPORARY_VR_MATCHING_PLACEHOLDER(0, 0, 3, 8);
#endif
}

void menu_radio_codec_helper_helper7_helper_80046A98(menu_chara_struct *pStru)
{
#ifndef VR_EXE
    char *pSaveText;
    int   imageSize;

    imageSize = rect_800AB6C8.w * rect_800AB6C8.h * 2; // 16-bit per pixel

    LoadImage(&rect_800AB6C8, (u_long *)pStru->field_2C_pSaveText);

    pSaveText = (char *)pStru->field_2C_pSaveText;
    LoadImage(&rect_800AB6D0, (u_long *)(pSaveText + imageSize));

    DrawSync(0);
    GV_FreeMemory_80015FD0(0, pStru->field_2C_pSaveText);
#else
    TEMPORARY_VR_MATCHING_PLACEHOLDER(0, 0, 2, 6);
#endif
}

void sub_80046B10(face_anim_image *image, int idx)
{
    RECT rect;

    rect.x = idx * 32 + 960 + image->field_0_xpos / 2;
    rect.y = image->field_1_ypos + 336;
    rect.w = image->field_2_width / 2;
    rect.h = image->field_3_height;

    LoadImage(&rect, (u_long *)image->field_4_image);
}

void menu_radio_load_palette_80046B74(void *image, int idx)
{
#ifndef VR_EXE
    RECT v3;

    v3 = rect_800AB6C8;
    v3.h = 1;
    v3.y += idx;

    LoadImage(&v3, image);
#else
    TEMPORARY_VR_MATCHING_PLACEHOLDER(0, 0, 2, 2);
#endif
}

void sub_80046BD8(int off)
{
#ifndef VR_EXE
    RECT rect;

    rect = rect_800AB6C8;
    rect.y += off;
    rect.h = 1;
    MoveImage(&rect, rect.x, (rect.y * 65536) / 65536 + 2);

    rect.x = off * 32 + 960;
    rect.y = 336;
    rect.w = 32;
    rect.h = 96;
    MoveImage(&rect, rect_800AB6D0.x + off * 32, rect_800AB6D0.y);
#else
    TEMPORARY_VR_MATCHING_PLACEHOLDER(0, 0, 4, 3);
#endif
}
