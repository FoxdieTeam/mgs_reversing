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
    unsigned int field_18;
    unsigned int field_1C;
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
        const int hack = dword_800AB928;
        if ((pActorList->mPause & hack) == 0) 
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

