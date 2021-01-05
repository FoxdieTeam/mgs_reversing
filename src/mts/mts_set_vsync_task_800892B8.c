#include "linker.h"
#include "mts_new.h"

extern const char aAssertionFaled[];
extern const char aMtsNewC[];
extern const char aGetNewVblContr[];
extern const char asc_80013E2C[];

void mts_dump_process_list_8008B77C(void);

extern int gTaskIdx_800C0DB0;
extern mts_task gTasks_800C0C30[];

typedef struct mts_msg
{
    int field_0;
    int field_4_task_idx;
    int field_8;
    int field_C;
    int field_10;
} mts_msg;

mts_msg SECTION(".gMtsMsgs_800C13D0") gMtsMsgs_800C13D0[8] = {};

#define mts_assert(functionName, lineNum) \
    mts_printf_8008BBA0(aAssertionFaled, aMtsNewC, lineNum, gTaskIdx_800C0DB0);\
    mts_printf_8008BBA0(functionName);\
    mts_printf_8008BBA0(asc_80013E2C);\
    mts_dump_process_list_8008B77C();

void mts_set_vsync_task_800892B8(void)
{
    int task_idx; // $s1
    mts_task* pTask; // $s0
    int idx; // $a0
    mts_msg* pIter; // $a1
    mts_msg* pMsg; // $v0

    if (!gTasks_800C0C30[gTaskIdx_800C0DB0].field_4_pMessage)
    {
        task_idx = gTaskIdx_800C0DB0;
        pTask = &gTasks_800C0C30[task_idx];
        idx = 0;
        pIter = gMtsMsgs_800C13D0;

        while (idx < 8)
        {
            if (!gMtsMsgs_800C13D0[idx].field_4_task_idx)
            {
                pMsg = pIter;
                goto got_free_entry;
            }

            pIter++;
            idx++;
        }

        mts_assert(aGetNewVblContr, 494);
        pMsg = 0;

    got_free_entry:
        pTask->field_4_pMessage = pMsg;
        pMsg->field_0 = 0;
        pMsg->field_4_task_idx = task_idx;
        pMsg->field_8 = 0;
        pMsg->field_C = 0;
        pMsg->field_10 = 0;
    }

}