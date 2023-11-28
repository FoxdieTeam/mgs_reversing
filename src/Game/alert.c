#include "game.h"
#include "linker.h"
#include "libgcl/libgcl.h"

extern int           dword_800ABA70;
int SECTION(".sbss") dword_800ABA70;

extern int           dword_800ABA78[2];
int SECTION(".sbss") dword_800ABA78[2];

extern short GM_RadarMode_800ABA80;                    // 79c
short        SECTION( ".sbss" ) GM_RadarMode_800ABA80; // GM_RadarMode_800ABA80

char byte_8009D698[] = {0, 0, 1, 2};
char GM_NoiseSound_800B76E0[4][3];

extern int   GM_GameOverVox_800AB45C;
extern int   dword_800ABA58;
extern int   GM_GameStatus_800AB3CC;
extern int   GM_AlertMode_800ABA00;
extern int   GM_AlertLevel_800ABA18;


void         GM_SeSet2_80032968( int byte_2, int byte_1, int byte_0 );
void         GM_Sound_80032C48( int code, int notUsed );

typedef enum // GM_RadarMode_800ABA80
{
    RADAR_ENABLED = 0,
    RADAR_JAMMED = 1,
    RADAR_EVASION = 2,
    RADAR_ALERT = 3
} RadarMode;

typedef enum // GM_AlertMode_800ABA00
{
    ALERT_DISABLED = 0,
    ALERT_ENABLED = 1,
    ALERT_EVASION = 2 // > 2 = ALERT_EVASION
} AlertMode;

/*
//not used anywhere yet
static  inline  void    GM_SetAlert( alert )
int         alert ;
{
    if ( alert > 256 ) alert = 256 ;
    if ( alert > GM_AlertMax ) GM_AlertMax = alert ;
}
*/


void sub_8002E508(int a1)
{
    if (a1 == 0)
    {
        GM_Sound_80032C48(0x1ffffff, 0);
    }
    else
    {
        GM_Sound_80032C48(a1 | 0x1000000, 0);
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

void GM_set_noise_sound_8002E588(int arg0)
{
    int i;

    for (i = 1; i < 4; i++)
    {
        GM_NoiseSound_800B76E0[i][arg0] = GCL_GetNextParamValue_80020AD4();
    }

    if (GCL_Get_Param_Result_80020AA4())
    {
        GM_NoiseSound_800B76E0[0][arg0] = GCL_GetNextParamValue_80020AD4();
    }
}

int GM_GetNoiseSound_8002E614(int arg0, int arg1)
{
    return GM_NoiseSound_800B76E0[arg0 >> 8 & 3][arg1];
}

void GM_SoundStart_8002E640()
{
    if (dword_800ABA70 == 0)
    {
        sub_8002E508(dword_800ABA78[GM_AlertMode_800ABA00 != 0]);
    }
}

//AlertCmd() ?
void GCL_Command_sound_impl_8002E688()
{
    int sdCode, xCode, voxCode, proc;

    if (GCL_GetOption_80020968('b'))
    {
        dword_800ABA78[0] = GCL_GetNextParamValue_80020AD4();
        dword_800ABA78[1] = GCL_GetNextParamValue_80020AD4();
        dword_800ABA70 &= ~1;
    }
    if (GCL_GetOption_80020968('s'))
    {
        sub_8002E508(GCL_GetNextParamValue_80020AD4());
        dword_800ABA70 |= 1;
    }
    if (GCL_GetOption_80020968('c'))
    {
        sdCode = GCL_GetNextParamValue_80020AD4();
        GM_Sound_80032C48(sdCode | 0x1FFFF00, 0);
        if (sdCode == 0x1FFFF01 || sdCode + 0xFE0000FD < 3)
        {
            dword_800ABA70 &= ~2;
        }
        else
        {
            dword_800ABA70 |= 2;
        }
    }
    if (GCL_GetOption_80020968('x'))
    {
        xCode = GCL_GetNextParamValue_80020AD4();
        if (xCode + 0xFE0000F6 < 4)
        {
            dword_800ABA70 |= 1;
        }
        GM_Sound_80032C48(xCode, 0);
    }
    if (GCL_GetOption_80020968('e'))
    {
        GM_SeSet2_80032968(GCL_GetNextParamValue_80020AD4(), GCL_GetNextParamValue_80020AD4(),
                          GCL_GetNextParamValue_80020AD4());
    }
    if (GCL_GetOption_80020968('v')) // vox
    {
        voxCode = GCL_GetNextParamValue_80020AD4();
        proc = 0;
        if (GCL_GetOption_80020968('f')) // func
        {
            proc = GCL_GetNextParamValue_80020AD4() | 0x80000000;
        }
        GM_VoxStream_80037E40(voxCode, proc);
    }
    if (GCL_GetOption_80020968('g'))
    {
        GM_GameOverVox_800AB45C = GCL_GetNextParamValue_80020AD4();
    }
    if (GCL_GetOption_80020968('k'))
    {
        GM_set_noise_sound_8002E588(0);
    }
    if (GCL_GetOption_80020968('r'))
    {
        GM_set_noise_sound_8002E588(1);
    }
    if (GCL_GetOption_80020968('l'))
    {
        GM_set_noise_sound_8002E588(2);
    }
    if (GCL_GetOption_80020968('n'))
    {
        GM_SoundStart_8002E640();
    }
}

void        GM_Act_helper2_8002E8D4()
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


void GM_AlertAct_8002E91C()
{
    if ( !( GM_GameStatus_800AB3CC & GAME_FLAG_BIT_27 ) )
    {
        if ( GM_RadarMode_800ABA80 >= 0 )
        {
            if ( GM_RadarMode_800ABA80 != GM_AlertMode_800ABA00 )
            {
                if ( dword_800ABA70 == 0 )
                {
                    switch ( GM_RadarMode_800ABA80 )
                    {
                    case RADAR_ALERT:
                        if ( GM_AlertMode_800ABA00 == ALERT_DISABLED )
                        {
                            GM_SeSet2_80032968( 0, 0x3F, 0x2A );
                            GM_Sound_80032C48( 0x01FFFF0B, 0 );
                            sub_8002E508( dword_800ABA78[1] );
                        }
                        else if ( GM_AlertMode_800ABA00 == ALERT_EVASION )
                        {
                            GM_Sound_80032C48( 0x01FFFF03, 0 );
                        }
                        break;
                    case RADAR_EVASION:
                        GM_Sound_80032C48( 0x01FFFF10, 0 );
                        break;
                    case RADAR_ENABLED:
                        sub_8002E508( dword_800ABA78[0] );
                        break;
                    }
                }
                GM_AlertMode_800ABA00 = GM_RadarMode_800ABA80;
            }
        }
        if ( ( GM_AlertMode_800ABA00 == ALERT_EVASION ) && ( dword_800ABA70 == 0 ) &&
             ( GM_AlertLevel_800ABA18 == 0x3C ) )
        {
            GM_Sound_80032C48( 0x01FFFF08, 0 );
        }
        GM_RadarMode_800ABA80 = -1;
    }
}

void GM_AlertModeSet_8002EA68(int a1)
{
    if (a1 > GM_RadarMode_800ABA80)
    {
        GM_RadarMode_800ABA80 = a1;
        GM_CallSystemCallbackProc_8002B570(2, byte_8009D698[a1]);
    }
}

void GM_AlertModeInit_8002EAA8()
{
    GM_RadarMode_800ABA80 = -1;
}

void GM_AlertModeReset_8002EAB8()
{
    GM_CallSystemCallbackProc_8002B570(2, 0);
}
