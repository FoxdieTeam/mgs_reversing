#ifndef __MGS_FMT_HZD_H__
#define __MGS_FMT_HZD_H__
// clang-format off

#include <sys/types.h>
#include <libgte.h>

/**
 * Hazard 16-bit vector
 */
typedef struct {
    long        long_access[0];
    short       x, z, y, h;
} HZD_VEC;

/**
 * Hazard segment (a.k.a "wall")
 *
 * Walls are always pefectly vertical.
 * The soliton radar is drawn from this data.
 */
typedef struct {
    HZD_VEC     p1, p2;
} HZD_SEG;

/**
 * Hazard floor
 *
 * Used for every collidable surface that's not considered a wall.
 */
typedef struct {
    HZD_VEC     b1, b2;
    HZD_VEC     p1, p2, p3, p4;
} HZD_FLR;

/**
 * Hazard trap (a.k.a "trigger volume")
 *
 * Named bounding box that triggers an event when an actor enters
 * or exits its dimensions.
 */
typedef struct {
    HZD_VEC     b1, b2;
    char        name[12];
    u_char      id1, id2;
    u_short     name_id;
} HZD_TRP;

/*
// Old version(?) from memleak

typedef struct  {
    HZD_VEC     b1, b2 ;
    char        name[ 12 ] ;
    u_short     name_id ;
} HZD_TRP ;
*/

/**
 * Hazard camera
 *
 * Camera angle data for "behind mode"
 */
typedef struct {
    HZD_VEC     b1, b2;
    HZD_VEC     cam;
    HZD_VEC     orient;
} HZD_CAM;

/*
typedef struct {
    HZD_VEC     b1, b2;
    HZD_VEC     c1, c2;
    HZD_VEC     orient;
    u_short     id;
    u_short     name_id;
} HZD_CAM;
*/

/**
 * Hazard trigger
 *
 * Union of the trap and camera data definitions.
 */
typedef union {
    HZD_CAM     cam;
    HZD_TRP     trap;
} HZD_TRG;

/**
 * Hazard zone
 *
 * Individual sector of the hazard map's navmesh.
 */
typedef struct {
    short       x, z, y;
    short       w, h;
    u_char      nears[6];
    u_char      dists[6];
    short       padding;
} HZD_ZON;

/**
 * Hazard patrol point
 *
 * Individual point of an enemy soldier's patrol route.
 * Includes behavior command data (which direction to face, etc.)
 */
typedef struct {
    short       x, z, y;
    short       command;        // act, time, dir, unk
} HZD_PTP;

/**
 * Hazard patrol route
 *
 * Complete enemy soldier patrol route data.
 * Defines the number of points and starting point for the soldier.
 */
typedef struct {
    short       n_points;
    short       init_point;
    HZD_PTP     *points;
} HZD_PAT;

typedef struct {
    short       n_triggers;
    short       n_walls;
    short       n_floors;
    short       n_flat_walls;
    HZD_SEG     *walls;
    HZD_FLR     *floors;
    HZD_TRG     *triggers;
    char        *wallsFlags;
} HZD_GRP;

typedef struct {
    void        *ptr_access[0];
    short       version;
    short       min_x, min_y;
    short       max_x, max_y;
    short       n_groups;
    short       n_zones;
    short       n_routes;
    HZD_GRP     *groups;
    HZD_ZON     *zones;
    HZD_PAT     *routes;
} HZD_MAP;

// clang-format on
#endif // __MGS_FMT_HZD_H__
