#ifndef __S19B_JEEP_SYSTEM_H__
#define __S19B_JEEP_SYSTEM_H__

#include "game/game.h"

struct _DemoCamera;

typedef struct _JEEP_ATTACH
{
    MATRIX  *mtx;       // world matrix of the jeep object
    SVECTOR  ofs;       // attach point in the jeep object's space
} JEEP_ATTACH;

/* State shared by all actors of the s19b jeep chase: the jeep Snake rides in
 * (jeep.c), the second jeep (jeep2.c), the scroll actor (jeep_srl.c), the
 * effects and the demo camera. Defined in overlay6.c. */
typedef struct _JEEP_SYSTEM
{
    /* 0x00 */ char        pad_00[0x04];
    /* 0x04 */ CONTROL    *control;         // set by jeep.c
    /* 0x08 */ SVECTOR    *rot;             // set by jeep.c
    /* 0x0C */ int         active2;         // set by jeep2.c
    /* 0x10 */ CONTROL    *control2;        // set by jeep2.c
    /* 0x14 */ SVECTOR    *rot2;            // set by jeep2.c
    /* 0x18 */ SVECTOR     pos;             // position of the jeep, as seen by the effects
    /* 0x20 */ SVECTOR     offset;          // push applied to the world around the jeep
    /* 0x28 */ VECTOR      world_pos;       // world position of the jeep
    /* 0x38 */ SVECTOR     field_38;
    /* 0x40 */ int         field_40;
    /* 0x44 */ int         field_44;
    /* 0x48 */ int         field_48;
    /* 0x4C */ int         flags;
    /* 0x50 */ int         flags_50;
    /* 0x54 */ int         flags_54;
    /* 0x58 */ char        pad_58[0x04];
    /* 0x5C */ int         has_homing_target;
    /* 0x60 */ OBJECT     *snake_body;
    /* 0x64 */ OBJECT     *meryl_body;
    /* 0x68 */ OBJECT     *liq_obj;
    /* 0x6C */ OBJECT     *body;            // set by jeep.c
    /* 0x70 */ OBJECT     *body2;           // set by jeep2.c
    /* 0x74 */ char        pad_74[0x04];
    /* 0x78 */ int         field_78;
    /* 0x7C */ int         field_7C;
    /* 0x80 */ MATRIX      world;
    /* 0xA0 */ char        pad_A0[0x128 - 0xA0];
    /* 0x128 */ SVECTOR    camera_pos;      // Snake's camera point
    /* 0x130 */ SVECTOR    meryl_head;      // world position of Meryl's head (jeep_mrl.c)
    /* 0x138 */ SVECTOR    liq_pos;         // world position of Liquid (jeep_liq.c)
    /* 0x140 */ SVECTOR    attach_pos[2];   // world position of the attach points of the two jeeps
    /* 0x150 */ JEEP_ATTACH attach[2];
    /* 0x168 */ struct _DemoCamera *demo_camera;
} JEEP_SYSTEM;

#ifndef __S19B_OVERLAY6_C__ // HACK: the definitions must not follow an extern declaration
extern JEEP_SYSTEM Takabe_JeepSystem;

/* The original code writes these two through their own symbols (a base register
 * of their own, not the one of the struct), so they are separate variables
 * located right where the fields of the same name are. */
extern SVECTOR Takabe_MerylHeadPos; // Takabe_JeepSystem.meryl_head
extern SVECTOR Takabe_JeepLiqPos;   // Takabe_JeepSystem.liq_pos
#endif

#endif
