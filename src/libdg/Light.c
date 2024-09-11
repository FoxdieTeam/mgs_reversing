#include "linker.h"
#include "libdg.h"
#include "psyq.h"
#include "common.h"
#include "Game/game.h"

/*---------------------------------------------------------------------------*/

/*** data ***/
MATRIX DG_LightMatrix = {
    {{ 0x0000, 0x0000, 0x1000 },
     { 0x0000, 0x0000, 0x0000 },
     { 0x0000, 0x0000, 0x0000 }},
    { 0, 0, 0 }
};

MATRIX DG_ColorMatrix = {
    {{ 0x1000, 0x1000, 0x1000 },
     { 0x1000, 0x1000, 0x1000 },
     { 0x1000, 0x1000, 0x1000 }},
    { 0, 0, 0 }
};

/*** $gp ***/
SVECTOR DG_Ambient = { 0, 0, 0, 0 };

int DG_PacketCode[2] = { 0x3C808080, 0x3E808080 };

/*** bss ***/
extern DG_FixedLight   gFixedLights_800B1E08[8];
extern DG_TmpLightList LightSystems_800B1E48[2];

/*** sbss ***/
extern int    GV_Time;
extern int    GM_GameStatus;

/*---------------------------------------------------------------------------*/

static inline DG_TmpLightList *getTempLight( int idx )
{
    return &LightSystems_800B1E48[ idx ];
}

void DG_InitLightSystem( void )
{
    DG_ResetFixedLight();
    LightSystems_800B1E48[0].n_lights = 0;
    LightSystems_800B1E48[1].n_lights = 0;
    DG_SetAmbient( 0 , 0 , 0 );
}

void DG_SetAmbient( int vx, int vy, int vz )
{
    DG_Ambient.vx = (short)vx;
    DG_Ambient.vy = (short)vy;
    DG_Ambient.vz = (short)vz;
    gte_SetBackColor( vx, vy, vz );

    vx = ( ( 0x100 - vx ) >> 1  ) & 0xFF;
    vy = ( ( 0x100 - vy ) << 7  ) & 0xFF00;
    vz = ( ( 0x100 - vz ) << 15 ) & 0xFF0000;

    DG_PacketCode[0] = 0x3C000000 | vx | vy | vz;
    DG_PacketCode[1] = DG_PacketCode[0] | 0x2000000;
}

void DG_SetMainLightDir( int x, int y, int z )
{
    VECTOR in;
    VECTOR out;

    in.vx = x;
    in.vy = y;
    in.vz = z;

    VectorNormal(&in, &out);
    DG_LightMatrix.m[0][0] = out.vx;
    DG_LightMatrix.m[0][1] = out.vy;
    DG_LightMatrix.m[0][2] = out.vz;
}

void DG_SetMainLightCol( int r, int g, int b )
{
    DG_ColorMatrix.m[0][0] = r * 16;
    DG_ColorMatrix.m[1][0] = g * 16;
    DG_ColorMatrix.m[2][0] = b * 16;
}

void DG_ResetFixedLight( void )
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
}

void DG_SetFixedLight( DG_LIT *light, int light_count )
{
    DG_FixedLight *pLightIter;
    DG_LIT       **current_light;
    int            i;

    pLightIter = &gFixedLights_800B1E08[0];
    i = 7;
    current_light = &gFixedLights_800B1E08[0].field_4_pLights;

    for (; i >= 1; i--, current_light += 2, pLightIter++)
    {
        if (current_light[0] == light)
        {
            return;
        }

        if (pLightIter->field_0_lightCount == 0)
        {
            pLightIter->field_0_lightCount = light_count;
            current_light[0] = light;
            return;
        }
    }
}

void DG_ClearTmpLight( void )
{
    DG_TmpLightList* tmp = getTempLight( GV_Time & 1 );
    tmp->n_lights = 0;
}

int DG_SetTmpLight( SVECTOR *svec, int brightness, int radius )
{
    int n_lights;
    DG_TmpLightList *tmp;
    DG_LIT *light;

    tmp = getTempLight( GV_Time & 1 );
    n_lights = tmp->n_lights;

    if (n_lights >= 8) return -1;

    tmp->n_lights++;
    light = &tmp->lights[n_lights];
    light->pos = *svec;
    light->field_8_brightness = brightness;
    light->field_A_radius = radius;
    *(int*)&light->field_C_colour = 0xFFFFFF;

    return 0;
}

void DG_GetLightVector( VECTOR *in_vec, int divisor, SVECTOR *out_vec )
{
    int    vec_length;
    int    val;
    int    multiplier;
    VECTOR vec_squared;

    Square0(in_vec, &vec_squared);
    vec_length = SquareRoot0(vec_squared.vx + vec_squared.vy + vec_squared.vz);
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

int DG_GetLightMatrix( SVECTOR *vec, MATRIX *mtx )
{
    int lightCount, lightCount2;
    int lightRadius;
    DG_LIT *pLightIter;
    short *pColorOut;
    int lightsAvailable;
    DG_SVECTOR *lightOut;
    DG_FixedLight *pFixedLightsIter;
    VECTOR lightDistance;
    DG_TmpLightList *pTmpLightList;

    lightOut = (DG_SVECTOR *)mtx->m[1];
    pColorOut = &mtx[1].m[0][1];
    pFixedLightsIter = gFixedLights_800B1E08;
    lightsAvailable = 2;

    memcpy(&mtx[0].m, DG_LightMatrix.m, 20);
    memcpy(&mtx[1].m, DG_ColorMatrix.m, 20);

    pTmpLightList = &LightSystems_800B1E48[~GV_Time & 1];
    lightCount2 = pTmpLightList->n_lights;
    pLightIter = pTmpLightList->lights;

    while (1)
    {
        for (lightCount = lightCount2; lightCount > 0; lightCount--, pLightIter++)
        {
            lightRadius = pLightIter->field_A_radius;

            lightDistance.vx = vec->vx - pLightIter->pos.vx;

            if (lightDistance.vx >= -lightRadius && lightDistance.vx <= lightRadius)
            {
                lightDistance.vy = vec->vy - pLightIter->pos.vy;

                if (lightDistance.vy >= -lightRadius && lightDistance.vy <= lightRadius)
                {
                    lightDistance.vz = vec->vz - pLightIter->pos.vz;

                    if (lightDistance.vz >= -lightRadius && lightDistance.vz <= lightRadius)
                    {
                        DG_GetLightVector(&lightDistance, pLightIter->field_8_brightness, (SVECTOR *)lightOut);
                        lightOut++;

                        pColorOut[0] = pLightIter->field_C_colour.r << 4;
                        pColorOut[3] = pLightIter->field_C_colour.g << 4;
                        pColorOut[6] = pLightIter->field_C_colour.b << 4;
                        pColorOut++;

                        if (--lightsAvailable == 0)
                        {
                            goto exit;
                        }
                    }
                }
            }
        }

        if (pFixedLightsIter->field_0_lightCount == 0)
        {
            break;
        }

        lightCount2 = pFixedLightsIter->field_0_lightCount;
        pLightIter = pFixedLightsIter->field_4_pLights;

        pFixedLightsIter++;
    }

exit:
    return 2 - lightsAvailable;
}

void DG_SetLightMatrix( MATRIX* mtx, int trans_x )
{
    mtx[1].t[0] = trans_x;
}

int DG_GetLightMatrix2( SVECTOR* vec, MATRIX* mtx )
{
    int ret = 2;

    if ( GM_GameStatus & STATE_THERMG )
    {
        unsigned long* mtx_lng = (unsigned long*)&mtx[1];
        mtx_lng[0] = 0;
        mtx_lng[1] = 0;
        mtx_lng[2] = 0;
        mtx_lng[3] = 0;
        mtx_lng[4] = 0;

        mtx->t[0] = 130;
        mtx->t[1] = 104;
        mtx->t[2] = 80;
    }
    else
    {
        ret = DG_GetLightMatrix(vec, mtx);
        mtx->t[0] = DG_Ambient.vx;
        mtx->t[1] = DG_Ambient.vy;
        mtx->t[2] = DG_Ambient.vz;
    }

    return ret;
}
