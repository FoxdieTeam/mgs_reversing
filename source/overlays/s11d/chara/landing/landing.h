#ifndef S11D_LANDING_H
#define S11D_LANDING_H

#include "common.h"
#include "libgv/libgv.h"
#include "game/control.h"
#include "game/game.h"

// Landing system global variables (at 0x800C3324+)
// These track helicopter landing zone state
extern unsigned char landing_byte_800C3324;
extern int           landing_int_800C3328;
extern int           landing_int_800C332C;
extern int           landing_int_800C3330;
extern unsigned char landing_byte_800C3334;
extern unsigned char landing_byte_800C3335;
extern int           landing_int_800C3338;
extern int           landing_int_800C333C;
extern int           landing_int_800C3340;
extern int           landing_int_800C3344;

// Landing array (at 0x800D1F8C)
extern int landing_array_800D1F8C[];

// Landing actor work structure
// Total size: 0x914 (2324 bytes)
typedef struct LandingWork
{
    GV_ACT  actor;                   // 0x00 - Base actor (32 bytes)
    CONTROL control;                 // 0x20 - Movement/collision control (0x64 bytes)
    char    field_84[0x18];          // 0x84 - Unknown data (24 bytes)
    OBJECT  object;                  // 0x9C - 3D object representation
    char    field_A0[0x738];         // 0xA0+ TODO: recalculate - various game data
    void   *field_7D8;               // 0x7D8 - DG_PRIM pointer (graphics primitive)
    char    field_7DC[0x20];         // 0x7DC - Padding
    void   *shadow;                  // 0x7FC - Shadow object pointer
    void   *field_800;               // 0x800 - DG_PRIM pointer (graphics primitive)
    char    field_804[0x100];        // 0x804 - More data
    int     field_904;               // 0x904 - GCL option 'l' value
    int     field_908;               // 0x908 - Counter/flags
    int     field_90C;               // 0x90C - GCL option 'c' value
    int     field_910;               // 0x910 - GCL option 'e' value
} LandingWork;

// Function declarations

// Tier 1: Simple getters
int           s11d_landing_800CD094(void);
unsigned char s11d_landing_800CD0A4(void);
unsigned char s11d_landing_800CD0B4(void);
int           s11d_landing_800CD0C4(void);
int           s11d_landing_800CD144(void);

// Tier 2: Simple setter
void          s11d_landing_800CCEA8(int arg0, int arg1);

// Tier 3A: Simple logic functions
int           s11d_landing_800CD0D4(int arg);
void          s11d_landing_800CD10C(void);
void          s11d_landing_800CCE64(int index, int value);

// Tier 3B: Initialization function
void          s11d_landing_800CCDE0(void);

// Tier 4: Complex functions (forward declarations)
void          s11d_landing_800CD154(GV_ACT *actor);  // Act function
void          s11d_landing_800CD378(GV_ACT *actor);  // Die function
int           s11d_landing_800CD810(LandingWork *work, int arg1, int arg2);  // Init function

// Main entry point / constructor
GV_ACT       *s11d_landing_800CDA20(int arg0, int arg1);

#endif // S11D_LANDING_H
