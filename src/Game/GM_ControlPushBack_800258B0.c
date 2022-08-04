#include "linker.h"
#include "Game/GM_Control.h"
#include "mts/mts_new.h"
#include "libgcl/hash.h"

int SECTION(".sbss") GM_CurrentMap_800AB9B0;
int SECTION(".sbss") gControlCount_800AB9B4;

GM_Control *SECTION(".GM_WhereList_800B56D0") GM_WhereList_800B56D0[96];
GM_Control SECTION(".gDefaultControl_800B5650") gDefaultControl_800B5650;

int GM_ControlPushBack_800258B0(GM_Control *pControlToAdd)
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

void GM_ControlRemove_80025904(GM_Control *pControl)
{
    int i = gControlCount_800AB9B4;
    int totalCount = gControlCount_800AB9B4;

    GM_Control **pControlIter = GM_WhereList_800B56D0;

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

extern const char aInitcontrolNoM[];

void HZD_SetEvent_80029AB4(void *param_1, int param_2);
void GV_ZeroMemory_8001619C(void *, int);
struct map_record *Map_FromId_800314C0(int);

int Res_Control_init_loader_8002599C(GM_Control *pControl, int scriptData, int scriptBinds)
{
    struct map_record *pMapRec;
    const int mapId = scriptBinds ? scriptBinds : GM_CurrentMap_800AB9B0;
    GM_CurrentMap_800AB9B0 = mapId;

    GV_ZeroMemory_8001619C(pControl, sizeof(GM_Control));

    pMapRec = Map_FromId_800314C0(mapId);
    pControl->field_2C_map = pMapRec;
    if (!pMapRec)
    {
        mts_printf_8008BBA0(aInitcontrolNoM, mapId);
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
    pControl->field_34 = -32767;
    pControl->field_38 = 450;
    pControl->field_36 = 450;
    pControl->field_59 = 2;
    pControl->field_55_flags = CONTROL_FLAG_UNK2;
    pControl->field_78 = -32000;
    pControl->field_7A = 32000;

    return 0;
}
