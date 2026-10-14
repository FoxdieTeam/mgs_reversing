#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"
#include "takabe/spark2.h"

#define N_SMOKES 4

void *NewCrashSmoke(SVECTOR *pos, SVECTOR *rot, int speed, int num, int type, int mode, u_char r, u_char g, u_char b);

typedef struct _Work
{
    GV_ACT  actor;
    int     map;                // 0x20
    SVECTOR pos;                // 0x24
    int     num;                // 0x2C
    int     type;               // 0x30
    int     mode;               // 0x34
    int     time;               // 0x38
    int     frame;              // 0x3C
    SVECTOR speeds[N_SMOKES];   // 0x40
    SVECTOR smokes[N_SMOKES];   // 0x60
    char    pad_80[0x80];
    u_char  r, g, b;            // 0x100
} Work;

#define EXEC_LEVEL GV_ACTOR_PREV

void AN_Unknown_800D6F6C(SVECTOR *pos);
void AN_Unknown_800D7028(SVECTOR *pos, int num);
void AN_Unknown_800D70E4(SVECTOR *pos, char r, char g, char b);

static void Act(Work *work)
{
    MATRIX  world;
    SVECTOR rot;
    int     i;

    GM_CurrentMap = work->map;

    for (i = 0; i < N_SMOKES; i++)
    {
        work->speeds[i].vy -= 15;

        work->smokes[i].vx += work->speeds[i].vx;
        work->smokes[i].vy += work->speeds[i].vy;
        work->smokes[i].vz += work->speeds[i].vz;

        switch (work->type)
        {
        case 0:
            AN_Unknown_800D6F6C(&work->smokes[i]);
            break;

        case 1:
            AN_Unknown_800D7028(&work->smokes[i], work->num);
            break;

        case 2:
            AN_Unknown_800D70E4(&work->smokes[i], work->r, work->g, work->b);
            break;
        }

        switch (work->mode)
        {
        case 2:
        case 3:
            if (GV_RandU(16) == 0 || work->time == 0)
            {
                rot.vx = GV_RandU(2048);
                rot.vy = GV_RandU(4096);
                rot.vz = 0;
                DG_SetPos2(&work->smokes[i], &rot);
                ReadRotMatrix(&world);
                NewSpark2_800CA714(&world);
            }
            break;
        }
    }

    if (--work->time < 0)
    {
        GV_DestroyActor(&work->actor);
    }

    if (!(work->time & 1))
    {
        work->frame++;
    }
}

static void Die(Work *work)
{
}

static int GetResources(Work *work, SVECTOR *pos, SVECTOR *rot, int speed, int num, int type, int mode, u_char r, u_char g, u_char b)
{
    SVECTOR vec;
    SVECTOR rot2;
    int     time;
    int     i;

    work->mode = mode;
    work->map = GM_CurrentMap;

    /* the default value is set twice (here and for cases 0/2); both are in
     * the original code */
    time = 15;

    switch (mode)
    {
    case 0:
    case 2:
        time = 15;
        break;
    case 1:
    case 3:
        time = 30;
        break;
    }

    work->pos = *pos;

    rot2 = DG_ZeroVector;

    for (i = 0; i < N_SMOKES; i++)
    {
        vec.vx = 0;
        vec.vy = GV_RandU(256) + 128;
        vec.vz = (speed * (GV_RandU(2048) + 2048) / time) / 4096;

        rot2.vy = GV_RandU(4096);

        DG_SetPos2(&DG_ZeroVector, &rot2);
        DG_PutVector(&vec, &vec, 1);

        DG_SetPos2(&DG_ZeroVector, rot);
        DG_PutVector(&vec, &work->speeds[i], 1);

        work->smokes[i] = work->pos;
    }

    work->num = num;
    work->type = type;
    work->r = r;
    work->g = g;
    work->b = b;
    work->time = time;
    work->frame = 0;
    return 0;
}

void *NewCrashSmoke(SVECTOR *pos, SVECTOR *rot, int speed, int num, int type, int mode, u_char r, u_char g, u_char b)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "crsh_smk.c");
        GetResources(work, pos, rot, speed, num, type, mode, r, g, b);
    }

    return (void *)work;
}
