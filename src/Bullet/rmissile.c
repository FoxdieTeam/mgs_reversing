#include "Equip/Takabe.h"
#include "Game/object.h"
#include "map/hzd.h"
#include "psyq.h"
#include "rmissile.h"

// nikita missile

extern int             GM_CameraTrackSave_800AB42C;
extern SVECTOR         GM_CameraRotateSave_800AB430;
extern int             GM_event_camera_flag_800ABA9C;
extern GM_Camera       GM_Camera_800B77E8;
extern UnkCameraStruct gUnkCameraStruct_800B77B8;
extern CAMERA          GM_CameraList_800B7718[8];

void rmissile_loader_helper4_8006B800(Actor_rmissile *pActor)
{
    GV_CopyMemory_800160D8(&GM_Camera_800B77E8,           &pActor->field_17C_camera,  sizeof(pActor->field_17C_camera));
    GV_CopyMemory_800160D8(&gUnkCameraStruct_800B77B8,    &pActor->field_1F8,         sizeof(pActor->field_1F8));
    GV_CopyMemory_800160D8(GM_CameraList_800B7718,        &pActor->field_228_camera,  sizeof(pActor->field_228_camera));
    GV_CopyMemory_800160D8(&GM_CameraRotateSave_800AB430, &pActor->field_2CC_svector, sizeof(pActor->field_2CC_svector));

    pActor->field_2C8 = GM_CameraTrackSave_800AB42C;
    pActor->field_2D4 = GM_event_camera_flag_800ABA9C;
}

void rmissile_8006B888(Actor_rmissile *pActor)
{
    GV_CopyMemory_800160D8(&pActor->field_17C_camera,  &GM_Camera_800B77E8,           sizeof(pActor->field_17C_camera));
    GV_CopyMemory_800160D8(&pActor->field_1F8,         &gUnkCameraStruct_800B77B8,    sizeof(pActor->field_1F8));
    GV_CopyMemory_800160D8(&pActor->field_228_camera,  &GM_CameraList_800B7718,       sizeof(pActor->field_228_camera));
    GV_CopyMemory_800160D8(&pActor->field_2CC_svector, &GM_CameraRotateSave_800AB430, sizeof(pActor->field_2CC_svector));

    GM_CameraTrackSave_800AB42C = pActor->field_2C8;
    GM_event_camera_flag_800ABA9C = pActor->field_2D4;

    sub_800309B4(2, 30);
    GM_CameraEventReset_800309A8();
}

extern int GM_GameStatus_800AB3CC;
extern GM_Control *gSnaControl_800AB9F4;

void rmissile_8006B924(Actor_rmissile *pActor)
{
    GM_Control *ctrl;

    ctrl = &pActor->field_20_ctrl;
    ctrl->field_55_flags |= CONTROL_FLAG_UNK2;

    rmissile_8006B888(pActor);
    GM_GameStatus_800AB3CC &= ~0x40;
    sub_8002A258(ctrl->field_2C_map->field_8_hzd, &ctrl->field_10_pStruct_hzd_unknown);

    ctrl = gSnaControl_800AB9F4;

    if (ctrl)
    {
        HZD_ReExecEvent_8002A1F4(ctrl->field_2C_map->field_8_hzd, &ctrl->field_10_pStruct_hzd_unknown, 0x102);
    }
}

#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_helper_8006B9B0.s")    // 192 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_helper_8006BA70.s")    // 160 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_helper_8006BB10.s")    // 532 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_8006BD24.s")           // 300 bytes

extern PlayerStatusFlag GM_PlayerStatus_800ABA50;

void rmissile_act_helper_8006BE50(Actor_rmissile *pActor, int arg1)
{
    if (GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK20000000)
    {
        return;
    }

    if (arg1 >= 0 && pActor->field_20_ctrl.field_4C_turn_vec.vy != arg1)
    {
        pActor->field_111 = 30;
        pActor->field_20_ctrl.field_4C_turn_vec.vy = arg1;
    }
}

void rmissile_act_helper_8006BE90(Actor_rmissile *pActor, int arg1)
{
    if (GM_PlayerStatus_800ABA50 & PLAYER_STATUS_UNK20000000)
    {
        return;
    }

    if (arg1 & 0x8000)
    {
        pActor->field_111 = 30;
        pActor->field_20_ctrl.field_4C_turn_vec.vy += 64;
        pActor->field_20_ctrl.field_4C_turn_vec.vy &= 0xFFF;
    }

    if (arg1 & 0x2000)
    {
        pActor->field_111 = 30;
        pActor->field_20_ctrl.field_4C_turn_vec.vy -= 64;
        pActor->field_20_ctrl.field_4C_turn_vec.vy &= 0xFFF;
    }
}

#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_8006BEEC.s")           // 232 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_8006BFD4.s")           // 208 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_helper_8006C0A4.s")    // 112 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_8006C114.s")           // 616 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_helper_8006C37C.s")           // 584 bytes
#pragma INCLUDE_ASM("asm/Bullet/rmissile_act_8006C5C4.s")                  // 1404 bytes

extern int   dword_8009F46C;
extern int   dword_8009F470;
extern short Nik_Blast_8009F484;

void rmissile_kill_8006CB40(Actor_rmissile *pActor)
{
    DG_PRIM *prim;

    GM_FreeControl_800260CC(&pActor->field_20_ctrl);
    GM_FreeObject_80034BF8(&pActor->field_9C_kmd);

    if (pActor->field_174_polys_2Array[0])
    {
        GV_DelayedFree_80016254(pActor->field_174_polys_2Array[0]);
        dword_8009F46C = 0;
    }
    else
    {
        dword_8009F46C = 0;
    }

    dword_8009F470 = 0;
    Nik_Blast_8009F484 = 0;

    prim = pActor->field_2D8_prim;

    if (prim)
    {
        DG_DequeuePrim_800182E0((DG_OBJS *)prim);
        DG_FreePrim_8001BC04((DG_OBJS *)prim);
    }

    if (!pActor->field_117)
    {
        rmissile_8006B924(pActor);
    }
}

extern SVECTOR svector_8009F488;
extern SVECTOR DG_ZeroVector_800AB39C;

int rmissile_loader_helper3_8006CBD8(Actor_rmissile *pActor, int whichSide)
{
    GM_Target *target = &pActor->field_120_target;

    GM_SetTarget_8002DC74(target, 0x4, whichSide, &svector_8009F488);
    GM_Target_8002DCCC(target, 0, -1, 1, 0, &DG_ZeroVector_800AB39C);
    GM_Target_SetVector_8002D500(target, &pActor->field_20_ctrl.field_0_position);
    return 0;
}

int rmissile_loader_helper2_8006CC50(Actor_rmissile *pActor)
{
    POLY_F4 *poly;
    POLY_F4 *poly2;

    pActor->field_174_polys_2Array[0] = poly = GV_Malloc_8001620C(sizeof(POLY_F4) * 2);

    if (!poly)
    {
        return -1;
    }

    pActor->field_174_polys_2Array[1] = poly + 1;

    LSTORE(0x8AB89E, &poly[0].r0);
    LSTORE(0x8AB89E, &poly[1].r0);

    poly2 = poly + 1;

    SetPolyF4_80092488(poly);
    SetPolyF4_80092488(poly2);
    SetSemiTrans_80092458(poly, 1);
    SetSemiTrans_80092458(poly2, 1);

    poly2->x2 = 31;
    poly2->x0 = 31;
    poly->x2 = 31;
    poly->x0 = 31;
    poly2->y1 = 39;
    poly2->y0 = 39;
    poly->y1 = 39;
    poly->y0 = 39;
    poly2->y3 = 49;
    poly2->y2 = 49;
    poly->y3 = 49;
    poly->y2 = 49;

    return 0;
}

static inline void rmissile_loader_helper_helper_8006CD1C_set_poly(POLY_FT4 *pPoly, DG_TEX *pTex)
{
    int u, v, w, h;

    setPolyFT4(pPoly);
    setSemiTrans(pPoly, 1);

    u = pTex->field_8_offx;
    w = (pTex->field_A_width + 1) / 2;
    pPoly->u2 = u;
    pPoly->u0 = u;
    u += w;
    pPoly->u3 = u - 1;
    pPoly->u1 = u - 1;

    v = pTex->field_9_offy;
    h = (pTex->field_B_height + 1) / 2;
    pPoly->v1 = v;
    pPoly->v0 = v;
    v += h;
    pPoly->v3 = v - 1;
    pPoly->v2 = v - 1;

    pPoly->tpage = pTex->field_4_tPage;
    pPoly->clut = pTex->field_6_clut;
}

void rmissile_loader_helper_helper_8006CD1C(POLY_FT4 *pPoly, DG_TEX *pTex, int primCount)
{
    rmissile_loader_helper_helper_8006CD1C_set_poly(pPoly, pTex);
    pPoly->tpage = (pPoly->tpage & 0xff9f) | 0x20;

    pPoly->r0 = 0;
    pPoly->g0 = 0;
    pPoly->b0 = 0;

    pPoly++;
    primCount--;

    while (primCount-- != 0)
    {
        rmissile_loader_helper_helper_8006CD1C_set_poly(pPoly, pTex);
        pPoly->tpage = pPoly->tpage | 0x60;

        pPoly->r0 = 0;
        pPoly->g0 = 0;
        pPoly->b0 = 0;

        pPoly++;
    }
}

extern const char aSocomF[]; // = "socom_f"

extern MATRIX DG_ZeroMatrix_8009D430;

void rmissile_loader_helper_8006CE54(Actor_rmissile *pActor)
{
    int hash;
    DG_TEX *tex;
    SVECTOR *vec;
    DG_PRIM *prim;
    int count;

    hash = GV_StrCode_80016CCC(aSocomF);
    tex = DG_GetTexture_8001D830(hash);

    pActor->field_2DC_tex = tex;
    prim = pActor->field_2D8_prim  = Takabe_MakeIndividualRect3DPrim_800793E8(8, &pActor->field_2E4_svector);

    rmissile_loader_helper_helper_8006CD1C(&prim->field_40_pBuffers[0]->poly_ft4, tex, 8);
    rmissile_loader_helper_helper_8006CD1C(&prim->field_40_pBuffers[1]->poly_ft4, tex, 8);

    prim->world = DG_ZeroMatrix_8009D430;
    prim->field_2E_k500 = 100;

    vec = &pActor->field_2E4_svector;

    for (count = 8; count > 0; count--)
    {
        (vec++)->pad = 0;
    }
}

extern SVECTOR svector_8009F478;
extern SVECTOR svector_800ABA10;

static inline int rmissile_loader_8006CF44_get_field_59(void)
{
    return 8;
}

int rmissile_loader_8006CF44(Actor_rmissile *pActor, MATRIX *pMtx, int whichSide)
{
    GM_Control *ctrl;
    OBJECT *kmd;

    dword_8009F46C = 1;
    dword_8009F470 = 1;

    rmissile_loader_helper4_8006B800(pActor);

    ctrl = &pActor->field_20_ctrl;

    if (Res_Control_init_loader_8002599C(ctrl, 0x50AE, 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlMatrix_80026154(ctrl, pMtx);

    pActor->field_100_svector = ctrl->field_0_position;
    pActor->field_110 = 8;
    ctrl->field_0_position = svector_800ABA10;
    pActor->field_108_svector = svector_800ABA10;
    svector_8009F478 = svector_800ABA10;

    GM_ConfigControlHazard_8002622C(ctrl, 400, 0xC8, 0xC8);
    ctrl->field_59 = rmissile_loader_8006CF44_get_field_59();
    GM_ConfigControlTrapCheck_80026308(ctrl);

    kmd = &pActor->field_9C_kmd;
    ctrl->field_4C_turn_vec.vz = 0;
    ctrl->field_8_rotator.vz = 0;
    ctrl->field_55_flags |= 4;

    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)kmd, 0x9A90, 0x36D, 0);

    if (!kmd->objs)
    {
        return -1;
    }

    GM_ConfigObjectLight_80034C44(kmd, &pActor->field_C0_matrix);

    if (rmissile_loader_helper3_8006CBD8(pActor, whichSide) < 0)
    {
        return -1;
    }

    if (rmissile_loader_helper2_8006CC50(pActor) < 0)
    {
        return -1;
    }

    pActor->field_9C_kmd.objs->flag |= 0x80;
    pActor->field_11C = -1;
    pActor->field_324 = 10;
    rmissile_loader_helper_8006CE54(pActor);
    return 0;
}

extern int dword_8009F480;

extern const char rRmissileC[]; // = "rmissile.c"

Actor_rmissile * NewRMissile_8006D124(MATRIX *pMtx, int whichSide)
{
    Actor_rmissile *actor;

    actor = (Actor_rmissile *)GV_NewActor_800150E4(6, sizeof(Actor_rmissile));

    if (actor)
    {
        GV_SetNamedActor_8001514C(&actor->field_0_actor, (TActorFunction)&rmissile_act_8006C5C4,
                                  (TActorFunction)&rmissile_kill_8006CB40, rRmissileC);

        if (rmissile_loader_8006CF44(actor, pMtx, whichSide) < 0)
        {
            GV_DestroyActor_800151C8(&actor->field_0_actor);
            return 0;
        }

        actor->field_111 = 30;
        actor->field_112 = 0;
        actor->field_113 = 0;
        actor->field_117 = 0;
        actor->field_114 = 0;
        actor->field_115 = 0;
        actor->field_116 = 0;
        dword_8009F480 = 0;
        actor->field_118 = 0;
        actor->field_11A = 0;
        actor->field_11C = 0;
        actor->field_168 = 0;
        Nik_Blast_8009F484 = 0;
    }

    return actor;
}
