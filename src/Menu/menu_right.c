#include "linker.h"
#include "menuman.h"
#include "Game/game.h"
#include "libgcl/gcl.h"
#include <SYS/TYPES.H>
#include <LIBGTE.H>

u_long SECTION(".sbss") dword_800ABADC;

// menu related?

int SECTION(".sbss") dword_800ABAE0;

extern struct menu_8009E544 *dword_800AB584;
struct menu_8009E544        *SECTION(".sdata") dword_800AB584;

extern GM_Camera GM_Camera_800B77E8;

struct menu_8009E544 *SECTION(".sdata") dword_800AB584;

Menu_rpk_item **SECTION(".sbss") gItemFile_table_800ABAE4;

extern struct menu_8009E544 *dword_800AB584;
extern menu_weapon_rpk_info  gMenuWeaponRpkInfo_8009E57C[];
extern GameState_800B4D98    gGameState_800B4D98;
extern int                   dword_8009E544[];
extern int                   GM_GameStatus_800AB3CC;

int SECTION(".sbss") dword_800ABAE8;
int SECTION(".sbss") dword_800ABAEC;
int SECTION(".sbss") gSnakeLifeYPos_800ABAF0;
int SECTION(".sbss") dword_800ABAF4;
int SECTION(".sbss") dword_800ABAF8;
int SECTION(".sbss") dword_800ABAFC;
int SECTION(".sbss") dword_800ABB00;
int SECTION(".sbss") dword_800ABB04;
int SECTION(".sbss") dword_800ABB08;
short SECTION(".sbss") word_800ABB0C;
short SECTION(".sbss") word_800ABB0E;

extern MenuMan_Inventory_14h_Unk gMenuRightItems_800BD888[MENU_ITEMS_RIGHT_COUNT];

#define OffsetToPointer(offset, valueToAdd) *((unsigned int *)offset) = (int)valueToAdd + *((unsigned int *)offset);

#pragma INCLUDE_ASM("asm/sub_8003CC88.s")
#pragma INCLUDE_ASM("asm/sub_8003CE40.s")

void sub_8003CE78(void)
{
    dword_800ABADC = 0;
}

#pragma INCLUDE_ASM("asm/sub_8003CE84.s")
#pragma INCLUDE_ASM("asm/sub_8003CEF8.s")
#pragma INCLUDE_ASM("asm/sub_8003CFE0.s")
#pragma INCLUDE_ASM("asm/sub_8003D070.s")
#pragma INCLUDE_ASM("asm/sub_8003D0D0.s")

Menu_Item_Unknown *menu_alloc_panel_8003D124(int count)
{
    const int          totalLen = (sizeof(Menu_Item_Unknown_Array_Item) * count) + sizeof(Menu_Item_Unknown_Main);
    Menu_Item_Unknown *pUnknown = (Menu_Item_Unknown *)GV_Malloc_8001620C(totalLen);
    if (pUnknown)
    {
        GV_ZeroMemory_8001619C(pUnknown, totalLen);
        pUnknown->field_0_main.field_0_array_count = count;
        pUnknown->field_0_main.field_10 = 0;
    }
    return pUnknown;
}

void menu_panel_free_8003D184(Menu_Item_Unknown *pPanel)
{
    if (pPanel)
    {
        GV_Free_80016230(pPanel);
    }
}

void AssignXY_8003D1A8(Menu_Item_Unknown_Array_Item *pArray, short idx, short amount)
{
    pArray->field_0_item_id_idx = idx;
    pArray->field_2_current_amount = amount;
    pArray->field_6 = 0;
}

void AssignXYFromVec_8003D1B8(Menu_Item_Unknown_Array_Item *pArray, Menu_Item_Unknown_Array_Item *pOther)
{
    short amount; // $v1

    pArray->field_0_item_id_idx = pOther->field_0_item_id_idx;
    amount = pOther->field_2_current_amount;
    pArray->field_6 = 1;
    pArray->field_4 = 0;
    pArray->field_2_current_amount = amount;
}
#pragma INCLUDE_ASM("asm/sub_8003D1DC.s")

#pragma INCLUDE_ASM("asm/sub_8003D2BC.s")

#pragma INCLUDE_ASM("asm/sub_8003D34C.s")
#pragma INCLUDE_ASM("asm/sub_8003D3A4.s")
#pragma INCLUDE_ASM("asm/sub_8003D3FC.s")
#pragma INCLUDE_ASM("asm/sub_8003D44C.s")
#pragma INCLUDE_ASM("asm/sub_8003D4CC.s")

void sub_8003D520(void)
{
    dword_800ABAE0 = 0;
    return;
}

int sub_8003D52C(void)
{
    return dword_800ABAE0;
}

int menu_8003D538(void)
{
    dword_800ABAE0 += 0x40;
    if (dword_800ABAE0 >= 0x100)
    {
        dword_800ABAE0 = 0x100;
        return 1;
    }

    return 0;
}

#pragma INCLUDE_ASM("asm/sub_8003D568.s")
#pragma INCLUDE_ASM("asm/sub_8003D594.s")
#pragma INCLUDE_ASM("asm/sub_8003D5F0.s")
#pragma INCLUDE_ASM("asm/sub_8003D64C.s")

extern struct menu_8009E544 stru_8009E544[];

void sub_8003D6A8(struct menu_left_right *pMenuLeft, int bIsRight, void *pUpdateFn)
{
    struct menu_8009E544 *pStru; // $v1

    pStru = &stru_8009E544[bIsRight];
    pMenuLeft->field_8_pStru = pStru;
    pStru->field_18_pFnUpdate = pUpdateFn;
}

#pragma INCLUDE_ASM("asm/sub_8003D6CC.s")
#pragma INCLUDE_ASM("asm/menu_8003D7DC.s")

void menu_sub_menu_update_8003DA0C(struct Actor_MenuMan *pActor, int a2, struct menu_left_right *pSubMenu)
{
    if ((GM_GameStatus_800AB3CC & 0x1020) != 0x20)
    {
        pSubMenu->field_8_pStru->field_18_pFnUpdate(pActor, a2, pSubMenu->field_8_pStru->field_0_xOffset,
                                                    pSubMenu->field_8_pStru->field_2_yOffset, pSubMenu);
    }
}

void sub_8003DA60(struct Actor_MenuMan *pActor, int a2, struct menu_left_right *pLeftRight, int off1, int off2)
{
    pLeftRight->field_8_pStru->field_18_pFnUpdate(pActor, a2, pLeftRight->field_8_pStru->field_0_xOffset + off1,
                                                  pLeftRight->field_8_pStru->field_2_yOffset + off2, pLeftRight);
}

int menu_8003DA9C(struct menu_left_right *pMenu, unsigned short *input)
{
    struct menu_8009E544 *field_8_pStru; // $a0

    if ((GM_Camera_800B77E8.field_18_flags & 0x101) != 0)
    {
    ret_zero:
        return 0;
    }

    if ((GM_GameStatus_800AB3CC & 0x1020) == 0x20)
    {
        // TODO: probably a fake match, every return 0
        // is supposed to point to ret_zero but
        // the last one doesn't without a goto.
        goto ret_zero;
    }

    field_8_pStru = pMenu->field_8_pStru;

    if ((*input & field_8_pStru->field_4_input) == 0)
    {
        goto ret_zero;
    }
    dword_800AB584 = field_8_pStru;

    return 1;
}

int sub_8003DAFC(int param_1, unsigned short *param_2)
{
    // clean this up before push but it matches
    if (((unsigned int)*param_2 & *(unsigned int *)(*(int *)(param_1 + 8) + 4)) == 0)
    {
        dword_800AB584 = 0;
        return 1;
    }
    return 0;
}

TILE *menu_render_rect_8003DB2C(MenuGlue *pOt, int x, int y, int w, int h, int rgb)
{
    TILE *pTile; // $v0

    pTile = (TILE *)pOt->mPrimBuf.mFreeLocation;
    pOt->mPrimBuf.mFreeLocation += sizeof(TILE);

    *(int *)&pTile->r0 = rgb;

    pTile->x0 = x;
    pTile->y0 = y;

    pTile->w = w;
    pTile->h = h;

    setTile(pTile);
    addPrim(pOt->mPrimBuf.mOt, pTile);

    return pTile;
}

#pragma INCLUDE_ASM("asm/sub_8003DBAC.s")

Menu_rpk_item **menu_rpk_init_8003DD1C(const char *pFileName)
{
    Menu_rpk_item **pEnd;
    Menu_rpk_item **pIter;
    int             i;
    int             count;
    RpkHeader      *pFileData = GV_GetCache_8001538C(GV_CacheID2_800152FC(pFileName, 'r'));
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

void menu_right_unknown_8003DEB0(void)
{
    sub_8003CE40(gMenuRightItems_800BD888, MENU_ITEMS_RIGHT_COUNT);
}

MenuMan_Inventory_14h_Unk *menu_right_get_weapon_rpk_info_8003DED8(int weaponIdx)
{
    int rpkIdx;
    if ((weaponIdx == eSOCOM) && (gGameState_800B4D98.field_4A_item_states[eSUPPR] == 0))
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

#pragma INCLUDE_ASM("asm/sub_8003DF30.s")
#pragma INCLUDE_ASM("asm/menu_right_update_helper2_helper_8003E030.s")
#pragma INCLUDE_ASM("asm/menu_right_init_helper_8003E0E8.s")
#pragma INCLUDE_ASM("asm/menu_right_update_helper2_helper2_8003E3B0.s")
#pragma INCLUDE_ASM("asm/menu_right_update_helper_8003E4B8.s")
#pragma INCLUDE_ASM("asm/menu_right_update_helper2_8003E674.s")
#pragma INCLUDE_ASM("asm/menu_right_update_8003E990.s")

void sub_8003EBDC(struct Actor_MenuMan *menuMan)
{
    MenuMan_Inventory_14h_Unk *inventory_unk;
    int                        weapon_index;

    weapon_index = (int)(menuMan->field_1F0_menu_right.field_0).field_0_item_id_idx;
    if ((weapon_index != -1) ||
        (weapon_index = *(signed char *)&((menuMan->field_1F0_menu_right).field_11), weapon_index != -1))
    {
        inventory_unk = menu_right_get_weapon_rpk_info_8003DED8(weapon_index);
        sub_8003CFE0(inventory_unk, 1);
    }
}

void menu_right_init_8003EC2C(struct Actor_MenuMan *menuMan)

{
    short val = -1;
    menuMan->m7FnPtrs_field_2C[1] = menu_right_update_8003E990;
    menuMan->field_1F0_menu_right.field_0.field_0_item_id_idx = val;
    menuMan->field_1F0_menu_right.field_10 = 0;
    menuMan->field_1F0_menu_right.field_12_flashingAnimationFrame = 0;
    menuMan->field_1F0_menu_right.field_0.field_4 = 0;
    menuMan->field_1F0_menu_right.field_0.field_6 = 1;
    menuMan->field_1F0_menu_right.field_11 = val;
    menuMan->field_28_flags |= 2;
    dword_800ABAE8 = 0;
    sub_8003D6A8(&menuMan->field_1F0_menu_right, 1, (int *)menu_right_init_helper_8003E0E8);
    menu_inventory_right_init_items_8003DE50();
    sub_8003EBDC(menuMan);
}

void sub_8003ECAC(int param_1)
{
    *(char *)(param_1 + 0x28) &= 0xfd;
    return;
}
