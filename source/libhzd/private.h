#ifndef __MGS_LIBHZD_PRIVATE_H__
#define __MGS_LIBHZD_PRIVATE_H__

#include <sys/types.h>
#include <libgte.h>
#include "inline_n.h"
#include <gtemac.h>

#define	ZONE_HEIGHT (2000)

#define	MAX_ROUTE	(255)

#define SCRPAD ((ScrPad *)SCRPAD_ADDR)

#define	VECTOR (&(SCRPAD->vector))
#define	RESULT (&(SCRPAD->result))

static inline void Add2D( DVECTOR *v0, DVECTOR *v1, DVECTOR *v2 )
{
    v0->vx = v1->vx + v2->vx;
    v0->vy = v1->vy + v2->vy;
}

static inline void Sub2D( DVECTOR *v0, DVECTOR *v1, DVECTOR *v2 )
{
    v0->vx = v1->vx - v2->vx;
    v0->vy = v1->vy - v2->vy;
}

static inline void Scale2D( DVECTOR *v0, DVECTOR *v1, int num, int denom )
{
    v0->vx = v1->vx * num / denom;
    v0->vy = v1->vy * num / denom;
}

static inline long InnerProduct2D( DVECTOR *v1, DVECTOR *v2 )
{
    typedef struct {
        char    unused[ 4 ];
        DVECTOR vector;
        long    result;
    } ScrPad;

    VECTOR->vx = -v2->vy;
    VECTOR->vy = v2->vx;
	gte_ldsxy3( 0, *(long *)v1, *(long *)VECTOR );
	gte_nclip();
	gte_stopz( RESULT );
    return *(long *)RESULT;
}

static inline long OuterProduct2D( DVECTOR *v1, DVECTOR *v2 )
{
    typedef struct {
        char    unused[ 4 ];
        DVECTOR vector;
        long    result;
    } ScrPad;

	gte_ldsxy3( 0, *(long *)v1, *(long *)v2 );
	gte_nclip();
	gte_stopz( RESULT );
    return *(long *)RESULT;
}

static inline long Length2D( DVECTOR *v1 )
{
    return SquareRoot0( InnerProduct2D( v1, v1 ) );
}

#undef SCRPAD
#undef VECTOR
#undef RESULT

#endif // __MGS_LIBHZD_PRIVATE_H__
