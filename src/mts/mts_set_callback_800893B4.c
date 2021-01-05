#include "linker.h"
#include "mts_new.h"

extern mts_task gTasks_800C0C30[];
extern int gTaskIdx_800C0DB0;

void mts_set_callback_800893B4(void* cb)
{
    gTasks_800C0C30[gTaskIdx_800C0DB0].field_4_pMessage->field_10 = cb;
}
