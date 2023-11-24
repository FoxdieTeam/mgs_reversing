#include "linker.h"
#include "overlays/s00a/Enemy/enemy.h"

int SECTION("overlay.bss") s00a_dword_800E0C9C;

int SECTION("overlay.bss") s00a_dword_800E0CA0;
int SECTION("overlay.bss") s00a_dword_800E0CA4;
int SECTION("overlay.bss") s00a_dword_800E0CA8;
int SECTION("overlay.bss") s00a_dword_800E0CAC;

GM_Camera SECTION("overlay.bss") s00a_dword_800E0CB0;

int SECTION("overlay.bss") s00a_dword_800E0D2C;
int SECTION("overlay.bss") s00a_dword_800E0D30;
int SECTION("overlay.bss") s00a_dword_800E0D34;

SVECTOR SECTION("overlay.bss") s00a_dword_800E0D38;

int SECTION("overlay.bss") COM_PlayerOnZone_800E0D40;

int SECTION("overlay.bss") COM_NoiseMinDisID_800E0D44;

SVECTOR SECTION("overlay.bss") COM_PlayerPositionOne_800E0D48[8];

int SECTION("overlay.bss") COM_SHOOTRANGE_800E0D88;
int SECTION("overlay.bss") COM_EYE_LENGTH_800E0D8C;
int SECTION("overlay.bss") COM_PlayerAddress_800E0D90;
unsigned int SECTION("overlay.bss") ENE_SPECIAL_FLAG_800E0D94;

ENEMY_COMMAND SECTION("overlay.bss")  EnemyCommand_800E0D98;

int SECTION("overlay.bss") COM_PlayerMap_800E0F1C;

TOPCOMMAND_STRUCT SECTION("overlay.bss") TOPCOMMAND_800E0F20;

TOPCOMMAND_STRUCT SECTION("overlay.bss") s00a_dword_800E0F28;

SVECTOR SECTION("overlay.bss")  COM_PlayerPosition_800E0F30;

int SECTION("overlay.bss") COM_NOISEMODE_DIS_800E0F38;

unsigned int SECTION("overlay.bss") COM_GameStatus_800E0F3C;

int SECTION("overlay.bss") COM_PlayerAddressOne_800E0F40[8];

int SECTION("overlay.bss") COM_ALERT_DECREMENT_800E0F60;

int SECTION("overlay.bss") GM_GameFlag_800E0F64;

int SECTION("overlay.bss") COM_VibTime_800E0F68;

int SECTION("overlay.bss") s00a_dword_800E0F6C;

int SECTION("overlay.bss") COM_PlayerMapOne_800E0F70[8];

