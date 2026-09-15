#include "rank.h"

RankEntry *rank_800CF328(int id)
{
    RankEntry *entry;

    for (entry = rank_dword_800E1974; entry != NULL; entry = entry->field_4)
    {
        if (entry->field_24 == id)
        {
            return entry;
        }
    }

    return NULL;
}
