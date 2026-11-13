/******************************************************************************
 * System   : METALGEAR^3 for PlayStation
 * Computer : PlayStation
 * OS       : PlayStation
 * Compiler : psyq
 * Module   : 
 */

/******************************************************************************
 * included
 */

#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"

/******************************************************************************
 * definitions and typedefs and structures
 */

typedef struct tagBLOODDRIP {
    GV_ACT   actor;
    int      nMap;
    DG_PRIM* lpPrim;
    SVECTOR  verts[4];
    SVECTOR  svectPos;
    int      nSize;
    int      nAccel;
    int      nSpeed;
} BLOODDRIP, *PBLOODDRIP, *LPBLOODDRIP;

#define KETCHAP GV_StrCode("ketchap")

#define PACK0   (((POLY_FT4 *)lpAct->lpPrim->packs[0]) + 0)
#define PACK1   (((POLY_FT4 *)lpAct->lpPrim->packs[0]) + 1)

/******************************************************************************
 * functions
 */

static void Act(LPBLOODDRIP lpAct);
static void Die(LPBLOODDRIP lpAct);

/******************************************************************************
 * publics
 */

void* NewBloodDrip(
    SVECTOR* lpsvectPos,
    int      nSize,
    int      nSpeed)
{
    LPBLOODDRIP lpAct;
    DG_TEX*     lpTex;

    if((lpAct = GV_NewActor(GV_ACTOR_USER, sizeof(BLOODDRIP))) == NULL)
        return NULL;

    GV_SetNamedActor(lpAct, Act, Die, "blooddrp.c");

    lpAct->nMap = GM_CurrentMap;

    lpAct->svectPos = *lpsvectPos;
    lpAct->svectPos.vy += nSpeed;

    lpAct->nSize = nSize;
    lpAct->nAccel = nSpeed;
    lpAct->nSpeed = nSpeed;

    lpAct->lpPrim = GM_MakePrim(DG_PRIM_POLY_FT4, 1, lpAct->verts, NULL);
    lpTex = DG_GetTexture(KETCHAP);

    {
        int x, y, w, h;
        x = lpTex->off_x;
        w = lpTex->w;
        y = lpTex->off_y;
        h = lpTex->h;
        setUVWH(PACK0, x, y, w, h);
        PACK0->tpage = lpTex->tpage;
        PACK0->clut = lpTex->clut;
    }
    {
        int x, y, w, h;
        x = lpTex->off_x;
        w = lpTex->w;
        y = lpTex->off_y;
        h = lpTex->h;
        setUVWH(PACK1, x, y, w, h);
        PACK1->tpage = lpTex->tpage;
        PACK1->clut = lpTex->clut;
    }

    PACK0->tpage = PACK0->tpage;
    PACK1->tpage = PACK1->tpage;
    
    setPolyFT4(PACK0);
    setPolyFT4(PACK1);

    setRGB0(PACK0, 128, 128, 128);
    setRGB0(PACK1, 128, 128, 128);

    setSemiTrans(PACK0, 1);
    setSemiTrans(PACK1, 1);

    return (void*)lpAct;
}

/******************************************************************************
 * statics
 */

static void Act(
    LPBLOODDRIP lpAct)
{
    int         lFloor[2];
    SVECTOR     diff;
    SVECTOR     svectRot;
    HZD_HDL*    lpHazard;

    GM_CurrentMap = lpAct->nMap;

    lpHazard = GM_GetMap(lpAct->nMap)->hzd;
    if(HZD_LevelHazardCheck(lpHazard, &lpAct->svectPos, HZD_CHK_F_FLOOR) != 1)
        lFloor[0] = 0;
    else
        HZD_GetLevelHeight(lFloor);


    lpAct->svectPos.vy -= lpAct->nSpeed;
    lpAct->nSpeed += lpAct->nAccel;

    if(lFloor[0] > lpAct->svectPos.vy)
        GV_DestroyActor(lpAct);

    lpAct->verts[0].vx = -(lpAct->nSize >> 3);
    lpAct->verts[0].vy = -(lpAct->nSize >> 1);
    lpAct->verts[0].vz = 0;

    lpAct->verts[1].vx = -(lpAct->nSize >> 3);
    lpAct->verts[1].vy = lpAct->nSize >> 1;
    lpAct->verts[1].vz = 0;

    lpAct->verts[2].vx = lpAct->nSize >> 3;
    lpAct->verts[2].vy = -(lpAct->nSize >> 1);
    lpAct->verts[2].vz = 0;

    lpAct->verts[3].vx = lpAct->nSize >> 3;
    lpAct->verts[3].vy = lpAct->nSize >> 1;
    lpAct->verts[3].vz = 0;

    diff.vx = (lpAct->svectPos.vx - gUnkCameraStruct2_800B7868.position.vx) >> 2;
    diff.vy = (lpAct->svectPos.vy - gUnkCameraStruct2_800B7868.position.vy) >> 2;
    diff.vz = (lpAct->svectPos.vz - gUnkCameraStruct2_800B7868.position.vz) >> 2;

    svectRot.vx = -ratan2(diff.vy, SquareRoot0(diff.vx * diff.vx + diff.vz * diff.vz));
    svectRot.vy = ratan2(diff.vx, diff.vz);
    svectRot.vz = 0;

    DG_SetPos2(&lpAct->svectPos, &svectRot);
    DG_PutVector(lpAct->verts, lpAct->verts, 4);
}

static void Die(
    LPBLOODDRIP lpAct)
{
    GM_FreePrim(lpAct->lpPrim);
}
