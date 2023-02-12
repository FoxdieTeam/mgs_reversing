#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "libdg/libdg.h"
#include "menuman.h"
#include "linker.h"
#include "psyq.h"

extern MenuMan_Inventory_14h_Unk gMenuLeftItems_800BD5A0[];
extern menu_weapon_rpk_info      gMenuItemRpkInfo_8009E484[];

extern short                     GM_WeaponTypes_8009D580[];
extern short                     GM_ItemTypes_8009D598[];
extern int                       GM_PlayerStatus_800ABA50;
extern int                       GM_DisableItem_800ABA28;

extern int                       dword_8009F46C;

extern int                       dword_800ABAD0;
int SECTION(".sbss")             dword_800ABAD0;

void menu_sub_8003B568(void)
{
    int   imgIdx;
    u_long palIdx;
    int   i;

    for (i = 0; i < MENU_ITEMS_LEFT_COUNT; i++)
    {
        imgIdx = 0xc + i;
        palIdx = 0x2e;
        if (imgIdx != 0x16)
        {
            palIdx = 0;
            if (imgIdx == 0x1b)
            {
                palIdx = 0x2f;
            }
        }
        menu_init_rpk_item_8003DDCC(&gMenuLeftItems_800BD5A0[i], imgIdx, palIdx);
    }
}

MenuMan_Inventory_14h_Unk * menu_rpk_8003B5E0(int index)
{
    return &gMenuLeftItems_800BD5A0[gMenuItemRpkInfo_8009E484[index].field_4_rpk_idx - 12];
}

// https://decomp.me/scratch/txHAy
// G0 function in a G8 file
#pragma INCLUDE_ASM("asm/menu_8003B614.s") // 188 bytes

int menu_inventory_Is_Item_Disabled_8003B6D0(int item)
{
    int bit;
    
    if ((GM_WeaponTypes_8009D580[GM_CurrentWeaponId + 1] & 0x200) &&
        (GM_ItemTypes_8009D598[item + 1] & 1))
    {
        return 1;
    }

    if (GM_PlayerStatus_800ABA50 & 0x42)
    {
        if ((item == ITEM_C_BOX_A) ||
            (item == ITEM_C_BOX_B) ||
            (item == ITEM_C_BOX_C))
        {     
            return 1;   
        }
    }

    if (dword_8009F46C != 0)
    {
        if ((item == ITEM_SCOPE)   ||
            (item == ITEM_C_BOX_A) ||
            (item == ITEM_C_BOX_B) ||
            (item == ITEM_C_BOX_C) ||
            (item == ITEM_CAMERA))
        {
            return 1;
        }
    }

    bit = 1 << item;
    return (GM_DisableItem_800ABA28 & bit) != 0;
}

void menu_8003B794(Actor_MenuMan *pActor, unsigned int *pOt, int id)
{
    RECT pal_rect;
    RECT img_rect;
    Menu_rpk_item *pPalItem;
    Menu_rpk_item *pImgItem;
    SPRT *pSprt;
    
    pPalItem = menu_rpk_get_pal_8003DD9C(id * 2 + 33);
    pImgItem = menu_rpk_get_img_8003DDB4(id * 2 + 34);

    pal_rect.x = 960;
    pal_rect.y = 336;
    pal_rect.w = 16;
    pal_rect.h = 1;
    LoadImage_8008FB10(&pal_rect, pPalItem->field_4_pixel_ptr);

    img_rect.x = 960;
    img_rect.y = 337;
    img_rect.w = pImgItem->field_2_w;
    img_rect.h = pImgItem->field_3_h;
    LoadImage_8008FB10(&img_rect, pImgItem->field_4_pixel_ptr);
    
    pSprt = (SPRT *)pActor->field_20_otBuf->mPrimBuf.mFreeLocation;
    pActor->field_20_otBuf->mPrimBuf.mFreeLocation = (unsigned char *)(pSprt + 1);

    pSprt->v0 = 81;
    pSprt->x0 = 230;
    pSprt->u0 = 0;
    pSprt->y0 = 116;
    pSprt->w = pImgItem->field_2_w * 4;
    pSprt->h = pImgItem->field_3_h;
    LSTORE(0x80808080, &pSprt->r0);
    pSprt->clut = getClut(pal_rect.x, pal_rect.y);
    setSprt(pSprt);
    addPrim(pOt, pSprt);
}

#pragma INCLUDE_ASM("asm/menu_inventory_left_helper_8003B8F0.s") // 764 bytes

void menu_8003BBEC(Actor_MenuMan *pActor)
{
    Menu_Item_Unknown *temp_v0 = pActor->field_1DC_menu_left.field_C_alloc;
    int index;
    short *pLinkVar;

    pActor->field_1DC_menu_left.field_10 = NULL;

    AssignXYFromVec_8003D1B8(&pActor->field_1DC_menu_left.field_0, &temp_v0->field_20_array[temp_v0->field_0_main.field_4_selected_idx]);

    if (pActor->field_1DC_menu_left.field_0.field_2_current_amount <= 0)
    {
        pActor->field_1DC_menu_left.field_0.field_0_item_id_idx = ITEM_NONE;
    }

    index = pActor->field_1DC_menu_left.field_0.field_0_item_id_idx;
    pLinkVar = linkvarbuf;
    
    if ((index >= 0) && !menu_inventory_Is_Item_Disabled_8003B6D0(index))
    {
        pLinkVar[15] = index;
        sub_8003CFE0(menu_rpk_8003B5E0(index), 0);
        pActor->field_1DC_menu_left.field_11 = pLinkVar[15];
    }
    else
    {
        if (index != ITEM_NONE)
        {
            dword_800ABAD0 = index;
        }

        GM_CurrentItemId = ITEM_NONE;
        pActor->field_1DC_menu_left.field_0.field_0_item_id_idx = ITEM_NONE;
    }

    pActor->field_1DC_menu_left.field_12_flashingAnimationFrame = 10;

    menu_panel_free_8003D184(pActor->field_1DC_menu_left.field_C_alloc);
    menu_font_kill_8003FC0C();

    GM_Sound_80032968(0, 63, 20);
}

#pragma INCLUDE_ASM("asm/menu_inventory_left_update_helper_8003BCD4.s") // 584 bytes
#pragma INCLUDE_ASM("asm/menu_inventory_left_update_helper2_8003BF1C.s") // 816 bytes
#pragma INCLUDE_ASM("asm/menu_inventory_left_update_helper3_8003C24C.s") // 672 bytes
#pragma INCLUDE_ASM("asm/menu_inventory_left_update_helper4_8003C4EC.s") // 1136 bytes
#pragma INCLUDE_ASM("asm/menu_inventory_left_update_8003C95C.s") // 572 bytes

int sub_8003CB98(struct Actor_MenuMan *pActor)
{
    int field_0_item_id_idx; // $a0
    MenuMan_Inventory_14h_Unk *pItem; // $v0
    int result;

    menu_restore_nouse_80043470();
    field_0_item_id_idx = pActor->field_1DC_menu_left.field_0.field_0_item_id_idx;
    result = -1;
    if ( field_0_item_id_idx != ITEM_NONE
      || (field_0_item_id_idx = pActor->field_1DC_menu_left.field_11, field_0_item_id_idx != ITEM_NONE) )
    {
        pItem = menu_rpk_8003B5E0(field_0_item_id_idx);
        result = sub_8003CFE0(pItem, 0);
    }
    return result;
}

void menu_inventory_left_8003CBF0(struct Actor_MenuMan *menuMan)
{
    short val = -1;
    menuMan->m7FnPtrs_field_2C[2] = (TMenuUpdateFn)menu_inventory_left_update_8003C95C;
    menuMan->field_1DC_menu_left.field_0.field_0_item_id_idx = val;
    menuMan->field_1DC_menu_left.field_10 = 0;
    menuMan->field_1DC_menu_left.field_0.field_4 = 0;
    menuMan->field_1DC_menu_left.field_0.field_6 = 1;
    menuMan->field_1DC_menu_left.field_11 = val;
    menuMan->field_28_flags |= 4;
    dword_800ABAD0 = 0;
    sub_8003D6A8(&menuMan->field_1DC_menu_left, 0, (int *)menu_inventory_left_helper_8003B8F0);
    menu_sub_8003B568();
    sub_8003CB98(menuMan);
    menu_init_nouse_800434A8();
}

void menu_left_kill_8003CC74(Actor_MenuMan *pMenu)
{
    pMenu->field_28_flags &= ~4u;
}
