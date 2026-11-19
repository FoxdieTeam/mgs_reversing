/******************************************************************************
 * included
 */

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"

#include "kojo/common.h"
#include "kojo/m1e1.h"

#include "takabe/cinema.h"      // for NewCinemaScreen, etc.

/******************************************************************************
 */

typedef struct tagM1E1CAMERAACT
{
    GV_ACT  actor;
    SVECTOR svectBoundMin1;
    SVECTOR svectBoundMax1;
    SVECTOR svectRot1;
    int     nTrack1;
    SVECTOR svectBoundMin2;
    SVECTOR svectBoundMax2;
    SVECTOR svectRot2;
    int     nTrack2;
    int     nZoom;
    int     nZoomLimit;
    int     nState;
    SVECTOR svectRot;
    SVECTOR svectTurn;
    SVECTOR svectPos;
    int     nStep;
    void   *lpCinemaScreen;
    int     nTime;
    BOOL    bLimit;
    BOOL    bInterp;
} M1E1CAMERAACT, *PM1E1CAMERAACT, *LPM1E1CAMERAACT;

extern LPM1E1ACT s05a_dword_800C362C;

static LPM1E1CAMERAACT lpCameraAct = NULL;

extern void sub_8007EF34(SVECTOR *pOutVec1, SVECTOR *pOutVec2, MATRIX *pInMtx);

static void Act(LPM1E1CAMERAACT lpAct);
static void Die(LPM1E1CAMERAACT lpAct);

static void s05a_800E1AA8(void);
static void s05a_800E1C14(void);
static void s05a_800E1D7C(void);
static void s05a_800E1F0C(void);
static void s05a_800E209C(VECTOR *out, VECTOR *in, int (*fn)());
static VECTOR *s05a_800E2328(VECTOR *out, SVECTOR *cam, VECTOR *in, SVECTOR *lo, SVECTOR *hi);

/******************************************************************************
 */

void *NewM1E1Camera(void)
{
    LPM1E1CAMERAACT lpAct;
    char           *str;

    lpAct = GV_NewActor(GV_ACTOR_USER, sizeof(M1E1CAMERAACT));
    if (lpAct == NULL) return NULL;

    GV_SetNamedActor(lpAct, Act, Die, "m1e1came.c");

    if (GCL_GetOption('b'))
    {
        if ((str = GCL_NextStr())) lpAct->svectBoundMin1.vx = GCL_StrToInt(str);
        if ((str = GCL_NextStr())) lpAct->svectBoundMin1.vy = GCL_StrToInt(str);
        if ((str = GCL_NextStr())) lpAct->svectBoundMin1.vz = GCL_StrToInt(str);
        if ((str = GCL_NextStr())) lpAct->svectBoundMax1.vx = GCL_StrToInt(str);
        if ((str = GCL_NextStr())) lpAct->svectBoundMax1.vy = GCL_StrToInt(str);
        if ((str = GCL_NextStr())) lpAct->svectBoundMax1.vz = GCL_StrToInt(str);
        if ((str = GCL_NextStr())) lpAct->svectBoundMin2.vx = GCL_StrToInt(str);
        if ((str = GCL_NextStr())) lpAct->svectBoundMin2.vy = GCL_StrToInt(str);
        if ((str = GCL_NextStr())) lpAct->svectBoundMin2.vz = GCL_StrToInt(str);
        if ((str = GCL_NextStr())) lpAct->svectBoundMax2.vx = GCL_StrToInt(str);
        if ((str = GCL_NextStr())) lpAct->svectBoundMax2.vy = GCL_StrToInt(str);
        if ((str = GCL_NextStr())) lpAct->svectBoundMax2.vz = GCL_StrToInt(str);
    }

    if (GCL_GetOption('r'))
    {
        if ((str = GCL_NextStr())) lpAct->svectRot1.vx = GCL_StrToInt(str);
        if ((str = GCL_NextStr())) lpAct->svectRot1.vy = GCL_StrToInt(str);
        if ((str = GCL_NextStr())) lpAct->svectRot1.vz = GCL_StrToInt(str);
        if ((str = GCL_NextStr())) lpAct->svectRot2.vx = GCL_StrToInt(str);
        if ((str = GCL_NextStr())) lpAct->svectRot2.vy = GCL_StrToInt(str);
        if ((str = GCL_NextStr())) lpAct->svectRot2.vz = GCL_StrToInt(str);
    }

    if (GCL_GetOption('t'))
    {
        if ((str = GCL_NextStr())) lpAct->nTrack1 = GCL_StrToInt(str);
        if ((str = GCL_NextStr())) lpAct->nTrack2 = GCL_StrToInt(str);
        if ((str = GCL_NextStr())) lpAct->nZoom = GCL_StrToInt(str);
    }

    if (GCL_GetOption('o'))
    {
        if ((str = GCL_NextStr())) lpAct->nZoomLimit = GCL_StrToInt(str);
    }

    lpAct->nState = 1;
    lpCameraAct = lpAct;
    return (void *)lpAct;
}

static void Act(LPM1E1CAMERAACT lpAct)
{
    SVECTOR     svect1;
    LPM1E1ACT   lpParent;

    lpParent = s05a_dword_800C362C;
    if (lpParent == NULL || lpParent->field_D54 == 6)
    {
        GV_DestroyActor(lpAct);
        return;
    }

    lpAct->nTime++;

    if (lpParent->field_ED0 == 2)
    {
        if (lpAct->nState != 3)
        {
            sub_8007EF34(&svect1, &lpAct->svectRot, &lpParent->objBody.objs->objs[3].world);
            memset(&lpAct->svectTurn, 0, sizeof(SVECTOR));
            memset(&lpAct->svectPos, 0, sizeof(SVECTOR));

            lpAct->nTime = 0;
            lpAct->bLimit = FALSE;
            lpAct->bInterp = FALSE;
            lpAct->svectRot.vz = 0;
            lpAct->svectTurn.vx = 0;
            lpAct->svectTurn.vy = -3;

            lpAct->svectRot.vx += 113;
            lpAct->svectRot.vy += 342;

            lpAct->nStep = 3500;

            if (lpAct->lpCinemaScreen == NULL)
            {
                lpAct->lpCinemaScreen = NewCinemaScreen(2000000000, 0);
            }

            GM_GameStatus |= (STATE_PADRELEASE | STATE_PAUSE_ONLY);
            GM_Camera.flag |= 0x202;
            sub_800309B4(0, 0);
            GM_SetCameraCallbackFunc(0, s05a_800E1AA8);
            GM_SetCameraCallbackFunc(1, s05a_800E1AA8);
        }
        else
        {
            lpAct->bInterp = TRUE;
        }
        GM_Camera.type = 0;
        lpAct->nState = 3;
        return;
    }

    if (lpParent->field_ED0 == 3)
    {
        if (lpAct->nState != 4)
        {
            sub_8007EF34(&svect1, &lpAct->svectRot, &lpParent->objBody.objs->objs[12].world);
            memset(&lpAct->svectTurn, 0, sizeof(SVECTOR));
            memset(&lpAct->svectPos, 0, sizeof(SVECTOR));

            lpAct->nTime = 0;
            lpAct->bLimit = FALSE;
            lpAct->bInterp = FALSE;
            lpAct->svectRot.vz = 0;
            lpAct->svectTurn.vx = 2;
            lpAct->svectTurn.vy = 6;

            lpAct->svectRot.vx += -284;

            lpAct->nStep = 3000;

            if (lpAct->lpCinemaScreen == NULL)
            {
                lpAct->lpCinemaScreen = NewCinemaScreen(2000000000, 0);
            }

            GM_GameStatus |= (STATE_PADRELEASE | STATE_PAUSE_ONLY);
            GM_Camera.flag |= 0x202;
            sub_800309B4(0, 0);
            GM_SetCameraCallbackFunc(0, s05a_800E1C14);
            GM_SetCameraCallbackFunc(1, s05a_800E1C14);
        }
        else
        {
            lpAct->bInterp = TRUE;
        }
        GM_Camera.type = 0;
        lpAct->nState = 4;
        return;
    }

    {
        HZD_HDL *hzd;
        HZD_GRP *grp;
        HZD_TRP *trp;
        int      i;

        hzd = lpParent->control.map->hzd;
        grp = hzd->grp;
        trp = &grp->triggers->trap;

        for (i = grp->n_triggers - hzd->n_cameras; i > 0; i--, trp++)
        {
            if (trp->name_id != GV_StrCode("nosubject")) continue;
            if (trp->b1.x > GM_PlayerPosition.vx) continue;
            if (trp->b2.x < GM_PlayerPosition.vx) continue;
            if (trp->b1.y > GM_PlayerPosition.vy) continue;
            if (trp->b2.y < GM_PlayerPosition.vy) continue;
            if (trp->b1.z > GM_PlayerPosition.vz) continue;
            if (trp->b2.z < GM_PlayerPosition.vz) continue;
            break;
        }

        if (i <= 0 &&
            s05a_dword_800C362C->field_E5C < s05a_dword_800C362C->field_DBC &&
            GM_PlayerPosition.vz > s05a_dword_800C362C->control.mov.vz)
        {
            if (lpAct->nState != 2)
            {
                if (lpAct->lpCinemaScreen != NULL)
                {
                    NewCinemaScreenClose(lpAct->lpCinemaScreen);
                    lpAct->lpCinemaScreen = NULL;
                }
                lpAct->nTime = 0;
                if (lpAct->nState != 1)
                {
                    lpAct->bInterp = FALSE;
                    GM_SnakeCamera.position = GM_PlayerPosition;
                }
                else
                {
                    lpAct->bInterp = TRUE;
                }
                GM_GameStatus &= ~(STATE_PADRELEASE | STATE_PAUSE_ONLY);
                GM_Camera.flag = (GM_Camera.flag | 2) & ~0x200;
                sub_800309B4(0, -1);
                GM_SetCameraCallbackFunc(0, NULL);
                GM_SetCameraCallbackFunc(1, s05a_800E1D7C);
            }
            else
            {
                lpAct->bInterp = TRUE;
            }
            if (GM_Camera.interp > 0)
            {
                lpAct->bLimit = FALSE;
            }
            else if (lpAct->nState != 1)
            {
                lpAct->bLimit = FALSE;
            }
            else
            {
                lpAct->bLimit = TRUE;
            }
            GM_Camera.type = 0;
            lpAct->nState = 2;
            return;
        }

        if (lpAct->nState != 1)
        {
            if (lpAct->lpCinemaScreen != NULL)
            {
                NewCinemaScreenClose(lpAct->lpCinemaScreen);
                lpAct->lpCinemaScreen = NULL;
            }
            lpAct->nTime = 0;
            if (lpAct->nState != 2)
            {
                lpAct->bInterp = FALSE;
                GM_SnakeCamera.position = GM_PlayerPosition;
            }
            else
            {
                lpAct->bInterp = TRUE;
            }
            GM_GameStatus &= ~(STATE_PADRELEASE | STATE_PAUSE_ONLY);
            GM_Camera.flag = (GM_Camera.flag | 2) & ~0x200;
            sub_800309B4(0, -1);
            GM_SetCameraCallbackFunc(0, NULL);
            GM_SetCameraCallbackFunc(1, s05a_800E1F0C);
        }
        else
        {
            lpAct->bInterp = TRUE;
        }

        if (GM_Camera.interp > 0)
        {
            lpAct->bLimit = FALSE;
        }
        else if (lpAct->nState != 2)
        {
            lpAct->bLimit = FALSE;
        }
        else
        {
            lpAct->bLimit = TRUE;
        }

        GM_Camera.type = 0;
        lpAct->nState = 1;
    }
}

static void Die(LPM1E1CAMERAACT lpAct)
{
    GM_Camera.flag &= ~2;
    GM_SetCameraCallbackFunc(1, NULL);
    lpCameraAct = 0;
}

static void s05a_800E1AA8(void)
{
    VECTOR  pos;
    VECTOR  rot;
    SVECTOR svect1;

    GM_PlayerStatus &= ~PLAYER_NOT_SIGHT;
    DG_SetPos2(&DG_ZeroVector, &lpCameraAct->svectRot);

    memset(&svect1, 0, sizeof(SVECTOR));
    svect1.vz = lpCameraAct->nStep;
    DG_PutVector(&svect1, &svect1, 1);

    lpCameraAct->svectPos.vx = s05a_dword_800C362C->objBody.objs->objs[6].world.t[0];
    lpCameraAct->svectPos.vy = s05a_dword_800C362C->objBody.objs->objs[6].world.t[1];
    lpCameraAct->svectPos.vz = s05a_dword_800C362C->objBody.objs->objs[6].world.t[2];
    lpCameraAct->svectPos.vy += 500;

    pos.vx = lpCameraAct->svectPos.vx + svect1.vx;
    pos.vy = lpCameraAct->svectPos.vy + svect1.vy;
    pos.vz = lpCameraAct->svectPos.vz + svect1.vz;

    rot.vx = lpCameraAct->svectPos.vx;
    rot.vy = lpCameraAct->svectPos.vy;
    rot.vz = lpCameraAct->svectPos.vz;

    s05a_800E209C(&pos, &rot, GV_NearExp2);

    lpCameraAct->svectRot.vx += lpCameraAct->svectTurn.vx;
    lpCameraAct->svectRot.vy += lpCameraAct->svectTurn.vy;
    lpCameraAct->svectRot.vz += lpCameraAct->svectTurn.vz;
}

static void s05a_800E1C14(void)
{
    VECTOR  vectPos;
    VECTOR  vectTrg;
    SVECTOR svect1;

    GM_PlayerStatus &= ~PLAYER_NOT_SIGHT;
    DG_SetPos2(&DG_ZeroVector, &lpCameraAct->svectRot);

    memset(&svect1, 0x00, sizeof(SVECTOR));
    svect1.vz = lpCameraAct->nStep;

    DG_PutVector(&svect1, &svect1, 1);

    lpCameraAct->svectPos.vx = s05a_dword_800C362C->objBody.objs->objs[10].world.t[0];
    lpCameraAct->svectPos.vy = s05a_dword_800C362C->objBody.objs->objs[10].world.t[1];
    lpCameraAct->svectPos.vz = s05a_dword_800C362C->objBody.objs->objs[10].world.t[2];

    vectPos.vx = lpCameraAct->svectPos.vx + svect1.vx;
    vectPos.vy = lpCameraAct->svectPos.vy + svect1.vy;
    vectPos.vz = lpCameraAct->svectPos.vz + svect1.vz;

    vectTrg.vx = lpCameraAct->svectPos.vx;
    vectTrg.vy = lpCameraAct->svectPos.vy;
    vectTrg.vz = lpCameraAct->svectPos.vz;

    s05a_800E209C(&vectPos, &vectTrg, GV_NearExp2);

    lpCameraAct->svectRot.vx += lpCameraAct->svectTurn.vx;
    lpCameraAct->svectRot.vy += lpCameraAct->svectTurn.vy;
    lpCameraAct->svectRot.vz += lpCameraAct->svectTurn.vz;
}

static void s05a_800E1D7C(void)
{
    VECTOR  vectPos;
    VECTOR  vectTrg;
    SVECTOR svect1;

    DG_SetPos2(&DG_ZeroVector, &lpCameraAct->svectRot2);

    memset(&svect1, 0x00, sizeof(SVECTOR));
    svect1.vz = lpCameraAct->nTrack2;

    if (s05a_dword_800C362C->field_E5C <= lpCameraAct->nZoomLimit)
    {
        svect1.vz += lpCameraAct->nZoom;
    }

    DG_PutVector(&svect1, &svect1, 1);

    vectPos.vx = GM_PlayerPosition.vx + svect1.vx;
    vectPos.vy = GM_PlayerPosition.vy + svect1.vy;
    vectPos.vz = GM_PlayerPosition.vz + svect1.vz;
    s05a_800E2328(&vectPos, &GM_Camera.position, &vectPos, &lpCameraAct->svectBoundMin2, &lpCameraAct->svectBoundMax2);

    vectTrg.vx = GM_PlayerPosition.vx;
    vectTrg.vy = GM_PlayerPosition.vy;
    vectTrg.vz = GM_PlayerPosition.vz;
    s05a_800E2328(&vectTrg, &GM_Camera.target, &vectTrg, &lpCameraAct->svectBoundMin2, &lpCameraAct->svectBoundMax2);

    vectTrg.vx = vectPos.vx;
    s05a_800E209C(&vectPos, &vectTrg, GV_NearExp8);

    if (GM_Camera.target.vz <= GM_Camera.position.vz)
    {
        GM_Camera.target.vz--;
    }
}

static void s05a_800E1F0C(void)
{
    VECTOR  vectPos;
    VECTOR  vectTrg;
    SVECTOR svect1;

    DG_SetPos2(&DG_ZeroVector, &lpCameraAct->svectRot1);

    memset(&svect1, 0x00, sizeof(SVECTOR));
    svect1.vz = lpCameraAct->nTrack1;

    if (s05a_dword_800C362C->field_E5C <= lpCameraAct->nZoomLimit)
    {
        svect1.vz += lpCameraAct->nZoom;
    }

    DG_PutVector(&svect1, &svect1, 1);

    vectPos.vx = GM_PlayerPosition.vx + svect1.vx;
    vectPos.vy = GM_PlayerPosition.vy + svect1.vy;
    vectPos.vz = GM_PlayerPosition.vz + svect1.vz;
    s05a_800E2328(&vectPos, &GM_Camera.position, &vectPos, &lpCameraAct->svectBoundMin1, &lpCameraAct->svectBoundMax1);

    vectTrg.vx = GM_PlayerPosition.vx;
    vectTrg.vy = GM_PlayerPosition.vy;
    vectTrg.vz = GM_PlayerPosition.vz;
    s05a_800E2328(&vectTrg, &GM_Camera.target, &vectTrg, &lpCameraAct->svectBoundMin1, &lpCameraAct->svectBoundMax1);

    vectTrg.vx = vectPos.vx;
    s05a_800E209C(&vectPos, &vectTrg, GV_NearExp8);

    if (GM_Camera.target.vz <= GM_Camera.position.vz)
    {
        GM_Camera.target.vz--;
    }
}

static void s05a_800E209C(VECTOR *lpvectPosition, VECTOR *lpvectTarget, int (*pfnInterp)())
{
    lpvectPosition->vx = __max(lpvectPosition->vx, lpCameraAct->svectBoundMin1.vx);
    lpvectPosition->vx = __min(lpvectPosition->vx, lpCameraAct->svectBoundMax1.vx);
    lpvectPosition->vy = __max(lpvectPosition->vy, lpCameraAct->svectBoundMin1.vy);
    lpvectPosition->vy = __min(lpvectPosition->vy, lpCameraAct->svectBoundMax1.vy);
    lpvectPosition->vz = __max(lpvectPosition->vz, lpCameraAct->svectBoundMin1.vz);
    lpvectPosition->vz = __min(lpvectPosition->vz, lpCameraAct->svectBoundMax1.vz);

    lpvectTarget->vx = __max(lpvectTarget->vx, lpCameraAct->svectBoundMin1.vx);
    lpvectTarget->vx = __min(lpvectTarget->vx, lpCameraAct->svectBoundMax1.vx);
    lpvectTarget->vy = __max(lpvectTarget->vy, lpCameraAct->svectBoundMin1.vy);
    lpvectTarget->vy = __min(lpvectTarget->vy, lpCameraAct->svectBoundMax1.vy);
    lpvectTarget->vz = __max(lpvectTarget->vz, lpCameraAct->svectBoundMin1.vz);
    lpvectTarget->vz = __min(lpvectTarget->vz, lpCameraAct->svectBoundMax1.vz);

    if (!lpCameraAct->bInterp)
    {
        GM_Camera.position.vx = lpvectPosition->vx;
        GM_Camera.position.vy = lpvectPosition->vy;
        GM_Camera.position.vz = lpvectPosition->vz;

        GM_Camera.target.vx = lpvectTarget->vx;
        GM_Camera.target.vy = lpvectTarget->vy;
        GM_Camera.target.vz = lpvectTarget->vz;
    }

    GM_Camera.position.vx = pfnInterp(GM_Camera.position.vx, lpvectPosition->vx);
    GM_Camera.position.vy = pfnInterp(GM_Camera.position.vy, lpvectPosition->vy);
    GM_Camera.position.vz = pfnInterp(GM_Camera.position.vz, lpvectPosition->vz);

    GM_Camera.target.vx = pfnInterp(GM_Camera.target.vx, lpvectTarget->vx);
    GM_Camera.target.vy = pfnInterp(GM_Camera.target.vy, lpvectTarget->vy);
    GM_Camera.target.vz = pfnInterp(GM_Camera.target.vz, lpvectTarget->vz);
}

static VECTOR *s05a_800E2328(VECTOR *lpvectResult, SVECTOR *lpsvectFrom, VECTOR *lpsvectTo, SVECTOR *lpsvectBoundMin, SVECTOR *lpsvectBoundMax)
{
    VECTOR  vect1;
    SVECTOR svect1;

    vect1.vx = lpsvectFrom->vx;
    vect1.vy = lpsvectFrom->vy;
    vect1.vz = lpsvectFrom->vz;

    if (!lpCameraAct->bLimit)
    {
        vect1.vx = lpsvectTo->vx;
    }
    else
    {
        int nLen;

        nLen = lpsvectTo->vx - vect1.vx;
        if ((lpsvectTo->vx - vect1.vx) > 1000)
        {
            vect1.vx -= 1000;
            vect1.vx += nLen;
        }
        else if ((vect1.vx - lpsvectTo->vx) > 1000)
        {
            vect1.vx += 1000;
            vect1.vx += nLen;
        }
    }

    if (!lpCameraAct->bLimit)
    {
        vect1.vy = lpsvectTo->vy;
    }
    else
    {
        int nLen;

        nLen = lpsvectTo->vy - vect1.vy;
        if ((lpsvectTo->vy - vect1.vy) > 1000)
        {
            vect1.vy -= 1000;
            vect1.vy += nLen;
        }
        else if ((vect1.vy - lpsvectTo->vy) > 1000)
        {
            vect1.vy += 1000;
            vect1.vy += nLen;
        }
    }

    if (!lpCameraAct->bLimit)
    {
        vect1.vz = lpsvectTo->vz;
    }
    else
    {
        int nLen;

        nLen = lpsvectTo->vz - vect1.vz;
        if ((lpsvectTo->vz - vect1.vz) > 1000)
        {
            vect1.vz -= 1000;
            vect1.vz += nLen;
        }
        else if ((vect1.vz - lpsvectTo->vz) > 1000)
        {
            vect1.vz += 1000;
            vect1.vz += nLen;
        }
    }

    vect1.vx = __max(vect1.vx, lpsvectBoundMin->vx);
    vect1.vx = __min(vect1.vx, lpsvectBoundMax->vx);
    vect1.vy = __max(vect1.vy, lpsvectBoundMin->vy);
    vect1.vy = __min(vect1.vy, lpsvectBoundMax->vy);
    vect1.vz = __max(vect1.vz, lpsvectBoundMin->vz);
    vect1.vz = __min(vect1.vz, lpsvectBoundMax->vz);

    *lpvectResult = vect1;
    return lpvectResult;
}
