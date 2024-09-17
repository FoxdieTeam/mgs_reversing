#include "libgv/libgv.h"
#include "Bullet/blast.h"

typedef struct BlastLnWork
{
    GV_ACT actor;
    int field_20;
    SVECTOR field_24;
    SVECTOR field_2C;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
} BlastLnWork;

#define EXEC_LEVEL 4

extern int GM_CurrentMap_800AB9B0;

void s11g_blst_ln_800CD7C8(BlastLnWork *work)
{
    SVECTOR svec;

    GM_CurrentMap_800AB9B0 = work->field_20;
    
    svec.vx = work->field_24.vx + (work->field_2C.vx - work->field_24.vx) * work->field_44 / work->field_40 + GV_RandS(0x8000) * work->field_34 / 32768;
    svec.vy = work->field_24.vy + (work->field_2C.vy - work->field_24.vy) * work->field_44 / work->field_40 + GV_RandS(0x8000) * work->field_34 / 32768;
    svec.vz = work->field_24.vz + (work->field_2C.vz - work->field_24.vz) * work->field_44 / work->field_40 + GV_RandS(0x8000) * work->field_34 / 32768;
    
    switch (work->field_38)
    {
    case 3:
        AN_Blast_high_8006E4A4(&svec);
        break;
    case 4:
        if (GV_RandU(2) != 0)
        {
        case 2:
            AN_Blast_Single_8006E224(&svec);
        }
        else
        {
        case 1:
            AN_Blast_Mini_8006E2A8(&svec);
        }
        break;
    case 5:
        if (GV_RandU(2) != 0)
        {
            AN_Blast_Mini_8006E2A8(&svec);
            break;
        }
    case 0:
        AN_Blast_Minimini_8006E32C(&svec);
        break;
    }
    if (--work->field_3C < 0)
    {
        GV_DestroyActor(&work->actor);
    }
    work->field_44++;
}

void s11g_blst_ln_800CDA28(BlastLnWork *work)
{
}

int s11g_blst_ln_800CDA30(BlastLnWork *work, int arg1, int arg2, int arg3, SVECTOR *arg4, SVECTOR *arg5)
{
    work->field_38 = arg1;
    work->field_3C = arg2;
    work->field_34 = arg3;
    work->field_20 = GM_CurrentMap_800AB9B0;
    work->field_24 = *arg4;
    work->field_2C = *arg5;
    work->field_40 = arg2;
    work->field_44 = 0;
    return 0;
}

GV_ACT *s11g_blst_ln_800CDAA0(int arg0, int arg1, int arg2, SVECTOR *arg3, SVECTOR *arg4)
{
    BlastLnWork *work;

    work = (BlastLnWork *) GV_NewActor(EXEC_LEVEL, sizeof(BlastLnWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)s11g_blst_ln_800CD7C8, (GV_ACTFUNC)s11g_blst_ln_800CDA28, "blst_ln.c");
        s11g_blst_ln_800CDA30(work, arg0, arg1, arg2, arg3, arg4);
    }
    return &work->actor;
}
