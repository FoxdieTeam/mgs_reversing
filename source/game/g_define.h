#ifndef __MGS_G_DEFINE_H__
#define __MGS_G_DEFINE_H__

// private to target.c
#define TARGET_MAX 64

// private to homing.c
#ifdef VR_EXE
#define HOMING_MAX 64
#else
#define HOMING_MAX 8
#endif

/*---------------------------------------------------------------------------*/

typedef enum {
    PLAYER_WATCH = 0x1,
    PLAYER_INTRUDE = 0x2, // Crawling in forced first person
    PLAYER_ACT_ONLY = 0x4,
    PLAYER_NORMAL_WATCH = 0x8, //first person can l r peek
    PLAYER_MOVE = 0x10,
    PLAYER_SQUAT = 0x20,
    PLAYER_GROUND = 0x40,
    // stops movement and actions. - item/weap switching + pause/radio still available
    PLAYER_NOT_PLAYABLE = 0x80,
    // hit flinch, step on claymore
    PLAYER_DAMAGED = 0x100,
    // knocked down related
    PLAYER_DOWNED = 0x200,
    // cleared leaving first person
    PLAYER_STILL_WATCH = 0x400,
    PLAYER_ATTACK = 0x800,
    PLAYER_CB_BOX = 0x1000,
    // triggers game over when set. could this be the 'dead' flag?
    PLAYER_GAME_OVER = 0x2000,
    // anther first person flag
    PLAYER_INVISIBLE = 0x4000,
    PLAYER_MENU_DISABLE = 0x8000,
    PLAYER_CAUTION = 0x10000, //on wall
    PLAYER_CHECK_WALL = 0x20000, //knocking
    PLAYER_MOVE_WATCH = 0x40000,
    PLAYER_TIMERBOMB_THROWN = 0x80000,
    PLAYER_KETCHUP = 0x100000,
    PLAYER_ITEM_DISABLE = 0x200000,
    PLAYER_WEAPON_DISABLE = 0x400000,
    PLAYER_INVINCIBLE = 0x800000,
    PLAYER_IN_THE_WATER = 0x1000000,
    PLAYER_HIDDEN = 0x2000000,
    // in level transition / mini cutscene, level transition duct
    PLAYER_NOT_SIGHT = 0x4000000,
    PLAYER_SECOND_CONTROLLER = 0x8000000, //using second controller
    PLAYER_SECOND_AVAILABLE = 0x10000000, //can use second controller
    // stops movement, actions, and item/weap switching. - pause/radio still available
    PLAYER_PAD_OFF = 0x20000000,
    // Set from sna_check_dead_8004E384() and sna_anim_dying_80055524().
    PLAYER_NOHIDDEN = 0x40000000, //dead or dying
    PLAYER_DEBUG = 0x80000000,
} PlayerStatusFlag;

/*---------------------------------------------------------------------------*/

#define GAME_FLAG_BIT_07 0x40    // set for camera change
#define GAME_FLAG_BIT_08 0x80    // cleared when unpausing, never set though
#define GAME_FLAG_BIT_09 0x100   // not set anywhere, used in bullet.c
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
#endif // __MGS_G_DEFINE_H__
