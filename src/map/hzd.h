#ifndef _HZD_H_
#define _HZD_H_

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

typedef struct      HZD_HEADER
{
    u_short         version;
    short           min_x, min_y;
    short           max_x, max_y;
    u_short         n_areas;
    u_short         n_navmesh;
    u_short         n_routes;
    int             areas_offset;
    int             navmeshes_offset;
    int             routes_offset;
} HZD_HEADER;

typedef struct      HZD_AREA
{
    u_short         n_trapsAndCameras;
    u_short         n_walls;
    u_short         n_altimetry;
    u_short         n_unknown; // some specific walls ?
    int             walls_offset;
    int             altimetry_offset;
    int             trapsAndCameras_offset;
    int             wallsConfig_offset;
} HZD_AREA;

typedef struct      HZD_VEC
{
    long            long_access[0];
    short           x, z, y, h;
} HZD_VEC;

typedef struct      HZD_SEG // segments (walls)
{
    HZD_VEC         p1, p2;         
} HZD_SEG;

typedef struct      HZD_FLR // altimetry
{
    HZD_VEC         b1, b2;         
    HZD_VEC         p1, p2, p3, p4;     
} HZD_FLR;

typedef struct      HZD_TRP // trap trigger
{
    HZD_VEC         b1, b2;         
    char            name[12];
    u_short         id;
    u_short         name_id;         
} HZD_TRP;

typedef struct      HZD_CAM // camera trigger
{
    HZD_VEC         b1, b2;
    HZD_VEC         c1, c2;
    HZD_VEC         orient;
    u_short         id;
    u_short         name_id;
} HZD_CAM;

typedef struct      HZD_ZON // navmesh
{
    short           x, z, y;         
    short           w, h;             
    u_char          nears[6];     
    u_char          dists[6];     
    short           padding;
} HZD_ZON;

typedef struct      HZD_PTP // patrol route point
{
    short           x, z, y;
    short           command; // act, time, dir, unk    
} HZD_PTP;

typedef struct      HZD_PAT // patrol routes
{
    short           n_points;
    short           init_point;
    HZD_PTP         *points;
} HZD_PAT;

#endif // _HZD_H_
