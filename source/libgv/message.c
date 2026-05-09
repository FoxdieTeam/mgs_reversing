#include "libgv.h"

/* ---------------------------------------------------------- */

extern MESSAGE_LIST message_list[ 2 ];
STATIC int SECTION(".sbss") which_buffer;

// TODO: remove padding
STATIC int SECTION(".sbss") dword_800AB94C;

/* ---------------------------------------------------------- */

static void slide_message_forward( GV_MSG *ptr, int n_ptr )
{
    ptr += n_ptr;

    while ( --n_ptr >= 0 )
    {
        *ptr = *(ptr - 1);
        ptr--;
    }
}

void GV_InitMessageSystem( void )
{
    message_list[ 0 ].num = 0;
    message_list[ 1 ].num = 0;
    which_buffer = 0;
}

void GV_ClearMessageSystem( void )
{
    MESSAGE_LIST *list;

    which_buffer = 1 - which_buffer;

    list = message_list + ( 1 - which_buffer );
    list->num = 0;
}

int GV_SendMessage( GV_MSG *send )
{
    MESSAGE_LIST *list;
    int           num;

    {
        list = message_list + ( 1 - which_buffer );
        num = list->num;
        if ( num >= MAX_MESSAGES ) return -1;
        list->num = num + 1;
    }

    {
        GV_MSG *msg;
        int address, length;

        msg = list->messages;
        address = send->address;
        length = 0;
        for ( ; num > 0; num-- )
        {
            if ( msg->address == address )
            {
                length = msg->_len;
                slide_message_forward( msg, num );
                break;
            }
            msg++;
        }

        *msg = *send;
        msg->_len = length + 1;
    }

    return 0;
}

int GV_ReceiveMessage( int address, GV_MSG **msg_ptr )
{
    MESSAGE_LIST *list;
    GV_MSG       *msg;
    int           num;

    if ( GV_PauseLevel != 0 ) return 0;

    list = message_list + which_buffer;
    if ( ( num = list->num ) == 0 ) return 0;
    msg = list->messages;
    while ( --num >= 0 )
    {
        if ( msg->address == address )
        {
            *msg_ptr = msg;
            return msg->_len;
        }
        msg++;
    }
    return 0;
}
