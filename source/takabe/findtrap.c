#include "findtrap.h"

#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "common.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "takabe/thing.h"
#include "strcode.h"

extern GM_CAMERA       GM_Camera;
extern UnkCameraStruct gUnkCameraStruct_800B77B8;
extern int             dword_8009F470;
extern DG_CHANL        DG_Chanls[3];

/*---------------------------------------------------------------------------*/

#define EXEC_LEVEL      GV_ACTOR_LEVEL5

typedef struct _Work
{
    GV_ACT  actor;
    int     map;
    int     name;
    SVECTOR pos;
    SVECTOR size;
    int     proc_id;
    int     flag;
    int     wait;
    int     field_44;   /* unused */
    int     field_48;   /* unused */
} Work;

/*---------------------------------------------------------------------------*/

static short msg_list[4] = {HASH_ENTER, HASH_LEAVE, 0x42DC, HASH_KILL};

SVECTOR       SECTION(".bss") s12c_dword_800DAA50;
int           SECTION(".bss") s12c_dword_800DAA58;
int           SECTION(".bss") s12c_dword_800DAA5C;
SVECTOR       SECTION(".bss") s12c_dword_800DAA60;
SVECTOR       SECTION(".bss") s12c_dword_800DAA68;
GV_PAD        SECTION(".bss") s12c_dword_800DAA70[2];
int           SECTION(".bss") s12c_dword_800DAA90;
TGMCameraFunc SECTION(".bss") s12c_dword_800DAA94;

/*---------------------------------------------------------------------------*/

static void FindEvent2(void);
static void FindEvent1(void);

static void Act(Work *work)
{
    int fpv_flag;

    GM_CurrentMap = work->map;

    switch (THING_Msg_CheckMessage(work->name, 4, msg_list))
    {
    case 0:
        if (work->flag == 0)
        {
            work->flag = 1;
        }
        break;
    case 1:
        work->flag = 0;
        break;
    case 2:
        work->flag = 8;
        GM_SetCameraCallbackFunc(0, FindEvent2);
        s12c_dword_800DAA58 = work->wait;
        break;
    }

    if (work->flag & 1)
    {
        if (work->flag == 1)
        {
            fpv_flag = GM_Camera.first_person;

            if (fpv_flag == work->flag && !(GM_Camera.flags & 0x100) &&
                (GV_PadData->status & PAD_TRIANGLE) && dword_8009F470 == 0)
            {
                MATRIX   eye_inv;
                SVECTOR  sxy;
                SVECTOR  svec;
                long     throwaway;
                SVECTOR *size;
                int      wait;

                eye_inv = DG_Chanl(0)->eye_inv;

                DG_AdjustOverscan(&eye_inv);
                DG_SetPos(&eye_inv);
                RotTransPers(&work->pos, (long *)&sxy, &throwaway, &throwaway);

                size = &work->size;
                if (sxy.vx < size->vx && -size->vx < sxy.vx && sxy.vy < size->vy && -size->vy < sxy.vy)
                {
                    work->pos.pad = fpv_flag;
                }
                else
                {
                    work->pos.pad = 0;
                }

                if (work->pos.pad != 0)
                {
                    work->flag |= 2;
                    GM_GameStatus |= STATE_PADDEMO;
                    GV_DemoPadStatus[0] = GV_PadData->status & PAD_TRIANGLE;
                    s12c_dword_800DAA90 = GM_Camera.flags & 0x200;
                    s12c_dword_800DAA94 = GM_Camera.callbacks[0];
                    GM_SetCameraCallbackFunc(0, FindEvent1);
                    GM_Camera.flags |= 0x200;
                    GV_SubVec3(&work->pos, &GM_Camera.eye, &svec);
                    s12c_dword_800DAA50.vz = 0;
                    s12c_dword_800DAA50.vy = GV_VecDir2(&svec) & 0xFFF;
                    s12c_dword_800DAA50.vx =
                        ratan2(-svec.vy, SquareRoot0(svec.vx * svec.vx + svec.vz * svec.vz)) & 0xFFF;
                    s12c_dword_800DAA5C = 0;
                    gUnkCameraStruct_800B77B8.rotate2.vy &= 0xFFF;
                    wait = work->wait;
                    s12c_dword_800DAA60 = gUnkCameraStruct_800B77B8.rotate2;
                    s12c_dword_800DAA68 = GM_PlayerControl->rot;
                    s12c_dword_800DAA70[0] = GV_PadData[0];
                    s12c_dword_800DAA70[1] = GV_PadData[1];
                    s12c_dword_800DAA58 = wait;
                }
            }
        }
        if ((work->flag & 2) && s12c_dword_800DAA5C != 0)
        {
            GCL_ARGS args;
            args.argc = 0;
            args.argv = NULL;
            GCL_ExecProc(work->proc_id, &args);

            work->flag &= ~2;
            work->flag |= 4;
        }
    }
}

static void Die(Work *work)
{
    GM_GameStatus &= ~STATE_PADDEMO;
    GM_Camera.flags &= ~0x200;
}

static int GetResources(Work *work, int name, int where)
{
    work->name = name;
    GM_CurrentMap = where;
    work->map = where;
    THING_Gcl_GetSVector('p', &work->pos);
    work->proc_id = THING_Gcl_GetInt('e');
    THING_Gcl_GetSVectorDefault('s', 160, 112, 0, &work->size);
    work->wait = THING_Gcl_GetInt('w');
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewFindTrap(int name, int where, int argc, char **argv)
{
    Work *work;

    work = GV_NewActor(EXEC_LEVEL, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "findtrap.c");
        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }
    return (void *)work;
}

/*---------------------------------------------------------------------------*/

static void FindEvent1(void)
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

static void FindEvent2(void)
{
    int temp_a3;

    temp_a3 = s12c_dword_800DAA58;
    if (s12c_dword_800DAA58 < 16)
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
        GM_SetCameraCallbackFunc(0, NULL);
        GV_PadData[0] = s12c_dword_800DAA70[0];
        GV_PadData[1] = s12c_dword_800DAA70[1];
        GM_Camera.flags |= s12c_dword_800DAA90;
        GM_Camera.callbacks[0] = s12c_dword_800DAA94;
    }
}
