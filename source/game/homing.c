#include "homing.h"

#include <stdio.h>
#include <sys/types.h>
#include <libapi.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "game.h"

extern HOMING homing_targets[NUM_HOMING_TARGETS];

void GM_ResetHomingTargets(void)
{
    HOMING *hom;
    int     i;

    hom = homing_targets;
    for (i = NUM_HOMING_TARGETS; i > 0; i--)
    {
        hom->used = FALSE;
        hom++;
    }
}

HOMING *GM_AllocHomingTarget(MATRIX *world, CONTROL *control)
{
    HOMING *hom;
    int     i;

    hom = homing_targets;
    for (i = NUM_HOMING_TARGETS; i > 0; i--)
    {
        if (!hom->used)
        {
            break;
        }

        hom++;
    }

    if (i == 0)
    {
        printf("Homing target over !!!\n");
        return 0;
    }

    hom->world = world;
    hom->control = control;
    hom->flag = FALSE;
    hom->used = TRUE;
    return hom;
}

void GM_FreeHomingTarget(HOMING *hom)
{
    if (hom)
    {
        hom->used = FALSE;
    }
}

void GM_GetHomingTarget(MATRIX *world, int ang, int *yaw, int *pitch, int map)
{
    SVECTOR pos;
    SVECTOR hom_pos;
    SVECTOR diff;
    int     min;
    HOMING *hom;
    int     i;
    int     len;
    int     dir;

    min = 6100;
    hom = homing_targets;

    pos.vx = world->t[0];
    pos.vy = world->t[1];
    pos.vz = world->t[2];

    *yaw = -1;
    *pitch = 0;

    for (i = NUM_HOMING_TARGETS; i > 0; i--)
    {
        if (hom->used && (hom->control->map->index & map) && (hom->flag == TRUE))
        {
            hom_pos.vx = hom->world->t[0];
            hom_pos.vy = hom->world->t[1];
            hom_pos.vz = hom->world->t[2];

            GV_SubVec3(&hom_pos, &pos, &diff);
            len = GV_VecLen3(&diff);

            if (len < min)
            {
                dir = GV_VecDir2(&diff);
                if (GV_DiffDirAbs(ang, dir) < 512)
                {
                    min = len;
                    *yaw = dir;
                    *pitch = (ratan2(len, hom_pos.vy - pos.vy) & 4095) - 1024;
                }
            }
        }

        hom++;
    }
}

void GM_GetHomingTarget2(MATRIX *world, int ang, int *yaw, int *pitch, int map, int max_dist, int max_ang)
{
    SVECTOR pos;
    SVECTOR hom_pos;
    SVECTOR diff;
    int     min;
    HOMING *hom;
    int     i;
    int     len;
    int     dir;

    min = max_dist + 100;
    hom = homing_targets;

    pos.vx = world->t[0];
    pos.vy = world->t[1];
    pos.vz = world->t[2];

    *yaw = -1;
    *pitch = 0;

    for (i = NUM_HOMING_TARGETS; i > 0; i--)
    {
        if (hom->used && (hom->control->map->index & map) && (hom->flag == TRUE))
        {
            hom_pos.vx = hom->world->t[0];
            hom_pos.vy = hom->world->t[1];
            hom_pos.vz = hom->world->t[2];

            GV_SubVec3(&hom_pos, &pos, &diff);
            len = GV_VecLen3(&diff);

            if (len < min)
            {
                dir = GV_VecDir2(&diff);
                if (GV_DiffDirAbs(ang, dir) < max_ang)
                {
                    min = len;
                    *yaw = dir;
                    *pitch = (ratan2(len, hom_pos.vy - pos.vy) & 4095) - 1024;
                }
            }
        }

        hom++;
    }
}
