#ifndef _MAP_H_
#define _MAP_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "libhzd/libhzd.h"
#include "libdg/libdg.h"

typedef struct LitHeader
{
    int    n_lights;
    DG_LIT lights[0];
} LitHeader;

typedef struct MAP
{
    int            index;
    unsigned short name;
    unsigned short used;
    HZD_HDL       *hzd;
    LitHeader     *lit;
    int            zone;
} MAP;

#define MAX_HISTORY 8

typedef struct AreaHistory
{
    short history[MAX_HISTORY];
} AreaHistory;

MAP     *Map_FindByNum_80031504(int mapNameHash);
int      GM_AddMap_80031324(int mapName);
void     Map_KmdLoad_80030E74(int pLitName, MAP *pMap);
HZD_HDL *Map_HZD_Load_80030F38(int resource_name_hashed, int flagsIndex, int bitIndex, int default_48, int default_24);
MAP     *Map_GetNextFreeRecord_80030E30(int mapNameHashed);
MAP     *Map_FromId_800314C0(int id);
MAP     *Map_ScriptLoadMapBlocks_800312D0();
int      Map_ScriptReloadMaps_80031450(int a1);
void     GM_SetMap_80031244(int mapNum, int resourceNameHashed);
void     Map_light_80030C6C(int a1);
void     Map_80030FA4();
void     GM_ResetMapObjs_800310A0();
HZD_HDL *Map_Enum_Get_Hzd_80031580(HZD_HDL *pPrevious);
void     GM_DieMap_80030FD0();
int      GM_DelMap_800313C0(int mapName);
void     GM_FreeMapObjs_80031028();
MAP     *Map_FindByZoneId_80031624(int zone_id);
MAP     *GM_Command_mapdef_impl_800310D0(void);

#endif // _MAP_H_
