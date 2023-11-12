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
    int     field_1E8;
    int     field_1EC;
    int     field_1F0;
    int     field_1F4;
    int     field_1F8;
    int     field_1FC;
    int     field_200;
    int     field_204;
    int     field_208;
    int     field_20C;
    int     field_210;
    int     field_214;
    int     field_218;
    int     field_21C;
    int     field_220;
    int     field_224;
    int     field_228;
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
    short   field_274;
    short   field_276;
    int     field_278;
    short   field_27C;
    short   field_27E;
    int     field_280;
    short   field_284;
    short   field_286;
    int     field_288;
    int     field_28C;
} ObjectWork;

extern char      s01a_aMcrane_800E4808[];
extern char      s01a_aRift_800E4800[];
extern char      s01a_aRotvxdrotvydrotvzd_800E47DC[];
extern char      s01a_dword_800E4814[];
extern int       s01a_dword_800E4E04;
extern SVECTOR   object_svec1_800C3CAC;
extern SVECTOR   object_svec2_800C3CB4;
extern ANIMATION anm_800C3C58;
extern ANIMATION anm_800C3C20;
extern ANIMATION anm_800C3C74;
extern ANIMATION anm_800C3C3C;
extern ANIMATION anm_800C3C04;

extern SVECTOR DG_ZeroVector_800AB39C;

void s01a_object_800D93BC(short *arg0)
{
    PRESCRIPT prescript;
    SVECTOR  *pos, *speed;

    pos = &prescript.pos;

    pos->vx = arg0[10];
    pos->vy = arg0[12];
    pos->vz = arg0[14];

    speed = &prescript.speed;

    speed->vx = 0;
    speed->vy = 0;
    speed->vz = 0;

    prescript.scr_num = 1;
    prescript.s_anim = 0;

    anm_800C3C04.field_14_pre_script = &prescript;
    NewAnime_8005FBC8(NULL, NULL, &anm_800C3C04);
}

void s01a_object_800D9424(SVECTOR *pos, short scr_num)
{
    PRESCRIPT prescript;

    prescript.pos = *pos;
    prescript.speed = DG_ZeroVector_800AB39C;
    prescript.scr_num = scr_num;
    prescript.s_anim = 0;

    anm_800C3C04.field_14_pre_script = &prescript;
    NewAnime_8005FBC8(NULL, NULL, &anm_800C3C04);
}

void s01a_object_800D94A8(SVECTOR *pos)
{
    PRESCRIPT prescript;

    prescript.pos = *pos;
    prescript.speed = DG_ZeroVector_800AB39C;
    prescript.scr_num = 0;
    prescript.s_anim = 0;

    anm_800C3C3C.field_14_pre_script = &prescript;
    NewAnime_8005FBC8(NULL, NULL, &anm_800C3C3C);
}

void s01a_object_800D952C(SVECTOR *pos, short scr_num)
{
    PRESCRIPT prescript;

    prescript.pos = *pos;
    prescript.speed = DG_ZeroVector_800AB39C;
    prescript.scr_num = scr_num;
    prescript.s_anim = 0;

    anm_800C3C58.field_14_pre_script = &prescript;
    NewAnime_8005FBC8(NULL, NULL, &anm_800C3C58);
}

void s01a_object_800D95B0(SVECTOR *pos)
{
    PRESCRIPT prescript;

    prescript.pos = *pos;
    prescript.speed = DG_ZeroVector_800AB39C;
    prescript.scr_num = 0;
    prescript.s_anim = 0;

    anm_800C3C74.field_14_pre_script = &prescript;
    NewAnime_8005FBC8(NULL, NULL, &anm_800C3C74);
}

void s01a_object_800D9634(SVECTOR *pos)
{
    PRESCRIPT prescript;

    prescript.pos = *pos;
    prescript.speed = DG_ZeroVector_800AB39C;
    prescript.scr_num = 0;
    prescript.s_anim = 0;

    anm_800C3C20.field_14_pre_script = &prescript;
    NewAnime_8005FBC8(NULL, NULL, &anm_800C3C20);
}

#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_object_800D96B8.s")

int s01a_object_800D98B0(ObjectWork *work, int threshold)
{
    SVECTOR svec;
    int     vx, vz;

    vx = work->field_274 - work->field_20.field_0_mov.vx;
    vz = work->field_276 - work->field_20.field_0_mov.vz;
    if (vx <= -threshold || vx >= threshold || vz <= -threshold || vz >= threshold)
    {
        svec.vx = vx;
        svec.vz = vz;
        return GV_YawVec3_80016EF8(&svec);
    }
    return -1;
}

#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_object_800D991C.s")

int s01a_object_800D9984(int arg0, short *params)
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
        GV_InvYawVec3_80016F24(work->field_284, work->field_268, &svec);
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

#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_object_800D9A88.s")
int s01a_object_800D9A88(ObjectWork *work);

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

#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_object_800D9C8C.s")

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

#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_object_800D9E20.s")
#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_object_800D9F10.s")
void s01a_object_800D9F10(ObjectWork *work);

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
    if (work->field_28C == 1 && s01a_dword_800E4E04 & 1)
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

#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_object_800DA108.s")
void s01a_object_800DA108(ObjectWork *work, int, int);

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

    fprintf(0, s01a_aRotvxdrotvydrotvzd_800E47DC, ctrl->field_8_rot.vx, ctrl->field_8_rot.vy, ctrl->field_8_rot.vz);

    type = 0x41;

    obj = &work->field_9C;
    str = (char *)GCL_GetOption_80020968('n');

    if (str != 0)
    {
        type = GCL_StrToInt_800209E8(str);
    }

    if ((type & 0xFF) == 0x41)
    {
        str = s01a_aRift_800E4800;
        work->field_28C = 0;
    }
    else if ((type & 0xFF) == 0x4B)
    {
        str = s01a_aMcrane_800E4808;
        work->field_28C = 2;
    }
    else
    {
        str = s01a_aRift_800E4800;
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
                                  (TActorFunction)s01a_object_800DA368, s01a_dword_800E4814);
        if (s01a_object_800DA1E8(work, arg1) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
        s01a_object_800DA108(work, arg0, arg1);
    }
    return &work->actor;
}
