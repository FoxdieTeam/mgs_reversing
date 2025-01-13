/**
 * @file actor.c
 * @brief This file contains the implementation of the actor system.
 *
 * The actor system manages a list of actors, allowing for initialization,
 * execution, and destruction of a generic actors. Actors can be added
 * to different lists, and each list can have its own pause and kill levels.
 * The system also supports deferred destruction of actors and provides
 * functions for memory allocation and initialization.
 */

#include <stdio.h>
#include <libsn.h>
#include "libgv.h"
#include "mts/mts.h"    // for cprintf

// 0x0 No pause
// 0x1 codec
// 0x2 game paused
int SECTION(".sbss") GV_PauseLevel_800AB928;
STATIC int SECTION(".sbss") dword_0x800AB92C; //maybe unused

extern ActorList gActorsList_800ACC18[GV_ACTOR_LEVEL];

typedef struct
{
    short pause;
    short kill;
} PauseKill;

// initialization structure for the actor lists
// the pause and kill levels are set for each list
STATIC PauseKill gPauseKills_8009D308[GV_ACTOR_LEVEL] = {
    {  0, 7 },  // 0: GV_ACTOR_DAEMON
    {  0, 7 },  // 1: GV_ACTOR_MANAGER
    {  9, 4 },  // 2: GV_ACTOR_LEVEL2
    {  9, 4 },  // 3: GV_ACTOR_LEVEL3
    { 15, 4 },  // 4: GV_ACTOR_LEVEL4
    { 15, 4 },  // 5: GV_ACTOR_LEVEL5
    { 15, 4 },  // 6: GV_ACTOR_AFTER
    {  9, 4 },  // 7: GV_ACTOR_AFTER2
    {  0, 7 }   // 8: GV_ACTOR_DAEMON2
};

extern int GM_CurrentMap_800AB9B0;

/*---------------------------------------------------------------------------*/

/**
 * @brief Initialize the actors lists and set the pause and kill levels.
 *
 */
void GV_InitActorSystem(void)
{
    int         i;
    ActorList  *lp = gActorsList_800ACC18;

    for (i = 0; i < GV_ACTOR_LEVEL; i++)
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

/**
 * @brief Set the pause and kill levels for an actor list.
 *
 * @param execLevel of the actor list
 * @param pause level to set for the pause flag
 * @param kill level to set for the kill flag
 */
void GV_ConfigActorSystem(int execLevel, short pause, short kill)
{
    ActorList *lp = &gActorsList_800ACC18[execLevel];
    lp->pause = pause;
    lp->kill = kill;
}

/**
 * @brief (Unused) Dump the actor system to the console.
 * Iterate over all actors in all actor lists and print their name and update
 * function.
 */
void GV_DumpActorSystem(void)
{
    int         i;
    ActorList  *lp = gActorsList_800ACC18;

    cprintf("--DumpActorSystem--\n");

    for (i = 0; i < GV_ACTOR_LEVEL; i++)
    {
        GV_ACT *actor;

        cprintf("Lv %d Pause %d Kill %d\n", i, lp->pause, lp->kill);

        actor = &lp->first;

        for (;;)
        {
            GV_ACT *next = actor->next;

            if (actor->act)
            {
                int unknown;
                if (actor->field_1C > 0)
                {
                    // TODO: I've yet to see this condition be hit - perhaps an
                    // unused feature of the actor system?
                    unknown = (actor->field_18 * 100) / actor->field_1C;
                }
                else
                {
                    unknown = 0;
                }

                cprintf("Lv%d %04d.%02d %08X %s\n", i,
                        unknown / 100,
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

/**
 * @brief Execute all actors in the actor system.
 * Iterate over all actors in all actor lists and call their update function.
 * This function is invoked continuously and represent the main game loop.
 */
void GV_ExecActorSystem(void)
{
    int         i;
    ActorList  *lp = gActorsList_800ACC18;

    // for every actor list
    for (i = GV_ACTOR_LEVEL; i > 0; i--)
    {
        // don't execute actors when the pause flag matches the
        // current pause level
        const int pause_level = GV_PauseLevel_800AB928;
        if ((lp->pause & pause_level) == 0)
        {
            // iterate over all actors in the list
            GV_ACT *actor = &lp->first;
            for (;;)
            {

                GV_ACT *current = actor;
                GV_ACT *next = current->next;
                // if the actor has an update function, call it
                if (current->act)
                {
                    current->act(current);
                }

                GM_CurrentMap_800AB9B0 = 0;
                // continue to the next actor until we reach the end of the list
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

/**
 * @brief Deferred destruction of actors in the actor system.
 *
 * @param execLevel The level at which to destroy actors.
 */
void GV_DestroyActorSystem(int execLevel)
{
    int         i;
    ActorList  *lp = gActorsList_800ACC18;

    // iterate over all actor lists
    for (i = GV_ACTOR_LEVEL; i > 0; i--)
    {
        // check only for lists with a specific kill level
        if (lp->kill <= execLevel)
        {
            GV_ACT *actor = &lp->first;
            for (;;)
            {

                GV_ACT *current = actor;
                GV_ACT *next = current->next;
                // if the actor has an update function or
                // a shutdown function, call it
                if (current->act || current->die)
                {
                    GV_DestroyActor(current);
                }
                // continue to the next actor until we reach the end of the list
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

/**
 * @brief Initialize an actor and add it at the end of the selected list
 *
 * @param execLevel The id of the list where the actor will be added.
 * @param actor The actor to add.
 * @param free_func The function to call when freeing the actor.
 */
void GV_InitActor(int execLevel, GV_ACT *actor, GV_FREEFUNC free_func)
{
    GV_ACT *last = &gActorsList_800ACC18[execLevel].last;
    GV_ACT *last_prev = last->prev;

    last->prev = actor;
    last_prev->next = actor;

    actor->next = last;
    actor->prev = last_prev;

    actor->die = NULL;
    actor->act = NULL;
    actor->free = free_func;
}

/**
 * @brief Allocate memory for an actor and initialize it.
 *
 * @param execLevel The id of the execution list where the actor will be added.
 * @param memSize The size of the actor.
 * @return GV_ACT* The allocated actor.
 */
GV_ACT *GV_NewActor(int execLevel, int memSize)
{
    GV_ACT *actor = GV_Malloc(memSize);
    if (actor)
    {
        GV_ZeroMemory(actor, memSize);
        GV_InitActor(execLevel, actor, GV_Free);
    }
    return actor;
}

void GV_SetNamedActor(GV_ACT *actor, GV_ACTFUNC act_func,
                      GV_ACTFUNC die_func, const char *filename)
{
    actor->act = act_func;
    actor->die = die_func;
    actor->filename = filename;
    actor->field_1C = 0;
    actor->field_18 = 0;
}

// Removes from linked list and calls shutdown/free funcs
/**
 * @brief Destroys an actor quickly by removing it from the actor list.
 * If the actor has a destructor and memory freeing functions, they are called.
 *
 * @param actor Pointer to the actor to be destroyed.
 */
void GV_DestroyActorQuick(GV_ACT *actor)
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

/**
 * @brief Schedule the destruction of an actor for the next activation cycle
 * by setting its update function.
 *
 * @param actor The actor to destroy.
 */
void GV_DestroyActor(GV_ACT *actor)
{
    actor->act = GV_DestroyActorQuick;
}

void GV_DestroyOtherActor(GV_ACT *actor)
{
    GV_ACT     *next;
    ActorList  *lp;
    int         i;

    lp = gActorsList_800ACC18;
    for (i = GV_ACTOR_LEVEL; i > 0; i--)
    {
        GV_ACT *current = &lp->first;
        do {
            next = current->next;
            if (current == actor)
            {
                GV_DestroyActor(current);
                return;
            }
            current = next;
        } while (next);
        lp++;
    }

    printf("#");
}

const char *GV_DebugMes = "none";
