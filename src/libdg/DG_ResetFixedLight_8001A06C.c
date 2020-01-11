#include "linker.h"
#include <sys/types.h>
#include <libgte.h>

typedef struct
{
    short int field_0_x;
    short int field_2_y;
    short int field_4_z;
    short int field_6_w; // padding?
    short int field_8_brightness;
    short int field_A_radius;
    CVECTOR field_C_colour;
} Light;
typedef struct
{
    int field_0_lightCount;
    Light *field_4_pLights;
} DG_FixedLight;

static DG_FixedLight SECTION(".bss_800B1E08") gFixedLights_800B1E08[8];

extern MATRIX DG_ColorMatrix_8009D3A4;

void DG_SetMainLightCol_8001A048(int r, int g, int b)
{
    DG_ColorMatrix_8009D3A4.m[0][0] = r * 16;
    DG_ColorMatrix_8009D3A4.m[1][0] = g * 16;
    DG_ColorMatrix_8009D3A4.m[2][0] = b * 16;
}

DG_FixedLight *DG_ResetFixedLight_8001A06C(void)
{
    DG_FixedLight *pLightIter = &gFixedLights_800B1E08[0];
    int i = COUNTOF(gFixedLights_800B1E08);
    while (i > 0)
    {
        i--;
        pLightIter->field_0_lightCount = 0;
        pLightIter->field_4_pLights = 0;
        pLightIter++;
    }
    return pLightIter;
}
