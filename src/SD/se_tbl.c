#include "SD/sound.h"
#include "SD/sd_incl.h"

// Some of the original names can probably be recovered from PSY-Q linker maps
// that got memleaked, depending on whether they actually match up to addresses
// in the various other builds of the game.
//
// Example found in 's17ar.bin' from SLPM-86111 (JP)
// --------------------
// 800A2688  jingle0300
// 800A26B0  jingle0301
// 800A26D8  jingle0302
// --------------------
// Each track has a basename (limited to 8-chars), "jingle03" in this case.
// The double-digit suffix indicates the index into SETBL.addr[].

#include "se_data/blob.h"

unsigned char se_dummy[] = { 0x00,0x00,0xfe,0xff };

#define ADDR(_array)    ((unsigned int)&_array[0])
#define SE_DUMMY        ((unsigned int)&se_dummy[0])

SETBL se_tbl_800A22C4[128] = {
    /* pri,tracks,kind,character */
    { 0x01, 0x01, 0x01, 0x00, { SE_DUMMY, SE_DUMMY, SE_DUMMY }}, /* 0 */
    { 0x40, 0x01, 0x01, 0x00, { ADDR(seunk00100), SE_DUMMY, SE_DUMMY }}, /* 1 */
    { 0x10, 0x01, 0x01, 0x00, { ADDR(seunk00200), SE_DUMMY, SE_DUMMY }}, /* 2 */
    { 0x10, 0x01, 0x01, 0x00, { ADDR(seunk00300), SE_DUMMY, SE_DUMMY }}, /* 3 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(karasht00), SE_DUMMY, SE_DUMMY }}, /* 4 */
    { 0x20, 0x01, 0x01, 0x00, { ADDR(seunk00500), SE_DUMMY, SE_DUMMY }}, /* 5 */
    { 0x20, 0x01, 0x01, 0x00, { ADDR(seunk00600), SE_DUMMY, SE_DUMMY }}, /* 6 */
    { 0x20, 0x01, 0x01, 0x00, { ADDR(seunk00700), SE_DUMMY, SE_DUMMY }}, /* 7 */
    { 0x20, 0x01, 0x01, 0x00, { ADDR(seunk00800), SE_DUMMY, SE_DUMMY }}, /* 8 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(seunk00900), SE_DUMMY, SE_DUMMY }}, /* 9 */
    { 0x30, 0x01, 0x00, 0x00, { ADDR(seunk01000), SE_DUMMY, SE_DUMMY }}, /* 10 */
    { 0x90, 0x01, 0x00, 0x00, { ADDR(seunk01100), SE_DUMMY, SE_DUMMY }}, /* 11 */
    { 0xB0, 0x01, 0x00, 0x00, { ADDR(seunk01200), SE_DUMMY, SE_DUMMY }}, /* 12 */
    { 0x90, 0x01, 0x00, 0x00, { ADDR(seunk01300), SE_DUMMY, SE_DUMMY }}, /* 13 */
    { 0x90, 0x01, 0x00, 0x00, { ADDR(seunk01400), SE_DUMMY, SE_DUMMY }}, /* 14 */
    { 0xF0, 0x03, 0x00, 0x00, { ADDR(seunk01500), ADDR(seunk01501), ADDR(seunk01502) }}, /* 15 */
    { 0x20, 0x01, 0x00, 0x00, { ADDR(seunk01600), SE_DUMMY, SE_DUMMY }}, /* 16 */
    { 0x90, 0x01, 0x00, 0x00, { ADDR(seunk01700), SE_DUMMY, SE_DUMMY }}, /* 17 */
    { 0xA0, 0x01, 0x01, 0x01, { ADDR(seunk01800), SE_DUMMY, SE_DUMMY }}, /* 18 */
    { 0xA0, 0x01, 0x01, 0x01, { ADDR(seunk01900), SE_DUMMY, SE_DUMMY }}, /* 19 */
    { 0x90, 0x01, 0x01, 0x00, { ADDR(seunk02000), SE_DUMMY, SE_DUMMY }}, /* 20 */
    { 0x20, 0x01, 0x00, 0x00, { ADDR(seunk02100), SE_DUMMY, SE_DUMMY }}, /* 21 */
    { 0x90, 0x02, 0x00, 0x00, { ADDR(seunk02200), ADDR(seunk02201), SE_DUMMY }}, /* 22 */
    { 0x10, 0x01, 0x00, 0x00, { ADDR(seunk02300), SE_DUMMY, SE_DUMMY }}, /* 23 */
    { 0xA0, 0x01, 0x01, 0x01, { ADDR(seunk02400), SE_DUMMY, SE_DUMMY }}, /* 24 */
    { 0xA0, 0x01, 0x01, 0x01, { ADDR(seunk02500), SE_DUMMY, SE_DUMMY }}, /* 25 */
    { 0xF0, 0x01, 0x00, 0x01, { ADDR(seunk02600), SE_DUMMY, SE_DUMMY }}, /* 26 */
    { 0x40, 0x01, 0x01, 0x00, { ADDR(seunk02700), SE_DUMMY, SE_DUMMY }}, /* 27 */
    { 0x20, 0x01, 0x01, 0x00, { ADDR(seunk02800), SE_DUMMY, SE_DUMMY }}, /* 28 */
    { 0x10, 0x01, 0x01, 0x00, { ADDR(seunk02900), SE_DUMMY, SE_DUMMY }}, /* 29 */
    { 0x20, 0x01, 0x01, 0x00, { ADDR(seunk03000), SE_DUMMY, SE_DUMMY }}, /* 30 */
    { 0x90, 0x01, 0x00, 0x00, { ADDR(seunk03100), SE_DUMMY, SE_DUMMY }}, /* 31 */
    { 0x90, 0x02, 0x00, 0x00, { ADDR(seunk03200), ADDR(seunk03201), SE_DUMMY }}, /* 32 */
    { 0x90, 0x03, 0x00, 0x00, { ADDR(seunk03300), ADDR(seunk03301), ADDR(seunk03302) }}, /* 33 */
    { 0x90, 0x02, 0x00, 0x00, { ADDR(seunk03400), ADDR(seunk03401), SE_DUMMY }}, /* 34 */
    { 0x90, 0x01, 0x01, 0x00, { ADDR(seunk03500), SE_DUMMY, SE_DUMMY }}, /* 35 */
    { 0x20, 0x02, 0x00, 0x00, { ADDR(seunk03600), ADDR(seunk03601), SE_DUMMY }}, /* 36 */
    { 0x60, 0x01, 0x01, 0x00, { ADDR(seunk03700), SE_DUMMY, SE_DUMMY }}, /* 37 */
    { 0x60, 0x01, 0x01, 0x00, { ADDR(seunk03800), SE_DUMMY, SE_DUMMY }}, /* 38 */
    { 0x10, 0x01, 0x01, 0x00, { ADDR(seunk03900), SE_DUMMY, SE_DUMMY }}, /* 39 */
    { 0x40, 0x01, 0x01, 0x00, { ADDR(seunk04000), SE_DUMMY, SE_DUMMY }}, /* 40 */
    { 0x90, 0x01, 0x01, 0x00, { ADDR(seunk04100), SE_DUMMY, SE_DUMMY }}, /* 41 */
    { 0xA0, 0x01, 0x00, 0x00, { ADDR(seunk04200), SE_DUMMY, SE_DUMMY }}, /* 42 */
    { 0x20, 0x01, 0x01, 0x00, { ADDR(seunk04300), SE_DUMMY, SE_DUMMY }}, /* 43 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(pinnuki00), SE_DUMMY, SE_DUMMY }}, /* 44 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(seunk04500), SE_DUMMY, SE_DUMMY }}, /* 45 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(seunk04600), SE_DUMMY, SE_DUMMY }}, /* 46 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(seunk04700), SE_DUMMY, SE_DUMMY }}, /* 47 */
    { 0x40, 0x01, 0x01, 0x00, { ADDR(seunk04800), SE_DUMMY, SE_DUMMY }}, /* 48 */
    { 0x40, 0x01, 0x01, 0x00, { ADDR(seunk04900), SE_DUMMY, SE_DUMMY }}, /* 49 */
    { 0x40, 0x01, 0x01, 0x00, { ADDR(seunk05000), SE_DUMMY, SE_DUMMY }}, /* 50 */
    { 0x70, 0x01, 0x01, 0x00, { ADDR(seunk05100), SE_DUMMY, SE_DUMMY }}, /* 51 */
    { 0x40, 0x01, 0x01, 0x00, { ADDR(seunk05200), SE_DUMMY, SE_DUMMY }}, /* 52 */
    { 0x40, 0x01, 0x01, 0x00, { ADDR(seunk05300), SE_DUMMY, SE_DUMMY }}, /* 53 */
    { 0x10, 0x01, 0x00, 0x00, { ADDR(seunk05400), SE_DUMMY, SE_DUMMY }}, /* 54 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(seunk05500), SE_DUMMY, SE_DUMMY }}, /* 55 */
    { 0x20, 0x01, 0x01, 0x00, { ADDR(seunk05600), SE_DUMMY, SE_DUMMY }}, /* 56 */
    { 0x20, 0x01, 0x01, 0x00, { ADDR(seunk05700), SE_DUMMY, SE_DUMMY }}, /* 57 */
    { 0x90, 0x02, 0x00, 0x00, { ADDR(seunk05800), ADDR(seunk05801), SE_DUMMY }}, /* 58 */
    { 0x60, 0x01, 0x01, 0x00, { ADDR(seunk05900), SE_DUMMY, SE_DUMMY }}, /* 59 */
    { 0x40, 0x01, 0x01, 0x00, { ADDR(seunk06000), SE_DUMMY, SE_DUMMY }}, /* 60 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(seunk06100), SE_DUMMY, SE_DUMMY }}, /* 61 */
    { 0x40, 0x01, 0x01, 0x00, { ADDR(seunk06200), SE_DUMMY, SE_DUMMY }}, /* 62 */
    { 0x60, 0x01, 0x01, 0x00, { ADDR(seunk06300), SE_DUMMY, SE_DUMMY }}, /* 63 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(seunk06400), SE_DUMMY, SE_DUMMY }}, /* 64 */
    { 0x90, 0x02, 0x01, 0x00, { ADDR(seunk06500), ADDR(seunk06501), SE_DUMMY }}, /* 65 */
    { 0x70, 0x01, 0x01, 0x00, { ADDR(seunk06600), SE_DUMMY, SE_DUMMY }}, /* 66 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(seunk06700), SE_DUMMY, SE_DUMMY }}, /* 67 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(seunk06800), SE_DUMMY, SE_DUMMY }}, /* 68 */
    { 0x01, 0x00, 0x00, 0x00, { SE_DUMMY, SE_DUMMY, SE_DUMMY }}, /* 69 */
    { 0x01, 0x00, 0x00, 0x00, { SE_DUMMY, SE_DUMMY, SE_DUMMY }}, /* 70 */
    { 0x01, 0x00, 0x00, 0x00, { SE_DUMMY, SE_DUMMY, SE_DUMMY }}, /* 71 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(seunk07200), SE_DUMMY, SE_DUMMY }}, /* 72 */
    { 0x40, 0x01, 0x01, 0x00, { ADDR(seunk07300), SE_DUMMY, SE_DUMMY }}, /* 73 */
    { 0x80, 0x02, 0x00, 0x00, { ADDR(seunk07400), ADDR(seunk07401), SE_DUMMY }}, /* 74 */
    { 0xFF, 0x01, 0x00, 0x00, { ADDR(seunk07500), SE_DUMMY, SE_DUMMY }}, /* 75 */
    { 0x40, 0x01, 0x01, 0x00, { ADDR(seunk07600), SE_DUMMY, SE_DUMMY }}, /* 76 */
    { 0x40, 0x01, 0x01, 0x00, { ADDR(seunk07700), SE_DUMMY, SE_DUMMY }}, /* 77 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(seunk07800), SE_DUMMY, SE_DUMMY }}, /* 78 */
    { 0x30, 0x01, 0x00, 0x00, { ADDR(seunk07900), SE_DUMMY, SE_DUMMY }}, /* 79 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(seunk08000), SE_DUMMY, SE_DUMMY }}, /* 80 */
    { 0x60, 0x01, 0x01, 0x00, { ADDR(seunk08100), SE_DUMMY, SE_DUMMY }}, /* 81 */
    { 0x40, 0x01, 0x01, 0x00, { ADDR(seunk08200), SE_DUMMY, SE_DUMMY }}, /* 82 */
    { 0xA0, 0x03, 0x00, 0x00, { ADDR(seunk08300), ADDR(seunk08301), ADDR(seunk08302) }}, /* 83 */
    { 0x80, 0x02, 0x00, 0x00, { ADDR(seunk08400), ADDR(seunk08401), SE_DUMMY }}, /* 84 */
    { 0x80, 0x01, 0x00, 0x00, { ADDR(seunk08500), SE_DUMMY, SE_DUMMY }}, /* 85 */
    { 0x80, 0x01, 0x00, 0x00, { ADDR(seunk08600), SE_DUMMY, SE_DUMMY }}, /* 86 */
    { 0x80, 0x02, 0x00, 0x00, { ADDR(seunk08700), ADDR(seunk08701), SE_DUMMY }}, /* 87 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(seunk08800), SE_DUMMY, SE_DUMMY }}, /* 88 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(seunk08900), SE_DUMMY, SE_DUMMY }}, /* 89 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(seunk09000), SE_DUMMY, SE_DUMMY }}, /* 90 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(seunk09100), SE_DUMMY, SE_DUMMY }}, /* 91 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(seunk09200), SE_DUMMY, SE_DUMMY }}, /* 92 */
    { 0x30, 0x01, 0x01, 0x00, { ADDR(seunk09300), SE_DUMMY, SE_DUMMY }}, /* 93 */
    { 0x10, 0x01, 0x01, 0x00, { ADDR(seunk09400), SE_DUMMY, SE_DUMMY }}, /* 94 */
    { 0x90, 0x01, 0x01, 0x00, { ADDR(seunk09500), SE_DUMMY, SE_DUMMY }}, /* 95 */
    { 0x20, 0x01, 0x01, 0x00, { ADDR(seunk09600), SE_DUMMY, SE_DUMMY }}, /* 96 */
    { 0x20, 0x01, 0x01, 0x00, { ADDR(seunk09700), SE_DUMMY, SE_DUMMY }}, /* 97 */
    { 0x20, 0x01, 0x01, 0x00, { ADDR(seunk09800), SE_DUMMY, SE_DUMMY }}, /* 98 */
    { 0x10, 0x01, 0x01, 0x00, { ADDR(seunk09900), SE_DUMMY, SE_DUMMY }}, /* 99 */
    { 0xFF, 0x03, 0x00, 0x00, { ADDR(seunk10000), ADDR(seunk10001), ADDR(seunk10002) }}, /* 100 */
    { 0x40, 0x01, 0x01, 0x00, { ADDR(seunk10100), SE_DUMMY, SE_DUMMY }}, /* 101 */
    { 0xF0, 0x02, 0x00, 0x00, { ADDR(seunk10200), ADDR(seunk10201), SE_DUMMY }}, /* 102 */
    { 0x20, 0x01, 0x00, 0x00, { ADDR(seunk10300), SE_DUMMY, SE_DUMMY }}, /* 103 */
    { 0x80, 0x01, 0x00, 0x00, { ADDR(seunk10400), SE_DUMMY, SE_DUMMY }}, /* 104 */
    { 0x80, 0x01, 0x00, 0x00, { ADDR(seunk10500), SE_DUMMY, SE_DUMMY }}, /* 105 */
    { 0x90, 0x01, 0x00, 0x00, { ADDR(seunk10600), SE_DUMMY, SE_DUMMY }}, /* 106 */
    { 0x90, 0x01, 0x00, 0x01, { ADDR(seunk10700), SE_DUMMY, SE_DUMMY }}, /* 107 */
    { 0x80, 0x02, 0x00, 0x00, { ADDR(seunk10800), ADDR(seunk10801), SE_DUMMY }}, /* 108 */
    { 0x20, 0x01, 0x01, 0x00, { ADDR(seunk10900), SE_DUMMY, SE_DUMMY }}, /* 109 */
    { 0x40, 0x02, 0x01, 0x00, { ADDR(seunk11000), ADDR(seunk11001), SE_DUMMY }}, /* 110 */
    { 0x30, 0x02, 0x01, 0x00, { ADDR(seunk11100), ADDR(seunk11101), SE_DUMMY }}, /* 111 */
    { 0x20, 0x01, 0x01, 0x00, { ADDR(seunk11200), SE_DUMMY, SE_DUMMY }}, /* 112 */
    { 0x30, 0x02, 0x01, 0x00, { ADDR(seunk11300), ADDR(seunk11301), SE_DUMMY }}, /* 113 */
    { 0x90, 0x01, 0x00, 0x00, { ADDR(seunk11400), SE_DUMMY, SE_DUMMY }}, /* 114 */
    { 0xB0, 0x01, 0x00, 0x00, { ADDR(seunk11500), SE_DUMMY, SE_DUMMY }}, /* 115 */
    { 0x40, 0x01, 0x00, 0x00, { ADDR(seunk11600), SE_DUMMY, SE_DUMMY }}, /* 116 */
    { 0xB0, 0x01, 0x00, 0x00, { ADDR(seunk11700), SE_DUMMY, SE_DUMMY }}, /* 117 */
    { 0x80, 0x01, 0x00, 0x00, { ADDR(seunk11800), SE_DUMMY, SE_DUMMY }}, /* 118 */
    { 0xB0, 0x01, 0x00, 0x00, { ADDR(seunk11900), SE_DUMMY, SE_DUMMY }}, /* 119 */
    { 0x90, 0x02, 0x00, 0x00, { ADDR(seunk12000), ADDR(seunk12001), SE_DUMMY }}, /* 120 */
    { 0xF0, 0x02, 0x00, 0x00, { ADDR(seunk12100), ADDR(seunk12101), SE_DUMMY }}, /* 121 */
    { 0xF0, 0x03, 0x00, 0x00, { ADDR(seunk12200), ADDR(seunk12201), ADDR(seunk12202) }}, /* 122 */
    { 0xF0, 0x03, 0x00, 0x00, { ADDR(seunk12300), ADDR(seunk12301), ADDR(seunk12302) }}, /* 123 */
    { 0x40, 0x02, 0x01, 0x00, { ADDR(seunk12400), ADDR(seunk12401), SE_DUMMY }}, /* 124 */
    { 0xF0, 0x02, 0x00, 0x00, { ADDR(seunk12500), ADDR(seunk12501), SE_DUMMY }}, /* 125 */
    { 0xB0, 0x03, 0x00, 0x00, { ADDR(seunk12600), ADDR(seunk12601), ADDR(seunk12602) }}, /* 126 */
    { 0x90, 0x01, 0x00, 0x00, { ADDR(seunk12700), SE_DUMMY, SE_DUMMY }}  /* 127 */
};
