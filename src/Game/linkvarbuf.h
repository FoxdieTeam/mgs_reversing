#ifndef _LINKVARBUF_H_
#define _LINKVARBUF_H_

extern short       gGameState_800B4D98[0x60];
#define linkvarbuf gGameState_800B4D98

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
#define GM_ChaffGrenadeMax    linkvarbuf[ 35 ]
#define GM_RifleMax           linkvarbuf[ 36 ]

//------------------------------------------------------------------------------
#define GM_Items              (&linkvarbuf[ 37 ])

// 0x4a Items (Use GM_Items[] instead)
//      value -1 = not in inventory
#define GM_TabakoFlag         linkvarbuf[ 37 ]
#define GM_ScopeFlag          linkvarbuf[ 38 ]
#define GM_CardboardBoxAFlag  linkvarbuf[ 39 ]
#define GM_CardboardBoxBFlag  linkvarbuf[ 40 ]
#define GM_CardboardBoxCFlag  linkvarbuf[ 41 ]
#define GM_NightVisionFlag    linkvarbuf[ 42 ]
#define GM_ThermalVisionFlag  linkvarbuf[ 43 ]
#define GM_GasMaskFlag        linkvarbuf[ 44 ]
#define GM_BodyArmorFlag      linkvarbuf[ 45 ]
#define GM_KetchupFlag        linkvarbuf[ 46 ]
#define GM_StealthFlag        linkvarbuf[ 47 ]
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
#define GM_BodyTemp           linkvarbuf[ 70 ]
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
    DIFFICULTY_VERY_EASY = -1,
    DIFFICULTY_EASY      = 0,
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
    SNA_STANCE_CROUCH    = 1,
    SNA_STANCE_GROUND    = 2, // prone + knocked down
    SNA_STANCE_UNK       = 3, // first person prone?
    // ... more?
};

enum // GM_Weapons[]
{
    WEAPON_NONE       = -1,
    WEAPON_SOCOM      = 0,
    WEAPON_FAMAS      = 1,
    WEAPON_GRENADE    = 2,
    WEAPON_NIKITA     = 3,
    WEAPON_STINGER    = 4,
    WEAPON_CLAYMORE   = 5,
    WEAPON_C4         = 6,
    WEAPON_STUN_G     = 7,
    WEAPON_CHAFF_G    = 8,
    WEAPON_PSG1       = 9,
};
#define GM_TotalWeapons 10

enum // GM_Items[]
{
    ITEM_NONE       = -1, // types:
    ITEM_CIGS       = 0,  // 0x8000
    ITEM_SCOPE      = 1,  // 0x8003
    ITEM_C_BOX_A    = 2,  // 0x8001
    ITEM_C_BOX_B    = 3,  // 0x8001
    ITEM_C_BOX_C    = 4,  // 0x8001
    ITEM_N_V_G      = 5,  // 0x8000
    ITEM_THERM_G    = 6,  // 0x8000
    ITEM_GASMASK    = 7,  // 0x8000
    ITEM_B_ARMOR    = 8,  // 0x8000
    ITEM_KETCHUP    = 9,  // 0x8000
    ITEM_STEALTH    = 10, // 0x8000
    ITEM_BANDANA    = 11, // 0x8000
    ITEM_CAMERA     = 12, // 0x8003
    ITEM_RATION     = 13, // 0x2000
    ITEM_MEDICINE   = 14, // 0x2000
    ITEM_DIAZEPAM   = 15, // 0x2000
    ITEM_PAL_KEY    = 16, // 0
    ITEM_CARD       = 17, // 0
    ITEM_TIMER_B    = 18, // 0
    ITEM_MINE_D     = 19, // 0
    ITEM_DISC       = 20, // 0
    ITEM_ROPE       = 21, // 0
    ITEM_SCARF      = 22, // 0
    ITEM_SUPPR      = 23  // 0
};
#define GM_TotalItems 24

enum // GM_ItemTypes_8009D598[]
{
    // ...
    ITEMTYPE_CONSUMABLE = 0x2000,
    // ...
};
//------------------------------------------------------------------------------

#define GM_LinkVar(buf, var)      (buf[((short*)&var - (short*)&linkvarbuf)])

#define GM_CurrentWeapon          (GM_Weapons[ GM_CurrentWeaponId ])
#define GM_CurrentItem            (GM_Items[ GM_CurrentItemId ])

#endif