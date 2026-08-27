#ifndef __MGS_EQUIP_H__
#define __MGS_EQUIP_H__

#include "game/game.h"      // for OBJECT, CONTROL

void *NewBandana( CONTROL *control, OBJECT *parent, int num_parent );
void *NewBodyArmor( CONTROL *control, OBJECT *parent, int num_parent );
void *NewBox( CONTROL *control, OBJECT *parent, int num_parent );
void *NewGasMask( CONTROL *control, OBJECT *parent, int num_parent );
void *NewKogaku2( CONTROL *control, OBJECT *object, int num_parent );
void *NewKogaku3( CONTROL *control, OBJECT *object, int num_parent );
void *NewScope( CONTROL *control, OBJECT *parent, int num_parent );
void *NewTabako( CONTROL *control, OBJECT *parent, int num_parent );

void *NewGoggleManager( int type );
void *NewGoggleSight( int type );
void *NewGasmaskSight(); // This has an issue with unused params

void *NewJpegcam( CONTROL *control, OBJECT *parent, int num_parent );

void EQ_ChangeTexture(const char *itemName1, const char *itemName2);
void EQ_InvisibleHead(OBJECT *object, short *n_packs, short *raise);
void EQ_VisibleHead(OBJECT *object, short *n_packs, short *raise);
#ifdef VR_EXE
void EQ_InvisibleUnit(OBJECT *object, int idx, short *n_packs, short *raise);
void EQ_VisibleUnit(OBJECT *object, int idx, short *n_packs, short *raise);
#endif

#endif // __EQUIP_EQUIP_H__
