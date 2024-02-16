#include "psyq.h"

int safechk_commands_800C3270[] = {
    0x03010001,
    0x05010007,
    0x03010302,
    0x05010016,
    0x0301010E,
    0x03040119,
    0x0301000B,
    0x03010003,
    0x03020119,
    0x05010009,
};

char *safechk_cdregs_800C3298[] = {
    (char *)0x1F801800,
    (char *)0x1F801801,
    (char *)0x1F801802,
    (char *)0x1F801803,
};

char safechk_params_800C32A8[] = {
    0, 0, 0, 0, 0, 0, 0, 0
};

char safechk_results_800C32B0[] = {
    0, 0, 0, 0, 0, 0, 0, 0
};

char safechk_800C32B8[] = {
    0, 0,
    6, 5,
    12, 10,
    18, 15,
    24, 20,
    30, 25,
    35, 30,
    40, 34,
    45, 38,
    49, 41,
    53, 44,
    56, 47,
    59, 49,
    61, 51,
    62, 52,
    63, 53,
    64, 54,
    0, 0,
    0, 0,
    0, 0,
    0, 0,
    0, 0,
    0, 0,
    0, 0
};

// 強制終了しました。 本体が改造されている おそれがあります。
const char safechk_string_800C5F1C[] = {
    "\x8B\xAD\x90\xA7\x8F\x49\x97\xB9\x82\xB5\x82\xDC\x82\xB5\x82\xBD\x81\x42\x0A\x96\x7B\x91\xCC\x82\xAA\x89\xFC\x91\xA2\x82\xB3\x82\xEA\x82\xC4\x82\xA2\x82\xE9\x0A\x82\xA8\x82\xBB\x82\xEA\x82\xAA\x82\xA0\x82\xE8\x82\xDC\x82\xB7\x81\x42"
};

const DVECTOR safechk_800C5F58[] = {
    {257, 511},
    {-255, -1},
    {0, 0},
    {0, 0},
    {0, 0}
};
