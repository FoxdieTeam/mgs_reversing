#include "scope.h"
#include "Menu/menuman.h"
#include "Game/camera.h"
#include "Game/object.h"
#include "Thing/sight.h"
#include "chara/snake/sna_init.h"
#include "Game/object.h"
#include "Game/linkvarbuf.h"
#include "libgcl/hash.h"

extern const char aZoomLevelD[];
extern const char aD_44[];  // = "%d"

extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern GM_Camera GM_Camera_800B77E8;

void scope_act_helper_helper_80062320(void *ot, void *prim)
{
    if ((GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK4000000) == 0)
    {
        addPrim(ot, prim);
    }
}

extern OBJECT *dword_800ABA20;
extern UnkCameraStruct  gUnkCameraStruct_800B77B8;
extern DG_CHNL DG_Chanls_800B1800[3];
extern SVECTOR svec_8009F2C8;

int scope_act_helper_helper_8006237C(Actor_scope *pActor)
{
    MATRIX *pMtx; // $a2
    DG_OBJS *objs; // $v0
    int bCalcLen; // $s2
    int vecLen; // $v0
    MATRIX mtx; // [sp+18h] [-30h] BYREF
    SVECTOR vecs[2]; // [sp+38h] [-10h] BYREF

    if ( GM_GameStatus_800AB3CC < 0 )
    {
        DG_CHNL* t = &DG_Chanls_800B1800[1]; 
        pMtx = &(t)->field_30_matrix;
    }
    else
    {
        objs = dword_800ABA20->objs;
        pMtx = &mtx;
        mtx = dword_800ABA20->objs->world;
        mtx.t[0] = gUnkCameraStruct_800B77B8.field_0.vx;
        mtx.t[1] = gUnkCameraStruct_800B77B8.field_0.vy;
        mtx.t[2] = gUnkCameraStruct_800B77B8.field_0.vz;
    }
    DG_SetPos_8001BC44(pMtx);
    DG_PutVector_8001BE48(&svec_8009F2C8, vecs, 2);
    bCalcLen = 0;
    if ( sub_80028454(pActor->field_50_pMap->field_8_hzd, vecs, &vecs[1], 15, 129) )
    {
        sub_80028890(&vecs[1]);
        bCalcLen = 1;
    }
    
    vecLen = 3200;
    if ( bCalcLen != 0 )
    {
        GV_SubVec3_80016D40(&vecs[1], vecs, vecs);
        vecLen = GV_VecLen3_80016D80(vecs);
    }
 
    return vecLen;
}

void scope_act_helper_800624BC(LINE_F2 *lines, int param_2, int param_3)
{
    int offsetIndex;
    lines->x1 = param_2;
    lines->x0 = param_2;
    offsetIndex = 4;
    lines[offsetIndex].x1 = 320 - param_2;
    lines[offsetIndex].x0 = 320 - param_2;
    lines[offsetIndex].y0 = param_3;
    lines->y0 = param_3;
    lines[offsetIndex].y1 = 240 - param_3;
    lines->y1 = 240 - param_3;
}

void scope_act_helper_helper_800624F4(LINE_F2 *lines, int param_2)
{
    int i;
    int var1;
    int var2;
    
    var1 = param_2 + 258;
    var2 = 66 - (param_2 * 9) / 15;

    for (i = 0; i < 4; i++)
    {
        scope_act_helper_800624BC(lines, var1, var2);
        lines++;
        var1 += 15;
        var2 -= 9;
    }
}

#pragma INCLUDE_ASM("asm/Equip/scope_act_helper_8006258C.s")        // 324 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_act_helper_800626D0.s")        // 712 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_act_helper_80062998.s")        // 580 bytes

extern int GV_Clock_800AB920;

void scope_act_helper_80062BDC(Actor_scope *scope, u_char *ot)
{
    LINE_F4 *line_f4;
    LINE_F2 *line_f2;
    short    sVar1;
    short    sVar2;
    short    sVar3;

    line_f4 = (LINE_F4 *)scope->field_7C_pPrims[GV_Clock_800AB920];
    line_f2 = (LINE_F2 *)(line_f4 + 1);
    
    sVar1 = scope->field_84 + 130;
    sVar2 = scope->field_84 + 189;
    sVar3 = scope->field_86;
    
    line_f2->x1 = sVar1;
    line_f2->x0 = sVar1;
    line_f4->x3 = sVar1;
    line_f4->x0 = sVar1;
    
    sVar1 = sVar3 + 102;
    sVar3 = sVar3 + 137;
    
    line_f4->x2 = sVar2;
    line_f4->x1 = sVar2;
    line_f2->y0 = sVar1;
    line_f4->y1 = sVar1;
    line_f4->y0 = sVar1;
    line_f2->y1 = sVar3;
    line_f4->y3 = sVar3;
    line_f4->y2 = sVar3;
    
    scope_act_helper_helper_80062320(ot, line_f4);
    scope_act_helper_helper_80062320(ot, line_f2);
}

#pragma INCLUDE_ASM("asm/Equip/scope_act_helper_80062C7C.s")        // 300 bytes


void scope_draw_text_80062DA8(Actor_scope *pActor)
{
    if ( (GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK4000000) == 0 )
    {
        menu_Text_XY_Flags_80038B34(20, 34, 0);
        menu_Color_80038B4C(127, 166, 97);
        menu_Text_80038C38(aZoomLevelD, 100 * (GM_Camera_800B77E8.field_20 / 320));
        menu_Color_80038B4C(101, 133, 77);
        menu_Text_XY_Flags_80038B34(32, 101, 1);
        menu_Text_80038C38(aD_44, -pActor->field_6C);
        menu_Text_Init_80038B98();
    }
}

extern int              DG_CurrentGroupID_800AB968;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern int              dword_8009F604;
extern int              GV_PauseLevel_800AB928;
extern GV_PAD           GV_PadData_800B05C0[4];
extern GM_Camera        GM_Camera_800B77E8;
extern DG_CHNL          DG_Chanls_800B1800[3];
extern const char       aGoggles_2[];

void scope_act_helper_8006258C(Actor_scope *pActor);
void scope_act_helper_800626D0(Actor_scope *pActor, unsigned short pad_status);
void scope_act_helper_80062998(Actor_scope *pActor, unsigned char *pOt, unsigned short pad_status);
void scope_act_helper_80062BDC(Actor_scope *pActor, unsigned char *pOt);
void scope_act_helper_80062C7C(Actor_scope *pActor, unsigned char *pOt);

static inline DG_CHNL *DG_CHANL(int idx)
{
    return &DG_Chanls_800B1800[idx];
}

void scope_act_80062E8C(Actor_scope *pActor)
{
    int            model;
    OBJECT        *parent_obj;
    OBJECT        *obj;
    unsigned char *pOt;
    unsigned short pad_status;
    DG_CHNL       *chnl;

    if ((pActor->field_9C_flags & 0x8000) == 0)
    {
        parent_obj = pActor->field_24_pParent;

        if (pActor->field_24_pParent->objs->n_models >= 7 && ((pActor->field_24_pParent->objs->flag & 0x80) != 0))
        {
            obj = &pActor->field_28_obj;
            model = GV_StrCode_80016CCC(aGoggles_2);

            GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)obj, model, 0x6d, 0);

            if ((pActor->field_28_obj).objs != (DG_OBJS *)0x0)
            {
                GM_ConfigObjectRoot_80034C5C(obj, parent_obj, 6);
                GM_ConfigObjectLight_80034C44(obj, parent_obj->light);
                EQ_InvisibleHead_80060D5C(parent_obj, &pActor->field_4C_saved_packs, &pActor->field_4E_saved_raise);
                pActor->field_9C_flags |= 0x8000;
            }
        }
    }


    if ((pActor->field_9C_flags & 0x8000) != 0)
    {
        GM_CurrentMap_800AB9B0 = pActor->field_20_ctrl->field_2C_map->field_0_map_index_bit;
        DG_GroupObjs(pActor->field_28_obj.objs, DG_CurrentGroupID_800AB968);

        if ((GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK4000000) != 0)
        {
            if ((pActor->field_24_pParent->objs->flag & 0x80) == 0)
            {
                DG_VisibleObjs(pActor->field_28_obj.objs);
            }
			
            GM_Camera_800B77E8.field_20 = 320;
            return;
        }

        DG_InvisibleObjs(pActor->field_28_obj.objs);
    }


    if (pActor->field_5C > 0)
    {
        if (GV_PauseLevel_800AB928 == 0)
        {
            pActor->field_5C--;
        }
        return;
    }


    if (dword_8009F604 != SGT_SCOPE)
    {
        NewSight_80071CDC(SGT_SCOPE, SGT_SCOPE, &GM_CurrentItemId, 1, 0);
        GM_Sound_80032968(0, 0x3f, 0x15);
    }


    if ((pActor->field_9C_flags & 3) != 3)
    {
        scope_act_helper_8006258C(pActor);
        return;
    }


    if ((GM_PlayerStatus_800ABA50 & PLAYER_STATUS_USING_CONTROLLER_PORT_2) != 0)
    {
        pActor->field_54_pOldPad = &GV_PadData_800B05C0[3];
    }
    else
    {
        pActor->field_54_pOldPad = &GV_PadData_800B05C0[2];
    }

    pad_status = pActor->field_54_pOldPad->status;
    GM_CheckShukanReverse_8004FBF8(&pad_status);

    if ((GV_PauseLevel_800AB928 != 0) || (GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK20000000) ||
        (GM_GameStatus_800AB3CC < 0))
    {
        pad_status = 0;
    }

    chnl = &DG_Chanls_800B1800[1];
    pOt = chnl[1].mOrderingTables[GV_Clock_800AB920]; // todo: fix when static inline DG_Chanl getter works.
    scope_act_helper_800626D0(pActor, pad_status);
    scope_act_helper_80062998(pActor, pOt, pad_status);
    scope_act_helper_80062BDC(pActor, pOt);
    scope_act_helper_80062C7C(pActor, pOt);
    scope_draw_text_80062DA8(pActor);
}


extern short scope_created_8009F2C4;

void scope_kill_8006317C(Actor_scope *pActor)
{
    void* field_74_alloc_0x100; // $a0
    void* v3; // $a0
    void* field_88_alloc; // $a0
    void* field_90_pPrims; // $a0

    field_74_alloc_0x100 = pActor->field_74_alloc_0x100;
    if ( field_74_alloc_0x100 )
    {
        GV_DelayedFree_80016254(field_74_alloc_0x100);
    }
    v3 = pActor->field_7C_pPrims[0];
    if ( v3 )
    {
        GV_DelayedFree_80016254(v3);
    }
    field_88_alloc = pActor->field_88_alloc;
    if ( field_88_alloc )
    {
        GV_DelayedFree_80016254(field_88_alloc);
    }
    field_90_pPrims = pActor->field_90_pPrims;
    if ( field_90_pPrims )
    {
        GV_DelayedFree_80016254(field_90_pPrims);
    }
    GM_Camera_800B77E8.field_20 = 320;
    if ( (pActor->field_9C_flags & 0x8000) != 0 )
    {
        EQ_VisibleHead_80060DF0(pActor->field_24_pParent, &pActor->field_4C_saved_packs, &pActor->field_4E_saved_raise);
        GM_FreeObject_80034BF8(&pActor->field_28_obj);
    }
    scope_created_8009F2C4 = 0;
}

void scope_loader_helper_80063238(LINE_F2 *lines)
{
	int i;

	for (i = 0; i < 16; i++)
	{
		*(int *)&lines->r0 = 0x41412e;
		setLineF2(lines);
		setSemiTrans(lines, 1);
		lines++;
	}
}

void scope_loader_helper_80063274(LINE_F4 *lines)
{
	int i;

	for (i = 0; i < 2; i++)
	{
		*(int *)&lines->r0 = 0x68b187;
		setLineF4(lines);
		lines++;

		*(int *)&lines->r0 = 0x68b187;
		setLineF2(lines);
		lines++;
	}
}

#pragma INCLUDE_ASM("asm/Equip/scope_loader_helper_800632D4.s")     // 148 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_loader_helper_80063368.s")     // 108 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_loader_800633D4.s")            // 308 bytes

extern const char aScopeC[];


void scope_act_80062E8C(Actor_scope *pActor);
void scope_kill_8006317C(Actor_scope *pActor);
int scope_loader_800633D4(Actor_scope *pActor, GM_Control *pCtrl, OBJECT *pObj);

Actor_scope* NewScope_80063508(GM_Control *a1, OBJECT *a2)
{
    Actor_scope *pActor; // $s0

    if ( scope_created_8009F2C4 )
    {
        return 0;
    }

    pActor = (Actor_scope *)GV_NewActor_800150E4(7, sizeof(Actor_scope));
    if ( pActor )
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_scope, (TActorFunction)scope_act_80062E8C, (TActorFunction)scope_kill_8006317C, aScopeC);
        if ( scope_loader_800633D4(pActor, a1, a2) < 0 )
        {
            GV_DestroyActor_800151C8(&pActor->field_0_scope);
            return 0;
        }
        scope_created_8009F2C4 = 1;
    }
    return pActor;
}
