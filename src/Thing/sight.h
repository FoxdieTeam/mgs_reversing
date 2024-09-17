#ifndef _SIGHT_H_
#define _SIGHT_H_

#include "common.h"
#include "libgv/libgv.h"
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

// https://github.com/Joy-Division/JoyDict/search?q=*sgt*

typedef struct SightPrimOffsetIndices
{
    char indices[4];
} SightPrimOffsetIndices;

typedef struct SightPrimOffsetInfo
{
    char        field_0_nextFrame;
    char        field_1_prevFrame;
    signed char field_2_xOffsetMultiplier;
    signed char field_3_yOffsetMultiplier;
} SightPrimOffsetInfo;

typedef struct SightPrimBufInfoStruct
{
    char           field_0_offsetIndicesIndex;
    char           field_1_tPageInfo;
    unsigned short field_2_primOffset;
} SightPrimBufInfoStruct;

typedef struct SightPrimBufInfo_0x14
{
    char field_0;
    char field_1;
    char field_2[2];
} SightPrimBufInfo_0x14;

// Contains the information necessary to obtain and animate the primitives for a certain aspect of the HUD.
typedef struct SightPrimitiveBufferInfo
{
    unsigned short          field_0_primitiveBufferSize;
    char                    field_2;
    char                    field_3_primCount;
    SightPrimBufInfoStruct *field_4_ancillaryInfo;
    void                   *field_8_primitiveBuffer; // This is copied into a Sight actor's double buffer.
    SightPrimOffsetIndices *field_C_primOffsetIndicesArray;
    SightPrimOffsetInfo    *field_10_primOffsetInfoArray;
    SightPrimBufInfo_0x14  *field_14_array;
} SightPrimitiveBufferInfo;

// Text pseudo-primitive
//
// The game uses the same memory to render primitives and text, executing the logic for the latter if the first field,
// which would normally be the primitive's tag, is equal to 0xff. This is presumably the structure of the text
// pseudo-primitive, unless the game is hijacking an actual primitive.
typedef struct SightTextPseudoPrim
{
    int   field_0_tag;
    char  field_4_r;
    char  field_5_g;
    char  field_6_b;
    char  field_7_code;
    short field_8_posX;
    short field_A_posY;
    char  field_C_text[16];
} SightTextPseudoPrim;

// Handles HUD appearance for:
// - the scope;
// - the box in first-person view;
// - the gas mask in first-person view;
// - the thermal goggles;
// - the night-vision goggles;
// - the camera;
// - the Stinger missile.
typedef struct SightWork
{
    GV_ACT                    actor;
    int                       field_20_itemId;
    short                    *field_24_itemEquippedIndicator;
    int                       field_28_currentMap;
    int                       field_2C_frameCount;
    int                       field_30;
    SightPrimitiveBufferInfo *field_34_primitiveBufferInfo;
    void                     *field_38_primitiveDoubleBuffer[2];
    int                       field_40;
    DR_TPAGE                 *field_44_tPageDoubleBuffer[2];
    short                    *field_4C_xyOffsetBuffer;
    int                       field_50;
    int                       field_54_maybeFlags;
    unsigned short            field_58_clock;
    short                     field_5A_maybeFlags;
} SightWork;

STATIC_ASSERT(sizeof(SightWork) == 0x5C, "sizeof(SightWork) is wrong!");

void sight_act_800714EC(SightWork *work);

SightWork *NewSight_80071CDC(int hashedFileName0, int hashedFileName1, short *itemEquippedIndicator, short itemId,
                             short *xyOffsetBuffer);

SightWork *sight_init_80071EA8(int hashedFileName0, int hashedFileName1, short *itemEquippedIndicator, short itemId,
                               short *xyOffsetBuffer);

#endif // _SIGHT_H_
