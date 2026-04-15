#include "pipe.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/vibrate.h"       // for NewPadVibration
#include "bullet/blast.h"       // for NewBlast

extern BLAST_DATA blast_data_8009F4B8[8]; // in bullet/blast.c

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL  GV_ACTOR_AFTER

#define MODEL_FLAG  ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

typedef struct _Work
{
    GV_ACT         actor;
    OBJECT_NO_ROTS object;
    MATRIX         light[2];
    TARGET        *target;
    SVECTOR        pos;
    u_short        models[2];
    int            where;
    int            counter;
    int            counter2;
} Work;

/*---------------------------------------------------------------------------*/

unsigned char pipe_vibration1_800C3360[] = {0x7F, 0x02, 0x00, 0x00};
unsigned char pipe_vibration2_800C3364[] = {0xAF, 0x04, 0x41, 0x04, 0x00, 0x00, 0x00, 0x00};

static int GetRaise(DG_MDL *mdl)
{
    unsigned int flags;
    int          raise;

    flags = mdl->flags;
    raise = 0;
    if (flags & 0x300)
    {
        raise = (4 - ((flags >> 12) & 3)) * 250;
        if (!(flags & 0x100))
        {
            raise = -raise;
        }
    }
    return raise;
}

static int SwitchModel(Work *work)
{
    DG_MDL  *mdl, *mdl2;
    DG_OBJ  *obj;
    DG_OBJS *objs;
    int      count;

    objs = work->object.objs;
    count = objs->n_models;
    obj = objs->objs;
    for (; count > 0; count--, obj++)
    {
        DG_FreeObjPacket(obj, 0);
        DG_FreeObjPacket(obj, 1);
    }

    objs->def = GV_GetCache(GV_CacheID(work->models[1], 'k'));

    count = objs->def->n_models;
    mdl = objs->def->model;
    mdl2 = &objs->def->model[0];
    obj = &objs->objs[0];
    for (; count > 0; obj++, mdl2++, mdl++, count--)
    {
        obj->model = mdl;

        if (mdl2->extend < 0)
        {
            obj->extend = NULL;
        }
        else
        {
            obj->extend = &objs->objs[mdl2->extend];
        }

        obj->raise = GetRaise(mdl);
        obj->n_packs = mdl2->n_faces;
    }

    return 0;
}

static void Destroy(Work *work)
{
    MATRIX mat;

    if (work->target->damaged & TARGET_POWER)
    {
        mat = DG_ZeroMatrix;

        mat.t[0] = work->pos.vx;
        mat.t[1] = work->pos.vy;
        mat.t[2] = work->pos.vz;

        NewBlast(&mat, &blast_data_8009F4B8[1]);
        NewPadVibration(pipe_vibration1_800C3360, 1);
        NewPadVibration(pipe_vibration2_800C3364, 2);

        GM_FreeTarget(work->target);
        work->target = NULL;
        work->counter2 = 1;
        SwitchModel(work);
        work->counter = 0;
    }
}

static void Act(Work *work)
{
    MATRIX mat;

    GM_CurrentMap = work->where;
    if (work->counter < 4)
    {
        work->counter++;
        DG_GetLightMatrix2(&work->pos, work->light);
    }

    if (work->counter2 == 0)
    {
        Destroy(work);
    }
    else if (work->counter2 < 16)
    {
        work->counter2++;
        if (work->counter2 == 8 || work->counter2 == 16)
        {
            mat = DG_ZeroMatrix;

            mat.t[0] = work->pos.vx;
            mat.t[1] = work->pos.vy;
            mat.t[2] = work->pos.vz;

            mat.t[0] += GV_RandS(2048);
            mat.t[1] += GV_RandS(2048);
            mat.t[2] += GV_RandS(2048);

            NewBlast(&mat, &blast_data_8009F4B8[1]);
            NewPadVibration(pipe_vibration1_800C3360, 1);
            NewPadVibration(pipe_vibration2_800C3364, 2);
        }
    }
}

static void Die(Work *work)
{
    GM_FreeObject((OBJECT *)&work->object);

    if (work->target != NULL)
    {
        GM_FreeTarget(work->target);
    }
}

static int InitTarget(Work *work)
{
    SVECTOR size, pos;
    TARGET *target;

    size.vx = 1500;
    size.vy = 750;
    size.vz = 4000;

    GCL_StrToSV(GCL_GetOption('t'), &pos);
    work->pos = pos;

    work->target = target = GM_AllocTarget();
    if (target == NULL)
    {
        return -1;
    }

    GM_SetTarget(target, ( TARGET_POWER | TARGET_SEEK ), PLAYER_SIDE, &size);
    GM_Target_8002DCCC(target, 1, 0, 1, -1, &DG_ZeroVector);
    GM_MoveTarget(target, &work->pos);

    work->counter = 0;
    return 0;
}

static void GetInts(Work *work)
{
    int    i;
    short *out;
    char  *res;

    if (!GCL_GetOption('m'))
    {
        return;
    }

    i = 0;
    out = work->models;
    while ((res = GCL_GetParamResult()))
    {
        if (i == 2)
        {
            break;
        }

        *out++ = GCL_StrToInt(res);
        i++;
    }
}

static int InitObject(Work *work)
{
    SVECTOR         dir, pos;
    MATRIX          world;
    OBJECT_NO_ROTS *object;
    int             i;

    GetInts(work);

    object = &work->object;
    GM_InitObjectNoRots(object, work->models[0], MODEL_FLAG, 0);
    GM_ConfigObjectLight((OBJECT *)object, work->light);

    GCL_StrToSV(GCL_GetOption('d'), &dir);
    GCL_StrToSV(GCL_GetOption('p'), &pos);
    DG_SetPos2(&pos, &dir);

    ReadRotMatrix(&world);
    work->object.objs->world = world;

    object->map_name = GM_CurrentMap;
    for (i = 0; i < object->objs->n_models; i++)
    {
        object->objs->objs[i].raise = 240;
    }

    return 0;
}

static int GetResources(Work *work, int name, int where)
{
    GM_CurrentMap = where;

    if (InitTarget(work) < 0)
    {
        return -1;
    }

    if (InitObject(work) < 0)
    {
        return -1;
    }

    work->counter2 = 0;
    work->where = GM_CurrentMap;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewPipe(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, Act, Die, "pipe.c");
    if (GetResources(work, name, where) < 0)
    {
        GV_DestroyActor(&work->actor);
        return NULL;
    }

    return (void *)work;
}
