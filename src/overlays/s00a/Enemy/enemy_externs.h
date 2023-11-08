#include "enemy.h"

// Those extern declarations can't be in enemy.h since
// overlay_bss.c includes that header and if there are
// externs before "int SECTION("overlay.bss") s00a_dword_800E0C9C;"
// (and others) declarations, BSS order is messed up.

extern int                     s00a_dword_800C3328[8];

extern SVECTOR                 ENEMY_TARGET_SIZE_800C35A4;
extern SVECTOR                 ENEMY_TARGET_FORCE_800C35AC;
extern SVECTOR                 ENEMY_ATTACK_SIZE_800C35B4;
extern SVECTOR                 ENEMY_ATTACK_FORCE_800C35BC;
extern SVECTOR                 ENEMY_TOUCH_SIZE_800C35C4;
extern SVECTOR                 ENEMY_TOUCH_FORCE_800C35CC;
extern SVECTOR                 COM_NO_POINT_800C35D4;

extern int                     dword_800E01F4;

extern const char              aCom_noisemode_disD_800E0940[]; // COM_NOISEMODE_DIS =%d \n
extern const char              aEeeDDDTD_800E095C[];           //eee %d %d %d t %d \n

extern int                     s00a_dword_800E0CA0;
extern GM_Camera               s00a_dword_800E0CB0;
extern int                     s00a_dword_800E0D2C;
extern int                     s00a_dword_800E0D30;
extern SVECTOR                 s00a_dword_800E0D38;
extern int                     COM_PlayerOnZone_800E0D40;
extern int                     COM_NoiseMinDisID_800E0D44;

extern int                     COM_SHOOTRANGE_800E0D88;
extern int                     COM_EYE_LENGTH_800E0D8C;
extern int                     COM_PlayerAddress_800E0D90;
extern unsigned int            ENE_SPECIAL_FLAG_800E0D94;


extern ENEMY_COMMAND           EnemyCommand_800E0D98;

//extern int                   EC_MODE_800E0DB0; // EC_MODE, direct access to EnemyCommand struct member

extern int                     COM_PlayerMap_800E0F1C;
extern TOPCOMMAND_STRUCT       TOPCOMMAND_800E0F20;
extern TOPCOMMAND_STRUCT       s00a_dword_800E0F28;
extern SVECTOR                 COM_PlayerPosition_800E0F30;
extern int                     COM_NOISEMODE_DIS_800E0F38;
extern unsigned int            COM_GameStatus_800E0F3C;

extern int                     COM_PlayerAddressOne_800E0F40[8];
extern SVECTOR                 COM_PlayerPositionOne_800E0D48[8];
extern int                     COM_PlayerMapOne_800E0F70[8];


extern int                     COM_ALERT_DECREMENT_800E0F60;
extern int                     GM_GameFlag_800E0F64;
extern int                     COM_VibTime_800E0F68;

extern short    ActTable_800C3358[];
