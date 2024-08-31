#include "bodyarm.h"
#include "libdg/libdg.h"
#include "Equip/effect.h"
#include "Game/linkvarbuf.h"

const char *off_8009F264[4] = {"sna_chest1", "sna_chest2", "sna_chest3", "sna_hip1"};
const char *off_8009F274[4] = {"sna_armer1", "sna_armer2", "sna_armer3", "sna_armer4"};

void bodyarm_free_80060874(OBJECT *a1)
{
    int i;
    for (i = 0; i < 2; ++i)
    {
        DG_FreeObjPacket_8001AAD0(&a1->objs->objs[0], i);
        DG_FreeObjPacket_8001AAD0(&a1->objs->objs[1], i);
    }

    for (i = 0; i < 4; i++)
    {
        EQ_ChangeTexture_80060CE4(off_8009F264[i], off_8009F274[i]);
    }
}

void bodyarm_kill_8006090C(BodyarmWork *work)
{
    if ((GM_GameStatusFlag & 0x20) == 0)
    {
        bodyarm_free_80060874(work->field_20);
    }
}

GV_ACT * NewBodyarm_80060940(CONTROL *pCtrl, OBJECT *pObj, int unused)
{
    BodyarmWork *work = (BodyarmWork *)GV_NewActor(6, sizeof(BodyarmWork));
    if (work)
    {
        GV_SetNamedActor(&work->field_0, 0, (TActorFunction)bodyarm_kill_8006090C, "bodyarm.c");
        work->field_20 = pObj;
        if ((GM_GameStatusFlag & 0x20) != 0)
        {
            return &work->field_0;
        }
        bodyarm_free_80060874(pObj);
    }

    return &work->field_0;
}
