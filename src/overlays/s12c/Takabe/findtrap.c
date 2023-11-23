#include "libgv/libgv.h"
#include "Game/camera.h"

typedef struct FindTrapWork
{
    GV_ACT  actor;
    int     field_20;
    int     field_24;
    SVECTOR field_28;
    SVECTOR field_30;
    int     field_38;
    int     field_3C;
    int     field_40;
    int     field_44;
    int     field_48;
} FindTrapWork;

short s12c_dword_800C350C[4] = {0x0DD2, 0xD5CC, 0x42DC, 0x3223};

SVECTOR SECTION("overlay.bss") s12c_dword_800DAA50;
int     SECTION("overlay.bss") s12c_dword_800DAA58;
int     SECTION("overlay.bss") s12c_dword_800DAA5C;
int     SECTION("overlay.bss") s12c_dword_800DAA60;
int     SECTION("overlay.bss") s12c_dword_800DAA64;
SVECTOR SECTION("overlay.bss") s12c_dword_800DAA68;
GV_PAD  SECTION("overlay.bss") s12c_dword_800DAA70[2];

int           SECTION("overlay.bss") s12c_dword_800DAA90;
TGMCameraFunc SECTION("overlay.bss") s12c_dword_800DAA94;

extern GM_Camera       GM_Camera_800B77E8;
extern UnkCameraStruct gUnkCameraStruct_800B77B8;
extern CONTROL        *GM_PlayerControl_800AB9F4;
extern GV_PAD          GV_PadData_800B05C0[4];

int  THING_Gcl_GetInt(char param);
void THING_Gcl_GetSVectorDefault(char param, short x, short y, short z, SVECTOR *vec);
void THING_Gcl_GetSVector(char param, SVECTOR *vec);

#pragma INCLUDE_ASM("asm/overlays/s12c/s12c_findtrap_800D72E8.s")
void s12c_findtrap_800D72E8(FindTrapWork *work);

void FindTrapDie_800D7734(FindTrapWork *work)
{
    GM_GameStatus_800AB3CC &= ~GAME_FLAG_BIT_31;
    GM_Camera_800B77E8.field_18_flags &= ~0x200;
}

int FindTrapGetResources_800D7768(FindTrapWork *work, int name, int where)
{
    work->field_24 = name;
    GM_CurrentMap_800AB9B0 = where;
    work->field_20 = where;
    THING_Gcl_GetSVector('p', &work->field_28);
    work->field_38 = THING_Gcl_GetInt('e');
    THING_Gcl_GetSVectorDefault('s', 160, 112, 0, &work->field_30);
    work->field_40 = THING_Gcl_GetInt('w');
    return 0;
}

GV_ACT *NewFindTrap_800D77DC(int name, int where, int argc, char **argv)
{
    FindTrapWork *work;

    work = (FindTrapWork *)GV_NewActor_800150E4(5, sizeof(FindTrapWork));
    if (work != NULL)
    {
        GV_SetNamedActor_8001514C(&work->actor, (TActorFunction)s12c_findtrap_800D72E8,
                                  (TActorFunction)FindTrapDie_800D7734, "findtrap.c");
        if (FindTrapGetResources_800D7768(work, name, where) < 0)
        {
            GV_DestroyActor_800151C8(&work->actor);
            return NULL;
        }
    }
    return &work->actor;
}

void s12c_findtrap_800D7870()
{
    int temp_a2;

    temp_a2 = s12c_dword_800DAA58;
    if (s12c_dword_800DAA58 >= 0)
    {
        if (s12c_dword_800DAA58 < 16)
        {
            s12c_dword_800DAA58--;
            GM_Camera_800B77E8.field_10.vy &= 0xFFF;
            GM_Camera_800B77E8.field_10.vx &= 0xFFF;
            GV_NearTimePV_80026BC4(&GM_Camera_800B77E8.field_10.vx, &s12c_dword_800DAA50.vx, temp_a2, 3);
        }
        GM_Camera_800B77E8.field_28 = 1;
        if (--s12c_dword_800DAA58 < 0)
        {
            s12c_dword_800DAA5C = 1;
        }
    }
}

void s12c_findtrap_800D7908()
{
    int temp_a3;

    temp_a3 = s12c_dword_800DAA58;
    if (s12c_dword_800DAA58 < 0x10)
    {
        s12c_dword_800DAA58--;
        GM_Camera_800B77E8.field_10.vy &= 0xFFF;
        GM_Camera_800B77E8.field_10.vx &= 0xFFF;
        GV_NearTimePV_80026BC4(&GM_Camera_800B77E8.field_10.vx, &gUnkCameraStruct_800B77B8.field_28.vx, temp_a3, 3);
    }
    GM_PlayerControl_800AB9F4->field_8_rot = s12c_dword_800DAA68;
    GM_Camera_800B77E8.field_28 = 1;
    if (--s12c_dword_800DAA58 < 0)
    {
        s12c_dword_800DAA5C = 0;
        GM_GameStatus_800AB3CC &= 0xBFFFFFFF;
        GM_Camera_800B77E8.field_18_flags &= ~0x200;
        GM_SetCameraCallbackFunc_8002FD84(0, 0);
        GV_PadData_800B05C0[0] = s12c_dword_800DAA70[0];
        GV_PadData_800B05C0[1] = s12c_dword_800DAA70[1];
        GM_Camera_800B77E8.field_18_flags |= s12c_dword_800DAA90;
        GM_Camera_800B77E8.field_74_funcs[0] = s12c_dword_800DAA94;
    }
}
