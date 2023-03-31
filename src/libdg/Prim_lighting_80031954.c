#include "libdg.h"

void Prim_lighting_80031954(SVECTOR *pVerts, int numVerts, DG_LitVertex *pOut, DG_Light *pLights, int numLights)
{
    VECTOR distance;
    VECTOR position;
    int remaining;
    int lights;
    DG_Light *pLight;
    int radius;
    int brightness;

    for (--numVerts; numVerts >= 0; pVerts++, pOut++, numVerts--)
    {
        gte_ldv0(pVerts);
        gte_rt();
        gte_stlvnl0(&position.vx);
        gte_stlvnl1(&position.vy);
        gte_stlvnl2(&position.vz);

        remaining = 2;

        pLight = pLights;
        for (lights = numLights; lights > 0; lights--, pLight++)
        {
            radius = pLight->field_A_radius;

            distance.vx = position.vx - pLight->pos.vx;
            if ((distance.vx < -radius) || (distance.vx > radius))
            {
                continue;
            }

            distance.vy = position.vy - pLight->pos.vy;
            if ((distance.vy < -radius) || (distance.vy > radius))
            {
                continue;
            }

            distance.vz = position.vz - pLight->pos.vz;
            if ((distance.vz < -radius) || (distance.vz > radius))
            {
                continue;
            }

            brightness = pLight->field_8_brightness;

            if (--remaining == 0)
            {
                DG_GetLightVector_8001A1A8(&distance, pLight->field_8_brightness, &pOut->intensity[1]);
                LCOPY(&pLight->field_C_colour, &pOut->color[1]);
                break;
            }

            DG_GetLightVector_8001A1A8(&distance, brightness, &pOut->intensity[0]);
            LCOPY(&pLight->field_C_colour, &pOut->color[0]);
        }

        switch (remaining)
        {
        case 2:
            LSTORE(0, &pOut->color[0]);

        case 1:
            LSTORE(0, &pOut->color[1]);
            break;
        }
    }
}
