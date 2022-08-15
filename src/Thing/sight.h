#ifndef _SIGHT_H_
#define _SIGHT_H_

#include "linker.h"
#include "libgv/libgv.h"
#include "LIBGPU.H"

typedef struct SightStruct
{
    unsigned short  field_0;
    unsigned char   field_2;
    unsigned char   field_3;
    unsigned short *field_4;
    int            *field_8;
    unsigned char  *field_C;
    unsigned char  *field_10;
} SightStruct;

typedef struct UnknownMenuStruct
{
    int           field_0;
    unsigned char field_4_r;
    unsigned char field_5_g;
    unsigned char field_6_b;
    unsigned char field_7;
    short         field_8_posX;
    short         field_A_posY;
    char          field_C_text[16];
} UnknownMenuStruct;

typedef struct Actor_Sight
{
    Actor              field_0_actor;
    int                field_20_itemId;
    short             *field_24_equippedItemIndicator;
    int                field_28_currentMap;
    int                field_2C_frameCount;
    int                field_30;
    SightStruct       *field_34_buffer;
    UnknownMenuStruct *field_38_menuStructBuffer;
    UnknownMenuStruct *field_3C_menuStructBuffer;
    int                field_40;
    DR_TPAGE          *field_44_tPageBuffer;
    DR_TPAGE          *field_48_tPageBuffer;
    short             *field_4C_xyOffsetBuffer;
    int                field_50;
    int                field_54_maybeFlags;
    int                field_58_maybeFlags;
} Actor_Sight;

STATIC_ASSERT_SIZE(Actor_Sight, 0x5c);

Actor_Sight *NewSight_80071CDC(int hashedFileName0, int hashedFileName1, short *itemEquippedIndicator, short itemId,
                               short *xyOffsetBuffer);

void sight_act_800714EC(Actor_Sight *sight);
void sight_kill_800719C8(Actor_Sight *sight);
int  sight_loader_80071A54(Actor_Sight *sight, int hashedFileName, short *itemEquippedIndicator, short itemId,
                           short *xyOffsetBuffer);

#endif // _SIGHT_H_
