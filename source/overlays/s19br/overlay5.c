#include "mgstype.h"
#include <libgte.h>

/* jeep2.c */
SVECTOR s19b_dword_800C3A7C = {0, 1435, -925};      // gun offset on the jeep body
VECTOR  s19b_dword_800C3A84 = {2048, 2048, 2048};   // jeep model scale
SVECTOR s19b_dword_800C3A94 = {365, 440, 677};      // jeep target size

/* jeep_liq.c / spark2_m.c */
u_char  s19b_dword_800C3A9C[4] = {0xB9, 0xBD, 0xBE, 0xBF}; // Liquid's voice SEs
SVECTOR s19b_dword_800C3AA0 = {0, 0, 100};          // blood offset
SVECTOR s19b_dword_800C3AA8 = {-1024, 0, 0};        // blood rotation
SVECTOR s19b_dword_800C3AB0 = {175, 500, 175};      // target size
SVECTOR s19b_dword_800C3AB8 = {0, 0, 0};            // target offset
SVECTOR s19b_dword_800C3AC0 = {5, -500, 80};        // muzzle offset
/* per difficulty (GM_GameLevel + 1); the last half word is uninitialised
 * padding of the original (end of an object) */
short   s19b_dword_800C3AC8[6] = {20, 20, 16, 12, 5, 0x0C00};

/* spark2_m.c */
int s19b_dword_800C3AD4 = 0;
