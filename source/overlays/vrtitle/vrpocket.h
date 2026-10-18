#ifndef _VRTITLE_VRPOCKET_H
#define _VRTITLE_VRPOCKET_H

// "Pocket" object list used by the title screen items (VR revision of the
// rank overlay's overlays/rank/chara/pocket/{entry,pkt_back}.c).

// Entry of the singly linked list of pocket objects.
typedef struct PocketObj
{
    /* 0x00 */ struct PocketObj *prev;
    /* 0x04 */ struct PocketObj *next;
    /* 0x08 */ void            (*update)(); // per frame callback of the owner (parameters differ per object kind)
    /* 0x0C */ short             field_C;
    /* 0x0E */ short             field_E;
    /* 0x10 */ unsigned short    count; // number of sub entries, see vrtitle_800C3028
    /* 0x12 */ char              kind;
    /* 0x13 */ char              enabled;
    /* 0x14 */ union
    {
        int word;
        struct
        {
            short          field_14;
            unsigned short field_16; // flag bits, see vrtitle_800C3A24
        } half;
    } field_14;
    /* 0x18 */ int               field_18;
    /* 0x1C */ char              field_1C;
    /* 0x1D */ char              pad_1D;
    /* 0x1E */ unsigned short    flags;
    /* 0x20 */ void             *entries;
    /* 0x24 */ unsigned short    id;
    /* 0x26 */ short             value;
    /* 0x28 */ int               field_28;
} PocketObj; // 0x2C bytes; the entries array it owns has 0x28 or 0x34 byte elements, see vrtitle_800C99A8

#define POCKET_OBJ_MAX 32



#include "libgv/libgv.h"
#include "libdg/libdg.h"

// Pending (id, value) update, applied to the list by the owner's update function.
typedef struct PocketUpdate
{
    /* 0x00 */ unsigned short id;
    /* 0x02 */ short          value;
} PocketUpdate;

// Element of the pocket list owned by the actor (the "file mode" style item list)
typedef struct PocketListItem
{
    /* 0x00 */ char  pad_00[0x28];
    /* 0x28 */ void *data; // allocated with GV_AllocMemory(2, ..), freed by the actor's die function
} PocketListItem; // 0x2C bytes

#define POCKET_LIST_MAX 24

typedef struct PocketList
{
    /* 0x000 */ int            field_0;
    /* 0x004 */ int            field_4;
    /* 0x008 */ int            field_8;
    /* 0x00C */ int            field_C;
    /* 0x010 */ PocketListItem items[POCKET_LIST_MAX];
    /* 0x430 */ int            count;
} PocketList;

// Entry of the pocket menu, filled from the GCL "t" option of the stage script
typedef struct PocketEntry
{
    /* 0x00 */ char *name; // GCL string
    /* 0x04 */ short selected;
    /* 0x06 */ char  pad_06[0xDA];
} PocketEntry; // 0xE0 bytes

// Work of the pocket (title menu) actor, created by vrtitle_800C97E0, 0x1A48 bytes
typedef struct PocketWork
{
    /* 0x0000 */ GV_ACT     actor;
    /* 0x0020 */ char       pad_20[0xC];
    /* 0x002C */ PocketList list;
    /* 0x0460 */ char       pad_460[0xC8];
    /* 0x0528 */ PocketEntry entries[22];
    /* 0x1868 */ char       pad_1868[0x124];
    /* 0x198C */ DG_PRIM   *prim1;
    /* 0x1990 */ DG_PRIM   *prim2;
    /* 0x1994 */ int         update_count;
    /* 0x1998 */ PocketUpdate updates[32]; // queued (id, value) updates, applied by vrtitle_800C9BE0
    /* 0x1A18 */ char       pad_1A18[4];
    /* 0x1A1C */ unsigned int flags;
    /* 0x1A20 */ char       pad_1A20[0x28];
} PocketWork;

// Work of the second pocket actor (pkt_back variant): same update queue, but only 8 slots
typedef struct PocketBackWork
{
    /* 0x00 */ char         pad_00[0x34];
    /* 0x34 */ int          update_count;
    /* 0x38 */ PocketUpdate updates[8];
} PocketBackWork;

#define POCKET_UPDATE_MAX2 8

#endif
