#include "libgv/libgv.h"
#include "Game/linkvarbuf.h"

typedef struct GasDamgeWork {
    GV_ACT actor;
    int    field_20;
    int    field_24;
    int    field_28;
    int    field_2C;
    int    field_30;
    int    field_34;
    int    field_38;
    int    field_3C;
    int    field_40;
} GasDamgeWork;

// FIXME: this BSS variable is outside of overlay bounds???
int SECTION("overlay.bss") s02c_dword_800E3F40[0];

extern short GM_O2_800ABA34;

int THING_Gcl_GetInt(char param);

void GasDamageAct_800E1348(GasDamgeWork *work)
{
    int temp_a0;
    int temp_a0_2;
    int temp_a1;
    int field_3C;
    int divisor;
    int field_40;

    if (s02c_dword_800E3F40[0] != 0)
    {
        if (GM_CurrentItemId == ITEM_GASMASK)
        {
            divisor = work->field_38;
        }
        else
        {
            divisor = 1;
        }
        temp_a0 = work->field_28 + work->field_2C / divisor;
        GM_O2_800ABA34 -= temp_a0 >> 0xC;
        work->field_28 = temp_a0 & 0xFFF;
        if (GM_O2_800ABA34 < 0)
        {
            GM_O2_800ABA34 = 0;
            temp_a0_2 = work->field_30 + work->field_34;
            GM_SnakeCurrentHealth -= temp_a0_2 >> 0xC;
            work->field_30 = temp_a0_2 & 0xFFF;
        }
    }
    temp_a1 = s02c_dword_800E3F40[0];

    if (!(s02c_dword_800E3F40[0] & 2))
    {
        field_3C = work->field_3C;
        field_40 = work->field_40;
        if (temp_a1 & 1)
        {
            field_40 >>= 3;
        }

        field_3C += field_40;
        work->field_3C = field_3C & 0xFFF;
        GM_O2_800ABA34 += field_3C >> 0xC;
        if (GM_O2_800ABA34 > 0x400)
        {
            GM_O2_800ABA34 = 0x400;
        }
    }
    s02c_dword_800E3F40[0] = 0;
}

void GasDamageDie_800E147C(GasDamgeWork *work)
{
    s02c_dword_800E3F40[0] = 0;
}

int GasDamageGetResources_800E1488(GasDamgeWork *work, int arg0, int arg1)
{
    work->field_2C = THING_Gcl_GetInt('o');
    work->field_34 = THING_Gcl_GetInt('h');
    work->field_38 = THING_Gcl_GetInt('m');
    work->field_40 = THING_Gcl_GetInt('r');
    work->field_30 = 0;
    work->field_28 = 0;
    work->field_3C = 0;
    return 0;
}

GV_ACT * NewGasDamage_800E14E8(int name, int where, int argc, char **argv)
{
    GasDamgeWork *work;

    work = (GasDamgeWork *)GV_NewActor_800150E4(5, sizeof(GasDamgeWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)GasDamageAct_800E1348, (TActorFunction)GasDamageDie_800E147C, "gasdamge.c");
        if (GasDamageGetResources_800E1488(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
        work->field_20 = where;
        work->field_24 = name;
    }
    return &work->actor;
}
