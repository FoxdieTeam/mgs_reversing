#ifndef _LIBHZD_H_
#define _LIBHZD_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "fmt_hzd.h"

#define OFFSET_TO_PTR(ptr, offset) (*(int *)offset = (int)ptr + *(int *)offset)

typedef struct {
    HZD_HEADER  *header;
    HZD_AREA    *area;
    short        area_index;
    short        dynamic_queue_index;
    short        dynamic_floor_index;
    short        n_cameras;
    short        max_dynamic_floors;
    short        max_dynamic_segments;
    HZD_ZON     *zones;
    HZD_TRP     *traps;
    HZD_FLR    **dynamic_floors;
    HZD_SEG    **dynamic_segments;
    char        *dynamic_flags;
} HZD_HDL;

typedef struct {
    u_short     field_0_scriptData_orHashedName;
    u_short     field_2_name_hash;
    u_short     field_4_trigger_Hash_Name_or_camera_w;
    short       field_6_count;
    u_short     field_8_array[6];
    SVECTOR     field_14_vec;
} HZD_EVT;

static inline int HZD_addr_shift( int addr )
{
    int temp = addr & 0xFF;
    return ( temp  | temp << 8 );
}

/* hzdd.c */
void HZD_StartDaemon(void);
int  HZD_LoadInitHzd(void *buf, int id);
HZD_HDL *HZD_MakeHandler(HZD_HEADER *hzd, int areaIndex, int dynamic_segments, int dynamic_floors);
void HZD_FreeHandler(void *ptr);
void HZD_MakeRoute(HZD_HEADER *hzd, char *arg1);

/* dynamic.c */
int  HZD_QueueDynamicSegment2(HZD_HDL *hdl, HZD_SEG *seg, int a_param_with_flag);
void HZD_DequeueDynamicSegment(HZD_HDL *hdl, HZD_SEG *seg);
void HZD_SetDynamicSegment(HZD_SEG *a1, HZD_SEG *a2);
int  HZD_QueueDynamicFloor(HZD_HDL *hdl, HZD_FLR *floor);
void HZD_DequeueDynamicFloor(HZD_HDL *hdl, HZD_FLR *floor);

/* event.c */
struct BindStruct;

void HZD_SetBind(int, struct BindStruct *, int);
void HZD_BindMapChange( int mask );
void HZD_SetEvent( HZD_EVT *event, int name );
void HZD_ExecBindX( struct BindStruct *, HZD_EVT *, int, int );
void HZD_80029B9C(HZD_HDL *hdl, HZD_EVT *event, int arg2);
void HZD_80029D50(HZD_HDL *hdl, HZD_EVT *event, int arg2);
void HZD_8002A090(HZD_HDL *hdl, HZD_EVT *event, int flags, int hash);
void HZD_ReExecEvent(HZD_HDL *hdl, HZD_EVT *event, unsigned int flags);
void HZD_8002A258(HZD_HDL *hdl, HZD_EVT *event);
void HZD_8002A27C(HZD_HDL *hdl, HZD_EVT *event);
void HZD_8002A4B8(HZD_HDL *hdl, HZD_EVT *event);
void HZD_8002A538(HZD_HDL *hdl, HZD_EVT *event);
HZD_TRP *HZD_CheckBehindTrap(HZD_HDL *hdl, SVECTOR *svec);

/* level.c */
int  HZD_80029384(HZD_FLR *floor);
int  HZD_80029514(HZD_FLR *floor);
void HZD_80029604(HZD_FLR *floor);
int  HZD_800296C4(HZD_HDL *hdl, SVECTOR *svec, int flags);
void HZD_800298C0(void *ptr);
void HZD_800298DC(HZD_VEC *vec);
int  HZD_SlopeFloorLevel(SVECTOR *svec, SVECTOR *arg1);
int  HZD_8002992C(HZD_FLR *floor, SVECTOR *arg1);
int  HZD_80029A2C(void);

/* zone.c */
int HZD_8005BF84(HZD_ZON *zone, int a2, int a3, int a4);
int HZD_8005BFDC(HZD_ZON *zone, SVECTOR *svec);
int HZD_8005C05C(HZD_ZON *zone1, HZD_ZON *zone2, SVECTOR *svec);
int HZD_8005C140(HZD_HDL *hdl, HZD_ZON *zone, SVECTOR *svec);
int HZD_8005C1E4(HZD_HDL *hdl, HZD_ZON *zone, SVECTOR *svec);
int HZD_8005C298(HZD_ZON *zone, SVECTOR *svec, int a3);
int HZD_8005C354(HZD_HDL *hdl, SVECTOR *svec);
int HZD_ReachTo_helper(HZD_HDL *hdl, int near_idx, int toFind);
int HZD_8005C458(HZD_HDL *hdl, int a2, int a3);
int HZD_8005C498(HZD_HDL *hdl, int idx, int *pOutNear);
int HZD_8005C4E4(HZD_HDL *hdl, int arg1, int arg2);
int HZD_8005C5D4(HZD_HDL *hdl, int param_2, int param_3);
int HZD_GetAddress(HZD_HDL *hdl, SVECTOR *vec, int param_3);
int HZD_ReachTo(HZD_HDL *hdl, int x, int y);
int HZD_LinkRoute(HZD_HDL *hdl, int x, int y, SVECTOR *svec);
int HZD_8005CB48(HZD_HDL *hdl, int x, int y, void *pControl);
int HZD_ZoneDistance(HZD_HDL *hdl, int from, int to);
int HZD_8005CE5C(HZD_HDL *hdl, int from, int to, int max_dist);
int HZD_8005CFAC(HZD_HDL *hdl, int from, int to, int max_dist);
int HZD_8005D134(HZD_HDL *hdl, SVECTOR *svec, int idx);
int HZD_8005D168(HZD_HDL *hdl, int a2, int *a3);
int HZD_8005D188(HZD_HDL *hdl, int mesh_idx, int a3, int *pBiggest);
int HZD_8005D288(HZD_HDL *hdl, int mesh_idx, int a3);

/* unknown.c */
int  HZD_80026C68(SVECTOR *vectors, int param_2, int param_3, SVECTOR *param_4);
void HZD_800272E0(HZD_FLR *floor, SVECTOR *out);
int  HZD_80027384(void);
void HZD_8002751C(SVECTOR *svec1, SVECTOR *svec2);
int  HZD_800275A8(void);
int  HZD_800276B4(void);
int  HZD_80027850(int mult);
void HZD_8002799C(int a0);
void HZD_80027A94(HZD_SEG *seg, int a2, int a3);
int  HZD_80027BF8(SVECTOR *svec);
int  HZD_80027C64(void);
int  HZD_80027D80(HZD_FLR *floor);
void HZD_80027F10(HZD_FLR *floor);
int  HZD_80028454(HZD_HDL *hdl, SVECTOR *a2, SVECTOR *a3, int flags, int flag);

HZD_FLR *HZD_80028820(void);
int  HZD_80028830(void);
void HZD_GetSpadVectorDiff(SVECTOR *out);
void HZD_GetSpadVector(SVECTOR *out);
void HZD_CopyVector(SVECTOR *src, SVECTOR *dst);
void HZD_800288E0(SVECTOR *vec, int delta);
int  HZD_80028930(void);
void HZD_80028CF8(void);
void HZD_80028DAC(HZD_SEG *wall, int index, int flags);
int  HZD_80029098(HZD_HDL *hdl, SVECTOR *pos, int delta, int flags, unsigned int mask);

void HZD_800292E4(HZD_FLR **floors);
void HZD_80029304(char *char_arr);
void HZD_80029324(SVECTOR *vectors);

#endif // _LIBHZD_H_
