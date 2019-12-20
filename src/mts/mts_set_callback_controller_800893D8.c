#include "linker.h"
#include "mts_new.h"

extern void* gControllerCallBack_800A3D74;

void mts_set_callback_controller_800893D8(void *pControllerCallBack)
{
    gControllerCallBack_800A3D74 = pControllerCallBack;
}
