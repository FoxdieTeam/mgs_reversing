#include <SYS/TYPES.H>
#include <LIBGTE.H>

#define SCRPAD_ADDR 0x1F800000

/**
 * Used in collision detection (ie, called when Snake nears an obstacle or an edge).
 *
 * This function is called with the VECTOR[2]* snake->field_20_ctrl->field_70 as its argument. Disabling it has no
 * obvious effects on collision or gameplay.
 */
void GM_ActControl_helper3_800292E4(SVECTOR **vectors_ptr)
{
	vectors_ptr[0] = *(SVECTOR**)(SCRPAD_ADDR + 0x70);
	vectors_ptr[1] = *(SVECTOR**)(SCRPAD_ADDR + 0x8c);
}
