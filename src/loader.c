#include "linker.h"
#include "actor.h"


extern const char aLoadreq[];
extern const char aNotFoundStageS[];
extern const char aLoaderC[];
extern const char aLoadend[];

// TODO: Copied from PC rev, might be wrong
struct Actor_Loader_Impl
{
    int field_0;
    int field_4_data_cnf_line_count;
    int field_8_unknown_state;
    const char* field_C_c_str_ptr_field_2C;
    int field_10;
    int field_14_last_loaded_file_size;
    int field_18_state;
    char* field_1C_c_str_data_cnf_sys_allocd;
    const char* field_20_c_str;
    short int field_24_field_2C_char_state_resident_type;
    short int field_26_padding_q;
    void* field_28_sys2_alloc_file_buffer;
    char field_2C_c_str[64];
    char* field_6C_pointer_file_second_dword;
    int field_70_count_file_first_dword;
};

extern struct Actor_Loader_Impl* sub_800236E0(const char* pStageName);
extern void Loader_End_80023804(struct Actor_Loader_Impl* pImpl);

struct Loader
{
	struct Actor base;
	// TODO: Check field name/offsets
	struct Actor_Loader_Impl* field_20;
	int field_28;
	int field_2C;
	int field_30;
};

extern void Loader_Act_8002e390(struct Loader* loader);

extern void mg_printf(const char*, ...);

extern int gLoaderState_800ABA38;
extern int dword_800AB3D0;


void Loader_Kill_8002e41c(struct Loader* pLoader)
{
	mg_printf(aLoadend);
	Loader_End_80023804(pLoader->field_20);
	gLoaderState_800ABA38 = 0xffffffff;
}

struct Loader* Loader_Init_8002e460(const char* pStageName)
{
	struct Loader* pLoader;
	struct Actor_Loader_Impl* pUnknown;


	pLoader = (struct Loader*)GV_ActorAlloc_800150e4(2, sizeof(struct Loader));
	mg_printf(aLoadreq);
	pUnknown = sub_800236E0(pStageName);

	pLoader->field_20 = pUnknown;
	if (pUnknown == 0)
	{
		mg_printf(aNotFoundStageS, pStageName);
	}
	
	GV_ActorInit_8001514c(&pLoader->base, (TActorFunction)Loader_Act_8002e390, (TActorFunction)Loader_Kill_8002e41c, aLoaderC);

	pLoader->field_2C = 1;
	pLoader->field_28 = (dword_800AB3D0 & 0xf);
	gLoaderState_800ABA38 = 0;	
	return pLoader;
}

