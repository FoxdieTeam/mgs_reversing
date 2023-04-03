#include "item.h"
#include "object.h"
#include "game.h"
#include "Game/linkvarbuf.h"

extern int            GM_CurrentMap_800AB9B0;
extern SVECTOR        DG_ZeroVector_800AB39C;
extern int            GV_Clock_800AB920;
extern int            GM_PlayerStatus_800ABA50;
extern int            GM_GameStatus_800AB3CC;
extern CONTROL    *gSnaControl_800AB9F4;
extern unsigned short GM_ItemTypes_8009D598[];
extern int            dword_800ABA0C;
extern                SVECTOR svector_800ABA10;

extern short word_800AB8EC;
short        SECTION(".word_800AB8EC") word_800AB8EC;

extern const char aFull[];           // = "FULL"
extern const char aGetWeaponFirst[]; // = "GET WEAPON FIRST"
extern const char aS_3[];            // = "%s"
extern const char aItemC[];          // = "item.c"
extern const char aItemMapD[];       // = "Item map = %d\n"
extern const char aNoIdItem[];       // = "NO ID ITEM\n"
extern const char aShadow[];         // = "shadow"

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

int item_act_helper_800335D0(Actor_Item *pActor)
{
    SVECTOR vec;
    int diff;
    unsigned short vy;

    if (!(pActor->field_108_where & dword_800ABA0C))
    {
        return 0;
    }

    vec = svector_800ABA10;

    diff = pActor->field_20_ctrl.field_0_mov.vy - vec.vy;

    if (diff < 0)
    {
        diff = -diff;
    }

    vy = pActor->field_20_ctrl.field_0_mov.vy;

    if (diff > 1000)
    {
        return 0;
    }

    vec.vy = vy;
    diff = pActor->field_20_ctrl.field_0_mov.vx - vec.vx;

    if (abs(diff) > 500)
    {
        return 0;
    }

    diff = pActor->field_20_ctrl.field_0_mov.vz - vec.vz;

    if (abs(diff) > 500)
    {
        return 0;
    }

    return 1;
}

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

int item_act_helper_80033704(short *pOut, SVECTOR *pIn)
{
    long z;

    gte_SetRotMatrix(&DG_Chanl(0)->field_10_eye_inv);
    gte_SetTransMatrix(&DG_Chanl(0)->field_10_eye_inv);

    gte_ldv0(pIn);
    gte_rtps();
    gte_stsxy(pOut);
    gte_stsz(&z);

    return z > 0;
}

void item_act_80033784(Actor_Item *pActor)
{
    short pos[2];
    SVECTOR position;
    const char *pText;
    CONTROL *pCtrl;
    int vx;
    int state;
    int x, y ,z;
    char *pOt;
    LINE_F4* pLine;
    int newx, newy;


    GM_CurrentMap_800AB9B0 = pActor->field_108_where;

    if (pActor->field_11C_full_str)
    {
        if (item_act_helper_80033704(pos, &pActor->field_20_ctrl.field_0_mov))
        {
            if (pActor->field_110_counter < 45)
            {
                pText = pActor->field_118_str;
            }
            else
            {
                pText = pActor->field_11C_full_str;
            }

            if (pActor->field_110_counter < 16)
            {
                pos[1] -= pActor->field_110_counter;
            }
            else
            {
                pos[1] -= 16;
            }

            if (pActor->field_11C_full_str != pActor->field_118_str)
            {
                menu_Color_80038B4C(255, 48, 48);
            }
            else
            {
                menu_Color_80038B4C(200, 200, 200);
            }

            menu_Text_XY_Flags_80038B34(pos[0] + 160, pos[1] + 104, 0x12);
            menu_Text_80038C38(pText);

            menu_Color_80038B4C(1, 1, 1);
            menu_Text_XY_Flags_80038B34(pos[0] + 161, pos[1] + 105, 0x12);
            menu_Text_80038C38(pText);

            menu_Text_Init_80038B98();
        }

        if (pActor->field_110_counter > 90)
        {
            if (pActor->field_112_state == 2)
            {
                GV_DestroyActor_800151C8(&pActor->field_0);
            }
            else if (item_act_helper_800335D0(pActor))
            {
                pActor->field_110_counter = 50;
            }
            else
            {
                pActor->field_11C_full_str = NULL;
            }
        }

        pActor->field_110_counter++;

        if (pActor->field_112_state == 2)
        {
            return;
        }
    }

    if ((pActor->field_112_state == 0) && (pActor->field_9C_kmd.objs->bound_mode == 0) && (pActor->field_10E <= 0))
    {
        return;
    }

    if (pActor->field_10E > 0)
    {
        if (--pActor->field_10E < 90)
        {
            if ((pActor->field_10E % 8) < 2)
            {
                DG_InvisibleObjs(pActor->field_9C_kmd.objs);
            }
            else
            {
                DG_VisibleObjs(pActor->field_9C_kmd.objs);
            }
        }

        if (pActor->field_10E == 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0);
            return;
        }
    }

    pCtrl = &pActor->field_20_ctrl;

    if (pActor->field_10C_64 > 73)
    {
        pActor->field_10C_64 -= 10;
    }

    pCtrl->field_4C_turn_vec.vy += pActor->field_10C_64;
    pCtrl->field_4C_turn_vec.vy &= 4095;

    if (pActor->field_112_state == 1)
    {
        if ((pCtrl->field_57 != 0) && (pCtrl->field_44_movementVector.vy < 0))
        {
            pCtrl->field_44_movementVector.vy = -pCtrl->field_44_movementVector.vy / 16;

            if (pCtrl->field_44_movementVector.vy < 16)
            {
                GM_ConfigControlHazard_8002622C(pCtrl, -1, -2, -1);
                pCtrl->field_44_movementVector = DG_ZeroVector_800AB39C;
                pActor->field_112_state = 0;
            }
        }
        else
        {
            pCtrl->field_44_movementVector.vy -= 16;
        }

        GM_ActControl_80025A7C(pCtrl);
    }
    else
    {
        GM_CurrentMap_800AB9B0 = pCtrl->field_2C_map->field_0_map_index_bit;

        if (pActor->field_11C_full_str)
        {
            position = pCtrl->field_0_mov;
            vx = (90 - pActor->field_110_counter) * 8;

            if (vx > 80)
            {
                vx = 80;
            }

            if (GV_Clock_800AB920 & 1)
            {
                vx = -vx;
            }

            position.vx += vx;
            DG_SetPos2_8001BC8C(&position, &pCtrl->field_4C_turn_vec);
        }
        else
        {
            DG_SetPos2_8001BC8C(&pCtrl->field_0_mov, &pCtrl->field_4C_turn_vec);
        }
    }

    GM_ActObject2_80034B88(&pActor->field_9C_kmd);
    DG_GetLightMatrix2_8001A5D8(&pCtrl->field_0_mov, pActor->field_C8_mtx);

    if (item_act_helper_800335D0(pActor) && (pActor->field_112_state != 1))
    {
        switch (pActor->field_113)
        {
        case 0:
            state = item_act_helper_800333F8(pActor->field_114_item_id, pActor->field_116_ammo_amount);
            break;

        case 1:
            state = item_act_try_add_ammo2_8003330C(pActor->field_114_item_id, pActor->field_116_ammo_amount);
            break;

        case 2:
            state = item_act_try_add_ammo_80033384(pActor->field_114_item_id, pActor->field_116_ammo_amount);
            break;
        }

        switch (state)
        {
        case 1:
            DG_InvisibleObjs(pActor->field_9C_kmd.objs);

            if (pActor->field_15C_pPrim)
            {
                DG_InvisiblePrim(pActor->field_15C_pPrim);
            }

            pActor->field_112_state = 2;
            pActor->field_110_counter = 0;
            pActor->field_11C_full_str = pActor->field_118_str;

            GM_Sound_80032968(0, 63, 22);
            return;

        case 0:
            if (!pActor->field_11C_full_str)
            {
                pActor->field_11C_full_str = aFull;
                pActor->field_110_counter = 0;
                GM_Sound_80032968(0, 63, 11);
            }
            break;

        case 2:
            if (!pActor->field_11C_full_str)
            {
                pActor->field_11C_full_str = aGetWeaponFirst;
                pActor->field_110_counter = 0;
                GM_Sound_80032968(0, 63, 11);
            }
            break;
        }
    }

    if (!pActor->field_118_str || pActor->field_11C_full_str)
    {
        return;
    }

    if (!(GM_PlayerStatus_800ABA50 & (PLAYER_STATUS_FIRST_PERSON_DUCT | PLAYER_STATUS_FIRST_PERSON)) || (GM_GameStatus_800AB3CC & 0x90000000))
    {
        pActor->field_110_counter = 0;
        return;
    }

    x = gSnaControl_800AB9F4->field_0_mov.vx - pCtrl->field_0_mov.vx;

    if (x < 0)
    {
        x = -x;
    }

    y = gSnaControl_800AB9F4->field_0_mov.vy - pCtrl->field_0_mov.vy;

    if (y < 0)
    {
        y = -y;
    }

    z = gSnaControl_800AB9F4->field_0_mov.vz - pCtrl->field_0_mov.vz;

    if (z < 0)
    {
        z = -z;
    }

    if ( (x >= 2000) || (y >= 2000) || (z >= 2000 ) )
    {
        return;
    }

    if ((pActor->field_110_counter++ % 60) <= 20)
    {
        return;
    }

    pOt = DG_Chanl(1)->mOrderingTables[GV_Clock_800AB920];
    pLine = &pActor->field_124_lineF4_array[GV_Clock_800AB920];

    if (!item_act_helper_80033704(&position.vx, &pCtrl->field_0_mov))
    {
        return;
    }

    newx = position.vx + 160;
    newy = position.vy + 104;

    if ((newy < -32) || (newy > 300))
    {
        return;
    }

    if (newy < 32)
    {
        newy = 32;
    }

    if (newy > 224)
    {
        newy = 224;
    }

    pLine->x0 = newx;
    pLine->x1 = newx + 16;
    pLine->x2 = newx + 16;

    pLine->y0 = newy;
    pLine->y1 = newy - 16;
    pLine->y2 = newy - 16;
    pLine->y3 = newy - 23;

    addPrim(pOt, pLine);

    menu_Color_80038B4C(200, 200, 200);
    menu_Text_XY_Flags_80038B34(pLine->x1 + 5, pLine->y1 - 8, 0x10);
    menu_Text_80038C38(aS_3, pActor->field_118_str);

    menu_Color_80038B4C(1, 1, 1);
    menu_Text_XY_Flags_80038B34(pLine->x1 + 6, pLine->y1 - 7, 0x10);
    pLine->x2 = pLine->x3 = menu_Text_80038C38(aS_3, pActor->field_118_str) + 3;
}

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
            if ( (GM_DifficultyFlag == DIFFICULTY_VERY_EASY) && (item_id == ITEM_SCOPE) )
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

int item_init_helper_800340D0(Actor_Item *pActor, int name, int where)
{
    short sVar3;
    int i;
    char *pcVar5;
    char *bReadVec2;
    unsigned char *puVar6;
    char *pbVar7;
    char *m_return;
    DG_PRIM *pPrim;
    DG_TEX *pTex;
    int type;
    CONTROL *pControl;
    OBJECT *pObject;
    int iVar10;
    int code;
    int value;
    int k500;
    SVECTOR *pVec1;
    SVECTOR *pVec2;
    SVECTOR *pVec3;
    SVECTOR *pVec4;

    pControl = &pActor->field_20_ctrl;
    GM_CurrentMap_800AB9B0 = where;
    pActor->field_108_where = where;

    if (Res_Control_init_loader_8002599C(pControl, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard_8002622C(pControl, -1, -2, -1);
    GM_ConfigControlInterp_80026244(pControl, '\0');

    pcVar5 = (char *) GCL_GetParam_80020968('p');
    bReadVec2 = (char *) GCL_GetParam_80020968('d');
    GM_ConfigControlString_800261C0(pControl, pcVar5, bReadVec2);

    pControl->field_44_movementVector = DG_ZeroVector_800AB39C;
    pControl->field_55_skip_flag = CTRL_SKIP_TRAP | CTRL_SKIP_MESSAGE;

    puVar6 = (unsigned char *) GCL_GetParam_80020968('b');
    type = 0;

    if (puVar6)
    {
        type = GCL_GetNextInt_800209E8(puVar6);
    }

    puVar6 = (unsigned char *)GCL_GetParam_80020968('i');
    if (!puVar6)
    {
        mts_printf_8008BBA0(aNoIdItem);
        return -1;
    }

    pActor->field_114_item_id = GCL_GetNextInt_800209E8(puVar6);
    puVar6 = (unsigned char *) GCL_GetParam_80020968('n');
    if (puVar6)
    {
      pActor->field_116_ammo_amount = GCL_GetNextInt_800209E8(puVar6);
    }
    else
    {
        pActor->field_116_ammo_amount = 1;
    }

    m_return = (char *)GCL_GetParam_80020968('m');

    if (m_return)
    {
      pcVar5 = GCL_Read_String_80020A70(m_return);
      pActor->field_118_str = pcVar5;
    }

    pActor->field_11C_full_str = (char *) 0x0;

    iVar10 = 0x1c2;
    puVar6 = (unsigned char *) GCL_GetParam_80020968('h');
    if (puVar6)
    {
      iVar10 = GCL_GetNextInt_800209E8(puVar6);
    }

    pActor->field_120_pScript = (unsigned char *) 0x0;

    if (GCL_GetParam_80020968('e'))
    {
        pActor->field_120_pScript = (unsigned char *)GCL_GetNextInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }
    else if (GCL_GetParam_80020968('x'))
    {
        pbVar7 = (char *) GCL_Get_Param_Result_80020AA4();
        GCL_GetNextValue_8002069C(pbVar7, &code, &value);
        pActor->field_120_pScript = (unsigned char *)value;
    }

    if (!item_init_helper_helper_80034020(pActor, type))
    {
        return 0;
    }

    if ((GM_DifficultyFlag == DIFFICULTY_EXTREME) && (type == 4) && (pActor->field_114_item_id == ITEM_RATION))
    {
        return 0;
    }

    GV_ZeroMemory_8001619C(pActor->field_C0, 8);
    pObject = &pActor->field_9C_kmd;
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *) pObject, type + 0x4d5f, 0x36d, 0);
    GM_ConfigObjectJoint_80034CB4(pObject);
    GM_ConfigObjectLight_80034C44(pObject, pActor->field_C8_mtx);
    GM_ConfigObjectStep_80034C54(pObject, &pActor->field_20_ctrl.field_44_movementVector);

    if (GCL_GetParam_80020968('v'))
    {
        pActor->field_9C_kmd.objs[2].world.m[1][1] = -10000;
    }

    for (i = 0; i < 2; i++)
    {
        setLineF4(&pActor->field_124_lineF4_array[i]);
        setRGB0(&pActor->field_124_lineF4_array[i], 255, 255, 255);
    }

    if (iVar10 >= 0)
    {
        pVec1 = &pActor->field_160;
        pVec2 = &pActor->field_168;
        pVec3 = &pActor->field_170;
        pVec4 = &pActor->field_178;

        sVar3 = pControl->field_0_mov.vy;

        pVec4->vy = sVar3;
        pActor->field_170.vy = sVar3;
        pVec2->vy = sVar3;
        pVec1->vy = sVar3;

        sVar3 = pControl->field_0_mov.vx + 0x100;
        pActor->field_170.vx = sVar3;
        pVec1->vx = sVar3;

        sVar3 = pControl->field_0_mov.vz + 0x100;
        pVec2->vz = sVar3;
        pVec1->vz = sVar3;

        sVar3 = pControl->field_0_mov.vx - 0x100;
        pVec4->vx = sVar3;
        pVec1[1].vx = sVar3;

        sVar3 = pControl->field_0_mov.vz - 0x100;
        pVec4->vz = sVar3;
        pVec1[2].vz = sVar3;

        pControl->field_0_mov.vy += iVar10;

        pPrim = DG_GetPrim(0x1012, 1, 0, &pActor->field_160, NULL);
        pActor->field_15C_pPrim = pPrim;

        k500 = 500;

        if (!pPrim)
        {
            return -1;
        }

        pPrim->field_2E_k500 = k500;

        pTex = DG_GetTexture_8001D830(GV_StrCode_80016CCC(aShadow));
        if (!pTex)
        {
            return -1;
        }

        item_init_prim_buffer_800336A4(&pPrim->field_40_pBuffers[0]->poly_ft4, pTex);
        item_init_prim_buffer_800336A4(&pPrim->field_40_pBuffers[1]->poly_ft4, pTex);

        setRGB0(&pPrim->field_40_pBuffers[0]->poly_ft4, 80, 80, 80);
        setRGB0(&pPrim->field_40_pBuffers[1]->poly_ft4, 80, 80, 80);
    }
    else
    {
        pActor->field_15C_pPrim = 0;
    }

    GM_ActControl_80025A7C(pControl);
    GM_ActObject2_80034B88(pObject);
    return 1;
}

Actor_Item * item_init_800344F8(int name, int where, int argc, char **argv)
{
    Actor_Item *pActor;
    int         inited;

    pActor = (Actor_Item *)GV_NewActor_800150E4(5, sizeof(Actor_Item));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0,
                                  (TActorFunction)&item_act_80033784,
                                  (TActorFunction)&item_kill_80033F88,
                                  aItemC);
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
                return pActor;
            }
            else
            {
                return NULL;
            }
        }
    }

    return pActor;
}

int item_init_helper_800345C0(Actor_Item *pActor, SVECTOR *pPos, SVECTOR *a3, Item_Info *pItemInfo, int where)
{
    int type; // $s3
    const char *str_name; // $v0
    int i; // $v1
    CONTROL *pCtrl;

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

    pCtrl->field_55_skip_flag = CTRL_SKIP_TRAP | CTRL_SKIP_MESSAGE;
    pCtrl->field_44_movementVector = *a3;
    pCtrl->field_44_movementVector.vy = 160;
    pCtrl->field_0_mov = *pPos;

    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)&pActor->field_9C_kmd, type + 0x4D5F, 877, 0);
    GM_ConfigObjectJoint_80034CB4(&pActor->field_9C_kmd);
    GM_ConfigObjectLight_80034C44(&pActor->field_9C_kmd, pActor->field_C8_mtx);
    GM_ConfigObjectStep_80034C54(&pActor->field_9C_kmd, &pCtrl->field_44_movementVector);

    for (i = 0; i < 2; i++)
    {
        setLineF4(&pActor->field_124_lineF4_array[i]);
        setRGB0(&pActor->field_124_lineF4_array[i], 255, 255, 255);
    }

    return 0;
}

Actor_Item * item_init_80034758(SVECTOR *pPos, SVECTOR *a2, Item_Info *pItemInfo)
{
    Actor_Item *pActor;
    int         map;

    pActor = (Actor_Item *)GV_NewActor_800150E4(5, sizeof(Actor_Item));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0,
                                  (TActorFunction)&item_act_80033784,
                                  (TActorFunction)&item_kill_80033F88,
                                  aItemC);

        if (item_init_helper_800345C0(pActor, pPos, a2, pItemInfo, GM_CurrentMap_800AB9B0) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0);
            return NULL;
        }

        pActor->field_10E = pItemInfo->field_A;
        map = GM_CurrentMap_800AB9B0;
        pActor->field_108_where = map;

        pActor->field_112_state = 1;
        pActor->field_10C_64 = 512;

        GM_Sound_80032968(0, 63, 13);
    }

    return pActor;
}
