#include "psyq.h"
#include "game.h"
#include "SD/sound.h"
#include "SD/g_sound.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Game/camera.h"

extern SVECTOR          GM_PlayerPosition_800ABA10;
extern GM_Camera        GM_Camera_800B77E8;
extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;

void sub_8003214C(SVECTOR *pVec, int *pRet)
{
    MATRIX *eye;

    eye = &DG_Chanl(0)->field_30_eye;
    pVec->vx = eye->t[0];
    pVec->vy = eye->t[1];
    pVec->vz = eye->t[2];
    *pRet = ratan2(eye->m[0][2], eye->m[2][2]);
}

int sub_800321AC(int a1, int a2)
{
    int v2 = rcos(a1 & 4095) * a2 / 4096;
    if (v2 < 0)
    {
        return v2 + 255;
    }
    return v2;
}

int sub_800321F8(SVECTOR *pos, int param_2, DVECTOR *out)
{
    int     vecdir;
    int     diffvec;
    int     vy;
    SVECTOR vec;

    diffvec = GV_DiffVec3(&GM_PlayerPosition_800ABA10, pos) - param_2;
    if (diffvec < 0)
    {
        diffvec = 0;
        vy = 63;
    }
    else
    {
        vy = 63;
    }

    if (diffvec >= 1000)
    {
        if (diffvec < 7300)
        {
            vy = 63 - (diffvec - 1000) / 100;
        }
        else
        {
            diffvec = 7300;
            vy = 0;
        }
    }

    GV_SubVec3(pos, &GM_PlayerPosition_800ABA10, &vec);
    vecdir = GV_VecDir2(&vec) + 1024;

    out->vx = sub_800321AC(vecdir - gUnkCameraStruct2_800B7868.field_10.vy, diffvec * 31 / 7300);
    out->vy = vy;

    if (vy <= 0)
    {
        return -1;
    }
    return 0;
}

int sub_80032308(SVECTOR *pos, int param_2, DVECTOR *out)
{
    int     vecdir;
    int     diffvec;
    int     vy;
    SVECTOR vec, eye;
    int     vecdirsub;

    sub_8003214C(&eye, &vecdirsub);
    diffvec = GV_DiffVec3(&eye, pos) - param_2;
    if (diffvec < 0)
    {
        diffvec = 0;
        vy = 63;
    }
    else
    {
        vy = 63;
    }

    if (diffvec < 9500)
    {
        vy = 63 - diffvec / 150;
    }
    else
    {
        diffvec = 9500;
        vy = 0;
    }

    diffvec *= 4;
    if (diffvec > 9500)
    {
        diffvec = 9500;
    }

    GV_SubVec3(pos, &eye, &vec);
    vecdir = GV_VecDir2(&vec) + 1024;

    out->vx = sub_800321AC(vecdir - vecdirsub, diffvec * 31 / 9500);
    out->vy = vy;

    if (vy <= 0)
    {
        return -1;
    }
    return 0;
}

int sub_80032420(SVECTOR *pos, int param_2, DVECTOR *out)
{
    int     vecdir;
    int     diffvec;
    int     vy;
    SVECTOR vec;

    diffvec = GV_DiffVec3(&GM_PlayerPosition_800ABA10, pos) - param_2;
    if (diffvec < 0)
    {
        diffvec = 0;
        vy = 63;
    }
    else
    {
        vy = 63;
    }

    if (diffvec >= 3000)
    {
        if (diffvec < 7700)
        {
            vy = 63 - (diffvec - 3000) / 200;
        }
        else
        {
            diffvec = 7700;
            vy = 39;
        }
    }

    GV_SubVec3(pos, &GM_PlayerPosition_800ABA10, &vec);
    vecdir = GV_VecDir2(&vec) + 1024;

    out->vx = sub_800321AC(vecdir - gUnkCameraStruct2_800B7868.field_10.vy, diffvec * 31 / 7700);
    out->vy = vy;

    if (vy <= 0)
    {
        return -1;
    }
    return 0;
}

int sub_80032534(SVECTOR *pos, int param_2, DVECTOR *out)
{
    int     vecdir;
    int     diffvec;
    int     vy;
    SVECTOR vec, vec2;
    int     vecdirsub;

    sub_8003214C(&vec2, &vecdirsub);
    diffvec = GV_DiffVec3(&vec2, pos) - param_2;
    if (diffvec < 0)
    {
        diffvec = 0;
        vy = 63;
    }
    else
    {
        vy = 63;
    }

    if (diffvec >= 2000)
    {
        if (diffvec < 9050)
        {
            vy = 63 - (diffvec - 2000) / 300;
        }
        else
        {
            diffvec = 9050;
            vy = 39;
        }
    }

    diffvec *= 4;
    if (diffvec > 9050)
    {
        diffvec = 9050;
    }

    GV_SubVec3(pos, &vec2, &vec);
    vecdir = GV_VecDir2(&vec) + 1024;

    out->vx = sub_800321AC(vecdir - vecdirsub, diffvec * 31 / 9050);
    out->vy = vy;

    if (vy <= 0)
    {
        return -1;
    }
    return 0;
}

int sub_8003265C(DVECTOR *out, SVECTOR *pos, int param_3)
{
    if ((GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_05 | GAME_FLAG_BIT_07)) == 0 && GM_Camera_800B77E8.field_22 == 0)
    {
        if (sub_800321F8(pos, param_3, out) < 0)
        {
            return -1;
        }
    }

    else if (sub_80032308(pos, param_3, out) < 0)
    {
        return -1;
    }

    return 0;
}

int sub_800326D4(DVECTOR *out, SVECTOR *pos)
{
    if (((GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_05 | GAME_FLAG_BIT_07)) == 0) && GM_Camera_800B77E8.field_22 == 0)
    {
        if (sub_800321F8(pos, 0, out) < 0)
        {
            return -1;
        }
    }
    else if (sub_80032308(pos, 0, out) < 0)
    {
        return -1;
    }

    return 0;
}

int sub_80032748(DVECTOR *out, SVECTOR *pos)
{
    if (((GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_05 | GAME_FLAG_BIT_07)) == 0) && GM_Camera_800B77E8.field_22 == 0)
    {
        if (sub_80032420(pos, 0, out) < 0)
        {
            return -1;
        }
    }
    else if (sub_80032534(pos, 0, out) < 0)
    {
        return -1;
    }

    return 0;
}


int sub_800327BC(DVECTOR *a1, SVECTOR *a2)
{
    if ((GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_05 | GAME_FLAG_BIT_07)) == 0 && GM_Camera_800B77E8.field_22 == 0)
    {
        return -1;
    }

    if (sub_80032308(a2, 0, a1) < 0)
    {
        return -1;
    }

    return 0;
}

int sub_80032820(DVECTOR *out, SVECTOR *pos)
{
  if (sub_80032308(pos, 0, out) < 0)
  {
      return -1;
  }

  return 0;
}

// play sound effect at pos by id
void GM_SeSet_80032858(SVECTOR *pos, unsigned int se_id)
{
    DVECTOR point;

    if (pos)
    {
        if (se_id == SE_EXP_05)
        {
            if (sub_80032748(&point, pos) < 0)
            {
                return;
            }
        }
        else if (se_id >= 160 && se_id <= 167)
        {
            if (sub_800327BC(&point, pos) < 0)
            {
                return;
            }
        }
        else if (se_id == SE_MOUSTEP2)
        {
            if (sub_80032820(&point, pos) < 0)
            {
                return;
            }
        }
        else
        {
            if (sub_800326D4(&point, pos) < 0)
            {
                return;
            }
        }
    }
    else
    {
        point.vy = 63;
        point.vx = 0;
    }

    GM_Sound(point.vx, point.vy, se_id);
}

void GM_SeSet2_80032968(int x_pos, int y_pos, int se_id)
{
    GM_Sound(x_pos, y_pos, se_id);
}

void GM_SeSetMode_800329C4( SVECTOR *pos, int se_id, int mode )
{
    DVECTOR point;

    if ( pos )
    {
        switch ( mode )
        {
        case GM_SEMODE_BOMB:
            if ( sub_80032748( &point, pos ) < 0 )
            {
                return;
            }
            break;

        case GM_SEMODE_REAL:
            if ( sub_800327BC( &point, pos ) < 0 )
            {
                return;
            }
            break;

        case GM_SEMODE_CAMERA:
            if ( sub_80032820( &point, pos ) < 0 )
            {
                return;
            }
            break;

        case GM_SEMODE_NORMAL:
            if ( sub_800326D4( &point, pos ) < 0 )
            {
                return;
            }
            break;
        }
    }
    else
    {
        point.vy = 63;
        point.vx = 0;
    }

    GM_Sound(point.vx, point.vy, se_id);
}

void sub_80032AEC(int x_pos, int y_pos, int se_id)
{
    int mask_id;

    if (!(GM_GameStatus_800AB3CC & GAME_IN_DEMO))
    {
        x_pos &= 0xff;
        y_pos &= 0xff;
        if (y_pos > 63)
        {
            y_pos = 63;
        }
        mask_id = se_id & 0xff;
        sd_set_cli(((x_pos << 16) | (y_pos << 8) | mask_id), 0);
    }
}

void sub_80032B40(SVECTOR *pos, unsigned int se_id, int y_pos)
{
    DVECTOR dvec;

    sub_800326D4(&dvec, pos);
    GM_Sound(dvec.vx, y_pos, se_id);
}

void sub_80032BC4(SVECTOR *pos, unsigned int se_id, int param_3) // GM_SeSetPan
{
    DVECTOR dvec;

    if (sub_8003265C(&dvec, pos, param_3) >= 0)
    {
        GM_Sound(dvec.vx, dvec.vy, se_id);
    }
}

void GM_Sound_80032C48(int sound_code, int sync_mode)
{
    sd_set_cli(sound_code, sync_mode);
}
