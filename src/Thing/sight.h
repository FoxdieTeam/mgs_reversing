#ifndef _SIGHT_H_
#define _SIGHT_H_

#include "linker.h"
#include "libgv/libgv.h"
#include "LIBGPU.H"

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
    char           field_0;
    char           field_1;
    unsigned short field_2;
} SightPrimBufInfoStruct;

typedef struct SightPrimitiveBufferInfo
{
    unsigned short          field_0_primitiveBufferSize;
    char                    field_2;
    char                    field_3;
    SightPrimBufInfoStruct *field_4_ancillaryInfo;
    void                   *field_8_primitiveBuffer;
    SightPrimOffsetIndices *field_C_primOffsetIndicesArray;
    SightPrimOffsetInfo    *field_10_primOffsetInfoArray;
} SightPrimitiveBufferInfo;

// Text pseudo-primitive
//
// The game uses the same memory to render primitives and text, executing the logic for the latter if the first field,
// which would normally be the primitive's tag, is equal to 0xff (see: 0x8007183c). This is presumably the structure of
// the text pseudo-primitive, unless the game is hijacking an actual primitive.
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

typedef struct Actor_Sight
{
    Actor                     field_0_actor;
    int                       field_20_itemId;
    short                    *field_24_itemEquippedIndicator;
    int                       field_28_currentMap;
    int                       field_2C_frameCount;
    int                       field_30;
    SightPrimitiveBufferInfo *field_34_primitiveBufferInfo;
    void                     *field_38_primitiveBuffer; // Double buffering.
    void                     *field_3C_primitiveBuffer;
    int                       field_40;
    DR_TPAGE                 *field_44_tPageBuffer; // Double buffering.
    DR_TPAGE                 *field_48_tPageBuffer;
    short                    *field_4C_xyOffsetBuffer;
    int                       field_50;
    int                       field_54_maybeFlags;
    short                     field_58_clock;
    short                     field_5A_maybeFlags;
} Actor_Sight;

STATIC_ASSERT_SIZE(Actor_Sight, 0x5c);

Actor_Sight *NewSight_80071CDC(int hashedFileName0, int hashedFileName1, short *itemEquippedIndicator, short itemId,
                               short *xyOffsetBuffer);

void sight_act_800714EC(Actor_Sight *sight);
void sight_kill_800719C8(Actor_Sight *sight);
int  sight_loader_80071A54(Actor_Sight *sight, int hashedFileName, short *itemEquippedIndicator, short itemId,
                           short *xyOffsetBuffer);

#endif // _SIGHT_H_
