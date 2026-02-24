#include "game.h"

#include "sd/sd_cli.h"
#include "sd/g_sound.h"
#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"

typedef struct _SOUND
{
    short pan;
    short vol;
} SOUND;

extern GM_CAMERA        GM_Camera;
extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;

static inline void GM_Sound( int pan, int vol, int se_id, int exclude )
{
    int se_id_;

    if (!(GM_GameStatus & exclude))
    {
        pan &= 0xff;
        vol &= 0xff;
        vol = MIN(vol, 63);
        se_id_ = se_id & 0xff;
        sd_set_cli( (pan << 16 | vol << 8 | se_id_), SD_ASYNC );
    }
}

STATIC void get_eye_pos(SVECTOR *pos, int *dir)
{
    MATRIX *eye;

    eye = &DG_Chanl(0)->eye;
    pos->vx = eye->t[0];
    pos->vy = eye->t[1];
    pos->vz = eye->t[2];
    *dir = ratan2(eye->m[0][2], eye->m[2][2]);
}

// Get the pan amount based on the angle from forward to the sound position
STATIC int get_pan(int angle, int scale)
{
    int pan;

    pan = (rcos(angle & 4095) * scale) / 4096;
    if (pan < 0)
    {
        return pan + 255;
    }

    return pan;
}

// Get the pan & vol relative to the world direction
STATIC int get_pan_vol_world(SVECTOR *pos, int size, SOUND *sound)
{
    SVECTOR diff;
    int     dist;
    int     vol;
    int     dir;

    dist = GV_DiffVec3(&GM_PlayerPosition, pos) - size;
    if (dist < 0)
    {
        dist = 0;
        vol = 63;
    }
    else
    {
        vol = 63;
    }

    if (dist >= 1000)
    {
        if (dist < 7300)
        {
            vol = 63 - ((dist - 1000) / 100);
        }
        else
        {
            dist = 7300;
            vol = 0;
        }
    }

    GV_SubVec3(pos, &GM_PlayerPosition, &diff);
    dir = GV_VecDir2(&diff) + 1024;

    sound->pan = get_pan(dir - gUnkCameraStruct2_800B7868.rotate.vy, (dist * 31) / 7300);
    sound->vol = vol;

    if (vol <= 0)
    {
        return -1;
    }

    return 0;
}

// Get the pan & vol relative to the camera direction
STATIC int get_pan_vol_camera(SVECTOR *pos, int size, SOUND *sound)
{
    SVECTOR diff;
    SVECTOR eye;
    int     eyedir;
    int     dist;
    int     vol;
    int     dir;

    get_eye_pos(&eye, &eyedir);

    dist = GV_DiffVec3(&eye, pos) - size;
    if (dist < 0)
    {
        dist = 0;
        vol = 63;
    }
    else
    {
        vol = 63;
    }

    if (dist < 9500)
    {
        vol = 63 - (dist / 150);
    }
    else
    {
        dist = 9500;
        vol = 0;
    }

    dist *= 4;

    if (dist > 9500)
    {
        dist = 9500;
    }

    GV_SubVec3(pos, &eye, &diff);
    dir = GV_VecDir2(&diff) + 1024;

    sound->pan = get_pan(dir - eyedir, (dist * 31) / 9500);
    sound->vol = vol;

    if (vol <= 0)
    {
        return -1;
    }

    return 0;
}

// Get the pan & vol relative to the world direction for explosions
STATIC int get_pan_vol_bomb_world(SVECTOR *pos, int size, SOUND *sound)
{
    SVECTOR diff;
    int     dist;
    int     vol;
    int     dir;

    dist = GV_DiffVec3(&GM_PlayerPosition, pos) - size;
    if (dist < 0)
    {
        dist = 0;
        vol = 63;
    }
    else
    {
        vol = 63;
    }

    if (dist >= 3000)
    {
        if (dist < 7700)
        {
            vol = 63 - ((dist - 3000) / 200);
        }
        else
        {
            dist = 7700;
            vol = 39;
        }
    }

    GV_SubVec3(pos, &GM_PlayerPosition, &diff);
    dir = GV_VecDir2(&diff) + 1024;

    sound->pan = get_pan(dir - gUnkCameraStruct2_800B7868.rotate.vy, (dist * 31) / 7700);
    sound->vol = vol;

    if (vol <= 0)
    {
        return -1;
    }

    return 0;
}

// Get the pan & vol relative to the camera direction for explosions
STATIC int get_pan_vol_bomb_camera(SVECTOR *pos, int size, SOUND *sound)
{
    SVECTOR diff;
    SVECTOR eye;
    int     eyedir;
    int     dist;
    int     vol;
    int     dir;

    get_eye_pos(&eye, &eyedir);

    dist = GV_DiffVec3(&eye, pos) - size;
    if (dist < 0)
    {
        dist = 0;
        vol = 63;
    }
    else
    {
        vol = 63;
    }

    if (dist >= 2000)
    {
        if (dist < 9050)
        {
            vol = 63 - ((dist - 2000) / 300);
        }
        else
        {
            dist = 9050;
            vol = 39;
        }
    }

    dist *= 4;

    if (dist > 9050)
    {
        dist = 9050;
    }

    GV_SubVec3(pos, &eye, &diff);
    dir = GV_VecDir2(&diff) + 1024;

    sound->pan = get_pan(dir - eyedir, (dist * 31) / 9050);
    sound->vol = vol;

    if (vol <= 0)
    {
        return -1;
    }

    return 0;
}

STATIC int get_pan_vol_size(SOUND *sound, SVECTOR *pos, int size)
{
    if (!(GM_GameStatus & (STATE_BEHIND_CAMERA | GAME_FLAG_BIT_07)) && !GM_Camera.first_person)
    {
        if (get_pan_vol_world(pos, size, sound) < 0)
        {
            return -1;
        }
    }
    else
    {
        if (get_pan_vol_camera(pos, size, sound) < 0)
        {
            return -1;
        }
    }

    return 0;
}

STATIC int get_sound_normal(SOUND *sound, SVECTOR *pos)
{
    if (!(GM_GameStatus & (STATE_BEHIND_CAMERA | GAME_FLAG_BIT_07)) && !GM_Camera.first_person)
    {
        if (get_pan_vol_world(pos, 0, sound) < 0)
        {
            return -1;
        }
    }
    else
    {
        if (get_pan_vol_camera(pos, 0, sound) < 0)
        {
            return -1;
        }
    }

    return 0;
}

STATIC int get_sound_bomb(SOUND *sound, SVECTOR *pos)
{
    if (!(GM_GameStatus & (STATE_BEHIND_CAMERA | GAME_FLAG_BIT_07)) && !GM_Camera.first_person)
    {
        if (get_pan_vol_bomb_world(pos, 0, sound) < 0)
        {
            return -1;
        }
    }
    else
    {
        if (get_pan_vol_bomb_camera(pos, 0, sound) < 0)
        {
            return -1;
        }
    }

    return 0;
}


STATIC int get_sound_real(SOUND *sound, SVECTOR *pos)
{
    if (!(GM_GameStatus & (STATE_BEHIND_CAMERA | GAME_FLAG_BIT_07)) && !GM_Camera.first_person)
    {
        return -1;
    }

    if (get_pan_vol_camera(pos, 0, sound) < 0)
    {
        return -1;
    }

    return 0;
}

STATIC int get_sound_camera(SOUND *sound, SVECTOR *pos)
{
    if (get_pan_vol_camera(pos, 0, sound) < 0)
    {
        return -1;
    }

    return 0;
}

void GM_SeSet(SVECTOR *pos, int se_id)
{
    SOUND sound;

    if (pos)
    {
        if (se_id == SE_EXPLOSION)
        {
            if (get_sound_bomb(&sound, pos) < 0)
            {
                return;
            }
        }
        else if (se_id >= 160 && se_id <= 167)
        {
            if (get_sound_real(&sound, pos) < 0)
            {
                return;
            }
        }
        else if (se_id == SE_MOUSE_STEP)
        {
            if (get_sound_camera(&sound, pos) < 0)
            {
                return;
            }
        }
        else
        {
            if (get_sound_normal(&sound, pos) < 0)
            {
                return;
            }
        }
    }
    else
    {
        sound.vol = 63;
        sound.pan = 0;
    }

    GM_Sound(sound.pan, sound.vol, se_id, (STATE_GAME_OVER | STATE_DEMO));
}

void GM_SeSet2(int pan, int vol, int se_id)
{
    GM_Sound(pan, vol, se_id, (STATE_GAME_OVER | STATE_DEMO));
}

void GM_SeSetMode( SVECTOR *pos, int se_id, int mode )
{
    SOUND sound;

    if ( pos )
    {
        switch ( mode )
        {
        case GM_SEMODE_BOMB:
            if ( get_sound_bomb( &sound, pos ) < 0 )
            {
                return;
            }
            break;

        case GM_SEMODE_REAL:
            if ( get_sound_real( &sound, pos ) < 0 )
            {
                return;
            }
            break;

        case GM_SEMODE_CAMERA:
            if ( get_sound_camera( &sound, pos ) < 0 )
            {
                return;
            }
            break;

        case GM_SEMODE_NORMAL:
            if ( get_sound_normal( &sound, pos ) < 0 )
            {
                return;
            }
            break;
        }
    }
    else
    {
        sound.vol = 63;
        sound.pan = 0;
    }

    GM_Sound(sound.pan, sound.vol, se_id, (STATE_GAME_OVER | STATE_DEMO));
}

void GM_SeSet3(int pan, int vol, int se_id)
{
    GM_Sound(pan, vol, se_id, STATE_DEMO);
}

void GM_SeSetPan(SVECTOR *pos, int se_id, int vol)
{
    SOUND sound;

    get_sound_normal(&sound, pos);
    GM_Sound(sound.pan, vol, se_id, (STATE_GAME_OVER | STATE_DEMO));
}

void GM_SeSetSize(SVECTOR *pos, int se_id, int size)
{
    SOUND sound;

    if (get_pan_vol_size(&sound, pos, size) >= 0)
    {
        GM_Sound(sound.pan, sound.vol, se_id, (STATE_GAME_OVER | STATE_DEMO));
    }
}

void GM_SetSound(int sound_code, int sync_mode)
{
    sd_set_cli(sound_code, sync_mode);
}
