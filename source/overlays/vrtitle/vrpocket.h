#ifndef _VRTITLE_VRPOCKET_H
#define _VRTITLE_VRPOCKET_H

// "Pocket" object list used by the title screen items (VR revision of the
// rank overlay's overlays/rank/chara/pocket/{entry,pkt_back}.c).

// Entry of the singly linked list of pocket objects.
typedef struct PocketObj
{
    /* 0x00 */ int               field_0;
    /* 0x04 */ struct PocketObj *next;
    /* 0x08 */ int               field_8;
    /* 0x0C */ short             field_C;
    /* 0x0E */ short             field_E;
    /* 0x10 */ char              pad_10[ 3 ];
    /* 0x13 */ char              enabled;
    /* 0x14 */ int               field_14;
    /* 0x18 */ int               field_18;
    /* 0x1C */ char              field_1C;
    /* 0x1D */ char              pad_1D;
    /* 0x1E */ unsigned short    flags;
    /* 0x20 */ int               pad_20;
    /* 0x24 */ unsigned short    id;
    /* 0x26 */ short             value;
} PocketObj; // allocated as 0x28 or 0x34 bytes, see vrtitle_800C99A8

// Pending (id, value) update, applied to the list by the owner's update function.
typedef struct PocketUpdate
{
    /* 0x00 */ unsigned short id;
    /* 0x02 */ short          value;
} PocketUpdate;

#endif
