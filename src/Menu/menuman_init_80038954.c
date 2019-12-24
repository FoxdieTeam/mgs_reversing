#include "linker.h"
#include "menuMan.h"

MenuMan SECTION(".gMenuMan_800BD360") gMenuMan_800BD360;

extern const char aMenumanC[];

void menuman_act_800386A4(MenuMan*);
void menuman_kill_800387E8(MenuMan*);

void sub_8003884C(MenuMan*);
void MENU_InitRadioTable_80049644(void);

void menuman_init_80038954(void)
{
    GV_ActorInit_8001514c(&gMenuMan_800BD360.mBase, (TActorFunction)menuman_act_800386A4, (TActorFunction)menuman_kill_800387E8, aMenumanC);
    sub_8003884C(&gMenuMan_800BD360);
    MENU_InitRadioTable_80049644();
}
