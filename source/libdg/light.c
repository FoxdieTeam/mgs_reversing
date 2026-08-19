#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "libdg.h"
#include "common.h"
#include "libgv/libgv.h"
#include "game/game.h"

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

u_long DG_PacketCode[2] = { 0x3C808080, 0x3E808080 };

/*** bss ***/
extern FIXLIGHT fix_lights[ MAX_FIX_LIGHTS ];
extern TLIGHT   tlights[ 2 ];

/*---------------------------------------------------------------------------*/

void DG_InitLightSystem( void )
{
    DG_ResetFixedLight();
    tlights[ 0 ].n_lights = 0;
    tlights[ 1 ].n_lights = 0;
    DG_SetAmbient( 0 , 0 , 0 );
}

void DG_SetAmbient( int r, int g, int b )
{
    DG_Ambient.vx = r;
    DG_Ambient.vy = g;
    DG_Ambient.vz = b;
    gte_SetBackColor( r, g, b );

    r = ( ( 256 - r ) >> 1  ) & 0xFF;
    g = ( ( 256 - g ) << 7  ) & 0xFF00;
    b = ( ( 256 - b ) << 15 ) & 0xFF0000;

    DG_PacketCode[ 0 ] = 0x3C000000 | r | g | b;
    DG_PacketCode[ 1 ] = DG_PacketCode[ 0 ] | 0x2000000;
}

void DG_SetMainLightDir( int x, int y, int z )
{
    VECTOR vec, dir;

    vec.vx = x;
    vec.vy = y;
    vec.vz = z;
    VectorNormal( &vec, &dir );
    DG_LightMatrix.m[ 0 ][ 0 ] = dir.vx;
    DG_LightMatrix.m[ 0 ][ 1 ] = dir.vy;
    DG_LightMatrix.m[ 0 ][ 2 ] = dir.vz;
}

void DG_SetMainLightCol( int r, int g, int b )
{
    DG_ColorMatrix.m[ 0 ][ 0 ] = r * 16;
    DG_ColorMatrix.m[ 1 ][ 0 ] = g * 16;
    DG_ColorMatrix.m[ 2 ][ 0 ] = b * 16;
}

void DG_ResetFixedLight( void )
{
    int i;
    FIXLIGHT *p;

    p = fix_lights;

    for ( i = MAX_FIX_LIGHTS; i > 0; i--, p++ )
    {
        p->n_lights = 0;
        p->lights = NULL;
    }
}

void DG_SetFixedLight( DG_LIT *lights, int n_lights )
{
    int i;
    FIXLIGHT *p;

    p = fix_lights;

    for ( i = MAX_FIX_LIGHTS - 1; i > 0; i--, p++ )
    {
        if ( p->lights == lights ) return;
        if ( p->n_lights == 0 )
        {
            p->n_lights = n_lights;
            p->lights = lights;
            return;
        }
    }
}

void DG_ClearTmpLight( void )
{
    TLIGHT *tlp;

    tlp = tlights + ( GV_Time & 1 );
    tlp->n_lights = 0;
}

int DG_SetTmpLight( SVECTOR *point, int r_range, int e_range )
{
    TLIGHT *tlp;
    DG_LIT *lit;
    int nl;

    tlp = tlights + ( GV_Time & 1 );
    nl = tlp->n_lights;

    if ( nl >= MAX_TMPLIGHTS ) return -1;
    tlp->n_lights = nl + 1;

    lit = tlp->lights + nl;
    lit->point = *point;
    lit->r_range = r_range;
    lit->e_range = e_range;
    LSTORE(COLOR_WHITE, &lit->color);

    return 0;
}

void DG_GetLightVector( VECTOR *vec, int r_range, SVECTOR *light )
{
    VECTOR temp;
    int sq, sq2;

    Square0(vec, &temp);
    sq = SquareRoot0(temp.vx + temp.vy + temp.vz);
    if (sq == 0) sq = 1;

    sq2 = r_range * 2 - sq;
    if (sq2 < 0) sq2 = 0;

    light->vx = vec->vx * 3072 / sq * sq2 / r_range;
    light->vy = vec->vy * 3072 / sq * sq2 / r_range;
    light->vz = vec->vz * 3072 / sq * sq2 / r_range;
}

int DG_GetLightMatrix( SVECTOR *pos, MATRIX *light )
{
    int lightCount, lightCount2;
    int lightRadius;
    DG_LIT *pLightIter;
    short *pColorOut;
    int lightsAvailable;
    DG_SVECTOR *lightOut;
    FIXLIGHT *pFixedLightsIter;
    VECTOR lightDistance;
    TLIGHT *pTmpLightList;

    lightOut = (DG_SVECTOR *)light->m[1];
    pColorOut = &light[1].m[0][1];
    pFixedLightsIter = fix_lights;
    lightsAvailable = 2;

    memcpy(&light[0].m, DG_LightMatrix.m, 20);
    memcpy(&light[1].m, DG_ColorMatrix.m, 20);

    pTmpLightList = &tlights[~GV_Time & 1];
    lightCount2 = pTmpLightList->n_lights;
    pLightIter = pTmpLightList->lights;

    while (1)
    {
        for (lightCount = lightCount2; lightCount > 0; lightCount--, pLightIter++)
        {
            lightRadius = pLightIter->e_range;

            lightDistance.vx = pos->vx - pLightIter->point.vx;

            if (lightDistance.vx >= -lightRadius && lightDistance.vx <= lightRadius)
            {
                lightDistance.vy = pos->vy - pLightIter->point.vy;

                if (lightDistance.vy >= -lightRadius && lightDistance.vy <= lightRadius)
                {
                    lightDistance.vz = pos->vz - pLightIter->point.vz;

                    if (lightDistance.vz >= -lightRadius && lightDistance.vz <= lightRadius)
                    {
                        DG_GetLightVector(&lightDistance, pLightIter->r_range, (SVECTOR *)lightOut);
                        lightOut++;

                        pColorOut[0] = pLightIter->color.r << 4;
                        pColorOut[3] = pLightIter->color.g << 4;
                        pColorOut[6] = pLightIter->color.b << 4;
                        pColorOut++;

                        if (--lightsAvailable == 0)
                        {
                            goto exit;
                        }
                    }
                }
            }
        }

        if (pFixedLightsIter->n_lights == 0)
        {
            break;
        }

        lightCount2 = pFixedLightsIter->n_lights;
        pLightIter = pFixedLightsIter->lights;

        pFixedLightsIter++;
    }

exit:
    return 2 - lightsAvailable;
}

void DG_SetLightMatrix( MATRIX *light, int trans_x )
{
    light[1].t[0] = trans_x;
}

int DG_GetLightMatrix2( SVECTOR* pos, MATRIX* light )
{
    int ret = 2;

    if ( GM_GameStatus & STATE_THERMG )
    {
        unsigned long* light_lng = (unsigned long*)&light[1];
        light_lng[0] = 0;
        light_lng[1] = 0;
        light_lng[2] = 0;
        light_lng[3] = 0;
        light_lng[4] = 0;

        light->t[0] = 130;
        light->t[1] = 104;
        light->t[2] = 80;
    }
    else
    {
        ret = DG_GetLightMatrix(pos, light);
        light->t[0] = DG_Ambient.vx;
        light->t[1] = DG_Ambient.vy;
        light->t[2] = DG_Ambient.vz;
    }

    return ret;
}
