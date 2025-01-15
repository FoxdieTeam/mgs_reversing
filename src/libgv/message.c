#include "libgv.h"

/*** bss ***/
extern MESSAGE_LIST message_list_800B0320[2];

/*** $gp ***/
STATIC int SECTION(".sbss") which_buffer;
STATIC int SECTION(".sbss") dword_800AB94C;

/*** sbss ***/
extern int GV_PauseLevel;

STATIC void GV_ReserveMessage(GV_MSG *ptr, int msg_count)
{
    // Move everything after msg to the left to erase msg
    GV_MSG *msg = &ptr[msg_count];

    for (msg_count = msg_count - 1; msg_count >= 0; --msg_count)
    {
        *(msg) = *(msg - 1);
        msg--;
    }
}

void GV_InitMessageSystem(void)
{
    message_list_800B0320[0].num = 0;
    message_list_800B0320[1].num = 0;
    which_buffer = 0;
}

void GV_ClearMessageSystem(void)
{
    MESSAGE_LIST *list;
    which_buffer = 1 - which_buffer;

    list = &message_list_800B0320[1 - which_buffer];
    list->num = 0;
}

int GV_SendMessage(GV_MSG *send)
{
    int          address, n_msg, length;
    MESSAGE_LIST *list;
    GV_MSG       *msg;

    list = &message_list_800B0320[1 - which_buffer];

    n_msg = list->num;
    if (n_msg > 15)
        return -1;

    msg = list->msg;
    list->num = n_msg + 1;
    length = 0;

    address = send->address;
    for (; n_msg > 0; --n_msg)
    {
        if (msg->address == address)
        {
            length = msg->_len;
            GV_ReserveMessage(msg, n_msg);
            break;
        }
        msg++;
    }

    *msg = *send;
    msg->_len = length + 1;

    return 0;
}

int GV_ReceiveMessage(int address, GV_MSG **msg_ptr)
{
    MESSAGE_LIST *list;
    GV_MSG       *msg;
    int           num;

    if (GV_PauseLevel)
    {
        return 0;
    }

    list = &message_list_800B0320[which_buffer];
    num = list->num;
    if (!num)
    {
        return 0;
    }

    msg = list->msg;
    num = num - 1;
    while (num >= 0)
    {
        if (msg->address == address)
        {
            *msg_ptr = msg;
            return msg->_len;
        }
        ++msg;
        --num;
    }
    return 0;
}
