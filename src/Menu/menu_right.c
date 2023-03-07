#include "linker.h"
#include "menuman.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "libgcl/libgcl.h"
#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include "Game/camera.h"

// TODO: Move to correct header
// Functions of signature TMenuItemUnknownFn:
void sub_8003D3A4(Menu_Item_Unknown *a1, int a2);
void sub_8003D34C(Menu_Item_Unknown *a1, int a2);

u_long SECTION(".sbss") dword_800ABAD8;
u_long SECTION(".sbss") dword_800ABADC;

// menu related?

int SECTION(".sbss") dword_800ABAE0;

extern struct PANEL_CONF *dword_800AB584;
struct PANEL_CONF        *SECTION(".sdata") dword_800AB584;

extern GM_Camera GM_Camera_800B77E8;

struct PANEL_CONF *SECTION(".sdata") dword_800AB584;

Menu_rpk_item **SECTION(".sbss") gItemFile_table_800ABAE4;

extern struct PANEL_CONF *dword_800AB584;
extern menu_weapon_rpk_info  gMenuWeaponRpkInfo_8009E57C[];
extern int                   dword_8009E544[];
extern int                   GM_GameStatus_800AB3CC;

int SECTION(".sbss") dword_800ABAE8;
int SECTION(".sbss") dword_800ABAEC;
int SECTION(".sbss") gSnakeLifeYPos_800ABAF0;
int SECTION(".sbss") dword_800ABAF4;
int SECTION(".sbss") dword_800ABAF8;
int SECTION(".sbss") gRadioClut_800ABAFC;
int SECTION(".sbss") dword_800ABB00;
int SECTION(".sbss") dword_800ABB04;
int SECTION(".sbss") dword_800ABB08;
short SECTION(".sbss") word_800ABB0C;
short SECTION(".sbss") word_800ABB0E;

extern PANEL_TEXTURE gMenuRightItems_800BD888[MENU_ITEMS_RIGHT_COUNT];

#define OffsetToPointer(offset, valueToAdd) *((unsigned int *)offset) = (int)valueToAdd + *((unsigned int *)offset);

extern int           dword_800ABAD0;
int SECTION(".sbss") dword_800ABAD0;

void sub_8003CC88()
{
    dword_800ABAD0 = 0;
}

#pragma INCLUDE_ASM("asm/Menu/sub_8003CC94.s") // 428 bytes

static inline int sub_8003CE40_index()
{
    return -1;
}

void sub_8003CE40(PANEL_TEXTURE *items, int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        items->field_8_index = sub_8003CE40_index();
        items->field_C_uvclut = 0;
        items++;
    }

    dword_800ABAD8 = 0;
    dword_800ABADC = 0;
}

void sub_8003CE78(void)
{
    dword_800ABADC = 0;
}

#pragma INCLUDE_ASM("asm/Menu/sub_8003CE84.s") // 116 bytes
void sub_8003CE84();

#pragma INCLUDE_ASM("asm/Menu/sub_8003CEF8.s") // 232 bytes
#pragma INCLUDE_ASM("asm/Menu/sub_8003CFE0.s") // 144 bytes
#pragma INCLUDE_ASM("asm/Menu/sub_8003D070.s") // 96 bytes

void menu_init_sprt_8003D0D0(SPRT *pPrim, PANEL_TEXTURE *pPanelTex, int offset_x, int offset_y)
{
    pPrim->x0 = pPanelTex->field_9_xofs + offset_x;
    pPrim->y0 = pPanelTex->field_A_yofs + offset_y;
    LSTORE(pPanelTex->field_C_uvclut, &pPrim->u0);
    pPrim->w = pPanelTex->field_10_w;
    pPrim->h = pPanelTex->field_12_h;
}

Menu_Item_Unknown *menu_alloc_panel_8003D124(int count)
{
    const int          totalLen = (sizeof(PANEL) * count) + sizeof(Menu_Item_Unknown_Main);
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

void AssignXY_8003D1A8(PANEL *pPanel, int idx, short amount)
{
    pPanel->field_0_id = idx;
    pPanel->field_2_num = amount;
    pPanel->field_6_current = 0;
}

void AssignXYFromVec_8003D1B8(PANEL *pPanel, PANEL *pPanel2)
{
    pPanel->field_0_id = pPanel2->field_0_id;
    pPanel->field_2_num = pPanel2->field_2_num;
    pPanel->field_6_current = 1;
    pPanel->field_4_pos = 0;
}

void sub_8003D1DC(Menu_Item_Unknown *pMenuItem)
{
    int array_count, array_half_count;
    int i;

    array_count = pMenuItem->field_0_main.field_0_array_count;
    array_half_count = array_count / 2;

    pMenuItem->field_20_array[pMenuItem->field_0_main.field_4_selected_idx].field_4_pos = 0;
    pMenuItem->field_0_main.field_8 = array_half_count * 256 + 128;
    for (i = 1; i <= array_half_count; i++)
    {
        int idx = pMenuItem->field_0_main.field_4_selected_idx + i;
        if (idx >= pMenuItem->field_0_main.field_0_array_count)
        {
            idx -= pMenuItem->field_0_main.field_0_array_count;
        }

        // TODO: pMenuItem->field_20_array[idx] did not match
        (idx + pMenuItem->field_20_array)->field_4_pos = i * 256;
    }

    array_half_count = array_count - (array_half_count + 1);
    pMenuItem->field_0_main.field_C = -(array_half_count * 256 + 128);
    for (i = -1; i >= -array_half_count; i--)
    {
        int idx = pMenuItem->field_0_main.field_4_selected_idx + i;
        if (idx < 0)
        {
            idx += pMenuItem->field_0_main.field_0_array_count;
        }

        // TODO: pMenuItem->field_20_array[idx] did not match
        (idx + pMenuItem->field_20_array)->field_4_pos = i * 256;
    }
}

extern const char aPanelMakeError[];

int menu_panel_8003D2BC(Menu_Item_Unknown *pMenu, int itemId)
{
    int i; // $v1

    i = pMenu->field_0_main.field_0_array_count - 1;
    pMenu->field_0_main.field_4_selected_idx = -1;
  
    while(i >= 0)
    {
        if ( pMenu->field_20_array[i].field_0_id == itemId )
        {
            pMenu->field_0_main.field_4_selected_idx = i;
        }
        i--;
    }
    
    if ( pMenu->field_0_main.field_4_selected_idx < 0 )
    {
        mts_printf_8008BBA0(aPanelMakeError);
        pMenu->field_0_main.field_4_selected_idx = 0;
    }
    
    pMenu->field_0_main.field_18 = -1;
    sub_8003D1DC(pMenu);
    return 1;
}

void sub_8003D34C(Menu_Item_Unknown *pItem, int a2)
{
  int count;
  int l_8;
  PANEL *pIter;
  int tmp;

  count = pItem->field_0_main.field_0_array_count;
  l_8 = pItem->field_0_main.field_8;
  pIter = &pItem->field_20_array[0];  
  while(count > 0)
  {
    pIter->field_4_pos += a2;
    if (pIter->field_4_pos >= l_8)
    {
        tmp = (pIter->field_4_pos - l_8);
        pIter->field_4_pos =pItem->field_0_main.field_C + tmp;
    }
    --count;
      pIter++;
  }
}

void sub_8003D3A4(Menu_Item_Unknown *pItem, int a2)
{
  int count;
  int l_8;
  PANEL *pIter;
  int tmp;

  count = pItem->field_0_main.field_0_array_count;
  l_8 = pItem->field_0_main.field_C;
  pIter = &pItem->field_20_array[0];  
  while(count > 0)
  {
    pIter->field_4_pos += a2;
    if (l_8 >= pIter->field_4_pos)
    {
        tmp = (pIter->field_4_pos - l_8);
        pIter->field_4_pos =pItem->field_0_main.field_8 + tmp;
    }
    --count;
      pIter++;
  }
}

void sub_8003D3FC(Menu_Item_Unknown *pMenu, int a2)
{
    int v3;
    int count;
    
    count = pMenu->field_0_main.field_0_array_count;
    if (a2 > 0) 
    {
        v3 = count - 1; 
    }
    else 
    {
        v3 =  count + 1;
    }
    pMenu->field_0_main.field_4_selected_idx = (pMenu->field_0_main.field_4_selected_idx + v3) % pMenu->field_0_main.field_0_array_count;
}

void sub_8003D44C(Menu_Item_Unknown *pMenu, int a2, int a3)
{
    TMenuItemUnknownFn pFn;

    pMenu->field_0_main.field_10 = a3;
    pMenu->field_0_main.field_14_fn_ctx = (a2 << 8) / a3;
    if ( a2 > 0 )
    {
        pFn = sub_8003D34C;
    }
    else
    {
        pFn = sub_8003D3A4;
    }
    pMenu->field_0_main.field_1C_fn = pFn;
    sub_8003D3FC(pMenu, a2);
    GM_Sound_80032968(0, 63, 23u);
}

int sub_8003D4CC(Menu_Item_Unknown *pMenuItem)
{
    if (pMenuItem->field_0_main.field_10 > 0)
    {
        pMenuItem->field_0_main.field_10--;
        if (pMenuItem->field_0_main.field_10 != 0)
        {
            pMenuItem->field_0_main.field_1C_fn(pMenuItem, pMenuItem->field_0_main.field_14_fn_ctx);
            return 1;
        }
        sub_8003D1DC(pMenuItem);
    }
    return 0;
}

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

int sub_8003D568()
{
    dword_800ABAE0 -= 0x40;

    if (dword_800ABAE0 < 1)
    {
        dword_800ABAE0 = 0;
        return 1;
    }

    return 0;
}

void sub_8003D594(PANEL_CONF *pPanelConf, int pos, int *xoff, int *yoff)
{
    int y1;
    int x1;
    int temp_lo;
    int temp_v1;
    int var_v0;

    x1 = pPanelConf->field_0_xOffset;
    y1 = pPanelConf->field_2_yOffset;
    if (pos == 0)
    {
        *xoff = x1;
        *yoff = y1;
        return;
    }

    *xoff = x1;
    temp_v1 = dword_800ABAE0 * 0x28;
    temp_lo = pos * temp_v1;
    var_v0 = temp_lo / 65536;

    *yoff = y1 - var_v0;
}

void sub_8003D5F0(PANEL_CONF *pPanelConf, int pos, int *xoff, int *yoff)
{
    int y1;
    int x1;
    int temp_lo;
    int temp_v1;
    int var_v0;

    x1 = pPanelConf->field_0_xOffset;
    y1 = pPanelConf->field_2_yOffset;
    if (pos == 0)
    {
        *xoff = x1;
        *yoff = y1;
        return;
    }

    temp_v1 = dword_800ABAE0 * 0x38;
    temp_lo = pos * temp_v1;
    var_v0 = temp_lo / 65536;

    *xoff = x1 - var_v0;
    *yoff = y1;
}

void sub_8003D64C(PANEL_CONF *pPanelConf, int pos, int *xoff, int *yoff)
{
    int y1;
    int x1;
    int temp_lo;
    int temp_v1;
    int var_v0;

    x1 = pPanelConf->field_0_xOffset;
    y1 = pPanelConf->field_2_yOffset;
    if (pos == 0)
    {
        *xoff = x1;
        *yoff = y1;
        return;
    }

    temp_v1 = dword_800ABAE0 * 0x38;
    temp_lo = pos * temp_v1;
    var_v0 = temp_lo / 65536;

    *xoff = x1 + var_v0;
    *yoff = y1;
}

extern struct PANEL_CONF stru_8009E544[];

void sub_8003D6A8(struct menu_left_right *pMenuLeft, int bIsRight, void *pUpdateFn)
{
    struct PANEL_CONF *pPanelConf;

    pPanelConf = &stru_8009E544[bIsRight];
    pMenuLeft->field_8_panel_conf = pPanelConf;
    pPanelConf->field_18_pFnUpdate = pUpdateFn;
}

void sub_8003D6CC(menu_left_right *pLeftRight, GV_PAD *pPad)
{
    int                bVar1;
    int                arg2_1;
    int                arg2_2;
    Menu_Item_Unknown *pMenuItem;
    PANEL_CONF     *pPanelConf;

    pMenuItem = pLeftRight->field_C_alloc;
    pPanelConf = pLeftRight->field_8_panel_conf;
    bVar1 = sub_8003D4CC(pMenuItem);
    if (pPad->press & (pPanelConf->field_8 | pPanelConf->field_C))
    {
        arg2_1 = -1;
        if (pPad->press & pPanelConf->field_8)
        {
            arg2_1 = 1;
        }
        if (!bVar1)
        {
            sub_8003D44C(pMenuItem, arg2_1, 6);
            pMenuItem->field_0_main.field_18 = 10;
        }
        else if (pMenuItem->field_0_main.field_18 > 0)
        {
            pMenuItem->field_0_main.field_18 = 0;
        }
    }
    if (pMenuItem->field_0_main.field_18 >= 0)
    {
        if (pPad->status & (pPanelConf->field_8 | pPanelConf->field_C))
        {
            arg2_2 = -1;
            if (pPad->status & pPanelConf->field_8)
            {
                arg2_2 = 1;
            }
            if (!bVar1)
            {
                pMenuItem->field_0_main.field_18--;
                if (pMenuItem->field_0_main.field_18 < 0)
                {
                    sub_8003D44C(pMenuItem, arg2_2, 4);
                    pMenuItem->field_0_main.field_18 = 0;
                }
            }
        }
        else
        {
            pMenuItem->field_0_main.field_18 = 10;
        }
    }
}

void menu_8003D7DC(Actor_MenuMan *pActor, int param_2, menu_left_right *pSubMenu)
{
    int                field_8, pos, field_C;
    PANEL_CONF        *pPanelConf;
    Menu_Item_Unknown *pItem;
    PANEL             *pPanel;
    int                array_count;
    int                i;
    int                xoff, yoff;
    int                xoff_2, yoff_2;
    int                xoff_3, yoff_3;

    sub_8003CE78();
    pItem = pSubMenu->field_C_alloc;
    pPanel = &pItem->field_20_array[pItem->field_0_main.field_4_selected_idx];
    pPanelConf = pSubMenu->field_8_panel_conf;

    pos = pPanel->field_4_pos;
    array_count = pItem->field_0_main.field_0_array_count;
    if (pos >= 0)
    {
        pPanelConf->field_10_pFn2(pPanelConf, pos, &xoff, &yoff);
    }
    else
    {
        pos = -pos;
        pPanelConf->field_14_pFn2(pPanelConf, pos, &xoff, &yoff);
    }
    pPanelConf->field_18_pFnUpdate(pActor, param_2, xoff, yoff, pPanel);

    array_count--;
    field_8 = pItem->field_0_main.field_8;
    if (1024 < field_8)
    {
        field_8 = 1152;
    }
    for (i = 1; 0 < array_count; i++, array_count--)
    {
        int    array_count_2, idx, pos_2;
        PANEL *pPanel_2;
        array_count_2 = pItem->field_0_main.field_0_array_count;
        idx = pItem->field_0_main.field_4_selected_idx + i;
        if (array_count_2 <= idx)
        {
            idx = idx - array_count_2;
        }
        pPanel_2 = &pItem->field_20_array[idx];
        pos_2 = pPanel_2->field_4_pos;
        if (pos_2 < 0 || pos_2 > field_8)
        {
            break;
        }
        pPanelConf->field_10_pFn2(pPanelConf, pos_2, &xoff_2, &yoff_2);
        pPanelConf->field_18_pFnUpdate(pActor, param_2, xoff_2, yoff_2, pPanel_2);
    }

    field_C = pItem->field_0_main.field_C;
    if (1024 < -field_C)
    {
        field_C = -1152;
    }

    for (i = -1; 0 < array_count; i--, array_count--)
    {
        int    idx, pos_2;
        PANEL *pPanel_2;
        idx = pItem->field_0_main.field_4_selected_idx + i;
        if (idx < 0)
        {
            idx = idx + pItem->field_0_main.field_0_array_count;
        }
        pPanel_2 = &pItem->field_20_array[idx];
        pos_2 = pPanel_2->field_4_pos;
        if (0 < pos_2 || pos_2 < field_C)
        {
            break;
        }
        pPanelConf->field_14_pFn2(pPanelConf, -pos_2, &xoff_3, &yoff_3);
        pPanelConf->field_18_pFnUpdate(pActor, param_2, xoff_3, yoff_3, pPanel_2);
    }
    sub_8003CE84();
}

void menu_sub_menu_update_8003DA0C(struct Actor_MenuMan *pActor, int a2, struct menu_left_right *pSubMenu)
{
    if ((GM_GameStatus_800AB3CC & 0x1020) != 0x20)
    {
        pSubMenu->field_8_panel_conf->field_18_pFnUpdate(pActor, a2, pSubMenu->field_8_panel_conf->field_0_xOffset,
                                                    pSubMenu->field_8_panel_conf->field_2_yOffset, &pSubMenu->field_0_current);
    }
}

void sub_8003DA60(struct Actor_MenuMan *pActor, int a2, struct menu_left_right *pLeftRight, int off1, int off2)
{
    pLeftRight->field_8_panel_conf->field_18_pFnUpdate(pActor, a2, pLeftRight->field_8_panel_conf->field_0_xOffset + off1,
                                                  pLeftRight->field_8_panel_conf->field_2_yOffset + off2, &pLeftRight->field_0_current);
}

int menu_8003DA9C(struct menu_left_right *pMenu, unsigned short *input)
{
    struct PANEL_CONF *pPanelConf; // $a0

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

    pPanelConf = pMenu->field_8_panel_conf;

    if ((*input & pPanelConf->field_4_input) == 0)
    {
        goto ret_zero;
    }
    dword_800AB584 = pPanelConf;

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

void Menu_item_render_frame_rects_8003DBAC(MenuGlue *pGlue, int x, int y, int param_4)
{
    TILE     *tile;
    DR_TPAGE *tpage;

    menu_render_rect_8003DB2C(pGlue, x, y, 47, 1, 0);
    menu_render_rect_8003DB2C(pGlue, x - 4, y, 14, 20, 0);
    menu_render_rect_8003DB2C(pGlue, x + 45, y + 1, 2, 19, 0);
    menu_render_rect_8003DB2C(pGlue, x - 4, y + 20, 51, 9, 0);

    tile = menu_render_rect_8003DB2C(pGlue, x + 10, y + 1, 35, 19, (param_4 != 0 ?: 0) << 23);
    setSemiTrans(tile, 1);

    tpage = (DR_TPAGE *)pGlue->mPrimBuf.mFreeLocation;
    pGlue->mPrimBuf.mFreeLocation += sizeof(DR_TPAGE);

    setDrawTPage(tpage, 1, 0, 0x1f);
    addPrim(pGlue->mPrimBuf.mOt, tpage);
}

Menu_rpk_item **menu_rpk_init_8003DD1C(const char *pFileName)
{
    Menu_rpk_item **pEnd;
    Menu_rpk_item **pIter;
    int             i;
    int             count;

    // At the start of the game, "item.rpk" file is loaded (5d43.r)
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

void menu_init_rpk_item_8003DDCC(PANEL_TEXTURE *pPanelTex, int imgIdx, int palIdx)
{
    Menu_rpk_item *pPal;
    Menu_rpk_item *pImg;

    pPal = menu_rpk_get_pal_8003DD9C(palIdx);
    pImg = menu_rpk_get_img_8003DDB4(imgIdx);
    pPanelTex->field_9_xofs = pImg->field_0_x - 2;
    pPanelTex->field_A_yofs = pImg->field_1_y - 2;
    pPanelTex->field_10_w = pImg->field_2_w * 4;
    pPanelTex->field_12_h = pImg->field_3_h;
    pPanelTex->field_0_pixels = &pImg->field_4_pixel_ptr[0];
    pPanelTex->field_4_word_ptr_pixels = &pPal->field_4_pixel_ptr[0];
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

PANEL_TEXTURE *menu_right_get_weapon_rpk_info_8003DED8(int weaponIdx)
{
    int rpkIdx;
    if ((weaponIdx == WEAPON_SOCOM) && !GM_SilencerFlag)
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

#pragma INCLUDE_ASM("asm/Menu/sub_8003DF30.s") // 256 bytes
#pragma INCLUDE_ASM("asm/Menu/menu_right_update_helper2_helper_8003E030.s") // 184 bytes
#pragma INCLUDE_ASM("asm/Menu/menu_right_init_helper_8003E0E8.s") // 712 bytes
#pragma INCLUDE_ASM("asm/Menu/menu_right_update_helper2_helper2_8003E3B0.s") // 264 bytes
#pragma INCLUDE_ASM("asm/Menu/menu_right_update_helper_8003E4B8.s") // 444 bytes
#pragma INCLUDE_ASM("asm/Menu/menu_right_update_helper2_8003E674.s") // 796 bytes
#pragma INCLUDE_ASM("asm/Menu/menu_right_update_8003E990.s") // 588 bytes

void sub_8003EBDC(struct Actor_MenuMan *menuMan)
{
    PANEL_TEXTURE *pPanelTex;
    int            weapon_index;

    weapon_index = menuMan->field_1F0_menu_right.field_0_current.field_0_id;
    if ((weapon_index != -1) ||
        (weapon_index = *(signed char *)&((menuMan->field_1F0_menu_right).field_11), weapon_index != -1))
    {
        pPanelTex = menu_right_get_weapon_rpk_info_8003DED8(weapon_index);
        sub_8003CFE0(pPanelTex, 1);
    }
}

void menu_right_init_8003EC2C(struct Actor_MenuMan *menuMan)

{
    short val = -1;
    menuMan->m7FnPtrs_field_2C[1] = menu_right_update_8003E990;
    menuMan->field_1F0_menu_right.field_0_current.field_0_id = val;
    menuMan->field_1F0_menu_right.field_10_state = 0;
    menuMan->field_1F0_menu_right.field_12_flashingAnimationFrame = 0;
    menuMan->field_1F0_menu_right.field_0_current.field_4_pos = 0;
    menuMan->field_1F0_menu_right.field_0_current.field_6_current = 1;
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
