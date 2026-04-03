#define DECLARE_NEWCHARA_PROTOS
#include "charalst.h"

CHARA _StageCharacterEntries[] = {
    CHARA_SHAKEMODEL,
    CHARA_WALL,         /* chara 障害物 */
    CHARA_ASIOTOKUN,    /* chara 足音君 */
    CHARA_FADEIO,
    CHARA_DYNWALL,      /* chara 透明壁 */
    CHARA_SELECT,
    CHARA_VIBEDITOR,
    CHARA_RIPPLES,
    CHARA_PADCONTROL,   /* chara パッドコントロール */
    CHARA_PADVIBRATE,   /* chara パッド振動 */
    CHARA_SNEBREATH,    /* chara スネーク息 */
    CHARA_ENV_SOUND,
    CHARA_CAMERASHAKE,  /* chara カメラ揺らし */
    CHARA_CAT_IN,
    CHARA_CINEMA,       /* chara シネマスクリーン */
    CHARA_PADDEMO,      /* chara パッドデモ */
    CHARA_ASIATOKUN,    /* chara 足跡君 */
    CHARA_PATOLAMP,     /* chara パトランプ */
    CHARA_COMMANDER,    /* chara コマンダー */
    CHARA_WATER_AREA,   /* chara 水領域 */
    CHARA_WATCHER,      /* chara 巡回兵 */
    CHARA_SMOKE,        /* chara 煙 */
    CHARA_EMITTER,
    CHARA_ELEVATOR,     /* chara エレベータ */
    CHARA_ELEVPANEL,    /* chara エレベーターパネル */
    CHARA_MOUSE,        /* chara ネズミ */
    CHARA_RSURFACE,
    CHARA_TELOP,        /* chara テロップ */
    CHARA_BUBBLE,       /* chara 泡 */
    CHARA_O2_DAMAGE,

    CHARA_0003_FADEIO,
    CHARA_0004_FADEIO,
    { 0x0028, NewSepia_800C4F9C }, // WRONG!! 0x0028 is NewSepia_800C5214

    CHARA_END
};
