#ifndef __S19B_JEEP_SYSTEM_H__
#define __S19B_JEEP_SYSTEM_H__

#include "game/game.h"

/* State shared by the jeep actors of the s19b chase, the jeep Snake rides in
 * (jeep.c) and the second jeep (jeep2.c). Defined in overlay6.c. */
typedef struct _JEEP_SYSTEM
{
    /* +0x00 */ char     pad_00[0x04];
    /* +0x04 */ CONTROL *control;       // set by jeep.c
    /* +0x08 */ SVECTOR *rot;           // set by jeep.c
    /* +0x0C */ int      active2;       // set by jeep2.c
    /* +0x10 */ CONTROL *control2;      // set by jeep2.c
    /* +0x14 */ SVECTOR *rot2;          // set by jeep2.c
    /* +0x18 */ SVECTOR  field_18;
    /* +0x20 */ SVECTOR  offset;        // push applied to the world around the jeep
    /* +0x28 */ VECTOR   pos;           // world position of the jeep
    /* +0x38 */ char     pad_38[0x10];
    /* +0x48 */ int      field_48;
    /* +0x4C */ int      flags_4C;
    /* +0x50 */ int      flags_50;
    /* +0x54 */ int      flags_54;
    /* +0x58 */ char     pad_58[0x14];
    /* +0x6C */ OBJECT  *body;          // set by jeep.c
    /* +0x70 */ OBJECT  *body2;         // set by jeep2.c
    /* +0x74 */ char     pad_74[0xBC];     // the rest of the original 0x16C bytes are separate variables in overlay6.c
} JEEP_SYSTEM;

#ifndef __S19B_OVERLAY6_C__ // HACK: the definition must not follow an extern declaration
extern JEEP_SYSTEM Takabe_JeepSystem;
#endif

#endif
