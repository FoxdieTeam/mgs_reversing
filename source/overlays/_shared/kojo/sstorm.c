#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "anime/animconv/anime.h"
#include "game/game.h"

extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL GV_ACTOR_LEVEL5

typedef struct _Work
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
    ANIMATION anime;
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
    PRESCRIPT pre_script;
} Work;

/*---------------------------------------------------------------------------*/

static char s11i_dword_800C36B4[] = {
    0x00,0x10,0x01,0x00, 0x05,0x01,0xFE,0x0C,
    0x00,0x00,0x01,0xFF, 0x08,0x00,0x00,0x00,
    0x02,0x00,0x01,0x0D, 0x0F
};

/*---------------------------------------------------------------------------*/

static void Act(Work *);
static void Die(Work *);
static int CheckMessage(unsigned short name, int nhashes, unsigned short *hashes);

void *NewSnowStorm(int arg0, int arg1)
{
    Work       *work;
    SVECTOR     svec1, svec2;
    short       field_30;
    int         xw, xw2;
    char       *param;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, Act, Die, "sstorm.c");

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

    work->anime.field_E_xw = field_30 - work->field_28;
    if (xw < work->anime.field_E_xw)
    {
        xw = work->anime.field_E_xw;
    }
    work->anime.field_E_xw = xw;

    xw2 = work->field_34 - work->field_2C;
    if (xw2 < work->anime.field_E_xw)
    {
        xw2 = work->anime.field_E_xw;
    }
    work->anime.field_E_xw = xw2;

    work->anime.field_2 = 1;
    work->anime.field_4 = 1;
    work->anime.n_anims = 1;
    work->anime.n_vertices = 1;
    work->anime.field_C = 3;
    work->anime.field_12_rgb = 0xFF;
    work->anime.pre_script = &work->pre_script;
    work->anime.field_18_ptr = work->field_6C;
    work->anime.field_A = work->field_3C;
    work->anime.field_10_yh = work->anime.field_E_xw;

    return (void *)work;
}

/*---------------------------------------------------------------------------*/

static void Act(Work *work)
{
    VECTOR         sp10;
    SVECTOR        sp20;
    SVECTOR        sp28;
    unsigned short mesg_list[2];
    int            div;
    unsigned int   xw;
    int            lhs, rhs;

    GM_CurrentMap = work->field_24;
    work->field_44++;

    mesg_list[0] = GV_StrCode("run");
    mesg_list[1] = GV_StrCode("stop");

    switch (CheckMessage(work->field_20, COUNTOF(mesg_list), mesg_list))
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
        work->pre_script.speed = work->field_48;
    }
    else
    {
        work->pre_script.speed = *GM_lpsvectWind;
    }
    sp10.vx = work->field_28 + (rand() & 0xFF) * (work->field_30 - work->field_28) / 256;
    sp10.vy = work->field_2A + (rand() & 0xFF) * (work->field_32 - work->field_2A) / 256;
    sp10.vz = work->field_2C + (rand() & 0xFF) * (work->field_34 - work->field_2C) / 256;

    sp20 = work->pre_script.speed;
    sp20.vx = sp20.vx < 0 ? -sp20.vx : sp20.vx;
    sp20.vy = sp20.vy < 0 ? -sp20.vy : sp20.vy;
    sp20.vz = sp20.vz < 0 ? -sp20.vz : sp20.vz;

    if (sp20.vx > sp20.vy && sp20.vz < sp20.vx)
    {
        if (work->pre_script.speed.vx < 0)
        {
            sp10.vx = work->field_30 + work->anime.field_E_xw / 4;
        }
        else
        {
            sp10.vx = work->field_28 - work->anime.field_E_xw / 4;
        }
    }
    else if (sp20.vy > sp20.vx && sp20.vz < sp20.vy)
    {
        if (work->pre_script.speed.vy < 0)
        {
            sp10.vy = work->field_32 + work->anime.field_E_xw / 4;
        }
        else
        {
            sp10.vy = work->field_2A - work->anime.field_E_xw / 4;
        }
    }
    else
    {
        if (work->pre_script.speed.vz < 0)
        {
            sp10.vz = work->field_34 + work->anime.field_E_xw / 4;
        }
        else
        {
            sp10.vz = work->field_2C - work->anime.field_E_xw / 4;
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

        sp20.vz = (work->anime.field_E_xw * 2) / 3;
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

    work->pre_script.pos.vx = sp10.vx;
    work->pre_script.pos.vy = sp10.vy;
    work->pre_script.pos.vz = sp10.vz;

    div = SquareRoot0(work->pre_script.speed.vx * work->pre_script.speed.vx +
                      work->pre_script.speed.vy * work->pre_script.speed.vy +
                      work->pre_script.speed.vz * work->pre_script.speed.vz);
    memcpy(work->field_6C, s11i_dword_800C36B4, 21);
    xw = work->anime.field_E_xw / div + 1;

    lhs = xw >> 8;
    rhs = (xw & 0xFF) << 8;
    *(short *)&work->field_6C[8] = (lhs & 0xFF) | rhs;

    switch (rand() % 3)
    {
    case 0:
        work->anime.field_0_texture_hash = GV_StrCode("snow_ex1");
        break;
    case 1:
        work->anime.field_0_texture_hash = GV_StrCode("snow_ex2");
        break;
    case 2:
        work->anime.field_0_texture_hash = GV_StrCode("snow_ex3");
        break;
    }
    NewAnime(NULL, NULL, &work->anime);
}

static void Die(Work *work)
{
}

/*---------------------------------------------------------------------------*/

// Less optimized version of d03a_red_alrt_800C437C (lol)
static int CheckMessage(unsigned short name, int nhashes, unsigned short *hashes)
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
