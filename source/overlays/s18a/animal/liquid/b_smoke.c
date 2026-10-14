#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"

/* black smoke rising from REX, puffs from up to 4 positions in turn */

#define MAX_SMOKE 4

typedef struct _Work
{
    GV_ACT  actor;
    SVECTOR pos[MAX_SMOKE];    /* 0x20 */
    u_char  timing[MAX_SMOKE]; /* 0x40 */
    int     n_pos;             /* 0x44 */
    int     time;              /* 0x48 */
} Work;

extern void AN_Smoke_800CE55C(SVECTOR *pos);

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    int i;

    for (i = 0; i < work->n_pos; i++)
    {
        if ((work->time % 8) == work->timing[i])
        {
            AN_Smoke_800CE55C(&work->pos[i]);
        }
    }

    work->time++;
}

static void Die(Work *work)
{
}

static int GetSvecs(char *opt, SVECTOR *out)
{
    int   count;
    char *str;

    count = 0;
    while ((str = GCL_NextStr()) && (count < MAX_SMOKE))
    {
        GCL_StrToSV(str, (short *)out);
        out++;
        count++;
    }

    return count;
}

static int GetResources(Work *work, int where)
{
    char *opt;
    int   i;

    opt = GCL_GetOption('p');
    if (opt == NULL)
    {
        return -1;
    }

    work->n_pos = GetSvecs(opt, work->pos);
    if (work->n_pos < 0)
    {
        return -1;
    }

    for (i = 0; i < work->n_pos; i++)
    {
        work->timing[i] = i * (8 / work->n_pos);
    }

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewBlackSmoke(int name, int where)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, Act, Die, "b_smoke.c");

        if (GetResources(work, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return (void *)work;
}
