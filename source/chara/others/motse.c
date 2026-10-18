#include "motse.h"

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

typedef struct MotseElem
{
    int param1;
    int sound;
} MotseElem;

typedef struct _Work
{
    GV_ACT     actor;
    int        m_opt;
    int        n_elems;
#ifdef VR_EXE
    int        name;    // 0x28
#endif
    MotseElem *elems;
} Work;

/*---------------------------------------------------------------------------*/

#ifdef VR_EXE
// The VR revision dies when the "kill" message arrives
static int CheckMessage(Work *work)
{
    GV_MSG *msg;
    int     len;

    len = GV_ReceiveMessage(work->name, &msg);
    if (len > 0)
    {
        for (len--; len >= 0; msg++, len--)
        {
            if (msg->message[0] == HASH_KILL)
            {
                return 1;
            }
        }
    }

    return 0;
}
#endif

static void Act(Work *work)
{
    MotseElem *elem;
    int        i;

#ifdef VR_EXE
    if (CheckMessage(work))
    {
        GV_DestroyActor(&work->actor);
        return;
    }
#endif

    if ((GM_PlayerStatus & PLAYER_ACT_ONLY) && GM_PlayerAction == work->m_opt)
    {
        for (i = 0, elem = work->elems; i < work->n_elems; i++, elem++)
        {
            if (elem->param1 == dword_800AB9D4)
            {
                GM_SeSetMode(&GM_PlayerControl->mov, elem->sound, GM_SEMODE_BOMB);
                return;
            }
        }
    }
}

static void Die(Work *work)
{
    GV_DelayedFree(work->elems);
}

static int GetResources(Work *work, int name)
{
    int            i, count;
    unsigned char *param;
    MotseElem     *elems;

    work->m_opt = GCL_StrToInt(GCL_GetOption('m'));
    work->n_elems = count = GCL_StrToInt(GCL_GetOption('n'));
    work->elems = elems = GV_Malloc(count * sizeof(MotseElem));

    GCL_GetOption('s');

    for (i = 0; (param = GCL_NextStr()) && i != count; i++, elems++)
    {
        elems->param1 = GCL_StrToInt(param);
        elems->sound = GCL_StrToInt(GCL_NextStr());
    }

#ifdef VR_EXE
    work->name = name;
#endif

    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewMotionSoundEffect(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_AFTER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "motse.c");
        if (GetResources(work, name) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
