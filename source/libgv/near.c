#include "libgv.h"

/*----------------------------------------------------------------*/

static short TimeInv[16] = {
    0, 2048, 1365, 1024, 819, 682, 585, 512,
    455, 409, 372, 341, 315, 292, 273, 256
};

/*----------------------------------------------------------------*/

static inline int NearExp2( int from, int to )
{
    int diff;

    diff = to - from;
    if ( diff > -2 && diff < 2 ) return to;
    return from + diff / 2;
}

static inline int NearExp4( int from, int to )
{
    int diff;

    diff = to - from;
    if ( diff > -4 && diff < 4 ) return to;
    return from + diff / 4;
}

static inline int NearExp8( int from, int to )
{
    int diff;

    diff = to - from;
    if ( diff > -8 && diff < 8 ) return to;
    return from + diff / 8;
}

static inline int NearPhase( int from, int to )
{
    short diff;

    diff = 4095 & ( from - to );
    if ( diff > 2048 ) diff -= 4096;
    return to + diff;
}

static inline int NearRange( int from, int to, int range )
{
    int border;

    border = to - range;
    if ( from < border ) return border;
    border = to + range;
    if ( from > border ) return border;
    return from;
}

static inline int NearSpeed( int from, int to, int speed )
{
    int next;

    if ( from < to )
    {
        next = from + speed;
        if ( next >= to ) return to;
    }
    else
    {
        next = from - speed;
        if ( next <= to ) return to;
    }
    return next;
}

static inline int NearTime( int from, int to, int interp )
{
    if ( interp == 0 ) return to;
    return ( to - from ) * interp / 4096 + from;
}

/*----------------------------------------------------------------*/

static inline int NearExp2P( int from, int to )
{
    return NearExp2( NearPhase( from, to ), to );
}

static inline int NearExp4P( int from, int to )
{
    return NearExp4( NearPhase( from, to ), to );
}

static inline int NearExp8P( int from, int to )
{
    return NearExp8( NearPhase( from, to ), to );
}

static inline int NearExp2S( int from, int to, int speed )
{
    int diff;

    diff = ( to - from ) / 2;
    if ( diff > -speed && diff < speed ) return to;
    return from + diff;
}

static inline int NearExp4S( int from, int to, int speed )
{
    int diff;

    diff = ( to - from ) / 4;
    if ( diff > -speed && diff < speed ) return to;
    return from + diff;
}

static inline int NearExp8S( int from, int to, int speed )
{
    int diff;

    diff = ( to - from ) / 8;
    if ( diff > -speed && diff < speed ) return to;
    return from + diff;
}

/*----------------------------------------------------------------*/

int GV_NearExp2( int from, int to )
{
    return NearExp2( from, to );
}

int GV_NearExp4( int from, int to )
{
    return NearExp4( from, to );
}

int GV_NearExp8( int from, int to )
{
    return NearExp8( from, to );
}

int GV_NearPhase( int from, int to )
{
    return NearPhase( from, to );
}

int GV_NearRange( int from, int to, int range )
{
    return NearRange( from, to, range );
}

int GV_NearSpeed( int from, int to, int speed )
{
    return NearSpeed( from, to, speed );
}

int GV_NearTime( int from, int to, int interp )
{
    if ( interp > 15 ) interp = 15;
    interp = TimeInv[ interp ];
    return NearTime( from, to, interp );
}

/*----------------------------------------------------------------*/

int GV_NearExp2P( int from, int to )
{
    return NearExp2P( from, to );
}

int GV_NearExp4P( int from, int to )
{
    return NearExp4P( from, to );
}

int GV_NearExp8P( int from, int to )
{
    return NearExp8P( from, to );
}

int GV_NearTimeP( int from, int to, int interp )
{
    if ( interp > 15 ) interp = 15;
    interp = TimeInv[ interp ];
    return NearTime( NearPhase( from, to ), to, interp );
}

/*----------------------------------------------------------------*/

void GV_NearExp2V( void *vfrom, void *vto, int n )
{
    short *from, *to;

    from = (short *)vfrom;
    to = (short *)vto;
    while ( --n >= 0 )
    {
        *from = NearExp2( *from, *to );
        from++;
        to++;
    }
}

void GV_NearExp4V( void *vfrom, void *vto, int n )
{
    short *from, *to;

    from = (short *)vfrom;
    to = (short *)vto;
    while ( --n >= 0 )
    {
        *from = NearExp4( *from, *to );
        from++;
        to++;
    }
}

void GV_NearExp8V( void *vfrom, void *vto, int n )
{
    short *from, *to;

    from = (short *)vfrom;
    to = (short *)vto;
    while ( --n >= 0 )
    {
        *from = NearExp8( *from, *to );
        from++;
        to++;
    }
}

void GV_NearPhaseV( void *vfrom, void *vto, int n )
{
    short *from, *to;

    from = (short *)vfrom;
    to = (short *)vto;
    while( --n >= 0 )
    {
        *from = NearPhase( *from, *to );
        from++;
        to++;
    }
}

void GV_NearRangeV( void *vfrom, void *vto, int range, int n )
{
    short *from, *to;

    from = (short *)vfrom;
    to = (short *)vto;
    while ( --n >= 0 )
    {
        *from = NearRange( *from, *to, range );
        from++;
        to++;
    }
}

void GV_NearSpeedV( void *vfrom, void *vto, int speed, int n )
{
    short *from, *to;

    from = (short *)vfrom;
    to = (short *)vto;
    while ( --n >= 0 )
    {
        *from = NearSpeed( *from, *to, speed );
        from++;
        to++;
    }
}

void GV_NearTimeV( void *vfrom, void *vto, int interp, int n )
{
    short *from, *to;

    if ( interp > 15 ) interp = 15;
    interp = TimeInv[ interp ];
    from = (short *)vfrom;
    to = (short *)vto;
    while ( --n >= 0 )
    {
        *from = NearTime( *from, *to, interp );
        from++;
        to++;
    }
}

/*----------------------------------------------------------------*/

void GV_NearExp2PV( void *vfrom, void *vto, int n )
{
    short *from, *to;

    from = (short *)vfrom;
    to = (short *)vto;
    while ( --n >= 0 )
    {
        *from = NearExp2P( *from, *to );
        from++;
        to++;
    }
}

void GV_NearExp4PV( void *vfrom, void *vto, int n )
{
    short *from, *to;

    from = (short *)vfrom;
    to = (short *)vto;
    while ( --n >= 0 )
    {
        *from = NearExp4P( *from, *to );
        from++;
        to++;
    }
}

void GV_NearExp8PV( void *vfrom, void *vto, int n )
{
    short *from, *to;

    from = (short *)vfrom;
    to = (short *)vto;
    while ( --n >= 0 )
    {
        *from = NearExp8P( *from, *to );
        from++;
        to++;
    }
}

void GV_NearExp2SV( void *vfrom, void *vto, int speed, int n )
{
    short *from, *to;

    from = (short *)vfrom;
    to = (short *)vto;
    while ( --n >= 0 )
    {
        *from = NearExp2S( *from, *to, speed );
        from++;
        to++;
    }
}

void GV_NearExp4SV( void *vfrom, void *vto, int speed, int n )
{
    short *from, *to;

    from = (short *)vfrom;
    to = (short *)vto;
    while ( --n >= 0 )
    {
        *from = NearExp4S( *from, *to, speed );
        from++;
        to++;
    }
}

void GV_NearExp8SV( void *vfrom, void *vto, int speed, int n )
{
    short *from, *to;

    from = (short *)vfrom;
    to = (short *)vto;
    while ( --n >= 0 )
    {
        *from = NearExp8S( *from, *to, speed );
        from++;
        to++;
    }
}

void GV_NearTimePV( void *vfrom, void *vto, int interp, int n )
{
    short *from, *to;

    if ( interp > 15 ) interp = 15;
    interp = TimeInv[ interp ];
    from = (short *)vfrom;
    to = (short *)vto;
    while ( --n >= 0 )
    {
        *from = NearTime( NearPhase( *from, *to ) , *to, interp );
        from++;
        to++;
    }
}
