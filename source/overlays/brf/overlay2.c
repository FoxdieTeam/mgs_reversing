#include "overlays/brf/onoda/brf/brf.h"

extern const char brf_dword_800E13BC[];
extern const char brf_dword_800E13D8[];
extern const char brf_dword_800E13F4[];
extern const char brf_dword_800E140C[];
extern const char brf_dword_800E1424[];
extern const char brf_dword_800E1438[];
extern const char brf_dword_800E1450[];
extern const char brf_dword_800E146C[];
extern const char brf_dword_800E1480[];
extern const char brf_dword_800E1494[];
extern const char brf_dword_800E14A8[];
extern const char brf_dword_800E14C4[];
extern const char brf_dword_800E14E0[];
extern const char brf_dword_800E14F0[];
extern const char brf_dword_800E150C[];
extern const char brf_dword_800E1524[];
extern const char brf_dword_800E1534[];
extern const char brf_dword_800E1550[];
extern const char brf_dword_800E1564[];
extern const char brf_dword_800E1580[];
extern const char brf_dword_800E159C[];
extern const char brf_dword_800E15B8[];
extern const char brf_dword_800E15CC[];
extern const char brf_dword_800E15E4[];
extern const char brf_dword_800E15F8[];
extern const char brf_dword_800E1614[];
extern const char brf_dword_800E1630[];
extern const char brf_dword_800E164C[];
extern const char brf_dword_800E1664[];
extern const char brf_dword_800E1680[];
extern const char brf_dword_800E169C[];
extern const char brf_dword_800E16B8[];
extern const char brf_dword_800E16D0[];
extern const char brf_dword_800E16D8[];
extern const char brf_dword_800E16E8[];
extern const char brf_dword_800E1700[];
extern const char brf_dword_800E1708[];
extern const char brf_dword_800E1714[];
extern const char brf_dword_800E1730[];
extern const char brf_dword_800E173C[];
extern const char brf_dword_800E1748[];
extern const char brf_dword_800E1764[];
extern const char brf_dword_800E177C[];
extern const char brf_dword_800E1798[];
extern const char brf_dword_800E17AC[];
extern const char brf_dword_800E17C4[];
extern const char brf_dword_800E17E0[];
extern const char brf_dword_800E17F8[];
extern const char brf_dword_800E180C[];
extern const char brf_dword_800E1828[];
extern const char brf_dword_800E1838[];
extern const char brf_dword_800E184C[];
extern const char brf_dword_800E1854[];
extern const char brf_dword_800E186C[];
extern const char brf_dword_800E1878[];
extern const char brf_dword_800E1880[];
extern const char brf_dword_800E1890[];
extern const char brf_dword_800E1898[];
extern const char brf_dword_800E18A8[];
extern const char brf_dword_800E18B4[];
extern const char brf_dword_800E18BC[];
extern const char brf_dword_800E18C8[];
extern const char brf_dword_800E18D8[];
extern const char brf_dword_800E18E0[];
extern const char brf_dword_800E18E8[];
extern const char brf_dword_800E18F4[];
extern const char brf_dword_800E18FC[];
extern const char brf_dword_800E1904[];
extern const char brf_dword_800E1910[];
extern const char brf_dword_800E1924[];
extern const char brf_dword_800E1938[];
extern const char brf_dword_800E1954[];
extern const char brf_dword_800E196C[];
extern const char brf_dword_800E1980[];
extern const char brf_dword_800E1994[];
extern const char brf_dword_800E19AC[];
extern const char brf_dword_800E19C4[];
extern const char brf_dword_800E19E0[];
extern const char brf_dword_800E19F0[];
extern const char brf_dword_800E1A08[];
extern const char brf_dword_800E1A20[];
extern const char brf_dword_800E1A38[];
extern const char brf_dword_800E1A48[];
extern const char brf_dword_800E1A64[];
extern const char brf_dword_800E1A80[];
extern const char brf_dword_800E1A9C[];
extern const char brf_dword_800E1AB0[];
extern const char brf_dword_800E1ACC[];
extern const char brf_dword_800E1AE8[];
extern const char brf_dword_800E1B04[];
extern const char brf_dword_800E1B1C[];
extern const char brf_dword_800E1B30[];
extern const char brf_dword_800E1B44[];
extern const char brf_dword_800E1B5C[];
extern const char brf_dword_800E1B74[];
extern const char brf_dword_800E1B84[];
extern const char brf_dword_800E1BA0[];
extern const char brf_dword_800E1BAC[];
extern const char brf_dword_800E1BB8[];
extern const char brf_dword_800E1BC8[];
extern const char brf_dword_800E1BE0[];

void brf_800CF984();
void brf_800D00C4();
void brf_800D02F4();
void brf_800D26E4();
void brf_800D3220();
void brf_800D41A4();
void brf_800D4664();
void brf_800D4A34();
void brf_800D52F0();
void brf_800D5780();
void brf_800D5ED0();
void brf_800D674C();
void brf_800D69A8();
void brf_800D70A4();
void brf_800D8060();
void brf_800D93F4();
void brf_800DBA7C();
void brf_800DCFB4();
void brf_800DD648();

/*
 * .data of b_graph.c. It belongs to b_graph.c (which links right after this
 * file), but defining it there changes how the assembler splits b_graph's code
 * records, which trips build/include_asm_fixup.py (objlib) on the INCLUDE_ASM
 * functions, so it is kept in this data-only file for now.
 */

/* number of b_graph polys in use per briefing index */
short brf_poly_counts[20] = {
    11, 5, 15, 835, 4, 291, 9, 40, 10, 9, 20, 10, 10, 9, 74, 684, 37, 12, 1, 0,
};

/* per-scene update function of each briefing (called from brf_800DDC40) */
void (*brf_scene_funcs[19])() = {
    brf_800CF984,
    brf_800D00C4,
    brf_800D02F4,
    brf_800D26E4,
    brf_800D3220,
    brf_800D41A4,
    brf_800D4664,
    brf_800D4A34,
    brf_800D52F0,
    brf_800D5780,
    brf_800D5ED0,
    brf_800D674C,
    brf_800D69A8,
    brf_800D70A4,
    brf_800D8060,
    brf_800D93F4,
    brf_800DBA7C,
    brf_800DCFB4,
    brf_800DD648,
};

/* polygon rectangles {poly index, x0, y0, x1, y1} scaled by brf_800CDAEC */
BrfPolyRect brf_800C357C[2] = {
    {0, -127, -104, 127, 0},
    {1, -127, 0, 127, 88},
};
BrfPolyRect brf_800C3594[2] = {
    {4, -127, -104, 127, 0},
    {5, -127, 0, 127, 88},
};
BrfPolyRect brf_800C35AC[2] = {
    {2, -167, 21, -55, 88},
    {3, 83, -104, 143, 88},
};
BrfPolyRect brf_800C35C4[2] = {
    {6, -127, -104, 127, 0},
    {7, -127, 0, 127, 88},
};
BrfPolyRect brf_800C35DC[2] = {
    {8, -127, -104, 127, 0},
    {9, -127, 0, 127, 88},
};
BrfPolyRect brf_800C35F4[2] = {
    {0, -127, -104, 127, 0},
    {1, -127, 0, 127, 88},
};
BrfPolyRect brf_800C360C[11] = {
    {2, -45, -104, 55, 88},
    {3, -45, -104, 55, 88},
    {4, -73, -148, 13, -56},
    {5, -73, -148, 13, -56},
    {6, -51, -104, 23, -51},
    {7, -51, -104, 23, -51},
    {8, -127, -104, -45, -19},
    {9, -129, -106, -67, -13},
    {10, -127, -8, 127, 88},
    {13, -112, -82, -26, 10},
    {14, -112, -82, -26, 10},
};
BrfPolyRect brf_800C3690[2] = {
    {11, -167, 21, -55, 88},
    {12, 83, -104, 143, 88},
};
BrfPolyRect brf_800C36A8[2] = {
    {0, -127, -104, 127, 0},
    {1, -127, 0, 127, 88},
};
BrfPolyRect brf_800C36C0[9] = {
    {2, -45, -104, 55, 88},
    {3, -45, -104, 55, 88},
    {4, -73, -148, 13, -56},
    {5, -73, -148, 13, -56},
    {6, -112, -82, -26, 10},
    {7, -112, -82, -26, 10},
    {8, -51, -104, 23, -51},
    {9, -51, -104, 23, -51},
    {12, -127, -8, 127, 88},
};
BrfPolyRect brf_800C372C[2] = {
    {10, -167, 21, -55, 88},
    {11, 83, -104, 143, 88},
};
BrfPolyRect brf_800C3744[3] = {
    {8, -127, -104, 127, 88},
    {9, -127, -104, 127, 88},
    {10, -127, -104, 127, 88},
};
BrfPolyRect brf_800C3768[4] = {
    {0, -127, -104, 127, 88},
    {2, -167, 21, -55, 88},
    {3, 83, -104, 143, 88},
    {4, -127, -104, 127, 88},
};
BrfPolyRect brf_800C3798[1] = {
    {1, -127, -104, 127, 88},
};
BrfPolyRect brf_800C37A4[4] = {
    {0, -127, -104, 127, 0},
    {1, -127, 0, 127, 88},
    {2, -127, -104, 127, 0},
    {3, -127, 0, 127, 88},
};
BrfPolyRect brf_800C37D4[6] = {
    {0, -167, 21, -55, 88},
    {1, 83, -104, 143, 88},
    {2, -127, -104, 127, 0},
    {3, -127, -104, 127, 0},
    {4, -127, 0, 127, 88},
    {8, -127, 0, 127, 88},
};
BrfPolyRect brf_800C381C[7] = {
    {0, -127, -104, 127, 0},
    {1, -127, 0, 127, 88},
    {4, -127, -104, 127, 0},
    {5, -167, 21, -55, 88},
    {6, 83, -104, 143, 88},
    {38, -127, -104, 127, 0},
    {39, -127, 0, 127, 88},
};
BrfPolyRect brf_800C3870[2] = {
    {6, -127, -104, 127, 0},
    {7, -127, 0, 127, 88},
};
BrfPolyRect brf_800C3888[2] = {
    {8, -127, -104, 127, 0},
    {9, -127, 0, 127, 88},
};
BrfPolyRect brf_800C38A0[6] = {
    {3, -127, -104, 127, 0},
    {4, -127, -104, 127, 0},
    {5, -127, 0, 127, 88},
    {6, -167, 21, -55, 88},
    {7, 83, -104, 143, 88},
    {8, -127, -104, 127, 88},
};
BrfPolyRect brf_800C38E8[3] = {
    {7, -127, -104, 127, 0},
    {8, -127, -104, 127, 0},
    {9, -127, 0, 127, 88},
};
BrfPolyRect brf_800C390C[6] = {
    {0, -127, -104, 127, 0},
    {1, -127, 0, 127, 88},
    {2, -167, 21, -55, 88},
    {3, 83, -104, 143, 88},
    {4, -127, -104, 127, 0},
    {5, -127, 0, 127, 88},
};
BrfPolyRect brf_800C3954[3] = {
    {0, -127, -104, 127, 0},
    {1, -127, 0, 127, 88},
    {2, -127, -104, 127, 0},
};
BrfPolyRect brf_800C3978[5] = {
    {3, -127, -104, 127, 0},
    {4, -127, 0, 127, 88},
    {5, -127, -104, 127, 0},
    {6, -127, -104, 127, 0},
    {7, -127, 0, 127, 88},
};
BrfPolyRect brf_800C39B4[2] = {
    {0, -127, -104, 127, 0},
    {1, -127, 0, 127, 88},
};
BrfPolyRect brf_800C39CC[2] = {
    {4, -127, -104, 127, 0},
    {5, -127, -104, 127, 0},
};
BrfPolyRect brf_800C39E4[10] = {
    {0, -167, 21, -55, 88},
    {1, 83, -104, 83, 88},
    {2, -127, -104, 127, 0},
    {3, -127, -104, 127, 0},
    {4, -127, -104, 127, 0},
    {5, -127, -104, 127, 0},
    {6, -127, -104, 127, 0},
    {30, -127, 0, 127, 88},
    {31, -127, 0, 127, 88},
    {32, -127, 0, 127, 88},
};
BrfPolyRect brf_800C3A5C[5] = {
    {12, -127, -104, 127, 0},
    {13, -127, -104, 127, 0},
    {14, -127, -104, 127, 0},
    {15, -127, 0, 127, 88},
    {29, -127, -104, 127, 0},
};
BrfPolyRect brf_800C3A98[8] = {
    {0, -167, 21, -55, 88},
    {1, 83, -104, 143, 88},
    {2, -127, -104, 127, 0},
    {3, -127, 0, 127, 88},
    {4, -127, -104, 127, 0},
    {5, -127, -104, 127, 0},
    {6, -127, -104, 127, 0},
    {7, -127, 0, 127, 88},
};
BrfPolyRect brf_800C3AF8[2] = {
    {8, -127, -104, 127, 0},
    {9, -127, 0, 127, 88},
};
BrfPolyRect brf_800C3B10[8] = {
    {0, -167, 21, -55, 88},
    {1, 83, -104, 143, 88},
    {2, -127, -104, 127, 0},
    {3, -127, 0, 127, 88},
    {4, -127, -104, 127, 0},
    {6, -127, -104, 127, 0},
    {7, -127, 0, 127, 88},
    {11, -127, -104, 127, 0},
};

/* poly layouts {type, flag, x0, y0, x1, y1, texture id} per briefing index (brf_800DECF8) */
BrfLayout brf_800C3B70[11] = {
    {1, 0, -127, -104, 127, 88, 0x5CEA},
    {1, 0, -20, -45, 10, -27, 0x8927},
    {1, 1, -127, -104, 127, 88, 0x5AEA},
    {1, 0, -35, -54, 53, -8, 0xFF8A},
    {1, 0, -76, 1, 28, 88, 0x7927},
    {1, 1, -127, -104, 127, 88, 0xEE31},
    {1, 1, -127, -104, 127, 88, 0xBB03},
    {2, 1, -127, -104, 127, 88, 0x0000},
    {2, 1, -127, -104, 127, 88, 0x0000},
    {2, 1, -127, -104, 127, 88, 0x0000},
    {2, 0, -127, -104, 127, 88, 0x0000},
};
BrfLayout brf_800C3C20[5] = {
    {1, 1, -127, -104, 127, 88, 0x11FE},
    {1, 1, -127, -104, 127, 88, 0x58EE},
    {1, 1, -167, 21, -55, 88, 0x1C99},
    {3, 1, 83, -104, 143, 88, 0x667A},
    {1, 1, -127, -104, 127, 88, 0x11FE},
};
BrfLayout brf_800C3C70[15] = {
    {1, 1, -127, -104, 127, 0, 0xC5B8},
    {1, 1, -127, 0, 127, 88, 0xC5A7},
    {1, 1, -45, -104, 55, 88, 0xB2B4},
    {1, 1, -45, -104, 55, 88, 0x4FAB},
    {1, 1, -73, -148, 13, -56, 0x4F31},
    {1, 1, -73, -148, 13, -56, 0x4F32},
    {1, 1, -51, -104, 23, -51, 0x5AB2},
    {1, 1, -51, -104, 23, -51, 0x5AB3},
    {1, 1, -127, -104, -45, -19, 0xA155},
    {1, 1, -129, -106, -67, -13, 0xE1CA},
    {1, 1, -127, -8, 127, 88, 0xE9C9},
    {1, 1, -167, 21, -55, 88, 0x1C99},
    {3, 1, 83, -104, 143, 88, 0x667A},
    {1, 1, -112, -82, -26, 10, 0x4F31},
    {1, 1, -112, -82, -26, 10, 0x4F32},
};
BrfLayout brf_800C3D60[16] = {
    {1, 1, -127, -104, 127, 0, 0xC5B8},
    {1, 1, -127, 0, 127, 88, 0xC5A7},
    {1, 1, -45, -104, 55, 88, 0xA6B1},
    {1, 1, -45, -104, 55, 88, 0x24AA},
    {1, 1, -73, -148, 13, -56, 0x4F31},
    {1, 1, -73, -148, 13, -56, 0x4F32},
    {1, 1, -112, -82, -26, 10, 0x4F31},
    {1, 1, -112, -82, -26, 10, 0x4F32},
    {1, 1, -51, -104, 23, -51, 0x5AB2},
    {1, 1, -51, -104, 23, -51, 0x5AB3},
    {1, 1, -167, 21, -55, 88, 0x1C99},
    {3, 1, 83, -104, 143, 88, 0x667A},
    {1, 1, -127, -8, 127, 88, 0xE9C9},
    {1, 1, 18, -99, 112, 70, 0x6711},
    {1, 1, 18, -99, 112, 70, 0x61A6},
    {4, 0, 0, 0, 0, 0, 0x0000},
};
BrfLayout brf_800C3E60[4] = {
    {1, 1, -127, -104, 127, 88, 0xC9EA},
    {1, 0, -35, -54, 53, -8, 0xFF8A},
    {1, 0, -76, 1, 28, 88, 0x7927},
    {1, 1, -127, -120, 127, 105, 0x4F34},
};
BrfLayout brf_800C3EA0[7] = {
    {1, 1, -127, -104, 127, 0, 0xC0F4},
    {1, 1, -127, 0, 127, 88, 0xACDB},
    {1, 1, -127, -104, 127, 0, 0x2E8D},
    {1, 1, -127, 0, 127, 88, 0x2E7C},
    {1, 1, -112, -99, -18, 70, 0x4F1A},
    {1, 1, -112, -99, -18, 70, 0x61A6},
    {5, 0, 0, 0, 0, 0, 0x0000},
};
BrfLayout brf_800C3F10[9] = {
    {1, 1, -167, 21, -55, 88, 0x1C99},
    {3, 1, 83, -104, 143, 88, 0x667A},
    {1, 1, -127, -104, 127, 0, 0xC5B8},
    {1, 1, -127, -104, 127, 0, 0xA5C0},
    {1, 1, -127, 0, 127, 88, 0x98FF},
    {1, 1, -127, -104, 127, 0, 0xACEE},
    {1, 1, -127, 0, 127, 88, 0xB5B7},
    {1, 1, -127, -104, 127, 0, 0xF760},
    {1, 1, -127, 0, 127, 88, 0xC5A7},
};
BrfLayout brf_800C3FA0[10] = {
    {1, 1, -127, -104, 127, 0, 0x049D},
    {1, 1, -127, 0, 127, 88, 0x1471},
    {1, 1, -112, -99, -18, 70, 0xF1A7},
    {1, 1, 18, -99, 112, 70, 0x4F5D},
    {1, 1, -127, -104, 127, 0, 0x7A1B},
    {1, 1, -167, 21, -55, 88, 0x1C99},
    {3, 1, 83, -104, 143, 88, 0x667A},
    {1, 1, -112, -99, -18, 70, 0x61A6},
    {1, 1, 18, -99, 112, 70, 0x61A6},
    {6, 0, 0, 0, 0, 0, 0x0000},
};
BrfLayout brf_800C4040[10] = {
    {1, 1, -127, -104, 127, 0, 0xC5B8},
    {1, 1, -127, 0, 127, 88, 0xC5A7},
    {1, 1, -167, 21, -55, 88, 0x1C99},
    {3, 1, 83, -104, 143, 88, 0x667A},
    {1, 1, -127, -104, 127, 0, 0x049D},
    {1, 1, -127, 0, 127, 88, 0x1471},
    {1, 1, -127, -104, 127, 0, 0xC0F4},
    {1, 1, -127, 0, 127, 88, 0xACDB},
    {1, 1, -127, -104, 127, 0, 0xACEE},
    {1, 1, -127, 0, 127, 88, 0xB5B7},
};
BrfLayout brf_800C40E0[9] = {
    {1, 0, -127, -104, 127, 88, 0x5AEA},
    {1, 0, -35, -54, 53, -8, 0xFF8A},
    {1, 0, -76, 1, 28, 88, 0x7927},
    {1, 1, -127, -104, 127, 0, 0x049D},
    {1, 1, -127, -104, 127, 0, 0x7A1B},
    {1, 1, -127, 0, 127, 88, 0x1471},
    {1, 1, -167, 21, -55, 88, 0x1C99},
    {3, 1, 83, -104, 143, 88, 0x667A},
    {1, 0, -127, -104, 127, 88, 0x58EE},
};
BrfLayout brf_800C4170[13] = {
    {1, 1, -127, -104, 127, 88, 0xC9EA},
    {1, 1, -35, -54, 53, -8, 0x4601},
    {1, 1, -76, 1, 28, 88, 0x7927},
    {1, 1, -127, -104, 127, 88, 0x5E99},
    {1, 1, -127, -104, 127, 88, 0xF2BA},
    {1, 1, -43, -51, 47, -3, 0xD445},
    {1, 1, -82, 1, 28, 88, 0x8D8F},
    {1, 1, -127, -104, 127, 0, 0xF760},
    {2, 1, -127, -104, 127, 0, 0x0000},
    {1, 1, -127, 0, 127, 88, 0xB5B7},
    {1, 1, 18, -99, 112, 70, 0x1A9A},
    {1, 1, 18, -99, 112, 70, 0x61A6},
    {7, 0, 0, 0, 0, 0, 0x0000},
};
BrfLayout brf_800C4240[10] = {
    {1, 1, -127, -104, 127, 0, 0xC5B8},
    {1, 1, -127, 0, 127, 88, 0xC5A7},
    {1, 1, -167, 21, -55, 88, 0x1C99},
    {3, 1, 83, -104, 143, 88, 0x667A},
    {1, 1, -127, -104, 127, 0, 0x049D},
    {1, 1, -127, 0, 127, 88, 0x1471},
    {1, 1, -127, -104, 127, 0, 0xC0F4},
    {1, 1, -127, 0, 127, 88, 0xACDB},
    {1, 1, -127, -104, 127, 0, 0xACEE},
    {1, 1, -127, 0, 127, 88, 0xB5B7},
};
BrfLayout brf_800C42E0[10] = {
    {1, 1, -127, -104, 127, 88, 0xC9EA},
    {1, 1, -35, -54, 53, -8, 0xFF8A},
    {1, 1, -76, 1, 28, 88, 0x7927},
    {1, 1, -127, -104, 127, 88, 0x5E99},
    {1, 1, -127, -104, 127, 88, 0xF2BA},
    {1, 1, -43, -51, 47, -3, 0x285B},
    {1, 1, -82, 1, 28, 88, 0x8D8F},
    {1, 1, -127, -104, 127, 0, 0xACEE},
    {1, 1, -127, 0, 127, 88, 0xB5B7},
    {1, 1, -127, -104, 127, 0, 0xF760},
};
BrfLayout brf_800C4380[9] = {
    {1, 1, -127, -104, 127, 0, 0xACEE},
    {1, 1, -127, 0, 127, 88, 0xB5B7},
    {1, 1, -127, -104, 127, 0, 0xF760},
    {1, 1, -127, -104, 127, 0, 0x049D},
    {1, 1, -127, 0, 127, 88, 0x1471},
    {1, 1, -127, -104, 127, 0, 0x5E03},
    {2, 1, -127, -104, 127, 0, 0x0000},
    {1, 1, -127, 0, 127, 88, 0xC5A7},
    {1, 1, -127, -300, 127, 200, 0x4F34},
};
BrfLayout brf_800C4410[14] = {
    {1, 1, -127, -104, 127, 0, 0xC0F4},
    {1, 1, -127, 0, 127, 88, 0xACDB},
    {1, 0, -127, -104, 127, 88, 0x48D6},
    {1, 1, 0, 0, 0, 0, 0x630C},
    {1, 1, 0, 0, 0, 0, 0x61A6},
    {1, 1, 0, 0, 0, 0, 0x99B7},
    {1, 1, 0, 0, 0, 0, 0x61A6},
    {1, 1, 0, 0, 0, 0, 0xF096},
    {1, 1, 0, 0, 0, 0, 0x61A6},
    {1, 1, 0, 0, 0, 0, 0x7787},
    {1, 1, 0, 0, 0, 0, 0x61A6},
    {1, 1, 0, 0, 0, 0, 0x6B43},
    {1, 1, 0, 0, 0, 0, 0x61A6},
    {8, 0, 0, 0, 0, 0, 0x0000},
};
BrfLayout brf_800C44F0[13] = {
    {1, 1, -127, -104, 127, 88, 0xC9EA},
    {1, 1, -35, -54, 53, -8, 0xFF8A},
    {1, 1, -76, 1, 28, 88, 0x7927},
    {2, 1, -127, -104, 127, 88, 0x0000},
    {1, 1, -127, -104, 127, 0, 0xC5B8},
    {1, 1, -127, -104, 127, 0, 0x049D},
    {1, 1, -127, -104, 127, 88, 0x0554},
    {1, 1, -127, -104, 127, 88, 0x0553},
    {1, 1, -112, -99, -18, 70, 0x918D},
    {1, 1, -112, -99, -18, 70, 0x61A6},
    {1, 1, 18, 27, 54, 70, 0x2FA0},
    {1, 1, 76, 27, 112, 70, 0x2FA1},
    {9, 0, 0, 0, 0, 0, 0x0000},
};
BrfLayout brf_800C45C0[37] = {
    {1, 1, -167, 21, -55, 88, 0x1C99},
    {3, 1, 83, -104, 143, 88, 0x667A},
    {1, 1, -127, -104, 127, 0, 0xC5B8},
    {1, 1, -127, -104, 127, 0, 0x65DA},
    {1, 1, -127, -104, 127, 0, 0xF9BC},
    {1, 1, -127, -104, 127, 0, 0x3DBD},
    {1, 1, -127, -104, 127, 0, 0x049D},
    {2, 1, -127, -104, 127, 88, 0x0000},
    {1, 1, -127, -104, 127, 0, 0x43B2},
    {2, 0, -127, -104, 127, 88, 0x0000},
    {1, 0, -76, 1, 28, 88, 0x7927},
    {1, 0, -35, -54, 53, -8, 0xFF8A},
    {2, 1, -127, -104, 127, 0, 0x0000},
    {2, 1, -127, -104, 127, 0, 0x0000},
    {2, 1, -127, -104, 127, 0, 0x0000},
    {2, 1, -127, 0, 127, 88, 0x0000},
    {2, 0, -127, -104, 127, 88, 0x0000},
    {1, 1, -117, -83, -77, -31, 0x4BDE},
    {1, 1, 0, -4, 8, 4, 0x245F},
    {1, 1, 16, -73, 88, -66, 0xDAFE},
    {1, 0, -14, -47, 58, -40, 0x8A1D},
    {1, 0, 42, -91, 58, -75, 0x4B5F},
    {1, 1, -75, -69, -31, -60, 0x4B5E},
    {1, 1, -117, -83, -77, -74, 0x4B5D},
    {1, 1, 88, -13, 96, -5, 0x6792},
    {1, 0, -121, -100, -21, -66, 0x500E},
    {1, 0, -121, -100, -21, -66, 0x500D},
    {1, 0, -121, -100, -21, -66, 0x500C},
    {2, 0, -127, -104, 127, 88, 0x0000},
    {2, 1, -127, -104, 127, 88, 0x0000},
    {1, 1, -127, 0, 127, 88, 0xC5A7},
    {1, 1, -127, 0, 127, 88, 0x65C9},
    {1, 1, -127, 0, 127, 88, 0xF9AB},
    {1, 1, 0, 0, 0, 0, 0x4BC7},
    {1, 1, 0, 0, 0, 0, 0x4BC8},
    {1, 1, 0, 0, 0, 0, 0x4BC9},
    {1, 1, 0, 0, 0, 0, 0x4BCA},
};
BrfLayout brf_800C4810[12] = {
    {1, 1, -167, 21, -55, 88, 0x1C99},
    {3, 1, 83, -104, 143, 88, 0x667A},
    {1, 1, -127, -104, 127, 0, 0xC5B8},
    {1, 1, -127, 0, 127, 88, 0xC5A7},
    {1, 1, -127, -104, 127, 0, 0xF9BC},
    {1, 1, -127, -104, 127, 0, 0x3DBD},
    {1, 1, -127, -104, 127, 0, 0x049D},
    {1, 1, -127, 0, 127, 88, 0x1471},
    {1, 1, -127, -104, 127, 0, 0xC0F4},
    {1, 1, -127, 0, 127, 88, 0xACDB},
    {2, 1, -127, -104, 127, 88, 0x0000},
    {1, 1, -127, -104, 127, 0, 0xD502},
};
BrfLayout brf_800C48D0[1] = {
    {1, 1, 0, 0, 0, 0, 0x630C},
};

BrfLayout *brf_layouts[19] = {
    brf_800C3B70,
    brf_800C3C20,
    brf_800C3C70,
    brf_800C3D60,
    brf_800C3E60,
    brf_800C3EA0,
    brf_800C3F10,
    brf_800C3FA0,
    brf_800C4040,
    brf_800C40E0,
    brf_800C4170,
    brf_800C4240,
    brf_800C42E0,
    brf_800C4380,
    brf_800C4410,
    brf_800C44F0,
    brf_800C45C0,
    brf_800C4810,
    brf_800C48D0,
};

/* scene timeline {time, scene} per briefing index (brf_800DD6DC) */
BrfKeyframe brf_800C492C[12] = {
    {0, 0}, {50, 1}, {906, 2}, {1270, 3}, {1295, 4}, {1727, 5},
    {1732, 6}, {1742, 7}, {1862, 8}, {1893, 9}, {1910, 10}, {2482, 11},
};
BrfKeyframe brf_800C495C[3] = {
    {0, 0}, {50, 1}, {611, 2},
};
BrfKeyframe brf_800C4968[23] = {
    {0, 0}, {50, 1}, {164, 2}, {190, 3}, {244, 4}, {260, 5},
    {490, 6}, {513, 7}, {522, 8}, {538, 9}, {554, 10}, {1138, 11},
    {1154, 12}, {1170, 13}, {1186, 14}, {1250, 15}, {1266, 16}, {1330, 17},
    {1346, 18}, {1604, 19}, {1620, 20}, {1636, 21}, {2255, 22},
};
BrfKeyframe brf_800C49C4[11] = {
    {0, 0}, {50, 1}, {230, 2}, {246, 3}, {262, 4}, {278, 5},
    {312, 6}, {328, 7}, {392, 8}, {408, 9}, {1336, 15},
};
BrfKeyframe brf_800C49F0[13] = {
    {0, 0}, {50, 1}, {90, 2}, {130, 3}, {170, 4}, {181, 5},
    {279, 6}, {320, 7}, {600, 8}, {730, 9}, {1018, 10}, {1058, 11},
    {1185, 12},
};
BrfKeyframe brf_800C4A24[8] = {
    {0, 0}, {50, 1}, {410, 2}, {442, 3}, {1180, 4}, {1212, 5},
    {2360, 6}, {2445, 7},
};
BrfKeyframe brf_800C4A44[6] = {
    {0, 0}, {50, 1}, {294, 2}, {310, 3}, {860, 4}, {2223, 5},
};
BrfKeyframe brf_800C4A5C[13] = {
    {0, 0}, {50, 1}, {110, 2}, {115, 3}, {147, 4}, {164, 5},
    {179, 6}, {191, 7}, {508, 8}, {540, 9}, {860, 10}, {876, 11},
    {1149, 12},
};
BrfKeyframe brf_800C4A90[4] = {
    {0, 0}, {50, 1}, {1090, 2}, {1973, 3},
};
BrfKeyframe brf_800C4AA0[13] = {
    {0, 0}, {50, 1}, {201, 2}, {236, 3}, {1017, 4}, {1628, 5},
    {2026, 6}, {2282, 7}, {2553, 8}, {2568, 9}, {2684, 10}, {2699, 11},
    {2959, 12},
};
BrfKeyframe brf_800C4AD4[18] = {
    {0, 0}, {50, 1}, {175, 2}, {195, 3}, {215, 4}, {240, 5},
    {295, 6}, {327, 7}, {335, 8}, {680, 9}, {696, 10}, {986, 11},
    {1018, 12}, {1320, 13}, {1780, 14}, {1796, 15}, {2060, 16}, {2321, 17},
};
BrfKeyframe brf_800C4B1C[3] = {
    {0, 0}, {50, 1}, {860, 2},
};
BrfKeyframe brf_800C4B28[20] = {
    {0, 0}, {50, 1}, {643, 2}, {658, 3}, {696, 4}, {717, 5},
    {733, 6}, {778, 7}, {788, 8}, {804, 9}, {1927, 10}, {1942, 11},
    {1958, 12}, {2228, 13}, {2244, 14}, {2260, 15}, {2545, 16}, {2575, 17},
    {2591, 18}, {2812, 19},
};
BrfKeyframe brf_800C4B78[10] = {
    {0, 0}, {50, 1}, {215, 2}, {231, 3}, {1160, 4}, {1365, 5},
    {1381, 6}, {1865, 7}, {1881, 8}, {2266, 9},
};
BrfKeyframe brf_800C4BA0[6] = {
    {0, 0}, {50, 1}, {590, 2}, {1465, 3}, {1701, 4}, {1905, 5},
};
BrfKeyframe brf_800C4BB8[21] = {
    {0, 0}, {50, 1}, {235, 2}, {300, 3}, {337, 4}, {1577, 5},
    {1627, 6}, {1951, 7}, {1963, 8}, {1983, 9}, {2005, 10}, {2015, 11},
    {2041, 12}, {2050, 13}, {2066, 14}, {2137, 15}, {2153, 16}, {2359, 17},
    {2624, 18}, {2640, 19}, {3082, 20},
};
BrfKeyframe brf_800C4C0C[25] = {
    {0, 0}, {50, 1}, {280, 2}, {297, 3}, {314, 4}, {430, 5},
    {910, 6}, {1005, 7}, {1071, 8}, {1300, 9}, {1366, 10}, {1382, 11},
    {1390, 12}, {1453, 13}, {1469, 14}, {1916, 15}, {1946, 16}, {2007, 17},
    {2037, 18}, {2163, 19}, {2220, 20}, {2275, 21}, {3333, 22}, {3438, 23},
    {4763, 24},
};
BrfKeyframe brf_800C4C70[13] = {
    {0, 0}, {50, 1}, {286, 2}, {302, 3}, {318, 4}, {1143, 5},
    {2205, 6}, {2284, 7}, {2755, 8}, {2915, 9}, {2985, 10}, {3025, 11},
    {3318, 12},
};
BrfKeyframe brf_800C4CA4[3] = {
    {0, 0}, {50, 1}, {515, 2},
};

BrfKeyframe *brf_timelines[19] = {
    brf_800C492C,
    brf_800C495C,
    brf_800C4968,
    brf_800C49C4,
    brf_800C49F0,
    brf_800C4A24,
    brf_800C4A44,
    brf_800C4A5C,
    brf_800C4A90,
    brf_800C4AA0,
    brf_800C4AD4,
    brf_800C4B1C,
    brf_800C4B28,
    brf_800C4B78,
    brf_800C4BA0,
    brf_800C4BB8,
    brf_800C4C0C,
    brf_800C4C70,
    brf_800C4CA4,
};

/* profile text lines {length, text} (brf_800DECF8) */
BrfText brf_800C4CFC[40] = {
    {8, brf_dword_800E173C},
    {9, brf_dword_800E1730},
    {24, brf_dword_800E1714},
    {11, brf_dword_800E1708},
    {7, brf_dword_800E1700},
    {22, brf_dword_800E16E8},
    {14, brf_dword_800E16D8},
    {7, brf_dword_800E16D0},
    {22, brf_dword_800E16B8},
    {24, brf_dword_800E169C},
    {26, brf_dword_800E1680},
    {24, brf_dword_800E1664},
    {23, brf_dword_800E164C},
    {26, brf_dword_800E1630},
    {26, brf_dword_800E1614},
    {27, brf_dword_800E15F8},
    {17, brf_dword_800E15E4},
    {22, brf_dword_800E15CC},
    {17, brf_dword_800E15B8},
    {25, brf_dword_800E159C},
    {27, brf_dword_800E1580},
    {26, brf_dword_800E1564},
    {19, brf_dword_800E1550},
    {27, brf_dword_800E1534},
    {14, brf_dword_800E1524},
    {23, brf_dword_800E150C},
    {27, brf_dword_800E14F0},
    {14, brf_dword_800E14E0},
    {25, brf_dword_800E14C4},
    {27, brf_dword_800E14A8},
    {18, brf_dword_800E1494},
    {17, brf_dword_800E1480},
    {16, brf_dword_800E146C},
    {26, brf_dword_800E1450},
    {20, brf_dword_800E1438},
    {19, brf_dword_800E1424},
    {23, brf_dword_800E140C},
    {20, brf_dword_800E13F4},
    {24, brf_dword_800E13D8},
    {27, brf_dword_800E13BC},
};
BrfText brf_800C4E3C[16] = {
    {5, brf_dword_800E1878},
    {11, brf_dword_800E186C},
    {23, brf_dword_800E1854},
    {11, brf_dword_800E1708},
    {7, brf_dword_800E184C},
    {16, brf_dword_800E1838},
    {14, brf_dword_800E1828},
    {24, brf_dword_800E180C},
    {17, brf_dword_800E17F8},
    {22, brf_dword_800E17E0},
    {24, brf_dword_800E17C4},
    {21, brf_dword_800E17AC},
    {16, brf_dword_800E1798},
    {26, brf_dword_800E177C},
    {22, brf_dword_800E1764},
    {26, brf_dword_800E1748},
};
BrfText brf_800C4EBC[3] = {
    {12, brf_dword_800E1898},
    {5, brf_dword_800E1890},
    {12, brf_dword_800E1880},
};
BrfText brf_800C4ED4[1] = {
    {8, brf_dword_800E18A8},
};
BrfText brf_800C4EDC[8] = {
    {6, brf_dword_800E18FC},
    {6, brf_dword_800E18F4},
    {11, brf_dword_800E18E8},
    {5, brf_dword_800E18E0},
    {7, brf_dword_800E18D8},
    {12, brf_dword_800E18C8},
    {8, brf_dword_800E18BC},
    {6, brf_dword_800E18B4},
};
BrfText brf_800C4F1C[35] = {
    {12, brf_dword_800E1BE0},
    {23, brf_dword_800E1BC8},
    {13, brf_dword_800E1BB8},
    {9, brf_dword_800E1BAC},
    {8, brf_dword_800E1BA0},
    {25, brf_dword_800E1B84},
    {14, brf_dword_800E1B74},
    {7, brf_dword_800E16D0},
    {21, brf_dword_800E1B5C},
    {22, brf_dword_800E1B44},
    {17, brf_dword_800E1B30},
    {19, brf_dword_800E1B1C},
    {21, brf_dword_800E1B04},
    {26, brf_dword_800E1AE8},
    {26, brf_dword_800E1ACC},
    {25, brf_dword_800E1AB0},
    {19, brf_dword_800E1A9C},
    {24, brf_dword_800E1A80},
    {25, brf_dword_800E1A64},
    {27, brf_dword_800E1A48},
    {15, brf_dword_800E1A38},
    {23, brf_dword_800E1A20},
    {20, brf_dword_800E1A08},
    {20, brf_dword_800E19F0},
    {14, brf_dword_800E19E0},
    {25, brf_dword_800E19C4},
    {20, brf_dword_800E19AC},
    {23, brf_dword_800E1994},
    {16, brf_dword_800E1980},
    {17, brf_dword_800E196C},
    {21, brf_dword_800E1954},
    {25, brf_dword_800E1938},
    {19, brf_dword_800E1924},
    {18, brf_dword_800E1910},
    {9, brf_dword_800E1904},
};

/* lip-sync mouth texture ids per mouth state (brf_800CAD24) */
u_short brf_mouth_tex_ids[12][4] = {
    {0x11FE, 0xD74D, 0x1C22, 0x11FE},
    {0xA6B1, 0x73F3, 0xB8C7, 0xA6B1},
    {0xA5C0, 0x60BB, 0xB1CE, 0xA5C0},
    {0x5E03, 0x767D, 0xC790, 0x5E03},
    {0x049D, 0x43B2, 0x94C5, 0x049D},
    {0xACDB, 0xC0E3, 0x11F7, 0xACDB},
    {0x8D8F, 0x632A, 0xA7FE, 0x8D8F},
    {0x7927, 0x2287, 0x675B, 0x7927},
    {0xACEE, 0xD0F4, 0x2208, 0xACEE},
    {0xF760, 0x6348, 0xB45B, 0xF760},
    {0x8927, 0x2307, 0x67DB, 0x8927},
    {0x016F, 0xD398, 0x24AC, 0x016F},
};

u_short *brf_mouth_textures[12] = {
    brf_mouth_tex_ids[0], brf_mouth_tex_ids[1], brf_mouth_tex_ids[2], brf_mouth_tex_ids[3],
    brf_mouth_tex_ids[4], brf_mouth_tex_ids[5], brf_mouth_tex_ids[6], brf_mouth_tex_ids[7],
    brf_mouth_tex_ids[8], brf_mouth_tex_ids[9], brf_mouth_tex_ids[10], brf_mouth_tex_ids[11],
};

/* blink texture ids (brf_800CBA84) */
u_short brf_blink_tex_ids[3][4] = {
    {0xACEC, 0x1208, 0xC0F4, 0x0000},
    {0x19A3, 0x8AD5, 0x4601, 0x0000},
    {0x19A3, 0x445F, 0xFF8A, 0x0000},
};

u_short *brf_blink_textures[3] = {brf_blink_tex_ids[0], brf_blink_tex_ids[1], brf_blink_tex_ids[2]};

/* texture ids for brf_800CBC04 / brf_800CBCB0 */
u_short brf_800C50E8[6] = {0x445F, 0x19A3, 0x19A3, 0xC43B, 0x4601, 0x0000};
u_short brf_800C50F4[6] = {0x8AD5, 0x19A3, 0x19A3, 0x445F, 0xFF8A, 0x0000};

/* 2D offset paths (used by brf_800DA700) */
DVECTOR brf_800C5100[48] = {
    {79, -4}, {75, -3}, {75, -3}, {75, -4}, {74, -4}, {72, -4},
    {63, -5}, {51, -9}, {40, -12}, {38, -13}, {34, -16}, {32, -18},
    {31, -21}, {30, -22}, {30, -25}, {30, -26}, {30, -27}, {30, -27},
    {31, -30}, {32, -30}, {34, -32}, {39, -34}, {42, -35}, {46, -36},
    {55, -40}, {59, -43}, {63, -47}, {64, -51}, {65, -53}, {66, -55},
    {66, -57}, {66, -58}, {65, -60}, {65, -60}, {65, -60}, {64, -60},
    {63, -60}, {63, -61}, {63, -61}, {63, -61}, {63, -61}, {63, -61},
    {63, -61}, {63, -61}, {63, -61}, {63, -61}, {63, -61}, {63, -61},
};
DVECTOR brf_800C51C0[12] = {
    {-10, 23}, {-10, 23}, {-10, 23}, {-15, 24}, {-23, 24}, {-35, 25},
    {-38, 25}, {-38, 25}, {-40, 25}, {-42, 25}, {-45, 24}, {-46, 24},
};
DVECTOR brf_800C51F0[16] = {
    {-47, 24}, {-48, 24}, {-50, 21}, {-54, 18}, {-57, 9}, {-58, 6},
    {-55, 2}, {-53, -3}, {-48, -12}, {-45, -17}, {-32, -28}, {-26, -35},
    {-22, -38}, {-20, -40}, {-20, -40}, {-19, -40},
};
