#include "linker.h"
#include "game.h"

PlayerStatusFlag SECTION(".sbss") GM_PlayerStatus_800ABA50;
/**
 * Some known settings via GM_SetPlayerStatusFlag_8004E2B4():
 * |= 0x20008000 if Snake dies from sna_init_check_dead_8004E384() and sna_init_anim_dying_80055524().
 * |= 0x20 if Snake crouches from sna_init_anim_crouch_800527DC().
 * |= 0x40 if Snake goes prone from  sna_init_anim_prone_begin_80053BE8() and sna_init_anim_prone_idle_800528BC().
 * |= 0x10 if Snake runs from sna_init_anim_run_begin_80053B88(), sna_init_anim_run_8005292C(), sna_init_anim_rungun_begin_80056BDC() and sna_init_anim_rungun_80056C3C().
 * |= 0x10 if Snake moves while prone from sna_init_anim_prone_move_800529C0().
 * |= 0x10 if Snake moves while in a box from sna_init_anim_box_run_8005544C().
 * |= 0x10000 if Snake pushes up against a wall from sna_init_anim_wall_idle_and_c4_80052A5C().
 * |= 0x10010 if Snake moves while up against a wall from sna_init_anim_wall_move_80052BA8().
 * |= 0x10020 if Snake crouches while up against a wall from sna_init_anim_wall_crouch_80052CCC().
 * |= 0x10 from sna_init_anim_choke_drag_80059054().
 */
