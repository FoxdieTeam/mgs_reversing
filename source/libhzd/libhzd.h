#ifndef __MGS_LIBHZD_H__
#define __MGS_LIBHZD_H__

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "fmt_hzd.h"

#define OFFSET_TO_PTR(ptr, offset) (*(int *)offset = (int)ptr + *(int *)offset)

typedef struct {
    HZD_DEF     *def;
    HZD_GRP     *grp;
    short        map;
    short        dynamic_queue_index;
    short        dynamic_floor_index;
    short        n_cameras;
    short        max_dynamic_floors;
    short        max_dynamic_segments;
    u_char      *route;
    HZD_TRP     *traps;
    HZD_FLR    **dynamic_floors;
    HZD_SEG    **dynamic_segments;
    char        *dynamic_flags;
} HZD_HDL;

typedef struct {
    u_short     name;
    u_short     type;
    u_short     object;
    short       n_inside;
    u_short     inside[6];
    SVECTOR     mov;
} HZD_EVT;

typedef struct {
    short       field_0;         // Name of entity entering/leaving the trap
    short       field_2_param_m; // Mask of event type enter/leave to accept
    short       field_4;         // Name of the trap being hit
    u_short     map;
    u_char      field_8_param_i_c_flags;
    u_char      field_9_param_s;
    u_char      field_A_param_b;
    u_char      field_B_param_e;
    u_short     field_C_param_d;
    u_short     field_E_param_d_or_512;
    int         time;
    int         command;
} HZD_BND;

/*----------------------------------------------------------------*/

#define HZD_SEG_NO_COLLIDE    (0x01) /* collisions */
#define HZD_SEG_NO_NAVIGATE   (0x02) /* enemy navigation */
#define HZD_SEG_NO_PLAYER     (0x04) /* player sight */
#define HZD_SEG_NO_MISSILE    (0x08) /* missile collisions */
#define HZD_SEG_NO_HARITSUKI  (0x10) /* attach c4 */
#define HZD_SEG_NO_BULLET     (0x20) /* bullet collisions */
#define HZD_SEG_NO_BEHIND     (0x40) /* player lean */
#define HZD_SEG_NO_DISP_RADAR (0x80) /* radar draw */

#define HZD_CHK_F_FLOOR   (0x1)
#define HZD_CHK_D_FLOOR   (0x2)
#define HZD_CHK_F_SEGMENT (0x4)
#define HZD_CHK_D_SEGMENT (0x8)
#define HZD_CHK_ALL       ( HZD_CHK_F_SEGMENT | HZD_CHK_F_FLOOR | HZD_CHK_D_SEGMENT | HZD_CHK_D_FLOOR )
#define HZD_CHK_FIX		  ( HZD_CHK_F_FLOOR | HZD_CHK_F_SEGMENT )
#define HZD_CHK_DYNAMIC	  ( HZD_CHK_D_FLOOR | HZD_CHK_D_SEGMENT )
#define	HZD_CHK_SEGMENT	  ( HZD_CHK_F_SEGMENT | HZD_CHK_D_SEGMENT )
#define	HZD_CHK_FLOOR	  ( HZD_CHK_F_FLOOR | HZD_CHK_D_FLOOR )

#define HZD_NO_ZONE (0xFF)

enum
{
    HZD_REACH,
    HZD_DIRECT_REACH,
    HZD_INDIRECT_REACH,
    HZD_UNREACH
};

/*----------------------------------------------------------------*/

static inline int HZD_Address( int zone1, int zone2 )
{
    if ( zone2 < zone1 )
    {
        SWAP( zone1, zone2 );
    }

    return ( 255 & zone1 ) | ( ( 255 & zone2 ) << 8 );
}

static inline int HZD_ZoneAddress( int address )
{
    return ( 255 & address ) | ( ( 255 & address ) << 8 );
}

static inline int HZD_Zone1( int address )
{
    return 255 & address;
}

static inline int HZD_Zone2( int address )
{
    return 255 & ( address >> 8 );
}

/*----------------------------------------------------------------*/

/* hzdd.c */
#ifndef __LIBHZD_HZDD_C__
extern int HZD_CurrentGroup;
#endif

void HZD_StartDaemon( void );
int HZD_LoadInitHzd( void *buf, int id );
HZD_HDL *HZD_MakeHandler( HZD_DEF *hzd, int id, int n_d_seg, int n_d_flr );
void HZD_FreeHandler( HZD_HDL *hdl ) ;

/* route.c */
void HZD_MakeRoute( HZD_DEF *hzd, u_char *routes );

/* dynamic.c */
int HZD_QueueDynamicSegment2( HZD_HDL *hzd, HZD_SEG *seg, int flag );
void HZD_DequeueDynamicSegment( HZD_HDL *hzd, HZD_SEG *seg );
void HZD_SetDynamicSegment( HZD_SEG *a1, HZD_SEG *a2 );
int HZD_QueueDynamicFloor( HZD_HDL *hzd, HZD_FLR *flr );
void HZD_DequeueDynamicFloor( HZD_HDL *hzd, HZD_FLR *flr );

/* bind.c */
void HZD_SetBind(int, HZD_BND *bnd, int);
void HZD_BindMapChange( int mask );
void HZD_SetEvent( HZD_EVT *ev, int name );
void HZD_ExecBind( HZD_BND *bnd, HZD_EVT *ev, int, int );
void HZD_ReExecEvent(HZD_HDL *hzd, HZD_EVT *ev, unsigned int flags);
void HZD_ExecLeaveEvent(HZD_HDL *hzd, HZD_EVT *ev);
void HZD_ExecEvent(HZD_HDL *hzd, HZD_EVT *ev, int type);

/* trap.c */
void HZD_EnterTrap( HZD_HDL *hzd, HZD_EVT *ev );
HZD_TRP *HZD_CheckBehindTrap( HZD_HDL *hzd, SVECTOR *pos );

/* level.c */
int HZD_LevelHazardCheck( HZD_HDL *hzd, SVECTOR *from, int chk_flag );
void HZD_GetLevelHazard( HZD_FLR **flr );
void HZD_GetLevelHeight( int *lvl_ptr );
int HZD_SlopeFloorLevel( SVECTOR *mov, HZD_FLR *flr );
int HZD_GetFloorHit( HZD_FLR *flr, SVECTOR *mov );
int HZD_GetFloorLevel( void );

/* navigate.c */
int HZD_GetAddress( HZD_HDL *hzd, SVECTOR *pos, int address );
int HZD_ReachTo( HZD_HDL *hzd, int addr1, int addr2 );
int HZD_Navigate( HZD_HDL *hzd, int addr1, int addr2, SVECTOR *pos );
int HZD_Navigate2( HZD_HDL *hzd, int addr1, int addr2, SVECTOR *pos );
int HZD_ZoneDistance( HZD_HDL *hzd, int zone_from, int zone_to );
int HZD_OverDistanceZone( HZD_HDL *hzd, int zone_from, int zone_to, int dis_th );
int HZD_BoundOutZone( HZD_HDL *hzd, int zone_from, int zone_to, int dis_th );
int HZD_InsideZone( HZD_HDL *hzd, SVECTOR *pos, int zone );
int HZD_NearZones( HZD_HDL *hzd, int zone, int *near );
int HZD_FarZoneNavigate( HZD_HDL *hzd, int zone1, int zone2, int *rout );
int HZD_GetRoute( HZD_HDL *hzd, int zone1, int zone2 );

/* online.c */
int HZD_OnlineHazardCheck( HZD_HDL *hzd, SVECTOR *from, SVECTOR *to, int chk_flag, int seg_flag );
void *HZD_GetOnlineHazard( void );
int HZD_GetOnlineHazardAtr( void );
void HZD_GetOnlineVector( SVECTOR *vect_ptr );
void HZD_GetOnlinePoint( SVECTOR *ptp_ptr );

/* near.c */
int HZD_NearHazardCheck( HZD_HDL *hzd, SVECTOR *from, int range, int chk_flag, int seg_flag );
void HZD_GetNearHazard( HZD_SEG **segs );
void HZD_GetIsEdge( signed char *ie );
void HZD_GetNearVector( SVECTOR *vect_ptr );

/* vector.c */
int HZD_HazardReaction( SVECTOR *vects, int n_vects, int range, SVECTOR *react );
void HZD_GetNormal( void *hzd, SVECTOR *norm );

#endif // __MGS_LIBHZD_H__
