#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Anime/animconv/anime.h"
#include "Game/game.h"
#include "Game/camera.h"

typedef struct SStormWork
{
    GV_ACT    actor;
    int       field_20;
    int       field_24;
    short     field_28;
    short     field_2A;
    short     field_2C;
    short     field_2E;
    short     field_30;
    short     field_32;
    short     field_34;
    short     field_36;
    int       field_38;
    int       field_3C;
    int       field_40;
    int       field_44;
    SVECTOR   field_48;
    ANIMATION field_50;
    char      field_6C[21];
    int       field_84;
    int       field_88;
    int       field_8C;
    int       field_90;
    int       field_94;
    int       field_98;
    int       field_9C;
    int       field_A0;
    int       field_A4;
    int       field_A8;
    int       field_AC;
    int       field_B0;
    int       field_B4;
    int       field_B8;
    PRESCRIPT field_BC;
} SStormWork;

#define EXEC_LEVEL GV_ACTOR_LEVEL5

int s11i_dword_800C36B4[] = {0x00011000, 0x0CFE0105, 0xFF010000, 0x00000008, 0x0D010002};
char s11i_dword_800C36C8[] = {0xF}; // FIXME: this is a part of s11i_dword_800C36B4[]

extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;

void SStormAct_800D478C(SStormWork *);
void SStormDie_800D4E90(SStormWork *);

void *NewSStorm_800D43D8(int arg0, int arg1)
{
    SStormWork *work;
    SVECTOR     svec1, svec2;
    short       field_30;
    int         xw, xw2;
    char       *param;

    work = GV_NewActor(EXEC_LEVEL, sizeof(SStormWork));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, SStormAct_800D478C, SStormDie_800D4E90, "sstorm.c");

    work->field_40 = 1;
    work->field_38 = 4;
    work->field_20 = arg0;
    work->field_24 = arg1;
    work->field_3C = 2000;

    if (GCL_GetOption('a'))
    {
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_28 = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_2A = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_2C = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_30 = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_32 = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_34 = GCL_StrToInt(param);
        }
    }

    if (GCL_GetOption('e'))
    {
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_38 = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param)
        {
            work->field_3C = GCL_StrToInt(param);
        }
    }

    if (GCL_GetOption('p'))
    {
        param = GCL_GetParamResult();
        if (param)
        {
            svec2.vx = (GCL_StrToInt(param) << 12) / 360;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            svec2.vy = (GCL_StrToInt(param) << 12) / 360;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            svec2.vz = (GCL_StrToInt(param) << 12) / 360;
        }
        param = GCL_GetParamResult();
        if (param)
        {
            svec1.vx = 0;
            svec1.vy = 0;
            svec1.vz = 0;
            DG_SetPos2(&svec1, &svec2);
            svec1.vz = GCL_StrToInt(param) / 3;
            DG_PutVector(&svec1, &svec1, 1);
            work->field_48.vx = svec1.vx;
            work->field_48.vy = svec1.vy;
            work->field_48.vz = svec1.vz;
        }
    }

    field_30 = work->field_30;
    xw = work->field_32 - work->field_2A;

    work->field_50.field_E_xw = field_30 - work->field_28;
    if (xw < work->field_50.field_E_xw)
    {
        xw = work->field_50.field_E_xw;
    }
    work->field_50.field_E_xw = xw;

    xw2 = work->field_34 - work->field_2C;
    if (xw2 < work->field_50.field_E_xw)
    {
        xw2 = work->field_50.field_E_xw;
    }
    work->field_50.field_E_xw = xw2;

    work->field_50.field_2 = 1;
    work->field_50.field_4 = 1;
    work->field_50.n_anims = 1;
    work->field_50.n_vertices = 1;
    work->field_50.field_C = 3;
    work->field_50.field_12_rgb = 0xFF;
    work->field_50.pre_script = &work->field_BC;
    work->field_50.field_18_ptr = work->field_6C;
    work->field_50.field_A = work->field_3C;
    work->field_50.field_10_yh = work->field_50.field_E_xw;

    return (void *)work;
}

int SStorm_ReceiveMessage_800D4E98(unsigned short name, int nhashes, unsigned short *hashes);

void SStormAct_800D478C(SStormWork *work)
{
    VECTOR         sp10;
    SVECTOR        sp20;
    SVECTOR        sp28;
    unsigned short hashes[2];
    int            div;
    unsigned int   xw;
    int            lhs, rhs;

    GM_CurrentMap = work->field_24;
    work->field_44++;

    hashes[0] = GV_StrCode("run");
    hashes[1] = GV_StrCode("stop");

    switch (SStorm_ReceiveMessage_800D4E98(work->field_20, 2, hashes))
    {
    case 0:
        work->field_40 = 1;
        printf("s-end\n");
        break;
    case 1:
        work->field_40 = 0;
        printf("s-start\n");
        break;
    }

    if (work->field_40 == 0 || work->field_44 % work->field_38 != 0)
    {
        return;
    }

    if (GM_lpsvectWind == NULL)
    {
        work->field_BC.speed = work->field_48;
    }
    else
    {
        work->field_BC.speed = *GM_lpsvectWind;
    }
    sp10.vx = work->field_28 + (rand() & 0xFF) * (work->field_30 - work->field_28) / 256;
    sp10.vy = work->field_2A + (rand() & 0xFF) * (work->field_32 - work->field_2A) / 256;
    sp10.vz = work->field_2C + (rand() & 0xFF) * (work->field_34 - work->field_2C) / 256;

    sp20 = work->field_BC.speed;
    sp20.vx = sp20.vx < 0 ? -sp20.vx : sp20.vx;
    sp20.vy = sp20.vy < 0 ? -sp20.vy : sp20.vy;
    sp20.vz = sp20.vz < 0 ? -sp20.vz : sp20.vz;

    if (sp20.vx > sp20.vy && sp20.vz < sp20.vx)
    {
        if (work->field_BC.speed.vx < 0)
        {
            sp10.vx = work->field_30 + work->field_50.field_E_xw / 4;
        }
        else
        {
            sp10.vx = work->field_28 - work->field_50.field_E_xw / 4;
        }
    }
    else if (sp20.vy > sp20.vx && sp20.vz < sp20.vy)
    {
        if (work->field_BC.speed.vy < 0)
        {
            sp10.vy = work->field_32 + work->field_50.field_E_xw / 4;
        }
        else
        {
            sp10.vy = work->field_2A - work->field_50.field_E_xw / 4;
        }
    }
    else
    {
        if (work->field_BC.speed.vz < 0)
        {
            sp10.vz = work->field_34 + work->field_50.field_E_xw / 4;
        }
        else
        {
            sp10.vz = work->field_2C - work->field_50.field_E_xw / 4;
        }
    }

    sp10.vx += GM_PlayerPosition.vx;
    sp10.vy += GM_PlayerPosition.vy;
    sp10.vz += GM_PlayerPosition.vz;

    if (GM_PlayerStatus & PLAYER_WATCH)
    {
        sp20.vx = gUnkCameraStruct2_800B7868.center.vx - gUnkCameraStruct2_800B7868.eye.vx;
        sp20.vy = gUnkCameraStruct2_800B7868.center.vy - gUnkCameraStruct2_800B7868.eye.vy;
        sp20.vz = gUnkCameraStruct2_800B7868.center.vz - gUnkCameraStruct2_800B7868.eye.vz;

        sp28.vx = -ratan2(sp20.vy, SquareRoot0(sp20.vx * sp20.vx + sp20.vz * sp20.vz));
        sp28.vy = ratan2(sp20.vx, sp20.vz);
        sp28.vz = 0;

        memset(&sp20, 0, sizeof(SVECTOR));
        DG_SetPos2(&sp20, &sp28);

        sp20.vz = (work->field_50.field_E_xw * 2) / 3;
        DG_PutVector(&sp20, &sp20, 1);

        sp10.vx += sp20.vx;
        sp10.vy += sp20.vy;
        sp10.vz += sp20.vz;
    }
    sp10.vx = sp10.vx < 32000 ? sp10.vx : 32000;
    sp10.vx = sp10.vx > -32000 ? sp10.vx : -32000;
    sp10.vy = sp10.vy < 32000 ? sp10.vy : 32000;
    sp10.vy = sp10.vy > -32000 ? sp10.vy : -32000;
    sp10.vz = sp10.vz < 32000 ? sp10.vz : 32000;
    sp10.vz = sp10.vz > -32000 ? sp10.vz : -32000;

    work->field_BC.pos.vx = sp10.vx;
    work->field_BC.pos.vy = sp10.vy;
    work->field_BC.pos.vz = sp10.vz;

    div = SquareRoot0(work->field_BC.speed.vx * work->field_BC.speed.vx +
                      work->field_BC.speed.vy * work->field_BC.speed.vy +
                      work->field_BC.speed.vz * work->field_BC.speed.vz);
    memcpy(work->field_6C, s11i_dword_800C36B4, 21);
    xw = work->field_50.field_E_xw / div + 1;

    lhs = xw >> 8;
    rhs = (xw & 0xFF) << 8;
    *(short *)&work->field_6C[8] = (lhs & 0xFF) | rhs;

    switch (rand() % 3)
    {
    case 0:
        work->field_50.field_0_texture_hash = GV_StrCode("snow_ex1");
        break;
    case 1:
        work->field_50.field_0_texture_hash = GV_StrCode("snow_ex2");
        break;
    case 2:
        work->field_50.field_0_texture_hash = GV_StrCode("snow_ex3");
        break;
    }
    NewAnime(NULL, NULL, &work->field_50);
}

void SStormDie_800D4E90(SStormWork *work)
{
}

// Less optimized version of d03a_red_alrt_800C437C (lol)
int SStorm_ReceiveMessage_800D4E98(unsigned short name, int nhashes, unsigned short *hashes)
{
    GV_MSG *msg;
    int     nmsgs;
    int     found;
    int     i;

    found = -1;
    nmsgs = GV_ReceiveMessage(name, &msg);

    for (; nmsgs > 0; nmsgs--, msg++)
    {
        for (i = 0; i < nhashes; i++)
        {
            if (msg->message[0] == hashes[i])
            {
                found = i;
            }
        }
    }

    return found;
}
