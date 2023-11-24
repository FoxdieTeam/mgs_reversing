#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Game/camera.h"

typedef struct _FogWork
{
    GV_ACT    actor;
    int       map;
    int       name;
    int       scale;
    int       f2C;
    TChanl_Fn bound;
    TChanl_Fn trans;
    TChanl_Fn shade;
    TChanl_Fn sort;
    int       f40;
} FogWork;

extern int       GM_CurrentMap_800AB9B0;
extern GM_Camera GM_Camera_800B77E8;

int THING_Gcl_GetInt(int);
int THING_Gcl_GetIntDefault(int, int);

void s12c_fadeio_800D497C(int, int);
void s12c_fadeio_800D4AB4(int);

void FogSortChanl_800D4E98(DG_CHNL *chnl, int idx);
void FogBoundChanl_800D5500(DG_CHNL *chnl, int idx);
void FogTransChanl_800D63B0(DG_CHNL *chnl, int idx);
void FogShadeChanl_800D6A04(DG_CHNL *chnl, int idx);

#define EXEC_LEVEL 3

void FogAct_800D4074(FogWork *work)
{
    int scale;

    GM_CurrentMap_800AB9B0 = work->map;

    scale = work->scale;
    scale += (255 - scale) * (GM_Camera_800B77E8.field_20 - 360) / 3640;
    s12c_fadeio_800D4AB4(scale);
}

void FogDie_800D40E0(FogWork *work)
{
    DG_SetChanlSystemUnits_80018598(DG_CHANL_BOUND, work->bound);
    DG_SetChanlSystemUnits_80018598(DG_CHANL_TRANS, work->trans);
    DG_SetChanlSystemUnits_80018598(DG_CHANL_SHADE, work->shade);
    DG_SetChanlSystemUnits_80018598(DG_CHANL_SORT,  work->sort);
}

int FogGetResources_800D4130(FogWork *work, int name, int map)
{
    int temp_s1;
    int temp_s2;

    work->name = name;

    GM_CurrentMap_800AB9B0 = map;
    work->map = map;

    temp_s2 = THING_Gcl_GetIntDefault('s', 50);
    temp_s1 = THING_Gcl_GetIntDefault('e', 50);

    work->f2C = THING_Gcl_GetInt('m');

    s12c_fadeio_800D497C(temp_s2, temp_s1);
    work->scale = temp_s2;

    work->bound = DG_SetChanlSystemUnits_80018598(DG_CHANL_BOUND, FogBoundChanl_800D5500);
    work->trans = DG_SetChanlSystemUnits_80018598(DG_CHANL_TRANS, FogTransChanl_800D63B0);
    work->shade = DG_SetChanlSystemUnits_80018598(DG_CHANL_SHADE, FogShadeChanl_800D6A04);
    work->sort  = DG_SetChanlSystemUnits_80018598(DG_CHANL_SORT,  FogSortChanl_800D4E98);
    work->f40 = 1;

    return 0;
}

GV_ACT * NewFog_800D4208(int arg0, int arg1)
{
    FogWork *work;

    work = (FogWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(FogWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)FogAct_800D4074, (TActorFunction)FogDie_800D40E0, "fog.c");

        if (FogGetResources_800D4130(work, arg0, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
