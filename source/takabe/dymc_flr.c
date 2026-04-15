#include "dymc_flr.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "strcode.h"
#include "takabe/thing.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct _Work
{
    GV_ACT      actor;
    int         map;
    int         name;
    HZD_HDL    *hzd;
    HZD_FLR     flr;
} Work;

/*---------------------------------------------------------------------------*/

static unsigned short mesg_list[2] = {HASH_ON2, HASH_OFF2};

static void InitFloor(HZD_FLR *flr, SVECTOR *pos)
{
    VECTOR vec1, vec2;
    HZD_VEC *hzdvec;
    SVECTOR *svec;

    int xmin, ymin, zmin;
    int xmax, ymax, zmax;

    int i;

    zmax = -32000;
    ymax = -32000;
    xmax = -32000;

    zmin = 32000;
    ymin = 32000;
    xmin = 32000;

    svec = pos;
    hzdvec = &flr->p1;
    for (i = 4; i > 0; svec++, hzdvec++, i--)
    {
        hzdvec->x = svec->vx;
        hzdvec->y = svec->vy;
        hzdvec->z = svec->vz;

        if (xmax < svec->vx)
        {
            xmax = svec->vx;
        }
        if (svec->vx < xmin)
        {
            xmin = svec->vx;
        }

        if (ymax < svec->vy)
        {
            ymax = svec->vy;
        }
        if (svec->vy < ymin)
        {
            ymin = svec->vy;
        }

        if (zmax < svec->vz)
        {
            zmax = svec->vz;
        }
        if (svec->vz < zmin)
        {
            zmin = svec->vz;
        }
    }

    flr->b1.x = xmin;
    flr->b1.y = ymin;
    flr->b1.z = zmin;
    flr->b2.x = xmax;
    flr->b2.y = ymax;
    flr->b2.z = zmax;

    vec1.vx = (pos[1].vx - pos[0].vx) / 4;
    vec1.vy = (pos[1].vy - pos[0].vy) / 4;
    vec1.vz = (pos[1].vz - pos[0].vz) / 4;

    vec2.vx = (pos[2].vx - pos[1].vx) / 4;
    vec2.vy = (pos[2].vy - pos[1].vy) / 4;
    vec2.vz = (pos[2].vz - pos[1].vz) / 4;

    VectorNormal(&vec1, &vec1);
    VectorNormal(&vec2, &vec2);
    OuterProduct12(&vec1, &vec2, &vec1);
    flr->p1.h = vec1.vx >> 4;
    flr->p3.h = vec1.vy >> 4;
    flr->p2.h = vec1.vz >> 4;
}

static void Act(Work *work)
{
    GM_SetCurrentMap(work->map);
    if (THING_Msg_CheckMessage(work->name, 2, mesg_list) == 1)
    {
        GV_DestroyActor(&work->actor);
    }
}

static void Die(Work *work)
{
    HZD_DequeueDynamicFloor(work->hzd, &work->flr);
}

static int GetResources(Work *work, int name, int where)
{
    SVECTOR pos[4];
    int s_param;

    GM_SetCurrentMap(where);
    work->map = where;
    work->name = name;

    if (GCL_GetOption('p'))
    {
        GCL_StrToSV(GCL_GetParamResult(), &pos[0]);
        GCL_StrToSV(GCL_GetParamResult(), &pos[1]);
        GCL_StrToSV(GCL_GetParamResult(), &pos[2]);
        GCL_StrToSV(GCL_GetParamResult(), &pos[3]);
    }
    s_param = THING_Gcl_GetInt('s');

    InitFloor(&work->flr, pos);
    work->hzd = GM_GetMap(where)->hzd;
    HZD_QueueDynamicFloor(work->hzd, &work->flr);
    work->flr.b1.h |= s_param << 8;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewDynamicFloorSet(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "dymc_flr.c");
        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
