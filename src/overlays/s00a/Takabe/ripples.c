#include "ripples.h"

#include <stddef.h> // for NULL
#include <rand.h>
#include "libgv/libgv.h"
#include "Takabe/thing.h"

typedef struct RipplesWork
{
    GV_ACT       actor;
    int          field_20;
    int          field_24;
    MATRIX       field_28;
    short        field_48;
    short        field_4A;
    short        field_4C;
    short        field_4E;
} RipplesWork;

void * NewRipple_800D7F30( MATRIX *, int );

extern int GM_CurrentMap_800AB9B0;
extern MATRIX DG_ZeroMatrix;

void RipplesAct_800D85A0(RipplesWork *work)
{
    GM_CurrentMap_800AB9B0 = work->field_20;
    if (--work->field_48 < 0)
    {
        NewRipple_800D7F30(&work->field_28, work->field_4A);
        work->field_48 = work->field_4C + ((rand() * work->field_4E >> 15) - work->field_4E / 2);
    }
}

void RipplesDie_800D862C(RipplesWork *work)
{

}

int RipplesGetResources_800D8634(RipplesWork *work, int name, int where)
{
    SVECTOR svec;

    work->field_28 = DG_ZeroMatrix;
    THING_Gcl_GetSVector('p', &svec);
    work->field_28.t[0] = svec.vx;
    work->field_28.t[1] = svec.vy;
    work->field_28.t[2] = svec.vz;
    work->field_4C = THING_Gcl_GetIntDefault('i', 90);
    work->field_4E = THING_Gcl_GetInt('r');
    work->field_4A = THING_Gcl_GetInt('s');
    work->field_48 = work->field_4C + ((rand() * work->field_4E >> 15) - work->field_4E / 2);
    return 0;
}

GV_ACT *NewRipples_800D872C(int name, int where, int argc, char **argv)
{
    RipplesWork *work;

    work = (RipplesWork *)GV_NewActor(5, sizeof(RipplesWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)RipplesAct_800D85A0, (TActorFunction)RipplesDie_800D862C, "ripples.c");
        if (RipplesGetResources_800D8634(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        work->field_20 = where;
        work->field_24 = name;
    }
    return &work->actor;
}
