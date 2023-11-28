#ifndef _HZD_H_
#define _HZD_H_

#include <SYS/TYPES.H>
#include <LIBGTE.H>
#include <LIBGPU.H>

#define OFFSET_TO_PTR(ptr, offset) (*(int *)offset = (int)ptr + *(int *)offset)

typedef struct HZD_VEC
{
    long  long_access[0];
    short x, z, y, h;
} HZD_VEC; // 8

typedef struct HZD_SEG // segments (walls)
{
    HZD_VEC p1, p2;
} HZD_SEG; // 16

typedef struct HZD_FLR // altimetry
{
    HZD_VEC b1, b2;
    HZD_VEC p1, p2, p3, p4;
} HZD_FLR; // 48

typedef struct HZD_TRP // trap trigger
{
    HZD_VEC b1, b2;
    char    name[12];
    //    u_short         id;
    u_char  id1, id2;
    u_short name_id;
} HZD_TRP; // 32

typedef struct HZD_CAM // camera trigger
{                      // most likely wrong
    HZD_VEC b1, b2;
    HZD_VEC cam;
    HZD_VEC orient;
} HZD_CAM; // 32

typedef union       HZD_CAM_TRP // cam or trap
{
    HZD_CAM         cam;
    HZD_TRP         trap;
} HZD_CAM_TRP; // 32

/*
typedef struct      HZD_CAM // camera trigger
{
    HZD_VEC         b1, b2;
    HZD_VEC         c1, c2;
    HZD_VEC         orient;
    u_short         id;
    u_short         name_id;
} HZD_CAM; // 44
*/
typedef union HZD_TRG // trigger (cam or trap)
{
    HZD_CAM cam;
    HZD_TRP trap;
} HZD_TRG; // 32

typedef struct HZD_ZON // navmesh
{
    short  x, z, y;
    short  w, h;
    u_char nears[6];
    u_char dists[6];
    short  padding;
} HZD_ZON; // 24

typedef struct HZD_PTP // patrol route point
{
    short x, z, y;
    short command; // act, time, dir, unk
} HZD_PTP;         // 8

typedef struct HZD_PAT // patrol routes
{
    short    n_points;
    short    init_point;
    HZD_PTP *points;
} HZD_PAT; // 12

typedef struct HZD_AREA
{
    short    n_triggers;
    short    n_walls;
    short    n_altimetry;
    short    n_unknown; // some specific walls ?
    HZD_SEG *walls;
    HZD_FLR *altimetry;
    HZD_TRG *triggers;
    char    *wallsFlags;
} HZD_AREA; // 24

// TODO: Should be HZD_MDL?
typedef struct HZD_HEADER
{
    void     *ptr_access[0];
    short     version;
    short     min_x, min_y; // 2
    short     max_x, max_y; // 6
    short     n_areas;      // A
    short     n_navmeshes;  // C
    short     n_routes;     // E
    HZD_AREA *areas;        // 10
    HZD_ZON  *navmeshes;    // 14
    HZD_PAT  *routes;       // 18
} HZD_HEADER;               // 28

typedef struct HZD_HDL
{
    HZD_HEADER *f00_header;
    HZD_AREA   *f04_area;
    short       f08_areaIndex;
    short       f0A_dynamic_queue_index;
    short       f0C_dynamic_floor_index;
    short       f0E_n_cameras;
    short       f10_max_dynamic_floors;
    short       f12_max_dynamic_segments;
    HZD_ZON    *f14_navmeshes;
    HZD_TRP    *f18_traps;
    HZD_FLR   **f1C_dynamic_floors;
    HZD_SEG   **f20_dynamic_segments;
    char       *f24_dynamic_flags;
} HZD_HDL; // 28

typedef struct HZD_EVT
{
    unsigned short  field_0_scriptData_orHashedName;
    unsigned short  field_2_name_hash;
    unsigned short  field_4_trigger_Hash_Name_or_camera_w;
    short           field_6_count;
    unsigned short  field_8_array[6];
    SVECTOR         field_14_vec;
} HZD_EVT;

static inline int HZD_addr_shift( int addr )
{
    int temp = addr & 0xFF;
    return ( temp  | temp << 8 );
}


int      HZD_QueueDynamicSegment2_8006FDDC(HZD_HDL *pHzdMap, HZD_SEG *pSeg, int a_param_with_flag);
void     HZD_DequeueDynamicSegment2_8006FE44(HZD_HDL *pHzdMap, HZD_SEG *arg1);
int      HZD_QueueDynamicFloor_8006FF9C(HZD_HDL *pMap, HZD_FLR *pFlr);
void     HZD_DequeueDynamicFloor_8006FFE8(HZD_HDL *pMap, HZD_FLR *pFlr);
void     HZD_SetDynamicSegment_8006FEE4(HZD_SEG *a1, HZD_SEG *a2);
void     HZD_StartDaemon_80021900(void);
HZD_HDL *HZD_MakeHandler_80021AE0(HZD_HEADER *hzd, int areaIndex, int default_48, int default_24);
void     HZD_SetEvent_80029AB4(HZD_EVT *param_1, int param_2);
void     HZD_FreeHandler_80021C40(void *param_1);
int      HZD_LoadInitHzd_800219F4(void *hzmFile);
void     HZD_ProcessTraps_80021928(HZD_CAM_TRP *trig, int n_trapsAndCameras);
void     HZD_MakeRoute_80021D6C(HZD_HEADER *hzd, char *arg1); // navmeshes
void     HZD_MakeRoute_helper_80021C64(HZD_ZON *param_1, int param_2, int param_3, char *param_4);
void     HZD_ReExecEvent_8002A1F4(HZD_HDL *param_1, HZD_EVT *param_2, unsigned int flags);
int      HZD_SlopeFloorLevel_800298F8(SVECTOR *param_1, SVECTOR *arg1);

void sub_800219C8(HZD_PAT *routes, int n_routes, HZD_HEADER *hzm);
int  sub_8002992C(HZD_FLR *pAltimetry, SVECTOR *arg1);
void sub_800298DC(HZD_VEC *vec);

struct BindStruct;
void HZD_SetBind_80029A5C(int, struct BindStruct *, int);

int         sub_80028454(HZD_HDL *pHzdMap, SVECTOR *a2, SVECTOR *a3, int flags, int flag);
SVECTOR*    sub_80028820(void);
void        GetVecFromScratchpad_80028840(SVECTOR *vec);
int         sub_80029098(HZD_HDL *pMap, SVECTOR *pPosition, int delta, int flags, unsigned int mask);
void        GM_ActControl_helper3_800292E4(SVECTOR **vectors_ptr);
void        GM_ActControl_helper4_80029304(char *char_arr);
void        GM_ActControl_helper5_80029324(SVECTOR *vectors);
int         GM_ActControl_helper_80026C68( SVECTOR *vectors, int param_2, int param_3, SVECTOR *param_4 );
int         sub_800296C4(HZD_HDL *pHzdMap, SVECTOR *param_2, int flags);
int         sub_80029A2C();
int         sub_80028830(void);

int sub_8005CFAC(HZD_HDL *pHzdMap, int from, int to, int max_dist);

int HZD_ReachTo_8005C89C(HZD_HDL *pHzd, int, int);
int HZD_GetAddress_8005C6C4(HZD_HDL *hzd, SVECTOR *vec, int param_3);
int HZD_LinkRoute_8005C974(HZD_HDL *pHzd, int, int, SVECTOR *svector);
int sub_8005D134(HZD_HDL *pHzd, SVECTOR *pVec, int idx);
int HZD_ZoneDistance_8005CD1C(HZD_HDL *pHzdMap, int from, int to);
int sub_8005CB48(HZD_HDL *pHzdMap, int x, int y, void *pControl);

#endif // _HZD_H_
