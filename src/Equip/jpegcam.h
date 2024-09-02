#ifndef _JPEGCAM_H
#define _JPEGCAM_H

#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/game.h"

typedef signed char TMat8x8B[8][8];     // Matrix with 8 rows by 8 bytes
typedef signed char TMat16x16B[16][16]; // Matrix with 16 rows by 16 bytes
typedef int         TMat8x8I[8][8];

GV_ACT *NewJpegcam_80065118(CONTROL *control, OBJECT *parent, int num_parent);

#endif // _JPEGCAM_H
