#include "game/game.h"
#include "chara/snake/sna_init.h"
#include "libhzd/libhzd.h"
#include "linkvar.h"
#include "strcode.h"

/* Partial view of the actor passed to s05a_800DEC18. The 0x204/0x208/0x238
   fields fall inside SnaInitWork's motion arrays, so they are kept separate
   until they can be reconciled against the original struct. */
typedef struct _DescentWork
{
    GV_ACT  actor;      /* 0x000 */
    CONTROL control;    /* 0x020 */
    OBJECT  body;       /* 0x09C */
    char    pad_180[0x204 - 0x180];
    int     field_204;  /* 0x204 */
    int     field_208;  /* 0x208 */
    char    pad_20C[0x238 - 0x20C];
    short   field_238;  /* 0x238 */
} DescentWork;

typedef struct _CamBbox
{
    char    pad_00[8];
    u_short field_08;
    char    pad_0A[0x10 - 0x0A];
    u_short field_10;
    char    pad_12[0x14 - 0x12];
    u_short field_14;
    char    pad_16[0x1C - 0x16];
    u_short field_1C;
} CamBbox;

typedef struct _CamModel
{
    char     pad_000[0x420];
    CamBbox *field_420;
    char     pad_424[0x4AC - 0x424];
    u_short  field_4AC;
    char     pad_4AE[0x4B0 - 0x4AE];
    u_short  field_4B0;
    char     pad_4B2[0x4B4 - 0x4B2];
    u_short  field_4B4;
} CamModel;

typedef struct _CamEb0
{
    char    pad_000[0x1C0];
    TARGET *field_1C0;      /* 0x1C0 */
} CamEb0;

typedef struct _CamActor
{
    char      pad_000[0x20];
    CONTROL   control;         /* 0x020 */
    char      pad_09C[0xB0 - 0x9C];
    int       field_B0;        /* 0x0B0 */
    int       field_B4;        /* 0x0B4 */
    int       field_B8;        /* 0x0B8 */
    char      pad_BC[0xDC - 0xBC];
    CamModel *field_DC;        /* 0x0DC */
    char      pad_E0[0x718 - 0xE0];
    TARGET   *field_718[10];   /* 0x718 */
    char      pad_740[0x744 - 0x740];
    int       field_744;       /* 0x744 */
    int       field_748;       /* 0x748 */
    char      pad_74C[0xD54 - 0x74C];
    int       field_D54;       /* 0xD54 */
    char      pad_D58[0xD64 - 0xD58];
    int       field_D64;       /* 0xD64 */
    int       field_D68;       /* 0xD68 */
    char      pad_D6C[0xD74 - 0xD6C];
    int       field_D74;       /* 0xD74 */
    char      pad_D78[0xD88 - 0xD78];
    int       field_D88;       /* 0xD88 */
    int       field_D8C;       /* 0xD8C */
    char      pad_D90[0xDA0 - 0xD90];
    int       field_DA0;       /* 0xDA0 */
    char      pad_DA4[0xDEC - 0xDA4];
    int       field_DEC;       /* 0xDEC */
    int       field_DF0;       /* 0xDF0 */
    int       field_DF4;       /* 0xDF4 */
    int       field_DF8;       /* 0xDF8 */
    int       field_DFC;       /* 0xDFC */
    char      pad_E00[0xE0C - 0xE00];
    int       field_E0C;       /* 0xE0C */
    char      pad_E10[0xE60 - 0xE10];
    int       field_E60;       /* 0xE60 */
    char      pad_E64[0xEB0 - 0xE64];
    CamEb0   *field_EB0;       /* 0xEB0 */
    char      pad_EB4[0xED0 - 0xEB4];
    int       field_ED0;       /* 0xED0 */
    char      pad_ED4[0xF4C - 0xED4];
    int       field_F4C;       /* 0xF4C */
    int       field_F50;       /* 0xF50 */
    char      pad_F54[0xF5C - 0xF54];
    int       field_F5C;       /* 0xF5C */
    char      pad_F60[0xF78 - 0xF60];
    int       field_F78;       /* 0xF78 */
    char      pad_F7C[0x102C - 0xF7C];
    HZD_FLR   trap;            /* 0x102C */
} CamActor;

typedef struct _Sol
{
    GV_ACT    actor;       /* 0x000 */
    CONTROL   control;     /* 0x020 */
    MATRIX    field_9C[2]; /* 0x09C light matrices */
    OBJECT    body;        /* 0x0DC */
    TARGET   *field_1C0;   /* 0x1C0 */
    HOMING   *field_1C4;   /* 0x1C4 */
    MATRIX    field_1C8;   /* 0x1C8 */
    int       field_1E8;   /* 0x1E8 */
    CamActor *field_1EC;   /* 0x1EC */
    char      pad_1F0[0x228 - 0x1F0];
    void     *field_228;   /* 0x228 */
    char      pad_22C[0x234 - 0x22C];
    char      field_234[0x284 - 0x234]; /* MOTION_CONTROL */
    char      field_284[0x4E8 - 0x284]; /* MOTION_SEGMENT[] */
    char      field_4E8[0x74C - 0x4E8]; /* MOTION_SEGMENT[] */
    char      field_74C[0x7C8 - 0x74C]; /* CONTROL (motion) */
    char      field_7C8[0x848 - 0x7C8]; /* SVECTOR rots[] */
} Sol;

extern CamActor *s05a_dword_800C362C;
extern CONTROL   s05a_dword_800E3800;

void s05a_800DDF18(Sol *work);
void s05a_800DEB94(Sol *work);
const char s05a_dword_800E356C[] = "m1e1sold.c";
const char s05a_dword_800E3578[] = "out_c_m1";
const char s05a_dword_800E3584[] = "tankman";
const char s05a_dword_800E358C[] = "out_cold";
const char s05a_dword_800E3598[] = {0x0, 0x0, 0x0, 0x0}; /* pad: jump tables are 8-aligned */
const int  s05a_dword_800E359C[] = {0x800DE0EC, 0x800DE0EC, 0x800DE0EC, 0x800DE40C, 0x800DE560, 0x800DE0EC, 0x800DE0EC}; /* s05a_800DDF18 */
const char s05a_dword_800E35B8[] = {0x0, 0x0, 0x0, 0x0};
const int  s05a_dword_800E35BC[] = {0x800DE654, 0x800DE654, 0x800DE5E4, 0x800DE610, 0x800DE654, 0x800DE600, 0x800DE654}; /* s05a_800DDF18 */
extern MATRIX DG_ZeroMatrix;

void *s05a_800DDCBC(CamActor *director)
{
    Sol      *work;
    int       one;
    int       name;
    int       i;
    OBJECT   *bodyp;
    const char *tankstr;
    DG_OBJS  *objs;
    SVECTOR   size;

    work = GV_NewActor(6, 0x848);
    if (work == NULL)
    {
        return 0;
    }
    one = 1;
    work->field_1E8 = one;
    work->field_1EC = director;
    GV_SetNamedActor(work, s05a_800DDF18, s05a_800DEB94, s05a_dword_800E356C);

    if (GM_InitControl(&work->control, work->field_1EC->field_744,
                       work->field_1EC->field_748) < 0)
    {
        GV_DestroyActor(work);
        return 0;
    }

    *(short *)((char *)&work->control + 0x36) = -2; /* sh -2, 0x56(s3) */
    *(char *)((char *)&work->control + 0x54) = 0;   /* sb 0, 0x74(s3) */
    GM_ConfigControlAttribute(&work->control, 5);

    *(int *)&work->field_9C[0].t[0] = *(int *)&work->field_1EC->field_B0;
    *(int *)&work->field_9C[0].t[1] = *(int *)&work->field_1EC->field_B4;
    *(int *)&work->field_9C[0].t[2] = *(int *)&work->field_1EC->field_B8;
    name = GV_StrCode(s05a_dword_800E3578);  /* "out_" */

    tankstr = s05a_dword_800E3584;
    bodyp = &work->body;
    GM_InitObject(bodyp, name, 0x32d, GV_StrCode(tankstr));
    GM_ConfigObjectJoint(bodyp);
    GM_ConfigMotionControl(bodyp, (MOTION_CONTROL *)work->field_234,
                           GV_StrCode(tankstr),
                           (MOTION_SEGMENT *)work->field_284,
                           (MOTION_SEGMENT *)work->field_4E8,
                           (CONTROL *)work->field_74C,
                           (SVECTOR *)work->field_7C8);
    GM_ConfigObjectLight(bodyp, &work->field_9C[0]);

    objs = bodyp->objs;
    *(int *)&objs->flag |= 0x80;
    work->field_1C4 = GM_AllocHomingTarget(&work->field_1C8, &work->control);
    work->field_1C4->flag = one;
    work->field_1C0 = GM_AllocTarget();
    size.vx = 0x12c;
    size.vy = 0x12c;
    size.vz = 0x12c;
    GM_SetTarget(work->field_1C0, 0x94, 2, &size);
    GM_SetPowerTarget(work->field_1C0, 1, -1, 0x2710, 0, &DG_ZeroVector);

    for (i = 0; i < 0x10; i++)
    {
        work->body.objs->objs[i].world = DG_ZeroMatrix;
    }
    return work;
}
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DDF18.s")

void s05a_800DEB94(Sol *work)
{
    work->field_1EC->field_EB0 = 0;
    if (work->field_228)
    {
        GV_DestroyActor(work->field_228);
    }
    GM_FreeObject(&work->body);
    GM_FreeControl(&work->control);
    if (work->field_1C0)
    {
        GM_FreeTarget(work->field_1C0);
    }
    if (work->field_1C4)
    {
        GM_FreeHomingTarget(work->field_1C4);
    }
}
int s05a_800DEC18(DescentWork *work, SVECTOR *s2, int a2)
{
    int     v;
    int     heights[2];
    SVECTOR local;

    v = 1;
    if (work->field_204 == 0)
    {
        work->field_208 = 0;
    }

    if (a2 - s2->vy <= 0)
    {
        work->field_204 += s2->vy - a2;
    }
    if (work->field_204 < 0x190)
    {
        return a2;
    }

    if (work->field_208 == 0)
    {
        v = work->field_238;
        if (v <= 0)
        {
            v = 1;
        }
    }

    local = *s2;
    local.vy += 0x2710;
    if (HZD_LevelHazardCheck(work->control.map->hzd, &local, HZD_CHK_FLOOR) != 1)
    {
        local.vy = 0;
    }
    else
    {
        HZD_GetLevelHeight(heights);
        local.vy = heights[0];
    }
    local.vy += 0x64;

    if (work->field_208 == 0)
    {
        work->field_208 = (s2->vy - local.vy) / v;
    }

    v = s2->vy - work->field_208;
    if (v < local.vy)
    {
        v = local.vy;
    }
    {
        int t = work->field_208 * 15;
        work->field_208 = t / 14;
    }
    if (work->field_208 >= 0x3E9)
    {
        work->field_208 = 0x3E8;
    }
    return v;
}
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DEDE8.s")
int s05a_800DF834(int arg0, SVECTOR *vec, u_short *arg3)
{
    SVECTOR d;
    SVECTOR e;
    int     dist;

    if (arg0 != 0)
    {
        return 0;
    }
    if (s05a_dword_800C362C->field_EB0 == NULL)
    {
        return 0;
    }

    d.vx = s05a_dword_800C362C->field_DC->field_4AC;
    d.vy = s05a_dword_800C362C->field_DC->field_4B0;
    d.vz = s05a_dword_800C362C->field_DC->field_4B4;
    d.vx -= vec->vx;
    d.vy -= vec->vy;
    d.vz -= vec->vz;

    e.vx = s05a_dword_800C362C->field_DC->field_420->field_14 -
           s05a_dword_800C362C->field_DC->field_420->field_08;
    e.vz = s05a_dword_800C362C->field_DC->field_420->field_1C -
           s05a_dword_800C362C->field_DC->field_420->field_10;
    e.vx = (e.vx + e.vz) >> 2;

    dist = SquareRoot0(d.vx * d.vx + d.vy * d.vy + d.vz * d.vz);
    if (dist < e.vx * s05a_dword_800C362C->field_DFC)
    {
        GM_SeSetPan(&s05a_dword_800C362C->field_EB0->field_1C0->center, 0xB2,
                    s05a_dword_800C362C->field_E60);
        *arg3 |= 4;
        return 1;
    }
    return 0;
}
int s05a_800DF9C8(TARGET *t, int flags)
{
    SVECTOR delta;
    SVECTOR e;
    int     i;
    short   dx, dy, dz;
    int     dist;

    if (s05a_dword_800C362C->field_ED0 != 0)
    {
        if (s05a_dword_800C362C->field_EB0 != 0)
        {
            s05a_dword_800C362C->field_EB0->field_1C0->vital = 0x2710;
            s05a_dword_800C362C->field_EB0->field_1C0->damage = 0;
            s05a_dword_800C362C->field_EB0->field_1C0->damaged = 0;
        }
        for (i = 0; i < 10; i++)
        {
            s05a_dword_800C362C->field_718[i]->vital = 0x2710;
            s05a_dword_800C362C->field_718[i]->damage = 0;
            s05a_dword_800C362C->field_718[i]->damaged = 0;
        }
        return 1;
    }

    if (s05a_dword_800C362C->field_EB0 != 0)
    {
        delta = s05a_dword_800C362C->field_EB0->field_1C0->center;
        dx = delta.vx - t->center.vx;
        delta.vx = dx;
        dy = delta.vy - t->center.vy;
        delta.vy = dy;
        dz = delta.vz - t->center.vz;
        delta.vz = dz;

        e.vx = s05a_dword_800C362C->field_DC->field_420->field_14 -
               s05a_dword_800C362C->field_DC->field_420->field_08;
        e.vz = s05a_dword_800C362C->field_DC->field_420->field_1C -
               s05a_dword_800C362C->field_DC->field_420->field_10;
        e.vx = (e.vx + e.vz) >> 2;

        if (flags & 4)
        {
            for (i = 0; i < 10; i++)
            {
                s05a_dword_800C362C->field_718[i]->vital = 0x2710;
                s05a_dword_800C362C->field_718[i]->damage = 0;
                s05a_dword_800C362C->field_718[i]->damaged = 0;
            }
            if (s05a_dword_800C362C->field_F5C > 0)
            {
                return 0;
            }
            s05a_dword_800C362C->field_EB0->field_1C0->damaged =
                (u_short)s05a_dword_800C362C->field_D74;
            return 1;
        }

        if (s05a_dword_800C362C->field_EB0->field_1C0->damaged != 0)
        {
            dist = SquareRoot0(dx * dx + dy * dy + dz * dz);
            if (dist < e.vx * s05a_dword_800C362C->field_DFC * 3 &&
                t->center.vy >=
                    s05a_dword_800C362C->field_EB0->field_1C0->center.vy - 0x3E8)
            {
                for (i = 0; i < 10; i++)
                {
                    s05a_dword_800C362C->field_718[i]->vital = 0x2710;
                    s05a_dword_800C362C->field_718[i]->damage = 0;
                    s05a_dword_800C362C->field_718[i]->damaged = 0;
                }
                if (s05a_dword_800C362C->field_F5C > 0)
                {
                    return 0;
                }
                s05a_dword_800C362C->field_EB0->field_1C0->damaged =
                    s05a_dword_800C362C->field_D74 / s05a_dword_800C362C->field_DEC;
                return (s05a_dword_800C362C->field_E0C -
                        s05a_dword_800C362C->field_EB0->field_1C0->damaged) < 1;
            }
        }

        s05a_dword_800C362C->field_EB0->field_1C0->vital = 0x2710;
        s05a_dword_800C362C->field_EB0->field_1C0->damage = 0;
        s05a_dword_800C362C->field_EB0->field_1C0->damaged = 0;
    }

    if (s05a_dword_800C362C->field_F4C > 0 ||
        s05a_dword_800C362C->field_F50 > 0 ||
        HZD_GetFloorHit((HZD_FLR *)((char *)s05a_dword_800C362C + 0x12AC), &t->center) == 1 ||
        HZD_GetFloorHit((HZD_FLR *)((char *)s05a_dword_800C362C + 0x102C), &t->center) == 1 ||
        HZD_GetFloorHit((HZD_FLR *)((char *)s05a_dword_800C362C + 0x10CC), &t->center) == 1)
    {
        for (i = 0; i < 10; i++)
        {
            s05a_dword_800C362C->field_718[i]->vital = 0x2710;
            s05a_dword_800C362C->field_718[i]->damage = 0;
            s05a_dword_800C362C->field_718[i]->damaged = 0;
        }
        return 0;
    }

    for (i = 0; i < 10; i++)
    {
        dx = s05a_dword_800C362C->field_718[i]->center.vx -
             t->center.vx;
        delta.vx = dx;
        dy = s05a_dword_800C362C->field_718[i]->center.vy -
             t->center.vy;
        delta.vy = dy;
        dz = s05a_dword_800C362C->field_718[i]->center.vz -
             t->center.vz;
        delta.vz = dz;
        if (s05a_dword_800C362C->field_718[i]->damaged != 0)
        {
            dist = SquareRoot0(dx * dx + dy * dy + dz * dz);
            if (dist >= 0x9C5)
            {
                s05a_dword_800C362C->field_718[i]->vital = 0x2710;
                s05a_dword_800C362C->field_718[i]->damage = 0;
                s05a_dword_800C362C->field_718[i]->damaged = 0;
            }
        }
    }

    if (s05a_dword_800C362C->field_D64 > s05a_dword_800C362C->field_D88 ||
        s05a_dword_800C362C->field_D68 > s05a_dword_800C362C->field_D8C)
    {
        for (i = 0; i < 10; i++)
        {
            if (s05a_dword_800C362C->field_718[i]->damaged != 0)
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
int s05a_800E0068(PlayerStatusFlag flag)
{
    return (GM_PlayerStatus & flag) != 0;
}

int s05a_800E0080(PlayerStatusFlag flag)
{
    int temp_v0;

    temp_v0 = GM_PlayerStatus | flag;
    GM_PlayerStatus = temp_v0;
    return temp_v0;
}

void s05a_800E0098(PlayerStatusFlag flag)
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
void s05a_800E0D38(CONTROL *control, HZD_HDL *hzd);
void s05a_800E0E28(CONTROL *work, HZD_HDL *hzd);
void s05a_800E0F64(CONTROL *work, HZD_HDL *hzd);
void s05a_800E1014(CONTROL *work, HZD_HDL *hzd);

int s05a_800E00EC(GV_ACT *actor)
{
    int      vy = 0;
    SnaInitWork *work = (SnaInitWork *)actor;
    HZD_HDL *hzd;
    SVECTOR  pos;
    SVECTOR  rot;
    int      time;
    int      dist;

    GM_uTenageMotion = -1;
    if (HZD_GetFloorHit(&s05a_dword_800C362C->trap, &work->control.mov) == 0 && !(GM_PlayerStatus & 0x1340))
    {
        if (s05a_dword_800C362C->field_EB0 != NULL)
        {
            pos = s05a_dword_800C362C->field_EB0->field_1C0->center;
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

    hzd = work->control.map->hzd;
    s05a_800E0D38(&work->control, hzd);
    GM_CurrentMap = work->control.map->index;

    if (work->control.r_sphere > 0)
    {
        work->control.n_touches = 0;
        if (work->control.hzd_height != -0x7fff)
        {
            vy = work->control.mov.vy;
            work->control.mov.vy = work->control.hzd_height;
        }
        s05a_800E0E28(&work->control, hzd);
        work->control.mov.vx += work->control.step.vx;
        work->control.mov.vz += work->control.step.vz;
        s05a_800E0F64(&work->control, hzd);
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
        s05a_800E1014(&work->control, hzd);
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
            s05a_800E1014(&work->control, hzd);
        }
    }

    if (!(work->control.skip_flag & CTRL_SKIP_TRAP))
    {
        work->control.evt.mov = work->control.mov;
        work->control.evt.mov.pad = work->control.rot.vy;
        HZD_EnterTrap(hzd, &work->control.evt);
    }
    DG_SetPos2(&work->control.mov, &work->control.rot);
    return 1;
}
int s05a_800E066C(SnaInitWork *work_)
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

    if (HZD_GetFloorHit((HZD_FLR *)&s05a_dword_800C362C->trap, &GM_PlayerPosition) != 0)
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
        *(int *)&work->body.objs->flag &= ~0x80;
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
void s05a_800E0D38(CONTROL *control, HZD_HDL *hzd)
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

void s05a_800E0E28(CONTROL *work, HZD_HDL *hzd)
{
    SVECTOR local;
    int     half;
    int     dist;
    int     len;
    int     diff;

    half = work->r_sphere / 2;
    dist = work->step.vx;
    if (dist < 0)
    {
        dist = -dist;
    }
    if (work->step.vz > 0)
    {
        dist += work->step.vz;
    }
    else
    {
        dist -= work->step.vz;
    }

    if (half < dist)
    {
        GV_AddVec3(&work->mov, &work->step, &local);
        if (HZD_OnlineHazardCheck(hzd, &work->mov, &local, 5, work->seg_flag) != 0)
        {
            work->n_touches = 1;
            work->segs[0] = HZD_GetOnlineHazard();
            work->is_edge[0] = HZD_GetOnlineHazardAtr();
            HZD_GetOnlineVector(&work->vecs[0]);
            len = GV_VecLen3(&work->vecs[0]);
            diff = len - half;
            if (diff < 0)
            {
                GV_LenVec3(&work->vecs[0], &local, len, -diff);
                GV_SubVec3(&DG_ZeroVector, &local, &local);
            }
            else
            {
                GV_LenVec3(&work->vecs[0], &local, len, diff);
            }
            work->step = local;
        }
    }
}
void s05a_800E0F64(CONTROL *work, HZD_HDL *hzd)
{
    SVECTOR react;
    int     hazard;

    hazard = HZD_NearHazardCheck(hzd, &work->mov, 0x1F4, 4, work->seg_flag);
    if (hazard > 0)
    {
        work->n_touches = hazard;
        HZD_GetNearHazard(&work->segs[0]);
        HZD_GetIsEdge(&work->is_edge[0]);
        HZD_GetNearVector(&work->vecs[0]);
        HZD_HazardReaction(&work->vecs[0], hazard, work->r_sphere, &react);
        work->mov.vx += react.vx;
        work->mov.vz += react.vz;
    }
}

void s05a_800E1014(CONTROL *work, HZD_HDL *hzd)
{
    int height[2];
    int flags;
    int y;
    int base;
    int lo;

    y = work->mov.vy + work->step.vy;
    base = work->height;
    work->grounded = 0;
    flags = HZD_LevelHazardCheck(hzd, &work->mov, HZD_CHK_F_FLOOR);
    HZD_GetLevelHeight(height);

    if (flags & HZD_CHK_D_FLOOR)
    {
        if ((unsigned int)(height[1] - work->levels[0] + 0xC7) < 0x18F)
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
        work->grounded = 1;
    }
    else if ((flags & HZD_CHK_D_FLOOR) && height[1] - base < y)
    {
        y = height[1] - base;
        work->grounded = 2;
    }

    work->levels[0] = height[0];
    lo = (work->levels[1] = height[1]);
    work->mov.vy = y;
}
