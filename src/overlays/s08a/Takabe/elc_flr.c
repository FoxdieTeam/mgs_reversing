#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/game.h"
#include "Game/object.h"
#include "Takabe/thing.h"

typedef struct _ElcFlrWork
{
    GV_ACT actor;
    int    map;
    int    name;
    MATRIX light[2];
    OBJECT object;
    int    f14C;
    int    f150;
} ElcFlrWork;

#define EXEC_LEVEL 5

unsigned short elc_flr_800C36DC[] = {0xD182, 0x006B};

void ElcFlrAct_800D47CC(ElcFlrWork *work)
{
    long   *t;
    int     ang;
    u_long *iter;
    int     i, j;
    long   *iter2;

    GM_CurrentMap_800AB9B0 = work->map;

    switch (THING_Msg_CheckMessage(work->name, 2, elc_flr_800C36DC))
    {
    case 0:
        work->f14C = 1;
        break;

    case 1:
        work->f14C = 0;
        break;
    }

    DG_SetPos(&DG_ZeroMatrix);
    DG_PutObjs(work->object.objs);

    work->f150++;

    t = work->light[0].t;
    if (work->f14C != 0)
    {
        ang = work->f150 * 64;

        t[0] = rsin(ang) / 512 + 16;
        t[1] = (rsin(ang) * 20) / 4096 + 40;
        t[2] = rsin(ang) / 128 + 64;

        if (work->f150 & 1)
        {
            iter = t;
            for (i = 3; i > 0; i--)
            {
                *iter++ = (*iter * 3) / 4;
            }
        }
    }
    else
    {
        iter2 = t;
        for (j = 3; j > 0; j--)
        {
            *iter2 = GV_NearExp4(*iter2, 1);

            if (*iter2 < 5)
            {
                *iter2 = 1;
            }

            iter2++;
        }
    }
}

void ElcFlrDie_800D4968(ElcFlrWork *work)
{
    GM_FreeObject(&work->object);
}

int ElcFlrGetResources_800D4988(ElcFlrWork *work, int name, int map)
{
    OBJECT *object;

    GM_CurrentMap_800AB9B0 = map;

    work->map = map;
    work->name = name;

    work->f14C = THING_Gcl_GetInt('a');

    object = &work->object;
    GM_InitObject(object, GV_StrCode("08a_o1"), 0x15D, 0);
    GM_ConfigObjectLight(object, work->light);
    GM_ConfigObjectJoint(object);
    object->objs->objs[0].raise = -3000;

    work->f150 = 0;
    return 0;
}

GV_ACT *NewElcFlr_800D4A18(int name, int where)
{
    ElcFlrWork *work;

    work = (ElcFlrWork *)GV_NewActor(EXEC_LEVEL, sizeof(ElcFlrWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)ElcFlrAct_800D47CC,
                         (GV_ACTFUNC)ElcFlrDie_800D4968, "elc_flr.c");

        if (ElcFlrGetResources_800D4988(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}