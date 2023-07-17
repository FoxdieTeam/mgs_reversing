#include "libdg/libdg.h"
#include "libhzd/libhzd.h"

static inline void helper()
{
    // what were the original parameters for this crap? trying to make
    // the source and destination two arguments swaps the registers
    short *scratch2 = ( short * )0x1f800000;

    scratch2[3] = *(short *)0x1f800038;
    scratch2[2] = -*(short *)0x1f80003a;
}

static inline void assign_subtract( int idx, short idx2, short idx3, short *val )
{
    ((short*)0x1F800000)[idx] = ((short*)0x1F800000)[idx2] - val[idx3];
}

int HZD_sub_80029514( HZD_FLR *a0 )
{
    short *test;
    int x, y;

    assign_subtract( 26, 6, 0, ( short * )&a0->p1 );
    assign_subtract( 27, 7, 1, ( short * )&a0->p1 );
    
    //todo: fix below, probably some inline
    test = ( short * )0x1F800038;
    test[0] = a0->p1.h;
    do {} while(0);
    test[y = 1] = a0->p2.h;
    
    helper();

    gte_ldsxy3(0, *( int * )0x1F800034, *( int* )0x1F800004);
    gte_nclip();
    gte_stopz( 0x1F800008 );

    x = *(int * )0x1F800008;
    return a0->p1.y - x / a0->p3.h;
}