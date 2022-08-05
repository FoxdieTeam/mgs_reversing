#ifndef ACTOR_H_
#define ACTOR_H_

#include <LIBSN.H>
#include "libgv/libgv.h"

struct Actor;

typedef void (*TActorFunction)(struct Actor *);
typedef void (*TActorFreeFunction)(void *);

typedef struct Actor
{
    struct Actor      *pPrevious;
    struct Actor      *pNext;
    TActorFunction     mFnUpdate;
    TActorFunction     mFnShutdown;
    TActorFreeFunction mFreeFunc;
    const char        *mName;
    int                field_18;
    int                field_1C;
} Actor;

struct ActorList
{
    struct Actor first;
    struct Actor last;
    short        mPause;
    short        mKill;
};

#define ACTOR_LIST_COUNT 9
struct PauseKill
{
    short pause;
    short kill;
};

extern int GM_CurrentMap_800AB9B0;

void          GV_ExecActorSystem_80014F88(void);
struct Actor *GV_NewActor_800150E4(int level, int memSize);
void          GV_InitActorSystem_80014D98(void);
void          GV_InitActor_800150A8(int level, struct Actor *pActor, TActorFreeFunction fnFree);
void          GV_SetNamedActor_8001514C(struct Actor *pActor, TActorFunction pFnUpdate, TActorFunction pFnShutdown,
                                        const char *pActorName);
void          GV_DestroyActor_800151C8(struct Actor *pActor);
void          GV_DestroyOtherActor_800151D8(struct Actor *pActorToKill);
void          GV_DestroyActorQuick_80015164(struct Actor *pActor);

#endif // ACTOR_H_
