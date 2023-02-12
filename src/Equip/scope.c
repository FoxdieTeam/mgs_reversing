#include "scope.h"
#include "Menu/menuman.h"
#include "Game/camera.h"
#include "Game/object.h"
#include "Thing/sight.h"
#include "chara/snake/sna_init.h"

extern const char aZoomLevelD[];
extern const char aD_44[];  // = "%d"

extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern GM_Camera GM_Camera_800B77E8;

void scope_act_helper_helper_80062320(int *a1, int *a2)
{
    if ((GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK4000000) == 0)
    {
        addPrim(a1, a2);
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

#pragma INCLUDE_ASM("asm/Equip/scope_act_helper_800624BC.s")        // 56 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_act_helper_helper_800624F4.s") // 152 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_act_helper_8006258C.s")        // 324 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_act_helper_800626D0.s")        // 712 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_act_helper_80062998.s")        // 580 bytes
#pragma INCLUDE_ASM("asm/Equip/scope_act_helper_80062BDC.s")        // 160 bytes
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
extern short gGameState_800B4D98[0x60];
extern int              dword_8009F604;
extern int              GV_PauseLevel_800AB928;
extern int              GV_Clock_800AB920;
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

// https://github.com/FoxdieTeam/mgs_reversing



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


    if (dword_8009F604 != 0x51c8)
    {
        NewSight_80071CDC(0x51c8, 0x51c8, &gGameState_800B4D98[15], 1, 0);
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

#pragma INCLUDE_ASM("asm/Equip/scope_kill_8006317C.s")              // 188 bytes

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

extern short scope_created_8009F2C4;

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
