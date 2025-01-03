#include "common.h"
#include "libgv/libgv.h"
#include "Takabe/thing.h"
#include "Game/linkvarbuf.h"
#include "Game/game.h"
#include "chara/snake/sna_init.h"

typedef struct ElcDamgWork
{
    GV_ACT actor;
    int    where;
    int    name;
    int    field_28;
    int    addend;
    int    field_30;
    int    field_34;
    int    field_38;
    int    proc_id;
} ElcDamgWork;

#define EXEC_LEVEL 5

unsigned short s08a_dword_800C36E0[2] = {HASH_ON2, HASH_OFF2};

// Duplicate of RasenElExecProc_800CD1E4
void ElcDamgExecProc_800D4AAC(int proc, int value)
{
    GCL_ARGS args;
    u_long   data;

    data = value;
    if (proc != 0)
    {
        args.argc = 1;
        args.argv = &data;
        GCL_ExecProc(proc, &args);
    }
}

void ElcDamgAct_800D4AE4(ElcDamgWork *work)
{
    int sum;

    if (THING_Msg_CheckMessage(work->name, 2, s08a_dword_800C36E0) == 0)
    {
        work->field_28 = 0;
        work->field_34 = work->field_30;
        GM_SeSet(NULL, 0xB7);
    }

    if (work->field_34)
    {
        sum = work->field_28 + work->addend;

        GM_SnakeCurrentHealth -= sum >> 8;
        work->field_28 = sum & 0xFF;

        if (GM_SnakeCurrentHealth < 0)
        {
            GM_SnakeCurrentHealth = 0;
        }

        if (--work->field_34 == 0)
        {
            if (GM_SnakeCurrentHealth <= 0 && GM_GameOverTimer == 0 && sna_ration_available_8004FB4C() == 0)
            {
                ElcDamgExecProc_800D4AAC(work->proc_id, 0x1A75);
                GM_GameOver();
            }
            else
            {
                ElcDamgExecProc_800D4AAC(work->proc_id, 0xF95A);
            }
        }
    }
}

void ElcDamgDie_800D4BF4()
{
}

int ElcDamgGetResources_800D4BFC(ElcDamgWork *work, int name, int where)
{
    work->addend = THING_Gcl_GetInt('s');
    work->field_30 = THING_Gcl_GetInt('c');
    work->proc_id = THING_Gcl_GetInt('e');
    work->field_28 = 0;
    work->where = where;
    work->name = name;
    return 0;
}

GV_ACT *NewElcDamg_800D4C68(int name, int where)
{
    ElcDamgWork *work;

    work = (ElcDamgWork *)GV_NewActor(EXEC_LEVEL, sizeof(ElcDamgWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)ElcDamgAct_800D4AE4,
                         (GV_ACTFUNC)ElcDamgDie_800D4BF4, "elc_damg.c");
        if (ElcDamgGetResources_800D4BFC(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
