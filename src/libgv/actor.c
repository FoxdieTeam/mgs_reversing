#include <libsn.h>
#include "actor.h"
#include "mts_new.h"

int SECTION(".sbss") GV_PauseLevel_800AB928;

int SECTION(".sbss") dword_0x800AB92C;

LibGV_FileRecord *SECTION(".sbss") dword_800AB930;
int SECTION(".sbss") dword_0x800AB934[2];

short SECTION(".sbss") pad1;
unsigned char *SECTION(".sbss") gResidentTop_800AB940;
int SECTION(".sbss") dword_800AB944;
int SECTION(".sbss") active_msg_queue_800AB948; 
int SECTION(".sbss") dword_800AB94C; 
int SECTION(".sbss") dword_800AB950;
int SECTION(".sbss") dword_800AB954;

int SECTION(".sbss") GV_DemoPadStatus_800AB958;
int SECTION(".sbss") GV_DemoPadAnalog_800AB95C;

void GV_ZeroMemory_8001619c(void *ptr, int size);
void *GV_Malloc_8001620C(int size);
void GV_Free_80016230(void *ptr);

#define ACTOR_LIST_COUNT 9

struct ActorList SECTION(".0x800ACC18") gActorsList[ACTOR_LIST_COUNT];

extern struct PauseKill gPauseKills_8009D308[9];

void GV_ActorList_Init_80014d98(void)
{
    int i;
    struct ActorList *pActorList = gActorsList;

    for (i = 0; i < ACTOR_LIST_COUNT; i++)
    {
        struct Actor *pFirst = &pActorList->first;
        struct Actor *pLast = &pActorList->last;

        pFirst->pPrevious = 0;
        pFirst->pNext = pLast;

        pLast->pPrevious = pFirst;
        pLast->pNext = 0;

        pFirst->mFnShutdown = 0;
        pFirst->mFnUpdate = 0;

        pLast->mFnShutdown = 0;
        pLast->mFnUpdate = 0;

        pActorList->mPause = gPauseKills_8009D308[i].pause;
        pActorList->mKill = gPauseKills_8009D308[i].kill;

        pActorList++;
    }

    GV_PauseLevel_800AB928 = 0;
}

void GV_SetPauseKill_80014e08(int index, short pause, short kill)
{
    struct ActorList *pActorList = &gActorsList[index];
    pActorList->mPause = pause;
    pActorList->mKill = kill;
}

extern const char aDumpactorsyste[];
extern const char aLvDPauseDKillD[];
extern const char aLvD04d02d08xS[];

void GV_DumpActorSystem_80014e2c(void)
{
    int i;
    struct ActorList *pActorList = gActorsList;

    mts_null_printf_8008BBA8(aDumpactorsyste);

    for (i = 0; i < ACTOR_LIST_COUNT; i++)
    {
        struct Actor *pActor;

        mts_null_printf_8008BBA8(aLvDPauseDKillD, i, pActorList->mPause, pActorList->mKill);

        pActor = &pActorList->first;

        for (;;)
        {
            struct Actor *pNext = pActor->pNext;

            if (pActor->mFnUpdate)
            {
                int unknown;
                if (pActor->field_1C > 0)
                {
                    // TODO: I've yet to see this condition be hit - perhaps an unused feature of the actor system?
                    unknown = (pActor->field_18 * 100) / pActor->field_1C;
                }
                else
                {
                    unknown = 0;
                }

                mts_null_printf_8008BBA8(aLvD04d02d08xS, i, unknown / 100, unknown % 100, pActor->mFnUpdate, pActor->mName);

                pActor->field_1C = 0;
                pActor->field_18 = 0;
            }

            pActor = pNext;

            if (!pNext)
            {
                break;
            }
        }
        pActorList++;
    }
}

void GV_ExecActorSystem_80014F88(void)
{
    int i;
    struct ActorList *pActorList = gActorsList;

    for (i = ACTOR_LIST_COUNT; i > 0; i--)
    {
        const int local_GV_PauseLevel_800AB928 = GV_PauseLevel_800AB928;
        if ((pActorList->mPause & local_GV_PauseLevel_800AB928) == 0)
        {
            struct Actor *pActor = &pActorList->first;
            for (;;)
            {

                struct Actor *pCur = pActor;
                struct Actor *pNext = pCur->pNext;
                if (pCur->mFnUpdate)
                {
                    pCur->mFnUpdate(pCur);
                }

                GM_CurrentMap_800AB9B0 = 0;

                pActor = pNext;
                if (!pNext)
                {
                    break;
                }
            }
        }
        pActorList++;
    }
}

void GV_ActorsKillAtLevel_80015010(int level)
{
    int i;
    struct ActorList *pActorList = gActorsList;

    for (i = ACTOR_LIST_COUNT; i > 0; i--)
    {
        if (pActorList->mKill <= level)
        {
            struct Actor *pActor = &pActorList->first;
            for (;;)
            {

                struct Actor *pCur = pActor;
                struct Actor *pNext = pCur->pNext;
                if (pCur->mFnUpdate || pCur->mFnShutdown)
                {
                    GV_ActorDelayedKill_800151c8(pCur);
                }

                pActor = pNext;
                if (!pNext)
                {
                    break;
                }
            }
        }
        pActorList++;
    }
}

void GV_ActorPushBack_800150a8(int level, struct Actor *pActor, TActorFreeFunction fnFree)
{
    struct Actor *pLast = &gActorsList[level].last;
    struct Actor *pLastPrevious = pLast->pPrevious;

    pLast->pPrevious = pActor;
    pLastPrevious->pNext = pActor;

    pActor->pNext = pLast;
    pActor->pPrevious = pLastPrevious;

    pActor->mFnShutdown = 0;
    pActor->mFnUpdate = 0;
    pActor->mFreeFunc = fnFree;
}

struct Actor *GV_ActorAlloc_800150e4(int level, int memSize)
{
    struct Actor *pActor = GV_Malloc_8001620C(memSize);
    if (pActor)
    {
        GV_ZeroMemory_8001619c(pActor, memSize);
        GV_ActorPushBack_800150a8(level, pActor, GV_Free_80016230);
    }
    return pActor;
}

void GV_ActorInit_8001514c(struct Actor *pActor, TActorFunction pFnUpdate, TActorFunction pFnShutdown, const char *pActorName)
{
    pActor->mFnUpdate = pFnUpdate;
    pActor->mFnShutdown = pFnShutdown;
    pActor->mName = pActorName;
    pActor->field_1C = 0;
    pActor->field_18 = 0;
}

// Removes from linked list and calls shutdown/free funcs
void GV_KillActor_80015164(struct Actor *pActor)
{
    struct Actor *pActorBeingRemoved = pActor;
    struct Actor *pPreviousActor;
    struct Actor *pNextActor;

    // Get points to current next/prev
    pNextActor = pActorBeingRemoved->pNext;
    pPreviousActor = pActorBeingRemoved->pPrevious;

    // Set the next actor prev to the actor behind to remove us from the back chain
    pNextActor->pPrevious = pPreviousActor;

    // Set the prev actor next to the actor ahead to remove us from the forward chain
    pPreviousActor->pNext = pNextActor;

    // Our prev/next are no longer valid
    pActorBeingRemoved->pPrevious = 0;
    pActorBeingRemoved->pNext = 0;

    // Same purpose as C++ destructor
    if (pActorBeingRemoved->mFnShutdown)
    {
        pActorBeingRemoved->mFnShutdown(pActorBeingRemoved);
    }

    // Memory freeing function
    if (pActorBeingRemoved->mFreeFunc)
    {
        pActorBeingRemoved->mFreeFunc(pActorBeingRemoved);
    }
}

void GV_ActorDelayedKill_800151c8(struct Actor *pActor)
{
    pActor->mFnUpdate = GV_KillActor_80015164;
}

extern void mts_printf_8008BBA0(const char *, ...);

void GV_KillActorIfExists_800151d8(struct Actor *pActorToKill)
{
    struct Actor *pNext;
    struct ActorList *pActorList;
    int i;

    pActorList = gActorsList;
    for (i = ACTOR_LIST_COUNT; i > 0; i--)
    {
        struct Actor *pCurActor = &pActorList->first;
        do
        {
            pNext = pCurActor->pNext;
            if (pCurActor == pActorToKill)
            {
                GV_ActorDelayedKill_800151c8(pCurActor);
                return;
            }
            pCurActor = pNext;
        } while (pNext);
        pActorList++;
    }

    mts_printf_8008BBA0("#");
}
