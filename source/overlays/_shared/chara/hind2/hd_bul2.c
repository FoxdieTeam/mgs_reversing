#include "libdg/libdg.h"
#include "libgv/libgv.h"
#include "game/game.h"
#include "linkvar.h"
#include "okajima/spark.h"

typedef struct _HdBul2Work
{
    GV_ACT   actor;
    CONTROL  control;
    TARGET   target;
    int      fE4;
    int      enable;
    int      map;
    SVECTOR  pos;
    DG_PRIM *prim;
    SVECTOR  vertices[16];
} HdBul2Work;

SVECTOR s11i_800C32C8 = {200, 200, 200, 0};

#define EXEC_LEVEL GV_ACTOR_LEVEL5

int HdBul2_800C5920( HdBul2Work *work )
{
    SVECTOR mov;
    SVECTOR scaled;
    SVECTOR diff;
    int     hit;

    if ( !work->enable )
    {
        return 0;
    }

    mov = work->control.mov;

    GV_SubVec3( &work->pos, &mov, &diff );
    GV_LenVec3( &diff, &scaled, GV_VecLen3( &diff ), 2000 );
    GV_AddVec3( &mov, &scaled, &scaled );

    hit = GM_Target_8002E1B8( &mov, &scaled, work->map, &scaled, ENEMY_SIDE );
    if ( hit != 0 )
    {
        GM_MoveTarget( &work->target, &scaled );
        GM_PowerTarget( &work->target );
    }

    return hit;
}

void HdBul2_800C5A14( HdBul2Work *work )
{
    SVECTOR step;
    SVECTOR rot;

    step = work->control.step;
    rot = DG_ZeroVector;

    rot.vy = ratan2( step.vx, step.vz );
    rot.vx = -ratan2( step.vy, SquareRoot0( step.vx * step.vx + step.vz * step.vz ) );

    RotMatrixYXZ( &rot, &work->prim->world );

    work->prim->world.t[ 0 ] = work->control.mov.vx;
    work->prim->world.t[ 1 ] = work->control.mov.vy;
    work->prim->world.t[ 2 ] = work->control.mov.vz;
}

void HdBul2Act( HdBul2Work *work )
{
    MATRIX    world;
    SVECTOR   rot;
    VECTOR    scale;
    POLY_FT4 *poly;
    int       i;

    GM_ActControl( &work->control );

    work->fE4 -= 2000;
    work->control.mov.vy += work->control.step.vy;

    HdBul2_800C5A14( work );

    if ( !HdBul2_800C5920( work ) )
    {
        if ( work->fE4 <= 0 )
        {
            rot.vx = -1024;
            rot.vy = rot.vz = 0;
            RotMatrixYXZ( &rot, &world );

            world.t[ 0 ] = work->pos.vx;
            world.t[ 1 ] = work->pos.vy;
            world.t[ 2 ] = work->pos.vz;

            GM_SeSet( &work->pos, 178 );

            scale.vx = scale.vy = scale.vz = 8192;
            ScaleMatrix( &world, &scale );

            NewSpark( &world, 1 );
        }
        else
        {
            return;
        }
    }

    poly = (POLY_FT4 *)work->prim->packs[ GV_Clock ];
    for ( i = 0; i < 4; i++ )
    {
        setRGB0( poly, 0, 0, 0 );
        poly++;
    }

    GV_DestroyActor( &work->actor );
}

void HdBul2Die( HdBul2Work *work )
{
    GM_FreeControl( &work->control );
    GM_FreePrim( work->prim );
}

int HdBul2_800C5C68( HdBul2Work *work, SVECTOR *arg1 )
{
    SVECTOR  sp18;
    SVECTOR  sp20;
    SVECTOR  sp28;
    int      hit;
    int      len;

    hit = 0;

    sp18 = work->control.mov;
    sp20 = *arg1;

    if ( HZD_80028454( work->control.map->hzd, &sp18, &sp20, 0x5, 0x4 ) )
    {
        HZD_GetSpadVector( &sp20 );
        hit = 1;
        work->pos = sp20;
    }

    if ( hit != 0 )
    {
        GV_SubVec3( &sp20, &sp18, &sp18 );
        len = GV_VecLen3( &sp18 );
    }
    else
    {
        work->pos = *arg1;
        GV_SubVec3( arg1, &work->control.mov, &sp28 );
        len = GV_VecLen3( &sp28 );
    }

    return len;
}

int HdBul2_800C5DB4( HdBul2Work *work )
{
    SVECTOR  *vertices;
    DG_PRIM  *prim;
    DG_TEX   *tex;
    int       i, j;
    POLY_FT4 *poly;
    int       rnd;
    int       x, y, w, h;

    vertices = work->vertices;
    prim = work->prim = DG_GetPrim( DG_PRIM_POLY_FT4, 4, 0, vertices, 0 );
    if ( !prim )
    {
        return -1;
    }

    tex = DG_GetTexture( GV_StrCode( "bullet" ) );
    if ( !tex )
    {
        return -1;
    }

    for ( i = 0; i < 2; i++ )
    {
        poly = (POLY_FT4 *)prim->packs[ i ];

        for ( j = 0; j < 4; j++ )
        {
            setPolyFT4( poly );

            rnd = GV_RandU( 128 );
            poly->r0 = rnd - 32;
            poly->g0 = ( ( rnd - 32 ) / 3 ) * 2;
            poly->b0 = ( ( rnd - 32 ) / 3 ) * 2;

            setSemiTrans( poly, 1 );

            x = tex->off_x;
            w = tex->w;
            y = tex->off_y;
            h = tex->h;
            setUVWH( poly, x, y, w, h );

            poly->tpage = tex->tpage;
            poly->clut = tex->clut;

            poly->tpage |= 0x20;

            poly++;
        }
    }

    prim->world = DG_ZeroMatrix;

    for ( i = 0; i < 16; i++, vertices++ )
    {
        if ( i < 4 )
        {
            if ( i & 2 )
            {
                vertices->vz = 750;
            }
            else
            {
                vertices->vz = 0;
            }

            if ( i & 1 )
            {
                vertices->vx = 16;
            }
            else
            {
                vertices->vx = -16;
            }

            vertices->vy = 0;
        }
        else if ( i < 8 )
        {
            if ( i & 2 )
            {
                vertices->vz = 750;
            }
            else
            {
                vertices->vz = 0;
            }

            if ( i & 1 )
            {
                vertices->vx = -16;
            }
            else
            {
                vertices->vx = 16;
            }

            vertices->vy = 0;
        }
        else if ( i < 12 )
        {
            if ( i & 2 )
            {
                vertices->vz = 750;
            }
            else
            {
                vertices->vz = 0;
            }

            if ( i & 1 )
            {
                vertices->vy = -16;
            }
            else
            {
                vertices->vy = 16;
            }

            vertices->vx = 0;
        }
        else
        {
            if ( i & 2 )
            {
                vertices->vz = 750;
            }
            else
            {
                vertices->vz = 0;
            }

            if ( i & 1 )
            {
                vertices->vy = 16;
            }
            else
            {
                vertices->vy = -16;
            }

            vertices->vx = 0;
        }
    }

    return 0;
}

int HdBul2GetResources( HdBul2Work *work, SVECTOR *arg1, SVECTOR *arg2 )
{
    SVECTOR  diff;
    CONTROL *control;
    TARGET  *target;
    int      len;
    int      len2;
    SVECTOR *step;

    control = &work->control;

    if ( GM_InitControl( control, 0, 0 ) < 0 )
    {
        return -1;
    }

    work->control.mov = *arg1;
    work->control.rot = work->control.turn = DG_ZeroVector;

    GM_ConfigControlHazard( control, 0, -2, -2 );

    target = &work->target;
    GM_SetTarget( target, TARGET_POWER, ENEMY_SIDE, &s11i_800C32C8 );
    GM_Target_8002DCCC( target, 0, 1, GM_SnakeMaxHealth / 8, 0, &DG_ZeroVector );

    step = &work->control.step;
    GV_SubVec3( arg2, &control->mov, &diff );

    len = GV_VecLen3( &diff );

    len2 = HdBul2_800C5C68( work, arg2 );
    if ( len2 < 0 )
    {
        return -1;
    }

    work->fE4 = len2;

    GV_LenVec3( &diff, step, len, 2000 );

    work->map = GM_CurrentMap;

    if ( HdBul2_800C5DB4( work ) < 0 )
    {
        return -1;
    }

    return 0;
}

void *NewHdBul2( SVECTOR *arg0, SVECTOR *arg1, int enable )
{
    HdBul2Work *work;

    work = GV_NewActor( EXEC_LEVEL, sizeof(HdBul2Work) );
    if ( work )
    {
        GV_SetNamedActor( &work->actor, HdBul2Act, HdBul2Die, "hd_bul2.c" );

        if ( HdBul2GetResources( work, arg0, arg1 ) >= 0 )
        {
            work->enable = enable;
            return work;
        }

        GV_DestroyActor( &work->actor );
    }

    return NULL;
}
