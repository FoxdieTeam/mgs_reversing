#include "libhzd.h"
#include "private.h"

#include "mgstype.h"
#include "inline_n.h"
#include "inline_x.h"
#include "libdg/libdg.h"

/*---------------------------------------------------------------------------*/

/* in game/map.c */
extern HZD_HDL *GM_IterHazard( HZD_HDL *cur );

typedef struct {
    /* 0x00 */ char    reserved[ 8 ];
    /* 0x08 */ int     side;
    /* 0x0C */ HZD_VEC from;
    /* 0x14 */ HZD_VEC to;
    /* 0x1C */ HZD_VEC step;
    /* 0x24 */ SVECTOR bmin;
    /* 0x2C */ SVECTOR bmax;
    /* 0x34 */ HZD_SEG p;
    /* 0x44 */ DVECTOR p1_from;
    /* 0x48 */ DVECTOR p1_p2;
    /* 0x4C */ HZD_VEC cross;
    /* 0x54 */ HZD_VEC mincross;
    /* 0x5C */ int     minlen;
    /* 0x60 */ int     flat;
    /* 0x64 */ void   *hzd;
    /* 0x68 */ short   atr;
    /* 0x6C */ int     hit;
    /* 0x70 */ char    pad1[ 0x4 ];
    /* 0x74 */ int     field_74;
    /* 0x78 */ int     field_78;
    /* 0x7C */ char    pad2[ 0x10 ];
    /* 0x8C */ int     field_8C;
    /* 0x90 */ MATRIX  field_90;
    /* 0xB0 */ MATRIX  field_B0;
} ScrPad;

#define SCRPAD   ((ScrPad *)SCRPAD_ADDR)

#define	SIDE     (&(SCRPAD->side))
#define	FROM     (&(SCRPAD->from))
#define	TO       (&(SCRPAD->to))
#define	STEP     (&(SCRPAD->step))
#define	BMIN     (&(SCRPAD->bmin))
#define	BMAX     (&(SCRPAD->bmax))
#define	P        (&(SCRPAD->p))
#define	P1_FROM  (&(SCRPAD->p1_from))
#define	P1_P2    (&(SCRPAD->p1_p2))
#define	CROSS    (&(SCRPAD->cross))
#define	MINCROSS (&(SCRPAD->mincross))
#define	MINLEN   (&(SCRPAD->minlen))
#define	FLAT     (&(SCRPAD->flat))
#define	HZD      (&(SCRPAD->hzd))
#define	ATR      (&(SCRPAD->atr))
#define	HIT      (&(SCRPAD->hit))
#define	FIELD_74 (&(SCRPAD->field_74))
#define	FIELD_78 (&(SCRPAD->field_78))
#define	FIELD_8C (&(SCRPAD->field_8C))
#define	FIELD_90 (&(SCRPAD->field_90))
#define	FIELD_B0 (&(SCRPAD->field_B0))

static inline int CheckFloorBound( void )
{
    if ( P->p1.z > BMAX->vz || P->p2.z < BMIN->vz ||
         P->p1.x > BMAX->vx || P->p2.x < BMIN->vx ||
         P->p1.y > BMAX->vy || P->p2.y < BMIN->vy )
    {
        return 0;
    }

    return 1;
}

static inline int CheckCross( void )
{
    if ( CROSS->x < P->p1.x || CROSS->x > P->p2.x ||
         CROSS->z < P->p1.z || CROSS->z > P->p2.z )
    {
        return 0;
    }

    return 1;
}

static inline void SV_to_HV( SVECTOR *sv, HZD_VEC *hv )
{
    hv->x = sv->vx;
    hv->y = sv->vy;
    hv->z = sv->vz;
}

/*---------------------------------------------------------------------------*/

static int MakeStepXZ( void )
{
    int len;

    STEP->x = TO->x - FROM->x;
    STEP->y = TO->y - FROM->y;
    STEP->z = TO->z - FROM->z;

    len = Length2D( (DVECTOR *)STEP );
    if ( len == 0 ) return 0;

    STEP->x = STEP->x * 256 / len;
    STEP->y = STEP->y * 256 / len;
    STEP->z = STEP->z * 256 / len;
    return len;
}

static void MakeBound( HZD_VEC *from, HZD_VEC *to )
{
    int d1, d2, temp;

    d1 = from->x; d2 = to->x;
    if (d2 < d1)
    {
        temp = d1;
        d1 = d2;
        d2 = temp;
    }
    BMIN->vx = d1;
    BMAX->vx = d2;

    d1 = from->y; d2 = to->y;
    if (d2 < d1)
    {
        temp = d1;
        d1 = d2;
        d2 = temp;
    }
    BMIN->vy = d1;
    BMAX->vy = d2;

    d1 = from->z; d2 = to->z;
    if (d2 < d1)
    {
        temp = d1;
        d1 = d2;
        d2 = temp;
    }
    BMIN->vz = d1;
    BMAX->vz = d2;
}

static int CheckSegmentConflict( void )
{
    int d1, d2, tmp;
    int y, y1, y2;

    if ( P->p1.x > BMAX->vx || P->p2.x < BMIN->vx ) return 0;

    d1 = P->p1.z;
    d2 = P->p2.z;

    if ( d1 > d2 )
    {
        tmp = d1;
        d1 = d2;
        d2 = tmp;
    }

    if (d1 > BMAX->vz || d2 < BMIN->vz ) return 0;

    y = BMAX->vy;
    y1 = P->p1.y;
    y2 = P->p2.y;
    if ( y1 > y && y2 > y ) return 0;

    y = BMIN->vy;
    y1 += P->p1.h;
    y2 += P->p2.h;
    if ( y1 < y && y2 < y ) return 0;

    return 1;
}

static int SegmentDistance( void )
{
    int hxv, dxh, len;
    long p1_p2, p1_from;

    Sub2D( P1_P2, (DVECTOR *)&P->p2, (DVECTOR *)&P->p1 );
    p1_p2 = *(long *)P1_P2;

    gte_ldsxy3( 0, p1_p2, *(long *)STEP );
    gte_nclip();

    P1_FROM->vx = FROM->x - P->p1.x;
    P1_FROM->vy = FROM->z - P->p1.z;

    gte_read_opz( hxv );

    // Can't get an absolute load of P1_FROM without this.
    asm volatile (" lw %0, 0(%1) " : "=r"( p1_from ) : "r"( P1_FROM ) );

    hxv /= 16;
    if ( hxv == 0 ) return 1000000;

    gte_ldsxy3( 0, p1_from, p1_p2 );
    gte_nclip();
    gte_read_opz( dxh );

    if ( dxh < 0 )
    {
        dxh = -dxh;
        hxv = -hxv;
    }

    if ( dxh >= 150994944 )
    {
        len = dxh / ( hxv / 16 );
    }
    else
    {
        len = ( dxh * 16 ) / hxv;
    }

    if ( len < 0 ) return 1000000;
    return len;
}

static int CheckSegmentCross( int len )
{
    int cross;

    CROSS->x = FROM->x + STEP->x * len / 256;
    CROSS->y = FROM->y + STEP->y * len / 256;
    CROSS->z = FROM->z + STEP->z * len / 256;

    if ( P1_P2->vx != 0 )
    {
        cross = CROSS->x;
        if ( cross < ( P->p1.x - 32 ) || cross > ( P->p2.x + 32 ) ) return 0;
        return 1;
    }
    else
    {
        cross = CROSS->z;
        if ( cross < ( P->p1.z - 32 ) || cross > ( P->p2.z + 32 ) ) return 0;
        return 2;
    }
}

static void CalculateSegmentHeight( int axis )
{
    int depth;

    if ( axis == 1 )
    {
        depth = ( CROSS->x - P->p1.x ) * 4096 / P1_P2->vx;
    }
    else
    {
        depth = ( CROSS->z - P->p1.z ) * 4096 / P1_P2->vy;
    }

    gte_lddp( depth );
    gte_ld_intpol_sv0( &P->p2.y );
    gte_ld_intpol_sv1( &P->p1.y );
    gte_intpl();
    gte_stsv( &P->p1.y );
}

static void CheckOneSegment( HZD_SEG *seg, int index, int flag )
{
    int len, axis, cross;

    char    *scratch3;
    int      tmp3;
    char    *tmp5;
    short    tmp6;

    *P = *seg;

    if ( !CheckSegmentConflict() ) return;

    len = SegmentDistance();
    axis = CheckSegmentCross( len );
    if ( axis == 0 ) return;

    if ( index > *FLAT )
    {
        CalculateSegmentHeight( axis );
    }

    cross = CROSS->y - P->p1.y;
    if ( cross < 0 || cross > P->p1.h ) return;

    *HIT += 1;

    if ( len > *MINLEN ) return;

    *MINCROSS = *CROSS;
    *MINLEN = len;

    scratch3 = (char *)SCRPAD_ADDR;
    do {} while ( 0 );

    tmp5 = *(char **)(scratch3 + 0x70);
    tmp6 = *(short *)(scratch3 + 0x6A);
    axis = flag & 0x7F;

    do {} while ( 0 );

    *HZD = seg;
    tmp3 = *(tmp5 - index);
    tmp3 <<= 8;
    *ATR = tmp6 | axis | tmp3;
}

static int DistanceTo( HZD_VEC *to )
{
    int d, len;

    len = to->x - FROM->x;
    if ( len < 0 ) len = -len;

    d = to->y - FROM->y;
    if ( d < 0 ) d = -d;
    len += d;

    d = to->z - FROM->z;
    if ( d < 0 ) d = -d;
    len += d;

    return len;
}

static int FloorDistance( void )
{
    int y;

    y = P->p1.y;
    if ( y == *FIELD_74 ) return *FIELD_78;

    gte_lddp( ( y - FROM->y ) * 4096 / ( TO->y - FROM->y ) );
    gte_ld_intpol_sv0( TO );
    gte_ld_intpol_sv1( FROM );
    gte_intpl();
    gte_stsv( CROSS );

    *FIELD_74 = y;
    *FIELD_78 = DistanceTo( CROSS );
    return *FIELD_78;
}

static int CheckInsideFloor( HZD_FLR *flr )
{
    long p0, p1, p2, p3, p4;

    p0 = CROSS->long_access[ 0 ];
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

        gte_NormalClip(p3, p4, p0, SIDE );
        if( *SIDE < 0 ) return 0;

        gte_NormalClip(p4, p1, p0, SIDE );
        return *SIDE >= 0;
    }
    else
    {
        gte_ldsxy3( p2, p3, p0 );
        gte_nclip();
        p4 = flr->p4.long_access[ 0 ];
        gte_stopz( SIDE );
        if ( *SIDE > 0 ) return 0;

        gte_NormalClip(p3, p4, p0, SIDE );
        if ( *SIDE > 0 ) return 0;

        gte_NormalClip(p4, p1, p0, SIDE );
        return *SIDE <= 0;
    }
}

static inline void GetFloorHeight(SVECTOR *dst, HZD_FLR *a, HZD_VEC *b)
{
    dst->vx = a->p1.x - b->x;
    dst->vy = a->p1.y - b->y;
    dst->vz = a->p1.z - b->z;
}

static inline int GetScratch(int offset)
{
    int *ptr = (int *)SCRPAD_ADDR;
    return ptr[offset];
}

static inline void SetScratch(int offset, int value)
{
    int *ptr = (int *)SCRPAD_ADDR;
    ptr[offset] = value;
}

static void CheckOneFloor( HZD_FLR *flr )
{
    int flag;

    int length;
    int n, d;

    *P = *(HZD_SEG *)flr;

    if ( !CheckFloorBound() ) return;

    flag = P->p1.h;

    if ( flag & HZD_FLOOR_FLAT )
    {
        if ( FROM->y == TO->y ) return;
        length = FloorDistance();
    }
    else
    {
        if ( GetScratch(0x23) == 0)
        {
            gte_ReadRotMatrix( FIELD_90 );
            SetScratch(0x23, 1);
        }

        SetScratch(0x1F, flr->p1.h);
        SetScratch(0x20, flr->p3.h);
        SetScratch(0x21, flr->p2.h);

        gte_ldlvl(0x1F80007C);

        GetFloorHeight((SVECTOR *)0x1F8000B0, (HZD_FLR *)0x1F800004, (HZD_VEC *)0x1F80000C);
        GetFloorHeight((SVECTOR *)0x1F8000B6, flr, (HZD_VEC *)0x1F80000C);

        gte_SetRotMatrix( FIELD_B0 );
        gte_rtir();
        gte_stlvnl(0x1F80007C);

        n = *(int *)0x1F800080;
        d = *(int *)0x1F80007C;

        if ( ( d < 0 && n < 0 ) || ( d > 0 && n > 0 ) )
        {
            *FIELD_74 = 1000000;
            *(short *)0x1F80004C = *(short *)0x1F80000C + ( *(short *)0x1F8000B0 * n ) / d;
            *(short *)0x1F800050 = *(short *)0x1F800010 + ( *(short *)0x1F8000B2 * n ) / d;
            *(short *)0x1F80004E = *(short *)0x1F80000E + ( *(short *)0x1F8000B4 * n ) / d;
            length = DistanceTo( CROSS );
        }
        else
        {
            length = 1000000;
        }
    }

    if ( length >= *MINLEN ) return;
    if ( !CheckCross() ) return;

    if ( ( flag & HZD_FLOOR_RECT ) || CheckInsideFloor( flr ) )
    {
        *HIT += 1;
        *MINCROSS = *CROSS;
        *MINLEN = length;
        *HZD = (void *)( (u_int)flr & ~0x80000000 );
    }
}

/*---------------------------------------------------------------------------*/

int HZD_OnlineHazardCheck( HZD_HDL *hzd, SVECTOR *from, SVECTOR *to, int chk_flag, int seg_flag )
{
    int group, i, j, n_flat, queue_size, idx;
    HZD_GRP *grp;
    HZD_SEG *seg, **dynseg;
    char *flag, *flag2, *flag3;
    HZD_HDL *next;
    HZD_FLR  *flr, **dynflr;

    int bit1, bit2;
    int n_areas;

    group = HZD_CurrentGroup;

    SV_to_HV( from, FROM );
    *HIT = 0;
    *HZD = NULL;
    SV_to_HV( to, TO );
    *MINCROSS = *TO;
    *FIELD_8C = 0;

    MakeBound( FROM, MINCROSS );

    *MINLEN = MakeStepXZ();
    if ( *MINLEN == 0 ) return 0;

    if ( chk_flag & HZD_CHK_F_SEGMENT )
    {
        char *scratchpad;

        bit2 = 1;
        grp = hzd->def->groups;

        for ( i = hzd->def->n_groups; i > 0; i--, bit2 <<= 1, grp++ )
        {
            if ( !( group & bit2 ) ) continue;

            do
            {
                seg = grp->walls;
                flag = grp->wallsFlags;
                do {} while (0);
                n_flat = grp->n_flat_walls;
                flag2 = flag + 2 * grp->n_walls;
                scratchpad = (char *)SCRPAD_ADDR;
                *((short *)(scratchpad + 0x6A)) = 0;
            } while (0);

            *((char **)(scratchpad + 0x70)) = flag2;
            *FLAT = n_flat;

            for ( j = grp->n_walls; j > 0; j--, seg++, flag++ )
            {
                if ( !( *flag & seg_flag ) )
                {
                    CheckOneSegment( seg, j, *flag );
                }
            }
        }
    }

    if ( chk_flag & HZD_CHK_D_SEGMENT )
    {
        char *scratchpad;

        next = NULL;
        while ( ( next = GM_IterHazard( next ) ) != NULL )
        {
            scratchpad = (char *)SCRPAD_ADDR;
            do
            {
                dynseg = next->dynamic_segments;
                flag = next->dynamic_flags;
                queue_size = next->max_dynamic_segments;
                idx = next->dynamic_queue_index;
                *((short *)(scratchpad + 0x6A)) = 0x80;
                do
                {
                } while (0);

                flag3 = (flag + queue_size) + idx;
                *((char **)(scratchpad + 0x70)) = flag3;
            } while (0); // TODO: Is it the same macro as above in "if (chk_flag & HZD_CHK_F_SEGMENT)" case?

            j = next->dynamic_queue_index;
            *FLAT = 0;

            for ( ; j > 0; j--, dynseg++, flag++ )
            {
                if ( !( *flag & seg_flag ) )
                {
                    CheckOneSegment( *dynseg, j, *flag );
                }
            }
        }
    }

    MakeBound( FROM, MINCROSS );
    *MINLEN = DistanceTo( MINCROSS );
    *FIELD_74 = 1000000;

    if ( chk_flag & HZD_CHK_F_FLOOR )
    {
        bit1 = 1;
        grp = hzd->def->groups;
        for ( n_areas = hzd->def->n_groups; n_areas > 0; n_areas--, bit1 <<= 1, grp++ )
        {
            if ( group & bit1 )
            {
                flr = grp->floors;
                for ( j = grp->n_floors; j > 0; j-- )
                {
                    CheckOneFloor( flr );
                    flr++;
                }
            }
        }
    }

    if ( chk_flag & HZD_CHK_D_FLOOR )
    {
        next = NULL;
        while ( ( next = GM_IterHazard( next ) ) != NULL )
        {
            dynflr = next->dynamic_floors;
            for ( j = next->dynamic_floor_index; j > 0; j--, dynflr++ )
            {
                CheckOneFloor( *dynflr );
            }
        }
    }

    if ( *FIELD_8C != 0 )
    {
        gte_SetRotMatrix( FIELD_90 );
    }

    if ( *HZD != NULL )
    {
        return *HIT;
    }

    return 0;
}

void *HZD_GetOnlineHazard( void )
{
    return *HZD;
}

int HZD_GetOnlineHazardAtr( void )
{
    return *ATR;
}

void HZD_GetOnlineVector( SVECTOR *vect_ptr )
{
    vect_ptr->vx = MINCROSS->x - FROM->x;
    vect_ptr->vy = MINCROSS->y - FROM->y;
    vect_ptr->vz = MINCROSS->z - FROM->z;
}

void HZD_GetOnlinePoint( SVECTOR *ptp_ptr )
{
    ptp_ptr->vx = MINCROSS->x;
    ptp_ptr->vy = MINCROSS->y;
    ptp_ptr->vz = MINCROSS->z;
}
