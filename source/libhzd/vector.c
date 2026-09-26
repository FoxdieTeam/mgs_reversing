#include "libhzd.h"
#include "private.h"

#include "mgstype.h"
#include "inline_n.h"
#include "inline_x.h"
#include "libgv/libgv.h"        // for GV_VecLen3

/*---------------------------------------------------------------------------*/

typedef struct {
    char    unused[ 12 ];
    DVECTOR vec1;
    DVECTOR vec2;
    DVECTOR react1;
    DVECTOR react2;
} ScrPad;

#define SCRPAD ((ScrPad *)SCRPAD_ADDR)

#define	VEC1   (&(SCRPAD->vec1))
#define	VEC2   (&(SCRPAD->vec2))
#define REACT1 (&(SCRPAD->react1))
#define REACT2 (&(SCRPAD->react2))

/*---------------------------------------------------------------------------*/

int HZD_HazardReaction( SVECTOR *vects, int n_vects, int range, SVECTOR *react )
{
    int len0, len1, rlen;
    int aoa, bob, aob, axb;

    react->vz = 0;
    react->vy = 0;
    react->vx = 0;
    if ( n_vects == 0 ) return 1;
    VEC1->vx = vects[ 0 ].vx;
    VEC1->vy = vects[ 0 ].vz;
    len0 = Length2D( VEC1 );
    if ( len0 >= range ) return 1;
    if ( len0 == 0 ) return 0;
    if ( n_vects == 2 )
    {
        VEC2->vx = vects[ 1 ].vx;
        VEC2->vy = vects[ 1 ].vz;
        len1 = Length2D( VEC2 );
        if ( len1 < range )
        {
            Scale2D( REACT1, VEC1, range, len0 );
            Scale2D( REACT2, VEC2, range, len1 );
            Sub2D( REACT1, REACT1, VEC1 );
            Sub2D( REACT2, REACT2, VEC2 );
            aoa = InnerProduct2D( REACT1, REACT1 );
            bob = InnerProduct2D( REACT2, REACT2 );
            aob = InnerProduct2D( REACT1, REACT2 );
            if ( aoa > aob && bob > aob )
            {
                axb = OuterProduct2D( REACT1, REACT2 );
                if ( axb != 0 )
                {
                    react->vx = ( REACT1->vy * bob - REACT2->vy * aoa ) / axb;
                    react->vz = ( REACT2->vx * aoa - REACT1->vx * bob ) / axb;
                    rlen = GV_VecLen3( react );
                    if ( rlen > ( range * 4 ) )
                    {
                        GV_LenVec3( react, react, rlen, range * 4 );
                    }
                }

                return 1;
            }
        }
    }

    Scale2D( REACT1, VEC1, range, len0 );
    Sub2D( REACT1, VEC1, REACT1 );
    react->vx = REACT1->vx;
    react->vz = REACT1->vy;
    return 1;
}

void HZD_NormalVector( void *hzd, SVECTOR *norm )
{
    if ( ( (HZD_VEC *)hzd )->h >= 0 ) // Wall
    {
        HZD_SEG *seg;

        seg = hzd;
        norm->vx = seg->p2.z - seg->p1.z;
        norm->vy = 0;
        norm->vz = seg->p1.x - seg->p2.x;
        GV_LenVec3( norm, norm, GV_VecLen3( norm ), 4096 );
    }
    else // Floor
    {
        HZD_FLR *flr;

        flr = hzd;
        norm->vx = flr->p1.h * 16;
        norm->vy = flr->p3.h * 16;
        norm->vz = flr->p2.h * 16;
    }
}
