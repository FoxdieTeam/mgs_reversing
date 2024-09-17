// #include "gmsight.h"

#include "common.h"
#include "Game/game.h"
#include "Thing/sight.h"
#include "SD/g_sound.h"
#include "strcode.h"

// gas mask first person

typedef struct _GmsightWork
{
    GV_ACT actor;
    int    time;
} GmsightWork;

extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
extern int              dword_8009F604;
extern short            word_800BDCC0;

void GmsightAct_800635BC(GmsightWork *work)
{
    if (dword_8009F604 != SGT_MASK)
    {
        NewSight_80071CDC(SGT_MASK, SGT_MASK, &word_800BDCC0, 1, NULL);
    }

    if ((++work->time == 45) && !(GM_PlayerStatus_800ABA50 & PLAYER_UNK4000000))
    {
        GM_SeSet2(0, 63, SE_GASMASK_BREATH);
        work->time = 0;
    }
}

void GmsightDie_80063644(GmsightWork *work)
{
    word_800BDCC0 = 0;
}

int GmsightGetResources_80063650(GmsightWork *work, int unused, int unused2)
{
    word_800BDCC0 = 1;
    work->time = 0;
    return 0;
}

GV_ACT *NewGmsight_80063668(int unused, int unused2, int unused3)
{
    GmsightWork *work;

    word_800BDCC0 = 0;

    work = (GmsightWork *)GV_NewActor(6, sizeof(GmsightWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, (GV_ACTFUNC)&GmsightAct_800635BC,
                         (GV_ACTFUNC)&GmsightDie_80063644, "gmsight.c");

        if (GmsightGetResources_80063650(work, unused2, unused3) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (GV_ACT *)work;
}
