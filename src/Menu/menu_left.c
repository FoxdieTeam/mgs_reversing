#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "libdg/libdg.h"
#include "menuman.h"
#include "radio.h"
#include "linker.h"
#include "psyq.h"
#include "Game/game.h"

extern PANEL_TEXTURE gMenuLeftItems_800BD5A0[];
extern menu_weapon_rpk_info      gMenuItemRpkInfo_8009E484[];

extern short                     GM_WeaponTypes_8009D580[];
extern short                     GM_ItemTypes_8009D598[];
extern int                       GM_GameStatus_800AB3CC;
extern int                       GM_PlayerStatus_800ABA50;
extern int                       GV_PauseLevel_800AB928;
extern int                       GM_DisableItem_800ABA28;

extern int                       dword_8009F46C;

extern int                       dword_800ABAD0;
int SECTION(".sbss")             dword_800ABAD0;

extern int                       dword_800AB574;
int SECTION(".sbss")             dword_800AB574;

extern int                       dword_800AB578;
int SECTION(".sbss")             dword_800AB578;

extern const char aNoItem[];
extern const char aLv[];

void sub_8003CEF8(PANEL_TEXTURE *a1);
void menu_number_draw_number2_80042FC0(Actor_MenuMan *pActor, int xpos, int ypos, int current, int total);
void menu_init_sprt_8003D0D0(SPRT *pPrim, PANEL_TEXTURE *pUnk, int offset_x, int offset_y);
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

PANEL_TEXTURE * menu_rpk_8003B5E0(int index)
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

    if (GM_PlayerStatus_800ABA50 & (PLAYER_STATUS_PRONE | PLAYER_STATUS_FIRST_PERSON_DUCT))
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
    PANEL_TEXTURE *pMenuSprt; // $s6
    MenuGlue *field_20_otBuf; // $v0
    SPRT *pIconSprt; // $s0
    int rgb; // $s1
    int bBlueBackground; // $a3
    TextConfig textConfig; // [sp+18h] [-10h] BYREF

    if ( pMenuSub->field_0_current.field_0_id >= 0 )
    {
        pMenuSprt = menu_rpk_8003B5E0(pMenuSub->field_0_current.field_0_id);
        sub_8003CEF8(pMenuSprt);
        if ( menu_inventory_Is_Item_Disabled_8003B6D0(pMenuSub->field_0_current.field_0_id) )
        {
            menu_draw_nouse_800435A4(pActor->field_20_otBuf, xpos, ypos);
        }
        if ( GM_FrozenItemsState == 1 )
        {
            if ( pMenuSub->field_0_current.field_0_id == ITEM_RATION ||
                 pMenuSub->field_0_current.field_0_id == ITEM_KETCHUP )
            {
                menu_draw_frozen_800435C8(pActor->field_20_otBuf, xpos, ypos);
            }
        }

        if ( GM_ItemTypes_8009D598[pMenuSub->field_0_current.field_0_id + 1] & ITEMTYPE_CONSUMABLE )
        {
            menu_number_draw_number2_80042FC0(
                pActor,
                xpos,
                ypos + 11,
                pMenuSub->field_0_current.field_2_num,
                GM_ItemsMax[pMenuSub->field_0_current.field_0_id]);
        }
        else if ( pMenuSub->field_0_current.field_0_id == ITEM_CARD )
        {
            textConfig.xpos = xpos;
            textConfig.ypos = ypos + 14;
            textConfig.flags = 0;
            textConfig.colour = 0x64808080;
            menu_number_draw_string_80042BF4(pActor->field_20_otBuf, &textConfig, aLv);
            textConfig.ypos -= 2;
            menu_number_draw_80042988(pActor->field_20_otBuf, &textConfig, GM_Items[ITEM_CARD]);
        }
        else if ( pMenuSub->field_0_current.field_0_id == ITEM_TIMER_B )
        {
            menu_number_draw_80042F78(
                pActor,
                (int)pOt,
                xpos + 10,
                ypos + 10,
                GM_Items[ITEM_TIMER_B],
                0);
        }

        if ( pMenuSprt->field_C_uvclut )
        {
            field_20_otBuf = pActor->field_20_otBuf;
            pIconSprt = (SPRT *)field_20_otBuf->mPrimBuf.mFreeLocation;
            field_20_otBuf->mPrimBuf.mFreeLocation += sizeof(SPRT);
            
            if ( !pMenuSub->field_0_current.field_4_pos )
            {
                rgb = 0x808080;
            }
            else
            {
                rgb = 0x404040;
            }
            menu_init_sprt_8003D0D0(pIconSprt, pMenuSprt, xpos, ypos);
            LSTORE(rgb, &pIconSprt->r0);
            setSprt(pIconSprt);
            addPrim(pOt, pIconSprt);
        }
        menu_number_draw_string_800430F0(
            pActor,
            (int)pOt,
            xpos + 46,
            ypos + 22,
            gMenuItemRpkInfo_8009E484[pMenuSub->field_0_current.field_0_id].field_0_weapon_name,
            1);
    }
    else
    {
        menu_number_draw_string_800430F0(pActor, (int)pOt, xpos + 46, ypos + 22, aNoItem, 1);
    }
    
    if ( !pMenuSub->field_0_current.field_4_pos )
    {
        bBlueBackground = pMenuSub->field_0_current.field_6_current == 0;
    }
    else
    {
        bBlueBackground = 0;
    }

    Menu_item_render_frame_rects_8003DBAC(pActor->field_20_otBuf, xpos, ypos, bBlueBackground);
}

void menu_8003BBEC(Actor_MenuMan *pActor)
{
    Menu_Item_Unknown *temp_v0 = pActor->field_1DC_menu_left.field_C_alloc;
    int index;
    short *pLinkVar;

    pActor->field_1DC_menu_left.field_10_state = 0;

    AssignXYFromVec_8003D1B8(&pActor->field_1DC_menu_left.field_0_current, &temp_v0->field_20_array[temp_v0->field_0_main.field_4_selected_idx]);

    if (pActor->field_1DC_menu_left.field_0_current.field_2_num <= 0)
    {
        pActor->field_1DC_menu_left.field_0_current.field_0_id = ITEM_NONE;
    }

    index = pActor->field_1DC_menu_left.field_0_current.field_0_id;
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
        pActor->field_1DC_menu_left.field_0_current.field_0_id = ITEM_NONE;
    }

    pActor->field_1DC_menu_left.field_12_flashingAnimationFrame = 10;

    menu_panel_free_8003D184(pActor->field_1DC_menu_left.field_C_alloc);
    menu_font_kill_8003FC0C();

    GM_Sound_80032968(0, 63, 20);
}
    
int menu_inventory_left_update_helper_8003BCD4(Actor_MenuMan *pActor)
{
    int activeItems;
    int i;
    Menu_Item_Unknown *pPanels;
    int cardVal;
    int panelIndex;

    if (!(GM_GameStatus_800AB3CC & 0x40000))
    {
        activeItems = 0;

        for (i = 0; i < GM_TotalItems; i++)
        {
            if (GM_Items[i] > 0)
            {
                activeItems++;
            }
        }

        pPanels = menu_alloc_panel_8003D124(activeItems + 1);
        pActor->field_1DC_menu_left.field_C_alloc = pPanels;

        if (!pPanels)
        {
            return 0;
        }

        if ((GM_CurrentItemId != ITEM_NONE) && (GM_CurrentItemId != ITEM_CARD))
        {
            dword_800ABAD0 = GM_CurrentItemId;
        }
        else if (dword_800ABAD0 < 0)
        {
            dword_800ABAD0 = 0;
        }

        cardVal = -1;

        if (GM_CardFlag > 0)
        {
            cardVal = 0;
        }
    
        panelIndex = 0;

        for (i = 0; i < GM_TotalItems; i++)
        {
            if (i == dword_800ABAD0)
            {
                AssignXY_8003D1A8(&pPanels->field_20_array[panelIndex], ITEM_NONE, 1);
    
                panelIndex++;

                if (cardVal == 0)
                {
                    if (GM_CurrentItemId == ITEM_NONE)
                    {
                        AssignXY_8003D1A8(&pPanels->field_20_array[panelIndex], ITEM_CARD, GM_Items[ITEM_CARD]);
                        panelIndex++;
                    }
                    else
                    {
                        cardVal = 1;
                    }
                }
            }

            if ((GM_Items[i] > 0) && (i != ITEM_CARD))
            {
                AssignXY_8003D1A8(&pPanels->field_20_array[panelIndex], i, GM_Items[i]);
                panelIndex++;
            }
    
            if (cardVal > 0)
            {
                AssignXY_8003D1A8(&pPanels->field_20_array[panelIndex], ITEM_CARD, GM_Items[ITEM_CARD]);
                panelIndex++;
                cardVal = 0;
            }
        }
    }
    else
    {
        pPanels = menu_alloc_panel_8003D124(1);
        pActor->field_1DC_menu_left.field_C_alloc = pPanels;

        if (!pPanels)
        {
            return 0;
        }

        AssignXY_8003D1A8(&pPanels->field_20_array[0], ITEM_NONE, 1);
    }

    if (!sub_8003F84C(0))
    {
        menu_panel_free_8003D184(pPanels);
        return 0;
    }
        
    dword_800AB578 = 0;
    dword_800AB574 = 0;
    pActor->field_1DC_menu_left.field_10_state = 2;

    sub_8003D520();
    sub_8003CE40(gMenuLeftItems_800BD5A0, MENU_ITEMS_LEFT_COUNT);
    sub_8003D2BC(pActor->field_1DC_menu_left.field_C_alloc, pActor->field_1DC_menu_left.field_0_current.field_0_id);
    GM_Sound_80032968(0, 63, 21);
    return 1;
}

#pragma INCLUDE_ASM("asm/menu_inventory_left_update_helper2_8003BF1C.s") // 816 bytes
#pragma INCLUDE_ASM("asm/menu_inventory_left_update_helper3_8003C24C.s") // 672 bytes
#pragma INCLUDE_ASM("asm/menu_inventory_left_update_helper4_8003C4EC.s") // 1136 bytes
#pragma INCLUDE_ASM("asm/menu_inventory_left_update_8003C95C.s") // 572 bytes

int sub_8003CB98(struct Actor_MenuMan *pActor)
{
    int field_0_item_id_idx; // $a0
    PANEL_TEXTURE *pItem; // $v0
    int result;

    menu_restore_nouse_80043470();
    field_0_item_id_idx = pActor->field_1DC_menu_left.field_0_current.field_0_id;
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
    menuMan->field_1DC_menu_left.field_0_current.field_0_id = val;
    menuMan->field_1DC_menu_left.field_10_state = 0;
    menuMan->field_1DC_menu_left.field_0_current.field_4_pos = 0;
    menuMan->field_1DC_menu_left.field_0_current.field_6_current = 1;
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
