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
    SVECTOR field_20; /* 0x20 */
    SVECTOR field_28; /* 0x28 */
    SVECTOR field_30; /* 0x30 */
    u_short field_38; /* 0x38 */
    char    pad_3A[0x3C - 0x3A];
    SVECTOR field_3C; /* 0x3C */
    SVECTOR field_44; /* 0x44 */
    SVECTOR field_4C; /* 0x4C */
    u_short field_54; /* 0x54 */
    char    pad_56[0x58 - 0x56];
    u_short field_58; /* 0x58 */
    char    pad_5A[0x5C - 0x5A];
    int     field_5C; /* 0x5C */
    int     field_60; /* 0x60 */
    u_short field_64; /* 0x64 */
    u_short field_66; /* 0x66 */
    u_short field_68; /* 0x68 */
    char    pad_6A[0x6C - 0x6A];
    u_short field_6C; /* 0x6C */
    u_short field_6E; /* 0x6E */
    u_short field_70; /* 0x70 */
    char    pad_72[0x74 - 0x72];
    SVECTOR field_74; /* 0x74 */
    u_short field_7C; /* 0x7C */
    char    pad_7E[0x80 - 0x7E];
    void   *field_80; /* 0x80 */
    int     field_84; /* 0x84 */
    int     field_88; /* 0x88 */
    int     field_8C; /* 0x8C */
} M1E1CAMERAACT, *PM1E1CAMERAACT, *LPM1E1CAMERAACT;

extern LPM1E1ACT s05a_dword_800C362C;
extern LPM1E1CAMERAACT s05a_dword_800C38CC;

void s05a_800E209C(VECTOR *out, VECTOR *in, int (*fn)());
VECTOR *s05a_800E2328(VECTOR *out, SVECTOR *cam, VECTOR *in, SVECTOR *lo, SVECTOR *hi);
void s05a_800E1448(LPM1E1CAMERAACT lpAct);
void s05a_800E1A68(void);
void s05a_800E1AA8(void);
void s05a_800E1C14(void);
void s05a_800E1D7C(void);
void s05a_800E1F0C(void);

const char s05a_dword_800E35D8[] = "m1e1came.c";
const char s05a_dword_800E35E4[] = {'n', 'o', 's', 'u', 'b', 'j', 'e', 'c', 't', 0x0, 'E', 'N'};

void sub_8007EF34(SVECTOR *pOutVec1, SVECTOR *pOutVec2, MATRIX *pInMtx);

/******************************************************************************
 */

void *s05a_800E1134(void)
{
    LPM1E1CAMERAACT lpAct;
    char   *s;

    lpAct = GV_NewActor(GV_ACTOR_USER, 0x90);
    if (lpAct == NULL)
    {
        return NULL;
    }
    GV_SetNamedActor(lpAct, s05a_800E1448, s05a_800E1A68, s05a_dword_800E35D8);

    if (GCL_GetOption(0x62))
    {
        if ((s = GCL_NextStr())) lpAct->field_20.vx = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) lpAct->field_20.vy = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) lpAct->field_20.vz = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) lpAct->field_28.vx = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) lpAct->field_28.vy = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) lpAct->field_28.vz = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) lpAct->field_3C.vx = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) lpAct->field_3C.vy = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) lpAct->field_3C.vz = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) lpAct->field_44.vx = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) lpAct->field_44.vy = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) lpAct->field_44.vz = GCL_StrToInt(s);
    }
    if (GCL_GetOption(0x72))
    {
        if ((s = GCL_NextStr())) lpAct->field_30.vx = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) lpAct->field_30.vy = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) lpAct->field_30.vz = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) lpAct->field_4C.vx = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) lpAct->field_4C.vy = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) lpAct->field_4C.vz = GCL_StrToInt(s);
    }
    if (GCL_GetOption(0x74))
    {
        if ((s = GCL_NextStr())) *(int *)&lpAct->field_38 = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) *(int *)&lpAct->field_54 = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) *(int *)&lpAct->field_58 = GCL_StrToInt(s);
    }
    if (GCL_GetOption(0x6F))
    {
        if ((s = GCL_NextStr())) lpAct->field_5C = GCL_StrToInt(s);
    }

    lpAct->field_60 = 1;
    s05a_dword_800C38CC = lpAct;
    return (void*)lpAct;
}

void s05a_800E1448(LPM1E1CAMERAACT lpAct)
{
    LPM1E1ACT lpParent;
    SVECTOR   sp10;

    lpParent = s05a_dword_800C362C;
    if (lpParent == NULL || lpParent->field_D54 == 6)
    {
        GV_DestroyActor((void *)lpAct);
        return;
    }

    lpAct->field_84++;

    if (lpParent->field_ED0 == 2)
    {
        if (lpAct->field_60 != 3)
        {
            int t;
            int u;

            sub_8007EF34(&sp10, (SVECTOR *)&lpAct->field_64, &lpParent->objBody.objs->objs[3].world);
            memset(&lpAct->field_6C, 0, 8);
            memset(&lpAct->field_74, 0, 8);
            t = -3;
            lpAct->field_6E = t;
            t = lpAct->field_64;
            u = 0xDAC;
            *(int *)&lpAct->field_7C = u;
            u = (int)lpAct->field_80;
            t += 0x71;
            lpAct->field_64 = t;
            t = lpAct->field_66;
            lpAct->field_84 = 0;
            lpAct->field_88 = 0;
            lpAct->field_8C = 0;
            lpAct->field_68 = 0;
            lpAct->field_6C = 0;
            t += 0x156;
            lpAct->field_66 = t;
            if (u == 0)
            {
                lpAct->field_80 = NewCinemaScreen(0x77359400, 0);
            }
            GM_GameStatus |= 0x104A2000;
            GM_Camera.flag |= 0x202;
            sub_800309B4(0, 0);
            GM_SetCameraCallbackFunc(0, s05a_800E1AA8);
            GM_SetCameraCallbackFunc(1, s05a_800E1AA8);
        }
        else
        {
            lpAct->field_8C = 1;
        }
        GM_Camera.type = 0;
        lpAct->field_60 = 3;
        return;
    }

    if (lpParent->field_ED0 == 3)
    {
        if (lpAct->field_60 != 4)
        {
            sub_8007EF34(&sp10, (SVECTOR *)&lpAct->field_64, &lpParent->objBody.objs->objs[12].world);
            memset(&lpAct->field_6C, 0, 8);
            memset(&lpAct->field_74, 0, 8);
            *(int *)&lpAct->field_7C = 0xBB8;
            lpAct->field_84 = 0;
            lpAct->field_88 = 0;
            lpAct->field_8C = 0;
            lpAct->field_68 = 0;
            lpAct->field_6C = 2;
            lpAct->field_6E = 6;
            lpAct->field_64 += -0x11C;
            if (lpAct->field_80 == 0)
            {
                lpAct->field_80 = NewCinemaScreen(0x77359400, 0);
            }
            GM_GameStatus |= 0x104A2000;
            GM_Camera.flag |= 0x202;
            sub_800309B4(0, 0);
            GM_SetCameraCallbackFunc(0, s05a_800E1C14);
            GM_SetCameraCallbackFunc(1, s05a_800E1C14);
        }
        else
        {
            lpAct->field_8C = 1;
        }
        GM_Camera.type = 0;
        lpAct->field_60 = 4;
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
            if (trp->name_id != GV_StrCode(s05a_dword_800E35E4)) continue;
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
            if (lpAct->field_60 != 2)
            {
                if (lpAct->field_80 != 0)
                {
                    NewCinemaScreenClose(lpAct->field_80);
                    lpAct->field_80 = 0;
                }
                lpAct->field_84 = 0;
                if (lpAct->field_60 != 1)
                {
                    lpAct->field_8C = 0;
                    GM_SnakeCamera.position = GM_PlayerPosition;
                }
                else
                {
                    lpAct->field_8C = lpAct->field_60;
                }
                GM_GameStatus &= ~0x104A2000;
                GM_Camera.flag = (GM_Camera.flag | 2) & ~0x200;
                sub_800309B4(0, -1);
                GM_SetCameraCallbackFunc(0, NULL);
                GM_SetCameraCallbackFunc(1, s05a_800E1D7C);
            }
            else
            {
                lpAct->field_8C = 1;
            }
            if (GM_Camera.interp > 0)
            {
                lpAct->field_88 = 0;
            }
            else if (lpAct->field_60 != 1)
            {
                lpAct->field_88 = 0;
            }
            else
            {
                lpAct->field_88 = lpAct->field_60;
            }
            GM_Camera.type = 0;
            lpAct->field_60 = 2;
            return;
        }

        if (lpAct->field_60 != 1)
        {
            if (lpAct->field_80 != 0)
            {
                NewCinemaScreenClose(lpAct->field_80);
                lpAct->field_80 = 0;
            }
            lpAct->field_84 = 0;
            if (lpAct->field_60 != 2)
            {
                lpAct->field_8C = 0;
                GM_SnakeCamera.position = GM_PlayerPosition;
            }
            else
            {
                lpAct->field_8C = 1;
            }
            GM_GameStatus &= ~0x104A2000;
            GM_Camera.flag = (GM_Camera.flag | 2) & ~0x200;
            sub_800309B4(0, -1);
            GM_SetCameraCallbackFunc(0, NULL);
            GM_SetCameraCallbackFunc(1, s05a_800E1F0C);
        }
        else
        {
            lpAct->field_8C = lpAct->field_60;
        }
        if (GM_Camera.interp > 0)
        {
            lpAct->field_88 = 0;
        }
        else if (lpAct->field_60 != 2)
        {
            lpAct->field_88 = 0;
        }
        else
        {
            lpAct->field_88 = 1;
        }
        GM_Camera.type = 0;
        lpAct->field_60 = 1;
    }
}

void s05a_800E1A68(void)
{
    GM_Camera.flag &= ~2;
    GM_SetCameraCallbackFunc(1, NULL);
    s05a_dword_800C38CC = 0;
}

void s05a_800E1AA8(void)
{
    VECTOR  pos;
    VECTOR  rot;
    SVECTOR off;

    GM_PlayerStatus &= ~PLAYER_NOT_SIGHT;
    DG_SetPos2(&DG_ZeroVector, (SVECTOR *)&s05a_dword_800C38CC->field_64);

    memset(&off, 0, 8);
    off.vz = s05a_dword_800C38CC->field_7C;
    DG_PutVector(&off, &off, 1);

    s05a_dword_800C38CC->field_74.vx = s05a_dword_800C362C->objBody.objs->objs[6].world.t[0];
    s05a_dword_800C38CC->field_74.vy = s05a_dword_800C362C->objBody.objs->objs[6].world.t[1];
    s05a_dword_800C38CC->field_74.vz = s05a_dword_800C362C->objBody.objs->objs[6].world.t[2];
    s05a_dword_800C38CC->field_74.vy += 0x1F4;

    pos.vx = s05a_dword_800C38CC->field_74.vx + off.vx;
    pos.vy = s05a_dword_800C38CC->field_74.vy + off.vy;
    pos.vz = s05a_dword_800C38CC->field_74.vz + off.vz;

    rot.vx = s05a_dword_800C38CC->field_74.vx;
    rot.vy = s05a_dword_800C38CC->field_74.vy;
    rot.vz = s05a_dword_800C38CC->field_74.vz;

    s05a_800E209C(&pos, &rot, GV_NearExp2);

    s05a_dword_800C38CC->field_64 += s05a_dword_800C38CC->field_6C;
    s05a_dword_800C38CC->field_66 += s05a_dword_800C38CC->field_6E;
    s05a_dword_800C38CC->field_68 += s05a_dword_800C38CC->field_70;
}

void s05a_800E1C14(void)
{
    VECTOR  pos;
    VECTOR  rot;
    SVECTOR off;

    GM_PlayerStatus &= ~PLAYER_NOT_SIGHT;
    DG_SetPos2(&DG_ZeroVector, (SVECTOR *)&s05a_dword_800C38CC->field_64);

    memset(&off, 0, 8);
    off.vz = s05a_dword_800C38CC->field_7C;
    DG_PutVector(&off, &off, 1);

    s05a_dword_800C38CC->field_74.vx = s05a_dword_800C362C->objBody.objs->objs[10].world.t[0];
    s05a_dword_800C38CC->field_74.vy = s05a_dword_800C362C->objBody.objs->objs[10].world.t[1];
    s05a_dword_800C38CC->field_74.vz = s05a_dword_800C362C->objBody.objs->objs[10].world.t[2];

    pos.vx = s05a_dword_800C38CC->field_74.vx + off.vx;
    pos.vy = s05a_dword_800C38CC->field_74.vy + off.vy;
    pos.vz = s05a_dword_800C38CC->field_74.vz + off.vz;

    rot.vx = s05a_dword_800C38CC->field_74.vx;
    rot.vy = s05a_dword_800C38CC->field_74.vy;
    rot.vz = s05a_dword_800C38CC->field_74.vz;

    s05a_800E209C(&pos, &rot, GV_NearExp2);

    s05a_dword_800C38CC->field_64 += s05a_dword_800C38CC->field_6C;
    s05a_dword_800C38CC->field_66 += s05a_dword_800C38CC->field_6E;
    s05a_dword_800C38CC->field_68 += s05a_dword_800C38CC->field_70;
}

void s05a_800E1D7C(void)
{
    VECTOR  hi;
    VECTOR  lo;
    SVECTOR off;

    DG_SetPos2(&DG_ZeroVector, (SVECTOR *)&s05a_dword_800C38CC->field_4C);

    memset(&off, 0, 8);
    {
        u_short base = s05a_dword_800C38CC->field_54;

        off.vz = base;
        if (s05a_dword_800C362C->field_E5C <= s05a_dword_800C38CC->field_5C)
        {
            off.vz = base + s05a_dword_800C38CC->field_58;
        }
    }
    DG_PutVector(&off, &off, 1);

    hi.vx = GM_PlayerPosition.vx + off.vx;
    hi.vy = GM_PlayerPosition.vy + off.vy;
    hi.vz = GM_PlayerPosition.vz + off.vz;
    s05a_800E2328(&hi, &GM_Camera.position, &hi, &s05a_dword_800C38CC->field_3C,
                  &s05a_dword_800C38CC->field_44);

    lo.vx = GM_PlayerPosition.vx;
    lo.vy = GM_PlayerPosition.vy;
    lo.vz = GM_PlayerPosition.vz;
    s05a_800E2328(&lo, &GM_Camera.target, &lo, &s05a_dword_800C38CC->field_3C,
                  &s05a_dword_800C38CC->field_44);

    lo.vx = hi.vx;
    s05a_800E209C(&hi, &lo, GV_NearExp8);

    if (GM_Camera.target.vz <= GM_Camera.position.vz)
    {
        GM_Camera.target.vz -= 1;
    }
}

void s05a_800E1F0C(void)
{
    VECTOR  hi;
    VECTOR  lo;
    SVECTOR off;

    DG_SetPos2(&DG_ZeroVector, (SVECTOR *)&s05a_dword_800C38CC->field_30);

    memset(&off, 0, 8);
    {
        u_short base = s05a_dword_800C38CC->field_38;

        off.vz = base;
        if (s05a_dword_800C362C->field_E5C <= s05a_dword_800C38CC->field_5C)
        {
            off.vz = base + s05a_dword_800C38CC->field_58;
        }
    }
    DG_PutVector(&off, &off, 1);

    hi.vx = GM_PlayerPosition.vx + off.vx;
    hi.vy = GM_PlayerPosition.vy + off.vy;
    hi.vz = GM_PlayerPosition.vz + off.vz;
    s05a_800E2328(&hi, &GM_Camera.position, &hi, &s05a_dword_800C38CC->field_20,
                  &s05a_dword_800C38CC->field_28);

    lo.vx = GM_PlayerPosition.vx;
    lo.vy = GM_PlayerPosition.vy;
    lo.vz = GM_PlayerPosition.vz;
    s05a_800E2328(&lo, &GM_Camera.target, &lo, &s05a_dword_800C38CC->field_20,
                  &s05a_dword_800C38CC->field_28);

    lo.vx = hi.vx;
    s05a_800E209C(&hi, &lo, GV_NearExp8);

    if (GM_Camera.target.vz <= GM_Camera.position.vz)
    {
        GM_Camera.target.vz -= 1;
    }
}

void s05a_800E209C(VECTOR *out, VECTOR *in, int (*fn)())
{
    { int t = s05a_dword_800C38CC->field_20.vx; if (t < out->vx) t = out->vx; out->vx = t; }
    { int t = s05a_dword_800C38CC->field_28.vx; if (out->vx < t) t = out->vx; out->vx = t; }
    { int t = s05a_dword_800C38CC->field_20.vy; if (t < out->vy) t = out->vy; out->vy = t; }
    { int t = s05a_dword_800C38CC->field_28.vy; if (out->vy < t) t = out->vy; out->vy = t; }
    { int t = s05a_dword_800C38CC->field_20.vz; if (t < out->vz) t = out->vz; out->vz = t; }
    { int t = s05a_dword_800C38CC->field_28.vz; if (out->vz < t) t = out->vz; out->vz = t; }
    { int t = s05a_dword_800C38CC->field_20.vx; if (t < in->vx) t = in->vx; in->vx = t; }
    { int t = s05a_dword_800C38CC->field_28.vx; if (in->vx < t) t = in->vx; in->vx = t; }
    { int t = s05a_dword_800C38CC->field_20.vy; if (t < in->vy) t = in->vy; in->vy = t; }
    { int t = s05a_dword_800C38CC->field_28.vy; if (in->vy < t) t = in->vy; in->vy = t; }
    { int t = s05a_dword_800C38CC->field_20.vz; if (t < in->vz) t = in->vz; in->vz = t; }
    { int t = s05a_dword_800C38CC->field_28.vz; if (in->vz < t) t = in->vz; in->vz = t; }

    if (s05a_dword_800C38CC->field_8C == 0)
    {
        GM_Camera.position.vx = out->vx;
        GM_Camera.position.vy = out->vy;
        GM_Camera.position.vz = out->vz;
        GM_Camera.target.vx = in->vx;
        GM_Camera.target.vy = in->vy;
        GM_Camera.target.vz = in->vz;
    }
    GM_Camera.position.vx = fn(GM_Camera.position.vx, out->vx);
    GM_Camera.position.vy = fn(GM_Camera.position.vy, out->vy);
    GM_Camera.position.vz = fn(GM_Camera.position.vz, out->vz);
    GM_Camera.target.vx = fn(GM_Camera.target.vx, in->vx);
    GM_Camera.target.vy = fn(GM_Camera.target.vy, in->vy);
    GM_Camera.target.vz = fn(GM_Camera.target.vz, in->vz);
}

VECTOR *s05a_800E2328(VECTOR *out, SVECTOR *cam, VECTOR *in, SVECTOR *lo, SVECTOR *hi)
{
    VECTOR  p;
    SVECTOR pad;

    p.vx = cam->vx;
    p.vy = cam->vy;
    p.vz = cam->vz;

    if (s05a_dword_800C38CC->field_88 == 0) { p.vx = in->vx; }
    else {
        int delta = in->vx - p.vx;
        if (delta >= 0x3E9) { int r = p.vx - 0x3E8; p.vx = r + delta; }
        else if (p.vx - in->vx >= 0x3E9) { int r = p.vx + 0x3E8; p.vx = r + delta; }
    }
    if (s05a_dword_800C38CC->field_88 == 0) { p.vy = in->vy; }
    else {
        int delta = in->vy - p.vy;
        if (delta >= 0x3E9) { int r = p.vy - 0x3E8; p.vy = r + delta; }
        else if (p.vy - in->vy >= 0x3E9) { int r = p.vy + 0x3E8; p.vy = r + delta; }
    }
    if (s05a_dword_800C38CC->field_88 == 0) { p.vz = in->vz; }
    else {
        int delta = in->vz - p.vz;
        if (delta >= 0x3E9) { int r = p.vz - 0x3E8; p.vz = r + delta; }
        else if (p.vz - in->vz >= 0x3E9) { int r = p.vz + 0x3E8; p.vz = r + delta; }
    }

    { int t = lo->vx; if (t < p.vx) t = p.vx; p.vx = t; }
    { int t = hi->vx; if (p.vx < t) t = p.vx; p.vx = t; }
    { int t = lo->vy; if (t < p.vy) t = p.vy; p.vy = t; }
    { int t = hi->vy; if (p.vy < t) t = p.vy; p.vy = t; }
    { int t = lo->vz; if (t < p.vz) t = p.vz; p.vz = t; }
    { int t = hi->vz; if (p.vz < t) t = p.vz; p.vz = t; }

    *out = p;
    return out;
}
