#include "linker.h"
#include "actor.h"
#include "mts_new.h"

extern const char aLoadreq[];
extern const char aNotFoundStageS[];
extern const char aLoaderC[];
extern const char aLoadend[];

extern int GM_LoadComplete_800ABA38;
extern int GM_LoadRequest_800AB3D0;
extern int GM_PadVibration2_800ABA54;

struct Loader_Rec_2
{
	char field_0;
	char field_1;
};

struct Loader_Record
{
	int field_0;
	int field_4; // cnf count?
	struct Loader_Rec_2 *field_8_p2Alloc;
	int field_C; // str ptr?
	int field_10;
	int field_14; // last size?
	int field_18; // state ?
	int field_1C; // cnf ptr?
	int field_20;
	int field_24;
	int field_28;
	int field_2C;
	int field_30;
	int field_34;
};

struct Loader
{
	struct Actor base;
	struct Loader_Record *field_20_pFileName;
	int field_24_proc_cancel_flags;
	int field_28_bRunning;
	int field_2C_counter;
};

void DG_OffsetDispEnv_80017784(int offset);

int FS_LoadStageSync_800237C0(struct Loader_Record *pRec);

extern struct Loader_Record *FS_LoadStageRequest_800236E0(const char *pStageName);
extern void FS_LoadStageComplete_80023804(struct Loader_Record *pImpl);

void Loader_Act_8002E390(struct Loader *pLoader)
{
	pLoader->field_2C_counter++;

	if (pLoader->field_24_proc_cancel_flags != 2)
	{
		if (pLoader->field_24_proc_cancel_flags == 3)
		{
			DG_OffsetDispEnv_80017784(pLoader->field_2C_counter & 2);
			GM_PadVibration2_800ABA54 = 100;
		}
	}

	if (pLoader->field_28_bRunning)
	{
		if (!FS_LoadStageSync_800237C0(pLoader->field_20_pFileName))
		{
			pLoader->field_28_bRunning = 0;
		}
	}
	else
	{
		GV_DestroyActor_800151C8(&pLoader->base);
	}
}

void Loader_Kill_8002E41C(struct Loader *pLoader)
{
	mts_printf_8008BBA0(aLoadend);
	FS_LoadStageComplete_80023804(pLoader->field_20_pFileName);
	GM_LoadComplete_800ABA38 = -1;
}

struct Loader *Loader_Init_8002E460(const char *pStageName)
{
	struct Loader *pLoader;
	struct Loader_Record *pLoaderRec;

	pLoader = (struct Loader *)GV_NewActor_800150E4(2, sizeof(struct Loader));
	mts_printf_8008BBA0(aLoadreq);
	pLoaderRec = FS_LoadStageRequest_800236E0(pStageName);

	pLoader->field_20_pFileName = pLoaderRec;
	if (pLoaderRec == 0)
	{
		mts_printf_8008BBA0(aNotFoundStageS, pStageName);
	}

	GV_SetNamedActor_8001514C(&pLoader->base, (TActorFunction)Loader_Act_8002E390, (TActorFunction)Loader_Kill_8002E41C, aLoaderC);

	pLoader->field_28_bRunning = 1;
	pLoader->field_24_proc_cancel_flags = (GM_LoadRequest_800AB3D0 & 0xf);
	GM_LoadComplete_800ABA38 = 0;
	return pLoader;
}
