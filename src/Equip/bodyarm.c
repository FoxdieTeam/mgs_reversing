#include "bodyarm.h"
#include "libdg/libdg.h"
#include "unknown.h"
#include "Game/linkvarbuf.h"

extern const char aBodyarmC[];
extern const char aSnaChest1[];
extern const char aSnaChest2[];
extern const char aSnaChest3[];
extern const char aSnaHip1[];
extern const char aSnaArmer1[];
extern const char aSnaArmer2[];
extern const char aSnaArmer3[];
extern const char aSnaArmer4[];

const char *SECTION(".data") off_8009F264[4] = {aSnaChest1, aSnaChest2, aSnaChest3, aSnaHip1};
const char *SECTION(".data") off_8009F274[4] = {aSnaArmer1, aSnaArmer2, aSnaArmer3, aSnaArmer4};

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
    if ((GM_GameStatusFlag & 0x20) == 0)
    {
        bodyarm_free_80060874(pActor->field_20);
    }
}

GV_ACT * NewBodyarm_80060940(CONTROL *pCtrl, OBJECT *pObj, int unused)
{
    Actor_bodyarm *pActor = (Actor_bodyarm *)GV_NewActor_800150E4(6, sizeof(Actor_bodyarm));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0, 0, (TActorFunction)bodyarm_kill_8006090C, aBodyarmC);
        pActor->field_20 = pObj;
        if ((GM_GameStatusFlag & 0x20) != 0)
        {
            return &pActor->field_0;
        }
        bodyarm_free_80060874(pObj);
    }

    return &pActor->field_0;
}
