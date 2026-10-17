#define VR_DEFINES_DATA
#include "vr.h"

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

/*---------------------------------------------------------------------------*/
// VR-DISC training mission manager: time limit, targets, goal, results

// enemy/command.c
extern int     bikkuri_flag;
extern SVECTOR bikkuri_pos;

// koba/vr/vrover.c
extern int   GM_VrGameOverVox;
extern void *NewVrOver(int exit_only, char *retry_var);

extern MenuWork Work;

/*---------------------------------------------------------------------------*/

#define VR_SE_LIMIT_COUNT   185     // last seconds of the time limit
#define VR_SE_TIME_UP       186
#define VR_SE_TARGET        180

#define TIME_FPS            30      // the mission time counts frames

#define WEAPON_NONE         -1
#define ITEM_NONE           -1

#define STANCE_GROUND       2

#define BIKKURI_FOUND       0x0001  // the player has been spotted
#define BIKKURI_ALERT       0x0002
#define BIKKURI_NO_GOAL     0x0100
#define BIKKURI_GOAL_OVER   0x0200
#define BIKKURI_LOOK        0x1000
#define BIKKURI_GAMEOVER    0x80000000

#define HASH_RECORD_END     0x32A1  // GV_StrCode("記録終了")
#define HASH_PAUSE          0x3041  // GV_StrCode("一時停止")
#define HASH_RESUME         0x2F6B  // GV_StrCode("再開")
#define HASH_VR_START       0xB247
#define HASH_VR_4           0xEC10
#define HASH_CHANGE         0x11F8  // GV_StrCode("change")
#define HASH_GOAL           0x48C1  // GV_StrCode("goal")

#define DEAD_TIME           90

// VrWork.mode
enum {
    VR_MODE_NORMAL = 0,
    VR_MODE_TARGET = 1,     // shoot 'b' targets or collect 'c' items
    VR_MODE_SNEAKING = 2,   // bonus for not being spotted
    VR_MODE_3 = 3,
    VR_MODE_4 = 4,
    VR_MODE_5 = 5,
};

typedef struct _VrWork
{
    GV_ACT    actor;
    int       name;             // 0x20
    SVECTOR   goal;             // 0x24
    SVECTOR   goal2;            // 0x2C: goal after the "change" message
    short     time;             // 0x34
    short     limit;            // 0x36
    int       end_proc;         // 0x38
    int       proc;             // 0x3C
    short     dir;              // 0x40
    short     angle;            // 0x42
    char      timed;            // 0x44
    u_char    countdown;        // 0x45
    char     *time_var;         // 0x48
    char      goal_end;         // 0x4C
    TILE      back[2];          // 0x50
    TILE      frame[4][2];      // 0x70
    DR_TPAGE  tpage[2];         // 0xF0
    int       gameover_vox;     // 0x100
    u_char    dead_timer;       // 0x104
    u_char    n_items;          // 0x105
    u_char    n_targets;        // 0x106
    u_char    target_timer;     // 0x107
    u_char    started;          // 0x108
    u_char    f109;             // 0x109
    u_char    mode;             // 0x10A
    u_char    step;             // 0x10B
    int       f10C;             // 0x10C
    int       last_count;       // 0x110
    int       bonus;            // 0x114: frames taken off the time
    u_int     paused : 1;       // 0x118
    u_int     stop : 1;
    u_int     remove_items : 1;
    u_int     result : 1;
} VrWork;

/*---------------------------------------------------------------------------*/

int vr_end_timer = 0;

int     SECTION(".bss") VR_FoundCount;
int     SECTION(".bss") VR_TargetCount;
int     SECTION(".bss") VR_Flags;
int     SECTION(".bss") VR_Unused;
int     SECTION(".bss") VR_Records[4];
int     SECTION(".bss") VR_Status;

/*---------------------------------------------------------------------------*/

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

static void StartClear(VrWork *work)
{
    GM_GameStatus |= STATE_PADRELEASE;

    if (work->step == 0)
    {
        work->step++;
    }
}

static void StopDemo(void)
{
    GV_MSG msg;

    msg.address = GV_StrCode("demo");
    msg.message[0] = HASH_RECORD_END;
    msg.message_len = 1;
    GV_SendMessage(&msg);
}

static void SetSnakeMotion(void)
{
    GV_MSG msg;

    msg.address = GV_StrCode("スネーク");
    msg.message[0] = HASH_MOTION;
    if (GM_PlayerStance == STANCE_GROUND)
    {
        msg.message[1] = 4;
    }
    else
    {
        msg.message[1] = 3;
    }

    if (VR_FoundCount == 3)
    {
        msg.message[1] = 2;
    }

    msg.message[2] = 0xFFFF;
    msg.message[3] = 0xFFFF;
    msg.message[4] = 0xFFFF;
    msg.message_len = 5;
    GV_SendMessage(&msg);
}

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

static int InRange(int value, int min, int max)
{
    return (u_int)(value - min) <= (u_int)(max - min);
}

static int CheckGoal(SVECTOR *pos, SVECTOR *goal)
{
    if (GM_PlayerStatus & (PLAYER_NOT_PLAYABLE | PLAYER_DAMAGED | PLAYER_DOWNED))
    {
        return 0;
    }

    if (GM_Vitality <= 0)
    {
        return 0;
    }

    if (VR_Status == VR_STATUS_END)
    {
        return 0;
    }

    if (GM_GameStatus & STATE_GAME_OVER)
    {
        return 0;
    }

    if (GM_PlayerStatus & PLAYER_GAME_OVER)
    {
        return 0;
    }

    if (InRange(pos->vx, goal->vx - 500, goal->vx + 500) &&
        InRange(pos->vz, goal->vz - 500, goal->vz + 500) &&
        InRange(pos->vy, goal->vy - 1000, goal->vy + 1000))
    {
        return 1;
    }

    return 0;
}

// not static: referenced by the relocatable asm of VrDrawTime
void VrItoa2(int value, char *str)
{
    str[2] = '\0';
    str[1] = value % 10 + '0';
    str[0] = (value / 10) % 10 + '0';
}

// DrawTime does not byte-match from C (7 words differ: register of `jitter`, the operand order of one
// mult and one delay slot), so the original code lives in source/koba/vr/reloc/VrDrawTime.s as RELOCATABLE asm
// (symbolic, generated by build/symbolize_asm.py) which keeps this object shareable between overlays.
void VrDrawTime(int time, char *label, int x, int y, VrWork *work, int show);
#pragma INCLUDE_ASM_RELOC("source/koba/vr/reloc/VrDrawTime.s")

#if 0 /* NON_MATCHING: best C attempt */
// FIXME: `t` is a second copy of `time` (assigned on both paths) so that gcc
// computes t / 30 and time / 30 separately like the original
static void VrDrawTime(int time, char *label, int x, int y, VrWork *work, int show)
{
    char   s_csec[8];
    char   s_sec[8];
    char   s_min[8];
    int    t;
    int    csec, sec, min;
    u_char digit;
    int    noise;
    u_char jitter;

    show = show && (VR_Flags & VRFLAG_RESULT);

    if (VR_Status == VR_STATUS_CLEAR && show && work->result)
    {
        time = VR_Records[3];
        t = VR_Records[3];
    }
    else
    {
        t = time;
    }

    csec = ((time % TIME_FPS) * 100) / TIME_FPS;
    digit = (((t % TIME_FPS) * 100) / TIME_FPS) % 10;
    noise = ((t % TIME_FPS) / 3) * (t / TIME_FPS + digit * 29);
    noise = (u_char)noise >> 1;
    time /= TIME_FPS;
    sec = time % 60;
    min = time / 60;

    if (digit == 6)
    {
        jitter = noise & 3;
    }
    else
    {
        jitter = (u_char)noise % 3;
    }

    csec += jitter;

    if (VR_Status == VR_STATUS_CLEAR && work->bonus != 0 && show)
    {
        csec += ((work->bonus % TIME_FPS) * 100) / TIME_FPS;
        sec += csec / 100;
        sec += work->bonus / TIME_FPS;
        csec %= 100;
        min += sec / 60;
        sec %= 60;
    }

    VrItoa2(csec, s_csec);
    VrItoa2(sec, s_sec);
    VrItoa2(min, s_min);

    MENU_Locate(x, y, 0);
    MENU_Printf("%s", label);

    MENU_Locate(x, y + 6, 0);
    MENU_Printf("%s:%s:%s", s_min, s_sec, s_csec);
}

#endif

static void DrawTargets(int x, int y, VrWork *work)
{
    int i;
    int c;

    for (i = 0; i < 2; i++)
    {
        c = 200 - i * 150;
        MENU_Color(c, c, c);

        MENU_Locate(x + i, y + i, 0x12);
        MENU_Printf("TARGET");

        MENU_Locate(x + i, y + 8 + i, 0x12);

        if (VR_TargetCount > work->last_count)
        {
            MENU_Color(255, 255, 0);
            GM_SeSet2(64, 80, VR_SE_TARGET);
        }

        MENU_Printf("%d/%d", VR_TargetCount, work->n_targets);
    }

    work->last_count = VR_TargetCount;
}

static void CheckEnd(VrWork *work)
{
    GV_ACTFUNC act;
    int        exit_only;
    char      *retry_var;

    if (vr_end_timer == 0)
    {
        return;
    }

    if (vr_end_timer > 0)
    {
        if (vr_end_timer == 1)
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
                    act = work->actor.act;
                    GV_DestroyActorSystem(GV_ACTOR_PREV);
                    work->actor.act = act;
                }
            }
            else if (GM_StreamStatus() == 1)
            {
                GM_StreamPlayStop();
            }
        }
        else
        {
            vr_end_timer--;
        }
    }
}

static void Finish(VrWork *work)
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

static void CalcResult(VrWork *work)
{
    GCL_ARGS args;
    long     argv[4];
    char     weights[10] = { 10, 1, 10, 10, 10, 30, 10, 10, 10, 10 };
    int      time;
    int      i;
    int      penalty;

    GM_PlayerControl->turn.vy = work->dir;
    time = work->time;

    // remaining ammo of the first weapon in the inventory
    // FIXME: linkvarbuf[17 + i] instead of GM_Weapons[i] to match the indexing
    i = 0;
    while (linkvarbuf[17 + i] < 0 && i < 11)
    {
        i++;
    }

    if (work->mode == VR_MODE_5)
    {
        VR_Flags |= VRFLAG_AMMO_BONUS;
    }

    if (work->mode == VR_MODE_4)
    {
        VR_Flags &= ~VRFLAG_AMMO_BONUS;
    }
    else if (i < 10)
    {
        penalty = linkvarbuf[17 + i] * weights[i];
        time -= penalty;
        work->bonus += penalty;
    }

    if (work->mode == VR_MODE_SNEAKING)
    {
        switch (VR_FoundCount)
        {
        case 0:
            time -= 90;
            work->bonus += 90;
            break;

        case 1:
            time -= 30;
            work->bonus += 30;
            break;
        }
    }

    if (time < 0)
    {
        time = 0;
    }

    i = 2;
    if (time >= abs(VR_Records[2]))
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

            if (time < abs(VR_Records[i]))
            {
                goto next;
            }

            i++;
        }
    }

    if (i >= 0 && i < 3) // FIXME: i >= 0 for an unsigned compare
    {
        VR_Records[i] = time;
    }

    args.argc = 4;
    args.argv = argv;
    VR_Flags |= i << 1;
    argv[0] = work->time;
    VR_Records[3] = time;
    argv[1] = VR_Records[0];
    argv[2] = VR_Records[1];
    argv[3] = VR_Records[2];

    work->result = 1;

    if (work->end_proc)
    {
        StopDemo();
        GCL_ExecProc(work->end_proc, &args);
    }

    work->end_proc = 0;
    work->started = 0;
}

static void ClearSequence(VrWork *work)
{
    switch (work->step)
    {
    case 0:
        return;

    case 1:
        if (work->remove_items)
        {
            if (GM_Item != ITEM_NONE)
            {
                GM_Item = ITEM_NONE;
            }

            if (GM_Weapon != WEAPON_NONE)
            {
                GM_Weapon = WEAPON_NONE;
            }
        }

        KillMissiles();
        break;

    case 2:
        work->step++;

        if (GM_Vitality > 0 && VR_Status != VR_STATUS_END)
        {
            SetSnakeMotion();
        }
        return;

    case 3:
        if (GM_Vitality > 0 && VR_Status != VR_STATUS_END)
        {
            if (GM_PlayerStance != STANCE_GROUND)
            {
                SetSnakeMotion();
            }

            CalcResult(work);
        }
        break;

    case 4:
    case 5:
    case 6:
    case 7:
        if (GM_Vitality > 0 && VR_Status != VR_STATUS_END && GM_PlayerStance != STANCE_GROUND)
        {
            SetSnakeMotion();
        }
        break;

    default:
        return;
    }

    work->step++;
}

static void GameOver(VrWork *work)
{
    if (VR_Status != VR_STATUS_END)
    {
        VR_Status = VR_STATUS_END;
        GM_GameOverTimer = 0;
        GM_GameStatus |= STATE_PADRELEASE;
        Finish(work);
        StopDemo();
    }
}

static void DeadWait(VrWork *work)
{
    if (work->dead_timer < DEAD_TIME)
    {
        if (work->dead_timer == 1)
        {
            GM_GameStatus |= STATE_PADRELEASE;
        }

        work->dead_timer++;

        if (VR_Status != VR_STATUS_END)
        {
            GM_GameOverTimer = 0;
        }
    }

    if (work->dead_timer == DEAD_TIME)
    {
        bikkuri_flag = 0;
        GameOver(work);
        work->dead_timer++;
    }
}

static void CheckMessages(VrWork *work)
{
    GV_MSG *msg;
    int     n_msgs;

    if (bikkuri_flag & BIKKURI_GAMEOVER)
    {
        bikkuri_flag &= ~BIKKURI_GAMEOVER;

        if (VR_Status == VR_STATUS_PLAY)
        {
            GameOver(work);
        }
    }

    n_msgs = GV_ReceiveMessage(work->name, &msg);
    for (; n_msgs > 0; n_msgs--, msg++)
    {
        if (msg->message[0] == HASH_PAUSE)
        {
            work->paused = 1;
        }

        if (msg->message[0] == HASH_RESUME)
        {
            work->paused = 0;
        }

        if (msg->message[0] == HASH_VR_START)
        {
            VR_Status = VR_STATUS_PLAY;
            work->started = 1;
        }

        if (msg->message[0] == HASH_VR_4)
        {
            VR_Status = VR_STATUS_4;
        }

        if (msg->message[0] == GV_StrCode("plus") && VR_Status == VR_STATUS_PLAY)
        {
            VR_TargetCount++;
        }

        if (msg->message[0] == HASH_CHANGE)
        {
            work->goal = work->goal2;
        }

        if (msg->message[0] == HASH_GOAL)
        {
            if (work->proc)
            {
                GCL_ExecProc(work->proc, NULL);
                work->proc = 0;
            }
        }

        if (msg->message[0] == GV_StrCode("vrover") && VR_Status == VR_STATUS_PLAY)
        {
            bikkuri_flag = 0;
            GameOver(work);
            GM_VrGameOverVox = -1;
        }

        if (msg->message[0] == GV_StrCode("voiceover") && VR_Status == VR_STATUS_PLAY)
        {
            bikkuri_flag = 0;
            GameOver(work);
            GM_VrGameOverVox = work->gameover_vox;
        }

        if (msg->message[0] == GV_StrCode("clear") && VR_Status == VR_STATUS_PLAY)
        {
            StartClear(work);
            VR_Status = VR_STATUS_CLEAR;
        }

        if (msg->message[0] == GV_StrCode("itemset"))
        {
            ResetEquip();
        }
    }
}

static void Act(VrWork *work)
{
    SVECTOR diff;
    int     left;
    int     i;

    MENU_Color(200, 200, 200);

    if (!work->paused)
    {
        if (work->n_targets && !work->n_items && work->started && work->proc)
        {
            DrawTargets(270, 75, work);
        }

        if (work->timed && (VR_Status == VR_STATUS_PLAY || VR_Status == VR_STATUS_CLEAR || VR_Status == VR_STATUS_END))
        {
            MENU_Color(200, 200, 200);
            VrDrawTime(work->limit, "limit", 138, 188, work, 0);

            left = (work->limit - work->time) / TIME_FPS;
            if (left < 10)
            {
                if (left * TIME_FPS == (work->limit - work->time) - (TIME_FPS - 1) && VR_Status == VR_STATUS_PLAY)
                {
                    GM_SeSet2(0, 63, VR_SE_LIMIT_COUNT);
                }

                if ((work->limit - work->time) % TIME_FPS >= 14)
                {
                    MENU_Color(200, 48, 48);
                }
                else
                {
                    MENU_Color(200, 200, 200);
                }
            }

            VrDrawTime(work->time, "time", 138, 200, work, 1);
            MENU_Color(200, 200, 200);

            if (VR_Status != VR_STATUS_4)
            {
                addPrim(DG_ChanlOTag(1), &work->back[GV_Clock]);

                for (i = 0; i < 4; i++)
                {
                    addPrim(DG_ChanlOTag(1), &work->frame[i][GV_Clock]);
                }

                addPrim(DG_ChanlOTag(1), &work->tpage[GV_Clock]);
            }

            if (!work->stop && VR_Status == VR_STATUS_PLAY)
            {
                if (work->limit == ++work->time)
                {
                    GM_SeSet2(0, 63, VR_SE_TIME_UP);
                    bikkuri_flag = 0;
                    GM_VrGameOverVox = work->gameover_vox;
                    GameOver(work);
                }
            }
        }
    }

    if ((bikkuri_flag & BIKKURI_FOUND) && !work->countdown && work->goal_end && work->end_proc)
    {
        diff.vx = bikkuri_pos.vx - GM_PlayerPosition.vx;
        diff.vy = bikkuri_pos.vy - GM_PlayerPosition.vy;
        diff.vz = bikkuri_pos.vz - GM_PlayerPosition.vz;
        work->angle = ratan2(diff.vx, diff.vz);

        work->countdown = 6;
        VR_Status = VR_STATUS_END;
        work->step = 0;
        GM_GameStatus |= STATE_PADRELEASE;
        bikkuri_flag |= BIKKURI_LOOK;
    }

    if (work->mode == VR_MODE_SNEAKING && VR_FoundCount < 2 && (bikkuri_flag & BIKKURI_FOUND))
    {
        VR_FoundCount++;
        bikkuri_flag &= ~BIKKURI_FOUND;
    }

    if (work->countdown != 0)
    {
        if (--work->countdown == 0)
        {
            if (GM_PlayerStance == 0 && VR_FoundCount < 3)
            {
                GM_PlayerControl->turn.vy = work->angle;
            }

            Finish(work);
            StopDemo();
        }
    }

    if (VR_TargetCount >= work->n_targets)
    {
        if (work->target_timer == 0)
        {
            work->target_timer = 1;
        }
        else if (work->target_timer < 30)
        {
            work->target_timer++;
        }
    }

    if (VR_TargetCount > work->n_targets)
    {
        VR_TargetCount = work->n_targets;
    }

    if (VR_Status == VR_STATUS_PLAY && work->n_targets && work->proc)
    {
        if (work->target_timer >= 30)
        {
            GCL_ExecProc(work->proc, NULL);
            work->proc = 0;
        }
    }
    else if ((bikkuri_flag & BIKKURI_ALERT) && work->proc)
    {
        GCL_ExecProc(work->proc, NULL);
        work->proc = 0;
    }

    if (work->n_items)
    {
        if ((GM_PlayerStatus & PLAYER_DOWNED) && work->proc)
        {
            GM_GameStatus |= STATE_PADRELEASE;
            GameOver(work);
        }

        if (work->proc && work->n_items <= GM_LandMineFlag)
        {
            GCL_ExecProc(work->proc, NULL);
            work->proc = 0;
        }
    }

    if (VR_Status == VR_STATUS_PLAY && !work->proc)
    {
        if (CheckGoal(&GM_PlayerPosition, &work->goal))
        {
            // FIXME: the clear code is duplicated (merged again by gcc) to match
            if (work->mode == VR_MODE_3)
            {
                if (bikkuri_flag & BIKKURI_NO_GOAL)
                {
                    StartClear(work);
                    VR_Status = VR_STATUS_CLEAR;
                }
                else if (bikkuri_flag & BIKKURI_GOAL_OVER)
                {
                    GameOver(work);
                }
            }
            else
            {
                StartClear(work);
                VR_Status = VR_STATUS_CLEAR;
            }
        }
    }

    if (GM_Vitality <= 0)
    {
        work->stop = 1;
        GM_GameStatus |= STATE_PADRELEASE;
    }

    if (!work->stop)
    {
        CheckMessages(work);
        ClearSequence(work);
    }

    if (work->stop)
    {
        DeadWait(work);
    }

    CheckEnd(work);
}

static void Die(VrWork *work)
{
    if (work->time_var)
    {
        GCL_SetVar(work->time_var, work->time);
    }
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

static void InitFrame(VrWork *work)
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

static int GetResources(VrWork *work, int map, SVECTOR *pos)
{
    GM_CurrentMap = map;

    work->goal = *pos;
    work->countdown = 0;
    GM_VrGameOverVox = -1;

    InitBack(&work->back[0]);
    InitBack(&work->back[1]);
    InitFrame(work);

    setDrawTPage(&work->tpage[0], 1, 0, 0);
    setDrawTPage(&work->tpage[1], 1, 0, 0);

    GM_TranquilizerTimer = 0;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewVr(int name, int where)
{
    SVECTOR pos;
    SVECTOR goal2;
    VrWork *work;
    char   *opt;

    work = GV_NewActor(GV_ACTOR_USER, sizeof(VrWork));
    vr_end_timer = 0;

    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, Act, Die, "vr.c");

        VR_Flags = 0;
        work->proc = 0;
        work->end_proc = 0;

        opt = GCL_GetOption('p');
        if (opt)
        {
            GCL_StrToSV(opt, (short *)&pos);
        }
        else
        {
            pos = DG_ZeroVector;
        }

        opt = GCL_GetOption('h');
        if (opt)
        {
            GCL_StrToSV(opt, (short *)&goal2);
            work->goal2 = goal2;
        }
        else
        {
            goal2 = pos;
        }

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

        opt = GCL_GetOption('e');
        if (!opt)
        {
            printf("Please Set ENDPROC!\n");
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        work->end_proc = GCL_StrToInt(opt);

        opt = GCL_GetOption('a');
        if (opt)
        {
            work->timed = 1;
            work->limit = GCL_StrToInt(opt);
            VR_Status = VR_STATUS_0;

            opt = GCL_GetOption('r');
            if (opt)
            {
                VR_Records[0] = GCL_StrToInt(opt);
                VR_Records[1] = GCL_StrToInt(GCL_NextStr());
                VR_Records[2] = GCL_StrToInt(GCL_NextStr());
                VR_Flags |= VRFLAG_RESULT;
            }
        }
        else
        {
            work->timed = 0;
            VR_Status = VR_STATUS_PLAY;
            VR_Records[0] = 0;
            VR_Records[1] = 0;
            VR_Records[2] = 0;
            VR_Records[3] = 0;
        }

        opt = work->time_var = GCL_GetOption('t');
        if (opt)
        {
            work->time = GCL_StrToInt(opt);
            VR_Flags |= VRFLAG_NO_NEXT;
            work->remove_items = GCL_StrToInt(GCL_NextStr());
        }
        else
        {
            work->time = 0;
            work->remove_items = 1;
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

        if (GCL_GetOption('v'))
        {
            work->goal_end = 0;
        }
        else
        {
            work->goal_end = 1;
        }

        opt = GCL_GetOption('b');
        if (opt)
        {
            VR_Flags |= VRFLAG_AMMO_BONUS;
            work->n_targets = GCL_StrToInt(opt);
            work->proc = GCL_StrToInt(GCL_NextStr());
        }
        else
        {
            work->n_targets = 0;
        }

        opt = GCL_GetOption('c');
        if (opt)
        {
            VR_Flags |= VRFLAG_AMMO_BONUS;
            work->n_items = GCL_StrToInt(opt);
            work->proc = GCL_StrToInt(GCL_NextStr());
        }
        else
        {
            work->n_items = 0;
        }

        if (work->n_targets)
        {
            work->mode = VR_MODE_TARGET;
        }
        else if (work->goal_end)
        {
            work->mode = VR_MODE_NORMAL;
        }
        else
        {
            work->mode = VR_MODE_SNEAKING;
        }

        if (work->n_items)
        {
            work->mode = VR_MODE_TARGET;
        }

        opt = GCL_GetOption('f');
        if (opt)
        {
            work->mode = GCL_StrToInt(opt);
        }

        if (!GCL_GetOption('i'))
        {
            Work.field_204_bars.field_6_snake_hp = GM_VitalityMax;
        }

        if (GetResources(work, where, &pos) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }

        bikkuri_flag = 0;
        VR_TargetCount = 0;

        work->name = name;
        work->paused = 0;
        work->stop = 0;
        work->dead_timer = 0;
        work->target_timer = 0;
        work->started = 0;
        work->f109 = 0;
        work->f10C = 0;
        work->last_count = 0;
        work->bonus = 0;
        work->result = 0;

        VR_Records[3] = 0;
    }

    return (void *)work;
}
