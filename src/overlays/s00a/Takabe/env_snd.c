#include "libgv/libgv.h"
#include "Game/game.h"

typedef struct _EnvSndWork
{
    GV_ACT  actor;
    int     map;
    int     name;
    int     f28;
    SVECTOR f2C;
    short   f34;
    short   f36;
    short   f38;
    short   f3A;
    short   f3C;
    short   f3E;
    int     f40;
    char    pad[0x4];
} EnvSndWork;

extern int GV_PassageTime_800AB924;

unsigned short env_snd_hashes[] = { 0xBA27, 0x560E };

int THING_Gcl_GetInt(int param);
int THING_Gcl_GetSVector(int param, SVECTOR *svec);
int THING_Msg_CheckMessage(unsigned short name, int n_message, short *mes_list);
int THING_Msg_GetResult();

#define EXEC_LEVEL 5

void EnvSndAct_800DF1F8(EnvSndWork *work)
{
    int time;
    int found;

    GM_SetCurrentMap(work->map);

    time = GV_PassageTime_800AB924;
    found = THING_Msg_CheckMessage(work->name, 4, env_snd_hashes);
    THING_Msg_GetResult();

    switch (found)
    {
    case 0:
        work->f28 = 0;
        break;

    case 1:
        work->f28 = 1;
        work->f3E = work->f3C;
        work->f40 = 0;
        break;

    default:
        break;
    }

    if (work->f28 == 0)
    {
        return;
    }

    if (work->f40 <= 0)
    {
        switch (work->f38)
        {
        case 1:
            GM_Sound_800329C4(&work->f2C, work->f36, 0);
            break;

        case 2:
            GM_Sound_800329C4(&work->f2C, work->f36, 3);
            break;

        case 3:
            GM_Sound_800329C4(&work->f2C, work->f36, 2);
            break;

        case 4:
            GM_Sound_800329C4(&work->f2C, work->f36, 1);
            break;

        case 0:
        default:
            sub_80032BC4(&work->f2C, work->f36, work->f34);
            break;
        }

        if (work->f3C >= 0 && --work->f3E == 0)
        {
            work->f28 = 0;
            return;
        }

        work->f40 = work->f3A * 2;
    }

    work->f40 -= time;
}

void EnvSndDie_800DF39C(EnvSndWork *work)
{
}

int EnvSndGetResources_800DF3A4(EnvSndWork *work, int name, int where)
{
    work->name = name;
    work->map = where;

    THING_Gcl_GetSVector('p', &work->f2C);

    work->f34 = THING_Gcl_GetInt('r');
    work->f36 = THING_Gcl_GetInt('n');
    work->f38 = THING_Gcl_GetInt('t');
    work->f3A = THING_Gcl_GetInt('i');
    work->f3C = THING_Gcl_GetInt('c');
    work->f28 = THING_Gcl_GetInt('s');

    return 0;
}

GV_ACT * NewEnvSnd_800DF424(int name, int where)
{
    EnvSndWork *work;

    work = (EnvSndWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(EnvSndWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)EnvSndAct_800DF1F8, (TActorFunction)EnvSndDie_800DF39C, "env_snd.c");

        if (EnvSndGetResources_800DF3A4(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
