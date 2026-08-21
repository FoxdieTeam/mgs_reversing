#ifndef __MGS_FMT_IMG_H__
#define __MGS_FMT_IMG_H__

#include <sys/types.h>

/*----------------------------------------------------------------*/

typedef struct _DG_IMG_ATTRIB {
    u_char texid;
    u_char xoff;
    u_char yoff;
    u_char unused;
} DG_IMG_ATTRIB;

typedef struct _DG_IMG {
    u_short        image_width;
    u_short        image_height;
    u_short        tile_width;
    u_short        tile_height;
    u_short       *textures; // textures[0] = count
    DG_IMG_ATTRIB *attribs;
    u_char        *tilemap;
} DG_IMG;

#endif // __MGS_FMT_IMG_H__
