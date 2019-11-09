#include <libsn.h>

#define SECTION(x) __attribute__((section(x)))

int SECTION(".sbss") dword_800AB918;
int SECTION(".sbss") dword_800AB91C;
int SECTION(".sbss") dword_800AB920;
int SECTION(".sbss") dword_800AB924;

int SECTION(".sbss") dword_800AB928;
int SECTION(".sbss") dword_0x800AB92C[4];
short SECTION(".sbss") pad1;
int SECTION(".sbss") dword_800AB940[7];

short SECTION(".sbss") pad2;
int SECTION(".sbss") dword_800AB960[2];
int SECTION(".sbss") dword_800AB968[5];

short SECTION(".sbss") word_800AB980[17];

int SECTION(".sbss") dword_800AB9A0[2];
int SECTION(".sbss") dword_800AB9A8[2];

// 2nd

struct Actor;

typedef void(*TActorFunction)(struct Actor*);

struct Actor
{
    struct Actor* pPrevious;
    struct Actor* pNext;
    TActorFunction mFnUpdate;
    TActorFunction mFnShutdown;
    TActorFunction mFreeFunc;
    const char* mName;
    int field_18;
    int field_1C;
};

struct ActorList
{
    struct Actor first;
    struct Actor last;
    short mPause;
    short mKill;
};

struct ActorList SECTION(".0x800ACC18") gActorsList[9];

extern int dword_800AB9B0;

void SECTION(".0x80014f88") GV_ExecActorSystem(void)
{
    int i;
    struct ActorList* pActorList = gActorsList;
    
    for (i =9; i > 0; i--)
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

void SECTION(".0x8001514c") GV_ActorInit_8001514c(struct Actor* pActor, TActorFunction pFnUpdate, TActorFunction pFnShutdown, const char* pActorName)
{
	pActor->mFnUpdate = pFnUpdate;
	pActor->mFnShutdown = pFnShutdown;
	pActor->mName = pActorName;
	pActor->field_1C = 0;
	pActor->field_18 = 0;
}


// Removes from linked list and calls shutdown/free funcs
void SECTION(".0x80015164") GV_KillActor_80015164(struct Actor* pActor)
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

