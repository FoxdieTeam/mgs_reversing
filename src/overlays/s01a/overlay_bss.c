#include "linker.h"
#include "psyq.h"
#include "overlays/s00a/Enemy/enemy.h"

int SECTION("overlay.bss") s01a_dword_800E4B24;

short SECTION("overlay.bss") sphere_image_width_800E4B28;
short SECTION("overlay.bss") sphere_image_height_800E4B2A;
short SECTION("overlay.bss") sphere_visible_tiles_x_800E4B2C;
short SECTION("overlay.bss") sphere_visible_tiles_y_800E4B2E;
short SECTION("overlay.bss") sphere_tiles_x_800E4B30;
short SECTION("overlay.bss") sphere_tiles_y_800E4B32;
short SECTION("overlay.bss") sphere_tile_width_800E4B34;
short SECTION("overlay.bss") sphere_tile_height_800E4B36;
short SECTION("overlay.bss") sphere_elevation_800E4B38;
short SECTION("overlay.bss") sphere_word_800E4B3A;

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

ENEMY_COMMAND SECTION("overlay.bss") EnemyCommand_800E0D98;

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
