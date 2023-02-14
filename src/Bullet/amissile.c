#include "Anime/animeconv/anime.h"
#include "Game/camera.h"
#include "Game/object.h"
#include "Game/target.h"
#include "amissile.h"
#include "blast.h"
#include "libgcl/hash.h"

// stinger missile?

void amissile_loader_helper_8006D1F4(POLY_FT4 *pPoly, DG_TEX *pTex)
{
    int i;
    char rgb;
    int x, y, w, h;

    for (i = 0; i < 4; pPoly++, i++)
    {
        rgb = 128 - 32 * i;

        setPolyFT4(pPoly);
        setSemiTrans(pPoly, 1);
        setRGB0(pPoly, rgb, rgb, rgb);

        x = pTex->field_8_offx;
        w = pTex->field_A_width + 1;
        pPoly->u0 = pPoly->u2 = x + w / 2;
        pPoly->u1 = pPoly->u3 = x + w - 1;

        y = pTex->field_9_offy;
        h = pTex->field_B_height + 1;
        pPoly->v0 = pPoly->v1 = y + h / 2;
        pPoly->v2 = pPoly->v3 = y + h - 1;

        pPoly->tpage = pTex->field_4_tPage;
        pPoly->clut = pTex->field_6_clut;
    }
}

extern SVECTOR DG_ZeroVector_800AB39C;

void amissile_act_helper_8006D2A0(Actor_amissile *pActor, SVECTOR input)
{
    SVECTOR position = pActor->field_20_ctrl.field_0_position;
    SVECTOR result;
    SVECTOR rotation;

    SVECTOR *out = &pActor->field_140_svector_4Array[3];
    int i;

    GV_SubVec3_80016D40(&input, &position, &result);

    for (i = 0; i < 4; i++)
    {
        GV_AddVec3_80016D00(&result, out - 1, out);
        out--;
    }

    rotation = DG_ZeroVector_800AB39C;
    rotation.vy = 500;

    DG_RotVector_8001BE98(&rotation, &pActor->field_140_svector_4Array[0], 1);
}

extern SVECTOR    svector_8009F4A0;
extern SVECTOR    svector_8009F4A8;
extern SVECTOR    svector_8009F4B0;
extern GM_Target *target_800BDF00;

void amissile_act_helper_8006D37C(Actor_amissile *pActor)
{
    SVECTOR diff;
    SVECTOR result;
    SVECTOR *pTargetPos;
    int dir;
    int temp_v0;
    int temp_s1;

    if (pActor->field_120 < 5)
    {
        DG_RotVector_8001BE98(&svector_8009F4A8, &pActor->field_20_ctrl.field_44_movementVector, 1);
        return;
    }

    if (pActor->field_120 < 14)
    {
        DG_RotVector_8001BE98(&svector_8009F4B0, &pActor->field_20_ctrl.field_44_movementVector, 1);
        return;
    }

    if (--pActor->field_124 >= 0)
    {
        svector_8009F4A0.vz = 11;
    }
    else
    {
        svector_8009F4A0.vz = 0;
    }

    DG_RotVector_8001BE98(&svector_8009F4A0, &pActor->field_20_ctrl.field_44_movementVector, 1);

    if (!target_800BDF00)
    {
        return;
    }

    pTargetPos = &target_800BDF00->field_8_vec;
    diff.vx = pTargetPos->vx / 8 - pActor->field_20_ctrl.field_0_position.vx / 8;
    diff.vy = pTargetPos->vy / 8 - pActor->field_20_ctrl.field_0_position.vy / 8;
    diff.vz = pTargetPos->vz / 8 - pActor->field_20_ctrl.field_0_position.vz / 8;

    dir = GV_VecDir2_80016EF8(&diff);
    temp_v0 = GV_DiffDirS_8001704C(pActor->field_20_ctrl.field_4C_turn_vec.vy, dir);

    if (abs(temp_v0) > 1024)
    {
        return;
    }

    temp_s1 = 30 - pActor->field_120 / 3;

    if (abs(temp_v0) < temp_s1)
    {
        pActor->field_20_ctrl.field_4C_turn_vec.vy += temp_v0;
    }
    else if (temp_v0 > 0)
    {
        pActor->field_20_ctrl.field_4C_turn_vec.vy += temp_s1;
    }
    else
    {
        pActor->field_20_ctrl.field_4C_turn_vec.vy -= temp_s1;
    }

    result.vx = diff.vy;
    result.vz = SquareRoot0_80092708(diff.vx * diff.vx + diff.vz * diff.vz);

    dir = -GV_VecDir2_80016EF8(&result);
    temp_v0 = GV_DiffDirS_8001704C(pActor->field_20_ctrl.field_4C_turn_vec.vx, (dir - 1024) & 4095);

    if (abs(temp_v0) < temp_s1)
    {
        pActor->field_20_ctrl.field_4C_turn_vec.vx += temp_v0;
    }
    else if (temp_v0 > 0)
    {
        pActor->field_20_ctrl.field_4C_turn_vec.vx += temp_s1;
    }
    else
    {
        pActor->field_20_ctrl.field_4C_turn_vec.vx -= temp_s1;
    }
}

int amissile_act_helper_8006D600(void)
{
    return 0;
}

extern int              dword_8009F490;
extern SVECTOR          svector_8009F494;
extern int              dword_8009F49C;

extern Blast_Data       blast_data_8009F4F4;
extern Blast_Data       blast_data_8009F544;

extern int              GM_GameStatus_800AB3CC;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern UnkCameraStruct  gUnkCameraStruct_800B77B8;

void amissile_act_8006D608(Actor_amissile *pActor)
{
    MATRIX rotation;
    SVECTOR position;
    SVECTOR addition;

    GM_Control *pCtrl;
    int result;
    Blast_Data *pBlastData;

    pCtrl = &pActor->field_20_ctrl;
    position = pCtrl->field_0_position;

    GM_ActControl_80025A7C(pCtrl);
    amissile_act_helper_8006D37C(pActor);
    GM_ActObject2_80034B88(&pActor->field_9C_kmd);

    pActor->field_134_prim->world.t[0] = pActor->field_20_ctrl.field_0_position.vx;
    pActor->field_134_prim->world.t[1] = pActor->field_20_ctrl.field_0_position.vy;
    pActor->field_134_prim->world.t[2] = pActor->field_20_ctrl.field_0_position.vz;

    DG_GetLightMatrix2_8001A5D8(&pCtrl->field_0_position, pActor->field_C0_light_matrix);

    if (pActor->field_120 >= 15)
    {
        amissile_act_helper_8006D2A0(pActor, position);
    }

    dword_8009F490 = 1;
    svector_8009F494 = pCtrl->field_0_position;

    if (pActor->field_120 == 0)
    {
        DG_VisiblePrim(pActor->field_134_prim);
        ReadRotMatrix_80092DD8(&pActor->field_100_rotation_matrix);
        anime_create_8005DE70(&pActor->field_100_rotation_matrix);
        pActor->field_128 = 4;
    }

    if (pActor->field_120 == 14)
    {
        ReadRotMatrix_80092DD8(&pActor->field_100_rotation_matrix);
        anime_create_8005DE70(&pActor->field_100_rotation_matrix);
        GM_Sound_80032968(0, 63, 77);
        pActor->field_138_rect.x = pActor->field_138_rect.y = 1030;
        pActor->field_138_rect.w = pActor->field_138_rect.h = 2060;
        pActor->field_128 = 12;
        GM_ConfigControlHazard_8002622C(pCtrl, 100, 100, 100);
    }

    if (--pActor->field_128 > 0)
    {
        gUnkCameraStruct_800B77B8.field_0.vy += GV_RandS_800170BC(512) * pActor->field_128 / 8;

        if (pActor->field_120 >= 14)
        {
            pActor->field_138_rect.x = pActor->field_138_rect.y = pActor->field_138_rect.y - 65;
            pActor->field_138_rect.w = pActor->field_138_rect.h = pActor->field_138_rect.h - 130;
        }
    }

    // probably an inline
    pCtrl = &pActor->field_20_ctrl;
    GV_AddVec3_80016D00(&pCtrl->field_0_position, &pCtrl->field_44_movementVector, &addition);

    result = amissile_act_helper_8006D600();

    // this is probably also an inline
    if (pActor->field_20_ctrl.field_58 <= 0 && !pActor->field_20_ctrl.field_57)
    {
        if (++pActor->field_120 != 90 &&
            !GM_Target_8002E1B8(&pCtrl->field_0_position, &addition,
                                pActor->field_20_ctrl.field_2C_map->field_0_map_index_bit, &addition, 1) &&
                                !dword_8009F49C)
        {
            if (!result)
            {
                if (abs(pActor->field_20_ctrl.field_0_position.vx) <= 30000 &&
                    abs(pActor->field_20_ctrl.field_0_position.vy) <= 30000 &&
                    abs(pActor->field_20_ctrl.field_0_position.vz) <= 30000)
                {
                    return;
                }
            }
        }
    }

    if (!result)
    {
        ReadRotMatrix_80092DD8(&rotation);

        if (GM_GameStatus_800AB3CC & 0xd0000000 || GM_PlayerStatus_800ABA50 & 0x20000000)
        {
            pBlastData = &blast_data_8009F544;
        }
        else
        {
            pBlastData = &blast_data_8009F4F4;
        }

        NewBlast_8006DFDC(&rotation, pBlastData);
    }

    dword_8009F490 = 0;
    GV_DestroyActor_800151C8(&pActor->field_0_actor);
}

void amissile_kill_8006D99C(Actor_amissile *pActor)
{
    DG_OBJS *pPrim;

    GM_FreeControl_800260CC(&pActor->field_20_ctrl);
    GM_FreeObject_80034BF8(&pActor->field_9C_kmd);

    pPrim = (DG_OBJS *)pActor->field_134_prim;

    if (pPrim)
    {
        DG_DequeuePrim_800182E0(pPrim);
        DG_FreePrim_8001BC04(pPrim);
    }

    if (target_800BDF00)
    {
        target_800BDF00 = 0;
    }

    dword_8009F490 = 0;
}

extern MATRIX DG_ZeroMatrix_8009D430;

int amissile_loader_8006DA0C(Actor_amissile *pActor, MATRIX *pMtx, int arg2)
{
    GM_Control *pCtrl = &pActor->field_20_ctrl;
    OBJECT *pKmd;
    DG_OBJS *pObjs;
    RECT *pRect;
    DG_PRIM *pNewPrim;
    SVECTOR vector;
    int i;
    DG_TEX *pTex;

    if (Res_Control_init_loader_8002599C(pCtrl, 0, 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlMatrix_80026154(pCtrl, pMtx);
    GM_ConfigControlHazard_8002622C(pCtrl, 100, 50, 50);

    pKmd = &pActor->field_9C_kmd;

    pCtrl->field_55_flags |= 4;
    pCtrl->field_59 = 8;

    GM_InitObjectNoRots_800349B0((OBJECT_NO_ROTS *)pKmd, 0x76AB, 0x36D, 0);

    pObjs = pKmd->objs;

    if (!pObjs)
    {
        return -1;
    }

    pObjs->world = *pMtx;
    GM_ConfigObjectLight_80034C44(pKmd, pActor->field_C0_light_matrix);

    pKmd->objs->objs[0].raise = -500;

    pRect = &pActor->field_138_rect;
    pRect->x = pRect->y = 30;
    pRect->w = pRect->h = 60;

    pActor->field_134_prim = pNewPrim = DG_GetPrim(0x412, 4, 0, pActor->field_140_svector_4Array, pRect);

    if (!pNewPrim)
    {
        return -1;
    }

    DG_SetPos2_8001BC8C(&pCtrl->field_0_position, &pCtrl->field_8_rotator);

    vector.vz = 0;
    vector.vx = 0;
    vector.vy = 500;

    for (i = 0; i < 4; i++)
    {
        DG_RotVector_8001BE98(&vector, &pActor->field_140_svector_4Array[i], 1);
        vector.vy += 2000;
    }

    pTex = DG_GetTexture_8001D830(PCX_SOCOM_F);
    if (!pTex)
    {
        return -1;
    }

    amissile_loader_helper_8006D1F4(&pNewPrim->field_40_pBuffers[0]->poly_ft4, pTex);
    amissile_loader_helper_8006D1F4(&pNewPrim->field_40_pBuffers[1]->poly_ft4, pTex);

    pNewPrim->world = DG_ZeroMatrix_8009D430;
    DG_InvisiblePrim(pNewPrim);
    return 0;
}

extern const char aRmissileC[]; // = "amissile.c"

Actor_amissile * NewAMissile_8006DC50(MATRIX *pMtx, int arg2)
{
    Actor_amissile *pActor = (Actor_amissile *)GV_NewActor_800150E4(6, sizeof(Actor_amissile));

    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0_actor, (TActorFunction)&amissile_act_8006D608,
                                  (TActorFunction)&amissile_kill_8006D99C, aRmissileC);

        if (amissile_loader_8006DA0C(pActor, pMtx, arg2) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0_actor);
            return 0;
        }

        pActor->field_124 = 30;
        pActor->field_120 = 0;
        pActor->field_128 = 0;
        pActor->field_12C_svector = DG_ZeroVector_800AB39C;
    }

    return pActor;
}
