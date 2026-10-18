// VR-DISC only: m_door.c ("mystery door")
// A door model that slams open when it is hit (it is shaken by a rotation table), together with two
// dynamic hazard segments: the first one is open while the door stands, the second one while the player is
// on the "side" status.  HASH_ENTER / HASH_LEAVE show and hide the model.

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "enemy/dymc_seg.h"
#include "strcode.h"

/*---------------------------------------------------------------------------*/

#define DOOR_FLAG ( DG_FLAG_TEXT | DG_FLAG_PAINT | DG_FLAG_TRANS | DG_FLAG_BOUND | DG_FLAG_ONEPIECE )

#define SE_DOOR_HIT_A   206
#define SE_DOOR_HIT_B   207
#define SE_DOOR_SLAM    208

#define STEP_SLAM_SE    8   // timer value at which the door slams and its hazard segment opens
#define STEP_END        40  // the shaking is over

enum
{
    STATE_IDLE = 0,
    STATE_OPENING = 1,
    STATE_OPEN = 2
};

typedef struct _Work
{
    GV_ACT   actor;
    OBJECT   object;
    MATRIX   light[2];          // 0x104 (not used by this actor)
    TARGET  *target;           // 0x144
    int     *segment_door;      // 0x148 hazard segment of the door itself
    int     *segment_side;      // 0x14C hazard segment, open while the player is on the "side" status
    SVECTOR  pos;               // 0x150
    SVECTOR  rot;               // 0x158
    int      name;              // 0x160
    int      visible;           // 0x164
    int      state;             // 0x168
    int      timer;             // 0x16C
} Work;

/*---------------------------------------------------------------------------*/

static SVECTOR door_target_size = {750, 1500, 400, 0};
static SVECTOR door_target_force = {0, 0, 0, 0};
static SVECTOR door_target_offset = {8000, 1500, 0, 0};

/*---------------------------------------------------------------------------*/

static void CheckMessage(Work *work)
{
    GV_MSG *msg;

    if (GV_ReceiveMessage(work->name, &msg) != 0)
    {
        if (msg->message[0] == HASH_LEAVE)
        {
            work->visible = 0;
        }
        else if (msg->message[0] == HASH_ENTER)
        {
            work->visible = 1;
        }
    }
}

static void UpdateVisibility(Work *work)
{
    if (work->visible != 0)
    {
        DG_VisibleObjs(work->object.objs);
    }
    else
    {
        DG_InvisibleObjs(work->object.objs);
    }
}

static void UpdateSideSegment(Work *work)
{
    if (GM_PlayerStatus & PLAYER_SIDE)
    {
        *work->segment_side = 1;
    }
    else
    {
        *work->segment_side = 0;
    }
}

static int CheckHit(Work *work)
{
    TARGET *target;

    target = work->target;
    if (target->damaged & TARGET_POWER)
    {
        switch (target->a_mode)
        {
        case 3:
            GM_SeSet(&work->pos, SE_DOOR_HIT_A);
            break;
        case 4:
            GM_SeSet(&work->pos, SE_DOOR_HIT_B);
            break;
        }

        target->damage = 0;
        target->damaged = 0;

        if (target->a_mode == 4)
        {
            return 1;
        }
    }

    return 0;
}

static int Shake(Work *work)
{
    int timer;

    if (work->timer < 4)
    {
        work->rot.vy -= 256;
        work->rot.vz += 10;
    }
    else if (work->timer < 6)
    {
        work->rot.vy += 128;
    }
    else if (work->timer < 8)
    {
        work->rot.vy += 64;
    }
    else if (work->timer < 12)
    {
        work->rot.vy += 32;
    }
    else if (work->timer < 16)
    {
        // no movement
    }
    else if (work->timer < 32)
    {
        work->rot.vy -= 20;
    }
    else if (work->timer < STEP_END)
    {
        work->rot.vy -= 24;
    }
    else
    {
        return 1;
    }

    timer = work->timer;
    if (timer == STEP_SLAM_SE)
    {
        GM_SeSet(&work->pos, SE_DOOR_SLAM);
        if (work->timer == timer)
        {
            *work->segment_door = 0;
        }
    }

    DG_SetPos2(&work->pos, &work->rot);
    DG_PutObjs(work->object.objs);

    work->timer++;
    return 0;
}

static void UpdateState(Work *work)
{
    switch (work->state)
    {
    case STATE_IDLE:
        UpdateSideSegment(work);
        if (CheckHit(work))
        {
            *work->segment_side = 0;
            work->state = STATE_OPENING;
            work->timer = 0;
        }
        break;

    case STATE_OPENING:
        if (Shake(work))
        {
            work->state = STATE_OPEN;
        }
        break;

    case STATE_OPEN:
        break;
    }
}

static void Act(Work *work)
{
    CheckMessage(work);
    UpdateVisibility(work);
    UpdateState(work);

    if (GM_CheckMessage(&work->actor, work->name, HASH_KILL))
    {
        GV_DestroyActor(&work->actor);
    }
}

static void Die(Work *work)
{
    GM_FreeObject(&work->object);
}

static void InitSegments(Work *work)
{
    SVECTOR min;
    SVECTOR max;

    min.vx = 7250;
    min.vy = 0;
    min.vz = 250;

    max.vx = 8750;
    max.vy = 0;
    max.vz = 250;

    NewDynamicSegment(GV_StrCode("メイン"), &min, &max, 1000, 1000, 256, &work->segment_door);
    *work->segment_door = 1;

    NewDynamicSegment(GV_StrCode("メイン"), &min, &max, 3000, 3000, 256, &work->segment_side);
    *work->segment_side = 0;
}

static int InitTarget(Work *work)
{
    TARGET *target;

    target = GM_AllocTarget();
    work->target = target;
    if (target == NULL)
    {
        return -1;
    }

    GM_SetTarget(target, 0x15, 2, &door_target_size);
    GM_SetPowerTarget(target, 1, -1, 0xFF, 5, &door_target_force);
    GM_MoveTarget(target, &door_target_offset);
    return 0;
}

static int GetResources(Work *work, SVECTOR *pos, SVECTOR *rot, int model, int map)
{
    OBJECT *object;

    object = &work->object;
    GM_CurrentMap = map;
    GM_InitObject(object, model, DOOR_FLAG, map);
    GM_ConfigObjectJoint(object);

    work->pos = *pos;
    work->rot = *rot;
    DG_SetPos2(pos, rot);
    DG_PutObjs(work->object.objs);
    GM_ReshadeObjs(work->object.objs);

    if (InitTarget(work) < 0)
    {
        return -1;
    }

    InitSegments(work);
    work->visible = 1;
    work->state = STATE_IDLE;
    work->timer = 0;
    return 0;
}

void *NewMysteryDoor(int name, int where)
{
    Work    *work;
    char    *opt;
    int      model; // FIXME: left uninitialized when there is no 'm' option, like the original
    SVECTOR  pos;
    SVECTOR  rot;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "m_door.c");

        opt = GCL_GetOption('m');
        if (opt != NULL)
        {
            model = GCL_StrToInt(opt);
        }

        opt = GCL_GetOption('p');
        if (opt != NULL)
        {
            GCL_StrToSV(opt, (short *)&pos);
        }
        else
        {
            pos = DG_ZeroVector;
        }

        opt = GCL_GetOption('d');
        if (opt != NULL)
        {
            GCL_StrToSV(opt, (short *)&rot);
        }
        else
        {
            rot = DG_ZeroVector;
        }

        if (GetResources(work, &pos, &rot, model, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->name = name;
    }

    return (void *)work;
}
