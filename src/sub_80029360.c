#include <sys/types.h>
#include <libgte.h>

/**
 * Used in collision detection, called every frame for Snake and each enemy on the map.
 *
 * In Snake's case, the first argument is snake->field_20_ctrl->field_0_vec. Whether for Snake or not, the second
 * argument is always the scratchpad address 0x1f800000c.
 *
 * Disabling this function badly messes up collision detection for both Snake and his enemies, ie Snake will constantly
 * fall into and come back out from the floor as he runs around.
 */
void sub_80029360(SVECTOR *vec_1,SVECTOR *vec_2)
{
	vec_2->vx = vec_1->vx;
	vec_2->vz = vec_1->vy;
	vec_2->vy = vec_1->vz;
}