#include "charalst.h"

CHARA _StageCharacterEntries[] = {
    CHARA_SHAKE_MODEL,
    CHARA_WALL,                 /* chara 障害物 */
    CHARA_ASIOTO,
    CHARA_FADE_IN_OUT,
    CHARA_DYNAMIC_SEGMENT,      /* chara 透明壁 */
    CHARA_FADEIO_0003,
    CHARA_FADEIO_0004,
    { 0x0028, NewSepia_800C4F9C }, // WRONG!! 0x0028 is NewSepia_800C5214
    CHARA_SELECT,
    CHARA_VIB_EDIT,
    CHARA_RIPPLES,
    CHARA_PAD,                  /* chara パッドコントロール */
    CHARA_VIBRATE,              /* chara パッド振動 */
    CHARA_BREATH,               /* chara スネーク息 */
    CHARA_ENV_SOUND,
    CHARA_CAMERA_SHAKE,
    CHARA_CAT_IN,
    CHARA_CINEMA,               /* chara シネマスクリーン */
    CHARA_PAD_DEMO,             /* chara パッドデモ */
    CHARA_DYNAMIC_SEGMENT,      // duplicate
    CHARA_ASIOTO,               // duplicate
    CHARA_ASIATOKUN,            /* chara 足跡君 */
    CHARA_WALL,                 // duplicate
    CHARA_SHAKE_MODEL,          // duplicate
    CHARA_PATO_LAMP,            /* chara パトランプ */
    CHARA_COMMANDER,            /* chara コマンダー */
    CHARA_WT_AREA,
    CHARA_WATCHER,              /* chara 巡回兵 */
    CHARA_SMOKE,                /* chara 煙 */
    CHARA_EMITTER,
    CHARA_ELEVATOR,             /* chara エレベータ */
    CHARA_ELEVATOR_PANEL,
    CHARA_MOUSE,
    CHARA_RSURFACE,
    CHARA_TELOP_SET,            /* chara テロップ */
    CHARA_BUBBLE_S,             /* chara 泡 */
    CHARA_O2_DAMAGE,
    CHARA_FADE_IN_OUT,          // duplicate
    CHARA_END
};
