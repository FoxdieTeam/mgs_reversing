#include "linker.h"
#include "menuMan.h"
#include "Script_tbl_map_8002BB44.h"

typedef struct
{
    char field_0_x;
    char field_1_y;
    char field_2_w;
    char field_3_h;
    unsigned char field_4_pixel_ptr[0];
} Menu_rpk_item;

typedef struct
{
    unsigned char field_0_count1;
    unsigned char field_1_count2;
    short pad;
    Menu_rpk_item *items[0]; // pointers ??
} RpkHeader;

Menu_rpk_item **SECTION(".sbss") gItemFile_table_800ABAE4;

int GV_HashFileName_800152FC(const char *pFileName, int ext);
void *GV_FindCachedFile_8001538C(int hash);

extern menu_weapon_rpk_info gMenuWeaponRpkInfo_8009E57C[];

#define OffsetToPointer(offset, valueToAdd) *((unsigned int *)offset) = (int)valueToAdd + *((unsigned int *)offset);

Menu_rpk_item **menu_rpk_init_8003DD1C(const char *pFileName)
{
    Menu_rpk_item **pEnd;
    Menu_rpk_item **pIter;
    int i;
    int count;
    RpkHeader *pFileData = GV_FindCachedFile_8001538C(GV_HashFileName_800152FC(pFileName, 'r'));
    if (!pFileData)
    {
        return 0;
    }

    count = pFileData->field_0_count1 + pFileData->field_1_count2;
    pEnd = pFileData->items + count;

    gItemFile_table_800ABAE4 = pFileData->items;

    pIter = pFileData->items;
    for (i = 0; i < count; i++)
    {
        OffsetToPointer(pIter, pEnd);
        pIter++;
    }

    return gItemFile_table_800ABAE4;
}

Menu_rpk_item *menu_rpk_get_pal_8003DD9C(int id)
{
    return gItemFile_table_800ABAE4[id];
}

Menu_rpk_item *menu_rpk_get_img_8003DDB4(int id)
{
    return gItemFile_table_800ABAE4[id];
}

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

void menu_init_rpk_item_8003DDCC(MenuMan_Inventory_14h_Unk *pUnk, int imgIdx, int palIdx)
{
    Menu_rpk_item *pPal;
    Menu_rpk_item *pImg;

    pPal = menu_rpk_get_pal_8003DD9C(palIdx);
    pImg = menu_rpk_get_img_8003DDB4(imgIdx);
    pUnk->field_9_x = pImg->field_0_x - 2;
    pUnk->field_A_y = pImg->field_1_y - 2;
    pUnk->field_10_w = pImg->field_2_w * 4;
    pUnk->field_12_h = pImg->field_3_h;
    pUnk->field_0_pixels = &pImg->field_4_pixel_ptr[0];
    pUnk->field_4_word_ptr_pixels = (short *)&pPal->field_4_pixel_ptr[0];
}

#define MENU_ITEMS_RIGHT_COUNT 11

MenuMan_Inventory_14h_Unk SECTION(".gMenuRightItems_800BD888") gMenuRightItems_800BD888[MENU_ITEMS_RIGHT_COUNT];

void menu_inventory_right_init_items_8003DE50(void)
{
    int i = 0;
    while (i < MENU_ITEMS_RIGHT_COUNT)
    {
        const int imgIdx = i + 1;
        menu_init_rpk_item_8003DDCC(&gMenuRightItems_800BD888[i], imgIdx, 0);
        i++;
    }
}

void sub_8003CE40(MenuMan_Inventory_14h_Unk *, int);

void menu_right_unknown_8003DEB0(void)
{
    sub_8003CE40(gMenuRightItems_800BD888, MENU_ITEMS_RIGHT_COUNT);
}

extern GameState gGameState_800B4D98;

MenuMan_Inventory_14h_Unk* menu_right_get_weapon_rpk_info_8003DED8(int weaponIdx)
{
    int rpkIdx;
    if ((weaponIdx == 0) && (gGameState_800B4D98.field_3E_item_states[23] == 0))
    {
        rpkIdx = 2;
    }
    else
    {
        rpkIdx = gMenuWeaponRpkInfo_8009E57C[weaponIdx].field_4_rpk_idx;
    }
    rpkIdx--;
    return gMenuRightItems_800BD888 + rpkIdx;
}

