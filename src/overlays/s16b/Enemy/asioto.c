#include "libgv/libgv.h"
#include "Game/game.h"

#define EXEC_LEVEL 4

typedef struct _Work
{
    GV_ACT actor;
    char   pad[0x82];
} Work;

void asioto_act_800C39E8();
void asioto_kill_800C3B8C();
int  asioto_800C3B94(Work *work);

extern char aAsioto_800C5874[]; // = "asioto.c";

#pragma INCLUDE_ASM("asm/overlays/s16b/asioto_800C3278.s")
#pragma INCLUDE_ASM("asm/overlays/s16b/asioto_800C32D8.s")
#pragma INCLUDE_ASM("asm/overlays/s16b/asioto_800C3320.s")
#pragma INCLUDE_ASM("asm/overlays/s16b/asioto_800C33A0.s")
#pragma INCLUDE_ASM("asm/overlays/s16b/asioto_800C34F0.s")
#pragma INCLUDE_ASM("asm/overlays/s16b/asioto_800C3718.s")
#pragma INCLUDE_ASM("asm/overlays/s16b/asioto_800C38AC.s")
void asioto_800C38AC();

void asioto_800C392C(void)
{
    asioto_800C38AC();
}

extern int GM_PlayerStatus_800ABA50;

int asioto_800C394C()
{
    return (GM_PlayerStatus_800ABA50 & 0x10050) == 0x10;
}

extern int dword_800AB9D4;

int asioto_800C396C(void)
{
    if (asioto_800C394C() == 0)
        return -1;

    if (dword_800AB9D4 == 8)
    {
        return 0;
    }
    if (dword_800AB9D4 == 0x10)
    {
        return 1;
    }
    return -1;
}

extern int dword_800AB9D4;

int asioto_800C39B8(void)
{
    if (dword_800AB9D4 == 0xC)
        return 0;
    if (dword_800AB9D4 == 0x18)
        return 1;
    return -1;
}

#pragma INCLUDE_ASM("asm/overlays/s16b/asioto_act_800C39E8.s")
void asioto_kill_800C3B8C()
{
}
#pragma INCLUDE_ASM("asm/overlays/s16b/asioto_800C3B94.s")

GV_ACT *NewAsioto_800C3E08(void)
{
    Work *work = NULL;

    work = (Work *)GV_NewActor_800150E4(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)asioto_act_800C39E8,
                                  (TActorFunction)asioto_kill_800C3B8C, aAsioto_800C5874);
        if (asioto_800C3B94(work) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return 0;
        }
    }

    return (GV_ACT *)work;
}
