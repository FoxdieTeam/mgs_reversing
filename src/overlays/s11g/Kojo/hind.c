#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/camera.h"
#include "Game/object.h"
#include "Game/linkvarbuf.h"
#include "Menu/menuman.h"

typedef struct HindWork
{
    GV_ACT   actor;
    CONTROL  control;
    OBJECT   field_9C;
    OBJECT   field_180;
    OBJECT   field_264;
    MATRIX   field_348_light1[2];
    MATRIX   field_388_light2[2];
    MATRIX   field_3C8_light3[2];
    TARGET  *field_408;
    TARGET  *field_40C;
    TARGET  *field_410;
    int      field_414;
    int      field_418;
    int      field_41C;
    int      field_420;
    int      field_424;
    int      field_428;
    int      field_42C;
    int      field_430;
    int      field_434;
    int      field_438;
    int      field_43C;
    int      field_440;
    int      field_444;
    int      field_448;
    int      field_44C;
    int      field_450;
    int      field_454;
    int      field_458;
    int      field_45C;
    int      field_460;
    int      field_464;
    int      field_468;
    int      field_46C;
    int      field_470;
    int      field_474;
    int      field_478;
    int      field_47C;
    int      field_480;
    int      field_484;
    int      field_488;
    int      field_48C;
    SVECTOR *field_490;
    int      field_494;
    int      field_498;
    int      field_49C;
    int      field_4A0;
    short    field_4A4;
    short    field_4A6;
    short    field_4A8;
    short    field_4AA;
    int      field_4AC;
    int      field_4B0;
    int      field_4B4;
    int      field_4B8;

    int field_4BC; // TODO: this and following 4 ints are copied as a "block", what's this type?
    int field_4C0;
    int field_4C4;
    int field_4C8;

    int    field_4CC;
    int    field_4D0;
    int    field_4D4;
    int    field_4D8;
    int    field_4DC;
    int    field_4E0;
    int    field_4E4;
    int    field_4E8;
    int    field_4EC;
    int    field_4F0;
    int    field_4F4;
    int    field_4F8;
    int    field_4FC;
    int    field_500;
    int    field_504;
    int    field_508;
    int    field_50C;
    int    field_510;
    int    field_514;
    VECTOR field_518; // array?
    VECTOR field_528;
    VECTOR field_538;
    VECTOR field_548;
    int    field_558;
    int    field_55C;
    int    field_560;
    int    field_564;
    int    field_568;
    int    field_56C;
    int    field_570;
    int    field_574;
    int    field_578;
    TARGET field_57C;
    int    field_5C4;
    int    field_5C8;
    int    field_5CC;
    int    field_5D0;
    int    field_5D4;
    int    field_5D8;
    int    field_5DC;
    int    field_5E0;
    int    field_5E4;
    int    field_5E8;
    int    field_5EC;
    int    field_5F0;
    int    field_5F4;
    int    field_5F8;

    int field_5FC; // TODO: this and following 4 ints are copied as a "block", what's this type?
    int field_600;
    int field_604;
    int field_608;

    int field_60C; // TODO: this and following 4 ints are copied as a "block", what's this type?
    int field_610;
    int field_614;
    int field_618;

    int       field_61C;
    int       field_620;
    int       field_624;
    int       field_628;
    int       field_62C;
    int       field_630;
    int       field_634;
    int       field_638;
    int       field_63C;
    int       field_640;
    SVECTOR   field_644;
    int       field_64C;
    int       field_650;
    int       field_654;
    int       field_658;
    int       field_65C;
    int       field_660;
    int       field_664;
    int       field_668;
    int       field_66C;
    int       field_670;
    int       field_674;
    int       field_678;
    OBJECT    field_67C;
    int       field_760;
    int       field_764;
    int       field_768;
    int       field_76C;
    int       field_770;
    int       field_774;
    int       field_778;
    int       field_77C;
    int       field_780;
    int       field_784;
    int       field_788;
    int       field_78C;
    int       field_790;
    int       field_794;
    MATRIX    field_798_light4[2];
    int       field_7D8;
    int       field_7DC;
    int       field_7E0;
    int       field_7E4;
    MENU_BAR_CONF field_7E8;
    int       field_7F4;
    int       field_7F8;
    int       field_7FC[1]; // unknown how large
    int       field_800;
    int       field_804;
    int       field_808;
    int       field_80C;
    int       field_810;
    int       field_814;
    int       field_818;
    int       field_81C;
    int       field_820;
    int       field_824;
    int       field_828;
    int       field_82C;
    int       field_830;
    int       field_834;
    int       field_838;
    int       field_83C;
    int       field_840;
    int       field_844;
    int       field_848;
    int       field_84C;
    int       field_850;
    int       field_854;
    int       field_858;
    int       field_85C;
    int       field_860;
    int       field_864;
    int       field_868;
    int       field_86C;
    int       field_870;
    int       field_874;
    int       field_878;
    int       field_87C;
    int       field_880;
    int       field_884;
    int       field_888;
    int       field_88C;
    int       field_890;
    int       field_894;
    int       field_898;
    int       field_89C;
    int       field_8A0;
    int       field_8A4;
    int       field_8A8;
    int       field_8AC;
    int       field_8B0;
    int       field_8B4;
    int       field_8B8;
    int       field_8BC;
    int       field_8C0;
    int       field_8C4;
    int       field_8C8;
    int       field_8CC;
    int       field_8D0;
    int       field_8D4;
    int       field_8D8;
    int       field_8DC;
    int       field_8E0;
    GV_ACT   *field_8E4;
    GV_ACT   *field_8E8;
    int       field_8EC;
    int       field_8F0;
    int       field_8F4;
    int       field_8F8;
    int       field_8FC;
    int       field_900;
    int       field_904;
    int       field_908;
    int       field_90C;
    int       field_910;
    int       field_914;
    int       field_918;
    int       field_91C;
    int       field_920;
    int       field_924;
    int       field_928;
    int       field_92C;
    int       field_930;
    int       field_934;
    int       field_938;
    int       field_93C;
    int       field_940;
    int       field_944;
    int       field_948;
    int       field_94C;
    int       field_950;
    int       field_954;
    int       field_958;
    int       field_95C;
    int       field_960;
    int       field_964;
    int       field_968;
    int       field_96C;
    SVECTOR   field_970[32];
    int       field_A70;
    int       field_A74;
    int       field_A78;
    int       field_A7C;
} HindWork;

SVECTOR s11g_dword_800C3598 = {5000, 3000, 5000, 0};
SVECTOR s11g_dword_800C35A0 = {100, 0, 0, 0};

extern MATRIX           DG_ZeroMatrix;
extern SVECTOR          DG_ZeroVector;
extern SVECTOR          GM_PlayerPosition_800ABA10;
extern UnkCameraStruct2 gUnkCameraStruct2_800B7868;
extern DG_CHNL          DG_Chanls_800B1800[3];
extern GM_Camera        GM_Camera_800B77E8;

void HindAct_800D3404(HindWork *work);
void HindDie_800D45C0(HindWork *work);
void sub_8007F0D0(VECTOR *out, VECTOR *a, VECTOR *b, VECTOR *c);

void HindGetIntParams_800D11E0(unsigned char *param, int *result)
{
    unsigned char *param2;

    while ((param2 = GCL_GetParamResult()))
    {
        *result = GCL_StrToInt(param2);
        result++;
    }
}

static inline int min(int a, int b)
{
    return a < b ? a : b;
}

static inline int max(int a, int b)
{
    return a > b ? a : b;
}

GV_ACT *NewHind_800D1224(int scriptData, int scriptBinds)
{
    SVECTOR        svec;
    VECTOR         vec1, vec2, vec3;
    HindWork      *work;
    HZD_SEG       *walls;
    HZD_FLR       *altimetry;
    int            i;
    unsigned char *param;

    work = (HindWork *)GV_NewActor(5, sizeof(HindWork));
    if (work == NULL)
    {
        return NULL;
    }

    GV_SetNamedActor(&work->actor, (TActorFunction)HindAct_800D3404,
                     (TActorFunction)HindDie_800D45C0, "hind.c");
    if (GM_InitControl(&work->control, scriptData, scriptBinds) < 0)
    {
        GV_DestroyActor(&work->actor);
        return NULL;
    }

    work->field_934 = scriptData;

    work->field_348_light1[0].t[0] = 16;
    work->field_348_light1[0].t[1] = 16;
    work->field_348_light1[0].t[2] = 16;

    if (GCL_GetOption('a'))
    {
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_348_light1[0].t[0] = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_348_light1[0].t[1] = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_348_light1[0].t[2] = GCL_StrToInt(param);
        }
    }

    work->field_41C = 233;
    work->field_420 = 205;

    if (GCL_GetOption('r'))
    {
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_41C = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_420 = GCL_StrToInt(param);
        }
    }

    if (GCL_GetOption('e'))
    {
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_424 = GCL_StrToInt(param) * 1000000 / 108000 * 16;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_428 = GCL_StrToInt(param) * 16 / 30;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_42C = GCL_StrToInt(param) * 4096 / 360;
        }
    }

    work->field_444 = 1;

    if (GCL_GetOption('d'))
    {
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_430 = work->field_434 = GCL_StrToInt(param);
        }

        work->field_650 = 1024 / work->field_430 + 1;

        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_438 = (GCL_StrToInt(param) + 1);
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_43C = GCL_StrToInt(param) * 1000000 / 108000 * 16;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_440 = GCL_StrToInt(param) * 16 / 30;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_444 = GCL_StrToInt(param);
        }

        if (work->field_444 <= 0)
        {
            work->field_444 = 1;
        }
    }

    if (GCL_GetOption('g'))
    {
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_448 = GCL_StrToInt(param) + 1;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_44C = GCL_StrToInt(param) * 4096 / 360;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_450 = GCL_StrToInt(param) * 4096 / 360;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_454 = GCL_StrToInt(param) * 4096 / 360;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_458 = GCL_StrToInt(param) * 4096 / 360;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_45C = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_460 = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_464 = GCL_StrToInt(param) * 1000;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_468 = GCL_StrToInt(param) * 1000000 / 108000;
        }
    }

    if (GCL_GetOption('m'))
    {
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_46C = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_470 = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_474 = GCL_StrToInt(param) + 1;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_478 = GCL_StrToInt(param) * 4096 / 360;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_47C = GCL_StrToInt(param) * 4096 / 360;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_480 = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_484 = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_488 = GCL_StrToInt(param) * 1000;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_48C = GCL_StrToInt(param) * 1000000 / 108000;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            if (GCL_StrToInt(param) == 1)
            {
                work->field_490 = &GM_PlayerPosition_800ABA10;
            }
        }
    }

    if (GCL_GetOption('p'))
    {
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_4BC = GCL_StrToInt(param) * 1000;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_4C0 = GCL_StrToInt(param) * 1000;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_4C4 = (GCL_StrToInt(param) * 1000);
        }

        // TODO: What's this memcopied stucture/array?
        memcpy(&work->field_5FC, &work->field_4BC, 4 * 4);
        memcpy(&work->field_60C, &work->field_4BC, 4 * 4);

        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->control.turn.vx = GCL_StrToInt(param) * 4096 / 360;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->control.turn.vy = GCL_StrToInt(param) * 4096 / 360;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->control.turn.vz = GCL_StrToInt(param) * 4096 / 360;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            svec.vx = 0;
            svec.vy = 0;
            svec.vz = 0;
            DG_SetPos2(&svec, &work->control.turn);
            svec.vz = GCL_StrToInt(param) * 1000000 / 108000 * 16;
            DG_PutVector(&svec, &svec, 1);
            work->field_4DC = svec.vx;
            work->field_4E0 = svec.vy;
            work->field_4E4 = svec.vz;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_4A0 = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_494 = GCL_StrToInt(param) * 1000;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_498 = GCL_StrToInt(param) * 1000;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_49C = GCL_StrToInt(param) * 1000;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_4AA = GCL_StrToInt(param);
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_4A4 = GCL_StrToInt(param) * 4096 / 360;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_4A6 = GCL_StrToInt(param) * 4096 / 360;
        }
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_4A8 = GCL_StrToInt(param) * 4096 / 360;
        }
    }

    if (GCL_GetOption('b'))
    {
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_4AC = GCL_StrToInt(param);
        }
    }

    if (GCL_GetOption('w'))
    {
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_4B0 = (GCL_StrToInt(param) * 1000);
        }
    }

    work->field_578 = -1;

    if (GCL_GetOption('z'))
    {
        param = GCL_GetParamResult();
        if (param != NULL)
        {
            work->field_578 = GCL_StrToInt(param);
        }
    }

    work->control.field_36 = -2;
    work->control.field_54 = 0;

    GM_ConfigControlAttribute(&work->control, 4);

    GM_InitObject(&work->field_9C, GV_StrCode("hind"), 0x12D, 0);
    GM_ConfigObjectJoint(&work->field_9C);
    GM_ConfigObjectLight(&work->field_9C, work->field_348_light1);

    GM_InitObject(&work->field_180, GV_StrCode("hindmsil"), 0x12D, 0);
    GM_ConfigObjectLight(&work->field_180, work->field_388_light2);
    GM_ConfigObjectJoint(&work->field_180);

    GM_InitObject(&work->field_264, GV_StrCode("hindmsil"), 0x12D, 0);
    GM_ConfigObjectLight(&work->field_264, work->field_3C8_light3);
    GM_ConfigObjectJoint(&work->field_264);

    work->field_414 = 1;

    work->control.rot.vx = work->control.turn.vx;
    work->control.rot.vy = work->control.turn.vy;
    work->control.rot.vz = work->control.turn.vz;

    work->field_504 = work->field_448 / 2;
    work->field_508 = (work->field_474 / 2);

    work->field_408 = GM_AllocTarget();
    work->field_40C = GM_AllocTarget();
    work->field_410 = GM_AllocTarget();

    work->field_408->damaged &= ~TARGET_POWER;
    work->field_40C->damaged &= ~TARGET_POWER;
    work->field_410->damaged &= ~TARGET_POWER;

    svec.vx = work->field_9C.objs->objs[0].model->max.vx / 2;
    svec.vy = -work->field_9C.objs->objs[0].model->min.vy / 4;
    svec.vz = work->field_9C.objs->objs[0].model->max.vz / 2;

    if (work->field_4AC != 2)
    {
        switch (GM_DifficultyFlag)
        {
        default:
        case -1:
        case 0:
            GM_SetTarget(work->field_408, 20, 2, &svec);
            GM_SetTarget(work->field_40C, 20, 2, &svec);
            GM_SetTarget(work->field_410, 20, 2, &svec);
            break;
        case 1:
        case 2:
            svec.vx = svec.vx / 2;
            svec.vy = svec.vy / 2;
            svec.vz = svec.vz / 2;
            GM_SetTarget(work->field_408, 20, 2, &svec);
            GM_SetTarget(work->field_40C, 20, 2, &svec);
            GM_SetTarget(work->field_410, 20, 2, &svec);
            break;
        case 3:
            svec.vx = svec.vx / 2;
            svec.vy = svec.vy / 2;
            svec.vz = svec.vz / 2;
            GM_SetTarget(work->field_408, 20, 2, &svec);
            GM_SetTarget(work->field_40C, 20, 2, &DG_ZeroVector);
            GM_SetTarget(work->field_410, 20, 2, &DG_ZeroVector);

            work->field_40C->class &= ~0x14;
            work->field_40C->class |= 1;
            work->field_410->class &= ~0x14;
            work->field_410->class |= 1;
            break;
        }
    }
    else
    {
        GM_SetTarget(work->field_408, 0, 2, &svec);
        GM_SetTarget(work->field_40C, 0, 2, &svec);
        GM_SetTarget(work->field_410, 0, 2, &svec);

        work->field_408->damaged |= TARGET_POWER;
        work->field_40C->damaged |= TARGET_POWER;
        work->field_410->damaged |= TARGET_POWER;
    }

    work->field_654 = 1024;
    work->field_7F4 = 1024;

    work->field_4B4 = work->field_41C * 4096 / 1800;
    work->field_4B8 = work->field_420 * 4096 / 1800;

    work->field_514 = max(work->field_9C.objs->def->min.vx - work->field_9C.objs->def->max.vx,
                          work->field_9C.objs->def->min.vy - work->field_9C.objs->def->max.vy);
    work->field_514 = max(work->field_514, work->field_9C.objs->def->min.vz - work->field_9C.objs->def->max.vz);

    work->field_514 = 33200 - work->field_514 / 3;

    vec1.vx = -work->field_514;
    vec1.vy = 0;
    vec1.vz = 0;
    vec2.vx = -work->field_514;
    vec2.vy = 1;
    vec2.vz = 0;
    vec3.vx = -work->field_514;
    vec3.vy = 0;
    vec3.vz = 1;
    sub_8007F0D0(&work->field_518, &vec1, &vec2, &vec3);

    vec1.vx = work->field_514;
    vec1.vy = 0;
    vec1.vz = 0;
    vec2.vx = work->field_514;
    vec2.vy = 1;
    vec2.vz = 0;
    vec3.vx = work->field_514;
    vec3.vy = 0;
    vec3.vz = 1;
    sub_8007F0D0(&work->field_528, &vec1, &vec2, &vec3);

    vec1.vx = 0;
    vec1.vy = 0;
    vec1.vz = -work->field_514;
    vec2.vx = 0;
    vec2.vy = 1;
    vec2.vz = -work->field_514;
    vec3.vx = 1;
    vec3.vy = 0;
    vec3.vz = -work->field_514;
    sub_8007F0D0(&work->field_538, &vec1, &vec2, &vec3);

    vec1.vx = 0;
    vec1.vy = 0;
    vec1.vz = work->field_514;
    vec2.vx = 0;
    vec2.vy = 1;
    vec2.vz = work->field_514;
    vec3.vx = 1;
    vec3.vy = 0;
    vec3.vz = work->field_514;
    sub_8007F0D0(&work->field_548, &vec1, &vec2, &vec3);

    work->field_558 = 26200;
    work->field_55C = 26200;
    work->field_560 = 26200;
    work->field_568 = -26200;
    work->field_56C = -26200;
    work->field_570 = -26200;

    walls = work->control.map->hzd->f04_area->walls;
    for (i = 0; i < work->control.map->hzd->f04_area->n_walls; i++, walls++)
    {
        work->field_558 = min(work->field_558, walls->p1.x);
        work->field_55C = min(work->field_55C, walls->p1.y);
        work->field_560 = min(work->field_560, walls->p1.z);

        work->field_558 = min(work->field_558, walls->p2.x);
        work->field_55C = min(work->field_55C, walls->p2.y);
        work->field_560 = min(work->field_560, walls->p2.z);

        work->field_568 = max(work->field_568, walls->p1.x);
        work->field_56C = max(work->field_56C, walls->p1.y);
        work->field_570 = max(work->field_570, walls->p1.z + walls->p1.h);

        work->field_568 = max(work->field_568, walls->p2.x);
        work->field_56C = max(work->field_56C, walls->p2.y);
        work->field_570 = max(work->field_570, walls->p2.z + walls->p2.h);
    }

    altimetry = work->control.map->hzd->f04_area->altimetry;
    for (i = 0; i < work->control.map->hzd->f04_area->n_altimetry; i++, altimetry++)
    {
        work->field_558 = min(work->field_558, altimetry->b1.x);
        work->field_55C = min(work->field_55C, altimetry->b1.y);
        work->field_560 = min(work->field_560, altimetry->b1.z);

        work->field_558 = min(work->field_558, altimetry->b2.x);
        work->field_55C = min(work->field_55C, altimetry->b2.y);
        work->field_560 = min(work->field_560, altimetry->b2.z);

        work->field_568 = max(work->field_568, altimetry->b1.x);
        work->field_56C = max(work->field_56C, altimetry->b1.y);
        work->field_570 = max(work->field_570, altimetry->b1.z);

        work->field_568 = max(work->field_568, altimetry->b2.x);
        work->field_56C = max(work->field_56C, altimetry->b2.y);
        work->field_570 = max(work->field_570, altimetry->b2.z);
    }

    for (i = 0; i < 11; i++)
    {
        work->field_9C.objs->objs[i].world = DG_ZeroMatrix;
    }

    param = (unsigned char *)GCL_GetOption('v');
    if (param != NULL)
    {
        HindGetIntParams_800D11E0(param, work->field_7FC);
    }

    param = (unsigned char *)GCL_GetOption('c');
    if (param != NULL)
    {
        work->field_8EC = GCL_StrToInt(param);
    }
    else
    {
        work->field_8EC = -1;
    }

    param = (unsigned char *)GCL_GetOption('s');
    if (param != NULL)
    {
        work->field_8F0 = GCL_StrToInt(param);
    }
    else
    {
        work->field_8F0 = -1;
    }

    work->field_5F4 = 1536;
    work->field_8C0 = 0;
    work->field_8C4 = 0;
    work->field_5C4 = 0;
    work->field_5C8 = 0;
    work->field_5E0 = 0;
    work->field_5E4 = 0;
    work->field_5E8 = 0;
    work->field_5EC = 0;
    work->field_5F0 = 0;
    work->field_5F8 = 0;
    work->field_5D4 = 0;
    work->field_5D8 = 0;
    work->field_5DC = 0;
    work->field_7F8 = 0;
    work->field_658 = 0;
    work->field_644 = DG_ZeroVector;
    work->field_8FC = 5400;
    work->field_50C = 0;
    work->field_674 = 0;
    work->field_678 = 0;
    work->field_8E0 = 0;
    work->field_8CC = 0;
    work->field_8D0 = 0;
    work->field_8D4 = 0;
    work->field_900 = 0;

    if (work->field_4AC == 2)
    {
        work->field_930 = 1;
    }
    else
    {
        work->field_930 = 0;
    }

    work->field_8D8 = 0;
    work->field_8DC = 0;
    work->field_938 = 0;
    work->field_8E4 = NULL;
    work->field_93C = 0;
    work->field_940 = -1;
    work->field_94C = 0;
    work->field_950 = 0;
    work->field_954 = GV_RandU(8) + 8;
    work->field_958 = 0;
    work->field_95C = 0;
    work->field_960 = 0;

    GM_InitObject(&work->field_67C, GV_StrCode("hindmsil"), 0x25D, 0);
    GM_ConfigObjectJoint(&work->field_67C);
    GM_ConfigObjectLight(&work->field_67C, work->field_798_light4);
    GM_SetTarget(&work->field_57C, 4, 2, &s11g_dword_800C3598);

    switch (GM_DifficultyFlag)
    {
    default:
    case -1:
    case 0:
        GM_Target_8002DCCC(&work->field_57C, 7, 2, 0x100, 0, &s11g_dword_800C35A0);
        break;
    case 1:
        GM_Target_8002DCCC(&work->field_57C, 7, 2, 0x200, 0, &s11g_dword_800C35A0);
        break;
    case 2:
        GM_Target_8002DCCC(&work->field_57C, 7, 2, 0x400, 0, &s11g_dword_800C35A0);
        break;
    case 3:
        GM_Target_8002DCCC(&work->field_57C, 7, 2, 0x800, 0, &s11g_dword_800C35A0);
        break;
    }

    GM_VoxStream_80037E40(work->field_7FC[0], 0x40000000);

    for (i = 0; i < 32; i++)
    {
        work->field_970[i] = DG_ZeroVector;
    }

    work->field_A74 = 0;

    return &work->actor;
}

void Hind_LookAt_800D2C1C(SVECTOR *eye, SVECTOR *center)
{
    DG_LookAt(&DG_Chanls_800B1800[1], eye, center, 320);
    GM_Camera_800B77E8.field_2A = 0;
    gUnkCameraStruct2_800B7868.eye = *eye;
    gUnkCameraStruct2_800B7868.center = *center;
}

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D2CB4.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D2F60.s")

void s11g_hind_800D3214(HindWork *work)
{
    int field_654;
    int var_a2;
    int var_s1;

    if (GM_GameStatus & STATE_LIFEBAR_OFF)
    {
        return;
    }

    field_654 = work->field_654;
    if (field_654 < 0)
    {
        field_654 = 0;
    }

    var_s1 = work->field_7F4;
    var_a2 = var_s1;
    if (var_s1 < field_654)
    {
        var_a2 = field_654;
        var_s1 = field_654;
    }
    MENU_DrawBar_80038D74(16, 28, var_a2, field_654, &work->field_7E8);
    if (field_654 < var_s1)
    {
        work->field_7F4 -= 8;
        if (work->field_7F4 < field_654)
        {
            work->field_7F4 = field_654;
        }
    }
}

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D32CC.s")

// Identical to d03a_red_alrt_800C437C
int HindReceiveMessage_800D3334(unsigned short name, int nhashes, unsigned short *hashes)
{
    GV_MSG *msg;
    int     nmsgs;
    int     found;
    int     hash;
    int     i;

    nmsgs = GV_ReceiveMessage(name, &msg);
    found = -1;

    for (; nmsgs > 0; nmsgs--, msg++)
    {
        hash = msg->message[0];

        for (i = 0; i < nhashes; i++)
        {
            if (hash == hashes[i])
            {
                found = i;
            }
        }
    }

    return found;
}

void Hind_800D33CC(HindWork *work, int arg)
{
    GCL_ARGS args;
    long     argv[1];

    args.argc = 1;
    argv[0] = arg;
    args.argv = argv;

    GCL_ExecProc(work->field_8F0, &args);
}

#pragma INCLUDE_ASM("asm/overlays/s11g/HindAct_800D3404.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D45A4.s")

void HindDie_800D45C0(HindWork *work)
{
    GM_GameStatus &= ~STATE_PADDEMO;
    GM_GameStatus &= ~(STATE_RADAR_OFF | STATE_MENU_OFF | STATE_LIFEBAR_OFF);
    if (work->field_578 >= 0 && work->field_94C != 1 && work->field_A74 == 1)
    {
        GCL_ForceExecProc(work->field_578, NULL);
    }

    if (work->field_8E8 != NULL)
    {
        GV_DestroyOtherActor(work->field_8E8);
        work->field_8E8 = NULL;
    }

    if (work->field_8E4 != NULL)
    {
        GV_DestroyOtherActor(work->field_8E4);
        work->field_8E4 = NULL;
    }

    GM_FreeControl(&work->control);
    GM_FreeObject(&work->field_9C);
    GM_FreeObject(&work->field_180);
    GM_FreeObject(&work->field_264);
    GM_FreeObject(&work->field_67C);
    GM_FreeTarget(work->field_408);
    GM_FreeTarget(work->field_40C);
    GM_FreeTarget(work->field_410);
}

const char s11g_aHind_800DD128[] = "HIND";
const char s11g_aBulletoff_800DD130[] = "bullet_off";
const char s11g_aBulleton_800DD13C[] = "bullet_on";
const char s11g_aDestroy_800DD148[] = "destroy";
const int s11g_dword_800DD150 = 0x800D3818;
const int s11g_dword_800DD154 = 0x800D36F8;
const int s11g_dword_800DD158 = 0x800D3704;
const int s11g_dword_800DD15C = 0x800D3734;
const int s11g_dword_800DD160 = 0x800D37E8;
const int s11g_dword_800DD164 = 0x800D4E10;
const int s11g_dword_800DD168 = 0x800D4E40;
const int s11g_dword_800DD16C = 0x800D4EA8;
const int s11g_dword_800DD170 = 0x800D4F94;
const int s11g_dword_800DD174 = 0x800D50B0;
const char s11g_dword_800DD178[] = {0x0, 0x0, 0x0, 0x0};
const int s11g_dword_800DD17C = 0x800D5BE8;
const int s11g_dword_800DD180 = 0x800D5BD0;
const int s11g_dword_800DD184 = 0x800D5BFC;
const int s11g_dword_800DD188 = 0x800D5C18;
const int s11g_dword_800DD18C = 0x800D5C34;
const int s11g_dword_800DD190 = 0x800D68E0;
const int s11g_dword_800DD194 = 0x800D68F0;
const int s11g_dword_800DD198 = 0x800D69E4;
const int s11g_dword_800DD19C = 0x800D7628;
const int s11g_dword_800DD1A0 = 0x800D7628;
const int s11g_dword_800DD1A4 = 0x800D7020;
const int s11g_dword_800DD1A8 = 0x800D70A8;
const int s11g_dword_800DD1AC = 0x800D724C;
const int s11g_dword_800DD1B0 = 0x800D743C;
const int s11g_dword_800DD1B4 = 0x800D7628;
const int s11g_dword_800DD1B8 = 0x800D7628;
const int s11g_dword_800DD1BC = 0x800D7628;
const int s11g_dword_800DD1C0 = 0x800D7628;
const int s11g_dword_800DD1C4 = 0x800D7628;
const int s11g_dword_800DD1C8 = 0x800D7628;
const int s11g_dword_800DD1CC = 0x800D7628;
const int s11g_dword_800DD1D0 = 0x800D7628;
const int s11g_dword_800DD1D4 = 0x800D6A54;
const int s11g_dword_800DD1D8 = 0x800D6BE0;
const int s11g_dword_800DD1DC = 0x800D7628;
const int s11g_dword_800DD1E0 = 0x800D7628;
const int s11g_dword_800DD1E4 = 0x800D6D40;
const int s11g_dword_800DD1E8 = 0x800D7700;
const int s11g_dword_800DD1EC = 0x800D776C;
const int s11g_dword_800DD1F0 = 0x800D7868;
const int s11g_dword_800DD1F4 = 0x800D9260;
const int s11g_dword_800DD1F8 = 0x800D9260;
const int s11g_dword_800DD1FC = 0x800D7FB4;
const int s11g_dword_800DD200 = 0x800D80D8;
const int s11g_dword_800DD204 = 0x800D827C;
const int s11g_dword_800DD208 = 0x800D8458;
const int s11g_dword_800DD20C = 0x800D8D58;
const int s11g_dword_800DD210 = 0x800D90B4;
const int s11g_dword_800DD214 = 0x800D9260;
const int s11g_dword_800DD218 = 0x800D9260;
const int s11g_dword_800DD21C = 0x800D9260;
const int s11g_dword_800DD220 = 0x800D9260;
const int s11g_dword_800DD224 = 0x800D9260;
const int s11g_dword_800DD228 = 0x800D9260;
const int s11g_dword_800DD22C = 0x800D78D8;
const int s11g_dword_800DD230 = 0x800D7A68;
const int s11g_dword_800DD234 = 0x800D9260;
const int s11g_dword_800DD238 = 0x800D9260;
const int s11g_dword_800DD23C = 0x800D7C3C;
const int s11g_dword_800DD240 = 0x800D96F0;
const int s11g_dword_800DD244 = 0x800D9B70;
const int s11g_dword_800DD248 = 0x800D9B70;
const int s11g_dword_800DD24C = 0x800D9B70;
const int s11g_dword_800DD250 = 0x800D974C;
const int s11g_dword_800DD254 = 0x800D9858;
const int s11g_dword_800DD258 = 0x800D9A74;
const int s11g_dword_800DD25C = 0x800D9B40;
const int s11g_dword_800DD260 = 0x800D9BC4;
const int s11g_dword_800DD264 = 0x800DA520;
const int s11g_dword_800DD268 = 0x800DA520;
const int s11g_dword_800DD26C = 0x800DA520;
const int s11g_dword_800DD270 = 0x800D9C08;
const int s11g_dword_800DD274 = 0x800D9D74;
const int s11g_dword_800DD278 = 0x800D9FD8;
const int s11g_dword_800DD27C = 0x800DA0E0;
const int s11g_dword_800DD280 = 0x800DA2B4;
const char s11g_dword_800DD284[] = {0x0, 0x0, 0x0, 0x0};
const int s11g_dword_800DD288 = 0x800DA808;
const int s11g_dword_800DD28C = 0x800DAAB4;
const int s11g_dword_800DD290 = 0x800DAAB4;
const int s11g_dword_800DD294 = 0x800DAAB4;
const int s11g_dword_800DD298 = 0x800DA83C;
const int s11g_dword_800DD29C = 0x800DA85C;
const int s11g_dword_800DD2A0 = 0x800DA9B4;
const int s11g_dword_800DD2A4 = 0x800DAA48;
const int s11g_dword_800DD2A8 = 0x800DAA84;

int SECTION("overlay.bss") s11g_dword_800DD34C;
int SECTION("overlay.bss") s11g_dword_800DD350;
int SECTION("overlay.bss") s11g_dword_800DD354;
int SECTION("overlay.bss") s11g_dword_800DD358;
int SECTION("overlay.bss") s11g_dword_800DD35C;
int SECTION("overlay.bss") s11g_dword_800DD360;
int SECTION("overlay.bss") s11g_dword_800DD364;
int SECTION("overlay.bss") s11g_dword_800DD368;
int SECTION("overlay.bss") s11g_dword_800DD36C;
int SECTION("overlay.bss") s11g_dword_800DD370;
int SECTION("overlay.bss") s11g_dword_800DD374;
int SECTION("overlay.bss") s11g_dword_800DD378;

#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D46B8.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D46D8.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D4744.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D48E8.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D4990.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D4A24.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D4A80.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D4B68.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D4DD0.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D50F0.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D5420.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D5820.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D5CD8.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D5DE4.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D5E44.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D5E54.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D5F94.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D5FB4.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D60F0.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D619C.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D61F8.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D6260.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D62BC.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D63A4.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D648C.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D66F0.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D6848.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D7644.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D9344.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D96B0.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800D9B80.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800DA534.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800DA614.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800DA7C4.s")
#pragma INCLUDE_ASM("asm/overlays/s11g/s11g_hind_800DAAC8.s")