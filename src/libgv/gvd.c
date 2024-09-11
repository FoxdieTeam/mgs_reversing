#include <libsn.h>
#include "libgv.h"
#include "mts/mts.h"
#include "common.h"

// sbss ===============================================

char   SECTION(".sbss") * GM_StageName_800AB918;
short *SECTION(".sbss") GM_CurrentPadData_800AB91C;
int    SECTION(".sbss") GV_Clock_800AB920;
int    SECTION(".sbss") GV_PassageTime_800AB924;

int GV_Time_800AB330 = 0;
int dword_800AB334 = 0;

extern int            DG_HikituriFlag_8009D460;
extern int            GV_PauseLevel_800AB928;
extern const char    *GV_DebugMes_800AB34C;
extern unsigned char *GV_ResidentMemoryBottom_800AB940;

extern GV_ACT GV_Daemon_800ACBF8;

void GV_ExceptionCallback(void)
{
    printf("HANGUP: %s\n", GV_DebugMes_800AB34C);
}

STATIC void GV_DaemonAct(GV_ACT *actor)
{
    int tmp;

    GV_Time_800AB330++;

    tmp = mts_get_tick_count();

    GV_PassageTime_800AB924 = tmp - dword_800AB334;
    dword_800AB334 = tmp;

    if (DG_HikituriFlag_8009D460 == 0)
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
    // passing heap_80182000 produces addiu instead of ori
    GV_InitMemorySystem(0, 1, (void *)0x80182000, 0x2f000);
    GV_InitMemorySystem(1, 1, (void *)0x801b1000, 0x2f000); // ditto
}

void GV_SetPacketTempMemory(void)
{
    // passing heap_80182000 produces addiu instead of ori
    GV_InitMemorySystem(0, 0, (void *)0x80182000, 0x5e000);
    GV_InitMemorySystem(1, 0, 0, 0);
}

void GV_InitMemory(void)
{
    GV_InitMemorySystemAll();
    GV_ResetPacketMemory();
    // passing heap_80117000 produces addiu instead of ori
    GV_InitMemorySystem(2, 0, (void *)0x80117000, 0x6b000);
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
    GV_InitActor(0, &GV_Daemon_800ACBF8, 0);
    GV_SetNamedActor(&GV_Daemon_800ACBF8, GV_DaemonAct, 0, "gvd.c");
    GV_Clock_800AB920 = 0;
    GV_Time_800AB330 = 0;
    mts_set_exception_func(GV_ExceptionCallback);
}
