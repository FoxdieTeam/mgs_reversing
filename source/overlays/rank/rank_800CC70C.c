#include "mts/mts.h"
#include "rank.h"

int rank_800CC70C(int arg)
{
    rank_dword_800E1874 = arg;
    mts_slp_tsk();
    return rank_dword_800E1878;
}
