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
#include "menu/menuman.h"

#include "common.h"
#include "m1e1.h"

extern void *NewM1Throw(int name);

/******************************************************************************
 * functions
 */

/* m1e1act.c */
extern void M1E1Act(LPM1E1ACT lpAct);
extern void M1E1Die(LPM1E1ACT lpAct);

/* m1e1sold.c */
extern int M1E1SoldierActControl();
extern int M1E1SoldierActObject();
extern int M1E1SoldierBombHoming();
extern int M1E1SoldierBombBound();
extern int M1E1SoldierBombExplosion();

/******************************************************************************
 * locals
 */

LPM1E1ACT s05a_dword_800C362C = NULL;
int s05a_dword_800C3630 = 0;
int s05a_dword_800C3634 = 0;
int s05a_dword_800C3638 = 0;

/******************************************************************************
 * publics
 */

void *NewM1E1(int nName, int nMap)
{
    LPM1E1ACT lpAct;
    char*     param;
    SVECTOR   svec;
    int       strcode;
    int       flag;
    int       s1;

    if((lpAct = GV_NewActor(GV_ACTOR_USER, sizeof(M1E1ACT))) == NULL)
        return NULL;

    lpAct->bInitialize = TRUE;
    GV_SetNamedActor(lpAct, M1E1Act, M1E1Die, "m1e1.c");
    lpAct->nName = nName;
    lpAct->nMap = nMap;

    if(GM_InitControl(&lpAct->control, 0, nMap) < 0)
    {
        GV_DestroyActor(lpAct);
        return NULL;
    }

    lpAct->light[0].t[0] = 255;
    lpAct->light[0].t[1] = 255;
    lpAct->light[0].t[2] = 255;

    if(GCL_GetOption('e'))
    {
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_D5C = GCL_StrToInt(param) * 1000 / 60 * 100 / 180;
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_D60 = GCL_StrToInt(param) / 30;
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_D64 = GCL_StrToInt(param) * 1000 / 60 * 100 / 180;
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_D68 = GCL_StrToInt(param) / 30;
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_D6C = GCL_StrToInt(param) / 30;

        if(lpAct->field_D64 > lpAct->field_D5C)
            lpAct->field_D64 = lpAct->field_D5C;

        if(lpAct->field_D68 > lpAct->field_D60)
            lpAct->field_D68 = lpAct->field_D60;
    }

    if(GCL_GetOption('d'))
    {
        lpAct->field_D84 = 1;

        if ((param = GCL_NextStr()) != NULL)
            lpAct->field_D70 = GCL_StrToInt(param);
        if ((param = GCL_NextStr()) != NULL)
            lpAct->field_D74 = GCL_StrToInt(param);
        if ((param = GCL_NextStr()) != NULL)
            lpAct->field_D78 = GCL_StrToInt(param);
        if ((param = GCL_NextStr()) != NULL)
            lpAct->field_D7C = GCL_StrToInt(param) * 1000 / 60 * 100 / 180;
        if ((param = GCL_NextStr()) != NULL)
            lpAct->field_D80 = GCL_StrToInt(param) / 30;
        if ((param = GCL_NextStr()) != NULL)
            lpAct->field_D84 = GCL_StrToInt(param);

        if(lpAct->field_D84 <= 0)
            lpAct->field_D84 = 1;

        if((param = GCL_NextStr()) != NULL)
            lpAct->field_D88 = GCL_StrToInt(param) * 1000 / 60 * 100 / 180;
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_D8C = GCL_StrToInt(param) / 30;
    }

    if(GCL_GetOption('s'))
    {
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_D94 = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_D90 = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_D98 = GCL_StrToInt(param) * 1000 / 60 * 100 / 23040;
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_D9C = GCL_StrToInt(param) * 1000 / 60 * 100 / 23040;
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DA0 = GCL_StrToInt(param);

        lpAct->field_E24 = lpAct->field_D94 - lpAct->field_D90;
        lpAct->field_E28 = lpAct->field_D98 - lpAct->field_D9C;

        if(lpAct->field_E28 <= 0)
            lpAct->field_E28 = 1;
    }

    if(GCL_GetOption('g'))
    {
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DA4 = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DA8 = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DAC = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DB0 = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DB4 = GCL_StrToInt(param) * 1000000 / 108000;
    }

    if(GCL_GetOption('c'))
    {
        param = GCL_NextStr();
        if (param) lpAct->field_DB8 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_DBC = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_DC0 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_DC4 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_DC8 = GCL_StrToInt(param) * 1000000 / 108000;
    }

    if(GCL_GetOption('p'))
    {
        if((param = GCL_NextStr()) != NULL)
            lpAct->control.mov.vx = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->control.mov.vy = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->control.mov.vz = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->control.turn.vx = GCL_StrToInt(param) * 4096 / 360;
        if((param = GCL_NextStr()) != NULL)
            lpAct->control.turn.vy = GCL_StrToInt(param) * 4096 / 360;
        if((param = GCL_NextStr()) != NULL)
            lpAct->control.turn.vz = GCL_StrToInt(param) * 4096 / 360;
        if((param = GCL_NextStr()) != NULL)
        {
            svec.vx = 0;
            svec.vy = 0;
            svec.vz = 0;
            DG_SetPos2(&svec, &lpAct->control.turn);
            svec.vz = GCL_StrToInt(param) * 1000000 / 108000 * 16;
            DG_PutVector(&svec, &svec, 1);
            lpAct->field_E34.vx = svec.vx;
            lpAct->field_E34.vy = svec.vy;
            lpAct->field_E34.vz = svec.vz;
        }
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DCC.pad = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DCC.vx = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DCC.vy = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DCC.vz = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DD4.pad = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DD4.vx = GCL_StrToInt(param) * 4096 / 360;
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DD4.vy = GCL_StrToInt(param) * 4096 / 360;
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DD4.vz = GCL_StrToInt(param) * 4096 / 360;
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DE2 = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DDC = GCL_StrToInt(param) * 4096 / 360;
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DDE = GCL_StrToInt(param) * 4096 / 360;
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DE0 = GCL_StrToInt(param) * 4096 / 360;
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DEA = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DE4 = GCL_StrToInt(param) * 4096 / 360;
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DE6 = GCL_StrToInt(param) * 4096 / 360;
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DE8 = GCL_StrToInt(param) * 4096 / 360;
    }

    if(GCL_GetOption('w'))
    {
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_E04 = GCL_StrToInt(param) * 1000000 / 108000;
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_E08 = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_E0C = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_E10 = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_E14 = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_E18 = GCL_StrToInt(param);
    }

    if(GCL_GetOption('o'))
    {
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DEC = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DF0 = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DF4 = GCL_StrToInt(param) * 4096 / 720;
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DF8 = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_DFC = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_E00 = GCL_StrToInt(param);
    }
    else
    {
        lpAct->field_DEC = 2;
        lpAct->field_DF0 = 4;
        lpAct->field_DF4 = 796;
        lpAct->field_DF8 = 12000;
        lpAct->field_DFC = 2;
        lpAct->field_E00 = 1;
    }

    if(GCL_GetOption('z'))
    {
        lpAct->field_E1C = -1;
        lpAct->field_E20 = -1;

        if((param = GCL_NextStr()) != NULL)
            lpAct->field_E1C = GCL_StrToInt(param);
        if((param = GCL_NextStr()) != NULL)
            lpAct->field_E20 = GCL_StrToInt(param);
    }

    lpAct->control.r_sphere = -2;
    lpAct->control.interp = 0;
    GM_ConfigControlAttribute(&lpAct->control, 5);
    strcode = GV_StrCode("m1e1");
    GM_InitObject(&lpAct->objBody, strcode, 0x2D, 0);
    GM_ConfigObjectJoint(&lpAct->objBody);
    GM_ConfigObjectLight(&lpAct->objBody, &lpAct->light[0]);
    DG_InvisibleObjs(lpAct->objBody.objs);

    strcode = GV_StrCode("m1e1cl1");
    GM_InitObject(&lpAct->objLeftCater[0], strcode, 0x2D, 0);
    GM_ConfigObjectJoint(&lpAct->objLeftCater[0]);
    GM_ConfigObjectLight(&lpAct->objLeftCater[0], &lpAct->light[0]);
    DG_InvisibleObjs(lpAct->objLeftCater[0].objs);

    strcode = GV_StrCode("m1e1cl2");
    GM_InitObject(&lpAct->objLeftCater[1], strcode, 0x2D, 0);
    GM_ConfigObjectJoint(&lpAct->objLeftCater[1]);
    GM_ConfigObjectLight(&lpAct->objLeftCater[1], &lpAct->light[0]);
    DG_InvisibleObjs(lpAct->objLeftCater[1].objs);

    strcode = GV_StrCode("m1e1cl3");
    GM_InitObject(&lpAct->objLeftCater[2], strcode, 0x2D, 0);
    GM_ConfigObjectJoint(&lpAct->objLeftCater[2]);
    GM_ConfigObjectLight(&lpAct->objLeftCater[2], &lpAct->light[0]);
    DG_InvisibleObjs(lpAct->objLeftCater[2].objs);

    strcode = GV_StrCode("m1e1cr1");
    GM_InitObject(&lpAct->objRightCater[0], strcode, 0x2D, 0);
    GM_ConfigObjectJoint(&lpAct->objRightCater[0]);
    GM_ConfigObjectLight(&lpAct->objRightCater[0], &lpAct->light[0]);
    DG_InvisibleObjs(lpAct->objRightCater[0].objs);

    strcode = GV_StrCode("m1e1cr2");
    GM_InitObject(&lpAct->objRightCater[1], strcode, 0x2D, 0);
    GM_ConfigObjectJoint(&lpAct->objRightCater[1]);
    GM_ConfigObjectLight(&lpAct->objRightCater[1], &lpAct->light[0]);
    DG_InvisibleObjs(lpAct->objRightCater[1].objs);

    strcode = GV_StrCode("m1e1cr3");
    GM_InitObject(&lpAct->objRightCater[2], strcode, 0x2D, 0);
    GM_ConfigObjectJoint(&lpAct->objRightCater[2]);
    GM_ConfigObjectLight(&lpAct->objRightCater[2], &lpAct->light[0]);
    DG_InvisibleObjs(lpAct->objRightCater[2].objs);
    lpAct->nCaterLength = 0x53;
    lpAct->field_F44 = lpAct->field_DA8 >> 1;
    lpAct->field_F48 = lpAct->field_DB8 >> 1;

    lpAct->svectLeftCater.vx =
        (u_short)lpAct->objLeftCater[0].objs->objs[0].model->lx +
        ((lpAct->objLeftCater[0].objs->objs[0].model->ux -
          lpAct->objLeftCater[0].objs->objs[0].model->lx) / 2);
    lpAct->svectRightCater.vx =
        (u_short)lpAct->objRightCater[0].objs->objs[0].model->lx +
        ((lpAct->objRightCater[0].objs->objs[0].model->ux -
          lpAct->objRightCater[0].objs->objs[0].model->lx) / 2);
    DG_SetPos2(&lpAct->control.mov, &lpAct->control.rot);
    DG_PutVector(&lpAct->svectLeftCater, &lpAct->svectLeftCater, 1);
    DG_PutVector(&lpAct->svectRightCater, &lpAct->svectRightCater, 1);

    DG_VisibleObjs(lpAct->objLeftCater[lpAct->field_E74].objs);
    DG_VisibleObjs(lpAct->objRightCater[lpAct->field_E78].objs);
    if(lpAct->field_E08 > 0)
    {
        lpAct->lpM1Throw = NewM1Throw(GV_StrCode("throw"));
        flag = 0x150;
        lpAct->nState = 1;
        GM_lpfnPlayerActControl = (int (*)(GV_ACT *))M1E1SoldierActControl;
        GM_lpfnPlayerActObject2 = (int (*)(GV_ACT *))M1E1SoldierActObject;
        GM_lpfnBombHoming       = (int (*)(CONTROL *, int, int *))M1E1SoldierBombHoming;
        GM_lpfnBombBound        = (int (*)(int, CONTROL *, int *))M1E1SoldierBombBound;
        GM_lpfnBombExplosion    = (int (*)(TARGET *, int))M1E1SoldierBombExplosion;
    }
    else
    {
        lpAct->nState = 6;
        if(lpAct->field_DCC.pad)
            lpAct->control.mov = lpAct->field_DCC;
        if(lpAct->field_DD4.pad)
            lpAct->control.turn = lpAct->field_DD4;
        if(lpAct->field_DE2)
        {
            lpAct->objBody.rots[3].vy = lpAct->field_DDE;
            lpAct->objBody.rots[5].vx = lpAct->field_DDC;
            lpAct->objBody.rots[11].vx = lpAct->field_DE8;
        }
        if(lpAct->field_DEA)
        {
            short t;
            t = (svec.vy = lpAct->field_DE6);
            if (t < -0xE3) { svec.vy = t; t = -0xE3; }
            svec.vy = t;
            if (t >= 0xE4) t = 0xE3;
            svec.vy = t;
            lpAct->objBody.rots[13].vy = t;
            t = lpAct->field_DE6 - svec.vy;
            svec.vy = t;
            if (t < -0x155) t = -0x155;
            svec.vy = t;
            if (t >= 0x71D) t = 0x71C;
            svec.vy = t;
            lpAct->objBody.rots[12].vy = t;
            lpAct->objBody.rots[13].vx = lpAct->field_DE4;
        }
        flag = 0x100;
    }

    lpAct->bbox[0].vx = lpAct->objBody.objs->objs[0].model->lx;
    lpAct->bbox[0].vy = lpAct->objBody.objs->objs[0].model->ly;
    lpAct->bbox[0].vz = lpAct->objBody.objs->objs[0].model->lz;
    lpAct->bbox[1].vx = lpAct->objBody.objs->objs[0].model->ux;
    lpAct->bbox[1].vy = lpAct->objBody.objs->objs[0].model->uy;
    lpAct->bbox[1].vz = lpAct->objBody.objs->objs[0].model->uz;
    if(lpAct->bbox[0].vy < 600)
        lpAct->bbox[0].vy = 600;
    if(lpAct->bbox[1].vy < lpAct->bbox[0].vy)
        lpAct->bbox[1].vy = lpAct->bbox[0].vy;

    lpAct->bbox[2].vx = lpAct->objBody.objs->objs[2].model->lx;
    lpAct->bbox[2].vy = lpAct->objBody.objs->objs[2].model->ly;
    lpAct->bbox[2].vz = lpAct->objBody.objs->objs[2].model->lz;
    lpAct->bbox[3].vx = lpAct->objBody.objs->objs[2].model->ux;
    lpAct->bbox[3].vy = lpAct->objBody.objs->objs[2].model->uy;
    lpAct->bbox[3].vz = lpAct->objBody.objs->objs[2].model->uz;
    if(lpAct->bbox[2].vy < 600)
        lpAct->bbox[2].vy = 600;
    if(lpAct->bbox[3].vy < lpAct->bbox[2].vy)
        lpAct->bbox[3].vy = lpAct->bbox[2].vy;

    lpAct->bbox[4].vx = lpAct->objLeftCater[0].objs->objs[0].model->lx;
    lpAct->bbox[4].vy = lpAct->objLeftCater[0].objs->objs[0].model->ly;
    lpAct->bbox[4].vz = lpAct->objLeftCater[0].objs->objs[0].model->lz;
    lpAct->bbox[5].vx = lpAct->objLeftCater[0].objs->objs[0].model->ux;
    lpAct->bbox[5].vy = lpAct->objLeftCater[0].objs->objs[0].model->uy;
    lpAct->bbox[5].vz = lpAct->objLeftCater[0].objs->objs[0].model->uz;
    if(lpAct->bbox[4].vy < 600)
        lpAct->bbox[4].vy = 600;
    if(lpAct->bbox[5].vy < lpAct->bbox[4].vy)
        lpAct->bbox[5].vy = lpAct->bbox[4].vy;

    lpAct->bbox[6].vx = lpAct->objRightCater[0].objs->objs[0].model->lx;
    lpAct->bbox[6].vy = lpAct->objRightCater[0].objs->objs[0].model->ly;
    lpAct->bbox[6].vz = lpAct->objRightCater[0].objs->objs[0].model->lz;
    lpAct->bbox[7].vx = lpAct->objRightCater[0].objs->objs[0].model->ux;
    lpAct->bbox[7].vy = lpAct->objRightCater[0].objs->objs[0].model->uy;
    lpAct->bbox[7].vz = lpAct->objRightCater[0].objs->objs[0].model->uz;
    if(lpAct->bbox[6].vy < 600)
        lpAct->bbox[6].vy = 600;
    if(lpAct->bbox[7].vy < lpAct->bbox[6].vy)
        lpAct->bbox[7].vy = lpAct->bbox[6].vy;

    lpAct->bbox[8].vx = lpAct->objBody.objs->objs[4].model->lx + 0xC8;
    lpAct->bbox[8].vy = lpAct->objBody.objs->objs[4].model->ly;
    lpAct->bbox[8].vz = lpAct->objBody.objs->objs[4].model->lz;
    lpAct->bbox[9].vx = lpAct->objBody.objs->objs[4].model->ux - 0xC8;
    lpAct->bbox[9].vy = lpAct->objBody.objs->objs[4].model->uy;
    lpAct->bbox[9].vz = lpAct->objBody.objs->objs[4].model->uz - 0x2BC;

    lpAct->bbox[10].vy = lpAct->objBody.objs->objs[5].model->ly - 0x1F4;
    lpAct->bbox[10].vz = lpAct->objBody.objs->objs[5].model->lz;
    lpAct->bbox[11].vx = lpAct->objBody.objs->objs[5].model->ux;
    lpAct->bbox[11].vy = lpAct->objBody.objs->objs[5].model->uy + 0x12C;
    lpAct->bbox[11].vz = lpAct->objBody.objs->objs[5].model->uz - 0x12C;
    lpAct->bbox[10].vx = -lpAct->bbox[11].vx;

    if(lpAct->nState == 6)
    {
        lpAct->bbox[0].vy = 0;
        lpAct->bbox[2].vy = 0;
        lpAct->bbox[4].vy = 0;
        lpAct->bbox[6].vy = 0;
        lpAct->bbox[10].vy = 0;
    }
    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[0].seg[0], flag);
    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[0].seg[1], flag);
    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[0].seg[2], flag);
    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[0].seg[3], flag);
    HZD_QueueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[0].flr[0]);
    HZD_QueueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[0].flr[1]);

    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[1].seg[0], flag);
    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[1].seg[1], flag);
    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[1].seg[2], flag);
    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[1].seg[3], flag);
    HZD_QueueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[1].flr[0]);
    HZD_QueueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[1].flr[1]);

    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[2].seg[0], flag);
    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[2].seg[1], flag);
    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[2].seg[2], flag);
    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[2].seg[3], flag);
    HZD_QueueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[2].flr[0]);
    HZD_QueueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[2].flr[1]);

    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[3].seg[0], flag);
    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[3].seg[1], flag);
    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[3].seg[2], flag);
    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[3].seg[3], flag);
    HZD_QueueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[3].flr[0]);
    HZD_QueueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[3].flr[1]);

    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[4].seg[0], flag);
    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[4].seg[1], flag);
    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[4].seg[2], flag);
    HZD_QueueDynamicSegment2(lpAct->control.map->hzd, &lpAct->hzdBlock[4].seg[3], flag);
    HZD_QueueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[4].flr[0]);
    HZD_QueueDynamicFloor(lpAct->control.map->hzd, &lpAct->hzdBlock[4].flr[1]);

    for(s1 = 0; s1 < 8; s1++)
    {
        lpAct->objBody.objs->objs[s1].world = DG_ZeroMatrix;
    }

    s05a_dword_800C362C = lpAct;
    lpAct->control.rot.vx = lpAct->control.turn.vx;
    lpAct->control.rot.vy = lpAct->control.turn.vy;
    lpAct->control.rot.vz = lpAct->control.turn.vz;

    if(lpAct->nState == 6)
        return (void*)lpAct;

    {
        char    *q;
        int      off2;

        lpAct->nLeftCaterDirection = 999;
        lpAct->nRightCaterDirection = 999;
        lpAct->field_A80 =
            (lpAct->objLeftCater[0].objs->objs[0].model->ux -
             lpAct->objLeftCater[0].objs->objs[0].model->lx) / 3;

        s1 = 0;
        svec.vx = (u_short)lpAct->field_A80;
        svec.vz = (u_short)lpAct->field_A80;
        svec.vy = 600;
        for (; s1 < 10; s1++)
        {
            TARGET *t = GM_AllocTarget();
            lpAct->lpTarget[s1] = t;
            GM_SetTarget(t, 0xC, 2, &svec);
            GM_SetPowerTarget(lpAct->lpTarget[s1], 1, -1, 10000, 0, &DG_ZeroVector);
        }

        svec.vy = 50;
        s1 = 0;
        {
            SVECTOR *zv = &DG_ZeroVector;
            off2 = 0xA84;
            for (; s1 < 10; s1++)
            {
                q = (char *)lpAct + off2;
                GM_SetTarget((TARGET *)q, 4, 2, &svec);
                GM_SetPowerTarget((TARGET *)q, 1, 2, lpAct->field_DA0, 0, zv);
                off2 += 0x48;
            }
        }

        lpAct->field_8C8 =
            (lpAct->objBody.objs->objs[0].model->ux -
             lpAct->objBody.objs->objs[0].model->lx) / 3;
        lpAct->field_95C =
            (lpAct->objBody.objs->objs[0].model->ux -
             lpAct->objBody.objs->objs[0].model->lx) >> 2;
        svec.vx = (u_short)lpAct->field_8C8;
        svec.vz = (u_short)lpAct->field_8C8;
        svec.vy =
            (lpAct->objBody.objs->objs[0].model->uy -
             lpAct->objBody.objs->objs[0].model->ly) / 6;
        GM_SetTarget(&lpAct->target0, 4, 2, &svec);
        GM_SetTarget(&lpAct->target1, 4, 2, &svec);
        svec.vx = (u_short)lpAct->field_95C;
        svec.vz = (u_short)lpAct->field_95C;
        GM_SetTarget(&lpAct->target2, 4, 2, &svec);
        GM_SetTarget(&lpAct->target3, 4, 2, &svec);
        GM_SetTarget(&lpAct->target4, 4, 2, &svec);
        GM_SetTarget(&lpAct->target5, 4, 2, &svec);
        GM_SetPowerTarget(&lpAct->target0, 1, 2, 0, 0, &DG_ZeroVector);
        GM_SetPowerTarget(&lpAct->target1, 1, 2, 0, 0, &DG_ZeroVector);
        GM_SetPowerTarget(&lpAct->target2, 1, 2, 0, 0, &DG_ZeroVector);
        GM_SetPowerTarget(&lpAct->target3, 1, 2, 0, 0, &DG_ZeroVector);
        GM_SetPowerTarget(&lpAct->target4, 1, 2, 0, 0, &DG_ZeroVector);
        GM_SetPowerTarget(&lpAct->target5, 1, 2, 0, 0, &DG_ZeroVector);

        memcpy(lpAct->life_name, "GUNNER", 7);
        lpAct->life_conf.name = lpAct->life_name;
        lpAct->life_conf.left[0] = 0x10;
        lpAct->life_conf.left[1] = 0x6F;
        lpAct->life_conf.left[2] = 0x9F;
        lpAct->life_conf.right[0] = 0x1F;
        lpAct->life_conf.right[1] = 0xDF;
        lpAct->life_conf.right[2] = 0x7F;
    }

    return (void*)lpAct;
}
