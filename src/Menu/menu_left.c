#include "Game/linkvarbuf.h"
#include "libdg/libdg.h"
#include "menuman.h"
#include "radio.h"
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

extern const char aNoItem[];
extern const char aLv[];

void sub_8003CEF8(MenuMan_Inventory_14h_Unk *a1);
void menu_number_draw_number2_80042FC0(Actor_MenuMan *pActor, int xpos, int ypos, int current, int total);
void menu_init_sprt_8003D0D0(SPRT *pPrim, MenuMan_Inventory_14h_Unk *pUnk, int offset_x, int offset_y);
int menu_number_draw_string_800430F0(Actor_MenuMan *pActor, int a2, int xpos, int ypos, const char *str, int flags);

void Menu_item_render_frame_rects_8003DBAC(MenuGlue *pGlue, int x, int y, int param_4);

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



void menu_inventory_left_helper_8003B8F0(struct Actor_MenuMan *pActor, unsigned int *pOt, int xpos, int ypos, menu_left_right *pMenuSub)
{
    int field_0_item_id_idx; // $a0
    MenuMan_Inventory_14h_Unk *pMenuSprt; // $s6
    int item_idx; // $v1
    int v12; // $a3
    MenuGlue *field_20_otBuf; // $v0
    SPRT *pIconSprt; // $s0
    int rgb; // $s1
    int bBlueBackground; // $a3
    TextConfig textConfig; // [sp+18h] [-10h] BYREF

    field_0_item_id_idx = pMenuSub->field_0.field_0_item_id_idx;
    if ( field_0_item_id_idx >= 0 )
    {
        pMenuSprt = menu_rpk_8003B5E0(field_0_item_id_idx);
        sub_8003CEF8(pMenuSprt);
        if ( menu_inventory_Is_Item_Disabled_8003B6D0(pMenuSub->field_0.field_0_item_id_idx) )
        {
            menu_draw_nouse_800435A4(pActor->field_20_otBuf, xpos, ypos);
        }
        if ( gGameState_800B4D98[69] == 1 )
        {
            item_idx = pMenuSub->field_0.field_0_item_id_idx;
            if ( item_idx == 13 || item_idx == 9 )
            {
                menu_draw_frozen_800435C8(pActor->field_20_otBuf, xpos, ypos);
            }
        }
        v12 = pMenuSub->field_0.field_0_item_id_idx;
        if ( (GM_ItemTypes_8009D598[v12 + 1] & 0x2000) != 0 )
        {
            menu_number_draw_number2_80042FC0(
                pActor,
                xpos,
                ypos + 11,
                pMenuSub->field_0.field_2_current_amount,
                GM_Items[v12  + 11]);
        }
        else if ( v12 == 17 )                   // id card
        {
            textConfig.xpos = xpos;
            textConfig.ypos = ypos + 14;
            textConfig.flags = 0;
            textConfig.colour = 0x64808080;
            menu_number_draw_string_80042BF4(pActor->field_20_otBuf, &textConfig, aLv);
            textConfig.ypos -= 2;
            menu_number_draw_80042988(pActor->field_20_otBuf, &textConfig, gGameState_800B4D98[54]);
        }
        else if ( v12 == 18 )                   // bomb
        {
            menu_number_draw_80042F78(
                pActor,
                (int)pOt,
                xpos + 10,
                ypos + 10,
                gGameState_800B4D98[55],
                0);
        }
        if ( *(int *)&pMenuSprt->field_C_u ) // uv or clut
        {
            field_20_otBuf = pActor->field_20_otBuf;
            pIconSprt = (SPRT *)field_20_otBuf->mPrimBuf.mFreeLocation;
            field_20_otBuf->mPrimBuf.mFreeLocation += 20;
            rgb = 0x404040;
            if ( !pMenuSub->field_0.field_4 )
            {
                rgb = 0x808080;
            }
            menu_init_sprt_8003D0D0(pIconSprt, pMenuSprt, xpos, ypos);
            *(int *)&pIconSprt->r0 = rgb;
            setSprt(pIconSprt);
            addPrim(pOt, pIconSprt);
        }
        menu_number_draw_string_800430F0(
            pActor,
            (int)pOt,
            xpos + 46,
            ypos + 22,
            gMenuItemRpkInfo_8009E484[pMenuSub->field_0.field_0_item_id_idx].field_0_weapon_name,
            1);
    }
    else
    {
        menu_number_draw_string_800430F0(pActor, (int)pOt, xpos + 46, ypos + 22, aNoItem, 1);
    }
    
    bBlueBackground = 0;
    if ( !pMenuSub->field_0.field_4 )
    {
        bBlueBackground = pMenuSub->field_0.field_6 == 0;
    }
    Menu_item_render_frame_rects_8003DBAC(pActor->field_20_otBuf, xpos, ypos, bBlueBackground);
}

#pragma INCLUDE_ASM("asm/menu_8003BBEC.s") // 232 bytes

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
    if ( field_0_item_id_idx != -1
      || (field_0_item_id_idx = pActor->field_1DC_menu_left.field_11, field_0_item_id_idx != -1) )
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
