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

#include "common.h"
#include "m1e1.h"

/******************************************************************************
 * definitions and typedefs and structures
 */

#define BODY_DATA   GV_StrCode("valcan")
#define MOTION_DATA GV_StrCode("tankman")

#define BODY_FLAG   ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                    | DG_FLAG_GBOUND | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )

/******************************************************************************
 * functions
 */

static void* NewM1E1Vulcan(LPM1E1ACT lpParent);
static void Act(LPM1E1GUNNERACT lpAct);
static void Die(LPM1E1GUNNERACT lpAct);

/******************************************************************************
 * locals
 */

static int nTimer1 = 0;
static int nTimer2 = 0;

/******************************************************************************
 * publics
 */

void s05a_800DD1C8(
    LPM1E1ACT lpAct)
{
    SVECTOR svectPos;
    int     nVolume;

    if(lpAct->field_ED0 == 2)
    {
        svectPos = GM_PlayerPosition;
        nVolume = 63;
    }
    else
    {
        svectPos = lpAct->control.mov;
        nVolume = lpAct->nSoundVolume;
    }

    if((nTimer2 <= 0) && (lpAct->lpValcan == NULL))
    {
        if(lpAct->field_EC0 == 1)
        {
            if(lpAct->field_EC4 < 2)
                nTimer1 = 50;
            else
                nTimer1 = 1;
        }

        if(nTimer1 == 1)
        {
            if((lpAct->field_EC4 < 2) || ((rand() & 1) == 0))
            {
                lpAct->lpValcan = NewM1E1Vulcan(lpAct);
                GM_ConfigObjectAction(&lpAct->lpValcan->body, 2, 0, 5);
            }
            else
            {
                nTimer2 = lpAct->field_DB8 * 2 / 3;
                GM_SeSetPan(&svectPos, 133, nVolume);
            }
        }
    }

    if(--nTimer1 < 0)
        nTimer1 = 0;

    if(--nTimer2 < 0)
        nTimer2 = 0;

    if(nTimer2 <= 0)
    {
        if((lpAct->lpValcan != NULL) && (lpAct->lpValcan->body.action != 5)
            && (lpAct->lpValcan->nActDelay == 0))
        {
            lpAct->objBody.rots[8].vx = GV_NearSpeed(lpAct->objBody.rots[8].vx, -1592, 45);
            if (lpAct->objBody.rots[8].vx >= -1457 && lpAct->objBody.rots[8].vx < -1412)
            {
                GM_SeSetPan(&svectPos, 188, nVolume);
            }
        }

        if((lpAct->lpValcan == NULL) || (lpAct->lpValcan->body.action == 5))
        {
            lpAct->objBody.rots[8].vx = GV_NearSpeed(lpAct->objBody.rots[8].vx, 0, 45);
            if((lpAct->objBody.rots[8].vx >= -180) && (lpAct->objBody.rots[8].vx < -135))
            {
                GM_SeSetPan(&svectPos, 187, nVolume);
            }
        }
    }
}

/******************************************************************************
 */

static void* NewM1E1Vulcan(
    LPM1E1ACT lpParent)
{
    int             i;
    LPM1E1GUNNERACT lpAct;

    if((lpAct = GV_NewActor(GV_ACTOR_AFTER, sizeof(M1E1GUNNERACT))) == NULL)
        return NULL;

    lpAct->bHidden = TRUE;
    lpAct->lpParent = lpParent;

    GV_SetNamedActor(lpAct, Act, Die, "m1e1valc.c");

    if(GM_InitControl(&lpAct->control, lpAct->lpParent->nName, lpAct->lpParent->nMap) < 0)
    {
        GV_DestroyActor(lpAct);
        return NULL;
    }

    lpAct->control.r_sphere = -2;
    lpAct->control.interp = 0;
    GM_ConfigControlAttribute(&lpAct->control, RADAR_SIGHT | RADAR_VISIBLE);

    lpAct->light[0].t[0] = lpAct->lpParent->light[0].t[0];
    lpAct->light[0].t[1] = lpAct->lpParent->light[0].t[1];
    lpAct->light[0].t[2] = lpAct->lpParent->light[0].t[2];

    GM_InitObject(&lpAct->body, BODY_DATA, BODY_FLAG, MOTION_DATA);
    GM_ConfigObjectJoint(&lpAct->body);
    GM_ConfigMotionControl(&lpAct->body, &lpAct->m_ctrl, MOTION_DATA,
        lpAct->m_segs1, lpAct->m_segs2, &lpAct->subcontrol, lpAct->rots);
    GM_ConfigObjectLight(&lpAct->body, lpAct->light);
    DG_InvisibleObjs(lpAct->body.objs);

    for(i = 0; i < 16; i++)
    {
        lpAct->body.objs->objs[i].world = DG_ZeroMatrix;
    }

    if((GM_Vitality != 0) && (GM_GameOverTimer == 0) && (lpAct->lpParent->field_EC4 < 2))
    {
        lpAct->lpParent->nState = 3;
        lpAct->lpParent->field_ED0 = 2;

        lpAct->nWeaponSave = GM_Weapon;
        lpAct->nItemSave = GM_Item;

        GM_Weapon = WP_None;
        if((GM_Item != IT_NVG) && (GM_Item != IT_ThermG))
        {
            GM_Item = IT_None;
        }
    }

    lpAct->nActDelay = 30;
    return (void*)lpAct;
}

/******************************************************************************
 * statics
 */

static void Act(
    LPM1E1GUNNERACT lpAct)
{
    SVECTOR svectPos;
    SVECTOR svect1;
    SVECTOR svect2;
    int     nVolume;

    if((lpAct->body.action == 5) && (lpAct->nActDelay == 1))
    {
        GV_DestroyActor(lpAct);
        return;
    }

    if(--lpAct->nActDelay < 0)
        lpAct->nActDelay = 0;

    if(lpAct->nActDelay > 0)
        return;

    memset(&lpAct->subcontrol.step, 0x00, sizeof(SVECTOR));

    GM_ActMotion(&lpAct->body);
    GM_ActControl(&lpAct->control);

    svect1 = lpAct->subcontrol.step;
    GM_ActObject(&lpAct->body);
    lpAct->subcontrol.step = svect1;

    DG_GetLightMatrix2(&lpAct->control.mov, lpAct->light);

    if(lpAct->bHidden == FALSE)
    {
        DG_VisibleObjs(lpAct->body.objs);
    }

    lpAct->control.step.vx = 0;
    lpAct->control.step.vz = 0;

    if(lpAct->lpParent->field_ED0 == 2)
    {
        svectPos = GM_PlayerPosition;
        nVolume = 63;
    }
    else
    {
        svectPos = lpAct->control.mov;
        nVolume = lpAct->lpParent->nSoundVolume;
    }

    switch(lpAct->body.action)
    {
    case 2:
    case 5:
        break;

    case 11:
    case 12:
        if(lpAct->nActionTime == 0)
            GM_SeSetPan(&svectPos, 131, nVolume);

        if(lpAct->body.action == 12)
        {
            if((lpAct->nActionTime == 17)
                || (lpAct->nActionTime == 24)
                || (lpAct->nActionTime == 31)
                || (lpAct->nActionTime == 38)
                || (lpAct->nActionTime == 45)
                || (lpAct->nActionTime == 52)
                || (lpAct->nActionTime == 59)
                || (lpAct->nActionTime == 66))
            {
                GM_SeSetPan(&svectPos, SE_PUNCH_HIT, nVolume / 2);
            }
        }

        if(lpAct->body.action == 12)
        {
            if((lpAct->nActionTime == 78)
                || (lpAct->nActionTime == 85)
                || (lpAct->nActionTime == 92)
                || (lpAct->nActionTime == 99)
                || (lpAct->nActionTime == 105)
                || (lpAct->nActionTime == 112))
            {
                GM_SeSetPan(&svectPos, 186, nVolume);
            }
        }
        lpAct->nActionTime++;
        break;

    case 13:
        if(lpAct->nActionTime == 23)
            GM_SeSetPan(&svectPos, 135, nVolume);

        if(lpAct->nActionTime == 80)
            GM_SeSetPan(&svectPos, 135, nVolume);

        lpAct->nActionTime++;
        break;
    }

    DG_SetPos(&lpAct->lpParent->objBody.objs->objs[6].world);

    svect1.vx = 0;
    svect1.vy = 0;
    svect1.vz = 0;

    svect2.vx = 0;
    svect2.vy = 0;
    svect2.vz = 100;

    DG_PutVector(&svect1, &svect1, 1);
    DG_PutVector(&svect2, &svect2, 1);

    svect2.vx -= svect1.vx;
    svect2.vy -= svect1.vy;
    svect2.vz -= svect1.vz;

    lpAct->control.turn.vx = -ratan2(svect2.vy, SquareRoot0(svect2.vx * svect2.vx + svect2.vz * svect2.vz));
    lpAct->control.turn.vy = ratan2(svect2.vx, svect2.vz);
    lpAct->control.turn.vz = 0;

    svect1.vx = lpAct->lpParent->objBody.objs->objs[6].world.t[0];
    svect1.vy = lpAct->lpParent->objBody.objs->objs[6].world.t[1];
    svect1.vz = lpAct->lpParent->objBody.objs->objs[6].world.t[2];

    lpAct->control.mov.vy = lpAct->body.height + lpAct->lpParent->control.mov.vy;
    lpAct->control.step.vx = svect1.vx - lpAct->control.mov.vx;
    lpAct->control.step.vz = svect1.vz - lpAct->control.mov.vz;

    if(!lpAct->body.is_end)
    {
        lpAct->bHidden = FALSE;
        return;
    }

    switch(lpAct->body.action)
    {
    case 2:
        lpAct->nUnused2 = 0;
        lpAct->nActionTime = 0;

        if(lpAct->lpParent->field_ED0 == 2)
        {
            if(lpAct->lpParent->field_ECC == 7)
                GM_ConfigObjectAction(&lpAct->body, 13, 0, 5);
            else if(lpAct->lpParent->field_ECC < 4)
                GM_ConfigObjectAction(&lpAct->body, 11, 0, 5);
            else
                GM_ConfigObjectAction(&lpAct->body, 12, 0, 5);
        }
        else
        {
            if((rand() & 1) == 0)
                GM_ConfigObjectAction(&lpAct->body, 11, 0, 5);
            else
                GM_ConfigObjectAction(&lpAct->body, 12, 0, 5);
        }
        lpAct->bHidden = FALSE;
        break;

    case 11:
    case 12:
    case 13:
        GM_ConfigObjectAction(&lpAct->body, 5, 0, 5);
        lpAct->bHidden = FALSE;
        break;

    case 5:
        lpAct->nActDelay = 30;
        DG_InvisibleObjs(lpAct->body.objs);
        break;

    default:
        lpAct->bHidden = FALSE;
        break;
    }
}

static void Die(
    LPM1E1GUNNERACT lpAct)
{
    if(lpAct->lpParent->field_ED0 == 2)
    {
        if(lpAct->lpParent->bCombo == FALSE)
            lpAct->lpParent->nState = 2;
        else
            lpAct->lpParent->nState = 7;

        lpAct->lpParent->field_ED0 = 1;
        lpAct->lpParent->field_F48 = lpAct->lpParent->field_DB8;

        GM_Weapon = lpAct->nWeaponSave;
        GM_Item = lpAct->nItemSave;
    }

    lpAct->lpParent->lpValcan = NULL;
    GM_FreeObject(&lpAct->body);
    GM_FreeControl(&lpAct->control);
}
