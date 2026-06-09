#include "fall_spl.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/game.h"

typedef struct _Work
{
    GV_ACT  actor;
    int     map;
    int     field_24;
    int     dir;
    SVECTOR limit[2];
} Work;

#define EXEC_LEVEL GV_ACTOR_USER

void *NewSplash3_800C83D0(int dir, SVECTOR *pos);

int s15b_fall_spl_800C7B0C(char *opt, SVECTOR *out)
{
    int            count;
    unsigned char *param;

    count = 0;
    while ((param = GCL_NextStr()))
    {
        GCL_StrToSV(param, (short *)out);
        out++;
        count++;
    }
    return count;
}

void s15b_fall_spl_800C7B60(Work *work)
{
    SVECTOR pos;
    int     rand;

    GM_CurrentMap = work->map;
    rand = GV_RandU(0x100);
    pos.vx = work->limit[0].vx + (work->limit[1].vx - work->limit[0].vx) * rand / 256;
    pos.vy = work->limit[0].vy + (work->limit[1].vy - work->limit[0].vy) * rand / 256;
    pos.vz = work->limit[0].vz + (work->limit[1].vz - work->limit[0].vz) * rand / 256;
    NewSplash3_800C83D0(work->dir, &pos);
}

int s15b_fall_spl_800C7C3C(Work *work, int where)
{
    char *opt1;
    unsigned char *opt2;

    work->map = where;
    opt1 = GCL_GetOption('l');
    if (opt1)
    {
        s15b_fall_spl_800C7B0C(opt1, work->limit);
    }
    opt2 = GCL_GetOption('d');
    if (opt2)
    {
        work->dir = GCL_StrToInt(opt2);
    }
    return 0;
}

void s15b_fall_spl_800C7C98(Work *work)
{
}

void *NewFallSplash(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, s15b_fall_spl_800C7B60,
                         s15b_fall_spl_800C7C98, "fall_spl.c");
        if (s15b_fall_spl_800C7C3C(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
