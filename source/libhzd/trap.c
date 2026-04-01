#include "common.h"
#include "strcode.h"
#include "game/game.h"
#include "libhzd/libhzd.h"

static inline int CheckTrapBounds(void)
{
    HZD_VEC *pos;
    HZD_SEG *box;

    pos = (HZD_VEC *)(SCRPAD_ADDR + 0);
    box = (HZD_SEG *)(SCRPAD_ADDR + 8);

    if (pos->x < box->p1.x || pos->x >= box->p2.x ||
        pos->z < box->p1.z || pos->z >= box->p2.z ||
        pos->y < box->p1.y || pos->y >= box->p2.y)
    {
        return 0;
    }

    return 1;
}

static inline int HZD_8002A27C_helper2(unsigned short *ptrIn, unsigned int target)
{
    int             count = *(unsigned int *)0x1F800018;
    unsigned short *ptr = (unsigned short *)0x1F80001C;

    for (; count > 0; count--)
    {
        if (*ptr++ == target)
        {
            *(int *)0x1F800018 -= 1;
            ptr[-1] = (ptrIn + 0x0E)[*(int *)0x1F800018];
            return 1;
        }
    }
    return 0;
}

STATIC void HZD_8002A27C(HZD_HDL *hzd, HZD_EVT *event)
{
    HZD_GRP *group;
    HZD_TRG *trigger;
    int      count;

    int             i, j;
    unsigned int    name_id;
    unsigned short *pSlots;
    unsigned short *ptr;
    int             a1;

    group = hzd->group;
    trigger = group->triggers;

    event->type = HASH_ENTER;

    count = 0;
    for (i = group->n_triggers - hzd->n_cameras; i > 0; i--, trigger++)
    {
        ptr = (unsigned short *)SCRPAD_ADDR;
        *(HZD_SEG *)(SCRPAD_ADDR + 8) = *(HZD_SEG *)trigger;

        if (!CheckTrapBounds())
        {
            continue;
        }

        name_id = trigger->trap.name_id;
        event->last = name_id;

        if (!HZD_8002A27C_helper2(ptr, name_id))
        {
            HZD_80029D50(hzd, event, 1);
        }
        else
        {
            HZD_80029D50(hzd, event, 2);
        }

        a1 = count;

        pSlots = event->triggers;
        for (j = count; j > 0; j--)
        {
            if (*pSlots++ == name_id)
            {
                count = a1;
                goto loop;
            }
        }

        *pSlots = name_id;
        count = a1 + 1;

loop:
    }

    event->n_triggers = count;
}

STATIC void HZD_8002A4B8(HZD_HDL *hzd, HZD_EVT *event)
{
    int    count;
    short *pData;

    pData = (short *)getScratchAddr(7);

    event->type = HASH_LEAVE;

    for (count = *getScratchAddr(6); count > 0; count--)
    {
        event->last = *pData++;
        HZD_80029D50(hzd, event, 0);
    }
}

void HZD_EnterTrap(HZD_HDL *hzd, HZD_EVT *event)
{
    SVECTOR *pSrcVec;
    short   *pArr;
    short   *pScr;
    short    tmp;
    int      i;

    pSrcVec = &event->pos;

    *(short *)0x1F800000 = pSrcVec->vx;
    do {} while (0);

    *(short *)0x1F800004 = pSrcVec->vy;
    pArr = event->triggers;
    do {} while (0);

    tmp = pSrcVec->vz;
    pScr = (short *)getScratchAddr(7);

    do {} while (0);

    *(short *)0x1F800002 = tmp;
    *getScratchAddr(6) = event->n_triggers;

    for (i = event->n_triggers; i > 0; i--)
    {
        *pScr++ = *pArr++;
    }

    HZD_8002A27C(hzd, event);
    HZD_8002A4B8(hzd, event);
}

// TODO: move

#define HZD_COPY_ELEM(dst, src) \
do {                            \
    *(dst) = (src);             \
} while (0)

#define HZD_COPY_VEC(dst, src)                        \
do {                                                  \
    HZD_COPY_ELEM(&((HZD_VEC *)(dst))->x, (src)->vx); \
    HZD_COPY_ELEM(&((HZD_VEC *)(dst))->y, (src)->vy); \
    HZD_COPY_ELEM(&((HZD_VEC *)(dst))->z, (src)->vz); \
} while (0)

HZD_TRP *HZD_CheckBehindTrap(HZD_HDL *hzd, SVECTOR *pos)
{
    int      i;
    HZD_TRP *trap;

    HZD_COPY_VEC(SCRPAD_ADDR + 0, pos);

    for (i = hzd->n_cameras, trap = hzd->traps; i > 0; i--, trap++)
    {
        *(HZD_SEG *)(SCRPAD_ADDR + 8) = *(HZD_SEG *)trap;

        if (CheckTrapBounds())
        {
            return trap;
        }
    }

    return NULL;
}
