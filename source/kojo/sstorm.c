/******************************************************************************
 * System   : METALGEAR^3 for PlayStation
 * Computer : PlayStation
 * OS       : PlayStation
 * Compiler : psyq
 * Module   : 雪嵐
 */

/******************************************************************************
 * included
 */

#include "sstorm.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "anime/animconv/anime.h"
#include "game/game.h"

extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;

/******************************************************************************
 * definitions and typedefs and structures
 */

typedef struct tagSNOWSTORM
{
    GV_ACT      actor;
    int         field_20;
    int         field_24;
    short       field_28;
    short       field_2A;
    short       field_2C;
    short       field_2E;
    short       field_30;
    short       field_32;
    short       field_34;
    short       field_36;
    int         field_38;
    int         field_3C;
    BOOL        bActive;
    int         field_44;
    SVECTOR     field_48;
    ANIMATION   anime;
    char        field_6C[21];
    int         field_84;
    int         field_88;
    int         field_8C;
    int         field_90;
    int         field_94;
    int         field_98;
    int         field_9C;
    int         field_A0;
    int         field_A4;
    int         field_A8;
    int         field_AC;
    int         field_B0;
    int         field_B4;
    int         field_B8;
    PRESCRIPT   pre_script;
} SNOWSTORM, *LPSNOWSTORM;

/******************************************************************************
 * locals
 */

static char s11i_dword_800C36B4[] = {
    0x00,0x10,0x01,0x00, 0x05,0x01,0xFE,0x0C,
    0x00,0x00,0x01,0xFF, 0x08,0x00,0x00,0x00,
    0x02,0x00,0x01,0x0D, 0x0F
};

/******************************************************************************
 * functions
 */

static void Act(LPSNOWSTORM lpAct);
static void Die(LPSNOWSTORM lpAct);
static int CheckMessage(unsigned short name, int nhashes, unsigned short *hashes);

/******************************************************************************
 * publics
 */

void *NewSnowStorm(int arg0, int arg1)
{
    LPSNOWSTORM lpAct;
    SVECTOR     svec1, svec2;
    short       field_30;
    int         xw, xw2;
    char       *param;

    lpAct = GV_NewActor(GV_ACTOR_USER, sizeof(SNOWSTORM));
    if (lpAct == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&lpAct->actor, Act, Die, "sstorm.c");

    lpAct->bActive = TRUE;
    lpAct->field_38 = 4;
    lpAct->field_20 = arg0;
    lpAct->field_24 = arg1;
    lpAct->field_3C = 2000;

    if (GCL_GetOption('a'))
    {
        param = GCL_NextStr();
        if (param)
        {
            lpAct->field_28 = GCL_StrToInt(param);
        }
        param = GCL_NextStr();
        if (param)
        {
            lpAct->field_2A = GCL_StrToInt(param);
        }
        param = GCL_NextStr();
        if (param)
        {
            lpAct->field_2C = GCL_StrToInt(param);
        }
        param = GCL_NextStr();
        if (param)
        {
            lpAct->field_30 = GCL_StrToInt(param);
        }
        param = GCL_NextStr();
        if (param)
        {
            lpAct->field_32 = GCL_StrToInt(param);
        }
        param = GCL_NextStr();
        if (param)
        {
            lpAct->field_34 = GCL_StrToInt(param);
        }
    }

    if (GCL_GetOption('e'))
    {
        param = GCL_NextStr();
        if (param)
        {
            lpAct->field_38 = GCL_StrToInt(param);
        }
        param = GCL_NextStr();
        if (param)
        {
            lpAct->field_3C = GCL_StrToInt(param);
        }
    }

    if (GCL_GetOption('p'))
    {
        param = GCL_NextStr();
        if (param)
        {
            svec2.vx = (GCL_StrToInt(param) << 12) / 360;
        }
        param = GCL_NextStr();
        if (param)
        {
            svec2.vy = (GCL_StrToInt(param) << 12) / 360;
        }
        param = GCL_NextStr();
        if (param)
        {
            svec2.vz = (GCL_StrToInt(param) << 12) / 360;
        }
        param = GCL_NextStr();
        if (param)
        {
            svec1.vx = 0;
            svec1.vy = 0;
            svec1.vz = 0;
            DG_SetPos2(&svec1, &svec2);
            svec1.vz = GCL_StrToInt(param) / 3;
            DG_PutVector(&svec1, &svec1, 1);
            lpAct->field_48.vx = svec1.vx;
            lpAct->field_48.vy = svec1.vy;
            lpAct->field_48.vz = svec1.vz;
        }
    }

    field_30 = lpAct->field_30;
    xw = lpAct->field_32 - lpAct->field_2A;

    lpAct->anime.size_w = field_30 - lpAct->field_28;
    if (xw < lpAct->anime.size_w)
    {
        xw = lpAct->anime.size_w;
    }
    lpAct->anime.size_w = xw;

    xw2 = lpAct->field_34 - lpAct->field_2C;
    if (xw2 < lpAct->anime.size_w)
    {
        xw2 = lpAct->anime.size_w;
    }
    lpAct->anime.size_w = xw2;

    lpAct->anime.texdev_x = 1;
    lpAct->anime.texdev_y = 1;
    lpAct->anime.n_anime = 1;
    lpAct->anime.n_verts = 1;
    lpAct->anime.amb = 3;
    lpAct->anime.v = 0xFF;
    lpAct->anime.pre_script = &lpAct->pre_script;
    lpAct->anime.script = lpAct->field_6C;
    lpAct->anime.raise = lpAct->field_3C;
    lpAct->anime.size_h = lpAct->anime.size_w;

    return (void *)lpAct;
}

/******************************************************************************
 * statics
 */

static void Act(LPSNOWSTORM lpAct)
{
    VECTOR         vect;
    SVECTOR        svect1;
    SVECTOR        svect2;
    unsigned short mesg_list[2];
    int            div;
    unsigned int   xw;
    int            lhs, rhs;

    GM_CurrentMap = lpAct->field_24;
    lpAct->field_44++;

    mesg_list[0] = GV_StrCode("run");
    mesg_list[1] = GV_StrCode("stop");

    switch (CheckMessage(lpAct->field_20, COUNTOF(mesg_list), mesg_list))
    {
    case 0:
        lpAct->bActive = TRUE;
        printf("s-end\n");
        break;
    case 1:
        lpAct->bActive = FALSE;
        printf("s-start\n");
        break;
    }

    if (lpAct->bActive == FALSE || lpAct->field_44 % lpAct->field_38 != 0)
    {
        return;
    }

    if (GM_lpsvectWind == NULL)
    {
        lpAct->pre_script.speed = lpAct->field_48;
    }
    else
    {
        lpAct->pre_script.speed = *GM_lpsvectWind;
    }
    vect.vx = lpAct->field_28 + (rand() & 0xFF) * (lpAct->field_30 - lpAct->field_28) / 256;
    vect.vy = lpAct->field_2A + (rand() & 0xFF) * (lpAct->field_32 - lpAct->field_2A) / 256;
    vect.vz = lpAct->field_2C + (rand() & 0xFF) * (lpAct->field_34 - lpAct->field_2C) / 256;

    svect1 = lpAct->pre_script.speed;
    svect1.vx = svect1.vx < 0 ? -svect1.vx : svect1.vx;
    svect1.vy = svect1.vy < 0 ? -svect1.vy : svect1.vy;
    svect1.vz = svect1.vz < 0 ? -svect1.vz : svect1.vz;

    if (svect1.vx > svect1.vy && svect1.vz < svect1.vx)
    {
        if (lpAct->pre_script.speed.vx < 0)
        {
            vect.vx = lpAct->field_30 + lpAct->anime.size_w / 4;
        }
        else
        {
            vect.vx = lpAct->field_28 - lpAct->anime.size_w / 4;
        }
    }
    else if (svect1.vy > svect1.vx && svect1.vz < svect1.vy)
    {
        if (lpAct->pre_script.speed.vy < 0)
        {
            vect.vy = lpAct->field_32 + lpAct->anime.size_w / 4;
        }
        else
        {
            vect.vy = lpAct->field_2A - lpAct->anime.size_w / 4;
        }
    }
    else
    {
        if (lpAct->pre_script.speed.vz < 0)
        {
            vect.vz = lpAct->field_34 + lpAct->anime.size_w / 4;
        }
        else
        {
            vect.vz = lpAct->field_2C - lpAct->anime.size_w / 4;
        }
    }

    vect.vx += GM_PlayerPosition.vx;
    vect.vy += GM_PlayerPosition.vy;
    vect.vz += GM_PlayerPosition.vz;

    if (GM_PlayerStatus & PLAYER_WATCH)
    {
        svect1.vx = gUnkCameraStruct2_800B7868.target.vx - gUnkCameraStruct2_800B7868.position.vx;
        svect1.vy = gUnkCameraStruct2_800B7868.target.vy - gUnkCameraStruct2_800B7868.position.vy;
        svect1.vz = gUnkCameraStruct2_800B7868.target.vz - gUnkCameraStruct2_800B7868.position.vz;

        svect2.vx = -ratan2(svect1.vy, SquareRoot0(svect1.vx * svect1.vx + svect1.vz * svect1.vz));
        svect2.vy = ratan2(svect1.vx, svect1.vz);
        svect2.vz = 0;

        memset(&svect1, 0, sizeof(SVECTOR));
        DG_SetPos2(&svect1, &svect2);

        svect1.vz = (lpAct->anime.size_w * 2) / 3;
        DG_PutVector(&svect1, &svect1, 1);

        vect.vx += svect1.vx;
        vect.vy += svect1.vy;
        vect.vz += svect1.vz;
    }
    vect.vx = MIN(vect.vx, 32000);
    vect.vx = MAX(vect.vx, -32000);
    vect.vy = MIN(vect.vy, 32000);
    vect.vy = MAX(vect.vy, -32000);
    vect.vz = MIN(vect.vz, 32000);
    vect.vz = MAX(vect.vz, -32000);

    lpAct->pre_script.pos.vx = vect.vx;
    lpAct->pre_script.pos.vy = vect.vy;
    lpAct->pre_script.pos.vz = vect.vz;

    div = SquareRoot0(lpAct->pre_script.speed.vx * lpAct->pre_script.speed.vx +
                      lpAct->pre_script.speed.vy * lpAct->pre_script.speed.vy +
                      lpAct->pre_script.speed.vz * lpAct->pre_script.speed.vz);
    memcpy(lpAct->field_6C, s11i_dword_800C36B4, 21);
    xw = lpAct->anime.size_w / div + 1;

    lhs = xw >> 8;
    rhs = (xw & 0xFF) << 8;
    *(short *)&lpAct->field_6C[8] = (lhs & 0xFF) | rhs;

    switch (rand() % 3)
    {
    case 0:
        lpAct->anime.tex = GV_StrCode("snow_ex1");
        break;
    case 1:
        lpAct->anime.tex = GV_StrCode("snow_ex2");
        break;
    case 2:
        lpAct->anime.tex = GV_StrCode("snow_ex3");
        break;
    }
    NewAnime(NULL, NULL, &lpAct->anime);
}

static void Die(LPSNOWSTORM lpAct)
{
    /* do nothing */
}

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
