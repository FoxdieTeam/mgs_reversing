#include "linker.h"
#include "libdg.h"
#include "psyq.h"

static DG_FixedLight SECTION(".bss_800B1E08") gFixedLights_800B1E08[8];

extern MATRIX DG_LightMatrix_8009D384;
extern MATRIX DG_ColorMatrix_8009D3A4;

#pragma INCLUDE_ASM("asm/libdg/DG_InitLightSystem_80019F40.s") // 64 bytes
#pragma INCLUDE_ASM("asm/libdg/DG_SetAmbient_80019F80.s")      // 120 bytes

void DG_SetMainLightDir_80019FF8(int x, int y, int z)
{
    VECTOR in;
    VECTOR out;

    in.vx = x;
    in.vy = y;
    in.vz = z;

    VectorNormal_80092838(&in, &out);
    DG_LightMatrix_8009D384.m[0][0] = out.vx;
    DG_LightMatrix_8009D384.m[0][1] = out.vy;
    DG_LightMatrix_8009D384.m[0][2] = out.vz;
}

void DG_SetMainLightCol_8001A048(int r, int g, int b)
{
    DG_ColorMatrix_8009D3A4.m[0][0] = r * 16;
    DG_ColorMatrix_8009D3A4.m[1][0] = g * 16;
    DG_ColorMatrix_8009D3A4.m[2][0] = b * 16;
}

DG_FixedLight *DG_ResetFixedLight_8001A06C(void)
{
    DG_FixedLight *pLightIter = &gFixedLights_800B1E08[0];
    int            i = COUNTOF(gFixedLights_800B1E08);
    while (i > 0)
    {
        i--;
        pLightIter->field_0_lightCount = 0;
        pLightIter->field_4_pLights = 0;
        pLightIter++;
    }
    return pLightIter;
}

void DG_SetFixedLight_8001A094(Light *pLight, int light_count)
{
    DG_FixedLight *pLightIter;
    Light        **current_light;
    int            i;

    pLightIter = &gFixedLights_800B1E08[0];
    i = 7;
    current_light = &gFixedLights_800B1E08[0].field_4_pLights;

    for (; i >= 1; i--, current_light += 2, pLightIter++)
    {
        if (current_light[0] == pLight)
        {
            return;
        }

        if (pLightIter->field_0_lightCount == 0)
        {
            pLightIter->field_0_lightCount = light_count;
            current_light[0] = pLight;
            return;
        }
    }
}

#pragma INCLUDE_ASM("asm/libdg/DG_ClearTmpLight_8001A0E4.s") // 48 bytes
#pragma INCLUDE_ASM("asm/libdg/DG_SetTmpLight_8001A114.s")   // 148 bytes

void DG_GetLightVector_8001A1A8(VECTOR *in_vec, int divisor, SVECTOR *out_vec)
{
    int    vec_length;
    int    val;
    int    multiplier;
    VECTOR vec_squared;

    Square0_80093340(in_vec, &vec_squared);
    vec_length = SquareRoot0_80092708(vec_squared.vx + vec_squared.vy + vec_squared.vz);
    if (vec_length == 0)
    {
        vec_length = 1;
    }
    multiplier = divisor * 2 - vec_length;
    if (multiplier < 0)
    {
        multiplier = 0;
    }

    val = in_vec->vx * 0xc00;
    val = (val / vec_length) * multiplier;
    out_vec->vx = val / divisor;

    val = in_vec->vy * 0xc00;
    val = (val / vec_length) * multiplier;
    out_vec->vy = val / divisor;

    val = in_vec->vz * 0xc00;
    val = (val / vec_length) * multiplier;
    out_vec->vz = val / divisor;
}

#pragma INCLUDE_ASM("asm/libdg/DG_GetLightMatrix_8001A3C4.s") // 524 bytes

void sub_8001A5D0(int param_1, int param_2)
{
    *(int *)(param_1 + 0x34) = param_2;
    return;
}

#pragma INCLUDE_ASM("asm/libdg/DG_GetLightMatrix2_8001A5D8.s") // 152 bytes
