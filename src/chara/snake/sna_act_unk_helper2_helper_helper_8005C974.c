#include "libgv/libgv.h"
#include "Game/jimctrl.h"

void sna_act_helper2_helper2_80033054(int id, SVECTOR *vec)
{
    int found;

    found = jimctrl_helper_80037F68(id) & 0xFF;
    if (found == 1)
    {
        vec->vx += 32;

        if (vec->vx >= 128)
        {
            vec->vx = 128;

            if (vec->vz == 0)
            {
                vec->vz = GV_RandS_800170BC(32);
            }
        }
    }
    else if (found == 2)
    {
        if (vec->vx < 64)
        {
            vec->vx += 16;

            if (vec->vx >= 64)
            {
                vec->vx = 64;

                if (vec->vz == 0)
                {
                    vec->vz = GV_RandS_800170BC(16);
                }
            }
        }
        else
        {
            vec->vx -= 16;

            if (vec->vx <= 64)
            {
                vec->vx = 64;

                if (vec->vz == 0)
                {
                    vec->vz = GV_RandS_800170BC(16);
                }
            }
        }
    }
    else if (vec->vx > 0)
    {
        vec->vx -= 8;
    }

    if (vec->vz != 0)
    {
        if (vec->vz > 0)
        {
            vec->vz -= 8;

            if (vec->vz < 0)
            {
                vec->vz = 0;
            }
        }
        else
        {
            vec->vz += 8;

            if (vec->vz > 0)
            {
                vec->vz = 0;
            }
        }
    }
}
