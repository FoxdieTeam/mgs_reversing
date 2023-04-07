#include "linker.h"
#include "control.h"
#include "mts/mts_new.h"
#include "libgcl/hash.h"
#include "libgv/libgv.h"
#include "map/map.h"
#include "libhzd/libhzd.h"

int SECTION(".sbss") GM_CurrentMap_800AB9B0;
int SECTION(".sbss") gControlCount_800AB9B4;

extern CONTROL *GM_WhereList_800B56D0[96];
extern CONTROL  gDefaultControl_800B5650;

int GM_ControlPushBack_800258B0(CONTROL *pControlToAdd)
{
    // sna_init must always be the first item
    if (pControlToAdd->field_30_scriptData == CHARA_SNAKE)
    {
        GM_WhereList_800B56D0[0] = pControlToAdd;
    }
    else
    {
        if (gControlCount_800AB9B4 > MAX_CONTROLS - 1)
        {
            return -1;
        }
        GM_WhereList_800B56D0[gControlCount_800AB9B4] = pControlToAdd;
        gControlCount_800AB9B4++;
    }

    return 0;
}

void GM_ControlRemove_80025904(CONTROL *pControl)
{
    int i = gControlCount_800AB9B4;
    int totalCount = gControlCount_800AB9B4;

    CONTROL **pControlIter = GM_WhereList_800B56D0;

    while (i > 0)
    {
        i--;

        if (*pControlIter == pControl)
        {
            goto found;
        }
        pControlIter++;
    }

    return;

found:

    if (pControlIter != GM_WhereList_800B56D0)
    {
        *pControlIter = GM_WhereList_800B56D0[--totalCount];
        gControlCount_800AB9B4 = totalCount;
    }
    else
    {
        GM_WhereList_800B56D0[0] = &gDefaultControl_800B5650;
    }
}

void GM_InitWhereSystem_8002597C(void)
{
    GM_WhereList_800B56D0[0] = &gDefaultControl_800B5650;
    gControlCount_800AB9B4 = 1;
}

int Res_Control_init_loader_8002599C(CONTROL *pControl, int scriptData, int scriptBinds)
{
    struct map_record *pMapRec;
    const int          mapId = scriptBinds ? scriptBinds : GM_CurrentMap_800AB9B0;
    GM_CurrentMap_800AB9B0 = mapId;

    GV_ZeroMemory_8001619C(pControl, sizeof(CONTROL));

    pMapRec = Map_FromId_800314C0(mapId);
    pControl->field_2C_map = pMapRec;
    if (!pMapRec)
    {
        mts_printf_8008BBA0("InitControl : no map %X\n", mapId);
        return -1;
    }

    pControl->field_30_scriptData = scriptData;
    if (scriptData)
    {
        HZD_SetEvent_80029AB4(&pControl->field_10_pStruct_hzd_unknown, scriptData);
        if (GM_ControlPushBack_800258B0(pControl) < 0)
        {
            return -1;
        }
    }

    pControl->field_32_height = 850;
    pControl->field_34_hzd_height = -32767;
    pControl->field_38 = 450;
    pControl->field_36 = 450;
    pControl->field_59 = 2;
    pControl->field_55_skip_flag = CTRL_SKIP_TRAP;
    pControl->field_78_levels[0] = -32000;
    pControl->field_78_levels[1] = 32000;

    return 0;
}
