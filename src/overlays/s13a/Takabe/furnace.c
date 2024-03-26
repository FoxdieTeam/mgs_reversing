#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "Takabe/thing.h"

typedef struct FurnaceWork
{
    GV_ACT  actor;
    int     where;
    int     name;
    SVECTOR bound[2];
    CVECTOR color;
    int     proc_id;
} FurnaceWork;

#define EXEC_LEVEL 5

extern CONTROL *GM_PlayerControl_800AB9F4;
extern int      GM_GameOverTimer_800AB3D4;
extern CONTROL *GM_WhereList_800B56D0[96];
extern int      gControlCount_800AB9B4;
extern int      tenage_ctrls_count_800BDD70;
extern CONTROL *tenage_ctrls_800BDD30[16];
extern int      dword_8009F49C;
extern int      amissile_alive_8009F490;
extern SVECTOR  svector_8009F494;

GV_ACT *NewMeltDie_800E0F5C(SVECTOR *arg1, int arg2);
GV_ACT *NewWaterView_800DBE04(int name, int where, SVECTOR *arg2, CVECTOR *color);

// Duplicate of WaterArea2BoundInCheck_800CEA48
int FurnaceBoundInCheck_800E08AC(SVECTOR *bound, SVECTOR *check)
{
    if (!(check->vx <= bound[0].vx))
    {
        if (check->vx < bound[1].vx)
        {
            if (!(check->vy <= bound[0].vy))
            {
                if (check->vy < bound[1].vy)
                {
                    if (!(check->vz <= bound[0].vz))
                    {
                        if (!(check->vz >= bound[1].vz))
                        {
                            return 1;
                        }
                    }
                }
            }
        }
    }

    return 0;
}

// Duplicate of RasenElExecProc_800CD1E4
void FurnaceExecProc_800E093C(int proc, int value)
{
    GCL_ARGS args;
    u_long   data;

    data = value;
    if (proc != 0)
    {
        args.argc = 1;
        args.argv = &data;
        GCL_ExecProc_8001FF2C(proc, &args);
    }
}

void FurnaceAct_800E0974(FurnaceWork *work)
{
    SVECTOR   svec;
    CONTROL **wherelist;
    CONTROL **tenage;
    int       inbounds;
    int       i;

    inbounds = FurnaceBoundInCheck_800E08AC(work->bound, &GM_PlayerControl_800AB9F4->field_0_mov);
    if (GM_GameOverTimer_800AB3D4 == 0 && inbounds)
    {
        svec = GM_PlayerControl_800AB9F4->field_0_mov;
        svec.vy = work->bound[1].vy;

        NewMeltDie_800E0F5C(&svec, 60);

        GM_SeSet_80032858(&svec, 186);
        GM_SetNoise(100, 2, &svec);

        GM_SnakeCurrentHealth = 0; // :(

        FurnaceExecProc_800E093C(work->proc_id, 0);
        GM_GameOver_8002B6C8();
    }

    for (wherelist = GM_WhereList_800B56D0, i = gControlCount_800AB9B4; i > 0; i--, wherelist++)
    {
        if (((*wherelist)->field_2C_map->field_0_map_index_bit & work->where) &&
            !((*wherelist)->field_55_skip_flag & 2) && (*wherelist)->field_30_scriptData >= 64)
        {
            svec = (*wherelist)->field_0_mov;
            svec.vy += (*wherelist)->field_44_step.vy;
            if (!FurnaceBoundInCheck_800E08AC(work->bound, &(*wherelist)->field_0_mov) &&
                FurnaceBoundInCheck_800E08AC(work->bound, &svec))
            {
                GM_Sound_800329C4(&svec, 186, 1);
                NewMeltDie_800E0F5C(&svec, 24);
            }
        }
    }

    if (tenage_ctrls_count_800BDD70 != 0)
    {
        for (tenage = tenage_ctrls_800BDD30, i = 16; i > 0; i--, tenage++)
        {
            if (*tenage && FurnaceBoundInCheck_800E08AC(work->bound, &(*tenage)->field_0_mov))
            {
                GM_Sound_800329C4(&(*tenage)->field_0_mov, 187, 1);
                NewMeltDie_800E0F5C(&(*tenage)->field_0_mov, 24);
                (*tenage)->field_0_mov.pad = 1;
            }
        }
    }

    dword_8009F49C = 0;
    if (amissile_alive_8009F490 && FurnaceBoundInCheck_800E08AC(work->bound, &svector_8009F494))
    {
        dword_8009F49C = 1;
    }
}

void FurnaceDie_800E0C38()
{
}

// Modified WaterAreaGetResources_800DABD0
int FurnaceGetResources_800E0C40(FurnaceWork *work, int name, int where)
{
    work->color.r = 64;
    work->color.g = 10;
    work->color.b = 10;

    if (GCL_GetOption_80020968('b'))
    {
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &work->bound[0]);
        GCL_StrToSV_80020A14(GCL_Get_Param_Result_80020AA4(), &work->bound[1]);
    }

    if (GCL_GetOption_80020968('c'))
    {
        work->color.r = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->color.g = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        work->color.b = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
    }

    work->proc_id = THING_Gcl_GetInt('e');

    NewWaterView_800DBE04(name, where, work->bound, &work->color);
    return 0;
}

GV_ACT *NewFurnace_800E0D2C(int name, int where, int argc, char **argv)
{
    FurnaceWork *work;

    work = (FurnaceWork *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(FurnaceWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)FurnaceAct_800E0974,
                                  (TActorFunction)FurnaceDie_800E0C38, "furnace.c");
        if (FurnaceGetResources_800E0C40(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
        work->where = where;
        work->name = name;
    }
    return &work->actor;
}
