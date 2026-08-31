#ifndef __MGS_G_DEFINE_H__
#define __MGS_G_DEFINE_H__

#ifndef __MGS_GAME_H__
#error "g_define.h must be included via game.h!"
#endif

// private to target.c
#define TARGET_MAX 64

// private to homing.c
#ifdef VR_EXE
#define HOMING_MAX 64
#else
#define HOMING_MAX 8
#endif

/*---------------------------------------------------------------------------*/

// GM_PlayerStatus
typedef enum {
    PLAYER_NORMAL               = 0x0000,
    PLAYER_WATCH                = 0x0001,       /* 1st-person */
    PLAYER_INTRUDE              = 0x0002,       /* Intrusion mode */
    PLAYER_ACT_ONLY             = 0x0004,
    PLAYER_NORMAL_WATCH         = 0x0008,       /* 1st-person (can peek left/right) */
    PLAYER_MOVE                 = 0x0010,       /* On the move */
    PLAYER_SQUAT                = 0x0020,       /* Crouching */
    PLAYER_GROUND               = 0x0040,       /* Crawling, downed */
    PLAYER_NOT_PLAYABLE         = 0x0080,
    PLAYER_DAMAGED              = 0x0100,
    PLAYER_DOWNED               = 0x0200,
    PLAYER_STILL_WATCH          = 0x0400,
    PLAYER_ATTACK               = 0x0800,
    PLAYER_CB_BOX               = 0x1000,
    PLAYER_GAME_OVER            = 0x2000,
    PLAYER_INVISIBLE            = 0x4000,
    PLAYER_MENU_DISABLE         = 0x8000,
    PLAYER_CAUTION              = 0x00010000,   /* Sticking (to the wall) */
    PLAYER_CHECK_WALL           = 0x00020000,   /* Knocking (on the wall) */
    PLAYER_MOVE_WATCH           = 0x00040000,
    PLAYER_TIMERBOMB_THROWN     = 0x00080000,
    PLAYER_KETCHUP              = 0x00100000,
    PLAYER_ITEM_DISABLE         = 0x00200000,
    PLAYER_WEAPON_DISABLE       = 0x00400000,
    PLAYER_INVINCIBLE           = 0x00800000,
    PLAYER_IN_THE_WATER         = 0x01000000,
    PLAYER_HIDDEN               = 0x02000000,
    PLAYER_NOT_SIGHT            = 0x04000000,
    PLAYER_SECOND_CONTROLLER    = 0x08000000,
    PLAYER_SECOND_AVAILABLE     = 0x10000000,
    PLAYER_PAD_OFF              = 0x20000000,
    PLAYER_NOHIDDEN             = 0x40000000,
    PLAYER_DEBUG                = 0x80000000,   /* Debug mode */
} PlayerStatusFlag;

/*---------------------------------------------------------------------------*/

#define GAME_FLAG_BIT_07 0x40    // set for camera change
#define GAME_FLAG_BIT_08 0x80    // cleared when unpausing, never set though
#define GAME_FLAG_BIT_09 0x100   // set by s12c dog.c, used in bullet.c
#define GAME_FLAG_BIT_13 0x1000  // enables menu when STATE_VOX_STREAM is set
#define GAME_FLAG_BIT_19 0x40000 // hides all items/weapons in the menu

/*---------------------------------------------------------------------------*/

// GM_GameStatus
enum {
    STATE_CHAFF = 0x1,
    STATE_STUN = 0x2,
    STATE_NVG = 0x4,
    STATE_THERMG = 0x8,
    STATE_BEHIND_CAMERA = 0x10,
    STATE_VOX_STREAM = 0x20,
    // ...
    STATE_ENEMY_OFF = 0x200,
    STATE_TAKING_PHOTO = 0x400,
    STATE_JPEGCAM = 0x800,
    // ...
    STATE_RADIO_OFF = 0x2000,
    STATE_PAUSE_OFF = 0x4000,
    STATE_SHOW_LIFEBAR = 0x8000,
    STATE_HIDE_LIFEBAR = 0x10000,
    STATE_LIFEBAR_OFF = 0x20000,
    // ...
    STATE_MENU_OFF = 0x80000,
    STATE_SHOW_RADAR = 0x100000,
    STATE_HIDE_RADAR = 0x200000,
    STATE_RADAR_OFF = 0x400000,
    STATE_JAMMING = 0x800000, // "Snake, you can't use the radar in an area with strong harmonic resonance" (Mei Ling)
    STATE_DEMO_VERBOSE = 0x1000000,
    STATE_DAMAGED = 0x2000000,
    STATE_GAME_OVER = 0x4000000,
    STATE_PADMASK = 0x8000000,
    STATE_PADRELEASE = 0x10000000,
    STATE_NOSLOW = 0x20000000,
    STATE_PADDEMO = 0x40000000,
    STATE_DEMO = 0x80000000,
};

#define STATE_ALL_OFF    ( STATE_RADAR_OFF | STATE_MENU_OFF | STATE_LIFEBAR_OFF | STATE_PAUSE_OFF | STATE_RADIO_OFF )  // 0x4A6000
#define STATE_PAUSE_ONLY ( STATE_RADAR_OFF | STATE_MENU_OFF | STATE_LIFEBAR_OFF | STATE_RADIO_OFF )                    // 0x4A2000

/*---------------------------------------------------------------------------*/
// clang-format off

enum {
    CTRL_SKIP_MESSAGE = 0x01,
    CTRL_SKIP_TRAP = 0x02,
    CTRL_SKIP_NEAR_CHECK = 0x04,
    CTRL_BOTH_CHECK = 0x08,
};

enum {
    NO_SIDE = 0,            /**/
    PLAYER_SIDE = 1,        /**/
    ENEMY_SIDE = 2,         /**/
    BOTH_SIDE = 3           /**/
} ;

enum {
    TARGET_STALE = 0,       /**/
    TARGET_AVAIL = 1,       /**/
    TARGET_CAPTURE = 2,     /**/
    TARGET_POWER = 4,       /**/
    TARGET_PUSH = 8,        /**/
    TARGET_SEEK = 16,       /**/
    TARGET_DOWN = 32,       /**/
    TARGET_C4 = 64,         /**/
    TARGET_TOUCH = 128,     /**/
    TARGET_PUSH_OVER = 256, /**/
    TARGET_NO_LOCKON = 512,
    TARGET_C4_CLEAR = 1024, /**/
    TARGET_DIE = 0x800,     /**/
} ;

#if 0
enum {
    POWER_SPREAD = 0,       /**/
    POWER_MISSILE = 1,      /**/
    POWER_LASER = 2,        /**/
    POWER_WAVE = 3,         /**/

    POWER_????????????? 
} ;
#endif
enum {
    POWER_ONCE      = 0,
    POWER_DECREASE  = 1,
    POWER_THRESHOLD = 2,
    POWER_CONST     = 3,
    POWER_EXPLODE   = 4,
};

// TODO: BULLET_* enum goes here.

enum {
	GM_SEMODE_NORMAL,
	GM_SEMODE_BOMB,		/**/
	GM_SEMODE_REAL,		/**/
	GM_SEMODE_CAMERA	/**/
} ;

enum {
    GM_DEBUGP2MODE_NONE = 0,        /**/
    GM_DEBUGP2MODE_CAMERA = 1,      /**/
    GM_DEBUGP2MODE_MODEL = 2,       /**/
//  GM_DEBUGP2MODE_???
};

// clang-format on
/*---------------------------------------------------------------------------*/

// radar_attr
enum {
    RADAR_OFF     = 0,
    RADAR_VISIBLE = 0x1,  // Enables dot at entity position
    RADAR_SIGHT   = 0x4,  // Enables vision cone for entities
    RADAR_ALL_MAP = 0x8,
    RADAR_NOISE   = 0x10, // Enables noise at position on radar (e.g. DARPA Chief)
    RADAR_UNK1    = 0x20, // Extends distance before entity is no longer drawn on the radar?
    RADAR_UNK2    = 0x40, // Enables RADAR_SIGHT if within certain height of Snake?
    RADAR_UNK4    = 0x1000,
    RADAR_UNK3    = 0x2000,
};

// GM_AlertMode
enum {
    ALERT_OFF = 0,
    ALERT_JAMMING = 1,
    ALERT_EVASION = 2,
    ALERT_ACTIVE = 3
};

enum {
    ATK_BLAST = 0x2,
};

/*---------------------------------------------------------------------------*/

// GM_GameLevel
enum {
    GM_LEVEL_VERYEASY = -1, // added for MGS:INTEGRAL
    GM_LEVEL_EASY      = 0, // the Japanese version's original (only) difficulty
    GM_LEVEL_NORMAL    = 1,
    GM_LEVEL_HARD      = 2,
    GM_LEVEL_EXTREME   = 3,
};

/*---------------------------------------------------------------------------*/

// GM_Configuration
enum {
    GM_CONFIG_BUTTON_TYPE_A  = 0x0000,
    GM_CONFIG_BUTTON_TYPE_B  = 0x0001,
    GM_CONFIG_BUTTON_TYPE_C  = 0x0002,
    GM_CONFIG_BUTTON_MASK    = 0x0007,
    GM_CONFIG_UNKNOWN_0008   = 0x0008,
    GM_CONFIG_UNKNOWN_0010   = 0x0010,
    GM_CONFIG_TUXEDO         = 0x0020, // + Red Ninja, Sneaking Suit Meryl
    GM_CONFIG_ENGLISH        = 0x0100, // 0: Japanese, 1: English
    GM_CONFIG_VIBRATION_OFF  = 0x0400,
    GM_CONFIG_RADAR_OFF      = 0x0800,
    GM_CONFIG_SHUKAN_REVERSE = 0x1000,
    GM_CONFIG_UNKNOWN_2000   = 0x2000,
    GM_CONFIG_CAPTION_OFF    = 0x4000,
    GM_CONFIG_SOUND_MONAURAL = 0x8000,
};

/*---------------------------------------------------------------------------*/

enum // GM_StatusEvent
{
    EV_CommonCold   = 0x1,
    EV_Tranquilizer = 0x4,
    EV_BlownUp      = 0x8,
};

/*---------------------------------------------------------------------------*/

// GM_PlayerStance
enum {
    STAND   = 0,
    CROUCH  = 1, /* Should be SQUAT but that conflicts with the quaternion struct name */
    GROUND  = 2,
    INTRUDE = 3,
};

/*---------------------------------------------------------------------------*/

// GM_Weapons
enum {
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
    WP_Max              = 10,
};

/*---------------------------------------------------------------------------*/

// GM_Items
enum {
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
    IT_Suppressor       = 23,   // 0
    IT_Max              = 24,
};

/*---------------------------------------------------------------------------*/

// GM_ItemTypes
enum {
    // ...
    IT_TYPE_CONSUMABLE = 0x2000,
    IT_TYPE_BITMASK    = 0x4000, // unused
    IT_TYPE_DISABLED   = 0x8000,
};

/*---------------------------------------------------------------------------*/
#endif // __MGS_G_DEFINE_H__
