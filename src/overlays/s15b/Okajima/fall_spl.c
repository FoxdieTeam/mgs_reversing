#include "libgv/libgv.h"
#include "libgcl/libgcl.h"

typedef struct FallSplWork
{
    GV_ACT  actor;
    int     field_20;
    int     field_24;
    int     field_28;
    SVECTOR field_2C[2];
} FallSplWork;

int s15b_splash3_800C83D0(int, SVECTOR *);

extern int GM_CurrentMap_800AB9B0;

int s15b_fall_spl_800C7B0C(int unused, SVECTOR *out)
{
    int            count;
    unsigned char *param;

    count = 0;
    while ((param = GCL_Get_Param_Result_80020AA4()))
    {
        GCL_StrToSV_80020A14(param, out);
        out++;
        count++;
    }
    return count;
}

void s15b_fall_spl_800C7B60(FallSplWork *work)
{
    SVECTOR svec;
    int     rand;

    GM_CurrentMap_800AB9B0 = work->field_20;
    rand = GV_RandU_80017090(0x100);
    svec.vx = work->field_2C[0].vx + (work->field_2C[1].vx - work->field_2C[0].vx) * rand / 256;
    svec.vy = work->field_2C[0].vy + (work->field_2C[1].vy - work->field_2C[0].vy) * rand / 256;
    svec.vz = work->field_2C[0].vz + (work->field_2C[1].vz - work->field_2C[0].vz) * rand / 256;
    s15b_splash3_800C83D0(work->field_28, &svec);
}

int s15b_fall_spl_800C7C3C(FallSplWork *work, int where)
{
    int            opt1;
    unsigned char *opt2;

    work->field_20 = where;
    opt1 = GCL_GetOption_80020968('l');
    if (opt1)
    {
        s15b_fall_spl_800C7B0C(opt1, work->field_2C);
    }
    opt2 = (unsigned char *)GCL_GetOption_80020968('d');
    if (opt2)
    {
        work->field_28 = GCL_StrToInt_800209E8(opt2);
    }
    return 0;
}

void s15b_fall_spl_800C7C98(FallSplWork *work)
{
}

GV_ACT *s15b_fall_spl_800C7CA0(int name, int where, int argc, char **argv)
{
    FallSplWork *work;

    work = (FallSplWork *)GV_NewActor_800150E4(5, sizeof(FallSplWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s15b_fall_spl_800C7B60,
                                  (TActorFunction)s15b_fall_spl_800C7C98, "fall_spl.c");
        if (s15b_fall_spl_800C7C3C(work, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}
