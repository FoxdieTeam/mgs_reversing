#include "enemy/enemy.h"

/***Inlines***********************************************************************************************/
static inline void SetZako11FMode( Zako11FWork *work, ZAKO11FACTION action ) // rename
{
    work->action = action;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_ConfigMotionAdjust( &( work->body ), NULL );
}

static inline void SetZako11FMode2( Zako11FWork *work, ZAKO11FACTION action ) // rename
{
    if ( !work->action2 )
    {
        work->action2 = action;
        work->time2 = 0;
    }

    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_ConfigMotionAdjust( &( work->body ), 0 );
}

static inline void SetZako11FModeFields( Zako11FWork *work, ZAKO11FACTION action ) // rename
{
    work->action = action;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

static inline void UnsetMode( Zako11FWork *work )
{
    extern short    ActTable_800C3330[];
    work->unknown.last_unset = 0;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3330[STANDSTILL], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->unknown.last_unset = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

static inline void SetAction( Zako11FWork *work, int n_action, int interp )
{
    extern short    ActTable_800C3330[];
    work->unknown.last_set = n_action ;
    GM_ConfigObjectAction( &( work->body ), ActTable_800C3330[n_action], 0, interp );
}

static inline void UnsetAction( Zako11FWork *work, int n_action )
{
    extern short    ActTable_800C3330[];

    work->unknown.last_unset = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3330[n_action], 0, ACTINTERP, 0x3FE );
}

static inline void UnsetActionManual( Zako11FWork *work, int n_action, int a4 )
{
    extern short    ActTable_800C3330[];

    work->unknown.last_unset = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3330[n_action], 0, ACTINTERP, a4 );
}
/**********************************************************************************************************/

SVECTOR s11i_800C33AC = {0, -700, 900, 0};
SVECTOR s11i_800C33B4 = {0, 0, 100, 0};
SVECTOR s11i_800C33BC = {-1024, 0, 0, 0};
SVECTOR s11i_800C33C4 = {0, 0, 100, 0};
SVECTOR s11i_800C33CC = {-1024, 0, 0, 0};

extern void AN_Unknown_800C3B7C( MATRIX *matrix );
extern void AN_Sleep( SVECTOR *pos );

void s11i_asiato_800CAD34( Zako11FWork *work, int time );

void s11i_asiato_800CC528(Zako11FWork *work, int time)
{
    if (time == 0)
    {
        UnsetAction(work, ACTION9);
    }

    if (!(work->pad.press & 0x1))
    {
        UnsetMode(work);
    }
    else if (time < 4)
    {
        work->vision.facedir = (work->control.rot.vy - (time * 256)) & 0xFFF;
    }
    else
    {
        work->vision.facedir = (work->control.rot.vy - 1024) & 0xFFF;
    }
}

void s11i_asiato_800CC5F4(Zako11FWork *work, int time)
{
    if (time == 0)
    {
        UnsetAction(work, ACTION10);
    }

    if (!(work->pad.press & 0x2))
    {
        UnsetMode(work);
    }
    else if (time < 4)
    {
        work->vision.facedir = (work->control.rot.vy + (time * 256)) & 0xFFF;
    }
    else
    {
        work->vision.facedir = (work->control.rot.vy + 1024) & 0xFFF;
    }
}

void ActOverScoutD_800CC6C0(Zako11FWork *work, int time)
{
    work->vision.length = 3000;

    if (time == 0)
    {
        UnsetAction(work, ACTION11);
    }

    if (!(work->pad.press & 0x4))
    {
        UnsetMode(work);
    }
}

void s11i_asiato_800CC758(Zako11FWork *work, int time)
{
    work->vision.length = 3000;

    if (time == 0)
    {
        UnsetAction(work, ACTION14);
    }

    if (!(work->pad.press & 0x2000))
    {
        UnsetMode(work);
    }
}

void s11i_asiato_800CC7F0(Zako11FWork *work, int time)
{
    work->vision.length = 0;

    if (time == 0)
    {
        UnsetAction(work, ACTION24);
        GM_SeSet(&work->control.mov, SE_V_ENE_SNEEZE);
    }

    if (work->body.time2 != 0 || !(work->pad.press & 0x40))
    {
        work->pad.time = 0;
        UnsetMode(work);
    }
}

void s11i_asiato_800CC8A4(Zako11FWork *work, int time)
{
    work->vision.length = 0;

    if (time == 0)
    {
        UnsetAction(work, ACTION22);
    }

    if (time == 60)
    {
        GM_SeSet(&work->control.mov, SE_V_ENE_YAWN);
    }

    if ((work->body.time2 != 0) || !(work->pad.press & 0x80))
    {
        work->pad.time = 0;
        UnsetMode(work);
    }
}

void s11i_asiato_800CC96C(Zako11FWork *work, int time)
    {
    if (time == 0)
    {
        UnsetAction(work, ACTION23);
    }

    if ((work->body.time2 != 0) || !(work->pad.press & 0x400))
    {
        work->pad.time = 0;
        UnsetMode(work);
    }
}

void s11i_asiato_800CCA10(Zako11FWork *work, int time)
{
    work->vision.length = 0;

    if (time == 0)
    {
        UnsetAction(work, ACTION19);
    }

    if (time == 90)
    {
        GM_SeSet(&work->control.mov, SE_V_ENE_YAWN);
    }

    if (work->body.time2 != 0 || !(work->pad.press & 0x800))
    {
        work->pad.time = 0;
        UnsetMode(work);
    }
}

void s11i_asiato_800CCAD8(Zako11FWork *work, int time)
{
    SVECTOR pos;

    work->vision.length = 0;

    if (time == 0)
    {
        UnsetAction(work, ACTION19);
    }

    if (time == 90)
    {
        GM_SeSet(&work->control.mov, SE_V_ENE_YAWN);
    }

    if (time == 110)
    {
        UnsetAction(work, ACTION20);
    }

    if (time > 110)
    {
        work->act_status |= 0x10;

        if (work->m_ctrl.info2.frame == 30)
        {
            pos = work->control.mov;
            pos.vy += 500;

            AN_Sleep(&pos);

            GM_SeSet(&work->control.mov, SE_V_ENE_SNORE);

            if (work->sn_dis < 1000 && (GM_PlayerStatus & PLAYER_WATCH) && GV_RandU(12) > 10)
            {
                work->pad.sound = 240;
            }
        }

        if (work->pad.press & 0x1000)
        {
            SetZako11FMode(work, s11i_asiato_800CAD34);
            UnsetMode(work);
            return;
        }
    }

    if (!(work->pad.press & 0x200))
    {
        UnsetMode(work);
    }
}

void s11i_asiato_800CCCB0(Zako11FWork *work)
{
    MATRIX rot;

    DG_SetPos(&work->body.objs->objs[6].world);
    DG_MovePos(&s11i_800C33AC);
    ReadRotMatrix(&rot);

    AN_Unknown_800C3B7C(&rot);
}

void s11i_asiato_800CCCF0(Zako11FWork *work, int time)
{
    int diff;

    work->vision.length = 3000;
    work->act_status |= 0x80;

    if (time == 0)
    {
        UnsetAction(work, ACTION25);
    }

    if (time >= 1000 && time < 1210)
    {
        diff = time - 1000;

        if (diff == 0  || diff == 4  || diff == 8  || diff == 12 ||
            diff == 20 || diff == 28 || diff == 36 || diff == 48 ||
            diff == 60)
        {
            GM_SeSet(&work->control.mov, SE_WET_STEP);
            s11i_asiato_800CCCB0(work);
        }
    }
    else if (time > 30 && time & 1)
    {
        GM_SeSet(&work->control.mov, SE_WET_STEP);
        if (time > 45)
        {
            s11i_asiato_800CCCB0(work);
        }
    }

    if (!(work->pad.press & 0x800000))
    {
        UnsetMode(work);
    }
}

void s11i_asiato_800CCE38(Zako11FWork *work, int time)
{
    work->vision.length = 3000;

    if (time == 0)
    {
        UnsetAction(work, ACTION25);
    }

    if (time == 186)
    {
        UnsetActionManual(work, ACTION26, 0xFFFF);
    }

    if (time == 0   || time == 4   || time == 8   || time == 12  ||
        time == 20  || time == 28  || time == 36  || time == 48  ||
        time == 60  || time == 120 || time == 122 || time == 124 ||
        time == 126 || time == 180 || time == 182 || time == 184 ||
        time == 186)
    {
        GM_SeSet(&work->control.mov, SE_WET_STEP);
        s11i_asiato_800CCCB0(work);
    }

    if ((time > 186 && work->body.time2 != 0) || !(work->pad.press & 0x1000000))
    {
        work->pad.time = 0;
        UnsetMode(work);
    }
}
