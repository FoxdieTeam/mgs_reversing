#ifndef _GAME_H_
#define _GAME_H_

#include "common.h"
#include "charadef.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "libhzd/libhzd.h"
#include "control.h"
#include "target.h"
#include "Menu/menuman.h"
#include "motion.h"
#include "strctrl.h"
//#include "linkvarbuf.h"
#include "SD/sd_cli.h"
#include "SD/g_sound.h"

enum GAMED_STATE {          // private to gamed.c
    WAIT_LOAD   = 0,
    WORKING     = 1
};

typedef struct GameWork     // private to gamed.c
{
    GV_ACT  actor;
    int     status;         // enum GAMED_STATE
    int     field_24;       // killing_count (?)
} GameWork;

#define DG_MAX_JOINTS 24

typedef struct _OBJECT
{
    DG_OBJS        *objs;
    u_long          flag;
    MATRIX         *light;
    u_short         map_name;
    short           action;
    short           action2; // for override actions
    MOTION_CONTROL *m_ctrl;
    short           height;
    short           is_end;
    short           time2;   // for override actions, why not is_end2?
    u_long          pad;     // unused
    SVECTOR         rots[DG_MAX_JOINTS];
} OBJECT;

typedef struct _OBJECT_NO_ROTS
{
    DG_OBJS        *objs;
    u_long          flag;
    MATRIX         *light;
    u_short         map_name;
    short           action;
    short           action2; // for override actions
    MOTION_CONTROL *m_ctrl;
    short           height;
    short           is_end;
    short           time2;   // for override actions, why not is_end2?
    u_long          pad;     // unused
} OBJECT_NO_ROTS;

typedef int (*TBombFunction)(CONTROL *, int, int *);
typedef int (*TBombFunction2)(int, CONTROL *, int *);
typedef int (*TBombFunction3)(TARGET *, int);
typedef int (*TPlayerActFunction)(GV_ACT *);

typedef enum
{
    PLAYER_FIRST_PERSON = 0x1,
    PLAYER_INTRUDE = 0x2, // Crawling in forced first person
    PLAYER_ACT_ONLY = 0x4,
    PLAYER_FIRST_PERSON_CAN_LR_PEEK = 0x8,
    PLAYER_MOVING = 0x10,
    PLAYER_SQUAT = 0x20,
    PLAYER_GROUND = 0x40,
    // stops movement and actions. - item/weap switching + pause/radio still available
    PLAYER_UNK80 = 0x80,
    // hit flinch, step on claymore
    PLAYER_UNK100 = 0x100,
    // knocked down related
    PLAYER_UNK200 = 0x200,
    // cleared leaving first person
    PLAYER_UNK400 = 0x400,
    PLAYER_PREVENT_FIRST_PERSON = 0x800,
    PLAYER_CB_BOX = 0x1000,
    // triggers game over when set. could this be the 'dead' flag?
    PLAYER_GAMEOVER = 0x2000,
    // anther first person flag
    PLAYER_UNK4000 = 0x4000,
    PLAYER_PREVENT_WEAPON_ITEM_SWITCH = 0x8000,
    PLAYER_ON_WALL = 0x10000,
    PLAYER_KNOCKING = 0x20000,
    PLAYER_UNK40000 = 0x40000,
    PLAYER_THROWING = 0x80000,
    PLAYER_UNK100000 = 0x100000,
    PLAYER_PREVENT_ITEM_SWITCH = 0x200000,
    PLAYER_PREVENT_WEAPON_SWITCH = 0x400000,
    PLAYER_INVULNERABLE = 0x800000,
    PLAYER_UNDERWATER = 0x1000000,
    PLAYER_UNK2000000 = 0x2000000,
    // in level transition / mini cutscene, level transition duct
    PLAYER_UNK4000000 = 0x4000000,
    PLAYER_USING_CONTROLLER_PORT_2 = 0x8000000,
    PLAYER_CAN_USE_CONTROLLER_PORT_2 = 0x10000000,
    // stops movement, actions, and item/weap switching. - pause/radio still available
    PLAYER_PAD_OFF = 0x20000000,
    // Set from sna_check_dead_8004E384() and sna_anim_dying_80055524().
    PLAYER_DEADORDYING = 0x40000000,
    PLAYER_UNK80000000 = 0x80000000,
} PlayerStatusFlag;

enum {
	GM_SEMODE_NORMAL,
	GM_SEMODE_BOMB,
	GM_SEMODE_REAL,
	GM_SEMODE_CAMERA
} ;

#define GAME_FLAG_BIT_07 0x40    // set for camera change
#define GAME_FLAG_BIT_08 0x80    // cleared when unpausing, never set though
#define GAME_FLAG_BIT_09 0x100   // not set anywhere, used in bullet.c
#define GAME_FLAG_BIT_13 0x1000  // enables menu when STATE_VOX_STREAM is set
#define GAME_FLAG_BIT_19 0x40000 // hides all items/weapons in the menu

enum // GM_GameStatus
{
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
#ifndef __BSSDEFINE__
extern int     GM_CurrentMap;
extern int     GM_NoisePower;
extern int     GM_NoiseLength;
extern SVECTOR GM_NoisePosition;

static inline void GM_SetNoise( int power, int length, SVECTOR *pos )
{
    int old = GM_NoisePower;
    if (power < old)
        return;
    if (power == old && length < GM_NoiseLength)
        return;

    GM_NoisePower = power;
    GM_NoiseLength = length;
    GM_NoisePosition = *pos;
}

extern int GM_GameStatus;
static inline void GM_Sound( int x_pos, int y_pos, int se_id )
{
    int mask_id;
    if (!(GM_GameStatus & (STATE_GAME_OVER | STATE_DEMO)))
    {
        x_pos &= 0xff;
        y_pos &= 0xff;
        if (y_pos > 63)
        {
            y_pos = 63;
        }
        mask_id = se_id & 0xff;
        sd_set_cli( (x_pos << 16 | y_pos << 8 | mask_id), SD_ASYNC );
    }
}

static inline void GM_FreePrim( DG_PRIM *prim )
{
    if ( prim != NULL ) {
        DG_DequeuePrim( prim ) ;
        DG_FreePrim( prim ) ;
    }
}

static inline void GM_ConfigPrimRoot( DG_PRIM *prim, OBJECT *obj, int unit )
{
    prim->root = &( obj->objs->objs[ unit ].world ) ;
}

static inline void GM_SetCurrentMap( int map )
{
    GM_CurrentMap = map;
}

static inline int GM_GetCurrentMap()
{
    return GM_CurrentMap;
}

static inline void GM_SetAlertMax( int alert )
{
    extern int GM_AlertMax;
    if ( GM_AlertMax < alert )
    {
        GM_AlertMax = alert;
    }
}

/*
//not used anywhere yet
static  inline  void    GM_SetAlert( alert )
int                     alert ;
{
        if ( alert > 256 ) alert = 256 ;
        if ( alert > GM_AlertMax ) GM_AlertMax = alert ;
}
*/

#endif // __BSSDEFINE__
/*---------------------------------------------------------------------------*/

/* gamed.c */
extern int GM_GameStatus;
extern int GM_LoadRequest;
extern int GM_GameOverTimer;
extern SVECTOR *GM_lpsvectWind;
extern TPlayerActFunction GM_lpfnPlayerActControl;
extern TPlayerActFunction GM_lpfnPlayerActObject2;
extern short GM_uBombHoming;
extern short GM_uTenageMotion;
extern TBombFunction  GM_lpfnBombHoming;
extern TBombFunction2 GM_lpfnBombBound;
extern TBombFunction3 GM_lpfnBombExplosion;
extern int GM_PadResetDisable;

void GM_InitReadError(void);
void DrawReadError(void);
void GM_SetSystemCallbackProc(int index, int proc);
void GM_CallSystemCallbackProc(int id, int arg);
void GM_SetLoadCallbackProc(int);
void GM_ContinueStart(void);
void GM_GameOver(void);
void GM_StartDaemon(void);

/* script.c */
int  GM_InitBinds(void);
void GM_InitScript(void);

/* area.c */
void GM_InitArea(void);
void GM_GetAreaHistory(AreaHistory *pHistoryCopy);
void GM_SetAreaHistory(AreaHistory *pNewHistory);
int  GM_SetArea(int stage_id, char *stage_name);
int  GM_AreaHistory(int stage_id);
char *GM_GetArea(int flag);

/* chara.c */
void GM_InitChara(void);
void GM_ResetChara(void);
NEWCHARA GM_GetChara(unsigned char *script);
NEWCHARA GM_GetCharaID(int chara_id);

/* alert.c */
void sub_8002E508(int a1);
void sub_8002E544(int param_1);
void GM_SetNoiseSound(int arg0);
int  GM_GetNoiseSound(int arg0, int arg1);
void GM_SoundStart(void);
void GM_Command_sound_impl(void);
void GM_Act_helper2(void);
void GM_AlertAct(void);
void GM_AlertModeSet(int a1);
void GM_AlertModeInit(void);
void GM_AlertModeReset(void);

/* sound.c */
void GM_SeSet(SVECTOR *pos, unsigned int se_id);
void GM_SeSet2(int x_pos, int y_pos, int se_id);
void GM_SeSetMode( SVECTOR *pos, int se_id, int mode );
void GM_SeSet3(int x_pos, int y_pos, int se_id);
void sub_80032B40(SVECTOR *svec, unsigned int se_id, int y_pos);
void sub_80032BC4(SVECTOR *svec, unsigned int se_id, int param_3);
void GM_SetSound(int sound_code, int sync_mode);

/* motion.c */
int  GM_ConfigMotionControl(OBJECT *object, MOTION_CONTROL *m_ctrl, int name,
                            MOTION_SEGMENT *m_segs1, MOTION_SEGMENT *m_segs2,
                            CONTROL *control, SVECTOR *rots);
int  GM_ConfigMotionAdjust(OBJECT *object, SVECTOR *adjust);

/* unsorted stuff */
void GM_ExitBehindCamera_80030AEC(void);
void GM_CheckBehindCamera(HZD_HDL *map, CONTROL *control);
void GM_Reset_helper3_80030760();

void sub_800309B4(int param_1, int param_2);
void sub_8002EBE8(SVECTOR *param_1, int param_2); // camera something
void sub_8002EADC(int);

void sub_8002EC8C(SVECTOR*, SVECTOR*, SVECTOR*);
void GM_CameraEventReset(void);

void            GM_CameraSetBounds_80030888(SVECTOR *vec1, SVECTOR *vec2, int param_3_bool);
void            GM_CameraSetLimits_800308E0(SVECTOR *vec1, SVECTOR *vec2, int param_3_bool);
void            GM_CameraSetRotation_80030938(SVECTOR *pVec);
void            GM_CameraSetTrack_80030980(int param_1);
unsigned int    GM_Command_menu_helper_8002CA48(void);

#endif // _GAME_H_
