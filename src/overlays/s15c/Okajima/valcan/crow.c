#include "common.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/object.h"
#include "Game/target.h"
#include "Game/linkvarbuf.h"

typedef struct _CrowEntry
{
    TARGET        *target;
    CONTROL        control;
    OBJECT         body;
    MOTION_CONTROL m_ctrl;
    MOTION_SEGMENT anims[8];
    SVECTOR        rots[14];
    MATRIX         light[2];
    SVECTOR        f384;
    SVECTOR        f38C;
    SVECTOR        f394;
    SVECTOR        f39C;
    SVECTOR        f3A4;
    int            f3AC;
    int            f3B0;
    int            f3B4;
    int            action_flag;
    int            f3BC;
    int            f3C0;
    int            f3C4;
    int            f3C8;
} CrowEntry;

typedef struct _CrowWork
{
    GV_ACT    actor;
    int       map;
    int       n_entries;
    int       f28;
    SVECTOR   f2C;
    SVECTOR   f34;
    SVECTOR   f3C;
    SVECTOR   f44;
    SVECTOR   f4C;
    int       f54;
    int       f58;
    int       f5C;
    int       f60;
    int       f64;
    int       f68;
    CrowEntry entries[0];
} CrowWork;

#define EXEC_LEVEL GV_ACTOR_AFTER

void Crow_800DD7D8(SVECTOR *from, SVECTOR *to, SVECTOR *out)
{
    SVECTOR diff;
    int     y;
    int     len;

    GV_SubVec3(to, from, &diff);

    out->vy = ratan2(diff.vx, diff.vz) & 0xFFF;

    y = diff.vy;
    diff.vy = 0;

    len = GV_VecLen3(&diff);
    out->vx = (ratan2(len, y) & 0xFFF) - 1024;
}

int Crow_800DD854(char *opt, SVECTOR *out)
{
    int   count;
    char *res;

    count = 0;
    while ((res = GCL_GetParamResult()) != NULL)
    {
        GCL_StrToSV(res, out);
        out++;
        count++;
    }

    return count;
}

void Crow_800DD8A8(CrowEntry *entry, int action_flag, int arg2)
{
    if (entry->action_flag != action_flag)
    {
        entry->action_flag = action_flag;
        GM_ConfigObjectAction(&entry->body, action_flag, 0, 4);
    }
    else if (entry->body.is_end == 1)
    {
        entry->f3C4 = arg2;
    }
}

void Crow_800DD900(SVECTOR *a, SVECTOR *b)
{
    int x, y, z;

    if (a->vx > b->vx)
    {
        x = a->vx;
        a->vx = b->vx;
        b->vx = x;
    }

    if (a->vy > b->vy)
    {
        y = a->vy;
        a->vy = b->vy;
        b->vy = y;
    }

    if (a->vz > b->vz)
    {
        z = a->vz;
        a->vz = b->vz;
        b->vz = z;
    }
}

int Crow_800DD968(SVECTOR *arg0, SVECTOR *arg1, SVECTOR *arg2)
{
    if (arg0->vx < arg1->vx || arg2->vx < arg0->vx || arg0->vz < arg1->vz || arg2->vz < arg0->vz)
    {
        return -1;
    }

    return 1;
}

void Crow_800DD9D0(SVECTOR *a, SVECTOR *b, CONTROL *control)
{
    VECTOR vec;
    int    x, y, z;

    x = GV_RandU(64);
    y = GV_RandU(64);
    z = GV_RandU(64);

    vec.vx = ((b->vx - a->vx) * x) >> 6;
    vec.vy = ((b->vy - a->vy) * y) >> 6;
    vec.vz = ((b->vz - a->vz) * z) >> 6;

    control->mov.vx = a->vx + vec.vx;
    control->mov.vy = a->vy + vec.vy;
    control->mov.vz = a->vz + vec.vz;
}

void Crow_800DDAD4(CrowEntry *entry)
{
    SVECTOR *pos;
    SVECTOR *rot;

    pos = &entry->control.mov;
    rot = &entry->control.turn;

    Crow_800DD7D8(pos, &entry->f384, rot);

    DG_SetPos2(&DG_ZeroVector, rot);
    DG_PutVector(&entry->f39C, &entry->f3A4, 1);

    GV_AddVec3(pos, &entry->f3A4, pos);
}

void Crow_800DDB50(CrowWork *work)
{
    int rnd;

    if ((GV_RandU(4096) % work->n_entries) >= work->f28)
    {
        return;
    }

    if (work->f60-- < 0)
    {
        work->f60 = GV_RandU(32) + 20;

        rnd = GV_RandU(4096) % 3;
        if (work->f58 != rnd)
        {
            work->f58 = rnd;
        }
        else
        {
            work->f58 = rnd + 1;
            if (work->f58 >= 3)
            {
                work->f58 = 0;
            }
        }

        GM_SeSet2(GV_RandS(32) & 0xFF, 63, work->f58 + 181);
    }

    if (work->f64-- < 0)
    {
        work->f64 = GV_RandU(16) + 15;

        rnd = GV_RandU(4);
        if (work->f5C != rnd)
        {
            work->f5C = rnd;
        }
        else
        {
            work->f5C = rnd + 1;
            if (work->f5C >= 4)
            {
                work->f5C = 0;
            }
        }

        GM_SeSet2(GV_RandS(32) & 0xFF, 63, work->f5C + 185);
    }
}

void Crow_800DDCD0(CrowEntry *entry)
{
    if ((GM_GameStatus & STATE_STUN) != 0 && entry->f3C8 != 1)
    {
        entry->f3C8 = 1;
        entry->f3C4 = 10;
    }
}

void CrowAct_800DDD08(CrowWork *work)
{
    SVECTOR    svec1;
    SVECTOR    svec2;
    int        time1, time2;
    CrowEntry *entry;
    int        rand2;
    int        rand1;
    int        rand3;
    int        i;

    GM_CurrentMap = work->map;

    Crow_800DDB50(work);

    svec1.vx = 0;
    svec1.vz = 0;

    svec2 = DG_ZeroVector;

    entry = work->entries;

    if (work->f68 == 0)
    {
        work->f68 = 1;

        GM_ActControl(&entry->control);
        GM_ActObject2(&entry->body);

        if (GM_CurrentItemId == ITEM_THERM_G)
        {
            DG_AmbientObjs(entry->body.objs);
        }
        else
        {
            DG_UnAmbientObjs(entry->body.objs);
        }

        DG_GetLightMatrix2(&entry->control.mov, entry->light);
    }

    time1 = GV_Time % work->n_entries;
    time2 = (GV_Time + work->n_entries / 2) % work->n_entries;

    for (i = 0; i < work->n_entries; i++, entry++)
    {
        if (!entry->body.objs[0].bound_mode && i != time1 && i != time2)
        {
            continue;
        }

        entry->f3B0--;
        entry->f3B4++;

        if (entry->f3C8 == 0)
        {
            if (entry->f3C0 == 0)
            {
                GM_MoveTarget(entry->target, &entry->control.mov);
                if (entry->target->damaged & TARGET_POWER)
                {
                    GM_ConfigControlHazard(&entry->control, 50, 50, 50);
                    work->f28--;

                    entry->f39C = entry->target->field_2C_vec;
                    entry->f39C.vx = GV_RandS(64);
                    entry->f39C.vy = GV_RandU(32) + 32;
                    entry->f39C.vz = GV_RandU(64);

                    entry->f3C0 = 1;
                    entry->f3C4 = 3;
                }
            }
        }
        else
        {
            entry->target->damaged |= ~TARGET_POWER;
        }

        switch (entry->f3C4)
        {
        case 0:
            entry->f3B0 = GV_RandU(256) + 30;
            Crow_800DD7D8(&entry->control.mov, &work->f2C, &entry->control.turn);

        case 1:
            entry->f3C4 = 2;
            entry->body.m_ctrl = &entry->m_ctrl;

            rand1 = GV_RandU(8);
            if (rand1 == 0)
            {
                entry->f3BC = 7;
            }
            else if (rand1 >= 0)
            {
                if (rand1 >= 4)
                {
                    entry->f3BC = 6;
                }
                else
                {
                    entry->f3BC = 5;
                }
            }
            else
            {
                entry->f3BC = 6;
            }

            svec2.vz = GV_RandU(4096) + 2000;

            DG_SetPos2(&entry->control.mov, &entry->control.turn);
            DG_PutVector(&svec2, &entry->f394, 1);

            if (Crow_800DD968(&entry->f394, &work->f44, &work->f4C) == -1)
            {
                svec2.vz = 1000;
                DG_SetPos2(&entry->control.mov, &entry->control.turn);
                DG_PutVector(&svec2, &entry->f394, 1);
            }

            entry->f394.vy = entry->control.mov.vy + GV_RandS(2048);
            if (entry->f394.vy < work->f34.vy || work->f3C.vy < entry->f394.vy)
            {
                entry->f394.vy = work->f2C.vy;
            }
            svec1.vy = entry->control.turn.vy;

            if (entry->f3AC == 0)
            {
                svec1.vy += 1024;
            }
            else
            {
                svec1.vy -= 1024;
            }

            svec2.vz = GV_RandU(2048) + 1000;
            DG_SetPos2(&entry->f394, &svec1);
            DG_PutVector(&svec2, &entry->f38C, 1);

            if (Crow_800DD968(&entry->f38C, &work->f44, &work->f4C) == -1)
            {
                svec2.vz = 1000;
                DG_SetPos2(&entry->f394, &svec1);
                DG_PutVector(&svec2, &entry->f38C, 1);
            }
            else if (GV_DiffVec3(&entry->control.mov, &work->f2C) < 3500)
            {
                entry->f3AC = 1 - entry->f3AC;
            }

            entry->f39C.vz = GV_RandU(64) + 100;

        case 2:
            if (GV_DiffVec3(&entry->control.mov, &entry->f38C) < 1000)
            {
                entry->f3C4 = 1;
            }
            entry->f384.vx = (entry->f394.vx * 7 + entry->f38C.vx) >> 3;
            entry->f384.vy = (entry->f394.vy * 7 + entry->f38C.vy) >> 3;
            entry->f384.vz = (entry->f394.vz * 7 + entry->f38C.vz) >> 3;
            entry->f394 = entry->f384;
            Crow_800DDAD4(entry);
            Crow_800DD8A8(entry, entry->f3BC, 2);
            Crow_800DDCD0(entry);
            break;

        case 3:
            entry->f3C4 = 4;
            GM_ConfigControlHazard(&entry->control, 50, 50, 50);
            GM_SeSet2(0, 0x3F, 184);
            work->f60 = 0;
            work->f64 = 0;
            break;

        case 4:
            GV_AddVec3(&entry->control.mov, &entry->f39C, &entry->control.mov);

            entry->control.turn.vx += 164;
            entry->control.turn.vy += 284;
            entry->control.turn.vz += 394;

            entry->f39C.vx = entry->f39C.vx * 15 / 16;
            entry->f39C.vy -= 3;
            entry->f39C.vz = entry->f39C.vz * 15 / 16;

            Crow_800DD8A8(entry, 4, 4);

            if (work->f60-- < 0)
            {
                work->f60 = GV_RandU(4) + 4;
                rand3 = GV_RandU(4);
                if (work->f58 != rand3)
                {
                    work->f58 = rand3;
                }
                else if (++work->f58 >= 4)
                {
                    work->f58 = 0;
                }
                GM_SeSet2(GV_RandS(32), 63, work->f58 + 181);
            }

            if (work->f64-- < 0)
            {
                work->f64 = GV_RandU(4) + 4;
                rand3 = GV_RandU(4);
                if (work->f5C != rand3)
                {
                    work->f5C = rand3;
                }
                else if (++work->f5C >= 4)
                {
                    work->f5C = 0;
                }
                GM_SeSet2(0, 63, work->f5C + 185);
            }

            if (entry->control.field_57 || entry->control.mov.vy < -20000)
            {
                entry->f3C4 = 5;
            }

            break;

        case 5:
            entry->f3B0 = 60;
            entry->f3C4 = 6;
            if (work->f54 != -1)
            {
                GCL_ExecProc(work->f54, NULL);
            }

        case 6:
            if (entry->f3B0 % 4 < 2)
            {
                DG_InvisibleObjs(entry->body.objs);
            }
            else
            {
                DG_VisibleObjs(entry->body.objs);
            }

            if (entry->f3B0 < 0)
            {
                entry->f3C4 = 7;
            }
            break;

        case 7:
            GM_ConfigControlHazard(&entry->control, -1, -2, -1);
            DG_InvisibleObjs(entry->body.objs);
            entry->f3C4 = 8;
            break;

        case 8:
            entry->f3C4 = 9;
            break;

        case 10:
            entry->f3C4 = 0xB;
            GM_ConfigControlHazard(&entry->control, 50, 50, 50);
            entry->f39C.vy = GV_RandU(64) + 4;
            work->f60 = 0;
            work->f64 = 0;

        case 11:
            GV_AddVec3(&entry->control.mov, &entry->f39C, &entry->control.mov);

            entry->control.turn.vx += 164;
            entry->control.turn.vy += 284;
            entry->control.turn.vz += 394;

            entry->f39C.vx = entry->f39C.vx * 15 / 16;
            entry->f39C.vy -= 3;
            entry->f39C.vz = entry->f39C.vz * 15 / 16;

            Crow_800DD8A8(entry, 4, 11);

            if (work->f60-- < 0)
            {
                work->f60 = GV_RandU(8) + 10;
                rand2 = GV_RandU(4);

                if (work->f58 != rand2)
                {
                    work->f58 = rand2;
                }
                else if (++work->f58 >= 4)
                {
                    work->f58 = 0;
                }

                GM_SeSet2(GV_RandS(32), 63, work->f58 + 181);
            }

            if (work->f64-- < 0)
            {
                work->f64 = GV_RandU(4) + 4;
                rand2 = GV_RandU(4);

                if (work->f5C != rand2)
                {
                    work->f5C = rand2;
                }
                else if (++work->f5C >= 4)
                {
                    work->f5C = 0;
                }

                GM_SeSet2(GV_RandS(32), 63, work->f5C + 185);
            }

            if (entry->control.field_57 != 0 || entry->control.mov.vy < -20000)
            {
                entry->control.field_57 = 0;

                GM_ConfigControlHazard(&entry->control, -1, -2, -1);

                entry->f3C4 = 12;
                entry->f3B0 = GV_RandU(128) + 60;

                entry->control.turn.vx = 0;
                entry->control.turn.vz = 0;
            }
            break;

        case 12:
            Crow_800DD8A8(entry, 9, 12);
            if (entry->f3B0 < 0 && !(GM_GameStatus & STATE_STUN))
            {
                entry->f3C8 = 0;
                entry->f3C4 = 0;
                entry->f39C = DG_ZeroVector;
            }
            break;
        }

        if (entry->f3C4 != 9)
        {
            GM_ActControl(&entry->control);
            GM_ActObject2(&entry->body);

            if (GM_CurrentItemId == ITEM_THERM_G)
            {
                DG_AmbientObjs(entry->body.objs);
            }
            else
            {
                DG_UnAmbientObjs(entry->body.objs);
            }

            DG_GetLightMatrix2(&entry->control.mov, entry->light);
        }
    }
}

int Crow_800DE890(CrowWork *work, int name, int map)
{
    SVECTOR    size;
    int        i;
    CrowEntry *entry;
    TARGET    *target;

    GM_GetMap(work->map);

    for (i = 0; i < work->n_entries; i++)
    {
        entry = &work->entries[i];

        target = GM_AllocTarget();
        entry->target = target;

        if (target != NULL)
        {
            size.vx = 50;
            size.vy = 50;
            size.vz = 50;
            GM_SetTarget(target, TARGET_SEEK | TARGET_POWER, ENEMY_SIDE, &size);
        }

        entry->f3C0 = 0;
    }

    return 0;
}

int Crow_800DE93C(CrowWork *work, int name, int map)
{
    char    *opt;
    int      i;
    CONTROL *control;
    OBJECT  *body;

    opt = GCL_GetOption('i');
    if (opt != NULL)
    {
        work->f54 = GCL_StrToInt(opt);
    }
    else
    {
        work->f54 = -1;
    }

    opt = GCL_GetOption('s');
    if (opt != NULL)
    {
        Crow_800DD854(opt, &work->f34);
        Crow_800DD900(&work->f34, &work->f3C);

        work->f44 = work->f34;
        work->f4C = work->f3C;

        work->f4C.vy = work->f34.vy;

        work->f2C.vx = (work->f34.vx + work->f3C.vx) / 2;
        work->f2C.vy = (work->f34.vy + work->f3C.vy) / 2;
        work->f2C.vz = (work->f34.vz + work->f3C.vz) / 2;
    }

    work->map = map;

    for (i = 0; i < work->n_entries; i++)
    {
        control = &work->entries[i].control;
        if (GM_InitControl(control, name, map) < 0)
        {
            return -1;
        }

        GM_ConfigControlAttribute(control, 0);
        GM_ConfigControlHazard(control, -1, -2, -1);
        GM_ConfigControlInterp(control, 4);

        control->step = DG_ZeroVector;

        body = &work->entries[i].body;
        GM_InitObject(body, GV_StrCode("crow"), 0x22D, GV_StrCode("crow"));
        GM_ConfigObjectJoint(body);
        GM_ConfigObjectLight(body, work->entries[i].light);

        DG_VisibleObjs(work->entries[i].body.objs);

        GM_ConfigMotionControl(body, &work->entries[i].m_ctrl, GV_StrCode("crow"),
                               work->entries[i].anims, NULL, control, work->entries[i].rots);
        GM_ConfigObjectAction(body, 0, 0, 0);

        work->entries[i].f3B4 = GV_RandU(4096);
        work->entries[i].f3C4 = 0;

        Crow_800DD9D0(&work->f34, &work->f3C, control);

        control->rot.vx = 0;
        control->rot.vy = GV_RandU(4096);
        control->rot.vz = 0;
        control->turn = control->rot;

        work->entries[i].f3AC = GV_RandU(2);
        work->entries[i].f3C8 = 0;
    }

    work->f58 = 0;
    work->f5C = GV_RandU(4);
    work->f60 = GV_RandU(64) + 20;
    work->f64 = GV_RandU(64) + 20;
    work->f68 = 0;

    return 0;
}

void CrowDie_800DEC78(CrowWork *work)
{
    int i;

    for (i = 0; i < work->n_entries; i++)
    {
        GM_FreeObject(&work->entries[i].body);
        GM_FreeControl(&work->entries[i].control);
        GM_FreeTarget(work->entries[i].target);
    }
}

GV_ACT *NewCrow_800DED08(int name, int where)
{
    CrowWork *work;
    char     *opt;
    int       n_entries;

    opt = GCL_GetOption('n');
    if (opt != NULL)
    {
        n_entries = GCL_StrToInt(opt);
        if (n_entries > 24)
        {
            n_entries = 24;
        }
    }
    else
    {
        n_entries = 1;
    }

    work = GV_NewActor(EXEC_LEVEL, sizeof(CrowWork) + sizeof(CrowEntry) * n_entries);
    if (work != NULL)
    {
        work->n_entries = n_entries;
        work->f28 = n_entries;

        GV_SetNamedActor(&work->actor, CrowAct_800DDD08, CrowDie_800DEC78, "crow.c");

        if (Crow_800DE93C(work, name, where) < 0 || Crow_800DE890(work, name, where) < 0)
        {
            do
            {
                GV_DestroyActor(&work->actor);
                return NULL;
            } while (0);
        }
    }

    return &work->actor;
}
