#include "zako.h"

/*---------------------------------------------------------------------------*/

void AN_Sleep( SVECTOR *pos );
void AN_Unknown_800C3B7C( MATRIX *world ); // TODO: test

/*---------------------------------------------------------------------------*/

static SVECTOR BreathPos = {0, -700, 900};

/*---------------------------------------------------------------------------*/

void s11a_800CD198( Work *work, int time )
{
    if ( time == 0 ) SetAction2( work, 9, 4, 0x3FE );

    if ( !( work->pad.press & 0x1 ) )
    {
        UnsetMode( work );
    }
    else if ( time < 4 )
    {
        work->vision.facedir = ( work->control.rot.vy - time * 256 ) & 4095;
    }
    else
    {
        work->vision.facedir = ( work->control.rot.vy - 1024 ) & 4095;
    }
}

void s11a_800CD264( Work *work, int time )
{
    if ( time == 0 ) SetAction2( work, 10, 4, 0x3FE );

    if ( !( work->pad.press & 0x2 ) )
    {
        UnsetMode( work );
    }
    else if ( time < 4 )
    {
        work->vision.facedir = ( work->control.rot.vy + time * 256 ) & 4095;
    }
    else
    {
        work->vision.facedir = ( work->control.rot.vy + 1024 ) & 4095;
    }
}

void s11a_800CD330( Work *work, int time )
{
    work->vision.length = 3000;

    if ( time == 0 ) SetAction2( work, 11, 4, 0x3FE );
    if ( !( work->pad.press & 0x4 ) ) UnsetMode( work );
}

void s11a_800CD3C8( Work *work, int time )
{
    work->vision.length = 3000;

    if ( time == 0 ) SetAction2( work, 14, 4, 0x3FE );
    if ( !( work->pad.press & 0x2000 ) ) UnsetMode( work );
}

void s11a_800CD460( Work *work, int time )
{
    work->vision.length = 0;

    if ( time == 0 )
    {
        SetAction2( work, 24, 4, 0x3FE );
        GM_SeSet( &work->control.mov, SE_V_ENE_SNEEZE );
    }

    if ( work->body.time2 != 0 || !( work->pad.press & 0x40 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

void s11a_800CD514( Work *work, int time )
{
    work->vision.length = 0;

    if ( time == 0 ) SetAction2( work, 22, 4, 0x3FE );
    if ( time == 60 ) GM_SeSet( &work->control.mov, SE_V_ENE_YAWN );

    if ( work->body.time2 != 0 || !( work->pad.press & 0x80 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

void s11a_800CD5DC( Work *work, int time )
{
    if ( time == 0 ) SetAction2( work, 23, 4, 0x3FE );

    if ( work->body.time2 != 0 || !( work->pad.press & 0x400 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

void s11a_800CD680( Work *work, int time )
{
    work->vision.length = 0;

    if ( time == 0 ) SetAction2( work, 19, 4, 0x3FE );
    if ( time == 90 ) GM_SeSet( &work->control.mov, SE_V_ENE_YAWN );

    if ( work->body.time2 != 0 || !( work->pad.press & 0x800 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}

void s11a_800CD748( Work *work, int time )
{
    SVECTOR pos;

    work->vision.length = 0;

    if ( time == 0 ) SetAction2( work, 19, 4, 0x3FE );
    if ( time == 90 ) GM_SeSet( &work->control.mov, SE_V_ENE_YAWN );
    if ( time == 110 ) SetAction2( work, 20, 4, 0x3FE );

    if ( time > 110 )
    {
        work->act_status |= 0x10;

        if ( work->m_ctrl.info2.frame == 30 )
        {
            pos = work->control.mov;
            pos.vy += 500;
            AN_Sleep( &pos );
            GM_SeSet( &work->control.mov, SE_V_ENE_SNORE );

            if ( work->sn_dis < 1000 &&
                 ( GM_PlayerStatus & PLAYER_WATCH ) &&
                 GV_RandU( 12 ) > 10 )
            {
                work->pad.sound = 240;
            }
        }

        if ( work->pad.press & 0x1000 )
        {
            SetMode( work, s11a_800CB964 );
            UnsetMode( work );
            return;
        }
    }

    if ( !( work->pad.press & 0x200 ) )
    {
        UnsetMode( work );
    }
}

static void s11a_800CD920( Work *work ) 
{
    MATRIX world;

    DG_SetPos( &work->body.objs->objs[ 6 ].world );
    DG_MovePos( &BreathPos );
    ReadRotMatrix( &world );
    AN_Unknown_800C3B7C( &world );
}

void s11a_800CD960( Work *work, int time )
{
    int cont;

    work->vision.length = 3000;
    work->act_status |= 0x80;

    if ( time == 0 ) SetAction2( work, 25, 4, 0x3FE );

    if ( time >= 1000 && time <= 1209 )
    {
        cont = time - 1000;
        if ( cont == 0  || cont == 4  || cont == 8  || cont == 12 ||
             cont == 20 || cont == 28 || cont == 36 || cont == 48 ||
             cont == 60 )
        {
            GM_SeSet( &work->control.mov, SE_WET_STEP );
            s11a_800CD920( work );
        }
    }
    else if ( time > 30 && ( time & 0x1 ) )
    {
        GM_SeSet( &work->control.mov, SE_WET_STEP );
        if ( time > 45 ) s11a_800CD920( work );
    }

    if ( !( work->pad.press & 0x800000 ) ) UnsetMode( work );
}

void s11a_800CDAA8( Work *work, int time )
{
    work->vision.length = 3000;

    if ( time == 0 ) SetAction2( work, 25, 4, 0x3FE );
    if ( time == 186 ) SetAction2( work, 26, 4, 0xFFFF );

    if ( time == 0   || time == 4   || time == 8   || time == 12  ||
         time == 20  || time == 28  || time == 36  || time == 48  ||
         time == 60  || time == 120 || time == 122 || time == 124 ||
         time == 126 || time == 180 || time == 182 || time == 184 ||
         time == 186 )
    {
        GM_SeSet( &work->control.mov, SE_WET_STEP );
        s11a_800CD920( work );
    }

    if ( ( time > 186 && work->body.time2 != 0 ) || !( work->pad.press & 0x1000000 ) )
    {
        work->pad.time = 0;
        UnsetMode( work );
    }
}
