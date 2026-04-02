#include "boxkeri.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "game/game.h"

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL      GV_ACTOR_LEVEL4

#define BOX_MODEL       GV_StrCode("cb_box")
#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                        | DG_FLAG_GBOUND | DG_FLAG_ONEPIECE )

typedef struct _Work
{
    GV_ACT         actor;
    OBJECT_NO_ROTS body;
    SVECTOR        field_44;
    SVECTOR        field_48;
    MATRIX         world;
    short          step;
    short          field_76;
    short          field_78;
    short          field_7A;
    MATRIX         light[2];
} Work;

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    int step;

    step = work->step;
    if (step > 40)
    {
        GV_DestroyActor(&work->actor);
        return;
    }
    if (step < 9)
    {
        work->field_7A += 80;
        work->field_78 += 256;
    }
    else if (step < 12)
    {
        work->field_78 -= 128;
    }
    else if (step < 15)
    {
        work->field_78 += 64;
    }
    else if (step < 18)
    {
        work->field_78 -= 32;
    }
    else if (step < 19)
    {
        work->field_78 += 32;
    }
    else if (step & 1)
    {
        DG_InvisibleObjs(work->body.objs);
    }
    else
    {
        DG_VisibleObjs(work->body.objs);
    }

    switch (work->field_76)
    {
    case 0:
        if (step < 9)
        {
            work->field_7A += 5;
        }
        work->field_48.vz = -work->field_7A;
        work->field_44.vx = -work->field_78;
        break;

    case 1:
        work->field_48.vx = -work->field_7A;
        work->field_44.vz = work->field_78;
        break;

    case 2:
        if (step < 9)
        {
            work->field_7A += 100;
        }
        work->field_48.vz = work->field_7A;
        work->field_44.vx = work->field_78;
        break;

    case 3:
        work->field_48.vx = work->field_7A;
        work->field_44.vz = -work->field_78;
        break;
    }

    GM_CurrentMap = GM_PlayerMap;

    DG_SetPos(&work->world);
    DG_MovePos(&work->field_48);
    DG_RotatePos(&work->field_44);
    DG_PutObjs(work->body.objs);
    DG_GetLightMatrix2(&GM_PlayerPosition, work->light);

    work->step++;
}

static void Die(Work *work)
{
    GM_FreeObject((OBJECT *)&work->body);
}

static void SendMessage(void)
{
    GV_MSG msg;

    msg.address = GV_StrCode("スネーク");
    msg.message[0] = GV_StrCode("段ボール");
    msg.message[1] = 1;
    msg.message_len = 2;
    GV_SendMessage(&msg);
}

static int s00a_boxkeri_800D2440(SVECTOR *pos, SVECTOR *svec2)
{
    SVECTOR svec;

    GV_SubVec3(svec2, pos, &svec);
    return GV_VecDir2(&svec);
}

static int GetResources(Work *work, MATRIX *world, SVECTOR *arg2)
{
    OBJECT_NO_ROTS *obj;
    int             dir;

    obj = &work->body;
    GM_CurrentMap = GM_PlayerMap;
    GM_InitObjectNoRots(obj, GV_StrCode("cb_box"), BODY_FLAG, 0);
    GM_ConfigObjectLight((OBJECT *)obj, work->light);

    work->body.objs->objs[0].raise = 500;

    work->field_44 = DG_ZeroVector;
    work->field_48 = DG_ZeroVector;

    work->field_78 = 0;
    work->field_7A = 0;

    dir = GV_DiffDirU(GM_PlayerControl->rot.vy,
                      s00a_boxkeri_800D2440(&GM_PlayerPosition, arg2));
    if (dir < 512 || dir >= 3607)
    {
        work->field_76 = 0;
    }
    else
    {
        if (dir >= 1536)
        {
            if (dir >= 2584)
            {
                work->field_76 = 3;
            }
            else
            {
                work->field_76 = 2;
            }
        }
        else
        {
            work->field_76 = 1;
        }
    }

    work->world = *world;
    work->step = 0;
    SendMessage();
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewBoxKeri(MATRIX *world, SVECTOR *svec)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "boxkeri.c");
        if (GetResources(work, world, svec) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}
