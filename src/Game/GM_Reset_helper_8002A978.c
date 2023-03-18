#include "game.h"
#include "linkvarbuf.h"

extern unsigned short   gSystemCallbackProcs_800B58C0[];
extern int              dword_800AB9F0;
int                     dword_800AB9F0;
extern int              GM_GameOverTimer_800AB3D4;
int                     GM_GameOverTimer_800AB3D4;
extern PlayerStatusFlag GM_PlayerStatus_800ABA50;
PlayerStatusFlag        GM_PlayerStatus_800ABA50;
extern short            d_800AB9EC_mag_size;
short                   d_800AB9EC_mag_size;
extern short            d_800ABA2C_ammo;
short                   d_800ABA2C_ammo;
extern int              GM_AlertLevel_800ABA18;
int                     GM_AlertLevel_800ABA18;
extern int              GM_AlertMax_800AB9E0;
int                     GM_AlertMax_800AB9E0;
extern int              claymore_map_800AB9DC;
int                     claymore_map_800AB9DC;
extern int              GM_AlertMode_800ABA00;
int                     GM_AlertMode_800ABA00;
extern unsigned int     GM_DisableWeapon_800AB9E4;
unsigned int            GM_DisableWeapon_800AB9E4;
extern char            *GM_StageName_800AB918;
char                   *GM_StageName_800AB918;
extern SVECTOR          svector_800ABA10;
SVECTOR                 svector_800ABA10;
extern int              GM_DisableItem_800ABA28;
int                     GM_DisableItem_800ABA28;
extern short            GM_WeaponChanged_800AB9D8;
short                   GM_WeaponChanged_800AB9D8;
extern short            GM_O2_800ABA34;
short                   GM_O2_800ABA34;
extern int              GM_GameStatus_800AB3CC;
int                     GM_GameStatus_800AB3CC;
extern int              GM_NoisePower_800ABA24;
int                     GM_NoisePower_800ABA24;
extern int              GM_NoiseLength_800ABA30;
int                     GM_NoiseLength_800ABA30;

void GM_Reset_helper_8002A978()
{
    int i;

    dword_800AB9F0 = -1;
    GM_GameStatus_800AB3CC = 0;
    GM_GameOverTimer_800AB3D4 = 0;
    GM_PlayerStatus_800ABA50 = 0;
    GM_NoisePower_800ABA24 = 0;
    GM_NoiseLength_800ABA30 = 0;
    claymore_map_800AB9DC = 0;
    GM_AlertLevel_800ABA18 = 0;
    GM_AlertMax_800AB9E0 = 0;
    GM_AlertMode_800ABA00 = 0;
    GM_WeaponChanged_800AB9D8 = 0;
    d_800AB9EC_mag_size = 0;
    d_800ABA2C_ammo = 0;
    GM_DisableItem_800ABA28 = 0;
    GM_DisableWeapon_800AB9E4 = 0;
    GM_O2_800ABA34 = 1024;
    GM_StageName_800AB918 = 0;
    GM_TempChangeSpeed = 0;
    svector_800ABA10.vx = GM_SnakePosX;
    svector_800ABA10.vy = GM_SnakePosY;
    svector_800ABA10.vz = GM_SnakePosZ;

    for (i = 5; i >= 0; i--)
    {
        gSystemCallbackProcs_800B58C0[i] = 0;
    }
}
