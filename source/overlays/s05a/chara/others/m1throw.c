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

extern const char s05a_dword_800E345C[]; /* = "m1throw.c" */

void s05a_800D46A4(Work *work);

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

void s05a_800D46A4(Work *work)
{
    int i;

    if (GM_PlayerBody == NULL) return;
    if (GM_PlayerControl == NULL) return;
    if (GM_uTenageMotion == -1) return;

    if (work->field_760 == 0)
    {
        for (i = 0; i < 16; i++)
        {
            work->rots[i] = GM_PlayerBody->objs->rots[i];
            work->body.height = GM_PlayerBody->height;
        }
        *work->body.objs->waist_rot = *GM_PlayerBody->objs->waist_rot;
        if (GM_PlayerBody->action2 == 0x32)
        {
            work->field_760 = 1;
            work->field_764 = 0;
        }
    }
    else if (work->field_760 == 1)
    {
        int motion = work->field_764;
        int mask;

        work->field_764 = motion + 1;
        mask = GM_PlayerBody->m_ctrl->info1.mask;
        if (motion == 0)
        {
            s05a_800D4654(work->body.m_ctrl->info1.m_segs, GM_PlayerBody->m_ctrl->info1.m_segs, mask);
            GM_ConfigObjectAction(&work->body, GM_uTenageMotion, 0, 4);
        }
        GM_ActMotion(&work->body);
        GM_PlayerBody->height = work->body.height;
        {
            int m = mask;
            for (i = 0; i < 16; i++)
            {
                if (m & 1)
                {
                    GM_PlayerBody->objs->rots[i] = work->rots[i];
                }
                m >>= 1;
            }
        }
        *GM_PlayerBody->objs->waist_rot = *work->body.objs->waist_rot;
        if (work->body.m_ctrl->info1.frames_left == 2 || GM_PlayerBody->action2 != 0x32)
        {
            s05a_800D4654(GM_PlayerBody->m_ctrl->info1.m_segs, work->body.m_ctrl->info1.m_segs, mask);
            GM_PlayerBody->m_ctrl->interp = 4;
            work->field_760 = 2;
        }
    }
    else
    {
        if (GM_PlayerBody->action2 != 0x32)
        {
            work->field_760 = 0;
        }
    }
}

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

void *s05a_800D49F8(int arg)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_AFTER, sizeof(Work));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(work, s05a_800D46A4, s05a_800D4968, s05a_dword_800E345C);

    if (s05a_800D4998(work, arg) < 0)
    {
        GV_DestroyActor(work);
        return NULL;
    }

    return work;
}
