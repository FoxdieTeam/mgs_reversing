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

#include "bullet/blast.h"       // for AN_Blast_high2
#include "okajima/bullet.h"     // for NewBulletEx
#include "takabe/fadeio.h"      // for NewFadeInOut

extern void *NewSmokeLn_800CDFA4(int a0, int a1, int a2, SVECTOR *p, SVECTOR *q,
                                 SVECTOR *r, char b, char c, char d);

/******************************************************************************
 */

extern LPM1E1ACT s05a_dword_800C362C;
extern int   s05a_dword_800C3630;
extern int   s05a_dword_800C3634;
extern int   s05a_dword_800C3638;

extern void GetHazard2(HZD_SEG *seg, HZD_FLR *flr, MATRIX *pTransform,
                         SVECTOR *pMin, SVECTOR *pMax);
extern void AN_Smoke_800CE08C(SVECTOR *pos);
extern void *NewM1E1Shell(int nName, MATRIX *lpWorld, int nSide, SVECTOR *lpsvectTarget, int nVital, int nLength, int nSpeed, int *lpnResult);
extern void *s05a_800DDCBC(LPM1E1ACT lpParent);

void s05a_800D627C(LPM1E1ACT lpAct);
void s05a_800D797C(LPM1E1ACT lpAct);
void s05a_800D863C(LPM1E1ACT lpAct);
void s05a_800D9754(LPM1E1ACT lpAct);
void s05a_800D9A14(LPM1E1ACT lpAct);
void s05a_800DA02C(LPM1E1ACT lpAct);
void s05a_800DA62C(LPM1E1ACT lpAct);
void s05a_800DA940(LPM1E1ACT lpAct);
void s05a_800DACF0(LPM1E1ACT lpAct);
void s05a_800DD1C8(LPM1E1ACT lpAct);

/******************************************************************************
 */

void s05a_800D4A74(LPM1E1ACT lpAct)
{
    SVECTOR va;         /* sp+0x28 */
    SVECTOR vb;         /* sp+0x30 */
    SVECTOR vc;         /* sp+0x38 */
    int     i;
    int     s0;
    OBJECT *bodyp;

    MENU_Locate(0x50, 0x5a, 0);

    /* control + objBody snapshot */
    memcpy(&lpAct->oldControl, &lpAct->control, sizeof(CONTROL));
    memcpy(&lpAct->oldBody, &lpAct->objBody, sizeof(OBJECT));

    bodyp = &lpAct->objBody;
    lpAct->objBody.rots[10].vy = 0x11c;
    GM_ActMotion(bodyp);

    /* ---- animation/control update ---- */
    lpAct->control.turn.vx += lpAct->field_E9C;
    lpAct->control.turn.vy += lpAct->field_E9E;
    lpAct->control.turn.vz += lpAct->field_EA0;
    GM_ActControl(&lpAct->control);
    GM_ActObject(bodyp);
    for (i = 0; i < 3; i++)
    {
        GM_ActMotion(&lpAct->objLeftCater[i]);
        GM_ActMotion(&lpAct->objRightCater[i]);
    }

    va = lpAct->control.mov;
    va.vy -= lpAct->field_EA4;
    vb.vx = lpAct->control.rot.vx - lpAct->field_E9C;
    vb.vy = lpAct->control.rot.vy - lpAct->field_E9E;
    vb.vz = lpAct->control.rot.vz - lpAct->field_EA0;
    DG_SetPos2(&va, &vb);

    for (i = 0; i < 3; i++)
    {
        GM_ActObject(&lpAct->objLeftCater[i]);
        GM_ActObject(&lpAct->objRightCater[i]);
    }
    DG_GetLightMatrix2(&lpAct->control.mov, lpAct->light);

    if (lpAct->bInitialize == 0)
    {
        lpAct->objBody.objs->flag &= ~0x80;
    }

    if (--lpAct->field_F40 < 0) lpAct->field_F40 = 0;
    if (--lpAct->field_F44 < 0) lpAct->field_F44 = 0;
    if (--lpAct->field_F48 < 0) lpAct->field_F48 = 0;
    if (--lpAct->field_F4C < 0) lpAct->field_F4C = 0;
    if (--lpAct->field_F50 < 0) lpAct->field_F50 = 0;
    if (--lpAct->field_F54 < 0) lpAct->field_F54 = 0;
    if (--lpAct->field_F58 < 0) lpAct->field_F58 = 0;
    if (--lpAct->nLeftCaterSmokeTCount < 0) lpAct->nLeftCaterSmokeTCount = 0;
    if (--lpAct->nRightCaterSmokeTCount < 0) lpAct->nRightCaterSmokeTCount = 0;
    if (--lpAct->field_F5C < 0) lpAct->field_F5C = 0;
    if (--lpAct->field_F68 < 0) lpAct->field_F68 = 0;
    if (--lpAct->field_F6C < 0) lpAct->field_F6C = 0;
    if (--lpAct->nCaterSoundTCount < 0) lpAct->nCaterSoundTCount = 0;
    if (--lpAct->nCaterSoundStartTCount < 0) lpAct->nCaterSoundStartTCount = 0;
    if (--lpAct->field_F78 < 0) lpAct->field_F78 = 0;
    if (--lpAct->field_F80 < 0) lpAct->field_F80 = 0;

    /* ======== EC0 audio state machine ======== */
    if (lpAct->field_EC0 == 1)
    {
        lpAct->field_EC4++;
        lpAct->field_EC8 = 0;
    }
    else if (lpAct->field_EC0 == 2 && !(GM_PlayerStatus & 0x800300))
    {
        if (++lpAct->field_EC8 >= 3)
        {
            lpAct->field_EC8 = 0;
            if (rand() & 3)
                GM_SeSetPan(&lpAct->control.mov, 0x86, lpAct->nSoundVolume);
        }
    }
    else if (lpAct->field_EC0 == 3)
    {
        lpAct->field_EC8 = 0;
    }

    /* snapshot player position into E44/E48/E4C, compute distance + volume */
    if (s05a_dword_800C362C->field_ED0 == 0)
    {
        lpAct->field_E44.vx = GM_PlayerPosition.vx;
        lpAct->field_E44.vy = GM_PlayerPosition.vy;
        lpAct->field_E44.vz = GM_PlayerPosition.vz;
    }
    va.vx = (lpAct->control.mov.vx - lpAct->field_E44.vx) >> 2;
    va.vy = (lpAct->control.mov.vy - lpAct->field_E44.vy) >> 2;
    va.vz = (lpAct->control.mov.vz - lpAct->field_E44.vz) >> 2;
    lpAct->field_E5C = SquareRoot0(va.vx * va.vx + va.vy * va.vy + va.vz * va.vz) << 2;
    lpAct->nSoundVolume = 0x1f;
    {
        int d = lpAct->field_E5C;
        if (d < 0x1f41)
            lpAct->nSoundVolume = 0x3f;
        else if (d < 0x7531)
        {
            int r = 0x3f;
            r -= ((d - 0x1f40) << 5) / 22000;
            lpAct->nSoundVolume = r;
        }
    }

    /* ======== F. D54 transition machine ======== */
    if (lpAct->field_D54 == 1 && lpAct->bInitialize == 0 && lpAct->field_E5C < lpAct->field_DC4)
    {
        lpAct->field_D54 = 2;
    }
    if (lpAct->lpGunner && *(int *)((char *)lpAct->lpGunner + 0x1f0) == 1)
    {
        if (--lpAct->field_E08 <= 0)
        {
            lpAct->field_D54 = 5;
            lpAct->field_F80 = 0x1e;
            NewFadeInOut(FADEIO_MODE_TOWHITE, 0x1e);
        }
        else
        {
            lpAct->field_D54 = 4;
            lpAct->field_F4C = lpAct->field_D78;
        }
    }

    if (lpAct->field_E08 <= 0 && lpAct->field_D54 == 5 && lpAct->field_F80 <= 0)
    {
        GV_DestroyActor(lpAct);
        return;
    }

    if (lpAct->field_F4C <= 0 && lpAct->field_D54 == 4 &&
        lpAct->lpGunner == NULL && lpAct->field_ED0 == 0)
    {
        if (!lpAct->field_D58)
            lpAct->field_D54 = 2;
        else
            lpAct->field_D54 = 7;
        lpAct->field_F5C = lpAct->field_E14;
    }

    /* ======== G. MENU progress bar ======== */
    if (lpAct->field_D54 != 1 && lpAct->field_D54 != 6)
    {
        s0 = ((lpAct->field_E0C + lpAct->field_D74 * (lpAct->field_E08 - 1)) << 10) /
             (lpAct->field_D74 * lpAct->field_D70);
        if (s0 < 0)
            s0 = 0;
        MENU_DrawBar(0x10, 0x1c, lpAct->field_ED8, s0, &lpAct->life_conf);
        lpAct->field_ED8 = s0;
    }

    /* ======== H. memset + 11-call cascade ======== */
    memset(&lpAct->field_E9C, 0, 8);
    *(int *)&lpAct->field_EA4 = 0;
    s05a_800D797C(lpAct);
    s05a_800D863C(lpAct);
    s05a_800D627C(lpAct);
    s05a_800DA02C(lpAct);
    s05a_800DA62C(lpAct);
    s05a_800D9754(lpAct);
    lpAct->control.mov.vy += lpAct->field_EA4;
    s05a_800DA940(lpAct);
    M1E1Caterpiller((LPM1E1ACT)lpAct);
    s05a_800DACF0(lpAct);
    s05a_800DD1C8(lpAct);

    /* ======== I. ED0/EC0/740 reset ======== */
    if (lpAct->field_ED0 == 1)
        lpAct->field_ED0 = 0;
    lpAct->field_EC0 = 0;
    lpAct->bInitialize = 0;
    lpAct->field_E2C = lpAct->field_E30;
    if (lpAct->field_D54 == 6)
        return;

    /* ======== J. Target-power section 1 ======== */
    if (lpAct->field_F78 <= 0)
    {
        for (i = 0; i < 10; i++)
        {
            GM_PowerTarget(&lpAct->field_A84[i]);
            if (lpAct->field_A84[i].vital != lpAct->field_DA0)
            {
                GM_PlayerStatus |= 0x200;
                lpAct->field_F78 = 0x5a;
                GM_SeSetPan(&GM_PlayerPosition, 0xbd, 0x3f);
                break;
            }
        }
        for (i = 0; i < 10; i++)
            lpAct->field_A84[i].vital = lpAct->field_DA0;
    }

    s0 = lpAct->field_E68 - lpAct->field_D9C;
    i = 0;
    if (s0 >= 0)
        i = (lpAct->field_E24 * s0) / lpAct->field_E28 + lpAct->field_D90;

    lpAct->target0.vital = i;
    lpAct->target1.vital = i;
    lpAct->target2.vital = i;
    lpAct->target3.vital = i;
    lpAct->target4.vital = i;
    lpAct->target5.vital = i;
    if (lpAct->field_F78 <= 0 && i > 0)
    {
        int r;
        int d;
        va = lpAct->control.turn;
        while (va.vy < -0x800)
            va.vy += 0x1000;
        while (va.vy >= 0x801)
            va.vy -= 0x1000;
        r = ratan2(lpAct->field_E34.vx, lpAct->field_E34.vz);
        d = va.vy;
        d -= r;
        if (d < 0)
            d = -d;
        d = d < 0x400;
        if (d)
        {
            GM_PowerTarget(&lpAct->target0);
            GM_PowerTarget(&lpAct->target2);
            GM_PowerTarget(&lpAct->target4);
        }
        else
        {
            GM_PowerTarget(&lpAct->target1);
            GM_PowerTarget(&lpAct->target3);
            GM_PowerTarget(&lpAct->target5);
        }
        if (lpAct->target0.vital != i || lpAct->target1.vital != i ||
            lpAct->target2.vital != i || lpAct->target3.vital != i ||
            lpAct->target4.vital != i || lpAct->target5.vital != i)
        {
            GM_PlayerStatus |= 0x200;
            lpAct->field_F78 = 0x5a;
            GM_SeSetPan(&GM_PlayerPosition, 0xbd, 0x3f);
        }
    }

    /* ======== K. Smoke/blast keyed on F4C ======== */
    if (lpAct->field_F4C > 0 && (lpAct->field_F4C & 0xf) == 0)
    {
        DG_SetPos((MATRIX *)&lpAct->objBody.objs->objs[10].world);
        memset(&va, 0, 8);
        DG_PutVector(&va, &va, 1);
        va.vy -= 0x1f4;
        vb = va;
        vb.vy += 0x3e8;
        memset(&vc, 0, 8);
        vc.vy = 0x3e;
        NewSmokeLn_800CDFA4(7, 1, 0, &va, &vb, &vc, 0, 0, 0);
    }

    /* ======== L. Target-power section 2 keyed on F50 ======== */
    if (lpAct->field_F4C <= 0)
    {
        if (lpAct->field_F50 <= 0)
        {
            if (lpAct->field_D64 > lpAct->field_D88 || lpAct->field_D68 > lpAct->field_D8C)
            {
                s0 = 0;
                for (i = 0; i < 10; i++)
                {
                    TARGET *t = lpAct->lpTarget[i];
                    if (t->damaged != 0 && t->damaged >= s0 &&
                        (unsigned int)(t->weapon - 2) < 5)
                    {
                        s0 = t->damaged;
                        lpAct->field_E88 = i;
                        lpAct->field_F50 = lpAct->field_D78 >> 1;
                    }
                }
                if (s0)
                {
                    int dx;
                    dx = (lpAct->field_D7C * s0) / lpAct->field_D84;
                    lpAct->field_D64 -= dx;
                    lpAct->field_D68 -= (lpAct->field_D80 * s0) / lpAct->field_D84;
                    {
                        int lo = lpAct->field_D88;
                        if (lo < lpAct->field_D64)
                            lo = lpAct->field_D64;
                        lpAct->field_D64 = lo;
                    }
                    {
                        int lo = lpAct->field_D8C;
                        if (lo < lpAct->field_D68)
                            lo = lpAct->field_D68;
                        lpAct->field_D68 = lo;
                    }
                    DG_SetPos2(&DG_ZeroVector, &lpAct->control.rot);
                    memset(&va, 0, 8);
                    if (lpAct->field_E88 < 5)
                        va.vy = 0x400;
                    else
                        va.vy = -0x400;
                    DG_RotatePos(&va);
                    memset(&va, 0, 8);
                    va.vz = 0x258;
                    DG_PutVector(&va, &va, 1);
                    AN_Blast_high2(&lpAct->lpTarget[lpAct->field_E88]->center, &va);
                    GM_SeSetPan(&lpAct->control.mov, 0xb1, lpAct->nSoundVolume);
                }
            }
        }
    }

    if (lpAct->field_F50 > 0 && (lpAct->field_F50 & 0xf) == 0)
    {
        va = lpAct->lpTarget[lpAct->field_E88]->center;
        vb = va;
        vb.vy += 0x3e8;
        memset(&vc, 0, 8);
        vc.vy = 0x3e;
        NewSmokeLn_800CDFA4(7, 2, 0, &va, &vb, &vc, 0, 0, 0);
    }

    for (i = 0; i < 10; i++)
    {
        lpAct->lpTarget[i]->vital = 0x2710;
        lpAct->lpTarget[i]->damage = 0;
        lpAct->lpTarget[i]->damaged = 0;
    }

    /* ======== M. Pad-driven 14-case state machine ======== */
    if (GM_ClearFlag == 0)
        return;

    {
        int *p3634 = &s05a_dword_800C3634;

        if (--*p3634 < 0)
        {
            s05a_dword_800C3630 = 0;
            *p3634 = 0;
        }

        if (lpAct->field_D54 == 7)
        {
            if (GV_PadData[1].status == 0xf0)
            {
                lpAct->field_D58 = 0;
                lpAct->field_D54 = 2;
                return;
            }
        }
        else
        {
            if (s05a_dword_800C3630 == 0)
            {
                if (GV_PadData[1].status == 0xf0)
                {
                    s05a_dword_800C3630 = 1;
                    *p3634 = 0x1e;
                    return;
                }
            }

            if ((unsigned int)(s05a_dword_800C3634 - 1) >= 0x1d)
                return;

            if (s05a_dword_800C3630 == 1 && GV_PadData[1].status == 5)
            {
                s05a_dword_800C3630 = 2;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 2 && GV_PadData[1].status == 0xa)
            {
                s05a_dword_800C3630 = 3;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 3 && GV_PadData[1].status == 0xc)
            {
                s05a_dword_800C3630 = 4;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 4 && GV_PadData[1].status == 0x1000)
            {
                s05a_dword_800C3630 = 5;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 5 && GV_PadData[1].status == 0x4000)
            {
                s05a_dword_800C3630 = 6;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 6 && GV_PadData[1].status == 6)
            {
                s05a_dword_800C3630 = 7;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 7 && GV_PadData[1].status == 0x8000)
            {
                s05a_dword_800C3630 = 8;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 8 && GV_PadData[1].status == 0x2000)
            {
                s05a_dword_800C3630 = 9;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 9 && GV_PadData[1].status == 3)
            {
                s05a_dword_800C3630 = 0xa;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 0xa && GV_PadData[1].status == 0xe0)
            {
                s05a_dword_800C3630 = 0xb;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 0xb && GV_PadData[1].status == 0x1000)
            {
                s05a_dword_800C3630 = 0xc;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 0xc && GV_PadData[1].status == 3)
            {
                s05a_dword_800C3630 = 0xd;
                s05a_dword_800C3634 = 0x1e;
            }
            else if (s05a_dword_800C3630 == 0xd && GV_PadData[1].status == 0x90)
            {
                lpAct->field_D58 = 1;
                lpAct->field_D54 = 7;
            }
        }
    }

    /* ======== N. D54==7 final pad input + DG_MakeCameraMatrix + AN_Blast tail ======== */
    if (lpAct->field_D54 == 7)
    {
        u_short pad;
        if (GV_PadData[1].status & 1)
        {
            va.vx = lpAct->field_E44.vx;
            va.vy = lpAct->field_E44.vy;
            va.vz = lpAct->field_E44.vz;
            va.vy += 0x320;
            vb = lpAct->control.mov;
            vb.vx = va.vx + (vb.vx - va.vx) / 3;
            vb.vy = va.vy + (vb.vy - va.vy) / 3;
            vb.vz = va.vz + (vb.vz - va.vz) / 3;
            DG_MakeCameraMatrix(DG_Chanl(0), &va, &vb, 0x140);
            GM_PlayerBody->objs->flag |= 0x80;
            s05a_dword_800C3638 = 1;
        }
        else if (s05a_dword_800C3638 == 1)
        {
            GM_PlayerBody->objs->flag &= ~0x80;
            s05a_dword_800C3638 = 0;
        }

        pad = GV_PadData[1].status;
        if (!(pad & 4))
            return;
        if (pad & 8)
            lpAct->field_F88 += 0x32;
        else if (pad & 2)
            lpAct->field_F88 -= 0x32;

        DG_SetPos((MATRIX *)&lpAct->objBody.objs->objs[6].world);
        memset(&va, 0, 8);
        memset(&vb, 0, 8);
        va.vz = 0x3e8;
        va.vy = 0x3e8;
        vb.vz = 0x7d0;
        vb.vy = lpAct->field_F88 + 0x3e8;
        DG_PutVector(&va, &va, 1);
        DG_PutVector(&vb, &vb, 1);
        DG_MakeCameraMatrix(DG_Chanl(0), &va, &vb, 0x140);
    }
}

void s05a_800D5E30(LPM1E1ACT lpAct)
{
    int i;

    GM_uTenageMotion = -1;
    if (lpAct->lpM1Throw) GV_DestroyActor(lpAct->lpM1Throw);
    GM_lpfnPlayerActControl = 0;
    GM_lpfnPlayerActObject2 = 0;
    GM_lpfnBombHoming = 0;
    GM_lpfnBombBound = 0;
    GM_lpfnBombExplosion = 0;
    if (lpAct->lpGunner) GV_DestroyActor(lpAct->lpGunner);

    if (lpAct->field_E1C >= 0)
    {
        long     argv[5];
        GCL_ARGS args;
        argv[0] = lpAct->field_D64 / 10 * 30 / 100 * 60 / 1000 * 60;
        argv[1] = lpAct->field_D68 * 30;
        argv[2] = lpAct->field_E08;
        argv[3] = lpAct->field_E0C;
        argv[4] = lpAct->field_E10;
        args.argv = argv;
        args.argc = 5;
        GCL_ForceExecProc(lpAct->field_E1C, &args);
    }

    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[0].seg[0]);
    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[0].seg[1]);
    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[0].seg[2]);
    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[0].seg[3]);
    HZD_DequeueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[0].flr[0]);
    HZD_DequeueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[0].flr[1]);
    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[1].seg[0]);
    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[1].seg[1]);
    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[1].seg[2]);
    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[1].seg[3]);
    HZD_DequeueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[1].flr[0]);
    HZD_DequeueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[1].flr[1]);
    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[2].seg[0]);
    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[2].seg[1]);
    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[2].seg[2]);
    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[2].seg[3]);
    HZD_DequeueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[2].flr[0]);
    HZD_DequeueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[2].flr[1]);
    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[3].seg[0]);
    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[3].seg[1]);
    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[3].seg[2]);
    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[3].seg[3]);
    HZD_DequeueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[3].flr[0]);
    HZD_DequeueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[3].flr[1]);
    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[4].seg[0]);
    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[4].seg[1]);
    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[4].seg[2]);
    HZD_DequeueDynamicSegment(lpAct->control.map->hzd, &lpAct->hzdBlock[4].seg[3]);
    HZD_DequeueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[4].flr[0]);
    HZD_DequeueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[4].flr[1]);

    GM_FreeObject(&lpAct->objBody);
    for (i = 0; i < 3; i++)
    {
        GM_FreeObject(&lpAct->objLeftCater[i]);
        GM_FreeObject(&lpAct->objRightCater[i]);
    }
    for (i = 0; i < 8; i++) GM_FreeTarget(lpAct->lpTarget[i]);
    GM_FreeControl(&lpAct->control);
    s05a_dword_800C362C = 0;
    if (lpAct->field_D54 == 5 && lpAct->field_E20 >= 0) GCL_ExecProc(lpAct->field_E20, 0);
}

void s05a_800D627C(LPM1E1ACT lpAct)
{
    int      lvl[2];
    VECTOR   mv;
    VECTOR   tmp;
    SVECTOR  vec;
    SVECTOR  step;
    VECTOR   dir;
    VECTOR   acc;
    int      spd_max = lpAct->field_D68;
    int      accel = lpAct->field_D64;
    int      turn = 0;
    u_int    snd = 0;
    int      quarter;
    int      len;
    int      i;
    int      hit;
    HZD_ZON *zone;
    HZD_ZON *next;
    MAP     *map;
    int      rate;

    lpAct->control.step.vx = 0;
    lpAct->control.step.vz = 0;
    mv.vy = 0;
    if (lpAct->field_E30 == 7)
    {
        mv.vx = (lpAct->field_EA8.vx - lpAct->control.mov.vx) >> 2;
        mv.vz = (lpAct->field_EA8.vz - lpAct->control.mov.vz) >> 2;
    }
    else if (lpAct->field_E30 >= 8 && lpAct->field_E30 <= 10)
    {
        mv.vx = (lpAct->field_E54.vx - lpAct->control.mov.vx) >> 2;
        mv.vz = (lpAct->field_E54.vz - lpAct->control.mov.vz) >> 2;
    }
    else if (lpAct->field_E30 >= 11 && lpAct->field_E30 <= 14)
    {
        spd_max = lpAct->field_D60;
        accel = lpAct->field_D5C;
        mv.vx = (lpAct->field_E54.vx - lpAct->control.mov.vx) >> 2;
        mv.vz = (lpAct->field_E54.vz - lpAct->control.mov.vz) >> 2;
    }
    else
    {
        mv.vx = (lpAct->field_E44.vx - lpAct->control.mov.vx) >> 2;
        mv.vz = (lpAct->field_E44.vz - lpAct->control.mov.vz) >> 2;
    }

    len = SquareRoot0((lpAct->field_E34.vx >> 2) * (lpAct->field_E34.vx >> 2) +
                      (lpAct->field_E34.vy >> 2) * (lpAct->field_E34.vy >> 2) +
                      (lpAct->field_E34.vz >> 2) * (lpAct->field_E34.vz >> 2));
    quarter = spd_max >> 2;
    if (len == 0)
    {
        memset(&dir, 0, 0x10);
    }
    else
    {
        len = (lpAct->field_D6C << 8) / (len << 2);
        dir.vx = (lpAct->field_E34.vx * len) >> 8;
        dir.vy = (lpAct->field_E34.vy * len) >> 8;
        dir.vz = (lpAct->field_E34.vz * len) >> 8;
    }
    memset(&acc, 0, 0x10);
    if (abs(lpAct->field_E34.vx) + abs(lpAct->field_E34.vz) != 0 && abs(dir.vx) + abs(dir.vz) != 0)
    {
        tmp = lpAct->field_E34;
        i = (abs(lpAct->field_E34.vx) + abs(lpAct->field_E34.vz)) / (abs(dir.vx) + abs(dir.vz));
        while (i > 0)
        {
            i--;
            acc.vx += tmp.vx >> 8;
            tmp.vx -= dir.vx;
            acc.vz += tmp.vz >> 8;
            tmp.vz -= dir.vz;
        }
    }

    len = SquareRoot0(mv.vx * mv.vx + mv.vy * mv.vy + mv.vz * mv.vz);
    if (len != 0)
    {
        i = (spd_max << 8) / len;
        mv.vx = (mv.vx * i) >> 8;
        mv.vy = (mv.vy * i) >> 8;
        mv.vz = (mv.vz * i) >> 8;
    }

    switch (lpAct->field_D54)
    {
    case 6:
        lpAct->field_E30 = 0;
        return;
    case 1:
    case 3:
    case 4:
    case 5:
        lpAct->field_E30 = 0;
        break;
    case 2:
        if (lpAct->field_E30 == 5)
        {
            if (lpAct->field_E68 != 0)
            {
                lpAct->field_E30 = 0;
            }
            else
            {
                memset(&mv, 0, 0x10);
                memset(&lpAct->field_E34, 0, 0x10);
                vec.vx = (lpAct->field_E44.vx - lpAct->control.mov.vx) >> 2;
                vec.vy = (lpAct->field_E44.vy - lpAct->control.mov.vy) >> 2;
                vec.vz = (lpAct->field_E44.vz - lpAct->control.mov.vz) >> 2;
                tmp.vy = ratan2(vec.vx, vec.vz);
                vec.vy = lpAct->control.rot.vy + 0x400;
                step.vy = vec.vy - tmp.vy;
                if (step.vy < -0x800) step.vy += 0x1000;
                if (step.vy >= 0x801) step.vy -= 0x1000;
                vec.vy = (short)(lpAct->control.rot.vy - 0x400) - tmp.vy;
                if (vec.vy < -0x800) vec.vy += 0x1000;
                if (vec.vy >= 0x801) vec.vy -= 0x1000;
                if (abs(vec.vy) < abs(step.vy))
                {
                    step.vy = vec.vy;
                }
                step.vy = (step.vy > (-spd_max >> 4)) ? step.vy : (-spd_max >> 4);
                step.vy = (step.vy < (spd_max >> 4)) ? step.vy : (spd_max >> 4);
                turn = step.vy;
                lpAct->control.turn.vy -= step.vy;
                if (lpAct->control.turn.vy < -0x800) lpAct->control.turn.vy += 0x1000;
                if (lpAct->control.turn.vy >= 0x801) lpAct->control.turn.vy -= 0x1000;
            }
        }
        else if (lpAct->field_E30 == 6)
        {
            if (lpAct->field_E68 != 0)
            {
                lpAct->field_E30 = 0;
            }
            else
            {
                memset(&mv, 0, 0x10);
                memset(&lpAct->field_E34, 0, 0x10);
                vec.vx = (lpAct->field_E44.vx - lpAct->control.mov.vx) >> 2;
                vec.vy = (lpAct->field_E44.vy - lpAct->control.mov.vy) >> 2;
                vec.vz = (lpAct->field_E44.vz - lpAct->control.mov.vz) >> 2;
                tmp.vy = ratan2(vec.vx, vec.vz);
                vec.vy = lpAct->control.rot.vy + lpAct->objBody.rots[3].vy + 0x2AA;
                step.vy = vec.vy - tmp.vy;
                if (step.vy < -0x800) step.vy += 0x1000;
                if (step.vy >= 0x801) step.vy -= 0x1000;
                step.vy = (step.vy > (-spd_max >> 4)) ? step.vy : (-spd_max >> 4);
                step.vy = (step.vy < (spd_max >> 4)) ? step.vy : (spd_max >> 4);
                turn = step.vy;
                lpAct->control.turn.vy -= step.vy;
                if (lpAct->control.turn.vy < -0x800) lpAct->control.turn.vy += 0x1000;
                if (lpAct->control.turn.vy >= 0x801) lpAct->control.turn.vy -= 0x1000;
            }
        }
        else if ((lpAct->field_E30 >= 8 && lpAct->field_E30 <= 10) || lpAct->field_E30 == 12 || lpAct->field_E30 == 13 ||
                 lpAct->field_E30 == 14)
        {
            if (len << 2 < 0x7D0)
            {
                lpAct->field_E30 = 0;
            }
        }
        else if (lpAct->field_E30 == 11)
        {
            if (len << 2 < 0x7D0)
            {
                memset(&mv, 0, 0x10);
                memset(&lpAct->field_E34, 0, 0x10);
                vec.vx = (lpAct->field_E44.vx - lpAct->control.mov.vx) >> 2;
                vec.vy = (lpAct->field_E44.vy - lpAct->control.mov.vy) >> 2;
                vec.vz = (lpAct->field_E44.vz - lpAct->control.mov.vz) >> 2;
                tmp.vy = ratan2(vec.vx, vec.vz);
                vec.vy = lpAct->control.rot.vy;
                step.vy = (short)(vec.vy + 0x400) - tmp.vy;
                if (step.vy < -0x800) step.vy += 0x1000;
                if (step.vy >= 0x801) step.vy -= 0x1000;
                step.vy = (step.vy > (-spd_max >> 4)) ? step.vy : (-spd_max >> 4);
                step.vy = (step.vy < (spd_max >> 4)) ? step.vy : (spd_max >> 4);
                turn = step.vy;
                lpAct->control.turn.vy -= step.vy;
                if (lpAct->control.turn.vy < -0x800) lpAct->control.turn.vy += 0x1000;
                if (lpAct->control.turn.vy >= 0x801) lpAct->control.turn.vy -= 0x1000;
            }
        }
        else if (lpAct->field_E30 == 1)
        {
            lpAct->field_E30 = 0;
        }
        else if (lpAct->field_E30 == 2)
        {
            if (quarter < lpAct->field_E68 &&
                mv.vx * lpAct->field_E34.vx + mv.vy * lpAct->field_E34.vy + mv.vz * lpAct->field_E34.vz <= 0)
            {
                lpAct->field_E30 = 0;
            }
        }
        break;
    case 7:
        lpAct->field_E30 = 2;
        len = 0;
        if (!(GV_PadData[1].status & 0x90) || (GV_PadData[1].status & 0x800))
        {
            if (GV_PadData[1].status & 0x1000)
            {
                len = spd_max;
            }
            else if (GV_PadData[1].status & 0x4000)
            {
                len = -spd_max;
            }
            else
            {
                lpAct->field_E30 = 0;
            }
            if (GV_PadData[1].status & 0x8000)
            {
                lpAct->control.turn.vy += spd_max >> 4;
                turn = spd_max >> 4;
            }
            if (GV_PadData[1].status & 0x2000)
            {
                turn = -spd_max >> 4;
                lpAct->control.turn.vy -= spd_max >> 4;
            }
            if (lpAct->control.turn.vy < -0x800) lpAct->control.turn.vy += 0x1000;
            if (lpAct->control.turn.vy >= 0x801) lpAct->control.turn.vy -= 0x1000;
        }
        memset(&vec, 0, 8);
        vec.vy = lpAct->control.turn.vy;
        DG_SetPos2(&DG_ZeroVector, &vec);
        memset(&vec, 0, 8);
        vec.vz = len;
        DG_PutVector(&vec, &vec, 1);
        mv.vx = vec.vx;
        mv.vy = vec.vy;
        mv.vz = vec.vz;
        vec.vy = lpAct->control.turn.vy - ratan2(lpAct->field_E34.vx / 10, lpAct->field_E34.vz / 10);
        while (vec.vy < -0x800) vec.vy += 0x1000;
        while (vec.vy >= 0x801) vec.vy -= 0x1000;
        i = -1;
        if (abs(vec.vy) < 0x400)
        {
            i = 1;
        }
        if (lpAct->field_E30 != 0)
        {
            if (lpAct->field_E68 > 0)
            {
                if (len == 0 || (len > 0 && i == -1) || (len < 0 && i == 1))
                {
                    lpAct->field_E30 = 0;
                }
            }
            if (lpAct->field_E30 != 0)
            {
                memset(&vec, 0, 8);
                vec.vz = SquareRoot0((lpAct->field_E34.vx >> 3) * (lpAct->field_E34.vx >> 3) +
                                     (lpAct->field_E34.vy >> 3) * (lpAct->field_E34.vy >> 3) +
                                     (lpAct->field_E34.vz >> 3) * (lpAct->field_E34.vz >> 3));
                if (len < 0)
                {
                    vec.vz *= -1;
                }
                DG_PutVector(&vec, &vec, 1);
                lpAct->field_E34.vx = vec.vx << 3;
                lpAct->field_E34.vy = vec.vy << 3;
                lpAct->field_E34.vz = vec.vz << 3;
            }
        }
        break;
    }

    if (lpAct->field_E30 == 0)
    {
        if (quarter >= lpAct->field_E68)
        {
            memset(&mv, 0, 0x10);
            memset(&lpAct->field_E34, 0, 0x10);
        }
        else
        {
            mv.vx = -dir.vx;
            mv.vy = -dir.vy;
            mv.vz = -dir.vz;
        }
    }
    else
    {
        if (lpAct->field_E30 == 3)
        {
            mv.vx = -mv.vx;
            mv.vy = -mv.vy;
            mv.vz = -mv.vz;
        }

        vec = lpAct->control.mov;
        vec.vx += acc.vx;
        vec.vz += acc.vz;
        hit = HZD_LevelHazardCheck(lpAct->control.map->hzd, &vec, HZD_CHK_F_FLOOR);
        HZD_GetLevelHeight(lvl);
        if (hit & 1)
        {
            vec.vy = lvl[0];
        }
        else if (hit & 2)
        {
            vec.vy = lvl[1];
        }
        else
        {
            vec.vy = 0;
        }
        vec.vy += 0x2EE;
        zone = &lpAct->control.map->hzd->def->zones[HZD_GetAddress(lpAct->control.map->hzd, &vec, 0xFFFF) & 0xFF];
        if (lpAct->field_E30 < 7 || lpAct->field_E30 > 14)
        {
            memset(&step, 0, 8);
            if (lpAct->control.mov.vx <= zone->x + zone->w && lpAct->control.mov.vx >= zone->x - zone->w)
            {
                if (vec.vx > zone->x + zone->w || vec.vx < zone->x - zone->w)
                {
                    step.vx = mv.vx;
                    mv.vx = -dir.vx;
                }
            }
            if (lpAct->control.mov.vz <= zone->z + zone->h && lpAct->control.mov.vz >= zone->z - zone->h)
            {
                if (vec.vz > zone->z + zone->h || vec.vz < zone->z - zone->h)
                {
                    step.vz = mv.vz;
                    mv.vz = -dir.vz;
                }
            }
            mv.vx += step.vz;
            mv.vz += step.vx;
        }
    }

    lpAct->field_E34.vx += mv.vx;
    lpAct->field_E34.vy += mv.vy;
    lpAct->field_E34.vz += mv.vz;
    len = SquareRoot0((lpAct->field_E34.vx >> 2) * (lpAct->field_E34.vx >> 2) +
                      (lpAct->field_E34.vy >> 2) * (lpAct->field_E34.vy >> 2) +
                      (lpAct->field_E34.vz >> 2) * (lpAct->field_E34.vz >> 2));
    if (len == 0)
    {
        len = 1;
    }
    len = (accel << 8) / (len << 2);
    if (len < 0x100)
    {
        lpAct->field_E34.vx = (lpAct->field_E34.vx * len) >> 8;
        lpAct->field_E34.vy = (lpAct->field_E34.vy * len) >> 8;
        lpAct->field_E34.vz = (lpAct->field_E34.vz * len) >> 8;
    }

    vec = lpAct->control.mov;
    vec.vx += lpAct->field_E34.vx >> 8;
    vec.vy += 0x1F4;
    vec.vz += lpAct->field_E34.vz >> 8;
    zone = &lpAct->control.map->hzd->def->zones[HZD_GetAddress(lpAct->control.map->hzd, &vec, 0xFFFF) & 0xFF];
    if (lpAct->field_E30 == 3)
    {
        if (lpAct->control.mov.vx <= zone->x + zone->w && lpAct->control.mov.vx >= zone->x - zone->w &&
            (vec.vx > zone->x + zone->w || vec.vx < zone->x - zone->w) &&
            lpAct->control.mov.vz <= zone->z + zone->h && lpAct->control.mov.vz >= zone->z - zone->h &&
            (vec.vz > zone->z + zone->h || vec.vz < zone->z - zone->h))
        {
            lpAct->field_E30 = 7;
            for (i = 0; i < sizeof(zone->nears); i++)
            {
                if (zone->nears[i] == 0xFF) break;
            }
            map = lpAct->control.map;
            next = &map->hzd->def->zones[zone->nears[GV_RandU(0x1000) % i]];
            lpAct->field_EA8.vx = next->x;
            lpAct->field_EA8.vy = next->y;
            lpAct->field_EA8.vz = next->z;
        }
    }
    else if (lpAct->field_E30 == 7)
    {
        if (lpAct->control.mov.vx >= lpAct->field_EA8.vx - 0x1F4 && lpAct->control.mov.vx <= lpAct->field_EA8.vx + 0x1F4 &&
            lpAct->control.mov.vz >= lpAct->field_EA8.vz - 0x1F4 && lpAct->control.mov.vz <= lpAct->field_EA8.vz + 0x1F4)
        {
            lpAct->field_E30 = 0;
        }
    }

    step.vx = (vec.vx < zone->x + zone->w) ? vec.vx : zone->x + zone->w;
    step.vx = (step.vx > zone->x - zone->w) ? step.vx : zone->x - zone->w;
    step.vz = (vec.vz < zone->z + zone->h) ? vec.vz : zone->z + zone->h;
    step.vz = (step.vz > zone->z - zone->h) ? step.vz : zone->z - zone->h;
    if (step.vx != vec.vx)
    {
        lpAct->field_E34.vx = 0;
    }
    if (step.vz != vec.vz)
    {
        lpAct->field_E34.vz = 0;
    }

    if (lpAct->field_D54 == 2)
    {
        if (step.vx != lpAct->control.mov.vx || step.vz != lpAct->control.mov.vz)
        {
            i = ratan2(step.vx - lpAct->control.mov.vx, step.vz - lpAct->control.mov.vz);
            lpAct->control.turn.vy = GV_NearSpeed(GV_NearPhase(lpAct->control.turn.vy, i), i, spd_max >> 4);
        }
    }

    step.vx -= lpAct->control.mov.vx;
    step.vz -= lpAct->control.mov.vz;
    lpAct->control.step.vx = step.vx;
    lpAct->control.step.vz = step.vz;
    len = SquareRoot0(step.vx * step.vx + step.vz * step.vz);
    if (lpAct->field_E68 <= 0)
    {
        if (len > 0)
        {
            lpAct->field_F54 = 0xF;
        }
        else if (lpAct->field_E30 == 0 && lpAct->field_E2C != 0)
        {
            lpAct->field_F54 = 0xF;
        }
    }
    else
    {
        if (len <= 0)
        {
            lpAct->field_F54 = 0xF;
        }
        else if (lpAct->field_E30 == 0 && lpAct->field_E2C != 0)
        {
            lpAct->field_F54 = 0xF;
        }
    }

    if (lpAct->field_E6C == 0)
    {
        if (turn != 0) snd = 1;
    }
    else if (turn == 0)
    {
        snd = 2;
    }
    lpAct->field_E6C = turn;
    if (lpAct->field_E68 == 0)
    {
        if (len != 0) snd = 1;
    }
    else if (len == 0)
    {
        snd = 2;
    }
    lpAct->field_E68 = len;
    if (len > 0 || lpAct->field_E30 != lpAct->field_E2C)
    {
        lpAct->field_F7C = 0;
    }
    else
    {
        lpAct->field_F7C++;
    }

    switch (snd)
    {
    case 0:
        if (lpAct->field_F6C < 2)
        {
            if (lpAct->field_E68 == 0 && lpAct->field_E6C == 0)
            {
                if (GV_Time % 5 == 0 || lpAct->field_F6C == 1)
                {
                    GM_SeSetPan(&lpAct->control.mov, 0xB0, lpAct->nSoundVolume);
                }
            }
            else
            {
                rate = spd_max >> 4;
                if (lpAct->field_E6C != 0)
                {
                    len = abs(rate - abs(lpAct->field_E6C)) * 4 / rate + 2;
                }
                else
                {
                    len = abs((spd_max - SquareRoot0(mv.vx * mv.vx + mv.vz * mv.vz)) * 2) / spd_max + 2;
                    len += ((accel >> 8) - lpAct->field_E68) * 2 / (accel >> 8);
                }
                if (len >= 6)
                {
                    len = 5;
                }
                if (GV_Time % len == 0 || lpAct->field_F6C == 1)
                {
                    GM_SeSetPan(&lpAct->control.mov, 0xB4, lpAct->nSoundVolume);
                }
            }
        }
        break;
    case 1:
    case 2:
        lpAct->field_F6C = 6;
        GM_SeSetPan(&lpAct->control.mov, 0xB3, lpAct->nSoundVolume);
        break;
    }
}

void s05a_800D797C(LPM1E1ACT lpAct)
{
    MATRIX   mtx;
    VECTOR   tgt;
    VECTOR   cur;
    VECTOR   pos;
    SVECTOR  v0;
    SVECTOR  v1;
    SVECTOR  vec;
    int      found = 0;
    int      fire = 0;
    int      cnt;
    HZD_TRP *trap;

    if (!(GV_Time & 1))
    {
        vec = lpAct->field_EE0;
    }
    else
    {
        pos = lpAct->field_E44;
        pos.vy = lpAct->field_E44.vy - 0x190;

        DG_SetPos(&lpAct->objBody.objs->objs[0].world);
        v0.vx = lpAct->objBody.objs->objs[3].model->tx;
        v0.vy = lpAct->objBody.objs->objs[3].model->ty;
        v0.vz = lpAct->objBody.objs->objs[3].model->tz;
        DG_MovePos(&v0);
        ReadRotMatrix(&mtx);
        memset(&v0, 0, 8);
        DG_PutVector(&v0, &v0, 1);
        v1.vx = (v0.vx - pos.vx) >> 2;
        v1.vy = (v0.vy - pos.vy) >> 2;
        v1.vz = (v0.vz - pos.vz) >> 2;
        tgt.vy = ratan2(v1.vx, v1.vz);

        v1.vx = 0;
        v1.vy = 0;
        v1.vz = lpAct->objBody.objs->objs[5].model->uz - lpAct->objBody.objs->objs[5].model->lz;
        DG_MovePos(&v1);
        memset(&v1, 0, 8);
        DG_PutVector(&v1, &v1, 1);
        v1.vx = v0.vx - v1.vx;
        v1.vy = v0.vy - v1.vy;
        v1.vz = v0.vz - v1.vz;
        cur.vy = ratan2(v1.vx, v1.vz);

        vec.vx = 0;
        vec.vz = 0;
        vec.vy = tgt.vy - cur.vy;
        if (vec.vy < -0x800) vec.vy += 0x1000;
        if (vec.vy >= 0x801) vec.vy -= 0x1000;
        DG_SetPos(&mtx);
        DG_RotatePos(&vec);

        v0.vx = lpAct->objBody.objs->objs[5].model->tx;
        v0.vy = lpAct->objBody.objs->objs[5].model->ty;
        v0.vz = lpAct->objBody.objs->objs[5].model->tz;
        DG_MovePos(&v0);
        memset(&v0, 0, 8);
        DG_PutVector(&v0, &v0, 1);
        v1.vx = (v0.vx - pos.vx) >> 2;
        v1.vy = (v0.vy - pos.vy) >> 2;
        v1.vz = (v0.vz - pos.vz) >> 2;
        tgt.vx = ratan2(v1.vy, SquareRoot0(v1.vx * v1.vx + v1.vz * v1.vz));

        v1.vx = 0;
        v1.vy = 0;
        v1.vz = lpAct->objBody.objs->objs[5].model->uz - lpAct->objBody.objs->objs[5].model->lz;
        DG_MovePos(&v1);
        memset(&v1, 0, 8);
        DG_PutVector(&v1, &v1, 1);
        v1.vx = v0.vx - v1.vx;
        v1.vy = v0.vy - v1.vy;
        v1.vz = v0.vz - v1.vz;
        cur.vx = ratan2(v1.vy, SquareRoot0(v1.vx * v1.vx + v1.vz * v1.vz));

        vec.vx = tgt.vx - cur.vx;
        DG_SetPos(&mtx);

        if (lpAct->field_D54 == 1 || lpAct->field_D54 == 3 || lpAct->field_D54 == 4 || lpAct->field_D54 == 5 ||
            lpAct->field_D54 == 6 || (GM_GameStatus & 1))
        {
            vec.vy = lpAct->objBody.rots[3].vy;
            vec.vx = lpAct->objBody.rots[5].vx;
        }
        else if (lpAct->field_E30 == 0xB)
        {
            vec.vy = 0;
            vec.vx = 0;
            lpAct->field_E30 = 0;
            s05a_800D9A14(lpAct);
        }
        else if (vec.vx < -0x11C ||
                 (abs(vec.vy) < 0x239 && vec.vx >= 0x3A) ||
                 (abs(vec.vy) >= 0x239 && abs(vec.vy) < 0x5C7 && vec.vx >= 0xE4) ||
                 (abs(vec.vy) >= 0x5C7 && vec.vx > 0))
        {
            if (vec.vx <= 0)
            {
                vec.vx = (vec.vx < -0x11C) ? -0x11C : vec.vx;
            }
            else if (abs(vec.vy) < 0x239)
            {
                if (vec.vx >= 2)
                {
                    vec.vx = 0x39;
                    if (lpAct->field_E30 == 0 || lpAct->field_E30 == 5)
                    {
                        fire = 1;
                    }
                }
            }
            else if (abs(vec.vy) >= 0x239 && abs(vec.vy) < 0x5C7)
            {
                vec.vx = (vec.vx < 0xE4) ? vec.vx : 0xE3;
            }
            else if (abs(vec.vy) >= 0x5C7)
            {
                if (vec.vx >= -0x4A)
                {
                    vec.vx = 0;
                    if (lpAct->field_E30 == 0 || lpAct->field_E30 == 5)
                    {
                        fire = 1;
                    }
                }
            }

            if (lpAct->field_E30 < 7 || lpAct->field_E30 > 11)
            {
                if (fire == 1)
                {
                    lpAct->field_E30 = 5;
                }
                else if (lpAct->field_E30 == 2 && lpAct->field_F7C >= 0x10)
                {
                    lpAct->field_E30 = 5;
                }
                else if (lpAct->field_E30 == 2 && lpAct->field_E5C >= lpAct->field_DC4 * 4 / 5)
                {
                    lpAct->field_E30 = 2;
                }
                else if (lpAct->field_E5C >= lpAct->field_DC4)
                {
                    lpAct->field_E30 = 2;
                }
                else if (lpAct->field_E30 == 5)
                {
                    lpAct->field_E30 = 0;
                }
                s05a_800D9A14(lpAct);
            }
            fire = 0;
        }
        else if (lpAct->field_D54 == 2)
        {
            if (abs(lpAct->objBody.rots[3].vy - vec.vy) < 0xB && abs(lpAct->objBody.rots[5].vx - vec.vx) < 0xB)
            {
                if (lpAct->field_E30 < 7 || lpAct->field_E30 > 11)
                {
                    if (lpAct->field_E5C < lpAct->field_DC4 >> 1)
                    {
                        lpAct->field_E30 = 3;
                    }
                    else if (lpAct->field_E5C >= lpAct->field_DC4)
                    {
                        lpAct->field_E30 = 2;
                    }
                    else
                    {
                        lpAct->field_E30 = 0;
                    }
                    s05a_800D9A14(lpAct);
                }

                {
                HZD_HDL *hzd = lpAct->control.map->hzd;
                HZD_GRP *grp = hzd->grp;
                trap = &grp->triggers->trap;
                cnt = grp->n_triggers - hzd->n_cameras;
                }
                for (; cnt > 0; cnt--, trap++)
                {
                    if (trap->name_id == GV_StrCode("nocannon"))
                    {
                        if (trap->b1.x <= lpAct->field_E44.vx && lpAct->field_E44.vx <= trap->b2.x &&
                            trap->b1.y <= lpAct->field_E44.vy && lpAct->field_E44.vy <= trap->b2.y &&
                            trap->b1.z <= lpAct->field_E44.vz && lpAct->field_E44.vz <= trap->b2.z)
                        {
                            found = 1;
                            break;
                        }
                    }
                }

                if (found == 0 && lpAct->field_F48 <= 0 && lpAct->field_E5C > lpAct->field_DBC &&
                    lpAct->field_E5C < lpAct->field_DC4)
                {
                    fire = 1;
                    lpAct->field_F58 = 0xF;
                    lpAct->field_F48 = lpAct->field_DB8;
                }
            }
        }

        lpAct->field_EE0 = vec;
    }

    if (lpAct->field_D54 == 7 && lpAct->field_F48 <= 0 && (GV_PadData[1].status & 0x20))
    {
        fire = 1;
        lpAct->field_F58 = 0xF;
        lpAct->field_F48 = lpAct->field_DB8;
    }

    if (lpAct->field_D54 != 7 || (GV_PadData[1].status & 0x880) == 0x880)
    {
        cnt = 0xA;
        if (lpAct->field_E00 == 1 && lpAct->field_E5C < lpAct->field_DBC)
        {
            cnt = 6;
        }
        lpAct->objBody.rots[3].vy = GV_NearSpeed(GV_NearPhase(lpAct->objBody.rots[3].vy, vec.vy), vec.vy, cnt);
        lpAct->objBody.rots[5].vx = GV_NearSpeed(GV_NearPhase(lpAct->objBody.rots[5].vx, vec.vx), vec.vx, cnt);
    }
    else if ((GV_PadData[1].status & 0x880) == 0x80)
    {
        if (GV_PadData[1].status & 0x8000) lpAct->objBody.rots[3].vy += 0xA;
        if (GV_PadData[1].status & 0x2000) lpAct->objBody.rots[3].vy -= 0xA;
        if (GV_PadData[1].status & 0x1000) lpAct->objBody.rots[5].vx -= 0xA;
        if (GV_PadData[1].status & 0x4000) lpAct->objBody.rots[5].vx += 0xA;
        if (GV_PadData[1].status & 0x100)
        {
            lpAct->objBody.rots[3].vy = 0;
            lpAct->objBody.rots[5].vx = 0;
        }
    }

    while (lpAct->objBody.rots[3].vy < -0x800) lpAct->objBody.rots[3].vy += 0x1000;
    while (lpAct->objBody.rots[3].vy >= 0x801) lpAct->objBody.rots[3].vy -= 0x1000;

    if (lpAct->objBody.rots[5].vx < -0x11C)
    {
        lpAct->objBody.rots[5].vx = GV_NearSpeed(GV_NearPhase(lpAct->objBody.rots[5].vx, -0x11C), -0x11C, 0xA);
    }
    if (abs(lpAct->objBody.rots[3].vy) < 0x239)
    {
        if (lpAct->objBody.rots[5].vx >= 0x3A)
        {
            lpAct->objBody.rots[5].vx = GV_NearSpeed(GV_NearPhase(lpAct->objBody.rots[5].vx, 0x39), 0x39, 0xA);
        }
    }
    else if (abs(lpAct->objBody.rots[3].vy) >= 0x239 && abs(lpAct->objBody.rots[3].vy) < 0x5C7)
    {
        if (lpAct->objBody.rots[5].vx >= 0xE4)
        {
            lpAct->objBody.rots[5].vx = GV_NearSpeed(GV_NearPhase(lpAct->objBody.rots[5].vx, 0xE3), 0xE3, 0xA);
        }
    }
    else if (abs(lpAct->objBody.rots[3].vy) >= 0x5C7)
    {
        if (lpAct->objBody.rots[5].vx > 0)
        {
            lpAct->objBody.rots[5].vx = GV_NearSpeed(GV_NearPhase(lpAct->objBody.rots[5].vx, 0), 0, 0xA);
        }
    }

    DG_SetPos(&lpAct->objBody.objs->objs[5].world);
    v0.vx = 0;
    v0.vy = 0;
    v0.vz = lpAct->objBody.objs->objs[5].model->uz - lpAct->objBody.objs->objs[5].model->lz;
    DG_MovePos(&v0);
    ReadRotMatrix(&mtx);

    if (fire == 1)
    {
        lpAct->field_ECC++;
        GM_SeSetPan(&lpAct->control.mov, 0xB8, lpAct->nSoundVolume);
        NewM1E1Shell(GV_StrCode("m1e1shel"), &mtx, 2, NULL, lpAct->field_DC0, lpAct->field_DC4 * 2,
                      lpAct->field_DC8, &lpAct->field_EC0);
    }
    else
    {
        if (GM_GameStatus & 2)
        {
            lpAct->field_F68 = 0xF0;
        }
        if (found == 0 && (lpAct->field_F68 > 0 || (!(GM_GameStatus & 1) && lpAct->field_E5C > lpAct->field_DBC)))
        {
            lpAct->field_E64 = 1;
        }
        else
        {
            lpAct->field_E64 = 0;
        }
    }
}

void s05a_800D863C(LPM1E1ACT lpAct)
{
    MATRIX  mtx;
    VECTOR  tgt;
    VECTOR  cur;
    VECTOR  pos;
    SVECTOR v0;
    SVECTOR v1;
    SVECTOR vec;
    int     fire = 0;
    int     k;

    k = 3;
    if (lpAct->field_E08 < 2)
    {
        k = 1;
    }

    if (GV_Time & 1)
    {
        vec = lpAct->field_EE8;
    }
    else
    {
        pos = lpAct->field_E44;

        DG_SetPos(&lpAct->objBody.objs->objs[0].world);
        v0.vx = lpAct->objBody.objs->objs[3].model->tx;
        v0.vy = lpAct->objBody.objs->objs[3].model->ty;
        v0.vz = lpAct->objBody.objs->objs[3].model->tz;
        DG_MovePos(&v0);
        v0 = lpAct->objBody.rots[3];
        DG_RotatePos(&v0);
        v0.vx = lpAct->objBody.objs->objs[12].model->tx;
        v0.vy = lpAct->objBody.objs->objs[12].model->ty;
        v0.vz = lpAct->objBody.objs->objs[12].model->tz;
        DG_MovePos(&v0);
        ReadRotMatrix(&mtx);
        memset(&v0, 0, 8);
        DG_PutVector(&v0, &v0, 1);
        v1.vx = (v0.vx - pos.vx) >> 2;
        v1.vy = (v0.vy - pos.vy) >> 2;
        v1.vz = (v0.vz - pos.vz) >> 2;
        tgt.vy = ratan2(v1.vx, v1.vz);

        v1.vx = 0;
        v1.vy = 0;
        v1.vz = lpAct->objBody.objs->objs[13].model->uz - lpAct->objBody.objs->objs[13].model->lz;
        DG_MovePos(&v1);
        memset(&v1, 0, 8);
        DG_PutVector(&v1, &v1, 1);
        v1.vx = v0.vx - v1.vx;
        v1.vy = v0.vy - v1.vy;
        v1.vz = v0.vz - v1.vz;
        cur.vy = ratan2(v1.vx, v1.vz);

        vec.vx = 0;
        vec.vz = 0;
        vec.vy = tgt.vy - cur.vy;
        if (vec.vy < -0x800) vec.vy += 0x1000;
        if (vec.vy >= 0x801) vec.vy -= 0x1000;
        if (vec.vy < -0x4AB) vec.vy = 0x1000 - vec.vy;
        DG_SetPos(&mtx);
        DG_RotatePos(&vec);

        v0.vx = 0;
        v0.vz = 0;
        v0.vy = lpAct->objBody.objs->objs[13].model->ty;
        DG_MovePos(&v0);
        memset(&v0, 0, 8);
        DG_PutVector(&v0, &v0, 1);
        v1.vx = (v0.vx - pos.vx) >> 2;
        v1.vy = (v0.vy - pos.vy) >> 2;
        v1.vz = (v0.vz - pos.vz) >> 2;
        tgt.vx = ratan2(v1.vy, SquareRoot0(v1.vx * v1.vx + v1.vz * v1.vz));

        v1.vx = 0;
        v1.vy = 0;
        v1.vz = lpAct->objBody.objs->objs[13].model->uz - lpAct->objBody.objs->objs[13].model->lz;
        DG_MovePos(&v1);
        memset(&v1, 0, 8);
        DG_PutVector(&v1, &v1, 1);
        v1.vx = v0.vx - v1.vx;
        v1.vy = v0.vy - v1.vy;
        v1.vz = v0.vz - v1.vz;
        cur.vx = ratan2(v1.vy, SquareRoot0(v1.vx * v1.vx + v1.vz * v1.vz));

        vec.vx = tgt.vx - cur.vx;

        if (lpAct->field_D54 == 1 || lpAct->field_D54 == 3 || lpAct->field_D54 == 4 || lpAct->field_D54 == 5 ||
            lpAct->field_D54 == 6)
        {
            lpAct->field_F40 = 0;
            vec.vy = lpAct->objBody.rots[12].vy + lpAct->objBody.rots[13].vy;
            vec.vx = lpAct->objBody.rots[13].vx;
            if (lpAct->field_D54 == 1)
            {
                lpAct->field_F84 = lpAct->field_DA4 / k;
            }
            else if (lpAct->field_D54 == 4)
            {
                lpAct->field_E10 = 1;
            }
        }
        else if (lpAct->lpGunner != NULL && lpAct->lpGunner->body.action == 6)
        {
            vec.vy = lpAct->objBody.rots[12].vy + lpAct->objBody.rots[13].vy;
            vec.vx = lpAct->objBody.rots[13].vx;
            if (lpAct->lpGunner->body.is_end)
            {
                GM_ConfigObjectAction(&lpAct->lpGunner->body, 0, 0, 5);
            }
        }
        else if (lpAct->field_E64 != 0)
        {
            lpAct->field_F40 = 0;
            vec.vy = lpAct->objBody.rots[12].vy + lpAct->objBody.rots[13].vy;
            vec.vx = lpAct->objBody.rots[13].vx;
            lpAct->objBody.rots[11].vx = GV_NearSpeed(lpAct->objBody.rots[11].vx, 0, 0x2D);
            if (lpAct->objBody.rots[11].vx >= -0xB4 && lpAct->objBody.rots[11].vx < -0x87)
            {
                GM_SeSetPan(&lpAct->control.mov, 0xBB, lpAct->nSoundVolume);
            }
            if (lpAct->lpGunner != NULL)
            {
                if (lpAct->objBody.rots[11].vx == 0)
                {
                    GV_DestroyActor(lpAct->lpGunner);
                }
                else if (lpAct->lpGunner->target != NULL && lpAct->lpGunner->body.action != 5)
                {
                    GM_ConfigObjectAction(&lpAct->lpGunner->body, 5, 0, 5);
                }
            }
            if (lpAct->field_E30 == 6)
            {
                lpAct->field_E30 = 0;
            }
        }
        else if (lpAct->objBody.rots[11].vx != -0x71C || lpAct->lpGunner == NULL || lpAct->lpGunner->body.action == 2)
        {
            if (lpAct->field_E30 < 7 || lpAct->field_E30 > 11)
            {
                lpAct->field_E30 = 3;
            }
            lpAct->field_F40 = 0;
            vec.vy = lpAct->objBody.rots[12].vy + lpAct->objBody.rots[13].vy;
            vec.vx = lpAct->objBody.rots[13].vx;
            lpAct->objBody.rots[11].vx = GV_NearSpeed(lpAct->objBody.rots[11].vx, -0x71C, 0x2D);
            if (lpAct->objBody.rots[11].vx >= -0x695 && lpAct->objBody.rots[11].vx < -0x668)
            {
                GM_SeSetPan(&lpAct->control.mov, 0xBC, lpAct->nSoundVolume);
            }
            if (lpAct->lpGunner == NULL && lpAct->field_E08 > 0)
            {
                lpAct->lpGunner = s05a_800DDCBC(lpAct);
                GM_ConfigObjectAction(&lpAct->lpGunner->body, 2, 0, 5);
            }
        }
        else if (lpAct->field_F84 <= 0 || lpAct->field_DA8 * k < lpAct->field_F44)
        {
            if (lpAct->field_E30 < 7 || lpAct->field_E30 > 11)
            {
                lpAct->field_E30 = 3;
                s05a_800D9A14(lpAct);
            }
            lpAct->field_F40 = 0;
            vec.vy = lpAct->objBody.rots[12].vy + lpAct->objBody.rots[13].vy;
            vec.vx = lpAct->objBody.rots[13].vx;
            if (lpAct->field_F84 <= 0)
            {
                lpAct->field_F84 = lpAct->field_DA4 / k;
                lpAct->field_F44 = 0;
                GM_ConfigObjectAction(&lpAct->lpGunner->body, 6, 0, 5);
            }
        }
        else if (vec.vx < -0x1C7 ||
                 !((vec.vy >= 0x239 && vec.vy <= 0x5C7) ? vec.vx < 0x11D : vec.vx < 0x72) ||
                 vec.vy < -0x238 || vec.vy >= 0x800)
        {
            if (lpAct->field_E30 < 7 || lpAct->field_E30 > 11)
            {
                if (lpAct->field_F40 == 0)
                {
                    lpAct->field_F40 = 0x3F2;
                }
                if (lpAct->field_F78 > 0)
                {
                    lpAct->field_E30 = 3;
                }
                else if (lpAct->field_F40 >= 0x2C7)
                {
                    lpAct->field_E30 = 4;
                }
                else if (lpAct->field_F40 < 0xD3)
                {
                    lpAct->field_E30 = 1;
                }
                else
                {
                    lpAct->field_E30 = 3;
                }
                if ((GM_GameStatus & 1) && lpAct->field_F84 > 0 && lpAct->field_E30 != 1)
                {
                    lpAct->field_E30 = 6;
                }
                s05a_800D9A14(lpAct);
            }
            vec.vy = (vec.vy < -0x238) ? -0x238 : vec.vy;
            vec.vy = (vec.vy < 0x800) ? vec.vy : 0x7FF;
            if (vec.vx <= 0)
            {
                vec.vx = (vec.vx < -0x1C7) ? -0x1C7 : vec.vx;
            }
            else if (vec.vy >= 0x239 && vec.vy <= 0x5C7)
            {
                vec.vx = (vec.vx < 0x11D) ? vec.vx : 0x11C;
            }
            else
            {
                vec.vx = (vec.vx < 0x72) ? vec.vx : 0x71;
            }
            GM_ConfigObjectAction(&lpAct->lpGunner->body, 0, 0, 5);
        }
        else if (lpAct->field_E64 == 0 && lpAct->field_D54 == 2)
        {
            if (abs(lpAct->objBody.rots[12].vy + lpAct->objBody.rots[13].vy - vec.vy) < 0x31C * k &&
                abs(lpAct->objBody.rots[13].vx - vec.vx) < 0x155 * k)
            {
                if (lpAct->field_E30 < 7 || lpAct->field_E30 > 11)
                {
                    if (lpAct->field_F40 <= 0)
                    {
                        if (lpAct->field_F78 > 0)
                        {
                            lpAct->field_E30 = 3;
                        }
                        else if (lpAct->field_E5C < lpAct->field_DC4 >> 1)
                        {
                            lpAct->field_E30 = 3;
                        }
                        else if (lpAct->field_E5C >= lpAct->field_DB0)
                        {
                            lpAct->field_E30 = 2;
                        }
                        else
                        {
                            lpAct->field_E30 = 1;
                        }
                        if (GM_GameStatus & 1)
                        {
                            if (lpAct->field_E30 != 1)
                            {
                                lpAct->field_E30 = 6;
                            }
                            else
                            {
                                lpAct->field_F40 = 0xD2;
                            }
                        }
                        else if (lpAct->field_E30 == 1)
                        {
                            lpAct->field_F40 = 0xD2;
                        }
                        s05a_800D9A14(lpAct);
                    }
                }
                if (lpAct->field_F44 <= 0 && lpAct->field_E5C < lpAct->field_DB0)
                {
                    fire = 1;
                    lpAct->field_F44 = lpAct->field_DA8;
                    lpAct->field_F84--;
                    GM_ConfigObjectAction(&lpAct->lpGunner->body, 1, 0, 5);
                }
                if (lpAct->lpGunner->body.is_end)
                {
                    GM_ConfigObjectAction(&lpAct->lpGunner->body, 0, 0, 5);
                }
            }
        }

        lpAct->field_EE8 = vec;
    }

    if (lpAct->lpGunner != NULL && lpAct->lpGunner->body.action == 6 && lpAct->lpGunner->body.is_end)
    {
        GM_ConfigObjectAction(&lpAct->lpGunner->body, 0, 0, 5);
    }

    if (lpAct->field_D54 == 7)
    {
        if (lpAct->field_F44 <= 0 && (GV_PadData[1].status & 0x40))
        {
            fire = 1;
            lpAct->field_F44 = lpAct->field_DA8;
            lpAct->field_F84--;
            if (lpAct->lpGunner != NULL)
            {
                GM_ConfigObjectAction(&lpAct->lpGunner->body, 1, 0, 5);
            }
        }
        if (lpAct->lpGunner != NULL && lpAct->lpGunner->body.is_end)
        {
            GM_ConfigObjectAction(&lpAct->lpGunner->body, 0, 0, 5);
        }
    }

    if (lpAct->field_D54 != 7 || (GV_PadData[1].status & 0x810) == 0x810)
    {
        v1.vy = vec.vy;
        v1.vy = (v1.vy < -0xE3) ? -0xE3 : v1.vy;
        v1.vy = (v1.vy < 0xE4) ? v1.vy : 0xE3;
        vec.vy -= v1.vy;
        vec.vy = (vec.vy < -0x155) ? -0x155 : vec.vy;
        vec.vy = (vec.vy < 0x71D) ? vec.vy : 0x71C;
        lpAct->objBody.rots[12].vy = GV_NearSpeed(lpAct->objBody.rots[12].vy, vec.vy, 0x17 / k);
        lpAct->objBody.rots[13].vy = GV_NearSpeed(GV_NearPhase(lpAct->objBody.rots[13].vy, v1.vy), v1.vy, 0x2E / k);
        lpAct->objBody.rots[13].vx = GV_NearSpeed(GV_NearPhase(lpAct->objBody.rots[13].vx, vec.vx), vec.vx, 0x2E / k);
    }
    else if ((GV_PadData[1].status & 0x810) == 0x10)
    {
        if (GV_PadData[1].status & 8) lpAct->objBody.rots[12].vy += 0x17;
        if (GV_PadData[1].status & 2) lpAct->objBody.rots[12].vy -= 0x17;
        if (GV_PadData[1].status & 0x8000) lpAct->objBody.rots[13].vy += 0x2E;
        if (GV_PadData[1].status & 0x2000) lpAct->objBody.rots[13].vy -= 0x2E;
        if (GV_PadData[1].status & 0x1000) lpAct->objBody.rots[13].vx -= 0x2E;
        if (GV_PadData[1].status & 0x4000) lpAct->objBody.rots[13].vx += 0x2E;
        if (GV_PadData[1].status & 0x100)
        {
            lpAct->objBody.rots[12].vy = 0;
            lpAct->objBody.rots[13].vy = 0;
            lpAct->objBody.rots[13].vx = 0;
        }
    }

    if (lpAct->objBody.rots[12].vy < -0x155)
    {
        lpAct->objBody.rots[12].vy = GV_NearSpeed(GV_NearPhase(lpAct->objBody.rots[12].vy, -0x155), -0x155, 0x17);
    }
    if (lpAct->objBody.rots[12].vy >= 0x71D)
    {
        lpAct->objBody.rots[12].vy = GV_NearSpeed(GV_NearPhase(lpAct->objBody.rots[12].vy, 0x71C), 0x71C, 0x17);
    }
    if (lpAct->objBody.rots[13].vy < -0xE3)
    {
        lpAct->objBody.rots[13].vy = GV_NearSpeed(GV_NearPhase(lpAct->objBody.rots[13].vy, -0xE3), -0xE3, 0x2E);
    }
    if (lpAct->objBody.rots[13].vy >= 0xE4)
    {
        lpAct->objBody.rots[13].vy = GV_NearSpeed(GV_NearPhase(lpAct->objBody.rots[13].vy, 0xE3), 0xE3, 0x2E);
    }
    if (lpAct->objBody.rots[13].vx < -0x1C7)
    {
        lpAct->objBody.rots[13].vx = GV_NearSpeed(GV_NearPhase(lpAct->objBody.rots[13].vx, -0x1C7), -0x1C7, 0x2E);
    }
    if (lpAct->objBody.rots[12].vy >= 0x239 && lpAct->objBody.rots[12].vy <= 0x5C7)
    {
        if (lpAct->objBody.rots[13].vx >= 0x11D)
        {
            lpAct->objBody.rots[13].vx = GV_NearSpeed(GV_NearPhase(lpAct->objBody.rots[13].vx, 0x11C), 0x11C, 0x2E);
        }
    }
    else if (lpAct->objBody.rots[13].vx >= 0x72)
    {
        lpAct->objBody.rots[13].vx = GV_NearSpeed(GV_NearPhase(lpAct->objBody.rots[13].vx, 0x71), 0x71, 0x2E);
    }

    DG_SetPos(&lpAct->objBody.objs->objs[13].world);
    v0.vx = 0;
    v0.vy = 0;
    v0.vz = lpAct->objBody.objs->objs[13].model->uz - lpAct->objBody.objs->objs[13].model->lz;
    DG_MovePos(&v0);
    ReadRotMatrix(&mtx);

    if (fire == 0)
    {
        lpAct->field_ED4++;
    }
    else
    {
        lpAct->field_ED4 = 0;
        GM_SeSetPan(&lpAct->control.mov, 0xB9, lpAct->nSoundVolume);
        NewBulletEx(0x620, &mtx, 2, 1, 0, 0x28, lpAct->field_DAC, lpAct->field_DB0, lpAct->field_DB4);
    }
}

void s05a_800D9754(LPM1E1ACT lpAct)
{
    SVECTOR vec;
    int     s0;

    if (lpAct->field_F58 <= 0) return;
    if (lpAct->field_F58 >= 0xF)
    {
        DG_SetPos2(&lpAct->control.mov, &lpAct->control.turn);
        memset(&vec, 0, 8); vec.vy = *(u_short *)&lpAct->bbox[1].vy; vec.vz = (short)*(u_short *)&lpAct->bbox[0].vz >> 1;
        DG_PutVector(&vec, &vec, 1); AN_Smoke_800CE08C(&vec);
        memset(&vec, 0, 8); vec.vy = *(u_short *)&lpAct->bbox[1].vy; vec.vz = (short)*(u_short *)&lpAct->bbox[1].vz >> 1;
        DG_PutVector(&vec, &vec, 1); AN_Smoke_800CE08C(&vec);
        memset(&vec, 0, 8);
        vec.vx = *(u_short *)((char *)lpAct->objBody.objs->objs[1].model + 0x20);
        vec.vy = *(u_short *)((char *)lpAct->objBody.objs->objs[1].model + 0x24) + (*(u_short *)&lpAct->bbox[9].vy - *(u_short *)&lpAct->bbox[8].vy);
        vec.vz = *(u_short *)((char *)lpAct->objBody.objs->objs[1].model + 0x28);
        DG_PutVector(&vec, &vec, 1); AN_Smoke_800CE08C(&vec);
    }
    s0 = lpAct->field_F58 - 0xA;
    {
        int d;
        if (s0 >= 0) { d = 5; s0 = 5 - s0; } else { d = 0xA; s0 = lpAct->field_F58; }
        s0 = s0 * 34 / d;
    }
    memset(&vec, 0, 8); vec.vx = s0; DG_SetPos2(&DG_ZeroVector, &vec);
    DG_RotatePos(&lpAct->objBody.rots[3]);
    {
        int dist, r;
        short pv[3];
        memset(&vec, 0, 8); vec.vz = 0x64; DG_PutVector(&vec, &vec, 1);
        dist = SquareRoot0(vec.vx * vec.vx + vec.vz * vec.vz); r = ratan2(vec.vy, dist);
        pv[0] = r;
        r = (short)r; if (r < 0) r = -r; pv[2] = s0 - r;
        s0 = lpAct->objBody.rots[3].vy;
        while (s0 < 0) s0 += 0x1000;
        while (s0 >= 0x1001) s0 -= 0x1000;
        if (s0 >= 0x801) pv[2] = -pv[2];
        lpAct->field_E9C += pv[0];
        lpAct->field_EA0 += pv[2];
    }
}

void s05a_800D9A14(LPM1E1ACT lpAct)
{
    int      cnt;
    HZD_TRP *trap;
    HZD_DEF *def;
    HZD_PAT *route;
    SVECTOR  d;
    int      dist, thr, s5;

    {
    HZD_HDL *hzd = lpAct->control.map->hzd;
    HZD_GRP *grp = hzd->grp;
    trap = &grp->triggers->trap;
    cnt = grp->n_triggers - hzd->n_cameras;
    }
    for (; cnt > 0; cnt--, trap++)
    {
        if (trap->name_id == GV_StrCode("drive4"))
        {
            if (trap->b1.x <= lpAct->field_E44.vx && lpAct->field_E44.vx <= trap->b2.x &&
                trap->b1.y <= lpAct->field_E44.vy && lpAct->field_E44.vy <= trap->b2.y &&
                trap->b1.z <= lpAct->field_E44.vz && lpAct->field_E44.vz <= trap->b2.z)
                break;
        }
        if (lpAct->field_F78 > 0)
        {
            if (trap->name_id == GV_StrCode("drive5") ||
                trap->name_id == GV_StrCode("drive6") ||
                trap->name_id == GV_StrCode("drive7"))
            {
                if (trap->b1.x <= lpAct->field_E44.vx && lpAct->field_E44.vx <= trap->b2.x &&
                    trap->b1.y <= lpAct->field_E44.vy && lpAct->field_E44.vy <= trap->b2.y &&
                    trap->b1.z <= lpAct->field_E44.vz && lpAct->field_E44.vz <= trap->b2.z)
                    break;
            }
        }
    }

    if (cnt <= 0)
    {
        HZD_HDL *hzd = lpAct->control.map->hzd;
        HZD_GRP *grp = hzd->grp;
        trap = &grp->triggers->trap;
        cnt = grp->n_triggers - hzd->n_cameras;
        if (cnt <= 0) return;
        for (; cnt > 0; cnt--, trap++)
        {
            if (lpAct->field_E08 < 2 && lpAct->field_E64 == 0)
            {
                if (trap->name_id == GV_StrCode("drive1") ||
                    trap->name_id == GV_StrCode("drive2") ||
                    trap->name_id == GV_StrCode("drive3"))
                {
                    if (trap->b1.x <= lpAct->control.mov.vx && lpAct->control.mov.vx <= trap->b2.x &&
                        trap->b1.y <= lpAct->control.mov.vy && lpAct->control.mov.vy <= trap->b2.y &&
                        trap->b1.z <= lpAct->control.mov.vz && lpAct->control.mov.vz <= trap->b2.z)
                        break;
                }
            }
        }
        if (cnt <= 0) return;
    }

    /* phase 3: dispatch found trap's name_id -> field_E30 + route */
    def = lpAct->control.map->hzd->def;
    route = def->routes;
    if (trap->name_id == GV_StrCode("drive1")) { lpAct->field_E30 = 8; }
    else if (trap->name_id == GV_StrCode("drive2")) { lpAct->field_E30 = 9; route += 1; }
    else if (trap->name_id == GV_StrCode("drive3")) { lpAct->field_E30 = 0xA; route += 2; }
    else if (trap->name_id == GV_StrCode("drive4")) { lpAct->field_E30 = 0xB; route += 3; }
    else if (trap->name_id == GV_StrCode("drive5")) { lpAct->field_E30 = 0xC; route += 4; }
    else if (trap->name_id == GV_StrCode("drive6")) { lpAct->field_E30 = 0xD; route += 5; }
    else if (trap->name_id == GV_StrCode("drive7")) { lpAct->field_E30 = 0xE; route += 6; }

    /* phase 4: initial distance target->route->points[0] */
    d.vx = (lpAct->control.mov.vx - route->points->x) >> 2;
    d.vy = (lpAct->control.mov.vy - route->points->y) >> 2;
    d.vz = (lpAct->control.mov.vz - route->points->z) >> 2;
    dist = SquareRoot0(d.vx * d.vx + d.vy * d.vy + d.vz * d.vz);
    cnt = 1;
    thr = (dist << 2) - 0x7d0;
    s5 = 0xbb8;

    /* phase 5: find nearest patrol point */
    {
        HZD_PTP *cur = route->points + 1;
        if (cnt < route->n_points)
        do
        {
            d.vx = (route->points[0].x - cur->x) >> 2;
            d.vy = (route->points[0].y - cur->y) >> 2;
            d.vz = (route->points[0].z - cur->z) >> 2;
            dist = SquareRoot0(d.vx * d.vx + d.vy * d.vy + d.vz * d.vz);
            if ((dist << 2) >= thr)
                break;
            if (cur->x - s5 <= lpAct->control.mov.vx &&
                lpAct->control.mov.vx <= cur->x + s5 &&
                cur->z - s5 <= lpAct->control.mov.vz &&
                lpAct->control.mov.vz <= cur->z + s5)
                break;
            cnt++;
            cur++;
        } while (cnt < route->n_points);
    }

    /* phase 6: store chosen point */
    cnt--;
    lpAct->field_E54.vx = route->points[cnt].x;
    lpAct->field_E54.vy = route->points[cnt].y;
    lpAct->field_E54.vz = route->points[cnt].z;
}

#define HZD_FLOOR(v)                                            \
    if (HZD_LevelHazardCheck(lpAct->control.map->hzd, (v), HZD_CHK_F_FLOOR) != 1) \
    {                                                           \
        (v)->vy = 0;                                            \
    }                                                           \
    else                                                        \
    {                                                           \
        HZD_GetLevelHeight(levels);                             \
        (v)->vy = levels[0];                                    \
    }

void s05a_800DA02C(LPM1E1ACT lpAct)
{
    int     levels[2];
    SVECTOR mov;
    SVECTOR turn;
    SVECTOR verts[10];
    SVECTOR mid[4];

    mov = lpAct->control.mov;
    mov.vy = mov.vy + *(u_short *)&lpAct->objBody.objs->def->uy;
    turn.vx = 0;
    turn.vy = lpAct->control.turn.vy;
    turn.vz = 0;
    DG_SetPos2(&mov, &turn);

    M1E1GetCaterpillerVertex(&lpAct->objLeftCater[0], &lpAct->objRightCater[0], verts, 1);
    DG_PutVector(verts, verts, 10);

    if ((GV_Time & 1) == 0)
    {
        verts[0].vy = lpAct->field_EF0[0].vy;
        verts[1].vy = lpAct->field_EF0[1].vy;
        verts[2].vy = lpAct->field_EF0[2].vy;
        verts[3].vy = lpAct->field_EF0[3].vy;
        verts[4].vy = lpAct->field_EF0[4].vy;
    }
    else
    {
        HZD_FLOOR(&verts[0]);
        HZD_FLOOR(&verts[1]);
        HZD_FLOOR(&verts[3]);
        HZD_FLOOR(&verts[4]);
        lpAct->field_EF0[0].vy = verts[0].vy;
        lpAct->field_EF0[1].vy = verts[1].vy;
        lpAct->field_EF0[2].vy = verts[2].vy;
        lpAct->field_EF0[3].vy = verts[3].vy;
        lpAct->field_EF0[4].vy = verts[4].vy;
    }

    {
        SVECTOR *r = &verts[5];
        if (GV_Time & 1)
        {
            verts[5].vy = lpAct->field_EF0[5].vy;
            verts[6].vy = lpAct->field_EF0[6].vy;
            verts[7].vy = lpAct->field_EF0[7].vy;
            verts[8].vy = lpAct->field_EF0[8].vy;
            verts[9].vy = lpAct->field_EF0[9].vy;
        }
        else
        {
            if (HZD_LevelHazardCheck(lpAct->control.map->hzd, r, HZD_CHK_F_FLOOR) != 1)
            {
                verts[5].vy = 0;
            }
            else
            {
                HZD_GetLevelHeight(levels);
                verts[5].vy = levels[0];
            }
            HZD_FLOOR(&verts[6]);
            HZD_FLOOR(&verts[8]);
            HZD_FLOOR(&verts[9]);
            lpAct->field_EF0[5].vy = verts[5].vy;
            lpAct->field_EF0[6].vy = verts[6].vy;
            lpAct->field_EF0[7].vy = verts[7].vy;
            lpAct->field_EF0[8].vy = verts[8].vy;
            lpAct->field_EF0[9].vy = verts[9].vy;
        }
    }

    {
    SVECTOR *mp = mid;
    int i = 0;
    mid[0].vx = (verts[0].vx + verts[1].vx) >> 1;
    mid[0].vy = (verts[0].vy + verts[1].vy) >> 1;
    mid[0].vz = (verts[0].vz + verts[1].vz) >> 1;
    mid[1].vx = (verts[3].vx + verts[4].vx) >> 1;
    mid[1].vy = (verts[3].vy + verts[4].vy) >> 1;
    mid[1].vz = (verts[3].vz + verts[4].vz) >> 1;
    mid[2].vx = (verts[5].vx + verts[6].vx) >> 1;
    mid[2].vy = (verts[5].vy + verts[6].vy) >> 1;
    mid[2].vz = (verts[5].vz + verts[6].vz) >> 1;
    mid[3].vx = (verts[8].vx + verts[9].vx) >> 1;
    mid[3].vy = (verts[8].vy + verts[9].vy) >> 1;
    mid[3].vz = (verts[8].vz + verts[9].vz) >> 1;

    lpAct->control.mov.vy = 0;
    for (i = 0; i < 4; i++)
    {
        lpAct->control.mov.vy = lpAct->control.mov.vy + mp[i].vy;
    }
    lpAct->control.mov.vy = (short)lpAct->control.mov.vy >> 2;
    }

    mov.vx = (mid[1].vx + mid[3].vx) - (mid[0].vx + mid[2].vx);
    mov.vy = (mid[1].vy + mid[3].vy) - (mid[0].vy + mid[2].vy);
    mov.vz = (mid[1].vz + mid[3].vz) - (mid[0].vz + mid[2].vz);
    lpAct->control.turn.vx = ratan2(mov.vy, SquareRoot0(mov.vx * mov.vx + mov.vz * mov.vz));

    mov.vx = (mid[0].vx + mid[1].vx) - (mid[2].vx + mid[3].vx);
    mov.vy = (mid[0].vy + mid[1].vy) - (mid[2].vy + mid[3].vy);
    mov.vz = (mid[0].vz + mid[1].vz) - (mid[2].vz + mid[3].vz);
    lpAct->control.turn.vz = ratan2(mov.vy, SquareRoot0(mov.vx * mov.vx + mov.vz * mov.vz));
}

void s05a_800DA62C(LPM1E1ACT lpAct)
{
    SVECTOR vec;
    SVECTOR rot;
    int     s0;
    int     d;
    int     r;
    int     v;

    if (lpAct->field_E30 == 0)
    {
        if (lpAct->field_E68 > 0)
        {
            s0 = lpAct->field_F54 - 10;
            d = 5;
            if (s0 < 0)
            {
                if (s0 >= -5)
                {
                    lpAct->field_E70 = s0 * 17 / d;
                }
            }
            else
            {
                v = lpAct->field_E70 * s0;
                lpAct->field_E70 = v / d;
            }
        }
        else
        {
            s0 = lpAct->field_F54 - 5;
            d = 10;
            if (s0 >= 0)
            {
                v = lpAct->field_E70 * s0;
                lpAct->field_E70 = v / d;
            }
        }
    }
    else
    {
        if (lpAct->field_E68 > 0)
        {
            s0 = lpAct->field_F54 - 10;
            d = 5;
            if (s0 >= 0)
            {
                v = d - s0;
                lpAct->field_E70 = v * 17 / d;
            }
        }
        else
        {
            s0 = lpAct->field_F54 - 5;
            d = 10;
            if (s0 >= 0)
            {
                v = lpAct->field_E70 * s0;
                lpAct->field_E70 = v / d;
            }
        }
    }

    memset(&rot, 0, 8);
    r = ratan2(lpAct->field_E34.vx, lpAct->field_E34.vz);
    rot.vy = r - lpAct->control.turn.vy;
    memset(&vec, 0, 8);
    vec.vx = lpAct->field_E70;
    DG_SetPos2(&DG_ZeroVector, &vec);
    DG_RotatePos(&rot);

    memset(&vec, 0, 8);
    vec.vz = 0x64;
    DG_PutVector(&vec, &vec, 1);
    v = vec.vx * vec.vx;
    d = SquareRoot0(v + vec.vz * vec.vz);
    r = ratan2(vec.vy, d);
    rot.vx = r;
    r = (short)r;
    if (r < 0) r = -r;
    v = lpAct->field_E70;
    s0 = rot.vy;
    if (v < 0) v = -v;
    v -= r;
    rot.vz = v;
    while (s0 < 0) s0 += 0x1000;
    while (s0 >= 0x1001) s0 -= 0x1000;
    if (s0 >= 0x801) rot.vz = -rot.vz;

    lpAct->field_E9C += rot.vx;
    lpAct->field_EA0 += rot.vz;
    DG_SetPos2(&DG_ZeroVector, &rot);

    memset(&vec, 0, 8);
    vec.vz = *(u_short *)&lpAct->bbox[1].vz;
    DG_PutVector(&vec, &vec, 1);
    r = vec.vy;
    v = *(int *)&lpAct->field_EA4;
    if (r < 0) r = -r;
    v -= r >> 1;
    *(int *)&lpAct->field_EA4 = v;
}

#define WMDL(off) (*(u_short *)((char *)lpAct->objBody.objs->objs[0].model + (off)))

void s05a_800DA940(LPM1E1ACT lpAct)
{
    SVECTOR vec;
    SVECTOR verts[10];
    int     i;
    int     s0, s1;

    if (lpAct->field_D54 == 6)
    {
        return;
    }

    DG_SetPos2(&lpAct->control.mov, &lpAct->control.turn);
    M1E1GetCaterpillerVertex(&lpAct->objLeftCater[0], &lpAct->objRightCater[0], verts, 1);
    for (i = 0; i < 10; i++) verts[i].vy += 0x258;
    DG_PutVector(verts, verts, 10);
    for (i = 0; i < 10; i++)
    {
        GM_MoveTarget(lpAct->lpTarget[i], &verts[i]);
        GM_PushTarget(lpAct->lpTarget[i]);
    }

    M1E1GetCaterpillerVertex(&lpAct->objLeftCater[0], &lpAct->objRightCater[0], verts, 0);
    for (i = 0; i < 10; i++) verts[i].vy += 0x12C;
    DG_PutVector(verts, verts, 10);
    for (i = 0; i < 10; i++)
    {
        GM_MoveTarget((TARGET *)&lpAct->field_A84[i], &verts[i]);
    }

    s0 = (*(int *)((char *)lpAct + 0x8C8) * 3) >> 2;
    s1 = (*(int *)((char *)lpAct + 0x95C) * 3) >> 2;

    vec.vx = 0; vec.vz = WMDL(0x1C) - s0; vec.vy = WMDL(0x18);
    DG_PutVector(&vec, &vec, 1); GM_MoveTarget((TARGET *)((char *)lpAct + 0x8CC), &vec);
    vec.vx = 0; vec.vz = WMDL(0x10) + s0; vec.vy = WMDL(0x18);
    DG_PutVector(&vec, &vec, 1); GM_MoveTarget((TARGET *)((char *)lpAct + 0x914), &vec);
    vec.vx = WMDL(0x08) + s1; vec.vz = WMDL(0x1C) - s1; vec.vy = WMDL(0x18);
    DG_PutVector(&vec, &vec, 1); GM_MoveTarget((TARGET *)((char *)lpAct + 0x960), &vec);
    vec.vx = WMDL(0x08) + s1; vec.vz = WMDL(0x10) + s1; vec.vy = WMDL(0x18);
    DG_PutVector(&vec, &vec, 1); GM_MoveTarget((TARGET *)((char *)lpAct + 0x9A8), &vec);
    vec.vx = WMDL(0x14) - s1; vec.vz = WMDL(0x1C) - s1; vec.vy = WMDL(0x18);
    DG_PutVector(&vec, &vec, 1); GM_MoveTarget((TARGET *)((char *)lpAct + 0x9F0), &vec);
    vec.vx = WMDL(0x14) - s1; vec.vz = WMDL(0x10) + s1; vec.vy = WMDL(0x18);
    DG_PutVector(&vec, &vec, 1); GM_MoveTarget((TARGET *)((char *)lpAct + 0xA38), &vec);
}

void s05a_800DACF0(LPM1E1ACT lpAct)
{
    lpAct->copy0 = lpAct->hzdBlock[0].flr[1];
    lpAct->copy1 = lpAct->hzdBlock[1].flr[1];
    lpAct->copy2 = lpAct->hzdBlock[4].flr[1];

    GetHazard2(lpAct->hzdBlock[0].seg, lpAct->hzdBlock[0].flr,
                 (MATRIX *)((char *)lpAct->objBody.objs + 0xA4), &lpAct->bbox[0], &lpAct->bbox[1]);
    GetHazard2(lpAct->hzdBlock[1].seg, lpAct->hzdBlock[1].flr,
                 (MATRIX *)((char *)lpAct->objBody.objs + 0x100), &lpAct->bbox[2], &lpAct->bbox[3]);
    GetHazard2(lpAct->hzdBlock[2].seg, lpAct->hzdBlock[2].flr,
                 (MATRIX *)((char *)lpAct->objLeftCater[0].objs + 0x48), &lpAct->bbox[4], &lpAct->bbox[5]);
    GetHazard2(lpAct->hzdBlock[3].seg, lpAct->hzdBlock[3].flr,
                 (MATRIX *)((char *)lpAct->objRightCater[0].objs + 0x48), &lpAct->bbox[6], &lpAct->bbox[7]);
    GetHazard2(lpAct->hzdBlock[4].seg, lpAct->hzdBlock[4].flr,
                 (MATRIX *)((char *)lpAct->objBody.objs + 0x15C), &lpAct->bbox[8], &lpAct->bbox[9]);
}
