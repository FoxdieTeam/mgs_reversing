#include "game.h"
#include "common.h"
#include "libgcl/libgcl.h"
#include "sd/g_sound.h"

STATIC int     SECTION(".sbss") song_status;
STATIC int     SECTION(".sbss") dword_800ABA74; // padding
STATIC int     SECTION(".sbss") song_codes[2];
STATIC short   SECTION(".sbss") new_alert_mode;
STATIC short   SECTION(".sbss") word_800ABA82;  // padding

char alert_procs[] = {0, 0, 1, 2};

extern char noise_sounds[4][3];
extern int  GM_GameOverVox;

#define STATUS_BIT_0 0x1
#define STATUS_BIT_1 0x2

static void set_song(int song)
{
    if (song == 0)
    {
        GM_SetSound(0x01ffffff, SD_ASYNC);
    }
    else
    {
        GM_SetSound(song | 0x01000000, SD_ASYNC);
    }
}

static void set_song2(int song)
{
    if (song == 0)
    {
        song_status &= ~STATUS_BIT_0;
    }
    else
    {
        set_song(song);
        song_status |= STATUS_BIT_0;
    }
}

static void set_noise_sound(int noise)
{
    int i;

    for (i = 1; i < 4; i++)
    {
        noise_sounds[i][noise] = GCL_GetNextParamValue();
    }

    if (GCL_GetParamResult())
    {
        noise_sounds[0][noise] = GCL_GetNextParamValue();
    }
}

int GM_GetNoiseSound(int flag, int noise)
{
    return noise_sounds[(flag >> 8) & 3][noise];
}

void GM_SoundStart(void)
{
    if (song_status == 0)
    {
        set_song(song_codes[GM_AlertMode != ALERT_OFF]);
    }
}

//AlertCmd() ?
void GM_AlertSound(void)
{
    int c_code;
    int x_code;
    int vox_code;
    int proc;

    if (GCL_GetOption('b'))
    {
        song_codes[0] = GCL_GetNextParamValue();
        song_codes[1] = GCL_GetNextParamValue();
        song_status &= ~STATUS_BIT_0;
    }

    if (GCL_GetOption('s')) // song
    {
        set_song(GCL_GetNextParamValue());
        song_status |= STATUS_BIT_0;
    }

    if (GCL_GetOption('c'))
    {
        c_code = GCL_GetNextParamValue();
        GM_SetSound(c_code | 0x01ffff00, SD_ASYNC);

        /* song pause or song fade in */
        if (c_code == 0x01ffff01 || (c_code >= 0x01ffff03 && c_code <= 0x01ffff05))
        {
            song_status &= ~STATUS_BIT_1;
        }
        else
        {
            song_status |= STATUS_BIT_1;
        }
    }

    if (GCL_GetOption('x'))
    {
        x_code = GCL_GetNextParamValue();

        /* song fade out */
        if (x_code >= 0x01ffff0a && x_code <= 0x01ffff0d)
        {
            song_status |= STATUS_BIT_0;
        }

        GM_SetSound(x_code, SD_ASYNC);
    }

    if (GCL_GetOption('e')) // emit
    {
        GM_SeSet2(GCL_GetNextParamValue(),  // pan
                  GCL_GetNextParamValue(),  // vol
                  GCL_GetNextParamValue()); // se_id
    }

    if (GCL_GetOption('v')) // vox
    {
        vox_code = GCL_GetNextParamValue();

        proc = 0;
        if (GCL_GetOption('f')) // func
        {
            proc = GCL_GetNextParamValue() | 0x80000000;
        }

        GM_VoxStream(vox_code, proc);
    }

    if (GCL_GetOption('g'))
    {
        GM_GameOverVox = GCL_GetNextParamValue();
    }

    if (GCL_GetOption('k'))
    {
        set_noise_sound(0);
    }

    if (GCL_GetOption('r'))
    {
        set_noise_sound(1);
    }

    if (GCL_GetOption('l'))
    {
        set_noise_sound(2);
    }

    if (GCL_GetOption('n'))
    {
        GM_SoundStart();
    }
}

void GM_AlertReset( void )
{
    int i;

    song_status = 0;
    song_codes[ 0 ] = 0;
    song_codes[ 1 ] = 0;

    noise_sounds[ 0 ][ 0 ] = SE_WALL02;
    noise_sounds[ 0 ][ 1 ] = SE_REB01;

    for ( i = 0; i < 4; i++ )
    {
        noise_sounds[ i ][ 2 ] = SE_REBDRM01;
    }
}

void GM_AlertAct( void )
{
    if ( GM_GameStatus & STATE_GAME_OVER )
    {
        return;
    }

    if ( new_alert_mode >= 0 && new_alert_mode != GM_AlertMode )
    {
        if ( song_status == 0 )
        {
            switch ( new_alert_mode )
            {
            case ALERT_ACTIVE:
                if ( GM_AlertMode == ALERT_OFF )
                {
                    GM_SeSet2( 0, 0x3F, SE_ALERT_SIREN );
                    GM_SetSound( 0x01ffff0b, SD_ASYNC );
                    set_song( song_codes[1] );
                }
                else if ( GM_AlertMode == ALERT_EVASION )
                {
                    GM_SetSound( 0x01ffff03, SD_ASYNC );
                }
                break;

            case ALERT_EVASION:
                GM_SetSound( 0x01ffff10, SD_ASYNC );
                break;

            case ALERT_OFF:
                set_song( song_codes[0] );
                break;
            }
        }

        GM_AlertMode = new_alert_mode;
    }

    if ( GM_AlertMode == ALERT_EVASION && song_status == 0 && GM_AlertLevel == 60 )
    {
        GM_SetSound( 0x01ffff08, SD_ASYNC );
    }

    new_alert_mode = -1;
}

void GM_AlertModeSet(int mode)
{
    if (mode > new_alert_mode)
    {
        new_alert_mode = mode;
        GM_CallSystemCallbackProc(2, alert_procs[mode]);
    }
}

void GM_AlertModeInit(void)
{
    new_alert_mode = -1;
}

void GM_AlertModeReset(void)
{
    GM_CallSystemCallbackProc(2, 0);
}
