#ifndef __MGS_FMT_KMD_H__
#define __MGS_FMT_KMD_H__

#include <sys/types.h>
#include <libgte.h>

/*----------------------------------------------------------------*/

enum {
    DG_MODEL_TRANS    = 0x00002,
    DG_MODEL_UNLIT    = 0x00004,
    DG_MODEL_BOTHFACE = 0x00400,
    DG_MODEL_INDIRECT = 0x10000,
};

/*----------------------------------------------------------------*/

typedef struct _DG_MDL {
    int         flags;
    int         n_faces;
    int         lx, ly, lz;
    int         ux, uy, uz;
    int         tx, ty, tz;
    int         parent;
    int         extend;
    int         n_verts;
    SVECTOR    *verts;
    u_char     *vindices;
    int         n_norms;
    SVECTOR    *norms;
    u_char     *nindices;
    u_char     *uvs;
    u_short    *texids;
    int         pad0;
} DG_MDL;

typedef struct _DG_DEF {
    int         n_models;
    int         n_x_models;
    int         lx, ly, lz;
    int         ux, uy, uz;
    DG_MDL      models[ 0 ];
} DG_DEF;

/*----------------------------------------------------------------*/

typedef struct _DG_KMDPACK {
    u_int       id;
    DG_DEF      def;
} DG_KMDPACK;

typedef struct _DG_ZMD_DEF {
    u_int       ident;
    u_int       n_kmd;
    u_int       vert_offset;
    u_int       body_len;
    DG_KMDPACK  kmd[ 0 ];
} DG_ZMD_DEF;

#endif // __MGS_FMT_KMD_H__
