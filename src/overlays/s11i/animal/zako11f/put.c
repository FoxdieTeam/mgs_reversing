#include "../../../s00a/Enemy/enemy.h"
#include "Anime/animeconv/anime.h"
#include "Game/item.h"
#include "Game/linkvarbuf.h"
#include "Okajima/blood.h"

extern SVECTOR s11i_800C33B4;
extern SVECTOR s11i_800C33BC;
extern SVECTOR s11i_800C33C4;
extern SVECTOR s11i_800C33CC;
extern SVECTOR s11i_800C33F4;
extern SVECTOR s11i_800C33FC;

extern const char *s11i_dword_800C33D4[3];
extern void       *PutFuncList_800C33E0[5];

extern ZAKO11F_COMMAND Zako11FCommand_800D5AF8;

void  AN_Breath_800C3AA8( MATRIX *world );
void  NewLSight_800D1D2C( SVECTOR *from, SVECTOR *to, int color );
void *NewBulletEx( int, MATRIX *, int, int, int, int, int, int, int );

int ZAKO11F_ClearPutChar_800CD748( Zako11FWork *work, void *func );

void ZAKO11F_PutBlood_800CCFD4(Zako11FWork *work, int unit, int count)
{
    MATRIX world;

    DG_SetPos(&work->body.objs->objs[unit].world);
    DG_MovePos(&s11i_800C33B4);
    DG_RotatePos(&s11i_800C33BC);
    ReadRotMatrix(&world);
    NewBlood(&world, count);
}

void ZAKO11F_PutFog_800CD044(Zako11FWork *work)
{
    MATRIX  world;
    SVECTOR pos;

    DG_SetPos( &work->body.objs->objs[1].world );
    DG_MovePos( &s11i_800C33C4 );
    DG_RotatePos( &s11i_800C33CC );
    ReadRotMatrix( &world );

    pos.vx = world.t[ 0 ];
    pos.vy = world.t[ 1 ];
    pos.vz = world.t[ 2 ];

    AN_Fog_800CA618( &pos );
}

void ZAKO11F_PutItem_800CD0A8( Zako11FWork *work )
{
    int rand;
    SVECTOR svec;
    CONTROL *ctrl;
    Item_Info item;

    svec = work->unknown.field_0C;
    rand = 10;
    ctrl = &work->control;
    svec.vx += GV_RandU( rand );
    svec.vy += 100;
    rand = GV_RandU( rand );
    svec.vz += rand;
    rand = GV_RandU( 4 );

    switch ( rand )
    {
    case 0:
    case 1:
        item.field_4_type   = 4;
        item.field_6_id     = ITEM_RATION;
        item.field_8_amount = 1;
        item.field_0_pName  = s11i_dword_800C33D4[0];
        break;
    case 2:
        //socom
        if ( GM_SocomFlag < 0 )
        {
            item.field_4_type   = 4;
            item.field_6_id     = ITEM_RATION;
            item.field_8_amount = 1;
            item.field_0_pName  = s11i_dword_800C33D4[0];
        }
        else
        {
            //Socom bullets
            item.field_4_type = 2;
            item.field_6_id = WEAPON_SOCOM;
            item.field_8_amount = 12;
            item.field_0_pName  = s11i_dword_800C33D4[1];
        }
        break;
    case 3:
        //famas
        if ( GM_FamasFlag < 0  )
        {
            item.field_4_type   = 4;
            item.field_6_id     = ITEM_RATION;
            item.field_8_amount = 1;
            item.field_0_pName  = s11i_dword_800C33D4[0];
        }
        else
        {
            item.field_6_id     = WEAPON_FAMAS;
            item.field_4_type   = 2;
            item.field_8_amount = 25;
            item.field_0_pName  = s11i_dword_800C33D4[2];
        }
        break;
    }
    item.field_A = 900;
    item_init_80034758( &ctrl->mov, &svec, &item );
}

void ZAKO11F_PutMark_800CD224( Zako11FWork *work, int mark )
{
    MATRIX *world;

    if (!(work->control.map->index & GM_PlayerMap))
    {
        return;
    }

    world = &work->body.objs->objs[6].world;

    if (mark == 0)
    {
        GM_SeSet(&work->control.mov, SE_EXCLAMATION);
    }

    if (work->mark_time != 0)
    {
        GV_DestroyActor(work->mark);
    }

    work->mark = AN_Unknown_800CA1EC(world, mark);
    work->mark_time = 30;
}

void ZAKO11F_PutSound_800CD2C0( Zako11FWork *work )
{
    int action;
    int frame;
    int step1, step2;

    action = work->unknown.last_set;
    frame = work->m_ctrl.info1.frame;
    step1 = 160 + (work->param.index % 4) * 2;
    step2 = 160 + (work->param.index % 4) * 2 + 1;

    if (action == ACTION1)
    {
        if (frame == 22)
        {
            GM_SeSet(&work->control.mov, step2);
        }
        else if (frame == 11)
        {
            GM_SeSet(&work->control.mov, step1);
        }
    }
    else if (action == ACTION2)
    {
        if (frame == 16)
        {
            GM_SeSet(&work->control.mov, step2);
        }
        else if (frame == 8)
        {
            GM_SeSet(&work->control.mov, step1);
        }
    }
}

void ZAKO11F_PutBreath_800CD358( Zako11FWork *work )
{
    int frame;

    if ( Zako11FCommand_800D5AF8.mode == TOP_COMM_ALERT )
    {
        return;
    }

    if ( !( work->control.map->index & GM_PlayerMap ) )
    {
        return;
    }

    if ( work->unknown.last_unset == ACTION20 )
    {
        frame = work->m_ctrl.info2.frame;
        if ( frame == 31 )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world );
        }
    }
    else if ( work->unknown.last_unset == ACTION22 )
    {
        frame = work->m_ctrl.info2.frame;
        if ( ( frame == 15 ) || ( frame == 35 ) || ( frame == 50 ) || ( frame == 60 ) ||
             ( frame == 70 ) || ( frame == 74 ) || ( frame == 78 ) )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world );
        }
    }
    else if ( work->unknown.last_unset == ACTION19 )
    {
        frame = work->m_ctrl.info2.frame;
        if ( ( frame == 30  ) || ( frame == 40  ) || ( frame == 50 ) || ( frame == 60 ) ||
             ( frame == 70  ) || ( frame == 80  ) || ( frame == 90 ) || ( frame == 95 ) ||
             ( frame == 100 ) || ( frame == 105 ) )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world );
        }
    }
    else
    {
        if ( ( GV_Time % 64 ) == ( work->param.index * 16 ) )
        {
            AN_Breath_800C3AA8( &work->body.objs->objs[6].world );
        }
    }
}

void ZAKO11F_PutLSight_800CD4A0( Zako11FWork *work )
{
    if ( work->vision.field_B92 == 2 )
    {
        NewLSight_800D1D2C( &GM_PlayerPosition, &work->control.mov, 0x00008F );
    }
}

void ZAKO11F_PutBulletEx_800CD4DC( Zako11FWork *work )
{
    SVECTOR rot;
    MATRIX  local;
    MATRIX *world;

    rot = DG_ZeroVector;
    rot.vz = GV_RandU( 128 );

    world = &work->body.objs->objs[4].world;

    DG_SetPos( world );
    DG_MovePos( &s11i_800C33F4 );
    DG_RotatePos( &rot );

    rot.vx = GV_RandS( 16 ) + 1024;
    rot.vz = 0;

    DG_RotatePos( &rot );
    ReadRotMatrix( &local );

    if ( GV_Time & 3 )
    {
        NewBulletEx(0x100, &local, ENEMY_SIDE, 1, 0, 0xA, work->field_B84, 10000, 750);
    }
    else
    {
        NewBulletEx(0x1100, &local, ENEMY_SIDE, 1, 0, 0xA, work->field_B84, 10000, 750);
    }

    GM_SeSetMode( &work->control.mov, SE_ENEMY_SHOT, GM_SEMODE_BOMB );

    NewAnime_8005D6BC( world, 0 );
    NewAnime_8005D604( &local );

    ZAKO11F_ClearPutChar_800CD748( work, ZAKO11F_PutBulletEx_800CD4DC );
}

void ZAKO11F_PutBulletEx2_800CD618( Zako11FWork *work )
{
    SVECTOR rot;
    MATRIX  local;
    MATRIX *world;

    rot.vx = 1024;
    rot.vy = 0;
    rot.vz = GV_RandS( 16 );

    world = &work->body.objs->objs[4].world;

    DG_SetPos( world );
    DG_MovePos( &s11i_800C33FC );
    DG_RotatePos( &rot );
    ReadRotMatrix( &local );

    NewBulletEx(0x901, &local, ENEMY_SIDE, 1, 0, 0x1E, work->field_B86, 40000, 1500);

    GM_SeSetMode( &work->control.mov, SE_ENEMY_SHOT, GM_SEMODE_BOMB );

    NewAnime_8005D6BC( world, 0 );
    NewAnime_8005D604( &local );

    ZAKO11F_ClearPutChar_800CD748( work, ZAKO11F_PutBulletEx2_800CD618 );
}

int ZAKO11F_SetPutChar_800CD700( Zako11FWork *work, int idx )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[ i ] == NULL )
        {
            work->field_B00[ i ] = PutFuncList_800C33E0[ idx ];
            return 1;
        }
    }

    return 0;
}

int ZAKO11F_ClearPutChar_800CD748( Zako11FWork *work, void *func )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[ i ] == func )
        {
            work->field_B00[ i ] = NULL;
            return 1;
        }
    }

    return 0;
}

void ZAKO11F_ExecPutChar_800CD77C( Zako11FWork *work )
{
    int i;

    for ( i = 0 ; i < 8 ; i++ )
    {
        if ( work->field_B00[i] )
        {
            ZAKO11FPUTFUNC func = work->field_B00[i];
            func( work );
        }
    }
}
