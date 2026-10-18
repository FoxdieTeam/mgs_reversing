#ifndef _VRTITLE_VRPOCKET_H
#define _VRTITLE_VRPOCKET_H

// "Pocket" object list used by the title screen items (VR revision of the
// rank overlay's overlays/rank/chara/pocket/{entry,pkt_back}.c).

// Entry of the singly linked list of pocket objects.
typedef struct PocketObj
{
    /* 0x00 */ struct PocketObj *prev;
    /* 0x04 */ struct PocketObj *next;
    /* 0x08 */ int               field_8;
    /* 0x0C */ short             field_C;
    /* 0x0E */ short             field_E;
    /* 0x10 */ short             count; // number of sub entries, see vrtitle_800C3028
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

// Pending (id, value) update, applied to the list by the owner's update function.
typedef struct PocketUpdate
{
    /* 0x00 */ unsigned short id;
    /* 0x02 */ short          value;
} PocketUpdate;

#endif
