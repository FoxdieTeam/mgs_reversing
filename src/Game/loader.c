#include "linker.h"
#include "actor.h"
#include "mts_new.h"

extern const char aLoadreq[];
extern const char aNotFoundStageS[];
extern const char aLoaderC[];
extern const char aLoadend[];

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

extern struct Loader_Record *Loader_load_file_by_name_800236E0(const char *pStageName);
extern void Loader_End_80023804(struct Loader_Record *pImpl);

struct Loader
{
	struct Actor base;
	struct Loader_Record *field_20_pFileName;
	int field_24_proc_cancel_flags;
	int field_28_bRunning;
	int field_2C_counter;
};

extern void Loader_Act_8002e390(struct Loader *loader);

extern int gLoaderState_800ABA38;
extern int gFlags_800AB3D0;

void Loader_Kill_8002e41c(struct Loader *pLoader)
{
	mts_printf_8008BBA0(aLoadend);
	Loader_End_80023804(pLoader->field_20_pFileName);
	gLoaderState_800ABA38 = 0xffffffff;
}

struct Loader *Loader_Init_8002e460(const char *pStageName)
{
	struct Loader *pLoader;
	struct Loader_Record *pLoaderRec;

	pLoader = (struct Loader *)GV_ActorAlloc_800150e4(2, sizeof(struct Loader));
	mts_printf_8008BBA0(aLoadreq);
	pLoaderRec = Loader_load_file_by_name_800236E0(pStageName);

	pLoader->field_20_pFileName = pLoaderRec;
	if (pLoaderRec == 0)
	{
		mts_printf_8008BBA0(aNotFoundStageS, pStageName);
	}

	GV_ActorInit_8001514c(&pLoader->base, (TActorFunction)Loader_Act_8002e390, (TActorFunction)Loader_Kill_8002e41c, aLoaderC);

	pLoader->field_28_bRunning = 1;
	pLoader->field_24_proc_cancel_flags = (gFlags_800AB3D0 & 0xf);
	gLoaderState_800ABA38 = 0;
	return pLoader;
}
