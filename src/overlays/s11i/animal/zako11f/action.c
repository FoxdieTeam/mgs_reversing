#include "../../../s00a/Enemy/enemy.h"

extern int GM_PlayerStatus_800ABA50;

extern SVECTOR s11i_800C33AC;

void AN_Unknown_800C3B7C( MATRIX *matrix );

// action
void s11i_asiato_800CAD34( void );
void s11i_asiato_800CADDC( void );
void s11i_asiato_800CB140( void );

// put
void s11i_asiato_800CE560( SVECTOR * );

/***Inlines***********************************************************************************************/
static inline void SetZako11FMode( Zako11FWork *work, void *action ) // rename
{
    work->action = action;
    work->time = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
    GM_ConfigMotionAdjust_80035008( &( work->body ), NULL );
}

static inline void UnsetMode( Zako11FWork *work )
{
    extern short    ActTable_800C3330[];
    work->field_8E2 = 0;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3330[STANDSTILL], 0, ACTINTERP, 0 );

    work->action2 = 0;
    work->time2 = 0;
    work->field_8E2 = 0;
    work->control.turn.vz = 0;
    work->control.turn.vx = 0;
}

static inline void SetAction( Zako11FWork *work, int n_action, int interp )
{
        extern short    ActTable_800C3330[];
    work->field_8E0 = n_action ;
    GM_ConfigObjectAction( &( work->body ), ActTable_800C3330[n_action], 0, interp );
}

static inline void UnsetAction( Zako11FWork *work, int n_action )
{
    extern short    ActTable_800C3330[];

    work->field_8E2 = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3330[n_action], 0, ACTINTERP, 0x3FE );
}

static inline void UnsetActionManual( Zako11FWork *work, int n_action, int a4 )
{
    extern short    ActTable_800C3330[];

    work->field_8E2 = n_action;
    GM_ConfigObjectOverride( &( work->body ), ActTable_800C3330[n_action], 0, ACTINTERP, a4 );
}
/**********************************************************************************************************/

int s11i_asiato_800C9840(Zako11FWork *work, int time)
{
    TARGET *target;

    target = work->target;
    if (target->damaged & TARGET_CAPTURE)
    {
        if (target->a_mode == 36)
        {
            SetZako11FMode(work, s11i_asiato_800CADDC);
        }
        else
        {
            SetZako11FMode(work, s11i_asiato_800CB140);
        }

        target->damaged = 0;
        return 1;
    }

    return 0;
}

int s11i_asiato_800C98CC(Zako11FWork *work)
{
    if (work->target->damaged & TARGET_DOWN)
    {
        return 1;
    }

    return 0;
}

int s11i_asiato_800C98E8(SVECTOR *vec)
{
    return ABS(vec->vx) + ABS(vec->vy) + ABS(vec->vz);
}

#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800C9924.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800C9B14.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800C9B6C.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800C9BE0.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800C9C34.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800C9CBC.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800C9D38.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800C9E48.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800C9EB0.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CA0B4.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CA25C.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CA4F4.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CA584.s")

void s11i_asiato_800CA66C(void) {}

#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CA674.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CA84C.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CA904.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CAA54.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CABAC.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CAC84.s")

#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CAD34.s")

#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CADDC.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CB0C0.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CB140.s")

#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CC1C4.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CC2FC.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CC314.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CC39C.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CC528.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CC5F4.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CC6C0.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CC758.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CC7F0.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CC8A4.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CC96C.s")
#pragma INCLUDE_ASM("asm/overlays/s11i/s11i_asiato_800CCA10.s")

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
        GM_SeSet(&work->control.mov, 0x92);
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

            s11i_asiato_800CE560(&pos);

            GM_SeSet(&work->control.mov, 0x93);

            if (work->sn_dis < 1000 && (GM_PlayerStatus_800ABA50 & PLAYER_FIRST_PERSON) && GV_RandU(12) > 10)
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

    if ((time > 186 && work->body.field_1C != 0) || !(work->pad.press & 0x1000000))
    {
        work->pad.time = 0;
        UnsetMode(work);
    }
}
