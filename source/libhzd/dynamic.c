#include "libhzd.h"
#include "mgstype.h"

int HZD_QueueDynamicSegment2( HZD_HDL *hzd, HZD_SEG *seg, int flag )
{
    int index;

    index = hzd->n_d_segs;
    if ( index >= hzd->max_d_segs ) return -1;

    hzd->d_segs[ index ] = seg;
    hzd->d_seg_flag[ index ] = flag;
    hzd->d_seg_flag[ hzd->max_d_segs + index ] = flag >> 8;
    hzd->n_d_segs = index + 1;
    return 0;
}

void HZD_DequeueDynamicSegment( HZD_HDL *hzd, HZD_SEG *seg )
{
    HZD_SEG **list;
    char *flag1, *flag2;
    int index, i;

    list = hzd->d_segs;
    flag1 = hzd->d_seg_flag;
    flag2 = hzd->d_seg_flag + hzd->max_d_segs;
    index = hzd->n_d_segs;

    for ( i = index; i > 0; i-- )
    {
        if ( *list == seg ) goto found;
        list++;
        flag1++;
        flag2++;
    }
    return;

found:
    index--;
    *list = hzd->d_segs[ index ];
    *flag1 = hzd->d_seg_flag[ index ];
    *flag2 = hzd->d_seg_flag[ index + hzd->max_d_segs ];
    hzd->n_d_segs = index;
}

void HZD_SetDynamicSegment( HZD_SEG *seg1, HZD_SEG *seg2 )
{
    int p1, p2;

    p1 = seg1->p1.x;
    p2 = seg1->p2.x;
    if ( p1 >= p2 )
    {
        if ( p2 < p1 ) goto end;
        p1 = seg1->p1.z;
        p2 = seg1->p2.z;
        if ( p1 >= p2 )
        {
            if ( p2 < p1 ) goto end;
            seg1->p2.x++;
        }
    }
    if ( seg1 != seg2 ) *seg2 = *seg1;
    return;

end:
    p1 = seg1->p1.x;
    p2 = seg1->p2.x;
    seg2->p2.x = p1;
    seg2->p1.x = p2;

    p1 = seg1->p1.y;
    p2 = seg1->p2.y;
    seg2->p2.y = p1;
    seg2->p1.y = p2;

    p1 = seg1->p1.z;
    p2 = seg1->p2.z;
    seg2->p2.z = p1;
    seg2->p1.z = p2;

    p1 = seg1->p1.h;
    p2 = seg1->p2.h;
    seg2->p2.h = p1;
    seg2->p1.h = p2;
}

int HZD_QueueDynamicFloor( HZD_HDL *hzd, HZD_FLR *flr )
{
    int index;

    index = hzd->n_d_flrs;
    if ( hzd->n_d_flrs >= hzd->max_d_flrs ) return -1;

    hzd->d_flrs[ index ] = flr;
    hzd->n_d_flrs = index + 1;
    flr->p4.h |= HZX_FLOOR_DYNAMIC;
    return 0;
}

void HZD_DequeueDynamicFloor( HZD_HDL *hzd, HZD_FLR *flr )
{
    HZD_FLR **list;
    int index, i;

    list = hzd->d_flrs;
    index = hzd->n_d_flrs;

    for ( i = index; i > 0; i-- )
    {
        if ( *list == flr ) goto found;
        list++;
    }
    return;

found:
    index--;
    *list = hzd->d_flrs[ index ];
    hzd->n_d_flrs = index;
}
