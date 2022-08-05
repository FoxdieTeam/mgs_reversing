#include <LIBSN.H>
#include "actor.h"
#include "libgv.h"
#include "mts/mts_new.h"

// sbss ===============================================

char   SECTION(".sbss") * GM_StageName_800AB918;    // sbss
short *SECTION(".sbss") GM_CurrentPadData_800AB91C; // sbss
int    SECTION(".sbss") GV_Clock_800AB920;          // sbss
int    SECTION(".sbss") GV_PassageTime_800AB924;    // sbss

int GV_Time_800AB330 = 0; // sdata
int dword_800AB334 = 0;   // sdata

extern int            DG_HikituriFlag_8009D460;
extern int            GV_PauseLevel_800AB928;
extern const char    *GV_DebugMes_800AB34C;
extern const char     aHangupS[];
extern unsigned char *GV_ResidentMemoryBottom_800AB940;
extern const char     aResidentTopX[];

unsigned char SECTION(".heap_80182000") heap_80182000[0x5E000];
unsigned char SECTION(".heap_80117000") heap_80117000[0x6b000];


extern struct Actor gGVActor_800acbf8;

void Callback_Hangup_80014B34(void)
{
    mts_printf_8008BBA0(aHangupS, GV_DebugMes_800AB34C);
}

void GV_Act_80014B60(Actor *pGv)
{
    int tmp;

    GV_Time_800AB330++;

    tmp = mts_get_tick_count_8008BBB0();

    GV_PassageTime_800AB924 = tmp - dword_800AB334;
    dword_800AB334 = tmp;

    if (DG_HikituriFlag_8009D460 == 0)
    {
        // Flip active buffer
        GV_Clock_800AB920 ^= 1;
    }

    if (GV_PauseLevel_800AB928 == 0)
    {
        GV_ClearMessageSystem_800164C8();
    }
}

void GV_ResetPacketMemory_80014BD8(void)
{
    GV_InitMemorySystem_80015AF4(0, 1, (void *)0x80182000,
                                 sizeof(heap_80182000) / 2); // passing heap_80182000 produces addiu instead of ori
    GV_InitMemorySystem_80015AF4(1, 1, (void *)0x80182000 + sizeof(heap_80182000) / 2,
                                 sizeof(heap_80182000) / 2); // ditto
}

void GV_SetPacketTempMemory_80014C28()
{
    GV_InitMemorySystem_80015AF4(0, 0, (void *)0x80182000,
                                 sizeof(heap_80182000)); // passing heap_80182000 produces addiu instead of ori
    GV_InitMemorySystem_80015AF4(1, 0, 0, 0);
}

void GV_Memory_Init_80014C70(void)
{
    GV_InitMemorySystemAll_80015AB0();
    GV_ResetPacketMemory_80014BD8();
    GV_InitMemorySystem_80015AF4(2, 0, (void *)0x80117000,
                                 sizeof(heap_80117000)); // passing heap_80117000 produces addiu instead of ori
    mts_printf_8008BBA0(aResidentTopX, GV_ResidentMemoryBottom_800AB940);
}

void GV_ResetSystem_80014CC8(void)
{
    GV_InitMessageSystem_800164AC();
    GV_InitPadSystem_800167C8();
}

void GV_ResetMemory_80014CF0(void)
{
    GV_FreeCacheSystem_80015540();
    GV_Memory_Init_80014C70();
}

void GV_StartDaemon_80014D18(void)
{
    GV_InitActorSystem_80014D98();
    GV_ResidentHeapReset_800163B0();
    GV_InitLoader_80015434();
    GV_InitCacheSystem_80015458();
    GV_ResetSystem_80014CC8();
    GV_InitActor_800150A8(0, &gGVActor_800acbf8, 0);
    GV_SetNamedActor_8001514C(&gGVActor_800acbf8, GV_Act_80014B60, 0, "gvd.c"); // sdata
    GV_Clock_800AB920 = 0;
    GV_Time_800AB330 = 0;
    mts_set_exception_func_800892A8((int)Callback_Hangup_80014B34); // TODO: fix func args
}
