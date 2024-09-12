#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Game/game.h"
#include "Game/object.h"
#include "Game/camera.h"

// There are two actors in this file

// Created by NewSnake03c1_800CDAEC
typedef struct Snake03c1Work
{
    GV_ACT         actor;
    CONTROL        control;
    OBJECT         object;
    MOTION_CONTROL motion;
    MOTION_SEGMENT oar1[17];
    MOTION_SEGMENT oar2[17];
    SVECTOR        rots[32];
    MATRIX         light[2];
    GV_ACT        *other_actor; // practically unused, did it store Snake03c2Work*?
    SVECTOR        svec7DC;
    int            mode;
    int            field_7E8;
    int            field_7EC;
    int            procs[4];
} Snake03c1Work;

// Created by NewSnake03c2_800CDF18
typedef struct Snake03c2Work
{
    GV_ACT actor;
    int    mode;
    int    field_24;
    int    procs[4];
} Snake03c2Work;

#define EXEC_LEVEL 5

extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern int              GM_GameStatus;
extern CONTROL         *GM_PlayerControl_800AB9F4;
extern OBJECT          *GM_PlayerBody_800ABA20;
extern UnkCameraStruct  gUnkCameraStruct_800B77B8;

void s03b_boxall_800C969C(int, int);
void s03b_boxall_800C96E8(void);
void s03b_boxall_800C974C(void);

GV_ACT *NewFadeIo_800C4224(int name, int where);

void Snake03c1Act_800CD698(Snake03c1Work *work)
{
    SVECTOR  svec;
    CONTROL *control;
    OBJECT  *object;
    int      field_7E8;

    object = &work->object;
    GM_ActMotion(object);

    control = &work->control;
    GM_ActControl(control);

    GM_ActObject(object);

    DG_GetLightMatrix(&control->mov, work->light);

    work->control.mov.vy = work->object.field_18;
    work->control.height = work->object.field_18;

    gUnkCameraStruct_800B77B8.eye = work->control.mov;

    field_7E8 = work->field_7E8++;

    s03b_boxall_800C974C();

    switch (work->mode)
    {
    case 0:
        if (field_7E8 == 0)
        {
            NewFadeIo_800C4224(1, 48);
            GM_GameStatus |= STATE_PADRELEASE;
            s03b_boxall_800C969C(0, 0xEA60);
            GCL_ExecProc(work->procs[1], NULL);
        }
        if (--work->field_7EC == 0)
        {
            if (work->object.action_flag != 1)
            {
                GM_ConfigObjectAction(object, 1, 0, 4);
            }
            work->field_7E8 = 0;
            work->mode++;
        }
        break;

    case 1:
        if (work->object.is_end != 0)
        {
            GM_GameStatus &= ~STATE_PADRELEASE;
            s03b_boxall_800C96E8();
            GCL_ExecProc(work->procs[3], NULL);
            GCL_ExecProc(work->procs[0], NULL);
            GV_DestroyActor(&work->actor);
        }
        break;

    case 2:
        GV_SubVec3(&work->svec7DC, &control->mov, &svec);
        work->control.turn.vy = GV_VecDir2(&svec);
        svec.vy = 0;
        if (GV_VecLen3(&svec) < 250)
        {
            if (work->object.action_flag != 2)
            {
                GM_ConfigObjectAction(object, 2, 0, 4);
            }
            work->field_7E8 = 0;
            work->mode++;
        }
        break;

    case 3:
        if (field_7E8 == 64)
        {
            GM_GameStatus &= ~STATE_PADRELEASE;
            s03b_boxall_800C96E8();
            GCL_ExecProc(work->procs[3], NULL);
            GCL_ExecProc(work->procs[0], NULL);
            GV_DestroyActor(&work->actor);
        }
        break;
    }
}

void Snake03c1Die_800CD8CC(Snake03c1Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->object);
    if (work->other_actor != NULL)
    {
        GV_DestroyActor(work->other_actor);
    }
}

void Snake03c1_800CD914(Snake03c1Work *work)
{
    int   i;
    int  *out;
    char *res;

    if (!GCL_GetOption('e'))
    {
        return;
    }

    i = 0;
    out = work->procs;
    while ((res = GCL_GetParamResult()))
    {
        if (i == 4)
        {
            break;
        }

        *out++ = GCL_StrToInt(res);
        i++;
    }
}

int Snake03c1GetResources_800CD98C(Snake03c1Work *work, int arg1, int arg2)
{
    CONTROL *control;
    int      motion;
    int      model;

    control = &work->control;
    if (GM_InitControl(control, arg1, arg2) < 0)
    {
        return -1;
    }

    GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));
    GM_ConfigControlHazard(control, control->mov.vy, -2, -2);

    model = GCL_StrToInt(GCL_GetOption('m'));
    motion = GCL_StrToInt(GCL_GetOption('o'));

    GCL_StrToSV(GCL_GetOption('t'), &work->svec7DC);

    GM_InitObject(&work->object, model & 0xFFFF, 0x2D, motion & 0xFFFF);
    GM_ConfigObjectJoint(&work->object);
    GM_ConfigMotionControl_80034F08(&work->object, &work->motion, motion & 0xFFFF, work->oar1, work->oar2, control,
                                    work->rots);
    GM_ConfigObjectLight(&work->object, work->light);
    GM_ConfigObjectAction(&work->object, 0, 0, 0);
    Snake03c1_800CD914(work);
    work->field_7E8 = 0;
    work->mode = 0;
    work->field_7EC = GCL_StrToInt(GCL_GetOption('c'));
    work->other_actor = NULL;
    return 0;
}

GV_ACT *NewSnake03c1_800CDAEC(int name, int where)
{
    Snake03c1Work *work;

    work = (Snake03c1Work *)GV_NewActor(EXEC_LEVEL, sizeof(Snake03c1Work));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, (TActorFunction)Snake03c1Act_800CD698,
                     (TActorFunction)Snake03c1Die_800CD8CC, "sne_03c.c");
    if (Snake03c1GetResources_800CD98C(work, name, where) < 0)
    {
        GV_DestroyActor(&work->actor);
        return NULL;
    }

    return &work->actor;
}

//
// Snake03c1 ends here, Snake03c2 starts here
//

int Snake03c2GetRaise_800CDB78(DG_MDL *mdl)
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

int Snake03c2_800CDBC8()
{
    DG_MDL  *mdl, *mdl2;
    DG_OBJ  *obj;
    DG_OBJS *playerBodyObjs;
    int      count;

    playerBodyObjs = GM_PlayerBody_800ABA20->objs;
    count = playerBodyObjs->n_models;
    obj = playerBodyObjs->objs;
    for (; count > 0; count--, obj++)
    {
        DG_FreeObjPacket(obj, 0);
        DG_FreeObjPacket(obj, 1);
    }

    playerBodyObjs->def = GV_GetCache(GV_CacheID(GV_StrCode("snake"), 'k'));

    count = playerBodyObjs->def->num_mesh_4;
    mdl = playerBodyObjs->def->model;
    mdl2 = &playerBodyObjs->def->model[0];
    obj = &playerBodyObjs->objs[0];
    for (; count > 0; obj++, mdl2++, mdl++, count--)
    {
        obj->model = mdl;

        if (mdl2->extend < 0)
        {
            obj->extend = NULL;
        }
        else
        {
            obj->extend = &playerBodyObjs->objs[mdl2->extend];
        }

        obj->raise = Snake03c2GetRaise_800CDB78(mdl);
        obj->n_packs = mdl2->n_faces;
    }

    return 0;
}

void Snake03c2Act_800CDCE8(Snake03c2Work *work)
{
    int field_24;

    field_24 = work->field_24++;
    switch (work->mode)
    {
    case 0:
        if (field_24 == 0)
        {
            s03b_boxall_800C969C(0, 0x7530);
            GM_GameStatus |= STATE_PADRELEASE;
            GCL_ExecProc(work->procs[0], NULL);
        }
        if (field_24 == 48)
        {
            GCL_ExecProc(work->procs[1], NULL);
            work->field_24 = 0;
            work->mode++;
        }
        return;
    case 1:
        if (!(GM_PlayerStatus_800ABA50 & PLAYER_UNK4))
        {
            GM_SeSet2_80032968(0xF0, 0x3F, 0xB8);
            Snake03c2_800CDBC8();
            work->field_24 = 0;
            work->mode++;
        }
        break;
    case 2:
        if (field_24 == 32)
        {
            GCL_ExecProc(work->procs[2], NULL);
            work->mode++;
            work->field_24++;
        }
        break;
    case 3:
        if (!(GM_PlayerStatus_800ABA50 & PLAYER_UNK4))
        {
            GM_GameStatus &= ~STATE_PADRELEASE;
            GM_PlayerControl_800AB9F4->turn.vy = 1024;
            s03b_boxall_800C96E8();
            GCL_ExecProc(work->procs[3], NULL);
            GV_DestroyActor(&work->actor);
        }
        break;
    }
}

void Snake03c2Die_800CDE78(void)
{
}

void Snake03c2GetResources_800CDE80(Snake03c2Work *work)
{
    int   i;
    int  *out;
    char *res;

    if (!GCL_GetOption('e'))
    {
        return;
    }

    i = 0;
    out = work->procs;
    while ((res = GCL_GetParamResult()))
    {
        if (i == 4)
        {
            break;
        }

        *out++ = GCL_StrToInt(res);
        i++;
    }
}

int Snake03c2GetResources_800CDEF8(Snake03c2Work *work)
{
    Snake03c2GetResources_800CDE80(work);
    return 0;
}

GV_ACT *NewSnake03c2_800CDF18()
{
    Snake03c2Work *work;

    work = (Snake03c2Work *)GV_NewActor(EXEC_LEVEL, sizeof(Snake03c2Work));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, (TActorFunction)Snake03c2Act_800CDCE8,
                     (TActorFunction)Snake03c2Die_800CDE78, "sne_03c.c");
    if (Snake03c2GetResources_800CDEF8(work) < 0)
    {
        GV_DestroyActor(&work->actor);
        return NULL;
    }

    return &work->actor;
}
