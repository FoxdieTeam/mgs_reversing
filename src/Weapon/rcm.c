#include "rcm.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Game/map.h"
#include "libdg/libdg.h"
#include "psyq.h"
#include "Game/object.h"
#include "Bullet/rmissile.h"
#include "Game/linkvarbuf.h"

// nikita

extern int   GM_CurrentMap_800AB9B0;
extern short GM_Magazine_800AB9EC;
extern short GM_MagazineMax_800ABA2C;

extern SVECTOR GM_PlayerPosition_800ABA10;

extern int DG_CurrentGroupID_800AB968;

extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern int              GV_Clock_800AB920;

SVECTOR stru_800AB870 = {-100, -800, 80, 0};
RECT    rect_800AB878 = {100, 100, 200, 200};
SVECTOR svector_800AB880 = {-50, -300, 100, 0};

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

void rcm_act_helper_80066B58(RcmWork *work, int flags)
{
    int               curRgb; // $a2
    union Prim_Union *pPrim;  // $v0

    curRgb = work->field_60_rgb;
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
    work->field_60_rgb = curRgb;

    curRgb = curRgb - 64;

    if (curRgb < 0)
    {
        curRgb = 0;
    }
    pPrim = work->field_5C_pPrim->packs[GV_Clock_800AB920];
    pPrim->line_g2.r0 = curRgb;
    pPrim->line_g2.g0 = curRgb;
    pPrim->line_g2.b0 = curRgb;
}

void rcm_act_80066BC0(RcmWork *work)
{
    int    mapBit;         // $a1
    int    p_flags;        // $s0
    int    weapon_state_3; // $s2
    MATRIX mt1;
    MATRIX mt2;

    SVECTOR vec1; // [sp+50h] [-8h] BYREF

    mapBit = work->field_44_pCtrl->field_2C_map->field_0_map_index_bit;

    DG_GroupObjs(work->f20_obj.objs, DG_CurrentGroupID_800AB968);
    DG_GroupPrim(work->field_5C_pPrim, DG_CurrentGroupID_800AB968);

    GM_CurrentMap_800AB9B0 = mapBit;

    if ((work->field_48_pParent->objs->flag & DG_FLAG_INVISIBLE) || (GM_PlayerStatus_800ABA50 & PLAYER_CB_BOX))
    {
        DG_InvisibleObjs( work->f20_obj.objs );
        DG_InvisiblePrim( work->field_5C_pPrim );
    }
    else
    {
        DG_VisibleObjs( work->f20_obj.objs );
        DG_VisiblePrim( work->field_5C_pPrim );
    }

    p_flags = *work->field_50_pUnknown;
    rcm_act_helper_80066B58(work, p_flags);

    weapon_state_3 = GM_Weapons[WEAPON_NIKITA];
    if (!weapon_state_3 && (p_flags & 2))
    {
        GM_SeSet_80032858(&work->field_44_pCtrl->field_0_mov, 4);
        GM_SetNoise(5, 2, &work->field_44_pCtrl->field_0_mov);
        return;
    }

    if (weapon_state_3 > 0 && (p_flags & 2))
    {
        work->field_58_counter = 6;
        return;
    }

    if (work->field_58_counter)
    {
        work->field_58_counter--;
        if (work->field_58_counter < 2)
        {
            work->field_58_counter = 0;

            vec1.vx = -1024;
            vec1.vz = 0;
            vec1.vy = work->field_44_pCtrl->field_8_rot.vy;

            RotMatrixYXZ(&vec1, &mt1);
            DG_SetPos_8001BC44(&work->field_48_pParent->objs->objs[work->field_4C_obj_idx].world);
            DG_MovePos_8001BD20(&stru_800AB870);
            ReadRotMatrix(&mt2);

            mt2.t[1] = GM_PlayerPosition_800ABA10.vy + 320;

            mt1.t[0] = mt2.t[0];
            mt1.t[1] = mt2.t[1];
            mt1.t[2] = mt2.t[2];

            if (NewRMissile_8006D124(&mt1, work->field_54_whichSide))
            {
                GM_Weapons[WEAPON_NIKITA] = --weapon_state_3;
                GM_SeSet_80032858(&work->field_44_pCtrl->field_0_mov, 76);
                GM_SetNoise(100, 2, &work->field_44_pCtrl->field_0_mov);
            }
        }
    }
}

void rcm_kill_80066E68(RcmWork *work)
{
    DG_PRIM *prim;

    GM_FreeObject_80034BF8((OBJECT *)&work->f20_obj);
    prim = work->field_5C_pPrim;
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

int rcm_loader_80066EB0(RcmWork *actor, OBJECT *a2, int unit)
{
    DG_PRIM        *pNewPrim;
    DG_TEX         *pTexture;
    OBJECT_NO_ROTS *obj;

    obj = &actor->f20_obj;
    GM_InitObjectNoRots_800349B0(obj, GV_StrCode_80016CCC("nikita"), 109, 0);
    if (!obj->objs)
    {
        return -1;
    }

    GM_ConfigObjectRoot_80034C5C((OBJECT *)obj, a2, unit);

    pNewPrim = DG_GetPrim(1042, 1, 0, &svector_800AB880, &rect_800AB878);
    actor->field_5C_pPrim = pNewPrim;

    if (pNewPrim)
    {
        pTexture = DG_GetTexture_8001D830(GV_StrCode_80016CCC("rcm_l"));
        if (pTexture)
        {
            rcm_loader_helper_80066AF8(&pNewPrim->packs[0]->poly_ft4, pTexture);
            rcm_loader_helper_80066AF8(&pNewPrim->packs[1]->poly_ft4, pTexture);
            pNewPrim->root = &a2->objs->objs[unit].world;
            return 0;
        }
    }

    return -1;
}

GV_ACT *NewRCM_80066FF0(CONTROL *pCtrl, OBJECT *parent_obj, int num_parent, unsigned int *pFlags, int whichSide)
{
    RcmWork *rcm;
    int        iVar1;

    rcm = (RcmWork *)GV_NewActor_800150E4(6, sizeof(RcmWork));
    if (rcm != 0)
    {
        GV_SetNamedActor_8001514C(&rcm->field_0_actor, (TActorFunction)rcm_act_80066BC0,
                                  (TActorFunction)rcm_kill_80066E68, "rcm.c");
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
    GM_MagazineMax_800ABA2C = 0;
    GM_Magazine_800AB9EC = 0;
    return &rcm->field_0_actor;
}
