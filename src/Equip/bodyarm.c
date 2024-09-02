#include "bodyarm.h"
#include "libdg/libdg.h"
#include "Equip/effect.h"
#include "Game/linkvarbuf.h"

typedef struct BodyarmWork
{
    GV_ACT  actor;
    OBJECT *parent;
} BodyarmWork;

const char *bodyarm_orig_tex_8009F264[4] = {"sna_chest1", "sna_chest2", "sna_chest3", "sna_hip1"};
const char *bodyarm_new_tex_8009F274[4] = {"sna_armer1", "sna_armer2", "sna_armer3", "sna_armer4"};

void BodyarmSwapTextures_80060874(OBJECT *a1)
{
    int i;

    for (i = 0; i < 2; ++i)
    {
        DG_FreeObjPacket_8001AAD0(&a1->objs->objs[0], i);
        DG_FreeObjPacket_8001AAD0(&a1->objs->objs[1], i);
    }

    for (i = 0; i < 4; i++)
    {
        EQ_ChangeTexture_80060CE4(bodyarm_orig_tex_8009F264[i], bodyarm_new_tex_8009F274[i]);
    }
}

void BodyarmDie_8006090C(BodyarmWork *work)
{
    if (!(GM_GameStatusFlag & 0x20))
    {
        BodyarmSwapTextures_80060874(work->parent);
    }
}

GV_ACT * NewBodyarm_80060940(CONTROL *control, OBJECT *parent, int num_parent)
{
    BodyarmWork *work = (BodyarmWork *)GV_NewActor(6, sizeof(BodyarmWork));
    if (work)
    {
        GV_SetNamedActor(&work->actor, NULL, (TActorFunction)BodyarmDie_8006090C, "bodyarm.c");

        work->parent = parent;

        if (!(GM_GameStatusFlag & 0x20))
        {
            BodyarmSwapTextures_80060874(parent);
        }
    }

    return (GV_ACT *)work;
}
