#include "bullet/blast.h"
#include "game/game.h"

typedef struct _Work
{
    GV_ACT   actor;
    int      map;
    SVECTOR  pos;
    DG_PRIM *prim;
    SVECTOR  prim_vertex[1];
    int      time;
    TARGET   target;
} Work;

extern SVECTOR s19b_dword_800C349C;

extern const char s19b_dword_800DDC68[]; // = "jblast.c"

void s19b_jblood_800C8610(SVECTOR *);

#define EXEC_LEVEL 5

static void Act(Work *work)
{
    int time;

    GM_SetCurrentMap(work->map);
    time = ++work->time;

    if (time == 1)
    {
        s19b_jblood_800C8610(&work->pos);
    }

    if (time == 2)
    {
        sub_8007913C();
    }

    if (time >= 30)
    {
        GV_DestroyActor(work);
    }
}

static void Die(Work *work)
{
    GM_FreePrim(work->prim);
}

static void set_target(BLAST_DATA *blast, Work *work)
{
    SVECTOR size;
    TARGET *target;

    target = &work->target;

    size.vx = size.vy = size.vz = blast->field_8_z / 2;
    GM_SetTarget(target, TARGET_POWER, NO_SIDE, &size);
    GM_Target_8002DCCC(target, 7, 2, blast->field_0, blast->field_4 - 3, &s19b_dword_800C349C);
    GM_MoveTarget(target, &work->pos);
    GM_PowerTarget(target);

    size.vx = size.vy = size.vz = blast->field_C;
    s19b_dword_800C349C.vx = 50;
    GM_SetTarget(target, TARGET_POWER, NO_SIDE, &size);
    GM_Target_8002DCCC(target, 7, 2, 1, 3, &s19b_dword_800C349C);
    GM_MoveTarget(target, &work->pos);
    GM_PowerTarget(target);
}

static int GetResources(BLAST_DATA *blast, Work *work, MATRIX *world)
{
    work->time = 0;
    work->map = GM_CurrentMap;
    work->pos.vx = world->t[0];
    work->pos.vy = world->t[1];
    work->pos.vz = world->t[2];
    set_target(blast, work);
    return 0;
}

void *NewJeepBlast(MATRIX *world, BLAST_DATA *blast)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work)
    {
        GV_SetNamedActor(work, Act, Die, s19b_dword_800DDC68);

        if (GetResources(blast, work, world) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }

        GM_SeSet(&work->pos, SE_EXPLOSION);
        GM_SetNoise(255, 32, &work->pos);
    }

    sub_800790E8();
    return work;
}
