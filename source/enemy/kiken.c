#include "kiken.h"

#include "common.h"
#include "libgv/libgv.h"
#include "enemy/enemy.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL4

typedef struct _Work
{
    GV_ACT actor;
    int    active;
    int    name;
} Work;

/*---------------------------------------------------------------------------*/

static int CheckMessage(Work *work)
{
    GV_MSG *msg;
    int     code;

    if (GV_ReceiveMessage(work->name, &msg) > 0)
    {
        code = msg->message[0];

        if (code == HASH_LEAVE)
        {
            work->active = FALSE;
        }
        else if (code == HASH_ENTER)
        {
            work->active = TRUE;
        }

        return code;
    }

    return -1;
}

static void Act(Work *work)
{
    CheckMessage(work);

    if (work->active)
    {
        ENE_SetTopCommAL(255);
        ENE_SetGopointLast();
    }
}

static void Die(Work *work)
{
    /* do nothing */
}

static int GetResources(Work *work, int name)
{
    work->name = name;
    work->active = FALSE;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewKikenKun(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "kiken.c");

        if (GetResources(work, name) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
