#include "mgstype.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "libhzd/libhzd.h"

extern const char s11d_aSocomf_800D1E40[];

int     s11d_dword_800C330C = 0x60;
SVECTOR s11d_dword_800C3310 = { 0, -1440, 2980 };

#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE )

typedef struct _HindPoint
{
    u_short x;
    u_short y;
    u_short z;
    u_short command;
} HindPoint;

// same layout as HZD_PTP
typedef struct _HindRoutePoint
{
    u_short x;
    u_short z;
    u_short y;
    u_short command;
} HindRoutePoint;

typedef struct _HindEventSrc
{
    u_short         count;
    u_short         pad;
    HindRoutePoint *data;
} HindEventSrc;

/* work->flags */
#define HIND_FLAG_FOLLOW_Y   0x01   /* follow the player's height ('s' option) */
#define HIND_FLAG_EVENT      0x02   /* run route point type 1 events */
#define HIND_FLAG_STINGER    0x04   /* switched to the stinger route */
#define HIND_FLAG_HOVER      0x10   /* 'h' option given */
#define HIND_FLAG_HOVERING   0x20
#define HIND_FLAG_FACE       0x80   /* face the player (route command type 4) */
#define HIND_FLAG_MSG_FFFA   0x100

typedef struct _Work
{
    GV_ACT     actor;
    CONTROL    control;
    OBJECT     body;
    MATRIX     light[2];
    int        field_1C0;
    int        field_1C4;
    union
    {
        int    i;
        u_char c;           /* s11d_hind_800CA424 tests HIND_FLAG_FACE bytewise */
    } flags;
    u_short    field_1CC;
    u_short    field_1CE;
    SVECTOR    field_1D0;
    SVECTOR    field_1D8;
    u_short    field_1E0;
    u_short    field_1E2;
    short      field_1E4;
    short      field_1E6;
    short      field_1E8;
    short      field_1EA;
    short      field_1EC;
    short      field_1EE;
    short      speed;           /* 0x1F0: also the arrival distance */
    short      max_roll;        /* 0x1F2: 'z' */
    short      rotor_speed;     /* 0x1F4: 'w' main rotor */
    short      tail_rotor_speed;/* 0x1F6: 'w' tail rotor */
    SVECTOR    field_1F8;
    u_short    n_routes;
    u_short    n_points[7];
    HindPoint  routes[7][32];
    HindPoint *point;
    u_short    route;
    u_short    point_idx;
    int        arrived;
    int        stinger_route;
    int        field_920;
    DG_PRIM   *prim;
    SVECTOR    prim_pos;
    RECT       prim_rect;
    DG_TEX    *tex;
    int        field_93C[7];
    int        field_958;
    int        field_95C;
    int        field_960;
    int        roll;
    char       pad_968[0x978 - 0x968];
    short      se_timer;
    short      se_id;
} Work;

int s11d_hind_800C976C(short *p, int target, int step)
{
    short val = *p;
    int   diff = target - val;

    if (diff < -step)
    {
        *p = val - step;
    }
    else if (diff > step)
    {
        *p = val + step;
    }
    else
    {
        *p = val + diff;
    }
    return *p == target;
}

void s11d_hind_800C97B8(Work *work)
{
    OBJECT *body;
    int     rot;

    body = &work->body;

    rot = body->rots[1].vy;
    rot = (body->rots[1].vy + work->rotor_speed) & 0xFFF;
    body->rots[1].vy = rot;

    rot = body->rots[2].vx;
    rot = (rot + work->tail_rotor_speed) & 0xFFF;
    body->rots[2].vx = rot;
}

void s11d_hind_800C97F0(Work *work)
{
    if (work->se_timer > 0)
    {
        work->se_timer--;
        if (work->se_timer == 0)
        {
            GM_SeSetMode(&work->control.mov, work->se_id, GM_SEMODE_BOMB);
        }
    }
}

void s11d_hind_800C9838(Work *work)
{
    SVECTOR svec;
    (void)svec;

    if ((GV_Time & 3) == 0)
    {
        GM_SeSetMode(&work->control.mov, 182, GM_SEMODE_BOMB);
    }
}

void s11d_hind_800C9870(Work *work)
{
    int v1 = (work->point->command & 0x300) >> 8;

    if (v1 == 3)
    {
        GV_DestroyActor(work);
        return;
    }

    if (v1 == 1)
    {
        if (work->flags.i & 2)
        {
            work->field_1CC = 1;
            work->field_1CE = (u_char)work->point->command >> 5;
            return;
        }
    }
    else if (v1 != 2)
    {
        return;
    }

    work->field_1CC = 0;
    work->field_1CE = 0xFFFF;
    work->field_1C4 = 0;
}

void s11d_hind_800C9908(Work *work, int arg1)
{
    HindPoint *event;
    int masked;
    int shifted;

    arg1--;
    work->route = arg1;
    event = work->routes[arg1];
    work->point_idx = 1;
    work->point = event;

    masked = event->command & 0x1F;
    shifted = masked << 5;
    if (shifted != 0)
    {
        work->speed = shifted;
    }

    if (work->flags.i & 0x10)
    {
        work->flags.i |= 0x20;
        work->field_958 = 0;
        work->field_1EA = 0;
        work->field_1E8 = 0;
        work->field_1EC = work->control.mov.vy;
    }

    work->flags.i &= ~0x80;
    if (((u_char)work->point->command >> 5) == 4)
    {
        work->flags.i |= 0x80;
    }
}

void s11d_hind_800C99A8(Work *work)
{
    int a1 = (work->point->command & 0x1C00) >> 10;
    if (a1 == 0)
    {
        a1 = work->route + 1;
    }

    s11d_hind_800C9908(work, a1);
}

void s11d_hind_800C99F4(Work *work)
{
    SVECTOR diff;
    SVECTOR cur;
    SVECTOR target;
    SVECTOR dir_step;
    int     speed;
    int     dist;
    int     turn;

    work->arrived = 0;

    cur = work->control.mov;
    target = *(SVECTOR *)work->point;

    if (work->flags.i & 1)
    {
        target.vy = 0;
        cur.vy = 0;
    }

    GV_SubVec3(&target, &cur, &diff);
    dist = GV_VecLen3(&diff);

    if (dist < work->speed)
    {
        work->arrived = 1;
    }

    turn = GV_DiffDirS(work->control.turn.vy, GV_VecDir2(&diff));
    if (turn < -24)
    {
        turn = -24;
    }
    else if (turn > 24)
    {
        turn = 24;
    }

    work->control.interp = 15;
    work->control.turn.vy += turn;

    GV_LenVec3(&diff, &dir_step, dist, work->speed);

    speed = work->speed / 8;
    s11d_hind_800C976C(&work->control.step.vx, dir_step.vx, speed);
    s11d_hind_800C976C(&work->control.step.vz, dir_step.vz, speed);

    if (work->flags.i & 1)
    {
        dist = GM_PlayerPosition.vy - (work->control.mov.vy + work->field_1D8.vy);
        if (dist < -128)
        {
            dist = -128;
        }
        if (dist > 128)
        {
            dist = 128;
        }
        work->control.step.vy = dist;
    }
    else
    {
        work->control.step.vy = 0;
    }
}

void s11d_hind_800C9B94(Work *work)
{
    CONTROL *ctrl;
    int      dir;
    int      diff;

    ctrl = &work->control;
    dir = GV_DiffDirS(ctrl->turn.vy, ctrl->rot.vy);

    if (dir == 0)
    {
        if (work->roll < -4)
        {
            work->roll = work->roll + 4;
        }
        else if (work->roll < 5)
        {
            work->roll = 0;
        }
        else
        {
            work->roll = work->roll - 4;
        }
    }
    else if (dir > 0)
    {
        diff = work->max_roll - work->roll;
        if (diff < -16)
        {
            work->roll = work->roll - 16;
        }
        else if (diff > 16)
        {
            work->roll = work->roll + 16;
        }
        else
        {
            work->roll = work->roll + diff;
        }
    }
    else
    {
        diff = -work->max_roll - work->roll;
        if (diff < -16)
        {
            work->roll = work->roll - 16;
        }
        else if (diff > 16)
        {
            work->roll = work->roll + 16;
        }
        else
        {
            work->roll = work->roll + diff;
        }
    }

    ctrl->turn.vz += work->roll;
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9C7C.s")
void s11d_hind_800C9C7C(Work *work);

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9D60.s")
void s11d_hind_800C9D60(Work *work);

void s11d_hind_800CA424(Work *work)
{
    SVECTOR svec_b;
    SVECTOR svec_a;

    if (work->flags.c >> 7)
    {
        svec_a = GM_PlayerPosition;
        svec_a.vx = 0;
        GV_SubVec3(&svec_a, &work->control.mov, &svec_b);
        work->control.turn.vy = GV_VecDir2(&svec_b);
    }
}

void s11d_hind_800CA49C(Work *work)
{
    if (work->control.mov.vz < -14000 && work->control.mov.vx >= -3999 && work->control.mov.vx < 3000)
    {
        DG_InvisibleObjs(work->body.objs);
    }
    else
    {
        DG_VisibleObjs(work->body.objs);
    }
}

void s11d_hind_800CA504(Work *work)
{
    GV_MSG *msg;
    int     n_msgs;
    int     idx;
    int     code_5A47;
    int     code_983F;
    int     code_6A3E;

    if (work->flags.i & 4)
    {
        return;
    }

    code_5A47 = 0x5A47;
    if (GM_Weapon == WP_Stinger)
    {
        work->field_1CC = 0;
        s11d_hind_800C9908(work, work->stinger_route);
        work->flags.i |= 4;
        return;
    }

    code_983F = 0x983F;
    code_6A3E = 0x6A3E;
    if (work->control.n_msg == 0)
    {
        return;
    }

    n_msgs = work->control.n_msg;

    msg = &work->control.msg[n_msgs] - 1;

    for (; n_msgs > 0; n_msgs--, msg--)
    {
        int mask_2 = ~2;
        int mask_11 = ~0x11;

        if (msg->message[0] == code_5A47)
        {
            if (msg->message[1] == 0)
            {
                work->flags.i &= mask_2;
            }
            else
            {
                work->flags.i |= 2;
            }
        }
        else if (msg->message[0] == code_983F)
        {
            if (msg->message[1] == 0)
            {
                work->flags.i &= mask_11;
            }
            else
            {
                work->flags.i |= 1;
            }
        }
        else if (msg->message[0] == code_6A3E)
        {
            idx = msg->message[1];
            if (idx >= 0 || idx < work->n_routes)
            {
                work->field_1CC = 0;
                s11d_hind_800C9908(work, idx);
            }
        }
        else if (msg->message[0] == 0xFFFA)
        {
            work->field_1E0 = msg->message[1];
            work->field_1E2 = msg->message[2];
            work->flags.i |= 0x100;
        }
    }
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CA6D8.s")
void s11d_hind_800CA6D8(Work *work, int arg1);
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CABA8.s")
void s11d_hind_800CABA8(Work *work, int arg1);

void s11d_hind_800CAD9C(Work *work)
{
    int masked;
    int shifted;

    s11d_hind_800C99F4(work);
    if (work->arrived == 0)
    {
        return;
    }

    s11d_hind_800C9870(work);

    if (work->point_idx == work->n_points[work->route])
    {
        s11d_hind_800C99A8(work);
        return;
    }

    work->control.interp = 0xF;
    work->point++;
    work->point_idx++;

    masked = work->point->command & 0x1F;
    shifted = masked << 5;
    if (shifted != 0)
    {
        work->speed = shifted;
    }

    work->flags.i &= ~0x80;
    if (((u_char)work->point->command >> 5) == 4)
    {
        work->flags.i |= 0x80;
    }
}

void s11d_hind_800CAE6C(Work *work)
{
    s11d_hind_800CA49C(work);
    s11d_hind_800CA504(work);

    if (work->flags.i & 0x20)
    {
        s11d_hind_800C9D60(work);
    }
    else
    {
        s11d_hind_800CAD9C(work);
        s11d_hind_800C9C7C(work);
        s11d_hind_800C9B94(work);
    }

    s11d_hind_800CA424(work);
    work->prim->type |= DG_FLAG_AMBIENT;

    if (work->field_1CC == 1)
    {
        int n = work->field_1C4;
        work->field_1C4 = n + 1;
        s11d_hind_800CABA8(work, n);
    }

    s11d_hind_800C97F0(work);
}

void s11d_hind_800CAF20(Work *work)
{
    CONTROL *ctrl = &work->control;
    OBJECT  *body = &work->body;

    GM_ActControl(ctrl);
    work->control.mov.vy += work->control.step.vy;
    GM_ActObject2(body);
    DG_GetLightMatrix(&ctrl->mov, work->light);
    s11d_hind_800C97B8(work);
    s11d_hind_800C9838(work);
    s11d_hind_800CAE6C(work);
}

void s11d_hind_800CAF9C(Work *work)
{
    DG_PRIM *prim;

    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    prim = work->prim;
    if (prim)
    {
        DG_DequeuePrim(prim);
        DG_FreePrim(prim);
    }
}

int s11d_hind_800CAFEC(HindEventSrc *src, u_short *out_count, HindPoint *out)
{
    HindRoutePoint *in;
    u_short    n;
    int        i;

    n = src->count;
    *out_count = n;
    i = (u_short)n;
    i--;
    in = src->data;
    for (; i >= 0; i--)
    {
        out->x = in->x;
        out->y = in->y;
        out->z = in->z;
        out->command = in->command;
        in++;
        out++;
    }
    return 0;
}

int s11d_hind_800CB054(Work *work)
{
    HZD_DEF      *def;
    HindEventSrc *route;
    int           n_routes;
    int           i;
    u_short      *counts;
    int           vy;

    def = work->control.map->hzd->def;
    route = (HindEventSrc *)def->routes;
    n_routes = def->n_routes;
    counts = work->n_points;
    work->n_routes = n_routes;

    i = 0;
    while (i < n_routes)
    {
        if (s11d_hind_800CAFEC(route, counts, work->routes[i]) < 0)
        {
            return -1;
        }
        i++;
        route++;
        counts++;
    }

    work->speed = 0x20;

    if (!GCL_GetOption('r'))
    {
        return -1;
    }

    s11d_hind_800C9908(work, GCL_StrToInt(GCL_NextStr()));
    vy = work->control.mov.vy;
    work->control.mov = *(SVECTOR *)work->point;
    work->control.mov.vy = vy;
    work->arrived = 0;
    work->flags.i &= ~0x20;
    return 0;
}

int s11d_hind_800CB178(Work *work)
{
    DG_PRIM  *prim;
    RECT     *rect;
    DG_TEX   *tex;
    POLY_FT4 *pack;
    int       i;
    int       x, y, w, h;

    rect = &work->prim_rect;
    work->prim_rect.x = rect->y = 400;
    rect->w = rect->h = 800;
    work->prim_pos = DG_ZeroVector;

    work->prim = prim = GM_MakePrim(0x412, 1, &work->prim_pos, rect);
    if (prim == NULL)
    {
        return -1;
    }

    work->tex = DG_GetTexture(GV_StrCode(s11d_aSocomf_800D1E40));
    tex = work->tex;

    for (i = 0; i < 2; i++)
    {
        pack = prim->packs[i];
        setPolyFT4(pack);
        setRGB0(pack, 128, 128, 128);
        setSemiTrans(pack, 1);

        x = tex->off_x;
        w = tex->w;
        pack->u0 = pack->u2 = x;
        pack->u1 = pack->u3 = x + (w + 1) / 2 - 1;

        y = tex->off_y;
        h = tex->h;
        pack->v0 = pack->v1 = y;
        pack->v2 = pack->v3 = y + (h + 1) / 2 - 1;

        pack->tpage = tex->tpage;
        pack->clut = tex->clut;
        pack->tpage = (pack->tpage & ~0x60) | (1 << 5);
    }

    prim->type |= DG_FLAG_AMBIENT;
    return 0;
}

void s11d_hind_800CB310(Work *work)
{
    int *p;
    int  i;
    u_char *param;

    if (!GCL_GetOption('h'))
    {
        return;
    }

    i = 0;
    p = work->field_93C;
    while ((param = GCL_NextStr()))
    {
        if (i == 7)
        {
            break;
        }
        *p = GCL_StrToInt(param);
        p++;
        i++;
    }

    work->flags.i |= 0x10;
}

int s11d_hind_800CB3A0(Work *work, int name, int where)
{
    CONTROL *control;
    OBJECT  *body;
    char    *pos;
    char    *dir;
    char    *model;
    char    *opt;
    int      count;
    int      i;

    control = &work->control;

    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    pos = GCL_GetOption('p');
    dir = GCL_GetOption('d');
    GM_ConfigControlString(control, pos, dir);

    GM_ConfigControlAttribute(control, 1);
    GM_ConfigControlTrapCheck(control);
    GM_ConfigControlHazard(control, 0, -2, -2);

    control->seg_flag = 2;

    model = GCL_GetOption('m');
    if (!model)
    {
        return -1;
    }

    body = &work->body;
    GM_InitObject(body, GCL_StrToInt(model), BODY_FLAG, 0);
    GM_ConfigObjectJoint(body);
    GM_ConfigObjectLight(body, work->light);

    work->field_1CE = 1;
    work->field_1CC = 0;
    work->field_1D0 = DG_ZeroVector;
    work->flags.i = 0;
    work->field_1C0 = 0;
    work->field_1C4 = 0;
    work->field_1EA = 0;
    work->field_1E8 = 0;
    work->field_1EE = 0;
    work->field_1EC = 0;

    if (GCL_GetOption('w'))
    {
        work->rotor_speed = GCL_StrToInt(GCL_NextStr());
        work->tail_rotor_speed = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->rotor_speed = 0;
        work->tail_rotor_speed = 0;
    }

    if (GCL_GetOption('s'))
    {
        if (GCL_StrToInt(GCL_NextStr()))
        {
            work->flags.i |= 1;
        }
    }

    if (GCL_GetOption('x'))
    {
        work->field_95C = control->turn.vx = GCL_StrToInt(GCL_NextStr());
    }

    if (GCL_GetOption('z'))
    {
        work->max_roll = GCL_StrToInt(GCL_NextStr());
    }

    opt = GCL_GetOption('b');
    if (opt)
    {
        GCL_StrToSV(opt, (short *)&work->field_1F8);
    }
    else
    {
        work->field_1F8 = DG_ZeroVector;
    }

    opt = GCL_GetOption('e');
    if (opt)
    {
        work->field_920 = GCL_StrToInt(opt);
    }
    else
    {
        work->field_920 = -1;
    }

    if (GCL_GetOption('g'))
    {
        GCL_StrToSV(GCL_NextStr(), (short *)&work->field_1D8);
    }
    else
    {
        work->field_1D8 = s11d_dword_800C3310;
    }

    if (GCL_GetOption('a'))
    {
        work->stinger_route = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->stinger_route = 0;
    }

    if (s11d_hind_800CB054(work) < 0)
    {
        return -1;
    }

    if (s11d_hind_800CB178(work) < 0)
    {
        return -1;
    }

    s11d_hind_800CB310(work);

    count = GM_GameLevel;
    if (count < 0)
    {
        count = 0;
    }

    if (GCL_GetOption('y'))
    {
        i = 0;
        while (i < count)
        {
            i++;
            GCL_GetNextInt();
        }
        s11d_dword_800C330C = GCL_GetNextInt();
    }

    return 0;
}

void *NewHind(int name, int where)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(work, s11d_hind_800CAF20, s11d_hind_800CAF9C, "hind.c");

    if (s11d_hind_800CB3A0(work, name, where) < 0)
    {
        GV_DestroyActor(work);
        return NULL;
    }

    return work;
}
