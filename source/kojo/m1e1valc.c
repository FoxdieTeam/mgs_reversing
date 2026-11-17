/******************************************************************************
 * included
 */

#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"

#include "kojo/common.h"
#include "kojo/m1e1.h"

/******************************************************************************
 */

static int s05a_dword_800C3644 = 0;
static int s05a_dword_800C3648 = 0;

/******************************************************************************
 */

void* NewM1E1Vulcan(LPM1E1ACT lpParent);
void s05a_800DD6B8(LPM1E1VALCANACT lpAct);
void s05a_800DDC14(LPM1E1VALCANACT lpAct);

/******************************************************************************
 */

void s05a_800DD1C8(LPM1E1ACT lpAct)
{
    SVECTOR pos;
    int     vol;

    if (lpAct->field_ED0 == 2)
    {
        pos = GM_PlayerPosition;
        vol = 0x3F;
    }
    else
    {
        pos = lpAct->control.mov;
        vol = lpAct->nSoundVolume;
    }

    if (s05a_dword_800C3648 <= 0 && lpAct->lpValcan == NULL)
    {
        if (lpAct->field_EC0 == 1)
        {
            if (lpAct->field_EC4 < 2)
            {
                s05a_dword_800C3644 = 0x32;
            }
            else
            {
                s05a_dword_800C3644 = 1;
            }
        }
        if (s05a_dword_800C3644 == 1)
        {
            if (lpAct->field_EC4 < 2 || !(rand() & 1))
            {
                lpAct->lpValcan = NewM1E1Vulcan(lpAct);
                GM_ConfigObjectAction(&lpAct->lpValcan->body, 2, 0, 5);
            }
            else
            {
                s05a_dword_800C3648 = lpAct->field_DB8 * 2 / 3;
                GM_SeSetPan(&pos, 0x85, vol);
            }
        }
    }

    if (--s05a_dword_800C3644 < 0)
    {
        s05a_dword_800C3644 = 0;
    }
    if (--s05a_dword_800C3648 < 0)
    {
        s05a_dword_800C3648 = 0;
    }

    if (s05a_dword_800C3648 <= 0)
    {
        if (lpAct->lpValcan != NULL && lpAct->lpValcan->body.action != 5 &&
            lpAct->lpValcan->nActDelay == 0)
        {
            lpAct->objBody.rots[8].vx = GV_NearSpeed(lpAct->objBody.rots[8].vx, -0x638, 0x2D);
            if (lpAct->objBody.rots[8].vx >= -0x5B1 && lpAct->objBody.rots[8].vx < -0x584)
            {
                GM_SeSetPan(&pos, 0xBC, vol);
            }
        }
        if (lpAct->lpValcan == NULL || lpAct->lpValcan->body.action == 5)
        {
            lpAct->objBody.rots[8].vx = GV_NearSpeed(lpAct->objBody.rots[8].vx, 0, 0x2D);
            if (lpAct->objBody.rots[8].vx >= -0xB4 && lpAct->objBody.rots[8].vx < -0x87)
            {
                GM_SeSetPan(&pos, 0xBB, vol);
            }
        }
    }
}

/******************************************************************************
 */

void* NewM1E1Vulcan(LPM1E1ACT lpParent)
{
    int             i;
    LPM1E1VALCANACT lpAct;

    lpAct = GV_NewActor(GV_ACTOR_AFTER, sizeof(M1E1VALCANACT));
    if (lpAct == NULL)
    {
        return NULL;
    }
    lpAct->bHidden = TRUE;
    lpAct->lpParent = lpParent;
    GV_SetNamedActor(lpAct, s05a_800DD6B8, s05a_800DDC14, "m1e1valc.c");
    if (GM_InitControl(&lpAct->control, lpAct->lpParent->field_744, lpAct->lpParent->field_748) < 0)
    {
        GV_DestroyActor(lpAct);
        return NULL;
    }
    lpAct->control.r_sphere = -2;
    lpAct->control.interp = 0;
    GM_ConfigControlAttribute(&lpAct->control, 5);
    lpAct->light[0].t[0] = lpAct->lpParent->light[0].t[0];
    lpAct->light[0].t[1] = lpAct->lpParent->light[0].t[1];
    lpAct->light[0].t[2] = lpAct->lpParent->light[0].t[2];
    GM_InitObject(&lpAct->body, GV_StrCode("valcan"), 0x32D, GV_StrCode("tankman"));
    GM_ConfigObjectJoint(&lpAct->body);
    GM_ConfigMotionControl(&lpAct->body, &lpAct->m_ctrl, GV_StrCode("tankman"),
                           lpAct->m_segs1, lpAct->m_segs2, &lpAct->subcontrol, lpAct->rots);
    GM_ConfigObjectLight(&lpAct->body, &lpAct->light[0]);
    DG_InvisibleObjs(lpAct->body.objs);
    for (i = 0; i < 16; i++)
    {
        lpAct->body.objs->objs[i].world = DG_ZeroMatrix;
    }
    if (GM_Vitality != 0 && GM_GameOverTimer == 0 && lpAct->lpParent->field_EC4 < 2)
    {
        lpAct->lpParent->field_D54 = 3;
        lpAct->lpParent->field_ED0 = 2;
        lpAct->nWeaponSave = GM_Weapon;
        lpAct->nItemSave = GM_Item;
        GM_Weapon = WP_None;
        if (GM_Item != IT_NVG && GM_Item != IT_ThermG)
        {
            GM_Item = IT_None;
        }
    }
    lpAct->nActDelay = 30;
    return (void*)lpAct;
}

void s05a_800DD6B8(LPM1E1VALCANACT lpAct)
{
    SVECTOR pos;
    SVECTOR vec;
    SVECTOR vec2;
    int     vol;

    if (lpAct->body.action == 5 && lpAct->nActDelay == 1)
    {
        GV_DestroyActor(lpAct);
        return;
    }
    if (--lpAct->nActDelay < 0) lpAct->nActDelay = 0;
    if (lpAct->nActDelay > 0) return;

    memset(&lpAct->subcontrol.step, 0, 8);
    GM_ActMotion(&lpAct->body);
    GM_ActControl(&lpAct->control);
    vec = lpAct->subcontrol.step;
    GM_ActObject(&lpAct->body);
    lpAct->subcontrol.step = vec;
    DG_GetLightMatrix2(&lpAct->control.mov, &lpAct->light[0]);
    if (!lpAct->bHidden)
    {
        DG_VisibleObjs(lpAct->body.objs);
    }
    lpAct->control.step.vx = 0;
    lpAct->control.step.vz = 0;

    if (lpAct->lpParent->field_ED0 == 2)
    {
        pos = GM_PlayerPosition;
        vol = 0x3F;
    }
    else
    {
        pos = lpAct->control.mov;
        vol = lpAct->lpParent->nSoundVolume;
    }

    switch (lpAct->body.action)
    {
    case 2:
    case 5:
        break;
    case 11:
    case 12:
        if (lpAct->nActionTime == 0) GM_SeSetPan(&pos, 0x83, vol);
        if (lpAct->body.action == 12)
        {
            if (lpAct->nActionTime == 0x11 || lpAct->nActionTime == 0x18 || lpAct->nActionTime == 0x1F ||
                lpAct->nActionTime == 0x26 || lpAct->nActionTime == 0x2D || lpAct->nActionTime == 0x34 ||
                lpAct->nActionTime == 0x3B || lpAct->nActionTime == 0x42)
            {
                GM_SeSetPan(&pos, 0x34, vol / 2);
            }
        }
        if (lpAct->body.action == 12)
        {
            if (lpAct->nActionTime == 0x4E || lpAct->nActionTime == 0x55 || lpAct->nActionTime == 0x5C ||
                lpAct->nActionTime == 0x63 || lpAct->nActionTime == 0x69 || lpAct->nActionTime == 0x70)
            {
                GM_SeSetPan(&pos, 0xBA, vol);
            }
        }
        lpAct->nActionTime++;
        break;
    case 13:
        if (lpAct->nActionTime == 0x17) GM_SeSetPan(&pos, 0x87, vol);
        if (lpAct->nActionTime == 0x50) GM_SeSetPan(&pos, 0x87, vol);
        lpAct->nActionTime++;
        break;
    }

    DG_SetPos(&lpAct->lpParent->objBody.objs->objs[6].world);
    vec.vx = 0;
    vec.vy = 0;
    vec.vz = 0;
    vec2.vx = 0;
    vec2.vy = 0;
    vec2.vz = 0x64;
    DG_PutVector(&vec, &vec, 1);
    DG_PutVector(&vec2, &vec2, 1);
    vec2.vx -= vec.vx;
    vec2.vy -= vec.vy;
    vec2.vz -= vec.vz;
    lpAct->control.turn.vx = -ratan2(vec2.vy, SquareRoot0(vec2.vx * vec2.vx + vec2.vz * vec2.vz));
    lpAct->control.turn.vy = ratan2(vec2.vx, vec2.vz);
    lpAct->control.turn.vz = 0;
    vec.vx = lpAct->lpParent->objBody.objs->objs[6].world.t[0];
    vec.vy = lpAct->lpParent->objBody.objs->objs[6].world.t[1];
    vec.vz = lpAct->lpParent->objBody.objs->objs[6].world.t[2];
    lpAct->control.mov.vy = lpAct->body.height + lpAct->lpParent->control.mov.vy;
    lpAct->control.step.vx = vec.vx - lpAct->control.mov.vx;
    lpAct->control.step.vz = vec.vz - lpAct->control.mov.vz;

    if (lpAct->body.is_end == 0)
    {
        lpAct->bHidden = FALSE;
    }
    else
    {
        switch (lpAct->body.action)
        {
        case 2:
            lpAct->nUnused2 = 0;
            lpAct->nActionTime = 0;
            if (lpAct->lpParent->field_ED0 == 2)
            {
                if (lpAct->lpParent->field_ECC == 7)
                {
                    GM_ConfigObjectAction(&lpAct->body, 0xD, 0, 5);
                }
                else if (lpAct->lpParent->field_ECC < 4)
                {
                    GM_ConfigObjectAction(&lpAct->body, 0xB, 0, 5);
                }
                else
                {
                    GM_ConfigObjectAction(&lpAct->body, 0xC, 0, 5);
                }
            }
            else
            {
                if ((rand() & 1) == 0)
                {
                    GM_ConfigObjectAction(&lpAct->body, 0xB, 0, 5);
                }
                else
                {
                    GM_ConfigObjectAction(&lpAct->body, 0xC, 0, 5);
                }
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
}

void s05a_800DDC14(LPM1E1VALCANACT lpAct)
{
    if (lpAct->lpParent->field_ED0 == 2)
    {
        if (lpAct->lpParent->field_D58 == 0)
        {
            lpAct->lpParent->field_D54 = lpAct->lpParent->field_ED0;
        }
        else
        {
            lpAct->lpParent->field_D54 = 7;
        }
        lpAct->lpParent->field_ED0 = 1;
        lpAct->lpParent->field_F48 = lpAct->lpParent->field_DB8;
        GM_Weapon = lpAct->nWeaponSave;
        GM_Item = lpAct->nItemSave;
    }

    lpAct->lpParent->lpValcan = NULL;
    GM_FreeObject(&lpAct->body);
    GM_FreeControl(&lpAct->control);
}
