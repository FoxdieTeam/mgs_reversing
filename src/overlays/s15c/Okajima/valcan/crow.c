#include "Game/control.h"
#include "Game/game.h"
#include "Game/object.h"
#include "Game/target.h"

typedef struct _CrowEntry
{
    TARGET        *target;
    CONTROL        control;
    OBJECT         body;
    MOTION_CONTROL m_ctrl;
    OAR_RECORD     anims[8];
    SVECTOR        rots[14];
    MATRIX         light[2];
    SVECTOR        f384;
    char           pad1[0x10];
    SVECTOR        f39C;
    SVECTOR        f3A4;
    int            f3AC;
    char           pad2[0x4];
    int            f3B4;
    int            action_flag;
    char           pad3[0x4];
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

extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GM_GameStatus_800AB3CC;

#define EXEC_LEVEL 6

void Crow_800DD7D8(SVECTOR *from, SVECTOR *to, SVECTOR *out)
{
    SVECTOR diff;
    int     y;
    int     len;

    GV_SubVec3_80016D40(to, from, &diff);

    out->vy = ratan2(diff.vx, diff.vz) & 0xFFF;

    y = diff.vy;
    diff.vy = 0;

    len = GV_VecLen3_80016D80(&diff);
    out->vx = (ratan2(len, y) & 0xFFF) - 1024;
}

int Crow_800DD854(char *opt, SVECTOR *out)
{
    int   count;
    char *res;

    count = 0;
    while ((res = GCL_Get_Param_Result_80020AA4()) != NULL)
    {
        GCL_StrToSV_80020A14(res, out);
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
        GM_ConfigObjectAction_80034CD4(&entry->body, action_flag, 0, 4);
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

    x = GV_RandU_80017090(64);
    y = GV_RandU_80017090(64);
    z = GV_RandU_80017090(64);

    vec.vx = ((b->vx - a->vx) * x) >> 6;
    vec.vy = ((b->vy - a->vy) * y) >> 6;
    vec.vz = ((b->vz - a->vz) * z) >> 6;

    control->field_0_mov.vx = a->vx + vec.vx;
    control->field_0_mov.vy = a->vy + vec.vy;
    control->field_0_mov.vz = a->vz + vec.vz;
}

void Crow_800DDAD4(CrowEntry *entry)
{
    SVECTOR *pos;
    SVECTOR *rot;

    pos = &entry->control.field_0_mov;
    rot = &entry->control.field_4C_turn;

    Crow_800DD7D8(pos, &entry->f384, rot);

    DG_SetPos2_8001BC8C(&DG_ZeroVector_800AB39C, rot);
    DG_PutVector_8001BE48(&entry->f39C, &entry->f3A4, 1);

    GV_AddVec3_80016D00(pos, &entry->f3A4, pos);
}

void Crow_800DDB50(CrowWork *work)
{
    int rnd;

    if ((GV_RandU_80017090(4096) % work->n_entries) >= work->f28)
    {
        return;
    }

    if (work->f60-- < 0)
    {
        work->f60 = GV_RandU_80017090(32) + 20;

        rnd = GV_RandU_80017090(4096) % 3;
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

        GM_SeSet2_80032968(GV_RandS_800170BC(32) & 0xFF, 63, work->f58 + 181);
    }

    if (work->f64-- < 0)
    {
        work->f64 = GV_RandU_80017090(16) + 15;

        rnd = GV_RandU_80017090(4);
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

        GM_SeSet2_80032968(GV_RandS_800170BC(32) & 0xFF, 63, work->f5C + 185);
    }
}

void Crow_800DDCD0(CrowEntry *entry)
{
    if ((GM_GameStatus_800AB3CC & GAME_FLAG_BIT_02) != 0 && entry->f3C8 != 1)
    {
        entry->f3C8 = 1;
        entry->f3C4 = 10;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s15c/s15c_crow_800DDD08.s")
void s15c_crow_800DDD08(CrowWork *work); // CrowAct

int Crow_800DE890(CrowWork *work, int name, int map)
{
    SVECTOR    size;
    int        i;
    CrowEntry *entry;
    TARGET    *target;

    Map_FromId_800314C0(work->map);

    for (i = 0; i < work->n_entries; i++)
    {
        entry = &work->entries[i];

        target = GM_AllocTarget_8002D400();
        entry->target = target;

        if (target != NULL)
        {
            size.vx = 50;
            size.vy = 50;
            size.vz = 50;
            GM_SetTarget_8002DC74(target, TARGET_SEEK | TARGET_POWER, ENEMY_SIDE, &size);
        }

        entry->f3C0 = 0;
    }

    return 0;
}

int Crow_800DE93C(CrowWork *work, int name, int map)
{
    int        opt;
    int        i;
    CONTROL   *control;
    OBJECT    *body;

    opt = GCL_GetOption_80020968('i');
    if (opt != NULL)
    {
        work->f54 = GCL_StrToInt_800209E8((char *)opt);
    }
    else
    {
        work->f54 = -1;
    }

    opt = GCL_GetOption_80020968('s');
    if (opt != NULL)
    {
        Crow_800DD854((char *)opt, &work->f34);
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
        if (GM_InitLoader_8002599C(control, name, map) < 0)
        {
            return -1;
        }

        GM_ConfigControlAttribute_8002623C(control, 0);
        GM_ConfigControlHazard_8002622C(control, -1, -2, -1);
        GM_ConfigControlInterp_80026244(control, 4);

        control->field_44_step = DG_ZeroVector_800AB39C;

        body = &work->entries[i].body;
        GM_InitObject_80034A18(body, GV_StrCode_80016CCC("crow"), 0x22D, GV_StrCode_80016CCC("crow"));
        GM_ConfigObjectJoint_80034CB4(body);
        GM_ConfigObjectLight_80034C44(body, work->entries[i].light);

        DG_VisibleObjs(work->entries[i].body.objs);

        GM_ConfigMotionControl_80034F08(body, &work->entries[i].m_ctrl, GV_StrCode_80016CCC("crow"), work->entries[i].anims, NULL, control, work->entries[i].rots);
        GM_ConfigObjectAction_80034CD4(body, 0, 0, 0);

        work->entries[i].f3B4 = GV_RandU_80017090(4096);
        work->entries[i].f3C4 = 0;

        Crow_800DD9D0(&work->f34, &work->f3C, control);

        control->field_8_rot.vx = 0;
        control->field_8_rot.vy = GV_RandU_80017090(4096);
        control->field_8_rot.vz = 0;
        control->field_4C_turn = control->field_8_rot;

        work->entries[i].f3AC = GV_RandU_80017090(2);
        work->entries[i].f3C8 = 0;
    }

    work->f58 = 0;
    work->f5C = GV_RandU_80017090(4);
    work->f60 = GV_RandU_80017090(64) + 20;
    work->f64 = GV_RandU_80017090(64) + 20;
    work->f68 = 0;

    return 0;
}

void CrowDie_800DEC78(CrowWork *work)
{
    int i;

    for (i = 0; i < work->n_entries; i++)
    {
        GM_FreeObject_80034BF8(&work->entries[i].body);
        GM_FreeControl_800260CC(&work->entries[i].control);
        GM_FreeTarget_8002D4B0(work->entries[i].target);
    }
}

GV_ACT * NewCrow_800DED08(int name, int where)
{
    CrowWork *work;
    int       opt;
    int       n_entries;

    opt = GCL_GetOption_80020968('n');
    if (opt != NULL)
    {
        n_entries = GCL_StrToInt_800209E8((char *)opt);
        if (n_entries > 24)
        {
            n_entries = 24;
        }
    }
    else
    {
        n_entries = 1;
    }

    work = (CrowWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(CrowWork) + sizeof(CrowEntry) * n_entries);
    if (work != NULL)
    {
        work->n_entries = n_entries;
        work->f28 = n_entries;

        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s15c_crow_800DDD08, (TActorFunction)CrowDie_800DEC78, "crow.c");

        if (Crow_800DE93C(work, name, where) < 0 || Crow_800DE890(work, name, where) < 0)
        {
            do
            {
                GV_DestroyActor_800151C8(&work->actor);
                return NULL;
            } while (0);
        }
    }

    return &work->actor;
}
