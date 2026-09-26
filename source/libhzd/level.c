#include "libhzd.h"
#include "private.h"

#include "mgstype.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "inline_n.h"

/*---------------------------------------------------------------------------*/

typedef struct {
    char     unused1[ 8 ];
    int      side;
    HZD_VEC  from;
    char     unused2[ 32 ];
    DVECTOR  p1_from;
    DVECTOR  normal;
    HZD_FLR *flrs[ 2 ];
    int      lvls[ 2 ];
} ScrPad;

#define SCRPAD      ((ScrPad *)SCRPAD_ADDR)

#define	TEMP		(&(SCRPAD->temp))
#define	SIDE		(&(SCRPAD->side))
#define	FROM		(&(SCRPAD->from))
#define	P1_FROM		(&(SCRPAD->p1_from))
#define	NORMAL		(&(SCRPAD->normal))
#define	FLOOR_PTR   (SCRPAD->flrs[ 0 ])
#define	CEIL_PTR    (SCRPAD->flrs[ 1 ])
#define	FLOOR_LVL   (SCRPAD->lvls[ 0 ])
#define	CEIL_LVL    (SCRPAD->lvls[ 1 ])

static inline int CheckFloorBound( HZD_FLR *flr, HZD_VEC *from )
{
    if (flr->b1.z > from->z || flr->b2.z < from->z ||
        flr->b1.x > from->x || flr->b2.x < from->x)
    {
        return 0;
    }

    return 1;
}

/*---------------------------------------------------------------------------*/

static void FV_to_HV( SVECTOR *sv, HZD_VEC *hv )
{
    hv->x = sv->vx;
    hv->y = sv->vy;
    hv->z = sv->vz;
}

static int CheckInsideFloor( HZD_FLR *flr )
{
    int p0, p1, p2, p3, p4;

    p0 = FROM->long_access[ 0 ];
    p1 = flr->p1.long_access[ 0 ];
    p2 = flr->p2.long_access[ 0 ];

    gte_ldsxy3( p1, p2, p0 );
    gte_nclip();
    p3 = flr->p3.long_access[ 0 ];
    gte_stopz( SIDE );

    if ( *SIDE >= 0 )
    {
        gte_ldsxy3( p2, p3, p0 );
        gte_nclip();
        p4 = flr->p4.long_access[ 0 ];
        gte_stopz( SIDE );
        if ( *SIDE < 0 ) return 0;

        gte_ldsxy3( p3, p4, p0 );
        gte_nclip();
        gte_stopz( SIDE );
        if ( *SIDE < 0 ) return 0;

        gte_ldsxy3( p4, p1, p0 );
        gte_nclip();
        gte_stopz( SIDE );
        return *SIDE >= 0;
    }
    else
    {
        gte_ldsxy3( p2, p3, p0 );
        gte_nclip();
        p4 = flr->p4.long_access[ 0 ];
        gte_stopz( SIDE );
        if ( *SIDE > 0 ) return 0;

        gte_ldsxy3( p3, p4, p0 );
        gte_nclip();
        gte_stopz( SIDE );
        if ( *SIDE > 0 ) return 0;

        gte_ldsxy3( p4, p1, p0 );
        gte_nclip();
        gte_stopz( SIDE );
        return *SIDE <= 0;
    }
}

static int SlopeFloorLevel( HZD_FLR *flr )
{
    int pf_n;

    Sub2D( P1_FROM, (DVECTOR *)FROM, (DVECTOR *)&flr->p1 );
    NORMAL->vx = flr->p1.h;
    NORMAL->vy = flr->p2.h;
    pf_n = InnerProduct2D( P1_FROM, NORMAL );
    return flr->p1.y - pf_n / flr->p3.h;
}

static void CheckFloor( HZD_FLR *flr )
{
    int flag, level;

    flag = flr->b1.h;

    if ( ( flag & 1 ) || CheckInsideFloor( flr ) )
    {
        if ( flag & 2 )
        {
            level = flr->b1.y;
        }
        else
        {
            level = SlopeFloorLevel( flr );
        }

        if ( FROM->y >= level )
        {
            if ( level > FLOOR_LVL )
            {
                FLOOR_LVL = level;
                FLOOR_PTR = flr;
            }
        }
        else
        {
            if ( level < CEIL_LVL )
            {
                CEIL_LVL = level;
                CEIL_PTR = flr;
            }
        }
    }
}

/*---------------------------------------------------------------------------*/

int HZD_LevelHazardCheck( HZD_HDL *hzd, SVECTOR *from, int chk_flag )
{
    HZD_GRP *grp;
    HZD_FLR *flr, **dynflr;
    int i;

    grp = hzd->grp;

    FV_to_HV( from, FROM );

    FLOOR_PTR = CEIL_PTR = NULL;
    FLOOR_LVL = -1000000;
    CEIL_LVL = 1000000;

    if ( chk_flag & HZD_CHK_F_FLOOR )
    {
        flr = grp->floors;
        for ( i = grp->n_floors; i > 0; i--, flr++ )
        {
            if ( CheckFloorBound( flr, FROM ) )
            {
                CheckFloor( flr );
            }
        }
    }

    if ( chk_flag & HZD_CHK_D_FLOOR )
    {
        dynflr = hzd->dynamic_floors;
        for ( i = hzd->dynamic_floor_index; i > 0; i--, dynflr++ )
        {
            if ( CheckFloorBound( *dynflr, FROM ) )
            {
                CheckFloor( *dynflr );
            }
        }
    }

    if ( CEIL_PTR == NULL )
    {
        return ( FLOOR_PTR == NULL ) ? 0 : 1;
    }
    else
    {
        return ( FLOOR_PTR == NULL ) ? 2 : 3;
    }
}

void HZD_GetLevelHazard( HZD_FLR **flr )
{
    flr[ 0 ] = FLOOR_PTR;
    flr[ 1 ] = CEIL_PTR;
}

void HZD_GetLevelHeight( int *lvl_ptr )
{
    lvl_ptr[ 0 ] = FLOOR_LVL;
    lvl_ptr[ 1 ] = CEIL_LVL;
}

int HZD_SlopeFloorLevel( SVECTOR *from, HZD_FLR *flr )
{
    FV_to_HV( from, FROM );
    return SlopeFloorLevel( flr );
}

int HZD_LevelHazardCheckOne( HZD_FLR *flr, SVECTOR *from )
{
    FV_to_HV( from, FROM );

    FLOOR_PTR = CEIL_PTR = NULL;
    FLOOR_LVL = -1000000;
    CEIL_LVL = 1000000;

    if ( CheckFloorBound( flr, FROM ) )
    {
        CheckFloor( flr );
    }

    if ( CEIL_PTR == NULL )
    {
        return ( FLOOR_PTR == NULL ) ? 0 : 1;
    }
    else
    {
        return ( FLOOR_PTR == NULL ) ? 2 : 3;
    }
}

int HZD_GetLevelAtr( void )
{
    if ( FLOOR_PTR == NULL ) return 0;
    return FLOOR_PTR->b1.h >> 8;
}
