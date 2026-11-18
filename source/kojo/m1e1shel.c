/******************************************************************************
 * included
 */

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"
#include "kojo/common.h"

/******************************************************************************
 */

extern void *NewM1E1Smoke(int arg0, SVECTOR *lpsvectPos, SVECTOR *lpsvectRot);

/******************************************************************************
 */
typedef struct tagSHELLACT
{
    GV_ACT   actor;
    CONTROL  control;
    OBJECT   body;
    MATRIX   light[2];
    TARGET   target;
    MATRIX   world;
    SVECTOR *lpsvectTarget;
    SVECTOR  svectPos;
    int      nVital;
    int      nMax;
    int      nSpeed;
    int     *lpnResult;
    int      nTime;
    int      nRange;
} SHELLACT, *PSHELLACT, *LPSHELLACT;

typedef struct tagLOCUSACT
{
    GV_ACT   actor;
    int      nMap;
    DG_PRIM *lpPrim;
    SVECTOR  verts[8];
    int      nTime;
    int      nR, nG, nB;
} LOCUSACT, *PLOCUSACT, *LPLOCUSACT;

typedef struct tagSMOKEACT
{
    GV_ACT   actor;
    int      nMap;
    SVECTOR  svectPos;
    SVECTOR  svectRot;
    int      nTime;
    TARGET   target;
} SMOKEACT, *PSMOKEACT, *LPSMOKEACT;

static void *NewShellLocus(LPSHELLACT lpParent);
static void *NewShellSmoke(SVECTOR *lpsvectPos, SVECTOR *lpsvectRot);

static void Act(LPSHELLACT lpAct);
static void Die(LPSHELLACT lpAct);

static void LocusAct(LPLOCUSACT lpAct);
static void LocusDie(LPLOCUSACT lpAct);
static void InitPacks(POLY_FT4 *lpPrim, DG_TEX *lpTex);

static void SmokeAct(LPSMOKEACT lpAct);
static void SmokeDie(LPSMOKEACT lpAct);

/******************************************************************************
 */
void *NewM1E1Shell(int nName, MATRIX *lpWorld, int nSide, SVECTOR *lpsvectTarget, int nVital, int nLength, int nSpeed, int *lpnResult)
{
    SVECTOR     svect1;
    SVECTOR     svect2;
    LPSHELLACT  lpAct;
    int         nDist;

    lpAct = GV_NewActor(GV_ACTOR_USER, sizeof(SHELLACT));
    if (lpAct == NULL) return NULL;

    lpAct->lpsvectTarget = lpsvectTarget;
    lpAct->nVital = nVital;
    lpAct->nSpeed = nSpeed;
    lpAct->lpnResult = lpnResult;
    lpAct->nMax = nLength / nSpeed;

    GV_SetNamedActor(lpAct, Act, Die, "m1e1shel.c");

    if (GM_InitControl(&lpAct->control, 0, 0) < 0)
    {
        GV_DestroyActor(lpAct);
        return NULL;
    }

    lpAct->world = *lpWorld;

    DG_SetPos(lpWorld);

    memset(&svect1, 0, sizeof(SVECTOR));
    svect2.vx = 0;
    svect2.vy = 0;
    svect2.vz = 100;

    DG_PutVector(&svect1, &svect1, 1);
    DG_PutVector(&svect2, &svect2, 1);

    svect2.vx -= svect1.vx;
    svect2.vy -= svect1.vy;
    svect2.vz -= svect1.vz;

    nDist = SquareRoot0(svect2.vx * svect2.vx + svect2.vz * svect2.vz);
    lpAct->control.rot.vx = -ratan2(svect2.vy, nDist);
    lpAct->control.rot.vy = ratan2(svect2.vx, svect2.vz);
    lpAct->control.rot.vz = 0;

    lpAct->control.turn = lpAct->control.rot;

    lpAct->control.mov.vx = lpWorld->t[0];
    lpAct->control.mov.vy = lpWorld->t[1];
    lpAct->control.mov.vz = lpWorld->t[2];

    GM_InitObject(&lpAct->body, nName, 0x36D, 0);
    GM_ConfigObjectLight(&lpAct->body, lpAct->light);

    svect1.vx = lpAct->body.objs->def->ux - lpAct->body.objs->def->lx;
    svect1.vy = lpAct->body.objs->def->uy - lpAct->body.objs->def->ly;
    svect1.vz = lpAct->body.objs->def->uz - lpAct->body.objs->def->lz;
    GM_ConfigControlHazard(&lpAct->control, svect1.vx, svect1.vy, svect1.vz);

    lpAct->nRange = __max(svect1.vx, svect1.vy);
    lpAct->nRange = __max(lpAct->nRange, svect1.vz);
    lpAct->nRange = __max(lpAct->nRange, lpAct->nSpeed) * 3 / 5;

    svect1.vx = lpAct->nRange;
    svect1.vy = lpAct->nRange;
    svect1.vz = lpAct->nRange;
    GM_SetTarget(&lpAct->target, TARGET_POWER, nSide, &svect1);

    svect1.vx = 0;
    svect1.vy = 0;
    svect1.vz = 0;
    DG_SetPos2(&svect1, &lpAct->control.rot);

    svect1.vx = 0;
    svect1.vy = 0;
    svect1.vz = lpAct->nSpeed / 10;
    DG_PutVector(&svect1, &svect1, 1);

    GM_SetPowerTarget(&lpAct->target, POWER_ONCE, -1, lpAct->nVital, 0, &svect1);

    return (void *)lpAct;
}

static void Act(LPSHELLACT lpAct)
{
    SVECTOR svect1;
    int     nPower;
    int     nDist;
    int     nTouch;

    nPower = 0;
    lpAct->svectPos = lpAct->control.mov;

    GM_ActControl(&lpAct->control);
    GM_ActObject2(&lpAct->body);
    DG_GetLightMatrix2(&lpAct->control.mov, lpAct->light);
    GM_MoveTarget(&lpAct->target, &lpAct->control.mov);

    lpAct->nTime++;

    if (lpAct->nTime < 2)
    {
        NewM1E1Smoke(0, &lpAct->control.mov, &lpAct->control.rot);
    }

    if (lpAct->lpsvectTarget == NULL)
    {
        DG_SetPos2(&lpAct->control.mov, &lpAct->control.rot);
        svect1.vx = 0;
        svect1.vy = 0;
        svect1.vz = lpAct->nSpeed;
        DG_RotVector(&svect1, &lpAct->control.step, 1);
    }
    else
    {
        svect1.vx = lpAct->lpsvectTarget->vx - lpAct->control.mov.vx;
        svect1.vy = lpAct->lpsvectTarget->vy - lpAct->control.mov.vy;
        svect1.vz = lpAct->lpsvectTarget->vz - lpAct->control.mov.vz;

        nDist = SquareRoot0(svect1.vx * svect1.vx + svect1.vy * svect1.vy + svect1.vz * svect1.vz);
        if (nDist == 0) nDist = 1;

        lpAct->control.step.vx = svect1.vx * lpAct->nSpeed / nDist;
        lpAct->control.step.vy = svect1.vy * lpAct->nSpeed / nDist;
        lpAct->control.step.vz = svect1.vz * lpAct->nSpeed / nDist;
        lpAct->control.turn.vx = -ratan2(svect1.vy, SquareRoot0(svect1.vx * svect1.vx + svect1.vz * svect1.vz));
        lpAct->control.turn.vy = ratan2(svect1.vx, svect1.vz);
        lpAct->control.turn.vz = 0;
    }

    nTouch = lpAct->control.n_touches;

    if (nTouch > 0)
    {
        nTouch = GM_CheckControlTouches(&lpAct->control, lpAct->nRange);
    }

    if (nTouch > 0 ||
        (nPower = GM_PowerTarget(&lpAct->target)) != 0 ||
        lpAct->nTime >= lpAct->nMax ||
        lpAct->control.mov.vx < -27000 || lpAct->control.mov.vx > 27000 ||
        lpAct->control.mov.vy < -27000 || lpAct->control.mov.vy > 27000 ||
        lpAct->control.mov.vz < -27000 || lpAct->control.mov.vz > 27000)
    {
        if (nPower != 0) *lpAct->lpnResult = 1;
        else if (nTouch > 0) *lpAct->lpnResult = 2;
        else *lpAct->lpnResult = 3;

        GM_SeSetPan(&lpAct->control.mov, 183, 63);
        NewShellSmoke(&lpAct->control.mov, &lpAct->control.rot);
        GV_DestroyActor(lpAct);
    }
    else
    {
        NewShellLocus(lpAct);
    }
}

static void Die(LPSHELLACT lpAct)
{
    GM_FreeControl(&lpAct->control);
    GM_FreeObject(&lpAct->body);
}

/******************************************************************************
 */
static void *NewShellLocus(LPSHELLACT lpParent)
{
    SVECTOR     svect1;
    SVECTOR     svect2;
    LPLOCUSACT  lpAct;
    DG_TEX     *lpTex;

    lpAct = GV_NewActor(GV_ACTOR_USER, sizeof(LOCUSACT));
    if (lpAct == NULL) return NULL;

    GV_SetNamedActor(lpAct, LocusAct, LocusDie, "m1e1shel.c");

    lpAct->nR = 255;
    lpAct->nG = 224;
    lpAct->nB = 192;
    lpAct->nMap = GM_CurrentMap;

    lpAct->lpPrim = GM_MakePrim(DG_PRIM_POLY_FT4, 2, lpAct->verts, NULL);
    lpTex = DG_GetTexture(GV_StrCode("none"));

    InitPacks((POLY_FT4 *)lpAct->lpPrim->packs[0], lpTex);
    InitPacks((POLY_FT4 *)lpAct->lpPrim->packs[1], lpTex);
    DG_RaisePrim(lpAct->lpPrim, 1000);

    svect1.vx = lpParent->body.objs->def->lx - lpParent->body.objs->def->ux;
    svect1.vy = lpParent->body.objs->def->ly - lpParent->body.objs->def->uy;
    svect1.vz = 0;

    svect2.vx = -svect1.vx;
    svect2.vz = 0;
    svect2.vy = -svect1.vy;

    DG_SetPos2(&DG_ZeroVector, &lpParent->control.rot);
    DG_PutVector(&svect1, &svect1, 1);
    DG_PutVector(&svect2, &svect2, 1);

    lpAct->verts[0].vx = lpParent->svectPos.vx;
    lpAct->verts[0].vy = lpParent->svectPos.vy + svect2.vy;
    lpAct->verts[0].vz = lpParent->svectPos.vz;
    lpAct->verts[1].vx = lpParent->svectPos.vx;
    lpAct->verts[1].vy = lpParent->svectPos.vy + svect1.vy;
    lpAct->verts[1].vz = lpParent->svectPos.vz;
    lpAct->verts[4].vx = lpParent->svectPos.vx + svect2.vx;
    lpAct->verts[4].vy = lpParent->svectPos.vy;
    lpAct->verts[4].vz = lpParent->svectPos.vz;
    lpAct->verts[5].vx = lpParent->svectPos.vx + svect1.vx;
    lpAct->verts[5].vy = lpParent->svectPos.vy;
    lpAct->verts[5].vz = lpParent->svectPos.vz;

    lpAct->verts[2].vx = lpParent->control.mov.vx;
    lpAct->verts[2].vy = lpParent->control.mov.vy + svect2.vy;
    lpAct->verts[2].vz = lpParent->control.mov.vz;
    lpAct->verts[3].vx = lpParent->control.mov.vx;
    lpAct->verts[3].vy = lpParent->control.mov.vy + svect1.vy;
    lpAct->verts[3].vz = lpParent->control.mov.vz;
    lpAct->verts[6].vx = lpParent->control.mov.vx + svect2.vx;
    lpAct->verts[6].vy = lpParent->control.mov.vy;
    lpAct->verts[6].vz = lpParent->control.mov.vz;
    lpAct->verts[7].vx = lpParent->control.mov.vx + svect1.vx;
    lpAct->verts[7].vy = lpParent->control.mov.vy;
    lpAct->verts[7].vz = lpParent->control.mov.vz;

    setRGB0((POLY_FT4 *)lpAct->lpPrim->packs[0], lpAct->nR, lpAct->nG, lpAct->nB);
    setRGB0((POLY_FT4 *)lpAct->lpPrim->packs[0] + 1, lpAct->nR, lpAct->nG, lpAct->nB);

    setRGB0((POLY_FT4 *)lpAct->lpPrim->packs[1], lpAct->nR, lpAct->nG, lpAct->nB);
    setRGB0((POLY_FT4 *)lpAct->lpPrim->packs[1] + 1, lpAct->nR, lpAct->nG, lpAct->nB);

    return (void *)lpAct;
}

static void LocusAct(LPLOCUSACT lpAct)
{
    GM_SetCurrentMap(lpAct->nMap);
    lpAct->nTime++;

    lpAct->nR -= 25;
    if (lpAct->nR < 0) lpAct->nR = 0;
    lpAct->nG -= 22;
    if (lpAct->nG < 0) lpAct->nG = 0;
    lpAct->nB -= 19;
    if (lpAct->nB < 0) lpAct->nB = 0;

    setRGB0((POLY_FT4 *)lpAct->lpPrim->packs[0], lpAct->nR, lpAct->nG, lpAct->nB);
    setRGB0((POLY_FT4 *)lpAct->lpPrim->packs[0] + 1, lpAct->nR, lpAct->nG, lpAct->nB);
    setRGB0((POLY_FT4 *)lpAct->lpPrim->packs[1], lpAct->nR, lpAct->nG, lpAct->nB);
    setRGB0((POLY_FT4 *)lpAct->lpPrim->packs[1] + 1, lpAct->nR, lpAct->nG, lpAct->nB);

    if (lpAct->nTime >= 11)
    {
        GV_DestroyActor(lpAct);
    }
}

static void LocusDie(LPLOCUSACT lpAct)
{
    GM_FreePrim(lpAct->lpPrim);
}

static void InitPacks(POLY_FT4 *lpPrim, DG_TEX *lpTex)
{
    int i;

    for (i = 0; i < 2; i++, lpPrim++)
    {
        setPolyFT4(lpPrim);
        DG_SetPacketTexture4(lpPrim, lpTex);
        setSemiTrans(lpPrim, 1);
        lpPrim->tpage |= (3 << 5);
    }
}

/******************************************************************************
 */
static void *NewShellSmoke(SVECTOR *lpsvectPos, SVECTOR *lpsvectRot)
{
    SVECTOR     svect1;
    SVECTOR     svect2;
    LPSMOKEACT  lpAct;

    memset(&svect1, 0x00, sizeof(SVECTOR));

    lpAct = GV_NewActor(GV_ACTOR_USER, sizeof(SMOKEACT));
    if (lpAct == NULL) return NULL;

    GV_SetNamedActor(lpAct, SmokeAct, SmokeDie, "m1e1shel.c");

    lpAct->nTime = 0;
    lpAct->nMap = GM_CurrentMap;
    lpAct->svectPos = *lpsvectPos;
    lpAct->svectRot = *lpsvectRot;

    setVector(&svect2, 1000, 1000, 1000);
    svect1.vx = 100;
    GM_SetTarget(&lpAct->target, TARGET_POWER, NO_SIDE, &svect2);
    GM_SetPowerTarget(&lpAct->target, POWER_CONST | POWER_EXPLODE, 2, 5, 2, &svect1);
    GM_MoveTarget(&lpAct->target, &lpAct->svectPos);
    GM_PowerTarget(&lpAct->target);

    setVector(&svect2, 2000, 2000, 2000);
    svect1.vx = 50;
    GM_SetTarget(&lpAct->target, TARGET_POWER, NO_SIDE, &svect2);
    GM_SetPowerTarget(&lpAct->target, POWER_CONST | POWER_EXPLODE, 2, 1, 3, &svect1);
    GM_MoveTarget(&lpAct->target, &lpAct->svectPos);
    GM_PowerTarget(&lpAct->target);

    sub_800790E8();
    return (void *)lpAct;
}

static void SmokeAct(LPSMOKEACT lpAct)
{
    GM_SetCurrentMap(lpAct->nMap);
    lpAct->nTime++;

    if (lpAct->nTime == 1)
    {
        NewM1E1Smoke(1, &lpAct->svectPos, &lpAct->svectRot);
    }
    else if (lpAct->nTime == 2)
    {
        sub_8007913C();
    }
    else if (lpAct->nTime >= 30)
    {
        GV_DestroyActor(lpAct);
    }
}

static void SmokeDie(LPSMOKEACT lpAct)
{
    /* do nothing */
}
