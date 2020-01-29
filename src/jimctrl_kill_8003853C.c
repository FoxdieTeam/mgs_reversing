#include <util/idaTypes.h>
#include "data.h"
#include "jimctrl.h"

extern unk_8009E280 dword_8009E280;
extern void sub_80024098(void);

void jimctrl_kill_8003853C(Actor_JimCtrl *pJimCtrl)
{
    jimctrl_kill_helper_clear_80038004(pJimCtrl);
    dword_8009E280.dword_8009E28C = 0;
    sub_80024098();
}
