#include "linker.h"
#include "memcard.h"

extern int gmem_card_system_inited_8009D524 ;

extern long gHardware_end_io_800B52C8;
extern long gHardware_end_write_800B52CC;
extern long gHardware_timeout_800B52D0;
extern long gHardware_new_device_800B52D4;


extern long gSoftware_end_io_800B52D8;
extern long gSoftware_end_write_800B52DC;
extern long gSoftware_timeout_800B52E0;
extern long gSoftware_new_device_800B52E4;

void StopCARD_80099130(void);
void EnterCriticalSection_8009952C(void);
void ExitCriticalSection_8009953C(void);
void CloseEvent_8009947C(int event);

void memcard_exit_800250C4()
{
    StopCARD_80099130();
    EnterCriticalSection_8009952C();
    CloseEvent_8009947C(gHardware_end_io_800B52C8);
    CloseEvent_8009947C(gHardware_end_write_800B52CC);
    CloseEvent_8009947C(gHardware_timeout_800B52D0);
    CloseEvent_8009947C(gHardware_new_device_800B52D4);
    CloseEvent_8009947C(gSoftware_end_io_800B52D8);
    CloseEvent_8009947C(gSoftware_end_write_800B52DC);
    CloseEvent_8009947C(gSoftware_timeout_800B52E0);
    CloseEvent_8009947C(gSoftware_new_device_800B52E4);
    ExitCriticalSection_8009953C();
    gmem_card_system_inited_8009D524 = 0;
}
