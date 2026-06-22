#include "game/game.h"

typedef struct _Work
{
    GV_ACT         actor;       /* 0x000 */
    CONTROL        control;     /* 0x020 */
    OBJECT         body;        /* 0x09C */
    DG_OBJS        objs;        /* 0x180 */
    MOTION_CONTROL m_ctrl;      /* 0x1C8 */
    MOTION_SEGMENT m_segs1[17]; /* 0x218 */
    MOTION_SEGMENT m_segs2[17]; /* 0x47C */
    SVECTOR        rots[16];    /* 0x6E0 */
    int            field_760;   /* 0x760 */
    int            field_764;   /* 0x764 */
    int            field_768;   /* 0x768 */
} Work;

void s05a_800D4654(MOTION_SEGMENT *dst, MOTION_SEGMENT *src, int mask)
{
    int i;

    for (i = 0; i < 16; i++, dst++, src++)
    {
        if (mask & 1)
        {
            dst->base = src->base;
        }
        mask >>= 1;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D46A4.s")

void s05a_800D4968(Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
}

int s05a_800D4998(Work *work, int name)
{
    work->body.objs = &work->objs;
    GM_ConfigMotionControl(&work->body, &work->m_ctrl, name, work->m_segs1,
                           work->m_segs2, &work->control, work->rots);
    work->field_760 = 0;
    work->field_764 = 0;
    return 0;
}

#pragma INCLUDE_ASM("asm/overlays/s05a/s05a_800D49F8.s")
