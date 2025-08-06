#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "takabe/thing.h"

/*---------------------------------------------------------------------------*/

typedef struct _TexScrollPrims
{
    DR_MOVE move[3];
} TexScrollPrims;

typedef struct _TexScrollEntry
{
    DR_STP         stp[2];
    TexScrollPrims prims[0];
} TexScrollEntry;

typedef struct _Work
{
    GV_ACT          actor;
    int             map;
    int             name;
    int             f28;
    RECT            f2C;
    TexScrollEntry *f34;
    TexScrollPrims *f38[2];
    int             speed;
    int             n_entries;
    RECT            rects[0];
} Work;

unsigned short tex_scroll_msgs[] = {0x448B, 0xA8A4};

#define getTPageX(tp) (((tp) << 6) & 0x3c0)
#define getTPageY(tp) ((((tp) << 4) & 0x100) + (((tp) >> 2) & 0x200))

#define EXEC_LEVEL GV_ACTOR_LEVEL2

/*---------------------------------------------------------------------------*/

static void TexScrollInitRect_800C97D4(DG_TEX *tex, RECT *rect)
{
    rect->x = getTPageX(tex->tpage) + tex->off_x / 4;
    rect->y = getTPageY(tex->tpage) + tex->off_y;
    rect->w = tex->w / 4 + 1;
    rect->h = tex->h;
}

static void TexScrollMoveRects_800C9834(DR_MOVE *moves, RECT *arg1, RECT *arg2, int speed)
{
    RECT r;

    if (speed < 0)
    {
        speed += arg1->h;
    }

    if (speed > arg2->h)
    {
        speed = arg2->h;
    }

    r.x = arg1->x;
    r.y = arg1->y;
    r.w = arg1->w;
    r.h = speed;
    SetDrawMove(&moves[2], &r, arg2->x, arg2->y);

    r.x = arg1->x;
    r.y = arg1->y + speed;
    r.w = arg1->w;
    r.h = arg1->h - speed;
    SetDrawMove(&moves[1], &r, arg1->x, arg1->y);

    r.x = arg2->x;
    r.y = arg2->y;
    r.w = arg1->w;
    r.h = speed;
    SetDrawMove(&moves[0], &r, arg1->x, (arg1->y + arg1->h) - speed);
}

static void Act(Work *work)
{
    GV_MSG         *msg;
    int             n_msgs;
    int             speed;
    unsigned int   *ot;
    TexScrollPrims *prims;
    RECT           *rect;
    int             i;

    if (GV_PauseLevel != 0)
    {
        return;
    }

    n_msgs = GV_ReceiveMessage(work->name, &msg);
    for (; n_msgs > 0; n_msgs--)
    {
        speed = msg->message[0];
        speed &= 0x1FF;

        work->speed = speed;
        if (work->speed >= 256)
        {
            work->speed -= 512;
        }
    }

    switch (THING_Msg_CheckMessage(0x53B6, 2, tex_scroll_msgs))
    {
    case 0:
        work->f28 = 0;
        break;

    case 1:
        work->f28 = 1;
        break;
    }

    if (work->f28 != 0)
    {
        return;
    }

    ot = (unsigned int *)DG_ChanlOTag(1);
    prims = work->f38[GV_Clock];
    rect = work->rects;

    if (work->speed == 0)
    {
        return;
    }

    for (i = work->n_entries; i > 0; i--)
    {
        TexScrollMoveRects_800C9834(prims->move, rect, &work->f2C, work->speed);
        addPrim(ot, &prims->move[0]);
        addPrim(ot, &prims->move[1]);
        addPrim(ot, &prims->move[2]);
        rect++;
        prims++;
    }

    addPrim(ot, &work->f34->stp[GV_Clock]);
}

static void Die(Work *work)
{
    void *ptr;

    ptr = work->f34;
    if (ptr != NULL)
    {
        GV_DelayedFree(ptr);
    }
}

static int GetResources(Work *work, int name, int map, int n_entries)
{
    int     i;
    DG_TEX *tex;
    void   *ptr;

    if (GCL_GetOption('t') != NULL)
    {
        for (i = 0; i < n_entries; i++)
        {
            tex = DG_GetTexture(GCL_StrToInt(GCL_GetParamResult()));
            if (tex == NULL)
            {
                n_entries--;
                i--;
            }
            else
            {
                TexScrollInitRect_800C97D4(tex, &work->rects[i]);
            }
        }
    }
    else
    {
        n_entries = 0;
    }

    tex = DG_GetTexture(THING_Gcl_GetShortDefault('w', GV_StrCode("scrl_tmp")));
    if (tex == NULL)
    {
        return -1;
    }

    TexScrollInitRect_800C97D4(tex, &work->f2C);

    work->speed = THING_Gcl_GetIntDefault('s', 1);

    ptr = GV_Malloc(sizeof(TexScrollEntry) + sizeof(TexScrollPrims) * n_entries * 2);
    work->f34 = ptr;
    work->f38[0] = work->f34->prims;
    work->f38[1] = work->f38[0] + n_entries;

    SetDrawStp(&work->f34->stp[0], 0);
    SetDrawStp(&work->f34->stp[1], 0);

    work->map = map;
    work->name = name;
    work->n_entries = n_entries;

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewTexScroll(int name, int where)
{
    int     n_entries;
    Work   *work;

    n_entries = THING_Gcl_GetIntDefault('n', 1);
    work = GV_NewActor(EXEC_LEVEL, sizeof(Work) + sizeof(RECT) * n_entries);
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "tex_scrl.c");

        if (GetResources(work, name, where, n_entries) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
