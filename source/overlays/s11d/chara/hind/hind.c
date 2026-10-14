#include "mgstype.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "libhzd/libhzd.h"

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

typedef struct _Work
{
    GV_ACT   actor; 
    CONTROL  control;
    OBJECT   body;
    char     pad_object[0x180 - 0x9C - sizeof(OBJECT)];
    MATRIX   field_180;
    char     pad_1a0[0x1C4 - 0x180 - sizeof(MATRIX)];
    int      field_1C4;
    u_char   field_1C8;
    char     pad_1c9[0x1CC - 0x1C8 - sizeof(u_char)];
    u_short  field_1CC;
    u_short  field_1CE;
    char     pad_1d0[0x1E8 - 0x1CC - sizeof(u_short) * 2];
    short    field_1E8;
    short    field_1EA;
    short    field_1EC;
    char     pad_1ee[0x1F0 - 0x1EC - sizeof(short)];
    short    field_1F0;
    short    field_1F2;
    short    field_1F4;
    short    field_1F6;
    char     pad_1f8[0x200 - 0x1F8];
    short    field_200;
    u_short  field_202[7];
    HindPoint events[7][32];
    u_short *field_910;
    u_short  field_914;
    u_short  field_916;
    int      field_918;
    char     pad_91c[0x924 - 0x918 - sizeof(int)];
    DG_PRIM *field_924;
    char     pad_928[0x93C - 0x924 - sizeof(DG_PRIM *)];
    int      field_93C[7];
    int      field_958;
    int      field_95C;
    char     pad_960[0x964 - 0x960];
    int      field_964;
    char     pad_968[0x978 - 0x968];
    short    f978;
    short    f97A;
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
    rot = (body->rots[1].vy + work->field_1F4) & 0xFFF;
    body->rots[1].vy = rot;

    rot = body->rots[2].vx;
    rot = (rot + work->field_1F6) & 0xFFF;
    body->rots[2].vx = rot;
}

void s11d_hind_800C97F0(Work *work)
{
    if (work->f978 > 0)
    {
        work->f978--;
        if (work->f978 == 0)
        {
            GM_SeSetMode(&work->control.mov, work->f97A, GM_SEMODE_BOMB);
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
    int v1 = (work->field_910[3] & 0x300) >> 8;

    if (v1 == 3)
    {
        GV_DestroyActor(work);
        return;
    }

    if (v1 == 1)
    {
        if (*(int *)&work->field_1C8 & 2)
        {
            work->field_1CC = 1;
            work->field_1CE = ((u_char *)work->field_910)[6] >> 5;
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
    u_short *event;
    int masked;
    int shifted;

    arg1--;
    work->field_914 = arg1;
    event = (u_short *)((char *)work + (arg1 * 256 + 0x210));
    work->field_916 = 1;
    work->field_910 = event;

    masked = event[3] & 0x1F;
    shifted = masked << 5;
    if (shifted != 0)
    {
        work->field_1F0 = shifted;
    }

    if (*(int *)&work->field_1C8 & 0x10)
    {
        *(int *)&work->field_1C8 |= 0x20;
        work->field_958 = 0;
        work->field_1EA = 0;
        work->field_1E8 = 0;
        work->field_1EC = work->control.mov.vy;
    }

    *(int *)&work->field_1C8 &= ~0x80;
    if ((((u_char *)work->field_910)[6] >> 5) == 4)
    {
        *(int *)&work->field_1C8 |= 0x80;
    }
}

void s11d_hind_800C99A8(Work *work)
{
    int a1 = (work->field_910[3] & 0x1C00) >> 10;
    if (a1 == 0)
    {
        a1 = work->field_914 + 1;
    }

    s11d_hind_800C9908(work, a1);
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C99F4.s")
void s11d_hind_800C99F4(Work *work);

void s11d_hind_800C9B94(Work *work)
{
    CONTROL *ctrl;
    int      dir;
    int      diff;

    ctrl = &work->control;
    dir = GV_DiffDirS(ctrl->turn.vy, ctrl->rot.vy);

    if (dir == 0)
    {
        if (work->field_964 < -4)
        {
            work->field_964 = work->field_964 + 4;
        }
        else if (work->field_964 < 5)
        {
            work->field_964 = 0;
        }
        else
        {
            work->field_964 = work->field_964 - 4;
        }
    }
    else if (dir > 0)
    {
        diff = work->field_1F2 - work->field_964;
        if (diff < -16)
        {
            work->field_964 = work->field_964 - 16;
        }
        else if (diff > 16)
        {
            work->field_964 = work->field_964 + 16;
        }
        else
        {
            work->field_964 = work->field_964 + diff;
        }
    }
    else
    {
        diff = -work->field_1F2 - work->field_964;
        if (diff < -16)
        {
            work->field_964 = work->field_964 - 16;
        }
        else if (diff > 16)
        {
            work->field_964 = work->field_964 + 16;
        }
        else
        {
            work->field_964 = work->field_964 + diff;
        }
    }

    ctrl->turn.vz += work->field_964;
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9C7C.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800C9D60.s")

void s11d_hind_800CA424(Work *work)
{
    SVECTOR svec_b;
    SVECTOR svec_a;

    if (work->field_1C8 >> 7)
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

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CA504.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CA6D8.s")
#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CABA8.s")

void s11d_hind_800CAD9C(Work *work)
{
    int masked;
    int shifted;

    s11d_hind_800C99F4(work);
    if (work->field_918 == 0)
    {
        return;
    }

    s11d_hind_800C9870(work);

    if (work->field_916 == work->field_202[work->field_914])
    {
        s11d_hind_800C99A8(work);
        return;
    }

    work->control.interp = 0xF;
    work->field_910 += 4;
    work->field_916++;

    masked = work->field_910[3] & 0x1F;
    shifted = masked << 5;
    if (shifted != 0)
    {
        work->field_1F0 = shifted;
    }

    *(int *)&work->field_1C8 &= ~0x80;
    if ((((u_char *)work->field_910)[6] >> 5) == 4)
    {
        *(int *)&work->field_1C8 |= 0x80;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CAE6C.s")
void s11d_hind_800CAE6C(Work *work);

void s11d_hind_800CAF20(Work *work)
{
    CONTROL *ctrl = &work->control;
    OBJECT  *body = &work->body;

    GM_ActControl(ctrl);
    work->control.mov.vy += work->control.step.vy;
    GM_ActObject2(body);
    DG_GetLightMatrix(&ctrl->mov, &work->field_180);
    s11d_hind_800C97B8(work);
    s11d_hind_800C9838(work);
    s11d_hind_800CAE6C(work);
}

void s11d_hind_800CAF9C(Work *work)
{
    DG_PRIM *prim;

    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    prim = work->field_924;
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
    counts = work->field_202;
    work->field_200 = n_routes;

    i = 0;
    while (i < n_routes)
    {
        if (s11d_hind_800CAFEC(route, counts, work->events[i]) < 0)
        {
            return -1;
        }
        i++;
        route++;
        counts++;
    }

    work->field_1F0 = 0x20;

    if (!GCL_GetOption('r'))
    {
        return -1;
    }

    s11d_hind_800C9908(work, GCL_StrToInt(GCL_NextStr()));
    vy = work->control.mov.vy;
    work->control.mov = *(SVECTOR *)work->field_910;
    work->control.mov.vy = vy;
    work->field_918 = 0;
    *(int *)&work->field_1C8 &= ~0x20;
    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CB178.s")

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

    *(int *)&work->field_1C8 |= 0x10;
}

#pragma INCLUDE_ASM("asm/overlays/s11d/s11d_hind_800CB3A0.s")
int s11d_hind_800CB3A0(Work *work, int name, int where);

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
