#include "libgcl.h"
#include "common.h"
#include "strcode.h"        // for GCX_* defs
#include "libgv/libgv.h"    // for GV_SetLoader

int SECTION(".sbss") scenerio_code;
int SECTION(".sbss") dword_800AB994; // padding

/**
 *  @brief      GCX bytecode initialization handler
 *
 *  If @p id is the same as @c scenerio_code the script will be loaded
 *  and set for execution, otherwise it will be skipped.
 *
 *  @param[in]  buf     pointer to cached GCX script
 *  @param[in]  id      strcode of the script's basename
 *
 *  @retval     1       on success
 *  @retval     <= 0    on failure (but this can't happen)
 */
static int GCL_InitFunc( void *top, int id )
{
    if ( id == scenerio_code )
    {
        GCL_LoadScript( top );
    }

    return 1;
}

/**
 *  @brief      Sets which GCX script to load.
 *
 *  If @p demo equals TRUE, demo.gcx will be set for execution
 *  upon loading a stage, otherwise it will default to the standard
 *  scenerio.gcx script.
 *
 *  @param      demo       Sets "demo.gcx" if TRUE
 */
void GCL_ChangeSenerioCode( int demo )
{
    scenerio_code = ( demo == TRUE )
        ? ( ( GCL_STRID << 16 ) | 0xa242 )  // GV_StrCode("demo")
        : ( ( GCL_STRID << 16 ) | 0xea54 ); // GV_StrCode("scenerio")
}

void GCL_StartDaemon( void )
{
    GCL_ParseInit();
    GCL_InitVar();
    GCL_InitBasicCommands();
    GV_SetLoader( 'g', GCL_InitFunc );

    GCL_ChangeSenerioCode( 0 );
}

void GCL_ResetSystem( void )
{
    /* do nothing */
}
