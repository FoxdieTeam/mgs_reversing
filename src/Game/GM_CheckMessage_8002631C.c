#include "libgv/libgv.h"

GV_MSG *GM_CheckMessage_8002631C(int pActor, int msgType, int toFind)
{
    GV_MSG *pMsg;
    int     foundCount;
    for (foundCount = GV_ReceiveMessage_80016620(msgType, &pMsg) - 1; foundCount >= 0; foundCount--)
    {
        if (pMsg->message[0] == toFind)
        {
            return pMsg;
        }
        pMsg++;
    }
    return 0;
}
