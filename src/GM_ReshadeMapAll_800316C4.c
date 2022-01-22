#include "linker.h"
#include "libdg.h"
#include "dgd.h"
#include "map\map.h"

DG_OBJS *SECTION(".StageObjs_800B7890") StageObjs_800B7890[32];

// re-declare to force GP usage
extern int N_StageObjs_800ABAA4;
int SECTION(".sbss") N_StageObjs_800ABAA4;

extern const char aReshadeNullMap[];

struct LitHeader
{
  int field_0_num_lights;
};

struct map_record* Map_FromId_800314C0(int id);
void DG_MakePreshade_80031F04(DG_OBJS *pPrim, short *pData, int dataCount);
extern void mts_printf_8008BBA0(const char*, ...);

void GM_ReshadeObjs_80031660(DG_OBJS *pObj)
{
	struct map_record *map;
	struct LitHeader *field_C_l_file;

	map = Map_FromId_800314C0(pObj->group_id);
	if (!map)
	{
		mts_printf_8008BBA0(aReshadeNullMap);
	}
	field_C_l_file = map->field_C_l_file;
	if (field_C_l_file)
	{
		DG_MakePreshade_80031F04(pObj, (short *)&field_C_l_file[1], field_C_l_file->field_0_num_lights);
	}
}

// TODO: OG name is GM_ReshadeMapAll
void Map_ReshadeAll_800316C4() // from memleak
{
	DG_OBJS **obj;
	int i;

	obj = StageObjs_800B7890;
	for (i = N_StageObjs_800ABAA4; i > 0; --i)
	{
		GM_ReshadeObjs_80031660(*obj);
		obj++;
	}
}
