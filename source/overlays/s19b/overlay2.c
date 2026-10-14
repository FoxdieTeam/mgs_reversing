#include "mgstype.h"
#include <libgte.h>
#include <libgpu.h>
#include "overlays/s19b/takabe/democame.h"
#include "overlays/s19b/takabe/jeep/jeepdemo.h"

/* jeep_srl.c */

/* model names of the road pieces */
u_short s19b_dword_800C3530[13] = {
    0xCB82, 0x1B3F, 0x1B40, 0x1F3F, 0x1F40, 0x1F41, 0x233F, 0x2340, 0x2341, 0x273F, 0x2740, 0x2741, 0xF6B4
};

/* road script: model, count, x, y, speed_x, speed_y, event_delay, event
 * (JeepRoadCmd in jeep_srl.c), ends with model == -1 */
short s19b_dword_800C354C[][8] = {
    {    0,    10,     0,  1000,     0,   200,     0,     0},
    {    0,    10,  1000,  1000,   100,   200,     0,     0},
    {    0,     4, -1000,  1000,   100,     0,     0,     0},
    {    0,    10,     0,     0,   100,   100,     2,     1},
    {    1,     1,     0,     0,     0,     0,     1,     9},
    {    2,     1,     0,     0,     0,     0,     1,     2},
    {    0,    10,     0,  1000,     0,   100,     0,     0},
    {    0,    10,     0,     0,     0,   100,     1,     3},
    {    1,     1,     0,     0,     0,     0,     1,     9},
    {    2,     1,     0,     0,     0,     0,     1,     4},
    {    0,    20,     0,  1000,     0,    50,    15,     5},
    {    0,    -8,     0,  1000,     0,     0,     5,     6},
    {    3,     1,     0,  1000,     0,     0,     1,    10},
    {    4,    -8,     0,  1000,     0,     0,     0,    15},
    {    5,     1,     0,  1000,     0,     0,     1,    12},
    {    0,    -8,     0,  1000,     0,     0,     5,     7},
    {    6,     1,     0,  1000,     0,     0,     1,    11},
    {    7,    -8,     0,  1000,     0,     0,     0,     0},
    {    8,     1,     0,  1000,     0,     0,     1,    13},
    {    0,   -16,     0,  1000,     0,     0,    11,     8},
    {    9,     1,     0,  1000,     0,     0,     0,     0},
    {   10,     1,     0,  1000,     0,     0,     0,     0},
    {   11,     1,     0,  1000,     0,     0,     0,     0},
    {   11,     8,     0,  1000,     0,     0,     0,    14},
    {   -1,     0,     0,  1000,   100,   200,     0,     0},
};

/* shear of the road pieces */
MATRIX s19b_dword_800C36DC = {{{0x800, 0, 0}, {0, 0x801, 0}, {0, 0, 0x800}}, {0, 0, 0}};

/* pad vibrations */
u_char s19b_dword_800C36FC[] = {0x7F, 0x09, 0x00, 0x04, 0x7F, 0x09, 0x00, 0x04, 0x7F, 0x06, 0x00, 0x04, 0x7F, 0x04, 0x00, 0x06, 0x7F, 0x03, 0x00, 0x00};
/* the last two bytes are uninitialised padding of the original (end of an object) */
u_char s19b_dword_800C3710[] = {0xFF, 0x09, 0xF3, 0x02, 0xE7, 0x02, 0xFF, 0x06, 0xF5, 0x01, 0xE0, 0x02, 0xF3, 0x08, 0xE5, 0x08, 0x0B, 0x02, 0xC8, 0x07, 0x0B, 0x03, 0xA4, 0x06, 0x65, 0x1F, 0x3F, 0x2F, 0x00, 0x00, 0x40, 0x14};

/* jeep_gls.c */
VECTOR s19b_dword_800C3730 = {2048, 2048, 2048};

SVECTOR s19b_dword_800C3740 = {0, 1062, 1625};
SVECTOR s19b_dword_800C3748 = {0, 1062, 375};

/* jeep_gte.c */
SVECTOR s19b_dword_800C3750 = {-1250, 562, 1375};
SVECTOR s19b_dword_800C3758 = {1250, 562, 625};

/* jeepdemo.c: attach points of the demo cameras */
SVECTOR s19b_dword_800C3760 = {500, 3000, 5000};
SVECTOR s19b_dword_800C3768 = {0, 0, 0};
SVECTOR s19b_dword_800C3770 = {250, 1400, 1500};

/* jeepdemo.c: demo camera 0 */
DEMOCAM_KEY s19b_dword_800C3778[] = {
    { 3,  30, 0, {0, 0, 0}, {0, 0, 0}, 0x300},
    { 3,  31, 0, {0, 0, 0}, {0, 0, 0}, 0x030},
    { 3, 130, 0, {0, 0, 0}, {0, 0, 0}, 0x003},
    { 0, 175, 0, {0, 0, 0}, {0, 0, 0}, 0x021},
    { 3, 176, 2, {0, 0, 0}, {-170, -1300, 500}, 0x0E0},
    { 3, 275, 2, {0, 0, 0}, {-170, -800, 500}, 0x024},
    { 3, 305, 2, {0, 0, 0}, {170, -1024, 500}, 0x0E0},
    { 1, 335, 2, {0, 0, 0}, {270, -20, 3000}, 0x02C},
    {-1,   0, 0, {0, 0, 0}, {0, 0, 0}, 0x000},
};

DEMOCAM_CMD s19b_dword_800C3898[] = {
    {  1, s19b_jlamp_800D06E0},
    { 30, s19b_jlamp_800D072C},
    {130, s19b_jlamp_800D07EC},
    {141, s19b_jlamp_800D087C},
    {275, s19b_jlamp_800D08C8},
    {335, s19b_jlamp_800D08F0},
    { -1, s19b_jlamp_800D072C},
};

/* jeepdemo.c: demo camera 1 */
DEMOCAM_KEY s19b_dword_800C38D0[] = {
    { 3,  30, 0, {0, 0, 0}, {0, 0, 0}, 0x300},
    { 1, 130, 2, {0, 0, 0}, {4050, 3000, 500}, 0x02C},
    { 1, 630, 0, {0, 0, 0}, {0, 4000, -12000}, 0x002},
    {-1,   0, 0, {0, 0, 0}, {0, 0, 0}, 0x000},
};

DEMOCAM_CMD s19b_dword_800C3950[] = {
    {  1, s19b_jlamp_800D0928},
    { 30, s19b_jlamp_800D094C},
    { 60, s19b_jlamp_800D0970},
    {130, s19b_jlamp_800D09B8},
    {140, s19b_jlamp_800D0990},
    {150, s19b_jlamp_800D09DC},
    { -1, s19b_jlamp_800D094C},
};

/* jlamp.c */
RECT s19b_dword_800C3988 = {300, 300, 600, 600};

/* jeep.c */
u_char s19b_dword_800C3990[] = {0x7F, 0x01, 0x00, 0x00};
u_char s19b_dword_800C3994[] = {0xFF, 0x02, 0x17, 0x05, 0xA0, 0x02, 0x00, 0x00};
u_char s19b_dword_800C399C[] = {0x7F, 0x02, 0x00, 0x00};
u_char s19b_dword_800C39A0[] = {0xFF, 0x01, 0xB7, 0x06, 0x90, 0x0B, 0x5C, 0x09, 0x45, 0x04, 0x22, 0x04, 0x00, 0x00, 0x00, 0x00};
u_char s19b_dword_800C39B0[] = {0x5A, 0x04, 0x7E, 0x04, 0xBC, 0x02, 0x3F, 0x0F, 0x21, 0x19, 0x00, 0x00};

SVECTOR s19b_dword_800C39BC = {365, 440, 677};
SVECTOR s19b_dword_800C39C4 = {315, 440, 365};

int s19b_dword_800C39CC = 0;

SVECTOR s19b_dword_800C39D0[2] = {{0, 450, 300}, {0, 450, -300}};
SVECTOR s19b_dword_800C39E0 = {345, 915, -440};
