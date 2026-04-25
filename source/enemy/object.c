#include "object.h"

#include <stdio.h>
#include "common.h"
#include "mts/mts.h" // for fprintf
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "anime/animconv/anime.h"

extern int GM_GameFlag;

/*---------------------------------------------------------------------------*/
// NOTE: This is apparently the scrapped forklift actor that would roam around
// the Heliport in early versions of the game, as seen in the E3 & TGS 1997
// trailers ( https://www.youtube.com/watch?v=x3Y5TS6_NxQ&t=247 ).

#define EXEC_LEVEL      GV_ACTOR_LEVEL4

#define BODY_FLAG       ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_SHADE \
                        | DG_FLAG_GBOUND | DG_FLAG_AMBIENT | DG_FLAG_IRTEXTURE )

typedef struct _Work
{
    GV_ACT  actor;
    CONTROL control;
    OBJECT  field_9C;
    TARGET *field_180;
    MATRIX  light;
    int     field_1A4;
    int     field_1A8;
    int     field_1AC;
    int     field_1B0;
    int     field_1B4;
    int     field_1B8;
    int     field_1BC;
    int     field_1C0;
    int     field_1C4;
    int     field_1C8;
    int     field_1CC;
    int     field_1D0;
    int     field_1D4;
    int     field_1D8;
    int     field_1DC;
    int     field_1E0;
    int     field_1E4;
    DVECTOR field_1E8[16];
    short   field_228[2];
    int     field_22C;
    int     field_230;
    int     field_234;
    int     field_238;
    int     field_23C;
    int     field_240;
    int     field_244;
    int     field_248;
    int     field_24C;
    int     field_250;
    int     field_254;
    int     field_258;
    int     field_25C;
    int     field_260;
    int     field_264;
    int     field_268;
    int     field_26C;
    int     field_270;
    DVECTOR field_274;
    int     field_278;
    short   field_27C;
    short   field_27E;
    int     field_280;
    short   field_284;
    short   field_286;
    int     field_288;
    int     field_28C;
} Work;

/*---------------------------------------------------------------------------*/

SVECTOR object_svec1_800C3CAC = {1000, 2000, 1500, 0};
SVECTOR object_svec2_800C3CB4 = {1500, 2000, 1500, 0};

static int s01a_object_800D98B0(Work *work, int threshold)
{
    SVECTOR svec;
    int     vx, vz;

    vx = work->field_274.vx - work->control.mov.vx;
    vz = work->field_274.vy - work->control.mov.vz;
    if (vx <= -threshold || vx >= threshold || vz <= -threshold || vz >= threshold)
    {
        svec.vx = vx;
        svec.vz = vz;
        return GV_VecDir2(&svec);
    }
    return -1;
}

static int s01a_object_800D991C(char *opt, DVECTOR *out)
{
    int   count;
    char *param;

    count = 0;

    while ((param = GCL_GetParamResult()) != NULL)
    {
        out->vx = GCL_StrToInt(param);
        out->vy = GCL_StrToInt(GCL_GetParamResult());
        out++;

        count++;
    }

    return count;
}

static int s01a_object_800D9984(char *opt, short *params)
{
    int            count;
    unsigned char *param;

    for (count = 0; (param = GCL_GetParamResult()) != NULL; params++, count++)
    {
        *params = GCL_StrToInt(param);
    }
    return count;
}

static void s01a_object_800D99DC(Work *work)
{
    SVECTOR svec;

    if (work->field_264 >= 0)
    {
        work->control.turn.vy = work->field_264;
    }
    if (work->field_284 >= 0)
    {
        GV_DirVec2(work->field_284, work->field_268, &svec);
        work->control.step.vx = svec.vx;
        work->control.step.vz = svec.vz;
    }
    else
    {
        work->control.step.vx = 0;
        work->control.step.vz = 0;
    }

    work->control.height = 20;
    work->control.step.vy -= 16;
    if (work->control.step.vy < 0 && work->control.level_flag != 0)
    {
        work->control.step.vy = 0;
    }
}

static void s01a_object_800D9A88(Work *work)
{
    SVECTOR diff;
    int     index;
    int     yaw;

    index = work->field_26C + 1;
    if (index >= work->field_1E4)
    {
        index = 0;
    }
    work->field_26C = index;

    work->field_274 = work->field_1E8[index];

    if (work->field_228[index] == 1)
    {
        diff.vx = work->control.mov.vx - work->field_274.vx;
        diff.vy = 0;
        diff.vz = work->control.mov.vz - work->field_274.vy;

        yaw = GV_VecDir2(&diff);
        GV_DirVec2(yaw, 500, &diff);

        work->field_274.vx += diff.vx;
        work->field_274.vy += diff.vz;
    }
    else if (work->field_228[index] == 2)
    {
        diff.vx = work->field_274.vx - work->control.mov.vx;
        diff.vy = 0;
        diff.vz = work->field_274.vy - work->control.mov.vz;

        yaw = GV_VecDir2(&diff);
        GV_DirVec2(yaw, 1250, &diff);

        work->field_274.vx += diff.vx;
        work->field_274.vy += diff.vz;
    }
}

static int s01a_object_800D9BA0(Work *work)
{
    int field_284;

    if (work->field_260 == 0)
    {
        s01a_object_800D9A88(work);
    }

    field_284 = s01a_object_800D98B0(work, 32);
    if (field_284 < 0)
    {
        return 1;
    }

    work->field_284 = field_284;
    work->field_268 = 32;
    work->field_260++;
    return 0;
}

static int s01a_object_800D9C10(Work *work)
{
    int field_284;

    field_284 = -1;
    work->field_268 = 0;
    if (work->field_260 < 4)
    {
        if (work->field_260 & 1)
        {
            field_284 = work->field_264;
            work->field_268 = 32;
        }
        else
        {
            field_284 = work->field_264 + 2048;
            if (field_284 > 4096)
            {
                field_284 = work->field_264 - 2048;
            }
            work->field_268 = 32;
        }
    }
    else if (work->field_260 >= 32)
    {
        return 1;
    }
    work->field_284 = field_284;
    work->field_260++;
    return 0;
}

static int s01a_object_800D9C8C(Work *work)
{
    SVECTOR diff;
    int     yaw;
    int     index;

    yaw = -1;

    work->field_284 = -1;
    work->field_268 = 0;

    index = work->field_26C + 1;
    if (index >= work->field_1E4)
    {
        index = 0;
    }

    diff.vx = work->field_1E8[index].vx - work->control.mov.vx;
    diff.vy = 0;
    diff.vz = work->field_1E8[index].vy - work->control.mov.vz;

    yaw = GV_VecDir2(&diff);
    if (GV_DiffDirAbs(work->field_264, yaw) < 16)
    {
        return 1;
    }

    if (GV_DiffDirS(work->field_264, yaw) > 0)
    {
        work->field_284 = work->field_264 + 16;
        if (work->field_284 >= 4096)
        {
            work->field_284 -= 4096;
        }
    }
    else
    {
        work->field_284 = work->field_264 - 16;
        if (work->field_284 < 0)
        {
            work->field_284 += 4096;
        }
    }

    work->field_268 = 32;
    work->field_264 = work->field_284;
    work->field_260++;

    return 0;
}

static int s01a_object_800D9DAC(Work *work)
{
    return --work->field_260 < 1;
}

static int s01a_object_800D9DC4(Work *work)
{
    switch (work->field_25C)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        if (s01a_object_800D9BA0(work))
        {
            return 1;
        }
    default:
        work->field_260++;
        return 0;
    }
}

static int s01a_object_800D9E20(Work *work)
{
    switch (work->field_25C)
    {
    case 0:
        if (s01a_object_800D9C10(work))
        {
            work->field_25C = 5;
        }
        break;

    case 1:
        if (s01a_object_800D9C8C(work))
        {
            return 1;
        }
        break;

    case 2:
        if (s01a_object_800D9C10(work))
        {
            work->field_25C = 1;
            work->field_260 = 0;
        }
        break;

    case 3:
        work->field_25C = 6;
        work->field_260 = 12;
        break;

    case 4:
        work->field_25C = 6;
        work->field_260 = 32;
        break;

    case 5:
        work->field_25C = 6;
        work->field_260 = 120;
        break;

    case 6:
        if (s01a_object_800D9DAC(work))
        {
            return 1;
        }
        break;
    }

    return 0;
}

static void s01a_object_800D9F10(Work *work)
{
    switch (work->field_258)
    {
    case 0:
        if (s01a_object_800D9DC4(work))
        {
            work->field_258 = 1;
            work->field_25C = work->field_228[work->field_26C];
            work->field_260 = 0;
        }
        break;

    case 1:
        if (s01a_object_800D9E20(work))
        {
            work->field_258 = 0;
            work->field_25C = work->field_228[work->field_26C];
            work->field_260 = 0;
        }
        break;
    }
}

static void s01a_object_800D9F9C(Work *work)
{
    int field_254;

    field_254 = work->field_254;
    work->field_284 = -1;
    work->field_27C = 0;
    work->field_27E = 0;
    if (field_254 == 0)
    {
        s01a_object_800D9F10(work);
    }
    else if (field_254 == 1)
    {
        s01a_object_800D9F10(work);
    }
}

static void Act(Work *work)
{
    TARGET *target;

    s01a_object_800D9F9C(work);
    s01a_object_800D99DC(work);
    if (work->field_28C == 1 && GM_GameFlag & 1)
    {
        work->control.mov.vy = 10000;
        work->control.step.vy = 0;
    }
    GM_ActControl(&work->control);
    GM_ActObject2(&work->field_9C);
    DG_GetLightMatrix2(&work->control.mov, &work->light);

    target = work->field_180;
    if (target->damaged & TARGET_PUSH)
    {
        target->damaged &= ~TARGET_PUSH;
    }
    GM_MoveTarget(target, &work->control.mov);
}

static void s01a_object_800DA08C(Work *work)
{
    TARGET *target;

    work->field_180 = target = GM_AllocTarget();
    if (work->field_28C == 1)
    {
        GM_SetTarget(target, 0x18, 0, &object_svec2_800C3CB4);
    }
    else
    {
        GM_SetTarget(target, 0x18, 0, &object_svec1_800C3CAC);
    }

    target->field_3C = 1;
}

static int s01a_object_800DA108(Work *work, int unused, int unused2)
{
    char *opt;

    s01a_object_800DA08C(work);

    opt = GCL_GetOption('r');
    if (opt == NULL)
    {
        printf("OBJECT:no ROOT\n");
    }

    work->field_1E4 = s01a_object_800D991C(opt, work->field_1E8);

    work->control.mov.vx = work->field_1E8[0].vx;
    work->control.mov.vy = 4000;
    work->control.mov.vz = work->field_1E8[0].vy;

    opt = GCL_GetOption('x');
    if (opt == NULL)
    {
        printf("OBJECT:no ACTION\n");
    }

    if (work->field_1E4 != s01a_object_800D9984(opt, work->field_228))
    {
        printf("node action set err!!\n");
    }

    work->field_254 = 0;
    work->field_258 = 0;
    work->field_260 = 0;
    work->field_268 = 0;
    work->field_26C = 0;
    work->field_270 = -1;
    work->field_264 = work->control.rot.vy;
    work->field_25C = work->field_228[0];

    return 0;
}

static int GetResources(Work *work, int arg1)
{
    CONTROL *ctrl;
    OBJECT  *obj;
    int      type;
    char    *name;

    ctrl = &work->control;
    if (GM_InitControl(ctrl, 0, arg1) < 0)
    {
        return -1;
    }

    GM_ConfigControlString(ctrl, GCL_GetOption('p'), GCL_GetOption('d'));
    GM_ConfigControlHazard(ctrl, -1, -1, -1);
    work->control.step = DG_ZeroVector;

    fprintf(0, "rot.vx=%d, rot.vy=%d, rot.vz=%d \n", ctrl->rot.vx, ctrl->rot.vy, ctrl->rot.vz);

    type = 0x41;

    obj = &work->field_9C;
    name = GCL_GetOption('n');

    if (name != NULL)
    {
        type = GCL_StrToInt(name);
    }

    if ((type & 0xFF) == 0x41)
    {
        name = "rift";
        work->field_28C = 0;
    }
    else if ((type & 0xFF) == 0x4B)
    {
        name = "m13_crane";
        work->field_28C = 2;
    }
    else
    {
        name = "rift";
        work->field_28C = 1;
    }

    GM_InitObject(obj, GV_StrCode(name), BODY_FLAG, 0);
    GM_ConfigObjectJoint(obj);
    GM_ConfigObjectLight(obj, &work->light);
    GM_ConfigObjectStep(obj, &work->control.step);

    return 0;
}

static void Die(Work *work)
{
    GM_FreeControl(&work->control);
    GM_FreeObject(&work->field_9C);
    GM_FreeTarget(work->field_180);
}

/*---------------------------------------------------------------------------*/

void *NewMovingObject(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "object.c");
        if (GetResources(work, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
        s01a_object_800DA108(work, name, where);
    }
    return (void *)work;
}
