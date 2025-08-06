#ifndef _LINKVAR_H_
#define _LINKVAR_H_

// This file was probably auto-generated in the original source.
// (The memleak shows exactly two tabs between each identifier and definition,
// and no tabstop setting will align them properly).

extern short       linkvarbuf[0x60];

//------------------------------------------------------------------------------
// 0x00 General
#define GM_UnkFlag00          linkvarbuf[ 0 ]
#define GM_DifficultyFlag     linkvarbuf[ 1 ] // -1,0,1,2,3
#define GM_GameStatusFlag     linkvarbuf[ 2 ] // bit 12 (0x800) = radar on/off
#define GM_BonusItemsFlag     linkvarbuf[ 3 ] // 0 = none, 1 = bandana, 2 = stealth, > 2 = tuxedo
#define GM_CurrentDiskFlag    linkvarbuf[ 4 ] // 1 or 2
#define GM_LastResultFlag     linkvarbuf[ 5 ] // Store result of last op, so it can be used in gcl scripting
#define GM_CurrentStageFlag   linkvarbuf[ 6 ] // hash
#define GM_CurrentMapFlag     linkvarbuf[ 7 ] // hash

//------------------------------------------------------------------------------
// 0x10 Snake
#define GM_SnakePosX          linkvarbuf[ 8 ]
#define GM_SnakePosY          linkvarbuf[ 9 ]
#define GM_SnakePosZ          linkvarbuf[ 10 ]
#define GM_SnakeCurrentHealth linkvarbuf[ 11 ]
#define GM_SnakeMaxHealth     linkvarbuf[ 12 ] // from 256 to around 1400 near end game
#define GM_StatusEvent        linkvarbuf[ 13 ] // bit 1 (0x1) = common cold, bit 3 (0x4) = diazepam active, bit 4 (0x8) = blown up
#define GM_CurrentWeaponId    linkvarbuf[ 14 ] // -1 = no equipped weapon
#define GM_CurrentItemId      linkvarbuf[ 15 ] // -1 = no equipped item
#define GM_PlayerStance        linkvarbuf[ 16 ] // 0 = standing, 1 = crouching, 2 = lying down

//------------------------------------------------------------------------------
#define GM_Weapons            (&linkvarbuf[ 17 ])

// 0x22 Weapons ammo (Use GM_Weapons[] instead)
//      value -1 = not in inventory
#define GM_SocomFlag          linkvarbuf[ 17 ]
#define GM_FamasFlag          linkvarbuf[ 18 ]
#define GM_GrenadeFlag        linkvarbuf[ 19 ]
#define GM_RemoteMissileFlag  linkvarbuf[ 20 ]
#define GM_StingerFlag        linkvarbuf[ 21 ]
#define GM_LandMineFlag       linkvarbuf[ 22 ]
#define GM_BombFlag           linkvarbuf[ 23 ]
#define GM_StunGrenadeFlag    linkvarbuf[ 24 ]
#define GM_ChaffGrenadeFlag   linkvarbuf[ 25 ]
#define GM_RifleFlag          linkvarbuf[ 26 ]

//-----------------------------------------------
#define GM_WeaponsMax         (&linkvarbuf[ 27 ])

// 0x36 Weapons max ammo (Use GM_WeaponsMax[] instead)
#define GM_SocomMax           linkvarbuf[ 27 ]
#define GM_FamasMax           linkvarbuf[ 28 ]
#define GM_GrenadeMax         linkvarbuf[ 29 ]
#define GM_RemoteMissileMax   linkvarbuf[ 30 ]
#define GM_StingerMax         linkvarbuf[ 31 ]
#define GM_LandMineMax        linkvarbuf[ 32 ]
#define GM_BombMax            linkvarbuf[ 33 ]
#define GM_StunGrenadeMax     linkvarbuf[ 34 ]
#define GM_ChaffGrenadeMax    linkvarbuf[ 35 ]  // $w:チャフグレネード弾数
#define GM_RifleMax           linkvarbuf[ 36 ]  // $w:ライフル弾数

//------------------------------------------------------------------------------
#define GM_Items              (&linkvarbuf[ 37 ])

// 0x4a Items (Use GM_Items[] instead)
//      value -1 = not in inventory
#define GM_TabakoFlag         linkvarbuf[ 37 ]  // $w:たばこ
#define GM_ScopeFlag          linkvarbuf[ 38 ]  // $w:双眼鏡
#define GM_CardboardBoxAFlag  linkvarbuf[ 39 ]  // $w:段ボールヘリポート
#define GM_CardboardBoxBFlag  linkvarbuf[ 40 ]  // $w:段ボール核保存庫
#define GM_CardboardBoxCFlag  linkvarbuf[ 41 ]  // $w:段ボール大雪原
#define GM_NightVisionFlag    linkvarbuf[ 42 ]  // $w:暗視ゴーグル
#define GM_ThermalVisionFlag  linkvarbuf[ 43 ]  // $w:赤外線ゴーグル
#define GM_GasMaskFlag        linkvarbuf[ 44 ]  // $w:ガスマスク
#define GM_BodyArmorFlag      linkvarbuf[ 45 ]  // $w:ボディアーマー
#define GM_KetchupFlag        linkvarbuf[ 46 ]  // $w:ケチャップ
#define GM_StealthFlag        linkvarbuf[ 47 ]  // $w:光学迷彩
#define GM_BandanaFlag        linkvarbuf[ 48 ]
#define GM_CameraFlag         linkvarbuf[ 49 ]
#define GM_RationFlag         linkvarbuf[ 50 ] // > 0 = ration ammount
#define GM_MedicineFlag       linkvarbuf[ 51 ] // > 0 = medicine ammount
#define GM_TranquilizerFlag   linkvarbuf[ 52 ] // > 0 = tranquilizer (diazepam) ammount
#define GM_ShapeKeyFlag       linkvarbuf[ 53 ]
#define GM_CardFlag           linkvarbuf[ 54 ] // > 0 = card level
#define GM_TimerBombFlag      linkvarbuf[ 55 ] // > 0 = timer
#define GM_MineDetectorFlag   linkvarbuf[ 56 ]
#define GM_MODiskFlag         linkvarbuf[ 57 ]
#define GM_RopeFlag           linkvarbuf[ 58 ]
#define GM_HandkerchiefFlag   linkvarbuf[ 59 ]
#define GM_SilencerFlag       linkvarbuf[ 60 ]

//-----------------------------------------------
#define GM_ItemsMax           (GM_Items + 11)

// 0x7a Items max capacity (use GM_ItemsMax[] instead)
#define GM_RationMax          linkvarbuf[ 61 ]
#define GM_ColdMedicineMax    linkvarbuf[ 62 ]
#define GM_TranquilizerMax    linkvarbuf[ 63 ]

//------------------------------------------------------------------------------
// 0x80 PAL Key
#define GM_EnvironTemp        linkvarbuf[ 64 ] // default to 10 or -10 (-30 in warehouse, 30 in blast furnace)
#define GM_ShapeKeyState      linkvarbuf[ 65 ] // 0-2-1 icon index
#define GM_ShapeKeyTemp       linkvarbuf[ 66 ] // -7200 in warehouse, 7200 in blast furnace
#define GM_ShapeKeyTempMax    linkvarbuf[ 67 ] // 9000
#define GM_ShapeKeyTempMin    linkvarbuf[ 68 ] // -9000

//------------------------------------------------------------------------------
// 0x8a Frozen items
#define GM_FrozenItemsState   linkvarbuf[ 69 ]
#define GM_BodyTemp           linkvarbuf[ 70 ] // 360 (36 degrees?)
#define GM_FrozenItemsTemp    linkvarbuf[ 71 ]
#define GM_FrozenItemsTempMin linkvarbuf[ 72 ] // -7200

//------------------------------------------------------------------------------
#define GM_TranquilizerTimer  linkvarbuf[ 73 ]

#define GM_PreviousStageFlag  linkvarbuf[ 74 ] // hash

//------------------------------------------------------------------------------
// 0x96 Snake common cold
#define GM_SnakeColdTimer     linkvarbuf[ 75 ]
#define GM_SnakeColdUnk98     linkvarbuf[ 76 ]
#define GM_SnakeColdUnk9A     linkvarbuf[ 77 ]

//------------------------------------------------------------------------------
// 0x9c Stats
#define GM_EnemyWatchCount    linkvarbuf[ 78 ] // score screen
#define GM_TotalEnemiesKilled linkvarbuf[ 79 ] // score screen
#define GM_UnkFlagA0          linkvarbuf[ 80 ]
#define GM_UnkFlagA2          linkvarbuf[ 81 ]
#define GM_UnkFlagA4          linkvarbuf[ 82 ]
#define GM_UnkFlagA6          linkvarbuf[ 83 ]
#define GM_UnkFlagA8          linkvarbuf[ 84 ]
#define GM_UnkFlagAA          linkvarbuf[ 85 ]
#define GM_TotalRationsUsed   linkvarbuf[ 86 ] // score screen
#define GM_TotalContinues     linkvarbuf[ 87 ] // score screen
#define GM_TotalSaves         linkvarbuf[ 88 ] // score screen
#define GM_GameTimeHours      linkvarbuf[ 89 ]
#define GM_GameTimeSeconds    linkvarbuf[ 90 ]
#define GM_TotalHours         linkvarbuf[ 91 ] // score screen
#define GM_TotalSeconds       linkvarbuf[ 92 ] // score screen
#define GM_LastSaveHours      linkvarbuf[ 93 ]
#define GM_LastSaveSeconds    linkvarbuf[ 94 ]
#define GM_UnkFlagBE          linkvarbuf[ 95 ]

//------------------------------------------------------------------------------
enum // GM_DifficultyFlag
{
    DIFFICULTY_VERY_EASY = -1,  // added for MGS:INTEGRAL
    DIFFICULTY_EASY      = 0,   // the Japanese version's original (only) difficulty
    DIFFICULTY_NORMAL    = 1,
    DIFFICULTY_HARD      = 2,
    DIFFICULTY_EXTREME   = 3,
};

enum // GM_GameStatusFlag
{
    STATUS_RADAR_OFF = 0x800,
};

enum // GM_StatusEvent
{
    EV_CommonCold   = 0x1,
    EV_Tranquilizer = 0x4,
    EV_BlownUp      = 0x8,
};

enum // GM_PlayerStance
{
    // ... negative ones too?
    SNA_STANCE_STANDING  = 0,
    SNA_STANCE_SQUAT    = 1,
    SNA_STANCE_CROUCH    = 2, // prone + knocked down
    SNA_STANCE_UNK       = 3, // first person prone?
    // ... more?
};

enum // GM_Weapons[]
{
    WP_None             = -1,
    WP_Socom            = 0,
    WP_Famas            = 1,
    WP_Grenade          = 2,
    WP_Nikita           = 3,
    WP_Stinger          = 4,
    WP_Claymore         = 5,
    WP_C4               = 6,
    WP_StunGrenade      = 7,
    WP_ChaffGrenade     = 8,
    WP_Rifle            = 9,
};
#define GM_TotalWeapons 10

enum // GM_Items[]
{
    IT_None             = -1,   // types:
    IT_Cigs             = 0,    // 0x8000
    IT_Scope            = 1,    // 0x8003
    IT_Box1             = 2,    // 0x8001
    IT_Box2             = 3,    // 0x8001
    IT_Box3             = 4,    // 0x8001
    IT_NVG              = 5,    // 0x8000
    IT_ThermG           = 6,    // 0x8000
    IT_GasMask          = 7,    // 0x8000
    IT_BodyArmor        = 8,    // 0x8000
    IT_Ketchup          = 9,    // 0x8000
    IT_Stealth          = 10,   // 0x8000
    IT_Bandana          = 11,   // 0x8000
    IT_Camera           = 12,   // 0x8003
    IT_Ration           = 13,   // 0x2000
    IT_ColdMedicine     = 14,   // 0x2000
    IT_Diazepam         = 15,   // 0x2000
    IT_PalKey           = 16,   // 0
    IT_Card             = 17,   // 0
    IT_TimerBomb        = 18,   // 0
    IT_MineDetector     = 19,   // 0
    IT_Disk             = 20,   // 0
    IT_Rope             = 21,   // 0
    IT_Handkerchief     = 22,   // 0
    IT_Suppressor       = 23    // 0
};
#define GM_TotalItems 24

enum // GM_ItemTypes[]
{
    // ...
    ITEMTYPE_CONSUMABLE = 0x2000,
    // ...
};
//------------------------------------------------------------------------------

#define GM_LinkVar(buf, var)      (buf[((short*)&var - (short*)&linkvarbuf)])

#define GM_CurrentWeapon          (GM_Weapons[ GM_CurrentWeaponId ])
#define GM_CurrentItem            (GM_Items[ GM_CurrentItemId ])

#endif // _LINKVAR_H_
