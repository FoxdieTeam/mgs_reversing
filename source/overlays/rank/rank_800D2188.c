#include "rank.h"

void rank_800D2188(int id, int bits)
{
    RankEntry *entry;

    entry = rank_800D2144(id);
    entry->field_1E |= bits;
}
