#ifndef GAME_H
#define GAME_H

#include "linker.h"
#include "strctrl.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "control.h"
#include "target.h"
#include "libhzd/libhzd.h"
#include "Menu/menuman.h"
#include "libgcl/libgcl.h"
#include "motion.h"
//#include "linkvarbuf.h"
#include "SD/sd.h"

extern int     GM_CurrentMap_800AB9B0;
extern int     GM_NoisePower_800ABA24;
extern int     GM_NoiseLength_800ABA30;
extern SVECTOR GM_NoisePosition_800AB9F8;

#define ACTOR_LIST_COUNT 9

typedef struct Actor_GM_Daemon
{
    GV_ACT field_0;
    int   field_20;
    int   field_24;
} Actor_GM_Daemon;

#define DG_MAX_JOINTS 24

typedef struct _OBJECT
{
    DG_OBJS        *objs;                // 0x00
    unsigned long   flag;                // 0x04
    MATRIX         *light;               // 0x08
    unsigned short  map_name;            // 0x0C
    short           action_flag;         // 0x0E
    short           field_10;            // 0x10 no match with unsigned in sna_8004E260
    unsigned short  field_12;            // 0x12
    MOTION_CONTROL *m_ctrl;              // 0x14
    short           field_18;            // 0x18
    short           is_end;              // 0x1A must be signed for sna_anim_box_stop_800554B4 to match
    short           field_1C;            // 0x1C
    unsigned short  field_1E;            // 0x1C
    unsigned long   field_20;            // 0x20
    SVECTOR         rots[DG_MAX_JOINTS]; // 0x24
} OBJECT;

typedef struct _OBJECT_NO_ROTS
{
    DG_OBJS        *objs;        // 0x00
    unsigned long   flag;        // 0x04
    MATRIX         *light;       // 0x08
    unsigned short  map_name;    // 0x0C
    unsigned short  action_flag; // 0x0E
    unsigned short  field_10;    // 0x10
    unsigned short  field_12;    // 0x12
    MOTION_CONTROL *m_ctrl;      // 0x14
    unsigned short  field_18;    // 0x18
    unsigned short  field_1A;    // 0x1A
    unsigned short  field_1C;    // 0x1C
    unsigned short  field_1E;    // 0x1C
    unsigned long   field_20;    // 0x20
} OBJECT_NO_ROTS;

typedef int (*TBombFunction)(CONTROL *, int, int *);
typedef int (*TBombFunction2)(int, CONTROL *, int *);
typedef int (*TBombFunction3)(TARGET *, int);
typedef int (*TPlayerActFunction)(GV_ACT *);

// Missing flags with unknown value: PLAYER_ACT_ONLY, PLAYER_INTRUDE
typedef enum
{
    PLAYER_FIRST_PERSON = 0x1,
    PLAYER_FIRST_PERSON_DUCT = 0x2,
    PLAYER_UNK4 = 0x4,
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
    PLAYER_UNK1000000 = 0x1000000,
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

enum // GM_GameStatus_800AB3CC
{
    //STATE_ENEMY_OFF = 0x200,
    STATE_RADAR_ON = 0x800,
    // ...
    STATE_PADRELEASE = 0x10000000,
};

//sound
#define SE_PINNUKI 0x2C

static inline void GM_SetNoise(int power, int length, SVECTOR *pos)
{
    int old = GM_NoisePower_800ABA24;
    if (power < old)
        return;
    if (power == old && length < GM_NoiseLength_800ABA30)
        return;

    GM_NoisePower_800ABA24 = power;
    GM_NoiseLength_800ABA30 = length;
    GM_NoisePosition_800AB9F8 = *pos;
}

extern int         GM_GameStatus_800AB3CC;
static inline void GM_Sound(int byte_2, int byte_1, int byte_0)
{
    int lowest_byte;
    if (!(GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_27 | GAME_FLAG_BIT_32)))
    {
        byte_2 &= 0xff;
        byte_1 &= 0xff;
        if (0x3f < byte_1)
        {
            byte_1 = 0x3f;
        }
        lowest_byte = byte_0 & 0xff;
        sd_set_cli_800887EC(byte_2 << 0x10 | byte_1 << 8 | lowest_byte, 0);
    }
}

static inline void GM_FreePrim( DG_PRIM *prim )
{
    if ( prim != 0  ) {
        DG_DequeuePrim_800182E0( prim ) ;
        DG_FreePrim_8001BC04( prim ) ;
    }
}

static inline void GM_ConfigPrimRoot( DG_PRIM *prim, OBJECT *obj, int unit )
{
    prim->root = &( obj->objs->objs[ unit ].world ) ;
}

static inline void GM_SetCurrentMap(int map)
{
    GM_CurrentMap_800AB9B0 = map;
}

static inline int GM_GetCurrentMap()
{
    return GM_CurrentMap_800AB9B0;
}

static inline void GM_SetAlertMax( int alert )
{
    extern int GM_AlertMax_800AB9E0;
    if ( GM_AlertMax_800AB9E0 < alert )
    {
        GM_AlertMax_800AB9E0 = alert;
    }
}

/*
//not used anywhere yet
static  inline  void    GM_SetAlert( alert )
int         alert ;
{
    if ( alert > 256 ) alert = 256 ;
    if ( alert > GM_AlertMax ) GM_AlertMax = alert ;
}
*/

void               GM_Act_8002ADBC(Actor_GM_Daemon *work);
void               GM_InitArea_8002A704(void);
void               GM_InitChara_8002A890();
void               GM_InitScript_8002D1DC(void);
void               GM_Reset_8002ABF4(Actor_GM_Daemon *work);
void               GM_ResetMemory_8002AA80(void);
void               GM_ClearWeaponAndItem_8002A960();
void               GV_SaveResidentTop_800163C4(void);
void               GM_CreateLoader_8002AAB0();
void               GM_Sound_80032C48(int code, int notUsed);
void               GM_SeSet2_80032968(int byte_2, int byte_1, int byte_0);
void               GM_SeSet_80032858(SVECTOR *pos, unsigned int sound_id);
void               GM_Sound_800329C4( SVECTOR *arg0, int arg1, int arg2 );
void               sub_80032BC4(SVECTOR *svec, unsigned int param_2, int param_3);
void               GM_ConfigControlInterp_80026244(CONTROL *pControl, char f5a);
int                GM_CheckControlTouches_8002624C(CONTROL *pControl, int param_2);
void               GM_ConfigObjectOverride_80034D30(OBJECT *obj, int a1, int motion, int interp, int a4);
void               GM_ExitBehindCamera_80030AEC(void);
void               GM_CheckBehindCamera_80030B3C(HZD_HDL *map, CONTROL *control);
int                GM_ConfigMotionAdjust_80035008(OBJECT *pObj, SVECTOR *adjust);
char              *GM_GetArea_8002A880(int unused);
int                GM_SetArea_8002A7D8(int stage_id, char *pStageName);
void               GM_ConfigControlHazard_8002622C(CONTROL *pControl, short height, short f36, short f38);
int                GM_StreamStatus_80037CD8(void);
void               GM_CallSystemCallbackProc_8002B570(int id, int arg);
void               GM_ConfigControlString_800261C0(CONTROL *pControl, char *bReadVec1, char *bReadVec2);
void               GM_ConfigObjectSlide_80034CC4(OBJECT *obj);
void               GM_ReshadeObjs_80031660(DG_OBJS *pObj);
void               GM_StartDaemon_8002B77C();
void               GM_ConfigControlAttribute_8002623C(CONTROL *pControl, int f3a);
void               GM_ConfigControlMatrix_80026154(CONTROL *pControl, MATRIX *pMatrix);
void               GM_ConfigObjectStep_80034C54(OBJECT *obj, SVECTOR *step);
void               GM_ConfigObjectJoint_80034CB4(OBJECT *obj);
void               GM_ConfigControlTrapCheck_80026308(CONTROL *pControl);
void               GM_AlertModeInit_8002EAA8(void);
void               GM_InitWhereSystem_8002597C(void);
void               GM_Reset_helper_8002A978();
void               GM_Reset_helper3_80030760();
void               GM_GetAreaHistory_8002A730(AreaHistory *pHistoryCopy);
void               GM_SetAreaHistory_8002A784(AreaHistory *pNewHistory);
int                GM_AreaHistory_8002A848(int stage_id);
void               GM_SoundStart_8002E640(void);
void               GM_set_noise_sound_8002E588(int arg0);
Actor_strctrl      *GM_VoxStream_80037E40(int voxCode, int proc);
void               GM_InitReadError_8002AC44();
void               GM_SetSystemCallbackProc_8002B558(int index, int proc);
void               GM_ResetChara_8002A8B0(void);
void               GM_ControlRemove_80025904(CONTROL *pControl);
TGCL_ActorCreateFn GM_GetCharaID_8002A8EC(int chara_id);
void               GM_AlertAct_8002E91C(void);
void               GM_StreamPlayStop_80037D64(void);
void               GM_AlertModeReset_8002EAB8(void);
void               GM_AlertModeSet_8002EA68(int a1);
void               GM_ContinueStart_8002B62C(void);
void               GM_GameOver_8002B6C8(void);
GV_MSG            *GM_CheckMessage_8002631C(GV_ACT *pActor, int msgType, int toFind);
int                GM_GetNoiseSound_8002E614(int arg0, int arg1);
void               sub_80032AEC(int byte_2, int byte_1, int byte_0);

HZD_TRP *HZD_CheckBehindTrap_8002A5E0(HZD_HDL *pHzdMap, CONTROL *pControl);

// SeSet helpers
int sub_80032748(DVECTOR *out, SVECTOR *pos);
int sub_800327BC(DVECTOR *out, SVECTOR *pos);
int sub_80032820(DVECTOR *out, SVECTOR *pos);
int sub_800326D4(DVECTOR *out, SVECTOR *pos);
int sub_80032308(SVECTOR *pos, int param_2, DVECTOR *out);
int sub_800321F8(SVECTOR *pos, int param_2, DVECTOR *out);
int sub_80032420(SVECTOR *pos, int param_2, DVECTOR *out);
int sub_80032534(SVECTOR *pos, int param_2, DVECTOR *out);
int sub_8003265C(DVECTOR *param_1, SVECTOR *param_2, int param_3);

void sub_800309B4(int param_1, int param_2);
void sub_8002EBE8(SVECTOR *param_1, int param_2); // camera something
void sub_8002E508(int a1);
void sub_8002B600(int);
void GM_HidePauseScreen_8002AAEC();
void sub_8002EADC(int);
void GM_ResetSystem_8002AA48(void);
void sub_8002EC8C(SVECTOR*, SVECTOR*, SVECTOR*);
void GM_ShowPauseScreen_8002AB40();
void GM_Act_helper_8002AA10(void); // noise/alert thing
void GM_TogglePauseScreen_8002ABA4(void);
void GM_Act_helper2_8002E8D4(void);
void GM_ActControl_80025A7C(CONTROL *pControl);
void GM_CameraEventReset_800309A8(void);
int  GM_ConfigMotionControl_80034F08(OBJECT *pObj, MOTION_CONTROL *pMCtrl, int name, OAR_RECORD *a4, OAR_RECORD *a5, CONTROL *pCtrl, SVECTOR *rots);

int GM_InitLoader_8002599C(CONTROL *pControl, int scriptData, int scriptBinds);

#endif // GAME_H
