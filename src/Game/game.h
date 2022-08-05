#ifndef GAME_H
#define GAME_H

#include "linker.h"
#include "libdg/libdg.h"
#include "libgv/actor.h"
#include "Game/GM_Control.h"
#include "map/hzd.h"

typedef struct Actor_GM_Daemon
{
    Actor field_0;
    int   field_20;
    int   field_24;
} Actor_GM_Daemon;

typedef struct _MOTION_CONTROL
{
    void           *field_00_oar_ptr; // 0x00
    unsigned short  field_04;         // 0x04
    unsigned short  field_06;
    unsigned short  field_08; // 0x08
    unsigned short  field_0A;
    unsigned long   field_0C; // 0x0C
    unsigned long   field_10; // 0x10
    unsigned short  field_14; // 0x14
    unsigned short  field_16;
    short           field_18; // 0x18
    unsigned short  field_1A; // 0x1A
    unsigned short  field_1C; // 0x1C
    unsigned short  field_1E;
    unsigned short  field_20; // 0x20
    unsigned short  field_22;
    unsigned long   field_24; // 0x24
    unsigned long   field_28; // 0x28
    unsigned short  field_2C; // 0x2C
    unsigned short  field_2E;
    unsigned short  field_30; // 0x30
    unsigned short  field_32; // 0x32
    SVECTOR        *field_34; // 0x34
    SVECTOR        *step;     // 0x38
    unsigned short *field_3C; // 0x3C
    unsigned long   interp;   // 0x40
    SVECTOR         field_44;
    SVECTOR        *field_4C;
    // todo: padding field here?
} MOTION_CONTROL;

typedef struct _OBJECT
{
    DG_OBJS        *objs;        // 0x00
    unsigned long   flag;        // 0x04
    MATRIX         *light;       // 0x08
    unsigned short  map_name;    // 0x0C
    short           action_flag; // 0x0E
    short           field_10;    // 0x10 no match with unsigned in sna_init_8004E260
    unsigned short  field_12;    // 0x12
    MOTION_CONTROL *m_ctrl;      // 0x14
    unsigned short  field_18;    // 0x18
    short           field_1A;    // 0x1A must be signed for sna_init_anim_box_stop_800554B4 to match
    short           field_1C;    // 0x1C
    unsigned short  field_1E;    // 0x1C
    unsigned long   field_20;    // 0x20
    SVECTOR         rots[0];     // 0x24
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

extern int     GM_CurrentMap_800AB9B0;
extern int     GM_NoisePower_800ABA24;
extern int     GM_NoiseLength_800ABA30;
extern SVECTOR GM_NoisePosition_800AB9F8;

typedef enum
{
    PLAYER_STATUS_FIRST_PERSON = 0x1,
    PLAYER_STATUS_FIRST_PERSON_DUCT = 0x2,
    PLAYER_STATUS_UNK4 = 0x4,
    PLAYER_STATUS_FIRST_PERSON_CAN_LR_PEEK = 0x8,
    PLAYER_STATUS_MOVING = 0x10,
    PLAYER_STATUS_CROUCHING = 0x20,
    PLAYER_STATUS_PRONE = 0x40,
    // stops movement and actions. - item/weap switching + pause/radio still available
    PLAYER_STATUS_UNK80 = 0x80,
    // hit flinch, step on claymore
    PLAYER_STATUS_UNK100 = 0x100,
    // knocked down related
    PLAYER_STATUS_UNK200 = 0x200,
    // cleared leaving first person
    PLAYER_STATUS_UNK400 = 0x400,
    PLAYER_STATUS_PREVENT_FIRST_PERSON = 0x800,
    PLAYER_STATUS_UNK1000 = 0x1000,
    // triggers game over when set. could this be the 'dead' flag?
    PLAYER_STATUS_GAMEOVER = 0x2000,
    // anther first person flag
    PLAYER_STATUS_UNK4000 = 0x4000,
    PLAYER_STATUS_PREVENT_WEAPON_ITEM_SWITCH = 0x8000,
    PLAYER_STATUS_ON_WALL = 0x10000,
    PLAYER_STATUS_KNOCKING = 0x20000,
    PLAYER_STATUS_UNK40000 = 0x40000,
    // throw grenade when set, then cleared
    PLAYER_STATUS_UNK80000 = 0x80000,
    PLAYER_STATUS_UNK100000 = 0x100000,
    PLAYER_STATUS_PREVENT_ITEM_SWITCH = 0x200000,
    PLAYER_STATUS_PREVENT_WEAPON_SWITCH = 0x400000,
    PLAYER_STATUS_INVULNERABLE = 0x800000,
    PLAYER_STATUS_UNK1000000 = 0x1000000,
    PLAYER_STATUS_UNK2000000 = 0x2000000,
    // in level transition / mini cutscene, level transition duct
    PLAYER_STATUS_UNK4000000 = 0x4000000,
    PLAYER_STATUS_USING_CONTROLLER_PORT_2 = 0x8000000,
    PLAYER_STATUS_CAN_USE_CONTROLLER_PORT_2 = 0x10000000,
    // stops movement, actions, and item/weap switching. - pause/radio still available
    PLAYER_STATUS_UNK20000000 = 0x20000000,
    // Set from sna_init_check_dead_8004E384() and sna_init_anim_dying_80055524().
    PLAYER_STATUS_DEADORDYING = 0x40000000,
    PLAYER_STATUS_UNK80000000 = 0x80000000,
} PlayerStatusFlag;

enum
{
    WEAPON_NONE = -1,
    WEAPON_SOCOM = 0,
    WEAPON_FAMAS = 1,
    WEAPON_GRENADE = 2,
    WEAPON_NIKITA = 3,
    WEAPON_STINGER = 4,
    WEAPON_CLAYMORE = 5,
    WEAPON_C4 = 6,
    WEAPON_STUNGRENADE = 7,
    WEAPON_CHAFF = 8,
    WEAPON_PSG1 = 9,
};

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
int                sd_set_cli_800887EC(int code, int unused);
static inline void GM_Sound(int byte_2, int byte_1, int byte_0)
{
    int lowest_byte;
    if (!(GM_GameStatus_800AB3CC & 0x84000000))
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

void GM_Sound_80032968(int byte_2, int byte_1, int byte_0);
void GM_SeSet_80032858(SVECTOR *pos, unsigned int sound_id);
void GM_ConfigControlInterp_80026244(GM_Control *pControl, char f5a);
void GM_ConfigObjectOverride_80034D30(OBJECT *obj, int a1, int motion, int interp, int a4);
void GM_ExitBehindCamera_80030AEC(void);
void GM_CheckBehindCamera_80030B3C(HZD_MAP *map, GM_Control *control);
int  GM_ConfigMotionAdjust_80035008(OBJECT *pObj, SVECTOR *adjust);

#endif // GAME_H
