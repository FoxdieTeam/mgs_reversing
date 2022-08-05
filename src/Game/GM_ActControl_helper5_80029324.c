#include <SYS/TYPES.H>
#include <LIBGTE.H>

#define SCRPAD_ADDR 0x1F800000

/**
 * Fundamental function in collision detection, called when Snake nears an obstacle or an edge.
 *
 * This function is called with the SVECTOR[2] snake->field_20_ctrl->field_60_vecs_ary as an argument. Disabling it
 * disables collision for Snake, seemingly as those vectors are then passed to GM_ActControl_helper_80026C68() as its
 * first argument and used by it to determine values in the scratchpad which are then used at the end of that function
 * to create Snake's movement vector.
 */
void GM_ActControl_helper5_80029324(SVECTOR *vectors)
{
    short *sVar1, *sVar2;

    sVar1 = (short *)(SCRPAD_ADDR + 0x68);
    vectors->vx = sVar1[8];
    vectors->vy = 0;
    vectors->vz = sVar1[9];

    sVar2 = (short *)(SCRPAD_ADDR + 0x84);
    vectors[1].vx = sVar2[8];
    vectors[1].vy = 0;
    vectors[1].vz = sVar2[9];
}
