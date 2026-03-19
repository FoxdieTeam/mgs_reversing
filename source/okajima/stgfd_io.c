#include "stgfd_io.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL3

typedef struct _PRIM_WORK
{
    DR_TPAGE    tpage[2];
    TILE        tile[2];
} PRIM_WORK;

typedef struct _Work
{
    GV_ACT      actor;
    PRIM_WORK  *prims;
    int         field_24;
    int         field_28;
    SVECTOR     field_2C;
    SVECTOR     field_34;
    int         state;
} Work;

/*---------------------------------------------------------------------------*/

static void UpdateStunFlash(Work *work)
{
    short rgb[3]; // or RGB struct?

    if (GV_PauseLevel)
    {
        return;
    }

    work->field_28++;
    if (work->field_24 >= work->field_28)
    {
        rgb[0] = work->field_2C.vx +
                 (((work->field_34.vx - work->field_2C.vx) * work->field_28)) / work->field_24;
        rgb[1] = work->field_2C.vy +
                 (((work->field_34.vy - work->field_2C.vy) * work->field_28)) / work->field_24;
        rgb[2] = work->field_2C.vz +
                 (((work->field_34.vz - work->field_2C.vz) * work->field_28)) / work->field_24;
    }
    setRGB0(&work->prims->tile[GV_Clock], rgb[0], rgb[1], rgb[2]);
}

static void stgfd_io_act_helper_80074F44(Work *work, int a2, int x, int y, int z)
{
    work->field_24 = a2;
    work->field_34.vx = x;
    work->field_34.vy = y;
    work->field_34.vz = z;
}

static void Act(Work *work)
{
    u_long *ot = (u_long *)DG_ChanlOTag(0);

    addPrim(ot, &work->prims->tile[GV_Clock]);
    addPrim(ot, &work->prims->tpage[GV_Clock]);

    UpdateStunFlash(work);

    if (work->field_28 == work->field_24)
    {
        work->field_28 = 0;
        work->field_2C = work->field_34;

        switch (work->state)
        {
        case 0:
            stgfd_io_act_helper_80074F44(work, 4, 250, 250, 250);
            break;
        case 1:
            stgfd_io_act_helper_80074F44(work, 2, 190, 190, 170);
            break;
        case 2:
            stgfd_io_act_helper_80074F44(work, 2, 240, 240, 240);
            break;
        case 3:
            stgfd_io_act_helper_80074F44(work, 2, 190, 190, 60);
            break;
        case 4:
            stgfd_io_act_helper_80074F44(work, 2, 220, 220, 170);
            break;
        case 5:
            stgfd_io_act_helper_80074F44(work, 40, 220, 220, 170);
            break;
        case 6:
            stgfd_io_act_helper_80074F44(work, 80, 0, 0, 0);
            break;
        default:
            GV_DestroyActor(&work->actor);
            break;
        }
        work->state++;
    }
}

static void Die(Work *work)
{
    if (work->prims)
    {
        GV_DelayedFree(work->prims);
    }
}

static int GetResources(Work *work)
{
    PRIM_WORK *prims = GV_Malloc(sizeof(PRIM_WORK));
    work->prims = prims;
    if (!prims)
    {
        return -1;
    }

    setDrawTPage(&prims->tpage[0], 0, 1, 0x20);
    setDrawTPage(&prims->tpage[1], 0, 1, 0x20);

    setTile(&prims->tile[0]);
    setSemiTrans(&prims->tile[0], 1);
    setXY0(&prims->tile[0], -160, -112);
    setWH(&prims->tile[0], FRAME_WIDTH, FRAME_HEIGHT);

    prims->tile[1] = prims->tile[0];
    setRGB0(&prims->tile[0], 0, 0, 0);
    setRGB0(&prims->tile[1], 0, 0, 0);

    work->field_28 = 0;
    work->field_2C = DG_ZeroVector;
    work->field_34.vx = 240;
    work->field_34.vy = 240;
    work->field_34.vz = 240;
    work->field_24 = 1;
    work->state = 0;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewStnFade(void)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(&work->actor, &Act, &Die, "stgfd_io.c");

        if (GetResources(work) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
