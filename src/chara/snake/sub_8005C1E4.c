#include "linker.h"
#include "hzd.h"

int sub_8005C05C(HZD_ZON *a1, HZD_ZON *a2, SVECTOR *a3);

int sub_8005C1E4(HZD_MAP *pHzd, HZD_ZON *pZon, SVECTOR *pVec)
{
    unsigned char *nears; // $s2
    int i; // $s1
    int cur_near; // $s0

    nears = pZon->nears;
    for ( i = 6; i > 0; --i )
    {
        cur_near = *nears++;
        if ( cur_near == 255 )
        {
            break;
        }
        if ( sub_8005C05C(pZon, &pHzd->f00_header->navmeshes[cur_near], pVec) )
        {
            return cur_near;
        }
    }
    return -1;
}