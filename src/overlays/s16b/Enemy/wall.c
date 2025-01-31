#include "wall.h"

#include <stdio.h>
#include "common.h"
#include "Game/game.h"
#include "Game/object.h"
#include "libgv/libgv.h"
#include "strcode.h"

typedef struct _Work
{
    GV_ACT  actor;
    OBJECT  object;
    MATRIX  light[2];
    SVECTOR position;
    int     hash;
    int     f150;
    short   f154;
    short   f156;
} Work;

extern int GM_CurrentMap;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

void asioto_800C3278(Work *work)
{
    GV_MSG *msg;

    if (GV_ReceiveMessage(work->hash, &msg))
    {
        if (msg->message[0] == HASH_LEAVE)
        {
            work->f150 = 0;
        }
        else if (msg->message[0] == HASH_ENTER)
        {
            work->f150 = 1;
        }
    }
}

void asioto_800C32D8(Work *work)
{
    if (work->f150 != 0)
    {
        DG_VisibleObjs(work->object.objs);
    }
    else
    {
        DG_InvisibleObjs(work->object.objs);
    }
}

void asioto_800C3320(DG_OBJS *objs)
{
    DG_OBJ *obj;
    int     i;

    obj = objs->objs;
    for (i = objs->n_models; i > 0; obj++, i--)
    {
        if (obj->packs[0])
        {
            DG_WriteObjPacketRGB(obj, 0);
        }

        if (obj->packs[1])
        {
            DG_WriteObjPacketRGB(obj, 1);
        }
    }
}

void asioto_800C33A0(Work *work)
{
    if (work->f154 != 0)
    {
        if (GM_GameStatus & STATE_THERMG)
        {
            if (work->f156 == 0)
            {
                work->object.flag = 0x35D;
                work->object.objs->flag = 0x35D;
                DG_GetLightMatrix2(&work->position, work->light);
                GM_ConfigObjectLight(&work->object, work->light);
                work->f156 = 1;
            }
        }
        else if (work->f156 != 0)
        {
            work->object.flag = 0x257;
            work->object.objs->flag = 0x257;
            asioto_800C3320(work->object.objs);
            work->f156 = 0;
        }
    }
}

void WallAct_800C345C(Work *work)
{
    asioto_800C3278(work);
    asioto_800C32D8(work);
    asioto_800C33A0(work);

    if (GM_CheckMessage(&work->actor, work->hash, HASH_KILL))
    {
        GV_DestroyActor(&work->actor);
    }
}

void WallDie_800C34B0(Work *work)
{
    printf("destroy\n");

    work->object.objs->flag = DG_FLAG_ONEPIECE | DG_FLAG_BOUND | DG_FLAG_TRANS | DG_FLAG_PAINT | DG_FLAG_TEXT;
    GM_FreeObject(&work->object);
}

int WallGetResources_800C34F0(work, pos, dir, def_model, map)
    Work *work;
    SVECTOR *pos;
    SVECTOR *dir;
    int def_model;
    int map;
{
    SVECTOR position;
    VECTOR  scale;
    int     model;
    OBJECT *object;

    position = *pos;

    switch (def_model)
    {
    case 0:
        model = GV_StrCode("box_01");
        scale.vx = 8192;
        scale.vy = 16384;
        scale.vz = 8192;
        position.vy += 200;
        break;

    case 1:
        model = GV_StrCode("dbx1");
        scale.vx = 4096;
        scale.vy = 4096;
        scale.vz = 4096;
        break;

    case 2:
        model = GV_StrCode("dbx2");
        scale.vx = 4096;
        scale.vy = 4096;
        scale.vz = 4096;
        break;

    default:
        model = def_model;
        scale.vx = 4096;
        scale.vy = 4096;
        scale.vz = 4096;
        break;
    }

    GM_CurrentMap = map;
    object = &work->object;

    if (work->f154 == 0)
    {
        GM_InitObject(object, model, 0x57, map);
    }
    else
    {
        GM_InitObject(object, model, 0x35d, map);
    }

    GM_ConfigObjectJoint(object);

    work->position = position;

    DG_SetPos2(&position, dir);
    DG_PutObjs(work->object.objs);
    ScaleMatrix(&work->object.objs->world, &scale);
    GM_ReshadeObjs(object->objs);

    work->f150 = 1;
    work->f156 = 1;
    return 0;
}

GV_ACT *NewWall_800C3688(SVECTOR *pos, SVECTOR *dir)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, NULL, WallDie_800C34B0, "wall.c");

        // Why? WallGetResources_800C34F0 is missing two last arguments, leading to nasty UB
        if (WallGetResources_800C34F0(work, pos, dir) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

GV_ACT *NewWall_800C3718(int name, int where, int argc, char **argv)
{
    SVECTOR pos;
    SVECTOR dir;
    Work   *work;
    int     model;
    char   *param;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, WallAct_800C345C, WallDie_800C34B0, "wall.c");

        param = GCL_GetOption('t');
        if (param != 0)
        {
            model = GCL_StrToInt(param);
        }
        else
        {
            model = 0;
        }

        param = GCL_GetOption('m');
        if (param != 0)
        {
            model = GCL_StrToInt(param);
        }

        param = GCL_GetOption('p');
        if (param != 0)
        {
            GCL_StrToSV(param, &pos);
        }
        else
        {
            pos = DG_ZeroVector;
        }

        param = GCL_GetOption('d');
        if (param != 0)
        {
            GCL_StrToSV(param, &dir);
        } else
        {
            dir = DG_ZeroVector;
        }

        param = GCL_GetOption('g');
        if (param != 0)
        {
            work->f154 = GCL_StrToInt(param);
        }
        else
        {
            work->f154 = 0;
        }

        if (WallGetResources_800C34F0(work, &pos, &dir, model, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->hash = name;
    }

    return &work->actor;
}
