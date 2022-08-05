#include "rcm.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "util/idaTypes.h"
#include "map/map.h"
#include "Script_tbl_map_8002BB44.h"
#include "libdg/libdg.h"
#include "psyq.h"
#include "Game/object.h"

// nikita

extern char       aNikita[];    // "nikita"
extern char       aRcmL_0[];    // "rcl_l"
extern int        aDd_800AB878; // TODO: convert to RECT
extern SVECTOR    dword_800AB880;
extern const char aRcmC[];
extern int        GM_CurrentMap_800AB9B0;
extern short      d_800AB9EC_mag_size;
extern short      dword_800ABA2C;

extern SVECTOR stru_800AB870;
extern SVECTOR stru_800ABA10;

extern int DG_CurrentGroupID_800AB968;

extern GameState_800B4D98 gGameState_800B4D98;
extern PlayerStatusFlag   GM_PlayerStatus_800ABA50;
extern int                GV_Clock_800AB920;

Actor *NewRMissile_8006D124(MATRIX *pMtx, int whichSide);

void rcm_loader_helper_80066AF8(POLY_FT4 *poly, DG_TEX *texture)
{
    u_char offx;
    u_char offy;
    u_char offx_width;
    u_char offy_height;

    setPolyFT4(poly);
    setSemiTrans(poly, 1);

    offx = texture->field_8_offx;
    offx_width = offx + texture->field_A_width;

    offy = texture->field_9_offy;
    offy_height = offy + texture->field_B_height;

    setUV4(poly, offx, offy, offx_width, offy, offx, offy_height, offx_width, offy_height);
    poly->tpage = texture->field_4_tPage;
    poly->clut = texture->field_6_clut;
}

void rcm_act_helper_80066B58(Actor_Rcm *pActor, int flags)
{
    int               curRgb; // $a2
    union Prim_Union *pPrim;  // $v0

    curRgb = pActor->field_60_rgb;
    if ((flags & 1) != 0)
    {
        if (curRgb <= 0)
        {
            curRgb = 256;
        }
        curRgb = curRgb - 8;
    }
    else
    {
        curRgb = 0;
    }
    pActor->field_60_rgb = curRgb;

    curRgb = curRgb - 64;

    if (curRgb < 0)
    {
        curRgb = 0;
    }
    pPrim = pActor->field_5C_pPrim->field_40_pBuffers[GV_Clock_800AB920];
    pPrim->line_g2.r0 = curRgb;
    pPrim->line_g2.g0 = curRgb;
    pPrim->line_g2.b0 = curRgb;
}

void rcm_act_80066BC0(Actor_Rcm *pActor)
{
    int    mapBit;         // $a1
    int    p_flags;        // $s0
    int    weapon_state_3; // $s2
    MATRIX mt1;
    MATRIX mt2;

    SVECTOR vec1; // [sp+50h] [-8h] BYREF

    mapBit = pActor->field_44_pCtrl->field_2C_map->field_0_map_index_bit;

    DG_SetObjectGroupId(pActor->f20_obj.objs, DG_CurrentGroupID_800AB968);
    DG_SetPrimGroupId(pActor->field_5C_pPrim, DG_CurrentGroupID_800AB968);

    GM_CurrentMap_800AB9B0 = mapBit;

    if ((pActor->field_48_pParent->objs->flag & 0x80) || (GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK1000))
    {
        pActor->f20_obj.objs->flag |= 0x80u;
        pActor->field_5C_pPrim->type |= 0x100u;
    }
    else
    {
        pActor->f20_obj.objs->flag &= ~0x80u;
        pActor->field_5C_pPrim->type &= ~0x100u;
    }

    p_flags = *pActor->field_50_pUnknown;
    rcm_act_helper_80066B58(pActor, p_flags);

    weapon_state_3 = gGameState_800B4D98.field_22_weapon_states[3];
    if (!weapon_state_3 && (p_flags & 2) != 0)
    {
        GM_SeSet_80032858(&pActor->field_44_pCtrl->field_0_position, 4);
        GM_SetNoise(5, 2, &pActor->field_44_pCtrl->field_0_position);
        return;
    }

    if (weapon_state_3 > 0 && (p_flags & 2) != 0)
    {
        pActor->field_58_counter = 6;
        return;
    }

    if (pActor->field_58_counter)
    {
        pActor->field_58_counter--;
        if (pActor->field_58_counter < 2)
        {
            pActor->field_58_counter = 0;

            vec1.vx = -1024;
            vec1.vz = 0;
            vec1.vy = pActor->field_44_pCtrl->field_8_vec.vy;

            RotMatrixYXZ_80093798(&vec1, &mt1);
            DG_SetPos_8001BC44(&pActor->field_48_pParent->objs->objs[pActor->field_4C_obj_idx].world);
            DG_MovePos_8001BD20(&stru_800AB870);
            ReadRotMatrix_80092DD8(&mt2);

            mt2.t[1] = stru_800ABA10.vy + 320;

            mt1.t[0] = mt2.t[0];
            mt1.t[1] = mt2.t[1];
            mt1.t[2] = mt2.t[2];

            if (NewRMissile_8006D124(&mt1, pActor->field_54_whichSide))
            {
                weapon_state_3--;
                gGameState_800B4D98.field_22_weapon_states[3] = weapon_state_3;
                GM_SeSet_80032858(&pActor->field_44_pCtrl->field_0_position, 76);
                GM_SetNoise(100, 2, &pActor->field_44_pCtrl->field_0_position);
            }
        }
    }
}

void rcm_kill_80066E68(Actor_Rcm *pActor)
{
    DG_PRIM *iVar1;

    GM_FreeObject_80034BF8(&pActor->f20_obj);
    iVar1 = pActor->field_5C_pPrim;
    if (iVar1 != 0)
    {
        DG_DequeuePrim_800182E0((DG_OBJS *)iVar1);
        DG_FreePrim_8001BC04((DG_OBJS *)iVar1);
    }
}

int rcm_loader_80066EB0(Actor_Rcm *actor, OBJECT *a2, int unit)
{
    DG_PRIM *pNewPrim;
    DG_TEX  *pTexture;
    OBJECT  *obj;
    int      new_var2;

    obj = &actor->f20_obj;
    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)obj, GV_StrCode_80016CCC(aNikita), 109, 0);
    if (!obj->objs)
    {
        return -1;
    }

    GM_ConfigObjectRoot_80034C5C(obj, a2, unit);

    pNewPrim = DG_MakePrim_8001BABC(1042, 1, 0, &dword_800AB880, (RECT *)&aDd_800AB878);
    if (pNewPrim)
    {
        DG_QueuePrim_80018274((DG_OBJS *)pNewPrim);
        new_var2 = GM_CurrentMap_800AB9B0;
        pNewPrim->group_id = new_var2;
    }

    actor->field_5C_pPrim = pNewPrim;
    if (pNewPrim)
    {
        pTexture = DG_FindTexture_8001D830(GV_StrCode_80016CCC(aRcmL_0));
        if (pTexture)
        {
            rcm_loader_helper_80066AF8(&pNewPrim->field_40_pBuffers[0]->poly_ft4, pTexture);
            rcm_loader_helper_80066AF8(&pNewPrim->field_40_pBuffers[1]->poly_ft4, pTexture);
            pNewPrim->root = &a2->objs->objs[unit].world;
            return 0;
        }
    }

    return -1;
}

Actor_Rcm *NewRCM_80066FF0(GM_Control *pCtrl, OBJECT *parent_obj, int num_parent, unsigned int *pFlags, int whichSide)
{
    Actor_Rcm *rcm;
    int        iVar1;

    rcm = (Actor_Rcm *)GV_NewActor_800150E4(6, sizeof(Actor_Rcm));
    if (rcm != 0)
    {
        GV_SetNamedActor_8001514C(&rcm->field_0_actor, (TActorFunction)rcm_act_80066BC0,
                                  (TActorFunction)rcm_kill_80066E68, aRcmC);
        iVar1 = rcm_loader_80066EB0(rcm, parent_obj, num_parent);

        if (iVar1 < 0)
        {
            GV_DestroyActor_800151C8(&rcm->field_0_actor);
            return 0;
        }

        rcm->field_44_pCtrl = pCtrl;
        rcm->field_48_pParent = parent_obj;
        rcm->field_4C_obj_idx = num_parent;
        rcm->field_50_pUnknown = pFlags;
        rcm->field_54_whichSide = whichSide;
        rcm->field_60_rgb = 0;
        rcm->field_58_counter = 0;
    }
    dword_800ABA2C = 0;
    d_800AB9EC_mag_size = 0;
    return rcm;
}
