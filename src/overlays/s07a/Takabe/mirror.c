#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Equip/equip.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "Takabe/thing.h"
#include "strcode.h"

typedef struct _MirrorEntry
{
    int      name;
    CONTROL *control;
    DG_OBJS *objs;
    DG_DEF  *def;
    MATRIX   light[2];
    MATRIX  *light2;
} MirrorEntry;

typedef struct _MirrorObject
{
    int     flags;
    DG_OBJS objs;
    DG_OBJ  obj;
    MATRIX  light[2];
} MirrorObject;

typedef struct _MirrorWork
{
    GV_ACT       actor;
    int          map;
    int          name;
    SVECTOR      f28;
    int          f30;
    int          f34;
    int          n_entries;
    MirrorEntry  entries[8];
    int          n_objects;
    MirrorObject objects[8];
    int          snake_flags;
    OBJECT       kogaku_object;
    GV_ACT      *kogaku;
} MirrorWork;

extern int      GM_CurrentMap_800AB9B0;
extern int      gControlCount_800AB9B4;
extern CONTROL *GM_WhereList_800B56D0[96];

void     Mirror_800E08F0(MirrorWork *work, int name);
void     Mirror_800E0A88(MirrorEntry *entry);
DG_DEF * Mirror_800E0AD8(DG_DEF *def, int arg1);
void     Mirror_800E0BDC(DG_OBJS *objs);

#define EXEC_LEVEL 5

void MirrorAct_800DFDDC(MirrorWork *work)
{
    SVECTOR       sp10;
    GV_MSG       *msg;
    int           n_msgs;
    int           action;
    int           name;
    int           found;
    MirrorEntry  *found_entry;
    MirrorEntry  *entry;
    int           i;
    short        *mtx_temp;
    int           prev_flags;
    DG_CHANL     *chanl;
    DG_OBJS     **queue;
    DG_OBJS     **src;
    DG_OBJS     **dst;
    MirrorObject *object;
    DG_MDL       *mdl;
    DG_OBJS      *objs;
    DG_OBJ       *obj;
    long         *mtx_temp2;


    GM_CurrentMap_800AB9B0 = work->map;

    n_msgs = GV_ReceiveMessage(work->name, &msg);

    for (; n_msgs > 0; n_msgs--)
    {
        action = msg->message[0];
        name = msg->message[1];

        found = 0;
        found_entry = NULL;

        entry = work->entries;
        for (i = 0; i < work->n_entries; i++)
        {
            if (entry->name == name)
            {
                found_entry = entry;
                found = 1;
                break;
            }

            entry++;
        }

        if (action == 0xD182)
        {
            if (found == 0)
            {
                Mirror_800E08F0(work, name);
            }
        }
        else if (found != 0)
        {
            if ((name == CHARA_SNAKE) && (work->snake_flags & 0x1))
            {
                work->snake_flags &= ~0x1;
                GV_DestroyActorQuick(work->kogaku);
            }

            Mirror_800E0A88(found_entry);
            *found_entry = work->entries[--work->n_entries];
        }

        msg++;
    }

    entry = work->entries;
    for (i = 0; i < work->n_entries; i++)
    {
        sp10 = entry->control->mov;

        mtx_temp = (short *)&sp10 + work->f30;
        *mtx_temp = *((short *)&work->f28 + work->f30) * 2 - *mtx_temp;

        DG_SetPos2(&sp10, &entry->control->rot);
        DG_PutObjs(entry->objs);

        entry->light[0] = entry->light2[0];
        entry->light[1] = entry->light2[1];

        mtx_temp = (short *)&entry->objs->world.m[work->f30];
        mtx_temp[0] = -mtx_temp[0];
        mtx_temp[1] = -mtx_temp[1];
        mtx_temp[2] = -mtx_temp[2];

        mtx_temp = (short *)entry->light + work->f30;
        mtx_temp[0] = -mtx_temp[0];
        mtx_temp[3] = -mtx_temp[3];
        mtx_temp[6] = -mtx_temp[6];

        entry++;
    }

    entry = work->entries;
    for (i = 0; i < work->n_entries; i++)
    {
        if (entry->name == CHARA_SNAKE)
        {
            if (GM_CurrentItemId == ITEM_STEALTH)
            {
                if (!(work->snake_flags & 0x1))
                {
                    work->kogaku_object.objs = entry->objs;
                    work->kogaku = NewKogaku2(entry->control, &work->kogaku_object, 0);
                    work->snake_flags |= 0x1;
                }
            }
            else if (work->snake_flags & 0x1)
            {
                GV_DestroyActorQuick(work->kogaku);
                work->snake_flags &= ~0x1;
            }

            prev_flags = work->snake_flags;

            if (GM_CurrentItemId == ITEM_B_ARMOR)
            {
                work->snake_flags |= 0x4;
            }
            else
            {
                work->snake_flags &= ~0x4;
            }

            if (GM_CurrentItemId == ITEM_BANDANA)
            {
                work->snake_flags |= 0x8;
            }
            else
            {
                work->snake_flags &= ~0x8;
            }

            if (prev_flags != work->snake_flags)
            {
                Mirror_800E0BDC(entry->objs);
            }
        }

        entry++;
    }

    chanl = DG_Chanl(0);

    queue = chanl->mQueue;
    objs = &work->objects[0].objs;
    for (i = chanl->mTotalObjectCount; i > 0; i--, queue++)
    {
        if (*queue != objs)
        {
            continue;
        }

        src = &queue[work->n_objects];
        dst = queue;
        for (i -= work->n_objects; i > 0; i--)
        {
            *dst++ = *src++;
        }

        chanl->mTotalObjectCount -= work->n_objects;

        object = &work->objects[work->n_objects];
        for (i = work->n_objects; i > 0; i--)
        {
            object--;

            mdl = &object->objs.def->model[0];
            mdl->flags = object->flags;

            DG_FreeObjPacket(&object->obj, 0);
            DG_FreeObjPacket(&object->obj, 1);
        }

        work->n_objects = 0;
        break;
    }

    if (work->n_entries == 0)
    {
        return;
    }

    queue = chanl->mQueue;
    object = work->objects;
    for (i = chanl->mTotalObjectCount; i > 0; i--)
    {
        objs = *queue++;

        if ((objs->n_models == 1) && ((objs->group_id & work->map) != 0))
        {
            object->objs = *objs;
            object->flags = objs->def->model[0].flags;
            objs->def->model[0].flags |= 0x400;

            obj = &object->obj;
            *obj = objs->objs[0];
            obj->packs[0] = NULL;
            obj->packs[1] = NULL;
            obj->raise = work->f34;

            object->light[0] = objs->light[0];
            object->light[1] = objs->light[1];

            objs = &object->objs;

            if (objs->root != NULL)
            {
                object->objs.world = *objs->root;
                objs->root = NULL;
            }

            objs->light = object->light;
            DG_VisibleObjs(objs);

            mtx_temp2 = &objs->world.t[work->f30];
            *mtx_temp2 = *((short *)&work->f28 + work->f30) * 2 - *mtx_temp2;

            mtx_temp = (short *)&object->objs.world.m[work->f30];
            mtx_temp[0] = -mtx_temp[0];
            mtx_temp[1] = -mtx_temp[1];
            mtx_temp[2] = -mtx_temp[2];

            mtx_temp = (short *)object->light + work->f30;
            mtx_temp[0] = -mtx_temp[0];
            mtx_temp[3] = -mtx_temp[3];
            mtx_temp[6] = -mtx_temp[6];

            object++;
            if (++work->n_objects == 8)
            {
                break;
            }
        }
    }

    object = work->objects;

    if (chanl->mFreePrimCount < (chanl->mTotalObjectCount + work->n_objects))
    {
        work->n_objects = chanl->mFreePrimCount - chanl->mTotalObjectCount;
    }

    queue = chanl->mQueue + chanl->mTotalObjectCount;
    for (i = work->n_objects; i > 0; i--)
    {
        *queue++ = &object->objs;
        object++;
    }

    chanl->mTotalObjectCount += work->n_objects;
}

void MirrorDie_800E0670(MirrorWork *work)
{
    MirrorEntry  *entry;
    int           i, j;
    DG_CHANL     *chanl;
    DG_OBJS     **queue;
    DG_OBJS      *first;
    DG_OBJS     **src;
    DG_OBJS     **dst;
    MirrorObject *object;
    DG_MDL       *mdl;

    entry = work->entries;
    for (i = 0; i < work->n_entries; i++)
    {
        if ((entry->name == CHARA_SNAKE) && (work->snake_flags & 0x1))
        {
            GV_DestroyActorQuick(work->kogaku);
        }

        Mirror_800E0A88(entry++);
    }

    chanl = DG_Chanl(0);
    queue = chanl->mQueue;

    first = &work->objects[0].objs;

    for (j = chanl->mTotalObjectCount; j > 0; j--, queue++)
    {
        if (*queue != first)
        {
            continue;
        }

        src = &queue[work->n_objects];
        dst = queue;
        for (j -= work->n_objects; j > 0; j--)
        {
            *dst++ = *src++;
        }

        chanl->mTotalObjectCount -= work->n_objects;

        object = &work->objects[work->n_objects];
        for (j = work->n_objects; j > 0; j--)
        {
            object--;

            mdl = &object->objs.def->model[0];
            mdl->flags = object->flags;

            DG_FreeObjPacket(&object->obj, 0);
            DG_FreeObjPacket(&object->obj, 1);
        }

        work->n_objects = 0;
        return;
    }
}

int MirrorGetResources_800E07F8(MirrorWork *work, int name, int map)
{
    GM_CurrentMap_800AB9B0 = map;

    work->name = name;
    work->map = map;

    THING_Gcl_GetSVector('p', &work->f28);

    work->f30 = THING_Gcl_GetInt('m');
    work->f34 = THING_Gcl_GetIntDefault('r', -750);
    work->n_entries = 0;
    work->n_objects = 0;

    return 0;
}

GV_ACT *NewMirror_800E085C(int name, int where)
{
    MirrorWork *work;

    work = (MirrorWork *)GV_NewActor(EXEC_LEVEL, sizeof(MirrorWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)MirrorAct_800DFDDC, (GV_ACTFUNC)MirrorDie_800E0670, "mirror.c");

        if (MirrorGetResources_800E07F8(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

void Mirror_800E08F0(MirrorWork *work, int name)
{
    CONTROL    **where;
    int          i;
    CONTROL     *control;
    MirrorEntry *entry;
    OBJECT      *object;
    DG_OBJ      *obj;

    where = GM_WhereList_800B56D0;
    for (i = gControlCount_800AB9B4; i > 0; i--)
    {
        control = *where;
        if (control->name == name)
        {
            break;
        }

        where++;
    }

    if (i == 0)
    {
        return;
    }

    entry = &work->entries[work->n_entries++];
    entry->control = *where;

    object = (OBJECT *)(entry->control + 1); // why...

    entry->def = Mirror_800E0AD8(object->objs->def, work->f30);
    entry->objs = DG_MakeObjs(entry->def, object->flag, 0);
    entry->name = name;

    entry->objs->rots = object->objs->rots;
    entry->objs->adjust = object->objs->adjust;
    entry->objs->waist_rot = object->objs->waist_rot;
    entry->objs->movs = object->objs->movs;
    entry->objs->light = entry->light;

    entry->light2 = object->objs->light;

    obj = entry->objs->objs;
    for (i = entry->objs->n_models; i > 0; i--)
    {
        obj->raise = work->f34;
        obj++;
    }

    DG_QueueObjs(entry->objs);
    DG_GroupObjs(entry->objs, GM_CurrentMap_800AB9B0);
}

void Mirror_800E0A88(MirrorEntry *entry)
{
    DG_DequeueObjs(entry->objs);
    DG_FreePreshade(entry->objs);
    DG_FreeObjs(entry->objs);
    GV_Free(entry->def);
}

DG_DEF * Mirror_800E0AD8(DG_DEF *def, int arg1)
{
    int     n_models;
    DG_DEF *copy;
    DG_MDL *src;
    DG_MDL *dst;

    n_models = def->num_mesh_4;

    copy = GV_Malloc(sizeof(DG_DEF) + n_models * sizeof(DG_MDL));
    memcpy(copy, def, sizeof(DG_DEF));

    src = def->model;
    dst = copy->model;

    for (; n_models > 0; n_models--)
    {
        memcpy(dst, src, sizeof(DG_MDL));
        dst->flags |= 0x400;

        src++;
        dst++;
    }

    def = copy;
    return def;
}

void Mirror_800E0BDC(DG_OBJS *objs)
{
    DG_OBJ *obj;
    int     i;

    obj = objs->objs;
    for (i = objs->n_models; i > 0; i--)
    {
        DG_WriteObjPacketUV(obj, 0);
        DG_WriteObjPacketUV(obj, 1);
        obj++;
    }
}

