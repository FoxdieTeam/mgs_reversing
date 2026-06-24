#include "game/game.h"

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
    char    pad_000[0x3C];
    SVECTOR field_3C; /* 0x3C */
    SVECTOR field_44; /* 0x44 */
    SVECTOR field_4C; /* 0x4C */
    u_short field_54; /* 0x54 */
    char    pad_56[0x58 - 0x56];
    u_short field_58; /* 0x58 */
    char    pad_5A[0x5C - 0x5A];
    int     field_5C; /* 0x5C */
    char    pad_60[0x64 - 0x60];
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
} Camera;

extern CamActor *s05a_dword_800C362C;
extern Camera  *s05a_dword_800C38CC;

void s05a_800E209C(VECTOR *out, VECTOR *in, int (*fn)());
void s05a_800E2328(VECTOR *out, SVECTOR *cam, VECTOR *in, SVECTOR *p3c, SVECTOR *p44);

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E1134.s")
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
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E1F0C.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E209C.s")
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E2328.s")
