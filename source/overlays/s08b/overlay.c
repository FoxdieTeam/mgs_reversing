#define DECLARE_NEWCHARA_PROTOS
#include "charalst.h"

CHARA _StageCharacterEntries[] = {
    CHARA_ASIOTO,
    CHARA_FADE_IN_OUT,
    { 0x8e70, (NEWCHARA)0x800DB50C },   // s08b_glass_800DB50C (NewGlass_800D37A4)
    CHARA_PAPER,
    CHARA_CHAIR,        /* chara 椅子 */
    CHARA_PANEL2,       /* chara パネル２ */
    CHARA_MONITOR1,     /* chara モニタ１ */
    CHARA_NINJA,        /* chara 忍者 */
    CHARA_LAMP,
    CHARA_CINEMA,       /* chara シネマスクリーン */
    CHARA_MOVIE_3453,
    CHARA_WALL,         /* chara 障害物 */
    CHARA_LIFE_UP,
    CHARA_DYNAMIC_SEGMENT, /* chara 透明壁 */
    CHARA_CAT_IN,

    CHARA_FADEIO_0003,
    CHARA_FADEIO_0004,
    CHARA_TELOP_0005,
    CHARA_UNKNOWN_000E,
    CHARA_DEMOKAGE,
    CHARA_UNKNOWN_0011,
    CHARA_SCOPE_0014,
    CHARA_GOGGLE_IR,
    CHARA_GOGGLE_SIGHT,
    CHARA_KOGAKU2,
    CHARA_KOGAKU3,
    CHARA_FOCUS,
    { 0x0023, (NEWCHARA)0x800D6AF4 },   // s08b_d_bloods_800D6AF4
    { 0x0025, (NEWCHARA)0x800D8D84 },   // s08b_blur_800D8D84 (NewBlur_800CD530)
    CHARA_KATANA,
    CHARA_GAS_EFCT,
    CHARA_TELOP_004C,

    CHARA_END
};
