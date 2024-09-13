#include "shakemdl.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "Takabe/thing.h"
#include "strcode.h"

typedef struct _ShakemdlWork
{
    GV_ACT  actor;
    int     name;
    int     f24;
    int     f28;
    int     f2C;
    int     f30;
    int     f34;
    DG_KMD *kmd;
    short   f3C[16];
    short   f5C[16];
    short  *vertices;
} ShakemdlWork;

int s16b_800C5728(ShakemdlWork *, short *);
int s16b_800C57A4(ShakemdlWork *work);
int s16b_800C5664(ShakemdlWork *work);

#define EXEC_LEVEL 5

void ShakemdlAct_800C5288(ShakemdlWork *work)
{
    GV_MSG *msg;
    int     count;
    short  *var_s4;
    int     temp_v0;
    short  *var_s0;
    short  *var_s1;
    int     i;

    count = GV_ReceiveMessage(work->name, &msg);

    for (; count > 0; count--, msg++)
    {
        switch (msg->message[0])
        {
        case HASH_KILL:
            GV_DestroyActor(&work->actor);
            return;

        case 0xD368:
            work->f30 = msg->message[1];
            work->f34 = msg->message[2];
            work->f24 = 1;
            break;

        case 0x9873:
            work->f24 = 0;
            break;
        }
    }

    var_s4 = (short *)0x1F800000;

    if (work->f24 != 0)
    {
        work->f28 = GV_NearSpeed(work->f28, work->f30, work->f34);
        temp_v0 = work->f28;

        var_s0 = work->f3C;
        var_s1 = work->f5C;

        for (i = 16; i > 0; i--)
        {
            *var_s4++ = (rsin(*var_s0) * temp_v0) >> 12;
            *var_s0++ += *var_s1++;
        }

        s16b_800C5728(work, (short *)0x1F800000);

        if ((work->f28 == 0) && (work->f30 == 0))
        {
            work->f24 = 0;
        }
    }
}

void ShakemdlDie_800C5418(ShakemdlWork *work)
{
    s16b_800C57A4(work);

    if (work->vertices)
    {
        GV_Free(work->vertices);
    }
}

int ShakemdlGetResources_800C5454(ShakemdlWork *work, int name)
{
    short *var_s1;
    short *var_s2;
    int    i;

    work->kmd = GV_GetCache(GV_CacheID(name, 'k'));

    if (s16b_800C5664(work))
    {
        return -1;
    }

    var_s2 = work->f3C;
    var_s1 = work->f5C;

    for (i = 16; i > 0; i--)
    {
        *var_s2++ = GV_RandU(0x1000U);
        *var_s1++ = GV_RandU(0x40U) + 0x10;
    }

    return 0;
}

GV_ACT *NewShakemdl_800C54E8(int name, int where, int argc, char **argv)
{
    ShakemdlWork *work;
    int           model;
    int           work_2;

    work = (ShakemdlWork *)GV_NewActor(EXEC_LEVEL, sizeof(ShakemdlWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)ShakemdlAct_800C5288, (GV_ACTFUNC)ShakemdlDie_800C5418, "shakemdl.c");

        model = THING_Gcl_GetInt('m');
        work->f2C = THING_Gcl_GetInt('a');

        if (ShakemdlGetResources_800C5454(work, model) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->name = name;
        work->f24 = THING_Gcl_GetIntDefault('f', 1);
        work_2 = THING_Gcl_GetIntDefault('s', 50);
        work->f28 = work_2;
        work->f30 = work_2;
    }

    return &work->actor;
}

GV_ACT *NewShakemdl_800c55b0(int arg0, int arg1, int arg2)
{
    ShakemdlWork *work;

    work = (ShakemdlWork *)GV_NewActor(EXEC_LEVEL, sizeof(ShakemdlWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)ShakemdlAct_800C5288, (GV_ACTFUNC)ShakemdlDie_800C5418, "shakemdl.c");

        work->f2C = arg1;

        if (ShakemdlGetResources_800C5454(work, arg0) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->name = 0x7743;
        work->f24 = 1;
        work->f28 = arg2;
        work->f30 = arg2;
    }

    return &work->actor;
}

int s16b_800C5664(ShakemdlWork *work)
{
    DG_KMD  *kmd;
    DG_MDL  *object;
    int      nvertices;
    int      nobjects;
    short   *vertices;
    SVECTOR *src;

    kmd = work->kmd;
    object = kmd->objects;
    nvertices = 0;

    for (nobjects = kmd->n_objects; nobjects > 0; object++, nobjects--)
    {
        nvertices += object->n_verts;
    }

    vertices = GV_Malloc(nvertices * 2);
    work->vertices = vertices;

    if (!vertices)
    {
        return -1;
    }

    object = kmd->objects;

    for (nobjects = kmd->n_objects; nobjects > 0; object++, nobjects--)
    {
        src = (SVECTOR *)((short *)object->vertices + work->f2C);

        for (nvertices = object->n_verts; nvertices > 0; nvertices--)
        {
            *vertices++ = src->vx;
            src++;
        }
    }

    return 0;
}

int s16b_800C5728(ShakemdlWork *work, short *arg1)
{
    DG_MDL  *object;
    short   *src;
    int      index;
    int      nobjects;
    SVECTOR *vertex;
    int      nvertices;
    int      ret;

    object = work->kmd->objects;
    src = work->vertices;
    index = 0;
    ret = 0;

    for (nobjects = work->kmd->n_objects; nobjects > 0; nobjects--, object++)
    {
        vertex = (SVECTOR *)((short *)object->vertices + work->f2C);

        for (nvertices = object->n_verts; nvertices > 0; nvertices--)
        {
            vertex->vx = *src++ + arg1[index];
            index = (index + 1) & 0xF;
            vertex++;
        }
    }

    return ret;
}

int s16b_800C57A4(ShakemdlWork *work)
{
    DG_MDL  *object;
    short   *src;
    int      nobjects;
    SVECTOR *vertex;
    int      nvertices;

    object = work->kmd->objects;
    src = work->vertices;

    for (nobjects = work->kmd->n_objects; nobjects > 0; nobjects--, object++)
    {
        vertex = (SVECTOR *)((short *)object->vertices + work->f2C);

        for (nvertices = object->n_verts; nvertices > 0; nvertices--)
        {
            vertex->vx = *src++;
            vertex++;
        }
    }

    return 0;
}
