#include "strcode.h"
#include "game/game.h"
#include "libgcl/libgcl.h"

typedef struct _JEEP_SYSTEM
{
    char     pad1[0x4];
    CONTROL *control;
    char     pad2[0x10];
    SVECTOR  pos;
    char     pad3[0x18];
    SVECTOR  field_38;
    int      field_40;
    char     pad4[0x1C];
    OBJECT  *body;
    char     pad5[0x18];
    int      field_7C;
    MATRIX   world;
    char     pad6[0xCC];
} JEEP_SYSTEM;

extern JEEP_SYSTEM Takabe_JeepSystem;

#define EXEC_LEVEL 4

typedef struct _Work
{
    GV_ACT work;
    char   pad1[0xC50];
    int    field_C70;
    int    field_C74;
    char   pad2[0xC];
} Work;

const char s19b_aLightoverjeepsrlc_800DDC94[] = "<<<<< light over !!!!!!!(jeep.srl.c) >>>>>\n";
const char s19b_aMaxlightd_800DDCC0[] = "max light:%d\n";
const char s19b_aJsnake_800DDCD0[] = "j_snake";

void *NewJeepGate(int name, SVECTOR *pos, int side);
void *NewJeepGlass(int name, SVECTOR *pos, int side);
void *NewJeepLamp(SVECTOR *root_pos, int tex_id, int unused);
void *s19b_jeep2_800D6F24(int name, int map); // NewJeep2

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_srl_800CD638.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_srl_800CD790.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_srl_800CD7B4.s")

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_srl_800CDAA4.s")
void s19b_jeep_srl_800CDAA4(Work *work);

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_srl_800CDF48.s")
void s19b_jeep_srl_800CDF48(Work *work);

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_srl_800CE020.s")
int s19b_jeep_srl_800CE020(Work *work, int name, int where);

void *NewJeepScroll(int name, int where)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(work, s19b_jeep_srl_800CDAA4, s19b_jeep_srl_800CDF48, "jeep_srl.c");

        if (s19b_jeep_srl_800CE020(work, name, where) < 0)
        {
            GV_DestroyActor(work);
            return NULL;
        }
    }

    return work;
}

#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_gls_800CE400.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_gls_800CE52C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_gls_800CE5F8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_gls_800CE628.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_gls_800CE83C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_gls_800CE8B8.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_gls_800CE8DC.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_gls_800CEB2C.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_gls_800CEC24.s")
#pragma INCLUDE_ASM("asm/overlays/s19b/s19b_jeep_gls_800CEDFC.s")

void s19b_jeep_gls_800CEE7C(Work *work, int arg1, SVECTOR *pos)
{
    GCL_ARGS args;
    SVECTOR  diff;
    int      state;
    int      proc_id;
    
    Takabe_JeepSystem.field_38 = *pos;
    state = Takabe_JeepSystem.field_40;

    GV_SubVec3(pos, &Takabe_JeepSystem.pos, &diff);

    if (state == 2)
    {
        Takabe_JeepSystem.field_7C = 0;

        NewJeepGate(1, &diff, 0);
        NewJeepGate(1, &diff, 1);
        NewJeepGlass(2, &diff, 0);
        NewJeepGlass(2, &diff, 1);

        proc_id = work->field_C70;
        if (proc_id)
        {
            args.argc = 0;
            args.argv = NULL;
            GCL_ExecProc(proc_id, &args);
        }
    }
    else if (state == 4)
    {
        Takabe_JeepSystem.field_7C = 0;

        NewJeepGate(1, &diff, 0);
        NewJeepGate(1, &diff, 1);
        NewJeepGlass(2, &diff, 0);
        NewJeepGlass(2, &diff, 1);

        proc_id = work->field_C74;
        if (proc_id)
        {
            args.argc = 0;
            args.argv = NULL;
            GCL_ExecProc(proc_id, &args);
        }
    }
    else if (state == 5)
    {
        s19b_jeep2_800D6F24(GV_StrCode("j_liquid"), GM_CurrentMap);
    }
}

void s19b_jeep_gls_800CEFE4(Work *work, int disable)
{
    SVECTOR diff;
    SVECTOR pos;

    GV_SubVec3(&Takabe_JeepSystem.field_38, &Takabe_JeepSystem.pos, &diff);

    if (disable == 0)
    {
        pos.vx = diff.vx + 1562;
        pos.vy = diff.vy + 1815;
        pos.vz = diff.vz - 500;
        NewJeepLamp(&pos, PCX_JEEP_BONBORI_ADD, 0);

        pos.vx = diff.vx - 1562;
        pos.vy = diff.vy + 1815;
        pos.vz = diff.vz - 500;
        NewJeepLamp(&pos, PCX_JEEP_BONBORI_ADD, 0);
    }
}

void s19b_jeep_gls_800CF088(void)
{
    GV_ZeroMemory(&Takabe_JeepSystem, sizeof(Takabe_JeepSystem));
}
