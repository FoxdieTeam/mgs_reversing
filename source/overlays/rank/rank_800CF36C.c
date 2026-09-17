#include "rank.h"

void rank_800CF36C(int id, int bits)
{
    RankEntry *entry;

    entry = rank_800CF328(id);
    entry->field_1E &= ~bits;
}
