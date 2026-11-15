#include "game/game.h"
#include "menu/menuman.h"

#include "kojo/common.h"
#include "kojo/m1e1.h"

typedef struct
{
    int         field_0;
    short       field_4;
    signed char field_6;
} GunnerTpl;

extern void  s05a_800D4A74(LPM1E1ACT lpAct);
extern void  s05a_800D5E30(LPM1E1ACT lpAct);
extern void *NewM1Throw(int name);
extern int s05a_800E00EC();
extern int s05a_800E066C();
extern int s05a_800DEDE8();
extern int s05a_800DF834();
extern int s05a_800DF9C8();

extern const char s05a_dword_800E340C[]; /* "m1e1.c" */
extern const char s05a_dword_800E3414[]; /* "m1e1" */
extern const char s05a_dword_800E341C[]; /* "m1e1cl1" */
extern const char s05a_dword_800E3424[]; /* "m1e1cl2" */
extern const char s05a_dword_800E342C[]; /* "m1e1cl3" */
extern const char s05a_dword_800E3434[]; /* "m1e1cr1" */
extern const char s05a_dword_800E343C[]; /* "m1e1cr2" */
extern const char s05a_dword_800E3444[]; /* "m1e1cr3" */
extern const char s05a_dword_800E344C[]; /* "throw" */
extern const GunnerTpl s05a_dword_800E3454; /* "GUNNER\0" @ 0x800E3454 */

extern LPM1E1ACT s05a_dword_800C362C;
extern MATRIX   DG_ZeroMatrix;
extern SVECTOR  DG_ZeroVector;

void *NewM1E1(int name, int where)
{
    LPM1E1ACT lpAct;
    char    *param;
    SVECTOR  svec;
    int      strcode;
    int      flag;
    int      s1;

    lpAct = GV_NewActor(GV_ACTOR_USER, sizeof(M1E1ACT));
    if (lpAct == NULL)
    {
        return NULL;
    }

    lpAct->bInitialize = 1;
    GV_SetNamedActor(lpAct, s05a_800D4A74, s05a_800D5E30, s05a_dword_800E340C);
    lpAct->field_744 = name;
    lpAct->field_748 = where;

    if (GM_InitControl(&lpAct->control, 0, where) < 0)
    {
        GV_DestroyActor(lpAct);
        return NULL;
    }

    lpAct->light[0].t[0] = 0xFF;
    lpAct->light[0].t[1] = 0xFF;
    lpAct->light[0].t[2] = 0xFF;
    if (GCL_GetOption('e'))
    {
        param = GCL_NextStr();
        if (param) lpAct->field_D5C = GCL_StrToInt(param) * 1000 / 60 * 100 / 180;
        param = GCL_NextStr();
        if (param) lpAct->field_D60 = GCL_StrToInt(param) / 30;
        param = GCL_NextStr();
        if (param) lpAct->field_D64 = GCL_StrToInt(param) * 1000 / 60 * 100 / 180;
        param = GCL_NextStr();
        if (param) lpAct->field_D68 = GCL_StrToInt(param) / 30;
        param = GCL_NextStr();
        if (param) lpAct->field_D6C = GCL_StrToInt(param) / 30;
        if (lpAct->field_D64 > lpAct->field_D5C) lpAct->field_D64 = lpAct->field_D5C;
        if (lpAct->field_D68 > lpAct->field_D60) lpAct->field_D68 = lpAct->field_D60;
    }
    if (GCL_GetOption('d'))
    {
        lpAct->field_D84 = 1;
        param = GCL_NextStr();
        if (param) lpAct->field_D70 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_D74 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_D78 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_D7C = GCL_StrToInt(param) * 1000 / 60 * 100 / 180;
        param = GCL_NextStr();
        if (param) lpAct->field_D80 = GCL_StrToInt(param) / 30;
        param = GCL_NextStr();
        if (param) lpAct->field_D84 = GCL_StrToInt(param);
        if (lpAct->field_D84 <= 0) lpAct->field_D84 = 1;
        param = GCL_NextStr();
        if (param) lpAct->field_D88 = GCL_StrToInt(param) * 1000 / 60 * 100 / 180;
        param = GCL_NextStr();
        if (param) lpAct->field_D8C = GCL_StrToInt(param) / 30;
    }
    if (GCL_GetOption('s'))
    {
        param = GCL_NextStr();
        if (param) lpAct->field_D94 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_D90 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_D98 = GCL_StrToInt(param) * 1000 / 60 * 100 / 23040;
        param = GCL_NextStr();
        if (param) lpAct->field_D9C = GCL_StrToInt(param) * 1000 / 60 * 100 / 23040;
        param = GCL_NextStr();
        if (param) lpAct->field_DA0 = GCL_StrToInt(param);
        lpAct->field_E24 = lpAct->field_D94 - lpAct->field_D90;
        lpAct->field_E28 = lpAct->field_D98 - lpAct->field_D9C;
        if (lpAct->field_E28 <= 0) lpAct->field_E28 = 1;
    }
    if (GCL_GetOption('g'))
    {
        param = GCL_NextStr();
        if (param) lpAct->field_DA4 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_DA8 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_DAC = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_DB0 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_DB4 = GCL_StrToInt(param) * 1000000 / 108000;
    }
    if (GCL_GetOption('c'))
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
    if (GCL_GetOption('p'))
    {
        param = GCL_NextStr();
        if (param) lpAct->control.mov.vx = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->control.mov.vy = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->control.mov.vz = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->control.turn.vx = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) lpAct->control.turn.vy = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) lpAct->control.turn.vz = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param)
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
        param = GCL_NextStr();
        if (param) lpAct->field_DCC.pad = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_DCC.vx = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_DCC.vy = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_DCC.vz = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_DD4.pad = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_DD4.vx = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) lpAct->field_DD4.vy = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) lpAct->field_DD4.vz = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) lpAct->field_DE2 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_DDC = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) lpAct->field_DDE = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) lpAct->field_DE0 = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) lpAct->field_DEA = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_DE4 = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) lpAct->field_DE6 = GCL_StrToInt(param) * 4096 / 360;
        param = GCL_NextStr();
        if (param) lpAct->field_DE8 = GCL_StrToInt(param) * 4096 / 360;
    }
    if (GCL_GetOption('w'))
    {
        param = GCL_NextStr();
        if (param) lpAct->field_E04 = GCL_StrToInt(param) * 1000000 / 108000;
        param = GCL_NextStr();
        if (param) lpAct->field_E08 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_E0C = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_E10 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_E14 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_E18 = GCL_StrToInt(param);
    }
    if (GCL_GetOption('o'))
    {
        param = GCL_NextStr();
        if (param) lpAct->field_DEC = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_DF0 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_DF4 = GCL_StrToInt(param) * 4096 / 720;
        param = GCL_NextStr();
        if (param) lpAct->field_DF8 = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_DFC = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_E00 = GCL_StrToInt(param);
    }
    else
    {
        lpAct->field_DEC = 2;
        lpAct->field_DF0 = 4;
        lpAct->field_DF4 = 0x31C;
        lpAct->field_DF8 = 0x2EE0;
        lpAct->field_DFC = 2;
        lpAct->field_E00 = 1;
    }
    if (GCL_GetOption('z'))
    {
        lpAct->field_E1C = -1;
        lpAct->field_E20 = -1;
        param = GCL_NextStr();
        if (param) lpAct->field_E1C = GCL_StrToInt(param);
        param = GCL_NextStr();
        if (param) lpAct->field_E20 = GCL_StrToInt(param);
    }

    lpAct->control.r_sphere = -2;
    lpAct->control.interp = 0;
    GM_ConfigControlAttribute(&lpAct->control, 5);
    strcode = GV_StrCode(s05a_dword_800E3414);
    GM_InitObject(&lpAct->objBody, strcode, 0x2D, 0);
    GM_ConfigObjectJoint(&lpAct->objBody);
    GM_ConfigObjectLight(&lpAct->objBody, &lpAct->light[0]);
    DG_InvisibleObjs(lpAct->objBody.objs);

    strcode = GV_StrCode(s05a_dword_800E341C);
    GM_InitObject(&lpAct->objLeftCater[0], strcode, 0x2D, 0);
    GM_ConfigObjectJoint(&lpAct->objLeftCater[0]);
    GM_ConfigObjectLight(&lpAct->objLeftCater[0], &lpAct->light[0]);
    DG_InvisibleObjs(lpAct->objLeftCater[0].objs);

    strcode = GV_StrCode(s05a_dword_800E3424);
    GM_InitObject(&lpAct->objLeftCater[1], strcode, 0x2D, 0);
    GM_ConfigObjectJoint(&lpAct->objLeftCater[1]);
    GM_ConfigObjectLight(&lpAct->objLeftCater[1], &lpAct->light[0]);
    DG_InvisibleObjs(lpAct->objLeftCater[1].objs);

    strcode = GV_StrCode(s05a_dword_800E342C);
    GM_InitObject(&lpAct->objLeftCater[2], strcode, 0x2D, 0);
    GM_ConfigObjectJoint(&lpAct->objLeftCater[2]);
    GM_ConfigObjectLight(&lpAct->objLeftCater[2], &lpAct->light[0]);
    DG_InvisibleObjs(lpAct->objLeftCater[2].objs);

    strcode = GV_StrCode(s05a_dword_800E3434);
    GM_InitObject(&lpAct->objRightCater[0], strcode, 0x2D, 0);
    GM_ConfigObjectJoint(&lpAct->objRightCater[0]);
    GM_ConfigObjectLight(&lpAct->objRightCater[0], &lpAct->light[0]);
    DG_InvisibleObjs(lpAct->objRightCater[0].objs);

    strcode = GV_StrCode(s05a_dword_800E343C);
    GM_InitObject(&lpAct->objRightCater[1], strcode, 0x2D, 0);
    GM_ConfigObjectJoint(&lpAct->objRightCater[1]);
    GM_ConfigObjectLight(&lpAct->objRightCater[1], &lpAct->light[0]);
    DG_InvisibleObjs(lpAct->objRightCater[1].objs);

    strcode = GV_StrCode(s05a_dword_800E3444);
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
    if (lpAct->field_E08 > 0)
    {
        lpAct->lpM1Throw = NewM1Throw(GV_StrCode(s05a_dword_800E344C));
        flag = 0x150;
        lpAct->field_D54 = 1;
        GM_lpfnPlayerActControl = (int (*)(GV_ACT *))s05a_800E00EC;
        GM_lpfnPlayerActObject2 = (int (*)(GV_ACT *))s05a_800E066C;
        GM_lpfnBombHoming       = (int (*)(CONTROL *, int, int *))s05a_800DEDE8;
        GM_lpfnBombBound        = (int (*)(int, CONTROL *, int *))s05a_800DF834;
        GM_lpfnBombExplosion    = (int (*)(TARGET *, int))s05a_800DF9C8;
    }
    else
    {
        lpAct->field_D54 = 6;
        if (lpAct->field_DCC.pad) lpAct->control.mov = lpAct->field_DCC;
        if (lpAct->field_DD4.pad) lpAct->control.turn = lpAct->field_DD4;
        if (lpAct->field_DE2)
        {
            lpAct->objBody.rots[3].vy = lpAct->field_DDE;
            lpAct->objBody.rots[5].vx = lpAct->field_DDC;
            lpAct->objBody.rots[11].vx = lpAct->field_DE8;
        }
        if (lpAct->field_DEA)
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
    lpAct->bbox[0].vx = lpAct->objBody.objs->objs[0].model->lx; /* F8C */
    lpAct->bbox[0].vy = lpAct->objBody.objs->objs[0].model->ly; /* F8E */
    lpAct->bbox[0].vz = lpAct->objBody.objs->objs[0].model->lz; /* F90 */
    lpAct->bbox[1].vx = lpAct->objBody.objs->objs[0].model->ux; /* F94 */
    lpAct->bbox[1].vy = lpAct->objBody.objs->objs[0].model->uy; /* F96 */
    lpAct->bbox[1].vz = lpAct->objBody.objs->objs[0].model->uz; /* F98 */
    if (lpAct->bbox[0].vy < 0x258) lpAct->bbox[0].vy = 0x258;
    if (lpAct->bbox[1].vy < lpAct->bbox[0].vy) lpAct->bbox[1].vy = lpAct->bbox[0].vy;

    lpAct->bbox[2].vx = lpAct->objBody.objs->objs[2].model->lx; /* F9C */
    lpAct->bbox[2].vy = lpAct->objBody.objs->objs[2].model->ly; /* F9E */
    lpAct->bbox[2].vz = lpAct->objBody.objs->objs[2].model->lz; /* FA0 */
    lpAct->bbox[3].vx = lpAct->objBody.objs->objs[2].model->ux; /* FA4 */
    lpAct->bbox[3].vy = lpAct->objBody.objs->objs[2].model->uy; /* FA6 */
    lpAct->bbox[3].vz = lpAct->objBody.objs->objs[2].model->uz; /* FA8 */
    if (lpAct->bbox[2].vy < 0x258) lpAct->bbox[2].vy = 0x258;
    if (lpAct->bbox[3].vy < lpAct->bbox[2].vy) lpAct->bbox[3].vy = lpAct->bbox[2].vy;

    lpAct->bbox[4].vx = lpAct->objLeftCater[0].objs->objs[0].model->lx; /* FAC */
    lpAct->bbox[4].vy = lpAct->objLeftCater[0].objs->objs[0].model->ly; /* FAE */
    lpAct->bbox[4].vz = lpAct->objLeftCater[0].objs->objs[0].model->lz; /* FB0 */
    lpAct->bbox[5].vx = lpAct->objLeftCater[0].objs->objs[0].model->ux; /* FB4 */
    lpAct->bbox[5].vy = lpAct->objLeftCater[0].objs->objs[0].model->uy; /* FB6 */
    lpAct->bbox[5].vz = lpAct->objLeftCater[0].objs->objs[0].model->uz; /* FB8 */
    if (lpAct->bbox[4].vy < 0x258) lpAct->bbox[4].vy = 0x258;
    if (lpAct->bbox[5].vy < lpAct->bbox[4].vy) lpAct->bbox[5].vy = lpAct->bbox[4].vy;

    lpAct->bbox[6].vx = lpAct->objRightCater[0].objs->objs[0].model->lx; /* FBC */
    lpAct->bbox[6].vy = lpAct->objRightCater[0].objs->objs[0].model->ly; /* FBE */
    lpAct->bbox[6].vz = lpAct->objRightCater[0].objs->objs[0].model->lz; /* FC0 */
    lpAct->bbox[7].vx = lpAct->objRightCater[0].objs->objs[0].model->ux; /* FC4 */
    lpAct->bbox[7].vy = lpAct->objRightCater[0].objs->objs[0].model->uy; /* FC6 */
    lpAct->bbox[7].vz = lpAct->objRightCater[0].objs->objs[0].model->uz; /* FC8 */
    if (lpAct->bbox[6].vy < 0x258) lpAct->bbox[6].vy = 0x258;
    if (lpAct->bbox[7].vy < lpAct->bbox[6].vy) lpAct->bbox[7].vy = lpAct->bbox[6].vy;

    lpAct->bbox[8].vx = lpAct->objBody.objs->objs[4].model->lx + 0xC8;  /* FCC */
    lpAct->bbox[8].vy = lpAct->objBody.objs->objs[4].model->ly;         /* FCE */
    lpAct->bbox[8].vz = lpAct->objBody.objs->objs[4].model->lz;         /* FD0 */
    lpAct->bbox[9].vx = lpAct->objBody.objs->objs[4].model->ux - 0xC8;  /* FD4 */
    lpAct->bbox[9].vy = lpAct->objBody.objs->objs[4].model->uy;         /* FD6 */
    lpAct->bbox[9].vz = lpAct->objBody.objs->objs[4].model->uz - 0x2BC; /* FD8 */

    lpAct->bbox[10].vy = lpAct->objBody.objs->objs[5].model->ly - 0x1F4; /* FDE */
    lpAct->bbox[10].vz = lpAct->objBody.objs->objs[5].model->lz;         /* FE0 */
    lpAct->bbox[11].vx = lpAct->objBody.objs->objs[5].model->ux;         /* FE4 */
    lpAct->bbox[11].vy = lpAct->objBody.objs->objs[5].model->uy + 0x12C; /* FE6 */
    lpAct->bbox[11].vz = lpAct->objBody.objs->objs[5].model->uz - 0x12C; /* FE8 */
    lpAct->bbox[10].vx = -lpAct->bbox[11].vx;                            /* FDC */

    if (lpAct->field_D54 == 6)
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
    for (s1 = 0; s1 < 8; s1++)
    {
        lpAct->objBody.objs->objs[s1].world = DG_ZeroMatrix;
    }

    s05a_dword_800C362C = lpAct;
    lpAct->control.rot.vx = lpAct->control.turn.vx;
    lpAct->control.rot.vy = lpAct->control.turn.vy;
    lpAct->control.rot.vz = lpAct->control.turn.vz;

    if (lpAct->field_D54 == 6)
    {
        return (void *)lpAct;
    }

    {
        char    *q;
        int      off2;

        lpAct->nLeftCaterDirection = 0x3E7;
        lpAct->nRightCaterDirection = 0x3E7;
        lpAct->field_A80 =
            (lpAct->objLeftCater[0].objs->objs[0].model->ux -
             lpAct->objLeftCater[0].objs->objs[0].model->lx) / 3;

        s1 = 0;
        svec.vx = (u_short)lpAct->field_A80;
        svec.vz = (u_short)lpAct->field_A80;
        svec.vy = 0x258;
        for (; s1 < 10; s1++)
        {
            TARGET *t = GM_AllocTarget();
            lpAct->lpTarget[s1] = t;
            GM_SetTarget(t, 0xC, 2, &svec);
            GM_SetPowerTarget(lpAct->lpTarget[s1], 1, -1, 0x2710, 0, &DG_ZeroVector);
        }

        svec.vy = 0x32;
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
        memcpy(lpAct->life_name, &s05a_dword_800E3454, 7);
        lpAct->life_conf.name = lpAct->life_name;
        lpAct->life_conf.left[0] = 0x10;
        lpAct->life_conf.left[1] = 0x6F;
        lpAct->life_conf.left[2] = 0x9F;
        lpAct->life_conf.right[0] = 0x1F;
        lpAct->life_conf.right[1] = 0xDF;
        lpAct->life_conf.right[2] = 0x7F;
    }

    return (void *)lpAct;
}
