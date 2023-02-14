#include "target.h"
#include "game.h"
#include "libgcl/gcl.h"
#include "libgcl/hash.h"
#include "homing_target.h"

extern DG_TEX gMenuTextureRec_800B58B0;

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
    DG_TEX *pTexture;
    
    pTexture = DG_GetTexture_8001D830(PCC_READ);
    gMenuTextureRec_800B58B0 = *pTexture;
    gMenuTextureRec_800B58B0.field_0_hash = 0;
}
