#include "linker.h"
#include "libgcl/libgcl.h"
#include "mts/mts_new.h"
#include "Menu/menuman.h"
#include "Game/strctrl.h"

extern int GM_CurrentMap_800AB9B0;
extern int gBinds_800ABA60;
extern int GM_GameStatus_800AB3CC;
extern int DG_UnDrawFrameCount_800AB380;

int SECTION(".sbss") gBinds_800ABA60;

int GCL_Command_demo_8002C890(unsigned char *pScript)
{
    int   code, cb_proc;
    char  *msg;

    if ( !GCL_GetParam_80020968( 's' ) ) // scene ?
    {
        printf( "DEMO:NO CODE\n" );
    }
    code = GCL_GetNextParamValue_80020AD4();

    if ( GCL_GetParam_80020968( 'p' ) ) // proc
    {
        cb_proc = GCL_GetNextParamValue_80020AD4() | GAME_FLAG_BIT_32;
    }
    else
    {
        cb_proc = 0;
    }

    GM_CurrentMap_800AB9B0 = gBinds_800ABA60;

    if ( code >= 0 )
    {
        DG_UnDrawFrameCount_800AB380 = 0x7FFF0000;
        GM_GameStatus_800AB3CC |= GAME_FLAG_BIT_32;
        GCL_Command_demo_helper_80037DD8( code, cb_proc );
    }
    else
    {
        if ( cb_proc < 0 )
        {
            cb_proc &= 0xFFFF;
        }
        else
        {
            cb_proc = -1;
        }

        if ( GCL_GetParam_80020968( 'f' ) ) // file
        {
            msg = GCL_Read_String_80020A70( GCL_Get_Param_Result_80020AA4() );
        }
        else
        {
            msg = "DEMO ( no data on CD )";
        }
        NewJimakuStr_8004955C( msg, cb_proc );
    }
    return 0;
}
