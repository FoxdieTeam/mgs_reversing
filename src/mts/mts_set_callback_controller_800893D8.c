#include "linker.h"
#include "mts_new.h"

extern void (*gControllerCallBack_800A3D74)(void);

extern int gMtsVSyncCount_800A3D78;
extern mts_msg stru_800A3D7C;
extern mts_task gTasks_800C0C30[];
extern int gTaskIdx_800C0DB0;
extern int gMts_bits_800C0DB4;
extern int gMts_active_task_idx_800C13C0;

int VSync_80098108(int);

void mts_set_callback_controller_800893D8(void *pControllerCallBack)
{
    gControllerCallBack_800A3D74 = pControllerCallBack;
}

void mts_init_vsync_helper_800893E8()
{
    int v0;
    mts_msg *pNext;
    mts_msg *pUnknownIter;
    int bitMask;
    int task_idx;
    int bChangeThreadContext;

    gMtsVSyncCount_800A3D78 = VSync_80098108(-1);

    if (gControllerCallBack_800A3D74)
    {
        gControllerCallBack_800A3D74();
    }

    v0 = -1;
    pNext = stru_800A3D7C.field_0;
    for (pUnknownIter = &stru_800A3D7C; pNext; pNext = pNext->field_0)
    {
        if ((unsigned int)gMtsVSyncCount_800A3D78 >= pNext->field_C)
        {
            if (pNext->field_10 == 0 || pNext->field_10())
            {
                pNext->field_8 = gMtsVSyncCount_800A3D78;
                gTasks_800C0C30[pNext->field_4_task_idx].field_0_state = 3;
                gMts_bits_800C0DB4 |= 1 << pNext->field_4_task_idx;
                if (v0 < 0)
                {
                    v0 = pNext->field_4_task_idx;
                }
                pUnknownIter->field_0 = pNext->field_0;
            }
            else
            {
                pUnknownIter = pNext;
            }
        }
        else
        {
            pUnknownIter = pNext;
        }
    }

    if (v0 > 0 && v0 < gTaskIdx_800C0DB0)
    {
        bitMask = 1;
        gMts_active_task_idx_800C13C0 = -1;
        for (task_idx = 0; task_idx < 12; task_idx++)
        {
            if ((gMts_bits_800C0DB4 & bitMask) != 0)
            {
                break;
            }
            bitMask *= 2;
        }

        gMts_active_task_idx_800C13C0 = task_idx;

        if (task_idx == gTaskIdx_800C0DB0)
        {
            bChangeThreadContext = 0;
        }
        else
        {
            gTaskIdx_800C0DB0 = task_idx;
            bChangeThreadContext = 1;
        }

        if (bChangeThreadContext)
        {
            // Set the current TCB
            struct TCB **pTCB = *(struct TCB ***)0x108;
            *pTCB = gTasks_800C0C30[gTaskIdx_800C0DB0].field_1C;
        }
    }
}
