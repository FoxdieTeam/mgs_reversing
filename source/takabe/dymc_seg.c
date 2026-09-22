#include "dymc_seg.h"

#include "mgstype.h"
#include "strcode.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "takabe/thing.h"

/*---------------------------------------------------------------------------*/

typedef struct _Work {
    GV_ACT   actor;
    int      map;
    int      name;
    HZD_HDL *hzd;
    HZD_SEG  seg;
} Work;

static u_short msg_list[] = { HASH_ON2, HASH_OFF2 };

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    GM_CurrentMap = work->map;

    if (THING_Msg_CheckMessage(work->name, 2, msg_list) == 1)
    {
        GV_DestroyActor(&work->actor);
    }
}

static void Die(Work *work)
{
    HZD_DequeueDynamicSegment(work->hzd, &work->seg);
}

static int GetResources(Work *work, int name, int where)
{
    SVECTOR pos[ 2 ];
    int     height, seg_flag;
    HZD_SEG *seg;
    SVECTOR *vec;

    GM_CurrentMap = where;

    work->map = where;
    work->name = name;

    if (GCL_GetOption('p'))
    {
        GCL_StrToSV(GCL_NextStr(), (short *)&pos[ 0 ]);
        GCL_StrToSV(GCL_NextStr(), (short *)&pos[ 1 ]);
    }

    height = THING_Gcl_GetInt('h');
    seg_flag = THING_Gcl_GetInt('s');

    seg = &work->seg;

    vec = &pos[ 0 ];
    seg->p1.x = vec->vx;
    seg->p1.y = vec->vy;
    seg->p1.z = vec->vz;
    seg->p1.h = height;

    vec = &pos[ 1 ];
    seg->p2.x = vec->vx;
    seg->p2.y = vec->vy;
    seg->p2.z = vec->vz;
    seg->p2.h = height;

    HZD_SetDynamicSegment(seg, seg);

    work->hzd = GM_GetMap(where)->hzd;
    HZD_QueueDynamicSegment2(work->hzd, seg, seg_flag);
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewDynamicWallSet(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "dymc_seg.c");
        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
