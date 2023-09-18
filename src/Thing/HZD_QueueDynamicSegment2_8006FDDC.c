#include "libhzd/libhzd.h"

int HZD_QueueDynamicSegment2_8006FDDC(HZD_HDL *pHzdMap, HZD_SEG *pSeg, int a_param_with_flag)
{
    int idx = pHzdMap->f0A_idx;
    if ( idx >= pHzdMap->f12_queue_size )
    {
        return -1;
    }
    pHzdMap->f20_pAfterStructure_24[idx] = pSeg;
    pHzdMap->f20_pAfterStructure_48[idx] = a_param_with_flag;
    pHzdMap->f20_pAfterStructure_48[pHzdMap->f12_queue_size + idx] = a_param_with_flag >> 8;
    pHzdMap->f0A_idx = idx + 1;
    return 0;
}
