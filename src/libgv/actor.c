#include <LIBSN.H>
#include "libgv.h"
#include "mts/mts_new.h"

int SECTION(".sbss") GV_PauseLevel_800AB928;

int SECTION(".sbss") dword_0x800AB92C;

LibGV_FileRecord *SECTION(".sbss") GV_CurrentTag_800AB930;
LibGV_FileRecord *SECTION(".sbss") GV_ResidentFileRecords_800AB934;
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
    struct ActorList *pActorList = gActorsList_800ACC18;

    for (i = 0; i < ACTOR_LIST_COUNT; i++)
    {
        GV_ACT *pFirst = &pActorList->first;
        GV_ACT *pLast = &pActorList->last;

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

void GV_ConfigActorSystem_80014E08(int index, short pause, short kill)
{
    struct ActorList *pActorList = &gActorsList_800ACC18[index];
    pActorList->mPause = pause;
    pActorList->mKill = kill;
}

void GV_DumpActorSystem_80014E2C(void)
{
    int               i;
    struct ActorList *pActorList = gActorsList_800ACC18;

    mts_null_printf_8008BBA8("--DumpActorSystem--\n");

    for (i = 0; i < ACTOR_LIST_COUNT; i++)
    {
        GV_ACT *pActor;

        mts_null_printf_8008BBA8("Lv %d Pause %d Kill %d\n",
                                 i,
                                 pActorList->mPause,
                                 pActorList->mKill);

        pActor = &pActorList->first;

        for (;;)
        {
            GV_ACT *pNext = pActor->pNext;

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

                mts_null_printf_8008BBA8("Lv%d %04d.%02d %08X %s\n",
                                         i, unknown / 100,
                                         unknown % 100,
                                         pActor->mFnUpdate,
                                         pActor->mName);

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
    int               i;
    struct ActorList *pActorList = gActorsList_800ACC18;

    for (i = ACTOR_LIST_COUNT; i > 0; i--)
    {
        const int local_GV_PauseLevel_800AB928 = GV_PauseLevel_800AB928;
        if ((pActorList->mPause & local_GV_PauseLevel_800AB928) == 0)
        {
            GV_ACT *pActor = &pActorList->first;
            for (;;)
            {

                GV_ACT *pCur = pActor;
                GV_ACT *pNext = pCur->pNext;
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

void GV_DestroyActorSystem_80015010(int level)
{
    int               i;
    struct ActorList *pActorList = gActorsList_800ACC18;

    for (i = ACTOR_LIST_COUNT; i > 0; i--)
    {
        if (pActorList->mKill <= level)
        {
            GV_ACT *pActor = &pActorList->first;
            for (;;)
            {

                GV_ACT *pCur = pActor;
                GV_ACT *pNext = pCur->pNext;
                if (pCur->mFnUpdate || pCur->mFnShutdown)
                {
                    GV_DestroyActor_800151C8(pCur);
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

void GV_InitActor_800150A8(int level, GV_ACT *pActor, TActorFreeFunction fnFree)
{
    GV_ACT *pLast = &gActorsList_800ACC18[level].last;
    GV_ACT *pLastPrevious = pLast->pPrevious;

    pLast->pPrevious = pActor;
    pLastPrevious->pNext = pActor;

    pActor->pNext = pLast;
    pActor->pPrevious = pLastPrevious;

    pActor->mFnShutdown = 0;
    pActor->mFnUpdate = 0;
    pActor->mFreeFunc = fnFree;
}

GV_ACT *GV_NewActor_800150E4(int level, int memSize)
{
    GV_ACT *pActor = GV_Malloc_8001620C(memSize);
    if (pActor)
    {
        GV_ZeroMemory_8001619C(pActor, memSize);
        GV_InitActor_800150A8(level, pActor, GV_Free_80016230);
    }
    return pActor;
}

void GV_SetNamedActor_8001514C(GV_ACT *pActor, TActorFunction pFnUpdate, TActorFunction pFnShutdown,
                               const char *pActorName)
{
    pActor->mFnUpdate = pFnUpdate;
    pActor->mFnShutdown = pFnShutdown;
    pActor->mName = pActorName;
    pActor->field_1C = 0;
    pActor->field_18 = 0;
}

// Removes from linked list and calls shutdown/free funcs
void GV_DestroyActorQuick_80015164(GV_ACT *pActor)
{
    GV_ACT *pActorBeingRemoved = pActor;
    GV_ACT *pPreviousActor;
    GV_ACT *pNextActor;

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

void GV_DestroyActor_800151C8(GV_ACT *pActor)
{
    pActor->mFnUpdate = GV_DestroyActorQuick_80015164;
}

void GV_DestroyOtherActor_800151D8(GV_ACT *pActorToKill)
{
    GV_ACT     *pNext;
    struct ActorList *pActorList;
    int               i;

    pActorList = gActorsList_800ACC18;
    for (i = ACTOR_LIST_COUNT; i > 0; i--)
    {
        GV_ACT *pCurActor = &pActorList->first;
        do
        {
            pNext = pCurActor->pNext;
            if (pCurActor == pActorToKill)
            {
                GV_DestroyActor_800151C8(pCurActor);
                return;
            }
            pCurActor = pNext;
        } while (pNext);
        pActorList++;
    }

    printf("#");
}

const char *GV_DebugMes_800AB34C = "none";
