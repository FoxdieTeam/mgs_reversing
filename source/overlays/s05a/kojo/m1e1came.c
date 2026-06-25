#include "game/game.h"
#include "libgcl/libgcl.h"

extern GM_CameraSystemWork GM_Camera;

typedef struct _CamModel
{
    char    pad_000[0x284];
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
} CamModel;

typedef struct _CamActor
{
    char      pad_000[0xDC];
    CamModel *field_DC; /* 0x0DC */
    char      pad_E0[0xE5C - 0xE0];
    int       field_E5C; /* 0xE5C */
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
    char    pad_7E[0x88 - 0x7E];
    int     field_88; /* 0x88 */
} Camera;

extern CamActor *s05a_dword_800C362C;
extern Camera  *s05a_dword_800C38CC;

void s05a_800E209C(VECTOR *out, VECTOR *in, int (*fn)());
VECTOR *s05a_800E2328(VECTOR *out, SVECTOR *cam, VECTOR *in, SVECTOR *lo, SVECTOR *hi);
void s05a_800E1448(void);
void s05a_800E1A68(void);
extern const char s05a_dword_800E35D8[];

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
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E1448.s")

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
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E209C.s")
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
