#include "game/game.h"
#include "linkvar.h"
#include "strcode.h"

typedef struct _Work
{
    GV_ACT  actor;    /* 0x000 */
    CONTROL control;   /* 0x020 */
    OBJECT  body;      /* 0x09C */
    char    pad_180[0x204 - 0x180];
    int     field_204; /* 0x204 */
    int     field_208; /* 0x208 */
    char    pad_20C[0x238 - 0x20C];
    short   field_238; /* 0x238 */
    char    pad_23A[0x894 - 0x23A];
    int     field_894; /* 0x894 */
    char    pad_898[0x89C - 0x898];
    u_short *field_89C; /* 0x89C */
    char    pad_8A0[0x9B8 - 0x8A0];
    int     field_9B8; /* 0x9B8 */
    int     field_9BC; /* 0x9BC */
    char    pad_9C0[0xA2A - 0x9C0];
    unsigned short field_A2A; /* 0xA2A */
    char    pad_A2C[0xA38 - 0xA2C];
    short   field_A38; /* 0xA38 */
    short   field_A3A; /* 0xA3A */
} Work;

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800DDCBC.s")
int s05a_800DEC18(Work *work, SVECTOR *s2, int a2)
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
    char      pad_09C[0xDC - 0x9C];
    CamModel *field_DC;        /* 0x0DC */
    char      pad_E0[0x718 - 0xE0];
    TARGET   *field_718[10];   /* 0x718 */
    char      pad_740[0xD54 - 0x740];
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
    char      pad_DF0[0xDFC - 0xDF0];
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

typedef struct _DfVec
{
    u_short field_0;
    u_short field_2;
    u_short field_4;
} DfVec;

typedef struct _UVec
{
    u_short vx;
    u_short vy;
    u_short vz;
    u_short pad;
} UVec;

extern CamActor *s05a_dword_800C362C;
extern CONTROL   s05a_dword_800E3800;

int s05a_800DF834(int arg0, DfVec *vec, u_short *arg3)
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
    d.vx -= vec->field_0;
    d.vy -= vec->field_2;
    d.vz -= vec->field_4;

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
    UVec    delta;
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
        delta = *(UVec *)&s05a_dword_800C362C->field_EB0->field_1C0->center;
        dx = delta.vx - ((UVec *)&t->center)->vx;
        delta.vx = dx;
        dy = delta.vy - ((UVec *)&t->center)->vy;
        delta.vy = dy;
        dz = delta.vz - ((UVec *)&t->center)->vz;
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
        dx = ((UVec *)&s05a_dword_800C362C->field_718[i]->center)->vx -
             ((UVec *)&t->center)->vx;
        delta.vx = dx;
        dy = ((UVec *)&s05a_dword_800C362C->field_718[i]->center)->vy -
             ((UVec *)&t->center)->vy;
        delta.vy = dy;
        dz = ((UVec *)&s05a_dword_800C362C->field_718[i]->center)->vz -
             ((UVec *)&t->center)->vz;
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

void s05a_800DFFC0(Work *work, int arg)
{
    short v;

    work->field_9B8 = arg;
    work->field_9BC = 0;
    work->field_A3A = 0;
    work->field_A38 = 0;
    v = 0;
    if (GM_PlayerStatus & PLAYER_GROUND)
    {
        v = work->field_A2A;
    }
    work->control.turn.vx = v;
    work->control.turn.vz = 0;
}

void s05a_800DFFF8(Work *work, int action, int interp)
{
    if (work->body.action != action)
    {
        GM_ConfigObjectAction(&work->body, action, 0, interp);
    }
}

void s05a_800E002C(Work *work, int action, int interp, u_long mask)
{
    if (work->body.action2 != action)
    {
        GM_ConfigObjectOverride(&work->body, action, 0, interp, mask);
    }
}

int s05a_800E0068(int mask)
{
    return (GM_PlayerStatus & mask) != 0;
}

int s05a_800E0080(int mask)
{
    return GM_PlayerStatus |= mask;
}

void s05a_800E0098(int mask)
{
    GM_PlayerStatus &= ~mask;
}

int s05a_800E00B0(Work *work, int mask)
{
    return work->field_894 |= mask;
}

int s05a_800E00C4(Work *work, int mask)
{
    return work->field_894 &= ~mask;
}

int s05a_800E00D8(Work *work, int mask)
{
    return (work->field_894 & mask) != 0;
}

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E00EC.s")
int s05a_800E066C(Work *work_)
{
    Work *work = work_;
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
        if (GM_SnakeCurrentHealth == 0)
        {
            GM_ActObject(&work->body);
            return 1;
        }
        if (GM_GameOverTimer != 0)
        {
            GM_ActObject(&work->body);
            return 1;
        }

        work->field_894 &= ~1;
        *work->field_89C |= 0x9e;
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
        if (work->field_89C[3] != 0)
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
void s05a_800E0D38(CONTROL *control)
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

void s05a_800E0E28(CONTROL *control, HZD_HDL *hzd)
{
    SVECTOR local;
    int     half = control->r_sphere / 2;
    int     dist = control->step.vx;

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
        if (HZD_OnlineHazardCheck(hzd, &control->mov, &local, HZD_CHK_FIX, control->seg_flag))
        {
            int len;
            int diff;

            control->n_touches = 1;
            control->segs[0] = HZD_GetOnlineHazard();
            control->is_edge[0] = HZD_GetOnlineHazardAtr();
            HZD_GetOnlineVector(control->vecs);
            len = GV_VecLen3(control->vecs);
            diff = len - half;
            if (diff < 0)
            {
                GV_LenVec3(control->vecs, &local, len, -diff);
                GV_SubVec3(&DG_ZeroVector, &local, &local);
            }
            else
            {
                GV_LenVec3(control->vecs, &local, len, diff);
            }
            control->step = local;
        }
    }
}
void s05a_800E0F64(CONTROL *control, HZD_HDL *hzd)
{
    SVECTOR react;
    int     n;

    n = HZD_NearHazardCheck(hzd, &control->mov, 0x1F4, HZD_CHK_F_SEGMENT, control->seg_flag);
    if (n > 0)
    {
        SVECTOR *vecs;

        control->n_touches = n;
        HZD_GetNearHazard(control->segs);
        HZD_GetIsEdge(control->is_edge);
        vecs = control->vecs;
        HZD_GetNearVector(vecs);
        HZD_HazardReaction(vecs, n, control->r_sphere, &react);
        control->mov.vx += react.vx;
        control->mov.vz += react.vz;
    }
}
#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800E1014.s")
