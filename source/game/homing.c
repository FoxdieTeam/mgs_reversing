#include "homing.h"

#include <stdio.h>
#include <sys/types.h>
#include <libapi.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "game/map.h"
#include "libgv/libgv.h"

extern HOMING gHomingTargets_800B8230[HOMING_ARRAY_LENGTH];

void GM_ResetHomingTargets(void)
{
    HOMING *pIter; // $v0
    int     i;     // $v1

    pIter = gHomingTargets_800B8230;
    for (i = HOMING_ARRAY_LENGTH; i > 0; --i)
    {
        pIter->auto_aimable = 0;
        ++pIter;
    }
}

HOMING *GM_AllocHomingTarget(MATRIX *matrix, CONTROL *control)
{
    int     pos; // $v1
    HOMING *pIter = gHomingTargets_800B8230;

    for (pos = HOMING_ARRAY_LENGTH; pos > 0; --pos)
    {
        if (!pIter->auto_aimable)
        {
            break;
        }
        ++pIter;
    }

    if (!pos)
    {
        printf("Homing target over !!!\n");
        return 0;
    }

    pIter->matrix = matrix;
    pIter->control = control;
    pIter->flag = 0;
    pIter->auto_aimable = 1;
    return pIter;
}

void GM_FreeHomingTarget(HOMING *homing)
{
    if (homing)
    {
        homing->auto_aimable = 0;
    }
}

void GM_GetHomingTarget(MATRIX *matrix, int vecY, int *pRetY, int *pRetX, int mapBit)
{
    int            smallest_len; // $s6
    HOMING        *homing;       // $s3
    int            i;            // $s5
    int            len;          // $s1
    int            retY;         // $s0
    SVECTOR        vec1;
    SVECTOR        vec2;
    SVECTOR        vec3;

    smallest_len = 6100;
    homing = &gHomingTargets_800B8230[0];
    vec1.vx = matrix->t[0];
    vec1.vy = matrix->t[1];
    vec1.vz = matrix->t[2];
    *pRetY = -1;
    *pRetX = 0;

    for (i = HOMING_ARRAY_LENGTH; i > 0; homing++, i--)
    {
        if (!homing->auto_aimable)
        {
            continue;
        }

        if ((homing->control->map->index & mapBit) && homing->flag == 1)
        {
            vec2.vx = homing->matrix->t[0];
            vec2.vy = homing->matrix->t[1];
            vec2.vz = homing->matrix->t[2];
            GV_SubVec3(&vec2, &vec1, &vec3);
            len = GV_VecLen3(&vec3);
            if (len < smallest_len)
            {
                retY = GV_VecDir2(&vec3);
                if (GV_DiffDirAbs(vecY, retY) < 512)
                {
                    smallest_len = len;
                    *pRetY = retY;
                    *pRetX = (ratan2(len, vec2.vy - vec1.vy) & 4095) - 1024;
                }
            }
        }
    }
}

void GM_GetHomingTarget2(MATRIX *matrix, int vecY, int *pRetY, int *pRetX, int mapBit, int max_dist, int min_angle)
{
    int            smallest_len; // $s6
    HOMING        *homing;       // $s3
    int            i;            // $s5
    int            len;          // $s1
    int            retY;         // $s0
    SVECTOR        vec1;
    SVECTOR        vec2;
    SVECTOR        vec3;

    smallest_len = max_dist + 100;
    homing = &gHomingTargets_800B8230[0];
    vec1.vx = matrix->t[0];
    vec1.vy = matrix->t[1];
    vec1.vz = matrix->t[2];
    *pRetY = -1;
    *pRetX = 0;

    for (i = HOMING_ARRAY_LENGTH; i > 0; homing++, i--)
    {
        if (!homing->auto_aimable)
        {
            continue;
        }

        if ((homing->control->map->index & mapBit) && homing->flag == 1)
        {
            vec2.vx = homing->matrix->t[0];
            vec2.vy = homing->matrix->t[1];
            vec2.vz = homing->matrix->t[2];
            GV_SubVec3(&vec2, &vec1, &vec3);
            len = GV_VecLen3(&vec3);
            if (len < smallest_len)
            {
                retY = GV_VecDir2(&vec3);
                if (GV_DiffDirAbs(vecY, retY) < min_angle)
                {
                    smallest_len = len;
                    *pRetY = retY;
                    *pRetX = (ratan2(len, vec2.vy - vec1.vy) & 4095) - 1024;
                }
            }
        }
    }
}
