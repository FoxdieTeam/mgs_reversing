#include "mts_new.h"

extern int gMts_Event1_800A3D70;
extern int gMts_Event2_800A3D90;

void EnterCriticalSection_8009952C(void);
void ExitCriticalSection_8009953C(void);
void CloseEvent_8009947C(int event);

void mts_shutdown_8008B044(void)
{
    EnterCriticalSection_8009952C();
    
    if (gMts_Event1_800A3D70)
    {
        CloseEvent_8009947C(gMts_Event1_800A3D70);
    }

    if (gMts_Event2_800A3D90)
    {
        CloseEvent_8009947C(gMts_Event2_800A3D90);
    }

    ExitCriticalSection_8009953C();
}
