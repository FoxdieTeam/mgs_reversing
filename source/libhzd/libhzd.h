#ifndef _LIBHZD_H_
#define _LIBHZD_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "fmt_hzd.h"

#define OFFSET_TO_PTR(ptr, offset) (*(int *)offset = (int)ptr + *(int *)offset)

typedef struct {
    HZD_MAP     *header;
    HZD_GRP     *group;
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
    u_short     last;
    short       n_triggers;
    u_short     triggers[6];
    SVECTOR     pos;
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
    int         field_10_every;
    int         field_14_proc_and_block;
} HZD_BIND;

static inline int HZD_addr_shift( int addr )
{
    int temp = addr & 0xFF;
    return ( temp  | temp << 8 );
}

/* hzdd.c */
#ifndef __HZDD_SBSS__
extern int HZD_CurrentGroup;
#endif

void HZD_StartDaemon(void);
int  HZD_LoadInitHzd(void *buf, int id);
HZD_HDL *HZD_MakeHandler(HZD_MAP *hzd, int areaIndex, int dynamic_segments, int dynamic_floors);
void HZD_FreeHandler(void *ptr);
void HZD_MakeRoute(HZD_MAP *hzd, char *arg1);

/* dynamic.c */
int  HZD_QueueDynamicSegment2(HZD_HDL *hzd, HZD_SEG *seg, int flag);
void HZD_DequeueDynamicSegment(HZD_HDL *hzd, HZD_SEG *seg);
void HZD_SetDynamicSegment(HZD_SEG *a1, HZD_SEG *a2);
int  HZD_QueueDynamicFloor(HZD_HDL *hzd, HZD_FLR *floor);
void HZD_DequeueDynamicFloor(HZD_HDL *hzd, HZD_FLR *floor);

/* event.c */
void HZD_SetBind(int, HZD_BIND *, int);
void HZD_BindMapChange( int mask );
void HZD_SetEvent( HZD_EVT *event, int name );
void HZD_ExecBindX( HZD_BIND *, HZD_EVT *, int, int );
void HZD_ExecEventRCM(HZD_HDL *hzd, HZD_EVT *event, int arg2);
void HZD_ReExecEvent(HZD_HDL *hzd, HZD_EVT *event, unsigned int flags);
void HZD_ExecLeaveEvent(HZD_HDL *hzd, HZD_EVT *event);
void HZD_EnterTrap(HZD_HDL *hzd, HZD_EVT *event);
HZD_TRP *HZD_CheckBehindTrap(HZD_HDL *hzd, SVECTOR *svec);

/* level.c */
int  HZD_LevelTestHazard(HZD_HDL *hzd, SVECTOR *point, int flags);
void HZD_LevelMinMaxFloors(HZD_FLR **floors);
void HZD_LevelMinMaxHeights(int *levels);
int  HZD_SlopeFloorLevel(SVECTOR *point, HZD_FLR *floor);
int  HZD_LevelTestFloor(HZD_FLR *floor, SVECTOR *point);
int  HZD_LevelMaxHeight(void);

/* zone.c */
int HZD_GetAddress(HZD_HDL *hzd, SVECTOR *pos, int addr);
int HZD_ReachTo(HZD_HDL *hzd, int from, int to);
int HZD_LinkRoute(HZD_HDL *hzd, int from, int to, SVECTOR *pos);
int HZD_LinkRouteEqual(HZD_HDL *hzd, int from, int to, SVECTOR *pos);
int HZD_ZoneDistance(HZD_HDL *hzd, int from, int to);
int HZD_NavigateLimit(HZD_HDL *hzd, int from, int to, int limit);
int HZD_NavigateBound(HZD_HDL *hzd, int from, int to, int limit);
int HZD_ZoneContains(HZD_HDL *hzd, SVECTOR *pos, int zone);
int HZD_GetNears(HZD_HDL *hzd, int zone, int *nears);
int HZD_MaxNear(HZD_HDL *hzd, int from, int to, int *maxdist);
int HZD_MinNearDist(HZD_HDL *hzd, int from, int to);

#define HZD_NO_ZONE (0xFF)

/* collide.c */
int HZD_StepCheck(SVECTOR *nears, int count, int scale, SVECTOR *out);
void HZD_SurfaceNormal(HZD_FLR *floor, SVECTOR *out);
int HZD_LineCheck(HZD_HDL *hzd, SVECTOR *from, SVECTOR *to, int flag, int exclude);
void *HZD_LineNearSurface(void);
int HZD_LineNearFlag(void);
void HZD_LineNearDir(SVECTOR *out);
void HZD_LineNearVec(SVECTOR *out);
int HZD_PointCheck(HZD_HDL *hzd, SVECTOR *point, int range, int flag, int exclude);
void HZD_PointNearSurface(void **surface);
void HZD_PointNearFlag(char *char_arr);
void HZD_PointNearVec(SVECTOR *vectors);

#define HZD_CHECK_FLR    (0x1)
#define HZD_CHECK_DYNFLR (0x2)
#define HZD_CHECK_SEG    (0x4)
#define HZD_CHECK_DYNSEG (0x8)
#define HZD_CHECK_ALL    (HZD_CHECK_SEG|HZD_CHECK_FLR|HZD_CHECK_DYNSEG|HZD_CHECK_DYNFLR)

#define HZD_SEG_NO_COLLIDE   (0x01) /* collisions */
#define HZD_SEG_NO_NAVIGATE  (0x02) /* enemy navigation */
#define HZD_SEG_NO_PLAYER    (0x04) /* player sight */
#define HZD_SEG_NO_MISSILE   (0x08) /* missile collisions */
#define HZD_SEG_NO_HARITSUKI (0x10) /* attach c4 */
#define HZD_SEG_NO_BULLET    (0x20) /* bullet collisions */
#define HZD_SEG_NO_BEHIND    (0x40) /* player lean */
#define HZD_SEG_NO_RADAR     (0x80) /* radar draw */

#endif // _LIBHZD_H_
