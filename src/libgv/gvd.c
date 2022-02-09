#include <libsn.h>
#include "actor.h"
#include "system.h"
#include "mts_new.h"

// sbss ===============================================

char SECTION(".sbss") *GM_StageName_800AB918; // sbss
int SECTION(".sbss") GM_CurrentPadData_800AB91C; // sbss
int SECTION(".sbss") GV_Clock_800AB920; // sbss
int SECTION(".sbss") GV_PassageTime_800AB924; // sbss

int gRenderedFramesCount_800AB330 = 0; // sdata
int dword_800AB334 = 0; // sdata


extern int DG_HikituriFlag_8009D460;
extern int GV_PauseLevel_800AB928;

int mts_get_tick_count_8008BBB0(void);
void GV_ClearMessageSystem_800164C8(void);

void GV_Act_80014b60(Actor* pGv)
{
	int tmp;

	gRenderedFramesCount_800AB330++;
	
	tmp = mts_get_tick_count_8008BBB0();
	
	GV_PassageTime_800AB924 = tmp - dword_800AB334;
	dword_800AB334= tmp;

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

unsigned char SECTION(".heap_80182000") heap_80182000[0x5E000];
unsigned char SECTION(".heap_80117000") heap_80117000[0x6b000];

void System_Init_Heap_0_1_Half_80014BD8(void)
{
    System_init_80015AF4(0, 1, (void*)0x80182000, sizeof(heap_80182000) / 2); // passing heap_80182000 produces addiu instead of ori
    System_init_80015AF4(1, 1, (void*)0x80182000 + sizeof(heap_80182000) / 2 , sizeof(heap_80182000) / 2); // ditto
}

void System_Init_Heap_0_1_Full_80014C28()
{
    System_init_80015AF4(0, 0, (void*)0x80182000, sizeof(heap_80182000)); // passing heap_80182000 produces addiu instead of ori
    System_init_80015AF4(1, 0, 0, 0);
}

extern unsigned char* gResidentTop_800AB940;

extern const char aResidentTopX[];

void GV_Memory_Init_80014C70(void)
{
	System_init_clear_3_heaps_80015AB0();
	System_Init_Heap_0_1_Half_80014BD8();
	System_init_80015AF4(2, 0, (void*)0x80117000, sizeof(heap_80117000)); // passing heap_80117000 produces addiu instead of ori
	mts_printf_8008BBA0(aResidentTopX, gResidentTop_800AB940);
}

extern void GV_MessageClear_800164AC(void);
extern void GV_PadInputClear_800167C8(void);

void GV_Messge_And_Pad_Init_80014CC8(void)
{
	GV_MessageClear_800164AC();
	GV_PadInputClear_800167C8();
}

extern void GV_FreeCacheSystem_80015540(void);

void sub_80014cf0(void)
{
	GV_FreeCacheSystem_80015540();
	GV_Memory_Init_80014C70();
}

extern void GV_ResidentHeapReset_800163B0(void);
extern void GD_ClearFileHandlers_80015434(void);
extern void GV_InitCacheSystem_80015458(void);
extern void SetHangupCallBack_800892A8(void*);
extern void Callback_Hangup_80014B34(void);

struct Actor SECTION(".gGVActor_800acbf8") gGVActor_800acbf8;

void GV_StartDaemon_80014d18(void)
{
	GV_ActorList_Init_80014d98();
	GV_ResidentHeapReset_800163B0();
	GD_ClearFileHandlers_80015434();
	GV_InitCacheSystem_80015458();
	GV_Messge_And_Pad_Init_80014CC8();
	GV_ActorPushBack_800150a8(0, &gGVActor_800acbf8, 0);
	GV_ActorInit_8001514c(&gGVActor_800acbf8, GV_Act_80014b60, 0, "gvd.c"); // sdata
	GV_Clock_800AB920 = 0;
	gRenderedFramesCount_800AB330 = 0;
	SetHangupCallBack_800892A8(Callback_Hangup_80014B34);
}

