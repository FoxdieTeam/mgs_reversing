#include "item.h"
#include "object.h"
#include "game.h"
#include "Game/linkvarbuf.h"

extern const char aItemC[];
extern const char aItemMapD[];

extern unsigned short GM_ItemTypes_8009D598[];

//------------------------------------------------------------------------------

int item_act_try_add_ammo2_8003330C(int weapon_id, short amount)
{
    short *pWeapons;
    short *pAmmo, *pMaxAmmo;
    short  oldAmmo;

    pWeapons = GM_Weapons;
    pAmmo = &pWeapons[weapon_id];
    if (*pAmmo < 0)
    {
        *pAmmo = 0;
    }

    pMaxAmmo = &GM_WeaponsMax[weapon_id];
    if (*pAmmo >= *pMaxAmmo)
    {
        return 0;
    }

    oldAmmo = *pAmmo ;
    *pAmmo += amount;

    if (*pMaxAmmo < (short)(oldAmmo + amount))
    {
        *pAmmo = *pMaxAmmo;
    }

    return 1;
}

int item_act_try_add_ammo_80033384(int weapon_id, short amount)
{
    short *pWeapons;
    short *pAmmo, *pMaxAmmo;
    short  oldAmmo;

    pWeapons = GM_Weapons;
    pAmmo = &pWeapons[weapon_id];
    if (*pAmmo < 0)
    {
        return 2;
    }

    pMaxAmmo = &GM_WeaponsMax[weapon_id];
    if (*pAmmo >= *pMaxAmmo)
    {
        return 0;
    }

    oldAmmo = *pAmmo;
    *pAmmo += amount;

    if (*pMaxAmmo < (short)(oldAmmo + amount))
    {
        *pAmmo = *pMaxAmmo;
    }

    return 1;
}

int item_act_helper_800333F8(int item_id, int param_2)
{
    int item_type;
    int max_capacity;

    if (item_id == (char)ITEM_NONE)
    {
        item_all_items_and_weapons_unknown_80033560();
        return 1;
    }

    item_type = GM_ItemTypes_8009D598[item_id + 1];

    if (item_type & 0x4000)
    {
        GM_Items[item_id] |= 1 << (param_2 - 1);
        do {} while(0);
        return 1;
    }

    if (item_type & ITEMTYPE_CONSUMABLE)
    {
        max_capacity = GM_ItemsMax[item_id];
        if (max_capacity <= GM_Items[item_id])
        {
            return 0;
        }
        if (GM_Items[item_id] < 0)
        {
            GM_Items[item_id] = 0;
        }
        GM_Items[item_id] += param_2;
        if (max_capacity < ((GM_Items[item_id] * 0x10000) >> 0x10))
        {
            GM_Items[item_id] = max_capacity;
        }
        return 1;
    }

    GM_Items[item_id] = param_2;
    return 1;
}

void item_all_items_and_weapons_unknown2_80033500()
{
    int    i;
    short *ptr;

    ptr = GM_Items;
    for (i = 0; i < GM_TotalItems; i++)
    {
        ptr[i] |= 0x8000;
    }

    ptr = GM_Weapons;
    for (i = 0; i < GM_TotalWeapons; i++)
    {
        ptr[i] |= 0x8000;
    }
}

void item_all_items_and_weapons_unknown_80033560()
{
    int    i;
    short *ptr;

    ptr = GM_Items;
    for (i = 0; i < GM_TotalItems; i++)
    {
        if (ptr[i] != -1)
        {
            ptr[i] &= 0x7FFF;
        }
    }

    ptr = GM_Weapons;
    for (i = 0; i < GM_TotalWeapons; i++)
    {
        if (ptr[i] != -1)
        {
            ptr[i] &= 0x7FFF;
        }
    }
}

#pragma INCLUDE_ASM("asm/Game/item_act_helper_800335D0.s")                     // 212 bytes

void item_init_prim_buffer_800336A4(POLY_FT4 *prims, DG_TEX *tex)
{
    char t_u0; // $a1
    char t_v0; // $v1
    char t_u1; // $a0
    char t_v2; // $v1

    setPolyFT4(prims);
    setSemiTrans(prims, 1);

    t_u0 = tex->field_8_offx;
    t_u1 = t_u0 + tex->field_A_width;

    t_v0 = tex->field_9_offy;
    t_v2 = t_v0 + tex->field_B_height;

    prims->u0 = t_u0;
    prims->v0 = t_v0;

    prims->u1 = t_u1;
    prims->v1 = t_v0;

    prims->u2 = t_u0;
    prims->v2 = t_v2;

    prims->u3 = t_u1;
    prims->v3 = t_v2;

    prims->tpage = tex->field_4_tPage;
    prims->clut = tex->field_6_clut;
}

#pragma INCLUDE_ASM("asm/Game/item_act_helper_80033704.s") // 128 bytes
#pragma INCLUDE_ASM("asm/Game/item_act_80033784.s")        // 2052 bytes

void item_kill_80033F88(Actor_Item *pActor)
{
    DG_PRIM       *field_15C_pPrim;   // $s0
    unsigned char *field_120_pScript; // $a0

    GM_FreeControl_800260CC(&pActor->field_20_ctrl);
    GM_FreeObject_80034BF8(&pActor->field_9C_kmd);

    field_15C_pPrim = pActor->field_15C_pPrim;
    if (field_15C_pPrim)
    {
        DG_DequeuePrim_800182E0(pActor->field_15C_pPrim);
        DG_FreePrim_8001BC04(field_15C_pPrim);
    }

    if (pActor->field_112_state == 2)
    {
        field_120_pScript = pActor->field_120_pScript;
        if (field_120_pScript)
        {
            if ((int)field_120_pScript < 0)
            {
                GCL_ExecBlock_80020118(field_120_pScript, 0);
            }
            else
            {
                GCL_ExecProc_8001FF2C((int)field_120_pScript, 0);
            }
        }
    }
}

int item_init_helper_helper_80034020( Actor_Item *pActor, int type )
{
    int item_id;

    item_id = pActor->field_114_item_id;
    if ( item_id == (char)ITEM_NONE )
    {
        return 1;
    }
    pActor->field_113 = 0;
    switch ( type )
    {
        case 2:
        case 3:
            if ( (GM_DifficultyFlag == -1) && (item_id == ITEM_SCOPE) )
            {
                return 0;
            }
            if (item_id > 9 )
            {
                return 0;
            }
            pActor->field_113 = 2;
            break;

        case 0:
            if (item_id > 9 )
            {
                return 0;
            }
            pActor->field_113 = 1;
            break;

        case 4:
            if ( item_id != ITEM_RATION )
            {
                return 0;
            }
            break;

        case 1:
        case 5:
            if ( item_id > (GM_TotalItems - 1) )
            {
                return 0;
            }
            break;
    }
    return 1;
}

#pragma INCLUDE_ASM("asm/Game/item_init_helper_800340D0.s")        // 1064 bytes

GV_ACT *item_init_800344F8(int name, int where, int argc, char **argv)
{
    Actor_Item *pActor; // $s0
    int         inited; // $s1

    pActor = (Actor_Item *)GV_NewActor_800150E4(5, sizeof(Actor_Item));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0, (TActorFunction)item_act_80033784,
                                  (TActorFunction)item_kill_80033F88, aItemC);
        pActor->field_112_state = 0;
        inited = item_init_helper_800340D0(pActor, name, where);
        if (inited > 0)
        {
            pActor->field_10E = -1;
            pActor->field_108_where = where;
            mts_nullsub_8_8008BB98(1, aItemMapD, where);
            pActor->field_10C_64 = 64;
        }
        else
        {
            GV_DestroyActor_800151C8(&pActor->field_0);
            if (inited == 0)
            {
                return (GV_ACT *)pActor;
            }
            else
            {
                return (GV_ACT *)0;
            }
        }
    }
    return (GV_ACT *)pActor;
}

int item_init_helper_800345C0(Actor_Item *pActor, SVECTOR *pPos, SVECTOR *a3, Item_Info *pItemInfo, int where)
{

    int type; // $s3

    const char *str_name; // $v0

    int i; // $v1

    GM_Control *pCtrl;

    type = pItemInfo->field_4_type;
    pActor->field_114_item_id = pItemInfo->field_6_id;
    pActor->field_116_ammo_amount = pItemInfo->field_8_amount;
    str_name = pItemInfo->field_0_pName;
    pActor->field_120_pScript = 0;
    pActor->field_118_str = str_name;
    if (!item_init_helper_helper_80034020(pActor, type))
    {
        return -1;
    }

    pCtrl = &pActor->field_20_ctrl;
    if (Res_Control_init_loader_8002599C(pCtrl, 0x5D43, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard_8002622C(pCtrl, 100, 500, 500);
    GM_ConfigControlInterp_80026244(pCtrl, 0);

    pCtrl->field_55_flags = (CONTROL_FLAG_UNK1 | CONTROL_FLAG_UNK2);
    pCtrl->field_44_movementVector = *a3;
    pCtrl->field_44_movementVector.vy = 160;
    pCtrl->field_0_position = *pPos;

    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)&pActor->field_9C_kmd, type + 0x4D5F, 877, 0);
    GM_ConfigObjectJoint_80034CB4(&pActor->field_9C_kmd);
    GM_ConfigObjectLight_80034C44(&pActor->field_9C_kmd, &pActor->field_C8_mtx);
    GM_ConfigObjectStep_80034C54(&pActor->field_9C_kmd, &pCtrl->field_44_movementVector);

    for (i = 0; i < 2; i++)
    {
        setLineF4(&pActor->field_124_lineF4_array[i]);
        setRGB0(&pActor->field_124_lineF4_array[i], 255, 255, 255);
    }

    return 0;
}

GV_ACT *item_init_80034758(SVECTOR *pPos, SVECTOR *a2, Item_Info *pItemInfo)
{
    Actor_Item *pActor = (Actor_Item *)GV_NewActor_800150E4(5, sizeof(Actor_Item));
    int         map;
    if (pActor)
    {

        GV_SetNamedActor_8001514C(&pActor->field_0, (TActorFunction)item_act_80033784,
                                  (TActorFunction)item_kill_80033F88, aItemC);

        if (item_init_helper_800345C0(pActor, pPos, a2, pItemInfo, GM_CurrentMap_800AB9B0) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0);
            return 0;
        }

        pActor->field_10E = pItemInfo->field_A;
        map = GM_CurrentMap_800AB9B0;
        pActor->field_108_where = map;

        pActor->field_112_state = 1;
        pActor->field_10C_64 = 512;

        GM_Sound_80032968(0, 63, 0xDu);
    }
    return &pActor->field_0;
}
