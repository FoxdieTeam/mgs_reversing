#include "libgv.h"

/*** bss ***/
extern GV_Messages gMessageQueue_800B0320[2];

/*** $gp ***/
extern int active_msg_queue_800AB948;
int SECTION(".sbss") active_msg_queue_800AB948;

/*** sbss ***/
extern int GV_PauseLevel_800AB928;

void GV_SlideMessageForward(GV_MSG *msg, int msg_count)
{
    // Move everything after msg to the left to erase msg
    GV_MSG *msgIter = &msg[msg_count];
    for (msg_count = msg_count - 1; msg_count >= 0; --msg_count)
    {
        *(msgIter) = *(msgIter - 1);
        msgIter--;
    }
}

void GV_InitMessageSystem(void)
{
    gMessageQueue_800B0320[0].field_0_count = 0;
    gMessageQueue_800B0320[1].field_0_count = 0;
    active_msg_queue_800AB948 = 0;
}

void GV_ClearMessageSystem(void)
{
    GV_Messages *list;
    active_msg_queue_800AB948 = 1 - active_msg_queue_800AB948;

    list = &gMessageQueue_800B0320[1 - active_msg_queue_800AB948];
    list->field_0_count = 0;
}

int GV_SendMessage(GV_MSG *send)
{
    int          address, n_msg, length;
    GV_Messages *list;
    GV_MSG      *message;

    list = &gMessageQueue_800B0320[1 - active_msg_queue_800AB948];

    n_msg = list->field_0_count;
    if (n_msg > 15)
        return -1;

    message = list->field_4_msgs;
    list->field_0_count = n_msg + 1;
    length = 0;

    address = send->address;
    for (; n_msg > 0; --n_msg)
    {
        if (message->address == address)
        {
            length = message->_len;
            GV_SlideMessageForward(message, n_msg);
            break;
        }
        message++;
    }

    *message = *send;
    message->_len = length + 1;

    return 0;
}

int GV_ReceiveMessage(int msg_type, GV_MSG **ppFound)
{
    GV_Messages *pMsgs;    // $v1
    int          count;    // $a2
    GV_MSG      *pMsgIter; // $v1

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
