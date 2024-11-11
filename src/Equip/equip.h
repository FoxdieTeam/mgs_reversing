#ifndef _EQUIP_H_
#define _EQUIP_H_

#include "libgv/libgv.h"    // for GV_ACT
#include "Game/game.h"      // for OBJECT
#include "Game/control.h"   // for CONTROL

GV_ACT *NewBandana( CONTROL *control, OBJECT *parent, int num_parent );
GV_ACT *NewBodyarm( CONTROL *control, OBJECT *parent, int num_parent );
GV_ACT *NewBox( CONTROL *control, OBJECT *parent, int num_parent );
GV_ACT *NewGasmask( CONTROL *control, OBJECT *parent, int num_parent );
GV_ACT *NewKogaku2( CONTROL *control, OBJECT *object, int num_parent );
GV_ACT *NewKogaku3( CONTROL *control, OBJECT *object, int num_parent );
GV_ACT *NewScope( CONTROL *control, OBJECT *parent, int num_parent );
GV_ACT *NewTabako( CONTROL *control, OBJECT *parent, int num_parent );

GV_ACT *NewGoggleManager( int type );
GV_ACT *NewGoggleSight( int type );
GV_ACT *NewGasmaskSight(); // This has an issue with unused params

/* these should be private to jpegcam.c, but bss.c needs it */
typedef signed char TMat8x8B[8][8];     //  8 x  8 byte matrix
typedef signed char TMat16x16B[16][16]; // 16 x 16 byte matrix
typedef int         TMat8x8I[8][8];     //  8 x  8 integer matrix

GV_ACT *NewJpegcam( CONTROL *control, OBJECT *parent, int num_parent );

void EQ_ChangeTexture(const char *itemName1, const char *itemName2);
void EQ_InvisibleHead(OBJECT *object, short *n_packs, short *raise);
void EQ_VisibleHead(OBJECT *object, short *n_packs, short *raise);
#ifdef VR_EXE
void EQ_InvisibleUnit(OBJECT *object, int idx, short *n_packs, short *raise);
void EQ_VisibleUnit(OBJECT *object, int idx, short *n_packs, short *raise);
#endif

#endif // _EQUIP_H_
