#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "Game/game.h"
#include "Menu/menuman.h"

RECT rect_800AB6C8 = {768, 256, 256, 4};
RECT rect_800AB6D0 = {896, 336, 64, 96};

void sub_800469F0(menu_chara_struct *pStru)
{
    int    offsetImage2;
    int    totalSize;
    short *pSaveText;
    char  *pSaveTextCopy;

    offsetImage2 = rect_800AB6C8.w * rect_800AB6C8.h * 2; // 16-bit per pixel
    totalSize = offsetImage2 + rect_800AB6D0.w * rect_800AB6D0.h * 2;
    pSaveText = (short *)GV_AllocMemory(GV_PACKET_MEMORY0, totalSize);

    pStru->field_2C_pSaveText = pSaveText;
    if (pSaveText == NULL)
    {
        printf("NO MEMORY FOR SAVE TEX\n");
    }

    pSaveTextCopy = (char *)pStru->field_2C_pSaveText;
    StoreImage(&rect_800AB6C8, (u_long *)pSaveTextCopy);
    StoreImage(&rect_800AB6D0, (u_long *)(pSaveTextCopy + offsetImage2));
}

void menu_radio_codec_helper_helper7_helper_80046A98(menu_chara_struct *pStru)
{
    char *pSaveText;
    int   imageSize;

    imageSize = rect_800AB6C8.w * rect_800AB6C8.h * 2; // 16-bit per pixel

    LoadImage(&rect_800AB6C8, (u_long *)pStru->field_2C_pSaveText);

    pSaveText = (char *)pStru->field_2C_pSaveText;
    LoadImage(&rect_800AB6D0, (u_long *)(pSaveText + imageSize));

    DrawSync(0);
    GV_FreeMemory(GV_PACKET_MEMORY0, pStru->field_2C_pSaveText);
}

/**
 * @brief Load an image from the face animation data for the codec screen.
 * The index is used to determine the position of the image.
 *
 * @param image The face animation image data.
 * @param idx 0 left character, 1 right character
 */
void LoadFaceAnimImage_80046B10(face_anim_image *image, int idx)
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
    RECT v3;

    v3 = rect_800AB6C8;
    v3.h = 1;
    v3.y += idx;

    LoadImage(&v3, image);
}

void sub_80046BD8(int off)
{
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
}
