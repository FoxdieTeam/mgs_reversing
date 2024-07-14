#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/map.h"

extern int    GV_PauseLevel_800AB928;
extern int    GM_CurrentMap_800AB9B0;
extern MATRIX DG_ZeroMatrix_8009D430;

DG_OBJS *s00a_unknown3_800DC724(int model, LitHeader *lit, int flag)
{
    DG_DEF  *def;
    DG_OBJS *objs;

    def = GV_GetCache_8001538C(GV_CacheID_800152DC(model, 'k'));
    objs = DG_MakeObjs_80031760(def, flag, 0);
    DG_PutObjs_8001BDB8(objs);

    if (lit)
    {
        DG_MakePreshade_80031F04(objs, lit->lights, lit->n_lights);
    }
    else
    {
        DG_MakePreshade_80031F04(objs, NULL, 0);
    }

    DG_QueueObjs_80018178(objs);
    DG_GroupObjs(objs, GM_CurrentMap_800AB9B0);

    return objs;
}

DG_OBJS *s00a_unknown3_800DC7BC(int model, LitHeader *lit)
{
    return s00a_unknown3_800DC724(model, lit, 0x57);
}

DG_OBJS *s00a_unknown3_800DC7DC(int model, LitHeader *lit)
{
    DG_SetPos_8001BC44(&DG_ZeroMatrix_8009D430);
    return s00a_unknown3_800DC7BC(model, lit);
}

void Takabe_FreeObjs_800DC820(DG_OBJS *objs)
{
    DG_DequeueObjs_800181E4(objs);
    DG_FreePreshade_80032110(objs);
    DG_FreeObjs_800318D0(objs);
}

void Takabe_RefreshObjectPacks_800DC854(DG_OBJS *objs);

void Takabe_ReshadeModel_800DC854(DG_OBJS *objs, LitHeader *lit)
{
    DG_MakePreshade_80031F04(objs, lit->lights, lit->n_lights);
    Takabe_RefreshObjectPacks_800DC854(objs);
}

void Takabe_RefreshObjectPacks_800DC854(DG_OBJS *objs)
{
    DG_OBJ *obj;
    int     n_models;

    n_models = objs->n_models;
    obj = objs->objs;
    while (n_models > 0)
    {
        if (obj->packs[0])
        {
            DG_WriteObjPacketRGB_8001A9B8(obj, 0);
        }
        if (obj->packs[1])
        {
            DG_WriteObjPacketRGB_8001A9B8(obj, 1);
        }
        obj++;
        n_models--;
    }
}

void s00a_unknown3_800DC908()
{
}

int s00a_unknown3_800DC910()
{
    return 0;
}

void s00a_unknown3_800DC918()
{
}

int Takabe_MakePreshadeObjectDupl_800DC920()
{
    return 0;
}
