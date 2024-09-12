#include "common.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/object.h"
#include "Game/vibrate.h"
#include "Bullet/blast.h"

typedef struct PipeWork
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
} PipeWork;

unsigned char pipe_vibration1_800C3360[] = {0x7F, 0x02, 0x00, 0x00};
unsigned char pipe_vibration2_800C3364[] = {0xAF, 0x04, 0x41, 0x04, 0x00, 0x00, 0x00, 0x00};

extern int        GM_CurrentMap_800AB9B0;
extern SVECTOR    DG_ZeroVector;
extern MATRIX     DG_ZeroMatrix;
extern Blast_Data blast_data_8009F4B8[8];

// Duplicate of Snake03c2GetRaise_800CDB78
int PipeGetRaise_800CE058(DG_MDL *mdl)
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
int Pipe_800CE0A8(PipeWork *work)
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

    count = objs->def->num_mesh_4;
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

        obj->raise = PipeGetRaise_800CE058(mdl);
        obj->n_packs = mdl2->n_faces;
    }

    return 0;
}

void Pipe_800CE1B8(PipeWork *work)
{
    MATRIX mat;

    if (work->target->damaged & TARGET_POWER)
    {
        mat = DG_ZeroMatrix;

        mat.t[0] = work->svec.vx;
        mat.t[1] = work->svec.vy;
        mat.t[2] = work->svec.vz;

        NewBlast_8006DFDC(&mat, &blast_data_8009F4B8[1]);
        NewPadVibration_8005D58C(pipe_vibration1_800C3360, 1);
        NewPadVibration_8005D58C(pipe_vibration2_800C3364, 2);

        GM_FreeTarget(work->target);
        work->target = NULL;
        work->counter2 = 1;
        Pipe_800CE0A8(work);
        work->counter = 0;
    }
}

void PipeAct_800CE2A4(PipeWork *work)
{
    MATRIX mat;

    GM_CurrentMap_800AB9B0 = work->where;
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

            NewBlast_8006DFDC(&mat, &blast_data_8009F4B8[1]);
            NewPadVibration_8005D58C(pipe_vibration1_800C3360, 1);
            NewPadVibration_8005D58C(pipe_vibration2_800C3364, 2);
        }
    }
}

void PipeDie_800CE404(PipeWork *work)
{
    GM_FreeObject((OBJECT *)&work->object);

    if (work->target != NULL)
    {
        GM_FreeTarget(work->target);
    }
}

int PipeInitTarget_800CE444(PipeWork *work)
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

void PipeGetInts_800CE52C(PipeWork *work)
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

int PipeInitObject_800CE5A4(PipeWork *work)
{
    SVECTOR         svec1, svec2;
    MATRIX          world;
    OBJECT_NO_ROTS *object;
    int             i;

    PipeGetInts_800CE52C(work);

    object = &work->object;
    GM_InitObjectNoRots(object, work->model_ids[0], 0x6D, 0);
    GM_ConfigObjectLight((OBJECT *)object, work->light);

    GCL_StrToSV(GCL_GetOption('d'), &svec1);
    GCL_StrToSV(GCL_GetOption('p'), &svec2);
    DG_SetPos2(&svec2, &svec1);

    ReadRotMatrix(&world);
    work->object.objs->world = world;

    object->map_name = GM_CurrentMap_800AB9B0;
    for (i = 0; i < object->objs->n_models; i++)
    {
        object->objs->objs[i].raise = 240;
    }

    return 0;
}

int PipeGetResources_800CE6DC(PipeWork *work, int name, int where)
{
    GM_CurrentMap_800AB9B0 = where;

    if (PipeInitTarget_800CE444(work) < 0)
    {
        return -1;
    }

    if (PipeInitObject_800CE5A4(work) < 0)
    {
        return -1;
    }

    work->counter2 = 0;
    work->where = GM_CurrentMap_800AB9B0;
    return 0;
}

GV_ACT *NewPipe_800CE73C(int name, int where, int argc, char **argv)
{
    PipeWork *work;

    work = (PipeWork *)GV_NewActor(6, sizeof(PipeWork));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, (TActorFunction)PipeAct_800CE2A4,
                     (TActorFunction)PipeDie_800CE404, "pipe.c");
    if (PipeGetResources_800CE6DC(work, name, where) < 0)
    {
        GV_DestroyActor(&work->actor);
        return NULL;
    }

    return &work->actor;
}
