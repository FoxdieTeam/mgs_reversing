#include "linker.h"

typedef struct
{
    unsigned short address;
    unsigned short _len;
    unsigned short message[7];
    unsigned short message_len;
} GV_MSG; // from mem leak

void GV_Message_8001642C(GV_MSG *pMsg, int msg_count)
{
    // Move everything after pMsg to the left to erase pMsg
    GV_MSG *pMsgIter = &pMsg[msg_count];
    for (msg_count = msg_count - 1; msg_count >= 0; --msg_count)
    {
        *(pMsgIter) = *(pMsgIter - 1);
        pMsgIter--;
    }
}
