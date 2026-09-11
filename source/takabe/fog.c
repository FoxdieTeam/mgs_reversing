#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "takabe/thing.h"

extern GM_CameraSystemWork GM_Camera;

extern void s12c_800D497C(int, int);
extern void s12c_800D4AB4(int);

extern void FogSortChanl_800D4E98(DG_CHANL *chanl, int idx);
extern void FogBoundChanl_800D5500(DG_CHANL *chanl, int idx);
extern void FogTransChanl_800D63B0(DG_CHANL *chanl, int idx);
extern void FogShadeChanl_800D6A04(DG_CHANL *chanl, int idx);

/*---------------------------------------------------------------------------*/

typedef struct _Work
{
    GV_ACT       actor;
    int          map;
    int          name;
    int          scale;
    int          f2C;
    DG_CHANLFUNC old_bound;
    DG_CHANLFUNC old_trans;
    DG_CHANLFUNC old_shade;
    DG_CHANLFUNC old_sort;
    int          f40;
} Work;

/*---------------------------------------------------------------------------*/

int SECTION(".bss") s12c_800DA428;
int SECTION(".bss") s12c_800DA42C;
int SECTION(".bss") s12c_800DA430;
int SECTION(".bss") s12c_800DA434;

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    int scale;

    GM_CurrentMap = work->map;

    scale = work->scale;
    scale += (255 - scale) * (GM_Camera.zoom - 360) / 3640;
    s12c_800D4AB4(scale);
}

static void Die(Work *work)
{
    DG_SetChanlSystemUnits(DG_BOUND_CHANL, work->old_bound);
    DG_SetChanlSystemUnits(DG_TRANS_CHANL, work->old_trans);
    DG_SetChanlSystemUnits(DG_SHADE_CHANL, work->old_shade);
    DG_SetChanlSystemUnits(DG_SORT_CHANL,  work->old_sort);
}

static int GetResources(Work *work, int name, int map)
{
    int temp_s1;
    int temp_s2;

    work->name = name;

    GM_CurrentMap = map;
    work->map = map;

    temp_s2 = THING_Gcl_GetIntDefault('s', 50);
    temp_s1 = THING_Gcl_GetIntDefault('e', 50);

    work->f2C = THING_Gcl_GetInt('m');

    s12c_800D497C(temp_s2, temp_s1);
    work->scale = temp_s2;

    work->old_bound = DG_SetChanlSystemUnits(DG_BOUND_CHANL, FogBoundChanl_800D5500);
    work->old_trans = DG_SetChanlSystemUnits(DG_TRANS_CHANL, FogTransChanl_800D63B0);
    work->old_shade = DG_SetChanlSystemUnits(DG_SHADE_CHANL, FogShadeChanl_800D6A04);
    work->old_sort  = DG_SetChanlSystemUnits(DG_SORT_CHANL,  FogSortChanl_800D4E98);
    work->f40 = 1;

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewFog(int name, int map)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_PREV2, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "fog.c");

        if (GetResources(work, name, map) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
