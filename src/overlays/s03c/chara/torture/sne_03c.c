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
    OAR_RECORD     oar1[17];
    OAR_RECORD     oar2[17];
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
extern int              GM_GameStatus_800AB3CC;
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
    GM_ActMotion_80034A7C(object);

    control = &work->control;
    GM_ActControl_80025A7C(control);

    GM_ActObject_80034AF4(object);

    DG_GetLightMatrix_8001A3C4(&control->field_0_mov, work->light);

    work->control.field_0_mov.vy = work->object.field_18;
    work->control.field_32_height = work->object.field_18;

    gUnkCameraStruct_800B77B8.field_0 = work->control.field_0_mov;

    field_7E8 = work->field_7E8++;

    s03b_boxall_800C974C();

    switch (work->mode)
    {
    case 0:
        if (field_7E8 == 0)
        {
            NewFadeIo_800C4224(1, 48);
            GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_29;
            s03b_boxall_800C969C(0, 0xEA60);
            GCL_ExecProc_8001FF2C(work->procs[1], NULL);
        }
        if (--work->field_7EC == 0)
        {
            if (work->object.action_flag != 1)
            {
                GM_ConfigObjectAction_80034CD4(object, 1, 0, 4);
            }
            work->field_7E8 = 0;
            work->mode++;
        }
        break;

    case 1:
        if (work->object.is_end != 0)
        {
            GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_29;
            s03b_boxall_800C96E8();
            GCL_ExecProc_8001FF2C(work->procs[3], NULL);
            GCL_ExecProc_8001FF2C(work->procs[0], NULL);
            GV_DestroyActor_800151C8(&work->actor);
        }
        break;

    case 2:
        GV_SubVec3_80016D40(&work->svec7DC, &control->field_0_mov, &svec);
        work->control.field_4C_turn.vy = GV_VecDir2_80016EF8(&svec);
        svec.vy = 0;
        if (GV_VecLen3_80016D80(&svec) < 250)
        {
            if (work->object.action_flag != 2)
            {
                GM_ConfigObjectAction_80034CD4(object, 2, 0, 4);
            }
            work->field_7E8 = 0;
            work->mode++;
        }
        break;

    case 3:
        if (field_7E8 == 64)
        {
            GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_29;
            s03b_boxall_800C96E8();
            GCL_ExecProc_8001FF2C(work->procs[3], NULL);
            GCL_ExecProc_8001FF2C(work->procs[0], NULL);
            GV_DestroyActor_800151C8(&work->actor);
        }
        break;
    }
}

void Snake03c1Die_800CD8CC(Snake03c1Work *work)
{
    GM_FreeControl_800260CC(&work->control);
    GM_FreeObject_80034BF8(&work->object);
    if (work->other_actor != NULL)
    {
        GV_DestroyActor_800151C8(work->other_actor);
    }
}

void Snake03c1_800CD914(Snake03c1Work *work)
{
    int   i;
    int  *out;
    char *res;

    if (!GCL_GetOption_80020968('e'))
    {
        return;
    }

    i = 0;
    out = work->procs;
    while ((res = GCL_Get_Param_Result_80020AA4()))
    {
        if (i == 4)
        {
            break;
        }

        *out++ = GCL_StrToInt_800209E8(res);
        i++;
    }
}

int Snake03c1GetResources_800CD98C(Snake03c1Work *work, int arg1, int arg2)
{
    CONTROL *control;
    int      motion;
    int      model;

    control = &work->control;
    if (GM_InitLoader_8002599C(control, arg1, arg2) < 0)
    {
        return -1;
    }

    GM_ConfigControlString_800261C0(control, GCL_GetOption_80020968('p'), GCL_GetOption_80020968('d'));
    GM_ConfigControlHazard_8002622C(control, control->field_0_mov.vy, -2, -2);

    model = GCL_StrToInt_800209E8(GCL_GetOption_80020968('m'));
    motion = GCL_StrToInt_800209E8(GCL_GetOption_80020968('o'));

    GCL_StrToSV_80020A14(GCL_GetOption_80020968('t'), &work->svec7DC);

    GM_InitObject_80034A18(&work->object, model & 0xFFFF, 0x2D, motion & 0xFFFF);
    GM_ConfigObjectJoint_80034CB4(&work->object);
    GM_ConfigMotionControl_80034F08(&work->object, &work->motion, motion & 0xFFFF, work->oar1, work->oar2, control,
                                    work->rots);
    GM_ConfigObjectLight_80034C44(&work->object, work->light);
    GM_ConfigObjectAction_80034CD4(&work->object, 0, 0, 0);
    Snake03c1_800CD914(work);
    work->field_7E8 = 0;
    work->mode = 0;
    work->field_7EC = GCL_StrToInt_800209E8(GCL_GetOption_80020968('c'));
    work->other_actor = NULL;
    return 0;
}

GV_ACT *NewSnake03c1_800CDAEC(int name, int where)
{
    Snake03c1Work *work;

    work = (Snake03c1Work *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(Snake03c1Work));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)Snake03c1Act_800CD698,
                              (TActorFunction)Snake03c1Die_800CD8CC, "sne_03c.c");
    if (Snake03c1GetResources_800CD98C(work, name, where) < 0)
    {
        GV_DestroyActor_800151C8(&work->actor);
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

    flags = mdl->flags_0;
    raise = 0;
    if (flags & 0x300)
    {
        raise = (4 - ((flags >> 0xC) & 3)) * 250;
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
        DG_FreeObjPacket_8001AAD0(obj, 0);
        DG_FreeObjPacket_8001AAD0(obj, 1);
    }

    playerBodyObjs->def = GV_GetCache_8001538C(GV_CacheID_800152DC(GV_StrCode_80016CCC("snake"), 'k'));

    count = playerBodyObjs->def->num_mesh_4;
    mdl = playerBodyObjs->def->model;
    mdl2 = &playerBodyObjs->def->model[0];
    obj = &playerBodyObjs->objs[0];
    for (; count > 0; obj++, mdl2++, mdl++, count--)
    {
        obj->model = mdl;

        if (mdl2->unknownA_30 < 0)
        {
            obj->extend = NULL;
        }
        else
        {
            obj->extend = &playerBodyObjs->objs[mdl2->unknownA_30];
        }

        obj->raise = Snake03c2GetRaise_800CDB78(mdl);
        obj->n_packs = mdl2->numFaces_4;
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
            GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_29;
            GCL_ExecProc_8001FF2C(work->procs[0], NULL);
        }
        if (field_24 == 48)
        {
            GCL_ExecProc_8001FF2C(work->procs[1], NULL);
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
            GCL_ExecProc_8001FF2C(work->procs[2], NULL);
            work->mode++;
            work->field_24++;
        }
        break;
    case 3:
        if (!(GM_PlayerStatus_800ABA50 & PLAYER_UNK4))
        {
            GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_29;
            GM_PlayerControl_800AB9F4->field_4C_turn.vy = 1024;
            s03b_boxall_800C96E8();
            GCL_ExecProc_8001FF2C(work->procs[3], NULL);
            GV_DestroyActor_800151C8(&work->actor);
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

    if (!GCL_GetOption_80020968('e'))
    {
        return;
    }

    i = 0;
    out = work->procs;
    while ((res = GCL_Get_Param_Result_80020AA4()))
    {
        if (i == 4)
        {
            break;
        }

        *out++ = GCL_StrToInt_800209E8(res);
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

    work = (Snake03c2Work *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(Snake03c2Work));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)Snake03c2Act_800CDCE8,
                              (TActorFunction)Snake03c2Die_800CDE78, "sne_03c.c");
    if (Snake03c2GetResources_800CDEF8(work) < 0)
    {
        GV_DestroyActor_800151C8(&work->actor);
        return NULL;
    }

    return &work->actor;
}
