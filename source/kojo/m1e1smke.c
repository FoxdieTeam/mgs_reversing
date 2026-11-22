/******************************************************************************
 * System   : METALGEAR^3 for PlayStation
 * Computer : PlayStation
 * OS       : PlayStation
 * Compiler : psyq
 * Module   : 
 */

/******************************************************************************
 * included
 */

#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include "game/game.h"

#include "common.h"
#include "m1e1.h"

#include "bullet/blast.h"       // for AN_Blast_high2
#include "okajima/splash2.h"    // for NewSplash2_800DB5E4

/* in anime/effect/m1e1.c */
extern void sub_8007DC24(SVECTOR *pos);
extern void sub_8007DD80(short param_1, SVECTOR *pos);
extern void sub_8007DF10(SVECTOR *rot, SVECTOR *trans);
extern void sub_8007E0AC(int y, SVECTOR *pos);

/******************************************************************************
 * definitions and typedefs and structures
 */

typedef struct tagM1E1SMOKEACT
{
    GV_ACT  actor;
    int     nMap;
    int     nType;
    SVECTOR svectPos;
    SVECTOR svectRot;
    int     nTime1;
    int     nTime2;
} M1E1SMOKEACT, *PM1E1SMOKEACT, *LPM1E1SMOKEACT;

/******************************************************************************
 * functions
 */

static void Act(LPM1E1SMOKEACT lpAct);
static void Die(LPM1E1SMOKEACT lpAct);

/******************************************************************************
 * publics
 */

void* NewM1E1Smoke(
    int      nType,
    SVECTOR* lpsvectPos,
    SVECTOR* lpsvectRot)
{
    LPM1E1SMOKEACT lpAct;

    if((lpAct = GV_NewActor(GV_ACTOR_PREV, sizeof(M1E1SMOKEACT))) == NULL)
        return NULL;

    lpAct->nType = nType;
    lpAct->nMap = GM_CurrentMap;
    lpAct->svectPos = *lpsvectPos;
    lpAct->svectRot = *lpsvectRot;
    lpAct->nTime2 = 0;

    switch(lpAct->nType)
    {
    case 0:
        lpAct->nTime1 = 60;
        break;
    case 1:
        lpAct->nTime1 = 10;
        break;
    }

    GV_SetNamedActor(&lpAct->actor, Act, Die, "m1e1smke.c");
    return (void*)lpAct;
}

/******************************************************************************
 * statics
 */

static void Act(
    LPM1E1SMOKEACT lpAct)
{
    SVECTOR svect1;

    GM_SetCurrentMap(lpAct->nMap);

    switch(lpAct->nType)
    {
    case 0:
        if(lpAct->nTime1 == 57)
            sub_8007DF10(&lpAct->svectRot, &lpAct->svectPos);

        if((lpAct->nTime2 / 4 * 4) == lpAct->nTime2 - 1)
        {
            if(lpAct->nTime1 >= 36)
                sub_8007E0AC(lpAct->svectRot.vy, &lpAct->svectPos);
        }

        if((lpAct->nTime2 & 3) == 0)
        {
            if(lpAct->nTime1 >= 41)
                sub_8007DD80(lpAct->svectRot.vy, &lpAct->svectPos);
        }
        break;

    case 1:
        if(lpAct->nTime1 == 5)
        {
            DG_SetPos2(&DG_ZeroVector, &lpAct->svectRot);

            memset(&svect1, 0x00, sizeof(SVECTOR));
            svect1.vx = -227;
            DG_RotatePos(&svect1);

            memset(&svect1, 0x00, sizeof(SVECTOR));
            svect1.vz = 600;
            DG_PutVector(&svect1, &svect1, 1);

            AN_Blast_high2(&lpAct->svectPos, &svect1);
        }

        if(lpAct->nTime1 >= 7)
            NewSplash2_800DB5E4(&lpAct->svectRot, &lpAct->svectPos);
        if((lpAct->nTime2 & 3) == 0)
            sub_8007DC24(&lpAct->svectPos);
        break;
    }

    if(--lpAct->nTime1 < 0)
        GV_DestroyActor(lpAct);

    if((lpAct->nTime1 & 1) == 0)
        lpAct->nTime2++;
}

static void Die(
    LPM1E1SMOKEACT lpAct)
{
    /* do nothing */
}
