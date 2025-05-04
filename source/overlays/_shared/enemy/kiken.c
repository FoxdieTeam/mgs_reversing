#include "kiken.h"

#include "common.h"
#include "libgv/libgv.h"
#include "overlays/_shared/enemy/enemy.h"
#include "strcode.h"

typedef struct _KikenWork
{
    GV_ACT actor;
    int    active;
    int    name;
} KikenWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL4

int KikenCheckMessages_800D6C64(KikenWork *work)
{
    GV_MSG *msg;
    int     code;

    if (GV_ReceiveMessage(work->name, &msg) > 0)
    {
        code = msg->message[0];

        if (code == HASH_LEAVE)
        {
            work->active = 0;
        }
        else if (code == HASH_ENTER)
        {
            work->active = 1;
        }

        return code;
    }

    return -1;
}

void KikenAct_800D6CC8(KikenWork *work)
{
    KikenCheckMessages_800D6C64(work);

    if (work->active != 0)
    {
        ENE_SetTopCommAL_800CEAE8(0xFF);
        ENE_SetGopointLast_800CEB00();
    }
}

void KikenDie_800D6D0C(KikenWork *work)
{
}

int KikenGetResources_800D6D14(KikenWork *work, int name)
{
    work->name = name;
    work->active = 0;
    return 0;
}

void *NewKiken_800D6D24(int name, int where, int argc, char **argv)
{
    KikenWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(KikenWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, KikenAct_800D6CC8, KikenDie_800D6D0C, "kiken.c");

        if (KikenGetResources_800D6D14(work, name) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
