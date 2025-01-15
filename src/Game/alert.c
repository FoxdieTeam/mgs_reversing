#include "game.h"
#include "common.h"
#include "libgcl/libgcl.h"
#include "SD/g_sound.h"

STATIC int     SECTION(".sbss") dword_800ABA70;
STATIC int     SECTION(".sbss") dword_800ABA74;
STATIC int     SECTION(".sbss") dword_800ABA78[2];
STATIC short   SECTION(".sbss") GM_RadarMode_800ABA80;
STATIC short   SECTION(".sbss") word_800ABA82;

char byte_8009D698[] = {0, 0, 1, 2};
char GM_NoiseSound_800B76E0[4][3];

extern int   GM_GameOverVox;
extern int   GM_AlertMode;
extern int   GM_AlertLevel;

typedef enum // GM_RadarMode_800ABA80
{
    RADAR_ENABLED = 0,
    RADAR_JAMMED = 1,
    RADAR_EVASION = 2,
    RADAR_ALERT = 3
} RadarMode;

typedef enum // GM_AlertMode
{
    ALERT_DISABLED = 0,
    ALERT_ENABLED = 1,
    ALERT_EVASION = 2 // > 2 = ALERT_EVASION
} AlertMode;


void sub_8002E508(int a1)
{
    if (a1 == 0)
    {
        GM_SetSound(0x01ffffff, SD_ASYNC);
    }
    else
    {
        GM_SetSound(a1 | 0x01000000, SD_ASYNC);
    }
}

void sub_8002E544(int param_1)
{
    if (param_1 == 0)
    {
        dword_800ABA70 &= ~1;
    }
    else
    {
        sub_8002E508(param_1);
        dword_800ABA70 |= 1;
    }
}

void GM_SetNoiseSound(int arg0)
{
    int i;

    for (i = 1; i < 4; i++)
    {
        GM_NoiseSound_800B76E0[i][arg0] = GCL_GetNextParamValue();
    }

    if (GCL_GetParamResult())
    {
        GM_NoiseSound_800B76E0[0][arg0] = GCL_GetNextParamValue();
    }
}

int GM_GetNoiseSound(int arg0, int arg1)
{
    return GM_NoiseSound_800B76E0[arg0 >> 8 & 3][arg1];
}

void GM_SoundStart(void)
{
    if (dword_800ABA70 == 0)
    {
        sub_8002E508(dword_800ABA78[GM_AlertMode != 0]);
    }
}

//AlertCmd() ?
void GM_Command_sound_impl(void)
{
    int sdCode, xCode, voxCode, proc;

    if (GCL_GetOption('b'))
    {
        dword_800ABA78[0] = GCL_GetNextParamValue();
        dword_800ABA78[1] = GCL_GetNextParamValue();
        dword_800ABA70 &= ~1;
    }
    if (GCL_GetOption('s'))
    {
        sub_8002E508(GCL_GetNextParamValue());
        dword_800ABA70 |= 1;
    }
    if (GCL_GetOption('c'))
    {
        sdCode = GCL_GetNextParamValue();
        GM_SetSound(sdCode | 0x01ffff00, SD_ASYNC);
        if (sdCode == 0x01ffff01 || sdCode + 0xfe0000fd < 3)
        {
            dword_800ABA70 &= ~2;
        }
        else
        {
            dword_800ABA70 |= 2;
        }
    }
    if (GCL_GetOption('x'))
    {
        xCode = GCL_GetNextParamValue();
        if (xCode + 0xFE0000F6 < 4)
        {
            dword_800ABA70 |= 1;
        }
        GM_SetSound(xCode, SD_ASYNC);
    }
    if (GCL_GetOption('e'))
    {
        GM_SeSet2(GCL_GetNextParamValue(),     // x_pos
                  GCL_GetNextParamValue(),     // y_pos
                  GCL_GetNextParamValue());    // se_id
    }
    if (GCL_GetOption('v')) // vox
    {
        voxCode = GCL_GetNextParamValue();
        proc = 0;
        if (GCL_GetOption('f')) // func
        {
            proc = GCL_GetNextParamValue() | 0x80000000;
        }
        GM_VoxStream(voxCode, proc);
    }
    if (GCL_GetOption('g'))
    {
        GM_GameOverVox = GCL_GetNextParamValue();
    }
    if (GCL_GetOption('k'))
    {
        GM_SetNoiseSound(0);
    }
    if (GCL_GetOption('r'))
    {
        GM_SetNoiseSound(1);
    }
    if (GCL_GetOption('l'))
    {
        GM_SetNoiseSound(2);
    }
    if (GCL_GetOption('n'))
    {
        GM_SoundStart();
    }
}

void GM_Act_helper2( void )
{
    int  i;
    char val;

    GM_NoiseSound_800B76E0[ 0 ][ 0 ] = 55;
    dword_800ABA70 = 0;
    dword_800ABA78[ 0 ] = 0;
    dword_800ABA78[ 1 ] = 0;
    GM_NoiseSound_800B76E0[ 0 ][ 1 ] = 39;

    val = 40;
    for ( i = 3; i >= 0; i-- )
    {
        GM_NoiseSound_800B76E0[ i ][ 2 ] = val;
    }
}


void GM_AlertAct( void )
{
    if ( GM_GameStatus & STATE_GAME_OVER )
    {
        return;
    }

    if ( GM_RadarMode_800ABA80 >= 0 )
    {
        if ( GM_RadarMode_800ABA80 != GM_AlertMode )
        {
            if ( dword_800ABA70 == 0 )
            {
                switch ( GM_RadarMode_800ABA80 )
                {
                case RADAR_ALERT:
                    if ( GM_AlertMode == ALERT_DISABLED )
                    {
                        GM_SeSet2( 0, 0x3F, SE_ALERT_SIREN );
                        GM_SetSound( 0x01ffff0b, SD_ASYNC );
                        sub_8002E508( dword_800ABA78[1] );
                    }
                    else if ( GM_AlertMode == ALERT_EVASION )
                    {
                        GM_SetSound( 0x01ffff03, SD_ASYNC );
                    }
                    break;
                case RADAR_EVASION:
                    GM_SetSound( 0x01ffff10, SD_ASYNC );
                    break;
                case RADAR_ENABLED:
                    sub_8002E508( dword_800ABA78[0] );
                    break;
                }
            }
            GM_AlertMode = GM_RadarMode_800ABA80;
        }
    }
    if ( ( GM_AlertMode == ALERT_EVASION ) && ( dword_800ABA70 == 0 ) &&
         ( GM_AlertLevel == 0x3C ) )
    {
        GM_SetSound( 0x01ffff08, SD_ASYNC );
    }
    GM_RadarMode_800ABA80 = -1;
}

void GM_AlertModeSet(int a1)
{
    if (a1 > GM_RadarMode_800ABA80)
    {
        GM_RadarMode_800ABA80 = a1;
        GM_CallSystemCallbackProc(2, byte_8009D698[a1]);
    }
}

void GM_AlertModeInit(void)
{
    GM_RadarMode_800ABA80 = -1;
}

void GM_AlertModeReset(void)
{
    GM_CallSystemCallbackProc(2, 0);
}
