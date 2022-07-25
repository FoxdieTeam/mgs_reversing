#ifndef _MESSAGE_H_
#define _MESSAGE_H_

typedef struct
{
    unsigned short address;
    unsigned short _len;
    unsigned short message[7];
    unsigned short message_len;
} GV_MSG; // from mem leak

int GV_ReceiveMessage_80016620(int msg_type, GV_MSG **ppFound);

#endif // _MESSAGE_H_
