#include <stdio.h>
#include "common.h"
#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "Game/game.h"
#include "Game/linkvarbuf.h"
#include "Game/object.h"

typedef struct _Hind2Work
{
    GV_ACT       actor;
    CONTROL      control;
    OBJECT       body;
    MATRIX       light[2];
    DG_PRIM     *prim;
    SVECTOR      vertices[1];
    RECT         prim_rect;
    DG_TEX      *tex;
    char         pad1[0x4];
    int          name;
    short        f1E0[2];
    VECTOR       f1E4;
    SVECTOR      f1F4;
    unsigned int f1FC;
    int          f200;
    char         pad2[0x10];
    VECTOR       f214;
    int          f224;
    SVECTOR      f228;
    int          f230;
    int          f234;
    SVECTOR      adjust[10];
    int          f288;
    SVECTOR      f28C;
    char         pad3[0x10];
    int          f2A4;
    int          f2A8;
} Hind2Work;

SVECTOR s11i_800C32C0 = { 0, -2728, 5587, 0 };

extern int     GV_Clock;
extern SVECTOR GM_PlayerPosition_800ABA10;

void *NewHdBul2( SVECTOR *arg0, SVECTOR *arg1, int enable );

#define EXEC_LEVEL GV_ACTOR_LEVEL5
#define BODY_FLAG  ( DG_FLAG_TEXT | DG_FLAG_TRANS | DG_FLAG_GBOUND | DG_FLAG_SHADE )

void Hind2_800C43F0( SVECTOR *a, SVECTOR *b, VECTOR *out )
{
    out->vx = a->vx - b->vx;
    out->vy = a->vy - b->vy;
    out->vz = a->vz - b->vz;
}

void Hind2_800C4430( Hind2Work *work )
{
    OBJECT *body;
    int     val;

    body = &work->body;

    val = body->rots[ 1 ].vy;
    val = ( val + work->f1E0[ 0 ] ) & 4095;
    body->rots[ 1 ].vy = val;

    val = body->rots[ 2 ].vx;
    val = ( val + work->f1E0[ 1 ] ) & 4095;
    body->rots[ 2 ].vx = val;
}

void Hind2_800C4468( Hind2Work *work, int arg1 )
{
    if ( GV_Time & 3 )
    {
        return;
    }

    if ( arg1 == 0 )
    {
        GM_SeSetMode( &work->f28C, 181, GM_SEMODE_BOMB );
    }
    else if ( arg1 == 1 )
    {
        GM_SeSet2( 0, 8, 181 );
    }
}

void Hind2_800C44C4( Hind2Work *work )
{
    VECTOR   diff;
    MATRIX   rot;
    SVECTOR  pos;
    SVECTOR  pos_world;
    SVECTOR *mov;

    mov = &work->control.mov;

    work->control.mov.vx = work->f1E4.vx;
    work->control.mov.vy = work->f1E4.vy;
    work->control.mov.vz = work->f1E4.vz;

    Hind2_800C43F0( &GM_PlayerPosition_800ABA10, mov, &diff );

    work->control.turn.vy = ratan2( diff.vx, diff.vz );
    work->control.turn.vx = -ratan2( diff.vy, SquareRoot0( diff.vx * diff.vx + diff.vz * diff.vz ) );

    pos = work->control.mov;

    ReadRotMatrix( &rot );
    DG_SetPos2( &pos, &work->control.rot );
    DG_RotVector( &work->f1F4, &pos_world, 1 );
    GV_SubVec3( &pos, &pos_world, mov );
    DG_SetPos( &rot );
}

void Hind2_800C45E4( Hind2Work *work, SVECTOR arg1 )
{
    MATRIX    sp10;
    SVECTOR   sp30;
    DG_PRIM  *prim;
    DG_TEX   *tex;
    int       rand_w, rand_h;
    int       x, y, w, h;
    POLY_FT4 *poly;

    prim = work->prim;

    DG_InvisiblePrim( prim );

    if ( !( work->f200 & 0x1 ) )
    {
        DG_MovePos( &work->f1F4 );
        ReadRotMatrix( &sp10 );

        DG_VisiblePrim( prim );
        DG_PutPrim( &prim->world );

        rand_w = GV_RandU( 1024 ) % 2;
        rand_h = GV_RandU( 1024 ) % 2;

        tex = work->tex;
        x = tex->off_x;
        w = tex->w;
        y = tex->off_y;
        h = tex->h;

        poly = (POLY_FT4 *)prim->packs[ GV_Clock ];

        poly->u0 = poly->u2 = x + ( w * rand_w ) / 2;
        poly->u1 = poly->u3 = x + ( w * ( rand_w + 1 ) ) / 2 - 1;

        poly->v0 = poly->v1 = y + ( h * rand_h ) / 2;
        poly->v2 = poly->v3 = y + ( h * ( rand_h + 1 ) ) / 2 - 1;

        sp30.vx = sp10.t[ 0 ];
        sp30.vy = sp10.t[ 1 ];
        sp30.vz = sp10.t[ 2 ];

        NewHdBul2( &sp30, &arg1, 1 );
        GM_SeSetMode( &work->f28C, 177, GM_SEMODE_BOMB );
    }
}

void Hind2_800C47A4( Hind2Work *work )
{
    work->control.mov.vx += work->f230;
    work->f1E4.vx += work->f230;
}

void Hind2_800C47C8( Hind2Work *work )
{
    int f224;

    f224 = work->f224;
    work->control.mov.vx += ( rsin( f224 * 23 ) - rsin( ( f224 - 1 ) * 23 ) ) * 2;
    work->control.mov.vy += ( rsin( f224 * 64 ) - rsin( ( f224 - 1 ) * 64 ) );
    work->control.mov.vz += ( rsin( f224 * 32 ) - rsin( ( f224 - 1 ) * 32 ) ) * 2;
}

void Hind2_800C4898( Hind2Work *work, int scale )
{
    work->f214.vx = scale;
    work->f214.vy = scale;
    work->f214.vz = scale;
    ScaleMatrix( &work->body.objs->world, &work->f214 );
}

int Hind2_800C48CC( Hind2Work *work )
{
    SVECTOR diff;
    int     ret;

    ret = 0;

    GV_SubVec3( &GM_PlayerPosition_800ABA10, &work->control.mov, &diff );

    if ( GV_VecLen3( &diff ) >= 10000 )
    {
        ret = 1;
    }

    if ( GM_PlayerPosition_800ABA10.vz >= -10000 )
    {
        ret = 2;
    }

    if ( GM_PlayerPosition_800ABA10.vx <= -7250 )
    {
        ret = 4;
    }

    if ( work->f1FC == 6 && GM_PlayerPosition_800ABA10.vz <= -10000 )
    {
        ret = 3;
    }

    if ( work->f1FC == 7 && GM_PlayerPosition_800ABA10.vx >= -7250 )
    {
        ret = 5;
    }

    return ret;
}

static inline void Hind2PlaySound( Hind2Work *work, int val )
{
    printf( "%d\n", val );

    if ( GM_GameOverTimer == 0 )
    {
        switch ( val )
        {
        case 0:
            GM_SeSetMode( &work->f28C, 187, GM_SEMODE_BOMB );
            break;

        case 1:
            GM_SeSetMode( &work->f28C, 188, GM_SEMODE_BOMB );
            break;

        case 2:
            GM_SeSetMode( &work->f28C, 189, GM_SEMODE_BOMB );
            break;

        case 3:
            GM_SeSetMode( &work->f28C, 190, GM_SEMODE_BOMB );
            break;
        }

        work->f2A4 = 1;
    }
}

void Hind2_800C499C( Hind2Work *work )
{
    SVECTOR sp10;
    int     scale;
    int     seg;
    int     rnd;

    switch ( work->f1FC )
    {
    case 0:
        Hind2_800C4468( work, 1 );

        if ( GM_PlayerPosition_800ABA10.vz <= -15000 && work->f234 != 0 )
        {
            DG_VisibleObjs( work->body.objs );
            work->f1FC = 1;
            GM_SeSetMode( &work->f28C, 180, GM_SEMODE_BOMB );
            work->f200 = 0;
            Hind2_800C4898( work, 2925 );
            Hind2_800C44C4( work );
            GCL_ExecProc( work->f288, NULL );
        }
        break;

    case 1:
        Hind2_800C4430( work );
        Hind2_800C4468( work, 0 );
        work->f1E4.vy += 500;

        scale = ( ( work->f200 * 2 + 100 ) * 4096 ) / 140;
        Hind2_800C4898( work, scale );
        Hind2_800C44C4( work );

        if ( work->f200 > 19 )
        {
            work->f1FC = 2;
            work->f200 = 0;
        }
        break;

    case 2:
        Hind2_800C4430( work );
        Hind2_800C4468( work, 0 );
        Hind2_800C44C4( work );
        Hind2_800C47C8( work );
        DG_InvisiblePrim( work->prim );

        if ( work->f200 >= 60 )
        {
            work->f1FC = 3;
            work->f228 = GM_PlayerPosition_800ABA10;
            work->f200 = 0;

            if ( work->f2A4 != 0 )
            {
                work->f2A4 = 0;
                break;
            }

            rnd = GV_RandU( 4 );
            Hind2PlaySound( work, rnd );
        }
        break;

    case 3:
        Hind2_800C4430( work );
        Hind2_800C4468( work, 0 );
        Hind2_800C44C4( work );
        Hind2_800C47C8( work );

        sp10.vx = work->f228.vx - ( work->f200 - 15 ) * 150;
        sp10.vy = work->f228.vy;
        sp10.vz = work->f228.vz;
        Hind2_800C45E4( work, sp10 );

        if ( work->f200 > 30 || GM_PlayerPosition_800ABA10.vx <= -7500 )
        {
            work->f1FC = 4;
            work->f200 = 0;
        }
        break;

    case 4:
        Hind2_800C4430( work );
        Hind2_800C4468( work, 0 );
        Hind2_800C44C4( work );
        Hind2_800C47C8( work );
        DG_InvisiblePrim( work->prim );

        seg = Hind2_800C48CC( work );
        switch ( seg )
        {
        case 0:
            work->f1FC = 2;
            work->f200 = 0;
            break;

        case 1:
            work->f1FC = 5;
            work->f230 = ( GM_PlayerPosition_800ABA10.vx - work->control.mov.vx ) / 100;
            work->f200 = 0;
            break;

        case 2:
            work->f1FC = 6;
            work->f200 = 0;
            break;

        case 4:
            work->f1FC = 7;
            work->f200 = 0;
            break;
        }
        break;

    case 5:
        Hind2_800C4430( work );
        Hind2_800C4468( work, 0 );
        Hind2_800C44C4( work );
        Hind2_800C47A4( work );
        Hind2_800C47C8( work );
        DG_InvisiblePrim( work->prim );

        if ( work->f200 >= 80 )
        {
            work->f1FC = 3;
            work->f228 = GM_PlayerPosition_800ABA10;
            work->f200 = 0;

            if ( work->f2A4 != 0 )
            {
                work->f2A4 = 0;
                break;
            }

            rnd = GV_RandU( 4 );
            Hind2PlaySound( work, rnd );
        }
        break;

    case 6:
        Hind2_800C4430( work );
        Hind2_800C4468( work, 0 );
        Hind2_800C44C4( work );
        Hind2_800C47C8( work );
        DG_InvisiblePrim( work->prim );

        seg = Hind2_800C48CC( work );
        if ( seg == 3 )
        {
            work->f1FC = 3;
            work->f228 = GM_PlayerPosition_800ABA10;
            work->f200 = 0;

            if ( work->f2A4 != 0 )
            {
                work->f2A4 = 0;
                break;
            }

            rnd = GV_RandU( 4 );
            Hind2PlaySound( work, rnd );
        }
        break;

    case 7:
        Hind2_800C4430( work );
        Hind2_800C4468( work, 1 );
        Hind2_800C44C4( work );
        Hind2_800C47C8( work );
        DG_InvisiblePrim( work->prim );

        seg = Hind2_800C48CC( work );
        if ( seg == 5 )
        {
            work->f1FC = 2;
            work->f228 = GM_PlayerPosition_800ABA10;
            work->f200 = 0;
        }
        break;

    case 8:
        Hind2_800C4430( work );
        Hind2_800C4468( work, 1 );
        work->f1E4.vy -= 300;
        scale = ( ( 140 - work->f200 * 2 ) * 4096 ) / 140;
        Hind2_800C44C4( work );
        Hind2_800C4898( work, scale );
        DG_InvisiblePrim( work->prim );

        if ( work->f200 > 29 )
        {
            work->f1FC = 9;
            work->f200 = 0;
            DG_InvisibleObjs( work->body.objs );
            GM_ConfigControlAttribute( &work->control, 0 );
        }

        if ( work->f200 == 2 )
        {
            GM_SeSetMode( &work->f28C, 186, GM_SEMODE_BOMB );
        }
        break;

    case 9:
        break;
    }

    if ( work->f1FC >= 2 && work->f1FC != 8 && work->f1FC != 9 && GM_CurrentWeaponId == WEAPON_STINGER )
    {
        work->f1FC = 8;
        work->f200 = 0;
        DG_InvisiblePrim( work->prim );
    }

}

void Hind2_800C5188( Hind2Work *work )
{
    SVECTOR sp10;
    VECTOR  sp18;
    int     ang;

    if ( work->f1FC == 3 )
    {
        sp10.vx = work->f228.vx - ( work->f200 - 15 ) * 150;
        sp10.vy = work->f228.vy;
        sp10.vz = work->f228.vz;

        Hind2_800C43F0( &sp10, &work->control.mov, &sp18 );

        ang = ratan2( sp18.vx, sp18.vz ) - work->control.turn.vy;
        if ( ang < 0 )
        {
            ang += 4096;
        }

        work->adjust[ 4 ].vy = ang;
    }
    else if ( work->adjust[ 4 ].vy <= 2048 )
    {
        work->adjust[ 4 ].vy -= work->adjust[ 4 ].vy / 2;
    }
    else
    {
        work->adjust[ 4 ].vy += ( 4096 - work->adjust[ 4 ].vy ) / 2;
    }
}

void Hind2_800C5274( Hind2Work *work )
{
    int     n_msgs;
    GV_MSG *msg;

    if ( work->control.field_56 == 0 )
    {
        return;
    }

    n_msgs = work->control.field_56;
    msg = &work->control.field_5C_mesg[ n_msgs ] - 1;

    for ( ; n_msgs > 0; n_msgs--, msg-- )
    {
        switch ( msg->message[ 0 ] )
        {
        case 0x7075:
            work->f2A8 = 1;
            printf( "up message\n" );
            break;

        case HASH_KILL:
            printf( "die message\n" );
            GV_DestroyActor( &work->actor );
            break;
        }
    }
}

void Hind2Act( Hind2Work *work )
{
    CONTROL *control;
    OBJECT  *body;

    control = &work->control;
    body = &work->body;

    GM_ActControl( control );
    GM_ActObject2( body );

    DG_GetLightMatrix( &control->mov, work->light );

    work->f28C.vx = ( GM_PlayerPosition_800ABA10.vx * 3 + work->control.mov.vx ) / 4;
    work->f28C.vy = ( GM_PlayerPosition_800ABA10.vy * 3 + work->control.mov.vy ) / 4;
    work->f28C.vz = ( GM_PlayerPosition_800ABA10.vz * 3 + work->control.mov.vz ) / 4;

    Hind2_800C5274( work );

    if ( work->f2A8 > 0 && work->f2A8 < 35 && ++work->f2A8 == 35 )
    {
        work->f234 = 1;
    }

    Hind2_800C499C( work );
    Hind2_800C5188( work );

    work->f200++;
    work->f224++;

    work->control.mov.vy += work->control.step.vy;
}

void Hind2Die( Hind2Work *work )
{
    DG_PRIM *prim;

    GM_FreeControl( &work->control );
    GM_FreeObject( &work->body );

    prim = work->prim;
    if ( prim )
    {
        DG_DequeuePrim( prim );
        DG_FreePrim( prim );
    }
}

int Hind2_800C54C8( Hind2Work *work )
{
    RECT     *prim_rect;
    DG_PRIM  *prim;
    DG_TEX   *tex;
    int       i;
    POLY_FT4 *poly;
    int       x, y, w, h;

    prim_rect = &work->prim_rect;
    prim_rect->x = 400;
    prim_rect->y = 400;
    prim_rect->w = 800;
    prim_rect->h = 800;

    work->vertices[ 0 ] = DG_ZeroVector;

    work->prim = prim = DG_GetPrim( DG_PRIM_OFFSET | DG_PRIM_POLY_FT4, 1, 0, work->vertices, prim_rect );
    if ( !prim )
    {
        return -1;
    }

    tex = work->tex = DG_GetTexture( GV_StrCode( "socom_f" ) );

    for ( i = 0; i < 2; i++ )
    {
        poly = (POLY_FT4 *)prim->packs[ i ];

        setPolyFT4( poly );
        setRGB0( poly, 128, 128, 128 );
        setSemiTrans( poly, 1 );

        x = tex->off_x;
        w = tex->w + 1;
        poly->u0 = poly->u2 = x;
        poly->u1 = poly->u3 = x + w / 2 - 1;

        y = tex->off_y;
        h = tex->h + 1;
        poly->v0 = poly->v1 = y;
        poly->v2 = poly->v3 = y + h / 2 - 1;

        poly->tpage = tex->tpage;
        poly->clut = tex->clut;

        poly->tpage = ( poly->tpage & ~0x60 ) | 0x20;
    }

    DG_InvisiblePrim( prim );
    return 0;
}

int Hind2GetResources( Hind2Work *work, int name, int map )
{
    CONTROL *control;
    char    *pos;
    char    *dir;
    char    *model;
    OBJECT  *body;
    int      i;

    control = &work->control;

    if ( GM_InitControl( control, name, map ) < 0 )
    {
        return -1;
    }

    pos = GCL_GetOption( 'p' );
    dir = GCL_GetOption( 'd' );
    GM_ConfigControlString( control, pos, dir );

    GM_ConfigControlAttribute( control, 1 );
    GM_ConfigControlTrapCheck( control );
    GM_ConfigControlHazard( control, 0, -2, -2 );

    control->field_59 = 2;

    model = GCL_GetOption( 'm' );
    if ( !model )
    {
        return -1;
    }

    work->f1E4.vx = work->control.mov.vx;
    work->f1E4.vy = work->control.mov.vy;
    work->f1E4.vz = work->control.mov.vz;

    body = &work->body;
    GM_InitObject( body, GCL_StrToInt( model ), BODY_FLAG, 0 );
    GM_ConfigObjectJoint( body );
    GM_ConfigObjectLight( body, work->light );

    DG_InvisibleObjs( body->objs );

    if ( GCL_GetOption( 'w' ) )
    {
        work->f1E0[ 0 ] = GCL_StrToInt( GCL_GetParamResult() );
        work->f1E0[ 1 ] = GCL_StrToInt( GCL_GetParamResult() );
    }
    else
    {
        work->f1E0[ 0 ] = 0;
        work->f1E0[ 1 ] = 0;
    }

    if ( GCL_GetOption( 'g' ) )
    {
        GCL_StrToSV( GCL_GetParamResult(), &work->f1F4 );
    }
    else
    {
        work->f1F4 = s11i_800C32C0;
    }

    if ( GCL_GetOption( 'e' ) )
    {
        work->f288 = GCL_StrToInt( GCL_GetParamResult() );
    }
    else
    {
        work->f288 = -1;
    }

    work->f1FC = 0;
    work->f200 = 0;
    work->f224 = 0;
    work->f234 = 0;
    work->f2A4 = 1;
    work->f2A8 = 0;

    for ( i = 0; i < 10; i++ )
    {
        work->adjust[ i ].vx = 0;
        work->adjust[ i ].vy = 0;
        work->adjust[ i ].vz = 0;
    }

    GM_ConfigMotionAdjust( &work->body, work->adjust );

    if ( Hind2_800C54C8( work ) < 0 )
    {
        return -1;
    }

    return 0;
}

void *NewHind2( int name, int where )
{
    Hind2Work *work;

    work = (Hind2Work *)GV_NewActor( EXEC_LEVEL, sizeof(Hind2Work) );
    if ( work )
    {
        GV_SetNamedActor( &work->actor, Hind2Act, Hind2Die, "hind2.c" );

        if ( Hind2GetResources( work, name, where ) >= 0 )
        {
            work->name = name;
            return work;
        }

        GV_DestroyActor( &work->actor );
    }

    return NULL;
}
