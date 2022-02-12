#include "linker.h"
#include "tabako.h"

struct Actor        *GV_NewActor_800150E4(int level, int memSize);

extern const char   aTabakoC[];

void                tabako_act_80061EAC(Actor_tabako *pActor);
void                tabako_kill_8006206C(Actor_tabako *pActor);
int                 tabako_loader_800620B4(Actor_tabako *pActor, OBJECT *pObj, int a3);

Actor_tabako *NewTabako_80062274(Res_Control *pCtrl, OBJECT *pObj, int a3)
{
    Actor_tabako *pActor;

    pActor = (Actor_tabako*)GV_NewActor_800150E4(6, sizeof(Actor_tabako));
    if (pActor)
    {
        GV_SetNamedActor_8001514C(&pActor->field_0, (TActorFunction)tabako_act_80061EAC, (TActorFunction)tabako_kill_8006206C, aTabakoC);
        if (tabako_loader_800620B4(pActor, pObj, a3) < 0)
        {
            GV_DestroyActor_800151C8(&pActor->field_0);
            return 0;
        }
        pActor->field_44_pCtrl = pCtrl;
        pActor->field_48_pObj = pObj;
        pActor->field_4C_unknown = a3;
    }
    return pActor;
}
