#include "vr2.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

#include "mgstype.h"
#include "libgv/libgv.h"
#include "libdg/libdg.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "menu/menuman.h"
#include "linkvar.h"
#include "strcode.h"
#include "koba/vr/vr.h"

/*---------------------------------------------------------------------------*/
// VR-DISC "VR2": mission manager of the ADVANCED VR missions (vab_* overlays). A sibling of vr.c: the pause/message
// handling, the end sequence and the equipment reset are the same code, the HUD (time limit, score) and the
// mission logic are different (the mission is cleared by reaching the target count when the time is up).

// enemy/command.c
extern int bikkuri_flag;

// koba/vr/vrover.c
extern int   GM_VrGameOverVox;
extern void *NewVrOver(int exit_only, char *retry_var);

extern MenuWork Work;

/*---------------------------------------------------------------------------*/

#define VR_SE_LIMIT_COUNT   185     // last seconds of the time limit
#define VR_SE_TARGET        180
#define VR_SE_DEAD          26

#define TIME_FPS            30      // the mission time counts frames

#define WEAPON_NONE         -1
#define ITEM_NONE           -1

#define STANCE_GROUND       2

#define HASH_MOTION2        0xBE0A  // motion message of the VR2 missions
#define HASH_VR_START       0xB247
#define HASH_VR_4           0xEC10

#define DEAD_TIME           90

typedef struct _Vr2Work
{
    GV_ACT    actor;
    int       name;             // 0x20
    short     time;             // 0x24: frames left
    short     limit;            // 0x26: time limit (0: no time limit, no HUD)
    int       end_proc;         // 0x28
    int       proc;             // 0x2C
    TILE      back[2];          // 0x30
    TILE      frame[4][2];      // 0x50
    DR_TPAGE  tpage[2];         // 0xD0
    int       gameover_vox;     // 0xE0
    u_short   dir;              // 0xE4
    char      pad_E6[2];
    char     *time_var;         // 0xE8
    u_char    n_targets;        // 0xEC
    char      pad_ED[3];
    int       score;            // 0xF0
    short     f_F4;             // 0xF4
    short     last_score;       // 0xF6
    u_short   dead_timer;       // 0xF8
    u_short   motion;           // 0xFA
} Vr2Work;                      // 0xFC

/*---------------------------------------------------------------------------*/

static void KillMissiles(void)
{
    GV_MSG msg;

    msg.address = GV_StrCode("nikita");
    msg.message[0] = GV_StrCode("kill");
    msg.message_len = 1;
    GV_SendMessage(&msg);

    msg.address = GV_StrCode("stinger");
    msg.message[0] = GV_StrCode("kill");
    msg.message_len = 1;
    GV_SendMessage(&msg);
}

static void SetSnakeMotion(void)
{
    GV_MSG msg;

    msg.address = GV_StrCode("スネーク");
    msg.message[0] = HASH_MOTION2;
    if (GM_PlayerStance == STANCE_GROUND)
    {
        msg.message[1] = 4;
    }
    else
    {
        msg.message[1] = 3;
    }

    msg.message[2] = 0xFFFF;
    msg.message[3] = 0xFFFF;
    msg.message[4] = 0xFFFF;
    msg.message_len = 5;
    GV_SendMessage(&msg);
}

static void ResetEquip(void)
{
    if (GM_Weapon == WEAPON_NONE)
    {
        Work.field_1F0_menu_weapon.field_11 = WEAPON_NONE;
        MENU_ResetWeaponPos();
    }

    if (GM_Item == ITEM_NONE)
    {
        Work.field_1DC_menu_item.field_11 = ITEM_NONE;
        MENU_ResetItemPos();
    }
}

static void Itoa2(int value, char *str)
{
    str[2] = '\0';
    str[1] = value % 10 + '0';
    str[0] = (value / 10) % 10 + '0';
}

static void DrawTime(int time, char *label, int x, int y, Vr2Work *work, int show)
{
    char s_csec[8];
    char s_sec[8];
    char s_min[8];
    int  csec, sec, min;

    csec = ((time % TIME_FPS) * 100) / TIME_FPS;
    sec = (time / TIME_FPS) % 60;
    min = (time / TIME_FPS) / 60;

    Itoa2(csec, s_csec);
    Itoa2(sec, s_sec);
    Itoa2(min, s_min);

    MENU_Locate(x, y, 0);
    MENU_Printf("%s", label);

    MENU_Locate(x, y + 6, 0);
    MENU_Printf("%s:%s:%s", s_min, s_sec, s_csec);
}

static void DrawScore(int score, char *label, int x, int y, Vr2Work *work, int show)
{
    char str[4];

    str[3] = '\0';
    str[2] = work->score % 10 + '0';
    str[1] = (work->score / 10) % 10 + '0';
    str[0] = (work->score / 100) % 10 + '0';

    MENU_Locate(x, y, 0);
    MENU_Printf("score");

    MENU_Locate(x + 44, y + 6, 1);

    if (work->last_score < work->score)
    {
        MENU_Color(255, 255, 0);
        GM_SeSet2(64, 80, VR_SE_TARGET);
    }

    MENU_Printf("%s", str);

    work->last_score = work->score;
    MENU_Color(148, 148, 148);
}

static void CheckEnd(Vr2Work *work)
{
    int   timer;
    int   exit_only;
    char *retry_var;

    timer = vr_end_timer;

    if (timer == 0)
    {
        return;
    }

    if (timer > 0)
    {
        if (timer == 1)
        {
            if (GM_StreamStatus() == -1)
            {
                exit_only = 0;
                if (VR_Flags & VRFLAG_NO_NEXT)
                {
                    // FIXME: set and reset exit_only to steer the delay slots
                    exit_only = 1;
                    if (work->time != work->limit)
                    {
                        exit_only = 0;
                        retry_var = work->time_var;
                    }
                    else
                    {
                        retry_var = NULL;
                    }
                }
                else
                {
                    retry_var = NULL;
                }

                if (NewVrOver(exit_only, retry_var))
                {
                    vr_end_timer = -1;
                }
                else
                {
                    GV_DestroyActorSystem(GV_ACTOR_PREV);
                }
            }
            else if (GM_StreamStatus() == timer)
            {
                GM_StreamPlayStop();
            }
        }
        else
        {
            vr_end_timer = timer - 1;
        }
    }
}

static void Finish(Vr2Work *work)
{
    if (vr_end_timer == 0)
    {
        VR_Status = VR_STATUS_END;

        if (VR_Flags & VRFLAG_NO_NEXT)
        {
            GCL_SetVar(work->time_var, work->time);
        }

        vr_end_timer = 4;
        GM_CallSystemCallbackProc(0, 0);
        GM_GameStatus |= STATE_MENU_DISABLE | STATE_PAUSE_OFF | STATE_RADIO_OFF;
    }
}

static void GameOver(Vr2Work *work)
{
    if (VR_Status != VR_STATUS_END)
    {
        bikkuri_flag = 0;
        VR_Status = VR_STATUS_END;
        GM_GameOverTimer = 0;
        Finish(work);
    }
}

static void CalcResult(Vr2Work *work)
{
    GCL_ARGS args;
    long     argv[4];
    int      i;

    GM_PlayerControl->turn.vy = work->dir;

    i = 2;
    if (abs(VR_Records[2]) >= work->score)
    {
        i = 3;
    }
    else
    {
        // FIXME: a goto loop (no loop optimization: the address of VR_Records is not hoisted)
next:
        if (i != 0)
        {
            VR_Records[i] = VR_Records[i - 1];
            i--;

            if (abs(VR_Records[i]) < work->score)
            {
                goto next;
            }

            i++;
        }
    }

    if (i >= 0 && i < 3) // FIXME: i >= 0 for an unsigned compare
    {
        VR_Records[i] = work->score;
    }

    args.argc = 4;
    args.argv = argv;
    argv[0] = work->score;
    argv[1] = VR_Records[0];
    argv[2] = VR_Records[1];
    argv[3] = VR_Records[2];
    VR_Records[3] = work->score;
    VR_Flags |= i << 1;
    GCL_ExecProc(work->end_proc, &args);
}

static void CheckMessages(Vr2Work *work)
{
    GV_MSG *msg;
    int     n_msgs;

    n_msgs = GV_ReceiveMessage(work->name, &msg);
    for (; n_msgs > 0; n_msgs--, msg++)
    {
        if (msg->message[0] == HASH_VR_START)
        {
            VR_Status = VR_STATUS_PLAY;
        }

        if (msg->message[0] == HASH_VR_4)
        {
            VR_Status = 3;
        }

        if (msg->message[0] == GV_StrCode("plus") && VR_Status == VR_STATUS_PLAY)
        {
            VR_TargetCount++;
        }

        if (msg->message[0] == GV_StrCode("itemset"))
        {
            ResetEquip();
        }
    }
}

static void Act(Vr2Work *work)
{
    int i;

    CheckMessages(work);

    if (VR_Status == VR_STATUS_PLAY)
    {
        work->score = VR_TargetCount;
    }

    if (work->limit)
    {
        if (VR_Status == VR_STATUS_PLAY || VR_Status == VR_STATUS_CLEAR || VR_Status == VR_STATUS_END)
        {
            MENU_Color(148, 148, 148);
            DrawScore(work->score, "score", 138, 188, work, 0);

            if (work->time / TIME_FPS < 10)
            {
                if (work->time % TIME_FPS == TIME_FPS - 1 && VR_Status == VR_STATUS_PLAY)
                {
                    GM_SeSet2(0, 63, VR_SE_LIMIT_COUNT);
                }

                if (work->time % TIME_FPS >= 15)
                {
                    MENU_Color(148, 48, 48);
                }
            }

            DrawTime(work->time, "time", 138, 200, work, 1);

            addPrim(DG_ChanlOTag(1), &work->back[GV_Clock]);

            for (i = 0; i < 4; i++)
            {
                addPrim(DG_ChanlOTag(1), &work->frame[i][GV_Clock]);
            }

            addPrim(DG_ChanlOTag(1), &work->tpage[GV_Clock]);
        }
    }

    if (work->motion)
    {
        SetSnakeMotion();
        SetSnakeMotion();
        SetSnakeMotion();
        work->motion = 0;
    }

    if (VR_Status == VR_STATUS_PLAY && work->limit)
    {
        if (work->time > 0)
        {
            work->time--;

            if (work->time == 2 && GM_Vitality > 0)
            {
                GM_GameStatus |= STATE_PADRELEASE;
                SetSnakeMotion();
                KillMissiles();
            }
        }
        else if (work->time == 0)
        {
            if (GM_Vitality > 0)
            {
                if (VR_TargetCount >= work->n_targets)
                {
                    CalcResult(work);
                    VR_Status = VR_STATUS_CLEAR;

                    if (GM_PlayerStance != STANCE_GROUND)
                    {
                        SetSnakeMotion();
                        SetSnakeMotion();
                        SetSnakeMotion();
                        work->motion = 1;
                    }
                }
                else
                {
                    GM_VrGameOverVox = work->gameover_vox;
                    GameOver(work);
                }
            }
        }
    }

    if (GM_Vitality <= 0)
    {
        if (work->dead_timer == 0)
        {
            GM_SeSet2(0, 63, VR_SE_DEAD);
        }

        if (work->dead_timer < DEAD_TIME)
        {
            work->dead_timer++;
        }

        GM_GameOverTimer = 0;
        VR_Status = VR_STATUS_END;
        GM_GameStatus |= STATE_PADRELEASE;

        if (work->dead_timer == DEAD_TIME)
        {
            bikkuri_flag = 0;
            Finish(work);
        }
    }

    CheckEnd(work);
}

static void Die(Vr2Work *work)
{
}

static void InitBack(TILE *tile)
{
    setTile(tile);
    setRGB0(tile, 0, 32, 32);
    tile->x0 = 135;
    tile->y0 = 185;
    tile->w = 50;
    tile->h = 29;
    setSemiTrans(tile, 1);
}

static void InitFrame(Vr2Work *work)
{
    int i, j;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 2; j++)
        {
            setTile(&work->frame[i][j]);
            setRGB0(&work->frame[i][j], 0, 0, 0);
            setSemiTrans(&work->frame[i][j], 0);
        }
    }

    for (i = 0; i < 2; i++)
    {
        setXY0(&work->frame[0][i], 134, 184);   // top
        setWH(&work->frame[0][i], 52, 1);

        setXY0(&work->frame[1][i], 185, 184);   // right
        setWH(&work->frame[1][i], 1, 31);

        setXY0(&work->frame[2][i], 134, 184);   // left
        setWH(&work->frame[2][i], 1, 31);

        setXY0(&work->frame[3][i], 134, 214);   // bottom
        setWH(&work->frame[3][i], 52, 1);
    }
}

static int GetResources(Vr2Work *work, int map, SVECTOR *pos)
{
    GM_CurrentMap = map;
    GM_VrGameOverVox = -1;

    InitBack(&work->back[0]);
    InitBack(&work->back[1]);
    InitFrame(work);

    setDrawTPage(&work->tpage[0], 1, 0, 0);
    setDrawTPage(&work->tpage[1], 1, 0, 0);

    GM_TranquilizerTimer = 0;
    Work.field_204_bars.field_6_snake_hp = GM_VitalityMax;
    return 0;
}

/*---------------------------------------------------------------------------*/

// NewVr2 does not byte-match from C (only the delay slot filling around the 'a' option differs: gcc hoists the
// load of 1800 above the branch), so the original code is kept as RELOCATABLE asm (build/gen_reloc_obj.py) which
// keeps this object shareable between overlays.
#pragma INCLUDE_ASM_RELOC("source/koba/vr/reloc/vr2_0.s")

#if 0 /* NON_MATCHING best C attempt */
void *NewVr2(int name, int where)
{
    SVECTOR  pos;
    Vr2Work *work;
    char    *opt;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(Vr2Work));
    vr_end_timer = 0;

    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "vr2.c");

        VR_Flags = 0;

        opt = GCL_GetOption('d');
        if (opt)
        {
            work->dir = GCL_StrToInt(opt);
        }

        opt = GCL_GetOption('s');
        if (opt)
        {
            VR_Flags |= VRFLAG_AMMO_BONUS;
            VR_Flags |= GCL_StrToInt(opt) << 8;
            work->proc = GCL_StrToInt(GCL_NextStr());
        }
        else
        {
            work->proc = 0;
        }

        opt = GCL_GetOption('e');
        if (!opt)
        {
            printf("Please Set ENDPROC!\n");
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->end_proc = GCL_StrToInt(opt);

        opt = GCL_GetOption('a');
        if (!opt)
        {
            work->time = 1800;
            work->limit = 0;
        }
        else
        {
            work->time = work->limit = GCL_StrToInt(opt);
        }

        VR_Status = VR_STATUS_0;

        opt = GCL_GetOption('r');
        if (opt)
        {
            VR_Records[0] = GCL_StrToInt(opt);
            VR_Records[1] = GCL_StrToInt(GCL_NextStr());
            VR_Records[2] = GCL_StrToInt(GCL_NextStr());
            VR_Flags |= VRFLAG_RESULT;
        }

        if (work->limit == 0)
        {
            VR_Flags &= ~VRFLAG_RESULT;
        }

        opt = GCL_GetOption('o');
        if (opt)
        {
            work->gameover_vox = GCL_StrToInt(opt);
        }
        else
        {
            work->gameover_vox = -1;
        }

        opt = GCL_GetOption('b');
        if (opt)
        {
            work->n_targets = GCL_StrToInt(opt);
        }
        else
        {
            work->n_targets = 0;
        }

        if (GetResources(work, where, &pos) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        bikkuri_flag = 0;
        work->name = name;
        VR_TargetCount = 0;
        work->dead_timer = 0;
        work->f_F4 = 0;
        work->last_score = 0;
        work->motion = 0;
    }

    return work;
}
#endif
