#include "common.h"
#include "charalst.h"

CHARA _StageCharacterEntries[] = {
    CHARA_ASIOTO,
    CHARA_FADE_IN_OUT,
    { 0x8e70, (NEWCHARA)0x800DB50C },   // s08b_glass_800DB50C (NewGlass_800D37A4)
    { 0x5f02, (NEWCHARA)0x800DB87C },   // s08b_paper_800DB87C
    { 0x788d, (NEWCHARA)0x800DAB50 },   // s08b_chair_800DAB50
    { 0xdd95, (NEWCHARA)0x800E1728 },   // NewPanel2_800E1728
    { 0x6d78, (NEWCHARA)0x800DCDE0 },   // NewMonitor1_800DCDE0
    { 0x30ba, (NEWCHARA)0x800C8DCC },   // s08b_ninja_800C8DCC
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
    CHARA_BLOOD_BL,
    CHARA_KATANA,
    CHARA_GAS_EFCT,
    CHARA_TELOP_004C,

    CHARA_END
};
