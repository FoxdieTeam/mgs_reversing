#include "linker.h"
#include "GM_Control.h"


int SECTION(".sbss") dword_800AB9B0;
int SECTION(".sbss") gControlCount_800AB9B4;

Res_Control *SECTION(".gControlArray_800B56D0") gControlArray_800B56D0[96];
Res_Control SECTION(".gDefaultControl_800B5650") gDefaultControl_800B5650;

int GM_ControlPushBack_800258B0(Res_Control *pControlToAdd)
{
    // sna_init must always be the first item
    if (pControlToAdd->field_30_scriptData == 0x21CA)
    {
        gControlArray_800B56D0[0] = pControlToAdd;
    }
    else
    {
        if (gControlCount_800AB9B4 > MAX_CONTROLS - 1)
        {
            return -1;
        }
        gControlArray_800B56D0[gControlCount_800AB9B4] = pControlToAdd;
        gControlCount_800AB9B4++;
    }

    return 0;
}

void GM_ControlRemove_80025904(Res_Control *pControl)
{
    int i = gControlCount_800AB9B4;
    int totalCount = gControlCount_800AB9B4;

    Res_Control **pControlIter = gControlArray_800B56D0;

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

    if (pControlIter != gControlArray_800B56D0)
    {
        *pControlIter = gControlArray_800B56D0[--totalCount];
        gControlCount_800AB9B4 = totalCount;
    }
    else
    {
        gControlArray_800B56D0[0] = &gDefaultControl_800B5650;
    }
}

void GM_ControlSetDefault_8002597C(void)
{
    gControlArray_800B56D0[0] = &gDefaultControl_800B5650;
    gControlCount_800AB9B4 = 1;
}

extern const char aInitcontrolNoM[];

void GM_control_loader_helper_80029AB4(void *param_1, int param_2);
void GV_ZeroMemory_8001619c(void *, int);
extern void mg_printf_8008BBA0(const char *, ...);
struct map_record *Map_FromId_800314C0(int);

int Res_Control_init_loader_44EB9E(Res_Control *pControl, int scriptData, int scriptBinds)
{
    struct map_record *pMapRec;
    const int mapId = scriptBinds ? scriptBinds : dword_800AB9B0;
    dword_800AB9B0 = mapId;

    GV_ZeroMemory_8001619c(pControl, sizeof(Res_Control));

    pMapRec = Map_FromId_800314C0(mapId);
    pControl->field_2C_map = pMapRec;
    if (!pMapRec)
    {
        mg_printf_8008BBA0(aInitcontrolNoM, mapId);
        return -1;
    }

    pControl->field_30_scriptData = scriptData;
    if (scriptData)
    {
        GM_control_loader_helper_80029AB4(&pControl->field_10_pStruct_hzd_unknown, scriptData);
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
    pControl->field_55_flags = 2;
    pControl->field_78 = -32000;
    pControl->field_7A = 32000;

    return 0;
}
