#include "findtrap.h"

#include "common.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "game/camera.h"
#include "takabe/thing.h"
#include "strcode.h"

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

#define EXEC_LEVEL GV_ACTOR_LEVEL5

short findtrap_msgs_800C350C[4] = {HASH_ENTER, HASH_LEAVE, 0x42DC, HASH_KILL};

SVECTOR       SECTION("overlay.bss") s12c_dword_800DAA50;
int           SECTION("overlay.bss") s12c_dword_800DAA58;
int           SECTION("overlay.bss") s12c_dword_800DAA5C;
SVECTOR       SECTION("overlay.bss") s12c_dword_800DAA60;
SVECTOR       SECTION("overlay.bss") s12c_dword_800DAA68;
GV_PAD        SECTION("overlay.bss") s12c_dword_800DAA70[2];
int           SECTION("overlay.bss") s12c_dword_800DAA90;
TGMCameraFunc SECTION("overlay.bss") s12c_dword_800DAA94;

extern GM_CAMERA       GM_Camera;
extern UnkCameraStruct gUnkCameraStruct_800B77B8;
extern int             dword_8009F470;
extern DG_CHANL        DG_Chanls_800B1800[3];

void FindTrap_callback1_800D7908();
void FindTrap_callback2_800D7870();

void s12c_findtrap_800D72E8(FindTrapWork *work)
{
    int field_22;

    GM_CurrentMap = work->field_20;
    switch (THING_Msg_CheckMessage(work->field_24, 4, findtrap_msgs_800C350C))
    {
    case 0:
        if (work->field_3C == 0)
        {
            work->field_3C = 1;
        }
        break;
    case 1:
        work->field_3C = 0;
        break;
    case 2:
        work->field_3C = 8;
        GM_SetCameraCallbackFunc_8002FD84(0, FindTrap_callback1_800D7908);
        s12c_dword_800DAA58 = work->field_40;
        break;
    }

    if (work->field_3C & 1)
    {
        if (work->field_3C == 1)
        {
            field_22 = GM_Camera.first_person;

            if (field_22 == work->field_3C && !(GM_Camera.flags & 0x100) &&
                (GV_PadData->status & PAD_TRIANGLE) && dword_8009F470 == 0)
            {
                MATRIX   eye_inv;
                SVECTOR  sxy;
                SVECTOR  svec;
                long     throwaway;
                SVECTOR *field_30;
                int      field_40;

                eye_inv = DG_Chanl(0)->field_10_eye_inv;

                DG_AdjustOverscan(&eye_inv);
                DG_SetPos(&eye_inv);
                RotTransPers(&work->field_28, (long *)&sxy, &throwaway, &throwaway);

                field_30 = &work->field_30;
                if (sxy.vx < field_30->vx && -field_30->vx < sxy.vx && sxy.vy < field_30->vy && -field_30->vy < sxy.vy)
                {
                    work->field_28.pad = field_22;
                }
                else
                {
                    work->field_28.pad = 0;
                }

                if (work->field_28.pad != 0)
                {
                    work->field_3C |= 2;
                    GM_GameStatus |= STATE_PADDEMO;
                    GV_DemoPadStatus[0] = GV_PadData->status & PAD_TRIANGLE;
                    s12c_dword_800DAA90 = GM_Camera.flags & 0x200;
                    s12c_dword_800DAA94 = GM_Camera.callbacks[0];
                    GM_SetCameraCallbackFunc_8002FD84(0, FindTrap_callback2_800D7870);
                    GM_Camera.flags |= 0x200;
                    GV_SubVec3(&work->field_28, &GM_Camera.eye, &svec);
                    s12c_dword_800DAA50.vz = 0;
                    s12c_dword_800DAA50.vy = GV_VecDir2(&svec) & 0xFFF;
                    s12c_dword_800DAA50.vx =
                        ratan2(-svec.vy, SquareRoot0(svec.vx * svec.vx + svec.vz * svec.vz)) & 0xFFF;
                    s12c_dword_800DAA5C = 0;
                    gUnkCameraStruct_800B77B8.rotate2.vy &= 0xFFF;
                    field_40 = work->field_40;
                    s12c_dword_800DAA60 = gUnkCameraStruct_800B77B8.rotate2;
                    s12c_dword_800DAA68 = GM_PlayerControl->rot;
                    s12c_dword_800DAA70[0] = GV_PadData[0];
                    s12c_dword_800DAA70[1] = GV_PadData[1];
                    s12c_dword_800DAA58 = field_40;
                }
            }
        }
        if ((work->field_3C & 2) && s12c_dword_800DAA5C != 0)
        {
            GCL_ARGS args;
            args.argc = 0;
            args.argv = NULL;
            GCL_ExecProc(work->field_38, &args);

            work->field_3C &= ~2;
            work->field_3C |= 4;
        }
    }
}

void FindTrapDie_800D7734(FindTrapWork *work)
{
    GM_GameStatus &= ~STATE_PADDEMO;
    GM_Camera.flags &= ~0x200;
}

int FindTrapGetResources_800D7768(FindTrapWork *work, int name, int where)
{
    work->field_24 = name;
    GM_CurrentMap = where;
    work->field_20 = where;
    THING_Gcl_GetSVector('p', &work->field_28);
    work->field_38 = THING_Gcl_GetInt('e');
    THING_Gcl_GetSVectorDefault('s', 160, 112, 0, &work->field_30);
    work->field_40 = THING_Gcl_GetInt('w');
    return 0;
}

void *NewFindTrap_800D77DC(int name, int where, int argc, char **argv)
{
    FindTrapWork *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(FindTrapWork));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, s12c_findtrap_800D72E8, FindTrapDie_800D7734, "findtrap.c");
        if (FindTrapGetResources_800D7768(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}

void FindTrap_callback2_800D7870()
{
    int temp_a2;

    temp_a2 = s12c_dword_800DAA58;
    if (s12c_dword_800DAA58 >= 0)
    {
        if (s12c_dword_800DAA58 < 16)
        {
            s12c_dword_800DAA58--;
            GM_Camera.rotate.vy &= 0xFFF;
            GM_Camera.rotate.vx &= 0xFFF;
            GV_NearTimePV(&GM_Camera.rotate.vx, &s12c_dword_800DAA50.vx, temp_a2, 3);
        }
        GM_Camera.field_28 = 1;
        if (--s12c_dword_800DAA58 < 0)
        {
            s12c_dword_800DAA5C = 1;
        }
    }
}

void FindTrap_callback1_800D7908()
{
    int temp_a3;

    temp_a3 = s12c_dword_800DAA58;
    if (s12c_dword_800DAA58 < 0x10)
    {
        s12c_dword_800DAA58--;
        GM_Camera.rotate.vy &= 0xFFF;
        GM_Camera.rotate.vx &= 0xFFF;
        GV_NearTimePV(&GM_Camera.rotate.vx, &gUnkCameraStruct_800B77B8.rotate2.vx, temp_a3, 3);
    }
    GM_PlayerControl->rot = s12c_dword_800DAA68;
    GM_Camera.field_28 = 1;
    if (--s12c_dword_800DAA58 < 0)
    {
        s12c_dword_800DAA5C = 0;
        GM_GameStatus &= ~STATE_PADDEMO;
        GM_Camera.flags &= ~0x200;
        GM_SetCameraCallbackFunc_8002FD84(0, 0);
        GV_PadData[0] = s12c_dword_800DAA70[0];
        GV_PadData[1] = s12c_dword_800DAA70[1];
        GM_Camera.flags |= s12c_dword_800DAA90;
        GM_Camera.callbacks[0] = s12c_dword_800DAA94;
    }
}
