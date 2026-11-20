#include "zako.h"

/*---------------------------------------------------------------------------*/

extern void AN_Sleep( SVECTOR *pos );
extern void AN_Unknown_800C3B7C( MATRIX *world );

/*---------------------------------------------------------------------------*/

static SVECTOR s11i_800C33AC = {0, -700, 900};

/*---------------------------------------------------------------------------*/

void s11i_asiato_800CC528(Work *work, int time)
{
    if (time == 0)
    {
        SetAction2(work, 9, ACTINTERP, 0x3FE);
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

void s11i_asiato_800CC5F4(Work *work, int time)
{
    if (time == 0)
    {
        SetAction2(work, 10, ACTINTERP, 0x3FE);
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

void ActOverScoutD_800CC6C0(Work *work, int time)
{
    work->vision.length = 3000;

    if (time == 0)
    {
        SetAction2(work, 11, ACTINTERP, 0x3FE);
    }

    if (!(work->pad.press & 0x4))
    {
        UnsetMode(work);
    }
}

void s11i_asiato_800CC758(Work *work, int time)
{
    work->vision.length = 3000;

    if (time == 0)
    {
        SetAction2(work, 14, ACTINTERP, 0x3FE);
    }

    if (!(work->pad.press & 0x2000))
    {
        UnsetMode(work);
    }
}

void s11i_asiato_800CC7F0(Work *work, int time)
{
    work->vision.length = 0;

    if (time == 0)
    {
        SetAction2(work, 24, ACTINTERP, 0x3FE);
        GM_SeSet(&work->control.mov, SE_V_ENE_SNEEZE);
    }

    if (work->body.time2 != 0 || !(work->pad.press & 0x40))
    {
        work->pad.time = 0;
        UnsetMode(work);
    }
}

void s11i_asiato_800CC8A4(Work *work, int time)
{
    work->vision.length = 0;

    if (time == 0)
    {
        SetAction2(work, 22, ACTINTERP, 0x3FE);
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

void s11i_asiato_800CC96C(Work *work, int time)
    {
    if (time == 0)
    {
        SetAction2(work, 23, ACTINTERP, 0x3FE);
    }

    if ((work->body.time2 != 0) || !(work->pad.press & 0x400))
    {
        work->pad.time = 0;
        UnsetMode(work);
    }
}

void s11i_asiato_800CCA10(Work *work, int time)
{
    work->vision.length = 0;

    if (time == 0)
    {
        SetAction2(work, 19, ACTINTERP, 0x3FE);
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

void s11i_asiato_800CCAD8(Work *work, int time)
{
    SVECTOR pos;

    work->vision.length = 0;

    if (time == 0)
    {
        SetAction2(work, 19, ACTINTERP, 0x3FE);
    }

    if (time == 90)
    {
        GM_SeSet(&work->control.mov, SE_V_ENE_YAWN);
    }

    if (time == 110)
    {
        SetAction2(work, 20, ACTINTERP, 0x3FE);
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
            SetMode(work, s11i_asiato_800CAD34);
            UnsetMode(work);
            return;
        }
    }

    if (!(work->pad.press & 0x200))
    {
        UnsetMode(work);
    }
}

void s11i_asiato_800CCCB0(Work *work)
{
    MATRIX rot;

    DG_SetPos(&work->body.objs->objs[6].world);
    DG_MovePos(&s11i_800C33AC);
    ReadRotMatrix(&rot);

    AN_Unknown_800C3B7C(&rot);
}

void s11i_asiato_800CCCF0(Work *work, int time)
{
    int diff;

    work->vision.length = 3000;
    work->act_status |= 0x80;

    if (time == 0)
    {
        SetAction2(work, 25, ACTINTERP, 0x3FE);
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

void s11i_asiato_800CCE38(Work *work, int time)
{
    work->vision.length = 3000;

    if (time == 0)
    {
        SetAction2(work, 25, ACTINTERP, 0x3FE);
    }

    if (time == 186)
    {
        SetAction2(work, 26, ACTINTERP, 0xFFFF);
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
