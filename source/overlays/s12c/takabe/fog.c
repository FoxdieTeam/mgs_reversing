#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "game/camera.h"
#include "takabe/thing.h"

typedef struct _FogWork
{
    GV_ACT       actor;
    int          map;
    int          name;
    int          scale;
    int          f2C;
    DG_CHANLFUNC bound;
    DG_CHANLFUNC trans;
    DG_CHANLFUNC shade;
    DG_CHANLFUNC sort;
    int          f40;
} FogWork;

int SECTION("overlay.bss") s12c_800DA428;
int SECTION("overlay.bss") s12c_800DA42C;
int SECTION("overlay.bss") s12c_800DA430;
int SECTION("overlay.bss") s12c_800DA434;

extern GM_CAMERA GM_Camera;

void s12c_800D497C(int, int);
void s12c_800D4AB4(int);

void FogSortChanl_800D4E98(DG_CHANL *chanl, int idx);
void FogBoundChanl_800D5500(DG_CHANL *chanl, int idx);
void FogTransChanl_800D63B0(DG_CHANL *chanl, int idx);
void FogShadeChanl_800D6A04(DG_CHANL *chanl, int idx);

#define EXEC_LEVEL GV_ACTOR_LEVEL3

void FogAct_800D4074(FogWork *work)
{
    int scale;

    GM_CurrentMap = work->map;

    scale = work->scale;
    scale += (255 - scale) * (GM_Camera.zoom - 360) / 3640;
    s12c_800D4AB4(scale);
}

void FogDie_800D40E0(FogWork *work)
{
    DG_SetChanlSystemUnits(DG_BOUND_CHANL, work->bound);
    DG_SetChanlSystemUnits(DG_TRANS_CHANL, work->trans);
    DG_SetChanlSystemUnits(DG_SHADE_CHANL, work->shade);
    DG_SetChanlSystemUnits(DG_SORT_CHANL,  work->sort);
}

int FogGetResources_800D4130(FogWork *work, int name, int map)
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

    work->bound = DG_SetChanlSystemUnits(DG_BOUND_CHANL, FogBoundChanl_800D5500);
    work->trans = DG_SetChanlSystemUnits(DG_TRANS_CHANL, FogTransChanl_800D63B0);
    work->shade = DG_SetChanlSystemUnits(DG_SHADE_CHANL, FogShadeChanl_800D6A04);
    work->sort  = DG_SetChanlSystemUnits(DG_SORT_CHANL,  FogSortChanl_800D4E98);
    work->f40 = 1;

    return 0;
}

void *NewFog_800D4208(int arg0, int arg1)
{
    FogWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(FogWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, FogAct_800D4074, FogDie_800D40E0, "fog.c");

        if (FogGetResources_800D4130(work, arg0, arg1) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
