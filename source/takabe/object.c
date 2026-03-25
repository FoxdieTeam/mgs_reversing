#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

void Takabe_RefreshObjectPacks(DG_OBJS *objs);

static DG_OBJS *MakePreshade(int model, LIT *lit, int flag)
{
    DG_DEF  *def;
    DG_OBJS *objs;

    def = GV_GetCache(GV_CacheID(model, 'k'));
    objs = DG_MakeObjs(def, flag, 0);
    DG_PutObjs(objs);

    if (lit)
    {
        DG_MakePreshade(objs, lit->lights, lit->n_lights);
    }
    else
    {
        DG_MakePreshade(objs, NULL, 0);
    }

    DG_QueueObjs(objs);
    DG_GroupObjs(objs, GM_CurrentMap);

    return objs;
}

DG_OBJS *Takabe_MakePreshade(int model, LIT *lit)
{
    return MakePreshade(model, lit, ( DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS | DG_FLAG_BOUND | DG_FLAG_ONEPIECE ));
}

DG_OBJS *Takabe_MakeElevatorPreshade(int model, LIT *lit)
{
    DG_SetPos(&DG_ZeroMatrix);
    return Takabe_MakePreshade(model, lit);
}

void Takabe_FreeObjs(DG_OBJS *objs)
{
    DG_DequeueObjs(objs);
    DG_FreePreshade(objs);
    DG_FreeObjs(objs);
}

void Takabe_ReshadeModel(DG_OBJS *objs, LIT *lit)
{
    DG_MakePreshade(objs, lit->lights, lit->n_lights);
    Takabe_RefreshObjectPacks(objs);
}

void Takabe_RefreshObjectPacks(DG_OBJS *objs)
{
    DG_OBJ *obj;
    int     n_models;

    n_models = objs->n_models;
    obj = objs->objs;
    while (n_models > 0)
    {
        if (obj->packs[0])
        {
            DG_WriteObjPacketRGB(obj, 0);
        }
        if (obj->packs[1])
        {
            DG_WriteObjPacketRGB(obj, 1);
        }
        obj++;
        n_models--;
    }
}

void s00a_unknown3_800DC908()
{
    /* do nothing */
}

int s00a_unknown3_800DC910()
{
    return 0;
}

void s00a_unknown3_800DC918()
{
    /* do nothing */
}

int Takabe_MakePreshadeObjectDupl_800DC920()
{
    return 0;
}
