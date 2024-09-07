#include "libgv/libgv.h"
#include "libhzd/libhzd.h"
#include "Game/game.h"
#include "Game/object.h"
#include "Takabe/thing.h"
#include "SD/g_sound.h"

typedef struct _ShuterWork
{
    GV_ACT   actor;
    int      map;
    int      name;
    OBJECT   object;
    HZD_HDL *hzd;
    HZD_FLR  floor;
    HZD_SEG  seg[2];
    SVECTOR  pos;
    SVECTOR  raised_pos;
    SVECTOR  rot;
    TARGET  *target;
    SVECTOR  target_size;
    int      f184;
    int      level;
    int      hzd_height;
    int      max_level;
    int      speed;
    int      f198;
    int      f19C;
    int      raise;
    int      delay;
    int      open;
    int      alert;
    SVECTOR  center;
    int      sound_timer;
    int      open_proc;
    int      close_proc;
    int      moving;
} ShuterWork;

unsigned short shuter_msgs_800C3738[] = {0x418B, 0x3A02};

extern int GM_CurrentMap_800AB9B0;
extern int GM_AlertMode_800ABA00;

DG_OBJS * s00a_unknown3_800DC7BC(int model, LitHeader *lit);
void      Takabe_FreeObjs_800DC820(DG_OBJS *objs);

void Shuter_800DFBD8(ShuterWork *);
void Shuter_800DFC30(ShuterWork *work);
void Shuter_800DFC84(ShuterWork *);
void Shuter_800DFD7C(ShuterWork *);
void Shuter_800DFDD0(ShuterWork *work);
void Shuter_800DFE24(ShuterWork *work);
void Shuter_800DFF34(OBJECT *, int, int);

#define EXEC_LEVEL 5

void ShuterAct_800DF484(ShuterWork *work)
{
    int found;

    GM_CurrentMap_800AB9B0 = work->map;

    found = THING_Msg_CheckMessage(work->name, 2, shuter_msgs_800C3738);
    if (found == 0 && work->open != 1)
    {
        if (work->open == 0)
        {
            work->moving = 1;
        }

        work->open = 1;
        work->delay = 5;
        sub_80032BC4(&work->center, SE_SHUTTER_CLOSE2, 2000);

        printf("open\n");
    }
    else if (found == 1 && work->open != 0)
    {
        if (work->open == 1)
        {
            work->moving = 1;
        }

        work->open = 0;
        work->delay = 5;
        sub_80032BC4(&work->center, SE_SHUTTER_CLOSE2, 2000);

        printf("close\n");
    }

    if (work->alert != 0)
    {
        if (GM_AlertMode_800ABA00 == 3 && work->open == 1)
        {
            work->open = 0;
            work->moving = 1;
            work->delay = 5;
            sub_80032BC4(&work->center, SE_SHUTTER_CLOSE2, 2000);
        }
        else if (GM_AlertMode_800ABA00 == 0 && work->open == 0)
        {
            work->open = 1;
            work->moving = 1;
            work->delay = 5;
            sub_80032BC4(&work->center, SE_SHUTTER_CLOSE2, 2000);
        }
    }

    if (work->delay != 0)
    {
        work->delay--;
    }
    else
    {
        switch (work->open)
        {
        case 0:
            work->level = GV_NearSpeed(work->level, 0, work->speed);
            if (work->level == 0 && work->moving != 0)
            {
                if (work->open_proc != 0)
                {
                    GCL_ExecProc(work->open_proc, NULL);
                }

                sub_80032BC4(&work->center, SE_SHUTTER_CLOSE, 2000);
                work->moving = 0;
            }
            else if (work->moving != 0)
            {
                if (++work->sound_timer >= 14)
                {
                    work->sound_timer = 0;
                }

                if (work->sound_timer == 0)
                {
                    sub_80032BC4(&work->center, SE_SHUTTER_CLOSING, 2000);
                }
            }
            break;

        case 1:
            work->level = GV_NearSpeed(work->level, work->max_level, work->speed);
            if (work->level == work->max_level && work->moving != 0)
            {
                if (work->close_proc != 0)
                {
                    GCL_ExecProc(work->close_proc, NULL);
                }

                sub_80032BC4(&work->center, SE_SHUTTER_CLOSE, 2000);
                work->moving = 0;
            }
            else if (work->moving != 0)
            {
                if (++work->sound_timer >= 14)
                {
                    work->sound_timer = 0;
                }

                if (work->sound_timer == 0)
                {
                    sub_80032BC4(&work->center, SE_SHUTTER_CLOSING, 2000);
                }
            }
            break;
        }
    }

    Shuter_800DFE24(work);

    DG_SetPos2(&work->raised_pos, &work->rot);
    GM_ActObject2(&work->object);

    work->target->center.vx = work->center.vx;
    work->target->center.vz = work->center.vz;
    work->target->center.vy = work->level + (work->center.vy - (work->hzd_height / 2)) + 250;
}

void ShuterDie_800DF774(ShuterWork *work)
{
    Shuter_800DFDD0(work);
    Shuter_800DFC30(work);
    GM_FreeTarget(work->target);
    Takabe_FreeObjs_800DC820(work->object.objs);
}

void Shuter_800DF7B8(ShuterWork *work)
{
    work->target = GM_AllocTarget();
    GM_SetTarget(work->target, 8, NO_SIDE, &work->target_size);
}

int ShuterGetResources_800DF7F4(ShuterWork *work, int name, int map)
{
    MATRIX   world;
    SVECTOR  max;
    SVECTOR  min;
    SVECTOR *pos;
    SVECTOR *rot;
    OBJECT  *object;
    int      model;
    DG_MDL  *mdl;

    GM_CurrentMap_800AB9B0 = map;

    work->map = map;
    work->name = name;

    work->f198 = 0;

    work->hzd = Map_FromId_800314C0(map)->hzd;

    pos = &work->pos;
    THING_Gcl_GetSVector('p', pos);

    rot = &work->rot;
    THING_Gcl_GetSVector('d', rot);

    work->alert = THING_Gcl_GetInt('a');
    work->raise = THING_Gcl_GetInt('r');
    work->speed = THING_Gcl_GetIntDefault('s', 20);
    work->max_level = THING_Gcl_GetInt('h');
    work->open = THING_Gcl_GetInt('o');

    if (GCL_GetOption('e'))
    {
        work->open_proc = GCL_StrToInt(GCL_GetParamResult());
        work->close_proc = GCL_StrToInt(GCL_GetParamResult());
    }

    DG_SetPos2(pos, rot);

    object = &work->object;

    model = THING_Gcl_GetShort('m');
    if (model == 0)
    {
        return -1;
    }

    Shuter_800DFF34(object, model, 0x57);

    mdl = work->object.objs->def->model;

    work->hzd_height = mdl->max.vy - mdl->min.vy;

    max.vx = mdl->min.vx;
    max.vy = mdl->min.vy;

    min.vx = mdl->max.vx;
    min.vy = mdl->max.vy;

    DG_SetPos2(pos, rot);
    ReadRotMatrix(&world);

    max.vz = min.vz = mdl->max.vz;
    s16b_800C45C4(&work->seg[0], &world, &max, &min);

    max.vz = min.vz = mdl->min.vz;
    s16b_800C45C4(&work->seg[1], &world, &max, &min);

    work->center.vx = (mdl->max.vx + mdl->min.vx) / 2;
    work->center.vy = (mdl->max.vy + mdl->min.vy) / 2;
    work->center.vz = (mdl->max.vz + mdl->min.vz) / 2;
    DG_PutVector(&work->center, &work->center, 1);

    work->target_size.vx = (mdl->max.vx - mdl->min.vx) / 2;
    work->target_size.vz = (mdl->max.vz - mdl->min.vz) / 2 - 100;
    work->target_size.vy = 200;

    if (work->alert != 0)
    {
        work->seg[0].p1.h -= 250;
        work->seg[0].p2.h -= 250;
        work->seg[1].p1.h -= 250;
        work->seg[1].p2.h -= 250;
    }

    Shuter_800DFC84(work);
    Shuter_800DFD7C(work);
    Shuter_800DFBD8(work);

    work->raised_pos = work->pos;
    work->f184 = 0;
    work->f19C = 0;
    work->moving = 0;

    if (work->max_level == 0)
    {
        work->max_level = work->hzd_height;
    }

    if (work->open == 0)
    {
        work->level = 0;
    }
    else
    {
        work->level = work->max_level;
    }

    Shuter_800DF7B8(work);

    object->objs->objs->raise = work->raise;
    return 0;
}

GV_ACT * NewShuter_800DFB44(int name, int where, int argc, char **argv)
{
    ShuterWork *work;

    work = (ShuterWork *)GV_NewActor(EXEC_LEVEL, sizeof(ShuterWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (TActorFunction)ShuterAct_800DF484, (TActorFunction)ShuterDie_800DF774, "shuter.c");

        if (ShuterGetResources_800DF7F4(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}

void Shuter_800DFBD8(ShuterWork *work)
{
    HZD_SEG *seg;
    int      i;

    seg = work->seg;
    for (i = 2; i > 0; i--)
    {
        HZD_QueueDynamicSegment2_8006FDDC(work->hzd, seg, 0x110);
        seg++;
    }
}

void Shuter_800DFC30(ShuterWork *work)
{
    HZD_SEG *seg;
    int      i;

    seg = work->seg;
    for (i = 2; i > 0; i--)
    {
        HZD_DequeueDynamicSegment_8006FE44(work->hzd, seg++);
    }
}

void Shuter_800DFC84(ShuterWork *work)
{
    HZD_SEG *seg;
    HZD_VEC *vec;
    int      xmax, zmax;
    int      xmin, zmin;
    HZD_FLR *floor;
    int      i;

    seg = work->seg;
    vec = &work->floor.p1;

    xmax = -32000;
    zmax = -32000;
    xmin = 32000;
    zmin = 32000;

    work->floor.p1 = work->seg[0].p1;
    work->floor.p2 = work->seg[0].p2;
    work->floor.p3 = work->seg[1].p2;
    work->floor.p4 = work->seg[1].p1;

    floor = &work->floor;
    floor->p1.h = 0;
    floor->p2.h = 0;
    floor->p3.h = 256;

    for (i = 4; i > 0; i--)
    {
        if (vec->x > xmax)
        {
            xmax = vec->x;
        }

        if (vec->z > zmax)
        {
            zmax = vec->z;
        }

        if (vec->x < xmin)
        {
            xmin = vec->x;
        }

        if (vec->z < zmin)
        {
            zmin = vec->z;
        }

        vec++;
    }

    floor->b1.x = xmin;
    floor->b1.z = zmin;
    floor->b2.x = xmax;
    floor->b2.z = zmax;
    floor->b1.y = seg->p1.y - 100;
    floor->b2.y = seg->p1.y + 100;
}

void Shuter_800DFD7C(ShuterWork *work)
{
    HZD_FLR *floor;
    int      i;

    floor = &work->floor;
    for (i = 1; i > 0; i--)
    {
        HZD_QueueDynamicFloor_8006FF9C(work->hzd, floor);
        floor++;
    }
}

void Shuter_800DFDD0(ShuterWork *work)
{
    HZD_FLR *floor;
    int      i;

    floor = &work->floor;
    for (i = 1; i > 0; i--)
    {
        HZD_DequeueDynamicFloor_8006FFE8(work->hzd, floor);
        floor++;
    }
}

void Shuter_800DFE24(ShuterWork *work)
{
    SVECTOR diff;
    SVECTOR pos;
    int     height;

    pos = work->pos;
    pos.vy += work->level;

    GV_SubVec3(&pos, &work->raised_pos, &diff);

    work->raised_pos = pos;

    work->seg[0].p1.y += diff.vy;
    work->seg[0].p2.y += diff.vy;
    work->seg[1].p1.y += diff.vy;
    work->seg[1].p2.y += diff.vy;

    if (work->level > 750 && work->level < 1250)
    {
        height = work->pos.vy + 1250;
    }
    else
    {
        height = work->pos.vy + work->level;
    }

    work->floor.p1.y = height;
    work->floor.p2.y = height;
    work->floor.p3.y = height;
    work->floor.p4.y = height;
    work->floor.b1.y = height;
    work->floor.b2.y = height;
}

void Shuter_800DFF34(OBJECT *object, int model, int flag)
{
    GV_ZeroMemory(object, sizeof(OBJECT));

    object->flag = flag;
    object->map_name = GM_CurrentMap_800AB9B0;
    object->objs = s00a_unknown3_800DC7BC(model, Map_FromId_800314C0(GM_CurrentMap_800AB9B0)->lit);
}
