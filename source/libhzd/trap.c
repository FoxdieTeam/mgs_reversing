#include "libhzd.h"

#include "mgstype.h"
#include "strcode.h"
#include "game/game.h"

typedef	struct {
    HZD_VEC from;
    HZD_SEG current;
    u_int   n_inside;
    u_short inside[ 6 ];
} ScrPad;

#define SCRPAD      ((ScrPad *)SCRPAD_ADDR)

#define	FROM		(&(SCRPAD->from))
#define	CURRENT		(&(SCRPAD->current))
#define	N_INSIDE    (&(SCRPAD->n_inside))
#define	INSIDE      (SCRPAD->inside)

/*----------------------------------------------------------------*/

static inline void CopyInsideList( HZD_EVT *ev )
{
    u_short *from, *to;
    int      i;

    from = ev->inside;
    to = INSIDE;
    *N_INSIDE = ev->n_inside;
    for ( i = ev->n_inside; i > 0; i-- )
    {
        *to++ = *from++;
    }
}

static inline int DeleteInsideList( int name )
{
    u_short *inside;
    int i;

    inside = INSIDE;
    for ( i = *N_INSIDE; i > 0; i-- )
    {
        if ( *inside++ == name )
        {
            ( *N_INSIDE )--;
            inside[ -1 ] = INSIDE[ *N_INSIDE ];
            return 1;
        }
    }

    return 0;
}

static inline int AppendInsideList( u_short *inside, int n_inside, int name )
{
    int i;

    for ( i = n_inside; i > 0; i-- )
    {
        if ( *inside++ == name ) return n_inside;
    }

    *inside = name;
    return n_inside + 1;
}

static inline void SV_to_HV( SVECTOR *sv, HZD_VEC *hv )
{
    hv->x = sv->vx;
    hv->y = sv->vy;
    hv->z = sv->vz;
}

static inline int InsideTrap( void )
{
    int d;

    d = FROM->x;
    if ( d < CURRENT->p1.x || d >= CURRENT->p2.x ) return 0;
    d = FROM->z;
    if ( d < CURRENT->p1.z || d >= CURRENT->p2.z ) return 0;
    d = FROM->y;
    if ( d < CURRENT->p1.y || d >= CURRENT->p2.y ) return 0;
    return 1;
}

/*----------------------------------------------------------------*/

static void ExecEnterEvent( HZD_HDL *hzd, HZD_EVT *ev )
{
    HZD_GRP *grp;
    HZD_TRP *trap;
    int n_inside, i, name;

    grp = hzd->grp;
    trap = (HZD_TRP *)grp->triggers;

    ev->type = HASH_ENTER;

    n_inside = 0;
    for ( i = grp->n_triggers - hzd->n_cameras; i > 0; i--, trap++ )
    {
        *CURRENT = *(HZD_SEG *)trap;
        if ( !InsideTrap() ) continue;

        name = trap->name_id;
        ev->object = name;
        if ( !DeleteInsideList( name ) )
        {
            HZD_ExecEvent( hzd, ev, 1 );
        }
        else
        {
            HZD_ExecEvent( hzd, ev, 2 );
        }

        n_inside = AppendInsideList( ev->inside, n_inside, name );
    }

    ev->n_inside = n_inside;
}

static void ExecLeaveEvent( HZD_HDL *hzd, HZD_EVT *ev )
{
    u_short *inside;
    int i;

    ev->type = HASH_LEAVE;

    inside = INSIDE;
    for ( i = *N_INSIDE; i > 0; i-- )
    {
        ev->object = *inside++;
        HZD_ExecEvent( hzd, ev, 0 );
    }
}

void HZD_EnterTrap( HZD_HDL *hzd, HZD_EVT *ev )
{
    u_short *from, *to;
    int i;

    SV_to_HV( &ev->coord, FROM );

    from = ev->inside;
    to = INSIDE;
    *N_INSIDE = ev->n_inside;

    for ( i = ev->n_inside; i > 0; i-- )
    {
        *to++ = *from++;
    }

    ExecEnterEvent( hzd, ev );
    ExecLeaveEvent( hzd, ev );
}

HZD_TRP *HZD_CheckBehindTrap( HZD_HDL *hzd, SVECTOR *pos )
{
    HZD_TRP *trap;
    int i;

    SV_to_HV( pos, FROM );

    trap = hzd->traps;
    for ( i = hzd->n_cameras; i > 0; i-- )
    {
        *CURRENT = *(HZD_SEG *)trap;
        if ( InsideTrap() ) return trap;
        trap++;
    }

    return NULL;
}
