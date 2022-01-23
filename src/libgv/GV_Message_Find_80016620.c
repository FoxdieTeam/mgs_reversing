#include "linker.h"
#include "libgv.h"

extern int GV_PauseLevel_800AB928;

struct GV_Messages SECTION(".gMessageQueue_800B0320") gMessageQueue_800B0320[2];

// force gp usage
extern int active_msg_queue_800AB948;
int SECTION(".sbss") active_msg_queue_800AB948;


int GV_Message_Find_80016620(int msg_type, GV_MSG **ppFound)
{
    struct GV_Messages *pMsgs; // $v1
    int count;                 // $a2
    GV_MSG *pMsgIter;          // $v1

    if (GV_PauseLevel_800AB928)
    {
        return 0;
    }

    pMsgs = &gMessageQueue_800B0320[active_msg_queue_800AB948];
    count = pMsgs->field_0_count;
    if (!count)
    {
        return 0;
    }

    pMsgIter = pMsgs->field_4_msgs;
    count = count - 1;
    while (count >= 0)
    {
        if (pMsgIter->address == msg_type)
        {
            *ppFound = pMsgIter;
            return pMsgIter->_len;
        }
        ++pMsgIter;
        --count;
    }
    return 0;
}
