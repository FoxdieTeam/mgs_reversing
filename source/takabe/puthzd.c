#include "puthzd.h"

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "takabe/thing.h"

/* Places additional hazard data (walls and floors) from a .hzm file */

typedef struct _Work
{
    GV_ACT    actor;
    int       map;      // 0x20
    int       name;     // 0x24
    int       copy;     // 0x28
    SVECTOR   pos;      // 0x2C
    HZD_DEF  *def;      // 0x34
    HZD_GRP  *grp;      // 0x38
    HZD_HDL  *hzd;      // 0x3C
    int       n_flrs;   // 0x40
    int       n_segs;   // 0x44
    HZD_SEG  *segs;     // 0x48
    HZD_FLR  *flrs;     // 0x4C
} Work;

#define EXEC_LEVEL GV_ACTOR_USER

unsigned short puthzd_msgs[2] = {0xD182, 0x006B};

static void QueueHazard(Work *work, HZD_GRP *grp);
static void DequeueHazard(Work *work, HZD_GRP *grp);
static void CopyHazard(Work *work, HZD_GRP *grp);

static void Act(Work *work)
{
    GM_CurrentMap = work->map;

    if (THING_Msg_CheckMessage(work->name, 2, puthzd_msgs) == 1)
    {
        THING_Hzd_800C4874(work->n_segs, work->segs, work->n_flrs, work->flrs);
        GV_DestroyActor(&work->actor);
    }
}

static void Die(Work *work)
{
    DequeueHazard(work, work->grp);

    if (work->copy)
    {
        GV_Free(work->segs);
    }
}

static int GetResources(Work *work, int name, int map)
{
    work->map = map;
    GM_CurrentMap = map;
    work->name = name;
    work->hzd = GM_GetMap(work->map)->hzd;

    if (GCL_GetOption('p'))
    {
        work->copy = 1;
        GCL_StrToSV(GCL_NextStr(), (short *)&work->pos);
    }

    if (!GCL_GetOption('h'))
    {
        return 0;
    }

    work->def = GV_GetCache(GV_CacheID(GCL_StrToInt(GCL_NextStr()), 'h'));
    work->grp = work->def->groups;

    work->n_segs = work->grp->n_walls;
    work->n_flrs = work->grp->n_floors;

    if (work->copy)
    {
        work->segs = GV_Malloc((work->n_flrs * 3 + work->n_segs) * sizeof(HZD_SEG));
        work->flrs = (HZD_FLR *)(work->segs + work->n_segs);
        CopyHazard(work, work->grp);
    }
    else
    {
        work->segs = work->grp->walls;
        work->flrs = work->grp->floors;
    }

    QueueHazard(work, work->grp);
    return 0;
}

void *NewPutHazard(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "puthzd.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}

static void QueueHazard(Work *work, HZD_GRP *grp)
{
    HZD_SEG *seg;
    HZD_FLR *flr;
    char    *flags;
    char    *flags2;
    int      i;

    seg = work->segs;
    flags = grp->wallsFlags;
    flags2 = flags + grp->n_walls;

    for (i = work->n_segs; i > 0; i--)
    {
        HZD_QueueDynamicSegment2(work->hzd, seg++, *flags | (*flags2 << 8));
        flags++;
        flags2++;
    }

    flr = work->flrs;
    for (i = work->n_flrs; i > 0; i--)
    {
        HZD_QueueDynamicFloor(work->hzd, flr);
        flr++;
    }
}

static void DequeueHazard(Work *work, HZD_GRP *grp)
{
    HZD_SEG *seg;
    HZD_FLR *flr;
    int      i;

    seg = work->segs;
    for (i = work->n_segs; i > 0; i--)
    {
        HZD_DequeueDynamicSegment(work->hzd, seg);
        seg++;
    }

    flr = work->flrs;
    for (i = work->n_flrs; i > 0; i--)
    {
        HZD_DequeueDynamicFloor(work->hzd, flr);
        flr++;
    }
}

static void CopyHazard(Work *work, HZD_GRP *grp)
{
    HZD_SEG *src_seg, *dst_seg;
    HZD_FLR *src_flr, *dst_flr;
    int      x, y, z;
    int      i;

    src_seg = grp->walls;
    dst_seg = work->segs;

    x = work->pos.vx;
    y = work->pos.vy;
    z = work->pos.vz;

    for (i = work->n_segs; i > 0; i--)
    {
        *dst_seg = *src_seg++;

        dst_seg->p1.x += x;
        dst_seg->p1.y += y;
        dst_seg->p1.z += z;
        dst_seg->p2.x += x;
        dst_seg->p2.y += y;
        dst_seg->p2.z += z;
        dst_seg++;
    }

    src_flr = grp->floors;
    dst_flr = work->flrs;

    for (i = work->n_flrs; i > 0; i--)
    {
        *dst_flr = *src_flr++;

        dst_flr->b1.x += x;
        dst_flr->b1.y += y;
        dst_flr->b1.z += z;
        dst_flr->b2.x += x;
        dst_flr->b2.y += y;
        dst_flr->b2.z += z;
        dst_flr->p1.x += x;
        dst_flr->p1.y += y;
        dst_flr->p1.z += z;
        dst_flr->p2.x += x;
        dst_flr->p2.y += y;
        dst_flr->p2.z += z;
        dst_flr->p3.x += x;
        dst_flr->p3.y += y;
        dst_flr->p3.z += z;
        dst_flr->p4.x += x;
        dst_flr->p4.y += y;
        dst_flr->p4.z += z;
        dst_flr++;
    }
}
