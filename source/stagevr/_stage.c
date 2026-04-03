#define DECLARE_NEWCHARA_PROTOS
#include "charalst.h"

// NOTE: This table was reversed from the PC port's VR executable (mgsvr.exe)
// with the only difference from the main executable's chara table being
// the addition of two entries.
//
// NOTE: There is one PSX-ONLY chara (0x3d78) which is missing from the table.
// This chara was added to vrtitle in the US/EU versions of the VR-DISC.

#if 0
CHARA _StageCharacterEntries[] = {
    { 0x002a, NULL },   // CHARA_002A,
    { 0x002f, NULL },   // CHARA_002F,
    { 0x0030, NULL },   // CHARA_0030_BLST_LN,
    { 0x0009, NULL },   // CHARA_0009_BLOOD,
    { 0x000d, NULL },   // CHARA_000D_D_BLOODS,
    { 0x0048, NULL },   // CHARA_0048_BLOODDRP,
    { 0x0047, NULL },   // CHARA_0047_BLOODHZD,
    { 0x000a, NULL },   // CHARA_000A_SPLASH,
    { 0x0025, NULL },   // CHARA_0025_BLUR,
    { 0x004a, NULL },   // CHARA_004A_BOMBLED,
    { 0x000e, NULL },   // CHARA_000E,
    { 0x0012, NULL },   // CHARA_0012_BUBBLE_T,
    { 0x0013, NULL },   // CHARA_0013_BUBBLE_P,
    { 0x000b, NULL },   // CHARA_000B_BULLET,
    { 0x0033, NULL },   // CHARA_0033,
    { 0x003a, NULL },   // CHARA_003A_CELOFAN,
    { 0x0040, NULL },   // CHARA_0040_CELOFAN2,
    { 0x0039, NULL },   // CHARA_0039_CRSH_SMK,
    { 0x0034, NULL },   // CHARA_0034,
    { 0x0015, NULL },   // CHARA_0015_GOGGLE,
    { 0x0016, NULL },   // CHARA_0016_GGLSIGHT,
    { 0x0037, NULL },   // CHARA_0037_RED_ALRT,
    { 0x0038, NULL },   // CHARA_0038_RED_ALRT,
    { 0x001c, NULL },   // CHARA_001C_ENVMAP3,
    { 0x0001, NULL },   // CHARA_0001_BLAST,
    { 0x0003, NULL },   // CHARA_0003_FADEIO,
    { 0x0004, NULL },   // CHARA_0004_FADEIO,
    { 0x0045, NULL },   // CHARA_0045_FAMASLIT,
    { 0x0010, NULL },   // CHARA_0010_DEMOASI,
    { 0x0044, NULL },   // CHARA_0044_BLURPURE,
    { 0x0019, NULL },   // CHARA_0019,
    { 0x0042, NULL },   // CHARA_0042_GAS_EFCT,
    { 0x0022, NULL },   // CHARA_0022_GMSIGHT,
    { 0x0046, NULL },   // CHARA_0046_REALSHDW,
    { 0x003b, NULL },   // CHARA_003B_INVERLT,
    { 0x003f, NULL },   // CHARA_003F_INVERLT2,
    { 0x0017, NULL },   // CHARA_0017_GOGGLEIR,
    { 0x0018, NULL },   // CHARA_0018_GGLSIGHT,
    { 0x0020, NULL },   // CHARA_0020_MGREXLZR,
    { 0x004b, NULL },   // CHARA_004B_MG_ROOM,
    { 0x000c, NULL },   // CHARA_000C,
    { 0x0028, NULL },   // CHARA_0028_SEPIA,
    { 0x0011, NULL },   // CHARA_0011,
    { 0x0049, NULL },   // CHARA_0049_WINDCRCL,
    { 0x0041, NULL },   // CHARA_0041_NINJALZR,
    { 0x002d, NULL },   // CHARA_002D_KATANA,
    { 0x0035, NULL },   // CHARA_0035,
    { 0x0036, NULL },   // CHARA_0036,
    { 0x001a, NULL },   // CHARA_001A_KOGAKU2,
    { 0x001b, NULL },   // CHARA_001B_KOGAKU3,
    { 0x001d, NULL },   // CHARA_001D_PLASMA,
    { 0x0024, NULL },   // CHARA_0024_PLASMA,
    { 0x0007, NULL },   // CHARA_0007,
    { 0x0029, NULL },   // CHARA_0029_RFSIGHT,
    { 0x0014, NULL },   // CHARA_0014_SCOPE,
    { 0x001f, NULL },   // CHARA_001F_SEPIA,
    { 0x000f, NULL },   // CHARA_000F_DEMOKAGE,
    { 0x0032, NULL },   // CHARA_0032_M1E1SMKE,
    { 0x002c, NULL },   // CHARA_002C_SIGHT,
    { 0x0008, NULL },   // CHARA_0008,
    { 0x0002, NULL },   // CHARA_0002,
    { 0x0031, NULL },   // CHARA_0031_SMKE_LN,
    { 0x003c, NULL },   // CHARA_003C_SPARK2,
    { 0x003d, NULL },   // CHARA_003D_SPARK,
    { 0x003e, NULL },   // CHARA_003E,
    { 0x0026, NULL },   // CHARA_0026,
    { 0x0027, NULL },   // CHARA_0027,
    { 0x002e, NULL },   // CHARA_002E_SUB_ROOM,
    { 0x0043, NULL },   // CHARA_0043_SUB_EFCT,
    { 0x0006, NULL },   // CHARA_0006,
    { 0x0005, NULL },   // CHARA_0005_TELOP,
    { 0x004c, NULL },   // CHARA_004C_TELOP,
    { 0x0021, NULL },   // CHARA_0021_FOCUS,
    { 0x0023, NULL },   // CHARA_0023_D_BLOODS,
    { 0x002b, NULL },   // CHARA_002B_D_BLOODS,
    { 0x001e, NULL },   // CHARA_001E_WINDCRCL,

    { 0x40e9, NULL },   // CHARA_10A_DEMO,
    { 0xe068, NULL },   // CHARA_S11_OBJS,      /* chara コントロールＳ１１物 */
    { 0xd53c, NULL },   // CHARA_11B_DEMO,
    { 0x153e, NULL },   // CHARA_11G_DEMO,
    { 0x9ffd, NULL },   // CHARA_9FFD_2ND,
    { 0x2d0a, NULL },   // CHARA_2D0A_2ND,
    { 0x566f, NULL },   // CHARA_ABST,          /* chara アブスト */
    { 0x4974, NULL },   // CHARA_ABST_DEMO1,    /* chara アブストデモ１ */
    { 0x4975, NULL },   // CHARA_ABST_DEMO2,    /* chara アブストデモ２ */
    { 0x05ef, NULL },   // CHARA_AIRSHOWER,     /* chara エアシャワー */
    { 0x2a90, NULL },   // CHARA_ARRAY,
    { 0x02c4, NULL },   // CHARA_ASIATOKUN,     /* chara 足跡君 */
    { 0x92bc, NULL },   // CHARA_ASIOTOKUN,     /* chara 足音君 */
    { 0x9988, NULL },   // CHARA_AT,            /* chara ＡＴ */
    { 0xf59e, NULL },   // CHARA_BELONG,
    { 0x6b6c, NULL },   // CHARA_BLACKSMOKE,    /* chara 黒煙 */
    { 0x8185, NULL },   // CHARA_BLINKTEX,      /* chara 点滅テクスチャ */
    { 0x1158, NULL },   // CHARA_BLOODY_MERYL,  /* chara 血まみれメリル */
    { 0x4e95, NULL },   // CHARA_BLOOD_POOL,    /* chara 血溜り */
    { 0x6a4c, NULL },   // CHARA_BLOOD_POOL2,   /* chara 血溜り２ */
    { 0x9093, NULL },   // CHARA_BLUR,          /* chara ブラー */
    { 0xf74b, NULL },   // CHARA_BOXALL,        /* chara 全部箱 */
    { 0x32fc, NULL },   // CHARA_BREAK_OBJECT,
    { 0x6471, NULL },   // CHARA_BUTTONCHECK,   /* chara ボタンチェッカー */
    { 0x1a02, NULL },   // CHARA_BUBBLE,        /* chara 泡 */
    { 0x93b6, NULL },   // CHARA_B_SELECT,
    { 0x7eca, NULL },   // CHARA_C4WIRE,        /* chara ワイヤ */
    { 0x6e90, NULL },   // CHARA_CAMERA,        /* chara カメラ */
    { 0x56cc, NULL },   // CHARA_CAMERA2,       /* chara カメラ２ */
    { 0xa9c5, NULL },   // CHARA_GUNCAMERA,
    { 0x7bc2, NULL },   // CHARA_CAMERASHAKE,   /* chara カメラ揺らし */
    { 0xb99f, NULL },   // CHARA_CAPE,
    { 0x51c6, NULL },   // CHARA_CAT_IN,
    { 0xf722, NULL },   // CHARA_CDCHANGE,      /* chara ＣＤ交換 */
    { 0x43a0, NULL },   // CHARA_CENSOR,        /* chara 赤外線センサー */
    { 0x788d, NULL },   // CHARA_CHAIR,         /* chara 椅子 */
    { 0x7a05, NULL },   // CHARA_CINEMA,        /* chara シネマスクリーン */
    { 0x3c0c, NULL },   // CHARA_CLAYMORE,      /* chara クレイモア地雷 */
    { 0xc6d7, NULL },   // CHARA_COMMANDER,     /* chara コマンダー */
    { 0xcc45, NULL },   // CHARA_CONTAINER,     /* chara コンテナ */
    { 0x22c6, NULL },   // CHARA_COUNTDOWN,     /* chara カウントダウン */
    { 0xeced, NULL },   // CHARA_COUNTDOWN2,    /* chara カウントダウンタイマー */
    { 0xa3fb, NULL },   // CHARA_CRANE,         /* chara クレーン */
    { 0x8e60, NULL },   // CHARA_CROW,          /* chara カラス */
    { 0xbe79, NULL },   // CHARA_DEATHSPARK,    /* chara 送別火花 */
    { 0x6a98, NULL },   // CHARA_DAMAGESMOKE,   /* chara ダメージ煙 */
    { 0x76bc, NULL },   // CHARA_DAMAGESMOKE2,  /* chara ダメージ煙２ */
    { 0xb4e6, NULL },   // CHARA_DEMOCANCEL,    /* chara デモキャンセル */
    { 0xe97e, NULL },   // CHARA_DEMODOLL,      /* chara デモ人形 */
    { 0x3686, NULL },   // CHARA_DEMOSEL,       /* chara デモ劇場 */
    { 0x9f7d, NULL },   // CHARA_DISPLAY,
    { 0x9d00, NULL },   // CHARA_DMYFLOOR,      /* chara 落し穴 */
    { 0x58f0, NULL },   // CHARA_DMYWALL,       /* chara 塗り壁 */
    { 0x6c0e, NULL },   // CHARA_DOG,           /* chara 狼犬 */
    { 0xb997, NULL },   // CHARA_DOOR,          /* chara ドア */
    { 0x73f8, NULL },   // CHARA_DOOR2,         /* chara ドア２ */
    { 0xb58d, NULL },   // CHARA_DRUMCAN,       /* chara ドラム缶 */
    { 0x4be8, NULL },   // CHARA_DRUMCAN2,      /* chara ドラム缶２ */
    { 0x3303, NULL },   // CHARA_DUCTMOUSE,
    { 0xaf6c, NULL },   // CHARA_DYNFLOOR,      /* chara 透明床 */
    { 0xb103, NULL },   // CHARA_DYNWALL,       /* chara 透明壁 */
    { 0xe75a, NULL },   // CHARA_ED_TELOP,      /* chara エンディングテロップ */
    { 0x107c, NULL },   // CHARA_ELECDAMAGE,    /* chara 電流床ダメージ */
    { 0xaef2, NULL },   // CHARA_ELECFLOOR,     /* chara 電廊 */
    { 0x2abc, NULL },   // CHARA_ELEVATOR,      /* chara エレベータ */
    { 0x9ab9, NULL },   // CHARA_ELEVCROW,      /* chara エレベーターのカラス */
    { 0xe253, NULL },   // CHARA_ELEVPANEL,     /* chara エレベーターパネル */
    { 0x32e5, NULL },   // CHARA_EMITTER,       /* chara ジン発光 */
    { 0xa9dd, NULL },   // CHARA_EMITTER2,      /* chara ジン発光２ */
    { 0xb789, NULL },   // CHARA_ENDINGROLL,    /* chara エンディングロール */
    { 0x3f9a, NULL },   // CHARA_ENV_SOUND,     /* chara 環境音 */
    { 0x76fe, NULL },   // CHARA_ENV_TEST,      /* chara 環境マッピングテスト */
    { 0xa12e, NULL },   // CHARA_FADEIO,        /* chara 白黒フェド */
    { 0xc73e, NULL },   // CHARA_FALL_SPLASH,
    { 0x5d64, NULL },   // CHARA_O2_DAMAGE,
    { 0x118c, NULL },   // CHARA_FINDTRAP,      /* chara 発見トラップ */
    { 0xd6fb, NULL },   // CHARA_FOG,           /* chara 黒フォグ */
    { 0x84e1, NULL },   // CHARA_FONT_TEXT,
    { 0x0fad, NULL },   // CHARA_MOTIONSE,
    { 0xadd8, NULL },   // CHARA_FURNACE,       /* chara 溶鉱炉 */
    { 0x8d5a, NULL },   // CHARA_GASDAMAGE,     /* chara ガスダメージ */
    { 0x5a50, NULL },   // CHARA_GASEFFECT,     /* chara ガス効果 */
    { 0x2477, NULL },   // CHARA_JEEP_EMY,
    { 0xccd3, NULL },   // CHARA_GHOST,         /* chara ゴースト */
    { 0x8e70, NULL },   // CHARA_GLASS,         /* chara ガラス */
    { 0xdb1f, NULL },   // CHARA_GOAL,          /* chara ゴール */
    { 0x9eb7, NULL },   // CHARA_GODZCOM,       /* chara ゴジラコマンダ */
    { 0xcb1f, NULL },   // CHARA_GODZILA,       /* chara ゴジラ */
    { 0x5f5a, NULL },   // CHARA_GRD_CAM,
    { 0xcbeb, NULL },   // CHARA_BG_HEX,
    { 0x0d9b, NULL },   // CHARA_BG_HEX_S,
    { 0x42e4, NULL },   // CHARA_HIYOKO,        /* chara ヒヨコ星 */
    { 0xdd8b, NULL },   // CHARA_INTRUDE_CAMERA, /* chara イントルードカメラ */
    { 0x8767, NULL },   // CHARA_ITEM,          /* chara アイテム */
    { 0x6a48, NULL },   // CHARA_JEEPSCROLL,    /* chara ジープスクロール */
    { 0xa27e, NULL },   // CHARA_JDRUM,
    { 0xb757, NULL },   // CHARA_B757_ED_TELOP,
    { 0x1ef9, NULL },   // CHARA_JOHNNY,        /* chara ジョニー */
    { 0x81c7, NULL },   // CHARA_JPEG,          /* chara ＪＰＥＧ */
    { 0x4f02, NULL },   // CHARA_JPEGCAMERA,    /* chara ＪＰＥＧカメラ */
    { 0xc6ac, NULL },   // CHARA_KEY_ITEM,
    { 0x52bf, NULL },   // CHARA_KIKENKUN,      /* chara 危険君 */
    { 0xa6f6, NULL },   // CHARA_A6F6,
    { 0x8b1a, NULL },   // CHARA_LANDING,
    { 0x711f, NULL },   // CHARA_LIFEUP,        /* chara ライフ増加 */
    { 0x425f, NULL },   // CHARA_LIFT,          /* chara リフト */
    { 0x921b, NULL },   // CHARA_LIFT2,         /* chara リフト２ */
    { 0x7bf2, NULL },   // CHARA_LIQUID,        /* chara リキッド */
    { 0xcf72, NULL },   // CHARA_AB_CH,
    { 0x53c7, NULL },   // CHARA_LOAD_DATA,     /* chara ロードデータ */
    { 0x9d71, NULL },   // CHARA_M1E1,
    { 0xd5ec, NULL },   // CHARA_M1E1CAME,
    { 0xe448, NULL },   // CHARA_DOLL2,
    { 0x450f, NULL },   // CHARA_HAIR_M,
    { 0xaf72, NULL },   // CHARA_MEMPSY,
    { 0xc755, NULL },   // CHARA_MERYL3,
    { 0x5078, NULL },   // CHARA_MERYL7,
    { 0xe271, NULL },   // CHARA_MERYL72,
    { 0x4754, NULL },   // CHARA_MGREX,
    { 0x954b, NULL },   // CHARA_MG_DEMO1,
    { 0x1787, NULL },   // CHARA_1787_HIND,
    { 0xb30a, NULL },   // CHARA_MINENE,
    { 0xc218, NULL },   // CHARA_MIRROR,
    { 0xa2b5, NULL },   // CHARA_SAFETY,
    { 0x7acf, NULL },   // CHARA_MODELDOT,      /* chara モデルドット */
    { 0x6d78, NULL },   // CHARA_MONITOR1,      /* chara モニタ１ */
    { 0x0065, NULL },   // CHARA_MOSAIC,        /* chara モザイク */
    { 0xd4a5, NULL },   // CHARA_MOUSE,         /* chara ネズミ */
    { 0x3453, NULL },   // CHARA_MOVIE,         /* chara ムービー */
    { 0x5345, NULL },   // CHARA_5345_MOVIE,
    { 0xb98c, NULL },   // CHARA_MYSTERY_DOOR,  /* chara ミステリードア */
    { 0x173c, NULL },   // CHARA_MYSTERY_SOLDIER, /* chara ミステリー兵 */
    { 0xd3c0, NULL },   // CHARA_D3C0,
    { 0xf002, NULL },   // CHARA_HAIR_N,
    { 0x30ba, NULL },   // CHARA_NINJA,         /* chara 忍者 */
    { 0x4811, NULL },   // CHARA_OBJECT,        /* chara 移動物 */
    { 0xcf79, NULL },   // CHARA_OPEN,          /* chara タイトル */
    { 0x3ac3, NULL },   // CHARA_OPENA,
    { 0xcfef, NULL },   // CHARA_OPENP,
    { 0x976c, NULL },   // CHARA_OPT,
    { 0x8d31, NULL },   // CHARA_OPTA,
    { 0xb916, NULL },   // CHARA_OPTP,
    { 0xcbf8, NULL },   // CHARA_PADCONTROL,    /* chara パッドコントロール */
    { 0x3ed7, NULL },   // CHARA_PADDEMO,       /* chara パッドデモ */
    { 0x720d, NULL },   // CHARA_PADDEMO2,      /* chara パッドデモ２ */
    { 0xfed1, NULL },   // CHARA_PADVIBRATE,    /* chara パッド振動 */
    { 0x20f2, NULL },   // CHARA_PANEL,         /* chara パネル */
    { 0xdd95, NULL },   // CHARA_PANEL2,        /* chara パネル２ */
    { 0x5f02, NULL },   // CHARA_PAPER,         /* chara 書類 */
    { 0x30ce, NULL },   // CHARA_PATOLAMP,      /* chara パトランプ */
    { 0xfdb6, NULL },   // CHARA_FDB6_POCKET,
    { 0x8fdc, NULL },   // CHARA_8FDC_POCKET,
    { 0x6414, NULL },   // CHARA_6414_POCKET,
    { 0xaa13, NULL },   // CHARA_AA13,
    { 0xcf00, NULL },   // CHARA_CF00,
    { 0x10ff, NULL },   // CHARA_PERAPICT,      /* chara ぺら絵 */
    { 0xedeb, NULL },   // CHARA_PHOTOSEL,
    { 0x8427, NULL },   // CHARA_SCN_ANIM,
    { 0x17f5, NULL },   // CHARA_BG_SP,
    { 0x1fa5, NULL },   // CHARA_BG_STAGE,
    { 0xb032, NULL },   // CHARA_BG_ST1,
    { 0xb033, NULL },   // CHARA_BG_ST2,
    { 0xb7ae, NULL },   // CHARA_BG_SP_CM,
    { 0xbc76, NULL },   // CHARA_BG_SP_ST,
    { 0x9c6c, NULL },   // CHARA_PK_GATE,
    { 0xb47a, NULL },   // CHARA_PJEEP,
    { 0x9bc2, NULL },   // CHARA_PLASMA,        /* chara プラズマ */
    { 0xfc0b, NULL },   // CHARA_FLR_SPA,
    { 0x3ad2, NULL },   // CHARA_3AD2,
    { 0xcc89, NULL },   // CHARA_BG_HEX_P,
    { 0x6d1b, NULL },   // CHARA_PREOPE,
    { 0xd8dd, NULL },   // CHARA_PRISON_NINJA,  /* chara 独房忍者 */
    { 0xbf66, NULL },   // CHARA_PRISON_OTACON, /* chara 独房オタコン */
    { 0xa404, NULL },   // CHARA_PRISON_SNAKE,  /* chara 独房スネーク */
    { 0x27a2, NULL },   // CHARA_PRISON_SNAKE2, /* chara 独房スネーク２ */
    { 0xa76f, NULL },   // CHARA_PSYCHOMANTIS,  /* chara サイコマンティス */
    { 0xf4b0, NULL },   // CHARA_PSYCHOMERYL,   /* chara サイコメリル */
    { 0x710d, NULL },   // CHARA_PSYOBJ,        /* chara サイコ物体 */
    { 0x91aa, NULL },   // CHARA_PUTHZD,
    { 0x169c, NULL },   // CHARA_PILOTLAMP,     /* chara パイロットランプ */
    { 0x5147, NULL },   // CHARA_RADARPOINT,    /* chara レーダーポイント */
    { 0x917b, NULL },   // CHARA_ITEM_DOT,
    { 0x04f2, NULL },   // CHARA_RANKING,       /* chara ランキング */
    { 0x5fd9, NULL },   // CHARA_RASEN,         /* chara 螺旋階段 */
    { 0xaa21, NULL },   // CHARA_RASEN_EL,      /* chara 螺旋階段エレベータ */
    { 0xe397, NULL },   // CHARA_RED_ALRT,      /* chara レッドアラート */
    { 0x05af, NULL },   // CHARA_REVOLVER04,    /* chara ボス */
    { 0x81ea, NULL },   // CHARA_RIPPLE_SURFACE,
    { 0x63aa, NULL },   // CHARA_RIPPLES,
    { 0xbda8, NULL },   // CHARA_ROPE,
    { 0xc35f, NULL },   // CHARA_PIPE,
    { 0x11e9, NULL },   // CHARA_11E9_HIND,
    { 0xb959, NULL },   // CHARA_HIND2,
    { 0x9302, NULL },   // CHARA_SAVE_DATA,     /* chara セーブデータ */
    { 0x600d, NULL },   // CHARA_SCN_BOMB,
    { 0xee63, NULL },   // CHARA_SCN_MARK,
    { 0xf50f, NULL },   // CHARA_SEARCHLIGHT,   /* chara サーチライト */
    { 0xba52, NULL },   // CHARA_SHAKEMODEL,
    { 0x03d9, NULL },   // CHARA_SHUTTER,       /* chara シャッター */
    { 0x170c, NULL },   // CHARA_SMOKE,         /* chara 煙 */
    { 0x21ca, NULL },   // CHARA_SNAKE,         /* chara スネーク */
    { 0x760e, NULL },   // CHARA_SNAKE18,       /* chara スネーク１８ */
    { 0x672e, NULL },   // CHARA_SNAKEWARP,     /* chara スネークワープ */
    { 0xc0fe, NULL },   // CHARA_BUB_D_SN,
    { 0xa791, NULL },   // CHARA_SNE17A,
    { 0x4170, NULL },   // CHARA_SNEBREATH,     /* chara スネーク息 */
    { 0x18e3, NULL },   // CHARA_SNOW,          /* chara 雪 */
    { 0xa6f5, NULL },   // CHARA_SNOWSTORM,     /* chara 雪嵐 */
    { 0x901e, NULL },   // CHARA_SNOWAREA,
    { 0x4efc, NULL },   // CHARA_SOUNDTEST,     /* chara サウンドテスト */
    { 0xfaa8, NULL },   // CHARA_FAA8_MOVIE,
    { 0x73ea, NULL },   // CHARA_SPHERE,        /* chara 天球 */
    { 0xbee1, NULL },   // CHARA_SPHERE2,       /* chara 天球２ */
    { 0xd2f6, NULL },   // CHARA_SELECT,
    { 0x175b, NULL },   // CHARA_SMKTRGT,
    { 0x7ff7, NULL },   // CHARA_TELOP,         /* chara テロップ */
    { 0xdcac, NULL },   // CHARA_TEXANIME,      /* chara テクスチャアニメ */
    { 0x6865, NULL },   // CHARA_TEXSCROLL,     /* chara テクスチャスクロール */
    { 0x1ad3, NULL },   // CHARA_TEXTURE_LAMP,  /* chara テクスチャ */
    { 0xaefb, NULL },   // CHARA_TOBCNT,
    { 0xe608, NULL },   // CHARA_TORTURE,
    { 0xcb3a, NULL },   // CHARA_TRUCKTRAP,
    { 0x2a21, NULL },   // CHARA_BED,           /* chara 拷問台 */
    { 0x050c, NULL },   // CHARA_REVOLVER03,    /* chara 拷問オセロット */
    { 0xf5c5, NULL },   // CHARA_UJI,           /* chara 蛆虫 */
    { 0x9ff5, NULL },   // CHARA_VALCAN,        /* chara バルカン */
    { 0x6c66, NULL },   // CHARA_VIBEDITOR,
    { 0x0a02, NULL },   // CHARA_VMODEL,        /* chara モデル */
    { 0x0dc9, NULL },   // CHARA_VOICESYS,      /* chara 音声制御 */
    { 0xed86, NULL },   // CHARA_VR,            /* chara ＶＲ */
    { 0x30c8, NULL },   // CHARA_VR2,           /* chara ＶＲ２ */
    { 0xd07f, NULL },   // CHARA_VRBG,          /* chara ＶＲ背景 */
    { 0x1454, NULL },   // CHARA_VRBG2,         /* chara ＶＲ背景２ */
    { 0x1455, NULL },   // CHARA_VRBG3,         /* chara ＶＲ背景３ */
    { 0xdf0f, NULL },   // CHARA_VRBOX,         /* chara ＶＲＢＯＸ */
    { 0x548e, NULL },   // CHARA_VRBOX2,        /* chara ＶＲＢＯＸ２ */
    { 0x548f, NULL },   // CHARA_VRBOX3,        /* chara ＶＲＢＯＸ３ */
    { 0x5490, NULL },   // CHARA_VRBOX4,        /* chara ＶＲＢＯＸ４ */
    { 0x4deb, NULL },   // CHARA_VRCLEAR,       /* chara ＶＲクリア */
    { 0xc249, NULL },   // CHARA_VRCLEAR2,      /* chara ＶＲクリア２ */
    { 0xc24a, NULL },   // CHARA_VRCLEAR3,      /* chara ＶＲクリア３ */
    { 0xb95f, NULL },   // CHARA_VRCLUTER,
    { 0x8a46, NULL },   // CHARA_VRDEMO,        /* chara ＶＲデモ */
    { 0x49d2, NULL },   // CHARA_VRGLASS,       /* chara ＶＲガラス */
    { 0x03bf, NULL },   // CHARA_VRRESET,       /* chara ＶＲリセット */
    { 0x0c09, NULL },   // CHARA_VRSPARK,
    { 0x5667, NULL },   // CHARA_VRTITLE,       /* chara ＶＲタイトル */
    { 0xd44e, NULL },   // CHARA_VRWINDOW,      /* chara ＶＲウィンドウ */
    { 0x3d26, NULL },   // CHARA_KOBA_WINMNGR,  /* chara ＶＲマネージャ */
    { 0xa5dc, NULL },   // CHARA_VR_PAUSE_MENU, /* chara ＶＲポーズメニュー */
    { 0xb162, NULL },   // CHARA_VR_SNAKE,
    { 0x41a3, NULL },   // CHARA_WAKE,          /* chara 覚醒スネーク */
    { 0xec77, NULL },   // CHARA_WALL,          /* chara 障害物 */
    { 0xf4c3, NULL },   // CHARA_PUT_OBJECT,
    { 0x2b24, NULL },   // CHARA_WALLSPARK,     /* chara 壁スパーク */
    { 0x6e9a, NULL },   // CHARA_WATCHER,       /* chara 巡回兵 */
    { 0x96b5, NULL },   // CHARA_WATEREFFECT,   /* chara 水エフェクト */
    { 0xeea7, NULL },   // CHARA_WSURFACE,
    { 0x962c, NULL },   // CHARA_WOLF,          /* chara ウルフ */
    { 0xdba3, NULL },   // CHARA_WATER_AREA,    /* chara 水領域 */
    { 0xa480, NULL },   // CHARA_WATER_AREA2,   /* chara 水領域２ */
    { 0x69ad, NULL },   // CHARA_WT_OBJ,
    { 0x8e45, NULL },   // CHARA_WT_VIEW,       /* chara 水中主観 */
    { 0xed87, NULL },   // CHARA_ZAKO,          /* chara ざこ */
    { 0x31e3, NULL },   // CHARA_ZAKO10,        /* chara ざこ１０ */
    { 0x8e64, NULL },   // CHARA_ZAKO10COM,     /* chara ざこ１０コマンダー */
    { 0xa608, NULL },   // CHARA_ZAKO11A,       /* chara ざこ１１ａ */
    { 0x5efa, NULL },   // CHARA_ZAKO11ACOM,    /* chara ざこ１１ａコマンダー */
    { 0xa60c, NULL },   // CHARA_ZAKO11E,       /* chara ざこ１１ｅ */
    { 0x5f0a, NULL },   // CHARA_ZAKO11ECOM,    /* chara ざこ１１ｅコマンダー */
    { 0xa60d, NULL },   // CHARA_ZAKO11F,       /* chara ざこ１１ｆ */
    { 0x5f0e, NULL },   // CHARA_ZAKO11FCOM,    /* chara ざこ１１ｆコマンダー */
    { 0x31e7, NULL },   // CHARA_ZAKO14,        /* chara ざこ１４ */
    { 0x8e74, NULL },   // CHARA_ZAKO14COM,     /* chara ざこ１４コマンダー */
    { 0x31ec, NULL },   // CHARA_ZAKO19,        /* chara ざこ１９ */
    { 0x8e88, NULL },   // CHARA_ZAKO19COM,     /* chara ざこ１９コマンダー */
    { 0x7cf7, NULL },   // CHARA_ZAKOCOM,       /* chara ざこコマンダー */
    { 0xb8d4, NULL },   // CHARA_NINJAPLAY,
    { 0xae06, NULL },   // CHARA_NOBU_WINMNGR,
    { 0xc8ca, NULL },   // CHARA_LOADREP,
    { 0xc5b7, NULL },   // CHARA_SAVEMANAGER,
    { 0x3f9d, NULL },   // CHARA_PLAYDEMO,
    { 0xf364, NULL },   // CHARA_REC_DEMO,
    { 0x26bc, NULL },   // CHARA_VR_CHECK,
    { 0xaf75, NULL },   // CHARA_PRESENT,

    CHARA_END
};
#endif
