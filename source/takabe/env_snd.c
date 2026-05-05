#include "env_snd.h"

#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "takabe/thing.h"

typedef struct _EnvSndWork
{
    GV_ACT  actor;
    int     map;
    int     name;
    int     f28;
    SVECTOR pos;
    short   size;   // "radius"?
    short   noise;
    short   type;
    short   f3A;
    short   f3C;
    short   f3E;
    int     f40;
    char    pad[0x4];
} EnvSndWork;

unsigned short env_snd_hashes[] = { 0xBA27, 0x560E };

#define EXEC_LEVEL GV_ACTOR_LEVEL5

void EnvSndAct_800DF1F8(EnvSndWork *work)
{
    int time;
    int found;

    GM_SetCurrentMap(work->map);

    time = GV_PassageTime;
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
        switch (work->type)
        {
        case 1:
            GM_SeSetMode(&work->pos, work->noise, GM_SEMODE_NORMAL);
            break;

        case 2:
            GM_SeSetMode(&work->pos, work->noise, GM_SEMODE_CAMERA);
            break;

        case 3:
            GM_SeSetMode(&work->pos, work->noise, GM_SEMODE_REAL);
            break;

        case 4:
            GM_SeSetMode(&work->pos, work->noise, GM_SEMODE_BOMB);
            break;

        case 0:
        default:
            GM_SeSetSize(&work->pos, work->noise, work->size);
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

    THING_Gcl_GetSVector('p', &work->pos);

    work->size = THING_Gcl_GetInt('r');
    work->noise = THING_Gcl_GetInt('n');
    work->type = THING_Gcl_GetInt('t');
    work->f3A = THING_Gcl_GetInt('i');
    work->f3C = THING_Gcl_GetInt('c');
    work->f28 = THING_Gcl_GetInt('s');

    return 0;
}

void *NewEnvSound(int name, int where, int argc, char **argv)
{
    EnvSndWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(EnvSndWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, EnvSndAct_800DF1F8, EnvSndDie_800DF39C, "env_snd.c");

        if (EnvSndGetResources_800DF3A4(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
