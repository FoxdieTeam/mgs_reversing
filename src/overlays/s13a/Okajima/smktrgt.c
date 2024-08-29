#include "Game/game.h"

typedef struct _SmktrgtWork
{
    GV_ACT  actor;
    TARGET  target[32];
    int     f920;
    int     f924[16];
    int     f964[16];
    int     f9A4[16];
    int     f9E4[16];
    SVECTOR fA24[16];
    SVECTOR fAA4[16];
    int     fB24[16];
    SVECTOR fB64[16];
    SVECTOR fBE4[16];
    SVECTOR fC64[16];
    int     map;
} SmktrgtWork;

extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GM_CurrentMap_800AB9B0;
extern int     GM_PlayerMap_800ABA0C;

SVECTOR s13a_800C36FC = {200, 200, 200, 0};
SVECTOR s13a_800C3704 = {300, 300, 300, 0};

void AN_Unknown_800DC5B4(SVECTOR *pos, SVECTOR *speed, int script);

#define EXEC_LEVEL 4

int s13a_smktrgt_800DBBC0(SmktrgtWork *work)
{
    int i;

    for (i = 0; i < work->f920; i++)
    {
        GM_SetTarget_8002DC74(&work->target[i * 2], TARGET_POWER, NO_SIDE, &s13a_800C36FC);
        GM_Target_8002DCCC(&work->target[i * 2], 0, 3, 32, 0, &DG_ZeroVector_800AB39C);

        GM_SetTarget_8002DC74(&work->target[i * 2 + 1], TARGET_POWER, NO_SIDE, &s13a_800C3704);
        GM_Target_8002DCCC(&work->target[i * 2 + 1], 0, 3, 32, 0, &DG_ZeroVector_800AB39C);
    }

    return 0;
}

int s13a_smktrgt_800DBCB4(char *opt, SVECTOR *out)
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

int s13a_smktrgt_800DBD08(char *opt, int *out)
{
    int   count;
    int  *iter;
    char *res;

    count = 0;
    iter = out;
    while ((res = GCL_Get_Param_Result_80020AA4()) != NULL)
    {
        *iter++ = GCL_StrToInt_800209E8(res);
        count++;
    }

    return count;
}

void s13a_smktrgt_800DBD60(SmktrgtWork *work, int index)
{
    MATRIX  sp10;
    SVECTOR sp30;
    SVECTOR sp38;
    SVECTOR sp40;
    TARGET *target1;
    TARGET *target2;

    target1 = &work->target[index * 2 + 0];
    target2 = &work->target[index * 2 + 1];

    switch (work->f924[index])
    {
    case 0:
        switch (work->f964[index])
        {
        case 0:
            work->f964[index] = 1;

        case 1:
            work->f924[index] = 1;
            work->f964[index] = 1;
            break;
        }
        break;

    case 1:
        switch (work->f964[index])
        {
        case 0:
            if ((GV_RandU_80017090(1024) % work->fB24[index]) != 0)
            {
                break;
            }

            work->f9A4[index] = GV_RandU_80017090(8) + 16;
            work->f964[index] = 1;
            GM_SeSetMode_800329C4(&work->fA24[index], 176, GM_SEMODE_BOMB);

        case 1:
            if (work->f9A4[index] > 0)
            {
                if ((work->f9A4[index] & 0x3) == 0)
                {
                    sp38 = DG_ZeroVector_800AB39C;

                    target2->field_26_hp = 32;
                    GM_MoveTarget_8002D500(target2, &work->fA24[index]);
                    GM_PowerTarget_8002D7DC(target2);

                    AN_Unknown_800DC5B4(&work->fA24[index], &sp38, work->f9E4[index]);
                }
            }
            else if (GV_RandU_80017090(32) >= 5)
            {
                GM_SeSetMode_800329C4(&work->fA24[index], 177, GM_SEMODE_BOMB);

                work->f9A4[index] = 15;
                work->f964[index] = 2;

                sp30.vx = 0;
                sp30.vy = 10;
                sp30.vz = 100;

                sp40.vx = work->fAA4[index].vx + GV_RandS_800170BC(64);
                sp40.vy = work->fAA4[index].vy + GV_RandS_800170BC(64);
                sp40.vz = work->fAA4[index].vz + GV_RandS_800170BC(64);

                RotMatrixYXZ_gte(&sp40, &sp10);
                ApplyMatrixSV(&sp10, &sp30, &sp38);

                work->fC64[index].vx = sp38.vx + GV_RandS_800170BC(8);
                work->fC64[index].vy = sp38.vy + GV_RandS_800170BC(8);
                work->fC64[index].vz = sp38.vz + GV_RandS_800170BC(8);

                work->fB64[index].vx = work->fA24[index].vx + work->fC64[index].vx * 14;
                work->fB64[index].vy = work->fA24[index].vy + work->fC64[index].vy * 14;
                work->fB64[index].vz = work->fA24[index].vz + work->fC64[index].vz * 14;

                work->fBE4[index].vx = work->fA24[index].vx + work->fC64[index].vx * 4;
                work->fBE4[index].vy = work->fA24[index].vy + work->fC64[index].vy * 4;
                work->fBE4[index].vz = work->fA24[index].vz + work->fC64[index].vz * 4;
            }
            else
            {
                work->f964[index] = 0;
            }

            work->f9A4[index]--;
            break;

        case 2:
            if (work->f9A4[index] <= 0)
            {
                work->f9A4[index] = GV_RandU_80017090(64);
                work->f964[index] = 3;
            }
            else
            {
                AN_Unknown_800DC5B4(&work->fA24[index], &work->fC64[index], work->f9E4[index]);
            }

            work->f9A4[index]--;
            break;

        case 3:
            if (work->f9A4[index] <= 0)
            {
                work->f964[index] = 0;
            }
            else
            {
                target2->field_26_hp = 32;
                GM_MoveTarget_8002D500(target2, &work->fB64[index]);
                GM_PowerTarget_8002D7DC(target2);

                target1->field_26_hp = 32;
                GM_MoveTarget_8002D500(target1, &work->fBE4[index]);
                GM_PowerTarget_8002D7DC(target1);

                AN_Unknown_800DC5B4(&work->fA24[index], &work->fC64[index], work->f9E4[index]);
            }

            work->f9A4[index]--;
            break;
        }
        break;

    case 2:
        break;
    }
}

void SmktrgtAct_800DC19C(SmktrgtWork *work)
{
    int i;

    if (work->map & GM_PlayerMap_800ABA0C)
    {
        GM_CurrentMap_800AB9B0 = work->map;

        for (i = 0; i < work->f920; i++)
        {
            s13a_smktrgt_800DBD60(work, i);
        }
    }
}

int SmktrgtGetResources_800DC210(SmktrgtWork *work, int name, int map)
{
    char *opt;
    int i;
    int count;

    work->map = map;
    GM_CurrentMap_800AB9B0 = map;

    opt = GCL_GetOption_80020968('m');
    if (opt != NULL)
    {
        work->f920 = s13a_smktrgt_800DBD08(opt, work->f9E4);
        for (i = 0; i < work->f920; i++)
        {
            if (work->f9E4[i] > 3)
            {
                work->f9E4[i] = 0;
            }
        }
    }

    opt = GCL_GetOption_80020968('c');
    if (opt != NULL)
    {
        count = s13a_smktrgt_800DBCB4(opt, work->fA24);
        if (count < work->f920)
        {
            for (i = count; i < work->f920; i++)
            {
                work->fA24[i] = DG_ZeroVector_800AB39C;
            }
        }
    }

    opt = GCL_GetOption_80020968('v');
    if (opt != NULL)
    {
        count = s13a_smktrgt_800DBCB4(opt, work->fAA4);
        if (count < work->f920)
        {
            for (i = count; i < work->f920; i++)
            {
                work->fAA4[i] = DG_ZeroVector_800AB39C;
            }
        }
    }

    opt = GCL_GetOption_80020968('t');
    if (opt != NULL)
    {
        count = s13a_smktrgt_800DBD08(opt, work->fB24);
        if (count < work->f920)
        {
            for (i = count; i < work->f920; i++)
            {
                work->fB24[i] = 1;
            }
        }
    }

    for (i = 0; i < work->f920; i++)
    {
        work->f924[i] = 0;
        work->f964[i] = 0;
    }

    s13a_smktrgt_800DBBC0(work);
    return 0;
}

int Smktrgt_800DC400(SmktrgtWork *work, int map)
{
    return 0;
}

void SmktrgtDie_800DC408(SmktrgtWork *work)
{
}

GV_ACT * NewSmktrgt_800DC410(int name, int map)
{
    SmktrgtWork *work;

    work = (SmktrgtWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(SmktrgtWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)SmktrgtAct_800DC19C, (TActorFunction)SmktrgtDie_800DC408, "smktrgt.c");

        if (Smktrgt_800DC400(work, map) < 0 || SmktrgtGetResources_800DC210(work, name, map) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }

    return &work->actor;
}
