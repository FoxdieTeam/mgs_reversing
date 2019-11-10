#include <libsn.h>
#include "actor.h"

struct Actor;

extern void GV_Act_80014b60(struct Actor*);
extern const char aGvdC[];

extern void sub_800163b0(void);
extern void sub_80015434(void);
extern void sub_80015434(void);
extern void sub_80015458(void);
extern void sub_80014cc8(void);
extern void sub_800892a8(void*);
extern void sub_80014b34(void);

struct Actor SECTION(".gGVActor_800acbf8") gGVActor_800acbf8;

/*
void SECTION(".0x80014d18") GV_StartDaemon_80014d18(void)
{
	GV_ActorList_Init_80014d98();
	sub_800163b0();
	sub_80015434();
	sub_80015458();
	sub_80014cc8();
	GV_ActorPushBack_800150a8(0, &gGVActor_800acbf8, 0);
	GV_ActorInit_8001514c(&gGVActor_800acbf8, GV_Act_80014b60, 0, aGvdC);
	dword_800AB928 = 0;
	dword_800AB9B0 = 0;
	sub_800892a8(sub_80014b34);
}
*/
