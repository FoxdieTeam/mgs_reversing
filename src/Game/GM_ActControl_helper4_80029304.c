#define SCRPAD_ADDR 0x1F800000

/**
 * Used in collision detection (ie, called when Snake nears an obstacle or an edge).
 *
 * This function is called with the char[2] snake->field_20_ctrl->field_5A as its argument. Disabling it makes Snake
 * treat edges as if they were walls, eg in Dock he turns his back towards the water instead of running towards it on
 * the spot, except if one approaches it while running where he is programmed to dive into it.
 */
void GM_ActControl_helper4_80029304(char *char_arr)
{
    char_arr[0] = *(char *)(SCRPAD_ADDR + 0x74);
    char_arr[1] = *(char *)(SCRPAD_ADDR + 0x90);
}