#include "libhzd.h"
#include "private.h"

#include "mgstype.h"
#include "inline_n.h"
#include "inline_x.h"

/*---------------------------------------------------------------------------*/

typedef struct {
    int      is_edge;
    int      length;
    HZD_SEG *seg;
    int      atr;
    DVECTOR  nearest;
    DVECTOR  edge1;
    DVECTOR  edge2;
} Nearest;

typedef struct {
    char    reserved[ 12 ];
    HZD_VEC from;
    SVECTOR bound1;
    SVECTOR bound2;
    HZD_SEG p;
    DVECTOR p1_from;
    DVECTOR p1_p2;
    char    pad[ 8 ];
    int     flat;
    int     n_nears;
    Nearest this;
    Nearest first;
    Nearest second;
    DVECTOR tmp;
    int     lzc;
    int     doh;
    int     hoh;
    char   *flag[ 2 ];
} ScrPad;

#define SCRPAD  ((ScrPad *)SCRPAD_ADDR)

#define	FROM    (&(SCRPAD->from))
#define	BOUND1  (&(SCRPAD->bound1))
#define	BOUND2  (&(SCRPAD->bound2))
#define	P	    (&(SCRPAD->p))
#define	P1_FROM (&(SCRPAD->p1_from))
#define	P1_P2	(&(SCRPAD->p1_p2))
#define	FLAT	(&(SCRPAD->flat))
#define	N_NEARS	(&(SCRPAD->n_nears))
#define	THIS	(&(SCRPAD->this))
#define	FIRST	(&(SCRPAD->first))
#define	SECOND	(&(SCRPAD->second))
#define	TMP     (&(SCRPAD->tmp))
#define	LZC     (&(SCRPAD->lzc))
#define	DOH     (&(SCRPAD->doh))
#define	HOH     (&(SCRPAD->hoh))
#define	FLAG    (SCRPAD->flag)

static inline int CheckSegmentConflict( HZD_SEG *seg )
{
    int d1, d2, tmp;
    int y, y1, y2;

    if ( seg->p1.x > BOUND2->vx || seg->p2.x < BOUND1->vx ) return 0;

    d1 = seg->p1.z;
    d2 = seg->p2.z;

    if ( d2 < d1 )
    {
        tmp = d1;
        d1 = d2;
        d2 = tmp;
    }

    if ( d1 > BOUND2->vz || d2 < BOUND1->vz ) return 0;

    y = BOUND1->vy;
    y1 = seg->p1.y;
    y2 = seg->p2.y;
    if ( y1 > y && y2 > y ) return 0;

    y = BOUND2->vy;
    y1 += seg->p1.h;
    y2 += seg->p2.h;
    if ( y1 < y && y2 < y ) return 0;

    return 1;
}

/*---------------------------------------------------------------------------*/

static void SV_to_HV( SVECTOR *sv, HZD_VEC *hv )
{
    hv->x = sv->vx;
    hv->y = sv->vy;
    hv->z = sv->vz;
}

static void CreateBoundingBox( HZD_VEC *from, int sphere )
{
    int d;

    d = from->x;
    BOUND1->vx = d - sphere;
    BOUND2->vx = d + sphere;

    d = from->z;
    BOUND1->vz = d - sphere;
    BOUND2->vz = d + sphere;

    d = from->y;
    BOUND1->vy = BOUND2->vy = d;
}

static int SegmentNearest( void )
{
    int doh, hoh, dxh, num;

    Sub2D( P1_P2, (DVECTOR *)&P->p2, (DVECTOR *)&P->p1 );
    Sub2D( P1_FROM, (DVECTOR *)FROM, (DVECTOR *)&P->p1 );

    doh = InnerProduct2D( P1_P2, P1_FROM );

    THIS->is_edge = 1;
    *HOH = 1;

    if ( doh < 0 )
    {
        *DOH = 0;
        Sub2D( &THIS->nearest, (DVECTOR *)&P->p1, (DVECTOR *)FROM );
    }
    else
    {
        hoh = InnerProduct2D( P1_P2, P1_P2 );

        if ( hoh < doh )
        {
            *DOH = 1;
            Sub2D( &THIS->nearest, (DVECTOR *)&P->p2, (DVECTOR *)FROM );
        }
        else
        {
            dxh = OuterProduct2D( P1_P2, P1_FROM );

            gte_ldlzc( hoh );
            gte_stlzc( LZC );

            if ( 16 - *LZC > 0 )
            {
                doh >>= 16 - *LZC;
                dxh >>= 16 - *LZC;
                hoh >>= 16 - *LZC;
            }

            *DOH = doh;
            *HOH = hoh;

            num = P1_P2->vy * dxh;
            THIS->nearest.vx = num / hoh;
            if ( THIS->nearest.vx == 0 && num != 0 )
            {
                THIS->nearest.vx = ( num > 0 ) ? 1 : -1;
            }

            num = -P1_P2->vx * dxh;
            THIS->nearest.vy = num / hoh;
            if ( THIS->nearest.vy == 0 && num != 0 )
            {
                THIS->nearest.vy = ( num > 0 ) ? 1 : -1;
            }

            THIS->is_edge = 0;
            *(int *)&THIS->edge1 = *(int *)&P->p1;
            *(int *)&THIS->edge2 = *(int *)&P->p2;
        }
    }

    THIS->length = InnerProduct2D( &THIS->nearest, &THIS->nearest );
    return THIS->length;
}

static void DiagonalSegmentHeight( void )
{
    gte_lddp( *DOH * 4096 / *HOH );
    gte_ld_intpol_sv0( &P->p2.y );
    gte_ld_intpol_sv1( &P->p1.y );
    gte_intpl();
    gte_stsv( &P->p1.y );
}

static void CheckOneSegment( HZD_SEG *seg, int index, int flags )
{
    int len, cross;

    if ( !CheckSegmentConflict( seg ) ) return;

    *P = *seg;

    len = SegmentNearest();
    if ( len >= SECOND->length ) return;

    if ( index > *FLAT )
    {
        DiagonalSegmentHeight();
        cross = FROM->y - P->p1.y;
        if ( cross < 0 || cross > P->p1.h ) return;
    }

    THIS->seg = seg;
    THIS->atr = ( flags & 0x7F ) | (int)FLAG[ 0 ] | ( *( FLAG[ 1 ] - index ) << 8 );

    if ( len < FIRST->length )
    {
        *SECOND = *FIRST;
        *FIRST = *THIS;
    }
    else if ( *(int *)&THIS->nearest != *(int *)&FIRST->nearest )
    {
        *SECOND = *THIS;
    }
    else
    {
        return;
    }

    *N_NEARS += 1;
}

/*---------------------------------------------------------------------------*/

int HZD_NearHazardCheck( HZD_HDL *hzd, SVECTOR *from, int sphere, int chk_flag, int seg_flag )
{
    HZD_GRP *grp;
    int n_flat, n_seg, n_dynseg, max_seg, i;
    HZD_SEG *seg, **dynseg;
    char *flag;

    grp = hzd->grp;

    SV_to_HV( from, FROM );
    CreateBoundingBox( FROM, sphere );

    *N_NEARS = 0;

    if ( chk_flag & HZD_CHK_F_SEGMENT )
    {
        n_flat = grp->n_flat_walls;
        FIRST->length = SECOND->length = sphere * sphere;

        seg = grp->walls;
        flag = grp->wallsFlags;
        n_seg = grp->n_walls;

        FLAG[ 0 ] = NULL;
        FLAG[ 1 ] = flag + n_seg * 2;
        *FLAT = n_flat;

        for ( i = grp->n_walls; i > 0; i--, seg++, flag++ )
        {
            if ( !( *flag & seg_flag ) )
            {
                CheckOneSegment( seg, i, *flag );
            }
        }
    }

    if ( chk_flag & HZD_CHK_D_SEGMENT )
    {
        dynseg = hzd->dynamic_segments;
        flag = hzd->dynamic_flags;
        max_seg = hzd->max_dynamic_segments;
        n_dynseg = hzd->dynamic_queue_index;

        FLAG[ 0 ] = (char *)0x80;
        FLAG[ 1 ] = flag + max_seg + n_dynseg;
        *FLAT = 0;

        for ( i = hzd->dynamic_queue_index; i > 0; i--, dynseg++, flag++ )
        {
            if ( !( *flag & seg_flag ) )
            {
                CheckOneSegment( *dynseg, i, *flag );
            }
        }
    }

    if ( *N_NEARS <= 1 ) goto check_end;

    *N_NEARS = 2;
    if ( !SECOND->is_edge ) goto check_end;

    if ( FIRST->is_edge )
    {
        if ( *(int *)&FIRST->nearest != *(int *)&SECOND->nearest ) goto check_end;
    }
    else
    {
        Add2D( TMP, (DVECTOR *)FROM, &SECOND->nearest );
        if ( *(int *)TMP != *(int *)&FIRST->edge1 &&
             *(int *)TMP != *(int *)&FIRST->edge2 ) goto check_end;
    }

    *N_NEARS = 1;

check_end:
    return *N_NEARS;
}

void HZD_GetNearHazard( HZD_SEG **segs )
{
    segs[ 0 ] = FIRST->seg;
    segs[ 1 ] = SECOND->seg;
}

void HZX_GetNearHazardAtr( char *atrs )
{
    atrs[ 0 ] = FIRST->atr;
    atrs[ 1 ] = SECOND->atr;
}

void HZD_GetNearVector( SVECTOR *vect_ptr )
{
    vect_ptr[ 0 ].vx = FIRST->nearest.vx;
    vect_ptr[ 0 ].vy = 0;
    vect_ptr[ 0 ].vz = FIRST->nearest.vy;

    vect_ptr[ 1 ].vx = SECOND->nearest.vx;
    vect_ptr[ 1 ].vy = 0;
    vect_ptr[ 1 ].vz = SECOND->nearest.vy;
}
