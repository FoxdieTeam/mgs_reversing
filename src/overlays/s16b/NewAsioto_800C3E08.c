#include "libgv/libgv.h"
#include "Game/game.h"

#define EXEC_LEVEL 4

typedef struct _Work
{
    GV_ACT actor;
    char    pad[0x82];
} Work;

void asioto_act_800C39E8();
void asioto_kill_800C3B8C();
int s16b_800C3B94(Work *work);

extern char aAsioto_800C5874[]; // = "asioto.c";

GV_ACT* NewAsioto_800C3E08(void)
{
    Work* work = NULL;


    work = (Work*)GV_NewActor_800150E4(EXEC_LEVEL , sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C( &( work->actor ), (TActorFunction)asioto_act_800C39E8, (TActorFunction)asioto_kill_800C3B8C, aAsioto_800C5874);
        if (s16b_800C3B94(work) < 0) {
            GV_DestroyActor_800151C8(&( work->actor ));
            return 0;
        }
    }

    return (GV_ACT*) work;
}
