#include "linker.h"
#include "menuMan.h"
#include "linker.h"
#include "menuMan.h"
#include "linker.h"
#include "menuMan.h"
#include "Script_tbl_map_8002BB44.h"
#include "menuMan.h"
#include "util/idaTypes.h"
#include "linker.h"
#include "linker.h"
#include "linker.h"
#include <sys/types.h>
#include <libgte.h>
#include "linker.h"

typedef struct
{
    unsigned char field_0_count1;
    unsigned char field_1_count2;
    short pad;
    Menu_rpk_item *items[0]; // pointers ??
} RpkHeader;


DWORD SECTION(".sbss") dword_800ABADC;

// menu related?

int SECTION(".sbss") dword_800ABAE0;


extern struct menu_8009E544 *dword_800AB584;
struct menu_8009E544 *SECTION(".sdata") dword_800AB584;

int SECTION(".dword_800B7800") dword_800B7800;


struct menu_8009E544 *SECTION(".sdata") dword_800AB584;


Menu_rpk_item **SECTION(".sbss") gItemFile_table_800ABAE4;

int GV_CacheID2_800152FC(const char* fileName, int extID);
void *GV_GetCache_8001538C(int hash);

extern struct menu_8009E544 *dword_800AB584;
extern menu_weapon_rpk_info gMenuWeaponRpkInfo_8009E57C[];
extern GameState_800B4D98 gGameState_800B4D98;
extern int dword_8009E544[];
extern int GM_GameStatus_800AB3CC;

int SECTION(".sbss") dword_800ABAE8;
int SECTION(".sbss") dword_800ABAEC;
int SECTION(".sbss") dword_800ABAF0;
int SECTION(".sbss") dword_800ABAF4;
int SECTION(".sbss") dword_800ABAF8;
int SECTION(".sbss") dword_800ABAFC;
int SECTION(".sbss") dword_800ABB00;
int SECTION(".sbss") dword_800ABB04;
int SECTION(".sbss") dword_800ABB08;
int SECTION(".sbss") dword_800ABB0C;

#define MENU_ITEMS_RIGHT_COUNT 11
MenuMan_Inventory_14h_Unk SECTION(".gMenuRightItems_800BD888") gMenuRightItems_800BD888[MENU_ITEMS_RIGHT_COUNT];

#define OffsetToPointer(offset, valueToAdd) *((unsigned int *)offset) = (int)valueToAdd + *((unsigned int *)offset);


void sub_8003CE40(MenuMan_Inventory_14h_Unk *, int);
MenuMan_Inventory_14h_Unk *menu_right_get_weapon_rpk_info_8003DED8(int weaponIdx);
void sub_8003CFE0(unsigned int **images, int index);
void menu_right_update_8003E990(struct Actor_MenuMan *menuMan, unsigned int *param_2);
void menu_right_init_helper_8003E0E8(struct Actor_MenuMan *menuMan, unsigned int *param_2, int param_3,
                                            int param_4, short *param_5);
void menu_inventory_left_update_8003C95C(struct Actor_MenuMan *menuMan, unsigned int *param_2);
void menu_inventory_left_helper_8003B8F0(struct Actor_MenuMan *menuMan, unsigned int *param_2, int param_3,
                                                int param_4, short *param_5);
void sub_8003D6A8(struct menu_left_right *pMenuLeft, int bIsRight, void* pUpdateFn);
void menu_inventory_right_init_items_8003DE50(void);
void sub_8003EBDC(struct Actor_MenuMan *a1);
void*    GV_Malloc_8001620C(int size);
void     GV_ZeroMemory_8001619C(void *, int);
void GV_Free_80016230(void *ptr);

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

int * sub_8003D124(int param_1)
{
    int *piVar1;
    int iVar2;

    iVar2 = param_1 * 8 + 0x20;
    piVar1 = (int *)GV_Malloc_8001620C(iVar2);
    if (piVar1 != (int *)0x0)
    {
        GV_ZeroMemory_8001619C(piVar1, iVar2);
        *piVar1 = param_1;
        piVar1[4] = 0;
    }
    return piVar1;
}

void sub_8003D184(void *param_1)
{
    if (param_1 != 0)
    {
        GV_Free_80016230(param_1);
    }
    return;
}

void AssignXY_8003D1A8(SVECTOR *vec, short vx, short vy)
{
    vec->vx = vx;
    vec->vy = vy;
    vec->pad = 0;
}

void AssignXYFromVec_8003D1B8(SVECTOR *vec_1, SVECTOR *vec_2)
{
    vec_1->vx = vec_2->vx;
    vec_1->vy = vec_2->vy;
    vec_1->pad = 1;
    vec_1->vz = 0;
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

void sub_8003D6A8(struct menu_left_right *pMenuLeft, int bIsRight, void* pUpdateFn)
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
        pSubMenu->field_8_pStru->field_18_pFnUpdate(
            pActor,
            a2,
            pSubMenu->field_8_pStru->field_0,
            pSubMenu->field_8_pStru->field_2,
            pSubMenu);
    }
}

void sub_8003DA60(struct Actor_MenuMan *pActor, int a2, struct menu_left_right *pLeftRight, int off1, int off2)
{
    pLeftRight->field_8_pStru->field_18_pFnUpdate(
        pActor,
        a2,
        pLeftRight->field_8_pStru->field_0 + off1,
        pLeftRight->field_8_pStru->field_2 + off2,
        pLeftRight);
}

int menu_8003DA9C(struct menu_left_right *pMenu, unsigned short *input)
{
    struct menu_8009E544 *field_8_pStru; // $a0

    if ((dword_800B7800 & 0x101) != 0)
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
    if (((unsigned int) *param_2 & *(unsigned int *)(*(int *)(param_1 + 8) + 4)) == 0)
    {
        dword_800AB584 = 0;
        return 1;
    }
    return 0;
}

#pragma INCLUDE_ASM("asm/sub_8003DB2C.s")
#pragma INCLUDE_ASM("asm/sub_8003DBAC.s")

Menu_rpk_item **menu_rpk_init_8003DD1C(const char *pFileName)
{
    Menu_rpk_item **pEnd;
    Menu_rpk_item **pIter;
    int i;
    int count;
    RpkHeader *pFileData = GV_GetCache_8001538C(GV_CacheID2_800152FC(pFileName, 'r'));
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


MenuMan_Inventory_14h_Unk* menu_right_get_weapon_rpk_info_8003DED8(int weaponIdx)
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
    int weapon_index;

    weapon_index = (int)(menuMan->field_1F0_menu_right).field_0_rpk_idx;
    if ((weapon_index != -1) ||
        (weapon_index = *(signed char *)&((menuMan->field_1F0_menu_right).field_11), weapon_index != -1))
    {
        inventory_unk = menu_right_get_weapon_rpk_info_8003DED8(weapon_index);
        sub_8003CFE0((unsigned int **)&inventory_unk->field_0_pixels, 1);
    }
}

void menu_right_init_8003EC2C(struct Actor_MenuMan *menuMan)

{
    short val = -1;
    menuMan->m7FnPtrs_field_2C[1] = menu_right_update_8003E990;
    menuMan->field_1F0_menu_right.field_0_rpk_idx = val;
    menuMan->field_1F0_menu_right.field_10 = 0;
    menuMan->field_1F0_menu_right.field_12 = 0;
    menuMan->field_1F0_menu_right.field_4 = 0;
    menuMan->field_1F0_menu_right.field_6 = 1;
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
