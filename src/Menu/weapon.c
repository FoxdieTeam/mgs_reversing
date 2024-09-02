#include "linker.h"
#include "menuman.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "libgcl/libgcl.h"
#include <sys/types.h>
#include <libgte.h>
#include "Game/camera.h"
#include "Menu/radio.h"
#include "SD/g_sound.h"

// TODO: Move to correct header
// Functions of signature TMenuItemUnknownFn:
void sub_8003D3A4(Menu_Item_Unknown *a1, int a2);
void sub_8003D34C(Menu_Item_Unknown *a1, int a2);

u_long SECTION(".sbss") dword_800ABAD8;
u_long SECTION(".sbss") dword_800ABADC;

// menu related?

int SECTION(".sbss") dword_800ABAE0;

extern GM_Camera GM_Camera_800B77E8;

Menu_rpk_item **SECTION(".sbss") gItemFile_table_800ABAE4;

PANEL_CONF *dword_800AB584 = NULL;

extern int dword_8009E544[];
extern int GM_GameStatus_800AB3CC;

int                       SECTION(".sbss") dword_800ABAE8;
int                       SECTION(".sbss") dword_800ABAEC;
int                       SECTION(".sbss") gSnakeLifeYPos_800ABAF0;
int                       SECTION(".sbss") dword_800ABAF4;
int                       SECTION(".sbss") dword_800ABAF8;
int                       SECTION(".sbss") gRadioClut_800ABAFC;
int                       SECTION(".sbss") dword_800ABB00;
char                     *SECTION(".sbss") dword_800ABB04;
MenuCallbackProc_800ABB08 SECTION(".sbss") gMenuCallbackProc_800ABB08;

extern PANEL_TEXTURE gMenuRightItems_800BD888[MENU_WEAPON_COUNT];

struct PANEL_CONF SECTION(".data") stru_8009E544[2] = {{16, 184, 1, 24576, 36864, sub_8003D64C, sub_8003D594, NULL},
                                                       {256, 184, 2, 12288, 49152, sub_8003D594, sub_8003D5F0, NULL}};

#define OffsetToPointer(offset, valueToAdd) *((unsigned int *)offset) = (int)valueToAdd + *((unsigned int *)offset);

extern int dword_800ABAD0;
int        SECTION(".sbss") dword_800ABAD0;

void sub_8003CC88()
{
    dword_800ABAD0 = 0;
}

extern array_800BD748_child array_800BD828[];
extern array_800BD748_child array_800BD748[];

void menu_texture_init_8003CC94(MenuWork *work)
{
    int                   i, uloop, vloop;
    int                   cy, cy2;
    int                   t1, t2;
    int                   u, v;
    array_800BD748_child *pArr;

    pArr = array_800BD748;
    i = 0;
    v = 384;
    for (vloop = 0; vloop < 3; vloop++)
    {
        u = 64;
        for (uloop = 0; uloop < 3; uloop++)
        {
            pArr->field_0_u = u;
            pArr->field_1_v = v;

            cy = (i + 4) % 8 + 480;

            pArr->field_2_clut = getClut(((i + 4) / 8 * 16 + 960), cy);

            t2 = i / 3 * 3;
            t1 = i % 3;
            pArr->field_8_rect1.x = t1 * 16 + 976;
            pArr->field_8_rect1.y = t2 * 8 + 384;

            pArr->field_8_rect1.w = 16;
            pArr->field_8_rect1.h = 24;

            pArr->field_10_rect2.x = (i + 4) / 8 * 16 + 960;
            i++;
            pArr->field_10_rect2.y = cy;
            pArr->field_10_rect2.w = 16;
            pArr->field_10_rect2.h = 1;
            pArr->field_4_panelTexture = 0;
            pArr++;
            u += 64;
        }
        v += 24;
    }
    dword_800ABAD8 = 0;
    dword_800ABADC = 0;

    pArr = array_800BD828;
    v = 384;
    for (i = 0; i < 4; i++)
    {
        pArr->field_0_u = 0;
        pArr->field_1_v = v;
        cy = i % 8 + 480;
        cy2 = cy;
        pArr->field_2_clut = getClut((i / 8) * 16 + 960, cy);
        pArr->field_8_rect1.x = 960;
        pArr->field_8_rect1.y = 384 + i * 24;
        pArr->field_8_rect1.w = 16;
        pArr->field_8_rect1.h = 24;
        pArr->field_10_rect2.x = (i / 8) * 16 + 960;
        pArr->field_10_rect2.y = cy2;
        pArr->field_10_rect2.w = 16;
        pArr->field_10_rect2.h = 1;
        pArr->field_4_panelTexture = 0;
        pArr++;
        v += 24;
    }
}

void sub_8003CE40(PANEL_TEXTURE *items, int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        items->field_8_bufid = -1;
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

void sub_8003CE84()
{
    int i;
    int bit;
    int bitmask;

    bitmask = dword_800ABAD8 & ~dword_800ABADC;
    for (bit = 1, i = 0; i < 9; bit <<= 1, i++)
    {
        if (bitmask & bit)
        {
            array_800BD748[i].field_4_panelTexture->field_C_uvclut = 0;
            array_800BD748[i].field_4_panelTexture->field_8_bufid = -1;
            array_800BD748[i].field_4_panelTexture = NULL;
            dword_800ABAD8 &= ~bit;
        }
    }
}

void sub_8003CEF8(PANEL_TEXTURE *pPanelTex)
{
    int                   i;
    int                   bit;
    int                   bitmask;
    array_800BD748_child *iter;

    if (pPanelTex->field_C_uvclut == 0)
    {
        bit = 1;
        bitmask = dword_800ABAD8;

        for (i = 0; i < 9; bit <<= 1, i++)
        {
            if (!(bitmask & bit))
            {
                iter = &array_800BD748[i];

                iter->field_4_panelTexture = pPanelTex;

                pPanelTex->field_8_bufid = i;
                pPanelTex->field_C_uvclut = LLOAD(&iter->field_0_u);

                dword_800ABAD8 |= bit;

                iter->field_8_rect1.w = pPanelTex->field_10_w / 4;
                iter->field_8_rect1.h = pPanelTex->field_12_h;
                LoadImage(&iter->field_8_rect1, pPanelTex->field_0_pixels);
                LoadImage(&iter->field_10_rect2, pPanelTex->field_4_word_ptr_pixels);

                break;
            }
        }
    }

    if (pPanelTex->field_8_bufid >= 0)
    {
        dword_800ABADC |= 1 << pPanelTex->field_8_bufid;
    }
}

void sub_8003CFE0(PANEL_TEXTURE *pPanelTex, int index)
{
    array_800BD748_child *elem;
    elem = &array_800BD828[index];

    pPanelTex->field_8_bufid = 31 - index;
    pPanelTex->field_C_uvclut = LLOAD(&elem->field_0_u);
    elem->field_8_rect1.w = pPanelTex->field_10_w / 4;
    elem->field_8_rect1.h = pPanelTex->field_12_h;
    LoadImage(&elem->field_8_rect1, pPanelTex->field_0_pixels);
    LoadImage(&elem->field_10_rect2, pPanelTex->field_4_word_ptr_pixels);
}

void sub_8003D070(PANEL_TEXTURE *pPanelTex, ResHeader *pRes)
{
    ResHeader_Sub *pSub;

    pRes->field_14[0] = 0;

    pSub = &pRes->field_34;

    pPanelTex->field_9_xofs = pSub->field_4.x;
    pPanelTex->field_A_yofs = pSub->field_4.y;
    pPanelTex->field_10_w = pSub->field_4.w << 2;
    pPanelTex->field_12_h = pSub->field_4.h;
    pPanelTex->field_4_word_ptr_pixels = (u_long *)pRes->field_14;
    pPanelTex->field_0_pixels = (u_long *)&pRes->field_14[pRes->field_8 >> 1];
}

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
    Menu_Item_Unknown *pUnknown = (Menu_Item_Unknown *)GV_Malloc(totalLen);
    if (pUnknown)
    {
        GV_ZeroMemory(pUnknown, totalLen);
        pUnknown->field_0_main.field_0_array_count = count;
        pUnknown->field_0_main.field_10 = 0;
    }
    return pUnknown;
}

void menu_panel_free_8003D184(Menu_Item_Unknown *pPanel)
{
    if (pPanel)
    {
        GV_Free(pPanel);
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

int menu_panel_8003D2BC(Menu_Item_Unknown *pMenu, int itemId)
{
    int i; // $v1

    i = pMenu->field_0_main.field_0_array_count - 1;
    pMenu->field_0_main.field_4_selected_idx = -1;

    while (i >= 0)
    {
        if (pMenu->field_20_array[i].field_0_id == itemId)
        {
            pMenu->field_0_main.field_4_selected_idx = i;
        }
        i--;
    }

    if (pMenu->field_0_main.field_4_selected_idx < 0)
    {
        printf("PANEL MAKE Error\n");
        pMenu->field_0_main.field_4_selected_idx = 0;
    }

    pMenu->field_0_main.field_18 = -1;
    sub_8003D1DC(pMenu);
    return 1;
}

void sub_8003D34C(Menu_Item_Unknown *pItem, int a2)
{
    int    count;
    int    l_8;
    PANEL *pIter;
    int    tmp;

    count = pItem->field_0_main.field_0_array_count;
    l_8 = pItem->field_0_main.field_8;
    pIter = &pItem->field_20_array[0];
    while (count > 0)
    {
        pIter->field_4_pos += a2;
        if (pIter->field_4_pos >= l_8)
        {
            tmp = (pIter->field_4_pos - l_8);
            pIter->field_4_pos = pItem->field_0_main.field_C + tmp;
        }
        --count;
        pIter++;
    }
}

void sub_8003D3A4(Menu_Item_Unknown *pItem, int a2)
{
    int    count;
    int    l_8;
    PANEL *pIter;
    int    tmp;

    count = pItem->field_0_main.field_0_array_count;
    l_8 = pItem->field_0_main.field_C;
    pIter = &pItem->field_20_array[0];
    while (count > 0)
    {
        pIter->field_4_pos += a2;
        if (l_8 >= pIter->field_4_pos)
        {
            tmp = (pIter->field_4_pos - l_8);
            pIter->field_4_pos = pItem->field_0_main.field_8 + tmp;
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
        v3 = count + 1;
    }
    pMenu->field_0_main.field_4_selected_idx =
        (pMenu->field_0_main.field_4_selected_idx + v3) % pMenu->field_0_main.field_0_array_count;
}

void sub_8003D44C(Menu_Item_Unknown *pMenu, int a2, int a3)
{
    TMenuItemUnknownFn pFn;

    pMenu->field_0_main.field_10 = a3;
    pMenu->field_0_main.field_14_fn_ctx = (a2 << 8) / a3;
    if (a2 > 0)
    {
        pFn = sub_8003D34C;
    }
    else
    {
        pFn = sub_8003D3A4;
    }
    pMenu->field_0_main.field_1C_fn = pFn;
    sub_8003D3FC(pMenu, a2);
    GM_SeSet2_80032968(0, 63, SE_ITEM_SELECT);
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

int sub_8003D568(void)
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

void sub_8003D6A8(Menu_Inventory *pMenuLeft, int bIsRight, void *pUpdateFn)
{
    struct PANEL_CONF *pPanelConf;

    pPanelConf = &stru_8009E544[bIsRight];
    pMenuLeft->field_8_panel_conf = pPanelConf;
    pPanelConf->field_18_pFnUpdate = pUpdateFn;
}

void sub_8003D6CC(Menu_Inventory *pLeftRight, GV_PAD *pPad)
{
    int                bVar1;
    int                arg2_1;
    int                arg2_2;
    Menu_Item_Unknown *pMenuItem;
    PANEL_CONF        *pPanelConf;

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

void menu_8003D7DC(MenuWork *work, unsigned int *pOt, Menu_Inventory *pSubMenu)
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
    pPanelConf->field_18_pFnUpdate(work, pOt, xoff, yoff, pPanel);

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
        pPanelConf->field_18_pFnUpdate(work, pOt, xoff_2, yoff_2, pPanel_2);
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
        pPanelConf->field_18_pFnUpdate(work, pOt, xoff_3, yoff_3, pPanel_2);
    }
    sub_8003CE84();
}

void menu_sub_menu_update_8003DA0C(MenuWork *work, unsigned int *pOt, Menu_Inventory *pSubMenu)
{
    if ((GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_06 | GAME_FLAG_BIT_13)) != GAME_FLAG_BIT_06)
    {
        pSubMenu->field_8_panel_conf->field_18_pFnUpdate(work, pOt, pSubMenu->field_8_panel_conf->field_0_xOffset,
                                                         pSubMenu->field_8_panel_conf->field_2_yOffset,
                                                         &pSubMenu->field_0_current);
    }
}

void sub_8003DA60(MenuWork *work, unsigned int *pOt, Menu_Inventory *pLeftRight, int off1, int off2)
{
    pLeftRight->field_8_panel_conf->field_18_pFnUpdate(
        work, pOt, pLeftRight->field_8_panel_conf->field_0_xOffset + off1,
        pLeftRight->field_8_panel_conf->field_2_yOffset + off2, &pLeftRight->field_0_current);
}

int menu_8003DA9C(Menu_Inventory *pMenu, GV_PAD *pPad)
{
    struct PANEL_CONF *pPanelConf; // $a0

    if ((GM_Camera_800B77E8.flags & 0x101) != 0)
    {
    ret_zero:
        return 0;
    }

    if ((GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_06 | GAME_FLAG_BIT_13)) == GAME_FLAG_BIT_06)
    {
        // TODO: probably a fake match, every return 0
        // is supposed to point to ret_zero but
        // the last one doesn't without a goto.
        goto ret_zero;
    }

    pPanelConf = pMenu->field_8_panel_conf;

    if (!(pPad->status & pPanelConf->field_4_input))
    {
        goto ret_zero;
    }
    dword_800AB584 = pPanelConf;

    return 1;
}

int sub_8003DAFC(Menu_Inventory *pLeftRight, GV_PAD *pPad)
{
    if (!(pPad->status & pLeftRight->field_8_panel_conf->field_4_input))
    {
        dword_800AB584 = NULL;
        return 1;
    }
    return 0;
}

TILE *menu_render_rect_8003DB2C(MenuPrim *pOt, int x, int y, int w, int h, int rgb)
{
    TILE *pTile; // $v0

    _NEW_PRIM(pTile, pOt);

    LSTORE(rgb, &pTile->r0);

    setXY0(pTile, x, y);
    setWH(pTile, w, h);

    setTile(pTile);

    addPrim(pOt->mPrimBuf.mOt, pTile);
    return pTile;
}

void Menu_item_render_frame_rects_8003DBAC(MenuPrim *pGlue, int x, int y, int param_4)
{
    TILE     *tile;
    DR_TPAGE *tpage;

    menu_render_rect_8003DB2C(pGlue, x, y, 47, 1, 0);
    menu_render_rect_8003DB2C(pGlue, x - 4, y, 14, 20, 0);
    menu_render_rect_8003DB2C(pGlue, x + 45, y + 1, 2, 19, 0);
    menu_render_rect_8003DB2C(pGlue, x - 4, y + 20, 51, 9, 0);

    tile = menu_render_rect_8003DB2C(pGlue, x + 10, y + 1, 35, 19, (param_4 != 0 ?: 0) << 23);
    setSemiTrans(tile, 1);

    _NEW_PRIM(tpage, pGlue);

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
    RpkHeader *pFileData = GV_GetCache(GV_CacheID2(pFileName, 'r'));
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
    while (i < MENU_WEAPON_COUNT)
    {
        const int imgIdx = i + 1;
        menu_init_rpk_item_8003DDCC(&gMenuRightItems_800BD888[i], imgIdx, 0);
        i++;
    }
}

void menu_weapon_unknown_8003DEB0(void)
{
    sub_8003CE40(gMenuRightItems_800BD888, MENU_WEAPON_COUNT);
}

menu_weapon_rpk_info SECTION(".data") gMenuWeaponRpkInfo_8009E57C[] = {
    {"SOCOM", 1},    {"FA-MAS", 3}, {"GRENADE", 5}, {"NIKITA", 10},  {"STINGER", 9},
    {"CLAYMORE", 8}, {"C4", 7},     {"STUN.G", 6},  {"CHAFF.G", 11}, {"PSG1", 4}};

PANEL_TEXTURE *menu_weapon_get_weapon_rpk_info_8003DED8(int weaponIdx)
{
    int rpkIdx;
    if (weaponIdx == WEAPON_SOCOM && !GM_SilencerFlag)
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

extern unsigned short GM_ItemTypes_8009D598[];
extern unsigned short GM_WeaponTypes_8009D580[];

extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern int              dword_8009F46C;
extern unsigned int     GM_DisableWeapon_800AB9E4;

int sub_8003DF30(int weaponId)
{
    if (((GM_ItemTypes_8009D598[GM_CurrentItemId + 1] & 1) && (GM_WeaponTypes_8009D580[weaponId + 1] & 0x200)))
    {
        return 1;
    }
    if ((GM_PlayerStatus_800ABA50 & PLAYER_ON_WALL) && weaponId == WEAPON_PSG1)
    {
        return 1;
    }
    if ((GM_PlayerStatus_800ABA50 & PLAYER_GROUND) && weaponId == WEAPON_STINGER)
    {
        return 1;
    }

    if ((GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_01 | GAME_FLAG_BIT_24)) && weaponId == WEAPON_NIKITA)
    {
        return 1;
    }

    if (dword_8009F46C && (weaponId == WEAPON_STINGER || weaponId == WEAPON_PSG1))
    {
        return 1;
    }

    return (GM_DisableWeapon_800AB9E4 & (1 << weaponId)) > 0;
}

// Also see dword_8009E3E4, dword_8009E444.
// Those strings are passed to font_draw_string_80045D0C().

char *wpn_descriptions_8009E5CC[] = {
    /* WP_Socom */
    (char[]){0xB0, 0x14, 0x82, 0x1D, 0xD0, 0x06, 0x82, 0x13, 0x82, 0x40, 0x82, 0x34, 0x82, 0x19, 0x82, 0x28, 0x82, 0x4B,
             0xD0, 0x15, 0x80, 0x7C, 0x90, 0x42, 0x91, 0x0C, 0x90, 0x98, 0x91, 0x0D, 0x91, 0x0E, 0xD0, 0x03, 0x82, 0x4C,
             0xD0, 0x06, 0x82, 0x16, 0xD0, 0x06, 0x90, 0x95, 0x90, 0x96, 0x90, 0xC1, 0x90, 0x93, 0x90, 0x94, 0xD0, 0x03,
             0x80, 0x23, 0x90, 0x1D, 0x82, 0x3C, 0x82, 0x1F, 0x82, 0x53, 0x81, 0x52, 0x90, 0x7B, 0x81, 0x19, 0x81, 0x28,
             0x82, 0x4D, 0xC2, 0x23, 0x82, 0x0F, 0x82, 0x0A, 0x82, 0x53, 0xD0, 0x02, 0x90, 0x7D, 0x81, 0x19, 0x81, 0x28,
             0x90, 0x7E, 0x90, 0x7F, 0xD0, 0x03, 0x82, 0x15, 0x82, 0x37, 0x82, 0x4C, 0xC2, 0x23, 0x82, 0x15, 0xD0, 0x06,
             0x90, 0x93, 0x90, 0x94, 0x90, 0xB6, 0x91, 0x0F, 0xD0, 0x03, 0x00, 0x00},
    /* WP_Famas */
    (char[]){0xB0, 0x14, 0x82, 0x35, 0xC2, 0x01, 0x82, 0x3E, 0x82, 0x19, 0xD0, 0x15, 0x80, 0x7C, 0x82, 0x02,
             0x82, 0x15, 0x82, 0x4B, 0x82, 0x28, 0x82, 0x49, 0x82, 0x04, 0x82, 0x35, 0x82, 0x4B, 0xD0, 0x03,
             0x80, 0x23, 0x90, 0x1D, 0x82, 0x3C, 0x82, 0x1F, 0x82, 0x53, 0x81, 0x52, 0x90, 0x7B, 0x81, 0x19,
             0x81, 0x28, 0x90, 0x7E, 0x90, 0x7F, 0xD0, 0x03, 0x90, 0x7B, 0x81, 0x17, 0x81, 0x24, 0x81, 0x25,
             0x81, 0x11, 0x81, 0x4B, 0x81, 0x28, 0xD0, 0x02, 0x82, 0x35, 0x82, 0x4B, 0x82, 0x0A, 0xD0, 0x06,
             0x82, 0x28, 0x90, 0x80, 0x90, 0x8C, 0xD0, 0x03, 0x00, 0x00, 0x00, 0x00},
    /* WP_Grenade */
    (char[]){0xB0, 0x14, 0x82, 0x10, 0x82, 0x4C, 0x82, 0x2D, 0xD0, 0x06, 0x82, 0x29, 0xD0, 0x15, 0x80, 0x7C,
             0x90, 0x82, 0x90, 0x83, 0x90, 0x5E, 0x90, 0x84, 0x90, 0x85, 0xD0, 0x03, 0x80, 0x23, 0x90, 0x1D,
             0x82, 0x3C, 0x82, 0x1F, 0x82, 0x53, 0x81, 0x52, 0x90, 0x7B, 0x81, 0x19, 0x81, 0x28, 0x90, 0x5B,
             0x90, 0xF8, 0x82, 0x34, 0x82, 0x53, 0x81, 0x52, 0x90, 0xF9, 0x81, 0x0D, 0xD0, 0x02, 0x90, 0x7D,
             0x81, 0x19, 0x81, 0x28, 0x90, 0x88, 0x81, 0x12, 0x81, 0x4B, 0xD0, 0x03, 0x82, 0x34, 0x82, 0x53,
             0x81, 0x52, 0x90, 0xF9, 0x81, 0x04, 0x81, 0x26, 0x81, 0x0B, 0x81, 0x49, 0x90, 0xFA, 0x80, 0x35,
             0x90, 0xFB, 0x90, 0xFC, 0x81, 0x2B, 0x90, 0xA2, 0x90, 0x7E, 0xD0, 0x03, 0x00, 0x00, 0x00, 0x00},
    /* WP_Nikita */
    (char[]){0xB0, 0x14, 0x82, 0x4A, 0x82, 0x42, 0x82, 0x13, 0x82, 0x53, 0x82, 0x3F, 0x82, 0x15, 0x82, 0x04,
             0x82, 0x4B, 0xD0, 0x15, 0x80, 0x7C, 0x90, 0x89, 0x90, 0x37, 0x90, 0x8A, 0x90, 0x8B, 0x82, 0x3F,
             0x82, 0x15, 0x82, 0x04, 0x82, 0x4B, 0xD0, 0x03, 0x80, 0x23, 0x90, 0x1D, 0x82, 0x3C, 0x82, 0x1F,
             0x82, 0x53, 0x81, 0x52, 0x90, 0x7B, 0x81, 0x19, 0x81, 0x28, 0x90, 0x7E, 0x90, 0x8C, 0xD0, 0x03,
             0x90, 0x7E, 0x90, 0x8C, 0x90, 0xFC, 0xD0, 0x02, 0x90, 0x87, 0x90, 0x9B, 0x82, 0x0D, 0xD0, 0x06,
             0x81, 0x27, 0x82, 0x3F, 0x82, 0x15, 0x82, 0x04, 0x82, 0x4B, 0x81, 0x52, 0x90, 0x8F, 0x90, 0x90,
             0x81, 0x27, 0x81, 0x0D, 0x81, 0x4B, 0xD0, 0x03, 0x00, 0x00, 0x00, 0x00},
    /* WP_Stinger */
    (char[]){0xB0, 0x14, 0x82, 0x19, 0x82, 0x26, 0xC2, 0x03, 0x82, 0x53, 0x82, 0x0C, 0xD0, 0x06, 0xC0, 0x7F, 0x82, 0x3F,
             0x82, 0x15, 0x82, 0x04, 0x82, 0x4B, 0xD0, 0x15, 0x80, 0x7C, 0x90, 0x6A, 0x90, 0x91, 0x90, 0x92, 0x82, 0x3F,
             0x82, 0x15, 0x82, 0x04, 0x82, 0x4B, 0xD0, 0x03, 0x90, 0x93, 0x90, 0x94, 0x81, 0x19, 0x81, 0x4B, 0x81, 0x28,
             0x90, 0x95, 0x90, 0x96, 0x82, 0x42, 0xD0, 0x06, 0x82, 0x29, 0x81, 0x2B, 0x90, 0xAC, 0x81, 0x4B, 0xD0, 0x03,
             0x90, 0x87, 0x90, 0x9B, 0x82, 0x0D, 0xD0, 0x06, 0x81, 0x27, 0x90, 0x95, 0x90, 0x96, 0x90, 0x97, 0x90, 0x98,
             0xD0, 0x02, 0x80, 0x23, 0x90, 0x1D, 0x82, 0x3C, 0x82, 0x1F, 0x82, 0x53, 0x81, 0x52, 0x90, 0x7B, 0x81, 0x19,
             0x81, 0x28, 0x90, 0x7E, 0x90, 0x8C, 0xD0, 0x03, 0x00, 0x00, 0x00, 0x00},
    /* WP_LandMine */
    (char[]){0xB0, 0x14, 0x82, 0x0F, 0x82, 0x4C, 0x82, 0x04, 0x82, 0x42, 0x82, 0x02, 0xD0, 0x15, 0x80, 0x7C,
             0x90, 0x91, 0x90, 0x99, 0x90, 0x9A, 0x90, 0x9B, 0x90, 0x9C, 0x90, 0x6A, 0x90, 0x6B, 0xD0, 0x03,
             0x80, 0x23, 0x90, 0x1D, 0x82, 0x3C, 0x82, 0x1F, 0x82, 0x53, 0x81, 0x27, 0x90, 0x9D, 0x90, 0x9E,
             0xD0, 0x03, 0x90, 0x9D, 0x90, 0x9E, 0x90, 0xDC, 0x81, 0x2B, 0x90, 0xED, 0x90, 0xEE, 0x81, 0x15,
             0x81, 0x4C, 0x81, 0x4B, 0x90, 0xA2, 0x90, 0x7E, 0x90, 0xFD, 0x90, 0xC8, 0x81, 0x2B, 0x90, 0xAC,
             0x81, 0x4B, 0x81, 0x28, 0x90, 0xA2, 0x90, 0x7E, 0x81, 0x19, 0x81, 0x4B, 0xD0, 0x03, 0x00, 0x00},
    /* WP_Bomb */
    (char[]){0xB0, 0x14, 0x43, 0x80, 0x34, 0x90, 0xA2, 0x90, 0x85, 0xD0, 0x15, 0x80, 0x7C, 0x82, 0x37, 0x82, 0x49,
             0x82, 0x19, 0x82, 0x21, 0xC2, 0x23, 0x82, 0x0F, 0x90, 0xA2, 0x90, 0x85, 0xD0, 0x03, 0x80, 0x23, 0x90,
             0x1D, 0x82, 0x3C, 0x82, 0x1F, 0x82, 0x53, 0x81, 0x27, 0x90, 0x9D, 0x90, 0x9E, 0xD0, 0x02, 0x80, 0x23,
             0x90, 0x24, 0x82, 0x3C, 0x82, 0x1F, 0x82, 0x53, 0x81, 0x27, 0x90, 0xA2, 0x90, 0x82, 0xD0, 0x03, 0x00},
    /* WP_StunGrenade */
    (char[]){0xB0, 0x14, 0x82, 0x19, 0x82, 0x1F, 0x82, 0x53, 0xC0, 0x7F, 0x82, 0x10, 0x82, 0x4C, 0x82, 0x2D, 0xD0,
             0x06, 0x82, 0x29, 0xD0, 0x15, 0x80, 0x7C, 0x90, 0xFE, 0x90, 0xFF, 0x90, 0xA3, 0x90, 0x4A, 0x90, 0x5E,
             0x90, 0x84, 0x90, 0x85, 0xD0, 0x03, 0x80, 0x23, 0x90, 0x1D, 0x82, 0x3C, 0x82, 0x1F, 0x82, 0x53, 0x81,
             0x52, 0x90, 0x7B, 0x81, 0x19, 0x81, 0x28, 0x90, 0x7C, 0x81, 0x08, 0xD0, 0x02, 0x90, 0x7D, 0x81, 0x19,
             0x81, 0x28, 0x90, 0x88, 0x81, 0x12, 0x81, 0x4B, 0xD0, 0x03, 0x90, 0xA2, 0x90, 0x7E, 0x81, 0x19, 0x81,
             0x4B, 0x81, 0x28, 0xD0, 0x02, 0x90, 0xE3, 0x90, 0x5C, 0x90, 0xDC, 0x90, 0xE4, 0x90, 0x9F, 0x81, 0x52,
             0x91, 0x01, 0x91, 0x02, 0x81, 0x15, 0x81, 0x1B, 0x81, 0x4B, 0xD0, 0x03, 0x00, 0x00},
    /* WP_ChaffGrenade */
    (char[]){0xB0, 0x14, 0x82, 0x21, 0xC2, 0x43, 0x82, 0x35, 0xC0, 0x7F, 0x82, 0x10, 0x82, 0x4C, 0x82, 0x2D, 0xD0,
             0x06, 0x82, 0x29, 0xD0, 0x15, 0x80, 0x7C, 0x90, 0xA6, 0x90, 0xA7, 0x90, 0xA8, 0x90, 0xA9, 0x90, 0x5E,
             0x90, 0x84, 0x90, 0x85, 0xD0, 0x03, 0x80, 0x23, 0x90, 0x1D, 0x82, 0x3C, 0x82, 0x1F, 0x82, 0x53, 0x81,
             0x52, 0x90, 0x7B, 0x81, 0x19, 0x81, 0x28, 0x90, 0x7C, 0x81, 0x08, 0xD0, 0x02, 0x90, 0x7D, 0x81, 0x19,
             0x81, 0x28, 0x90, 0x88, 0x81, 0x12, 0x81, 0x4B, 0xD0, 0x03, 0x91, 0x03, 0x91, 0x04, 0x90, 0x83, 0x81,
             0x52, 0x91, 0x05, 0x91, 0x06, 0x81, 0x17, 0xD0, 0x02, 0x90, 0xA6, 0x90, 0xA7, 0x90, 0x93, 0x90, 0x9E,
             0x81, 0x52, 0x90, 0xA8, 0x90, 0xA9, 0x81, 0x19, 0x81, 0x4B, 0xD0, 0x03, 0x00, 0x00},
    /* WP_Rifle */
    (char[]){0xB0, 0x14, 0x80, 0x50, 0x80, 0x53, 0x80, 0x47, 0x80, 0x31, 0xD0, 0x15, 0x80, 0x7C, 0x90, 0xAA, 0x90, 0xAB,
             0x90, 0x49, 0x82, 0x49, 0x82, 0x04, 0x82, 0x35, 0x82, 0x4B, 0xD0, 0x03, 0x90, 0x93, 0x90, 0x94, 0x81, 0x19,
             0x81, 0x4B, 0x81, 0x28, 0x90, 0x95, 0x90, 0x96, 0x82, 0x42, 0xD0, 0x06, 0x82, 0x29, 0x81, 0x2B, 0x90, 0xAC,
             0x81, 0x4B, 0xD0, 0x03, 0x90, 0x87, 0x90, 0x9B, 0x82, 0x0D, 0xD0, 0x06, 0x81, 0x27, 0x90, 0x95, 0x90, 0x96,
             0x90, 0x97, 0x90, 0x98, 0xD0, 0x02, 0x80, 0x23, 0x90, 0x1D, 0x82, 0x3C, 0x82, 0x1F, 0x82, 0x53, 0x81, 0x52,
             0x90, 0x7B, 0x81, 0x19, 0x81, 0x28, 0x90, 0x7E, 0x90, 0x7F, 0xD0, 0x03, 0x00, 0x00},
};

// TODO: how to specify table size as 1 to keep in sdata?
const char WP_MP5_80011B04[] = (const char[]){
    0xB0, 0x14, 0x4D, 0x50, 0x20, 0x35, 0x20, 0x53, 0x44, 0xD0, 0x15, 0x80, 0x7C, 0x82, 0x15, 0x82, 0x36, 0x82,
    0x3E, 0x82, 0x17, 0x82, 0x53, 0x82, 0x0C, 0x82, 0x53, 0xD0, 0x03, 0x80, 0x23, 0x90, 0x1D, 0x82, 0x3C, 0x82,
    0x1F, 0x82, 0x53, 0x81, 0x52, 0x90, 0x7B, 0x81, 0x19, 0x81, 0x28, 0x90, 0x7E, 0x90, 0x7F, 0xD0, 0x03, 0x90,
    0x7B, 0x81, 0x17, 0x81, 0x24, 0x81, 0x25, 0x81, 0x11, 0x81, 0x4B, 0x81, 0x28, 0xD0, 0x02, 0x82, 0x35, 0x82,
    0x4B, 0x82, 0x0A, 0xD0, 0x06, 0x82, 0x28, 0x90, 0x80, 0x90, 0x8C, 0xD0, 0x03, 0x82, 0x15, 0x82, 0x37, 0x82,
    0x4C, 0xC2, 0x23, 0x82, 0x15, 0xD0, 0x06, 0x90, 0x93, 0x90, 0x94, 0xD0, 0x03, 0x00};
char *wpn_mp5_description_800AB5CC = (char *)WP_MP5_80011B04;

void menu_weapon_update_helper2_helper_8003E030(int wpn_id)
{
    char *param_1;

    param_1 = wpn_descriptions_8009E5CC[wpn_id];
    if (wpn_id == 0)
    {
        if (GM_SilencerFlag == 0)
        {
            wpn_descriptions_8009E5CC[0][0x70] = 0xd0;
            wpn_descriptions_8009E5CC[0][0x71] = 3;
            wpn_descriptions_8009E5CC[0][0x72] = 0;
        }
        else
        {
            wpn_descriptions_8009E5CC[0][0x70] = 0x90;
            wpn_descriptions_8009E5CC[0][0x71] = 0xb6;
            wpn_descriptions_8009E5CC[0][0x72] = 0x91;
        }
    }
    else if (GM_DifficultyFlag == DIFFICULTY_VERY_EASY && wpn_id == WEAPON_FAMAS)
    {
        param_1 = wpn_mp5_description_800AB5CC;
    }
    sub_8003F97C(param_1);
}

extern short GM_MagazineMax_800ABA2C;
extern short GM_Magazine_800AB9EC;

void menu_weapon_init_helper_8003E0E8(MenuWork *work, unsigned int *pOt, int off_x, int off_y, PANEL *pPanel)
{
    PANEL_TEXTURE        *pTexture;
    const char           *str;
    int                   weaponIdx, weaponIdxCopy;
    int                   pSubCnt2;
    SPRT                 *pPrim;
    int                   offset_x;
    menu_weapon_rpk_info *weaponRpkInfo;

    weaponIdx = pPanel->field_0_id;
    offset_x = off_x;
    offset_x += 4;

    if (weaponIdx >= 0)
    {
        weaponIdxCopy = weaponIdx;
        if (sub_8003DF30(weaponIdxCopy))
        {
            menu_draw_nouse_800435A4(work->field_20_otBuf, offset_x, off_y);
        }

        if (pPanel->field_2_num >= 0 && pPanel->field_2_num < 10000)
        {
            menu_number_draw_number2_80042FC0(work, offset_x, off_y + 11, pPanel->field_2_num,
                                              GM_WeaponsMax[pPanel->field_0_id]);
        }

        weaponRpkInfo = &gMenuWeaponRpkInfo_8009E57C[weaponIdxCopy];
        pTexture = menu_weapon_get_weapon_rpk_info_8003DED8(weaponIdxCopy);

        if (pPanel->field_6_current == 0)
        {
            sub_8003CEF8(pTexture);
        }

        else if (pTexture->field_8_bufid < 16)
        {
            sub_8003CFE0(pTexture, 1);
        }

        if (pTexture->field_C_uvclut != 0)
        {
            NEW_PRIM(pPrim, work);

            LSTORE(pPanel->field_4_pos == 0 ? 0x808080 : 0x404040, &pPrim->r0);
            menu_init_sprt_8003D0D0(pPrim, pTexture, offset_x, off_y);
            setSprt(pPrim);
            addPrim(pOt, pPrim);
        }

        if (pPanel->field_6_current && GM_MagazineMax_800ABA2C > 0)
        {
            pSubCnt2 = (GM_CurrentWeaponId == WEAPON_FAMAS ? 3 : 0);
            menu_number_draw_magazine_80042E38(work, pOt, offset_x + 45, off_y + 20, GM_Magazine_800AB9EC,
                                               GM_MagazineMax_800ABA2C, pSubCnt2);
        }
        else
        {
            if (weaponIdxCopy == WEAPON_FAMAS && GM_DifficultyFlag == DIFFICULTY_VERY_EASY)
            {
                str = "MP 5 SD";
            }

            else
            {
                str = weaponRpkInfo->field_0_weapon_name;
            }
            menu_number_draw_string_800430F0(work, pOt, offset_x + 46, off_y + 22, str, 1);
        }
    }
    else
    {
        menu_number_draw_string_800430F0(work, pOt, offset_x + 46, off_y + 22, "NO ITEM", 1);
    }

    Menu_item_render_frame_rects_8003DBAC(work->field_20_otBuf, offset_x, off_y,
                                          (pPanel->field_4_pos == 0 && pPanel->field_6_current == 0));
}

extern short GM_WeaponChanged_800AB9D8;

void menu_weapon_update_helper2_helper2_8003E3B0(MenuWork *work)
{
    Menu_Item_Unknown *pItemUnknown;
    int                id;
    short             *varbuf;

    pItemUnknown = work->field_1F0_menu_weapon.field_C_alloc;
    work->field_1F0_menu_weapon.field_10_state = 0;

    AssignXYFromVec_8003D1B8(&work->field_1F0_menu_weapon.field_0_current,
                             &pItemUnknown->field_20_array[pItemUnknown->field_0_main.field_4_selected_idx]);

    id = work->field_1F0_menu_weapon.field_0_current.field_0_id;
    varbuf = linkvarbuf_800B4D98;

    if (id >= 0 && !sub_8003DF30(id))
    {
        GM_CurrentWeaponId = work->field_1F0_menu_weapon.field_0_current.field_0_id;
        GM_WeaponChanged_800AB9D8 = 1;
        if (GM_CurrentWeaponId >= 0)
        {
            sub_8003CFE0(
                menu_weapon_get_weapon_rpk_info_8003DED8(work->field_1F0_menu_weapon.field_0_current.field_0_id), 1);
        }
        work->field_1F0_menu_weapon.field_11 = varbuf[14]; // GM_CurrentWeaponId would not match...
    }
    else
    {
        if (id != -1)
        {
            dword_800ABAE8 = id;
            work->field_1F0_menu_weapon.field_11 = id;
        }
        GM_CurrentWeaponId = -1;
        work->field_1F0_menu_weapon.field_0_current.field_0_id = -1;
        GM_WeaponChanged_800AB9D8 = 1;
    }

    work->field_1F0_menu_weapon.field_12_flashingAnimationFrame = 10;
    menu_panel_free_8003D184(work->field_1F0_menu_weapon.field_C_alloc);
    menu_font_kill_8003FC0C();
    GM_SeSet2_80032968(0, 0x3f, SE_ITEM_EQUIP);
}

int dword_800AB5E0 = 0;
int dword_800AB5E4 = 0;

int menu_weapon_update_helper_8003E4B8(MenuWork *work)
{
    Menu_Item_Unknown *pPanel;
    int                i;
    int                panelCount, currentPanel;

    if (!(GM_GameStatus_800AB3CC & GAME_FLAG_BIT_19))
    {
        panelCount = 0;

        for (i = 0; i < 10; i++)
        {

            if (GM_Weapons[i] >= 0)
            {
                panelCount++;
            }
        }

        pPanel = menu_alloc_panel_8003D124(panelCount + 1);
        work->field_1F0_menu_weapon.field_C_alloc = pPanel;

        if (!pPanel)
        {
            return 0;
        }

        if (GM_CurrentWeaponId != -1)
        {
            dword_800ABAE8 = GM_CurrentWeaponId;
        }
        else if (dword_800ABAE8 < 0)
        {
            dword_800ABAE8 = 0;
        }

        currentPanel = 0;

        for (i = 0; i < 10; i++)
        {
            if (i == dword_800ABAE8)
            {
                AssignXY_8003D1A8(&pPanel->field_20_array[currentPanel], -1, 1);
                currentPanel++;
            }

            if (GM_Weapons[i] >= 0)
            {
                AssignXY_8003D1A8(&pPanel->field_20_array[currentPanel], i, GM_Weapons[i]);
                currentPanel++;
            }
        }
    }
    else
    {
        pPanel = menu_alloc_panel_8003D124(1);
        work->field_1F0_menu_weapon.field_C_alloc = pPanel;

        if (!pPanel)
        {
            return 0;
        }

        AssignXY_8003D1A8(&pPanel->field_20_array[0], -1, 1);
    }

    if (!sub_8003F84C(1))
    {
        menu_panel_free_8003D184(pPanel);
        return 0;
    }

    dword_800AB5E4 = 0;
    dword_800AB5E0 = 0;
    work->field_1F0_menu_weapon.field_10_state = 2;
    sub_8003D520();
    sub_8003CE40(gMenuRightItems_800BD888, 11);
    menu_panel_8003D2BC(work->field_1F0_menu_weapon.field_C_alloc,
                        work->field_1F0_menu_weapon.field_0_current.field_0_id);
    GM_SeSet2_80032968(0, 0x3f, SE_ITEM_OPENWINDOW);
    return 1;
}

extern int DG_UnDrawFrameCount_800AB380;
extern int GV_PauseLevel_800AB928;

void menu_weapon_update_helper2_8003E674(MenuWork *work, unsigned int *pOt)
{
    unsigned short     anim_frame;
    int                anim_frame2;
    int                switched_weapon;
    int                last_id;
    Menu_Item_Unknown *pAlloc;
    PANEL             *pPanel;

    switch (work->field_1F0_menu_weapon.field_10_state)
    {
    case 0:
        anim_frame = work->field_1F0_menu_weapon.field_12_flashingAnimationFrame & 0xffff;
        anim_frame2 = anim_frame & 0xffff;

        if (anim_frame2 != 0)
        {
            work->field_1F0_menu_weapon.field_12_flashingAnimationFrame--;

            if ((anim_frame2 & 3) > 1)
            {
                menu_sub_menu_update_8003DA0C(work, pOt, &work->field_1F0_menu_weapon);

                if (((anim_frame2 & 3) == 3) &&
                    (GM_CurrentWeaponId != work->field_1F0_menu_weapon.field_0_current.field_0_id) &&
                    sub_8003DF30(work->field_1F0_menu_weapon.field_0_current.field_0_id) &&
                    (DG_UnDrawFrameCount_800AB380 == 0))
                {
                    GM_SeSet2_80032968(0, 63, SE_ITEM_CURSOR);
                    break;
                }
            }
        }
        else
        {
            switched_weapon = 0;

            if (sub_8003DF30(GM_CurrentWeaponId))
            {
                last_id = GM_CurrentWeaponId;
                GM_CurrentWeaponId = WEAPON_NONE;
                GM_WeaponChanged_800AB9D8 = 1;
                work->field_1F0_menu_weapon.field_12_flashingAnimationFrame = 19;
                dword_800ABAE8 = last_id;
                break;
            }

            if (GM_CurrentWeaponId != work->field_1F0_menu_weapon.field_0_current.field_0_id)
            {
                switched_weapon = 1;
                GM_WeaponChanged_800AB9D8 = 1;
                printf("HERE %d\n", work->field_1F0_menu_weapon.field_0_current.field_0_id);

                if (work->field_1F0_menu_weapon.field_0_current.field_0_id != -1)
                {
                    dword_800ABAE8 = work->field_1F0_menu_weapon.field_0_current.field_0_id;
                }

                work->field_1F0_menu_weapon.field_0_current.field_0_id = GM_CurrentWeaponId;
            }

            if (GM_CurrentWeaponId >= 0)
            {
                if (switched_weapon != 0)
                {
                    sub_8003CFE0(menu_weapon_get_weapon_rpk_info_8003DED8(GM_CurrentWeaponId), 1);
                    work->field_1F0_menu_weapon.field_11 = GM_CurrentWeaponId;
                }

                work->field_1F0_menu_weapon.field_0_current.field_2_num = GM_Weapons[GM_CurrentWeaponId];
                menu_sub_menu_update_8003DA0C(work, pOt, &work->field_1F0_menu_weapon);
            }
        }
        break;

    case 2:
        if (menu_8003D538())
        {
            work->field_1F0_menu_weapon.field_10_state = 1;
        }

    case 1:
        pAlloc = work->field_1F0_menu_weapon.field_C_alloc;
        pPanel = &pAlloc->field_20_array[pAlloc->field_0_main.field_4_selected_idx];

        if ((pPanel->field_4_pos == 0) && (pPanel->field_0_id >= 0))
        {
            if (dword_800AB5E4 == 0)
            {
                if (++dword_800AB5E0 == 4)
                {
                    menu_weapon_update_helper2_helper_8003E030(pPanel->field_0_id);
                    dword_800AB5E4 = 1;
                }
            }
        }
        else
        {
            dword_800AB5E4 = 0;
            dword_800AB5E0 = 0;
        }

        if (dword_800AB5E4 != 0)
        {
            menu_8003F9B4(work, pOt, "WEAPON");
        }

        menu_8003D7DC(work, pOt, &work->field_1F0_menu_weapon);
        break;

    case 3:
        if (sub_8003D568() != 0)
        {
            work->field_2A_state = 0;
            GV_PauseLevel_800AB928 &= ~4;
            menu_weapon_update_helper2_helper2_8003E3B0(work);
        }
        else
        {
            menu_8003D7DC(work, pOt, &work->field_1F0_menu_weapon);
        }
        break;
    }
}

void menu_weapon_update_8003E990(MenuWork *work, unsigned char *pOt)
{
    GV_PAD         *pPad;
    Menu_Inventory *pMenu;
    int             selected_id, weapon_id, xoffset;

    pPad = work->field_24_pInput;

    if (work->field_2A_state == 0)
    {
        if (GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_11 | GAME_FLAG_BIT_20))
        {
            return;
        }

        if (!(GM_PlayerStatus_800ABA50 & 0x20408000))
        {
            if (menu_8003DA9C(&work->field_1F0_menu_weapon, pPad))
            {
                if (menu_weapon_update_helper_8003E4B8(work))
                {
                    work->field_2A_state = 1;
                    GV_PauseLevel_800AB928 |= 4;
                    sub_8003D520();
                }
            }
            else if ((!(GM_GameStatus_800AB3CC & GAME_FLAG_BIT_19)) && (pPad->press & PAD_R1))
            {
                weapon_id = GM_CurrentWeaponId;

                if (GM_CurrentWeaponId > WEAPON_NONE)
                {
                    GM_CurrentWeaponId = WEAPON_NONE;
                }
                else if (!sub_8003DF30(work->field_1F0_menu_weapon.field_11))
                {
                    selected_id = work->field_1F0_menu_weapon.field_11;

                    if (GM_Weapons[selected_id] > WEAPON_NONE)
                    {
                        GM_CurrentWeaponId = selected_id;
                    }
                }

                if (weapon_id != GM_CurrentWeaponId)
                {
                    GM_WeaponChanged_800AB9D8 = 1;
                    GM_SeSet2_80032968(0, 63, SE_ITEM_EQUIP);
                }
            }
        }
    }
    else if (work->field_2A_state == 1)
    {
        pMenu = &work->field_1F0_menu_weapon;

        if (sub_8003DAFC(pMenu, pPad))
        {
            work->field_1F0_menu_weapon.field_10_state = 3;
        }
        else if (sub_8003D52C() > 255)
        {
            sub_8003D6CC(pMenu, pPad);

            if (work->field_1F0_menu_weapon.field_10_state == 3)
            {
                work->field_1F0_menu_weapon.field_10_state = 2;
            }
        }
    }
    else if (work->field_2A_state == 4)
    {
        return;
    }
    else
    {
        if (GM_CurrentWeaponId > WEAPON_NONE)
        {
            xoffset = sub_8003D52C();

            if (xoffset < 255)
            {
                sub_8003DA60(work, (unsigned int *)pOt, &work->field_1F0_menu_weapon, xoffset / 4, 0);
                work->field_1F0_menu_weapon.field_12_flashingAnimationFrame = 0;
            }
        }
        else
        {
            work->field_1F0_menu_weapon.field_12_flashingAnimationFrame = 0;
        }

        return;
    }

    menu_weapon_update_helper2_8003E674(work, (unsigned int *)pOt);
}

void sub_8003EBDC(MenuWork *work)
{
    PANEL_TEXTURE *pPanelTex;
    int            weapon_index;

    weapon_index = work->field_1F0_menu_weapon.field_0_current.field_0_id;
    if (weapon_index != -1 || (weapon_index = work->field_1F0_menu_weapon.field_11) != -1)
    {
        pPanelTex = menu_weapon_get_weapon_rpk_info_8003DED8(weapon_index);
        sub_8003CFE0(pPanelTex, 1);
    }
}

void menu_weapon_init_8003EC2C(MenuWork *work)
{
    work->field_2C_modules[MENU_WEAPON] = menu_weapon_update_8003E990;
    work->field_1F0_menu_weapon.field_0_current.field_0_id = -1;
    work->field_1F0_menu_weapon.field_10_state = 0;
    work->field_1F0_menu_weapon.field_12_flashingAnimationFrame = 0;
    work->field_1F0_menu_weapon.field_0_current.field_4_pos = 0;
    work->field_1F0_menu_weapon.field_0_current.field_6_current = 1;
    work->field_1F0_menu_weapon.field_11 = -1;
    work->field_28_flags |= 2;
    dword_800ABAE8 = 0;
    sub_8003D6A8(&work->field_1F0_menu_weapon, 1, (int *)menu_weapon_init_helper_8003E0E8);
    menu_inventory_right_init_items_8003DE50();
    sub_8003EBDC(work);
}

void menu_weapon_kill_8003ECAC(MenuWork *work)
{
    work->field_28_flags &= ~0x2;
}
