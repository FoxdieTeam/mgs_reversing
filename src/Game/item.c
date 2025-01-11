#include "item.h"

#include <stdio.h>
#include <kernel.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "mts/mts.h" // for fprintf
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"
#include "Game/control.h"
#include "Game/object.h"
#include "Game/linkvarbuf.h"
#include "SD/g_sound.h"

extern int            GM_CurrentMap_800AB9B0;
extern int            GV_Clock_800AB920;
extern int            GM_PlayerStatus_800ABA50;
extern CONTROL       *GM_PlayerControl_800AB9F4;
extern unsigned short GM_ItemTypes[];
extern int            GM_PlayerMap_800ABA0C;
extern SVECTOR        GM_PlayerPosition_800ABA10;

/*---------------------------------------------------------------------------*/

typedef struct ItemWork
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT_NO_ROTS field_9C_kmd;
    char           field_C0[8];
    MATRIX         field_C8_mtx[2];
    int            field_108_where;
    short          field_10C_64;
    short          field_10E;
    short          field_110_counter;
    unsigned char  field_112_state;
    char           field_113;
    short          field_114_item_id;
    short          field_116_ammo_amount;
    const char    *field_118_str;
    const char    *field_11C_full_str;
    unsigned char *field_120_pScript;
    LINE_F4        field_124_lineF4_array[2];
    DG_PRIM       *field_15C_pPrim;
    SVECTOR        field_160;
    SVECTOR        field_168;
    SVECTOR        field_170;
    SVECTOR        field_178;
} ItemWork;

#define EXEC_LEVEL 5

/*---------------------------------------------------------------------------*/

STATIC int item_act_try_add_ammo2_8003330C(int weapon_id, short amount)
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

STATIC int item_act_try_add_ammo_80033384(int weapon_id, short amount)
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

STATIC int item_act_helper_800333F8(int item_id, int param_2)
{
    int item_type;
    int max_capacity;

    if (item_id == (char)ITEM_NONE)
    {
        item_all_items_and_weapons_unknown_80033560();
        return 1;
    }

    item_type = GM_ItemTypes[item_id + 1];

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
        if (max_capacity < ((GM_Items[item_id] * 0x10000) >> 16))
        {
            GM_Items[item_id] = max_capacity;
        }
        return 1;
    }

    GM_Items[item_id] = param_2;
    return 1;
}

void item_all_items_and_weapons_unknown2_80033500(void)
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

void item_all_items_and_weapons_unknown_80033560(void)
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

STATIC int item_act_helper_800335D0(ItemWork *work)
{
    SVECTOR vec;
    int diff;
    unsigned short vy;

    if (!(work->field_108_where & GM_PlayerMap_800ABA0C))
    {
        return 0;
    }

    vec = GM_PlayerPosition_800ABA10;

    diff = work->control.mov.vy - vec.vy;

    if (diff < 0)
    {
        diff = -diff;
    }

    vy = work->control.mov.vy;

    if (diff > 1000)
    {
        return 0;
    }

    vec.vy = vy;
    diff = work->control.mov.vx - vec.vx;

    if (abs(diff) > 500)
    {
        return 0;
    }

    diff = work->control.mov.vz - vec.vz;

    if (abs(diff) > 500)
    {
        return 0;
    }

    return 1;
}

STATIC void item_init_prim_buffer_800336A4(POLY_FT4 *prims, DG_TEX *tex)
{
    char t_u0; // $a1
    char t_v0; // $v1
    char t_u1; // $a0
    char t_v2; // $v1

    setPolyFT4(prims);
    setSemiTrans(prims, 1);

    t_u0 = tex->off_x;
    t_u1 = t_u0 + tex->w;

    t_v0 = tex->off_y;
    t_v2 = t_v0 + tex->h;

    prims->u0 = t_u0;
    prims->v0 = t_v0;

    prims->u1 = t_u1;
    prims->v1 = t_v0;

    prims->u2 = t_u0;
    prims->v2 = t_v2;

    prims->u3 = t_u1;
    prims->v3 = t_v2;

    prims->tpage = tex->tpage;
    prims->clut = tex->clut;
}

STATIC int item_act_helper_80033704(short *pOut, SVECTOR *pIn)
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

STATIC void item_Act(ItemWork *work)
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


    GM_CurrentMap_800AB9B0 = work->field_108_where;

    if (work->field_11C_full_str)
    {
        if (item_act_helper_80033704(pos, &work->control.mov))
        {
            if (work->field_110_counter < 45)
            {
                pText = work->field_118_str;
            }
            else
            {
                pText = work->field_11C_full_str;
            }

            if (work->field_110_counter < 16)
            {
                pos[1] -= work->field_110_counter;
            }
            else
            {
                pos[1] -= 16;
            }

            if (work->field_11C_full_str != work->field_118_str)
            {
                MENU_Color(255, 48, 48);
            }
            else
            {
                MENU_Color(200, 200, 200);
            }

            MENU_Locate(pos[0] + 160, pos[1] + 104, 0x12);
            MENU_Printf(pText);

            MENU_Color(1, 1, 1);
            MENU_Locate(pos[0] + 161, pos[1] + 105, 0x12);
            MENU_Printf(pText);

            menu_Text_Init_80038B98();
        }

        if (work->field_110_counter > 90)
        {
            if (work->field_112_state == 2)
            {
                GV_DestroyActor(&work->actor);
            }
            else if (item_act_helper_800335D0(work))
            {
                work->field_110_counter = 50;
            }
            else
            {
                work->field_11C_full_str = NULL;
            }
        }

        work->field_110_counter++;

        if (work->field_112_state == 2)
        {
            return;
        }
    }

    if ((work->field_112_state == 0) && (work->field_9C_kmd.objs->bound_mode == 0) && (work->field_10E <= 0))
    {
        return;
    }

    if (work->field_10E > 0)
    {
        if (--work->field_10E < 90)
        {
            if ((work->field_10E % 8) < 2)
            {
                DG_InvisibleObjs(work->field_9C_kmd.objs);
            }
            else
            {
                DG_VisibleObjs(work->field_9C_kmd.objs);
            }
        }

        if (work->field_10E == 0)
        {
            GV_DestroyActor(&work->actor);
            return;
        }
    }

    pCtrl = &work->control;

    if (work->field_10C_64 > 73)
    {
        work->field_10C_64 -= 10;
    }

    pCtrl->turn.vy += work->field_10C_64;
    RevisionDir( pCtrl->turn.vy );

    if (work->field_112_state == 1)
    {
        if ((pCtrl->field_57 != 0) && (pCtrl->step.vy < 0))
        {
            pCtrl->step.vy = -pCtrl->step.vy / 16;

            if (pCtrl->step.vy < 16)
            {
                GM_ConfigControlHazard(pCtrl, -1, -2, -1);
                pCtrl->step = DG_ZeroVector;
                work->field_112_state = 0;
            }
        }
        else
        {
            pCtrl->step.vy -= 16;
        }

        GM_ActControl(pCtrl);
    }
    else
    {
        GM_CurrentMap_800AB9B0 = pCtrl->map->index;

        if (work->field_11C_full_str)
        {
            position = pCtrl->mov;
            vx = (90 - work->field_110_counter) * 8;

            if (vx > 80)
            {
                vx = 80;
            }

            if (GV_Clock_800AB920 & 1)
            {
                vx = -vx;
            }

            position.vx += vx;
            DG_SetPos2(&position, &pCtrl->turn);
        }
        else
        {
            DG_SetPos2(&pCtrl->mov, &pCtrl->turn);
        }
    }

    GM_ActObject2((OBJECT *)&work->field_9C_kmd);
    DG_GetLightMatrix2(&pCtrl->mov, work->field_C8_mtx);

    if (item_act_helper_800335D0(work) && (work->field_112_state != 1))
    {
        switch (work->field_113)
        {
        case 0:
            state = item_act_helper_800333F8(work->field_114_item_id, work->field_116_ammo_amount);
            break;

        case 1:
            state = item_act_try_add_ammo2_8003330C(work->field_114_item_id, work->field_116_ammo_amount);
            break;

        case 2:
            state = item_act_try_add_ammo_80033384(work->field_114_item_id, work->field_116_ammo_amount);
            break;
        }

        switch (state)
        {
        case 1:
            DG_InvisibleObjs(work->field_9C_kmd.objs);

            if (work->field_15C_pPrim)
            {
                DG_InvisiblePrim(work->field_15C_pPrim);
            }

            work->field_112_state = 2;
            work->field_110_counter = 0;
            work->field_11C_full_str = work->field_118_str;

            GM_SeSet2(0, 63, SE_ITEM_GET);
            return;

        case 0:
            if (!work->field_11C_full_str)
            {
                work->field_11C_full_str = "FULL";
                work->field_110_counter = 0;
                GM_SeSet2(0, 63, SE_ITEM_FULL);
            }
            break;

        case 2:
            if (!work->field_11C_full_str)
            {
                work->field_11C_full_str = "GET WEAPON FIRST";
                work->field_110_counter = 0;
                GM_SeSet2(0, 63, SE_ITEM_FULL);
            }
            break;
        }
    }

    if (!work->field_118_str || work->field_11C_full_str)
    {
        return;
    }

    if (!(GM_PlayerStatus_800ABA50 & (PLAYER_INTRUDE | PLAYER_FIRST_PERSON)) || (GM_GameStatus & (STATE_PADRELEASE | STATE_DEMO)))
    {
        work->field_110_counter = 0;
        return;
    }

    x = GM_PlayerControl_800AB9F4->mov.vx - pCtrl->mov.vx;

    if (x < 0)
    {
        x = -x;
    }

    y = GM_PlayerControl_800AB9F4->mov.vy - pCtrl->mov.vy;

    if (y < 0)
    {
        y = -y;
    }

    z = GM_PlayerControl_800AB9F4->mov.vz - pCtrl->mov.vz;

    if (z < 0)
    {
        z = -z;
    }

    if ( (x >= 2000) || (y >= 2000) || (z >= 2000 ) )
    {
        return;
    }

    if ((work->field_110_counter++ % 60) <= 20)
    {
        return;
    }

    pOt = DG_ChanlOTag(1);
    pLine = &work->field_124_lineF4_array[GV_Clock_800AB920];

    if (!item_act_helper_80033704(&position.vx, &pCtrl->mov))
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

    MENU_Color(200, 200, 200);
    MENU_Locate(pLine->x1 + 5, pLine->y1 - 8, 0x10);
    MENU_Printf("%s", work->field_118_str);

    MENU_Color(1, 1, 1);
    MENU_Locate(pLine->x1 + 6, pLine->y1 - 7, 0x10);
    pLine->x2 = pLine->x3 = MENU_Printf("%s", work->field_118_str) + 3;
}

STATIC void item_Die(ItemWork *work)
{
    DG_PRIM       *field_15C_pPrim;   // $s0
    unsigned char *field_120_pScript; // $a0

    GM_FreeControl(&work->control);
    GM_FreeObject((OBJECT *)&work->field_9C_kmd);

    field_15C_pPrim = work->field_15C_pPrim;
    if (field_15C_pPrim)
    {
        DG_DequeuePrim(work->field_15C_pPrim);
        DG_FreePrim(field_15C_pPrim);
    }

    if (work->field_112_state == 2)
    {
        field_120_pScript = work->field_120_pScript;
        if (field_120_pScript)
        {
            if ((int)field_120_pScript < 0)
            {
                GCL_ExecBlock(field_120_pScript, 0);
            }
            else
            {
                GCL_ExecProc((int)field_120_pScript, 0);
            }
        }
    }
}

STATIC int item_init_helper_helper_80034020( ItemWork *work, int type )
{
    int item_id;

    item_id = work->field_114_item_id;
    if ( item_id == (char)ITEM_NONE )
    {
        return 1;
    }
    work->field_113 = 0;
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
            work->field_113 = 2;
            break;

        case 0:
            if (item_id > 9 )
            {
                return 0;
            }
            work->field_113 = 1;
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

STATIC int item_GetResources(ItemWork *work, int name, int where)
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
    OBJECT_NO_ROTS *pObject;
    int iVar10;
    int code;
    int value;
    int k500;
    SVECTOR *pVec1;
    SVECTOR *pVec2;
    SVECTOR *pVec3;
    SVECTOR *pVec4;

    pControl = &work->control;
    GM_CurrentMap_800AB9B0 = where;
    work->field_108_where = where;

    if (GM_InitControl(pControl, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(pControl, -1, -2, -1);
    GM_ConfigControlInterp(pControl, '\0');

    pcVar5 = (char *) GCL_GetOption('p');
    bReadVec2 = (char *) GCL_GetOption('d');
    GM_ConfigControlString(pControl, pcVar5, bReadVec2);

    pControl->step = DG_ZeroVector;
    pControl->skip_flag = CTRL_SKIP_TRAP | CTRL_SKIP_MESSAGE;

    puVar6 = (unsigned char *) GCL_GetOption('b');
    type = 0;

    if (puVar6)
    {
        type = GCL_StrToInt(puVar6);
    }

    puVar6 = (unsigned char *)GCL_GetOption('i');
    if (!puVar6)
    {
        printf("NO ID ITEM\n");
        return -1;
    }

    work->field_114_item_id = GCL_StrToInt(puVar6);
    puVar6 = (unsigned char *) GCL_GetOption('n');
    if (puVar6)
    {
      work->field_116_ammo_amount = GCL_StrToInt(puVar6);
    }
    else
    {
        work->field_116_ammo_amount = 1;
    }

    m_return = GCL_GetOption('m');

    if (m_return)
    {
      pcVar5 = GCL_ReadString(m_return);
      work->field_118_str = pcVar5;
    }

    work->field_11C_full_str = (char *) 0x0;

    iVar10 = 0x1c2;
    puVar6 = (unsigned char *) GCL_GetOption('h');
    if (puVar6)
    {
      iVar10 = GCL_StrToInt(puVar6);
    }

    work->field_120_pScript = (unsigned char *) 0x0;

    if (GCL_GetOption('e'))
    {
        work->field_120_pScript = (unsigned char *)GCL_StrToInt(GCL_GetParamResult());
    }
    else if (GCL_GetOption('x'))
    {
        pbVar7 = (char *) GCL_GetParamResult();
        GCL_GetNextValue(pbVar7, &code, &value);
        work->field_120_pScript = (unsigned char *)value;
    }

    if (!item_init_helper_helper_80034020(work, type))
    {
        return 0;
    }

    if ((GM_DifficultyFlag == DIFFICULTY_EXTREME) && (type == 4) && (work->field_114_item_id == ITEM_RATION))
    {
        return 0;
    }

    GV_ZeroMemory(work->field_C0, 8);
    pObject = &work->field_9C_kmd;
    GM_InitObjectNoRots(pObject, type + 0x4d5f, 0x36d, 0);
    GM_ConfigObjectJoint((OBJECT *)pObject);
    GM_ConfigObjectLight((OBJECT *)pObject, work->field_C8_mtx);
    GM_ConfigObjectStep((OBJECT *)pObject, &work->control.step);

    if (GCL_GetOption('v'))
    {
        work->field_9C_kmd.objs[2].world.m[1][1] = -10000;
    }

    for (i = 0; i < 2; i++)
    {
        setLineF4(&work->field_124_lineF4_array[i]);
        setRGB0(&work->field_124_lineF4_array[i], 255, 255, 255);
    }

    if (iVar10 >= 0)
    {
        pVec1 = &work->field_160;
        pVec2 = &work->field_168;
        pVec3 = &work->field_170;
        pVec4 = &work->field_178;

        sVar3 = pControl->mov.vy;

        pVec4->vy = sVar3;
        work->field_170.vy = sVar3;
        pVec2->vy = sVar3;
        pVec1->vy = sVar3;

        sVar3 = pControl->mov.vx + 0x100;
        work->field_170.vx = sVar3;
        pVec1->vx = sVar3;

        sVar3 = pControl->mov.vz + 0x100;
        pVec2->vz = sVar3;
        pVec1->vz = sVar3;

        sVar3 = pControl->mov.vx - 0x100;
        pVec4->vx = sVar3;
        pVec1[1].vx = sVar3;

        sVar3 = pControl->mov.vz - 0x100;
        pVec4->vz = sVar3;
        pVec1[2].vz = sVar3;

        pControl->mov.vy += iVar10;

        pPrim = DG_GetPrim(DG_PRIM_ONEFACE | DG_PRIM_POLY_FT4, 1, 0, &work->field_160, NULL);
        work->field_15C_pPrim = pPrim;

        k500 = 500;

        if (!pPrim)
        {
            return -1;
        }

        pPrim->field_2E_k500 = k500;

        pTex = DG_GetTexture(GV_StrCode("shadow"));
        if (!pTex)
        {
            return -1;
        }

        item_init_prim_buffer_800336A4(&pPrim->packs[0]->poly_ft4, pTex);
        item_init_prim_buffer_800336A4(&pPrim->packs[1]->poly_ft4, pTex);

        setRGB0(&pPrim->packs[0]->poly_ft4, 80, 80, 80);
        setRGB0(&pPrim->packs[1]->poly_ft4, 80, 80, 80);
    }
    else
    {
        work->field_15C_pPrim = 0;
    }

    GM_ActControl(pControl);
    GM_ActObject2((OBJECT *)pObject);
    return 1;
}

/*---------------------------------------------------------------------------*/

GV_ACT *NewItem(int name, int where, int argc, char **argv)
{
    ItemWork   *work;
    int         inited;

    work = (ItemWork *)GV_NewActor(EXEC_LEVEL, sizeof(ItemWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor,
                         (GV_ACTFUNC)&item_Act,
                         (GV_ACTFUNC)&item_Die,
                         "item.c");
        work->field_112_state = 0;
        inited = item_GetResources(work, name, where);
        if (inited > 0)
        {
            work->field_10E = -1;
            work->field_108_where = where;
            fprintf(1, "Item map = %d\n", where);
            work->field_10C_64 = 64;
        }
        else
        {
            GV_DestroyActor(&work->actor);
            if (inited == 0)
            {
                return &work->actor;
            }
            else
            {
                return NULL;
            }
        }
    }

    return &work->actor;
}

/*---------------------------------------------------------------------------*/

STATIC int item_init_helper_800345C0(ItemWork *work, SVECTOR *pPos, SVECTOR *a3, Item_Info *pItemInfo, int where)
{
    int type; // $s3
    const char *str_name; // $v0
    int i; // $v1
    CONTROL *pCtrl;

    type = pItemInfo->field_4_type;
    work->field_114_item_id = pItemInfo->field_6_id;
    work->field_116_ammo_amount = pItemInfo->field_8_amount;
    str_name = pItemInfo->field_0_pName;
    work->field_120_pScript = 0;
    work->field_118_str = str_name;
    if (!item_init_helper_helper_80034020(work, type))
    {
        return -1;
    }

    pCtrl = &work->control;
    if (GM_InitControl(pCtrl, 0x5D43, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(pCtrl, 100, 500, 500);
    GM_ConfigControlInterp(pCtrl, 0);

    pCtrl->skip_flag = CTRL_SKIP_TRAP | CTRL_SKIP_MESSAGE;
    pCtrl->step = *a3;
    pCtrl->step.vy = 160;
    pCtrl->mov = *pPos;

    GM_InitObjectNoRots(&work->field_9C_kmd, type + 0x4D5F, 877, 0);
    GM_ConfigObjectJoint((OBJECT *)&work->field_9C_kmd);
    GM_ConfigObjectLight((OBJECT *)&work->field_9C_kmd, work->field_C8_mtx);
    GM_ConfigObjectStep((OBJECT *)&work->field_9C_kmd, &pCtrl->step);

    for (i = 0; i < 2; i++)
    {
        setLineF4(&work->field_124_lineF4_array[i]);
        setRGB0(&work->field_124_lineF4_array[i], 255, 255, 255);
    }

    return 0;
}

GV_ACT *item_init_80034758(SVECTOR *pPos, SVECTOR *a2, Item_Info *pItemInfo)
{
    ItemWork   *work;
    int         map;

    work = (ItemWork *)GV_NewActor(EXEC_LEVEL, sizeof(ItemWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor,
                         (GV_ACTFUNC)&item_Act,
                         (GV_ACTFUNC)&item_Die,
                         "item.c");

        if (item_init_helper_800345C0(work, pPos, a2, pItemInfo, GM_CurrentMap_800AB9B0) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->field_10E = pItemInfo->field_A;
        map = GM_CurrentMap_800AB9B0;
        work->field_108_where = map;

        work->field_112_state = 1;
        work->field_10C_64 = 512;

        GM_SeSet2(0, 63, SE_SPAWN_ITEM);
    }

    return &work->actor;
}
