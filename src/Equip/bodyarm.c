#include "bodyarm.h"
#include "libdg/libdg.h"
#include "unknown.h"

const char               *off_8009F264[4];
const char               *off_8009F274[4];
extern const char         aBodyarmC[];

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

void bodyarm_kill_8006090C(Actor_bodyarm *pActor)
{
    if ((gGameState_800B4D98[GM_Flags] & 0x20) == 0)
    {
        bodyarm_free_80060874(pActor->field_20);
    }
}

Actor *bodyarm_init_80060940(GM_Control *pCtrl, OBJECT *pObj)
{
    Actor_bodyarm *pActor = (Actor_bodyarm *)GV_NewActor_800150E4(6, sizeof(Actor_bodyarm));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0, 0, (TActorFunction)bodyarm_kill_8006090C, aBodyarmC);
        pActor->field_20 = pObj;
        if ((gGameState_800B4D98[GM_Flags] & 0x20) != 0)
        {
            return &pActor->field_0;
        }
        bodyarm_free_80060874(pObj);
    }
    return &pActor->field_0;
}
