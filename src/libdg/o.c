#include "linker.h"
#include "Game/map.h"
#include "libdg.h"

extern MATRIX DG_LightMatrix_8009D384;
extern MATRIX DG_ZeroMatrix_8009D430;

// #define STATIC static
#define STATIC

STATIC int DG_MakeObjs_helper( DG_MDL *mdl )
{
    int          val;
    int          mask;
    unsigned int flags;

    flags = mdl->flags;
    val = 0;

    if ((flags & 0x300) != 0)
    {
        mask = 4 - (flags >> 12 & 3);
        val = mask * 0xfa;
        if ((flags & 0x100) == 0)
        {
            val = mask * -0xfa;
        }
    }

    return val;
}

DG_OBJS *DG_MakeObjs( DG_DEF *def, int flag, int chanl )
{
    DG_MDL *model = (DG_MDL *)&def[1];

    const int objs_size = sizeof(DG_OBJS) + (sizeof(DG_OBJ) * def->num_mesh_4);
    DG_OBJS  *objs_buf = (DG_OBJS *)GV_Malloc(objs_size);

    if (!objs_buf)
    {
        return 0;
    }
    else
    {
        int     numMesh;
        DG_OBJ *obj;

        GV_ZeroMemory(objs_buf, objs_size);
        objs_buf->world = DG_ZeroMatrix_8009D430;

        objs_buf->def = def;

        objs_buf->n_models = def->num_bones_0;

        objs_buf->flag = flag;
        objs_buf->chanl = chanl;
        objs_buf->light = &DG_LightMatrix_8009D384;

        obj = &objs_buf->objs[0];
        for (numMesh = def->num_mesh_4; numMesh > 0; numMesh--)
        {
            obj->model = model;
            if (model->extend < 0)
            {
                obj->extend = 0;
            }
            else
            {
                obj->extend = &objs_buf->objs[model->extend];
            }

            obj->raise = DG_MakeObjs_helper(model);
            obj->n_packs = model->n_faces;
            obj++;
            model++;
        }
        return objs_buf;
    }
}

void DG_FreeObjs( DG_OBJS *objs )
{
    int     n_models;
    DG_OBJ *obj;

    n_models = objs->n_models;
    obj = objs->objs;
    while (n_models > 0)
    {
        DG_FreeObjPacket(obj, 0);
        DG_FreeObjPacket(obj, 1);
        --n_models;
        ++obj;
    }
    DG_FreePreshade(objs);
    GV_Free(objs);
}

void DG_SetObjsRots( DG_OBJS *objs, SVECTOR *rot )
{
    objs->rots = rot;
}

void DG_SetObjsMovs( DG_OBJS *objs, SVECTOR *mov )
{
    objs->movs = mov;
}

