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
int  HZD_QueueDynamicSegment2(HZD_HDL *hzd, HZD_SEG *seg, int a_param_with_flag);
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
void HZD_80029D50(HZD_HDL *hzd, HZD_EVT *event, int arg2);
void HZD_8002A090(HZD_HDL *hzd, HZD_EVT *event, int flags, int hash);
void HZD_ReExecEvent(HZD_HDL *hzd, HZD_EVT *event, unsigned int flags);
void HZD_8002A258(HZD_HDL *hzd, HZD_EVT *event);
void HZD_8002A27C(HZD_HDL *hzd, HZD_EVT *event);
void HZD_8002A4B8(HZD_HDL *hzd, HZD_EVT *event);
void HZD_8002A538(HZD_HDL *hzd, HZD_EVT *event);
HZD_TRP *HZD_CheckBehindTrap(HZD_HDL *hzd, SVECTOR *svec);

/* level.c */
int  HZD_LevelTestHazard(HZD_HDL *hzd, SVECTOR *point, int flags);
void HZD_LevelMinMaxFloors(HZD_FLR **floors);
void HZD_LevelMinMaxHeights(int *levels);
int  HZD_SlopeFloorLevel(SVECTOR *point, HZD_FLR *floor);
int  HZD_LevelTestFloor(HZD_FLR *floor, SVECTOR *point);
int  HZD_LevelMaxHeight(void);

/* zone.c */
int HZD_GetAddress(HZD_HDL *hzd, SVECTOR *point, int param_3);
int HZD_ReachTo(HZD_HDL *hzd, int x, int y);
int HZD_LinkRoute(HZD_HDL *hzd, int x, int y, SVECTOR *point);
int HZD_8005CB48(HZD_HDL *hzd, int x, int y, SVECTOR *point);
int HZD_ZoneDistance(HZD_HDL *hzd, int from, int to);
int HZD_8005CE5C(HZD_HDL *hzd, int from, int to, int max_dist);
int HZD_8005CFAC(HZD_HDL *hzd, int from, int to, int max_dist);
int HZD_8005D134(HZD_HDL *hzd, SVECTOR *svec, int idx);
int HZD_8005D168(HZD_HDL *hzd, int a2, int *a3);
int HZD_8005D188(HZD_HDL *hzd, int mesh_idx, int a3, int *pBiggest);
int HZD_8005D288(HZD_HDL *hzd, int mesh_idx, int a3);

#define HZD_NO_ZONE (0xFF)

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
int  HZD_80028454(HZD_HDL *hzd, SVECTOR *a2, SVECTOR *a3, int flags, int flag);

HZD_FLR *HZD_80028820(void);
int  HZD_80028830(void);
void HZD_GetSpadVectorDiff(SVECTOR *out);
void HZD_GetSpadVector(SVECTOR *out);
void HZD_CopyVector(SVECTOR *src, SVECTOR *dst);
void HZD_800288E0(SVECTOR *vec, int delta);
int  HZD_80028930(void);
void HZD_80028CF8(void);
void HZD_80028DAC(HZD_SEG *wall, int index, int flags);
int  HZD_80029098(HZD_HDL *hzd, SVECTOR *pos, int delta, int flags, unsigned int mask);

void HZD_800292E4(HZD_FLR **floors);
void HZD_80029304(char *char_arr);
void HZD_80029324(SVECTOR *vectors);

#endif // _LIBHZD_H_
