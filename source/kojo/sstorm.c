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

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"
#include "anime/animconv/anime.h"

#include "common.h"

/******************************************************************************
 * definitions and typedefs and structures
 */

typedef struct tagSNOWSTORM
{
    GV_ACT      actor;
    int         nName;
    int         nMap;
    SVECTOR     svectMin;
    SVECTOR     svectMax;
    int         nDivisor;
    int         nSStormRaise;
    BOOL        bActive;
    int         nTime;
    SVECTOR     svectPos;
    ANIMATION   animation;
    char        script[80];
    PRESCRIPT   preScript;
} SNOWSTORM, *PSNOWSTORM, *LPSNOWSTORM;

/******************************************************************************
 * locals
 */

static char sstorm_script[] = {
    0x00,0x10,0x01,0x00, 0x05,0x01,0xFE,0x0C,
    0x00,0x00,0x01,0xFF, 0x08,0x00,0x00,0x00,
    0x02,0x00,0x01,0x0D, 0x0F
};

/******************************************************************************
 * functions
 */

static void Act(LPSNOWSTORM lpAct);
static void Die(LPSNOWSTORM lpAct);
static int CheckMessage(u_short name, int n_mes_list, u_short *mes_list);

/******************************************************************************
 * publics
 */

void* NewSnowStorm(int nName, int nMap)
{
    LPSNOWSTORM lpAct;
    SVECTOR     svectPos;
    SVECTOR     svectRotate;
    char*       lpstrParam;

    if((lpAct = GV_NewActor(GV_ACTOR_USER, sizeof(SNOWSTORM))) == NULL)
        return NULL;

    GV_SetNamedActor(&lpAct->actor, Act, Die, "sstorm.c");

    lpAct->bActive = TRUE;
    lpAct->nDivisor = 4;
    lpAct->nName = nName;
    lpAct->nMap = nMap;
    lpAct->nSStormRaise = 2000;

    if(GCL_GetOption('a'))
    {
        if((lpstrParam = GCL_NextStr()) != NULL)
            lpAct->svectMin.vx = GCL_StrToInt(lpstrParam);
        if((lpstrParam = GCL_NextStr()) != NULL)
            lpAct->svectMin.vy = GCL_StrToInt(lpstrParam);
        if((lpstrParam = GCL_NextStr()) != NULL)
            lpAct->svectMin.vz = GCL_StrToInt(lpstrParam);
        if((lpstrParam = GCL_NextStr()) != NULL)
            lpAct->svectMax.vx = GCL_StrToInt(lpstrParam);
        if((lpstrParam = GCL_NextStr()) != NULL)
            lpAct->svectMax.vy = GCL_StrToInt(lpstrParam);
        if((lpstrParam = GCL_NextStr()) != NULL)
            lpAct->svectMax.vz = GCL_StrToInt(lpstrParam);
    }

    if(GCL_GetOption('e'))
    {
        if((lpstrParam = GCL_NextStr()) != NULL)
            lpAct->nDivisor = GCL_StrToInt(lpstrParam);
        if((lpstrParam = GCL_NextStr()) != NULL)
            lpAct->nSStormRaise = GCL_StrToInt(lpstrParam);
    }

    if(GCL_GetOption('p'))
    {
        if((lpstrParam = GCL_NextStr()) != NULL)
            svectRotate.vx = GCL_StrToInt(lpstrParam) * 4096 / 360;
        if((lpstrParam = GCL_NextStr()) != NULL)
            svectRotate.vy = GCL_StrToInt(lpstrParam) * 4096 / 360;
        if((lpstrParam = GCL_NextStr()) != NULL)
            svectRotate.vz = GCL_StrToInt(lpstrParam) * 4096 / 360;
        if((lpstrParam = GCL_NextStr()) != NULL)
        {
            svectPos.vx = 0;
            svectPos.vy = 0;
            svectPos.vz = 0;
            DG_SetPos2(&svectPos, &svectRotate);
            svectPos.vz = GCL_StrToInt(lpstrParam) / 3;
            DG_PutVector(&svectPos, &svectPos, 1);
            lpAct->svectPos.vx = svectPos.vx;
            lpAct->svectPos.vy = svectPos.vy;
            lpAct->svectPos.vz = svectPos.vz;
        }
    }

    lpAct->animation.size_w = lpAct->svectMax.vx - lpAct->svectMin.vx;
    lpAct->animation.size_w = __max(lpAct->animation.size_w, lpAct->svectMax.vy - lpAct->svectMin.vy);
    lpAct->animation.size_w = __max(lpAct->animation.size_w, lpAct->svectMax.vz - lpAct->svectMin.vz);
    lpAct->animation.texdev_x = 1;
    lpAct->animation.texdev_y = 1;
    lpAct->animation.n_anime = 1;
    lpAct->animation.unit_num = 1;
    lpAct->animation.amb = 3;
    lpAct->animation.v = 255;
    lpAct->animation.pre_script = &lpAct->preScript;
    lpAct->animation.script = lpAct->script;
    lpAct->animation.raise = lpAct->nSStormRaise;
    lpAct->animation.size_h = lpAct->animation.size_w;

    return (void*)lpAct;
}

/******************************************************************************
 * statics
 */

static void Act(
    LPSNOWSTORM lpAct)
{
    VECTOR  vectPos;
    SVECTOR svectSpeed;
    SVECTOR svectRotate;
    u_short mes_list[2];
    int     length, lo, hi;
    u_int   xw;

    GM_CurrentMap = lpAct->nMap;
    lpAct->nTime++;

    mes_list[0] = GV_StrCode("run");
    mes_list[1] = GV_StrCode("stop");

    switch(CheckMessage(lpAct->nName, 2, mes_list))
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

    if((lpAct->bActive == FALSE) || ((lpAct->nTime % lpAct->nDivisor) != 0))
        return;

    if(GM_lpsvectWind == NULL)
        lpAct->preScript.speed = lpAct->svectPos;
    else
        lpAct->preScript.speed = *GM_lpsvectWind;

    vectPos.vx = lpAct->svectMin.vx + (rand() & 255) * (lpAct->svectMax.vx - lpAct->svectMin.vx) / 256;
    vectPos.vy = lpAct->svectMin.vy + (rand() & 255) * (lpAct->svectMax.vy - lpAct->svectMin.vy) / 256;
    vectPos.vz = lpAct->svectMin.vz + (rand() & 255) * (lpAct->svectMax.vz - lpAct->svectMin.vz) / 256;

    svectSpeed = lpAct->preScript.speed;
    svectSpeed.vx = ABS(svectSpeed.vx);
    svectSpeed.vy = ABS(svectSpeed.vy);
    svectSpeed.vz = ABS(svectSpeed.vz);

    if((svectSpeed.vx > svectSpeed.vy) && (svectSpeed.vz < svectSpeed.vx))
    {
        if(lpAct->preScript.speed.vx < 0)
            vectPos.vx = lpAct->svectMax.vx + lpAct->animation.size_w / 4;
        else
            vectPos.vx = lpAct->svectMin.vx - lpAct->animation.size_w / 4;
    }
    else if((svectSpeed.vy > svectSpeed.vx) && (svectSpeed.vz < svectSpeed.vy))
    {
        if(lpAct->preScript.speed.vy < 0)
            vectPos.vy = lpAct->svectMax.vy + lpAct->animation.size_w / 4;
        else
            vectPos.vy = lpAct->svectMin.vy - lpAct->animation.size_w / 4;
    }
    else
    {
        if(lpAct->preScript.speed.vz < 0)
            vectPos.vz = lpAct->svectMax.vz + lpAct->animation.size_w / 4;
        else
            vectPos.vz = lpAct->svectMin.vz - lpAct->animation.size_w / 4;
    }

    vectPos.vx += GM_PlayerPosition.vx;
    vectPos.vy += GM_PlayerPosition.vy;
    vectPos.vz += GM_PlayerPosition.vz;

    if(GM_PlayerStatus & PLAYER_WATCH)
    {
        svectSpeed.vx = gUnkCameraStruct2_800B7868.target.vx - gUnkCameraStruct2_800B7868.position.vx;
        svectSpeed.vy = gUnkCameraStruct2_800B7868.target.vy - gUnkCameraStruct2_800B7868.position.vy;
        svectSpeed.vz = gUnkCameraStruct2_800B7868.target.vz - gUnkCameraStruct2_800B7868.position.vz;

        svectRotate.vx = -ratan2(svectSpeed.vy, SquareRoot0(svectSpeed.vx * svectSpeed.vx + svectSpeed.vz * svectSpeed.vz));
        svectRotate.vy = ratan2(svectSpeed.vx, svectSpeed.vz);
        svectRotate.vz = 0;

        memset(&svectSpeed, 0x00, sizeof(SVECTOR));
        DG_SetPos2(&svectSpeed, &svectRotate);

        svectSpeed.vz = lpAct->animation.size_w * 2 / 3;
        DG_PutVector(&svectSpeed, &svectSpeed, 1);

        vectPos.vx += svectSpeed.vx;
        vectPos.vy += svectSpeed.vy;
        vectPos.vz += svectSpeed.vz;
    }

    vectPos.vx = __min(vectPos.vx, 32000);
    vectPos.vx = __max(vectPos.vx, -32000);
    vectPos.vy = __min(vectPos.vy, 32000);
    vectPos.vy = __max(vectPos.vy, -32000);
    vectPos.vz = __min(vectPos.vz, 32000);
    vectPos.vz = __max(vectPos.vz, -32000);

    lpAct->preScript.pos.vx = vectPos.vx;
    lpAct->preScript.pos.vy = vectPos.vy;
    lpAct->preScript.pos.vz = vectPos.vz;

    length = SquareRoot0(
        lpAct->preScript.speed.vx * lpAct->preScript.speed.vx +
        lpAct->preScript.speed.vy * lpAct->preScript.speed.vy +
        lpAct->preScript.speed.vz * lpAct->preScript.speed.vz);

    memcpy(lpAct->script, sstorm_script, sizeof(sstorm_script));
    xw = lpAct->animation.size_w / length + 1;
    lo = xw >> 8;
    hi = (xw & 0xFF) << 8;
    SSTOREL((lo & 0xFF) | hi, &lpAct->script[8]);

    switch(rand() % 3)
    {
    case 0:
        lpAct->animation.tex = GV_StrCode("snow_ex1");
        break;
    case 1:
        lpAct->animation.tex = GV_StrCode("snow_ex2");
        break;
    case 2:
        lpAct->animation.tex = GV_StrCode("snow_ex3");
        break;
    }

    NewAnime(NULL, NULL, &lpAct->animation);
}

static void Die(
    LPSNOWSTORM lpAct)
{
    /* do nothing */
}

/******************************************************************************
 */
static int CheckMessage( u_short name, int n_mes_list, u_short *mes_list )
{
    GV_MSG *msg;
    int found, n_msg, i;

    found = -1;
    n_msg = GV_ReceiveMessage( name, &msg );

    for ( ; n_msg > 0; n_msg--, msg++ )
    {
        for ( i = 0; i < n_mes_list; i++ )
        {
            if ( msg->message[ 0 ] == mes_list[ i ] ) found = i;
        }
    }

    return found;
}
