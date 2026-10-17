#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "game/game.h"
#include "bullet/blast.h"
#include "takabe/thing.h"

/* drum can (CHARA_DRUMCAN): a destructible oil drum that blows up and bounces around */

typedef struct _Work
{
    GV_ACT   actor;
    int      map;           // 0x20
    CONTROL  control;       // 0x24
    OBJECT   body;          // 0xA0
    MATRIX   light[2];      // 0x184
    SVECTOR  size;          // 0x1C4
    TARGET  *target;        // 0x1CC
    TARGET  *target2;       // 0x1D0
    char     pad_1D4[0x20];
    HOMING  *hom;           // 0x1F4
    int      field_1F8;
    int      field_1FC;
    int      state;         // 0x200 counts the frames after the explosion
    int      bouncing;      // 0x204
    int      height;        // 0x208
    int      n_segs;        // 0x20C
    HZD_HDL *hzd;           // 0x210
    HZD_SEG  segs[8];       // 0x214
    int      proc;          // 0x294
    int      bounces;       // 0x298
    int      has_force;     // 0x29C
    SVECTOR  turn;          // 0x2A0
    SVECTOR  force;         // 0x2A8
} Work;

#define BODY_MODEL        0xFAEE // GV_StrCode( "drum" )
#define BODY_MODEL_BROKEN 0xFAEF
#define BODY_FLAG ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE | DG_FLAG_BOUND | DG_FLAG_ONEPIECE )

extern BLAST_DATA blast_data_8009F4B8[8];

void *NewDrumSmoke(MATRIX *world, int flag, int time);
void *NewDrumFire(MATRIX *world, int flag, int time);

/* the walls of the drum (an octagon) */
SVECTOR drum_walls[8] = {
    {-500, 0, -250}, {-250, 1000, -500}, {250, 0, -500}, {500, 1000, -250},
    {500, 0, 250}, {250, 1000, 500}, {-250, 0, 500}, {-500, 1000, 250},
};

/* the walls of the broken drum */
SVECTOR drum_broken_walls[4] = {
    {-250, -500, -250}, {250, 500, -250}, {-250, -500, 250}, {250, 500, 250},
};

static void Act(Work *work)
{
    CONTROL *control;
    TARGET  *target;
    OBJECT  *body;
    MATRIX   world;
    HZD_SEG *seg;
    SVECTOR *p1, *p2;
    int      i;
    int      n;
    int      exploded;

    control = &work->control;
    GM_CurrentMap = work->map;
    DG_GetLightMatrix(&control->mov, work->light);

    exploded = 0;
    if (work->state == 0)
    {
        GM_ConfigControlAttribute(control, RADAR_VISIBLE);
    }
    else
    {
        GM_ConfigControlAttribute(control, 0);
    }

    target = work->target;
    if (target->damaged & TARGET_POWER)
    {
        target->damaged &= ~TARGET_POWER;

        if (work->state == 0 && (target->vital < 0 || target->a_mode == 2))
        {
            work->field_1FC = 1;
            work->state = 1;
            target->vital = 255;
            work->hom->flag = 0;
            target->class = TARGET_AVAIL;
        }
    }

    if (work->state != 0)
    {
        if (work->state < 7)
        {
            work->state++;
        }
        else if (work->state == 7)
        {
            body = &work->body;
            work->state = 8;

            GM_FreeObject(body);
            GM_InitObject(body, BODY_MODEL_BROKEN, BODY_FLAG, 0);
            GM_ConfigObjectJoint(body);
            GM_ConfigObjectLight(body, work->light);
            GM_ConfigObjectStep(body, &control->step);

            control->mov.vy = work->height - work->body.objs->def->models[0].ly;
            control->height = -work->body.objs->def->models[0].ly;
            control->grounded = 0;

            seg = work->segs;
            for (n = work->n_segs; n > 0; n--)
            {
                HZD_DequeueDynamicSegment(work->hzd, seg++);
            }

            exploded = 1;
            if (work->proc != 0)
            {
                GCL_ExecProc(work->proc, NULL);
            }

            GM_ConfigControlHazard(control, control->height, 400, 400);

            if (work->has_force == 0)
            {
                control->step.vy = GV_RandU(128) + 150;
                control->step.vx = GV_RandS(128);
                control->step.vz = GV_RandS(128);
            }
            else
            {
                control->step = work->force;
            }

            control->seg_flag = 4;
            work->turn.vx = 0;
            work->turn.vy = GV_RandS(128);
            work->turn.vz = GV_RandS(128);
            work->bouncing = 1;
            work->bounces = 0;
        }
        else if (work->bouncing)
        {
            GV_AddVec3(&work->turn, &control->turn, &control->turn);

            if (control->grounded)
            {
                work->bounces++;
                control->grounded = 0;
                control->step.vy = -control->step.vy / 2;
                control->step.vx = control->step.vx / 2;
                control->step.vz = control->step.vz / 2;

                if (control->step.vy < 20)
                {
                    GM_ConfigControlHazard(control, -1, 0, -1);
                    work->bouncing = 0;
                }
            }

            control->step.vy -= 20;

            if (work->bounces >= 3)
            {
                if (control->rot.vz < 2048)
                {
                    control->turn.vz = 1024;
                }
                else
                {
                    control->turn.vz = 3072;
                }
            }

            control->rot = control->turn;

            world = DG_ZeroMatrix;
            RotMatrixY(control->rot.vy, &world);

            seg = work->segs;
            for (i = 0; i < 4; i++)
            {
                p1 = &drum_broken_walls[i];
                p2 = &drum_broken_walls[(i + 1) & 3];
                world.t[0] = control->mov.vx;
                world.t[1] = control->mov.vy;
                world.t[2] = control->mov.vz;
                THING_Hzd_800C45C4(seg, &world, p1, p2);
                HZD_QueueDynamicSegment2(work->hzd, seg++, 0x144);
            }

            work->n_segs = 4;
        }
    }

    GM_ActControl(control);
    GM_ActObject2(&work->body);

    if (exploded)
    {
        NewBlast(&work->body.objs->world, blast_data_8009F4B8);
        NewDrumSmoke(&work->body.objs->world, 0, 100);
        NewDrumFire(&work->body.objs->world, 0, 55);
        NewDrumSmoke(&work->body.objs->world, 1, 200);
    }

    GM_MoveTarget(target, &work->control.mov);
}

static void Die(Work *work)
{
    HZD_SEG *seg;
    int      i;

    seg = work->segs;
    for (i = work->n_segs; i > 0; i--)
    {
        HZD_DequeueDynamicSegment(work->hzd, seg++);
    }

    GM_ResetHomingTarget(work->hom);
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->body);
    GM_FreeTarget(work->target);
    GM_FreeTarget(work->target2);
}

static void InitTarget(Work *work)
{
    TARGET *target;
    TARGET *target2;
    DG_MDL *mdl;

    work->target = target = GM_AllocTarget();
    work->target2 = target2 = GM_AllocTarget();

    mdl = &work->body.objs->def->models[0];
    work->size.vx = 550;
    work->size.vy = (mdl->uy - mdl->ly) / 2 + 10;
    work->size.vz = 550;

    GM_SetTarget(target, TARGET_POWER | TARGET_SEEK, ENEMY_SIDE, &work->size);
    GM_SetTarget(target2, TARGET_POWER | TARGET_SEEK, PLAYER_SIDE, &work->size);
    GM_SetPowerTarget(target, POWER_DECREASE, -1, 150, 0, &DG_ZeroVector);
    GM_SetPowerTarget(target2, POWER_DECREASE, -1, 150, 0, &DG_ZeroVector);

    work->height = work->control.mov.vy;
    work->control.mov.vy -= mdl->ly;

    GM_MoveTarget(target, &work->control.mov);
    GM_MoveTarget(target2, &work->control.mov);
    target2->class = TARGET_AVAIL;
}

static int GetResources(Work *work, int name, int where)
{
    CONTROL *control;
    OBJECT  *body;
    MATRIX   world;
    HZD_SEG *seg;
    DG_DEF  *def;
    SVECTOR *p1, *p2;
    int      ly, uy;
    int      i;

    control = &work->control;
    if (GM_InitControl(control, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlHazard(control, -1, -2, -1);
    GM_ConfigControlInterp(control, 0);
    GM_ConfigControlString(control, GCL_GetOption('p'), GCL_GetOption('d'));

    work->proc = THING_Gcl_GetInt('e');

    if (GCL_GetOption('f'))
    {
        GCL_StrToSV(GCL_NextStr(), (short *)&work->force);
        work->has_force = 1;
    }

    body = &work->body;
    GM_InitObject(body, BODY_MODEL, BODY_FLAG, 0);
    GM_ConfigObjectLight(body, work->light);

    InitTarget(work);

    work->hom = GM_SetHomingTarget(&work->body.objs->world, control);
    if (work->hom)
    {
        work->hom->flag = 1;
    }

    seg = work->segs;
    work->hzd = GM_GetMap(where)->hzd;

    DG_SetPos2(&control->mov, &control->rot);
    ReadRotMatrix(&world);

    def = work->body.objs->def;
    ly = def->models[0].ly;
    uy = def->models[0].uy;

    for (i = 0; i < 8; i++)
    {
        p1 = &drum_walls[i];
        p2 = &drum_walls[(i + 1) & 7];
        p1->vy = ly;
        p2->vy = uy;
        THING_Hzd_800C45C4(seg, &world, p1, p2);
        HZD_QueueDynamicSegment2(work->hzd, seg++, 0x100);
    }

    work->n_segs = 8;
    work->map = where;
    work->state = 0;
    work->field_1FC = 0;
    work->bouncing = 0;
    return 0;
}

void *NewDrumCan(int name, int where)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "drum.c");
        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return (void *)work;
}
