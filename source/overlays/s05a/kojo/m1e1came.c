#include "game/game.h"
#include "libgcl/libgcl.h"

extern GM_CameraSystemWork GM_Camera;

typedef struct _CamModel
{
    char    pad_000[0x15C];
    MATRIX  field_15C; /* 0x15C */
    char    pad_17C[0x284 - 0x17C];
    u_short field_284; /* 0x284 */
    char    pad_286[0x288 - 0x286];
    u_short field_288; /* 0x288 */
    char    pad_28A[0x28C - 0x28A];
    u_short field_28C; /* 0x28C */
    char    pad_28E[0x3F4 - 0x28E];
    u_short field_3F4; /* 0x3F4 */
    char    pad_3F6[0x3F8 - 0x3F6];
    u_short field_3F8; /* 0x3F8 */
    char    pad_3FA[0x3FC - 0x3FA];
    u_short field_3FC; /* 0x3FC */
    char    pad_3FE[0x498 - 0x3FE];
    MATRIX  field_498; /* 0x498 */
} CamModel;

typedef struct _CamActor
{
    char      pad_000[0x24];
    short     field_24;  /* 0x024 */
    char      pad_26[0x4C - 0x26];
    MAP      *field_4C;  /* 0x04C */
    char      pad_50[0xDC - 0x50];
    CamModel *field_DC;  /* 0x0DC */
    char      pad_E0[0xD54 - 0xE0];
    int       field_D54; /* 0xD54 */
    char      pad_D58[0xDBC - 0xD58];
    int       field_DBC; /* 0xDBC */
    char      pad_DC0[0xE5C - 0xDC0];
    int       field_E5C; /* 0xE5C */
    char      pad_E60[0xED0 - 0xE60];
    int       field_ED0; /* 0xED0 */
} CamActor;

typedef struct _Camera
{
    char    pad_000[0x20];
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
} Camera;

extern CamActor *s05a_dword_800C362C;
extern Camera  *s05a_dword_800C38CC;

void s05a_800E209C(VECTOR *out, VECTOR *in, int (*fn)());
VECTOR *s05a_800E2328(VECTOR *out, SVECTOR *cam, VECTOR *in, SVECTOR *lo, SVECTOR *hi);
void s05a_800E1448(Camera *actor);
void s05a_800E1A68(void);
void s05a_800E1AA8(void);
void s05a_800E1C14(void);
void s05a_800E1D7C(void);
void s05a_800E1F0C(void);
extern const char s05a_dword_800E35D8[];
extern const char s05a_dword_800E35E4[];

extern GM_SnakeCameraWork GM_SnakeCamera;

void *NewCinemaScreen(int time, int type);
void *NewCinemaScreenClose(void *addr);
void sub_8007EF34(SVECTOR *pOutVec1, SVECTOR *pOutVec2, MATRIX *pInMtx);

void *s05a_800E1134(void)
{
    Camera *cam;
    char   *s;

    cam = GV_NewActor(GV_ACTOR_USER, 0x90);
    if (cam == NULL)
    {
        return 0;
    }
    GV_SetNamedActor(cam, s05a_800E1448, s05a_800E1A68, s05a_dword_800E35D8);

    if (GCL_GetOption(0x62))
    {
        if ((s = GCL_NextStr())) cam->field_20.vx = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) cam->field_20.vy = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) cam->field_20.vz = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) cam->field_28.vx = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) cam->field_28.vy = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) cam->field_28.vz = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) cam->field_3C.vx = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) cam->field_3C.vy = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) cam->field_3C.vz = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) cam->field_44.vx = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) cam->field_44.vy = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) cam->field_44.vz = GCL_StrToInt(s);
    }
    if (GCL_GetOption(0x72))
    {
        if ((s = GCL_NextStr())) cam->field_30.vx = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) cam->field_30.vy = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) cam->field_30.vz = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) cam->field_4C.vx = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) cam->field_4C.vy = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) cam->field_4C.vz = GCL_StrToInt(s);
    }
    if (GCL_GetOption(0x74))
    {
        if ((s = GCL_NextStr())) *(int *)&cam->field_38 = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) *(int *)&cam->field_54 = GCL_StrToInt(s);
        if ((s = GCL_NextStr())) *(int *)&cam->field_58 = GCL_StrToInt(s);
    }
    if (GCL_GetOption(0x6F))
    {
        if ((s = GCL_NextStr())) cam->field_5C = GCL_StrToInt(s);
    }

    cam->field_60 = 1;
    s05a_dword_800C38CC = cam;
    return cam;
}
void s05a_800E1448(Camera *actor)
{
    CamActor *listener;
    SVECTOR   sp10;

    listener = s05a_dword_800C362C;
    if (listener == NULL || listener->field_D54 == 6)
    {
        GV_DestroyActor((GV_ACT *)actor);
        return;
    }

    actor->field_84++;

    if (listener->field_ED0 == 2)
    {
        if (actor->field_60 != 3)
        {
            int t;
            int u;

            sub_8007EF34(&sp10, (SVECTOR *)&actor->field_64, &listener->field_DC->field_15C);
            memset(&actor->field_6C, 0, 8);
            memset(&actor->field_74, 0, 8);
            t = -3;
            actor->field_6E = t;
            t = actor->field_64;
            u = 0xDAC;
            *(int *)&actor->field_7C = u;
            u = (int)actor->field_80;
            t += 0x71;
            actor->field_64 = t;
            t = actor->field_66;
            actor->field_84 = 0;
            actor->field_88 = 0;
            actor->field_8C = 0;
            actor->field_68 = 0;
            actor->field_6C = 0;
            t += 0x156;
            actor->field_66 = t;
            if (u == 0)
            {
                actor->field_80 = NewCinemaScreen(0x77359400, 0);
            }
            GM_GameStatus |= 0x104A2000;
            GM_Camera.flag |= 0x202;
            sub_800309B4(0, 0);
            GM_SetCameraCallbackFunc(0, s05a_800E1AA8);
            GM_SetCameraCallbackFunc(1, s05a_800E1AA8);
        }
        else
        {
            actor->field_8C = 1;
        }
        GM_Camera.type = 0;
        actor->field_60 = 3;
        return;
    }

    if (listener->field_ED0 == 3)
    {
        if (actor->field_60 != 4)
        {
            sub_8007EF34(&sp10, (SVECTOR *)&actor->field_64, &listener->field_DC->field_498);
            memset(&actor->field_6C, 0, 8);
            memset(&actor->field_74, 0, 8);
            *(int *)&actor->field_7C = 0xBB8;
            actor->field_84 = 0;
            actor->field_88 = 0;
            actor->field_8C = 0;
            actor->field_68 = 0;
            actor->field_6C = 2;
            actor->field_6E = 6;
            actor->field_64 += -0x11C;
            if (actor->field_80 == 0)
            {
                actor->field_80 = NewCinemaScreen(0x77359400, 0);
            }
            GM_GameStatus |= 0x104A2000;
            GM_Camera.flag |= 0x202;
            sub_800309B4(0, 0);
            GM_SetCameraCallbackFunc(0, s05a_800E1C14);
            GM_SetCameraCallbackFunc(1, s05a_800E1C14);
        }
        else
        {
            actor->field_8C = 1;
        }
        GM_Camera.type = 0;
        actor->field_60 = 4;
        return;
    }

    {
        HZD_HDL *hzd;
        HZD_GRP *grp;
        HZD_TRP *trp;
        int      i;

        hzd = listener->field_4C->hzd;
        grp = hzd->grp;
        trp = (HZD_TRP *)grp->triggers;

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
            GM_PlayerPosition.vz > s05a_dword_800C362C->field_24)
        {
            if (actor->field_60 != 2)
            {
                if (actor->field_80 != 0)
                {
                    NewCinemaScreenClose(actor->field_80);
                    actor->field_80 = 0;
                }
                actor->field_84 = 0;
                if (actor->field_60 != 1)
                {
                    actor->field_8C = 0;
                    GM_SnakeCamera.position = GM_PlayerPosition;
                }
                else
                {
                    actor->field_8C = actor->field_60;
                }
                GM_GameStatus &= ~0x104A2000;
                GM_Camera.flag = (GM_Camera.flag | 2) & ~0x200;
                sub_800309B4(0, -1);
                GM_SetCameraCallbackFunc(0, NULL);
                GM_SetCameraCallbackFunc(1, s05a_800E1D7C);
            }
            else
            {
                actor->field_8C = 1;
            }
            if (GM_Camera.interp > 0)
            {
                actor->field_88 = 0;
            }
            else if (actor->field_60 != 1)
            {
                actor->field_88 = 0;
            }
            else
            {
                actor->field_88 = actor->field_60;
            }
            GM_Camera.type = 0;
            actor->field_60 = 2;
            return;
        }

        if (actor->field_60 != 1)
        {
            if (actor->field_80 != 0)
            {
                NewCinemaScreenClose(actor->field_80);
                actor->field_80 = 0;
            }
            actor->field_84 = 0;
            if (actor->field_60 != 2)
            {
                actor->field_8C = 0;
                GM_SnakeCamera.position = GM_PlayerPosition;
            }
            else
            {
                actor->field_8C = 1;
            }
            GM_GameStatus &= ~0x104A2000;
            GM_Camera.flag = (GM_Camera.flag | 2) & ~0x200;
            sub_800309B4(0, -1);
            GM_SetCameraCallbackFunc(0, NULL);
            GM_SetCameraCallbackFunc(1, s05a_800E1F0C);
        }
        else
        {
            actor->field_8C = actor->field_60;
        }
        if (GM_Camera.interp > 0)
        {
            actor->field_88 = 0;
        }
        else if (actor->field_60 != 2)
        {
            actor->field_88 = 0;
        }
        else
        {
            actor->field_88 = 1;
        }
        GM_Camera.type = 0;
        actor->field_60 = 1;
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

    s05a_dword_800C38CC->field_74.vx = s05a_dword_800C362C->field_DC->field_284;
    s05a_dword_800C38CC->field_74.vy = s05a_dword_800C362C->field_DC->field_288;
    s05a_dword_800C38CC->field_74.vz = s05a_dword_800C362C->field_DC->field_28C;
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

    s05a_dword_800C38CC->field_74.vx = s05a_dword_800C362C->field_DC->field_3F4;
    s05a_dword_800C38CC->field_74.vy = s05a_dword_800C362C->field_DC->field_3F8;
    s05a_dword_800C38CC->field_74.vz = s05a_dword_800C362C->field_DC->field_3FC;

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
