#include "target.h"
#include "game.h"

int  GCL_BindsInit_8002D1A8();
int  GM_AlertModeInit_8002EAA8();
void GM_InitWhereSystem_8002597C(void);
int  GM_Reset_helper_8002A978();
int  GM_Reset_helper3_80030760();
void HomingTarget_Clear_All_80032C68();

DG_TEX SECTION(".gMenuTextureRec_800B58B0") gMenuTextureRec_800B58B0;

void GM_Reset_8002ABF4(Actor_GM_Daemon *pActor)
{
    GM_Reset_helper3_80030760();
    GM_InitWhereSystem_8002597C();
    GM_Targets_Reset_8002D3F0();
    HomingTarget_Clear_All_80032C68();
    GCL_BindsInit_8002D1A8();
    GM_Reset_helper_8002A978();
    GM_AlertModeInit_8002EAA8();
}

void GM_InitReadError_8002AC44()
{
    DG_TEX *pTexture = DG_FindTexture_8001D830(0xA0BE);
    gMenuTextureRec_800B58B0 = *pTexture;
    gMenuTextureRec_800B58B0.field_0_hash = 0;
}
