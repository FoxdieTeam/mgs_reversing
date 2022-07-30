#ifndef _HZD_H_
#define _HZD_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>


typedef struct      HZD_VEC
{
    long            long_access[0];
    short           x, z, y, h;
} HZD_VEC; // 8

typedef struct      HZD_SEG // segments (walls)
{
    HZD_VEC         p1, p2;         
} HZD_SEG; // 16

typedef struct      HZD_FLR // altimetry
{
    HZD_VEC         b1, b2;         
    HZD_VEC         p1, p2, p3, p4;     
} HZD_FLR; // 48

typedef struct      HZD_TRP // trap trigger
{
    HZD_VEC         b1, b2;         
    char            name[12];
//    u_short         id;
    u_char          id1, id2;
    u_short         name_id;         
} HZD_TRP; // 32

typedef struct      HZD_CAM // camera trigger
{ // most likely wrong
    HZD_VEC         b1, b2;
    HZD_VEC         cam;
    HZD_VEC         orient;
} HZD_CAM; // 32
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
typedef union       HZD_TRG // trigger (cam or trap)
{
    HZD_CAM         cam;
    HZD_TRP         trap;
} HZD_TRG; // 32

typedef struct      HZD_ZON // navmesh
{
    short           x, z, y;         
    short           w, h;             
    u_char          nears[6];     
    u_char          dists[6];     
    short           padding;
} HZD_ZON; // 24

typedef struct      HZD_PTP // patrol route point
{
    short           x, z, y;
    short           command; // act, time, dir, unk    
} HZD_PTP; // 8

typedef struct      HZD_PAT // patrol routes
{
    short           n_points;
    short           init_point;
    HZD_PTP         *points;
} HZD_PAT; // 12

typedef struct      HZD_AREA
{
    short           n_triggers;
    short           n_walls;
    short           n_altimetry;
    short           n_unknown; // some specific walls ?
    HZD_SEG         *walls;
    HZD_FLR         *altimetry;
    HZD_TRG         *triggers;
    int             *wallsFlags;
} HZD_AREA; // 24

typedef struct      HZD_HEADER
{
    void            *ptr_access[0];
    short           version;
    short           min_x, min_y; //2
    short           max_x, max_y; //6
    short           n_areas; //A
    short           n_navmeshes; //C
    short           n_routes; //E
    HZD_AREA        *areas; //10
    HZD_ZON         *navmeshes; //14
    HZD_PAT         *routes; //18
} HZD_HEADER; // 28

typedef struct      HZD_MAP
{
    HZD_HEADER      *f00_header;
    HZD_AREA        *f04_area;
    short           f08_areaIndex;
    short           f0A;
    short           f0C;
    short           f0E_n_cameras;
    short           f10_24size;
    short           f12_48size;
    HZD_ZON         *f14_navmeshes;
    HZD_TRP         *f18_traps;
    int             *f1C_pEndOfHzdMap;
    int             *f20_pAfterStructure_24;
    int             *f20_pAfterStructure_48;
} HZD_MAP; // 28

#endif // _HZD_H_
