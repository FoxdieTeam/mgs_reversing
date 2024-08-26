#include <libsn.h>
#include "libgv.h"
#include "mts/mts_new.h"

int SECTION(".sbss") GV_PauseLevel_800AB928;

int SECTION(".sbss") dword_0x800AB92C;

GV_CACHE_TAG     *SECTION(".sbss") GV_CurrentTag_800AB930;
GV_CACHE_TAG     *SECTION(".sbss") GV_ResidentFileRecords_800AB934;
int               SECTION(".sbss") N_ResidentFileRecords_800AB938;

short          SECTION(".sbss") dword_800AB93C;
unsigned char *SECTION(".sbss") GV_ResidentMemoryBottom_800AB940;
int            SECTION(".sbss") dword_800AB944;
int            SECTION(".sbss") active_msg_queue_800AB948;
int            SECTION(".sbss") dword_800AB94C;
int            SECTION(".sbss") dword_800AB950;
int            SECTION(".sbss") dword_800AB954;

int SECTION(".sbss") GV_DemoPadStatus_800AB958;
int SECTION(".sbss") GV_DemoPadAnalog_800AB95C;

extern struct ActorList gActorsList_800ACC18[ACTOR_LIST_COUNT];

struct PauseKill gPauseKills_8009D308[9] = {{0, 7},  {0, 7},  {9, 4}, {9, 4}, {15, 4},
                                            {15, 4}, {15, 4}, {9, 4}, {0, 7}};

extern int GM_CurrentMap_800AB9B0;

void GV_InitActorSystem_80014D98(void)
{
    int               i;
    struct ActorList *lp = gActorsList_800ACC18;

    for (i = 0; i < ACTOR_LIST_COUNT; i++)
    {
        GV_ACT *first = &lp->first;
        GV_ACT *last = &lp->last;

        first->prev = 0;
        first->next = last;

        last->prev = first;
        last->next = 0;

        first->die = 0;
        first->act = 0;

        last->die = 0;
        last->act = 0;

        lp->pause = gPauseKills_8009D308[i].pause;
        lp->kill = gPauseKills_8009D308[i].kill;

        lp++;
    }

    GV_PauseLevel_800AB928 = 0;
}

void GV_ConfigActorSystem_80014E08(int index, short pause, short kill)
{
    struct ActorList *lp = &gActorsList_800ACC18[index];
    lp->pause = pause;
    lp->kill = kill;
}

void GV_DumpActorSystem_80014E2C(void)
{
    int               i;
    struct ActorList *lp = gActorsList_800ACC18;

    mts_null_printf_8008BBA8("--DumpActorSystem--\n");

    for (i = 0; i < ACTOR_LIST_COUNT; i++)
    {
        GV_ACT *actor;

        mts_null_printf_8008BBA8("Lv %d Pause %d Kill %d\n",
                                 i, lp->pause, lp->kill);

        actor = &lp->first;

        for (;;)
        {
            GV_ACT *next = actor->next;

            if (actor->act)
            {
                int unknown;
                if (actor->field_1C > 0)
                {
                    // TODO: I've yet to see this condition be hit - perhaps an unused feature of the actor system?
                    unknown = (actor->field_18 * 100) / actor->field_1C;
                }
                else
                {
                    unknown = 0;
                }

                mts_null_printf_8008BBA8("Lv%d %04d.%02d %08X %s\n",
                                         i, unknown / 100,
                                         unknown % 100,
                                         actor->act,
                                         actor->filename);

                actor->field_1C = 0;
                actor->field_18 = 0;
            }

            actor = next;

            if (!next)
            {
                break;
            }
        }
        lp++;
    }
}

void GV_ExecActorSystem_80014F88(void)
{
    int               i;
    struct ActorList *lp = gActorsList_800ACC18;

    for (i = ACTOR_LIST_COUNT; i > 0; i--)
    {
        const int pause_level = GV_PauseLevel_800AB928;
        if ((lp->pause & pause_level) == 0)
        {
            GV_ACT *actor = &lp->first;
            for (;;)
            {

                GV_ACT *current = actor;
                GV_ACT *next = current->next;
                if (current->act)
                {
                    current->act(current);
                }

                GM_CurrentMap_800AB9B0 = 0;

                actor = next;
                if (!next)
                {
                    break;
                }
            }
        }
        lp++;
    }
}

void GV_DestroyActorSystem_80015010(int level)
{
    int               i;
    struct ActorList *lp = gActorsList_800ACC18;

    for (i = ACTOR_LIST_COUNT; i > 0; i--)
    {
        if (lp->kill <= level)
        {
            GV_ACT *actor = &lp->first;
            for (;;)
            {

                GV_ACT *current = actor;
                GV_ACT *next = current->next;
                if (current->act || current->die)
                {
                    GV_DestroyActor_800151C8(current);
                }

                actor = next;
                if (!next)
                {
                    break;
                }
            }
        }
        lp++;
    }
}

void GV_InitActor_800150A8(int level, GV_ACT *actor, TActorFreeFunction free_func)
{
    GV_ACT *last = &gActorsList_800ACC18[level].last;
    GV_ACT *last_prev = last->prev;

    last->prev = actor;
    last_prev->next = actor;

    actor->next = last;
    actor->prev = last_prev;

    actor->die = 0;
    actor->act = 0;
    actor->free = free_func;
}

GV_ACT *GV_NewActor_800150E4(int level, int memSize)
{
    GV_ACT *actor = GV_Malloc_8001620C(memSize);
    if (actor)
    {
        GV_ZeroMemory_8001619C(actor, memSize);
        GV_InitActor_800150A8(level, actor, GV_Free_80016230);
    }
    return actor;
}

void GV_SetNamedActor_8001514C(GV_ACT *actor, TActorFunction act_func, TActorFunction die_func,
                               const char *filename)
{
    actor->act = act_func;
    actor->die = die_func;
    actor->filename = filename;
    actor->field_1C = 0;
    actor->field_18 = 0;
}

// Removes from linked list and calls shutdown/free funcs
void GV_DestroyActorQuick_80015164(GV_ACT *actor)
{
    GV_ACT *act = actor;
    GV_ACT *prev;
    GV_ACT *next;

    // Get points to current next/prev
    next = act->next;
    prev = act->prev;

    // Set the next actor prev to the actor behind to remove us from the back chain
    next->prev = prev;

    // Set the prev actor next to the actor ahead to remove us from the forward chain
    prev->next = next;

    // Our prev/next are no longer valid
    act->prev = 0;
    act->next = 0;

    // Same purpose as C++ destructor
    if (act->die)
    {
        act->die(act);
    }

    // Memory freeing function
    if (act->free)
    {
        act->free(act);
    }
}

void GV_DestroyActor_800151C8(GV_ACT *actor)
{
    actor->act = GV_DestroyActorQuick_80015164;
}

void GV_DestroyOtherActor_800151D8(GV_ACT *actor)
{
    GV_ACT           *next;
    struct ActorList *lp;
    int               i;

    lp = gActorsList_800ACC18;
    for (i = ACTOR_LIST_COUNT; i > 0; i--)
    {
        GV_ACT *current = &lp->first;
        do {
            next = current->next;
            if (current == actor)
            {
                GV_DestroyActor_800151C8(current);
                return;
            }
            current = next;
        } while (next);
        lp++;
    }

    printf("#");
}

const char *GV_DebugMes_800AB34C = "none";
