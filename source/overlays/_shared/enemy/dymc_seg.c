#include "dymc_seg.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libhzd/libhzd.h"
#include "game/game.h"

typedef struct DymcSegWork
{
    GV_ACT   actor;
    int      field_20;
    HZD_HDL *field_24;
    HZD_SEG  field_28;
    SVECTOR  field_38;
    SVECTOR  field_40;
    int      field_48;
    int      field_4C;
} DymcSegWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

extern char s07a_dword_800E2F10[];

void s07a_dymc_seg_800D6430(DymcSegWork *work)
{
    HZD_SEG *seg;

    seg = &work->field_28;
    if (work->field_4C != 0)
    {
        if (work->field_48 == 0)
        {
            work->field_4C = 0;
            seg->p1.y = work->field_38.vy - 10000;
            seg->p2.y = work->field_40.vy - 10000;
        }
    }
    else if (work->field_48 != 0)
    {
        work->field_4C = 1;
        seg->p1.y = work->field_38.vy;
        seg->p2.y = work->field_40.vy;
    }
}

void s07a_dymc_seg_800D64A4(DymcSegWork *work)
{
    HZD_DequeueDynamicSegment(work->field_24, &work->field_28);
}

int s07a_dymc_seg_800D64CC(DymcSegWork *work, int arg1, SVECTOR *min, SVECTOR *max, int min_h, int max_h, int flag)
{
    HZD_SEG *seg;

    work->field_20 = arg1;
    work->field_38 = *min;
    work->field_40 = *max;

    seg = &work->field_28;
    seg->p1.x = min->vx;
    seg->p1.y = min->vy;
    seg->p1.z = min->vz;
    seg->p1.h = min_h;

    seg->p2.x = max->vx;
    seg->p2.y = max->vy;
    seg->p2.z = max->vz;
    seg->p2.h = max_h;

    HZD_SetDynamicSegment(seg, seg);
    work->field_24 = GM_FindMap(arg1)->hzd;
    HZD_QueueDynamicSegment2(work->field_24, seg, flag);

    return 0;
}

void *s07a_dymc_seg_800D65C8(int arg0, SVECTOR *min, SVECTOR *max, int min_h, int max_h, int flag, void **arg6)
{
    DymcSegWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(DymcSegWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, s07a_dymc_seg_800D6430,
                         s07a_dymc_seg_800D64A4, s07a_dword_800E2F10);
        if (s07a_dymc_seg_800D64CC(work, arg0, min, max, min_h, max_h, flag) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        if (arg6 != NULL)
        {
            *arg6 = &work->field_48;
        }
        work->field_48 = 1;
        work->field_4C = 1;
    }
    return (void *)work;
}
