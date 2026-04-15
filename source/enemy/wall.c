#include "wall.h"

#include <stdio.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL      GV_ACTOR_LEVEL5

#define FLAG_UNLIT      ( DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS \
                        | DG_FLAG_BOUND | DG_FLAG_ONEPIECE )

#define FLAG_UNLIT_IR   ( DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS \
                        | DG_FLAG_BOUND | DG_FLAG_ONEPIECE | DG_FLAG_IRTEXTURE )

#define FLAG_AMBIENT    ( DG_FLAG_TEXT | DG_FLAG_SHADE | DG_FLAG_TRANS \
                        | DG_FLAG_BOUND | DG_FLAG_ONEPIECE \
                        | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )

/*---------------------------------------------------------------------------*/

typedef struct _Work
{
    GV_ACT  actor;
    OBJECT  object;
    MATRIX  light[2];
    SVECTOR position;
    int     name;
    int     visible;
    short   g_flag;
    short   ir_flag;
} Work;

/*---------------------------------------------------------------------------*/

static void CheckMessage(Work *work)
{
    GV_MSG *msg;

    if (GV_ReceiveMessage(work->name, &msg))
    {
        if (msg->message[0] == HASH_LEAVE)
        {
            work->visible = FALSE;
        }
        else if (msg->message[0] == HASH_ENTER)
        {
            work->visible = TRUE;
        }
    }
}

static void SetVisibility(Work *work)
{
    if (work->visible)
    {
        DG_VisibleObjs(work->object.objs);
    }
    else
    {
        DG_InvisibleObjs(work->object.objs);
    }
}

static void WriteObjsPacket(DG_OBJS *objs)
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

static void SetLighting(Work *work)
{
    if (work->g_flag)
    {
        if (GM_GameStatus & STATE_THERMG)
        {
            if (!work->ir_flag)
            {
                work->object.flag = FLAG_AMBIENT;
                work->object.objs->flag = FLAG_AMBIENT;
                DG_GetLightMatrix2(&work->position, work->light);
                GM_ConfigObjectLight(&work->object, work->light);
                work->ir_flag = TRUE;
            }
        }
        else if (work->ir_flag)
        {
            work->object.flag = FLAG_UNLIT_IR;
            work->object.objs->flag = FLAG_UNLIT_IR;
            WriteObjsPacket(work->object.objs);
            work->ir_flag = FALSE;
        }
    }
}

static void Act(Work *work)
{
    CheckMessage(work);
    SetVisibility(work);
    SetLighting(work);

    if (GM_CheckMessage(&work->actor, work->name, HASH_KILL))
    {
        GV_DestroyActor(&work->actor);
    }
}

static void Die(Work *work)
{
    printf("destroy\n");

    work->object.objs->flag = FLAG_UNLIT;
    GM_FreeObject(&work->object);
}

static int GetResources(work, pos, dir, def_model, map)
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

    GM_SetCurrentMap(map);
    object = &work->object;

    if (!work->g_flag)
    {
        GM_InitObject(object, model, FLAG_UNLIT, map);
    }
    else
    {
        GM_InitObject(object, model, FLAG_AMBIENT, map);
    }

    GM_ConfigObjectJoint(object);

    work->position = position;

    DG_SetPos2(&position, dir);
    DG_PutObjs(work->object.objs);
    ScaleMatrix(&work->object.objs->world, &scale);
    GM_ReshadeObjs(object->objs);

    work->visible = TRUE;
    work->ir_flag = TRUE;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewWall(SVECTOR *pos, SVECTOR *dir)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, NULL, Die, "wall.c");

        // Why? GetResources is missing two last arguments, leading to nasty UB
        if (GetResources(work, pos, dir) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}

void *NewWallGcl(int name, int where, int argc, char **argv)
{
    SVECTOR pos;
    SVECTOR dir;
    Work   *work;
    int     model;
    char   *param;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "wall.c");

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
            work->g_flag = GCL_StrToInt(param);
        }
        else
        {
            work->g_flag = FALSE;
        }

        if (GetResources(work, &pos, &dir, model, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->name = name;
    }

    return (void *)work;
}
