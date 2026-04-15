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

#define EXEC_LEVEL GV_ACTOR_AFTER

typedef struct _Work
{
    GV_ACT         actor;
    OBJECT_NO_ROTS object;
    MATRIX         light[2];
    TARGET        *target;
    SVECTOR        svec;
    unsigned short model_ids[2];
    int            where;
    int            counter;
    int            counter2;
} Work;

/*---------------------------------------------------------------------------*/

unsigned char pipe_vibration1_800C3360[] = {0x7F, 0x02, 0x00, 0x00};
unsigned char pipe_vibration2_800C3364[] = {0xAF, 0x04, 0x41, 0x04, 0x00, 0x00, 0x00, 0x00};

// Duplicate of Snake03c2GetRaise_800CDB78
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

// Modified Snake03c2_800CDBC8
static int Pipe_800CE0A8(Work *work)
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

    objs->def = GV_GetCache(GV_CacheID(work->model_ids[1], 'k'));

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

static void Pipe_800CE1B8(Work *work)
{
    MATRIX mat;

    if (work->target->damaged & TARGET_POWER)
    {
        mat = DG_ZeroMatrix;

        mat.t[0] = work->svec.vx;
        mat.t[1] = work->svec.vy;
        mat.t[2] = work->svec.vz;

        NewBlast(&mat, &blast_data_8009F4B8[1]);
        NewPadVibration(pipe_vibration1_800C3360, 1);
        NewPadVibration(pipe_vibration2_800C3364, 2);

        GM_FreeTarget(work->target);
        work->target = NULL;
        work->counter2 = 1;
        Pipe_800CE0A8(work);
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
        DG_GetLightMatrix2(&work->svec, work->light);
    }

    if (work->counter2 == 0)
    {
        Pipe_800CE1B8(work);
    }
    else if (work->counter2 < 16)
    {
        work->counter2++;
        if (work->counter2 == 8 || work->counter2 == 16)
        {
            mat = DG_ZeroMatrix;

            mat.t[0] = work->svec.vx;
            mat.t[1] = work->svec.vy;
            mat.t[2] = work->svec.vz;

            mat.t[0] += GV_RandS(0x800);
            mat.t[1] += GV_RandS(0x800);
            mat.t[2] += GV_RandS(0x800);

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
    SVECTOR svec1, svec2;
    TARGET *target;

    svec1.vx = 1500;
    svec1.vy = 750;
    svec1.vz = 4000;

    GCL_StrToSV(GCL_GetOption('t'), &svec2);
    work->svec = svec2;

    work->target = target = GM_AllocTarget();
    if (target == NULL)
    {
        return -1;
    }

    GM_SetTarget(target, 0x14, 1, &svec1);
    GM_Target_8002DCCC(target, 1, 0, 1, -1, &DG_ZeroVector);
    GM_MoveTarget(target, &work->svec);

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
    out = work->model_ids;
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
    SVECTOR         svec1, svec2;
    MATRIX          world;
    OBJECT_NO_ROTS *object;
    int             i;

    GetInts(work);

    object = &work->object;
    GM_InitObjectNoRots(object, work->model_ids[0], 0x6D, 0);
    GM_ConfigObjectLight((OBJECT *)object, work->light);

    GCL_StrToSV(GCL_GetOption('d'), &svec1);
    GCL_StrToSV(GCL_GetOption('p'), &svec2);
    DG_SetPos2(&svec2, &svec1);

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
