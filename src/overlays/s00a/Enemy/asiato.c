#include "libgv/libgv.h"
#include "Game/game.h"

extern const char aAsiatoc_800E0998[]; // asiato.c
extern SVECTOR    asiato_svecs[49];
extern int        s00a_dword_800E0F90;

extern unsigned int GM_PlayerStatus_800ABA50;
extern SVECTOR      GM_PlayerPosition_800ABA10;
extern int          dword_800AB9D4;
extern CONTROL     *GM_WhereList_800B56D0[96];

typedef struct AsiatoWork
{
    GV_ACT actor;
    int    field_20;
    int    field_24;
} AsiatoWork;

void s00a_asiato_800D0DD4(int param_1, char param_2, char param_3, char param_4, char param_5)
{
    int iVar1;

    iVar1 = *(int *)(param_1 + 0x40);
    *(char *)(iVar1 + 4) = param_3;
    *(char *)(iVar1 + 5) = param_4;
    *(char *)(iVar1 + 6) = param_5;
    iVar1 = *(int *)(param_1 + 0x44);
    *(char *)(iVar1 + 4) = param_3;
    *(char *)(iVar1 + 5) = param_4;
    *(char *)(iVar1 + 6) = param_5;
    return;
}

void s00a_asiato_800D0E00(SVECTOR *out, short vx, short vy, short vz)
{
    out->vx = vx;
    out->vy = vy;
    out->vz = vz;
}

#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D0E10.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D0E9C.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D0F90.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D116C.s")

// NewAsiatoChar
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D11DC.s")

void AsiatoPos_800D129C(int idx, SVECTOR *out)
{
    *out = asiato_svecs[idx];
}

int NextAsiato_800D12D0(HZD_HDL *hdl, int idx, SVECTOR *svec2)
{
    SVECTOR *vec;

    if (++idx >= 48)
    {
        idx = 0;
    }

    vec = &asiato_svecs[idx];
    if (GV_DistanceVec3_80016E84(svec2, vec) >= 5000)
    {
        return -1;
    }

    if (sub_80028454(hdl, svec2, vec, 15, 2))
    {
        return -1;
    }

    if (vec->pad == 1)
    {
        return idx;
    }

    return -1;
}

void CleanAsiato_800D1378()
{
    int i;

    for (i = 0; i < 48; i++)
    {
        asiato_svecs[i].pad = 0;
    }
}

int NearAsiato_800D13A0()
{
    return s00a_dword_800E0F90;
}

#pragma INCLUDE_ASM("asm/overlays/s00a/SearchNearAsiato_800D13B0.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D1500.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D15D8.s")

#pragma INCLUDE_ASM("asm/overlays/s00a/AsiatoCheck_800D16C0.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D16F8.s")
int s00a_asiato_800D16F8(AsiatoWork *work, HZD_HDL *hdl, SVECTOR *pos);

int s00a_asiato_800D179C()
{
    // If player is moving and not on wall or prone
    return (GM_PlayerStatus_800ABA50 & (PLAYER_ON_WALL | PLAYER_MOVING | PLAYER_PRONE)) == PLAYER_MOVING;
}

int s00a_asiato_800D17BC(AsiatoWork *work)
{
    HZD_HDL *hdl;

    hdl = GM_WhereList_800B56D0[0]->field_2C_map->field_8_hzd;
    if (!s00a_asiato_800D179C() || !s00a_asiato_800D16F8(work, hdl, &GM_PlayerPosition_800ABA10))
    {
        return 0;
    }

    if (dword_800AB9D4 != 2)
    {
        return dword_800AB9D4 == 10 ? 2 : 0;
    }
    return 1;
}

#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D1844.s")
#pragma INCLUDE_ASM("asm/overlays/s00a/s00a_asiato_800D18C8.s")

void AsiatoDie_800D1994(AsiatoWork *work)
{
}

void s00a_asiato_800D199C(AsiatoWork *work)
{
    int i;

    for (i = 0; i < 48; i++)
    {
        s00a_asiato_800D0E00(&asiato_svecs[i], 0, 0, 0);
        asiato_svecs[i].pad = 0;
    }

    asiato_svecs[48].vx = 0;
    asiato_svecs[48].vy = 0;
    work->field_24 = 0;
}

void s00a_asiato_800D18C8(AsiatoWork *work);

GV_ACT *NewAsiato_800D1A14(int name, int where, int argc, char **argv)
{
    AsiatoWork *work;

    work = (AsiatoWork *)GV_NewActor_800150E4(4, sizeof(AsiatoWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s00a_asiato_800D18C8,
                                  (TActorFunction)AsiatoDie_800D1994, aAsiatoc_800E0998);
        s00a_asiato_800D199C(work);
    }

    return &work->actor;
}

GV_ACT *NewAsiatoKun_800D1A70(int name, int where, int argc, char **argv)
{
    // Identical to NewAsiato_800D1A14
    AsiatoWork *work;

    work = (AsiatoWork *)GV_NewActor_800150E4(4, sizeof(AsiatoWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s00a_asiato_800D18C8,
                                  (TActorFunction)AsiatoDie_800D1994, aAsiatoc_800E0998);
        s00a_asiato_800D199C(work);
    }

    return &work->actor;
}
