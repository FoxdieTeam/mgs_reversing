#include "chara/snake/sna_init.h"
#include "libgcl/libgcl.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"

typedef struct _O2DamgeWork
{
    GV_ACT actor;
    int    map;
    int    name;
    int    f28;
    int    f2C;
    int    f30;
    int    f34;
    int    f38;
    int    f3C;
    int    f40;
    int    f44;
    int    f48;
    int    f4C;
    int    f50;
    int    f54;
} O2DamgeWork;

extern int   GM_GameStatus_800AB3CC;
extern int   GM_GameOverTimer_800AB3D4;
extern short GM_O2_800ABA34;
extern int   GM_PlayerStatus_800ABA50;

int THING_Gcl_GetIntDefault(char param, int def);
int THING_Gcl_GetInt(char param);

#define EXEC_LEVEL 5

void ExecProc_800DE580(int proc, long arg)
{
    GCL_ARGS args;
    long     val;

    val = arg;
    if (proc != 0)
    {
        args.argc = 1;
        args.argv = &val;

        GCL_ExecProc_8001FF2C(proc, &args);
    }
}

void O2DamageAct_800DE5B8(O2DamgeWork *work)
{
    GV_MSG *msg;
    int     damage;
    int     var_s3;
    int     count;
    int     reduction;
    int     temp_a0;
    int     temp_v1_2;
    int     temp_s1;

    damage = 0;
    var_s3 = 0;

    count = GV_ReceiveMessage_80016620(work->name, &msg);
    for (; count > 0; count--, msg++)
    {
        switch (msg->message[0])
        {
        case 0x6FE7:
            work->f48 = 1;
            break;

        case 0x92E5:
            work->f48 = 0;
            break;

        case 0x4E29:
            work->f4C = 1;
            break;

        case 0x9A5E:
            work->f4C = 0;
            break;

        case 0xFAA5:
            work->f2C = msg->message[1];
            work->f34 = msg->message[2];
            break;

        case 0xD8E7:
            work->f38 = msg->message[1];
            break;

        case 0x344B:
            work->f3C = msg->message[1];
            break;
        }
    }

    if (GM_GameOverTimer_800AB3D4 == 0)
    {
        if (work->f48 != 0)
        {
            if (GM_CurrentItemId == ITEM_GASMASK)
            {
                reduction = work->f3C;
            }
            else
            {
                reduction = 1;
            }

            temp_a0 = work->f28 + work->f2C / reduction;
            GM_O2_800ABA34 -= temp_a0 >> 12;
            work->f28 = temp_a0 & 0xFFF;

            if (GM_O2_800ABA34 < 0)
            {
                GM_O2_800ABA34 = 0;
                damage = work->f34;
                var_s3 = 1;
            }
        }
        else
        {
            temp_v1_2 = work->f40 + work->f44;
            work->f40 = temp_v1_2 & 0xFFF;
            GM_O2_800ABA34 += temp_v1_2 >> 12;

            if (GM_O2_800ABA34 > 1024)
            {
                GM_O2_800ABA34 = 1024;
            }
        }

        if (work->f4C != 0)
        {
            var_s3 = 1;
            damage += work->f38;
        }

        if (GM_SnakeCurrentHealth > 0)
        {
            temp_s1 = work->f30;
            temp_s1 += damage;
            damage = temp_s1 >> 12;

            if (var_s3 != 0)
            {
                if ((++work->f50 & 0xF) == 0)
                {
                    GM_SeSet_80032858(NULL, 106);
                    GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_26;
                }
            }

            GM_SnakeCurrentHealth -= damage;
            work->f30 = temp_s1 & 0xFFF;

            // "We haven't managed to avoid drowning"
            if ((GM_SnakeCurrentHealth <= 0) && (GM_GameOverTimer_800AB3D4 == 0) && !sna_ration_available_8004FB4C())
            {
                ExecProc_800DE580(work->f54, (GM_PlayerStatus_800ABA50 & PLAYER_GROUND) ? 0xEF61 : 0xB9AA);
                GM_GameOver_8002B6C8();
            }
        }
    }
}

void O2DamageDie_800DE8F4(O2DamgeWork *work)
{
}

int O2DamageGetResources_800DE8FC(O2DamgeWork *work, int name, int where)
{
    if (GCL_GetOption_80020968('o'))
    {
        work->f2C = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->f34 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    work->f38 = THING_Gcl_GetInt('h');
    work->f3C = THING_Gcl_GetIntDefault('m', 1);
    work->f44 = THING_Gcl_GetInt('r');
    work->f54 = THING_Gcl_GetInt('e');

    if (GCL_GetOption_80020968('i'))
    {
        work->f48 = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->f4C = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    work->f30 = 0;
    work->f28 = 0;
    work->f40 = 0;

    return 0;
}

GV_ACT * NewO2Damage_800DE9C8(int name, int where)
{
    O2DamgeWork *work;

    work = (O2DamgeWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(O2DamgeWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)O2DamageAct_800DE5B8, (TActorFunction)O2DamageDie_800DE8F4, "o2_damge.c");

        if (O2DamageGetResources_800DE8FC(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }

        work->map = where;
        work->name = name;
    }

    return &work->actor;
}
