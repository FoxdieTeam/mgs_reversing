#include "psyq.h"
#include "game.h"
#include "SD/sound.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Game/camera.h"

extern SVECTOR          GM_PlayerPosition_800ABA10;
extern GM_Camera        GM_Camera_800B77E8;
extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;

void sub_8003214C(SVECTOR *pVec, int *pRet)
{
    MATRIX *mtx;

    mtx = &DG_Chanl(0)->field_30_eye;
    pVec->vx = mtx->t[0];
    pVec->vy = mtx->t[1];
    pVec->vz = mtx->t[2];
    *pRet = ratan2(mtx->m[0][2], mtx->m[2][2]);
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

    diffvec = GV_DiffVec3_80016E84(&GM_PlayerPosition_800ABA10, pos) - param_2;
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

    GV_SubVec3_80016D40(pos, &GM_PlayerPosition_800ABA10, &vec);
    vecdir = GV_VecDir2_80016EF8(&vec) + 1024;

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
    SVECTOR vec, vec2;
    int     vecdirsub;

    sub_8003214C(&vec2, &vecdirsub);
    diffvec = GV_DiffVec3_80016E84(&vec2, pos) - param_2;
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

    GV_SubVec3_80016D40(pos, &vec2, &vec);
    vecdir = GV_VecDir2_80016EF8(&vec) + 1024;

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

    diffvec = GV_DiffVec3_80016E84(&GM_PlayerPosition_800ABA10, pos) - param_2;
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

    GV_SubVec3_80016D40(pos, &GM_PlayerPosition_800ABA10, &vec);
    vecdir = GV_VecDir2_80016EF8(&vec) + 1024;

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
    diffvec = GV_DiffVec3_80016E84(&vec2, pos) - param_2;
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

    GV_SubVec3_80016D40(pos, &vec2, &vec);
    vecdir = GV_VecDir2_80016EF8(&vec) + 1024;

    out->vx = sub_800321AC(vecdir - vecdirsub, diffvec * 31 / 9050);
    out->vy = vy;

    if (vy <= 0)
    {
        return -1;
    }
    return 0;
}

int sub_8003265C(DVECTOR *param_1, SVECTOR *param_2, int param_3)
{
    if ((GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_05 | GAME_FLAG_BIT_07)) == 0 && GM_Camera_800B77E8.field_22 == 0)
    {
        if (sub_800321F8(param_2, param_3, param_1) < 0)
        {
            return -1;
        }
    }

    else if (sub_80032308(param_2, param_3, param_1) < 0)
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
void GM_SeSet_80032858(SVECTOR *pos, unsigned int sound_id)
{
    DVECTOR point;

    if (pos)
    {
        if (sound_id == 41)
        {
            if (sub_80032748(&point, pos) < 0)
            {
                return;
            }
        }
        else if (sound_id - 160 < 8)
        {
            if (sub_800327BC(&point, pos) < 0)
            {
                return;
            }
        }
        else if (sound_id == 29)
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

    GM_Sound(point.vx, point.vy, sound_id);
}

void GM_SeSet2_80032968(int byte_2, int byte_1, int byte_0)
{
    GM_Sound(byte_2, byte_1, byte_0);
}

//GM_SeSetPan ?
void       GM_Sound_800329C4( SVECTOR *arg0, int arg1, int arg2 )
{
    DVECTOR sp10;
    int     x, y, z;

    if ( arg0 )
    {
        switch ( arg2 )
        {
        case 1:
            if ( sub_80032748( &sp10, arg0 ) < 0 )
            {
                return;
            }
            break;

        case 2:
            if ( sub_800327BC( &sp10, arg0 ) < 0 )
            {
                return;
            }
            break;

        case 3:
            if ( sub_80032820( &sp10, arg0 ) < 0 )
            {
                return;
            }
            break;
        case 0:
            if ( sub_800326D4( &sp10, arg0 ) < 0 )
            {
                return;
            }
            break;
        }
    }
    else
    {
        sp10.vy = 0x3F;
        sp10.vx = 0;
    }

    x = sp10.vx;
    y = sp10.vy;
    if ( !( GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_27 | GAME_FLAG_BIT_32) ) )
    {
        y &= 0xFF;
        x &= 0xFF;
        if ( y >= 0x40 )
        {
            y = 0x3F;
        }
        z = arg1 & 0xff;
        sd_set_cli_800887EC( ( ( x << 0x10 ) | ( y << 8 ) ) | z, 0 );
    }
}

void sub_80032AEC(int byte_2, int byte_1, int byte_0)
{
    int lowest_byte;
    if (GM_GameStatus_800AB3CC > -1)
    {
        byte_2 &= 0xff;
        byte_1 &= 0xff;
        if (0x3f < byte_1)
        {
            byte_1 = 0x3f;
        }
        lowest_byte = byte_0 & 0xff;
        sd_set_cli_800887EC(byte_2 << 0x10 | byte_1 << 8 | lowest_byte, 0);
    }
}

void sub_80032B40(SVECTOR *svec, unsigned int param_2, int param_3)
{
    int     vx, vz;
    DVECTOR dvec;

    sub_800326D4(&dvec, svec);
    vx = dvec.vx;
    if (!(GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_27 | GAME_FLAG_BIT_32)))
    {
        vx &= 0xff;
        param_3 &= 0xff;
        if (param_3 > 63)
        {
            param_3 = 63;
        }
        vz = param_2 & 0xff;
        sd_set_cli_800887EC((vx << 16) | (param_3 << 8) | vz, 0);
    }
}

void sub_80032BC4(SVECTOR *svec, unsigned int param_2, int param_3)
{
    int     vx, vy, vz;
    DVECTOR dvec;

    if (sub_8003265C(&dvec, svec, param_3) >= 0)
    {
        vx = dvec.vx;
        vy = dvec.vy;
        if (!(GM_GameStatus_800AB3CC & (GAME_FLAG_BIT_27 | GAME_FLAG_BIT_32)))
        {
            vx &= 0xff;
            vy &= 0xff;
            if (vy > 63)
            {
                vy = 63;
            }

            vz = param_2 & 0xff;
            sd_set_cli_800887EC((vx << 16) | (vy << 8) | vz, 0);
        }
    }
}

void GM_Sound_80032C48(int code, int notUsed)
{
    sd_set_cli_800887EC(code, notUsed);
}
