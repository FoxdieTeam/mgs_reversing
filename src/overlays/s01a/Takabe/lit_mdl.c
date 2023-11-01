#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "Game/game.h"
#include "Game/object.h"

typedef struct LitMdlWork
{
    GV_ACT         actor;
    int            field_20;
    OBJECT_NO_ROTS field_24_obj;
    MATRIX         field_48_light;
    int            field_68;
    int            field_6C;
    int            field_70;
    int            field_74;
    int            field_78;
    int            field_7C;
    int            field_80;
    int            field_84;
    MATRIX         field_88_root;
    int            field_A8;
    int            field_AC;
    int            field_B0;
    int            field_B4;
    int            field_B8;
    int            field_BC;
    int            field_C0;
    int            field_C4;

    DG_DEF field_C8;
    DG_MDL field_E8;

    int field_140;
    int field_144;
    int field_148;
    int field_14C;
    int field_150;
    int field_154;
    int field_158;
    int field_15C;
    int field_160;
    int field_164;
    int field_168;
    int field_16C;
    int field_170;
    int field_174;
    int field_178;
    int field_17C;
    int field_180;
    int field_184;
    int field_188;
    int field_18C;
    int field_190;
    int field_194;
    int field_198;
    int field_19C;
    int field_1A0;
    int field_1A4;
    int field_1A8;
    int field_1AC;
    int field_1B0;
    int field_1B4;
    int field_1B8;
    int field_1BC;
    int field_1C0;
    int field_1C4;
    int field_1C8;
    int field_1CC;
    int field_1D0;
    int field_1D4;
    int field_1D8;
    int field_1DC;
    int field_1E0;
    int field_1E4;
    int field_1E8;
    int field_1EC;
    int field_1F0;
    int field_1F4;
    int field_1F8;
    int field_1FC;
    int field_200;
    int field_204;
    int field_208;
    int field_20C;
    int field_210;
    int field_214;
    int field_218;
    int field_21C;
    int field_220;
    int field_224;
    int field_228;
    int field_22C;
    int field_230;
    int field_234;
    int field_238;
    int field_23C;
    int field_240;
    int field_244;
    int field_248;
    int field_24C;
    int field_250;
    int field_254;
    int field_258;
    int field_25C;
    int field_260;
    int field_264;
    int field_268;
    int field_26C;
    int field_270;
    int field_274;
    int field_278;
    int field_27C;
    int field_280;
    int field_284;
    int field_288;
    int field_28C;
    int field_290;
    int field_294;
    int field_298;
    int field_29C;
    int field_2A0;
    int field_2A4;
    int field_2A8;
    int field_2AC;
    int field_2B0;
    int field_2B4;
    int field_2B8;
    int field_2BC;
    int field_2C0;
    int field_2C4;
    int field_2C8;
    int field_2CC;
    int field_2D0;
    int field_2D4;
    int field_2D8;
    int field_2DC;
    int field_2E0;
    int field_2E4;
    int field_2E8;
    int field_2EC;
    int field_2F0;
    int field_2F4;
    int field_2F8;
    int field_2FC;
    int field_300;
    int field_304;
    int field_308;
    int field_30C;
    int field_310;
    int field_314;
    int field_318;
    int field_31C;
    int field_320;
    int field_324;
    int field_328;
    int field_32C;
    int field_330;
    int field_334;
    int field_338;
    int field_33C;
    int field_340;
    int field_344;
    int field_348;
    int field_34C;
    int field_350;
    int field_354;
    int field_358;
    int field_35C;
    int field_360;
    int field_364;
    int field_368;
    int field_36C;
    int field_370;
    int field_374;
    int field_378;
    int field_37C;
    int field_380;
    int field_384;
    int field_388;
    int field_38C;
    int field_390;
    int field_394;
    int field_398;
    int field_39C;
    int field_3A0;
    int field_3A4;
    int field_3A8;
    int field_3AC;
    int field_3B0;
    int field_3B4;
    int field_3B8;
    int field_3BC;
    int field_3C0;
    int field_3C4;
    int field_3C8;
    int field_3CC;
    int field_3D0;
    int field_3D4;
    int field_3D8;
    int field_3DC;
    int field_3E0;
    int field_3E4;
    int field_3E8;
    int field_3EC;
    int field_3F0;
    int field_3F4;
    int field_3F8;
    int field_3FC;
    int field_400;
    int field_404;
    int field_408;
    int field_40C;
    int field_410;
    int field_414;
    int field_418;
    int field_41C;
    int field_420;
    int field_424;
    int field_428;
    int field_42C;
    int field_430;
    int field_434;
    int field_438;
    int field_43C;
    int field_440;
    int field_444;
    int field_448;
    int field_44C;
    int field_450;
    int field_454;
    int field_458;
    int field_45C;
    int field_460;
    int field_464;
    int field_468;
    int field_46C;
    int field_470;
    int field_474;
    int field_478;
    int field_47C;
    int field_480;
    int field_484;
    int field_488;
    int field_48C;
    int field_490;
    int field_494;
    int field_498;
    int field_49C;
    int field_4A0;
    int field_4A4;
    int field_4A8;
    int field_4AC;
    int field_4B0;
    int field_4B4;
    int field_4B8;
    int field_4BC;
    int field_4C0;
    int field_4C4;
    int field_4C8;
    int field_4CC;
    int field_4D0;
    int field_4D4;
    int field_4D8;
    int field_4DC;
    int field_4E0;
    int field_4E4;
    int field_4E8;
    int field_4EC;
    int field_4F0;
    int field_4F4;
    int field_4F8;
    int field_4FC;
    int field_500;
    int field_504;
    int field_508;
    int field_50C;
    int field_510;
    int field_514;
    int field_518;
    int field_51C;
    int field_520;
    int field_524;
    int field_528;
    int field_52C;
    int field_530;
    int field_534;
    int field_538;
    int field_53C;
    int field_540;
    int field_544;
    int field_548;
    int field_54C;
    int field_550;
    int field_554;
    int field_558;
    int field_55C;
    int field_560;
    int field_564;
    int field_568;
    int field_56C;
    int field_570;
    int field_574;
    int field_578;
    int field_57C;
    int field_580;
    int field_584;
} LitMdlWork;

extern char    aLitmdlC[];
extern DG_DEF  litmdl_dg_def; // with 1 DG_MDL
extern MATRIX  DG_ZeroMatrix_8009D430;
extern SVECTOR DG_ZeroVector_800AB39C;
extern int     GM_CurrentMap_800AB9B0;

#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_lit_mdl_800E26EC.s")
#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_lit_mdl_800E2928.s")

void s01a_lit_mdl_800E2ABC(LitMdlWork *work)
{
    GM_FreeObject_80034BF8((OBJECT *)&work->field_24_obj);
}

int s01a_camshake_800E2D64(LitMdlWork *, SVECTOR *);

int s01a_lit_mdl_800E2ADC(LitMdlWork *work, int arg2, int arg3, int arg4, int raise)
{
    OBJECT_NO_ROTS *obj;
    short           map;

    memcpy(&work->field_C8, &litmdl_dg_def, sizeof(DG_DEF) + sizeof(DG_MDL));
    s01a_camshake_800E2D64(work, &DG_ZeroVector_800AB39C);

    obj = &work->field_24_obj;
    obj->flag = 0x15D;
    obj->light = &work->field_48_light;
    obj->map_name = GM_CurrentMap_800AB9B0;
    obj->objs = DG_MakeObjs_80031760(&work->field_C8, obj->flag, 0);
    DG_QueueObjs_80018178(obj->objs);

    map = obj->map_name;
    work->field_24_obj.objs->group_id = map;
    work->field_24_obj.objs->root = &work->field_88_root;
    work->field_24_obj.objs->light = &work->field_48_light;
    work->field_24_obj.objs->objs[0].raise = raise;
    work->field_20 = GM_CurrentMap_800AB9B0;
    work->field_88_root = DG_ZeroMatrix_8009D430;
    work->field_B0 = 1;
    work->field_A8 = arg2;
    work->field_AC = arg3;
    work->field_B4 = arg4;
    work->field_B8 = arg4 / 6;
    work->field_BC = arg4 / 6;
    return 0;
}

void s01a_lit_mdl_800E2928(LitMdlWork *);

GV_ACT *s01a_lit_mdl_800E2C88(int arg0, int arg1, int arg2, int arg3)
{
    LitMdlWork *work;

    work = (LitMdlWork *)GV_NewActor_800150E4(7, sizeof(LitMdlWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s01a_lit_mdl_800E2928,
                                  (TActorFunction)s01a_lit_mdl_800E2ABC, aLitmdlC);
        if (s01a_lit_mdl_800E2ADC(work, arg0, arg1, arg2, arg3) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}

#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_camshake_800E2D3C.s")
#pragma INCLUDE_ASM("asm/overlays/s01a/s01a_camshake_800E2D64.s")
