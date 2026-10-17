#include "paddemo2.h"

#include <stdio.h>
#include <stdlib.h>
#include "mgstype.h"
#include "libgv/libgv.h"
#include "libgcl/libgcl.h"
#include "game/game.h"
#include "menu/menuman.h"
#include "mts/mts.h"
#include "mts/mts_pad.h"
#include "linkvar.h"
#include "strcode.h"

extern void InitRandamTable(void);

/*---------------------------------------------------------------------------*/
// VR-DISC version of pad_demo.c: plays back a recorded pad stream (the
// training mode demonstrations) or records a new one ('r' option).
//
// Stream format (u_short words):
//   header[0] name, header[1] size in words, header[2] random seed,
//   header[3] flags (DEMO_HDR_SHUKAN_REVERSE), then one entry per
//   change of input: status [analog] [count]

// FIXME: GV_DemoPadAnalog (u_long) is only written as a halfword here
#define DemoPadAnalog           (*(u_short *)&GV_DemoPadAnalog)

#define DEMO_PAD_BUFFER         ((u_short *)0x00200000)
#define DEMO_PAD_BUFFER_SIZE    0xDFE   // words

// Bits of a stream status word (L3/R3/SELECT are not recorded)
#define DEMO_END                PAD_SEL // last entry
#define DEMO_COUNT              PAD_AL  // a repeat count follows
#define DEMO_ANALOG             PAD_AR  // an analog value (lx | ly << 8) follows
#define DEMO_DIGITAL_MASK       0x0FFF

#define DEMO_MAX_COUNT          30000
#define DEMO_ANALOG_NEUTRAL     0x8080
#define DEMO_ANALOG_DEADZONE    63

#define DEMO_HDR_SHUKAN_REVERSE 0x8000  // recorded with GM_CONFIG_SHUKAN_REVERSE

#define DEMO_CANCEL_BUTTONS     (PAD_START | PAD_CROSS | PAD_CIRCLE)

// flags
#define DEMO_STARTED            0x1
#define DEMO_STOPPED            0x2

#define HASH_START_JP           0x2103  // GV_StrCode("スタート")
#define HASH_RECORD_END         0x32A1  // GV_StrCode("記録終了"), sent by vr.c to "demo"
#define HASH_PLAY_END           0x545F  // GV_StrCode("再生終了")
#define HASH_CANCEL             0xED87  // GV_StrCode("キャンセル")

typedef struct _Work
{
    GV_ACT   actor;
    int      map;           // 0x20
    int      name;          // 0x24
    int      flags;         // 0x28
    int      count;         // 0x2C
    int      f30;           // 0x30
    int      noslow;        // 0x34
    u_short *ptr;           // 0x38
    u_short  status;        // 0x3C
    u_short  analog;        // 0x3E
    int      f40;           // 0x40
    int      proc;          // 0x44
    int      cancel;        // 0x48
    int      record;        // 0x4C
    int      size;          // 0x50
    u_short *header;        // 0x54
    int      f58;           // 0x58
    char     f5C;           // 0x5C
    char     wait_end;      // 0x5D
    int      wait;          // 0x60
    char     skip;          // 0x64
    u_short  config;        // 0x66
} Work;

/*---------------------------------------------------------------------------*/

static void ExecProc(Work *work)
{
    GCL_ARGS args;
    long     data;

    if (work->proc > 0)
    {
        args.argc = 1;
        args.argv = &data;

        data = work->cancel;

        GCL_ExecProc(work->proc, &args);
    }
}

static void Act(Work *work)
{
    GV_MSG   *msg;
    int       n_msgs;
    int       stop;
    u_short   status;
    u_short   analog;
    GV_PAD   *pad;
    int       dx, dy;
    short     len;

    stop = 0;

    if (GV_PauseLevel == 0)
    {
        n_msgs = GV_ReceiveMessage(work->name, &msg);
        for (; n_msgs > 0; n_msgs--, msg++)
        {
            if (msg->message[0] == HASH_RECORD_END)
            {
                stop = 1;
            }
            if (msg->message[0] == HASH_PLAY_END)
            {
                stop = 1;
            }
            if (msg->message[0] == HASH_KILL)
            {
                stop = 1;
            }
            if (msg->message[0] == HASH_CANCEL)
            {
                work->skip = 1;
            }
        }
    }

    if (GV_PauseLevel & GV_PAUSE_READERROR)
    {
        return;
    }

    if (!work->record)
    {
        /* playback */
        if (work->flags == 0)
        {
            work->flags = DEMO_STARTED;

            GM_GameStatus |= STATE_PADDEMO;
            if (work->noslow)
            {
                GM_GameStatus |= STATE_NOSLOW;
            }
        }

        if (work->cancel && ((mts_read_pad(1) & DEMO_CANCEL_BUTTONS) || work->skip))
        {
            ExecProc(work);
            work->cancel = 0;
            if (work->wait)
            {
                work->wait_end = 1;
            }
        }

        status = work->status & ~DEMO_COUNT;

        if (work->wait_end && work->wait-- <= 0)
        {
            DemoPadAnalog = 0;
            GV_DemoPadStatus[0] = 0;
            GM_GameStatus |= STATE_RADAR_OFF | STATE_MENU_DISABLE | STATE_LIFE_OFF;
            GV_PauseLevel |= GV_PAUSE_MENU;

            if (!stop)
            {
                return;
            }
        }

        GV_DemoPadStatus[0] = status & ~DEMO_END;
        DemoPadAnalog = work->analog;

        if (--work->count == 0)
        {
            work->status = *work->ptr++;
            if (work->status & DEMO_ANALOG)
            {
                work->analog = *work->ptr++;
            }

            if (work->status & DEMO_COUNT)
            {
                work->count = *work->ptr++;
            }
            else
            {
                work->count = 1;
            }
        }

        if ((status & DEMO_END) || stop)
        {
            work->cancel = 0;
            GM_GameStatus &= ~(STATE_PADDEMO | STATE_NOSLOW | STATE_PADRELEASE);
            GV_DestroyActor(&work->actor);
        }
    }
    else
    {
        /* recording */
        if (work->flags == 0)
        {
            printf("pad release ?\n");
            work->f5C = 0;
            work->flags |= DEMO_STARTED;
            if (work->noslow)
            {
                GM_GameStatus |= STATE_NOSLOW;
            }
        }

        pad = &GV_PadData[0];
        status = pad->status & ~(DEMO_COUNT | DEMO_ANALOG);

        if (work->size >= DEMO_PAD_BUFFER_SIZE)
        {
            stop = 1;
            work->header[0] = 0;
        }

        if (stop == 1)
        {
            status |= DEMO_END;
            work->flags |= DEMO_STOPPED;
        }

        // FIXME: the comma expression puts the "neutral" block before the
        // "analog" block (an if/else gives the opposite order); the left
        // stick (left_dx, left_dy) is read as one halfword
        if (pad->analog == 0 || GV_PauseLevel != 0 ||
            (analog = *(u_short *)&pad->left_dx,
             dx = pad->left_dx - 128, dy = pad->left_dy - 128,
             dx > -DEMO_ANALOG_DEADZONE && dx < DEMO_ANALOG_DEADZONE &&
             dy < DEMO_ANALOG_DEADZONE && dy > -DEMO_ANALOG_DEADZONE))
        {
            analog = DEMO_ANALOG_NEUTRAL;
        }
        else
        {
            status = (status | DEMO_ANALOG) & DEMO_DIGITAL_MASK;
        }

        if (work->count == 0)
        {
            work->status = status;
            work->analog = analog;
        }

        if (work->status == status && work->analog == analog &&
            !(work->flags & DEMO_STOPPED) && work->count < DEMO_MAX_COUNT)
        {
            work->count++;
        }
        else
        {
            if (work->count != 1)
            {
                len = 2;
                *work->ptr++ = work->status | DEMO_COUNT;
                if (work->status & DEMO_ANALOG)
                {
                    len = 3;
                    *work->ptr++ = work->analog;
                }
                *work->ptr++ = work->count;
                work->size += len;
            }
            else
            {
                len = 1;
                *work->ptr++ = work->status;
                if (work->status & DEMO_ANALOG)
                {
                    len = 2;
                    *work->ptr++ = work->analog;
                }
                work->size += len;
            }

            work->count = 1;
            work->status = status;
            work->analog = analog;
        }

        if (work->flags & DEMO_STOPPED)
        {
            len = 1;
            *work->ptr++ = work->status;
            if (work->status & DEMO_ANALOG)
            {
                len = 2;
                *work->ptr++ = work->analog;
            }
            work->size += len;
            work->header[1] = work->size;

            GM_GameStatus &= ~STATE_NOSLOW;
            if (GM_Configuration & GM_CONFIG_SHUKAN_REVERSE)
            {
                work->header[3] |= DEMO_HDR_SHUKAN_REVERSE;
            }

            GV_DestroyActor(&work->actor);
        }
    }
}

static void Die(Work *work)
{
    GV_PauseLevel &= ~GV_PAUSE_MENU;
    GM_Configuration = work->config;
    ExecProc(work);
}

static void RecordAct(Work *work)
{
    work->actor.act = (GV_ACTFUNC)Act;
}

static void WaitAct(Work *work)
{
    GV_MSG *msg;
    int     n_msgs;

    if (GV_PauseLevel == 0)
    {
        n_msgs = GV_ReceiveMessage(work->name, &msg);
        for (; n_msgs > 0; n_msgs--, msg++)
        {
            if (msg->message[0] == HASH_START_JP)
            {
                if (!work->record)
                {
                    work->actor.act = (GV_ACTFUNC)Act;
                }
                else
                {
                    work->actor.act = (GV_ACTFUNC)RecordAct;
                }

                GV_Time = 0;
                srand(work->header[2]);
            }
        }
    }
}

static int GetResources(Work *work, int name, int map)
{
    int seed;

    work->map = map;
    work->name = name;
    GM_CurrentMap = map;
    work->config = GM_Configuration;

    seed = rand() & 0x7FFF;

    if (GCL_GetOption('r'))
    {
        work->record = GCL_StrToInt(GCL_NextStr());
    }

    if (!work->record)
    {
        work->status = 0;
        GV_DemoPadStatus[0] = 0;
        GV_DemoPadStatus[1] = 0;

        work->ptr = DEMO_PAD_BUFFER;
        if (GCL_GetOption('d'))
        {
            work->ptr = GV_GetCache(GV_CacheID(GCL_StrToInt(GCL_NextStr()), 'c'));
        }

        work->header = work->ptr;
        seed = work->header[2];
        work->ptr += 4;

        work->status = *work->ptr++;
        if (work->status & DEMO_ANALOG)
        {
            work->analog = *work->ptr++;
        }
        else
        {
            work->analog = DEMO_ANALOG_NEUTRAL;
        }

        if (work->status & DEMO_COUNT)
        {
            work->count = *work->ptr++;
        }
        else
        {
            work->count = 1;
        }

        GV_DemoPadStatus[0] = work->status & ~(DEMO_COUNT | DEMO_ANALOG);
        DemoPadAnalog = work->analog;
        GM_Configuration |= GM_CONFIG_UNKNOWN_2000;

        if (work->header[3] & DEMO_HDR_SHUKAN_REVERSE)
        {
            GM_Configuration |= GM_CONFIG_SHUKAN_REVERSE;
        }
        else
        {
            GM_Configuration &= ~GM_CONFIG_SHUKAN_REVERSE;
        }
    }
    else
    {
        work->status = 0;

        work->ptr = DEMO_PAD_BUFFER;
        if (GCL_GetOption('d'))
        {
            work->ptr = GV_GetCache(GV_CacheID(GCL_StrToInt(GCL_NextStr()), 'c'));
        }

        work->header = work->ptr;
        work->ptr[0] = name;
        printf("name = %d\n", name);
        printf("GV_StrCode(\"demo\") = %d\n", GV_StrCode("demo"));

        work->ptr[1] = 0;
        work->ptr[2] = seed;
        work->ptr[3] = 0;

        work->analog = DEMO_ANALOG_NEUTRAL;
        work->status = 0;
        work->count = 0;
        work->ptr += 4;
        work->size += 4;
        printf("Save address : %08x\n", work->ptr);
    }

    if (GCL_GetOption('h'))
    {
        work->noslow = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->noslow = 1;
    }

    MENU_ResetItemPos();
    MENU_ResetWeaponPos();

    if (GCL_GetOption('f'))
    {
        work->proc = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->proc = -1;
    }

    work->cancel = GCL_GetOption('c') != 0;
    work->f5C = 1;

    if (GCL_GetOption('p'))
    {
        work->wait = GCL_StrToInt(GCL_NextStr());
    }
    else
    {
        work->wait = 0;
    }

    work->wait_end = 0;
    work->skip = 0;

    InitRandamTable();
    srand(seed);
    GV_Time = 0;
    return 0;
}

/*---------------------------------------------------------------------------*/

void *NewPadDemo2(int name, int where)
{
    Work *work;

    work = GV_NewActor(GV_ACTOR_MANAGER, sizeof(Work));
    if (work != NULL)
    {
        GV_SetNamedActor(&work->actor, WaitAct, Die, "paddemo2.c");

        if (GetResources(work, name, where) < 0)
        {
            GV_DestroyActor(&work->actor);
            return NULL;
        }
    }

    return (void *)work;
}
