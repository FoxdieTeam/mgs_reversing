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

#include "chara/snake/sna_init.h"
#include "strcode.h"
#include "bullet/blast.h"   // for AN_Blast_high

extern void *NewDemoKage(OBJECT *parent, SVECTOR vec, int *arg2, int *arg3, char r, char g, char b);

/******************************************************************************
 */

extern LPM1E1ACT s05a_dword_800C362C;

static CONTROL s05a_dword_800E3800;

static void Act(LPM1E1GUNNERACT lpAct);
static void Die(LPM1E1GUNNERACT lpAct);
int s05a_800DEC18(LPM1E1GUNNERACT lpAct, SVECTOR *s2, int a2);
void s05a_800E0D38(CONTROL *control, HZD_HDL *lpHazard);
void s05a_800E0E28(CONTROL *control, HZD_HDL *lpHazard);
void s05a_800E0F64(CONTROL *control, HZD_HDL *lpHazard);
void s05a_800E1014(CONTROL *control, HZD_HDL *lpHazard);

/******************************************************************************
 */

void *NewM1E1Soldier(LPM1E1ACT lpParent)
{
    LPM1E1GUNNERACT lpAct;
    int       name;
    int       i;
    OBJECT   *bodyp;
    const char *tankstr;
    SVECTOR   size;

    lpAct = GV_NewActor(6, 0x848);
    if (lpAct == NULL)
    {
        return 0;
    }
    lpAct->bHidden = TRUE;
    lpAct->lpParent = lpParent;
    GV_SetNamedActor(lpAct, Act, Die, "m1e1sold.c");

    if (GM_InitControl(&lpAct->control, lpAct->lpParent->nName,
                       lpAct->lpParent->nMap) < 0)
    {
        GV_DestroyActor(lpAct);
        return 0;
    }

    lpAct->control.r_sphere = -2;
    lpAct->control.interp = 0;
    GM_ConfigControlAttribute(&lpAct->control, 5);

    lpAct->light[0].t[0] = lpAct->lpParent->light[0].t[0];
    lpAct->light[0].t[1] = lpAct->lpParent->light[0].t[1];
    lpAct->light[0].t[2] = lpAct->lpParent->light[0].t[2];
    name = GV_StrCode("out_c_m1");  /* "out_" */

    tankstr = "tankman";
    bodyp = &lpAct->body;
    GM_InitObject(bodyp, name, 0x32d, GV_StrCode(tankstr));
    GM_ConfigObjectJoint(bodyp);
    GM_ConfigMotionControl(bodyp, &lpAct->m_ctrl,
                           GV_StrCode(tankstr),
                           lpAct->m_segs1,
                           lpAct->m_segs2,
                           &lpAct->subcontrol,
                           lpAct->rots);
    GM_ConfigObjectLight(bodyp, &lpAct->light[0]);

    DG_InvisibleObjs(bodyp->objs);
    lpAct->hom = GM_SetHomingTarget(&lpAct->homMatrix, &lpAct->control);
    lpAct->hom->flag = 1;
    lpAct->target = GM_AllocTarget();
    size.vx = 0x12c;
    size.vy = 0x12c;
    size.vz = 0x12c;
    GM_SetTarget(lpAct->target, 0x94, 2, &size);
    GM_SetPowerTarget(lpAct->target, 1, -1, 0x2710, 0, &DG_ZeroVector);

    for (i = 0; i < 0x10; i++)
    {
        lpAct->body.objs->objs[i].world = DG_ZeroMatrix;
    }
    return (void*)lpAct;
}

static void Act(LPM1E1GUNNERACT lpAct)
{
    int     lvl[2];
    SVECTOR vec1;
    SVECTOR vec2;

    memset(&lpAct->subcontrol.step, 0, 8);
    GM_ActMotion(&lpAct->body);
    GM_ActControl(&lpAct->control);
    vec1 = lpAct->subcontrol.step;
    GM_ActObject(&lpAct->body);
    lpAct->subcontrol.step = vec1;
    DG_GetLightMatrix2(&lpAct->control.mov, &lpAct->light[0]);

    if (!lpAct->bHidden)
    {
        DG_VisibleObjs(lpAct->body.objs);
    }
    if (--lpAct->nFallDelay < 0) lpAct->nFallDelay = 0;
    if (--lpAct->nSoundDelay1 < 0) lpAct->nSoundDelay1 = 0;
    if (--lpAct->nSoundDelay2 < 0) lpAct->nSoundDelay2 = 0;

    if (lpAct->nSoundDelay2 == 0 && lpAct->lpParent->field_ED0 == 3)
    {
        if (lpAct->lpParent->field_D58 == 0)
        {
            lpAct->lpParent->field_D54 = 2;
        }
        else
        {
            lpAct->lpParent->field_D54 = 7;
        }
        lpAct->lpParent->field_ED0 = 1;
        GM_Weapon = lpAct->nWeaponSave;
        GM_Item = lpAct->nItemSave;
    }

    lpAct->bDead = FALSE;
    if (lpAct->m_ctrl.info1.frame == 1)
    {
        lpAct->nHeight = lpAct->body.height;
    }
    lpAct->control.step.vx = 0;
    lpAct->control.step.vz = 0;
    lpAct->subcontrol.step.vy = lpAct->body.height - lpAct->nHeight;

    switch (lpAct->body.action)
    {
    case 0:
    case 1:
    case 2:
    case 5:
    case 6:
        if (lpAct->body.action == 2 && lpAct->lpParent->field_E10 == 1)
        {
            lpAct->lpParent->field_E10 = 0;
            if (GM_Vitality != 0 && GM_GameOverTimer == 0)
            {
                lpAct->nSoundDelay1 = 150;
                lpAct->nSoundDelay2 = 60;
                GM_SeSetPan(&GM_PlayerPosition, 0x82, 0x3F);
                lpAct->lpParent->field_D54 = 3;
                lpAct->lpParent->field_ED0 = 3;
                lpAct->nWeaponSave = GM_Weapon;
                lpAct->nItemSave = GM_Item;
                GM_Weapon = WP_None;
                if (GM_Item != IT_NVG && GM_Item != IT_ThermG)
                {
                    GM_Item = IT_None;
                }
            }
        }
        else if (lpAct->body.action == 1)
        {
            if (lpAct->lpParent->field_E10 == 0 && lpAct->nSoundDelay1 <= 0 && lpAct->lpParent->field_ED4 >= 0x1E)
            {
                if (rand() % 3 != 0)
                {
                    lpAct->nSoundDelay1 = 150;
                    GM_SeSetPan(&lpAct->control.mov, 0x80, lpAct->lpParent->nSoundVolume);
                }
            }
        }

        DG_SetPos(&lpAct->lpParent->objBody.objs->objs[12].world);
        vec1.vx = 0;
        vec1.vy = 0;
        vec1.vz = 0;
        vec2.vx = 0;
        vec2.vy = 0;
        vec2.vz = 0x64;
        DG_PutVector(&vec1, &vec1, 1);
        DG_PutVector(&vec2, &vec2, 1);
        vec2.vx -= vec1.vx;
        vec2.vy -= vec1.vy;
        vec2.vz -= vec1.vz;
        lpAct->control.turn.vx = -ratan2(vec2.vy, SquareRoot0(vec2.vx * vec2.vx + vec2.vz * vec2.vz));
        lpAct->control.turn.vy = ratan2(vec2.vx, vec2.vz);
        lpAct->control.turn.vz = 0;
        vec1.vx = lpAct->lpParent->objBody.objs->objs[12].world.t[0];
        vec1.vy = lpAct->lpParent->objBody.objs->objs[12].world.t[1];
        vec1.vz = lpAct->lpParent->objBody.objs->objs[12].world.t[2];
        lpAct->control.mov.vy = lpAct->body.height + lpAct->lpParent->control.mov.vy - 0xC8;
        lpAct->control.step.vx = vec1.vx - lpAct->control.mov.vx;
        lpAct->control.step.vz = vec1.vz - lpAct->control.mov.vz;
        memset(&vec1, 0, 8);
        vec1.vy = 0x12C;
        DG_PutVector(&vec1, &vec1, 1);
        GM_MoveTarget(lpAct->target, &vec1);
        vec1.vy += 0x96;
        DG_SetPos2(&vec1, &DG_ZeroVector);
        ReadRotMatrix(&lpAct->homMatrix);
        break;

    case 3:
        DG_SetPos2(&DG_ZeroVector, &lpAct->control.rot);
        vec1.vx = 0;
        vec1.vy = lpAct->subcontrol.step.vy;
        vec1.vz = SquareRoot0(lpAct->subcontrol.step.vx * lpAct->subcontrol.step.vx +
                              lpAct->subcontrol.step.vz * lpAct->subcontrol.step.vz);
        DG_PutVector(&vec1, &vec1, 1);
        lpAct->control.mov.vy = s05a_800DEC18(lpAct, &lpAct->control.mov, lpAct->control.mov.vy + vec1.vy);
        lpAct->control.step.vx = vec1.vx;
        lpAct->control.step.vz = vec1.vz;
        vec1 = lpAct->control.mov;
        if (HZD_LevelHazardCheck(lpAct->control.map->hzd, &vec1, HZD_CHK_FLOOR) != 1)
        {
            vec1.vy = 0;
        }
        else
        {
            HZD_GetLevelHeight(lvl);
            vec1.vy = lvl[0];
        }
        if (!lpAct->bFell && lpAct->control.mov.vy - vec1.vy < 0x12C)
        {
            lpAct->bFell = TRUE;
            GM_SeSetPan(&lpAct->control.mov, SE_HIT_FLOOR, lpAct->lpParent->nSoundVolume);
        }
        lpAct->nKageDir = lpAct->control.rot.vy;
        lpAct->nKageHeight = vec1.vy + 100;
        break;

    case 4:
        if (!((GV_Time >> 2) & 1))
        {
            DG_InvisibleObjs(lpAct->body.objs);
        }
        if (lpAct->nFallDelay <= 0)
        {
            GV_DestroyActor(lpAct);
            return;
        }
        break;
    }

    if (lpAct->body.is_end != 0)
    {
        switch (lpAct->body.action)
        {
        case 2:
            GM_ConfigObjectAction(&lpAct->body, 0, 0, 5);
            break;
        case 5:
            GV_DestroyActor(lpAct);
            return;
        case 3:
            lpAct->nFallDelay = 60;
            GM_ConfigObjectAction(&lpAct->body, 4, 0, 5);
            if (!lpAct->bFell)
            {
                lpAct->bFell = TRUE;
                GM_SeSetPan(&lpAct->control.mov, SE_HIT_FLOOR, lpAct->lpParent->nSoundVolume);
            }
            break;
        case 0:
        case 1:
        case 4:
        case 6:
            break;
        }
    }

    if (lpAct->target != NULL)
    {
        if (lpAct->lpParent->field_F5C > 0)
        {
            if (lpAct->lpParent->field_ED0 == 0 && !((GV_Time >> 2) & 1))
            {
                DG_InvisibleObjs(lpAct->body.objs);
            }
            lpAct->target->vital = 0x2710;
            lpAct->target->damage = 0;
            lpAct->target->damaged = 0;
        }
        if (lpAct->target != NULL)
        {
            if (lpAct->target->damaged < lpAct->lpParent->field_D74 / lpAct->lpParent->field_DEC)
            {
                if (lpAct->lpParent->field_D74 / lpAct->lpParent->field_DF0 >= lpAct->lpParent->field_E0C)
                {
                    lpAct->target->vital = 0x2710;
                    lpAct->target->damage = 0;
                    lpAct->target->damaged = 0;
                }
            }
            if (lpAct->target != NULL && lpAct->target->damaged != 0)
            {
                if (lpAct->target->damaged >= lpAct->lpParent->field_D74 / lpAct->lpParent->field_DEC)
                {
                    lpAct->lpParent->field_F5C = lpAct->lpParent->field_E14;
                }
                else
                {
                    lpAct->target->damaged = lpAct->lpParent->field_D74 / lpAct->lpParent->field_DF0;
                    lpAct->lpParent->field_F5C = lpAct->lpParent->field_E18;
                }
                if ((lpAct->lpParent->field_E0C -= lpAct->target->damaged) < 0)
                {
                    lpAct->lpParent->field_E0C = 0;
                }
                lpAct->target->vital = 0x2710;
                lpAct->target->damage = 0;
                lpAct->target->damaged = 0;
                if (lpAct->lpParent->field_E0C > 0)
                {
                    GM_SeSetPan(&lpAct->control.mov, 0x88, lpAct->lpParent->nSoundVolume);
                }
            }
        }
    }

    if (GM_Vitality != 0 && GM_GameOverTimer == 0 && lpAct->target != NULL && lpAct->lpParent->field_E0C <= 0)
    {
        GM_EnemyKillCount++;
        lpAct->lpParent->field_E0C = lpAct->lpParent->field_D74;
        lpAct->bDead = TRUE;
        GM_FreeTarget(lpAct->target);
        lpAct->target = NULL;
        AN_Blast_high(&lpAct->control.mov);
        GM_SeSetPan(&lpAct->control.mov, 0xB1, lpAct->lpParent->nSoundVolume);
        GM_FreeObject(&lpAct->body);
        GM_InitObject(&lpAct->body, GV_StrCode("out_cold"), 0x32D, GV_StrCode("tankman"));
        GM_ConfigObjectJoint(&lpAct->body);
        GM_ConfigMotionControl(&lpAct->body, &lpAct->m_ctrl, GV_StrCode("tankman"), lpAct->m_segs1,
                               lpAct->m_segs2, &lpAct->subcontrol, lpAct->rots);
        GM_ConfigObjectLight(&lpAct->body, &lpAct->light[0]);
        GM_ActMotion(&lpAct->body);
        GM_ActControl(&lpAct->control);
        GM_ActObject(&lpAct->body);
        if (lpAct->lpParent->field_E08 >= 2)
        {
            GM_SeSetPan(&lpAct->control.mov, 0x81, lpAct->lpParent->nSoundVolume);
        }
        else
        {
            GM_SeSetPan(&lpAct->control.mov, 0x84, lpAct->lpParent->nSoundVolume);
        }
        GM_ConfigObjectAction(&lpAct->body, 3, 0, 5);
        vec1.vx = 0;
        vec1.vy = 6;
        vec1.vz = 0xC;
        vec1.pad = 0xF;
        lpAct->lpShadow = NewDemoKage(&lpAct->body, vec1, &lpAct->nKageDir, &lpAct->nKageHeight, 0x80, 0x80, 0x80);
        memset(&vec1, 0, 8);
        vec1.vx = -lpAct->control.mov.vx;
        vec1.vy = -lpAct->control.mov.vy;
        vec1.vz = -lpAct->control.mov.vz;
        lpAct->control.turn.vx = 0;
        lpAct->control.turn.vy = ratan2(vec1.vx, vec1.vz);
        lpAct->control.turn.vz = 0;
        lpAct->field_204 = 0;
    }

    lpAct->nHeight = lpAct->body.height;
    lpAct->lpParent->field_EB4 = lpAct->control.mov;
    lpAct->bHidden = FALSE;
}

static void Die(LPM1E1GUNNERACT lpAct)
{
    lpAct->lpParent->lpGunner = NULL;
    if (lpAct->lpShadow)
    {
        GV_DestroyActor(lpAct->lpShadow);
    }
    GM_FreeObject(&lpAct->body);
    GM_FreeControl(&lpAct->control);
    if (lpAct->target)
    {
        GM_FreeTarget(lpAct->target);
    }
    if (lpAct->hom)
    {
        GM_ResetHomingTarget(lpAct->hom);
    }
}

int s05a_800DEC18(LPM1E1GUNNERACT lpAct, SVECTOR *s2, int a2)
{
    int     v;
    int     heights[2];
    SVECTOR local;

    v = 1;
    if (lpAct->field_204 == 0)
    {
        lpAct->field_208 = 0;
    }

    if (a2 - s2->vy <= 0)
    {
        lpAct->field_204 += s2->vy - a2;
    }
    if (lpAct->field_204 < 0x190)
    {
        return a2;
    }

    if (lpAct->field_208 == 0)
    {
        v = lpAct->m_ctrl.info1.frames_left;
        if (v <= 0)
        {
            v = 1;
        }
    }

    local = *s2;
    local.vy += 0x2710;
    if (HZD_LevelHazardCheck(lpAct->control.map->hzd, &local, HZD_CHK_FLOOR) != 1)
    {
        local.vy = 0;
    }
    else
    {
        HZD_GetLevelHeight(heights);
        local.vy = heights[0];
    }
    local.vy += 0x64;

    if (lpAct->field_208 == 0)
    {
        lpAct->field_208 = (s2->vy - local.vy) / v;
    }

    v = s2->vy - lpAct->field_208;
    if (v < local.vy)
    {
        v = local.vy;
    }
    {
        int t = lpAct->field_208 * 15;
        lpAct->field_208 = t / 14;
    }
    if (lpAct->field_208 >= 0x3E9)
    {
        lpAct->field_208 = 0x3E8;
    }
    return v;
}

void M1E1SoldierBombHoming(CONTROL *control, int fuse_time, u_short *arg3)
{
    int     lvl[2];
    SVECTOR pos;
    SVECTOR tgt;
    SVECTOR mov_d;
    SVECTOR rot_d;
    int     hit;
    int     frames;
    int     d1;
    int     d2;
    int     v;
    int     spd;
    int     q;
    short   h;

    mov_d.vx = s05a_dword_800C362C->control.mov.vx - s05a_dword_800C362C->oldControl.mov.vx;
    mov_d.vy = s05a_dword_800C362C->control.mov.vy - s05a_dword_800C362C->oldControl.mov.vy;
    mov_d.vz = s05a_dword_800C362C->control.mov.vz - s05a_dword_800C362C->oldControl.mov.vz;
    rot_d.vx = s05a_dword_800C362C->control.rot.vx - s05a_dword_800C362C->oldControl.rot.vx;
    rot_d.vy = s05a_dword_800C362C->control.rot.vy - s05a_dword_800C362C->oldControl.rot.vy;
    rot_d.vz = s05a_dword_800C362C->control.rot.vz - s05a_dword_800C362C->oldControl.rot.vz;

    pos = control->mov;
    pos.vy += 0x4B;
    if (HZD_LevelHazardCheckOne(&s05a_dword_800C362C->copy2, &pos) == 1)
    {
        HZD_GetLevelHeight(lvl);
        hit = control->mov.vy - lvl[0];
        if (hit < 0x96)
        {
            DG_SetPos2(&mov_d, &rot_d);
            memset(&pos, 0, 8);
            pos.vy = s05a_dword_800C362C->objBody.rots[3].vy - s05a_dword_800C362C->oldBody.rots[3].vy;
            DG_RotatePos(&pos);
            pos = control->mov;
            pos.vx -= s05a_dword_800C362C->oldControl.mov.vx;
            pos.vy -= s05a_dword_800C362C->oldControl.mov.vy;
            pos.vz -= s05a_dword_800C362C->oldControl.mov.vz;
            DG_PutVector(&pos, &pos, 1);
            pos.vx += s05a_dword_800C362C->oldControl.mov.vx;
            pos.vy += s05a_dword_800C362C->oldControl.mov.vy;
            pos.vz += s05a_dword_800C362C->oldControl.mov.vz;
            hit = HZD_LevelHazardCheckOne(&s05a_dword_800C362C->hzdBlock[4].flr[1], &pos);
            HZD_GetLevelHeight(lvl);
            if (hit & 1)
            {
                control->mov.vy = lvl[0];
            }
            else if (hit & 2)
            {
                control->mov.vy = lvl[1];
            }
            if (hit & 3)
            {
                control->step.vx = pos.vx - control->mov.vx;
                control->step.vz = pos.vz - control->mov.vz;
                return;
            }
        }
    }

    pos = control->mov;
    pos.vy += 0x4B;
    if (HZD_LevelHazardCheckOne(&s05a_dword_800C362C->copy0, &pos) == 1)
    {
        HZD_GetLevelHeight(lvl);
        hit = control->mov.vy - lvl[0];
        if (hit < 0x96)
        {
            DG_SetPos2(&mov_d, &rot_d);
            pos = control->mov;
            pos.vx -= s05a_dword_800C362C->oldControl.mov.vx;
            pos.vy -= s05a_dword_800C362C->oldControl.mov.vy;
            pos.vz -= s05a_dword_800C362C->oldControl.mov.vz;
            DG_PutVector(&pos, &pos, 1);
            pos.vx += s05a_dword_800C362C->oldControl.mov.vx;
            pos.vy += s05a_dword_800C362C->oldControl.mov.vy;
            pos.vz += s05a_dword_800C362C->oldControl.mov.vz;
            hit = HZD_LevelHazardCheckOne(&s05a_dword_800C362C->hzdBlock[0].flr[1], &pos);
            HZD_GetLevelHeight(lvl);
            if (hit & 1)
            {
                control->mov.vy = lvl[0];
            }
            else if (hit & 2)
            {
                control->mov.vy = lvl[1];
            }
            if (hit & 3)
            {
                control->step.vx = pos.vx - control->mov.vx;
                control->step.vz = pos.vz - control->mov.vz;
                return;
            }
        }
    }

    pos = control->mov;
    pos.vy += 0x4B;
    if (HZD_LevelHazardCheckOne(&s05a_dword_800C362C->copy1, &pos) == 1)
    {
        HZD_GetLevelHeight(lvl);
        hit = control->mov.vy - lvl[0];
        if (hit < 0x96)
        {
            DG_SetPos2(&mov_d, &rot_d);
            pos = control->mov;
            pos.vx -= s05a_dword_800C362C->oldControl.mov.vx;
            pos.vy -= s05a_dword_800C362C->oldControl.mov.vy;
            pos.vz -= s05a_dword_800C362C->oldControl.mov.vz;
            DG_PutVector(&pos, &pos, 1);
            pos.vx += s05a_dword_800C362C->oldControl.mov.vx;
            pos.vy += s05a_dword_800C362C->oldControl.mov.vy;
            pos.vz += s05a_dword_800C362C->oldControl.mov.vz;
            hit = HZD_LevelHazardCheckOne(&s05a_dword_800C362C->hzdBlock[1].flr[1], &pos);
            HZD_GetLevelHeight(lvl);
            if (hit & 1)
            {
                control->mov.vy = lvl[0];
            }
            else if (hit & 2)
            {
                control->mov.vy = lvl[1];
            }
            if (hit & 3)
            {
                control->step.vx = pos.vx - control->mov.vx;
                control->step.vz = pos.vz - control->mov.vz;
                return;
            }
        }
    }

    if (*arg3 & 4)
    {
        return;
    }

    tgt.vx = s05a_dword_800C362C->objBody.objs->objs[12].world.t[0];
    tgt.vy = s05a_dword_800C362C->objBody.objs->objs[12].world.t[1];
    tgt.vz = s05a_dword_800C362C->objBody.objs->objs[12].world.t[2];
    pos.vx = (tgt.vx - GM_PlayerControl->mov.vx) >> 2;
    pos.vy = (tgt.vy - GM_PlayerControl->mov.vy) >> 2;
    pos.vz = (tgt.vz - GM_PlayerControl->mov.vz) >> 2;
    memset(&rot_d, 0, 8);
    rot_d.vy = ratan2(pos.vx, pos.vz);
    while (rot_d.vy < -0x800) rot_d.vy += 0x1000;
    while (rot_d.vy >= 0x801) rot_d.vy -= 0x1000;
    hit = SquareRoot0(pos.vx * pos.vx + pos.vz * pos.vz) * 4;

    if (!(*arg3 & 1))
    {
        *arg3 |= 1;
        if (GM_PlayerStatus & 0x340)
        {
            return;
        }
        if (s05a_dword_800C362C->field_DF8 < hit)
        {
            return;
        }
        pos.vy = rot_d.vy - GM_PlayerControl->rot.vy;
        while (pos.vy < -0x800) pos.vy += 0x1000;
        while (pos.vy >= 0x801) pos.vy -= 0x1000;
        if (pos.vy < -s05a_dword_800C362C->field_DF4 || pos.vy > s05a_dword_800C362C->field_DF4)
        {
            return;
        }
        memset(&control->step, 0, 8);
        if (hit <= s05a_dword_800C362C->field_DF8 * 2 / 3)
        {
            control->step.vz = 0x78;
        }
        else
        {
            control->step.vz = 0xAA;
        }
        frames = hit / control->step.vz * 3 / 4;
        h = control->mov.vy;
        if (h < tgt.vy) h = tgt.vy;
        pos.vy = h + 0x3E8;
        d1 = pos.vy - control->mov.vy;
        d2 = pos.vy - tgt.vy;
        v = d1 + d2;
        if (v == 0)
        {
            d1 = 0;
        }
        else
        {
            d1 = frames * d1 / v;
        }
        v = 0;
        if (d1 != 0)
        {
            v = (pos.vy - control->mov.vy) * 2 / d1 / d1;
        }
        control->step.vy = v * d1;
        *arg3 |= v << 8;
        *arg3 |= 2;
    }
    else
    {
        if (!(*arg3 & 2))
        {
            return;
        }
        if (GM_PlayerStatus & 0x300)
        {
            return;
        }
        if (control->mov.vy < s05a_dword_800C362C->objBody.objs->objs[12].world.t[1])
        {
            return;
        }
    }

    memset(&mov_d, 0, 8);
    spd = SquareRoot0(control->step.vx * control->step.vx + control->step.vz * control->step.vz);
    q = hit / fuse_time;
    mov_d.vz = spd;
    if (mov_d.vz < q) mov_d.vz = q;
    DG_SetPos2(&DG_ZeroVector, &rot_d);
    DG_PutVector(&mov_d, &mov_d, 1);
    control->step.vx = mov_d.vx;
    control->step.vz = mov_d.vz;
    control->step.vy += 0x10;
    control->step.vy -= (short)*arg3 >> 8;
}

int M1E1SoldierBombBound(int arg0, SVECTOR *vec, u_short *arg3)
{
    SVECTOR d;
    SVECTOR e;
    int     dist;

    if (arg0 != 0)
    {
        return 0;
    }
    if (s05a_dword_800C362C->lpGunner == NULL)
    {
        return 0;
    }

    d.vx = s05a_dword_800C362C->objBody.objs->objs[12].world.t[0];
    d.vy = s05a_dword_800C362C->objBody.objs->objs[12].world.t[1];
    d.vz = s05a_dword_800C362C->objBody.objs->objs[12].world.t[2];
    d.vx -= vec->vx;
    d.vy -= vec->vy;
    d.vz -= vec->vz;

    e.vx = s05a_dword_800C362C->objBody.objs->objs[10].model->ux -
           s05a_dword_800C362C->objBody.objs->objs[10].model->lx;
    e.vz = s05a_dword_800C362C->objBody.objs->objs[10].model->uz -
           s05a_dword_800C362C->objBody.objs->objs[10].model->lz;
    e.vx = (e.vx + e.vz) >> 2;

    dist = SquareRoot0(d.vx * d.vx + d.vy * d.vy + d.vz * d.vz);
    if (dist < e.vx * s05a_dword_800C362C->field_DFC)
    {
        GM_SeSetPan(&s05a_dword_800C362C->lpGunner->target->center, 0xB2,
                    s05a_dword_800C362C->nSoundVolume);
        *arg3 |= 4;
        return 1;
    }
    return 0;
}

int M1E1SoldierBombExplosion(TARGET *t, int flags)
{
    SVECTOR delta;
    SVECTOR e;
    int     i;
    short   dx, dy, dz;
    int     dist;

    if (s05a_dword_800C362C->field_ED0 != 0)
    {
        if (s05a_dword_800C362C->lpGunner != NULL)
        {
            s05a_dword_800C362C->lpGunner->target->vital = 0x2710;
            s05a_dword_800C362C->lpGunner->target->damage = 0;
            s05a_dword_800C362C->lpGunner->target->damaged = 0;
        }
        for (i = 0; i < 10; i++)
        {
            s05a_dword_800C362C->lpTarget[i]->vital = 0x2710;
            s05a_dword_800C362C->lpTarget[i]->damage = 0;
            s05a_dword_800C362C->lpTarget[i]->damaged = 0;
        }
        return 1;
    }

    if (s05a_dword_800C362C->lpGunner != NULL)
    {
        delta = s05a_dword_800C362C->lpGunner->target->center;
        dx = delta.vx - t->center.vx;
        delta.vx = dx;
        dy = delta.vy - t->center.vy;
        delta.vy = dy;
        dz = delta.vz - t->center.vz;
        delta.vz = dz;

        e.vx = s05a_dword_800C362C->objBody.objs->objs[10].model->ux -
               s05a_dword_800C362C->objBody.objs->objs[10].model->lx;
        e.vz = s05a_dword_800C362C->objBody.objs->objs[10].model->uz -
               s05a_dword_800C362C->objBody.objs->objs[10].model->lz;
        e.vx = (e.vx + e.vz) >> 2;

        if (flags & 4)
        {
            for (i = 0; i < 10; i++)
            {
                s05a_dword_800C362C->lpTarget[i]->vital = 0x2710;
                s05a_dword_800C362C->lpTarget[i]->damage = 0;
                s05a_dword_800C362C->lpTarget[i]->damaged = 0;
            }
            if (s05a_dword_800C362C->field_F5C > 0)
            {
                return 0;
            }
            s05a_dword_800C362C->lpGunner->target->damaged =
                (u_short)s05a_dword_800C362C->field_D74;
            return 1;
        }

        if (s05a_dword_800C362C->lpGunner->target->damaged != 0)
        {
            dist = SquareRoot0(dx * dx + dy * dy + dz * dz);
            if (dist < e.vx * s05a_dword_800C362C->field_DFC * 3 &&
                t->center.vy >=
                    s05a_dword_800C362C->lpGunner->target->center.vy - 0x3E8)
            {
                for (i = 0; i < 10; i++)
                {
                    s05a_dword_800C362C->lpTarget[i]->vital = 0x2710;
                    s05a_dword_800C362C->lpTarget[i]->damage = 0;
                    s05a_dword_800C362C->lpTarget[i]->damaged = 0;
                }
                if (s05a_dword_800C362C->field_F5C > 0)
                {
                    return 0;
                }
                s05a_dword_800C362C->lpGunner->target->damaged =
                    s05a_dword_800C362C->field_D74 / s05a_dword_800C362C->field_DEC;
                return (s05a_dword_800C362C->field_E0C -
                        s05a_dword_800C362C->lpGunner->target->damaged) < 1;
            }
        }

        s05a_dword_800C362C->lpGunner->target->vital = 0x2710;
        s05a_dword_800C362C->lpGunner->target->damage = 0;
        s05a_dword_800C362C->lpGunner->target->damaged = 0;
    }

    if (s05a_dword_800C362C->field_F4C > 0 ||
        s05a_dword_800C362C->field_F50 > 0 ||
        HZD_LevelHazardCheckOne((HZD_FLR *)((char *)s05a_dword_800C362C + 0x12AC), &t->center) == 1 ||
        HZD_LevelHazardCheckOne((HZD_FLR *)((char *)s05a_dword_800C362C + 0x102C), &t->center) == 1 ||
        HZD_LevelHazardCheckOne((HZD_FLR *)((char *)s05a_dword_800C362C + 0x10CC), &t->center) == 1)
    {
        for (i = 0; i < 10; i++)
        {
            s05a_dword_800C362C->lpTarget[i]->vital = 0x2710;
            s05a_dword_800C362C->lpTarget[i]->damage = 0;
            s05a_dword_800C362C->lpTarget[i]->damaged = 0;
        }
        return 0;
    }

    for (i = 0; i < 10; i++)
    {
        dx = s05a_dword_800C362C->lpTarget[i]->center.vx -
             t->center.vx;
        delta.vx = dx;
        dy = s05a_dword_800C362C->lpTarget[i]->center.vy -
             t->center.vy;
        delta.vy = dy;
        dz = s05a_dword_800C362C->lpTarget[i]->center.vz -
             t->center.vz;
        delta.vz = dz;
        if (s05a_dword_800C362C->lpTarget[i]->damaged != 0)
        {
            dist = SquareRoot0(dx * dx + dy * dy + dz * dz);
            if (dist >= 0x9C5)
            {
                s05a_dword_800C362C->lpTarget[i]->vital = 0x2710;
                s05a_dword_800C362C->lpTarget[i]->damage = 0;
                s05a_dword_800C362C->lpTarget[i]->damaged = 0;
            }
        }
    }

    if (s05a_dword_800C362C->field_D64 > s05a_dword_800C362C->field_D88 ||
        s05a_dword_800C362C->field_D68 > s05a_dword_800C362C->field_D8C)
    {
        for (i = 0; i < 10; i++)
        {
            if (s05a_dword_800C362C->lpTarget[i]->damaged != 0)
            {
                return 1;
            }
        }
    }

    return 0;
}

void s05a_800DFFC0(SnaInitWork *work, void *pFn)
{
    short vec_x = 0;
    work->field_9B8_fn_anim = pFn;
    work->field_9BC_anim_frame = 0;
    work->field_A3A = 0;
    work->field_A38_local_data = 0;

    if ((GM_PlayerStatus & PLAYER_GROUND) != 0)
    {
        vec_x = work->field_A2A;
    }

    work->control.turn.vx = vec_x;
    work->control.turn.vz = 0;
}

void s05a_800DFFF8(SnaInitWork *work, int action_flag, int interp)
{
    if (work->body.action != action_flag)
    {
        GM_ConfigObjectAction(&work->body, action_flag, 0, interp);
    }
}

void s05a_800E002C(SnaInitWork *work, int a2, int interp, int a4)
{
    if (work->body.action2 != a2)
    {
        GM_ConfigObjectOverride(&work->body, a2, 0, interp, a4);
    }
}

int s05a_800E0068(int flag)
{
    return (GM_PlayerStatus & flag) != 0;
}

int s05a_800E0080(int flag)
{
    int temp_v0;

    temp_v0 = GM_PlayerStatus | flag;
    GM_PlayerStatus = temp_v0;
    return temp_v0;
}

void s05a_800E0098(int flag)
{
    GM_PlayerStatus &= ~flag;
}

void s05a_800E00B0(SnaInitWork *snake, SnaFlag1 flags)
{
    snake->field_894_flags1 |= flags;
}

void s05a_800E00C4(SnaInitWork *snake, SnaFlag1 flags)
{
    snake->field_894_flags1 &= ~flags;
}

int s05a_800E00D8(SnaInitWork *snake, SnaFlag1 flags)
{
    return (snake->field_894_flags1 & flags) != 0;
}

int M1E1SoldierActControl(GV_ACT *actor)
{
    int      vy = 0;
    SnaInitWork *work = (SnaInitWork *)actor;
    HZD_HDL *lpHazard;
    SVECTOR  pos;
    SVECTOR  rot;
    int      time;
    int      dist;

    GM_uTenageMotion = -1;
    if (HZD_LevelHazardCheckOne(&s05a_dword_800C362C->hzdBlock[0].flr[0], &work->control.mov) == 0 && !(GM_PlayerStatus & 0x1340))
    {
        if (s05a_dword_800C362C->lpGunner != NULL)
        {
            pos = s05a_dword_800C362C->lpGunner->target->center;
        }
        else
        {
            pos = s05a_dword_800C362C->control.mov;
        }
        pos.vx = (pos.vx - work->control.mov.vx) >> 2;
        pos.vy = (pos.vy - work->control.mov.vy) >> 2;
        pos.vz = (pos.vz - work->control.mov.vz) >> 2;
        memset(&rot, 0, 8);
        rot.vy = ratan2(pos.vx, pos.vz);
        while (rot.vy < -0x800) rot.vy += 0x1000;
        while (rot.vy >= 0x801) rot.vy -= 0x1000;
        dist = SquareRoot0(pos.vx * pos.vx + pos.vz * pos.vz) * 4;
        if (s05a_dword_800C362C->field_DF8 >= dist)
        {
            pos.vy = rot.vy - GM_PlayerControl->rot.vy;
            while (pos.vy < -0x800) pos.vy += 0x1000;
            while (pos.vy >= 0x801) pos.vy -= 0x1000;

            if (pos.vy >= -s05a_dword_800C362C->field_DF4 && pos.vy <= -s05a_dword_800C362C->field_DF4 / 2)
            {
                if (dist <= s05a_dword_800C362C->field_DF8 * 2 / 3)
                {
                    GM_uTenageMotion = 2;
                }
                else
                {
                    GM_uTenageMotion = 5;
                }
            }
            else if (pos.vy > -s05a_dword_800C362C->field_DF4 / 2 && pos.vy < s05a_dword_800C362C->field_DF4 / 2)
            {
                if (dist <= s05a_dword_800C362C->field_DF8 * 2 / 3)
                {
                    GM_uTenageMotion = 0;
                }
                else
                {
                    GM_uTenageMotion = 3;
                }
            }
            else if (pos.vy >= s05a_dword_800C362C->field_DF4 / 2 && pos.vy <= s05a_dword_800C362C->field_DF4)
            {
                if (dist <= s05a_dword_800C362C->field_DF8 * 2 / 3)
                {
                    GM_uTenageMotion = 1;
                }
                else
                {
                    GM_uTenageMotion = 4;
                }
            }
        }
        return 0;
    }

    lpHazard = work->control.map->hzd;
    s05a_800E0D38(&work->control, lpHazard);
    GM_CurrentMap = work->control.map->index;

    if (work->control.r_sphere > 0)
    {
        work->control.n_touches = 0;
        if (work->control.hzd_height != -0x7fff)
        {
            vy = work->control.mov.vy;
            work->control.mov.vy = work->control.hzd_height;
        }
        s05a_800E0E28(&work->control, lpHazard);
        work->control.mov.vx += work->control.step.vx;
        work->control.mov.vz += work->control.step.vz;
        s05a_800E0F64(&work->control, lpHazard);
        if (work->control.hzd_height != -0x7fff)
        {
            work->control.mov.vy = vy;
        }
        time = work->control.interp;
        if (work->control.interp == 0)
        {
            GV_NearExp4PV(&work->control.rot.vx, &work->control.turn.vx, 3);
        }
        else
        {
            GV_NearTimePV(&work->control.rot.vx, &work->control.turn.vx, work->control.interp, 3);
            work->control.interp = time - 1;
        }
        s05a_800E1014(&work->control, lpHazard);
    }
    else if (work->control.r_sphere < 0)
    {
        work->control.n_touches = 0;
        time = work->control.interp;
        work->control.mov.vx += work->control.step.vx;
        work->control.mov.vz += work->control.step.vz;
        if (time == 0)
        {
            GV_NearExp4PV(&work->control.rot.vx, &work->control.turn.vx, 3);
        }
        else
        {
            GV_NearTimePV(&work->control.rot.vx, &work->control.turn.vx, time, 3);
            work->control.interp = time - 1;
        }
        if (work->control.r_sphere >= -1)
        {
            s05a_800E1014(&work->control, lpHazard);
        }
    }

    if (!(work->control.skip_flag & CTRL_SKIP_TRAP))
    {
        work->control.evt.coord = work->control.mov;
        work->control.evt.coord.pad = work->control.rot.vy;
        HZD_EnterTrap(lpHazard, &work->control.evt);
    }
    DG_SetPos2(&work->control.mov, &work->control.rot);
    return 1;
}

int M1E1SoldierActObject(SnaInitWork *work_)
{
    SnaInitWork *work = work_;
    int     heights[2];
    SVECTOR size;
    TARGET  target;
    int     hit;
    int     dx, dz, dist;
    int     status;

    if (s05a_dword_800C362C->field_ED0 == 1)
    {
        s05a_dword_800E3800.step.vx = 0;
        s05a_dword_800E3800.step.vy = 0;
        s05a_dword_800E3800.step.vz = 0;
        GM_PlayerControl->mov  = s05a_dword_800E3800.mov;
        GM_PlayerControl->step = s05a_dword_800E3800.step;
        GM_PlayerControl->rot  = s05a_dword_800E3800.rot;
        GM_PlayerControl->turn = s05a_dword_800E3800.turn;
        GM_GameStatus   &= ~STATE_PADRELEASE;
        GM_PlayerStatus &= ~PLAYER_PAD_OFF;
        return 0;
    }
    if (s05a_dword_800C362C->field_ED0 != 0)
    {
        GM_PlayerControl->mov.vx = 0x7530;
        GM_PlayerControl->mov.vy = 0;
        GM_PlayerControl->mov.vz = 0x7530;
        GM_PlayerStatus |= PLAYER_PAD_OFF;
        return 0;
    }

    if (s05a_dword_800C362C->field_D54 == 1 || s05a_dword_800C362C->field_D54 == 6)
    {
        s05a_dword_800E3800 = *GM_PlayerControl;
        return 0;
    }

    if (HZD_LevelHazardCheckOne((HZD_FLR *)&s05a_dword_800C362C->hzdBlock[0].flr[0], &GM_PlayerPosition) != 0)
    {
        if (s05a_dword_800C362C->field_F78 > 0)
        {
            s05a_dword_800C362C->field_F78 = 0x5a;
        }
        hit = HZD_LevelHazardCheck(s05a_dword_800C362C->control.map->hzd, &s05a_dword_800E3800.mov, HZD_CHK_F_FLOOR);
        HZD_GetLevelHeight(heights);
        if (hit & 1)
        {
            s05a_dword_800E3800.mov.vy = heights[0];
        }
        else if (hit & 2)
        {
            s05a_dword_800E3800.mov.vy = heights[1];
        }
        else
        {
            s05a_dword_800E3800.mov.vy = 0;
        }
        s05a_dword_800E3800.step.vx = 0;
        s05a_dword_800E3800.step.vy = 0;
        s05a_dword_800E3800.step.vz = 0;
        s05a_dword_800E3800.mov.vy += 0x64;
        GM_PlayerControl->mov  = s05a_dword_800E3800.mov;
        GM_PlayerControl->step = s05a_dword_800E3800.step;
        GM_PlayerControl->rot  = s05a_dword_800E3800.rot;
        GM_PlayerControl->turn = s05a_dword_800E3800.turn;
        GM_PlayerStatus |= PLAYER_PAD_OFF;
        DG_SetPos2(&GM_PlayerControl->mov, &GM_PlayerControl->rot);

        if ((u_int)(GM_PlayerAction - 0x43) < 2)
        {
            GM_ActObject(&work->body);
            return 1;
        }
        status = GM_PlayerStatus;
        if (status & PLAYER_DOWNED)
        {
            GM_ActObject(&work->body);
            return 1;
        }
        if (GM_Vitality == 0)
        {
            GM_ActObject(&work->body);
            return 1;
        }
        if (GM_GameOverTimer != 0)
        {
            GM_ActObject(&work->body);
            return 1;
        }

        work->field_894_flags1 &= ~1;
        work->field_89C_pTarget->class |= 0x9e;
        GM_PlayerStatus = status & ~(PLAYER_INVINCIBLE | PLAYER_DAMAGED);
        DG_VisibleObjs(work->body.objs);
        size.vx = 0x7d0;
        size.vy = 0x7d0;
        size.vz = 0x7d0;
        memset(&target, 0, sizeof(target));
        GM_SetTarget(&target, 4, ENEMY_SIDE, &size);
        GM_SetPowerTarget(&target, POWER_CONST, ATK_BLAST, s05a_dword_800C362C->field_DA0, 0, &DG_ZeroVector);
        GM_MoveTarget(&target, &GM_PlayerPosition);
        GM_PowerTarget(&target);
        GM_PushTarget(&target);
        if (work->field_89C_pTarget->damaged != 0)
        {
            GM_PlayerStatus |= PLAYER_DOWNED;
            s05a_dword_800C362C->field_F78 = 0x5a;
            GM_SeSetPan(&GM_PlayerPosition, 0xbd, 0x3f);
        }
        return 0;
    }

    size.vy = 0;
    dx = (s05a_dword_800E3800.mov.vx - GM_PlayerControl->mov.vx) >> 2;
    size.vx = dx;
    dz = (s05a_dword_800E3800.mov.vz - GM_PlayerControl->mov.vz) >> 2;
    size.vz = dz;
    dist = SquareRoot0(dx * dx + dz * dz);
    if ((dist << 2) < 0x1f4)
    {
        GM_GameStatus   &= ~STATE_PADRELEASE;
        GM_PlayerStatus &= ~PLAYER_PAD_OFF;
        s05a_dword_800E3800 = *GM_PlayerControl;
        return 0;
    }

    hit = HZD_LevelHazardCheck(s05a_dword_800C362C->control.map->hzd, &s05a_dword_800E3800.mov, HZD_CHK_F_FLOOR);
    HZD_GetLevelHeight(heights);
    if (hit & 1)
    {
        s05a_dword_800E3800.mov.vy = heights[0];
    }
    else if (hit & 2)
    {
        s05a_dword_800E3800.mov.vy = heights[1];
    }
    else
    {
        s05a_dword_800E3800.mov.vy = 0;
    }
    s05a_dword_800E3800.step.vx = 0;
    s05a_dword_800E3800.step.vy = 0;
    s05a_dword_800E3800.step.vz = 0;
    s05a_dword_800E3800.mov.vy += 0x64;
    GM_PlayerControl->mov  = s05a_dword_800E3800.mov;
    GM_PlayerControl->step = s05a_dword_800E3800.step;
    GM_PlayerControl->rot  = s05a_dword_800E3800.rot;
    GM_PlayerControl->turn = s05a_dword_800E3800.turn;
    GM_PlayerStatus |= PLAYER_PAD_OFF;
    DG_SetPos2(&GM_PlayerControl->mov, &GM_PlayerControl->rot);
    GM_ActObject(&work->body);
    return 1;
}

void s05a_800E0D38(CONTROL *control, HZD_HDL *lpHazard)
{
    GV_MSG *msg;
    int     name;
    int     n_msg;
    int     map_msg, move_msg;
    MAP    *map;

    name = control->name;

    if ((name != 0) && !(control->skip_flag & CTRL_SKIP_MESSAGE))
    {
        n_msg = GV_ReceiveMessage(name, &control->msg);
        control->n_msg = n_msg;

        msg = control->msg;

        map_msg = HASH_MAP;
        move_msg = HASH_MOVE2;

        for (n_msg--; n_msg >= 0; n_msg--, msg++)
        {
            if (msg->message[0] == map_msg)
            {
                map = GM_FindMap(msg->message[1]);

                if (map)
                {
                    control->map = map;
                }
            }
            else if (msg->message[0] == move_msg)
            {
                control->mov.vx = msg->message[1];
                control->mov.vy = msg->message[2];
                control->mov.vz = msg->message[3];
            }
        }
    }
}

void s05a_800E0E28(CONTROL *control, HZD_HDL *lpHazard)
{
    SVECTOR local;
    int     half;
    int     dist;
    int     len;
    int     diff;

    half = control->r_sphere / 2;
    dist = control->step.vx;
    if (dist < 0)
    {
        dist = -dist;
    }
    if (control->step.vz > 0)
    {
        dist += control->step.vz;
    }
    else
    {
        dist -= control->step.vz;
    }

    if (half < dist)
    {
        GV_AddVec3(&control->mov, &control->step, &local);
        if (HZD_OnlineHazardCheck(lpHazard, &control->mov, &local, 5, control->seg_flag) != 0)
        {
            control->n_touches = 1;
            control->segs[0] = HZD_GetOnlineHazard();
            control->atrs[0] = HZD_GetOnlineHazardAtr();
            HZD_GetOnlineVector(&control->vecs[0]);
            len = GV_VecLen3(&control->vecs[0]);
            diff = len - half;
            if (diff < 0)
            {
                GV_LenVec3(&control->vecs[0], &local, len, -diff);
                GV_SubVec3(&DG_ZeroVector, &local, &local);
            }
            else
            {
                GV_LenVec3(&control->vecs[0], &local, len, diff);
            }
            control->step = local;
        }
    }
}

void s05a_800E0F64(CONTROL *control, HZD_HDL *lpHazard)
{
    SVECTOR react;
    int     hazard;

    hazard = HZD_NearHazardCheck(lpHazard, &control->mov, 0x1F4, 4, control->seg_flag);
    if (hazard > 0)
    {
        control->n_touches = hazard;
        HZD_GetNearHazard(&control->segs[0]);
        HZX_GetNearHazardAtr(&control->atrs[0]);
        HZD_GetNearVector(&control->vecs[0]);
        HZD_HazardReaction(&control->vecs[0], hazard, control->r_sphere, &react);
        control->mov.vx += react.vx;
        control->mov.vz += react.vz;
    }
}

void s05a_800E1014(CONTROL *control, HZD_HDL *lpHazard)
{
    int height[2];
    int flags;
    int y;
    int base;
    int lo;

    y = control->mov.vy + control->step.vy;
    base = control->height;
    control->grounded = 0;
    flags = HZD_LevelHazardCheck(lpHazard, &control->mov, HZD_CHK_F_FLOOR);
    HZD_GetLevelHeight(height);

    if (flags & HZD_CHK_D_FLOOR)
    {
        if ((unsigned int)(height[1] - control->levels[0] + 0xC7) < 0x18F)
        {
            height[0] = height[1];
            flags &= ~HZD_CHK_D_FLOOR;
        }
    }
    if (!(flags & HZD_CHK_F_FLOOR))
    {
        height[0] = 0;
    }
    if (!(flags & HZD_CHK_D_FLOOR))
    {
        height[1] = 0x7D00;
    }

    lo = base;
    if (flags & HZD_CHK_F_FLOOR)
    {
        lo += height[0];
    }

    if (y < lo)
    {
        y = lo;
        control->grounded = 1;
    }
    else if ((flags & HZD_CHK_D_FLOOR) && height[1] - base < y)
    {
        y = height[1] - base;
        control->grounded = 2;
    }

    control->levels[0] = height[0];
    lo = (control->levels[1] = height[1]);
    control->mov.vy = y;
}
