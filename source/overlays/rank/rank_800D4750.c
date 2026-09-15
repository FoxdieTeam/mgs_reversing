#include "libgv/libgv.h"

extern int rank_dword_800E59F8;

int rank_800D4750(unsigned short name, int hash_count, unsigned short *hashes)
{
    GV_MSG *msg;
    int     msg_count;
    int     found;
    int     hash;
    int     i;

    msg_count = GV_ReceiveMessage(name, &msg);
    found = -1;

    for (; msg_count > 0; msg_count--, msg++)
    {
        hash = msg->message[0];

        for (i = 0; i < hash_count; i++)
        {
            if (hash == hashes[i])
            {
                found = i;
                rank_dword_800E59F8 = msg->message[1];
            }
        }
    }

    return found;
}
