#define DECLARE_NEWCHARA_PROTOS
#include "charalst.h"

CHARA _StageCharacterEntries[] = {
    { 0x51c6, (NEWCHARA *)0x800d7ddc }, //  CHARA_CAT_IN,
    { 0xec77, (NEWCHARA *)0x800c4e24 }, //  CHARA_WALL,         /* chara 障害物 */
    { 0x92bc, (NEWCHARA *)0x800c5c5c }, //  CHARA_ASIOTOKUN,    /* chara 足音君 */
    { 0x4170, (NEWCHARA *)0x800c48f8 }, //  CHARA_SNEBREATH,    /* chara スネーク息 */
    { 0xa12e, (NEWCHARA *)0x800d609c }, //  CHARA_FADEIO,       /* chara 白黒フェド */
    { 0x9ff5, (NEWCHARA *)0x800ca1cc }, //  CHARA_VALCAN,       /* chara バルカン */
    { 0xcc45, (NEWCHARA *)0x800d334c }, //  CHARA_CONTAINER,    /* chara コンテナ */
    { 0x5a50, (NEWCHARA *)0x800d4ebc }, //  CHARA_GASEFFECT,    /* chara ガス効果 */
    { 0x8e60, (NEWCHARA *)0x800d4900 }, //  CHARA_CROW,         /* chara カラス */
    { 0x7a05, (NEWCHARA *)0x800d6b8c }, //  CHARA_CINEMA,       /* chara シネマスクリーン */
    { 0x1ad3, (NEWCHARA *)0x800c3e74 }, //  CHARA_TEXTURE,      /* chara テクスチャ */
    { 0x711f, (NEWCHARA *)0x800d63c4 }, //  CHARA_LIFEUP,       /* chara ライフ増加 */
    { 0xb103, (NEWCHARA *)0x800d6dbc }, //  CHARA_DYNWALL,      /* chara 透明壁 */
    { 0xaf6c, (NEWCHARA *)0x800d8224 }, //  CHARA_DYNFLOOR,     /* chara 透明床 */
    { 0x4e95, (NEWCHARA *)0x800c72b8 }, //  CHARA_BLOOD_POOL,   /* chara 血溜り */

    { 0x0002, (NEWCHARA *)0x800c40c8 }, //  DEMO_SMOKE,
    { 0x0003, (NEWCHARA *)0x800d6004 }, //  DEMO_FADEIN,
    { 0x0004, (NEWCHARA *)0x800d6004 }, //  DEMO_FADEOUT,
    { 0x0009, (NEWCHARA *)0x80072728 }, //  DEMO_BLOOD,
    { 0x000a, (NEWCHARA *)0x800c6234 }, //  DEMO_BLOOD2,
    { 0x000d, (NEWCHARA *)0x800c6dc0 }, //  DEMO_BLOODCIRCLE,
    { 0x000e, (NEWCHARA *)0x800c3f68 }, //  DEMO_BREATH,
    { 0x000f, (NEWCHARA *)0x800c5600 }, //  DEMO_SHADOW,
    { 0x0021, (NEWCHARA *)0x800d73d8 }, //  DEMO_UNSHAPEVIEW,
    { 0x0025, (NEWCHARA *)0x800c8f98 }, //  DEMO_BLUR,
    { 0x0028, (NEWCHARA *)0x800d7a20 }, //  DEMO_MONOTONE,
    { 0x0031, (NEWCHARA *)0x800c95a0 }, //  DEMO_SMOKELINE,
    { 0x0037, (NEWCHARA *)0x800c7e44 }, //  DEMO_ENVIRONMENTLIGHT,
    { 0x0038, (NEWCHARA *)0x800c7f08 }, //  DEMO_ENVIRONMENTLIGHT2,
    { 0x0044, (NEWCHARA *)0x800c8494 }, //  DEMO_GHOST,

    CHARA_END
};
