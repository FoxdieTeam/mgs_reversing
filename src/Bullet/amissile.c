#include "Anime/animeconv/anime.h"
#include "Game/camera.h"
#include "Game/object.h"
#include "Game/target.h"
#include "amissile.h"
#include "blast.h"
#include "libgcl/hash.h"
#include "SD/g_sound.h"

// stinger missile?

int amissile_alive_8009F490 = 0;
SVECTOR svector_8009F494 = {0, 0, 0, 0};
int dword_8009F49C = 0;
SVECTOR svector_8009F4A0 = {0, -800, 0, 0};
SVECTOR svector_8009F4A8 = {0, -350, 0, 0};
SVECTOR svector_8009F4B0 = {0, -100, -70, 0};

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

        x = pTex->off_x;
        w = pTex->w + 1;
        pPoly->u0 = pPoly->u2 = x + w / 2;
        pPoly->u1 = pPoly->u3 = x + w - 1;

        y = pTex->off_y;
        h = pTex->h + 1;
        pPoly->v0 = pPoly->v1 = y + h / 2;
        pPoly->v2 = pPoly->v3 = y + h - 1;

        pPoly->tpage = pTex->tpage;
        pPoly->clut = pTex->clut;
    }
}

extern SVECTOR DG_ZeroVector_800AB39C;

void amissile_act_helper_8006D2A0(AMissileWork *work, SVECTOR input)
{
    SVECTOR position = work->control.mov;
    SVECTOR result;
    SVECTOR rotation;

    SVECTOR *out = &work->field_140_svector_4Array[3];
    int i;

    GV_SubVec3(&input, &position, &result);

    for (i = 0; i < 4; i++)
    {
        GV_AddVec3(&result, out - 1, out);
        out--;
    }

    rotation = DG_ZeroVector_800AB39C;
    rotation.vy = 500;

    DG_RotVector_8001BE98(&rotation, &work->field_140_svector_4Array[0], 1);
}

extern TARGET *target_800BDF00;

void amissile_act_helper_8006D37C(AMissileWork *work)
{
    SVECTOR diff;
    SVECTOR result;
    SVECTOR *pTargetPos;
    int dir;
    int temp_v0;
    int temp_s1;

    if (work->field_120 < 5)
    {
        DG_RotVector_8001BE98(&svector_8009F4A8, &work->control.step, 1);
        return;
    }

    if (work->field_120 < 14)
    {
        DG_RotVector_8001BE98(&svector_8009F4B0, &work->control.step, 1);
        return;
    }

    if (--work->field_124 >= 0)
    {
        svector_8009F4A0.vz = 11;
    }
    else
    {
        svector_8009F4A0.vz = 0;
    }

    DG_RotVector_8001BE98(&svector_8009F4A0, &work->control.step, 1);

    if (!target_800BDF00)
    {
        return;
    }

    pTargetPos = &target_800BDF00->center;
    diff.vx = pTargetPos->vx / 8 - work->control.mov.vx / 8;
    diff.vy = pTargetPos->vy / 8 - work->control.mov.vy / 8;
    diff.vz = pTargetPos->vz / 8 - work->control.mov.vz / 8;

    dir = GV_VecDir2(&diff);
    temp_v0 = GV_DiffDirS(work->control.turn.vy, dir);

    if (abs(temp_v0) > 1024)
    {
        return;
    }

    temp_s1 = 30 - work->field_120 / 3;

    if (abs(temp_v0) < temp_s1)
    {
        work->control.turn.vy += temp_v0;
    }
    else if (temp_v0 > 0)
    {
        work->control.turn.vy += temp_s1;
    }
    else
    {
        work->control.turn.vy -= temp_s1;
    }

    result.vx = diff.vy;
    result.vz = SquareRoot0(diff.vx * diff.vx + diff.vz * diff.vz);

    dir = -GV_VecDir2(&result);
    temp_v0 = GV_DiffDirS(work->control.turn.vx, (dir - 1024) & 4095);

    if (abs(temp_v0) < temp_s1)
    {
        work->control.turn.vx += temp_v0;
    }
    else if (temp_v0 > 0)
    {
        work->control.turn.vx += temp_s1;
    }
    else
    {
        work->control.turn.vx -= temp_s1;
    }
}

int amissile_act_helper_8006D600(void)
{
#ifdef VR_EXE
    GV_MSG *msg;
    int     count;

    count = GV_ReceiveMessage(KMD_STINGER, &msg);
    if (count > 0)
    {
        for (count--; count >= 0; count--)
        {
            if (msg->message[0] == HASH_KILL)
            {
                return 1;
            }

            msg++;
        }
    }
#endif

    return 0;
}

extern Blast_Data       blast_data_8009F4B8[8];

extern int              GM_GameStatus_800AB3CC;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern UnkCameraStruct  gUnkCameraStruct_800B77B8;

void amissile_act_8006D608(AMissileWork *work)
{
    MATRIX rotation;
    SVECTOR position;
    SVECTOR addition;
#ifdef VR_EXE
    SVECTOR rotator;
#endif

    CONTROL *pCtrl;
    int result;
    Blast_Data *pBlastData;

    pCtrl = &work->control;
    position = pCtrl->mov;

    GM_ActControl_80025A7C(pCtrl);
    amissile_act_helper_8006D37C(work);
    GM_ActObject2_80034B88((OBJECT *)&work->field_9C_kmd);

    work->field_134_prim->world.t[0] = work->control.mov.vx;
    work->field_134_prim->world.t[1] = work->control.mov.vy;
    work->field_134_prim->world.t[2] = work->control.mov.vz;

    DG_GetLightMatrix2_8001A5D8(&pCtrl->mov, work->field_C0_light_matrix);

    if (work->field_120 >= 15)
    {
        amissile_act_helper_8006D2A0(work, position);
    }

    amissile_alive_8009F490 = 1;
    svector_8009F494 = pCtrl->mov;

    if (work->field_120 == 0)
    {
        DG_VisiblePrim(work->field_134_prim);
        ReadRotMatrix(&work->field_100_rotation_matrix);
        anime_create_8005DE70(&work->field_100_rotation_matrix);
        work->field_128 = 4;
    }

    if (work->field_120 == 14)
    {
        ReadRotMatrix(&work->field_100_rotation_matrix);
        anime_create_8005DE70(&work->field_100_rotation_matrix);
        GM_SeSet2_80032968(0, 63, SE_MISSILE_BOOST);
        work->field_138_rect.x = work->field_138_rect.y = 1030;
        work->field_138_rect.w = work->field_138_rect.h = 2060;
        work->field_128 = 12;
        GM_ConfigControlHazard_8002622C(pCtrl, 100, 100, 100);
    }

    if (--work->field_128 > 0)
    {
        gUnkCameraStruct_800B77B8.eye.vy += GV_RandS(512) * work->field_128 / 8;

        if (work->field_120 >= 14)
        {
            work->field_138_rect.x = work->field_138_rect.y = work->field_138_rect.y - 65;
            work->field_138_rect.w = work->field_138_rect.h = work->field_138_rect.h - 130;
        }
    }

    // probably an inline
    pCtrl = &work->control;
    GV_AddVec3(&pCtrl->mov, &pCtrl->step, &addition);

    result = amissile_act_helper_8006D600();

    // this is probably also an inline
    if (work->control.field_58 <= 0 && !work->control.field_57)
    {
        if (++work->field_120 != 90 &&
            !GM_Target_8002E1B8(&pCtrl->mov, &addition,
                                work->control.map->index, &addition, 1) &&
                                !dword_8009F49C)
        {
            if (!result)
            {
                if (abs(work->control.mov.vx) <= 30000 &&
                    abs(work->control.mov.vy) <= 30000 &&
                    abs(work->control.mov.vz) <= 30000)
                {
                    return;
                }
            }
        }
    }

#ifdef VR_EXE
    rotator = work->control.mov;

    if (rotator.vx > 30000)
    {
        rotator.vx = 30000;
    }
    else if (rotator.vx < -30000)
    {
        rotator.vx = -30000;
    }

    if (rotator.vy > 30000)
    {
        rotator.vy = 30000;
    }
    else if (rotator.vy < -30000)
    {
        rotator.vy = -30000;
    }

    if (rotator.vz > 30000)
    {
        rotator.vz = 30000;
    }
    else if (rotator.vz < -30000)
    {
        rotator.vz = -30000;
    }

    DG_SetPos2_8001BC8C(&rotator, &work->control.rot);
#endif

    if (!result)
    {
        ReadRotMatrix(&rotation);

        if (GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_29 | GAME_FLAG_BIT_31 | GAME_IN_DEMO) || GM_PlayerStatus_800ABA50 & PLAYER_PAD_OFF)
        {
            pBlastData = &blast_data_8009F4B8[7];
#ifdef VR_EXE
            if ((GM_GameStatus_800AB3CC & GAME_FLAG_BIT_31) && !(GM_PlayerStatus_800ABA50 & PLAYER_PAD_OFF) && !(GM_GameStatus_800AB3CC & GAME_FLAG_BIT_29))
            {
                pBlastData = &blast_data_8009F4B8[3];
            }
#endif
        }
        else
        {
            pBlastData = &blast_data_8009F4B8[3];
        }

        NewBlast_8006DFDC(&rotation, pBlastData);
    }

    amissile_alive_8009F490 = 0;
    GV_DestroyActor(&work->actor);
}

void amissile_kill_8006D99C(AMissileWork *work)
{
    DG_PRIM *pPrim;

    GM_FreeControl_800260CC(&work->control);
    GM_FreeObject_80034BF8((OBJECT *)&work->field_9C_kmd);

    pPrim = work->field_134_prim;

    if (pPrim)
    {
        DG_DequeuePrim_800182E0(pPrim);
        DG_FreePrim_8001BC04(pPrim);
    }

    if (target_800BDF00)
    {
        target_800BDF00 = 0;
    }

    amissile_alive_8009F490 = 0;
}

extern MATRIX DG_ZeroMatrix_8009D430;

int amissile_loader_8006DA0C(AMissileWork *work, MATRIX *pMtx, int side)
{
    CONTROL *pCtrl = &work->control;
    OBJECT_NO_ROTS *pKmd;
    DG_OBJS *pObjs;
    RECT *pRect;
    DG_PRIM *pNewPrim;
    SVECTOR vector;
    int i;
    DG_TEX *pTex;

    if (GM_InitControl_8002599C(pCtrl, 0, 0) < 0)
    {
        return -1;
    }

    GM_ConfigControlMatrix_80026154(pCtrl, pMtx);
    GM_ConfigControlHazard_8002622C(pCtrl, 100, 50, 50);

    pKmd = &work->field_9C_kmd;

    pCtrl->skip_flag |= CTRL_SKIP_NEAR_CHECK;
    pCtrl->field_59 = 8;

    GM_InitObjectNoRots_800349B0(pKmd, 0x76AB, 0x36D, 0);

    pObjs = pKmd->objs;

    if (!pObjs)
    {
        return -1;
    }

    pObjs->world = *pMtx;
    GM_ConfigObjectLight_80034C44((OBJECT *)pKmd, work->field_C0_light_matrix);

    pKmd->objs->objs[0].raise = -500;

    pRect = &work->field_138_rect;
    pRect->x = pRect->y = 30;
    pRect->w = pRect->h = 60;

    work->field_134_prim = pNewPrim = DG_GetPrim(0x412, 4, 0, work->field_140_svector_4Array, pRect);

    if (!pNewPrim)
    {
        return -1;
    }

    DG_SetPos2_8001BC8C(&pCtrl->mov, &pCtrl->rot);

    vector.vz = 0;
    vector.vx = 0;
    vector.vy = 500;

    for (i = 0; i < 4; i++)
    {
        DG_RotVector_8001BE98(&vector, &work->field_140_svector_4Array[i], 1);
        vector.vy += 2000;
    }

    pTex = DG_GetTexture_8001D830(PCX_SOCOM_F);
    if (!pTex)
    {
        return -1;
    }

    amissile_loader_helper_8006D1F4(&pNewPrim->packs[0]->poly_ft4, pTex);
    amissile_loader_helper_8006D1F4(&pNewPrim->packs[1]->poly_ft4, pTex);

    pNewPrim->world = DG_ZeroMatrix_8009D430;
    DG_InvisiblePrim(pNewPrim);
    return 0;
}

GV_ACT *NewAMissile_8006DC50(MATRIX *pMtx, int side)
{
    AMissileWork *work = (AMissileWork *)GV_NewActor(6, sizeof(AMissileWork));

    if (work)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)&amissile_act_8006D608,
                         (TActorFunction)&amissile_kill_8006D99C, "amissile.c");

        if (amissile_loader_8006DA0C(work, pMtx, side) < 0)
        {
            GV_DestroyActor(&work->actor);
            return 0;
        }

        work->field_124 = 30;
        work->field_120 = 0;
        work->field_128 = 0;
        work->field_12C_svector = DG_ZeroVector_800AB39C;
    }

    return &work->actor;
}
