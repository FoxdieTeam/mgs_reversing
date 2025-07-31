#define __GVD_SBSS__
#include "libgv.h"

#include <stdio.h>
#include <libsn.h>
#include "common.h"
#include "mts/mts.h"
#include "libdg/libdg.h"    // for DG_HikituriFlag

extern unsigned char *GV_ResidentMemoryBottom;

/*---------------------------------------------------------------------------*/

char   SECTION(".sbss") *GM_StageName;
short *SECTION(".sbss")  GM_CurrentPadData;
int    SECTION(".sbss")  GV_Clock;
int    SECTION(".sbss")  GV_PassageTime;

int GV_Time = 0;
STATIC int GV_LastTickCount = 0;

typedef struct {
    GV_ACT actor;
} Work;

extern Work GV_Work_800ACBF8;

/*---------------------------------------------------------------------------*/

static void GV_ExceptionCallback(void)
{
    printf("HANGUP: %s\n", GV_DebugMes);
}

static void Act(Work *work)
{
    int ticks;

    GV_Time++;

    ticks = mts_get_tick_count();

    GV_PassageTime = ticks - GV_LastTickCount;
    GV_LastTickCount = ticks;

    if (DG_HikituriFlag == 0)
    {
        // Flip active buffer
        GV_Clock ^= 1;
    }

    if (GV_PauseLevel == 0)
    {
        GV_ClearMessageSystem();
    }
}

void GV_ResetPacketMemory(void)
{
    GV_InitMemorySystem(GV_PACKET_MEMORY0, 1, GV_PACKET_MEMORY0_TOP, GV_PACKET_MEMORY_SIZE);
    GV_InitMemorySystem(GV_PACKET_MEMORY1, 1, GV_PACKET_MEMORY1_TOP, GV_PACKET_MEMORY_SIZE);
}

void GV_SetPacketTempMemory(void)
{
    GV_InitMemorySystem(GV_PACKET_MEMORY0, 0, GV_PACKET_MEMORY0_TOP, (GV_PACKET_MEMORY_SIZE * 2));
    GV_InitMemorySystem(GV_PACKET_MEMORY1, 0, NULL, 0);
}

static void GV_InitMemory(void)
{
    GV_InitMemorySystemAll();
    GV_ResetPacketMemory();
    GV_InitMemorySystem(GV_NORMAL_MEMORY, 0, GV_NORMAL_MEMORY_TOP, GV_NORMAL_MEMORY_SIZE);
    printf("RESIDENT TOP %X\n", (unsigned int)GV_ResidentMemoryBottom);
}

void GV_ResetSystem(void)
{
    GV_InitMessageSystem();
    GV_InitPadSystem();
}

void GV_ResetMemory(void)
{
    GV_FreeCacheSystem();
    GV_InitMemory();
}

void GV_StartDaemon(void)
{
    GV_InitActorSystem();
    GV_InitResidentMemory();
    GV_InitLoader();
    GV_InitCacheSystem();
    GV_ResetSystem();

    GV_InitActor(GV_ACTOR_DAEMON, &GV_Work_800ACBF8.actor, NULL);
    GV_SetNamedActor(&GV_Work_800ACBF8.actor, Act, NULL, "gvd.c");

    GV_Clock = 0;
    GV_Time = 0;

    mts_set_exception_func(GV_ExceptionCallback);
}
