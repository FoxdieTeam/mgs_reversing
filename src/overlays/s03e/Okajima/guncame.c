#include "libgv/libgv.h"
#include "Game/control.h"
#include "Game/game.h"
#include "Game/object.h"

// We came, we saw, GunCamE
typedef struct GunCamEWork
{
    GV_ACT   actor;
    CONTROL  field_20;
    OBJECT   field_9C;
    int      field_C0;
    int      field_C4;
    int      field_C8;
    int      field_CC;
    int      field_D0;
    int      field_D4;
    int      field_D8;
    int      field_DC;
    int      field_E0;
    int      field_E4;
    int      field_E8;
    int      field_EC;
    int      field_F0;
    int      field_F4;
    int      field_F8;
    int      field_FC;
    int      field_100;
    int      field_104;
    int      field_108;
    int      field_10C;
    int      field_110;
    int      field_114;
    int      field_118;
    int      field_11C;
    int      field_120;
    int      field_124;
    int      field_128;
    int      field_12C;
    int      field_130;
    int      field_134;
    int      field_138;
    int      field_13C;
    int      field_140;
    int      field_144;
    int      field_148;
    int      field_14C;
    int      field_150;
    int      field_154;
    int      field_158;
    int      field_15C;
    int      field_160;
    int      field_164;
    int      field_168;
    int      field_16C;
    int      field_170;
    int      field_174;
    int      field_178;
    int      field_17C;
    MATRIX   field_180;
    int      field_1A0;
    int      field_1A4;
    int      field_1A8;
    int      field_1AC;
    int      field_1B0;
    int      field_1B4;
    int      field_1B8;
    int      field_1BC;
    int      field_1C0;
    int      field_1C4;
    int      field_1C8;
    int      field_1CC;
    int      field_1D0;
    int      field_1D4;
    int      field_1D8;
    int      field_1DC;
    TARGET  *field_1E0;
    int      field_1E4;
    int      field_1E8;
    int      field_1EC;
    int      field_1F0;
    OBJECT   field_1F4;
    int      field_218;
    int      field_21C;
    int      field_220;
    int      field_224;
    int      field_228;
    int      field_22C;
    int      field_230;
    int      field_234;
    int      field_238;
    int      field_23C;
    int      field_240;
    int      field_244;
    int      field_248;
    int      field_24C;
    int      field_250;
    int      field_254;
    int      field_258;
    int      field_25C;
    int      field_260;
    int      field_264;
    int      field_268;
    int      field_26C;
    int      field_270;
    int      field_274;
    int      field_278;
    int      field_27C;
    int      field_280;
    int      field_284;
    int      field_288;
    int      field_28C;
    int      field_290;
    int      field_294;
    int      field_298;
    int      field_29C;
    int      field_2A0;
    int      field_2A4;
    int      field_2A8;
    int      field_2AC;
    int      field_2B0;
    int      field_2B4;
    int      field_2B8;
    int      field_2BC;
    int      field_2C0;
    int      field_2C4;
    int      field_2C8;
    int      field_2CC;
    int      field_2D0;
    int      field_2D4;
    MATRIX   field_2D8;
    int      field_2F8;
    int      field_2FC;
    int      field_300;
    int      field_304;
    int      field_308;
    int      field_30C;
    int      field_310;
    int      field_314;
    SVECTOR  field_318;
    int      field_320;
    int      field_324;
    DG_PRIM *field_328;
    DG_TEX  *field_32C;
    int      field_330;
    int      field_334;
    int      field_338;
    int      field_33C;
    int      field_340;
    int      field_344;
    int      field_348;
    int      field_34C;
    int      field_350;
    int      field_354;
    int      field_358;
    int      field_35C;
    int      field_360;
    int      field_364;
    int      field_368;
    int      field_36C;
    int      field_370;
    int      field_374;
    int      field_378;
    int      field_37C;
    int      field_380;
    int      field_384;
    int      field_388;
    int      field_38C;
    int      field_390;
    int      field_394;
    int      field_398;
    int      field_39C;
    int      field_3A0;
    int      field_3A4;
    int      field_3A8;
    SVECTOR  field_3AC;
    SVECTOR  field_3B4;
    int      field_3BC;
    int      field_3C0;
    int      field_3C4;
    int      field_3C8;
    int      field_3CC;
    int      field_3D0;
    int      field_3D4;
    int      field_3D8;
    int      field_3DC;
    int      field_3E0;
    int      field_3E4;
    int      field_3E8;
    int      field_3EC;
    int      field_3F0;
    int      field_3F4;
    int      field_3F8;
    int      field_3FC;
    int      field_400;
    int      field_404;
    int      field_408;
    int      field_40C;
    int      field_410;
    int      field_414;
    int      field_418;
} GunCamEWork;

extern int     dword_8009F480;
extern int     s03e_dword_800C32B8;
extern SVECTOR DG_ZeroVector_800AB39C;
extern char    s03e_aGcaarm_800CC110[];
extern char    s03e_aGcagun_800CC108[];
extern int     s03e_dword_800C32B4;
extern SVECTOR guncame_svec;
extern int     s03e_dword_800CC6BC;
extern int     s03e_dword_800C32B4;
extern char    s03e_dword_800CC118[];
extern char    s03e_aCameral_800CC0FC[];
extern RECT    guncame_rect;
extern SVECTOR GM_PlayerPosition_800ABA10;
extern int     dword_8009F46C[];
extern int     dword_8009F480;
extern SVECTOR svector_8009F478;

int  s03e_guncame_800C8978(GunCamEWork *, int, int);
int  s03e_guncame_800C8E7C(GunCamEWork *);
void s03e_guncame_800C80F4(GunCamEWork *);

#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C6F60.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C6FF8.s")

void s03e_guncame_800C7068(GunCamEWork *work)
{
    work->field_3A0 = 1;
    work->field_3AC = GM_PlayerPosition_800ABA10;
    if (dword_8009F46C[0] == 1)
    {
        work->field_3A4 = dword_8009F46C[0];
        work->field_3B4 = svector_8009F478;
    }
    else
    {
        work->field_3B4 = GM_PlayerPosition_800ABA10;
        work->field_3A4 = 0;
        dword_8009F480 = 0;
        work->field_3C4 = 0;
    }
}

#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C7118.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C7144.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C7154.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C71A8.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C7224.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C73D0.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C75FC.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C76E8.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C7740.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C77D4.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C7868.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C7994.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C7AD8.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C7C0C.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C7CE0.s")

void s03e_guncame_800C8024(GunCamEWork *work)
{
    work->field_20.field_3C.vx = work->field_20.field_8_rotator.vy;
}

#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C8030.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C80F4.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C8924.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C8940.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C8978.s")
#pragma INCLUDE_ASM("asm/overlays/s03e/s03e_guncame_800C8E04.s")
void s03e_guncame_800C8E04(POLY_FT4 *, DG_TEX *, int);

int s03e_guncame_800C8E7C(GunCamEWork *work)
{
    DG_PRIM *prim;
    DG_TEX  *tex;

    work->field_318.vx = -90;
    work->field_318.vy = 300;
    work->field_318.vz = 350;
    prim = DG_GetPrim(0x412, 1, 0, &work->field_318, &guncame_rect);
    work->field_328 = prim;
    if (prim != NULL)
    {
        prim->field_2E_k500 = 500;
        tex = DG_GetTexture_8001D830(GV_StrCode_80016CCC(s03e_aCameral_800CC0FC));
        work->field_32C = tex;
        if (tex != 0)
        {
            s03e_guncame_800C8E04(&prim->field_40_pBuffers[0]->poly_ft4, tex, 128);
            s03e_guncame_800C8E04(&prim->field_40_pBuffers[1]->poly_ft4, tex, 100);
            return 0;
        }
    }
    return -1;
}

int s03e_guncame_800C8F64(GunCamEWork *work, int name, int where)
{
    CONTROL *control;
    OBJECT  *obj1, *obj2;

    control = &work->field_20;
    work->field_404 = 1;
    work->field_408 = 1;
    work->field_3DC = name;

    if (GM_InitLoader_8002599C(control, name, where) < 0)
    {
        return -1;
    }

    GM_ConfigControlAttribute_8002623C(control, 7);
    GM_ConfigControlHazard_8002622C(control, -1, -2, -1);
    GM_ConfigControlInterp_80026244(control, 4);
    work->field_20.field_44_movementVector = DG_ZeroVector_800AB39C;

    obj1 = &work->field_9C;
    do {} while (0);
    GM_InitObject_80034A18(obj1, GV_StrCode_80016CCC(s03e_aGcagun_800CC108), 0x26D, 0);
    GM_ConfigObjectLight_80034C44(obj1, &work->field_180);

    obj2 = &work->field_1F4;
    do {} while (0);
    GM_InitObject_80034A18(obj2, GV_StrCode_80016CCC(s03e_aGcaarm_800CC110), 0x26D, 0);
    GM_ConfigObjectLight_80034C44(obj2, &work->field_2D8);

    if (s03e_guncame_800C8E7C(work) == -1)
    {
        return -1;
    }

    work->field_1E0 = GM_AllocTarget_8002D400();
    if (work->field_1E0)
    {
        GM_SetTarget_8002DC74(work->field_1E0, 0x15, 2, &guncame_svec);
        s03e_guncame_800C8978(work, name, where);
        DG_GetLightMatrix_8001A3C4(&control->field_0_mov, &work->field_180);
        DG_GetLightMatrix_8001A3C4(&control->field_0_mov, &work->field_2D8);
        s03e_dword_800CC6BC = 0;
        work->field_40C = 0;
        work->field_410 = 0;
        work->field_414 = s03e_dword_800C32B4;
        return 0;
    }

    return -1;
}

void s03e_guncame_800C911C(GunCamEWork *work)
{
    DG_PRIM *prim;

    s03e_dword_800C32B8 = 0;
    dword_8009F480 = 0;
    GM_FreeObject_80034BF8(&work->field_9C);
    GM_FreeObject_80034BF8(&work->field_1F4);
    GM_FreeTarget_8002D4B0(work->field_1E0);
    GM_FreeControl_800260CC(&work->field_20);
    prim = work->field_328;
    if (prim)
    {
        DG_DequeuePrim_800182E0(prim);
        DG_FreePrim_8001BC04(prim);
    }
}

GV_ACT *s03e_guncame_800C9190(int name, int where, int argc, char **argv)
{
    GunCamEWork *work;

    work = (GunCamEWork *)GV_NewActor_800150E4(4, sizeof(GunCamEWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s03e_guncame_800C80F4,
                                  (TActorFunction)s03e_guncame_800C911C, s03e_dword_800CC118);
        if (s03e_guncame_800C8F64(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
        work->field_378 = where;
        s03e_dword_800C32B4++;
    }
    return &work->actor;
}
