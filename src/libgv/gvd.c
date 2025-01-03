#include "libgv.h"

#include <stdio.h>
#include <libsn.h>
#include "common.h"
#include "mts/mts.h"

// sbss ===============================================

char   SECTION(".sbss") * GM_StageName_800AB918;
short *SECTION(".sbss") GM_CurrentPadData_800AB91C;
int    SECTION(".sbss") GV_Clock_800AB920;
int    SECTION(".sbss") GV_PassageTime_800AB924;

int GV_Time = 0;
STATIC int GV_LastTickCount = 0;

extern int            DG_HikituriFlag;
extern int            GV_PauseLevel_800AB928;
extern const char    *GV_DebugMes;
extern unsigned char *GV_ResidentMemoryBottom_800AB940;

extern GV_ACT GV_Daemon_800ACBF8;

void GV_ExceptionCallback(void)
{
    printf("HANGUP: %s\n", GV_DebugMes);
}

STATIC void GV_DaemonAct(GV_ACT *actor)
{
    int ticks;

    GV_Time++;

    ticks = mts_get_tick_count();

    GV_PassageTime_800AB924 = ticks - GV_LastTickCount;
    GV_LastTickCount = ticks;

    if (DG_HikituriFlag == 0)
    {
        // Flip active buffer
        GV_Clock_800AB920 ^= 1;
    }

    if (GV_PauseLevel_800AB928 == 0)
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

void GV_InitMemory(void)
{
    GV_InitMemorySystemAll();
    GV_ResetPacketMemory();
    GV_InitMemorySystem(GV_NORMAL_MEMORY, 0, GV_NORMAL_MEMORY_TOP, GV_NORMAL_MEMORY_SIZE);
    printf("RESIDENT TOP %X\n", (unsigned int)GV_ResidentMemoryBottom_800AB940);
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
    GV_ResidentHeapReset();
    GV_InitLoader();
    GV_InitCacheSystem();
    GV_ResetSystem();
    GV_InitActor(0, &GV_Daemon_800ACBF8, NULL);
    GV_SetNamedActor(&GV_Daemon_800ACBF8, GV_DaemonAct, 0, "gvd.c");
    GV_Clock_800AB920 = 0;
    GV_Time = 0;
    mts_set_exception_func(GV_ExceptionCallback);
}
