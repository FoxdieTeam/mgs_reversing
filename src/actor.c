#include <libsn.h>
#include "actor.h"



int SECTION(".sbss") dword_800AB928;
int SECTION(".sbss") dword_0x800AB92C[4];
short SECTION(".sbss") pad1;
int SECTION(".sbss") gResidentTop_800AB940;
int SECTION(".sbss") dword_800AB944[6];

short SECTION(".sbss") pad2;
int SECTION(".sbss") dword_800AB960[2];
int SECTION(".sbss") dword_800AB968;

short SECTION(".sbss") word_800AB96C;
short SECTION(".sbss") word_800AB96E;
short SECTION(".sbss") word_800AB970[4];

// pad ?

int SECTION(".sbss") dword_800AB978;

char SECTION(".sbss") byte_800AB97C;
char SECTION(".sbss") byte_800AB97D;
short SECTION(".sbss") byte_800AB97E;

short SECTION(".sbss") word_800AB980;
short SECTION(".sbss") word_800AB982;

short SECTION(".sbss") word_800AB984[2];

int SECTION(".sbss") dword_800AB988;
int SECTION(".sbss") dword_800AB98C;


void ZeroMemory_8001619c(void* ptr, int size);
void* sub_8001620C(int size);
void sub_80016230(void* ptr);

#define ACTOR_LIST_COUNT 9

struct ActorList SECTION(".0x800ACC18") gActorsList[ACTOR_LIST_COUNT];

extern struct PauseKill  gPauseKills_8009D308[9];

void GV_ActorList_Init_80014d98(void)
{
	int i;
    struct ActorList* pActorList = gActorsList;

    for (i = 0; i < ACTOR_LIST_COUNT; i++)
    {
		struct Actor* pFirst = &pActorList->first;
		struct Actor* pLast = &pActorList->last;
		
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

    dword_800AB928 = 0;
}

void GV_SetPauseKill_80014e08(int index, short pause, short kill)
{
	struct ActorList* pActorList = &gActorsList[index];
	pActorList->mPause = pause;
    pActorList->mKill = kill;
}

extern void null_printf_8008BBA8(const char*, ...);

extern const char aDumpactorsyste[];
extern const char aLvDPauseDKillD[];
extern const char aLvD04d02d08xS[];

void GV_DumpActorSystem_80014e2c(void)
{
	int i;
	struct ActorList* pActorList = gActorsList;

	null_printf_8008BBA8(aDumpactorsyste);
  
	for (i = 0; i < ACTOR_LIST_COUNT; i++)
	{
		struct Actor* pActor ;

		null_printf_8008BBA8(aLvDPauseDKillD, i, pActorList->mPause, pActorList->mKill);
		
		pActor = &pActorList->first;
	
        for ( ;; )
		{
			struct Actor* pNext = pActor->pNext;

			if (pActor->mFnUpdate)
			{
				int unknown;
				if (pActor->field_1C > 0)
				{
					// TODO: I've yet to see this condition be hit - perhaps an unused feature of the actor system?
					unknown = (pActor->field_18 * 100) /pActor->field_1C;
				}
				else
				{
					unknown = 0;
				}

				null_printf_8008BBA8(aLvD04d02d08xS, i, unknown / 100, unknown % 100, pActor->mFnUpdate, pActor->mName);
				
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
    struct ActorList* pActorList = gActorsList;
    
    for (i = ACTOR_LIST_COUNT; i > 0; i--)
    {
        const int local_dword_800AB928 = dword_800AB928;
        if ((pActorList->mPause & local_dword_800AB928) == 0) 
        {
            struct Actor* pActor = &pActorList->first;
            for (;;)
            {
           
                struct Actor* pCur = pActor;
                struct Actor* pNext = pCur->pNext;
                if (pCur->mFnUpdate)
                {
                     pCur->mFnUpdate( pCur);
                }
				
                dword_800AB9B0 = 0;
                
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
    struct ActorList* pActorList = gActorsList;
    
    for (i = ACTOR_LIST_COUNT; i > 0; i--)
    {
        if (pActorList->mKill <= level) 
        {
            struct Actor* pActor = &pActorList->first;
            for (;;)
            {
           
                struct Actor* pCur = pActor;
                struct Actor* pNext = pCur->pNext;
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

void GV_ActorPushBack_800150a8(int level, struct Actor* pActor, TActorFreeFunction fnFree)
{
	struct Actor* pLast = &gActorsList[level].last;
    struct Actor* pLastPrevious = pLast->pPrevious;

    pLast->pPrevious = pActor;
    pLastPrevious->pNext = pActor;

    pActor->pNext = pLast;
    pActor->pPrevious = pLastPrevious;

    pActor->mFnShutdown = 0;
    pActor->mFnUpdate = 0;
    pActor->mFreeFunc = fnFree;	
}

struct Actor* GV_ActorAlloc_800150e4(int level, int memSize)
{
	struct Actor* pActor = sub_8001620C(memSize);
	if (pActor) 
	{
		ZeroMemory_8001619c(pActor, memSize);
		GV_ActorPushBack_800150a8(level, pActor, sub_80016230);
	}
	return pActor;
}

void GV_ActorInit_8001514c(struct Actor* pActor, TActorFunction pFnUpdate, TActorFunction pFnShutdown, const char* pActorName)
{
	pActor->mFnUpdate = pFnUpdate;
	pActor->mFnShutdown = pFnShutdown;
	pActor->mName = pActorName;
	pActor->field_1C = 0;
	pActor->field_18 = 0;
}

// Removes from linked list and calls shutdown/free funcs
void GV_KillActor_80015164(struct Actor* pActor)
{
	struct Actor* pActorBeingRemoved = pActor;
	struct Actor* pPreviousActor;
	struct Actor* pNextActor;

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

void GV_ActorDelayedKill_800151c8(struct Actor* pActor)
{
	pActor->mFnUpdate = GV_KillActor_80015164;
}

extern const char asc_800AB340[];
extern void mg_printf_8008BBA0(const char*, ...);

void GV_KillActorIfExists_800151d8(struct Actor* pActorToKill)
{
	struct Actor* pNext;
	struct ActorList* pActorList;
	int i;
  
	pActorList = gActorsList;
	for (i = ACTOR_LIST_COUNT; i > 0; i--)
    {
		struct Actor* pCurActor = &pActorList->first;
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

	mg_printf_8008BBA0(asc_800AB340);
}

