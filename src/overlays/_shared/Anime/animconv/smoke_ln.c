#include "common.h"
#include "libdg/libdg.h"
#include "Anime/animconv/anime.h"
#include "strcode.h"

const char d16e_dword_800D291C[] = {0x0, 0x15, 0x1, 0x0};
const char d16e_dword_800D2920[] = {0x5, 0x1, 0xfe, 0xc};
const char d16e_dword_800D2924[] = {0x0, '\n', '\n', 0x0};
const char d16e_dword_800D2928[] = {0xc8, 0x0, 0xc8, 0x1};
const char d16e_dword_800D292C[] = {0xff, 0x8, 0xe7, 0xe7};
const char d16e_dword_800D2930[] = {0xe7, 0x2, 0x0, 0x1};
const char d16e_dword_800D2934[] = {0xd, 0xf};

ANIMATION d16e_dword_800C3520 = { PCX_SMOKE, 8, 4, 30, 1, 1000, 3, 4000, 4000, 255, 0, (char *)d16e_dword_800D291C };

const char d16e_dword_800D2938[] = {0x0, 0x15, 0x1, 0x0};
const char d16e_dword_800D293C[] = {0x5, 0x1, 0xfe, 0xc};
const char d16e_dword_800D2940[] = {0x0, 0x7, '\n', 0x0};
const char d16e_dword_800D2944[] = {0xc8, 0x0, 0xc8, 0x1};
const char d16e_dword_800D2948[] = {0xff, 0x8, 0xfc, 0xfc};
const char d16e_dword_800D294C[] = {0xfc, 0x2, 0x0, 0x1};
const char d16e_dword_800D2950[] = {0xd, 0xf};

ANIMATION d16e_dword_800C353C = { PCX_SMOKE, 8, 4, 30, 1, 1000, 3, 3000, 3000, 32, 0, (char *)d16e_dword_800D2938 };

const char d16e_dword_800D2954[] = {0x0, ':', 0x1, 0x0};
const char d16e_dword_800D2958[] = {0x5, 0x1, 0xfe, 0xc};
const char d16e_dword_800D295C[] = {0x0, 0x7, 0x4, 0x0};
const char d16e_dword_800D2960[] = {0x0, 0x0, 0x96, 0x0};
const char d16e_dword_800D2964[] = {0x0, '\n', 0x1, ','};
const char d16e_dword_800D2968[] = {0x1, ',', 0x2, 0x0};
const char d16e_dword_800D296C[] = {0x1, 0x4, 0x0, 0x0};
const char d16e_dword_800D2970[] = {0x0, 0x96, 0x0, 0x0};
const char d16e_dword_800D2974[] = {'\n', 0x1, ',', 0x1};
const char d16e_dword_800D2978[] = {',', 0x2, 0x0, 0x1};
const char d16e_dword_800D297C[] = {0x4, 0x0, 0x0, 0x0};
const char d16e_dword_800D2980[] = {0x96, 0x0, 0x0, '\n'};
const char d16e_dword_800D2984[] = {0x1, ',', 0x1, ','};
const char d16e_dword_800D2988[] = {0x1, 0xff, 0x8, 0xf0};
const char d16e_dword_800D298C[] = {0xf0, 0xf0, 0x2, 0x0};
const char d16e_dword_800D2990[] = {0x1, 0xd, 0xf};

ANIMATION d16e_dword_800C3558 = { PCX_SMOKE, 8, 4, 30, 1, 1000, 2, 1500, 1500, 128, 0, (char *)d16e_dword_800D2954 };

const char d16e_dword_800D2994[] = {0x0, 0xa7, 0x4, 0x0};
const char d16e_dword_800D2998[] = {0xb, 0x0, '1', 0x0};
const char d16e_dword_800D299C[] = {'\\', 0x0, 0x87, 0x1};
const char d16e_dword_800D29A0[] = {0xfe, 0xc, 0x0, 0x7};
const char d16e_dword_800D29A4[] = {0x2, 0x0, 0x1, '\n'};
const char d16e_dword_800D29A8[] = {0x0, '2', 0x0, '2'};
const char d16e_dword_800D29AC[] = {0x1, 0xff, 0x2, 0x0};
const char d16e_dword_800D29B0[] = {0x1, 0xd, 0xc, 0x0};
const char d16e_dword_800D29B4[] = {0x7, 0x1, 0xff, 0x2};
const char d16e_dword_800D29B8[] = {0x0, 0x1, 0x1, 0xff};
const char d16e_dword_800D29BC[] = {0x8, 0xff, 0xff, 0xff};
const char d16e_dword_800D29C0[] = {0x2, 0x0, 0x1, 0xd};
const char d16e_dword_800D29C4[] = {0xf, '\n', 0x1, 0xf4};
const char d16e_dword_800D29C8[] = {0x1, 0xf4, 0x1, 0xfe};
const char d16e_dword_800D29CC[] = {0xc, 0x0, 0x7, 0x2};
const char d16e_dword_800D29D0[] = {0x0, 0x1, '\n', 0x0};
const char d16e_dword_800D29D4[] = {'d', 0x0, 'd', 0x1};
const char d16e_dword_800D29D8[] = {0xff, 0x2, 0x0, 0x1};
const char d16e_dword_800D29DC[] = {0xd, 0xc, 0x0, 0x7};
const char d16e_dword_800D29E0[] = {0x1, 0xff, 0x2, 0x0};
const char d16e_dword_800D29E4[] = {0x1, 0x1, 0xff, 0x8};
const char d16e_dword_800D29E8[] = {0xff, 0xff, 0xff, 0x2};
const char d16e_dword_800D29EC[] = {0x0, 0x1, 0xd, 0xf};
const char d16e_dword_800D29F0[] = {'\n', 0x3, 0xe8, 0x3};
const char d16e_dword_800D29F4[] = {0xe8, 0x1, 0xfe, 0xc};
const char d16e_dword_800D29F8[] = {0x0, 0x7, 0x2, 0x0};
const char d16e_dword_800D29FC[] = {0x1, '\n', 0x0, 0xc8};
const char d16e_dword_800D2A00[] = {0x0, 'd', 0x1, 0xff};
const char d16e_dword_800D2A04[] = {0x2, 0x0, 0x1, 0xd};
const char d16e_dword_800D2A08[] = {0xc, 0x0, 0x7, 0x1};
const char d16e_dword_800D2A0C[] = {0xff, 0x2, 0x0, 0x1};
const char d16e_dword_800D2A10[] = {0x1, 0xff, 0x8, 0xff};
const char d16e_dword_800D2A14[] = {0xff, 0xff, 0x2, 0x0};
const char d16e_dword_800D2A18[] = {0x1, 0xd, 0xf, '\n'};
const char d16e_dword_800D2A1C[] = {0x7, 0xd0, 0x7, 0xd0};
const char d16e_dword_800D2A20[] = {0x1, 0xfe, 0xc, 0x0};
const char d16e_dword_800D2A24[] = {0x7, 0x2, 0x0, 0x1};
const char d16e_dword_800D2A28[] = {'\n', 0x1, 0x90, 0x1};
const char d16e_dword_800D2A2C[] = {0x90, 0x1, 0xff, 0x2};
const char d16e_dword_800D2A30[] = {0x0, 0x1, 0xd, 0xc};
const char d16e_dword_800D2A34[] = {0x0, 0x7, 0x1, 0xff};
const char d16e_dword_800D2A38[] = {0x2, 0x0, 0x1, 0x1};
const char d16e_dword_800D2A3C[] = {0xff, 0x8, 0xff, 0xff};
const char d16e_dword_800D2A40[] = {0xff, 0x2, 0x0, 0x1};
const char d16e_dword_800D2A44[] = {0xd, 0xf};

ANIMATION d16e_dword_800C3574 = { PCX_SMOKE, 8, 4, 30, 1, 1000, 2, 500, 500, 8, 0, (char *)d16e_dword_800D2994 };
ANIMATION d16e_dword_800C3590 = { PCX_SMOKE, 8, 4, 30, 1, 1000, 2, 500, 500, 16, 0, (char *)d16e_dword_800D2994 };

const char d16e_dword_800D2A48[] = {0x0, ':', 0x1, 0x0};
const char d16e_dword_800D2A4C[] = {0x5, 0x1, 0xfe, 0xc};
const char d16e_dword_800D2A50[] = {0x0, 0x7, 0x4, 0x0};
const char d16e_dword_800D2A54[] = {0x0, 0x0, 0x96, 0x0};
const char d16e_dword_800D2A58[] = {0x0, '\n', 0x1, ','};
const char d16e_dword_800D2A5C[] = {0x1, ',', 0x2, 0x0};
const char d16e_dword_800D2A60[] = {0x1, 0x4, 0x0, 0x0};
const char d16e_dword_800D2A64[] = {0x0, 0x96, 0x0, 0x0};
const char d16e_dword_800D2A68[] = {'\n', 0x1, ',', 0x1};
const char d16e_dword_800D2A6C[] = {',', 0x2, 0x0, 0x1};
const char d16e_dword_800D2A70[] = {0x4, 0x0, 0x0, 0x0};
const char d16e_dword_800D2A74[] = {0x96, 0x0, 0x0, '\n'};
const char d16e_dword_800D2A78[] = {0x1, ',', 0x1, ','};
const char d16e_dword_800D2A7C[] = {0x1, 0xff, 0x8, 0xfc};
const char d16e_dword_800D2A80[] = {0xfc, 0xfc, 0x2, 0x0};
const char d16e_dword_800D2A84[] = {0x1, 0xd, 0xf};

ANIMATION d16e_dword_800C35AC = { PCX_SMOKE, 8, 4, 30, 1, 3000, 2, 1000, 1000, 32, 0, (char *)d16e_dword_800D2A48 };
ANIMATION d16e_dword_800C35C8 = { PCX_SMOKE, 8, 4, 30, 1, 3000, 2, 1000, 1000, 32, 0, (char *)d16e_dword_800D2A48 };

const char d16e_dword_800D2A88[] = {0x0, 0xab, 0x4, 0x0};
const char d16e_dword_800D2A8C[] = {0xb, 0x0, '2', 0x0};
const char d16e_dword_800D2A90[] = {'^', 0x0, 0x8a, 0x1};
const char d16e_dword_800D2A94[] = {0xfe, 0xc, 0x0, 0xf};
const char d16e_dword_800D2A98[] = {'\n', 0x0, '2', 0x0};
const char d16e_dword_800D2A9C[] = {'2', 0x1, 0xff, 0x2};
const char d16e_dword_800D2AA0[] = {0x0, 0x1, 0xd, 0xc};
const char d16e_dword_800D2AA4[] = {0x0, 0x1e, 0x1, 0xff};
const char d16e_dword_800D2AA8[] = {0x2, 0x0, 0x1, 0xd};
const char d16e_dword_800D2AAC[] = {0xc, 0x0, 0xf, 0x1};
const char d16e_dword_800D2AB0[] = {0xff, 0x8, 0xf0, 0xf0};
const char d16e_dword_800D2AB4[] = {0xf0, 0x2, 0x0, 0x1};
const char d16e_dword_800D2AB8[] = {0xd, 0xf, '\n', 0x0};
const char d16e_dword_800D2ABC[] = {0xfa, 0x0, 0xfa, 0x1};
const char d16e_dword_800D2AC0[] = {0xfe, 0xc, 0x0, 0xf};
const char d16e_dword_800D2AC4[] = {'\n', 0x0, 'F', 0x0};
const char d16e_dword_800D2AC8[] = {'F', 0x1, 0xff, 0x2};
const char d16e_dword_800D2ACC[] = {0x0, 0x1, 0xd, 0xc};
const char d16e_dword_800D2AD0[] = {0x0, 0x1e, 0x1, 0xff};
const char d16e_dword_800D2AD4[] = {0x2, 0x0, 0x1, 0xd};
const char d16e_dword_800D2AD8[] = {0xc, 0x0, 0xf, 0x1};
const char d16e_dword_800D2ADC[] = {0xff, 0x8, 0xf0, 0xf0};
const char d16e_dword_800D2AE0[] = {0xf0, 0x2, 0x0, 0x1};
const char d16e_dword_800D2AE4[] = {0xd, 0xf, '\n', 0x1};
const char d16e_dword_800D2AE8[] = {0xf4, 0x1, 0xf4, 0x1};
const char d16e_dword_800D2AEC[] = {0xfe, 0xc, 0x0, 0xf};
const char d16e_dword_800D2AF0[] = {'\n', 0x0, 'Z', 0x0};
const char d16e_dword_800D2AF4[] = {'Z', 0x1, 0xff, 0x2};
const char d16e_dword_800D2AF8[] = {0x0, 0x1, 0xd, 0xc};
const char d16e_dword_800D2AFC[] = {0x0, 0x1e, 0x1, 0xff};
const char d16e_dword_800D2B00[] = {0x2, 0x0, 0x1, 0xd};
const char d16e_dword_800D2B04[] = {0xc, 0x0, 0xf, 0x1};
const char d16e_dword_800D2B08[] = {0xff, 0x8, 0xf0, 0xf0};
const char d16e_dword_800D2B0C[] = {0xf0, 0x2, 0x0, 0x1};
const char d16e_dword_800D2B10[] = {0xd, 0xf, '\n', 0x2};
const char d16e_dword_800D2B14[] = {0xee, 0x2, 0xee, 0x1};
const char d16e_dword_800D2B18[] = {0xfe, 0xc, 0x0, 0xf};
const char d16e_dword_800D2B1C[] = {'\n', 0x0, 'n', 0x0};
const char d16e_dword_800D2B20[] = {'n', 0x1, 0xff, 0x2};
const char d16e_dword_800D2B24[] = {0x0, 0x1, 0xd, 0xc};
const char d16e_dword_800D2B28[] = {0x0, 0x1e, 0x1, 0xff};
const char d16e_dword_800D2B2C[] = {0x2, 0x0, 0x1, 0xd};
const char d16e_dword_800D2B30[] = {0xc, 0x0, 0xf, 0x1};
const char d16e_dword_800D2B34[] = {0xff, 0x8, 0xf0, 0xf0};
const char d16e_dword_800D2B38[] = {0xf0, 0x2, 0x0, 0x1};
const char d16e_dword_800D2B3C[] = {0xd, 0xf};

ANIMATION d16e_dword_800C35E4 = { PCX_SMOKE, 8, 4, 30, 1, 1000, 3, 500, 500, 255, 0, (char *)d16e_dword_800D2A88 };

const char d16e_dword_800D2B40[] = {0x0, 0xab, 0x4, 0x0};
const char d16e_dword_800D2B44[] = {0xb, 0x0, '2', 0x0};
const char d16e_dword_800D2B48[] = {'^', 0x0, 0x8a, 0x1};
const char d16e_dword_800D2B4C[] = {0xfe, 0xc, 0x0, 0xf};
const char d16e_dword_800D2B50[] = {'\n', 0x0, '2', 0x0};
const char d16e_dword_800D2B54[] = {'2', 0x1, 0xff, 0x2};
const char d16e_dword_800D2B58[] = {0x0, 0x1, 0xd, 0xc};
const char d16e_dword_800D2B5C[] = {0x0, 0x1e, 0x1, 0xff};
const char d16e_dword_800D2B60[] = {0x2, 0x0, 0x1, 0xd};
const char d16e_dword_800D2B64[] = {0xc, 0x0, 0xf, 0x1};
const char d16e_dword_800D2B68[] = {0xff, 0x8, 0xff, 0xff};
const char d16e_dword_800D2B6C[] = {0xff, 0x2, 0x0, 0x1};
const char d16e_dword_800D2B70[] = {0xd, 0xf, '\n', 0x0};
const char d16e_dword_800D2B74[] = {0xfa, 0x0, 0xfa, 0x1};
const char d16e_dword_800D2B78[] = {0xfe, 0xc, 0x0, 0xf};
const char d16e_dword_800D2B7C[] = {'\n', 0x0, 'F', 0x0};
const char d16e_dword_800D2B80[] = {'F', 0x1, 0xff, 0x2};
const char d16e_dword_800D2B84[] = {0x0, 0x1, 0xd, 0xc};
const char d16e_dword_800D2B88[] = {0x0, 0x1e, 0x1, 0xff};
const char d16e_dword_800D2B8C[] = {0x2, 0x0, 0x1, 0xd};
const char d16e_dword_800D2B90[] = {0xc, 0x0, 0xf, 0x1};
const char d16e_dword_800D2B94[] = {0xff, 0x8, 0xff, 0xff};
const char d16e_dword_800D2B98[] = {0xff, 0x2, 0x0, 0x1};
const char d16e_dword_800D2B9C[] = {0xd, 0xf, '\n', 0x1};
const char d16e_dword_800D2BA0[] = {0xf4, 0x1, 0xf4, 0x1};
const char d16e_dword_800D2BA4[] = {0xfe, 0xc, 0x0, 0xf};
const char d16e_dword_800D2BA8[] = {'\n', 0x0, 'Z', 0x0};
const char d16e_dword_800D2BAC[] = {'Z', 0x1, 0xff, 0x2};
const char d16e_dword_800D2BB0[] = {0x0, 0x1, 0xd, 0xc};
const char d16e_dword_800D2BB4[] = {0x0, 0x1e, 0x1, 0xff};
const char d16e_dword_800D2BB8[] = {0x2, 0x0, 0x1, 0xd};
const char d16e_dword_800D2BBC[] = {0xc, 0x0, 0xf, 0x1};
const char d16e_dword_800D2BC0[] = {0xff, 0x8, 0xff, 0xff};
const char d16e_dword_800D2BC4[] = {0xff, 0x2, 0x0, 0x1};
const char d16e_dword_800D2BC8[] = {0xd, 0xf, '\n', 0x2};
const char d16e_dword_800D2BCC[] = {0xee, 0x2, 0xee, 0x1};
const char d16e_dword_800D2BD0[] = {0xfe, 0xc, 0x0, 0xf};
const char d16e_dword_800D2BD4[] = {'\n', 0x0, 'n', 0x0};
const char d16e_dword_800D2BD8[] = {'n', 0x1, 0xff, 0x2};
const char d16e_dword_800D2BDC[] = {0x0, 0x1, 0xd, 0xc};
const char d16e_dword_800D2BE0[] = {0x0, 0x1e, 0x1, 0xff};
const char d16e_dword_800D2BE4[] = {0x2, 0x0, 0x1, 0xd};
const char d16e_dword_800D2BE8[] = {0xc, 0x0, 0xf, 0x1};
const char d16e_dword_800D2BEC[] = {0xff, 0x8, 0xff, 0xff};
const char d16e_dword_800D2BF0[] = {0xff, 0x2, 0x0, 0x1};
const char d16e_dword_800D2BF4[] = {0xd, 0xf};

ANIMATION d16e_dword_800C3600 = { PCX_SMOKE, 8, 4, 30, 1, 1000, 2, 500, 500, 16, 0, (char *)d16e_dword_800D2B40 };

const char d16e_dword_800D2BF8[] = {0x0, 0xbb, 0x4, 0x0};
const char d16e_dword_800D2BFC[] = {0xb, 0x0, '6', 0x0};
const char d16e_dword_800D2C00[] = {'f', 0x0, 0x96, 0x8};
const char d16e_dword_800D2C04[] = {0xff, 0xff, 0xff, 0x1};
const char d16e_dword_800D2C08[] = {0xfe, 0xc, 0x0, 0xf};
const char d16e_dword_800D2C0C[] = {'\n', 0x0, '2', 0x0};
const char d16e_dword_800D2C10[] = {'2', 0x1, 0xff, 0x2};
const char d16e_dword_800D2C14[] = {0x0, 0x1, 0xd, 0xc};
const char d16e_dword_800D2C18[] = {0x0, 0x1e, 0x1, 0xff};
const char d16e_dword_800D2C1C[] = {0x2, 0x0, 0x1, 0xd};
const char d16e_dword_800D2C20[] = {0xc, 0x0, 0xf, 0x1};
const char d16e_dword_800D2C24[] = {0xff, 0x8, 0xf0, 0xf0};
const char d16e_dword_800D2C28[] = {0xf0, 0x2, 0x0, 0x1};
const char d16e_dword_800D2C2C[] = {0xd, 0xf, 0x8, 0xff};
const char d16e_dword_800D2C30[] = {0xff, 0xff, '\n', 0x0};
const char d16e_dword_800D2C34[] = {0xfa, 0x0, 0xfa, 0x1};
const char d16e_dword_800D2C38[] = {0xfe, 0xc, 0x0, 0xf};
const char d16e_dword_800D2C3C[] = {'\n', 0x0, 'F', 0x0};
const char d16e_dword_800D2C40[] = {'F', 0x1, 0xff, 0x2};
const char d16e_dword_800D2C44[] = {0x0, 0x1, 0xd, 0xc};
const char d16e_dword_800D2C48[] = {0x0, 0x1e, 0x1, 0xff};
const char d16e_dword_800D2C4C[] = {0x2, 0x0, 0x1, 0xd};
const char d16e_dword_800D2C50[] = {0xc, 0x0, 0xf, 0x1};
const char d16e_dword_800D2C54[] = {0xff, 0x8, 0xf0, 0xf0};
const char d16e_dword_800D2C58[] = {0xf0, 0x2, 0x0, 0x1};
const char d16e_dword_800D2C5C[] = {0xd, 0xf, 0x8, 0xff};
const char d16e_dword_800D2C60[] = {0xff, 0xff, '\n', 0x1};
const char d16e_dword_800D2C64[] = {0xf4, 0x1, 0xf4, 0x1};
const char d16e_dword_800D2C68[] = {0xfe, 0xc, 0x0, 0xf};
const char d16e_dword_800D2C6C[] = {'\n', 0x0, 'Z', 0x0};
const char d16e_dword_800D2C70[] = {'Z', 0x1, 0xff, 0x2};
const char d16e_dword_800D2C74[] = {0x0, 0x1, 0xd, 0xc};
const char d16e_dword_800D2C78[] = {0x0, 0x1e, 0x1, 0xff};
const char d16e_dword_800D2C7C[] = {0x2, 0x0, 0x1, 0xd};
const char d16e_dword_800D2C80[] = {0xc, 0x0, 0xf, 0x1};
const char d16e_dword_800D2C84[] = {0xff, 0x8, 0xf0, 0xf0};
const char d16e_dword_800D2C88[] = {0xf0, 0x2, 0x0, 0x1};
const char d16e_dword_800D2C8C[] = {0xd, 0xf, 0x8, 0xff};
const char d16e_dword_800D2C90[] = {0xff, 0xff, '\n', 0x2};
const char d16e_dword_800D2C94[] = {0xee, 0x2, 0xee, 0x1};
const char d16e_dword_800D2C98[] = {0xfe, 0xc, 0x0, 0xf};
const char d16e_dword_800D2C9C[] = {'\n', 0x0, 'n', 0x0};
const char d16e_dword_800D2CA0[] = {'n', 0x1, 0xff, 0x2};
const char d16e_dword_800D2CA4[] = {0x0, 0x1, 0xd, 0xc};
const char d16e_dword_800D2CA8[] = {0x0, 0x1e, 0x1, 0xff};
const char d16e_dword_800D2CAC[] = {0x2, 0x0, 0x1, 0xd};
const char d16e_dword_800D2CB0[] = {0xc, 0x0, 0xf, 0x1};
const char d16e_dword_800D2CB4[] = {0xff, 0x8, 0xf0, 0xf0};
const char d16e_dword_800D2CB8[] = {0xf0, 0x2, 0x0, 0x1};
const char d16e_dword_800D2CBC[] = {0xd, 0xf};

ANIMATION d16e_dword_800C361C = { PCX_SMOKE, 8, 4, 30, 1, 1000, 3, 500, 500, 0, 0, (char *)d16e_dword_800D2BF8 };

const char d16e_dword_800D2CC0[] = {0x0, 0x87, 0x4, 0x0};
const char d16e_dword_800D2CC4[] = {0xb, 0x0, ')', 0x0};
const char d16e_dword_800D2CC8[] = {'L', 0x0, 'o', 0x1};
const char d16e_dword_800D2CCC[] = {0xfe, 0xc, 0x0, 0x7};
const char d16e_dword_800D2CD0[] = {'\n', 0x0, 'd', 0x0};
const char d16e_dword_800D2CD4[] = {'d', 0x1, 0xff, 0x2};
const char d16e_dword_800D2CD8[] = {0x0, 0x1, 0xd, 0xc};
const char d16e_dword_800D2CDC[] = {0x0, 0x3, 0x1, 0xff};
const char d16e_dword_800D2CE0[] = {0x8, 0xc0, 0xc0, 0xc0};
const char d16e_dword_800D2CE4[] = {0x2, 0x0, 0x1, 0xd};
const char d16e_dword_800D2CE8[] = {0xf, '\n', 0x0, 0xfa};
const char d16e_dword_800D2CEC[] = {0x0, 0xfa, 0x1, 0xfe};
const char d16e_dword_800D2CF0[] = {0xc, 0x0, 0x7, '\n'};
const char d16e_dword_800D2CF4[] = {0x0, 0x96, 0x0, 0x96};
const char d16e_dword_800D2CF8[] = {0x1, 0xff, 0x2, 0x0};
const char d16e_dword_800D2CFC[] = {0x1, 0xd, 0xc, 0x0};
const char d16e_dword_800D2D00[] = {0x3, 0x1, 0xff, 0x8};
const char d16e_dword_800D2D04[] = {0xc0, 0xc0, 0xc0, 0x2};
const char d16e_dword_800D2D08[] = {0x0, 0x1, 0xd, 0xf};
const char d16e_dword_800D2D0C[] = {'\n', 0x1, 0xf4, 0x1};
const char d16e_dword_800D2D10[] = {0xf4, 0x1, 0xfe, 0xc};
const char d16e_dword_800D2D14[] = {0x0, 0x7, '\n', 0x0};
const char d16e_dword_800D2D18[] = {0xc8, 0x0, 0xc8, 0x1};
const char d16e_dword_800D2D1C[] = {0xff, 0x2, 0x0, 0x1};
const char d16e_dword_800D2D20[] = {0xd, 0xc, 0x0, 0x3};
const char d16e_dword_800D2D24[] = {0x1, 0xff, 0x8, 0xc0};
const char d16e_dword_800D2D28[] = {0xc0, 0xc0, 0x2, 0x0};
const char d16e_dword_800D2D2C[] = {0x1, 0xd, 0xf, '\n'};
const char d16e_dword_800D2D30[] = {0x2, 0xee, 0x2, 0xee};
const char d16e_dword_800D2D34[] = {0x1, 0xfe, 0xc, 0x0};
const char d16e_dword_800D2D38[] = {0x7, '\n', 0x0, 0xfa};
const char d16e_dword_800D2D3C[] = {0x0, 0xfa, 0x1, 0xff};
const char d16e_dword_800D2D40[] = {0x2, 0x0, 0x1, 0xd};
const char d16e_dword_800D2D44[] = {0xc, 0x0, 0x3, 0x1};
const char d16e_dword_800D2D48[] = {0xff, 0x8, 0xc0, 0xc0};
const char d16e_dword_800D2D4C[] = {0xc0, 0x2, 0x0, 0x1};
const char d16e_dword_800D2D50[] = {0xd, 0xf};

ANIMATION d16e_dword_800C3638 = { PCX_SMOKE, 8, 4, 30, 1, 1000, 3, 500, 500, 255, 0, (char *)d16e_dword_800D2CC0 };

const char d16e_dword_800D2D54[] = {0x0, 0x87, 0x4, 0x0};
const char d16e_dword_800D2D58[] = {0xb, 0x0, ')', 0x0};
const char d16e_dword_800D2D5C[] = {'L', 0x0, 'o', 0x1};
const char d16e_dword_800D2D60[] = {0xfe, 0xc, 0x0, 0x7};
const char d16e_dword_800D2D64[] = {'\n', 0x0, 'd', 0x0};
const char d16e_dword_800D2D68[] = {'d', 0x1, 0xff, 0x2};
const char d16e_dword_800D2D6C[] = {0x0, 0x1, 0xd, 0xc};
const char d16e_dword_800D2D70[] = {0x0, 0x3, 0x1, 0xff};
const char d16e_dword_800D2D74[] = {0x8, 0xfc, 0xfc, 0xfc};
const char d16e_dword_800D2D78[] = {0x2, 0x0, 0x1, 0xd};
const char d16e_dword_800D2D7C[] = {0xf, '\n', 0x0, 0xfa};
const char d16e_dword_800D2D80[] = {0x0, 0xfa, 0x1, 0xfe};
const char d16e_dword_800D2D84[] = {0xc, 0x0, 0x7, '\n'};
const char d16e_dword_800D2D88[] = {0x0, 0x96, 0x0, 0x96};
const char d16e_dword_800D2D8C[] = {0x1, 0xff, 0x2, 0x0};
const char d16e_dword_800D2D90[] = {0x1, 0xd, 0xc, 0x0};
const char d16e_dword_800D2D94[] = {0x3, 0x1, 0xff, 0x8};
const char d16e_dword_800D2D98[] = {0xfc, 0xfc, 0xfc, 0x2};
const char d16e_dword_800D2D9C[] = {0x0, 0x1, 0xd, 0xf};
const char d16e_dword_800D2DA0[] = {'\n', 0x1, 0xf4, 0x1};
const char d16e_dword_800D2DA4[] = {0xf4, 0x1, 0xfe, 0xc};
const char d16e_dword_800D2DA8[] = {0x0, 0x7, '\n', 0x0};
const char d16e_dword_800D2DAC[] = {0xc8, 0x0, 0xc8, 0x1};
const char d16e_dword_800D2DB0[] = {0xff, 0x2, 0x0, 0x1};
const char d16e_dword_800D2DB4[] = {0xd, 0xc, 0x0, 0x3};
const char d16e_dword_800D2DB8[] = {0x1, 0xff, 0x8, 0xfc};
const char d16e_dword_800D2DBC[] = {0xfc, 0xfc, 0x2, 0x0};
const char d16e_dword_800D2DC0[] = {0x1, 0xd, 0xf, '\n'};
const char d16e_dword_800D2DC4[] = {0x2, 0xee, 0x2, 0xee};
const char d16e_dword_800D2DC8[] = {0x1, 0xfe, 0xc, 0x0};
const char d16e_dword_800D2DCC[] = {0x7, '\n', 0x0, 0xfa};
const char d16e_dword_800D2DD0[] = {0x0, 0xfa, 0x1, 0xff};
const char d16e_dword_800D2DD4[] = {0x2, 0x0, 0x1, 0xd};
const char d16e_dword_800D2DD8[] = {0xc, 0x0, 0x3, 0x1};
const char d16e_dword_800D2DDC[] = {0xff, 0x8, 0xfc, 0xfc};
const char d16e_dword_800D2DE0[] = {0xfc, 0x2, 0x0, 0x1};
const char d16e_dword_800D2DE4[] = {0xd, 0xf};

ANIMATION d16e_dword_800C3654 = { PCX_SMOKE, 8, 4, 30, 1, 1000, 2, 500, 500, 16, 0, (char *)d16e_dword_800D2D54 };

const char d16e_dword_800D2DE8[] = {0x0, '*', 0x1, 0x0};
const char d16e_dword_800D2DEC[] = {0x5, 0x1, 0xfe, 0xc};
const char d16e_dword_800D2DF0[] = {0x0, 0x2, 0x2, 0x0};
const char d16e_dword_800D2DF4[] = {0x1, 0xd, '\n', 0x3};
const char d16e_dword_800D2DF8[] = {0xe8, 0x3, 0xe8, 0xc};
const char d16e_dword_800D2DFC[] = {0x0, 0x7, '\n', 0x0};
const char d16e_dword_800D2E00[] = {'d', 0x0, 'd', 0x1};
const char d16e_dword_800D2E04[] = {0xff, 0x2, 0x0, 0x1};
const char d16e_dword_800D2E08[] = {0xd, 0xc, 0x0, 0x3};
const char d16e_dword_800D2E0C[] = {0x1, 0xff, 0x8, 0xc0};
const char d16e_dword_800D2E10[] = {0xc0, 0xc0, 0x2, 0x0};
const char d16e_dword_800D2E14[] = {0x1, 0xd, 0xf};

ANIMATION d16e_dword_800C3670 = { PCX_SMOKE, 8, 4, 30, 1, 1000, 3, 1, 1, 255, 0, (char *)d16e_dword_800D2DE8 };

void AN_Smoke_800CE08C(SVECTOR *pos)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    memset(&pre, 0, sizeof(PRESCRIPT));
    pre.pos = *pos;

    anm = &d16e_dword_800C3520;
    anm->pre_script = &pre;

    NewAnime(NULL, 0, anm);
}

void AN_Smoke_800CE0F8(SVECTOR *pos)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    memset(&pre, 0, sizeof(PRESCRIPT));
    pre.pos = *pos;

    anm = &d16e_dword_800C3558;
    anm->pre_script = &pre;

    NewAnime(NULL, 0, anm);
}

void AN_Smoke_800CE164(SVECTOR *pos, SVECTOR *speed, int index, int script)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    memset(&pre, 0, sizeof(PRESCRIPT));
    pre.pos = *pos;
    pre.speed = *speed;
    pre.scr_num = script;

    anm = NULL;

    switch (index)
    {
    case 0:
        anm = &d16e_dword_800C3574;
        break;

    case 1:
        anm = &d16e_dword_800C3590;
        break;
    }

    anm->pre_script = &pre;

    NewAnime(NULL, 0, anm);
}

void AN_Smoke_800CE240(SVECTOR *pos)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    memset(&pre, 0, sizeof(PRESCRIPT));
    pre.pos = *pos;

    anm = &d16e_dword_800C35AC;
    anm->pre_script = &pre;

    NewAnime(NULL, 0, anm);

    anm = &d16e_dword_800C353C;
    anm->pre_script = &pre;

    NewAnime(NULL, 0, anm);
}

void AN_Smoke_800CE2C4(SVECTOR *pos, SVECTOR *speed, int index, int script, char r, char g, char b)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    memset(&pre, 0, sizeof(PRESCRIPT));
    pre.pos = *pos;
    pre.speed = *speed;
    pre.scr_num = script;

    anm = NULL;

    switch (index)
    {
    case 0:
        anm = &d16e_dword_800C35E4;
        break;

    case 1:
        anm = &d16e_dword_800C3600;
        break;

    case 2:
        anm = &d16e_dword_800C361C;

        anm->field_18_ptr[12] = r;
        anm->field_18_ptr[13] = g;
        anm->field_18_ptr[14] = b;

        anm->field_18_ptr[55] = r;
        anm->field_18_ptr[56] = g;
        anm->field_18_ptr[57] = b;

        anm->field_18_ptr[108] = r;
        anm->field_18_ptr[109] = g;
        anm->field_18_ptr[110] = b;

        anm->field_18_ptr[151] = r;
        anm->field_18_ptr[152] = g;
        anm->field_18_ptr[153] = b;

        r = -((r - 1) / 15);
        g = -((g - 1) / 15);
        b = -((b - 1) / 15);

        anm->field_18_ptr[46] = r;
        anm->field_18_ptr[47] = g;
        anm->field_18_ptr[48] = b;

        anm->field_18_ptr[94] = r;
        anm->field_18_ptr[95] = g;
        anm->field_18_ptr[96] = b;

        anm->field_18_ptr[142] = r;
        anm->field_18_ptr[143] = g;
        anm->field_18_ptr[144] = b;

        anm->field_18_ptr[190] = r;
        anm->field_18_ptr[191] = g;
        anm->field_18_ptr[192] = b;
        break;
    }

    anm->pre_script = &pre;

    NewAnime(NULL, 0, anm);
}

void AN_Smoke_800CE55C(SVECTOR *pos)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    memset(&pre, 0, sizeof(PRESCRIPT));
    pre.pos = *pos;

    anm = &d16e_dword_800C35C8;
    anm->pre_script = &pre;

    NewAnime(NULL, 0, anm);
}

void AN_Smoke_800CE5C8(SVECTOR *pos, SVECTOR *speed, int index, int script)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    memset(&pre, 0, sizeof(PRESCRIPT));
    pre.pos = *pos;
    pre.speed = *speed;
    pre.scr_num = script;

    anm = NULL;

    switch (index)
    {
    case 0:
        anm = &d16e_dword_800C3638;
        break;

    case 1:
        anm = &d16e_dword_800C3654;
        break;
    }

    anm->pre_script = &pre;

    NewAnime(NULL, 0, anm);
}

void AN_Smoke_800CE6A4(SVECTOR *pos)
{
    PRESCRIPT  pre;
    ANIMATION *anm;

    memset(&pre, 0, sizeof(PRESCRIPT));
    pre.pos = *pos;
    pre.speed = DG_ZeroVector;
    pre.scr_num = 0;
    pre.s_anim = 0;

    anm = &d16e_dword_800C3670;
    anm->pre_script = &pre;

    NewAnime(NULL, 0, anm);
}
