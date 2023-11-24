#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/object.h"
#include "Anime/animeconv/anime.h"

typedef struct ObjectWork
{
    GV_ACT  actor;
    CONTROL field_20;
    OBJECT  field_9C;
    TARGET *field_180;
    MATRIX  field_184;
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
} ObjectWork;

SVECTOR object_svec1_800C3CAC = {1000, 2000, 1500, 0};
SVECTOR object_svec2_800C3CB4 = {1500, 2000, 1500, 0};

extern int     GM_GameFlag_800E0F64;
extern SVECTOR DG_ZeroVector_800AB39C;

int s01a_object_800D98B0(ObjectWork *work, int threshold)
{
    SVECTOR svec;
    int     vx, vz;

    vx = work->field_274.vx - work->field_20.field_0_mov.vx;
    vz = work->field_274.vy - work->field_20.field_0_mov.vz;
    if (vx <= -threshold || vx >= threshold || vz <= -threshold || vz >= threshold)
    {
        svec.vx = vx;
        svec.vz = vz;
        return GV_VecDir2_80016EF8(&svec);
    }
    return -1;
}

int s01a_object_800D991C(char *opt, DVECTOR *out)
{
    int   count;
    char *param;

    count = 0;

    while ((param = GCL_Get_Param_Result_80020AA4()) != NULL)
    {
        out->vx = GCL_StrToInt_800209E8(param);
        out->vy = GCL_StrToInt_800209E8(GCL_Get_Param_Result_80020AA4());
        out++;

        count++;
    }

    return count;
}

int s01a_object_800D9984(char *opt, short *params)
{
    int            count;
    unsigned char *param;

    for (count = 0; (param = GCL_Get_Param_Result_80020AA4()) != NULL; params++, count++)
    {
        *params = GCL_StrToInt_800209E8(param);
    }
    return count;
}

void s01a_object_800D99DC(ObjectWork *work)
{
    SVECTOR svec;

    if (work->field_264 >= 0)
    {
        work->field_20.field_4C_turn.vy = work->field_264;
    }
    if (work->field_284 >= 0)
    {
        GV_DirVec2_80016F24(work->field_284, work->field_268, &svec);
        work->field_20.field_44_step.vx = svec.vx;
        work->field_20.field_44_step.vz = svec.vz;
    }
    else
    {
        work->field_20.field_44_step.vx = 0;
        work->field_20.field_44_step.vz = 0;
    }

    work->field_20.field_32_height = 20;
    work->field_20.field_44_step.vy -= 16;
    if (work->field_20.field_44_step.vy < 0 && work->field_20.field_57 != 0)
    {
        work->field_20.field_44_step.vy = 0;
    }
}

void s01a_object_800D9A88(ObjectWork *work)
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
        diff.vx = work->field_20.field_0_mov.vx - work->field_274.vx;
        diff.vy = 0;
        diff.vz = work->field_20.field_0_mov.vz - work->field_274.vy;

        yaw = GV_VecDir2_80016EF8(&diff);
        GV_DirVec2_80016F24(yaw, 500, &diff);

        work->field_274.vx += diff.vx;
        work->field_274.vy += diff.vz;
    }
    else if (work->field_228[index] == 2)
    {
        diff.vx = work->field_274.vx - work->field_20.field_0_mov.vx;
        diff.vy = 0;
        diff.vz = work->field_274.vy - work->field_20.field_0_mov.vz;

        yaw = GV_VecDir2_80016EF8(&diff);
        GV_DirVec2_80016F24(yaw, 1250, &diff);

        work->field_274.vx += diff.vx;
        work->field_274.vy += diff.vz;
    }
}

int s01a_object_800D9BA0(ObjectWork *work)
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

int s01a_object_800D9C10(ObjectWork *work)
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

int s01a_object_800D9C8C(ObjectWork *work)
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

    diff.vx = work->field_1E8[index].vx - work->field_20.field_0_mov.vx;
    diff.vy = 0;
    diff.vz = work->field_1E8[index].vy - work->field_20.field_0_mov.vz;

    yaw = GV_VecDir2_80016EF8(&diff);
    if (GV_DiffDirAbs_8001706C(work->field_264, yaw) < 16)
    {
        return 1;
    }

    if (GV_DiffDirS_8001704C(work->field_264, yaw) > 0)
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

int s01a_object_800D9DAC(ObjectWork *work)
{
    return --work->field_260 < 1;
}

int s01a_object_800D9DC4(ObjectWork *work)
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

int s01a_object_800D9E20(ObjectWork *work)
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

void s01a_object_800D9F10(ObjectWork *work)
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

void s01a_object_800D9F9C(ObjectWork *work)
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

void s01a_object_800D9FE0(ObjectWork *work)
{
    TARGET *target;

    s01a_object_800D9F9C(work);
    s01a_object_800D99DC(work);
    if (work->field_28C == 1 && GM_GameFlag_800E0F64 & 1)
    {
        work->field_20.field_0_mov.vy = 10000;
        work->field_20.field_44_step.vy = 0;
    }
    GM_ActControl_80025A7C(&work->field_20);
    GM_ActObject2_80034B88(&work->field_9C);
    DG_GetLightMatrix2_8001A5D8(&work->field_20.field_0_mov, &work->field_184);

    target = work->field_180;
    if (target->field_6_flags & TARGET_PUSH)
    {
        target->field_6_flags &= ~TARGET_PUSH;
    }
    GM_Target_SetVector_8002D500(target, &work->field_20.field_0_mov);
}

void s01a_object_800DA08C(ObjectWork *work)
{
    TARGET *target;

    work->field_180 = target = GM_AllocTarget_8002D400();
    if (work->field_28C == 1)
    {
        GM_SetTarget_8002DC74(target, 0x18, 0, &object_svec2_800C3CB4);
    }
    else
    {
        GM_SetTarget_8002DC74(target, 0x18, 0, &object_svec1_800C3CAC);
    }

    target->field_3C = 1;
}

int s01a_object_800DA108(ObjectWork *work, int unused, int unused2)
{
    int opt;

    s01a_object_800DA08C(work);

    opt = GCL_GetOption_80020968('r');
    if (opt == NULL)
    {
        printf("OBJECT:no ROOT\n");
    }

    work->field_1E4 = s01a_object_800D991C((char *)opt, work->field_1E8);

    work->field_20.field_0_mov.vx = work->field_1E8[0].vx;
    work->field_20.field_0_mov.vy = 4000;
    work->field_20.field_0_mov.vz = work->field_1E8[0].vy;

    opt = GCL_GetOption_80020968('x');
    if (opt == NULL)
    {
        printf("OBJECT:no ACTION\n");
    }

    if (work->field_1E4 != s01a_object_800D9984((char *)opt, work->field_228))
    {
        printf("node action set err!!\n");
    }

    work->field_254 = 0;
    work->field_258 = 0;
    work->field_260 = 0;
    work->field_268 = 0;
    work->field_26C = 0;
    work->field_270 = -1;
    work->field_264 = work->field_20.field_8_rot.vy;
    work->field_25C = work->field_228[0];

    return 0;
}

int s01a_object_800DA1E8(ObjectWork *work, int arg1)
{
    CONTROL *ctrl;
    OBJECT  *obj;
    int      type;
    char    *str;

    ctrl = &work->field_20;
    if (GM_InitLoader_8002599C(ctrl, 0, arg1) < 0)
    {
        return -1;
    }

    GM_ConfigControlString_800261C0(ctrl, (char *)GCL_GetOption_80020968('p'), (char *)GCL_GetOption_80020968('d'));
    GM_ConfigControlHazard_8002622C(ctrl, -1, -1, -1);
    work->field_20.field_44_step = DG_ZeroVector_800AB39C;

    fprintf(0, "rot.vx=%d, rot.vy=%d, rot.vz=%d \n", ctrl->field_8_rot.vx, ctrl->field_8_rot.vy, ctrl->field_8_rot.vz);

    type = 0x41;

    obj = &work->field_9C;
    str = (char *)GCL_GetOption_80020968('n');

    if (str != 0)
    {
        type = GCL_StrToInt_800209E8(str);
    }

    if ((type & 0xFF) == 0x41)
    {
        str = "rift";
        work->field_28C = 0;
    }
    else if ((type & 0xFF) == 0x4B)
    {
        str = "m13_crane";
        work->field_28C = 2;
    }
    else
    {
        str = "rift";
        work->field_28C = 1;
    }

    GM_InitObject_80034A18(obj, GV_StrCode_80016CCC(str), 0x32D, 0);
    GM_ConfigObjectJoint_80034CB4(obj);
    GM_ConfigObjectLight_80034C44(obj, &work->field_184);
    GM_ConfigObjectStep_80034C54(obj, &work->field_20.field_44_step);

    return 0;
}

void s01a_object_800DA368(ObjectWork *work)
{
    GM_FreeControl_800260CC(&work->field_20);
    GM_FreeObject_80034BF8(&work->field_9C);
    GM_FreeTarget_8002D4B0(work->field_180);
}

GV_ACT *s01a_object_800DA3A4(int arg0, int arg1)
{
    ObjectWork *work;

    work = (ObjectWork *)GV_NewActor_800150E4(4, sizeof(ObjectWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s01a_object_800D9FE0,
                                  (TActorFunction)s01a_object_800DA368, "object.c");
        if (s01a_object_800DA1E8(work, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
        s01a_object_800DA108(work, arg0, arg1);
    }
    return &work->actor;
}
