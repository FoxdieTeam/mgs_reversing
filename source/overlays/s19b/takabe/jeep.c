#include "game/game.h"

#define EXEC_LEVEL 6

typedef struct _Work
{
    GV_ACT         actor;
    void          *field_20;
    char           pad1[0x4];
    CONTROL        control;
    TARGET        *target;
    OBJECT         field_A8;
    OBJECT         field_18C;
    char           pad2[0x40];
    TARGET         target2;
    OBJECT_NO_ROTS field_2F8;
    OBJECT_NO_ROTS field_31C;
    char           pad3[0xBC];
} Work;


extern SVECTOR s19b_dword_800C39BC;
extern SVECTOR s19b_dword_800C39C4;

void s19b_jeep_800D2170(SVECTOR *arg0, SVECTOR *arg1, SVECTOR *arg2, short *arg3)
{
    arg3[0] = arg0->vx;
    arg3[1] = arg1->vx;
    arg3[2] = arg2->vx;
    arg3[3] = arg0->vy;
    arg3[4] = arg1->vy;
    arg3[5] = arg2->vy;
    arg3[6] = arg0->vz;
    arg3[7] = arg1->vz;
    arg3[8] = arg2->vz;
}

void s19b_jeep_800D21DC(int ang, MATRIX *mat, SVECTOR *out)
{
    SVECTOR vec;
    VECTOR  sqr;
    int     y;

    sqr.vx = 4096 - ang;
    sqr.vz = ang;

    gte_ldlvl(&sqr);
    gte_sqr12();
    y = ang * (4096 - ang);
    y >>= 11;
    gte_stlvnl(&sqr);

    vec.vy = y;
    vec.vx = sqr.vx;
    vec.vz = sqr.vz;
    ApplyMatrixSV(mat, &vec, out);
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_800D2258.s")
void s19b_jeep_800D2258(Work *work);

void s19b_jeep_800D2790(Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->field_A8);
    GM_FreeObject(&work->field_18C);
    GM_FreeObject((OBJECT *)&work->field_2F8);
    GM_FreeObject((OBJECT *)&work->field_31C);
    GM_FreeTarget(work->target);
    GV_DestroyActor(work->field_20);
    GM_SetSound(0xFF0000FE, 0);
}

void s19b_jeep_800D2800(Work *work)
{
    TARGET *trg;

    trg = work->target = GM_AllocTarget();
    GM_SetTarget(trg, TARGET_PUSH, PLAYER_SIDE, &s19b_dword_800C39BC);

    trg = &work->target2;
    GM_SetTarget(trg, TARGET_POWER, PLAYER_SIDE, &s19b_dword_800C39C4);
    GM_Target_8002DCCC(trg, 5, 2, 8, 0, &DG_ZeroVector);
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_800D2880.s")
int s19b_jeep_800D2880(Work *work, int, int);

extern const char s19b_aJeepc_800DDD8C[]; // = "jeep.c"

void *NewJeep(int arg0, int arg1)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jeep_800D2258, s19b_jeep_800D2790, s19b_aJeepc_800DDD8C);

        if (s19b_jeep_800D2880(work, arg0, arg1) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}
